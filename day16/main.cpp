#include "main.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "../utils/graph.h"

namespace day16
{


    struct puzzle{
        const graph::Graph graph;
        const point::Point start;
        const point::Point end;
    };

    // typedef graph::Graph puzzle;

    ull part2(const puzzle &input)
    {
        return 0;
    }

    ull part1(const puzzle &input)
    {
        return input.graph.path_between(graph::PointAndDir(input.start, point::LEFT), input.end);
    }

    puzzle parse_puzzle(const std::string path, unsigned int square_size)
    {
        std::vector<std::vector<uc>> out;
        out.reserve(square_size);
        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::string input_line;

        unsigned int curr_y = 0;
        unsigned int curr_x = 0;
        unsigned int start_x = 0;
        unsigned int start_y = 0;
        unsigned int end_x = 0;
        unsigned int end_y = 0;

        while (std::getline(input_file, input_line))
        {
            curr_x = 0;
            std::vector<uc> row;
            row.reserve(square_size);
            for (char c : input_line)
            {

                if (c == '#')
                {
                    row.emplace_back(1);
                }
                else if (c == 'S')
                {
                    start_x = curr_x;
                    start_y = curr_y;
                    row.emplace_back(0);
                }
                else if (c == 'E')
                {
                    end_x = curr_x;
                    end_y = curr_y;
                    row.emplace_back(0);
                }
                else
                {
                    row.emplace_back(0);
                }
                curr_x++;
            }
            out.emplace_back(row);
            curr_y++;
        }

        const auto start = point::Point(start_x, start_y);
        const auto end = point::Point(end_x, end_y);

        const auto graph = graph::convert_to_graph(out, start, point::RIGHT, end, 1, 1000);
        return puzzle(graph, start, end);
    }

    int main()
    {
        const puzzle test = parse_puzzle("./day16/test_input.txt", 15);

        std::cout << "\tRead in test input" << std::endl;
        ull test_expected_1 = 0;
        ull test_actual_1 = part1(test);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        ull test_expected_2 = 0;
        ull test_actual_2 = part2(test);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        std::cout << "\tPassed tests" << std::endl;

        const puzzle actual = parse_puzzle("./day16/puzzle_input.txt", 140);
        std::cout << "\tRead in puzzle input" << std::endl;

        ull conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        ull conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;
        return 0;
    }
}