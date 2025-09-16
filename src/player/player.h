#ifndef PLAYER_H
#define PLAYER_H

#include "../ship/ship.h"

#include <SDL2/SDL.h>

typedef struct {
    char name[50];  
    int score;      
    int life;       
    Ship ship;
    SDL_Texture *texture; // Texture du vaisseau
} Player;

// Prototypes des fonctions
void init_player(Player *player, const char *name, int x, int y, SDL_Renderer *renderer);
void update_player(Player *player);
void handle_player_input(Player *player, SDL_Event *event);
void render_player(Player *player, SDL_Renderer *renderer);


#endif // PLAYER_H