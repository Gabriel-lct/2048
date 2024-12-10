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

int run_GUI(GameState &gameState)
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

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

        renderBoard(gameState.currentBoard, renderer, font, window);
        renderScore(gameState.score, renderer, font);
        SDL_RenderPresent(renderer);
        int dir = handleEvents(running, gameState.currentBoard);

        if (dir == 4)
        {
            iaRunning = !iaRunning;
        }
        else if (dir == 5)
        {
            resetGame(gameState);
            continue;
        }
        else if (dir == 6)
        {
            terminateGUI(window, renderer, font);
            return 1;
        }
        if (iaRunning)
        {
            dir = findBestMove(gameState.currentBoard, gameState.score, 6, genome);
        }

        slide(gameState.currentBoard, dir, gameState.score, true);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay)
        {
            SDL_Delay(frameDelay - frameTime);
        } // TODO - Check if board is dead.
    }

    // Clean up SDL resources
    terminateGUI(window, renderer, font);
    return 0;
}

int run_CLI(GameState &gameState)
{
    clearConsole();

    bool isIaRunning = false;

    while (true)
    {
        clearConsole();
        std::cout << "SCORE: " << gameState.score << std::endl;
        displayBoard(gameState.currentBoard);

        int direction;
        if (isIaRunning)
        {
            // Vérifiez si la touche 'a' est pressée pour arrêter l'IA
            if (kbhit() && getchar() == 'a')
            {
                isIaRunning = !isIaRunning;
                continue;
            }

            direction = findBestMove(gameState.currentBoard, gameState.score, 6, genome);
            if (direction == -1)
            {
                std::cout << "Game over!" << std::endl;
                break;
            }
        }
        else
        {
            direction = takeInput(gameState.keySetting);
            if (direction == 4)
            {
                isIaRunning = !isIaRunning;
                continue;
            }
            else if (direction == 5)
            {
                std::cout << std::endl;
                std::cout << "Are you sure you want to reset your game? [y/n]  ";
                char c;
                std::cin >> c;
                if (c == 'y')
                {
                    resetGame(gameState);
                    clearConsole();
                    std::cout << "Game has been reseted." << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                continue;
            }
            else if (direction == 6)
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
            slide(gameState.currentBoard, direction, gameState.score, true);
        }

        if (isGameOver(gameState.currentBoard)) // FIXME - When the game is over, the game is not really over (for most of the cases).
        {
            std::cout << std::endl;
            std::cout << "Game over!" << std::endl;
            resetGame(gameState);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return 1;
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

int run_OPT(GameState &gameState)
{
    clearConsole();

    std::cout << "Please select an option to modify: " << std::endl;
    std::cout << "  1. Board size" << std::endl;
    std::cout << "  2. Keyboard setting" << std::endl;
    std::cout << "  3. Return" << std::endl
              << std::endl;

    int option;
    std::cout << "Your option: ";
    std::cin >> option;

    if (option == 1)
    {
        clearConsole();
        std::cout << "Please enter the new board size : ";
        int N;
        std::cin >> N;
        if (N < 1 || N > 21)
        {
            clearConsole();
            std::cout << "Board size must be between 2 and 20." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            return run_OPT(gameState);
        }
        gameState.boardSize = N;
        std::cout << "Board size updated to " << N << "x" << N << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        return run_OPT(gameState);
    }
    else if (option == 2)
    {
        clearConsole();
        std::cout << "Please select a keyboard setting:" << std::endl;
        std::cout << "  1. ZQSD" << std::endl;
        std::cout << "  2. WASD" << std::endl;
        std::cout << "  3. Return" << std::endl
                  << std::endl;

        std::cout << "Your option: ";
        int keySetting;
        std::cin >> keySetting;

        if (keySetting == 1)
        {
            gameState.keySetting = "ZQSD";
            clearConsole();
            std::cout << "Keyboard setting updated to ZQSD" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else if (keySetting == 2)
        {
            gameState.keySetting = "WASD";
            clearConsole();
            std::cout << "Keyboard setting updated to WASD" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else if (keySetting == 3)
        {
            return run_OPT(gameState);
        }
        else
        {
            clearConsole();
            std::cout << "Invalid option" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        return run_OPT(gameState);
    }
    else if (option == 3)
    {
        return 1;
    }
    else
    {
        clearConsole();
        std::cout << "Invalid option" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return run_OPT(gameState);
    }
}

int main(int argc, char const *argv[])
{
    GameState gameState = {0, 4, "ZQSD"};
    int DISPLAY_MODE;
    int running = 1;
    while (running)
    {
        clearConsole();
        initializeBoard(gameState);

        std::cout << "Welcome to the 2048 Game." << std::endl
                  << std::endl;
        std::cout << "Current board size: " << gameState.boardSize << "x" << gameState.boardSize << std::endl;
        std::cout << "Current key setting: " << gameState.keySetting << std::endl;
        std::cout << "Current score: " << gameState.score << std::endl
                  << std::endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "  1. CLI (Client L... Interface)" << std::endl;
        std::cout << "  2. GUI (Game User Interface)" << std::endl;
        std::cout << "  3. GA (Genetic Algorithm)" << std::endl;
        std::cout << "  4. OPTIONS" << std::endl;
        std::cout << "  5. RESET" << std::endl;
        std::cout << "  6. QUIT" << std::endl
                  << std::endl;

        std::cout << "Your choice: ";
        std::cin >> DISPLAY_MODE;

        if (DISPLAY_MODE == 1)
        {
            running = run_CLI(gameState);
        }
        else if (DISPLAY_MODE == 2)
        {
            running = run_GUI(gameState);
        }
        else if (DISPLAY_MODE == 3)
        {
            running = run_GA();
        }

        else if (DISPLAY_MODE == 4)
        {
            running = run_OPT(gameState);
        }
        else if (DISPLAY_MODE == 5)
        {
            resetGame(gameState);
            clearConsole();
            std::cout << "Game has been reseted." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else if (DISPLAY_MODE == 6)
        {
            clearConsole();
            running = 0;
        }
        else
        {
            clearConsole();
            std::cout << "Invalid option" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    return 0;
}
