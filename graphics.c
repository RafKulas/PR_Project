//
// Created by Rafal on 5/13/20.
//

#include "graphics.h"
#define rect rect_t
#define player player_t

int initWindow() {
    WINDOW = SDL_CreateWindow("PR Project Client",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              BOARD_WIDTH,
                              BOARD_HEIGHT,
                              0);//SDL_WINDOW_BORDERLESS);
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
    RECT.x = toDraw.cords.x * 30;
    RECT.y = toDraw.cords.y * 30;
    RECT.h = toDraw.height * 30;
    RECT.w = toDraw.width * 30;
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

void drawSpeedSpots(rect* speed_spots, int speed_spots_no) {
    colour ss_col = SPEED_SPOT_COLOUR;
    for(int i=0; i< speed_spots_no; i++) {
        drawRect(speed_spots[i], ss_col);
    }
}

void drawPlayer(player p, colour c) {
    RECT.x = p.player_rect.cords.x;
    RECT.y = p.player_rect.cords.y;
    RECT.h = p.player_rect.size;
    RECT.w = p.player_rect.size;
    SDL_SetRenderDrawColor(RENDERER, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(RENDERER, &RECT);
}

void drawPlayers(player* pl, int player_amount) {
    for(int i = 0; i<player_amount; i++) {
        drawPlayer(pl[i], (colour){(100*i)%256, (90*i+60)%256, (i*30+100)%256, 255});
    }
}
