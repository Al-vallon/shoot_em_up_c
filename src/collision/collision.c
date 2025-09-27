#include "collision.h"
#include "../ship/ship.h"
#include "../weapon/weapon.h"
#include "../enemies/enemies.h"


int check_collision(const Ship *a, const Ship *b) {
    if (!a || !b) return 0;
    return (a->x < b->x + b->width &&
            a->x + a->width > b->x &&
            a->y < b->y + b->height &&
            a->y + a->height > b->y);
}

int missile_enemy_collision(Missile *missile, Enemy *enemy, Uint32 now) {
    if (!missile || !enemy || !enemy->is_active) return 0;

    // Treat missile as a small rect (4x8) centered on missile coords
    int mx = (int)missile->x;
    int my = (int)missile->y;
    int mw = 4, mh = 8;

    if (mx < enemy->ship.x + enemy->ship.width &&
        mx + mw > enemy->ship.x &&
        my < enemy->ship.y + enemy->ship.height &&
        my + mh > enemy->ship.y) {
        // hit: deactivate missile
        missile->actif = 0;
        return 1;
    }
    return 0;
}