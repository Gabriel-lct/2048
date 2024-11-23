#ifndef IA_H
#define IA_H

#include <iostream>
#include <vector>
#include <limits>

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;
using BoardVect = std::vector<Board>;

int numberEmptyCells(Board &board);

BoardVect generatePossibleSpawns(Board &board);

bool boardExists(const BoardVect &boardVect, const Board &board);

std::pair<double, int> minimax(Board board, int score, int depth, double alpha, double beta, bool isMaximizingPlayer);

int findBestMove(Board &board, int &score, const int &depth);

double evaluateBoard(Board &board, int &score);

#endif