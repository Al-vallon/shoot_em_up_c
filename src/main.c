#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include "./game/game.h"
#include "config.h"
#include <time.h>

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Shoot Em Up",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Configurer la priorité des logs pour afficher tous les messages
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);

    // Test initial pour vérifier SDL_Log
    SDL_Log("SDL_Log fonctionne correctement.");

    Game game;
    SDL_Log("Initializing game...");
    init_game(&game, renderer);
    SDL_Log("game initialized");
    SDL_Log("Enemies initialized");

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
            handle_input(&game, &event);
        }

        SDL_Log("Updating game...");
        SDL_Log("[main] Appel de update_game avec game: %p", &game);
        update_game(&game);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fond noir
        SDL_RenderClear(renderer);

        SDL_Log("Rendering game...");
        render_game(&game, renderer);

        SDL_Log("Presenting renderer...");
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 fps
    }
    SDL_Log("Exiting main loop...");


    // Clean up game resources and SDL objects
    SDL_Log("Cleaning up game resources");
    cleanup_game(&game);

    if (renderer) {
        SDL_Log("Destruction du renderer");
        SDL_DestroyRenderer(renderer);
    }

    if (window) {
        SDL_Log("Destruction de la fenêtre");
        SDL_DestroyWindow(window);
    }

    SDL_Log("Quitting SDL");
    SDL_Quit();

    return 0;
}
