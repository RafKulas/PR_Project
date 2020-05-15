#include <SDL.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "graphics.h"
#include "map.h"
#include "game_structure.h"
#include "connection.h"

#define PORT 8080
#define IP "127.0.0.1"

int running = 1;
move_t direction = STOP;
game_object *game;
char buff[1];

void *keySender(void* add_sock){
    int sock = *(int*)add_sock;
    while(running) {
        if(direction!=STOP) {
            printf("ide, bo %d\n", direction);
            buff[0] = direction;
            send(sock, (char*)buff, 1, 0);
            SDL_Delay(64);
        }
    }
    printf("koncze\n");
    return  NULL;
}

void *mapReceiver(void* add_sock) {
    int sock = *(int*)add_sock;
    while(running) {
        recv_structure(sock, game);
    }
    printf("koncze\n");
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
        running = 0;
    }
}

int main()
{
    game = (game_object*)malloc(sizeof(game_object));
    game->obstacles = (rect*)malloc(sizeof(rect) * 100); // space for 100 obstacles
    game->players = (player*)malloc(sizeof(player) * 20); // space for 20 players

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

    pthread_t ks, mr;
    pthread_create(&ks, NULL, keySender, &sock);
    pthread_create(&mr, NULL, mapReceiver, &sock);


    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    running = 0;
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

        drawPlayer(pl);

        drawObstacles(gmap.obstacles, gmap.obstacles_number);

        updateScreen();
    }
    quitSDL();
    pthread_join(ks, NULL);
    pthread_join(mr, NULL);

    return EXIT_SUCCESS;
}