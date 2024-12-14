#pragma once

#include "directions.h"
#include "numerics.h"
#include "motion.h"

#include <vector>
#include <optional>
#include <math.h>
#include <cassert>
#include <string>
#include <iostream>
#include <set>

namespace point
{

    typedef unsigned long ul;

    class Point
    {
    private:
    public:
        const ul x;
        const ul y;
        Point(ul x, ul y) : x{x}, y{y} {};
        Point(const std::pair<ul, ul> &p) : x{p.first}, y{p.second} {};
        Point(const Point &p) : x{p.x}, y{p.y} {};
        Point(const Point &a, const Point &b) : x{a.x + b.x}, y{a.y + b.y} {};
        Point(const Point &a, const Motion &b) : x{a.x + b.x}, y{a.y + b.y} {};
        ul hash() const;
        bool operator==(const Point &other) const;
        bool operator<(const Point &other) const;
        bool operator>(const Point &other) const;
        const bool can_move_sq(const Direction &dir, ul size) const;
        const bool can_move(const Direction &dir, ul x_limit, ul y_limit) const;
        const Point move(const Direction &dir) const;
        const Point move_away(const Direction &dir) const
        {
            return move(dir.turn_around());
        }
        const std::string as_string() const;
        const bool inside(const ul square_size) const;
        const bool inside(const ul max_x, const ul max_y) const;
        const unsigned char extract_uchar_from_map(const std::vector<std::vector<unsigned char>> &map) const;
        const bool extract_bool_from_map(const std::vector<std::vector<bool>> &map) const;
        const std::vector<Point> get_plus_in_bounds(const ul square_size) const;
        const std::vector<Point> get_plus_in_bounds(const ul max_x, const ul max_y) const;
        const float distance(const Point &other) const;
        const std::optional<Point> continue_to_next_point(const Point &other, const ul max_size);
        const std::set<Point> create_line(const Point &other, const ul max_size);
        const bool gone_past_x_or_y(const Point &other) const;
        Point(const Point &a, const Point &b, const ul max_x, const ul max_y) : 
            x{numerics::wrap_addition_upper_bound(a.x, b.x, max_x)},
            y{numerics::wrap_addition_upper_bound(a.y, b.y, max_y)}
            {}
            ;
        Point(const Point &a, const Point &b, const ul square_size) : 
            x{numerics::wrap_addition_upper_bound(a.x, b.x, square_size)},
            y{numerics::wrap_addition_upper_bound(a.y, b.y, square_size)}
            {}
            ;

        Point(const Point &a, const Motion &b, const ul max_x, const ul max_y) : 
            x{numerics::wrap_addition_upper_bound(a.x, b.x, max_x)},
            y{numerics::wrap_addition_upper_bound(a.y, b.y, max_y)}
            {}
            ;
        Point(const Point &a, const Motion &b, const ul square_size) : 
            x{numerics::wrap_addition_upper_bound(a.x, b.x, square_size)},
            y{numerics::wrap_addition_upper_bound(a.y, b.y, square_size)}
            {}
            ;

        Point(const Point &a, const Motion &b, const ul max_x, const ul max_y, const ul times) : 
            x{numerics::wrap_addition_upper_bound(a.x, b.x * times, max_x)},
            y{numerics::wrap_addition_upper_bound(a.y, b.y * times, max_y)}
            {}
            ;
    };
}