#include "collision.h"
#include "../ship/ship.h"

int check_collision(const Ship *a, const Ship *b) {
    if (!a || !b) {
        return 0; // No collision if either ship is NULL
    }

    // Simple AABB (Axis-Aligned Bounding Box) collision detection
    if (a->x < b->x + b->width &&
        a->x + a->width > b->x &&
        a->y < b->y + b->height &&
        a->y + a->height > b->y) {
        SDL_Log("Collision detected between ships");
        return 1; // Collision detected
    }
    return 0; // No collision
}
