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

/**
 * @brief Counts the number of empty tiles on the board.
 * 
 * @param board The game board.
 * @return The number of empty tiles.
 */
int numberEmptyTiles(Board &board);

/**
 * @brief Generates all possible board states after a spawn.
 * 
 * @param board The current game board.
 * @return A vector of possible board states.
 */
BoardVect generatePossibleSpawns(Board &board);

/**
 * @brief Checks if a board state exists in a vector of board states.
 * 
 * @param boardVect The vector of board states.
 * @param board The board state to check.
 * @return True if the board state exists, false otherwise.
 */
bool boardExists(const BoardVect &boardVect, const Board &board);

/**
 * @brief Performs the minimax algorithm to find the best move.
 * 
 * @param board The current game board.
 * @param oldScore The previous score.
 * @param score The current score.
 * @param genome The genome used for evaluation.
 * @param depth The depth of the search.
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param isMaximizingPlayer True if the current player is maximizing, false otherwise.
 * @return A pair containing the best score and the best move.
 */
std::pair<double, int> minimax(Board board, int oldScore, int score, const VectDouble &genome, int depth, double alpha, double beta, bool isMaximizingPlayer);

/**
 * @brief Finds the best move for the current board state.
 * 
 * @param board The current game board.
 * @param score The current score.
 * @param depth The depth of the search.
 * @param genome The genome used for evaluation.
 * @return The best move.
 */
int findBestMove(Board &board, int &score, const int &depth, const VectDouble &genome);

/**
 * @brief Evaluates the current board state.
 * 
 * @param board The current game board.
 * @param oldScore The previous score.
 * @param score The current score.
 * @param genome The genome used for evaluation.
 * @return The evaluation score of the board.
 */
double evaluateBoard(Board &board, int &oldScore, int &score, const VectDouble &genome);

/**
 * @brief Checks the serpentinage pattern on the board.
 * 
 * @param board The current game board.
 * @param rowIndex The index of the row to check.
 * @param dir The direction of the check (true for right, false for left).
 * @param boardValues The values of the board.
 * @param inRow The number of tiles in a row.
 */
void check_serpentinage(Board &board, const int &rowIndex, const bool &dir, Vect &boardValues, int &inRow);

#endif