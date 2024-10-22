/**
 * @author Marco Netti
 * @file moves_list.c
 * @brief Implementation of the moves_list header (moves_list.h).
 */

#include "../include/moves_list.h"
#include "../include/graphics.h"

void init_moves_list(PMovesList *l) {
    (*l)->head = (*l)->tail = NULL;
}

PMovesList create_moves_list() {
    PMovesList l = malloc(sizeof(MoveCell));
    init_moves_list(&l);
    return l;
}

void push_front_move(PMovesList *l, GameMove m) {
    PMoveCell node = malloc(sizeof(MoveCell));
    node->info = m;
    node->next = (*l)->head;

    if((*l)->head == NULL) {
        (*l)->tail = node;
    }

    (*l)->head = node;
}

void push_back_move(PMovesList *l, GameMove m) {
    if (is_moves_list_empty(l)) {
        push_front_move(l, m);
    } else {
        PMoveCell node = malloc(sizeof(MoveCell));
        node->info = m;
        node->next = NULL;
        (*l)->tail->next = node;
        (*l)->tail = node;
    }
}

void destroy_moves_list(PMovesList *l) {
    PMoveCell current = (*l)->head;
    while (current != NULL) {
        PMoveCell tmp = current;
        current = current->next;
        free(tmp);
    }
    init_moves_list(l);
}

bool is_moves_list_empty(PMovesList *l) {
    return (*l)->head == NULL;
}

void print_moves_list(PMovesList *l) {
    if(!is_moves_list_empty(l)) {
        PMoveCell pc = (*l)->head;
        while(pc) {
            printf("%c", pc->info);
            pc = pc->next;
        }
    }
    else {
        display_message("No solution found!");
    }
}