#include <iostream>
#include "minmax.h"
#include "gamestate.h"

int main(){
    GameState game(X,O);
    MinMax minmax(O);
    game.printTitle();
    game.printInstructions();
    game.printBoard();

    while(!game.gameOver()){
        Board board = game.getBoard();

        if(!game.isIAPlayerTurn()){
            int jugada;
            std::cout << "Seleccione su jugada: ";
            std::cin >> jugada;

            if(jugada == 1){
                int pos;
                std::cout << "Ingrese casilla en la que poner: ";
                std::cin >> pos;
                if(!game.play((pos-1)/3, (pos-1)%3)){
                    std::cout << "Jugada invalida, intenta de nuevo.\n";
                }else{
                    game.printBoard();
                }
            }else if(jugada == 2){
                int pos, nuevaPos;
                std::cout << "Que ficha quiere mover: ";
                std::cin >> pos;
                std::cout << "A donde la quiere mover: ";
                std::cin >> nuevaPos;
                if(!game.move((pos-1)/3, (pos-1)%3, (nuevaPos-1)/3, (nuevaPos-1)%3)){
                    std::cout << "Movimiento invalido, intenta de nuevo.\n";
                }else{
                    game.printBoard();
                }
            }else{
                std::cout << "Muchas gracias por jugar!\n";
                break;
            }

        }else{
            Board mejorJugada = minmax.minmaxAlgorithm(board);
            game.setBoard(mejorJugada);
            game.nextTurn();
            game.printBoard();
        }
    }

    game.printWinner();
    return 0;
}
