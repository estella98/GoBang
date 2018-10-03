#pragma once
#include <string>
#include "Point.hpp"

class Decision
{
  public:
    Decision();
    Decision(std::string s);
    unsigned int get(Point position);
    void add1(Point position);
    Point BestChoice();
    Point RandomChoice();
    std::string toStr();

  private:
    std::string s;
};