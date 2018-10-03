#include "Decision.hpp"
#include <random>

Decision::Decision()
    : s((226) * sizeof(unsigned int), '\0')
{
    for (int i = 0; i < 225; ++i)
    {
        std::size_t const addr = i * sizeof(unsigned int);
        unsigned int *data = (unsigned int *)&this->s[addr];
        *data = 1U;
    }
    // initilize all possiblity of position to 1

    std::size_t const addr = 225 * sizeof(unsigned int);
    unsigned int *data = (unsigned int *)&this->s[addr];
    *data = 15U * 15U;
    // total become 15*15
}

Decision::Decision(std::string s)
    : s(s)
{
}

unsigned int Decision::get(Point position)
{
    std::size_t index = position.x * 15 + position.y;
    std::size_t const addr = index * sizeof(unsigned int);
    unsigned int const *const data = (unsigned int *)&this->s[addr];
    return *data;
}

void Decision::add1(Point position)
{
    std::size_t index = position.x * 15 + position.y;
    std::size_t addr = index * sizeof(unsigned int);
    unsigned int *data = (unsigned int *)&this->s[addr];
    *data = ++(*data);
    addr = 225 * sizeof(unsigned int);
    data = (unsigned int *)&this->s[addr];
    *data = ++(*data);
}

std::string Decision::toStr()
{
    return this->s;
}

Point Decision::BestChoice(){
    unsigned int maxval(0);
    Point maxPt = {0, 0};
    for(int i = 0; i < 15; ++i){
        for(int j = 0; j < 15; ++j){
            Point pt = {i, j};
            if(this->get(pt) > maxval){
                maxPt = pt;
            }
        }
    }
    return maxPt;
}

Point Decision::RandomChoice(){
    std::size_t const addr = 255 * sizeof(unsigned int);
    // fetch the 256-th unsigned int;
    unsigned int *data = (unsigned int *)&this->s[addr];
    // now data = \sum_{n = 0}^254 (int) str
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,*data);
    int randomval = distribution(generator);
    Point maxPt = {0, 0};
    for(int i = 0; i < 15; ++i){
        for(int j = 0; j < 15; ++j){
            Point pt = {i, j};
            randomval = randomval - get(pt);
            if(randomval <= 0){
                return pt;
            }
        }
    }
    return maxPt;
}