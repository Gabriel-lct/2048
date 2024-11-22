#include "./include/Game.h"
#include "./include/Utils.h"

#include <cmath>
#include <string>
#include <iostream>
#include <time.h>

Board test_board = {{0, 0, 2, 0}, {4, 0, 16, 8}, {0, 0, 2, 0}, {4, 0, 16, 8}};
Game::Game() {};

Game::~Game() {};

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    isRunning = false;
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return;
    }

    std::cout << "Subsystems Initialised" << std::endl;

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (!window)
    {
        std::cout << "Failed to create the window!" << std::endl;
        return;
    }

    std::cout << "Window created" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
    {
        std::cout << "Failed to create the renderer!" << std::endl;
        return;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    std::cout << "Renderer created" << std::endl;

    // Initialize SDL_ttf library
    if (TTF_Init() == -1)
    {
        std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return;
    }

    // Load the font and set the font size
    font = TTF_OpenFont("./fonts/ClearSans/ClearSans-Medium.ttf", 24);
    if (font == nullptr)
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    isRunning = true;
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:

    default:
        break;
    }
}

void Game::update() {
};

void Game::render()
{
    SDL_RenderClear(renderer);
    drawGrid(test_board);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

bool Game::running()
{
    return isRunning;
}

void Game::drawGrid(Board board)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

    int gridSize = 400;
    int gridX = (screenWidth - gridSize) / 2;
    int gridY = (screenHeight - gridSize) / 2;

    SDL_Rect gridRect = {gridX, gridY, gridSize, gridSize};
    SDL_RenderFillRect(renderer, &gridRect);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            SDL_Rect tileRect = {gridX + col * 100 + 10, gridY + row * 100 + 10, 90, 90};
            SDL_SetRenderDrawColor(renderer, 100, 200, 200, 255);
            SDL_RenderFillRect(renderer, &tileRect);

            int tileValue = board[row][col];

            if (tileValue != 0)
            {
                std::string text = std::to_string(tileValue);

                SDL_Color textColor = {0, 0, 0, 255};
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

                if (textSurface)
                {
                    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    SDL_FreeSurface(textSurface);

                    if (textTexture)
                    {
                        int textWidth, textHeight;
                        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
                        SDL_Rect textRect = {
                            tileRect.x + (tileRect.w - textWidth) / 2,
                            tileRect.y + (tileRect.h - textHeight) / 2,
                            textWidth,
                            textHeight};

                        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                        SDL_DestroyTexture(textTexture);
                    }
                }
            }
        }
    }
}

/* Game Luca */
std::map<char, int> MODE = WASD;

/**
 * @brief Spawns a new tile on the board.
 *
 * This function sets a random tile on the board
 * to a random integer, either 2 (90%) or 4 (10%)
 *
 * @param board The 2D vector containing integer elements.
 */

void spawn(Board &board)
{
    int x, y, v;
    int N = board.size();
    int M = board[0].size();
    do
    {
        x = rand() % N;
        y = rand() % M;
    } while (board[x][y] != 0);
    int prob = rand() % 10;
    if (prob < 9)
    {
        v = 2;
    }
    else
    {
        v = 4;
    }
    board[x][y] = v;
}

/**
 * @brief Generates a new board.
 *
 * This function generates a new NxM board, empty except
 * for two tiles, filled with either 2 or 4.
 *
 * @param N The number of rows.
 * @param M The number of columns.
 * @return Board The generated board.
 */

Board genBoard(int N, int M)
{
    srand(time(NULL));
    Board p(N, std::vector<int>(M, 0));

    spawn(p);
    spawn(p);

    return p;
}

/**
 * @brief Takes input from the player.
 *
 * This function takes a command from the player and assings an integer value,
 * this
 *
 * @param board The 2D vector containing integer elements.
 * @return int The largest element in the board.
 */

int takeInput()
{
    char i;
    std::cout << "Entrer commande: ";
    std::cin >> i;
    std::cout << std::endl;
    int dir;
    try
    {
        dir = MODE.at(i);
    }
    catch (const std::exception &e)
    {
        return -1;
    }

    return dir;
}

void move(Board &board, int &c)
{
    int N = board.size();
    int M = board[0].size();
    for (int y = 0; y < M; y++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (board[j][y]==0){continue;}
                if (board[j - 1][y] == 0)
                {
                    board[j - 1][y] = board[j][y];
                    board[j][y] = 0;
                    c++;
                }
            }
        }
    }
}
void fuse(Board &board, int &c, int &s)
{
    int N = board.size();
    int M = board[0].size();
    int f;
    for (int y = 0; y < M; y++)
    {
        for (int i = 0; i < N - 1; i++)
        {
            f = board[i][y];
            if (f==0){continue;}
            if (board[i + 1][y] == f)
            {
                board[i + 1][y] = 0;
                board[i][y] = 2 * f;
                c++;
                s = s + 2*f;
            }
        }
    }
}
//0: up, 1: left, 2: down, 3: right
void slide(Board &board, int dir, int &s)
{
    int c = 0;
    rotateMatrix(board, dir);
    move(board, c);
    fuse(board, c, s);
    move(board, c);
    rotateMatrix(board, (4-dir)%4);
    if (c){
        spawn(board);
    }
}