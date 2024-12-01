#include "point.h"

namespace day06
{

    unsigned long Point::hash() const{
        const unsigned long prime = 137;
        unsigned long result = x;
        result = prime * result + y;
        return result;
    }

    bool Point::operator== (const Point & other) const{
        return hash() == other.hash();
    }
    bool Point::operator< (const Point & other) const{
        return hash() < other.hash();
    }
    bool Point::operator> (const Point & other) const{
        return hash() > other.hash();
    }

    const Point Point::move(const Direction &dir) const
    {
        Point aft(x + dir.x, y + dir.y);
        return aft;
    }

    const bool Point::can_move_sq(const Direction &dir, unsigned int size) const
    {
        return can_move(dir, size, size);
    }

    const bool Point::can_move(const Direction &dir, unsigned int x_limit, unsigned int y_limit) const
    {
        if (x != 0 || dir.x > -1)
        {
            if (y != 0 || dir.y > -1)
            {
                Point moved = move(dir);
                return moved.x < x_limit && moved.y < y_limit;
            }
        }
        return false;
    }

    const unsigned char Point::extract_value_square_map(const std::vector<std::vector<unsigned char>> &map) const
    {
        return map[y][x];
    }
}