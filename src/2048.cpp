#include "./include/Display.h"
#include "./include/Game.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Game *game = nullptr;

int main(int argc, char const *argv[])
{
    // Set the frames per second
    const int FPS = 20;
    // Calculate the frame delay
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    // Create a new game instance
    game = new Game();

    // Initialize the game with a title, position, size, and fullscreen flag
    game->init("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    // Main game loop
    while (game->running())
    {
        // Initialize the Time before any instructions
        frameStart = SDL_GetTicks();

        // Handle game events, updates, and rendering
        game->handleEvents();
        game->update();
        game->render();

        // Delay the frame to reach the wanted frameTime
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}

/*     int N = 4;
int M = 4;

Plateau plateau = genPlateau(N, M);

while (true)
{
    displayBoard(plateau);
    int dir = takeInput();
    if (dir == -1)
    {
        std::cout << "Commande invalide" << std::endl;
    }
    else
    {
        slide(plateau, dir);
    }
}

return 0; */
