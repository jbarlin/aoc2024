#pragma once

#include "directions.h"

#include <vector>
#include <optional>
#include <math.h>
#include <cassert>
#include <string>
#include <iostream>
#include <set>

namespace point
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
        const bool can_move_sq(const Direction &dir, unsigned int size) const;
        const bool can_move(const Direction &dir, unsigned int x_limit, unsigned int y_limit) const;
        const Point move(const Direction &dir) const;
        const Point move_away(const Direction &dir) const{
            return move(dir.turn_around());
        }
        const std::string as_string() const;
        const bool inside(const unsigned int square_size) const;
        const unsigned char extract_value_square_map(const std::vector<std::vector<unsigned char>> &map) const;
        const std::vector<Point> get_plus_in_bounds(const unsigned int square_size) const;
        const float distance(const Point &other) const;
        const std::optional<Point> continue_to_next_point(const Point &other, const unsigned int max_size);
        const std::set<Point> create_line(const Point &other, const unsigned int max_size);
    };
}