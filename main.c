#include <SDL.h>
#include "graphics.h"
#include "map.h"
#include  <pthread.h>
#include "game_structure.h"

int running = 1;
move_t direction = STOP;
game_object *go;

void *keySender(void *i){
    while(running) {
        if(direction!=STOP) {
            printf("ide, bo %d\n", direction);
            SDL_Delay(100);
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
    go = (game_object*)malloc(sizeof(game_object));

    memcpy(go, &gmap, sizeof(gmap));

    colour backDolor = BACKGROUND_COLOUR;
    initWindow();

    pthread_t w;
    pthread_create (&w, NULL , keySender, NULL);

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

        drawObstacles(go->obstacles, gmap.obstacles_number);

        updateScreen();
    }
    quitSDL();
    pthread_join(w, NULL);

    return EXIT_SUCCESS;
}