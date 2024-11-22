#include "./include/Utils.h"
#include <cmath>
#include <vector>

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

void clearConsole()
{
    if (system("clear"))
    {
        system("cls");
    }
}


void reverseVector(vector<int> &v)
{
    int s = v.size();
    for (int i=0; i<s/2; i++)
    {
        int o = v[i];
        v[i] = v[s-i-1];
        v[s-i-1] = o;
    }
}

void rotateMatrix(vector<vector<int>>& matrix, int t) {
    int n = matrix.size();
    for (int l=0; l<t; l++){
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int o = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = o;
            }
        }
        for (int i = 0; i < n; ++i) {
            reverseVector(matrix[i]);
        }
    
    }
}