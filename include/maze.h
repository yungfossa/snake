/**
 * @author Marco Netti
 * @file maze.h
 * @brief Declarations for Maze-related functions and structures.
 */

#ifndef SNAKE_MAZE_H
#define SNAKE_MAZE_H

#include "points_list.h"

/**
 * @struct MazeInfo
 * @brief Contains information about the maze.
 */
typedef struct MazeInfo {
    int rows;     /**< Number of rows in the maze. */
    int cols;     /**< Number of columns in the maze. */
    int size;     /**< Total size (rows * cols) of the maze. */
    Point start;  /**< Starting point of the maze. */
    Point end;    /**< Ending point of the maze. */
} MazeInfo;

/**
 * @struct Maze
 * @brief Represents a maze with its information and layout.
 */
typedef struct Maze {
    MazeInfo info; /**< Information about the maze. */
    char *str;     /**< Layout of the maze represented as a string. */
} Maze;

/**
 * @brief Reads maze configuration from user input.
 * @return The maze information provided by the user.
 */
MazeInfo maze_info_input_read();

/**
 * @brief Reads the maze layout and initializes the Maze struct.
 * @param m A pointer to the Maze struct.
 */
void maze_input_read(Maze **m);

/**
 * @brief Initializes a Maze with the information provided by the user.
 * @param m A pointer to the Maze struct to be initialized.
 * @param config The MazeInfo struct containing maze details.
 */
void init_maze(Maze *m, MazeInfo config);

/**
 * @brief Gets the index in the maze string for a given Point.
 * @param p The Point.
 * @param cols The number of columns in the maze.
 * @return The index corresponding to the Point in the maze string.
 */
int get_maze_index(Point p, int cols);

/**
 * @brief Checks if a character represents a wall in the maze.
 * @param c The character to be checked.
 * @return true if the character represents a wall, false otherwise.
 */
bool is_maze_wall(char c);

/**
 * @brief Checks if a Point is within the bounds of the maze.
 * @param p The Point to be checked.r
 * @param info The MazeInfo struct containing maze details.
 * @return true if the Point is within the bounds, false otherwise.
 */
bool is_point_inside_maze(Point p, MazeInfo info);

#endif