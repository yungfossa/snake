#ifndef SNAKE_FINAL_LIST_H
#define SNAKE_FINAL_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Point {
    int x;
    int y;
} Point;

Point create_point(int, int);

bool equal(Point, Point);

typedef struct Cell {
    Point info;
    struct Cell *next;
    struct Cell *prev;
} Cell;

typedef struct Cell *PCell;

typedef struct List {
    PCell head;
    PCell tail;
    PCell target;
    int size;
} List;

typedef struct List *PList;

void init_list(PList *);

PList create_list();

bool empty(PList *);

void push_front(PList *, Point);

void push_back(PList *, Point);

void pop_back(PList *);

void destroy_list(PList *);

void print_list(PList *);

Point get_head(PList *);

bool contains(PList *, Point);

void reduce_list(PList *);

void adjust_cells(PList *, Point);

void remove_cells_after_target(PList *, Point);

#endif //SNAKE_FINAL_LIST_H
