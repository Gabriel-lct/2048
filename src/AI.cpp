#include "./include/AI.h"
#include "./include/Utils.h"
#include "./include/Game.h"
#include "./include/Display.h"

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

std::pair<double, int> minimax(Board board, int score, const VectDouble &genome, int depth, double alpha, double beta, bool isMaximizingPlayer)
{
    if (depth == 0 || isGameOver(board))
    {
        return {evaluateBoard(board, score, genome), -1};
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
            auto [eval, _] = minimax(dupliBoard, score, genome, depth - 1, alpha, beta, false);
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
            auto [eval, _] = minimax(childBoard, score, genome, depth - 1, alpha, beta, true);
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

int findBestMove(Board &board, int &score, const int &depth, const VectDouble &genome)
{
    auto [_, bestDir] = minimax(board, score, genome, depth, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), true);
    return bestDir;
}

double evaluateBoard(Board &board, int &score, const VectDouble &genome)
{
    double evaluation = 0.0;

    double w_max_tile = genome[0];
    double w_proximity = genome[1];
    double w_empty = genome[2];
    double w_score = genome[3];

    // Criteria n°1 - Max tile in corner
    int maxTile = biggestTile(board);

    if (board[0][0] == maxTile || board[0][board.size() - 1] == maxTile || board[board.size() - 1][0] == maxTile || board[board.size() - 1][board.size() - 1] == maxTile)
    {
        evaluation += w_max_tile * maxTile;
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
                    evaluation -= w_proximity * std::abs(board[i][j] - board[i - 1][j]);
                }
                if (j > 0 && board[i][j - 1] != 0)
                {
                    evaluation -= w_proximity * std::abs(board[i][j] - board[i][j - 1]);
                }
            }
        }
    }

    // Criteria n°3 : number of empty cells
    int emptyCells = numberEmptyCells(board);
    evaluation += w_empty * emptyCells;

    // Criteria n°4 : score
    evaluation += w_score * score;

    return evaluation;
}
