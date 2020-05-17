#include "game.h"
#include "connection.h"
#include <stdlib.h>

#define OBSTACLES_NUMBER 19
#define BOARD_WIDTH     32
#define BOARD_HEIGHT    16
#define PLAYER_WIDTH 10 
#define PLAYER_HEIGHT 10 

//cords for player out of the board, for example before starting or after finishing
#define BANNED_X -10 
#define BANNED_Y -10 

//initial cords of player
#define START_X 50 
#define START_Y 50 

//initial vel of player
#define START_VEL 4 

game_object_t game_object;

rect_t obs[19] = {
        {{0,   0}, 32, 1},
        {{0,   0}, 1, 16},
        {{31,0}, 10, 16},
        {{0,   15}, 32, 1},
        {{1,  9}, 2,  6},
        {{13, 11}, 2,  4},
        {{21, 11}, 2,  4},
        {{17, 3},  2,  10},
        {{9, 3},  2,  10},
        {{25, 3},  2,  10}, //10
        {{27, 3},  2,  2},
        {{27, 11}, 2,  2},
        {{29, 7}, 2,  2},
        {{9, 5}, 18, 2},
        {{3,  5}, 4, 2}, //15
        {{7, 9}, 2,  4},
        {{5, 11}, 2,  2},
        {{13, 1},  2,  2},
        {{21, 1},  2,  2}
};


void init_player(player_t** player)
{

    //I guess server is smart and I don't get too many players
    *player = &(game_object.players[game_object.players_index]);
    (*player)->vel = START_VEL;
    (*player)->player_rect.cords.x = START_X;
    (*player)->player_rect.cords.y = START_Y;
    //width and height of players rect should be set previously

    game_object.players_index++;
}

void remove_player(player_t** player)
{
    int index;

    //search for index of player
    for(int i=0;i<game_object.players_index;i++)
    {
        //comapare address of player with address of array element
        if((*player) == &game_object.players[i])
        {
            index = i;
        }
    }

    //remove player from players array
    for(int i=index;i<(game_object.players_index-1);i++)
    {
        //move next element to previous one
        game_object.players[i].vel = game_object.players[i+1].vel;
        game_object.players[i].player_rect.cords.x = game_object.players[i+1].player_rect.cords.x; 
        game_object.players[i].player_rect.cords.y = game_object.players[i+1].player_rect.cords.y; 
    }

    game_object.players_index--;
}

void make_move(player_t** player, move_t move)
{
    rect_t hyp_player;
    pair_t max_cords;
    hyp_player.width = (*player)->player_rect.width;
    hyp_player.height = (*player)->player_rect.height;
    max_cords.x = hyp_player.cords.x = (*player)->player_rect.cords.x;
    max_cords.y = hyp_player.cords.y = (*player)->player_rect.cords.y;
    
    int i;

    //look for maximum speed, that player can go 
    for(i=0;i<=(*player)->vel;i++)
    {
        switch (move)
        {
            case UP:
                hyp_player.cords.y = (*player)->player_rect.cords.y - i;
                break;
            case DOWN:
                hyp_player.cords.y = (*player)->player_rect.cords.y + i;
                break;
            case LEFT:
                hyp_player.cords.x = (*player)->player_rect.cords.x - i;
                break;
            case RIGHT:
                hyp_player.cords.x = (*player)->player_rect.cords.x + i;
                break;
        }
        if(check_obstacles(hyp_player) == FALSE)
        {
            //we found out that player can't go with such speed, because of obsticles

            //set previous speed and return
            (*player)->player_rect.cords.x = max_cords.x;
            (*player)->player_rect.cords.y = max_cords.y;
            return;
        }
        else
        {
            max_cords.x = hyp_player.cords.x;
            max_cords.y = hyp_player.cords.y;
        }
    }
    (*player)->player_rect.cords.x = max_cords.x;
    (*player)->player_rect.cords.y = max_cords.y;
    return;
    
}

void init_game(int max_client_number)
{
    game_object.players = (player_t*)malloc(sizeof(player_t)*max_client_number);
    
    //to make sending easier
    game_object.obstacles_number = OBSTACLES_NUMBER;
    game_object.board_width = BOARD_WIDTH;
    game_object.board_height = BOARD_HEIGHT;
    
    game_object.players_index = 0;

    game_object.obstacles = (rect_t*)obs;

   for(int i=0;i<max_client_number;i++)
   {
       game_object.players[i].vel = 0;
       game_object.players[i].player_rect.height = PLAYER_HEIGHT;
       game_object.players[i].player_rect.width = PLAYER_WIDTH;
       game_object.players[i].player_rect.cords.x = BANNED_X;
       game_object.players[i].player_rect.cords.y = BANNED_Y;
   }
}

bool_t check_obstacles(rect_t rect)
{
    int xo,yo,wo,ho,xr,yr,wr,hr;
    xr = rect.cords.x;
    yr = rect.cords.y;
    hr = rect.height;
    wr = rect.width;
    //if player is not on board
    if(xr<0||xr>(BOARD_WIDTH-wr))return FALSE;
    if(yr<0||yr>(BOARD_HEIGHT-hr))return FALSE;
    for(int i=0;i<game_object.obstacles_number;i++)
    {
        xo = game_object.obstacles[i].cords.x;
        yo = game_object.obstacles[i].cords.y;
        wo = game_object.obstacles[i].width;
        ho = game_object.obstacles[i].height;
        
        //if player is in obstacle area
        if(xr>(xo-wr)&&xr<(xo+wo)&&
            yr>(yo-hr)&&yr<(yo+ho))return FALSE;
    }
    return TRUE;
}

int min(int a, int b)
{
    return a<b?a:b;
}

int max(int a, int b)
{
    return a>b?a:b;
}

void send_s(int socket)
{
    send_structure(socket, &game_object);
}

void send_init_s(int socket)
{
    send_init_structure(socket, &game_object);
}

void printGame() {
    debug_printf(&game_object);
}
