#include "connection.h"
#include <stdlib.h>
#include <stdio.h>

void send_init_structure(int sock, game_object_t* pdata)
{
	char buffer[BUFOR_SIZE_CHAR];

	buffer[BUFOR_START] = pdata->ID;

	buffer[1] = pdata->obstacles_number;

	for (int i = 0; i < pdata->obstacles_number; ++i)
	{
		buffer[RECT_SIZE * i + 2] = pdata->obstacles[i].cords.x;
		buffer[RECT_SIZE * i + 3] = pdata->obstacles[i].cords.y;
		buffer[RECT_SIZE * i + 4] = pdata->obstacles[i].width;
		buffer[RECT_SIZE * i + 5] = pdata->obstacles[i].height;
	}

	buffer[1 + 1 + RECT_SIZE * buffer[1]] = pdata->speed_spots_number;

	for (int i = 0; i < pdata->speed_spots_number; ++i)
	{
		buffer[RECT_SIZE * i + 3 + RECT_SIZE * buffer[1]] = pdata->speed_spots[i].cords.x;
		buffer[RECT_SIZE * i + 4 + RECT_SIZE * buffer[1]] = pdata->speed_spots[i].cords.y;
		buffer[RECT_SIZE * i + 5 + RECT_SIZE * buffer[1]] = pdata->speed_spots[i].width;
		buffer[RECT_SIZE * i + 6 + RECT_SIZE * buffer[1]] = pdata->speed_spots[i].height;
	}

	buffer[1 + 1 + RECT_SIZE * buffer[1] + 1 + RECT_SIZE * buffer[1 + 1 + RECT_SIZE * buffer[1]]] = 0;

	buffer[1 + 1 + RECT_SIZE * buffer[1] + 1 + RECT_SIZE * buffer[1 + 1 + RECT_SIZE * buffer[1]] + 1] = pdata->board_width;
	buffer[1 + 1 + RECT_SIZE * buffer[1] + 1 + RECT_SIZE * buffer[1 + 1 + RECT_SIZE * buffer[1]] + 1 + 1] = pdata->board_height;
	send(sock, (char *)(buffer), (1 + 1 + RECT_SIZE * buffer[1] + 1 + RECT_SIZE * buffer[1 + 1 + RECT_SIZE * buffer[1]] + 1 + 1 + 1) * CHAR_SIZE, NO_FLAGS);
}

void send_structure(int sock, game_object_t* pdata)
{
	char buffer[BUFOR_SIZE_CHAR];

	buffer[BUFOR_START] = pdata->players_index;

	for (int i = 0; i < pdata->players_index; ++i)
	{
		*(int*)&(buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 0]) = pdata->players[i].player_rect.cords.x;
		*(int*)&(buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 1]) = pdata->players[i].player_rect.cords.y;
		*(int*)&(buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 2]) = pdata->players[i].player_rect.size;
		*(int*)&(buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 3]) = pdata->players[i].player_rect.game_result;
		buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 2] = pdata->players[i].id;
		buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 2 + 1] = pdata->players[i].vel;
	}

	send(sock, (char *)(buffer), (1 + buffer[0] * PLAYER_SIZE) * CHAR_SIZE, NO_FLAGS);
}


void recv_init_structure(int sock, game_object_t* pdata)
{
	char buffer[BUFOR_SIZE_CHAR];
	recv(sock, (char *)buffer, BUFOR_SIZE_CHAR, NO_FLAGS);

	pdata->ID = buffer[BUFOR_START];

	pdata->obstacles_number = buffer[1];

	for (int i = 0; i < pdata->obstacles_number; ++i)
	{
		pdata->obstacles[i].cords.x = buffer[RECT_SIZE * i + 2];
		pdata->obstacles[i].cords.y = buffer[RECT_SIZE * i + 3];
		pdata->obstacles[i].width = buffer[RECT_SIZE * i + 4];
		pdata->obstacles[i].height = buffer[RECT_SIZE * i + 5];
	}

	pdata->speed_spots_number = buffer[1 + 1 + RECT_SIZE * buffer[1]];

	for (int i = 0; i < pdata->speed_spots_number; ++i)
	{
		pdata->speed_spots[i].cords.x = buffer[RECT_SIZE * i + 3 + RECT_SIZE * buffer[1]];
		pdata->speed_spots[i].cords.y = buffer[RECT_SIZE * i + 4 + RECT_SIZE * buffer[1]];
		pdata->speed_spots[i].width = buffer[RECT_SIZE * i + 5 + RECT_SIZE * buffer[1]];
		pdata->speed_spots[i].height = buffer[RECT_SIZE * i + 6 + RECT_SIZE * buffer[1]];
	}

	pdata->players_index = buffer[1 + 1 + RECT_SIZE * buffer[1] + 1 + RECT_SIZE * buffer[1 + 1 + RECT_SIZE * buffer[1]]];

	pdata->board_width = buffer[1 + 1 + RECT_SIZE * buffer[1] + 1 + RECT_SIZE * buffer[1 + 1 + RECT_SIZE * buffer[1]] + 1];
	pdata->board_height = buffer[1 + 1 + RECT_SIZE * buffer[1] + 1 + RECT_SIZE * buffer[1 + 1 + RECT_SIZE * buffer[1]] + 1 + 1];
}

void recv_structure(int sock, game_object_t* pdata)
{
	char buffer[BUFOR_SIZE_CHAR];
	recv(sock, (char *)buffer, BUFOR_SIZE_CHAR, NO_FLAGS);

	pdata->players_index = buffer[BUFOR_START];

	for (int i = 0; i < pdata->players_index; ++i)
	{
		pdata->players[i].player_rect.cords.x = *(int*)&buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 0];
		pdata->players[i].player_rect.cords.y = *(int*)&buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 1];
		pdata->players[i].player_rect.size = *(int*)&buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 2];
		pdata->players[i].player_rect.game_result = *(int*)&buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 3];
		pdata->players[i].id = buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 2];
		pdata->players[i].vel = buffer[PLAYER_SIZE * i + 1 + INT_SIZE * 2 + 1];
	}

}

void debug_printf(game_object_t* data)
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
	printf("data.obstacles_number = %d\n", data->obstacles_number);
	for (int i = 0; i < data->speed_spots_number; ++i)
	{
		printf("i = %d\n", i);
		printf("data.speed_spots[i].cords.x = %d\n", data->speed_spots[i].cords.x);
		printf("data.speed_spots[i].cords.y = %d\n", data->speed_spots[i].cords.y);
		printf("data.speed_spots[i].width = %d\n", data->speed_spots[i].width);
		printf("data.speed_spots[i].height = %d\n", data->speed_spots[i].height);
	}
	printf("data.board_width = %d\n", data->board_width);
	printf("data.board_height = %d\n", data->board_height);
	printf("data.players_index =  %d\n", data->players_index);
	for (int i = 0; i < data->players_index; ++i)
	{
		printf("i = %d\n", i);
		printf("data.players[i].player_rect.cords.x = %d\n", data->players[i].player_rect.cords.x);
		printf("data.players[i].player_rect.cords.y = %d\n", data->players[i].player_rect.cords.y);
		printf("data.players[i].vel = %d\n", data->players[i].vel);
		printf("data.players[i].id = %d\n", data->players[i].id);
	}
}
