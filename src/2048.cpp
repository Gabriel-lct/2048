#include "./include/Display.h"
#include "./include/Game.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Game *game = nullptr;

void run_GUI(){
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    // Initialize the game with a title, position, size, and fullscreen option
    game->init("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running())
    {
        // Initialize the Time before any instructions
        frameStart = SDL_GetTicks();

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
}

void run_CLI(){
    int N = 4;
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
}

int main(int argc, char const *argv[])
{

    int MODE;
    std::cout << "Please select a Game Mode: GUI (1), CLI (2): ";
    std::cin >> MODE;
    if (MODE == 1){
        run_GUI();
    } else if (MODE == 2){
        run_CLI();
    }

    return 0;
}
