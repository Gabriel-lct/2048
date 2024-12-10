#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;
using VectDouble = std::vector<double>;

int countDigits(int n);

Vect biggestTile(Board &board);

std::tuple<int, int, int> getTileColor(int value);

void clearConsole();

void transposeMatrix(Board &matrix);

void reverseRows(Board &matrix);

void rotateMatrix(Board &m, int t);

Vect getMatrixValues(Board &board);

int maxScoreGain(const Vect &values);

int getNumberTiles(Board &board);

int numberEmptyTiles(Board &board);

double vectorAverage(VectDouble &vect);

int kbhit(void);

#endif