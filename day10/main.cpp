#include "main.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "topography.h"

namespace day10
{

    typedef Topography puzzle;

    ull part2(const puzzle &input)
    {
        return input.score_rating();
    }

    ull part1(const puzzle &input)
    {
        return input.score_trailheads();
    }

    puzzle parse_puzzle(std::string path, unsigned int square_size)
    {
        std::vector<std::vector<unsigned char>> result;
        result.reserve(square_size);
        std::vector<Point> zeros;

        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::string input_line;
        unsigned int y = 0;
        unsigned int x = 0;
        while (std::getline(input_file, input_line))
        {
            x = 0;
            std::vector<uc> cells;
            cells.reserve(square_size);
            for (char c : input_line)
            {
                if (c == '.')
                {
                    cells.emplace_back(11);
                }
                else
                {
                    uc value = c - '0';
                    if (value == 0)
                    {
                        zeros.push_back(Point(x, y));
                    }
                    cells.emplace_back(value);
                }
                x++;
            }
            result.emplace_back(cells);
            y++;
        }

        return puzzle(result, zeros, result.size());
    }

    int main()
    {
        const puzzle test = parse_puzzle("./day10/test_input.txt", 8);

        std::cout << "\tRead in test input" << std::endl;
        ull test_expected_1 = 36;
        ull test_actual_1 = part1(test);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        ull test_expected_2 = 81;
        ull test_actual_2 = part2(test);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        std::cout << "\tPassed tests" << std::endl;

        const puzzle actual = parse_puzzle("./day10/puzzle_input.txt", 45);
        std::cout << "\tRead in puzzle input" << std::endl;

        ull conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        ull conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;
        return 0;
    }
}