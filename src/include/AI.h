#ifndef AI_H
#define AI_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using Vect = std::vector<int>;
using VectDouble = std::vector<double>;
using Board = std::vector<std::vector<int>>;
using BoardVect = std::vector<Board>;

int numberEmptyTiles(Board &board);

BoardVect generatePossibleSpawns(Board &board);

bool boardExists(const BoardVect &boardVect, const Board &board);

std::pair<double, int> minimax(Board board, int oldScore, int score, const VectDouble &genome, int depth, double alpha, double beta, bool isMaximizingPlayer);

int findBestMove(Board &board, int &score, const int &depth, const VectDouble &genome);
double evaluateBoard(Board &board, int &oldScore, int &score /*, const VectDouble &genome */);

/* dir:
- true = -->
- false = <--
 */

void check_serpentinage(Board &board, const int &rowIndex, const bool &dir, Vect &boardValues, int &inRow);

#endif