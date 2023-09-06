#include "../include/game_header.h"

void init_entities(Entities *e) {
    e->snake.score = 1000;
    e->snake.body = create_list();
    init_list(&e->snake.body);
    push_front(&e->snake.body, MAZE_START);
    e->drill.active = false;
    e->drill.usages = 0;
}

void set_drill(Drill *d) {
    if (!d->active) d->active = true;
    d->usages += 3;
}

void apply_coin(Snake *s) {
    s->score += 10;
    push_back(&s->body, s->body->tail->info);
}

void apply_sudden(Snake *s) {
    s->score /= 2;
    reduce_list(&s->body);
}

void update_drill(Drill *d) {
    if (d->active && d->usages == 0) d->active = false;
}

void update_entities(char *c, Entities **e) {
    switch (*c) {
        case '$':
            apply_coin(&(*e)->snake);
            *c = ' ';
            break;
        case '!':
            apply_sudden(&(*e)->snake);
            *c = ' ';
            break;
        case 'T':
            set_drill(&(*e)->drill);
            *c = ' ';
            break;
        default:
            break;
    }
}

void update_snake(Snake *s, Point next) {
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