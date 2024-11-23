#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>

using Board = std::vector<std::vector<int>>;

class GUI
{
public:
    GUI();
    ~GUI();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif