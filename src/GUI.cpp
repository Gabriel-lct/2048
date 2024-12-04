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
    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
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

void renderBoard(Board &board, SDL_Renderer *&renderer, TTF_Font *&font)
{
    // Background
    SetRenderDrawColorFromHex(renderer, 0x9C8B7CFF);
    SDL_Rect rect = {0, 0, W, H};
    SDL_RenderFillRect(renderer, &rect);
    int size = board.size();
    int tileSize = W / (size + 1);
    int separation = tileSize / (size + 1);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (int)board[i].size(); j++)
        {
            // Tile color
            int tileValue = board[i][j];
            auto [r, g, b] = getTileColor(tileValue);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);

            SDL_Rect tile = {separation * (j + 1) + tileSize * j, separation * (i + 1) + tileSize * i, tileSize, tileSize};
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
            SDL_Rect destRect = {separation * (j + 1) + tileSize * j - (textWidth - tileSize) / 2, separation * (i + 1) + tileSize * i - (textHeight - tileSize) / 2, textWidth, textHeight};

            SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

            SDL_DestroyTexture(textTexture);
        }
    }
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
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
            {
                return 2;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_UP)
            {
                return 0;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
            {
                return 1;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
            {
                return 3;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_Q) // ia master
            {
                return 4;
            }
            break;
        }
    }
    return -1;
}