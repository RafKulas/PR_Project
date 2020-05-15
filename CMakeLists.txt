cmake_minimum_required(VERSION 3.16)
project(server C)

set(CMAKE_C_STANDARD 99)

add_executable(server server.c connection.h connection.c game.h game.c game_structure.h priority_queue_list.h priority_queue_list.c)