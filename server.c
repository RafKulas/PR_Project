#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "game.h"
#include "priority_queue_list.h"

#define MAX_CLIENT_NUMBER 3
#define PORT 8080
#define BACKLOG 10

typedef struct client_t client_t;
typedef struct client_move_t client_move_t;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
typedef struct clients_array_t clients_array_t;

void check(int result, const char* message);
void accept_handler(int client_socket);
void* client_listener(void* client_socket);
void remove_client(int socket);
int find_index(int socket);
void* moves_handler(void* sth);


struct client_t
{
    player_t* pplayer; //pointer to player - connected with game
    int client_socket; //id of connection with client
};

struct client_move_t
{
    int client_socket; //index in clients_array
    move_t move; //move, that client send to us
};

struct clients_array_t
{
    client_t* clients_array; //array of clients, that stores its socket id
    int* requests;
    int index;
}clients_array;

//queue, that stores all clients moves, which have to be on plane
pqueue* moves_queue = NULL;
pthread_mutex_t clients_array_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t moves_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_variable = PTHREAD_COND_INITIALIZER;



int main()
{
    clients_array.clients_array = (client_t*)malloc(MAX_CLIENT_NUMBER*sizeof(client_t));
    clients_array.requests = (int*)calloc(MAX_CLIENT_NUMBER,sizeof(int));
    clients_array.index = 0;

    int server_socket, client_socket;
	sockaddr_in server_address;

    init_game(MAX_CLIENT_NUMBER);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0)
    {
        printf("Failed to create server socket\n");
        return 1;
    }
	memset(&server_address, '0', sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORT); 

    if(bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("Failed to bind\n");
        return 1;
    }

    if(listen(server_socket, BACKLOG) < 0)
    {
        printf("Failed to listen\n");
        return 1;
    }

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, moves_handler, NULL);

	for (;;) 
    {
		client_socket = accept(server_socket, (sockaddr*)NULL, NULL);
        if(client_socket<0)
        {
            printf("Failed to accept\n");
            return 1;
        }

		printf("Client connected\n");

        accept_handler(client_socket);
		
	}
    return 0;
}

void accept_handler(int client_socket)
{
    if(clients_array.index == MAX_CLIENT_NUMBER)
    {
        printf("No more clients, please\n");
        return;
    }
    
    pthread_mutex_lock(&clients_array_mutex);

    //initialize player at game side
    init_player(&clients_array.clients_array[clients_array.index].pplayer);

    //set connection id
    clients_array.clients_array[clients_array.index].client_socket = client_socket;

    //increase amount of players
    clients_array.index++;

    //first send to player
    send_s(client_socket);

    pthread_mutex_unlock(&clients_array_mutex);

    //create thread for new client
    pthread_t thread_id;
    int *pclient = (int*)malloc(sizeof(int));
    *pclient = client_socket;
    pthread_create(&thread_id, NULL, client_listener, (void*)pclient);
}

void* client_listener(void* client_socket)
{
    int socket = *(int *)client_socket;
	char* client_message = (char*)malloc(sizeof(char));
    *client_message = BEYOND; 
    int index;
	
	for(;;) 
    {
		//receive message
        recv(socket , client_message , 1 , 0);

        //if message is in accordance with contract with client
        if(*client_message>=UP && *client_message<=END)
        {
            //termination condition
            if(*client_message == END)
            {
                printf("Client left\n");
                break;
            }
            //increase number of client requests
            pthread_mutex_lock(&clients_array_mutex);

            index = find_index(socket);
            if(index!=-1)
            clients_array.requests[index]++;

            pthread_mutex_unlock(&clients_array_mutex);

            //set information about client
            client_move_t client_move;
            client_move.client_socket = socket;
            client_move.move = *client_message;

            pthread_mutex_lock(&moves_queue_mutex);

            qinsert(&moves_queue, &client_move, -clients_array.requests[index]);
            pthread_cond_signal(&condition_variable);

            pthread_mutex_unlock(&moves_queue_mutex);

        }
        *client_message = BEYOND;
	}
	remove_client(socket);
    free(client_message);
    free(client_socket);
	pthread_exit(NULL);
}

void remove_client(int socket)
{

    pthread_mutex_lock(&clients_array_mutex);

    int index = find_index(socket);

    //remove player at game side
    remove_player(&clients_array.clients_array[index].pplayer);

    for(int i=index;i<(clients_array.index-1);i++)
    {
        //move next element to previous one
        clients_array.clients_array[i].pplayer = clients_array.clients_array[i+1].pplayer;
        clients_array.clients_array[i].client_socket = clients_array.clients_array[i+1].client_socket;
        clients_array.requests[i] = clients_array.requests[i+1];
    }

    clients_array.index--;

    pthread_mutex_unlock(&clients_array_mutex);
}

int find_index(int socket)
{
    for(int i=0;i<clients_array.index;i++)
    {
        if(clients_array.clients_array[i].client_socket == socket)return i;
    }
    return -1;
}

void* moves_handler(void* sth)
{
    pqueue *help;
    for(;;)
    {
        //Obtain lock and pop message from queue when not empty
        pthread_mutex_lock(&moves_queue_mutex);

        pthread_cond_wait(&condition_variable, &moves_queue_mutex);
        help = qpop(&moves_queue);

        client_move_t* client_move = (client_move_t*)(help->data);
        pthread_mutex_unlock(&moves_queue_mutex);

        pthread_mutex_lock(&clients_array_mutex);

        int index = find_index(client_move->client_socket);

        free(help);

        if(index!=-1)
            make_move(&clients_array.clients_array[index].pplayer, client_move->move);

        //Broadcast message to all connected clients
        for(int i = 0; i < clients_array.index; i++)
        {
            int socket = clients_array.clients_array[i].client_socket;
            send_s(socket);
        }

        pthread_mutex_unlock(&clients_array_mutex);

        //if there is no clients
        if(clients_array.index == 0)break;
    }
    pthread_exit(NULL);    
}

