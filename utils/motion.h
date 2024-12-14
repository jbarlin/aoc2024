#pragma once

#include <utility>
#include <string>

namespace point{

    typedef signed int si;

    class Motion {
        public:
            const si x;
            const si y;
            Motion(si x, si y) : x{x}, y{y} {};
            Motion(std::pair<si, si> p) : x{p.first}, y{p.second} {};
            Motion(const Motion &a, const Motion &b) : x{a.x + b.x}, y{a.y + b.y} {};
            const std::string as_string() const {
                return "Vec(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
            }
    };
}