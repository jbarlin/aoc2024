#pragma once

#include "../utils/point.h"

namespace day14{

    typedef point::Point Point;
    typedef point::Motion Motion;

    class Droid{
        public:
            const Point position;
            const Motion motion;
            const unsigned int number;
            Droid(const Point &p, const Motion &m, const unsigned int number) : position{Point(p.x, p.y)},motion{m},number{number}{};
            const Droid after_ticks(const unsigned int ticks, const unsigned int max_x, const unsigned int max_y) const;
            const std::string as_string() const;
    };
}