#include "./include/Display.h"
#include "./include/Game.h"
#include "./include/Utils.h"
#include "./include/AI.h"
#include "./include/GA.h"
// #include "./include/GUI.h"

#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>

/* void run_GUI()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;


    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
} */

void run_CLI()
{
    clearConsole();
    int N = 4;
    int M = 4;
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
            int c = 0;
            slide(board, dir, S, c);
            spawn(board, c);
            clearConsole();
        }
    }
}

void run_AI()
{
    // Max tile in corner - Power of 2 prowimity - number of empty tiles - score
    VectDouble genome = {14.9085, 5.27724, 5.71421, 3.52666};
    clearConsole();
    int N = 4;
    int M = 4;
    int S = 0;
    Board board = genBoard(N, M);

    while (true)
    {
        std::cout << "SCORE: " << S << std::endl;
        displayBoard(board);
        int c = 0;
        int dir = findBestMove(board, S, 6, genome);
        if (dir == -1)
        {
            std::cout << "Game over!" << std::endl;
            return;
        }
        slide(board, dir, S, c);
        spawn(board, c);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clearConsole();
    }
}

void run_GA()
{
    std::cout << "Running genetic algorithm..." << std::endl;
    VectDouble genome = {1, 1, 1, 1, 1};
    int populationSize = 100;
    int maxGamesPerGenome = 50;
    int maxGenerations = 200;
    double mutationRate = 0.15;
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
    if (DISPLAY_MODE == 2)
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
