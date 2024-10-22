/**
 * @author Marco Netti
 * @file maze.c
 * @brief Implementation of the maze header (maze.h).
 */

#include "../include/maze.h"
#include "../include/graphics.h"

MazeInfo maze_info_input_read() {
    display_title();
    MazeInfo config;
    display_message("· Insert the number of cols: ");
    scanf("%d", &config.cols);
    printf("\n");
    display_message("· Insert the number of rows: ");
    scanf("%d", &config.rows);
    printf("\n");
    config.size = config.rows * config.cols;
    return config;
}

void maze_input_read(Maze **m) {
    char c;
    bool start = false, end = false;

    int size = (*m)->info.size,
            cols = (*m)->info.cols,
            rows = (*m)->info.rows;

    (*m)->str = malloc(sizeof(char) * (size + 1));
    if (!(*m)->str) exit(EXIT_FAILURE);

    display_message("· Insert your labyrinth:\n");

    getchar();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            c = getchar();
            if (!start && c == 'o') {
                start = true;
                (*m)->info.start = create_point(i, j);
                c = ' ';
            } else if (!end && c == '_') {
                end = true;
                (*m)->info.end = create_point(i, j);
            }
            (*m)->str[i * cols + j] = c;
        }
        getchar();
    }

    (*m)->str[size] = '\0';
}

void init_maze(Maze *m, MazeInfo info) {
    m->info = info;
    maze_input_read(&m);
}

int get_maze_index(Point p, int cols) {
    return p.x * cols + p.y;
}

bool is_maze_wall(char c) {
    return c == '#';
}

bool is_point_inside_maze(Point p, MazeInfo info) {
    return p.x >= 0 && p.y >= 0 ? p.y != info.cols && get_maze_index(p, info.cols) < info.size : false;
}



