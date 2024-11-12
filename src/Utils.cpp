#include "./include/Utils.h"
#include <cmath>

/**
 * @brief Compte le nombre de chiffres dans un entier donné.
 *
 * Cette fonction prend un entier en entrée et retourne le nombre de chiffres
 * qu'il contient. Par exemple, pour l'entrée 1214, la fonction retournera 4.
 *
 * @param n L'entier dont on veut compter les chiffres.
 * @return Le nombre de chiffres dans l'entier donné.
 */
int countDigits(int n)
{
    return n == 0 ? 1 : static_cast<int>(log10(n) + 1);
}

/**
 * @brief Finds the largest element in a 2D vector.
 *
 * This function iterates through each element of a 2D vector (board) to find
 * and return the largest element.
 *
 * @param board The 2D vector containing integer elements.
 * @return int The largest element in the board.
 */

int biggestElement(vector<vector<int>> board)
{
    int biggest = board[0][0];
    for (const auto &line : board)
    {
        for (const auto &cell : line)
        {
            biggest = std::max(biggest, cell);
        }
    }
    return biggest;
}