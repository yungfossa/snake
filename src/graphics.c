/**
 * @author Marco Netti
 * @file graphics.c
 * @brief Implementation of the graphics header (graphics.h).
 */

#include <string.h>
#include <stdio.h>
#include "../include/graphics.h"


void display_title() {
    clear_screen();
    printf(BMAG"                              $$\\                     \n"
           "                              $$ |                    \n"
           " $$$$$$$\\ $$$$$$$\\   $$$$$$\\  $$ |  $$\\  $$$$$$\\      \n"
           "$$  _____|$$  __$$\\  \\____$$\\ $$ | $$  |$$  __$$\\     \n"
           "\\$$$$$$\\  $$ |  $$ | $$$$$$$ |$$$$$$  / $$$$$$$$ |    \n"
           " \\____$$\\ $$ |  $$ |$$  __$$ |$$  _$$<  $$   ____|    \n"
           "$$$$$$$  |$$ |  $$ |\\$$$$$$$ |$$ | \\$$\\ \\$$$$$$$\\ $$\\ \n"
           "\\_______/ \\__|  \\__| \\_______|\\__|  \\__| \\_______|\\__|\n\n"CRESET);
}

void display_main_menu() {
    display_title();
    printf(BMAG"╔══════╗\n"CRESET);
    printf(BCYN"║ MENU ║\n"CRESET);
    printf(BMAG"╠══════╩══════════════════════════════════════╗\n"CRESET);
    printf(BCYN"║ · Press "uu"to start a new game!              ║\n"CRESET);
    printf(BCYN"║ · Press "aa"to see the my AI strategy :)      ║\n"CRESET);
    printf(BCYN"║ · Press "ee"to exit the game :/               ║\n"CRESET);
    printf(BMAG"╚═════════════════════════════════════════════╝\n\n"CRESET);
    printf(BCYN"· Insert your choice: "CRESET);
}

void display_interactive_mode_final_score(int score) {
    clear_screen();
    printf(BCYN"$$$$$$$$\\ $$\\   $$\\ $$$$$$$\\  $$\\ \n"
           "$$  _____|$$$\\  $$ |$$  __$$\\ $$ |\n"
           "$$ |      $$$$\\ $$ |$$ |  $$ |$$ |\n"
           "$$$$$\\    $$ $$\\$$ |$$ |  $$ |$$ |\n"
           "$$  __|   $$ \\$$$$ |$$ |  $$ |\\__|\n"
           "$$ |      $$ |\\$$$ |$$ |  $$ |    \n"
           "$$$$$$$$\\ $$ | \\$$ |$$$$$$$  |$$\\ \n"
           "\\________|\\__|  \\__|\\_______/ \\__|\n"CRESET);
    printf(BCYN"\n· Your final score is %d\n"CRESET, score);
}

void display_interactive_mode_instructions() {
    display_title();
    printf(BMAG"╔════════════════════╗\n"CRESET);
    printf(BCYN"║   SNAKE COMMANDS   ║\n"CRESET);
    printf(BMAG"╠════════════════════╩════╗\n"CRESET);
    printf(BCYN"║ "ww" - move up            ║\n"CRESET);
    printf(BCYN"║ "aa" - move left          ║\n"CRESET);
    printf(BCYN"║ "ss" - move down          ║\n"CRESET);
    printf(BCYN"║ "dd" - move right         ║\n"CRESET);
    printf(BMAG"╚═════════════════════════╝\n"CRESET);

    printf(BMAG"╔══════════════╗\n"CRESET);
    printf(BCYN"║    RULES     ║\n"CRESET);
    printf(BMAG"╠══════════════╩═══════════════════════════════════════════════════════════════════╗\n"CRESET);
    printf(BCYN"║ █ - walls that cannot be crossed                                                 ║\n"CRESET);
    printf(BCYN"║ $ - coins, each worth 10 points and also increase snake's length                 ║\n"CRESET);
    printf(BCYN"║ ⚠ - unexpected events, that when encountered, halve (integer division)           ║\n"CRESET);
    printf(BCYN"║     the number of collected coins and its length.                                ║\n"CRESET);
    printf(BCYN"║ ⛏ - drill, allows you to drill through walls. Every time a ⛏ is collected,       ║\n"CRESET);
    printf(BCYN"║     the number of available drill uses increases by 3                            ║\n"CRESET);
    printf(BMAG"╚══════════════════════════════════════════════════════════════════════════════════╝\n"CRESET);

    printf(BCYN"· Press any key to play..."CRESET);
    getchar();
}

void display_ai_mode_instructions() {
    display_title();
    printf(BMAG"╔═════════════════════════╗\n"CRESET);
    printf(BCYN"║    ALGORITHM ADOPTED    ║\n"CRESET);
    printf(BMAG"╠═════════════════════════╩═══════════════════════════════════════════════════════════════════╗\n"CRESET);
    printf(BCYN"║ ·  The Right Hand Algorithm is a simple maze-solving strategy that relies on the agent      ║\n"CRESET);
    printf(BCYN"║    keeping their right hand in contact with the wall and never lifting it until they        ║\n"CRESET);
    printf(BCYN"║    reach thea maze's exit.                                                                  ║\n"CRESET);
    printf(BMAG"╚═════════════════════════════════════════════════════════════════════════════════════════════╝\n"CRESET);

    printf(BCYN"· Press any key to see the AI solution... "CRESET);
    getchar();
}

void display_maze_and_entities(Maze *m, Entities *e) {
    clear_screen();

    PPointCell pc = e->snake.body->tail;
    int size = m->info.size, cols = m->info.cols, rows = m->info.rows;
    char printedMaze[size];

    memcpy(printedMaze, m->str, size);
    while (pc != NULL) {
        int idx = get_maze_index(pc->info, cols);
        if (pc == e->snake.body->head) {
            printedMaze[idx] = 'O';
        } else {
            printedMaze[idx] = 'o';
        }
        pc = pc->prev;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            display_maze_tile(printedMaze[i * cols + j]);
        }
        printf("\n");
    }

    printf(BCYN"\n· Score: %d\n" CRESET, e->snake.score);
    if (e->drill.active) {
        printf(BRED"· Drill usages: %d\n" CRESET, e->drill.usages);
    }
}

void clear_screen() {
    printf("\033[2J");
    printf("\033[0;0H");
}

void display_ai_solution_road(Maze *m, Snake *s, PPointsList *ai_road) {
    clear_screen();

    PPointCell pc = s->body->tail;
    int size = m->info.size, cols = m->info.cols, rows = m->info.rows;
    char printedMaze[size];

    memcpy(printedMaze, m->str, size);
    while (pc != NULL) {
        int idx = get_maze_index(pc->info, cols);
        if (pc == s->body->head) {
            printedMaze[idx] = 'O';
        } else {
            printedMaze[idx] = 'o';
        }
        pc = pc->prev;
    }

    pc = (*ai_road)->head;

    while (pc != NULL) {
        int idx = get_maze_index(pc->info, cols);
        if (printedMaze[idx] != 'O' && printedMaze[idx] != 'o') {
            printedMaze[idx] = '.';
        }
        pc = pc->next;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            display_maze_tile(printedMaze[i * cols + j]);
        }
        printf("\n");
    }
}

void display_ai_moves_and_score(PMovesList *ai_moves, Snake *s) {
    display_message("· AI score: ");
    printf("%d\n", s->score);
    display_message("· AI moves: ");
    print_moves_list(ai_moves);
}

void display_play_again() {
    printf(BMAG"\n╔══════════════════════════════════════╗\n"CRESET);
    printf(BCYN"║ · Do you want to play again ? [y/n]  ║\n"CRESET);
    printf(BMAG"╚══════════════════════════════════════╝\n"CRESET);
    char c;
    display_message("· Insert your choice: ");
    scanf("%c", &c);
    switch (c) {
        case 'Y':
        case 'y':
            return main_menu();
        case 'N':
        case 'n':
            clear_screen();
            return;
        default:
            clear_screen();
            return display_play_again();
    }
}

void display_message(char *str) {
    printf(BCYN"%s"CRESET, str);
}

void display_maze_tile(char c) {
    switch (c) {
        case '#':
            printf(CYN "█"CRESET);
            break;
        case 'O':
            printf(MAG "●"CRESET);
            break;
        case 'o':
            printf(MAG "○"CRESET);
            break;
        case '$':
            printf(GRN "$"CRESET);
            break;
        case '!':
            printf(YEL "⚠"CRESET);
            break;
        case 'T':
            printf(RED "⛏"CRESET);
            break;
        case '_':
            printf("E");
            break;
        case '.':
            printf("·");
            break;
        default:
            printf(" ");
            break;
    }
}

void enable_input_hiding() {
    system("stty -echo");
    system("stty -icanon");
}

void disable_input_hiding() {
    system("stty echo");
    system("stty icanon");
}

