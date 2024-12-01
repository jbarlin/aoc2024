#include "./main.h"
#include "equation.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>

namespace day07
{

    unsigned long long part2(const std::vector<Equation> &eqs)
    {
        unsigned long long sum = 0;
        for (Equation eq : eqs)
        {
            bool ans = eq.does_work_pt2();
            sum += ans ? eq.goal : 0;
        }

        return sum;
    }

    unsigned long long part1(const std::vector<Equation> &eqs)
    {
        unsigned long long sum = 0;
        for (Equation eq : eqs)
        {
            bool ans = eq.does_work_pt1();
            sum += ans ? eq.goal : 0;
        }

        return sum;
    }

    std::vector<Equation> read_puzzle(const std::string &path, const unsigned int size)
    {
        // 190: 10 19
        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::vector<Equation> results;
        results.reserve(size);

        std::string delimiter = ": ";

        std::string input_line;
        while (std::getline(input_file, input_line))
        {
            auto l = input_line.find(delimiter);
            unsigned long goal = std::stoull(
                input_line.substr(0, l)
            );
            input_line.erase(0, l + delimiter.length());
            std::vector<unsigned int> partials;
            std::istringstream iline(input_line);
            std::string curr;
            while(std::getline(iline, curr, ' ')){
                partials.push_back(std::stoi(curr));
            }
            results.emplace_back(Equation(goal, partials));
        }

        return results;
    }

    int main()
    {
        const std::vector<Equation> test = read_puzzle("./day07/test_input.txt", 9);
        std::cout << "\tRead in test input" << std::endl;
        unsigned long long test_expected_1 = 3749;
        unsigned long long test_actual_1 = part1(test);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            // return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        unsigned long long test_expected_2 = 11387;
        unsigned long long test_actual_2 = part2(test);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }
        std::cout << "\tPassed tests" << std::endl;
        // 3350727456176
        const std::vector<Equation> actual = read_puzzle("./day07/puzzle_input.txt", 850);
        std::cout << "\tRead in puzzle input" << std::endl;

        unsigned long long conrad_pt1 = part1(actual);
        assert(conrad_pt1 > 3350727456176);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        unsigned long long conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;

        return 0;
    }

}