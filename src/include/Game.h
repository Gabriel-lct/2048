#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

using Board = std::vector<std::vector<int>>;

class Game
{
public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();

    Board initiadeGrid();
    void drawGrid(Board);

private:
    bool isRunning;
    TTF_Font *font;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

//u l d r
const std::map<char, int> WASD = {{'w', 0}, {'a', 1}, {'s', 2}, {'d', 3}};
const std::map<char, int> ZQSD = {{'z', 0}, {'q', 1}, {'s', 2}, {'d', 3}};
const std::map<char, int> FR = {{'h', 0}, {'d', 1}, {'b', 2}, {'g', 3}};
const std::map<char, int> EN = {{'u', 0}, {'l', 1}, {'d', 2}, {'r', 3}};

Board genBoard(int N, int M);

int takeInput();

void moveRight(Board &p);
void fuseRight(Board &p, int &c, int &s);

void moveLeft(Board &p);
void fuseLeft(Board &p, int &c, int &s);

void moveUp(Board &p);
void fuseUp(Board &p, int &c, int &s);

void moveDown(Board &p);
void fuseDown(Board &p, int &c, int &s);

void move(Board &p);
void fuse(Board &p, int &c, int &s);

void spawn(Board &p);

void slide(Board &p, int dir, int &s);

#endif