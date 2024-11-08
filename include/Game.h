#ifndef GAME_H
#define GAME_H

#include <vector>

using Plateau = std::vector<std::vector<int>>;

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