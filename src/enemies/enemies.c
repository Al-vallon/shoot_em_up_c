#include "enemies.h"
#include "../config.h"
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// fonction usuelle
int random_delay(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void init_enemies(Enemy enemies[MAX_ENEMIES], int type, int x, int y, SDL_Renderer *renderer) {
    SDL_Log("[enemies] Initializing enemies array: %p, Renderer: %p", enemies, renderer);
    if (!enemies || !renderer) {
        SDL_Log("[enemies] Enemies array or renderer is NULL, aborting init_enemies.");
        return;
    }
    Uint32 current_time = SDL_GetTicks();
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].ship.x = rand() % WINDOW_WIDTH;
        enemies[i].ship.y = rand() % WINDOW_HEIGHT;
        enemies[i].ship.width = 40;
        enemies[i].ship.height = 40;
        enemies[i].ship.health = 50;
        enemies[i].type = type;
        enemies[i].is_active = false;
        enemies[i].is_boss = (type == 2);
        enemies[i].spawn_time = current_time + (rand() % 5000);
        enemies[i].speed_x = (rand() % 5) + 1;
        enemies[i].speed_y = (rand() % 3) + 1;
        enemies[i].start_x = enemies[i].ship.x;
        enemies[i].texture = IMG_LoadTexture(renderer, "assets/sprite/ship/enemy1.png");
        if (!enemies[i].texture) {
            SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
        }
    }
}

void update_enemies(Enemy enemies[MAX_ENEMIES]) {
    SDL_Log("[enemies] Updating enemies array: %p", enemies);
    if (!enemies) {
        SDL_Log("[enemies] Enemies array is NULL, aborting update_enemies.");
        return;
    }
    Uint32 current_time = SDL_GetTicks();
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].is_active && current_time >= enemies[i].spawn_time) {
            enemies[i].is_active = true;
            SDL_Log("Enemy %d activated at time %d", i, current_time);
        }
        if (enemies[i].is_active) {
            // Exemple de déplacement : zig-zag horizontal
            if (enemies[i].type == 1) {
                enemies[i].ship.x = enemies[i].start_x + (int)(20 * sin(current_time / 500.0));
            }
            // Mouvement vertical
            enemies[i].ship.y += enemies[i].speed_y;
        }
    }
}

void render_enemies(Enemy enemies[MAX_ENEMIES], SDL_Renderer *renderer) {
    SDL_Log("[enemies] Rendering enemies array: %p, Renderer: %p", enemies, renderer);
    if (!enemies || !renderer) {
        SDL_Log("[enemies] Enemies array or renderer is NULL, aborting render_enemies.");
        return;
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!renderer || !enemies[i].texture) continue;
        if (enemies[i].is_active) {
            SDL_Rect rect = { enemies[i].ship.x, enemies[i].ship.y, enemies[i].ship.width, enemies[i].ship.height };
            SDL_RenderCopy(renderer, enemies[i].texture, NULL, &rect);
        }
    }
}

void cleanup_enemies(Enemy enemies[MAX_ENEMIES]) {
    SDL_Log("[enemies] Cleaning up enemies array: %p", enemies);
    if (!enemies) {
        SDL_Log("[enemies] Enemies array is NULL, aborting cleanup_enemies.");
        return;
    }
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].texture) {
            SDL_DestroyTexture(enemies[i].texture);
            enemies[i].texture = NULL;
        }
        enemies[i].is_active = false;
    }
}
