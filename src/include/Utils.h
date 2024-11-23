#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <stdlib.h>

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;

int countDigits(int n);

int biggestTile(Board &board);

void clearConsole();

void reverseVector(Vect &v);

void rotateMatrix(Board &m, int t);

std::tuple<int, int, int> getCellColor(int value);

#endif