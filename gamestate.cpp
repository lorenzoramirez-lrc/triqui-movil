#include "board.h"
#include <iostream>
#include <string>
// terminal color 
namespace Color {
    std::string Red = "\033[1;31m"; // for player X 
    std::string Blue = "\033[1;34m"; // for player O
    std::string Yellow = "\033[1;33m"; // for actual turn player
    std::string Reset = "\033[0m"; // reset color
}

class GameState {

Board board;
Marks currentPlayer;
Marks IAPlayer;
int turnCount;

std::string symbol (Marks mark) {
    
    if(mark == X){
        return Color::Red + "X" + Color::Reset; 
    } else if (mark == O){
        return Color::Blue + "O" + Color::Reset;
    }
        return " ";
}

int countMarks(Marks m) {
    int count = 0;
    for(int i=0; i<3;i++){
        for(int j=0; j<3;j++){
            if(board.at(i,j)==m){
                count++;
            }
        }
    }
    return count;
}

public:
GameState(Marks startingPlayer, Marks IAPlayer): currentPlayer(startingPlayer), IAPlayer(IAPlayer), turnCount(1){}

Board& getBoard(){ 
    return board; 
}

Marks getCurrentPlayer(){ 
    return currentPlayer; 
}
  
bool isIAPlayerTurn() {
    return currentPlayer == IAPlayer;
}
void nextTurn(){
    currentPlayer = (currentPlayer == X) ? O : X;
    turnCount++;
}

bool play(int row,int col){
    if(!board.addMark(row,col,currentPlayer)){
        return false;
    }
    nextTurn();
    return true;
}

bool move(int row, int col, int new_row, int new_col){
    if(board.at(row,col) != currentPlayer){
        return false;
    }

    if(!board.moveMark(row,col,new_row,new_col)){
        return false;
    }
    nextTurn();
    return true;
}

bool gameOver(){
    return board.winner() != EMPTY || board.fullBoard();
}
void printTitle() {
    std::cout << Color::Yellow << "Triqui movil" << Color::Reset << std::endl;
}
void printBoard() {
    std::cout << "    ┌───┬───┬───┐\n";

    for (int i = 0; i <3; i++) {
        std::cout << "    │ ";
        for (int j = 0; j < 3; j++) {
            std::cout << symbol(board.at(i,j)) << " │ ";
        }
        std::cout << "\n";
        if (i < 2) {
            std::cout << "    ├───┼───┼───┤\n";
        }
    }
    std::cout << "    └───┴───┴───┘\n";

    std::cout << Color::Yellow<<"jugada # "<<turnCount<<Color::Reset<<std::endl;
    std::cout << "Turno del jugador: " << symbol(currentPlayer) << std::endl;
    std::cout << "Jugador X: " << countMarks(X) << " | Jugador O: " << countMarks(O) << std::endl;
}

void printWinner() {
        Marks winner = board.winner();
        if (winner == X) {
            std::cout << Color::Red << "Jugador X gana!" << Color::Reset << std::endl;
        } else if (winner == O) {
            std::cout << Color::Blue << "Jugador O gana!" << Color::Reset << std::endl;
        } else {
            std::cout << "Empate!" << std::endl;
        }
}
};