#include "game_structure.h"
#include <sys/types.h>
#include <sys/socket.h>

#define NO_FLAGS 0

#define CHAR_SIZE sizeof(char)
#define INT_SIZE sizeof(int)
#define RECT_SIZE sizeof(rect_t)
#define PLAYER_SIZE sizeof(player_t)

#define BUFOR_SIZE_CHAR 4096

#define BUFOR_START 0

void send_init_structure(int sock, game_object_t* pdata);
void send_structure(int sock, game_object_t* pdata);
void recv_init_structure(int sock, game_object_t* pdata);
void recv_structure(int sock, game_object_t* pdata);
void debug_printf(game_object_t* data);