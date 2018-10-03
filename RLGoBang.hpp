#include "GoBang.hpp"
#include "leveldb/db.h"

class RLGoBang: public GoBang{
  public:
    RLGoBang(std::string location);
    int learn();
    int learn(leveldb::DB *LearnedData);
    int ComputerPlayRandom(enum Player player);
    int ComputerPlayBest(enum Player player);
    ~RLGoBang();
  private:
    leveldb::DB *db;
    int writeData(const std::vector<std::string> &status,
                  const std::vector<Point> &point);
};