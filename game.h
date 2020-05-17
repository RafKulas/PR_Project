#include "game_structure.h"

void init_player(player_t** player);

void remove_player(player_t** player);

void make_move(player_t** player, move_t move);

void init_game(int max_client_number);

bool_t check_obstacles(rect_t_player rect);

int check_game_result(player_t** player);

int find_player_index(player_t** player);

void send_s(int socket);

void send_init_s(int socket);

void printGame();
