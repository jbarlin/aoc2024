#pragma once

#include "./point.h"
#include <map>

namespace graph
{
    typedef point::Point Point;
    typedef point::Direction Direction;

    typedef point::Point Point;
    typedef point::Direction Direction;

    struct PointAndDir
    {
        const Point position;
        const Direction facing;

        PointAndDir(Point p, Direction f): position{p},facing{f}{};
        PointAndDir(const PointAndDir &oth): position{oth.position},facing{oth.facing}{};

        const bool operator==(const PointAndDir &oth) const
        {
            return position == oth.position && facing == oth.facing;
        }

        const bool operator<(const PointAndDir &oth) const
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

    class Graph
    {
    private:
        const std::map<PointAndDir, std::map<PointAndDir, unsigned int>> graph;

    public:
        Graph(const std::map<PointAndDir, std::map<PointAndDir, unsigned int>> &in) : graph{in} {};
        const unsigned long long path_between(const PointAndDir &start, const Point &end) const;
    };

    Graph convert_to_graph(const std::vector<std::vector<unsigned char>> &incoming_map, const Point start, const Direction start_direction, const Point end, unsigned char wall_char, unsigned int turn_cost);
}