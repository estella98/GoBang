#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int size = 15;
const char ChessBoardflag = ' ';
const char symbol1 = 'o';
const char symbol2 = 'x';

typedef struct Coordinate
{
  int x;
  int y;
} Coordinate;

class GoBang
{
public:
  GoBang()
  {
    InitChessBoard();
  }
  void Play()
  {
    Coordinate P1;
    Coordinate P2;
    int n = 0;
    while (1)
    {

      ComputerChess(P1, symbol1);
      if (Victory(P1, symbol1) == 1)
      {
        break;
      }
      PlayChess(P2, 2, symbol2);
  
      if (Victory(P2, symbol2) == 1)
      {
        break;
      }
    }
  }

  void InitChessBoard()
  {
    for (int i = 0; i <= size; ++i)
    {
      for (int j = 0; j <= size; ++j)
      {
        ChessBoard[i][j] = ChessBoardflag;
      }
    }
  }
  void PrintChessBoard()
  {
    system("clear");
    for (int i = 0; i <= size; ++i)
    {
      if (i == 0)
      {
        printf(" ");
      }
      for (int j = 0; j <= size; ++j)
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
          if (i <= size)
          {

            printf("%c |", ChessBoard[i][j]); // "%c |"
          }
        }
      }
      cout << endl;
      cout << "  "; // " "
      for (int m = 0; m < size; m++)
      {
        printf("--|");
      }
      cout << endl;
    }
  }
  void PlayChess(Coordinate &pos, int player, int flag)
  {
    PrintChessBoard();
    while (1)
    {
      cout << "enter coordinate" << endl;
      cin >> pos.x >> pos.y;
      if (JudgeValue(pos) == 1)
      {
        break;
      }
      cout << "not valid" << endl;
    }
    ChessBoard[pos.x][pos.y] = flag;
  }

  void ComputerChess(Coordinate &pos, char flag)
  {

    PrintChessBoard();
    int x = 0;
    int y = 0;

    while (1)
    {
      x = (rand() % size) + 1;
      srand((unsigned int)time(NULL));
      y = (rand() % size) + 1;
      srand((unsigned int)time(NULL));
      if (ChessBoard[x][y] == ChessBoardflag)
        break;
    }
    pos.x = x;
    pos.y = y;
    ChessBoard[pos.x][pos.y] = flag;
  }

  int JudgeValue(const Coordinate &pos) //judge if a coordinator is valid
  {
    if (pos.x > 0 && pos.x <= size && pos.y > 0 && pos.y <= size)
    {
      if (ChessBoard[pos.x][pos.y] == ChessBoardflag)
      {
        return 1; // valid position
      }
    }
    return 0; //already been occupied
  }

  int checkInRange(int x, int y)
  {
    return ((x < 15) && (x >= 0) &&
            (y < 15) && (y >= 0));
  }

  int Victory(Coordinate pos, char flag)
  {
    for (int arrayPos = 0; arrayPos < 4; ++arrayPos)
    {
      int acc = 0;
      int coordinateX = pos.x;
      int coordinateY = pos.y;
      int addX = arrayX[arrayPos];
      int addY = arrayY[arrayPos];
      int DirectionFlag = 0;
      while (true)
      {
        bool inrange = checkInRange(coordinateX + addX, coordinateY + addY);
        if (inrange && ChessBoard[coordinateX + addX][coordinateY + addY] == flag)
        {
          acc += 1;
          coordinateX += arrayX[arrayPos];
          coordinateY += arrayY[arrayPos];
        }
        else
        {
          if (DirectionFlag == 0)
          {
            coordinateX = pos.x;
            coordinateY = pos.y;
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
        return 1; // 1 represents victory
      }
    }
    return 0; // 0 represents failure
  }

private:
  char ChessBoard[size + 1][size + 1];
  static int arrayX[8];
  static int arrayY[8];
};

int GoBang::arrayX[] = {1, 1, 0, -1};
int GoBang::arrayY[] = {0, 1, 1, 1};

int main()
{
  // GoBang().PrintChessBoard();
  GoBang().Play();
}