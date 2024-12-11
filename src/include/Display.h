#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <ncurses.h>

using Board = std::vector<std::vector<int>>;
using std::vector;

/**
 * @brief Initializes the color pairs for ncurses.
 */
void initializeColors();

/**
 * @brief Displays the game board on the console.
 * 
 * @param board The game board.
 * @param tab The tab spacing for the display.
 */
void displayBoard(Board &board, int tab = 0);

/**
 * @brief Gets the color of a tile based on its value.
 * 
 * @param value The value of the tile.
 * @return A tuple containing the RGB color values.
 */
std::tuple<int, int, int> getTileColor(int value);

#endif