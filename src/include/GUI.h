#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <vector>

using Board = std::vector<std::vector<int>>;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, TTF_Font* &font, int width, int height);

void renderBoard(Board &board, SDL_Renderer* &renderer, TTF_Font* &font);

int handleEvents(bool &running, Board board);

#endif