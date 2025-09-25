#include "collision.h"
#include "../ship/ship.h"


int check_collision(const Ship *a, const Ship *b) {
    if (!a || !b) return 0;
    return (a->x < b->x + b->width &&
            a->x + a->width > b->x &&
            a->y < b->y + b->height &&
            a->y + a->height > b->y);
}