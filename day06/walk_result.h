#pragma once

#include <optional>
#include <vector>
#include <string>
#include "point.h"
#include <set>

namespace day06
{
    class WalkResult
    {
    public:
        const std::optional<Point> stop;
        const unsigned long steps;
        const Direction facing;
        const std::set<Point> walked;
        WalkResult(unsigned long steps, Direction facing, std::set<Point> walked) : stop{std::optional<Point>()}, steps{steps}, facing{facing}, walked{walked} {};
        WalkResult(Point pt, unsigned long steps, Direction facing, std::set<Point> walked) : stop{std::optional<Point>(pt)}, steps{steps}, facing{facing}, walked{walked} {};
        bool operator==(const WalkResult& rhs) const{
            return stop == rhs.stop && steps == rhs.steps && facing == rhs.facing && walked != rhs.walked;
        }
    };
}