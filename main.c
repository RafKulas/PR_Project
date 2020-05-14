#include <SDL.h>
#include "graphics.h"
#include "map.h"

void PrintKeyInfo( SDL_KeyboardEvent *key ){
    if( key->type == SDL_KEYUP )
        printf( "Release:- " );
    else
        printf( "Press:- " );
    printf( "Scancode: 0x%02X", key->keysym.scancode );
    printf( ", Name: %s \n", SDL_GetKeyName( key->keysym.sym ) );

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
                case SDL_KEYUP:
                    PrintKeyInfo( &e.key );
                    break;
            }
        }
        colourBackground(backDolor);

        drawObstacles(go.obstacles, go.obstacles_number);

        updateScreen();
    }
    quitSDL();

    return EXIT_SUCCESS;
}