#include "Utils.h"
#include "GUI.h"
#include "Game.h"
#include "GA.h"
#include "Display.h"
#include "AI.h"
#include <cassert>

void testUtils()
{
    // Test countDigits
    assert(countDigits(12345) == 5);
    assert(countDigits(0) == 1);

    // Test biggestTile
    Board board = {{2, 4, 8}, {16, 32, 64}, {128, 256, 512}};
    Vect biggest = biggestTile(board);
    assert(biggest[0] == 512);

    // Test getTileColor
    auto color = getTileColor(2);
    assert(std::get<0>(color) == 238);

    // Test clearConsole (no assertion, just call)
    clearConsole();

    // Test transposeMatrix
    Board matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    transposeMatrix(matrix);
    assert(matrix[0][1] == 4);

    // Test reverseRows
    reverseRows(matrix);
    assert(matrix[0][0] == 3);

    // Test rotateMatrix
    rotateMatrix(matrix, 1);
    assert(matrix[0][0] == 7);

    // Test getMatrixValues
    Vect values = getMatrixValues(matrix);
    assert(values[0] == 7);

    // Test maxScoreGain
    assert(maxScoreGain(values) == 9);

    // Test getNumberTiles
    assert(getNumberTiles(board) == 9);

    // Test numberEmptyTiles
    Board emptyBoard = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    assert(numberEmptyTiles(emptyBoard) == 9);

    // Test vectorAverage
    VectDouble vect = {1.0, 2.0, 3.0};
    assert(vectorAverage(vect) == 2.0);

    // Test kbhit (no assertion, just call)
    kbhit();
}

int main()
{
    testUtils();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
