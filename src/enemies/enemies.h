#ifndef ENEMIES_H
#define ENEMIES_H

#include <stdbool.h>
#include "../ship/ship.h"

typedef struct {
    Ship ship;
    SDL_Texture *texture; 
    int type; // Type d'ennemi pour différentes apparences ou comportements
    bool is_active;
    bool is_boss;
    Uint32 spawn_time; 
} Enemies;

// Prototypes des fonctions
void init_enemies(Enemies enemies[10], int type, int x, int y, SDL_Renderer *renderer);
void update_enemies(Enemies enemies[10]);
void render_enemies(Enemies enemies[10], SDL_Renderer *renderer);
void cleanup_enemies(Enemies enemies[10]);

#endif // ENEMIES_H