#include "point.h"


namespace point
{

    const ul prime = 149;

    ul Point::hash() const
    {
        return (prime * x) + y;
    }

    const Point Point::move(const Direction &dir) const
    {
        Point aft(x + dir.x, y + dir.y);
        return aft;
    }

    const bool Point::can_move_sq(const Direction &dir, ul size) const
    {
        return can_move(dir, size, size);
    }

    const bool Point::can_move(const Direction &dir, ul x_limit, ul y_limit) const
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

    const bool Point::inside(const ul square_size) const
    {
        return inside(square_size, square_size);
    }

    const bool Point::inside(const ul max_x, const ul max_y) const {
        return x < max_x && y < max_y;
    }

    const bool Point::extract_bool_from_map(const std::vector<std::vector<bool>> &map) const
    {
        return map[y][x];
    }

    const unsigned char Point::extract_uchar_from_map(const std::vector<std::vector<unsigned char>> &map) const
    {
        return map[y][x];
    }

    const std::vector<Point> Point::get_plus_in_bounds(const ul square_size) const
    {
        return get_plus_in_bounds(square_size, square_size);
    }

    const std::vector<Point> Point::get_plus_in_bounds(const ul max_x, const ul max_y) const
    {
        std::vector<Point> points;
        points.reserve(4);
        // +1, 0
        if (x + 1 < max_x)
        {
            points.emplace_back(Point(x + 1, y));
        }
        // -1, 0
        if (x >= 1)
        {
            points.emplace_back(Point(x - 1, y));
        }
        // 0, +1
        if (y + 1 < max_y)
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

    const float Point::distance(const Point &other) const
    {
        return std::sqrt(std::pow((x - other.x), 2.0) + std::pow((y - other.y), 2.0));
    }

    const std::optional<Point> Point::continue_to_next_point(const Point &B, const ul sq_size)
    {
        int dx = ((int)B.x) - ((int)this->x);
        int dy = ((int)B.y) - ((int)this->y);

        long x = ((long)B.x) - (dx * 2);
        long y = ((long)B.y) - (dy * 2);

        if (x >= 0 && ((ul)x) < sq_size && y >= 0 && ((ul)y) < sq_size)
        {
            const Point c(x, y);
            return std::optional(c);
        }
        else
        {
            return std::optional<Point>();
        }
    }

    const std::set<Point> Point::create_line(const Point &B, const ul sq_size)
    {

        int dx = ((int)B.x) - ((int)this->x);
        int dy = ((int)B.y) - ((int)this->y);
        std::set<Point> points;
        int mult = 2;
        while (true)
        {
            long x = ((long)B.x) - (dx * mult);
            long y = ((long)B.y) - (dy * mult);
            if (x >= 0 && ((ul)x) < sq_size && y >= 0 && ((ul)y) < sq_size)
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
            if (x >= 0 && ((ul)x) < sq_size && y >= 0 && ((ul)y) < sq_size)
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

    const bool Point::gone_past_x_or_y(const Point &other) const
    {
        return this->x > other.x || this->y > other.y;
    }

}