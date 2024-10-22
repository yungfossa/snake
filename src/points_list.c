/**
 * @author Marco Netti
 * @file points_list.c
 * @brief Implementation of the points_list header (points_list.h).
 */

#include "../include/points_list.h"

Point create_point(int x, int y) {
    Point p = {x, y};
    return p;
}

bool equal(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void init_points_list(PPointsList *l) {
    (*l)->head = (*l)->tail = (*l)->target = NULL;
    (*l)->size = 0;
}

PPointsList create_points_list() {
    PPointsList l = malloc(sizeof(PointsList));
    init_points_list(&l);
    return l;
}

bool is_points_list_empty(PPointsList *l) {
    return (*l)->head == NULL;
}

void push_front_point(PPointsList *l, Point p) {
    PPointCell node = malloc(sizeof(PointCell));
    node->info = p;
    node->next = (*l)->head;
    node->prev = NULL;

    if (is_points_list_empty(l)) {
        (*l)->tail = node;
    } else {
        (*l)->head->prev = node;
    }

    (*l)->head = node;
    ++(*l)->size;
}

void push_back_point(PPointsList *l, Point p) {
    if (is_points_list_empty(l)) {
        push_front_point(l, p);
    } else {
        PPointCell node = malloc(sizeof(PointCell));
        node->info = p;
        node->next = NULL;
        node->prev = (*l)->tail;

        (*l)->tail->next = node;
        (*l)->tail = node;
        ++(*l)->size;
    }
}

void pop_back(PPointsList *l) {
    if (!is_points_list_empty(l)) {
        PPointCell to_remove = (*l)->tail;

        if ((*l)->head == (*l)->tail) {
            init_points_list(l);
        } else {
            (*l)->tail = to_remove->prev;
            (*l)->tail->next = NULL;
        }

        free(to_remove);
        --(*l)->size;
    }
}

void destroy_points_list(PPointsList *l) {
    PPointCell current = (*l)->head;

    while (current != NULL) {
        PPointCell tmp = current;
        current = current->next;
        free(tmp);
    }

    init_points_list(l);
}

void halve_points_list(PPointsList *l) {
    if (!is_points_list_empty(l)) {
        int sz = (*l)->size;

        if (sz == 1) {
            pop_back(l);
            init_points_list(l);
        } else {
            sz /= 2;
            for (int i = 0; i < sz; ++i) pop_back(l);
            (*l)->size = sz;
        }
    }
}

Point get_points_list_head(PPointsList *l) {
    return (*l)->head->info;
}

bool contains(PPointsList *l, Point p) {
    PPointCell pc = (*l)->head;
    bool contained = false;
    while (pc != NULL && !contained) {
        if (equal(pc->info, p)) {
            (*l)->target = pc;
            contained = true;
        } else {
            pc = pc->next;
        }
    }
    return contained;
}

void remove_cells_after_target(PPointsList *l, Point meeting_point) {
    Point tmp = (*l)->head->info;
    while (!equal((*l)->tail->info, (*l)->target->info)) pop_back(l);
    (*l)->head->info = meeting_point;
    (*l)->tail->info = tmp;
    (*l)->target = NULL;
}

void adjust_cells(PPointsList *l, Point data) {
    if (!is_points_list_empty(l)) {
        Point old_head_info = (*l)->head->info;
        if ((*l)->size > 2 && contains(l, data)) {
            remove_cells_after_target(l, data);
        } else {
            PPointCell pc = (*l)->head;
            pc->info = data;
            pc = pc->next;

            while (pc != NULL) {
                Point tmp = pc->info;
                pc->info = old_head_info;
                old_head_info = tmp;
                pc = pc->next;
            }
        }
    }
}