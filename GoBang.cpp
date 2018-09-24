#include "GoBang.hpp"
#include <iostream>

GoBang::GoBang()
{
}

int GoBang::ComputerPlay(enum Player player)
{
    struct Point position = {0, 0};
    srand((unsigned int)time(NULL));
    while (1)
    {
        position.x = (rand() % 15) + 1;
        position.y = (rand() % 15) + 1;
        // std::cout << chessBoard.get(position);
        if (this->chessBoard.get(position) == 'b')
        {
            break;
        }
    }
    // std::cout << (char)player << std::endl;
    this->chessBoard.put(position, (char)player);
    this->previousStep = position;
    this->previousPlayer = player;
    return 0;
}

int GoBang::PlayerPlay(enum Player player, struct Point position)
{
    if ((this->chessBoard.get(position) == 'o') ||
        (this->chessBoard.get(position) == 'x'))
    {
        return 1; // which represents false return
    }
    else
    {
        this->chessBoard.put(position, player);
        this->previousStep = position;
        this->previousPlayer = player;
        return 0;
    }
    return 0;
}

int checkInRange(int x, int y)
{
    return ((x < 15) && (x > 0) &&
            (y < 15) && (y > 0));
}

bool GoBang::Victory()
{
    const int arrayX[] = {1, 1, 0, -1};
    const int arrayY[] = {0, 1, 1, 1};
    for (int arrayPos = 0; arrayPos < 4; ++arrayPos)
    {
        int acc = 0;
        int coordinateX = this->previousStep.x;
        int coordinateY = this->previousStep.y;
        int addX = arrayX[arrayPos];
        int addY = arrayY[arrayPos];
        int DirectionFlag = 0;
        while (true)
        {
            bool inrange = checkInRange(coordinateX + addX, coordinateY + addY);
            if (inrange && this->chessBoard.get(coordinateX + addX, coordinateY + addY) == this->previousPlayer)
            {
                acc += 1;
                coordinateX += addX;
                coordinateY += addY;
            }
            else
            {
                if (DirectionFlag == 0)
                {
                    coordinateX = this->previousStep.x;
                    coordinateY = this->previousStep.y;
                    addX *= -1;
                    addY *= -1;
                    DirectionFlag = 1;
                }
                else
                {
                    break;
                }
            }
        }
        if (acc >= 4)
        {
            return true;
        }
    }
    return false;
}

void GoBang::PrintChessBoard()
{
    //system("clear");
    for (int i = 0; i <= 15; ++i)
    {
        if (i == 0)
        {
            printf(" ");
        }
        for (int j = 0; j <= 15; ++j)
        {
            if (i == 0)
            {
                if (j != 0)
                {
                    printf("%d ", j); // "%d "
                    if (j <= 9)
                    {
                        printf(" ");
                    }
                }
                else
                {
                    printf(" ");
                }
            }
            else if (j == 0)
            {
                printf("%d", i); // "%d"
                if (i <= 9)
                    printf(" ");
            }
            else
            {
                if (i <= 15)
                {

                    printf("%c |", this->chessBoard.get(i, j)); // "%c |"
                }
            }
        }
        std::cout << std::endl;
        std::cout << "  "; // " "
        for (int m = 0; m < 15; m++)
        {
            printf("--|");
        }
        std::cout << std::endl;
    }
}
std::string GoBang::Status()
{
    return this->chessBoard.toStr();
}

void GoBang::PreviousInfo(struct Point &step, Player &player){
    step = this->previousStep;
    player = this->previousPlayer;
}