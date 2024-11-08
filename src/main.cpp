#include "../include/Display.h"
#include "../include/Utils.h"

#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int n = 4;                                         // Define the size of the n*n array
    vector<vector<int>> tableau(n, vector<int>(n, 0)); // Initialize n*n array with zeros

    // Fill the array with some values (example values)
    int value = 1;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tableau[i][j] = value++;
        }
    }
    displayBoard(tableau);

    return 0;
}
