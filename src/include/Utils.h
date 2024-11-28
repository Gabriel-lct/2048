#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <stdlib.h>

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;
using VectDouble = std::vector<double>;

int countDigits(int n);

Vect biggestTile(Board &board);

void clearConsole();

void transposeMatrix(Board &matrix);

void reverseRows(Board &matrix);

void rotateMatrix(Board &m, int t);

Vect getMatrixValues(Board &board);

std::tuple<int, int, int> getTileColor(int value);

int maxScoreGain(const Vect &values);

int getNumberTiles(Board &board);

int numberEmptyTiles(Board &board);

double vectorAverage(VectDouble &vect);

#endif