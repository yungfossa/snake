cmake_minimum_required(VERSION 3.25)
project(snake_final C)

set(CMAKE_C_STANDARD 99)

add_executable(snake_final src/maze.c src/game.c src/list.c src/entities.c src/main.c)
