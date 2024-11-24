#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
using Board = std::vector<std::vector<int>>;

using std::vector;

void displayBoard(Board);

class Display
{
public:
    void drawGrid();
};

#endif