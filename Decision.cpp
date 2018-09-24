#include "Decision.hpp"

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