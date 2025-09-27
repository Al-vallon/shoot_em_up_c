#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "../player/player.h"
#include "../enemies/enemies.h"

typedef struct {
    Player player;
    Enemy enemies[MAX_ENEMIES];
    SDL_Texture *enemy_texture;
} Game;

void init_game(Game *game, SDL_Renderer *renderer);
void handle_input(Game *game, SDL_Event *event);
void update_game(Game *game);
void render_game(Game *game, SDL_Renderer *renderer);
void cleanup_game(Game *game);

#endif // GAME_H
