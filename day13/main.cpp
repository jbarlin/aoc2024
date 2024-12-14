#include "main.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>

#include "./machine.h"

namespace day13
{

    typedef std::vector<Machine> puzzle;

    ull part2(const puzzle &input)
    {
        ull count = 0;
        for(Machine m : input){
            count += m.cheapest_prize_win(3, 1, 100, 10000000000000);
        }
        return count;
    }

    ull part1(const puzzle &input)
    {
        ull count = 0;
        for(Machine m : input){
            count += m.cheapest_prize_win(3, 1, 100, 0);
        }
        return count;
    }

    puzzle parse_puzzle(std::string path, unsigned int num_file_lines)
    {
        std::vector<Machine> out;
        assert((num_file_lines + 1) % 4 == 0);
        out.reserve((num_file_lines + 1) / 4);

        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::string input_line;

        const auto plus_delim = "+";
        const auto comma_delim = ",";
        const auto equals_delim = "=";
        unsigned int number = 0;

        while (std::getline(input_file, input_line))
        {
            if (input_line.length() == 0)
            {
                continue;
            }
            else
            {
                // Button A: X+94, Y+34
                input_line.erase(0, input_line.find(plus_delim) + 1);
                const unsigned int a_btn_x = std::stoi(input_line.substr(0, input_line.find(comma_delim)));
                input_line.erase(0, input_line.find(plus_delim) + 1);
                const Point btn_a(a_btn_x, std::stoi(input_line));
                // Button B: X+22, Y+67
                assert(std::getline(input_file, input_line));
                input_line.erase(0, input_line.find(plus_delim) + 1);
                const unsigned int b_btn_x = std::stoi(input_line.substr(0, input_line.find(comma_delim)));
                input_line.erase(0, input_line.find(plus_delim) + 1);
                const Point btn_b(b_btn_x, std::stoi(input_line));
                // Prize: X=8400, Y=5400
                assert(std::getline(input_file, input_line));
                input_line.erase(0, input_line.find(equals_delim) + 1);
                const unsigned int p_x = std::stoi(input_line.substr(0, input_line.find(comma_delim)));
                input_line.erase(0, input_line.find(equals_delim) + 1);
                const Point p(p_x, std::stoi(input_line));
                out.emplace_back(Machine(btn_a, btn_b, p, number));
                number ++;
            }
        }

        input_file.close();
        return out;
    }

    int main()
    {
        const puzzle test = parse_puzzle("./day13/test_input.txt", 15);

        std::cout << "\tRead in test input" << std::endl;
        ull test_expected_1 = 480;
        ull test_actual_1 = part1(test);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed test - no part 2 again :'(" << std::endl;

        const puzzle actual = parse_puzzle("./day13/puzzle_input.txt", 1279);
        std::cout << "\tRead in puzzle input" << std::endl;

        ull conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        ull conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;

        assert(conrad_pt1 == 30413);
        assert(conrad_pt2 == 92827349540204);

        return 0;
    }
}