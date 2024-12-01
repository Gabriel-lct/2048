#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using Board = std::vector<std::vector<int>>;

Board genBoard(int N, int M);

int takeInput();

void move(Board &p, int &c);
void fuse(Board &p, int &c, int &s);

void spawn(Board &p, int &c);

void slide(Board &p, int dir, int &s, bool sp);

bool isGameOver(Board &board);

// u l d r
const std::map<char, int>
    WASD = {{'w', 0}, {'a', 1}, {'s', 2}, {'d', 3}};

const std::map<char, int> ZQSD = {{'z', 0}, {'q', 1}, {'s', 2}, {'d', 3}};
const std::map<char, int> FR = {{'h', 0}, {'d', 1}, {'b', 2}, {'g', 3}};
const std::map<char, int> EN = {{'u', 0}, {'l', 1}, {'d', 2}, {'r', 3}};

#endif