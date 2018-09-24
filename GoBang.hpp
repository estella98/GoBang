#pragma once
#include <iostream>
#include <string>
#include "Point.hpp"
#include "ChessBoard.hpp"
#include "Player.hpp"

class GoBang
{
  public:
    GoBang();
    int ComputerPlay(enum Player player);
    int PlayerPlay(enum Player player, struct Point position);
    bool Victory();
    void PrintChessBoard();
    std::string Status();
  protected:
    ChessBoard chessBoard;
    struct Point previousStep;
    Player previousPlayer;
};