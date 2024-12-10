#include "point.h"

namespace day10
{

    unsigned long Point::hash() const
    {
        const unsigned long prime = 137;
        unsigned long result = x;
        result = prime * result + y;
        return result;
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

    const float Point::distance(const Point &other) const
    {
        return std::sqrt(std::pow((x - other.x), 2.0) + std::pow((y - other.y), 2.0));
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

    const std::vector<Point> Point::get_plus_in_bounds(const unsigned int square_size) const
    {
        std::vector<Point> points;
        points.reserve(4);
        // +1, 0
        if (x + 1 < square_size)
        {
            points.emplace_back(Point(x + 1, y));
        }
        // -1, 0
        if (x >= 1)
        {
            points.emplace_back(Point(x - 1, y));
        }
        // 0, +1
        if (y + 1 < square_size)
        {
            points.emplace_back(Point(x, y + 1));
        }
        // 0, -1
        if (y >= 1)
        {
            points.emplace_back(Point(x, y - 1));
        }
        return points;
    }
}