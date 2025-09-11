#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

// Définition de la struct Game
typedef struct {
    int x, y;
} Game;

// Prototypes des fonctions
void init_game(Game *game);
void update_game(Game *game);
void handle_input(Game *game, SDL_Event *event);
void render_game(Game *game, SDL_Renderer *renderer);
void cleanup_game(Game *game);

#endif
