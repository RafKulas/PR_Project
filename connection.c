#include "connection.h"
#include <stdlib.h>

void send_structure(int sock, game_object* pdata)
{
	int buffer[BUFOR_SIZE_INT];

	buffer[BUFOR_START] = pdata->obstacles_number;

	for (int i = 0; i < pdata->obstacles_number; ++i)
	{
		buffer[RECT_SIZE * i + 1] = pdata->obstacles[i].cords.x;
		buffer[RECT_SIZE * i + 2] = pdata->obstacles[i].cords.y;
		buffer[RECT_SIZE * i + 3] = pdata->obstacles[i].width;
		buffer[RECT_SIZE * i + 4] = pdata->obstacles[i].height;
	}

	buffer[1 + buffer[0] * RECT_SIZE] = pdata->players_amount;


	for (int i = 0; i < pdata->players_amount; ++i)
	{
		buffer[PLAYER_SIZE * i + 2 + buffer[0] * RECT_SIZE] = pdata->players[i].player_rect.cords.x;
		buffer[PLAYER_SIZE * i + 3 + buffer[0] * RECT_SIZE] = pdata->players[i].player_rect.cords.y;
		buffer[PLAYER_SIZE * i + 4 + buffer[0] * RECT_SIZE] = pdata->players[i].player_rect.width;
		buffer[PLAYER_SIZE * i + 5 + buffer[0] * RECT_SIZE] = pdata->players[i].player_rect.height;
		buffer[PLAYER_SIZE * i + 6 + buffer[0] * RECT_SIZE] = pdata->players[i].vel;
	}

	buffer[1 + buffer[0] * RECT_SIZE + 1 + buffer[1 + buffer[0] * RECT_SIZE] * PLAYER_SIZE] = pdata->board_width;
	buffer[1 + buffer[0] * RECT_SIZE + 1 + buffer[1 + buffer[0] * RECT_SIZE] * PLAYER_SIZE + 1] = pdata->board_height;

	send(sock, (char *)(buffer), (1 + buffer[0] * RECT_SIZE + 1 + buffer[1 + buffer[0] * RECT_SIZE] * PLAYER_SIZE + 1 + 1) * INT_SIZE, NO_FLAGS);
}

void recv_structure(int sock, game_object* pdata)
{
	int buffer[BUFOR_SIZE_INT];
	recv(sock, (char *)buffer, BUFOR_SIZE_CHAR, NO_FLAGS);

	pdata->obstacles_number = buffer[BUFOR_START];

	for (int i = 0; i < pdata->obstacles_number; ++i)
	{
		pdata->obstacles[i].cords.x = buffer[RECT_SIZE * i + 1];
		pdata->obstacles[i].cords.y = buffer[RECT_SIZE * i + 2];
		pdata->obstacles[i].width  = buffer[RECT_SIZE * i + 3];
		pdata->obstacles[i].height = buffer[RECT_SIZE * i + 4];
	}

	pdata->players_amount = buffer[1 + buffer[0] * RECT_SIZE];

	for (int i = 0; i < pdata->players_amount; ++i)
	{
		pdata->players[i].player_rect.cords.x = buffer[PLAYER_SIZE * i + 2 + buffer[0] * RECT_SIZE];
		pdata->players[i].player_rect.cords.y = buffer[PLAYER_SIZE * i + 3 + buffer[0] * RECT_SIZE];
		pdata->players[i].player_rect.width   = buffer[PLAYER_SIZE * i + 4 + buffer[0] * RECT_SIZE];
		pdata->players[i].player_rect.height  = buffer[PLAYER_SIZE * i + 5 + buffer[0] * RECT_SIZE];
		pdata->players[i].vel				  = buffer[PLAYER_SIZE * i + 6 + buffer[0] * RECT_SIZE];
	}

	pdata->board_width  = buffer[1 + buffer[0] * RECT_SIZE + 1 + buffer[1 + buffer[0] * RECT_SIZE] * PLAYER_SIZE];
	pdata->board_height = buffer[1 + buffer[0] * RECT_SIZE + 1 + buffer[1 + buffer[0] * RECT_SIZE] * PLAYER_SIZE + 1];
}