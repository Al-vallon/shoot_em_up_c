#include "hud.h"
#include <SDL2/SDL.h>
#include "../player/player.h"

void render_health_bar(Player *player, SDL_Renderer *renderer) {
    int bar_width = 200;
    int bar_height = 20;
    int x = 10;
    int y = 10;

    // Dessiner le fond de la barre de vie (rouge)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect bg_rect = { x, y, bar_width, bar_height };
    SDL_RenderFillRect(renderer, &bg_rect);

    // Dessiner la partie de la barre de vie correspondant à la santé actuelle (vert)
    int health_width = (player->ship.health * bar_width) / 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   
    SDL_Rect health_rect = { x, y, health_width, bar_height };
    SDL_RenderFillRect(renderer, &health_rect);

    // Dessiner le contour de la barre de vie (blanc)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &bg_rect); 
}

void render_lives(Player *player, SDL_Renderer *renderer) {
    int x = 10;
    int y = 40;
    int spacing = 30;

    for (int i = 0; i < player->life; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // jaune
        SDL_Rect life_rect = { x + i * spacing, y, 20, 20 };
        SDL_RenderFillRect(renderer, &life_rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // noir
        SDL_RenderDrawRect(renderer, &life_rect);
    }
}