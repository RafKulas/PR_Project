struct pair_t
{
	int x, y;
};

struct rect_t
{
	pair_t cords;
	int width, height;
};

struct player_t
{
	rect_t player_rect;
	int vel;
};

struct game_object_t
{
	int obstacles_number;
	rect_t* obstacles;
	int players_index;
	player_t* players;
	int board_width, board_height;
};