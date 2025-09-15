#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "player.h"

typedef struct {
    Player player;
} Game;

void init_game(Game *game);
void handle_input(Game *game, SDL_Event *event);
void update_game(Game *game);
void render_game(Game *game, SDL_Renderer *renderer);
void cleanup_game(Game *game);

#endif

