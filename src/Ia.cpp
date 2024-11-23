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
    for (Board::size_type i = 0; i < board.size(); i++)
    {
        for (Board::size_type j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                numberEmptyCells++;
            }
        }
    }
    return numberEmptyCells;
}

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
        for (BoardVect::size_type j = 0; j < tree.size(); j++)
        {
            Board board = tree[j];

            for (int dir = 0; dir < 4; dir++)
            {
                int S = 100;
                int c = 0;
                Board dupliBoard = board;
                slide(dupliBoard, dir, S, c);

                BoardVect possibilities = generateSpawnPossibilities(dupliBoard);
                for (BoardVect::size_type i = 0; i < possibilities.size(); i++)
                {
                    if (!boardExists(newTree, possibilities[i]))
                    {
                        newTree.push_back(possibilities[i]);
                    }
                }
            }
        }
        tree = newTree;
    }
    std::cout << "tree size: " << tree.size() << std::endl;
}