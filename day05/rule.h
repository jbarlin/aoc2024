#pragma once

#include <vector>
#include <string>

namespace day05
{
    class Rule
    {
    private:
        const unsigned char before;
        const unsigned char after;

    public:
        Rule(unsigned char before, unsigned char after);
        bool satisfied(const std::vector<unsigned char> &book);
        void make_happy(std::vector<unsigned char> &book);
    };

}