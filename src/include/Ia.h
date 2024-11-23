#ifndef IA_H
#define IA_H

#include <iostream>
#include <vector>

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;
using BoardVect = std::vector<Board>;

void mainIA(Board board);

int numberEmptyCells(Board board);

BoardVect generateSpawnPossibilities(Board board);

void displayAllPossibilities(BoardVect boardVect);

bool boardExists(const BoardVect &boardVect, const Board &board);

void decisionTree(Board board, int depthLevel);

double evaluateBoard(const Board &board);

#endif