#include "../include/game_header.h"

Game *create_game(GameMode m) {
    Game *g = malloc(sizeof(Game));
    init_maze(&g->maze);
    init_entities(&g->entities);
    g->mode = m;
    g->state = IN_PROGRESS;
    return g;
}

PlayerMove get_input_move() {
    char key;
    bool correct_key = false;
    PlayerMove move;

    while (!correct_key) {
        key = (char) getchar();
        switch (key) {
            case 'w':
                move = UP;
                correct_key = true;
                break;
            case 'a':
                move = LEFT;
                correct_key = true;
                break;
            case 's':
                move = DOWN;
                correct_key = true;
                break;
            case 'd':
                move = RIGHT;
                correct_key = true;
                break;
            default:
                continue;
        }
    }
    return move;
}

Point map_move(PlayerMove m) {
    Point p = {0, 0};

    switch (m) {
        case UP:
            p.x = -1;
            break;
        case DOWN:
            p.x = 1;
            break;
        case LEFT:
            p.y = -1;
            break;
        case RIGHT:
            p.y = 1;
            break;
        default:
            break;
    }

    return p;
}

Point calculate_move(PlayerMove m, Point p) {
    Point mapped_move = map_move(m);
    p.x += mapped_move.x;
    p.y += mapped_move.y;
    return p;
}

void update_game_entities(Maze *m, Entities *e, Point next) {
    int index = get_index(next);
    if (check_point(next)) {
        char sym = m->str[index];
        if (is_collision(sym)) {
            if (e->drill.active && e->drill.usages > 0) {
                m->str[index] = ' ';
                --e->drill.usages;
                update_drill(&e->drill);
                update_snake(&e->snake, next);
            }
        } else {
            update_entities(&m->str[index], &e);
            update_snake(&e->snake, next);
        }
    }
}

void print_maze_and_snake(Maze *m, Snake *s) {
    PCell pc = s->body->tail;

    // Create a temporary array for printing and initialize it with the maze array
    char printedMaze[MAZE_SIZE];
    memcpy(printedMaze, m->str, MAZE_SIZE);

    // Update the temporary array for the snake's position
    while (pc != NULL) {
        int idx = get_index(pc->info);
        if (pc == s->body->head) {
            printedMaze[idx] = 'O';  // Set 'O' for the head
        } else {
            printedMaze[idx] = 'o';  // Set 'o' for the body
        }
        pc = pc->prev;
    }

    // Print the updated maze and snake position
    for (int i = 0; i < MAZE_ROWS; ++i) {
        for (int j = 0; j < MAZE_COLS; ++j) {
            int idx = i * MAZE_COLS + j;
            printf("%c", printedMaze[idx]);
        }
        printf("\n");
    }
}

void update_game_status(Game **g) {
    bool are_equal = equal(get_head(&(*g)->entities.snake.body), MAZE_END);
    if ((*g)->entities.snake.score == 0 && !are_equal) {
        (*g)->state = GAME_OVER;
    } else if ((*g)->entities.snake.score >= 0 && are_equal) {
        (*g)->state = WON;
    }
}

void start_game(GameMode mode) {
    Game *g = create_game(mode);
    system("clear");
    while (g->state == IN_PROGRESS) {
        print_maze_and_snake(&g->maze, &g->entities.snake);
        printf("Score: %d\n", g->entities.snake.score);
        printf("Drill usages: %d\n", g->entities.drill.usages);
        if (!g->entities.drill.active) {
            printf("Drill not active.\n");
        }
        update_game_entities(&g->maze, &g->entities,
                             calculate_move(get_input_move(), get_head(&g->entities.snake.body)));
        update_game_status(&g);
        system("clear");
    }
    print_maze_and_snake(&g->maze, &g->entities.snake);
    //TODO temp
    //--------------------------------------------------------------------------
    if (g->state == GAME_OVER) {
        printf("You LOST!\nScore: %d\n", g->entities.snake.score);
    } else if (g->state == WON) {
        printf("You WON!\nScore: %d\n", g->entities.snake.score);
    }
    //--------------------------------------------------------------------------
    destroy_list(&g->entities.snake.body);
    free(g->maze.str);
    free(g);
}


