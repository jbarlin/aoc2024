#include "./main.h"
#include "point.h"
#include "map.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>
#include <cassert>
#include <set>

namespace day08
{

    unsigned int part2(const Map &map)
    {
        std::set<Point> antinodes;
        for (unsigned int c = 0; c < map.map.size(); c++)
        {
            const std::vector<Point> characters_points = map.map[c];
            antinodes.insert(characters_points.begin(), characters_points.end());
            for (unsigned int outer = 0; outer < characters_points.size() - 1; outer++)
            {
                Point a_pt = characters_points[outer];
                for (unsigned int inner = outer + 1; inner < characters_points.size(); inner++)
                {
                    Point b_pt = characters_points[inner];

                    const std::set<Point> c_past_b = a_pt.create_line(b_pt, map.square_size);
                    const std::set<Point> c_past_a = b_pt.create_line(a_pt, map.square_size);

                    antinodes.insert(c_past_b.begin(), c_past_b.end());
                    antinodes.insert(c_past_a.begin(), c_past_a.end());
                }
            }
        }
        return antinodes.size();
    }

    unsigned int part1(const Map &map)
    {
        std::set<Point> antinodes;
        for (unsigned int c = 0; c < map.map.size(); c++)
        {
            auto v = map.map[c];
            for (unsigned int outer = 0; outer < v.size() - 1; outer++)
            {
                Point a_pt = v[outer];
                for (unsigned int inner = outer + 1; inner < v.size(); inner++)
                {
                    Point b_pt = v[inner];

                    auto c_past_b = a_pt.continue_to_next_point(b_pt, map.square_size);
                    if (c_past_b.has_value())
                    {
                        auto c = c_past_b.value();
                        antinodes.insert(c);
                    }
                    auto c_past_a = b_pt.continue_to_next_point(a_pt, map.square_size);
                    if (c_past_a.has_value())
                    {
                        auto c = c_past_a.value();
                        antinodes.insert(c);
                    }
                }
            }
        }
        return antinodes.size();
    }

    Map parse_puzzle(const std::string &path, const unsigned int size)
    {
        std::string seen = "";
        std::vector<std::vector<Point>> map;

        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::string input_line;
        unsigned int y = 0;
        unsigned int x = 0;
        while (std::getline(input_file, input_line))
        {
            x = 0;
            for (unsigned char c : input_line)
            {
                if (isalnum(c))
                {
                    if (!seen.contains(c))
                    {
                        seen += c;
                        map.push_back(std::vector<Point>());
                    }
                    unsigned int ix = seen.find(c);
                    const Point p(x, y);
                    map[ix].push_back(p);
                }

                x++;
            }
            y++;
        }

        return Map(map, size);
    }

    int main()
    {
        const Map test = parse_puzzle("./day08/test_input.txt", 12);
        // assert(test.map.size() == 2 && ((test.map[0].size() == 3 && test.map[1].size() == 4) || (test.map[0].size() == 4 && test.map[1].size() == 3)));
        std::cout << "\tRead in test input" << std::endl;
        unsigned int test_expected_1 = 14;
        unsigned int test_actual_1 = part1(test);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        unsigned int test_expected_2 = 34;
        unsigned int test_actual_2 = part2(test);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }
        std::cout << "\tPassed tests" << std::endl;
        // 3350727456176
        const Map actual = parse_puzzle("./day08/puzzle_input.txt", 50);
        std::cout << "\tRead in puzzle input" << std::endl;

        unsigned int conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        unsigned int conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;
        return 0;
    }
}