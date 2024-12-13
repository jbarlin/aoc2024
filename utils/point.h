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
        const unsigned long x;
        const unsigned long y;
        Point(unsigned long x, unsigned long y) : x{x}, y{y} {};
        Point(std::pair<unsigned long, unsigned long> p) : x{p.first}, y{p.second} {};
        Point(const Point &a, const Point &b) : x{a.x + b.x}, y{a.y + b.y} {};
        unsigned long hash() const;
        bool operator==(const Point &other) const;
        bool operator<(const Point &other) const;
        bool operator>(const Point &other) const;
        const bool can_move_sq(const Direction &dir, unsigned long size) const;
        const bool can_move(const Direction &dir, unsigned long x_limit, unsigned long y_limit) const;
        const Point move(const Direction &dir) const;
        const Point move_away(const Direction &dir) const
        {
            return move(dir.turn_around());
        }
        const std::string as_string() const;
        const bool inside(const unsigned long square_size) const;
        const unsigned char extract_value_square_map(const std::vector<std::vector<unsigned char>> &map) const;
        const std::vector<Point> get_plus_in_bounds(const unsigned long square_size) const;
        const float distance(const Point &other) const;
        const std::optional<Point> continue_to_next_point(const Point &other, const unsigned long max_size);
        const std::set<Point> create_line(const Point &other, const unsigned long max_size);
        const bool gone_past_x_or_y(const Point &other) const;
    };
}