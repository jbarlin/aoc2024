#pragma once

#include "./point.h"
#include <unordered_set>

namespace navigator
{
    typedef point::Point Point;
    typedef point::Direction Direction;

    class CostAndPathOfNavigation
    {
    public:
        const unsigned long long cost;
        const std::vector<std::unordered_set<Point>> positions_visted;

        const std::unordered_set<Point> all_possible_points() const
        {
            std::unordered_set<Point> points;
            for (const std::unordered_set<Point> &pathish : positions_visted)
            {
                points.insert(pathish.begin(), pathish.end());
            }
            return points;
        }
        CostAndPathOfNavigation(unsigned long long cost, const std::vector<std::unordered_set<Point>> &positions_visted): cost{cost}, positions_visted{positions_visted}{};        
    };

    class NavigatorPosition
    {
    public:
        const Point position;
        const Direction facing;

        NavigatorPosition(Point p, Direction f) : position{p}, facing{f} {};
        NavigatorPosition(const NavigatorPosition &oth) : position{oth.position}, facing{oth.facing} {};

        const std::size_t hash() const
        {
            return position.hash() * 5 + facing.as_index();
        }

        bool operator==(const NavigatorPosition &oth) const
        {
            return hash() == oth.hash();
        }

        bool operator<(const NavigatorPosition &oth) const
        {
            return hash() < oth.hash();
        }

        const std::string as_string() const
        {
            return "@" + position.as_string() + " F " + facing.as_string();
        }
    };
};

template <>
struct std::hash<navigator::NavigatorPosition>
{
    std::size_t operator()(const navigator::NavigatorPosition &k) const
    {
        return k.hash();
    }
};