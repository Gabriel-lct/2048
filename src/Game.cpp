#include "./include/Game.h"

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
void spawn(Plateau &plateau)
{
    int x, y, v;
    int N = plateau.size();
    int M = plateau[0].size();
    do
    {
        x = rand() % N;
        y = rand() % M;
    } while (plateau[x][y] != 0);
    v = ((rand() % 2) + 1) * 2;
    plateau[x][y] = v;
}

Plateau genPlateau(int N, int M)
{
    Plateau p(N, std::vector<int>(M, 0));

    spawn(p);
    spawn(p);

    return p;
}

int takeInput()
{
    std::string i;
    std::cout << "Entrer commande: ";
    std::cin >> i;
    std::cout << std::endl;
    if (i == "u")
    {
        return 0;
    }
    else if (i == "d")
    {
        return 1;
    }
    else if (i == "l")
    {
        return 2;
    }
    else if (i == "r")
    {
        return 3;
    }
    return -1;
}
// NxM
//  0: up, 1: down, 2: right, 3: left
void moveRight(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < N; y++)
    {
        for (int i = M - 2; i >= 0; i--)
        {
            for (int j = i; j < M - 1; j++)
            {
                if (plateau[y][j + 1] == 0)
                {
                    plateau[y][j + 1] = plateau[y][j];
                    plateau[y][j] = 0;
                }
            }
        }
    }
}
void fuseRight(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < N; y++)
    {
        for (int i = M - 1; i > 0; i--)
        {
            if (plateau[y][i - 1] == plateau[y][i])
            {
                plateau[y][i - 1] = 0;
                plateau[y][i] = 2 * plateau[y][i];
            }
        }
    }
}

void moveLeft(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < N; y++)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (plateau[y][j - 1] == 0)
                {
                    plateau[y][j - 1] = plateau[y][j];
                    plateau[y][j] = 0;
                }
            }
        }
    }
}
void fuseLeft(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < N; y++)
    {
        for (int i = 0; i < M - 1; i++)
        {
            if (plateau[y][i + 1] == plateau[y][i])
            {
                plateau[y][i + 1] = 0;
                plateau[y][i] = 2 * plateau[y][i];
            }
        }
    }
}

void moveUp(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < M; y++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (plateau[j - 1][y] == 0)
                {
                    plateau[j - 1][y] = plateau[j][y];
                    plateau[j][y] = 0;
                }
            }
        }
    }
}
void fuseUp(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < M; y++)
    {
        for (int i = 0; i < N - 1; i++)
        {
            if (plateau[i + 1][y] == plateau[i][y])
            {
                plateau[i + 1][y] = 0;
                plateau[i][y] = 2 * plateau[i][y];
            }
        }
    }
}

void moveDown(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < M; y++)
    {
        for (int i = N - 2; i >= 0; i--)
        {
            for (int j = i; j < N - 1; j++)
            {
                if (plateau[j + 1][y] == 0)
                {
                    plateau[j + 1][y] = plateau[j][y];
                    plateau[j][y] = 0;
                }
            }
        }
    }
}
void fuseDown(Plateau &plateau)
{
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y < M; y++)
    {
        for (int i = N - 1; i > 0; i--)
        {
            if (plateau[i - 1][y] == plateau[i][y])
            {
                plateau[i - 1][y] = 0;
                plateau[i][y] = 2 * plateau[i][y];
            }
        }
    }
}

void slide(Plateau &plateau, int dir)
{
    switch (dir)
    {
    case 0: // up
        moveUp(plateau);
        fuseUp(plateau);
        moveUp(plateau);
        break;

    case 1: // down
        moveDown(plateau);
        fuseDown(plateau);
        moveDown(plateau);
        break;
    case 2: // left
        moveLeft(plateau);
        fuseLeft(plateau);
        moveLeft(plateau);
        break;
    case 3: // right
        moveRight(plateau);
        fuseRight(plateau);
        moveRight(plateau);
        break;
    }
    spawn(plateau);
}
