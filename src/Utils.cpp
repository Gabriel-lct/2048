#include "./include/Utils.h"
#include <cmath>
#include <vector>
#include <map>

/**
 * @brief Compte le nombre de chiffres dans un entier donné.
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
    for (int i = 0; i < s / 2; i++)
    {
        int o = v[i];
        v[i] = v[s - i - 1];
        v[s - i - 1] = o;
    }
}

void rotateMatrix(vector<vector<int>> &matrix, int t)
{
    int n = matrix.size();
    for (int l = 0; l < t; l++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int o = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = o;
            }
        }
        for (int i = 0; i < n; ++i)
        {
            reverseVector(matrix[i]);
        }
    }
}

/**
 * @brief Returns the RGB color associated with a given cell value in the 2048 game.
 *
 * @param value The value of the cell.
 * @return A tuple containing the RGB color (red, green, blue) associated with the cell value.
 */
std::tuple<int, int, int> getCellColor(int value)
{
    // Couleurs associées aux valeurs des cellules
    std::map<int, std::tuple<int, int, int>> colorMap = {
        {2, {238, 228, 218}},   // Beige clair
        {4, {237, 224, 200}},   // Beige
        {8, {242, 177, 121}},   // Orange clair
        {16, {245, 149, 99}},   // Orange foncé
        {32, {246, 124, 95}},   // Rouge clair
        {64, {246, 94, 59}},    // Rouge
        {128, {237, 207, 114}}, // Jaune
        {256, {237, 204, 97}},  // Jaune doré
        {512, {237, 200, 80}},  // Jaune foncé
        {1024, {237, 197, 63}}, // Or
        {2048, {237, 194, 46}}  // Doré brillant
    };

    // Retourne la couleur correspondante ou un gris par défaut
    if (colorMap.find(value) != colorMap.end())
    {
        return colorMap[value];
    }
    return {0, 0, 0}; // noir pour les cellules vides
}