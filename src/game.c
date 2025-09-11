#include "game.h"

void init_game(Game *game) {
    game->x = 320; // centre du carré
    game->y = 240;
}

void update_game(Game *game) {
    // rien pour le moment
}

void handle_input(Game *game, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_LEFT: game->x -= 5; break;
            case SDLK_RIGHT: game->x += 5; break;
            case SDLK_UP: game->y -= 5; break;
            case SDLK_DOWN: game->y += 5; break;
        }
    }
}

void render_game(Game *game, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // blanc
    SDL_Rect rect = { game->x - 25, game->y - 25, 10, 10 }; // carré 50x50
    SDL_RenderFillRect(renderer, &rect);
}

void cleanup_game(Game *game) {
    // pour l'instant rien à nettoyer
}
    