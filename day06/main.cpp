#include "./main.h"
#include "./puzzle.h"

#include <cassert>
#include <set>
#include <fstream>
#include <memory>
#include "../utils/grab_bag.h"

namespace day06
{

    const Direction UP = point::UP;

    unsigned long part2(const Puzzle& puzzle, const std::set<Point> &points_walked)
    {
        unsigned long blockers = 0;
        for (Point where_to_add_blocker : points_walked)
        {
            if (where_to_add_blocker == puzzle.start_point())
            {
                continue;
            }
            Puzzle added = puzzle.with_new_obsticle_at(where_to_add_blocker);
            const WalkResult orig(puzzle.start_point(), 0, UP, std::set<Point>());
            auto ref = std::ref(orig);
            
            // bool visited[puzzle.size][puzzle.size][4] = {false};
            // std::vector<std::vector<std::vector<bool>>> visited(puzzle.size, std::vector<std::vector<bool>>(puzzle.size, std::vector<bool>(4, false))); 
            // std::vector<bool> visited(puzzle.size * puzzle.size * 4, false);
            std::unique_ptr<bool[]> visited = std::make_unique<bool[]>(puzzle.size * puzzle.size * 4);
            
            while (ref.get().stop.has_value())
            {
                const WalkResult nxt = added.misty_step_and_turn_right(ref.get().stop.value(), ref.get().facing);
                if(nxt.stop.has_value()){
                    const Point pt = nxt.stop.value();
                    const Direction d = nxt.facing;
                    const size_t visited_ix = puzzle.size * 4 * pt.x + pt.y * 4 + d.as_index();
                    if(visited[visited_ix]){
                        blockers++;
                        break;
                    }
                    visited[visited_ix] = true;
                }

                ref = std::ref(nxt);
            }
        }
        return blockers;
    }

    std::set<Point> part1(Puzzle puzzle)
    {
        // OK, let's try and walk somewhere!
        std::set<Point> points;
        auto start = puzzle.start_point();
        points.insert(start);
        WalkResult orig(start, 0, UP, points);
        auto ref = std::ref(orig);
        while (ref.get().stop.has_value())
        {
            auto pt = ref.get().stop.value();
            WalkResult nxt = puzzle.walk_and_turn_right(pt, ref.get().facing);
            points.insert(nxt.walked.begin(), nxt.walked.end());
            ref = std::ref(nxt);
        }
        return points;
    }

    Puzzle make_puzzle(const std::string filename, const unsigned int size)
    {
        std::ifstream input_file(filename);
        assert(input_file.is_open());

        std::vector<std::vector<unsigned char>> map;
        map.reserve(size);

        std::string curr_line;
        while (std::getline(input_file, curr_line))
        {
            std::vector<unsigned char> line_reps;
            line_reps.reserve(size);
            for (char c : curr_line)
            {
                switch (c)
                {
                case '^':
                    line_reps.emplace_back(2);
                    break;
                case '#':
                    line_reps.emplace_back(1);
                    break;
                default:
                    line_reps.emplace_back(0);
                    break;
                }
            }
            map.emplace_back(line_reps);
        }
        input_file.close();
        for (unsigned int y = 0; y < size; y++)
        {
            for (unsigned int x = 0; x < size; x++)
            {
                if (map[y][x] == 2)
                {
                    return Puzzle(map, std::pair(x, y), size);
                }
            }
        }
        assert(false);
    }

    int main()
    {
        Puzzle test_puzzle = make_puzzle("./day06/test_input.txt", 10);
        std::cout << "\tRead in test input" << std::endl;
        unsigned long test_expected_1 = 41;
        const std::set<Point> test_actual_1 = part1(test_puzzle);
        unsigned long test_1_actual_size = test_actual_1.size();
        if (test_1_actual_size != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_1_actual_size) << std::endl;
            return 1;
        }

        unsigned long test_expected_2 = 6;
        unsigned long test_actual_2 = part2(test_puzzle, test_actual_1);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        std::cout << "\tPassed tests" << std::endl;
        const Puzzle actual_puzzle = make_puzzle("./day06/puzzle_input.txt", 130);

        const std::set<Point> conrad_pt1 = part1(actual_puzzle);
        unsigned long pt1 = conrad_pt1.size();
        std::cout << "\tPart 1 Answer - " << std::to_string(pt1) << std::endl;
        assert(pt1 == 5329);

        unsigned long conrad_pt2 = part2(actual_puzzle, conrad_pt1);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;
        assert(conrad_pt2 == 2162);

        return 0;
    }
}