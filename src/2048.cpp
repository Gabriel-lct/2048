#include "../include/Display.h"
#include "../include/Game.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    int N = 4;
    int M = 4;

    Plateau plateau = genPlateau(N, M);

    while (true){
        displayBoard(plateau);
        int dir = takeInput();
        if (dir == -1){
            std::cout << "Commande invalide" << std::endl;
        } else{
            slide(plateau, dir);
        }
    }

    return 0;
}
