#define ENEMIES_C
#include "enemies.h"

#include <time.h>

// fonction usuelle
int random_delay(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void init_enemies(Enemies enemies[10], int type, int x, int y, SDL_Renderer *renderer) {
    Uint32 current_time = SDL_GetTicks(); // Temps actuel en millisecondes

    for (int i = 0; i < 10; i++) {
        enemies[i].ship.x = x + i * 50; // Décalage pour chaque ennemi
        enemies[i].ship.y = y;
        enemies[i].ship.width = 40;
        enemies[i].ship.height = 40;
        enemies[i].ship.health = 50;
        enemies[i].type = type;
        enemies[i].is_active = false; // Désactivé par défaut
        enemies[i].spawn_time = current_time + random_delay(1000, 5000); // Apparition entre 1 et 5 secondes
        enemies[i].texture = IMG_LoadTexture(renderer, "assets/sprite/ship/enemy1.png");
        if (!enemies[i].texture) {
            SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
        }
    }
}

void render_enemies(Enemies enemies[10], SDL_Renderer *renderer) {
    SDL_Log("Rendering enemy at (%d, %d)", enemies->ship.x, enemies->ship.y);
    // Vérification des pointeurs avant le rendu
    if (!renderer) {
        SDL_Log("Renderer is NULL, cannot render enemy.");
        return;
    }
    if (!enemies) {
        SDL_Log("Enemies pointer is NULL, cannot render.");
        return;
    }
    if (!enemies->texture) {
        SDL_Log("Enemy texture is NULL, skipping render.");
        return;
    }
    if (enemies->is_active && enemies->texture) {
        SDL_Rect rect = { enemies->ship.x, enemies->ship.y, enemies->ship.width, enemies->ship.height };
        SDL_RenderCopy(renderer, enemies->texture, NULL, &rect);
    }
}

void update_enemies(Enemies enemies[10]) {
    Uint32 current_time = SDL_GetTicks(); // Temps actuel en millisecondes

    for (int i = 0; i < 10; i++) {
        // Ajouter des logs pour déboguer les temps d'apparition
        SDL_Log("Current time: %d, Enemy %d spawn time: %d", current_time, i, enemies[i].spawn_time);

        if (!enemies[i].is_active && current_time >= enemies[i].spawn_time) {
            enemies[i].is_active = true;
            SDL_Log("Enemy %d activated at time %d", i, current_time);
        }
    }
}

void cleanup_enemies(Enemies enemies[10]) {
    // Vérification des pointeurs avant de détruire la texture
    if (!enemies) {
        SDL_Log("Enemies pointer is NULL, skipping cleanup.");
        return;
    }
    if (!enemies->texture) {
        SDL_Log("Enemy texture is NULL, nothing to destroy.");
        return;
    }

    if (enemies->texture) {
        SDL_Log("Destroying enemy texture");
        SDL_DestroyTexture(enemies->texture);
        enemies->texture = NULL;
    }
    enemies->is_active = false;
}

// Fonction pour définir la position initiale d'un ennemi
void set_enemy_position(Ship *ship, int x, int y) {
    if (!ship) {
        SDL_Log("Ship pointer is NULL, cannot set position.");
        return;
    }
    ship->x = x;
    ship->y = y;
    SDL_Log("Ship position set to (%d, %d)", x, y);
}


