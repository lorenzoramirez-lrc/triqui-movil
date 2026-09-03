#ifndef BOARD_H 
#define BOARD_H 
#include <array>
#include <cmath>
#include <iostream>

enum Marks{
    EMPTY,
    X,
    O,
};

class Board{

    static const int BOARD_SIZE = 3;

    std::array<std::array<Marks,BOARD_SIZE>, BOARD_SIZE> board{{
                          {EMPTY,EMPTY,EMPTY},
                          {EMPTY,EMPTY,EMPTY},
                          {EMPTY,EMPTY,EMPTY}
                          }};

    bool emptyCell(int x, int y){
        return board[x][y] == EMPTY;
    }

    public:

    bool adjacentCells(int row, int col , int new_row, int new_col){
        return (abs(new_row - row) + abs(new_col - col) ) == 1 ? true : false;
    }

    bool validCell(int row, int col){
        if(row < 0 or BOARD_SIZE <= row) return false;
        if(col < 0 or BOARD_SIZE <= col) return false;

        return true;
    }

    bool addMark(int row, int col, Marks mark){

        if(not validCell(row,col)) return false;
        if(not emptyCell(row,col)) return false;

        board[row][col] = mark;
        return true;
    }

    bool moveMark(int row, int col, int new_row , int new_col){

        if(not validCell(row,col) or not validCell(new_row,new_col)) return false;

        if(emptyCell(row, col)) return false;
        if(not emptyCell(new_row, new_col)) return false;
        if(not adjacentCells(row, col, new_row, new_col)) return false;

        board[new_row][new_col] = board[row][col];
        board[row][col] = EMPTY;

        return true;
    }

    bool fullBoard(){
        for(auto& row: board){
            for(auto& cell: row){
                if(cell == EMPTY) return false;
            }
        }
        return true;
    }

    Marks winner(){
        int Xs = 0;
        int Os = 0;

        //Rows
        for(auto& rows : board){
            for(auto& mark : rows){
                if(mark ==  X) Xs++;
                if(mark ==  O) Os++;
            }
            if(Xs==3) return X;
            if(Os==3) return O;
            Xs = Os = 0;
        }

        //Columns
        for(int i = 0 ; i< BOARD_SIZE ; i++){
            for(int j = 0; j<BOARD_SIZE; j++){
                if(board[j][i] == X) Xs++;
                if(board[j][i] == O) Os++;
            }
            if(Xs==3) return X;
            if(Os==3) return O;
            Xs = Os = 0;
        }

        //Diagonal
        for(int i =0; i<BOARD_SIZE; i++){
            if(board[i][i] == X) Xs++;
            if(board[i][i] == O) Os++;
        }

        if(Xs==3) return X;
        if(Os==3) return O;
        Xs = Os = 0;

        //Anti-Diagonal
        for(int i =0; i<BOARD_SIZE; i++){
            if(board[i][BOARD_SIZE-i-1] == X) Xs++;
            if(board[i][BOARD_SIZE-i-1] == O) Os++;
        }

        if(Xs==3) return X;
        if(Os==3) return O;
        Xs = Os = 0;

        return EMPTY;
    }
    

    void print() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                char symbol = ' ';

                if (board[i][j] == X) symbol = 'X';
                else if (board[i][j] == O) symbol = 'O';

                std::cout << " " << symbol << " ";

                if (j < BOARD_SIZE - 1)
                    std::cout << "|";
            }

            std::cout << "\n";

            if (i < BOARD_SIZE - 1)
                std::cout << "---+---+---\n";
        }
    }

};

#endif
