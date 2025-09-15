#ifndef SHIP_H
#define SHIP_H

#include <SDL2/SDL.h>

typedef struct {
    int score;
    int health;
    int x, y;
    int width, height;
    int speed;
} Ship;

#endif // SHIP_H
