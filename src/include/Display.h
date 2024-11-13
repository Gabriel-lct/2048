#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
using std::vector;

using Board = std::vector<std::vector<int>>;

void displayBoard(Board);

class Display
{
public:
    void drawGrid();
};

#endif