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

VectDouble genome = {10, 5, 0, 2, 10};

int run_GUI()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    int N = 10;
    int M = 10;

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

        renderBoard(board, renderer, font, window);
        renderScore(S, renderer, font);
        SDL_RenderPresent(renderer);
        int dir = handleEvents(running, board);

        if (dir == 4)
        {
            iaRunning = !iaRunning;
        } else if (dir == 5)
        {
            terminateGUI(window, renderer, font);
            return 1;
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
    terminateGUI(window, renderer, font);
    return 0;
}

int run_CLI()
{
    clearConsole();
    const int N = 4;
    const int M = 4;
    int score = 0;
    bool isIaRunning = false;
    Board board = genBoard(N, M);

    while (true)
    {
        clearConsole();
        std::cout << "SCORE: " << score << std::endl;
        displayBoard(board);

        int direction;
        if (isIaRunning)
        {
            // Vérifiez si la touche 'a' est pressée pour arrêter l'IA
            if (kbhit() && getchar() == 'a')
            {
                isIaRunning = !isIaRunning;
                continue;
            }

            direction = findBestMove(board, score, 6, genome);
            if (direction == -1)
            {
                std::cout << "Game over!" << std::endl;
                break;
            }
        }
        else
        {
            direction = takeInput();
            if (direction == 4)
            {
                isIaRunning = !isIaRunning;
                continue;
            }
            if (direction == 5)
            {
                return 1;
            }
        }

        if (direction == -1)
        {
            clearConsole();
            std::cout << "Invalid command" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        else
        {
            slide(board, direction, score, true);
        }

        if (isGameOver(board))
        {
            std::cout << "Game over!" << std::endl;
            break;
        }
    }
    return 0;
}

int run_GA()
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
    return 0;
}

int run_OPT(){
    //"Please select a option to modif"
}

int main(int argc, char const *argv[])
{
    int DISPLAY_MODE;
    int running = 1;
    while(running)
    {
        std::cout << "Please select a Game Mode: CLI (1), GUI (2), GA (3), OPT (4), EXIT (5): ";
        std::cin >> DISPLAY_MODE;

        if (DISPLAY_MODE == 1)
        {
            running = run_CLI();
        }
        else if (DISPLAY_MODE == 2)
        {
            running = run_GUI();
        }
        else if (DISPLAY_MODE == 3)
        {
            running = run_GA();
        } else if (DISPLAY_MODE == 4)
        {
            run_OPT();
        } else if (DISPLAY_MODE == 5)
        {
            running = 0;
        }
    }

    return 0;
}
