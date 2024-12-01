#include "./main.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

namespace day05
{

    unsigned long part2(Puzzle puzzle) {
        unsigned long sum = 0;
        auto books = puzzle.noncompliant_books();
        for(std::vector<unsigned char> book : books){
            puzzle.fix_book(book);
            unsigned int element = book.size() / 2;
            sum += book[element];
        }
        return sum;
    }

    unsigned long part1(Puzzle puzzle) {
        unsigned long sum = 0;
        auto books = puzzle.compliant_books();
        for(std::vector<unsigned char> book : books) {
            unsigned int element = book.size() / 2;
            sum += book[element];
        }
        return sum;
    }

    int main()
    {
        const Puzzle test_puzzle("./day05/test_input.txt");
        std::cout << "\tRead in test input" << std::endl;
        long test_expected_1 = 143;
        long test_actual_1 = part1(test_puzzle);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        long test_expected_2 = 123;
        long test_actual_2 = part2(test_puzzle);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        std::cout << "\tPassed tests" << std::endl;
        const Puzzle actual_puzzle("./day05/puzzle_input.txt");

        unsigned long conrad_pt1 = part1(actual_puzzle);
        unsigned long conrad_pt2 = part2(actual_puzzle);

        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;

        return 0;
    }
}