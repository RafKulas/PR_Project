#include "game_structure.h"
#include <sys/types.h>
#include <sys/socket.h>

#define NO_FLAGS 0

#define INT_SIZE sizeof(int)
#define RECT_SIZE sizeof(rect_t)
#define PLAYER_SIZE sizeof(player_t)

#define BUFOR_SIZE_INT 1024
#define BUFOR_SIZE_CHAR BUFOR_SIZE_INT * INT_SIZE

#define BUFOR_START 0