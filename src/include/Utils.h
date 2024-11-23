#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <stdlib.h>

using Board = std::vector<std::vector<int>>;
using std::vector;

int countDigits(int n);

int biggestElement(vector<vector<int>>);

void clearConsole();

void reverseVector(vector<int> &v);

void rotateMatrix(vector<vector<int>> &m, int t);

std::tuple<int, int, int> getCellColor(int value);

#endif