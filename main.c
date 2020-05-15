#include <SDL.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "graphics.h"
#include "map.h"
#include "game_structure.h"

int running = 1;
move_t direction = STOP;
game_object *game;

void *keySender(void *socket_desc){
    //int sock = * (int *)socket_desc;
    int read_size;
    while(running) {
        if(direction!=STOP) {
            printf("ide, bo %d\n", direction);
            //write(sock , &direction , sizeof(direction));
            SDL_Delay(64);
        }
    }
    printf("koncze\n");
    return  NULL;
}

void *mapReceiver() {

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

    pthread_t thread_id;

    int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    colour backDolor = BACKGROUND_COLOUR;
    initWindow();

    pthread_t w;
    pthread_create(&w, NULL , keySender, NULL);

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
        colourBackground(backDolor);

        drawPlayer(pl);

        drawObstacles(gmap.obstacles, gmap.obstacles_number);

        updateScreen();
    }
    quitSDL();
    pthread_join(w, NULL);

    return EXIT_SUCCESS;
}