//
// Created by Rafal on 5/14/20.
//

#ifndef MAIN_GAME_STRUCTURE_H
#define MAIN_GAME_STRUCTURE_H

typedef struct
{
    int x, y;
} pair;

typedef struct
{
    pair cords;
    int width, height;
} rect;

typedef struct
{
    rect player_rect;
    int vel;
} player;

typedef struct
{
    int obstacles_number;
    rect* obstacles;
    int players_amount;
    player* players;
    int board_width, board_height;
} game_object;

#endif //MAIN_GAME_STRUCTURE_H
