#include "ChessBoard.hpp"

ChessBoard::ChessBoard()
{
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            this->board[i][j] = 'b'; // B stands for blank space
        }
    }
}

char ChessBoard::get(struct Point position)
{
    return this->board[position.x - 1][position.y - 1];
}

char ChessBoard::get(int x, int y){
    return this->board[x - 1][y - 1];
}

void ChessBoard::put(struct Point position, char val)
{
    this->board[position.x - 1][position.y - 1] = val;
}

void ChessBoard::put(int x, int y,char val){
    this->board[x - 1][y - 1] = val;   
}

std::string ChessBoard::toStr()
{
    std::string status = "";
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            status += this->board[i][j];
        }
    }
    return status;
}