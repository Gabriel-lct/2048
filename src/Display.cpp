#include "./include/Display.h"
#include "./include/Utils.h"
#include <iostream>

// Previous code.
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

    std::string line = "*";
    for (int i = 0; i < numberOfTiles; i++)
    {
        line += std::string(tileSpace + 1, '*');
    }
    return line;
}

/**
 * @brief Displays the 2048 game board in a formatted manner.
 *
 * @param board A 2D vector of integers representing the game board.
 */

void displayBoard(vector<vector<int>> board)
{
    int numberOfTiles = board[0].size();
    Vect biggestTileIndex = biggestTile(board);
    int tileSpace = std::max(countDigits(board[biggestTileIndex[0]][biggestTileIndex[1]]), 5);

    std::cout << createLine(numberOfTiles, tileSpace) << std::endl;
    for (const auto &line : board)
    {
        std::cout << "*";
        for (const auto &tile : line)
        {
            int numberOfDigits = countDigits(tile);
            int spaces = tileSpace - numberOfDigits;
            if (tile != 0)
            {
                auto [r, g, b] = getTileColor(tile);
                std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m"
                          << "\033[30m"
                          << std::string(spaces / 2, ' ') << tile << std::string((spaces + 1) / 2, ' ')
                          << "\033[0m" << "*";
            }
            else
            {
                std::cout << std::string(spaces / 2, ' ') << tile << std::string((spaces + 1) / 2, ' ') << "*";
            }
        }
        std::cout << std::endl;
        std::cout << createLine(numberOfTiles, tileSpace) << std::endl;
    }
}
