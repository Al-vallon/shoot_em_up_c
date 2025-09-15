#include "player.h"

#include <string.h>

void init_player(Player *player, const char *name, int x, int y) {
    strncpy(player->name, name, sizeof(player->name) - 1);
    player->name[sizeof(player->name) - 1] = '\0'; // Ensure null-termination
    player->score = 0;
    player->life = 3;
    // Initialize ship
    // For simplicity, we set some default values
    player->ship.health = 100;
    player->ship.x = x;
    player->ship.y = y;
    player->ship.width = 50;
    player->ship.height = 50;
    player->ship.speed = 5;
}

void update_player(Player *player) {
    if (player->ship.x < 0) player->ship.x = 0;
    if (player->ship.x > 640 - player->ship.width) player->ship.x = 640 - player->ship.width;
    if (player->ship.y < 0) player->ship.y = 0;
    if (player->ship.y > 480 - player->ship.height) player->ship.y = 480 - player->ship.height;
}

void handle_player_input(Player *player, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_LEFT: player->ship.x -= player->ship.speed; break; // Move left
            case SDLK_RIGHT: player->ship.x += player->ship.speed; break; // Move right
            case SDLK_UP: player->ship.y -= player->ship.speed; break; // Move up
            case SDLK_DOWN: player->ship.y += player->ship.speed; break; // Move down
        }
    }
}

void render_player(Player *player, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // vert
    SDL_Rect rect = { player->ship.x, player->ship.y, player->ship.width, player->ship.height };
    SDL_RenderFillRect(renderer, &rect);
}

void cleanup_player(Player *player) {
    // Pour l'instant rien à nettoyer
}