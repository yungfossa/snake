#include "../include/game_header.h"

int MAZE_COLS = 0;
int MAZE_ROWS = 0;
int MAZE_SIZE = 0;
Point MAZE_START = {0, 0};
Point MAZE_END = {0, 0};

void read_size() {
    printf("Insert cols: ");
    scanf("%d", &MAZE_COLS);
    printf("Insert rows: ");
    scanf("%d", &MAZE_ROWS);
    MAZE_SIZE = MAZE_ROWS * MAZE_COLS;
}

void read_maze(Maze **m) {
    char c;
    bool start = false, end = false;

    (*m)->str = malloc(sizeof(char) * (MAZE_SIZE + 1));
    if (!(*m)->str) exit(EXIT_FAILURE);

    getchar();

    for (int i = 0; i < MAZE_ROWS; ++i) {
        for (int j = 0; j < MAZE_COLS; ++j) {
            c = (char) getchar();
            if (!start && c == 'o') {
                start = true;
                MAZE_START = create_point(i, j);
                c = ' ';
            } else if (!end && c == '_') {
                end = true;
                MAZE_END = create_point(i, j);
            }
            (*m)->str[i * MAZE_COLS + j] = c;
        }
        getchar();
    }

    (*m)->str[MAZE_SIZE] = '\0';
}

void init_maze(Maze *m) {
    read_size();
    read_maze(&m);
}

bool check_point(Point p) {
    return p.x >= 0 && p.y >= 0 ? get_index(p) < MAZE_SIZE : false;
}

int get_index(Point p) {
    return p.x * MAZE_COLS + p.y;
}

bool is_collision(char c) {
    return c == '#';
}