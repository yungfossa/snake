/**
 * @author Marco Netti
 * @file moves_list.h
 * @brief Declarations for managing a list of game moves.
 */

#ifndef SNAKE_MOVES_LIST_H
#define SNAKE_MOVES_LIST_H

#include "game.h"

/**
 * @struct MoveCell
 * @brief Represents a cell in the list of game moves.
 */
typedef struct MoveCell {
    GameMove info;             /**< Information about a game move. */
    struct MoveCell *next;     /**< Pointer to the next cell in the list. */
} MoveCell;

/**
 * @typedef PMoveCell
 * @brief Pointer to a MoveCell.
 */
typedef MoveCell* PMoveCell;

/**
 * @struct MovesList
 * @brief Represents a list of game moves.
 */
typedef struct MovesList {
    PMoveCell head;    /**< Pointer to the head of the list. */
    PMoveCell tail;    /**< Pointer to the tail of the list. */
} MovesList;

/**
 * @typedef PMovesList
 * @brief Pointer to a MovesList.
 */
typedef MovesList* PMovesList;

/**
 * @brief Initializes a moves list.
 * @param l A pointer to a pointer to the MovesList struct.
 */
void init_moves_list(PMovesList *l);

/**
 * @brief Creates a new empty moves list.
 * @return A pointer to the newly created MovesList struct.
 */
PMovesList create_moves_list();

/**
 * @brief Adds a game move to the front of the list.
 * @param l A pointer to a pointer to the MovesList struct.
 * @param m The game move to be added.
 */
void push_front_move(PMovesList *l, GameMove m);

/**
 * @brief Destroys a moves list, freeing all allocated memory.
 * @param l A pointer to a pointer to the MovesList struct.
 */
void destroy_moves_list(PMovesList *l);

/**
 * @brief Adds a game move to the end of the list.
 * @param l A pointer to a pointer to the MovesList struct.
 * @param m The game move to be added.
 */
void push_back_move(PMovesList *l, GameMove m);

/**
 * @brief Checks if a moves list is empty.
 * @param l A pointer to a pointer to the MovesList struct.
 * @return true if the list is empty, false otherwise.
 */
bool is_moves_list_empty(PMovesList *l);

/**
 * @brief Prints the contents of a moves list. If the list is empty,
 * the function prints a message on the screen.
 * @param l A pointer to a pointer to the MovesList struct.
 */
void print_moves_list(PMovesList *l);

#endif

