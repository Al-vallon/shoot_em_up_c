// #include "game.h"
// #include "../hud/hud.h"
// #include "../config.h"

// void init_game(Game *game, SDL_Renderer *renderer) {
//     init_player(&game->player,"alex", WINDOW_WIDTH / 2, WINDOW_HEIGHT/2, renderer);  // centre l’écran
//     init_enemies(game->enemies, 1, 100, 100, renderer);
//     for (int i = 0; i < MAX_ENEMIES; i++) {
//         game->enemies[i].texture = enemy_texture;
//     }
// }

// void handle_input(Game *game, SDL_Event *event) {
//     handle_player_input(&game->player, event);
// }

// void update_game(Game *game) {
//     update_player(&game->player);
//     update_enemies(game->enemies);
// }

// void render_game(Game *game, SDL_Renderer *renderer) {
//     render_player(&game->player, renderer);
//     render_health_bar(&game->player, renderer);
//     for (int i = 0; i < 10; i++) {
//         render_enemies(game->enemies[i], renderer);
//     }

// }

// void cleanup_game(Game *game) {
//     cleanup_player(&game->player);
//     cleanup_enemies(game->enemies);
// }
#include "game.h"
#include "../hud/hud.h"
#include "../config.h"
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

    // Initialiser les ennemis avec la texture chargée
    init_enemies(game->enemies, 1, 100, 100, renderer);
}

void handle_input(Game *game, SDL_Event *event) {
    handle_player_input(&game->player, event);
}

void update_game(Game *game) {
    SDL_Log("[game] update_game: game struct: %p", game);
    if (!game) {
        SDL_Log("[game] update_game: game pointer is NULL, aborting.");
        return;
    }
    SDL_Log("[game] update_game: before update_player");
    update_player(&game->player);
    SDL_Log("[game] update_game: after update_player, before update_enemies");
    update_enemies(game->enemies);
    SDL_Log("[game] update_game: after update_enemies");
}

void render_game(Game *game, SDL_Renderer *renderer) {
    render_player(&game->player, renderer);
    render_health_bar(&game->player, renderer);
    render_enemies(game->enemies, renderer);
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
