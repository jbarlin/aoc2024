#include "./graph.h"

#include <stack>
#include <queue>

namespace graph
{

    struct PDandCost
    {
        unsigned long pos_x;
        unsigned long pos_y;
        char dir_x;
        char dir_y;
        unsigned long long cost;
        PDandCost(const PointAndDir pd, const unsigned long long cost): pos_x{pd.position.x}, pos_y{pd.position.y},dir_x{pd.facing.x},dir_y{pd.facing.y}, cost{cost}{};
        const PointAndDir situation() const {
            return PointAndDir(Point(pos_x, pos_y), Direction(dir_x, dir_y));
        };
    };

    class ComparePdAndCost
    {
    public:
        bool operator()(const PDandCost& a, const PDandCost& b)
        {
            return a.cost < b.cost;
        }
    };

    const unsigned long long Graph::path_between(const PointAndDir &start, const Point &end) const
    {
        std::priority_queue<PDandCost, std::vector<PDandCost>, ComparePdAndCost> djikstra_queue;
        const PDandCost start_cost(start, 0);
        djikstra_queue.push(start_cost);
        while (djikstra_queue.size() > 0)
        {
            const auto curr_sit = djikstra_queue.top();
            djikstra_queue.pop();
            for (const auto &nx : this->graph.at(curr_sit.situation()))
            {
                if (nx.first.position == end)
                {
                    return curr_sit.cost + nx.second;
                }
                else
                {
                    const PDandCost to_go(nx.first, curr_sit.cost + nx.second);
                    djikstra_queue.push(to_go);
                }
            }
        }
        assert(false);
    }

    Graph convert_to_graph(const std::vector<std::vector<unsigned char>> &incoming_map, const Point start, const Direction start_direction, const Point end, unsigned char wall_char, unsigned int turn_cost)
    {

        std::map<PointAndDir, std::map<PointAndDir, unsigned int>> graph;
        std::stack<PointAndDir> stack;
        stack.push(PointAndDir(start, start_direction));
        while (stack.size() > 0)
        {
            const auto curr_situation = stack.top();
            stack.pop();
            if (graph.contains(curr_situation))
            {
                // Already handled - don't re-handle!
                continue;
            }
            // OK, so options are:
            //  1. progress forward
            //  2. turn left (and incur the cost)
            //  3. turn right (and incur the cost)
            //  4. turn around (and incur the cost * 2)
            if (curr_situation.position.can_move(curr_situation.facing, incoming_map.size(), incoming_map.size()))
            {
                // OK, we can get that object!
                const auto moved = curr_situation.position.move(curr_situation.facing);
                if (moved.extract_uchar_from_map(incoming_map) != wall_char)
                {
                    const auto next = PointAndDir(moved, curr_situation.facing);
                    graph[curr_situation][next] = 1;
                    stack.push(next);
                }
            }
            const PointAndDir left(curr_situation.position, curr_situation.facing.turn_left());
            stack.push(left);
            graph[curr_situation][left] = turn_cost;

            const PointAndDir right(curr_situation.position, curr_situation.facing.turn_right());
            stack.push(right);
            graph[curr_situation][right] = turn_cost;

            const PointAndDir around(curr_situation.position, curr_situation.facing.turn_around());
            stack.push(around);
            graph[curr_situation][around] = turn_cost * 2;
        }

        return Graph(graph);
    }
}