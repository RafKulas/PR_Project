#include "connection.h"
#include <stdlib.h>
#include <stdio.h>

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

void debug_printf(game_object* data)
{
    printf("data.obstacles_number = %d\n", data->obstacles_number);
    for (int i = 0; i < data->obstacles_number; ++i)
    {
        printf("i = %d\n", i);
        printf("data.obstacles[i].cords.x = %d\n", data->obstacles[i].cords.x);
        printf("data.obstacles[i].cords.y = %d\n", data->obstacles[i].cords.y);
        printf("data.obstacles[i].width = %d\n", data->obstacles[i].width);
        printf("data.obstacles[i].height = %d\n", data->obstacles[i].height);
    }
    printf("data.players_index =  %d\n", data->players_amount);
    for (int i = 0; i < data->players_amount; ++i)
    {
        printf("i = %d\n", i);
        printf("data.players[i].player_rect.cords.x = %d\n", data->players[i].player_rect.cords.x);
        printf("data.players[i].player_rect.cords.y = %d\n", data->players[i].player_rect.cords.y);
        printf("data.players[i].player_rect.width = %d\n", data->players[i].player_rect.width);
        printf("data.players[i].player_rect.height = %d\n", data->players[i].player_rect.height);
        printf("data.players[i].vel = %d\n", data->players[i].vel);
    }
    printf("data.board_width = %d\n", data->board_width);
    printf("data.board_height = %d\n", data->board_height);
}

void recv_structure(int sock, game_object* pdata)
{

	int buffer[BUFOR_SIZE_INT];
	recv(sock, (char *)buffer, BUFOR_SIZE_CHAR, NO_FLAGS);
    if(buffer[BUFOR_START] == 0) {
        return;
    }
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
	debug_printf(pdata);
}