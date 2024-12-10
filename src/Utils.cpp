#include "./include/Utils.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;

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

Vect biggestTile(Board &board)
{
    int biggest = board[0][0];
    int x = 0;
    int y = 0;
    for (Board::size_type i = 0; i < board.size(); i++)
    {
        for (Vect::size_type j = 0; j < board[i].size(); j++)
        {
            int tile = board[i][j];
            if (tile >= biggest)
            {
                biggest = tile;
                x = i;
                y = j;
            }
        }
    }
    return {x, y};
}

/**
 * @brief Returns the RGB color associated with a given tile value in the 2048 game.
 *
 * @param value The value of the tile.
 * @return A tuple containing the RGB color (red, green, blue) associated with the tile value.
 */
std::tuple<int, int, int> getTileColor(int value)
{
    // Couleurs associées aux valeurs des tileules
    std::map<int, std::tuple<int, int, int>> colorMap = {
        {0, {192, 192, 192}},
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

    if (colorMap.find(value) != colorMap.end())
    {
        return colorMap[value];
    }
    return {61, 58, 50};
}

void clearConsole()
{
    if (system("clear"))
    {
        system("cls");
    }
}

void transposeMatrix(Board &matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void reverseRows(Board &matrix)
{
    for (auto &row : matrix)
    {
        std::reverse(row.begin(), row.end());
    }
}

void rotateMatrix(Board &matrix, int t)
{
    int rotations = t % 4;
    for (int i = 0; i < rotations; ++i)
    {
        transposeMatrix(matrix);
        reverseRows(matrix);
    }
}

Vect getMatrixValues(Board &board)
{
    Vect values = Vect(pow(board.size(), 2));
    for (Board::size_type i = 0; i < board.size(); i++)
    {
        for (Vect::size_type j = 0; j < board[i].size(); j++)
        {
            values[i * board.size() + j] = board[i][j];
        }
    }
    std::sort(values.begin(), values.end());
    std::reverse(values.begin(), values.end());
    return values;
}

int maxScoreGain(const Vect &values)
{
    int s = 0;
    for (Vect::size_type i = 0; i < values.size() - 1; i++)
    {
        if (values[i] == values[i + 1])
        {
            s += 2 * values[i];
            i++;
        }
    }
    return s;
}

int getNumberTiles(Board &board)
{
    int columnSize = static_cast<int>(board.size());
    int rowSize = static_cast<int>(board[0].size());
    return columnSize * rowSize;
}

int numberEmptyTiles(Board &board)
{
    int numberEmptyTiles = 0;
    for (auto &row : board)
    {
        for (auto &tile : row)
        {
            if (tile == 0)
            {
                numberEmptyTiles++;
            }
        }
    }
    return numberEmptyTiles;
}

double vectorAverage(VectDouble &vect)
{
    double a = 0;
    for (auto c : vect)
    {
        a += c;
    }
    return a / vect.size();
}

// Function to check if a key has been pressed
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}