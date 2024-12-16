#pragma once

#include "./point.h"

namespace navigator
{
    typedef point::Point Point;
    typedef point::Direction Direction;
    
    class NavigatorPosition
    {
    public:
        const Point position;
        const Direction facing;

        NavigatorPosition(Point p, Direction f) : position{p}, facing{f} {};
        NavigatorPosition(const NavigatorPosition &oth) : position{oth.position}, facing{oth.facing} {};

        const bool operator==(const NavigatorPosition &oth) const
        {
            return position == oth.position && facing == oth.facing;
        }

        const bool operator<(const NavigatorPosition &oth) const
        {
            // Prefer the facing one since it doesn't do a hash
            if (facing == oth.facing)
            {
                return position < oth.position;
            }
            else
            {
                return facing < oth.facing;
            }
        }
    };
};

template<>
struct std::hash<navigator::NavigatorPosition>{
    std::size_t operator()(const navigator::NavigatorPosition& k) const {
        return k.position.hash() * 5 + k.facing.as_index();
    }
};