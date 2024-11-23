#include "./include/Display.h"
#include "./include/Utils.h"
#include <iostream>

// Previous code.
/**
 * @brief Creates a line of asterisks with specified number of cells and cell spacing.
 *
 * @param numberOfCells The number of cells to be included in the line. Each cell
 *                      is separated by a single asterisk. Default is 4.
 * @param cellSpace The number of asterisks in each cell. Default is 5.
 * @return std::string The generated line of asterisks.
 */

std::string createLine(int numberOfCells, int cellSpace)
{

    std::string line = "*";
    for (int i = 0; i < numberOfCells; i++)
    {
        line += std::string(cellSpace + 1, '*');
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
    int numberOfCells = board[0].size();
    int cellSpace = std::max(countDigits(biggestElement(board)), 5);

    std::cout << createLine(numberOfCells, cellSpace) << std::endl;
    for (const auto &line : board)
    {
        std::cout << "*";
        for (const auto &cell : line)
        {
            int numberOfDigits = countDigits(cell);
            int spaces = cellSpace - numberOfDigits;
            if (cell != 0)
            {
                auto [r, g, b] = getCellColor(cell);
                std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m"
                          << "\033[30m"
                          << std::string(spaces / 2, ' ') << cell << std::string((spaces + 1) / 2, ' ')
                          << "\033[0m" << "*";
            }
            else
            {
                std::cout << std::string(spaces / 2, ' ') << cell << std::string((spaces + 1) / 2, ' ') << "*";
            }
        }
        std::cout << std::endl;
        std::cout << createLine(numberOfCells, cellSpace) << std::endl;
    }
}
