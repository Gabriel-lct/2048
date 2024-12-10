#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <ncurses.h>

using Board = std::vector<std::vector<int>>;

struct GameState
{
    int score;
    int boardSize;
    std::string keySetting;

    Board currentBoard;
};

Board genBoard(int N, int M);

void initializeBoard(GameState &gameState);

void resetGame(GameState &gameState);

int takeInput();

int transformInputToCommand(std::string &keySetting, int input);

void move(Board &p, int &c);
void fuse(Board &p, int &c, int &s);

void spawn(Board &p, int &c);

void slide(Board &p, int dir, int &s, bool sp);

bool isGameOver(Board &board);

// u l d r
const std::map<char, int>
    WASD = {{'w', 0}, {'a', 1}, {'s', 2}, {'d', 3}, {'q', 4}};
const std::map<char, int> ZQSD = {{'z', 0}, {'q', 1}, {'s', 2}, {'d', 3}, {'a', 4}};

#endif