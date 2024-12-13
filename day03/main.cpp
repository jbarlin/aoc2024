#include "./main.h"
#include "./inputs.h"

#include <iostream>
#include <regex>
#include <cassert>

namespace day03
{

    long part1(std::string input)
    {

        // (mul\((\d{1,3}),(\d{1,3})\))
        // Grouped into the two numbers
        std::regex top_level_regex("(mul\\((\\d{1,3}),(\\d{1,3})\\))");

        const std::vector<std::smatch> top_level_matches{
            std::sregex_iterator(C_ALL(input), top_level_regex),
            std::sregex_iterator{}};

        assert(top_level_matches.size() > 3);

        long sum = 0;
        for (std::smatch top_match : top_level_matches)
        {
            int first_field = std::stoi(top_match[2]);
            int second_field = std::stoi(top_match[3]);
            sum += (first_field * second_field);
        }

        return sum;
    }

    long part2(std::string input)
    {

        // (mul\((\d{1,3}),(\d{1,3})\))
        // Grouped into the two numbers
        std::regex top_level_regex("(mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don\\'t\\(\\))");

        const std::vector<std::smatch> top_level_matches{
            std::sregex_iterator(C_ALL(input), top_level_regex),
            std::sregex_iterator{}};

        assert(top_level_matches.size() > 3);

        long sum = 0;
        bool enabled = true;
        for (std::smatch top_match : top_level_matches)
        {

            if (top_match[0] == "do()")
            {
                enabled = true;
            }
            else if (top_match[0] == "don't()")
            {
                enabled = false;
            }
            else if (enabled)
            {
                int first_field = std::stoi(top_match[2]);
                int second_field = std::stoi(top_match[3]);
                sum += (first_field * second_field);
            }
        }

        return sum;
    }

    int main()
    {
        auto test_input = day03inputs::get_file_contents("./day03/test_input.txt");
        long test_expected_1 = 161;
        long test_actual_1 = part1(test_input);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        long test_expected_2 = 48;
        long test_actual_2 = part2(test_input);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        auto puzzle_input = day03inputs::get_file_contents("./day03/puzzle_input.txt");
        const auto p1 = part1(puzzle_input);
        std::cout << "\t Part 1 Answer - " << std::to_string(p1) << std::endl;
        const auto p2 = part2(puzzle_input);
        std::cout << "\t Part 2 Answer - " << std::to_string(p2) << std::endl;
        assert(p1 == 171183089);
        assert(p2 == 63866497);

        return 0;
    }
}