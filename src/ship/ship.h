#ifndef SHIP_H
#define SHIP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    int score;
    int health;
    int x, y;
    int width, height;
    int speed;
    int damage;
    bool is_active;
} Ship;

#endif // SHIP_H
