#ifndef WEAPON_H
#define WEAPON_H

// Simple dynamic missile linked list interface
typedef struct Missile {
    float x, y;           // position
    int actif;            // 1 = active, 0 = inactive
    struct Missile *suivant;
} Missile;

#include <SDL2/SDL.h>

// Head pointer for the missile list
extern Missile* listeMissiles;

// Management functions
void tirerMissile(float x, float y);
void majMissiles();
void dessinerMissiles(SDL_Renderer *renderer);
void detruireMissiles();

#endif // WEAPON_H
