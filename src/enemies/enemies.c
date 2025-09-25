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

void init_enemies(Enemy enemies[MAX_ENEMIES], int type, SDL_Renderer *renderer, SDL_Texture *enemy_texture) {
    SDL_Log("[enemies] Initializing enemies array: %p, Renderer: %p", enemies, renderer);
    if (!enemies || !renderer) {
        SDL_Log("[enemies] Enemies array or renderer is NULL, aborting init_enemies.");
        return;
    }
    if (!enemy_texture) {
        SDL_Log("[enemies] Warning: enemy_texture is NULL — enemies will be initialized without textures.");
    }

    Uint32 current_time = SDL_GetTicks();
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].ship.x = rand() % WINDOW_WIDTH;
        enemies[i].ship.y = rand() % WINDOW_HEIGHT;
        enemies[i].ship.width = 40;
        enemies[i].ship.height = 40;
        enemies[i].ship.health = 50;
        enemies[i].type = rand() % 3;
        enemies[i].is_active = false;
        enemies[i].is_boss = (type == 2);
        enemies[i].spawn_time = current_time + (rand() % 5000);
        enemies[i].speed_x = (rand() % 4) -1;
        enemies[i].speed_y = 1 + rand() % 2;
        enemies[i].start_x = enemies[i].ship.x;
        enemies[i].phase = rand() % 360;
        enemies[i].damage = 10;

        // Affecter la texture déjà chargée
        enemies[i].texture = enemy_texture;
    }
}

void update_enemies(Enemy enemies[MAX_ENEMIES]) {
    if (!enemies) return;
    Uint32 current_time = SDL_GetTicks();

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].is_active && current_time >= enemies[i].spawn_time) {
            enemies[i].is_active = true;
            // reset position en haut par exemple
            enemies[i].ship.y = -enemies[i].ship.height;
            enemies[i].start_x = rand() % (WINDOW_WIDTH - enemies[i].ship.width);
            enemies[i].ship.x = enemies[i].start_x;
        }
        if (enemies[i].is_active) {
            // Mouvement selon le type (une seule modification par frame)
            switch (enemies[i].type) {
                case 0: // droit
                    enemies[i].ship.y += enemies[i].speed_y;
                    break;
                case 1: // zigzag sin
                    enemies[i].ship.x = enemies[i].start_x + (int)(20 * sin(current_time / 500.0 + enemies[i].phase));
                    enemies[i].ship.y += enemies[i].speed_y;
                    break;
                case 2: // S plus prononcé
                    enemies[i].ship.x = enemies[i].start_x + (int)(30 * sin(current_time / 300.0 + enemies[i].phase));
                    enemies[i].ship.y += enemies[i].speed_y;
                    break;
            }

            // Si l'ennemi sort du bas -> désactiver / replanifier spawn
            if (enemies[i].ship.y > WINDOW_HEIGHT) {
                enemies[i].is_active = false;
                enemies[i].spawn_time = current_time + random_delay(3000, 10000);
            }
        }
    }
}


// void update_enemies(Enemy enemies[MAX_ENEMIES]) {
//     SDL_Log("[enemies] Updating enemies array: %p", enemies);
//     if (!enemies) {
//         SDL_Log("[enemies] Enemies array is NULL, aborting update_enemies.");
//         return;
//     }
//     Uint32 current_time = SDL_GetTicks();
//     for (int i = 0; i < MAX_ENEMIES; i++) {
//         if (!enemies[i].is_active && current_time >= enemies[i].spawn_time) {
//             enemies[i].is_active = true;
//             SDL_Log("Enemy %d activated at time %d", i, current_time);
//         }
//         if (enemies[i].is_active) {
//             SDL_Log("Updating enemy %d: x=%d, y=%d", i, enemies[i].ship.x, enemies[i].ship.y);
//             // gerer le mouvement selon le type
//             if (enemies[i].type == 0) {
//                 enemies[i].ship.y += enemies[i].speed_y;
//             }
//             else if (enemies[i].type == 1) {
//                 enemies[i].ship.x = enemies[i].start_x + (int)(20 * sin((current_time / 500.0) + enemies[i].phase));
//                 enemies[i].ship.y += enemies[i].speed_y;
//             }
//             else if (enemies[i].type == 2) {
//                 enemies[i].ship.x = enemies[i].start_x + (int)(30 * sin(current_time / 300.0 + enemies[i].phase));
//                 enemies[i].ship.y += enemies[i].speed_y;
//             }

//             // Mouvement vertical
//             enemies[i].ship.y += enemies[i].speed_y;
//             enemies[i].ship.x = enemies[i].start_x + (int)(20 * sin((current_time / 500.0) + enemies[i].phase));
//         }
//     }
// }

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
        // The enemy textures are shared (loaded once by the game). Do not destroy
        // them here to avoid double-free. The owning code (e.g. cleanup_game)
        // should destroy the shared texture once.
        enemies[i].texture = NULL;
        enemies[i].is_active = false;
    }
}
