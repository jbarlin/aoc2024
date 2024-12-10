#include "main.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>

namespace day10
{

    typedef std::vector<std::vector<uc>> puzzle;

    ull part2(const puzzle &input)
    {   
        return 0;
    }

    ull part1(const puzzle &input)
    {
        return 0;
    }

    puzzle parse_puzzle(std::string path){

    }

    int main()
    {
        const puzzle test = parse_puzzle("./day09/test_input.txt");

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

        const puzzle actual = parse_puzzle("./day09/puzzle_input.txt");
        std::cout << "\tRead in puzzle input" << std::endl;

        ull conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        ull conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;
        return 0;
    }
}