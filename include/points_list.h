/**
 * @author Marco Netti
 * @file points_list.h
 * @brief Header file containing declarations for a doubly linked list
 * implementation.
 */

#ifndef SNAKE_POINTS_LIST_H
#define SNAKE_POINTS_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * @struct Point
 * @brief Represents a 2D point with x and y coordinates.
 */
typedef struct Point {
    int x;     /**< x-coordinate */
    int y;     /**< y-coordinate */
} Point;

/**
 * @brief Creates a Point with given x and y coordinates.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return The created Point.
 */
Point create_point(int x, int y);

/**
 * @brief Checks if two Points are equal.
 * @param p1 The first Point.
 * @param p2 The second Point.
 * @return true if the Points are equal, false otherwise.
 */
bool equal(Point p1, Point p2);

/**
 * @struct PointCell
 * @brief Represents a node in the doubly linked list.
 */
typedef struct PointCell {
    Point info;                /**< The Point information stored in the Cell. */
    struct PointCell *next;    /**< Pointer to the next Cell. */
    struct PointCell *prev;    /**< Pointer to the previous Cell. */
} PointCell;

/**
 * @typedef PPointCell
 * @brief A pointer to a PointCell.
 */
typedef struct PointCell *PPointCell;

/**
 * @struct PointsList
 * @brief Represents a doubly linked list.
 */
typedef struct PointsList {
    PPointCell head;     /**< Pointer to the first PointCell in the list. */
    PPointCell tail;     /**< Pointer to the last PointCell in the list. */
    PPointCell target;   /**< Pointer to the target PointCell. */
    int size;            /**< The size of the list. */
} PointsList;

/**
 * @typedef PPointsList
 * @brief A pointer to a PointsList.
 */
typedef PointsList *PPointsList;

/**
 * @brief Initializes a PointsList
 * @param l A pointer to the PointsList to be initialized.
 */
void init_points_list(PPointsList *l);

/**
 * @brief Creates a new PointsList.
 * @return A pointer to the created PointsList.
 */
PPointsList create_points_list();

/**
 * @brief Checks if a PointsList is empty.
 * @param l A pointer to the PointsList.
 * @return true if the PointsList is empty, false otherwise.
 */
bool is_points_list_empty(PPointsList *l);

/**
 * @brief Adds a Point to the front of a PointsList.
 * @param l A pointer to the PointsList.
 * @param p The Point to be added.
 */
void push_front_point(PPointsList *l, Point p);

/**
 * @brief Adds a Point to the back of a PointsList.
 * @param l A pointer to the PointsList.
 * @param p The Point to be added.
 */
void push_back_point(PPointsList *l, Point p);

/**
 * @brief Removes the last element from a PointsList.
 * @param l A pointer to the PointsList.
 */
void pop_back(PPointsList *l);

/**
 * @brief Destroys a PointsList and frees the allocated memory.
 * @param l A pointer to the PointsList to be destroyed.
 */
void destroy_points_list(PPointsList *l);

/**
 * @brief Gets the Point at the head of a PointsList.
 * @param l A pointer to the PointsList.
 * @return The Point at the head of the PointsList.
 */
Point get_points_list_head(PPointsList *l);

/**
 * @brief Checks if a PointsList contains a specific Point.
 * @param l A pointer to the PointsList.
 * @param p The Point to search for.
 * @return true if the Point is found, false otherwise.
 */
bool contains(PPointsList *l, Point p);

/**
 * @brief Halves the size of a PointsList by removing elements from the end.
 * @param l A pointer to the PointsList to be halved.
 */
void halve_points_list(PPointsList *l);

/**
 * @param l A pointer to the PointsList
 * @param p The Point
 */
void adjust_cells(PPointsList *l, Point p); //TODO commentare meglio questa

/**
 * @brief Removes Cells after a target Point in a PointsList.
 * @param l A pointer to the PointsList.
 * @param p_target The target Point.
 */
void remove_cells_after_target(PPointsList *l, Point p_target);

#endif
