#include "point.h"

namespace day12
{

    const unsigned long prime = 149;

    unsigned long Point::hash() const
    {
        return (prime * x) + y;
    }

    bool Point::operator==(const Point &other) const
    {
        return hash() == other.hash();
    }

    bool Point::operator<(const Point &other) const
    {
        return hash() < other.hash();
    }

    bool Point::operator>(const Point &other) const
    {
        return hash() > other.hash();
    }

    const std::string Point::as_string() const
    {
        return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
    }

    const bool Point::inside(const unsigned int square_size) const
    {
        return x < square_size && y < square_size;
    }

    const unsigned char Point::extract_value_square_map(const std::vector<std::vector<unsigned char>> &map) const
    {
        return map[y][x];
    }

}