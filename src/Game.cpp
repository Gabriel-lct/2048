#include "../include/Game.h"

#include <cmath>
#include <string>
#include <iostream>

std::map<char, int> MODE = EN;

/**
 * @brief Spawns a new tile on the board.
 *
 * This function sets a random tile on the board
 * to a random integer, either 2 (90%) or 4 (10%)
 * 
 * @param plateau The 2D vector containing integer elements.
 */

void spawn(Plateau &plateau){
    int x, y, v;
    int N = plateau.size();
    int M = plateau[0].size();
    do{
        x = rand() % N;
        y = rand() % M;
    }while (plateau[x][y] != 0);
    int prob = rand() % 10;
    if (prob < 9){
        v = 2;
    } else{
        v = 4;
    }
    plateau[x][y] = v;
}

/**
 * @brief Generates a new board.
 *
 * This function generates a new NxM board, empty except 
 * for two tiles, filled with either 2 or 4.
 *
 * @param N The number of rows.
 * @param M The number of columns.
 * @return Plateau The generated board.
 */

Plateau genPlateau(int N, int M){
    Plateau p(N, std::vector<int>(M, 0));

    spawn(p);
    spawn(p);    

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

int takeInput(){
    char i;
    std::cout << "Entrer commande: ";
    std::cin >> i;
    std::cout << std::endl;
    int dir;
    try
    {
        dir = MODE.at(i);
    }
    catch(const std::exception& e)
    {
        return -1;
    }
    
    return dir;
}
//NxM
// 0: up, 1: down, 2: right, 3: left
void moveRight(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y=0; y<N; y++){
        for (int i = M-2; i>=0; i--){
            for (int j = i; j < M-1; j++){
                if (plateau[y][j+1] == 0){
                    plateau[y][j+1] = plateau[y][j];
                    plateau[y][j] = 0;
                }
            }
        }
    }
}
void fuseRight(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y<N; y++){
        for (int i = M-1; i>0; i--){
            if (plateau[y][i-1] == plateau[y][i]){
                plateau[y][i-1] = 0;
                plateau[y][i] = 2*plateau[y][i];
            }
        }
    }
}

void moveLeft(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y=0; y<N; y++){
        for (int i = 0; i<M; i++){
            for (int j = i; j > 0; j--){
                if (plateau[y][j-1] == 0){
                    plateau[y][j-1] = plateau[y][j];
                    plateau[y][j] = 0;
                }
            }
        }
    }
}
void fuseLeft(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y<N; y++){
        for (int i = 0; i<M-1; i++){
            if (plateau[y][i+1] == plateau[y][i]){
                plateau[y][i+1] = 0;
                plateau[y][i] = 2*plateau[y][i];
            }
        }
    }
}

void moveUp(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y=0; y<M; y++){
        for (int i = 0; i<N; i++){
            for (int j = i; j > 0; j--){
                if (plateau[j-1][y] == 0){
                    plateau[j-1][y] = plateau[j][y];
                    plateau[j][y] = 0;
                }
            }
        }
    }
}
void fuseUp(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y<M; y++){
        for (int i = 0; i<N-1; i++){
            if (plateau[i+1][y] == plateau[i][y]){
                plateau[i+1][y] = 0;
                plateau[i][y] = 2*plateau[i][y];
            }
        }
    }
}

void moveDown(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y=0; y<M; y++){
        for (int i = N-2; i>=0; i--){
            for (int j = i; j < N-1; j++){
                if (plateau[j+1][y] == 0){
                    plateau[j+1][y] = plateau[j][y];
                    plateau[j][y] = 0;
                }
            }
        }
    }
}
void fuseDown(Plateau &plateau){
    int N = plateau.size();
    int M = plateau[0].size();
    for (int y = 0; y<M; y++){
        for (int i = N-1; i>0; i--){
            if (plateau[i-1][y] == plateau[i][y]){
                plateau[i-1][y] = 0;
                plateau[i][y] = 2*plateau[i][y];
            }
        }
    }
}

void slide(Plateau &plateau, int dir){
    switch (dir)
    {
    case 0://up
        moveUp(plateau);
        fuseUp(plateau);
        moveUp(plateau);
        break;
    
    case 1://down
        moveDown(plateau);
        fuseDown(plateau);
        moveDown(plateau);
        break;
    case 2://left
        moveLeft(plateau);
        fuseLeft(plateau);
        moveLeft(plateau);
        break;
    case 3://right
        moveRight(plateau);
        fuseRight(plateau);
        moveRight(plateau);
        break;
    }
    spawn(plateau);
}
