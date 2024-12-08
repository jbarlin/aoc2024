#pragma once

#include <vector>
#include <optional>
#include <math.h>
#include <cassert>
#include <string>
#include <iostream>
#include <set>

namespace day08
{

    class Point
    {
    private:
    public:
        const unsigned int x;
        const unsigned int y;
        Point(unsigned int x, unsigned int y) : x{x}, y{y} {};
        Point(std::pair<unsigned int, unsigned int> p) : x{p.first}, y{p.second} {};

        unsigned long hash() const;
        bool operator==(const Point &other) const;
        bool operator<(const Point &other) const;
        bool operator>(const Point &other) const;
        const float distance(const Point &other) const;
        const std::string as_string() const;
        const std::optional<Point> continue_to_next_point(const Point &other, const unsigned int max_size);
        const std::set<Point> create_line(const Point &other, const unsigned int max_size);
        const bool inside(const unsigned int square_size) const;
    };
}