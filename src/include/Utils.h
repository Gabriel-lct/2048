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

/**
 * @brief Counts the number of digits in an integer.
 * 
 * @param n The integer to count digits of.
 * @return The number of digits.
 * @author Gabriel Lancelot
 */
int countDigits(int n);

/**
 * @brief Finds the biggest tile on the board.
 * 
 * @param board The game board.
 * @return A vector containing the biggest tile.
 * @author Gabriel Lancelot
 */
Vect biggestTile(Board &board);

/**
 * @brief Gets the color of a tile based on its value.
 * 
 * @param value The value of the tile.
 * @return A tuple containing the RGB color values.
 * @author Gabriel Lancelot
 */
std::tuple<int, int, int> getTileColor(int value);

/**
 * @brief Clears the console screen.
 * @author Luca Bozzi Menéndez
 */
void clearConsole();

/**
 * @brief Transposes the given matrix.
 * 
 * @param matrix The matrix to transpose.
 * @author Luca Bozzi Menéndez
 */
void transposeMatrix(Board &matrix);

/**
 * @brief Reverses the rows of the given matrix.
 * 
 * @param matrix The matrix whose rows are to be reversed.
 * @author Luca Bozzi Menéndez
 */
void reverseRows(Board &matrix);

/**
 * @brief Rotates the given matrix by 90 degrees t times.
 * 
 * @param m The matrix to rotate.
 * @param t The number of 90-degree rotations.
 * @author Luca Bozzi Menéndez
 */
void rotateMatrix(Board &m, int t);

/**
 * @brief Gets the values of the matrix as a vector.
 * 
 * @param board The game board.
 * @return A vector containing the values of the matrix.
 * @author Luca Bozzi Menéndez
 */
Vect getMatrixValues(Board &board);

/**
 * @brief Calculates the maximum score gain from the given values.
 * 
 * @param values The values to calculate the score gain from.
 * @return The maximum score gain.
 * @author Luca Bozzi Menéndez
 */
int maxScoreGain(const Vect &values);

/**
 * @brief Gets the number of tiles on the board.
 * 
 * @param board The game board.
 * @return The number of tiles.
 * @author Gabriel Lancelot
 */
int getNumberTiles(Board &board);

/**
 * @brief Counts the number of empty tiles on the board.
 * 
 * @param board The game board.
 * @return The number of empty tiles.
 * @author Gabriel Lancelot
 */
int numberEmptyTiles(Board &board);

/**
 * @brief Calculates the average of the given vector of doubles.
 * 
 * @param vect The vector of doubles.
 * @return The average value.
 * @author Gabriel Lancelot
 */
double vectorAverage(VectDouble &vect);

/**
 * @brief Checks if a keyboard key has been hit.
 * 
 * @return 1 if a key has been hit, 0 otherwise.
 * @author Gabriel Lancelot
 */
int kbhit(void);

#endif