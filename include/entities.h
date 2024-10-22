/**
 * @author Marco Netti
 * @file entities.h
 * @brief Declarations for game entities and related functions.
 */

#ifndef SNAKE_ENTITIES_H
#define SNAKE_ENTITIES_H

#include "points_list.h"

/**
 * @struct SnakeEntity
 * @brief Represents the snake entity in the game.
 */
typedef struct SnakeEntity {
    int score;           /**< Current score of the snake. */
    int grabbed_coins;   /**< Number of coins grabbed by the snake. */
    PPointsList body;    /**< Doubly Linked list representing the snake's body. */
} Snake;

/**
 * @struct DrillEntity
 * @brief Represents the drill entity in the game.
 */
typedef struct DrillEntity {
    bool active;        /**< Indicates if the drill is active. */
    int usages;         /**< Remaining usages of the drill. */
} Drill;

/**
 * @struct Entities
 * @brief Contains all the game entities.
 */
typedef struct Entities {
    Snake snake;        /**< The snake entity. */
    Drill drill;        /**< The drill entity. */
} Entities;

/**
 * @brief Initializes the game entities.
 * @param e A pointer to the Entities struct to be initialized.
 * @param p_start The starting position of the snake.
 */
void init_entities(Entities *e, Point p_start);

/**
 * @brief Updates the game entities based on the last char read from
 * the maze.
 * @param c A pointer to the last char read .
 * @param e A pointer to the Entities struct to be updated.
 */
void entities_update(Entities **e, char *c);

/**
 * @brief Applies the effects of grabbing a coin to the snake.
 * @param s A pointer to the Snake struct.
 */
void snake_apply_coin(Snake *s);

/**
 * @brief Applies the sudden event effect to the snake.
 * @param s A pointer to the Snake struct.
 */
void snake_apply_sudden(Snake *s);

/**
 * @brief Updates the snake's position and body.
 * @param s A pointer to the Snake struct.
 * @param new_head_pos The new position of the snake's head.
 */
void snake_update(Snake *s, Point new_head_pos);

/**
 * @brief Sets the drill entity to be active.
 * @param d A pointer to the Drill struct.
 */
void drill_set(Drill *d);

/**
 * @brief Updates the state of the drill entity.
 * @param d A pointer to the Drill struct.
 */
void drill_update(Drill *d);

#endif