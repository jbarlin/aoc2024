#include "main.h"

#include "blinky.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>

namespace day11
{

    Inky parse_puzzle(std::string path){
        std::vector<ull> out;

        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::string input_line;

        std::getline(input_file, input_line);
        input_file.close();

        std::stringstream line(input_line);
        ull in;
        while(line >> in){
            out.push_back(in);
        }

        return out;
    }

    int main()
    {
        Inky test = parse_puzzle("./day11/test_input.txt");

        std::cout << "\tRead in test input" << std::endl;
        ull test_expected_1 = 55312;
        ull test_actual_1 = test.total_stones_after(25);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed only test... :'( Y no pt 2 test" << std::endl;

        Inky actual = parse_puzzle("./day11/puzzle_input.txt");
        std::cout << "\tRead in puzzle input" << std::endl;

        ull conrad_pt1 = actual.total_stones_after(25);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        ull conrad_pt2 = actual.total_stones_after(75);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;
        return 0;
    }
}