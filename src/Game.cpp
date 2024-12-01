#include "./include/Game.h"
#include "./include/Utils.h"

#include <cmath>
#include <string>
#include <iostream>
#include <time.h>

std::map<char, int> MODE = WASD;

/**
 * @brief Spawns a new tile on the board.
 *
 * This function sets a random tile on the board
 * to a random integer, either 2 (90%) or 4 (10%)
 *
 * @param board The 2D vector containing integer elements.
 * @param c A condition to check before spawning a new tile. If c is 0, the function returns immediately without spawning a tile.
 */

void spawn(Board &board, int &c)
{
    if (!c)
    {
        return;
    }

    int x, y, v;
    int N = board.size();
    int M = board[0].size();
    do
    {
        x = rand() % N;
        y = rand() % M;
    } while (board[x][y] != 0);
    int prob = rand() % 10;
    if (prob < 9)
    {
        v = 2;
    }
    else
    {
        v = 4;
    }
    board[x][y] = v;
}

/**
 * @brief Generates a new board.
 *
 * This function generates a new NxM board, empty except
 * for two tiles, filled with either 2 or 4.
 *
 * @param N The number of rows.
 * @param M The number of columns.
 * @return Board The generated board.
 */

Board genBoard(int N, int M)
{
    srand(time(NULL));
    Board p(N, std::vector<int>(M, 0));
    int c = 1;

    spawn(p, c);
    spawn(p, c);

    return p;
}

/**
 * @brief Takes input from the player.
 *
 * This function takes a command from the player and assings an integer value,
 * this
 *
 * @param board The 2D vector containing integer elements.
 * @return int The largest element in the board.
 */

int takeInput()
{
    std::string i;
    std::cout << "Entrer commande: ";
    std::cin >> i;
    std::cout << std::endl;
    int dir;
    try
    {
        dir = MODE.at(i[0]);
    }
    catch (const std::exception &e)
    {
        return -1;
    }

    return dir;
}

bool isGameOver(Board &board)
{
    for (Board::size_type i=0; i<board.size(); i++)
    {
        for (Vect::size_type j=0; j<board[i].size(); j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
            if (i > 0 && board[i][j] == board[i-1][j])
            {
                return false;
            }
            if (j > 0 && board[i][j] == board[i][j-1])
            {
                return false;
            }
        }
    }
    return true;
}

void move(Board &board, int &c)
{
    int N = board.size();
    int M = board[0].size();
    for (int y = 0; y < M; y++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (board[j][y] == 0)
                {
                    continue;
                }
                if (board[j - 1][y] == 0)
                {
                    board[j - 1][y] = board[j][y];
                    board[j][y] = 0;
                    c++;
                }
            }
        }
    }
}
void fuse(Board &board, int &c, int &s)
{
    int N = board.size();
    int M = board[0].size();
    int f;
    for (int y = 0; y < M; y++)
    {
        for (int i = 0; i < N - 1; i++)
        {
            f = board[i][y];
            if (f == 0)
            {
                continue;
            }
            if (board[i + 1][y] == f)
            {
                board[i + 1][y] = 0;
                board[i][y] = 2 * f;
                c++;
                s = s + 2 * f;
            }
        }
    }
}
// 0: up, 1: left, 2: down, 3: right
void slide(Board &board, int dir, int &s, bool sp)
{
    if (dir == -1)
    {
        return;
    }
    int c = 0;
    rotateMatrix(board, dir);
    move(board, c);
    fuse(board, c, s);
    move(board, c);
    rotateMatrix(board, (4 - dir) % 4);
    if (sp){spawn(board, c);}
}