#include "game.h"
#include "../hud/hud.h"
#include "../config.h"

void init_game(Game *game, SDL_Renderer *renderer) {
    init_player(&game->player,"alex", WINDOW_WIDTH / 2, WINDOW_HEIGHT/2, renderer);  // centre l’écran
    init_enemies(&game->enemies, 1, 100, 100, renderer);
}

void handle_input(Game *game, SDL_Event *event) {
    handle_player_input(&game->player, event);
}

void update_game(Game *game) {
    update_player(&game->player);

    // Ajouter des logs pour suivre les coordonnées des ennemis
    for (int i = 0; i < 10; i++) {
        SDL_Log("Before update: Enemy %d at (%d, %d)", i, game->enemies[i].ship.x, game->enemies[i].ship.y);
    }

    // ... (logique de mise à jour des ennemis ici) ...

    for (int i = 0; i < 10; i++) {
        SDL_Log("After update: Enemy %d at (%d, %d)", i, game->enemies[i].ship.x, game->enemies[i].ship.y);
    }
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
    cleanup_enemies(&game->enemies[10]);
}
