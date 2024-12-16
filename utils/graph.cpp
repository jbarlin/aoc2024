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
        PDandCost(const PointAndDir pd, const unsigned long long cost) : pos_x{pd.position.x}, pos_y{pd.position.y}, dir_x{pd.facing.x}, dir_y{pd.facing.y}, cost{cost} {};
        const PointAndDir situation() const
        {
            return PointAndDir(Point(pos_x, pos_y), Direction(dir_x, dir_y));
        };
    };

    class ComparePdAndCost
    {
    public:
        bool operator()(const PDandCost &a, const PDandCost &b)
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
            const auto curr_posn_cost = djikstra_queue.top();
            djikstra_queue.pop();
            const PointAndDir point_and_dir = curr_posn_cost.situation();

            if (point_and_dir.position == end)
            {
                return curr_posn_cost.cost;
            }

            const std::map<PointAndDir, unsigned int> next_possible_moves = graph.at(point_and_dir);
            for (const std::pair<PointAndDir, unsigned int> move: next_possible_moves)
            {
                const PDandCost next(move.first, curr_posn_cost.cost + move.second);
                djikstra_queue.push(next);
            }
        }
        assert(false);
    }

    Graph convert_to_graph(const std::vector<std::vector<unsigned char>> &incoming_map, const Point start, const Direction start_direction, const Point end, unsigned char wall_char, unsigned int turn_cost)
    {

        std::map<PointAndDir, std::map<PointAndDir, unsigned int>> graph;
        Direction dirs[4] = {point::UP, point::DOWN, point::LEFT, point::RIGHT};
        bool has_seen_start = false;
        bool has_seen_end = false;
        for (unsigned int y = 0; y < incoming_map.size(); y++)
        {
            auto curr_x = incoming_map[y];
            for (unsigned int x = 0; x < curr_x.size(); x++)
            {
                const Point curr(x, y);
                if (curr.extract_uchar_from_map(incoming_map) != wall_char)
                {
                    for (const Direction &d : dirs)
                    {
                        if(curr == start && d == start_direction){
                            has_seen_start = true;
                        }
                        const PointAndDir me(curr, d);
                        std::map<PointAndDir, unsigned int> possibles;
                        // OK, there is the left/right/turn around
                        const PointAndDir left(me.position, me.facing.turn_left());
                        possibles.insert(std::pair(left, turn_cost));

                        const PointAndDir right(me.position, me.facing.turn_right());
                        possibles.insert(std::pair(right, turn_cost));

                        const PointAndDir around(me.position, me.facing.turn_around());
                        possibles.insert(std::pair(around, turn_cost * 2));

                        // And (maybe) moving forward for 1!
                        if (curr.can_move(d, incoming_map.size(), curr_x.size()))
                        {
                            const auto moved = curr.move(d);
                            if (moved.extract_uchar_from_map(incoming_map) != wall_char)
                            {
                                const PointAndDir mv(moved, d);
                                possibles.insert(std::pair(mv, 1));
                                has_seen_end = has_seen_end || moved == end;
                            }
                        }

                        graph.insert(std::pair(me, possibles));
                    }
                }
            }
        }
        
        std::cout << "Graph size: " << std::to_string(graph.size()) << std::endl;
        
        assert(has_seen_start);
        assert(has_seen_end);

        return Graph(graph);
    }
}