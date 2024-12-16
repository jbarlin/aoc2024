#include "./graph.h"

#include <stack>
#include <queue>

namespace graph
{

#define graphtesting true

    struct PDandCost
    {
        unsigned long pos_x;
        unsigned long pos_y;
        char dir_x;
        char dir_y;
        unsigned long long cost;
        unsigned long prev_x;
        unsigned long prev_y;
        PDandCost(const PointAndDir pd, const unsigned long long cost, Point prev) : pos_x{pd.position.x}, pos_y{pd.position.y}, dir_x{pd.facing.x}, dir_y{pd.facing.y}, cost{cost}, prev_x{prev.x}, prev_y{prev.y} {};
        const PointAndDir situation() const
        {
            return PointAndDir(Point(pos_x, pos_y), Direction(dir_x, dir_y));
        };

        const Point prev() const
        {
            return Point(prev_x, prev_y);
        }

        const std::string as_string() const
        {
            return "@" + Point(pos_x, pos_y).as_string() + " Facing " + Direction(dir_x, dir_y).as_string() + " Cost: " + std::to_string(cost);
        }
    };

    class ComparePdAndCost
    {
    public:
        bool operator()(const PDandCost &a, const PDandCost &b)
        {
            return a.cost > b.cost; // we want opposite sorting!!!
        }
    };

    const unsigned long long Graph::path_between(const PointAndDir &start, const Point &end) const
    {
        std::priority_queue<PDandCost, std::vector<PDandCost>, ComparePdAndCost> djikstra_queue;
        const PDandCost start_cost(start, 0, start.position);
        djikstra_queue.push(start_cost);
        unsigned long long iters = 0;
        while (djikstra_queue.size() > 0)
        {
            iters++;
            const auto curr_posn_cost = djikstra_queue.top();
            djikstra_queue.pop();
            const PointAndDir point_and_dir = curr_posn_cost.situation();

            if (point_and_dir.position == end)
            {
                return curr_posn_cost.cost;
            }

            const std::map<PointAndDir, unsigned int> next_possible_moves = graph.at(point_and_dir);
            for (const std::pair<PointAndDir, unsigned int> move : next_possible_moves)
            {
                if (move.first.position != curr_posn_cost.prev())
                {
                    const PDandCost next(move.first, curr_posn_cost.cost + move.second, point_and_dir.position);
                    djikstra_queue.push(next);
                }
            }
#if graphtesting
            std::cout << "\tDjikstra stack size: " << std::to_string(djikstra_queue.size()) << std::endl;
            std::cout << "\t\tcurr_posn_cost: " << curr_posn_cost.as_string() << std::endl;
#endif
            assert(djikstra_queue.size() < 5000);
            assert(iters < 5000);
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
                        if (curr == start && d == start_direction)
                        {
                            has_seen_start = true;
                        }
                        const PointAndDir me(curr, d);
                        std::map<PointAndDir, unsigned int> possibles;
                        // OK, there is the left/right/turn around

                        const auto l_turn = d.turn_left();
                        if (curr.can_move(l_turn, curr_x.size(), incoming_map.size()))
                        {
                            const auto moved = curr.move(l_turn);
assert((moved.x == curr.x || moved.y == curr.y) && (!(moved.x == curr.x && moved.y == curr.y))));
                            if (moved.extract_uchar_from_map(incoming_map) != wall_char)
                            {
                                const PointAndDir mv(moved, l_turn);
                                possibles.insert(std::pair(mv, turn_cost + 1));
                                has_seen_end = has_seen_end || moved == end;
                            }
                        }

                        const auto r_turn = d.turn_right();
                        if (curr.can_move(r_turn, curr_x.size(), incoming_map.size()))
                        {
                            const auto moved = curr.move(r_turn);
assert((moved.x == curr.x || moved.y == curr.y) && (!(moved.x == curr.x && moved.y == curr.y))));
                            if (moved.extract_uchar_from_map(incoming_map) != wall_char)
                            {
                                const PointAndDir mv(moved, r_turn);
                                possibles.insert(std::pair(mv, turn_cost + 1));
                                has_seen_end = has_seen_end || moved == end;
                            }
                        }

                        const auto a_turn = d.turn_around();
                        if (curr.can_move(a_turn, curr_x.size(), incoming_map.size()))
                        {
                            const auto moved = curr.move(a_turn);
assert((moved.x == curr.x || moved.y == curr.y) && (!(moved.x == curr.x && moved.y == curr.y))));
                            if (moved.extract_uchar_from_map(incoming_map) != wall_char)
                            {
                                const PointAndDir mv(moved, a_turn);
                                possibles.insert(std::pair(mv, turn_cost + turn_cost + 1));
                                has_seen_end = has_seen_end || moved == end;
                            }
                        }

                        // And (maybe) moving forward for 1!
                        if (curr.can_move(d, curr_x.size(), incoming_map.size()))
                        {
                            const auto moved = curr.move(d);
assert((moved.x == curr.x || moved.y == curr.y) && (!(moved.x == curr.x && moved.y == curr.y))));
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
#if graphtesting
        std::cout << "\tGraph size: " << std::to_string(graph.size()) << std::endl;
#endif
        assert(has_seen_start);
        assert(has_seen_end);

        return Graph(graph);
    }
}