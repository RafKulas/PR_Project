#include <SDL.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "graphics.h"
#include "game_structure.h"
#include "connection.h"

#define PORT 8080
//#define IP "127.0.0.1"
#define IP "153.19.216.3"
#define _ID game1->ID

#define rect rect_t
#define player player_t
#define game_object game_object_t

#define WIN 1
#define LOSE 2
#define PLAY 3
#define NOT_PLAY 4

int running = 1;
move_t direction = STOP;
game_object *game1, *game2;
char buff[1];

pthread_mutex_t map_mutex = PTHREAD_MUTEX_INITIALIZER;

void swap(void** one, void** two) {
    void* temp = *one;
    *one = *two;
    *two = temp;
}

void *keySender(void* add_sock){
    int sock = *(int*)add_sock;
    while(running) {
        if(direction!=STOP) {
            buff[0] = direction;
            send(sock, (char*)buff, 1, 0);
            if(direction == END) {
                running = 0;
            }
            SDL_Delay(100);
        }
    }
    return  NULL;
}

void *mapReceiver(void* add_sock) {
    int sock = *(int*)add_sock;
    while(running) {
        recv_structure(sock, game1);
        pthread_mutex_lock(&map_mutex);
        swap(&game1, &game2);
        pthread_mutex_unlock(&map_mutex);
    }
    return  NULL;
}

void keyHandler(SDL_KeyboardEvent *key){
    if(key->keysym.scancode == SDL_SCANCODE_UP) {
        direction = UP;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_DOWN) {
        direction = DOWN;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_RIGHT) {
        direction = RIGHT;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_LEFT) {
        direction = LEFT;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_ESCAPE) {
        direction = END;
    }
}

int main()
{
    game1 = (game_object*)malloc(sizeof(game_object));
    game1->obstacles = (rect*)malloc(sizeof(rect) * 100); // space for 100 obstacles
    game1->players = (player*)malloc(sizeof(player) * 20); // space for 20 players
    game1->speed_spots = (rect*)malloc(sizeof(rect) * 10); // space for 10 speed spots

    game2 = (game_object*)malloc(sizeof(game_object));
    game2->obstacles = (rect*)malloc(sizeof(rect) * 100); // space for 100 obstacles
    game2->players = (player*)malloc(sizeof(player) * 20); // space for 20 players
    game2->speed_spots = (rect*)malloc(sizeof(rect) * 10); // space for 10 speed spots


    /////////////socket
    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, IP, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }


    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    ///////////socket

    colour backColor = BACKGROUND_COLOUR;
    initWindow();

    recv_init_structure(sock, game2);
    game1->ID = game2->ID;
    game1->obstacles_number = game2->obstacles_number;
    for(int i = 0; i<game1->obstacles_number; ++i) {
        game1->obstacles[i].cords.x = game2->obstacles[i].cords.x;
        game1->obstacles[i].cords.y = game2->obstacles[i].cords.y;
        game1->obstacles[i].width   = game2->obstacles[i].width;
        game1->obstacles[i].height  = game2->obstacles[i].height;
    }
    game1->speed_spots_number = game2->speed_spots_number;
    for(int i = 0; i<game1->speed_spots_number; ++i) {
        game1->speed_spots[i].cords.x = game2->speed_spots[i].cords.x;
        game1->speed_spots[i].cords.y = game2->speed_spots[i].cords.y;
        game1->speed_spots[i].width   = game2->speed_spots[i].width;
        game1->speed_spots[i].height  = game2->speed_spots[i].height;
    }

    pthread_t ks, mr;
    pthread_create(&ks, NULL, keySender, &sock);
    pthread_create(&mr, NULL, mapReceiver, &sock);


    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            for(int i = 0; i<game2->players_index; i++) {
                if (game2->players[i].id == _ID) {
                    if(game2->players[i].player_rect.game_result==LOSE) {
                        //TODO
                        direction = END;
                        pthread_cancel(mr);
                        running = 0;
                        printf("\nPrzegrales :(\n");
                        return 0;

                    }
                    else if(game2->players[i].player_rect.game_result==WIN) {
                        //TODO
                        direction = END;
                        pthread_cancel(mr);
                        running = 0;
                        printf("\nWygrales :)\n");
                        return 0;

                    }
                    else {
                        i = game2->players_index;
                    }
                }
            }
            switch(e.type)
            {
                case SDL_QUIT:
                    direction = END;
                    pthread_cancel(mr);
                    break;
                case SDL_KEYDOWN:
                    keyHandler(&e.key);
                    break;
                case SDL_KEYUP:
                    direction = STOP;
                    break;
            }
        }
        colourBackground(backColor);

        drawObstacles(game2->obstacles, game2->obstacles_number);
        drawSpeedSpots(game2->speed_spots, game2->speed_spots_number);
        pthread_mutex_lock(&map_mutex);
        drawPlayers(game2->players, game2->players_index);
        pthread_mutex_unlock(&map_mutex);

        updateScreen();
    }
    quitSDL();
    pthread_cancel(ks);

    return EXIT_SUCCESS;
}
