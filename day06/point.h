#pragma once

#include <vector>

#include "directions.h"

namespace day06{
    class Point{
        private:
        public:
            unsigned int x;
            unsigned int y;
            Point(unsigned int x, unsigned int y): x{x},y{y}{};
            Point(std::pair<unsigned int, unsigned int> p): x{p.first},y{p.second}{};
            const bool can_move_sq(const Direction &dir, unsigned int size) const;
            const bool can_move(const Direction &dir, unsigned int x_limit, unsigned int y_limit) const;
            const Point move(const Direction &dir) const;
            const Point move_away(const Direction &dir) const{
                return move(dir.turn_around());
            }
            const unsigned char extract_value_square_map(const std::vector<std::vector<unsigned char>> &map) const;
            unsigned long hash() const;
            bool operator== (const Point & other) const;
            bool operator< (const Point & other) const;
            bool operator> (const Point & other) const;
    };
}