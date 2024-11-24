#include "./include/GUI.h"
#include "./include/Utils.h"

#include <cmath>
#include <string>
#include <iostream>
#include <time.h>
#include <vector>

Board test_board = {{0, 0, 2, 0}, {4, 0, 16, 8}, {0, 0, 2, 0}, {4, 0, 16, 8}};
GUI::GUI() {};

GUI::~GUI() {};

void GUI::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
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

    isRunning = true;
}

void GUI::handleEvents()
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

void GUI::update() {
};

void GUI::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void GUI::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "GUI cleaned" << std::endl;
}

bool GUI::running()
{
    return isRunning;
}