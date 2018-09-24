#include "GoBang.hpp"
#include "Player.hpp"
#include "Point.hpp"
#include <iostream>

int main(){
    GoBang game;
    while(true){
        game.ComputerPlay(P1);
        game.PrintChessBoard();
        if(game.Victory()){
            std::cout << "P1" << std::endl;
            return 0;
        }
        game.ComputerPlay(P2);
        game.PrintChessBoard();
        if(game.Victory()){
            std::cout << "P2" << std::endl;
            return 0;
        }
    }
    return 0;
}