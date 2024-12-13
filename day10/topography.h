#pragma once

#include <vector>
#include "../utils/point.h"

namespace day10
{
    typedef unsigned long long ull;
    typedef point::Point Point;

    class Topography
    {
    private:
    public:
        const std::vector<std::vector<unsigned char>> map;
        const std::vector<Point> zeros;
        const unsigned int square_size;
        Topography(const std::vector<std::vector<unsigned char>> &map, std::vector<Point> zeros, unsigned int square_size) : map{map}, zeros{zeros}, square_size{square_size} {};
        const ull score_trailheads() const;
        const ull score_rating() const;
    };

}