/**
 * @author Marco Netti
 * @file graphics.h
 * @brief Declarations for functions related to graphics and user interface.
 */

#ifndef SNAKE_GRAPHICS_H
#define SNAKE_GRAPHICS_H

#include "moves_list.h"
#include "entities.h"
#include "game.h"

/**
 * @def ww
 * @brief Represents the 'w' movement option in the game menu.
 */
#define ww "🆆 "
/**
 * @def aa
 * @brief Represents the 'a' movement option in the game menu.
 */
#define aa "🅰 "
/**
 * @def ss
 * @brief Represents the 's' movement option in the game menu.
 */
#define ss "🆂 "
/**
 * @def dd
 * @brief Represents the 'd' movement option in the game menu.
 */
#define dd "🅳 "
/**
 * @def ee
 * @brief Represents the 'e' action option in the game menu.
 */
#define ee "🅴 "
/**
 * @def uu
 * @brief Represents the 'u' action option in the game menu.
 */
#define uu "🆄 "

/**
 * @def RED
 * @brief Defines the ANSI escape code for red color in terminal output.
 */
#define RED "\e[0;31m"
/**
 * @def GRN
 * @brief Defines the ANSI escape code for green color in terminal output.
 */
#define GRN "\e[0;32m"
/**
 * @def YEL
 * @brief Defines the ANSI escape code for yellow color in terminal output.
 */
#define YEL "\e[0;33m"
/**
 * @def MAG
 * @brief Defines the ANSI escape code for magenta color in terminal output.
 */
#define MAG "\e[0;35m"
/**
 * @def CYN
 * @brief Defines the ANSI escape code for cyan color in terminal output.
 */
#define CYN "\e[0;36m"
/**
 * @def BRED
 * @brief Defines the ANSI escape code for bold red color in terminal output.
 */
#define BRED "\e[1;31m"
/**
 * @def BMAG
 * @brief Defines the ANSI escape code for bold magenta color in terminal output.
 */
#define BMAG "\e[1;35m"
/**
 * @def BCYN
 * @brief Defines the ANSI escape code for bold cyan color in terminal output.
 */
#define BCYN "\e[1;36m"
/**
 * @def CRESET
 * @brief Defines the ANSI escape code to reset color formatting in terminal output.
 */
#define CRESET "\e[0m"

/**
 * @brief Displays the title of the game.
 */
void display_title();

/**
 * @brief Displays the main menu options.
 */
void display_main_menu();

/**
 * @brief Displays the maze layout and game entities.
 * @param m A pointer to the Maze struct.
 * @param e A pointer to the Entities struct.
 */
void display_maze_and_entities(Maze *m, Entities *e);

/**
 * @brief Displays the final score
 * @param score The final score of the game.
 */
void display_interactive_mode_final_score(int score);

/**
 * @brief Displays instructions for interactive mode.
 */
void display_interactive_mode_instructions();

/**
 * @brief Displays the maze layout including a dotted road,
 * which is the solution found by the AI to reach the end
 * of the labyrinth: it also displays the Snake.
 * @param m A pointer to the Maze struct
 * @param s A pointer to the Snake struct
 * @param l A pointer to a PointsList which contains all the
 * Points crossed by the AI.
 */
void display_ai_solution_road(Maze *m, Snake *s, PPointsList *l);

/**
 * @brief Displays the moves done by the AI to reach the
 * end of the labyrinth and the final score.
 * @param l A pointer to a MovesList which contains all
 * the moves done by the AI mode.
 * @param s A pointer to the SnakeEntity
 */
void display_ai_moves_and_score(PMovesList *l, Snake *s);

/**
 * @brief Displays instructions for AI mode.
 */
void display_ai_mode_instructions();

/**
 * @brief Displays the option to play again.
 */
void display_play_again();

/**
 * @brief Displays a tile of the maze.
 * @param tile The character representing the tile.
 */
void display_maze_tile(char tile);

/**
 * @brief Displays a message in the terminal.
 * @param message The message to be displayed.
 */
void display_message(char *message);

/**
 * @brief Clears the terminal screen.
 */
void clear_screen();

/**
 * @brief Enables hiding user input in the terminal.
 */
void enable_input_hiding();

/**
 * @brief Disables hiding user input in the terminal.
 */
void disable_input_hiding();

#endif
