#include "../include/list.h"

Point create_point(int x, int y) {
    Point p = {x, y};
    return p;
}

bool equal(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void init_list(PList *l) {
    (*l)->head = (*l)->tail = (*l)->target = NULL;
    (*l)->size = 0;
}

PList create_list() {
    PList l = malloc(sizeof(List));
    init_list(&l);
    return l;
}

bool empty(PList *l) {
    return (*l)->head == NULL;
}

void push_front(PList *l, Point p) {
    PCell node = malloc(sizeof(Cell));
    node->info = p;
    node->next = (*l)->head;
    node->prev = NULL;

    if (empty(l)) {
        (*l)->tail = node;
    } else {
        (*l)->head->prev = node;
    }

    (*l)->head = node;
    ++(*l)->size;
}

void push_back(PList *l, Point p) {
    if (empty(l)) {
        push_front(l, p);
    } else {
        PCell node = malloc(sizeof(Cell));
        node->info = p;
        node->next = NULL;
        node->prev = (*l)->tail;

        (*l)->tail->next = node;
        (*l)->tail = node;
        ++(*l)->size;
    }
}

void pop_back(PList *l) {
    if (!empty(l)) {
        PCell to_remove = (*l)->tail;

        if ((*l)->head == (*l)->tail) {
            init_list(l);
        } else {
            (*l)->tail = to_remove->prev;
            (*l)->tail->next = NULL;
        }

        free(to_remove);
        --(*l)->size;
    }
}

void destroy_list(PList *l) {
    PCell current = (*l)->head;

    while (current != NULL) {
        PCell tmp = current;
        current = current->next;
        free(tmp);
    }

    init_list(l);
}

void print_list(PList *l) {
    if (empty(l)) {
        printf("the list is empty!\n");
        return;
    }

    PCell pc = (*l)->head;

    while (pc != NULL) {
        printf("(%d, %d)\n", pc->info.x, pc->info.y);
        pc = pc->next;
    }
}

void reduce_list(PList *l) {
    if (!empty(l)) {
        int sz = (*l)->size;

        if (sz == 1) {
            pop_back(l);
            init_list(l);
        } else {
            sz /= 2;
            for (int i = 0; i < sz; ++i) pop_back(l);
            (*l)->size = sz;
        }
    }
}

Point get_head(PList *l) {
    return (*l)->head->info;
}

bool contains(PList *l, Point p) {
    PCell pc = (*l)->head;
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

void remove_cells_after_target(PList *l, Point meeting_point) {
    Point tmp = (*l)->head->info;
    while (!equal((*l)->tail->info, (*l)->target->info)) pop_back(l);
    (*l)->head->info = meeting_point;
    (*l)->tail->info = tmp;
    (*l)->target = NULL;
}

void adjust_cells(PList *l, Point data) {
    if (!empty(l)) {
        Point old_head_info = (*l)->head->info;
        if ((*l)->size > 2 && contains(l, data)) {
            remove_cells_after_target(l, data);
        } else {
            PCell pc = (*l)->head;
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