#ifndef AI_H
#define AI_H

#include <iostream>
#include <vector>
#include <limits>

using Vect = std::vector<int>;
using VectDouble = std::vector<double>;
using Board = std::vector<std::vector<int>>;
using BoardVect = std::vector<Board>;

int numberEmptyCells(Board &board);

BoardVect generatePossibleSpawns(Board &board);

bool boardExists(const BoardVect &boardVect, const Board &board);

std::pair<double, int> minimax(Board board, int score, VectDouble &genome, int depth, double alpha, double beta, bool isMaximizingPlayer);

int findBestMove(Board &board, int &score, const int &depth, VectDouble &genome);

double evaluateBoard(Board &board, int &score, VectDouble &genome);

#endif