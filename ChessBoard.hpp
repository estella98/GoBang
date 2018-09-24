#pragma once
#include "Point.hpp"
#include <string>

class ChessBoard
{
  public:
    ChessBoard();
    char get(struct Point position);
    char get(int x, int y);
    void put(struct Point position, char val);
    void put(int x, int y, char val);
    std::string toStr();

  protected:
    char board[15][15];
};