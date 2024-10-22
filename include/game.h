/**
 * @author Marco Netti
 * @file game.h
 * @brief Defines types, enums and function prototypes for
 * the snake game logic.
 */
#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "maze.h"
#include "entities.h"

/**
 * @enum GameMove
 * @brief Enumeration which contains all the possible game
 * moves.
 */
typedef enum {
    UP = 'N',   /**< Move the Snake up. */
    DOWN = 'S', /**< Move the Snake down. */
    LEFT = 'W', /**< Move the Snake left. */
    RIGHT = 'E'  /**< Move the Snake right. */
} GameMove;

/**
 * @enum GameStatus
 * @brief Enumeration for game status.
 */
typedef enum {
    IN_PROGRESS, /**< The game is in progress. */
    FINISHED     /**< The game has finished. */
} GameStatus;

/**
 * @enum GameMode
 * @brief Enumeration for different game modes.
 */
typedef enum {
    NOT_DECIDED,    /**< Game mode has not been decided. */
    INTERACTIVE,    /**< Interactive mode where the user plays. */
    AI              /**< AI mode where the computer plays. */
} GameMode;

/**
 * @struct Game
 * @brief Struct that wraps all the game elements
 * (Maze, Entities) and also contains a field for the
 * GameStatus.
 */
typedef struct Game {
    Maze maze;           /**< The Maze struct representing the game's maze layout. */
    Entities entities;   /**< The Entities struct containing information about game entities (Snake and Drill). */
    GameStatus state;    /**< The current status of the game (IN_PROGRESS or FINISHED). */
} Game;

/**
 * @brief Creates a new game.
 * @param config Configuration information for the maze.
 * @return A pointer to the created Game.
 */
Game *create_game(MazeInfo config);

/**
 * @brief Updates game entities based on the next move.
 * @param m Pointer to the Maze struct.
 * @param e Pointer to the Entities struct.
 * @param next The next position in the maze.
 */
void game_entities_update(Maze *m, Entities *e, Point next);

/**
 * @brief Updates the game status.
 * @param g Pointer to the Game struct.
 */
void game_status_update(Game **g);

/**
 * @brief Maps a GameMove to a Point.
 * @param m The GameMove.
 * @return The corresponding Point.
 */
Point map_move(GameMove move);

/**
 * @brief Calculates the next move based on the current move and position.
 * @param m The current GameMove.
 * @param p The current position.
 * @return The next position.
 */
Point calculate_move(GameMove move, Point p);

/**
 * @brief Gets the next move from the user.
 * @return The chosen GameMove.
 */
GameMove get_next_user_move();

/**
 * @brief Initiates an interactive game session.
 * @param config Configuration information for the maze.
 */
void user_plays(MazeInfo config);

/**
 * @brief Swaps two GameMoves.
 * @param nd The new GameMove.
 * @param pd Pointer to the current GameMove.
 */
void ai_swap_moves(GameMove nd, GameMove *pd);

/**
 * @brief Checks if a move hits a maze wall.
 * @param m Pointer to the Maze struct.
 * @param s Pointer to the Snake struct.
 * @param move The GameMove to check.
 * @return True if the move hits a wall, false otherwise.
 */
bool is_maze_wall_ai(Maze *m, Snake *s, GameMove move);

/**
 * @brief Changes the direction to turn right basing on
 * the current move.
 * @param move The current GameMove.
 * @return The new GameMove.
 */
GameMove ai_turn_right(GameMove move);

/**
 * @brief Changes the direction to turn left basing on
 * the current move.
 * @param move The current GameMove.
 * @return The new GameMove.
 */
GameMove ai_turn_left(GameMove move);

/**
 * @brief Initiates an AI-driven game session.
 * @param config Configuration information for the maze.
 */
void ai_plays(MazeInfo config);

/**
 * @brief Gets the user's menu choice.
 * @return The chosen menu option.
 */
char get_menu_choice();

/**
 * @brief Selects the game mode based on user input.
 * @param c The user's choice.
 * @return The selected game mode.
 */
GameMode select_game_mode(char select);

/**
 * @brief Initiates the game based on the selected mode and maze configuration.
 * @param mode The selected game mode.
 * @param config Configuration information for the maze.
 */
void select_who_plays(GameMode mode, MazeInfo config);

/**
 * @brief Displays the main menu and initiates the game based on user input.
 */
void main_menu();

void destroy_game(Game *g);

#endif
