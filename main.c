#include <SDL.h>
#include "graphics.h"
#include "map.h"

void keyHandler(SDL_KeyboardEvent *key, int* quitter){
    if(key->keysym.scancode == SDL_SCANCODE_UP) {
        pl.player_rect.cords.y-=4;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_DOWN) {
        pl.player_rect.cords.y+=4;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_RIGHT) {
        pl.player_rect.cords.x+=4;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_LEFT) {
        pl.player_rect.cords.x-=4;
    }
    else if(key->keysym.scancode == SDL_SCANCODE_ESCAPE) {
        *quitter = 0;
    }
}

int main()
{
    colour backDolor = BACKGROUND_COLOUR;
    initWindow();

    int keep_window_open = 1;
    while(keep_window_open)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    keep_window_open = 0;
                    break;
                case SDL_KEYDOWN:
                    keyHandler(&e.key, &keep_window_open);
                    break;
            }
        }
        colourBackground(backDolor);

        drawPlayer(pl);

        drawObstacles(go.obstacles, go.obstacles_number);

        updateScreen();
    }
    quitSDL();

    return EXIT_SUCCESS;
}