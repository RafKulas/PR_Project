cmake_minimum_required(VERSION 3.16)
project(main C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c graphics.c graphics.h game_structure.h map.h connection.c connection.h)

find_package(SDL2 REQUIRED)

target_link_libraries(main SDL2::SDL2)
