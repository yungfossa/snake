/**
 * @author Marco Netti
 * @file game.c
 * @brief Implementation of the game header (game.h).
 */

#include "../include/points_list.h"
#include "../include/game.h"
#include "../include/graphics.h"

Game *create_game(MazeInfo info) {
    Game *g = malloc(sizeof(Game));
    init_maze(&g->maze, info);
    init_entities(&g->entities, g->maze.info.start);
    g->state = IN_PROGRESS;
    return g;
}

void game_entities_update(Maze *m, Entities *e, Point next) {
    int index = get_maze_index(next, m->info.cols);
    if (is_point_inside_maze(next, m->info)) {
        char tile = m->str[index];
        if (is_maze_wall(tile)) {
            if (e->drill.active) {
                m->str[index] = ' ';
                drill_update(&e->drill);
                snake_update(&e->snake, next);
            }
        } else {
            entities_update(&e, &m->str[index]);
            snake_update(&e->snake, next);
        }
    }
}

void game_status_update(Game **g) {
    if(equal(get_points_list_head(&(*g)->entities.snake.body), (*g)->maze.info.end)) {
        (*g)->state = FINISHED;
    }
}

char get_menu_choice() {
    char choice;
    choice = (char) getchar();
    return choice;
}

GameMode select_game_mode(char c) {
    switch (c) {
        case 'U':
        case 'u':
            return INTERACTIVE;
        case 'A':
        case 'a':
            return AI;
        default:
            clear_screen();
            return NOT_DECIDED;
    }
}

void select_who_plays(GameMode mode, MazeInfo config) {
    if (mode == INTERACTIVE) {
        user_plays(config);
    } else {
        ai_plays(config);
    }
}

void main_menu() {
    GameMode mode;
    char choice;
    bool valid_choice = false;
    clear_screen();
    do {
        display_main_menu();
        enable_input_hiding();
        choice = get_menu_choice();
        disable_input_hiding();
        mode = select_game_mode(choice);
        if (mode != NOT_DECIDED || choice == 'e') {
            valid_choice = true;
        }
    } while (!valid_choice);
    clear_screen();
    if (mode != NOT_DECIDED) {
        MazeInfo config = maze_info_input_read();
        select_who_plays(mode, config);
    }
}

Point map_move(GameMove m) {
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

Point calculate_move(GameMove m, Point p) {
    Point mapped_move = map_move(m);
    p.x += mapped_move.x;
    p.y += mapped_move.y;
    return p;
}

GameMove get_next_user_move() {
    char key;
    bool correct_key = false;
    GameMove move;
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

void user_plays(MazeInfo config) {
    Game *g = create_game(config);
    display_interactive_mode_instructions();
    enable_input_hiding();
    while (g->state == IN_PROGRESS) {
        display_maze_and_entities(&g->maze, &g->entities);
        game_entities_update(&g->maze,
                             &g->entities,
                             calculate_move(get_next_user_move(),
                                            get_points_list_head(&g->entities.snake.body)));
        game_status_update(&g);
    }
    disable_input_hiding();
    display_interactive_mode_final_score(&g->entities.snake.score);
    destroy_game(g);
    display_play_again();
}

GameMove ai_turns_right(GameMove move) {
    if (move == DOWN) {
        return LEFT;
    } else if (move == UP) {
        return RIGHT;
    } else if (move == LEFT) {
        return UP;
    } else {
        return DOWN;
    }
}

GameMove ai_turns_left(GameMove move) {
    if (move == DOWN) {
        return RIGHT;
    } else if (move == UP) {
        return LEFT;
    } else if (move == LEFT) {
        return DOWN;
    } else {
        return UP;
    }
}

void ai_swaps_moves(GameMove nd, GameMove *pd) {
    *pd = nd;
}
bool is_maze_wall_ai(Maze *m, Snake *s, GameMove move) {
    Point current = calculate_move(move, get_points_list_head(&s->body));
    int idx = get_maze_index(current, m->info.cols);
    return is_maze_wall(m->str[idx]);
}

void ai_plays(MazeInfo config) {
    Game *g = create_game(config);
    display_ai_mode_instructions();
    PMovesList moves = create_moves_list();
    PPointsList road = create_points_list();
    push_back_point(&road,g->maze.info.start);
    GameMove start_dir = DOWN; GameMove *current_dir = &start_dir;
    while (g->state == IN_PROGRESS) {
        if (is_maze_wall_ai(&g->maze, &g->entities.snake, ai_turns_right(*current_dir))) {
            while (is_maze_wall_ai(&g->maze, &g->entities.snake, *current_dir)) {
                ai_swaps_moves(ai_turns_left(*current_dir), current_dir);
            }
        } else {
            ai_swaps_moves(ai_turns_right(*current_dir), current_dir);
        }
        Point last = calculate_move(*current_dir, get_points_list_head(&g->entities.snake.body));
        push_back_point(&road, last);
        push_back_move(&moves, *current_dir);
        game_entities_update(&g->maze, &g->entities,last);
        game_status_update(&g);
        display_ai_solution_road(&g->maze, &g->entities.snake, &road);
        usleep(800000);
        fflush(stdout); // Assicura che il buffer di output sia svuotato
    }
    display_ai_moves_and_score(&moves, &g->entities.snake);
    destroy_points_list(&road);
    destroy_moves_list(&moves);
    destroy_game(g);
    display_play_again();
}

void destroy_game(Game *g) {
    destroy_points_list(&g->entities.snake.body);
    free(g->maze.str);
    free(g);
}