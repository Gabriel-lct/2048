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
    GUI *gui = nullptr;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    gui = new GUI();

    // Initialize the gui with a title, position, size, and fullscreen option
    gui->init("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (gui->running())
    {
        // Initialize the Time before any instructions
        frameStart = SDL_GetTicks();

        gui->handleEvents();
        gui->update();
        gui->render();

        // Delay the frame to reach the wanted frameTime
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    gui->clean();
}

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
    // Max tile in corner - Power of 2 prowimity - number of empty cells - score
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
    VectDouble genome = {14.9085, 5.27724, 5.71421, 3.52666};
    int populationSize = 20;
    int maxGamesPerGenome = 2;
    int maxGenerations = 2;
    double mutationRate = 0.3;
    double mutationStrength = 0.4;

    BoardDouble firstPopulation = initializePopulationFromGenome(genome, populationSize, mutationRate);

    runGeneticAlgorithm(firstPopulation, maxGamesPerGenome, maxGenerations, mutationRate, mutationStrength);
}

int main(int argc, char const *argv[])
{
    run_GA();
    /* int DISPLAY_MODE;
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
    } */

    return 0;
}
