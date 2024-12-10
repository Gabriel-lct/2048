#include "./include/GUI.h"
#include "./include/Utils.h"
#include "./include/Game.h"

#include <cmath>
#include <string>
#include <iostream>
#include <time.h>
#include <vector>

Board test_board = {{0, 0, 2, 0}, {4, 0, 16, 8}, {0, 0, 2, 0}, {4, 0, 16, 8}};
int W;
int H;

void SetRenderDrawColorFromHex(SDL_Renderer *renderer, Uint32 hexColor)
{
    Uint8 r = (hexColor >> 24) & 0xFF;
    Uint8 g = (hexColor >> 16) & 0xFF;
    Uint8 b = (hexColor >> 8) & 0xFF;
    Uint8 a = hexColor & 0xFF;
    // Set the color in the renderer
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void initSDL(SDL_Window *&window, SDL_Renderer *&renderer, TTF_Font *&font, int width, int height)
{
    W = width;
    H = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("./fonts/ClearSans/ClearSans-Bold.ttf", W);
    if (!font)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    }
}

SDL_Texture *getTextTexture(const std::string &text, TTF_Font *&font, SDL_Color color, SDL_Renderer *&renderer)
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface)
    {
        SDL_Log("TTF_RenderText_Blended Error: %s", TTF_GetError());
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        SDL_Log("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
    }
    SDL_FreeSurface(textSurface);
    return textTexture;
}

void renderBoard(Board &board, SDL_Renderer *&renderer, TTF_Font *&font, SDL_Window *&window)
{

    SDL_GetWindowSize(window, &W, &H);
    /*int newDimension = std::min(W, H);
    SDL_SetWindowSize(window, newDimension, newDimension);
    W = H = newDimension;*/

    // Background
    SetRenderDrawColorFromHex(renderer, 0x9C8B7CFF);
    SDL_Rect rect = {0, 0, W, H};
    SDL_RenderFillRect(renderer, &rect);
    int size = board.size();
    int tileSize = std::min(W, H) / (size + 1);
    int separation = tileSize / (size + 1);
    int wmargin = (W - size * tileSize - (size + 1) * separation) / 2;
    int hmargin = (H - size * tileSize - (size + 1) * separation) / 2;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (int)board[i].size(); j++)
        {
            // Tile color
            int tileValue = board[i][j];
            auto [r, g, b] = getTileColor(tileValue);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);

            SDL_Rect tile = {wmargin + separation * (j + 1) + tileSize * j, hmargin + separation * (i + 1) + tileSize * i, tileSize, tileSize};
            SDL_RenderFillRect(renderer, &tile);

            // Tile text
            if (tileValue == 0)
            {
                continue;
            }
            SDL_Color black = {0, 0, 0, 255};
            SDL_Texture *textTexture = getTextTexture(std::to_string(tileValue), font, black, renderer);
            int textWidth, textHeight;
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
            int maxDim = std::max(textHeight, textWidth);
            textWidth = (textWidth * tileSize) / (2 * maxDim);
            textHeight = (textHeight * tileSize) / (2 * maxDim);
            SDL_Rect destRect = {wmargin + separation * (j + 1) + tileSize * j - (textWidth - tileSize) / 2, hmargin + separation * (i + 1) + tileSize * i - (textHeight - tileSize) / 2, textWidth, textHeight};

            SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

            SDL_DestroyTexture(textTexture);
        }
    }
}

void renderScore(int score, SDL_Renderer *&renderer, TTF_Font *&font)
{
    SDL_Color black = {0, 0, 0, 255};
    SDL_Texture *textTexture = getTextTexture(std::to_string(score), font, black, renderer);
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    int maxDim = std::max(textHeight, textWidth);
    textWidth = (textWidth * W / 10) / (2 * maxDim);
    textHeight = (textHeight * H / 10) / (2 * maxDim);
    SDL_Rect destRect = {0, 0, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

    SDL_DestroyTexture(textTexture);
}

int handleEvents(bool &running, Board board)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_DOWN:
            case SDL_SCANCODE_S:
                return 2;
                break;
            case SDL_SCANCODE_UP:
            case SDL_SCANCODE_W:
                return 0;
                break;
            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_A:
                return 1;
                break;
            case SDL_SCANCODE_RIGHT:
            case SDL_SCANCODE_D:
                return 3;
                break;
            case SDL_SCANCODE_Q:
                return 4;
                break;
            case SDL_SCANCODE_R:
                return 5;
                break;
            case SDL_SCANCODE_ESCAPE:
                return 6;
                break;
            default:
                break;
            }
        }
    }
    return -1;
}

void terminateGUI(SDL_Window *&window, SDL_Renderer *&renderer, TTF_Font *&font)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}