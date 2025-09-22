// #ifndef ENEMIES_H
// #define ENEMIES_H

// #include <stdbool.h>
// #include <SDL2/SDL.h>
// #include "../ship/ship.h"

// #define MAX_ENEMIES 10

// typedef struct {
//     Ship ship;
//     SDL_Texture *texture; 
//     int type;           // Type d'ennemi pour pattern
//     bool is_active;
//     bool is_boss;
//     Uint32 spawn_time;
//     int speed_y;        // vitesse verticale
//     int speed_x;        // vitesse horizontale pour oscillation
//     int start_x;        // position horizontale de départ (pour zig-zag)
// } Enemy;

// // Prototypes
// SDL_Texture* load_enemy_texture(SDL_Renderer *renderer, const char *path);
// void init_enemies(Enemy enemies[MAX_ENEMIES], SDL_Texture *texture, int type);
// void update_enemies(Enemy enemies[MAX_ENEMIES]);
// void render_enemies(Enemy enemies[MAX_ENEMIES], SDL_Renderer *renderer);
// void cleanup_enemies(Enemy enemies[MAX_ENEMIES]);

// #endif // ENEMIES_H
#ifndef ENEMIES_H
#define ENEMIES_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../ship/ship.h"

#define MAX_ENEMIES 10
#define ENEMY_TEXTURE_PATH "assets/sprite/ship/enemy1.png"

// Structure Enemy, qui contient un Ship + propriétés spécifiques
typedef struct {
    Ship ship;           // Structure de base
    SDL_Texture *texture;
    int type;            // Type de mouvement (0 = droit, 1 = zig-zag, 2 = S)
    bool is_active;
    bool is_boss;
    Uint32 spawn_time;   // Moment où l'ennemi apparaît
    int speed_x;         // Vitesse horizontale
    int speed_y;         // Vitesse verticale
    int start_x;         // Position horizontale initiale pour mouvements spéciaux
} Enemy;

// Prototypes
SDL_Texture* load_enemy_texture(SDL_Renderer *renderer, const char *path);
void init_enemies(Enemy enemies[MAX_ENEMIES], int type, int x, int y, SDL_Renderer *renderer);
void update_enemies(Enemy enemies[MAX_ENEMIES]);
void render_enemies(Enemy enemies[MAX_ENEMIES], SDL_Renderer *renderer);
void cleanup_enemies(Enemy enemies[MAX_ENEMIES]);

#endif // ENEMIES_H
