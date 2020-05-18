#ifndef MAIN_GAME_STRUCTURE_H
#define MAIN_GAME_STRUCTURE_H

typedef struct player_t player_t;
typedef struct pair_t pair_t;
typedef struct rect_t rect_t;
typedef struct pair_t_player pair_t_player;
typedef struct rect_t_player rect_t_player;
typedef enum move_t move_t;
typedef struct game_object_t game_object_t;

struct pair_t
{
	char x, y;
};

struct rect_t
{
	pair_t cords; //cords of left upper corner
	char width, height; //not point to make things simple
};

struct pair_t_player
{
	int x, y;
};

struct rect_t_player
{
	pair_t_player cords; //cords of left upper corner
	int size, game_result; //not point to make things simple
};

struct player_t
{
	rect_t_player player_rect;
	char vel;
	char id;
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
	char ID;
	char obstacles_number;
	rect_t* obstacles;
	char speed_spots_number;
	rect_t* speed_spots;
	char board_width, board_height; //not point to make things simple
	char players_index;
	player_t* players;
};

#endif //MAIN_GAME_STRUCTURE_H
