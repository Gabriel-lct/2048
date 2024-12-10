#include "./include/Display.h"
#include "./include/Utils.h"
#include <iostream>
#include <ncurses.h> // Ensure ncurses is included
#include <tuple>
#include <map>

/**
 * @brief Creates a line of asterisks with specified number of tiles and tile spacing.
 *
 * @param numberOfTiles The number of tiles to be included in the line. Each tile
 *                      is separated by a single asterisk. Default is 4.
 * @param tileSpace The number of asterisks in each tile. Default is 5.
 * @return std::string The generated line of asterisks.
 */

std::string createLine(int numberOfTiles, int tileSpace)
{
    // Using ncurses to create a line
    std::string line = "*";
    for (int i = 0; i < numberOfTiles; i++)
    {
        line += std::string(tileSpace + 1, '*');
    }
    return line;
}

void initializeColors()
{
    start_color();
    if (!can_change_color() || COLORS < 16)
    {
        throw std::runtime_error("Your terminal does not support changing colors.");
    }

    // Define the custom colors (scale RGB values from 0-255 to 0-1000)
    std::map<int, std::tuple<int, int, int>> colorMap = {
        {0, {192, 192, 192}},
        {2, {238, 228, 218}},
        {4, {237, 224, 200}},
        {8, {242, 177, 121}},
        {16, {245, 149, 99}},
        {32, {246, 124, 95}},
        {64, {246, 94, 59}},
        {128, {237, 207, 114}},
        {256, {237, 204, 97}},
        {512, {237, 200, 80}},
        {1024, {237, 197, 63}},
        {2048, {237, 194, 46}}};

    int pairIndex = 1;
    for (const auto &[value, rgb] : colorMap)
    {
        int r = std::get<0>(rgb) * 1000 / 255;
        int g = std::get<1>(rgb) * 1000 / 255;
        int b = std::get<2>(rgb) * 1000 / 255;

        init_color(pairIndex, r, g, b);
        if (value == 0)
        {
            init_pair(pairIndex, COLOR_WHITE, pairIndex);
        }
        else
        {
            init_pair(pairIndex, COLOR_BLACK, pairIndex);
        }
        ++pairIndex;
    }
}
/**
 * @brief Displays the 2048 game board in a formatted manner.
 *
 * @param board A 2D vector of integers representing the game board.
 */

void displayBoard(Board &board)
{
    int numberOfTiles = board[0].size();
    Vect biggestTileIndex = biggestTile(board);
    int tileSpace = std::max(countDigits(board[biggestTileIndex[0]][biggestTileIndex[1]]), 5);

    printw("%s\n", createLine(numberOfTiles, tileSpace).c_str());
    for (const auto &line : board)
    {
        printw("*");
        for (const auto &tile : line)
        {
            int numberOfDigits = countDigits(tile);
            int spaces = tileSpace - numberOfDigits;
            int power = 0;
            while ((1 << power) < std::min(tile, 4096))
            {
                ++power;
            }
            int color_pair = power + 1;
            attron(COLOR_PAIR(color_pair));
            printw("%s", std::string(spaces / 2, ' ').c_str());
            if (tile != 0)
            {
                printw("%d", tile);
            }
            else
            {
                printw(" ");
            }
            printw("%s", std::string(spaces - spaces / 2, ' ').c_str());
            attroff(COLOR_PAIR(color_pair));
            printw("*");
        }
        printw("\n");
        printw("%s\n", createLine(numberOfTiles, tileSpace).c_str());
    }

    refresh(); // Refresh the screen to show changes
}