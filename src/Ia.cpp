#include "./include/Ia.h"
#include "./include/Utils.h"
#include "./include/Game.h"
#include "./include/Display.h"

/**
 * @brief Counts the number of empty cells in the given board.
 *
 * @param board The game board represented as a 2D array.
 * @return int The number of empty cells in the board.
 */

int numberEmptyCells(Board &board)
{
    int numberEmptyCells;
    for (auto &row : board)
    {
        for (auto &cell : row)
        {
            if (cell == 0)
            {
                numberEmptyCells++;
            }
        }
    }
    return numberEmptyCells;
}

/**
 * @brief Generates all possible board configurations by spawning a 2 or 4 in each empty cell.
 *
 * @param board The current board configuration.
 * @return A vector of board configurations with all possible spawns of 2 and 4 in empty cells.
 */
BoardVect generatePossibleSpawns(Board &board)
{
    BoardVect possibilities;

    for (Board::size_type i = 0; i < board.size(); i++)
    {
        for (Board::size_type j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                Board newBoard = board;
                newBoard[i][j] = 2;
                possibilities.push_back(newBoard);

                newBoard[i][j] = 4;
                possibilities.push_back(newBoard);
            }
        }
    }
    return possibilities;
}

/**
 * @brief Checks if a given board exists in a vector of boards.
 *
 * @param boardVect A vector of boards to search through.
 * @param board The board to check for existence in the vector.
 * @return true If the board exists in the vector.
 * @return false If the board does not exist in the vector.
 */
bool boardExists(const BoardVect &boardVect, const Board &board)
{
    for (const auto &existingBoard : boardVect)
    {
        if (existingBoard == board)
        {
            return true;
        }
    }
    return false;
}

std::pair<double, int> minimax(Board board, int score, int depth, double alpha, double beta, bool isMaximizingPlayer)
{
    if (depth == 0 || isGameOver(board))
    {
        return {evaluateBoard(board, score), -1};
    }

    if (isMaximizingPlayer)
    {
        double maxEval = -std::numeric_limits<double>::infinity();
        int bestDir = -1;
        for (int dir = 0; dir < 4; dir++)
        {
            int c = 0;
            Board dupliBoard = board;
            slide(dupliBoard, dir, score, c);
            if (dupliBoard == board)
            {
                continue;
            }
            auto [eval, _] = minimax(dupliBoard, score, depth - 1, alpha, beta, false);
            if (eval > maxEval)
            {
                maxEval = eval;
                bestDir = dir;
            }
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return {maxEval, bestDir};
    }
    else
    {
        double minEval = std::numeric_limits<double>::infinity();
        for (Board &childBoard : generatePossibleSpawns(board))
        {
            auto [eval, _] = minimax(childBoard, score, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return {minEval, -1};
    }
}

int findBestMove(Board &board, int &score, const int &depth)
{
    auto [_, bestDir] = minimax(board, score, depth, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), true);
    return bestDir;
}

double evaluateBoard(Board &board, int &score)
{
    double evaluation = 0.0;

    // Criteria n°1 - Max tile in corner
    int maxTile = biggestTile(board);

    if (board[0][0] == maxTile || board[0][board.size() - 1] == maxTile || board[board.size() - 1][0] == maxTile || board[board.size() - 1][board.size() - 1] == maxTile)
    {
        evaluation += 10 * maxTile;
    }

    // Criteria n°2 : power of 2 proximity
    for (Board::size_type i = 0; i < board.size(); ++i)
    {
        for (Vect::size_type j = 0; j < board[i].size(); ++j)
        {
            if (board[i][j] != 0)
            {
                if (i > 0 && board[i - 1][j] != 0)
                {
                    evaluation -= 2 * std::abs(board[i][j] - board[i - 1][j]);
                }
                if (j > 0 && board[i][j - 1] != 0)
                {
                    evaluation -= 2 * std::abs(board[i][j] - board[i][j - 1]);
                }
            }
        }
    }

    evaluation += 1.5 * score;

    return evaluation;
}