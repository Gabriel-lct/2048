#include "../include/Display.h"
#include "../include/Game.h"

#include <iostream>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int N = 4;
    int M = 4;
    int dir;

    Plateau plateau = genPlateau(N, M);

    while (true){
        //Clears console
        if (system("clear")){
            system("cls");
        }
        displayBoard(plateau);
        dir = takeInput();
        if (dir == -1){
            std::cout << "Commande invalide" << std::endl;
        } else{
            slide(plateau, dir);
        }
    }

    return 0;
}
