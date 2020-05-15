//
// Created by Rafal on 5/14/20.
//

#ifndef MAIN_GAME_STRUCTURE_H
#define MAIN_GAME_STRUCTURE_H

typedef struct player_t player_t;
typedef struct pair_t pair_t;
typedef struct rect_t rect_t;
typedef enum move_t move_t;
typedef enum bool_t bool_t;
typedef struct game_object_t game_object_t;

struct pair_t
{
    int x,y;
};

struct rect_t
{
    pair_t cords; //cords of left upper corner
    int width, height; //not point to make things simple
};

struct player_t
{
    rect_t player_rect;
    int vel;
};

//DEPEND ON CLIENT PREFERENCES
enum move_t
{
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
    END = 5,
    BEYOND = 6,
};

struct game_object_t
{
    int obstacles_number;
    rect_t* obstacles;
    int players_index;
    player_t* players;
    int board_width,board_height; //not point to make things simple
};

#endif //MAIN_GAME_STRUCTURE_H
