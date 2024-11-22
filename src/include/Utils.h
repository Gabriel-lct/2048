#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <stdlib.h>
using std::vector;

int countDigits(int n);

int biggestElement(vector<vector<int>>);

void clearConsole();

void reverseVector(vector<int> &v);

void rotateMatrix(vector<vector<int>>& m, int t);

#endif