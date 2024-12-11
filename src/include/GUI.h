#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <vector>

using Board = std::vector<std::vector<int>>;

/**
 * @brief Initializes the SDL library, creates a window and a renderer, and loads a font.
 * 
 * @param window Reference to the SDL_Window pointer that will be initialized.
 * @param renderer Reference to the SDL_Renderer pointer that will be initialized.
 * @param font Reference to the TTF_Font pointer that will be loaded.
 * @param width The width of the window to be created.
 * @param height The height of the window to be created.
 */
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, TTF_Font* &font, int width, int height);

/**
 * @brief Renders the game board on the screen.
 * 
 * This function takes the current state of the game board and renders it
 * using the provided SDL renderer, font, and window.
 * 
 * @param board Reference to the game board object to be rendered.
 * @param renderer Reference to the SDL_Renderer used for rendering the board.
 * @param font Pointer to the TTF_Font used for rendering text on the board.
 * @param window Pointer to the SDL_Window where the board will be displayed.
 */
void renderBoard(Board &board, SDL_Renderer* &renderer, TTF_Font* &font, SDL_Window* &window);

/**
 * @brief Renders the current score on the screen.
 * 
 * This function takes the current score and renders it using the provided
 * SDL_Renderer and TTF_Font. It is used to display the score in the game.
 * 
 * @param score The current score to be rendered.
 * @param renderer A reference to the SDL_Renderer used for rendering.
 * @param font A reference to the TTF_Font used for rendering the text.
 */
void renderScore(int score, SDL_Renderer* &renderer, TTF_Font *&font);

/**
 * @brief Renders the "Game Over" screen.
 * 
 * This function renders the "Game Over" screen using the provided SDL_Renderer and TTF_Font.
 * 
 * @param renderer A reference to the SDL_Renderer used for rendering.
 * @param font A reference to the TTF_Font used for rendering text.
 */
void renderGameOver(SDL_Renderer *&renderer, TTF_Font *&font);

/**
 * @brief Handles the events for the game.
 * 
 * This function processes user inputs and updates the game state accordingly.
 * It modifies the running state of the game based on the events.
 * 
 * @param running A reference to a boolean that indicates whether the game is running.
 * @param board The current state of the game board.
 * @return An integer representing the status after handling events.
 */
int handleEvents(bool &running, Board board);

/**
 * @brief Terminates the GUI by destroying the SDL window, renderer, and font.
 * 
 * This function cleans up the resources used by the GUI, including the SDL window,
 * renderer, and font. It ensures that all allocated resources are properly released
 * to avoid memory leaks.
 * 
 * @param window Reference to the pointer of the SDL_Window to be destroyed.
 * @param renderer Reference to the pointer of the SDL_Renderer to be destroyed.
 * @param font Reference to the pointer of the TTF_Font to be closed.
 */
void terminateGUI(SDL_Window* &window, SDL_Renderer* &renderer, TTF_Font* &font);

#endif