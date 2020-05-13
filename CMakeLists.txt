cmake_minimum_required(VERSION 3.16)
project(main C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c)

find_package(SDL2 REQUIRED)

target_link_libraries(main SDL2::SDL2)
