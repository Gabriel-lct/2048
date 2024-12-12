#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <ncurses.h>

using Board = std::vector<std::vector<int>>;

struct GameState
{
    int score;
    int boardSize;
    int aiDepth;
    std::string keySetting;

    Board currentBoard;
};

/**
 * @brief Generates a new game board with given dimensions.
 * 
 * @param N The number of rows.
 * @param M The number of columns.
 * @return The generated game board.
 * @author Luca Bozzi Menéndez
 */
Board genBoard(int N, int M);

/**
 * @brief Initializes the game board for a new game.
 * 
 * @param gameState The current game state.
 * @author Gabriel Lancelot
 */
void initializeBoard(GameState &gameState);

/**
 * @brief Resets the game to its initial state.
 * 
 * @param gameState The current game state.
 * @author Gabriel Lancelot
 */
void resetGame(GameState &gameState);

/**
 * @brief Takes input from the user.
 * 
 * @return The input taken from the user.
 * 
 */
int takeInput();

/**
 * @brief Transforms the input into a game command.
 * 
 * @param keySetting The key setting used for input.
 * @param input The input to transform.
 * @return The transformed command.
 */
int transformInputToCommand(std::string &keySetting, int input);

/**
 * @brief Moves the tiles on the board.
 * 
 * @param p The game board.
 * @param c The current score.
 */
void move(Board &p, int &c);

/**
 * @brief Fuses the tiles on the board.
 * 
 * @param p The game board.
 * @param c The current score.
 * @param s The score gained from fusing.
 */
void fuse(Board &p, int &c, int &s);

/**
 * @brief Spawns a new tile on the board.
 * 
 * @param p The game board.
 * @param c The current score.
 */
void spawn(Board &p, int &c);

/**
 * @brief Slides the tiles on the board in a given direction.
 * 
 * @param p The game board.
 * @param dir The direction to slide.
 * @param s The score gained from sliding.
 * @param sp Whether to spawn a new tile after sliding.
 */
void slide(Board &p, int dir, int &s, bool sp);

/**
 * @brief Checks if the game is over.
 * 
 * @param board The game board.
 * @return True if the game is over, false otherwise.
 */
bool isGameOver(Board &board);

// u l d r
const std::map<char, int>
    WASD = {{'w', 0}, {'a', 1}, {'s', 2}, {'d', 3}, {'q', 4}};
const std::map<char, int> ZQSD = {{'z', 0}, {'q', 1}, {'s', 2}, {'d', 3}, {'a', 4}};

#endif