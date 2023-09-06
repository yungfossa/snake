#ifndef SNAKE_FINAL_GAME_HEADER_H
#define SNAKE_FINAL_GAME_HEADER_H

#include <stddef.h>
#include <string.h>
#include "list.h"

extern int MAZE_ROWS;
extern int MAZE_COLS;
extern int MAZE_SIZE;
extern Point MAZE_START;
extern Point MAZE_END;

typedef struct Maze {
    char *str;
} Maze;

typedef struct SnakeEntity {
    int score;
    PList body;
} Snake;

typedef struct DrillEntity {
    bool active;
    int usages;
} Drill;

typedef struct Entities {
    Snake snake;
    Drill drill;
} Entities;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} PlayerMove;

typedef enum {
    IN_PROGRESS,
    WON,
    GAME_OVER
} GameStatus;

typedef enum {
    INTERACTIVE,
    CPU
} GameMode;

typedef struct Game {
    Maze maze;
    Entities entities;
    GameMode mode;
    GameStatus state;
} Game;

/**********************************************/
//                MAZE FUNCTIONS
/**********************************************/

void read_size();

void read_maze(Maze **);

void init_maze(Maze *);

int get_index(Point);

bool check_point(Point);

bool is_collision(char);

/**********************************************/
//                ENTITIES FUNCTIONS
/**********************************************/

void init_entities(Entities *);

void set_drill(Drill *);

void apply_coin(Snake *);

void apply_sudden(Snake *);

void update_drill(Drill *);

void update_snake(Snake *, Point);

void update_entities(char *, Entities **);

/**********************************************/
//                GAME FUNCTIONS
/**********************************************/

Game *create_game(GameMode);

PlayerMove get_input_move();

Point map_move(PlayerMove);

Point calculate_move(PlayerMove, Point);

void update_game_entities(Maze *, Entities *, Point);

void print_maze_and_snake(Maze *, Snake *);

void update_game_status(Game **);

void start_game(GameMode);

#endif //SNAKE_FINAL_GAME_HEADER_H