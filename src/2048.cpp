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
#include <ncurses.h>

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
            dir = findBestMove(gameState.currentBoard, gameState.score, gameState.aiDepth, genome);
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
    clear();
    bool isIaRunning = false;

    while (true)
    {
        clear();
        printw("SCORE: %d\n", gameState.score);
        displayBoard(gameState.currentBoard);
        refresh();

        int command;
        if (isIaRunning)
        {
            // Check if 'a' is pressed to stop the AI
            if (kbhit() && getchar() == 'a')
            {
                isIaRunning = !isIaRunning;
                continue;
            }

            command = findBestMove(gameState.currentBoard, gameState.score, gameState.aiDepth, genome);
            if (command == -1)
            {
                printw("\nGame over!\n");
                refresh();
                resetGame(gameState);
                napms(2500);
                break;
            }
        }
        else
        {
            int input = takeInput();
            command = transformInputToCommand(gameState.keySetting, input);
            if (command == 4)
            {
                isIaRunning = !isIaRunning;
                continue;
            }
            else if (command == 5)
            {
                printw("\nAre you sure you want to reset your game? [y/n]  ");
                refresh();
                echo();
                char c = getch();
                noecho();
                if (c == 'y')
                {
                    resetGame(gameState);
                    clear();
                    printw("Game has been reset.\n");
                    refresh();
                    napms(1000);
                }
                continue;
            }
            else if (command == 6)
            {
                return 1;
            }
        }

        if (command == -1)
        {
            printw("Invalid command\n");
            refresh();
            napms(300);
        }
        else
        {
            slide(gameState.currentBoard, command, gameState.score, true);
        }

        if (isGameOver(gameState.currentBoard))
        {
            printw("\nGame over!\n");
            resetGame(gameState);
            refresh();
            napms(1000);
            return 1;
        }
    }
    return 0;
}

int run_GA()
{
    clear();
    printw("Running Genetic Algorithm\n");
    refresh();
    VectDouble genome = {1.05984, 0.159454, 0.115378, 0.636072, 2.69887}; //{1.51422, 0.173924, 1.4986, 1.04476, 0.243911};
    int populationSize = 50;
    int maxGamesPerGenome = 10;
    int maxGenerations = 20;
    double mutationRate = 0.1;
    double mutationStrength = 0.1;

    BoardDouble firstPopulation = initializePopulationFromGenome(genome, populationSize, mutationRate);

    runGeneticAlgorithm(firstPopulation, maxGamesPerGenome, maxGenerations, mutationRate, mutationStrength);
    return 1;
}

int run_OPT(GameState &gameState)
{
    clear();
    printw("Please select an option to modify:\n");
    printw("    1. Board size (%dx%d)\n", gameState.boardSize, gameState.boardSize);
    printw("    2. Keyboard setting (%s)\n", gameState.keySetting.c_str());
    printw("    3. Ai minimax algorithm depth (%d)\n", gameState.aiDepth);
    printw("    4. Return\n\n");
    refresh();

    int option;
    option = takeInput();

    if (option == 49)
    {
        clear();
        echo();
        printw("Please enter the new board size: ");
        refresh();
        int N;
        scanw("%d", &N);
        noecho();
        if (N < 1 || N > 21)
        {
            clear();
            printw("Board size must be between 2 and 20.\n");
            refresh();
            napms(1000);

            return run_OPT(gameState);
        }
        gameState.boardSize = N;
        printw("Board size updated to %dx%d\n", N, N);
        refresh();
        napms(1000);

        return run_OPT(gameState);
    }
    else if (option == 50)
    {
        clear();
        printw("Please select a keyboard setting:\n");
        printw("  1. ZQSD\n");
        printw("  2. WASD\n");
        printw("  3. Return\n\n");
        refresh();
        int keySetting;
        keySetting = takeInput();

        if (keySetting == 49)
        {
            gameState.keySetting = "ZQSD";
            clear();
            printw("Keyboard setting updated to ZQSD\n");
            refresh();
            napms(1000);
        }
        else if (keySetting == 50)
        {
            gameState.keySetting = "WASD";
            clear();
            printw("Keyboard setting updated to WASD\n");
            refresh();
            napms(1000);
        }
        else if (keySetting == 51)
        {
            return run_OPT(gameState);
        }
        else
        {
            printw("Invalid option\n");
            refresh();
            napms(300);
        }
        return run_OPT(gameState);
    }
    else if (option == 51)
    {
        clear();
        echo();
        printw("Please enter the new AI depth: ");
        refresh();
        int d;
        scanw("%d", &d);
        noecho();
        if (d < 1 || d > 16)
        {
            clear();
            printw("Board size must be between 1 and 15.\n");
            refresh();
            napms(1000);

            return run_OPT(gameState);
        }
        gameState.aiDepth = d;
        printw("AI depth updated to %d.\n", d);
        refresh();
        napms(1000);

        return run_OPT(gameState);
    }
    else if (option == 52)
    {
        return 1;
    }
    else
    {
        printw("Invalid option\n");
        refresh();
        napms(300);
        return run_OPT(gameState);
    }
}

int main(int argc, char const *argv[])
{
    GameState gameState = {0, 4, 5, "ZQSD"};
    int DISPLAY_MODE;
    int running = 1;

    initscr();
    initializeColors();
    use_default_colors();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (running)
    {
        clearConsole();
        clear();
        initializeBoard(gameState);

        printw("Welcome to the 2048 Game.\n\n");

        printw("Current game: \n");
        printw("    - Score: %d\n", gameState.score);
        printw("    - Board :\n");
        displayBoard(gameState.currentBoard, 1);

        printw("\n");
        printw("Please select an option:\n");
        printw("  1. CLI (Client Line Interface)\n");
        printw("  2. GUI (Game User Interface)\n");
        printw("  3. GA (Genetic Algorithm)\n");
        printw("  4. OPTIONS\n");
        printw("  5. RESET\n");
        printw("  6. QUIT\n\n");
        refresh();

        DISPLAY_MODE = takeInput();

        if (DISPLAY_MODE == 49)
        {
            running = run_CLI(gameState);
        }
        else if (DISPLAY_MODE == 50)
        {
            running = run_GUI(gameState);
        }
        else if (DISPLAY_MODE == 51)
        {
            running = run_GA();
        }
        else if (DISPLAY_MODE == 52)
        {
            running = run_OPT(gameState);
        }
        else if (DISPLAY_MODE == 53)
        {
            resetGame(gameState);
            clear();
            printw("Game has been reseted.\n");
            refresh();
            napms(1000);
        }
        else if (DISPLAY_MODE == 54)
        {
            clear();
            running = 0;
        }
        else
        {
            printw("Invalid option\n");
            refresh();
            napms(300);
        }
    }
    endwin();
    return 0;
}
