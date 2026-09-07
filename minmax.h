#ifndef MINMAX_H
#define MINMAX_H


#include "board.h"
#include <vector>

class MinMax{
    Marks ai;
    Marks opponent;
    const int MAX_DEPTH = 2;

    int heuristic (Board board){
        int value = 0;
        
        //Winner move
        if (board.winner() == ai){
            return 100;
        }else if (board.winner() == opponent){
            return -100;
        }

        //Center
        if (board.at(1, 1) == ai){
            value += 3;
        }else if (board.at(1, 1) == opponent){
            value -= 3;
        }

        //Boards
        for (int i = 0; i <= 2; i+=2){
            for (int j = 0; j <= 2; j+=2){
                if (board.at (i, j) == ai){
                    value += 2;
                }else if (board.at (i, j) == opponent){
                    value -= 2;
                }
            }
        }
        
        return value;
    }

    std::vector<Board> getChildren (Board board, Marks player){
        std::vector<Board> children;

        for (int i=0; i<3; i++){
            for (int j=0; j<3; j++){
                if (board.at(i, j) == player){
                    int new_row[4] = {-1, 1, 0, 0};
                    int new_col[4] = {0, 0, -1, 1};
            
                    for (int k = 0; k<4; k++){
                        if (board.validCell(i+new_row[k], j+new_col[k]) && board.at(i+new_row[k], j+new_col[k]) == EMPTY){
                            Board copy = board;
                            copy.moveMark(i, j, i+new_row[k], j+new_col[k]);
                            children.push_back(copy); 
                        }   
                    }
                    
                }else if (board.at(i, j) == EMPTY){
                    Board copy = board;
                    copy.addMark(i, j, player);
                    children.push_back(copy);
                }
            }
        }
        
        return children;
    }

    int minimax(Board board, Marks player, int depth, bool max){
        if (depth == MAX_DEPTH || board.winner() != EMPTY || board.fullBoard()){
            return heuristic(board);
        }

        std::vector<Board> children = getChildren(board, player);
        std::vector<Board>::iterator it = children.begin();

        if (max){
            int best_value = minimax(*it,(player == X ? O:X), depth+1, false);
            it++;

            for (; it != children.end(); it++){
                int value = minimax(*it, (player == X ? O:X), depth+1, false);

                if (value > best_value){
                    best_value = value;
                }
            }

            return best_value;

        }else{
            int best_value = minimax(*it,(player == X ? O:X), depth+1, true);
            it++;

            for (; it != children.end(); it++){
                int value = minimax(*it, (player == X ? O:X), depth+1, true);

                if (value < best_value){
                    best_value = value;
                }
            }

            return best_value;

        }  
    }


    public:

    MinMax (Marks ai_player){
        ai = ai_player;
        opponent = (ai_player == X ? O : X);
    }



    Board minmaxAlgorithm (Board board){
        std::vector<Board> children_ai;
        children_ai = getChildren (board, ai);
        std::vector<Board>::iterator it = children_ai.begin();
        Board best_move = *(children_ai.begin());
        int best_value = minimax(best_move, opponent, 1, false);
        it++;

        for (; it != children_ai.end(); it++){
            int move_value = minimax(*it, opponent, 1, false);
            if (best_value < move_value){
                best_move = *it;
                best_value = move_value;
            }
        }
        return best_move;
    }


};


#endif
