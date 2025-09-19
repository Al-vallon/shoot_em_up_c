#include "game.h"
#include "../hud/hud.h"
#include "../config.h"

void init_game(Game *game, SDL_Renderer *renderer) {
    init_player(&game->player,"alex", WINDOW_WIDTH / 2, WINDOW_HEIGHT/2, renderer);  // centre l’écran
    init_enemies(game->enemies, 1, 100, 100, renderer);
}

void handle_input(Game *game, SDL_Event *event) {
    handle_player_input(&game->player, event);
}

void update_game(Game *game) {
    update_player(&game->player);
    update_enemies(game->enemies);
}

void render_game(Game *game, SDL_Renderer *renderer) {
    render_player(&game->player, renderer);
    render_health_bar(&game->player, renderer);
    // Parcourir correctement le tableau d'ennemis pour le rendu
    for (int i = 0; i < 10; i++) {
        render_enemies(&game->enemies[i], renderer);
    }
}

void cleanup_game(Game *game) {
    cleanup_player(&game->player);
    for (int i = 0; i < 10; i++) {
        cleanup_enemies(&game->enemies[i]);
    }
}
