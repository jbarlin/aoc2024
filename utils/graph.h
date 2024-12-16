#pragma once

#include "./point.h"
#include <map>
#include <unordered_map>
#include "navigator.h"

namespace graph
{
    typedef point::Point Point;
    typedef point::Direction Direction;

    typedef point::Point Point;
    typedef point::Direction Direction;

    typedef navigator::NavigatorPosition PointAndDir;

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