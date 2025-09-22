#include "../player/player.h"
#include "../config.h"

#include <string.h>

void init_player(Player *player, const char *name, int x, int y, SDL_Renderer *renderer) {
    SDL_Log("[player] Initializing player struct: %p, Renderer: %p", player, renderer);
    if (!player || !renderer) {
        SDL_Log("[player] Player struct or renderer is NULL, aborting init_player.");
        return;
    }

    strncpy(player->name, name, sizeof(player->name) - 1);

    player->name[sizeof(player->name) - 1] = '\0'; // Ensure null-termination
    player->score = 0;
    player->life = 3;

    // Initialize ship
    player->ship.health = 100;
    player->ship.x = x;
    player->ship.y = y;
    player->ship.width = 50;
    player->ship.height = 50;
    player->ship.speed = 15;

    player->texture = IMG_LoadTexture(renderer, "assets/sprite/ship/hero.png");
    if (!player->texture) {
        SDL_Log("Failed to load player texture: %s", SDL_GetError());
    } else {
        SDL_Log("Player texture loaded successfully");
    }
}

void update_player(Player *player) {
    SDL_Log("[player] Updating player struct: %p", player);
    if (!player) {
        SDL_Log("[player] Player pointer is NULL, aborting update_player.");
        return;
    }

    if (player->ship.x < 0) player->ship.x = 0;
    if (player->ship.x > WINDOW_WIDTH - player->ship.width) player->ship.x = WINDOW_WIDTH - player->ship.width;
    if (player->ship.y < 0) player->ship.y = 0;
    if (player->ship.y > WINDOW_HEIGHT - player->ship.height) player->ship.y = WINDOW_HEIGHT - player->ship.height;
}

void handle_player_input(Player *player, SDL_Event *event) {
    Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_LEFT]) {
        player->ship.x -= player->ship.speed;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        player->ship.x += player->ship.speed;
    }
    if (keystate[SDL_SCANCODE_UP]) {
        player->ship.y -= player->ship.speed;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        player->ship.y += player->ship.speed;
    }

    // if (keystate[SDL_SCANCODE_SPACE]) {
    //     // Tirer un projectile (à implémenter)
    // }
}

void render_player(Player *player, SDL_Renderer *renderer) {
    SDL_Log("[player] Rendering player struct: %p, Renderer: %p", player, renderer);
    if (!player || !renderer) {
        SDL_Log("[player] Player struct or renderer is NULL, aborting render_player.");
        return;
    }

    SDL_Rect rect = { player->ship.x, player->ship.y, player->ship.width, player->ship.height };

    if (player->texture) {
        if (SDL_RenderCopy(renderer, player->texture, NULL, &rect) != 0) {
            SDL_Log("SDL_RenderCopy failed: %s", SDL_GetError());
        }
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // cyan
        SDL_RenderFillRect(renderer, &rect);
    }
}

void cleanup_player(Player *player) {
    SDL_Log("[player] Cleaning up player struct: %p", player);
    if (!player) {
        SDL_Log("[player] Player pointer is NULL, aborting cleanup_player.");
        return;
    }
    if (player->texture) {
        SDL_Log("[player] Destroying player texture: %p", player->texture);
        SDL_DestroyTexture(player->texture);
        player->texture = NULL;
    }
    SDL_Log("[player] Finished cleanup_player");
}