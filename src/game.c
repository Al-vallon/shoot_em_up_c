#include "game.h"
#include "hud/hud.h"
#include "config.h"


void init_game(Game *game) {
    init_player(&game->player,"alex", WINDOW_WIDTH / 2, WINDOW_HEIGHT/2);  // centre l’écran
}

void handle_input(Game *game, SDL_Event *event) {
    // Ici on route vers le joueur
    handle_player_input(&game->player, event);
}

void update_game(Game *game) {
    update_player(&game->player);
}

void render_game(Game *game, SDL_Renderer *renderer) {
    render_player(&game->player, renderer);
    render_health_bar(&game->player, renderer);
}

void cleanup_game(Game *game) {
    cleanup_player(&game->player);
}
