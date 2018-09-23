#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <leveldb/dumpfile.h>

using namespace std;

constexpr int SIZE = 15;
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
        cout << "here1" << endl;
        break;
      }
      ComputerChess(P2, symbol2);
      if (Victory(P2, symbol2) == 1)
      {
        cout << "here2" << endl;
        break;
      }
    }
  }

  void InitChessBoard()
  {
    for (int i = 0; i <= SIZE; ++i)
    {
      for (int j = 0; j <= SIZE; ++j)
      {
        ChessBoard[i][j] = ChessBoardflag;
      }
    }
  }
  void PrintChessBoard()
  {
    //system("clear");
    for (int i = 0; i <= SIZE; ++i)
    {
      if (i == 0)
      {
        printf(" ");
      }
      for (int j = 0; j <= SIZE; ++j)
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
          if (i <= SIZE)
          {

            printf("%c |", ChessBoard[i][j]); // "%c |"
          }
        }
      }
      cout << endl;
      cout << "  "; // " "
      for (int m = 0; m < SIZE; m++)
      {
        printf("--|");
      }
      cout << endl;
    }
  }
  void PlayChess(Coordinate &pos, int player, int flag)
  {
    
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
    PrintChessBoard();
  }

  void ComputerChess(Coordinate &pos, char flag)
  {
    int x = 0;
    int y = 0;
    srand((unsigned int)time(NULL));
    while (1)
    {
      x = (rand() % SIZE) + 1;

      y = (rand() % SIZE) + 1;

      if (ChessBoard[x][y] == ChessBoardflag)
        break;
    }
    pos.x = x;
    pos.y = y;
    ChessBoard[pos.x][pos.y] = flag;
    PrintChessBoard();
  }

  int JudgeValue(const Coordinate &pos) //judge if a coordinator is valid
  {
    if (pos.x > 0 && pos.x <= SIZE && pos.y > 0 && pos.y <= SIZE)
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

  int Victory(Coordinate &pos, char flag){
    cout << "check" << flag << endl;
    //cout << pos.x << endl;
    //cout << pos.y << endl;
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
          cout <<" match one" <<endl;
          acc += 1;
          coordinateX += addX;
          coordinateY += addY;
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
        cout << "win" << endl;
        return 1; // 1 represents victory
      }
    }
    return 0; // 0 represents failure
  }

private:
  char ChessBoard[SIZE + 1][SIZE + 1];
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
