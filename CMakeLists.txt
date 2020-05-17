cmake_minimum_required(VERSION 3.16)
project(main C)

set(CMAKE_C_STANDARD 11)

add_executable(main connection.h connection.c game.h game.c game_structure.h priority_queue_list.h priority_queue_list.c server.c)