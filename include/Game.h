#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>

using Plateau = std::vector<std::vector<int>>;

const std::map<char, int> WASD = {{'w', 0}, {'s', 1}, {'a', 2}, {'d', 3}};
const std::map<char, int> ZQSD = {{'z', 0}, {'s', 1}, {'q', 2}, {'d', 3}};
const std::map<char, int> FR = {{'h', 0}, {'b', 1}, {'g', 2}, {'d', 3}};
const std::map<char, int> EN = {{'u', 0}, {'d', 1}, {'l', 2}, {'r', 3}};

Plateau genPlateau(int N, int M);

int takeInput();

void moveRight(Plateau &p);
void fuseRight(Plateau &p);

void moveLeft(Plateau &p);
void fuseLeft(Plateau &p);

void moveUp(Plateau &p);
void fuseUp(Plateau &p);

void moveDown(Plateau &p);
void fuseDown(Plateau &p);

void spawn(Plateau &p);

void slide(Plateau &p, int dir);

#endif