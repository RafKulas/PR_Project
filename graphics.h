//
// Created by Rafal on 5/13/20.
//

#ifndef MAIN_GRAPHICS_H
#define MAIN_GRAPHICS_H

#include <SDL.h>
#include "game_structure.h"

#define BOARD_WIDTH     960
#define BOARD_HEIGHT    480
#define PLAYER_WIDTH    8
#define PLAYER_HEIGHT   16

#define WHITE {255, 255, 255, 255}
#define BLACK {0, 0, 0, 255}
#define OBSTACLE_COLOUR BLACK
#define BACKGROUND_COLOUR WHITE



typedef struct
{
    int r;
    int g;
    int b;
    int a;
} colour;

SDL_Rect RECT;
SDL_Window *WINDOW;
SDL_Renderer *RENDERER;

int initWindow();
void drawRect(rect toDraw, colour color);
void colourBackground(colour color);
void updateScreen();
void quitSDL();
void drawObstacles(rect* obstacles, int no_obs);


#endif //MAIN_GRAPHICS_H
