/**
 * @author Marco Netti
 * @file entities.c
 * @brief Implementation of the entities header (entities.h).
 */

#include "../include/entities.h"

void init_entities(Entities *e, Point start) {
    e->snake.score = 1000;
    e->snake.grabbed_coins = 0;
    e->snake.body = create_points_list();
    push_front_point(&e->snake.body, start);
    e->drill.active = false;
    e->drill.usages = 0;
}

void entities_update(Entities **e, char *tile) {
    switch (*tile) {
        case '$':
            snake_apply_coin(&(*e)->snake);
            *tile = ' ';
            break;
        case '!':
            snake_apply_sudden(&(*e)->snake);
            *tile = ' ';
            break;
        case 'T':
            drill_set(&(*e)->drill);
            *tile = ' ';
            break;
        default:
            break;
    }
}

void snake_apply_coin(Snake *s) {
    s->grabbed_coins += 1;
    s->score += 10;
    push_back_point(&s->body, s->body->tail->info);
}

void snake_apply_sudden(Snake *s) {
    if(s->grabbed_coins >= 1) {
       s->grabbed_coins /= 2;
       s->score -= s->grabbed_coins * 10;
       halve_points_list(&s->body);
    }
}

void snake_update(Snake *s, Point next) {
    Point old_head_info = s->body->head->info;
    int old_size = s->body->size;
    adjust_cells(&s->body, next);
    if (!equal(old_head_info, s->body->head->info)) {
        --s->score;
        if (s->body->size < old_size) {
            s->score -= (old_size - s->body->size) * 10;
        }
    }
}

void drill_set(Drill *d) {
    if (!d->active) d->active = true;
    d->usages += 3;
}

void drill_update(Drill *d) {
    --d->usages;
    if (d->active && d->usages == 0) d->active = false;
}