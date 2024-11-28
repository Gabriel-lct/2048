#include "./include/AI.h"
#include "./include/Utils.h"
#include "./include/Game.h"
#include "./include/Display.h"

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

std::pair<double, int> minimax(Board board, int oldScore, int score, const VectDouble &genome, int depth, double alpha, double beta, bool isMaximizingPlayer)
{
    if (depth == 0 || isGameOver(board))
    {
        return {evaluateBoard(board, oldScore, score/*, genome */), -1};
    }

    if (isMaximizingPlayer)
    {
        double maxEval = -std::numeric_limits<double>::infinity();
        int bestDir = -1;
        for (int dir = 0; dir < 4; dir++)
        {
            int c = 0;
            Board dupliBoard = board;
            int newScore = score;
            slide(dupliBoard, dir, newScore, c);
            if (dupliBoard == board)
            {
                continue;
            }
            auto [eval, _] = minimax(dupliBoard, score, newScore, genome, depth - 1, alpha, beta, false);
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
            auto [eval, _] = minimax(childBoard, oldScore, score, genome, depth - 1, alpha, beta, true);
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
    int empties = numberEmptyTiles(board);
    int ndepth = depth;
    if (empties > pow(board.size(), 2)/4)
    {
        ndepth = depth/2;
    }
    auto [_, bestDir] = minimax(board, score, score, genome, ndepth, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), true);
    return bestDir;
}

void check_serpentinage(Board &board, const int &rowIndex, const bool &dir, Vect &boardValues, int &inRow)
{
    Vect row = board[rowIndex];
    bool strike = true;
    if (not dir)
    {
        std::reverse(row.begin(), row.end());
    }

    for (Vect::size_type i = 0; i < row.size(); i++)
    {
        if (row[i] == boardValues[0])
        {
            inRow += 1;
            boardValues.erase(boardValues.begin());
        }
        else
        {
            strike = false;
            break;
        }
    }
    if (strike && rowIndex < static_cast<int>(board.size()) - 1)
    {
        check_serpentinage(board, rowIndex + 1, not dir, boardValues, inRow);
    }
}

double evaluateBoard(Board &board, int &oldScore, int &score /*, const VectDouble &genome */)
{
    double evaluation = 0.0;

    double w_corner = 1;
    double w_proximity = 1;
    double w_serpentinage = 1;
    /* double w_empty = 1;
    double w_score = 1; */

    int numberTiles = getNumberTiles(board);

        if (isGameOver(board))
    {
        return -std::numeric_limits<double>::max();
    }

    //ANCHOR - Criteria n°1 - Max tile in corner a.k.a PG au coin
    Vect biggestIndex = biggestTile(board);
    Vect::size_type maxX = biggestIndex[0];
    Vect::size_type maxY = biggestIndex[1];

    bool inCorner = false;

    if ((maxX == 0 && (maxY == 0 || maxY == board[maxX].size() - 1)) || (maxX == board.size() - 1 && (maxY == 0 || maxY == board[maxX].size() - 1))){
        inCorner = true;
        evaluation += w_corner;
    }
    
    //ANCHOR - Criteria N°2 - Serpentinage
    if (score < 10000) {
        for (Board::size_type i = 0; i < board.size(); ++i)
        {
            for (Vect::size_type j = 0; j < board[i].size(); ++j)
            {
                if (board[i][j] != 0)
                {
                    if (i > 0 && board[i - 1][j] != 0)
                    {
                        evaluation -= w_proximity * std::abs(board[i][j] - board[i - 1][j]); //TODO - Normaliser ici
                    }
                    if (j > 0 && board[i][j - 1] != 0)
                    {
                        evaluation -= w_proximity * std::abs(board[i][j] - board[i][j - 1]);
                    }
                }
            }
        }
    } else {
        if(inCorner) {
            Board boardCopy = board;
            if (maxX == boardCopy.size() - 1 && maxY == 0)
            {
                rotateMatrix(boardCopy, 1);
            }
            else if (maxX == boardCopy.size() - 1 && maxY == boardCopy.size() - 1)
            {
                rotateMatrix(boardCopy, 2);
            }
            else if (maxX == 0 && maxY == boardCopy.size() - 1)
            {
                rotateMatrix(boardCopy, 3);
            }

            if (boardCopy[1][0] > boardCopy[0][1])
            {
                transposeMatrix(boardCopy);
            }

            Vect boardValues = getMatrixValues(boardCopy);
            int inRow = 0;
            check_serpentinage(boardCopy, 0, true, boardValues, inRow);

            score += w_serpentinage * inRow / numberTiles;
        }
    }


    // Criteria n°3 : number of empty tiles
    score += numberEmptyTiles(board) / numberTiles;

    // Criteria n°4 : score
    score += (score - oldScore) / maxScoreGain(getMatrixValues(board));

    return evaluation;
}


