#include <iostream>
#include "minmax.h"
#include "gamestate.h"

int main() {
	int IABegins;

	std::cout << "Ingrese quien quiere comenzar: 0 para IA - 1 para Usuario: ";
	std::cin >> IABegins;

	Marks iaPlayer;
	if (IABegins == 0) {
		iaPlayer = X;
	} else {
		iaPlayer = O;
	}
	GameState game(X, iaPlayer);
	MinMax minmax(iaPlayer);

	game.printTitle();
	std::cout << std::endl;
	game.printInstructions();
	game.printBoard();

	while(!game.gameOver()) {
		Board board = game.getBoard();

		if(!game.isIAPlayerTurn()) {
			int jugada;
			std::cout << "Seleccione su jugada: ";
			if(!(std::cin >> jugada)) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Entrada invalida, intenta de nuevo.\n";
				continue;
			}

			if(jugada == 1) {
				if(!game.canPlaceMore()) {
					std::cout << "Ya pusiste todas tus fichas, solo puedes mover.\n";
					continue;
				}
				int pos;
				std::cout << "Ingrese casilla en la que poner: ";
				std::cin >> pos;
				if(!game.play((pos-1)/3, (pos-1)%3)) {
					std::cout << "Jugada invalida, intenta de nuevo.\n";
				} else {
					game.printBoard();
				}
			} else if(jugada == 2) {
				int pos, nuevaPos;
				std::cout << "Que ficha quiere mover: ";
				std::cin >> pos;
				std::cout << "A donde la quiere mover: ";
				std::cin >> nuevaPos;
				if(!game.move((pos-1)/3, (pos-1)%3, (nuevaPos-1)/3, (nuevaPos-1)%3)) {
					std::cout << "Movimiento invalido, intenta de nuevo.\n";
				} else {
					game.printBoard();
				}
			} else {
				std::cout << "Muchas gracias por jugar!\n";
				return 0;
			}

		} else {
			Board mejorJugada = minmax.minmaxAlgorithm(board);
			game.setBoard(mejorJugada);
			game.nextTurn();
			game.printBoard();
		}
	}

	game.printWinner();
	return 0;
}
