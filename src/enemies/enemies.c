#define ENEMIES_C
#include "enemies.h"

void init_enemies(Enemies *enemies, int type, int x, int y, SDL_Renderer *renderer) {
    SDL_Log("Initializing enemy at (%d, %d) with type %d", x, y, type);

    // Define spawn position using set_enemy_position
    set_enemy_position(&enemies->ship, x, y);

    enemies->type = type;
    enemies->is_active = 1; // Actif par défaut
    enemies->is_boss = (type == 2); // Supposons que le type 2 est un boss

    // Initialiser les propriétés du vaisseau ennemi en fonction du type
    switch (type) {
        case 1: // Ennemi standard
            enemies->ship.health = 50;
            enemies->ship.width = 40;
            enemies->ship.height = 40;
            enemies->ship.speed = 3;
            enemies->texture = IMG_LoadTexture(renderer, "assets/sprite/ship/enemy1.png");
            break;
        case 2: // Boss
            enemies->ship.health = 200;
            enemies->ship.width = 100;
            enemies->ship.height = 100;
            enemies->ship.speed = 1;
            enemies->texture = IMG_LoadTexture(renderer, "assets/sprite/ship/boss.png");
            break;
        default:
            // Valeurs par défaut pour les types inconnus
            enemies->ship.health = 30;
            enemies->ship.width = 30;
            enemies->ship.height = 30;
            enemies->ship.speed = 2;
            enemies->texture = IMG_LoadTexture(renderer, "assets/sprite/ship/enemy_default.png");
            break;
    }

    if (!enemies->texture) {
        SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
        enemies->is_active = false; // Désactiver l'ennemi si la texture n'est pas chargée
        return;
    }

    // Log détaillé après l'initialisation de l'ennemi
    SDL_Log("Enemy initialized: type=%d, x=%d, y=%d, width=%d, height=%d, health=%d, texture=%p", 
            enemies->type, enemies->ship.x, enemies->ship.y, 
            enemies->ship.width, enemies->ship.height, enemies->ship.health, enemies->texture);
}

void render_enemies(Enemies *enemies, SDL_Renderer *renderer) {
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

void cleanup_enemies(Enemies *enemies) {
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


