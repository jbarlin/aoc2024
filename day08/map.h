#pragma once

#include <map>
#include <vector>
#include "point.h"

namespace day08
{
    class Map
    {
    private:
    public:
        const std::vector<std::vector<Point>> map;
        const unsigned int square_size;
        Map(const std::vector<std::vector<Point>> &map, const unsigned int square_size) : map{map}, square_size{square_size} {};
    };
}