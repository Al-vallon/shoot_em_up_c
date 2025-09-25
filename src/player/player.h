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
    Uint32 last_hit_time; // Temps du dernier hit pour le cooldown
    Uint32 last_shot_time; // Temps du dernier tir pour limiter la cadence
} Player;

void damage_player(Player *player, int damage);

// Prototypes des fonctions
void init_player(Player *player, const char *name, int x, int y, SDL_Renderer *renderer);
void update_player(Player *player);
void handle_player_input(Player *player, SDL_Event *event);
void render_player(Player *player, SDL_Renderer *renderer);
void cleanup_player(Player *player);


#endif // PLAYER_H