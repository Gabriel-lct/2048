#include "./include/Display.h"
#include "./include/Game.h"
#include "./include/Utils.h"
#include "./include/AI.h"
#include "./include/GA.h"
#include "./include/GUI.h"

#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>

void run_GUI()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    int N = 4;
    int M = 4;

    int S = 0;

    Board board = genBoard(N, M);
    VectDouble genome = {10, 5, 0, 2, 10};

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;
    initSDL(window, renderer, font, 600, 600);
    bool running = true;
    bool iaRunning = false;
    Uint32 frameStart, frameTime;
    while (running)
    {
        frameStart = SDL_GetTicks();

        renderBoard(board, renderer, font);
        SDL_RenderPresent(renderer);
        int dir = handleEvents(running, board);

        if (dir == 4)
        {
            iaRunning = !iaRunning;
        }
        if (iaRunning)
        {
            dir = findBestMove(board, S, 6, genome);
        }

        slide(board, dir, S, true);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Clean up SDL resources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void run_CLI()
{
    clearConsole();
    int N = 8;
    int M = 8;
    int S = 0;

    Board board = genBoard(N, M);

    while (true)
    {
        std::cout << "SCORE: " << S << std::endl;
        displayBoard(board);
        int dir = takeInput();
        if (dir == -1)
        {
            std::cout << "Commande invalide" << std::endl;
        }
        else
        {
            slide(board, dir, S, true);
        }
    }
}

void run_AI()
{
    // Max tile in corner - Power of 2 prowimity - number of empty tiles - score
    VectDouble genome = {10, 5, 0, 2, 10};
    clearConsole();
    int N = 4;
    int M = 4;
    int S = 0;
    Board board = genBoard(N, M);

    while (true)
    {
        std::cout << "SCORE: " << S << std::endl;
        displayBoard(board);
        int dir = findBestMove(board, S, 10, genome);
        if (dir == -1)
        {
            std::cout << "Game over!" << std::endl;
            return;
        }
        slide(board, dir, S, true);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clearConsole();
    }
}

void run_GA()
{
    std::cout << "Running genetic algorithm..." << std::endl;
    VectDouble genome = {1.05984, 0.159454, 0.115378, 0.636072, 2.69887}; //{1.51422, 0.173924, 1.4986, 1.04476, 0.243911};
    int populationSize = 50;
    int maxGamesPerGenome = 10;
    int maxGenerations = 20;
    double mutationRate = 0.1;
    double mutationStrength = 0.1;

    BoardDouble firstPopulation = initializePopulationFromGenome(genome, populationSize, mutationRate);

    runGeneticAlgorithm(firstPopulation, maxGamesPerGenome, maxGenerations, mutationRate, mutationStrength);
}

int main(int argc, char const *argv[])
{
    // run_AI();
    int DISPLAY_MODE;
    // Provisionally using only CLI
    std::cout << "Please select a Game Mode: GUI (1), CLI (2), AI (3), GA (4): ";
    std::cin >> DISPLAY_MODE;
    if (DISPLAY_MODE == 1)
    {
        run_GUI();
    }
    else if (DISPLAY_MODE == 2)
    {
        run_CLI();
    }
    else if (DISPLAY_MODE == 3)
    {
        run_AI();
    }
    else if (DISPLAY_MODE == 4)
    {
        run_GA();
    }

    return 0;
}
