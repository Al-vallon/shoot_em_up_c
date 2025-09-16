#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "../player/player.h"
#include "../enemies/enemies.h"

typedef struct {
    Player player;
    Enemies enemies[10]; // Exemple avec un tableau fixe de 10 ennemis
} Game;

void init_game(Game *game, SDL_Renderer *renderer);
void handle_input(Game *game, SDL_Event *event);
void update_game(Game *game);
void render_game(Game *game, SDL_Renderer *renderer);
void cleanup_game(Game *game);

#endif // GAME_H
