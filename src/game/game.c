#include "game.h"
#include "../hud/hud.h"
#include "../config.h"
#include "../collision/collision.h"
#include <SDL2/SDL_image.h>

static SDL_Texture* enemy_texture = NULL;


void init_game(Game *game, SDL_Renderer *renderer) {
    SDL_Log("[game] Game struct: %p, Renderer: %p", game, renderer);
    if (!game || !renderer) {
        SDL_Log("[game] Game or renderer is NULL, aborting init_game.");
        return;
    }

    SDL_Log("Initializing game...");

    // Initialiser le joueur
    init_player(&game->player, "Alex", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, renderer);

    if (!game->player.texture) {
        SDL_Log("Failed to load player texture: %s", SDL_GetError());
    }

    if (!enemy_texture) {
        SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
    }

    // Charger la texture ennemis une seule fois
    enemy_texture = IMG_LoadTexture(renderer, "assets/sprite/enemy.png");
    if (!enemy_texture) {
        SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
    }

    if (!enemy_texture) {
        enemy_texture = IMG_LoadTexture(renderer, "assets/sprite/ship/enemy1.png");
        if (!enemy_texture) {
            SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
        }
    }

    // Initialiser les ennemis avec la texture chargée
    init_enemies(game->enemies, 1, renderer, enemy_texture);
}

void handle_input(Game *game, SDL_Event *event) {
    handle_player_input(&game->player, event);
}

void update_game(Game *game) {
    if (!game) return;

    // Mise à jour du joueur
    if (game->player.ship.is_active)
        update_player(&game->player);

    // Mise à jour des ennemis
    update_enemies(game->enemies);

    // Vérification des collisions
    Uint32 now = SDL_GetTicks();
    const Uint32 HIT_COOLDOWN_MS = 500; // demi seconde

    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy *e = &game->enemies[i];
        if (!e->is_active) continue;
        if (!game->player.ship.is_active) break;

        if (check_collision(&game->player.ship, &e->ship)) {
            SDL_Log("Collision detected with enemy %d!", i);

            // cooldown : que si assez de temps depuis le dernier hit
            if (now - game->player.last_hit_time >= HIT_COOLDOWN_MS) {
                damage_player(&game->player, e->damage);
                game->player.last_hit_time = now;
            }

            // désactiver l'ennemi immédiatement
            e->is_active = false;
            // optionnel : le déplacer hors-écran pour éviter tout recouvrement
            e->ship.x = -1000;
            e->ship.y = -1000;
            // ou replanifier spawn:
            e->spawn_time = now + random_delay(3000, 10000);
        }
    }
}

void render_game(Game *game, SDL_Renderer *renderer) {
    render_player(&game->player, renderer);
    render_enemies(game->enemies, renderer);

    //HUD DISplay
    render_health_bar(&game->player, renderer);
    render_lives(&game->player, renderer);
}

void cleanup_game(Game *game) {
    SDL_Log("[game] Cleaning up game struct: %p", game);
    if (!game) {
        SDL_Log("[game] Game pointer is NULL, aborting cleanup.");
        return;
    }

    cleanup_player(&game->player);
    
    cleanup_enemies(game->enemies); 
    if (enemy_texture) {
        SDL_DestroyTexture(enemy_texture);
        enemy_texture = NULL;
    }
    SDL_Log("[game] Finished cleanup_game");
}
