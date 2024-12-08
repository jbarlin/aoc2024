#include "point.h"

namespace day08
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

    const std::optional<Point> Point::continue_to_next_point(const Point &B, const unsigned int sq_size)
    {
        int dx = ((int)B.x) - ((int)this->x);
        int dy = ((int)B.y) - ((int)this->y);

        long x = ((long)B.x) - (dx * 2);
        long y = ((long)B.y) - (dy * 2);

        if (x >= 0 && x < sq_size && y >= 0 && y < sq_size)
        {
            const Point c(x, y);
            return std::optional(c);
        }
        else
        {
            return std::optional<Point>();
        }
    }

    const std::set<Point> Point::create_line(const Point &B, const unsigned int sq_size)
    {

        int dx = ((int)B.x) - ((int)this->x);
        int dy = ((int)B.y) - ((int)this->y);
        std::set<Point> points;
        int mult = 2;
        while (true)
        {
            long x = ((long)B.x) - (dx * mult);
            long y = ((long)B.y) - (dy * mult);
            if (x >= 0 && x < sq_size && y >= 0 && y < sq_size)
            {
                mult++;
                const Point c(x, y);
                points.insert(c);
            }
            else
            {
                break;
            }
        }
        mult = 2;
        while (true)
        {
            long x = ((long)B.x) + (dx * mult);
            long y = ((long)B.y) + (dy * mult);
            if (x >= 0 && x < sq_size && y >= 0 && y < sq_size)
            {
                mult++;
                const Point c(x, y);
                points.insert(c);
            }
            else
            {
                return points;
            }
        }
    }

    const bool Point::inside(const unsigned int square_size) const
    {
        return x < square_size && y < square_size;
    }
}