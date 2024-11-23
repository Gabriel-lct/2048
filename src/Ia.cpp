#include "./include/Ia.h"
#include "./include/Utils.h"
#include "./include/Game.h"
#include "./include/Display.h"

// Only for dev use
void mainIA(Board board)
{
    decisionTree(board, 2);
}

void displayAllPossibilities(BoardVect boardVect)
{
    for (BoardVect::size_type i = 0; i < boardVect.size(); i++)
    {
        displayBoard(boardVect[i]);
        std::cout << "" << std::endl;
    }
    std::cout << "number of possibilities rendered : " << boardVect.size() << std::endl;
}

/**
 * @brief Counts the number of empty cells in the given board.
 *
 * @param board The game board represented as a 2D array.
 * @return int The number of empty cells in the board.
 */

int numberEmptyCells(Board board)
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
BoardVect generateSpawnPossibilities(Board board)
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

void decisionTree(Board board, int depthLevel)
{
    BoardVect tree = {board};

    // iterate depthLevel time the process
    for (int i = 0; i < depthLevel; i++)
    {
        BoardVect newTree;
        // do the process for each Board of the tree
        for (Board &board : tree)
        {
            for (int dir = 0; dir < 4; dir++)
            {
                int S = 100;
                int c = 0;
                Board dupliBoard = board;
                slide(dupliBoard, dir, S, c);

                BoardVect possibilities = generateSpawnPossibilities(dupliBoard);
                for (Board &board : possibilities)
                {
                    if (!boardExists(newTree, board))
                    {
                        newTree.push_back(board);
                    }
                }
            }
        }
        tree = newTree;
    }
    std::cout << "tree size: " << tree.size() << std::endl;
}

double evaluateBoard(Board &board)
{
    double score = 0.0;

    // Criteria n°1 - Max tile in corner
    int maxTile = biggestTile(board);

    if (board[0][0] == maxTile || board[0][board.size() - 1] == maxTile || board[board.size() - 1][0] == maxTile || board[board.size() - 1][board.size() - 1] == maxTile)
    {
        score += 1.5 * maxTile;
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
                    score -= std::abs(board[i][j] - board[i - 1][j]);
                }
                if (j > 0 && board[i][j - 1] != 0)
                {
                    score -= std::abs(board[i][j] - board[i][j - 1]);
                }
            }
        }
    }

    return score;
}