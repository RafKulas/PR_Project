//
// Created by Rafal on 5/13/20.
//

#include "graphics.h"

int initWindow() {
    WINDOW = SDL_CreateWindow("PR Project Client",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          BOARD_WIDTH,
                                          BOARD_HEIGHT,
                              SDL_WINDOW_BORDERLESS);
    RENDERER = NULL;
    if(!WINDOW)
    {
        return -1;
    }

    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
    return 0;
}

void colourBackground(colour color) {
    SDL_SetRenderDrawColor(RENDERER, color.r, color.g, color.b, color.a);
    SDL_RenderClear(RENDERER);
}

void drawRect(rect toDraw, colour color) {
    RECT.x = toDraw.cords.x;
    RECT.y = toDraw.cords.y;
    RECT.h = toDraw.height;
    RECT.w = toDraw.width;
    SDL_SetRenderDrawColor(RENDERER, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(RENDERER, &RECT);
}

void updateScreen() {
    SDL_RenderPresent(RENDERER);
    SDL_UpdateWindowSurface(WINDOW);
}

void quitSDL() {
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}

void drawObstacles(rect* obstacles, int no_obs) {
    colour obs_col = OBSTACLE_COLOUR;
    for(int i =0; i<no_obs; ++i) {
        drawRect(obstacles[i], obs_col);
    }
}

void drawPlayer(player p, colour c) {
    drawRect(p.player_rect, c);
}

void drawPlayers(player* pl, int player_amount) {
    for(int i = 0; i<player_amount; i++) {
        drawPlayer(pl[i], (colour){(100*i)%256, (99*i+60)%256, (i*30+100)%256, 255});
    }
}