#include "./graph.h"

#include <stack>
#include <queue>
#include <unordered_set>

namespace graph
{

#define graphtesting false

    struct PDandCost
    {
        unsigned long pos_x;
        unsigned long pos_y;
        char dir_x;
        char dir_y;
        unsigned long long cost;
        std::unordered_set<PointAndDir> seen_points;
        PDandCost(const PointAndDir &pd, const unsigned long long cost, const std::unordered_set<PointAndDir> &seen_points) : pos_x{pd.position.x}, pos_y{pd.position.y}, dir_x{pd.facing.x}, dir_y{pd.facing.y}, cost{cost}, seen_points{seen_points} {};
        const PointAndDir situation() const
        {
            return PointAndDir(Point(pos_x, pos_y), Direction(dir_x, dir_y));
        };

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

    const CostAndPathOfNavigation Graph::path_between(const PointAndDir &start, const Point &end) const
    {
        // PDandCost has: Position and Direction (the "node" we are at) and the cost incurred so far
        std::priority_queue<PDandCost, std::vector<PDandCost>, ComparePdAndCost> djikstra_queue;
        std::unordered_map<PointAndDir, unsigned long long> lowest_costs;
        std::unordered_set<PointAndDir> seen_points;

        const PDandCost start_cost(start, 0, seen_points);
        djikstra_queue.push(start_cost);
        lowest_costs.insert(std::pair(start, 0));

        std::vector<std::unordered_set<Point>> paths;
        unsigned long long final_cost = 0;

        while (!djikstra_queue.empty())
        {
            const auto curr_posn_cost = djikstra_queue.top();
            djikstra_queue.pop();
            std::unordered_set<PointAndDir> now_seen(curr_posn_cost.seen_points);
            now_seen.insert(curr_posn_cost.situation());
            const PointAndDir point_and_dir = curr_posn_cost.situation();

            if (point_and_dir.position == end)
            {
                // return curr_posn_cost.cost;
                if (paths.empty())
                {
                    final_cost = curr_posn_cost.cost;
                }

                if (final_cost == curr_posn_cost.cost)
                {
                    std::unordered_set<Point> points;
                    for (const auto &v : now_seen)
                    {
                        points.insert(v.position);
                    }
                    paths.push_back(points);
                }
                else
                {
                    assert(final_cost < curr_posn_cost.cost);
                    // OK, we've gone past the best ones!
                    return CostAndPathOfNavigation(final_cost, paths);
                }
            }

            const Point curr_pt = point_and_dir.position;

            const std::map<PointAndDir, unsigned int> next_possible_moves = graph.at(point_and_dir);
            for (const std::pair<PointAndDir, unsigned int> move : next_possible_moves)
            {
                const PointAndDir &next_pd = move.first;
                unsigned long long new_cost = curr_posn_cost.cost + move.second;

                if (now_seen.contains(next_pd))
                {
                    continue;
                }

                // Check if already visited with a lower cost
                if (lowest_costs.contains(next_pd) && lowest_costs[next_pd] < new_cost)
                {
                    continue;
                }

                lowest_costs.insert(std::pair(next_pd, new_cost));
                djikstra_queue.push(PDandCost(next_pd, new_cost, now_seen));
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
                    for (const Direction d : dirs)
                    {
                        if (curr == start && d == start_direction)
                        {
                            has_seen_start = true;
                        }
                        const PointAndDir me(curr, d);
#if graphtesting
                        std::cout << "\tNODE: " << me.as_string() << std::endl;
#endif
                        std::map<PointAndDir, unsigned int> possibles;
                        // OK, there is the left/right turn around

                        const auto l_turn = d.turn_left();
                        const PointAndDir l(curr, l_turn);
                        possibles.insert(std::pair(l, turn_cost));

                        const auto r_turn = d.turn_right();
                        const PointAndDir r(curr, r_turn);
                        possibles.insert(std::pair(r, turn_cost));

                        // And (maybe) moving forward for 1!
                        const Point moved = curr.move(d);
#if graphtesting
                        std::cout << "\t\tMOVED = " << moved.as_string() << " -> " << std::to_string(moved.extract_uchar_from_map(incoming_map)) << std::endl;
#endif
                        assert((moved.x == curr.x || moved.y == curr.y) && (!(moved.x == curr.x && moved.y == curr.y)));
                        if (moved.extract_uchar_from_map(incoming_map) != wall_char)
                        {
#if graphtesting
                            std::cout << "\t\tINSERTED!!!" << std::endl;
#endif
                            const PointAndDir mv(moved, d);
                            possibles.insert(std::pair(mv, 1));
                            has_seen_end = has_seen_end || moved == end;
                        }
#if graphtesting

                        for (const auto m : possibles)
                        {
                            std::cout << "\t\t-> " << m.first.as_string() << " $" << std::to_string(m.second) << std::endl;
                        }
#endif
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