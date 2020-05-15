#include "game_structure.h"
/*
typedef struct player_t player_t;
typedef struct pair_t pair_t;
typedef struct rect_t rect_t;
typedef enum move_t move_t;
typedef enum bool_t bool_t;
typedef struct game_object_t game_object_t;

//just point
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
*/
enum bool_t
{
    FALSE,
    TRUE,
};
/*
struct game_object_t
{
    int obstacles_number;
    rect_t* obstacles;
    int players_index;
    player_t* players;
    int board_width,board_height; //not point to make things simple
};
*/

void init_player(player_t** player);

void remove_player(player_t** player);

void make_move(player_t** player, move_t move);

void init_game(int max_client_number);

bool_t check_obstacles(rect_t rect);

int min(int a, int b);

int max(int a, int b);

void send_s(int socket);

void printGame();