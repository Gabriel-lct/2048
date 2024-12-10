#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <ncurses.h>

using Board = std::vector<std::vector<int>>;
using std::vector;

void initializeColors();

void displayBoard(Board &board);

std::tuple<int, int, int> getTileColor(int value);

#endif