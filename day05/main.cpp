#include "./main.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

namespace day05
{

    unsigned long part2(const Puzzle &puzzle) {
        unsigned long sum = 0;
        auto books = puzzle.noncompliant_books();
        for(std::vector<unsigned char> book : books){
            const auto fixed = puzzle.fix_book(book);
            unsigned int element = book.size() / 2;
            sum += fixed[element];
        }
        return sum;
    }

    unsigned long part1(const Puzzle &puzzle) {
        unsigned long sum = 0;
        auto books = puzzle.compliant_books();
        for(std::vector<unsigned char> book : books) {
            unsigned int element = book.size() / 2;
            sum += book[element];
        }
        return sum;
    }

    Puzzle read_puzzle(std::string path){
        std::vector<Rule> rules;
        std::vector<std::vector<unsigned char>>  books;
        std::ifstream input_file(path);
        assert(input_file.is_open());

        const auto rule_delimiter = "|";
        const auto book_delimiter = ",";

        std::string curr_line;
        while (std::getline(input_file, curr_line))
        {
            if (curr_line.contains(rule_delimiter))
            {
                int delim_p = curr_line.find(rule_delimiter);
                // OK, this is a Rule
                unsigned char before = std::stoi(curr_line.substr(0, delim_p));
                curr_line.erase(0, delim_p + 1);
                unsigned char after = std::stoi(curr_line);
                Rule rule(before, after);
                rules.push_back(rule);
            }
            else if (curr_line.contains(book_delimiter))
            {
                std::vector<unsigned char> book;
                std::string delim = book_delimiter;
                while (curr_line.contains(book_delimiter))
                {
                    int delim_p = curr_line.find(book_delimiter);
                    unsigned char page = std::stoi(curr_line.substr(0, delim_p));
                    curr_line.erase(0, delim_p + 1);
                    book.push_back(page);
                }
                book.push_back(std::stoi(curr_line));
                books.push_back(book);
            }
        }
        input_file.close();
        return Puzzle(rules, books);
    }

    int main()
    {
        const Puzzle test_puzzle = read_puzzle("./day05/test_input.txt");
        std::cout << "\tRead in test input" << std::endl;
        long test_expected_1 = 143;
        long test_actual_1 = part1(test_puzzle);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        long test_expected_2 = 123;
        long test_actual_2 = part2(test_puzzle);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        std::cout << "\tPassed tests" << std::endl;
        const Puzzle actual_puzzle = read_puzzle("./day05/puzzle_input.txt");

        unsigned long conrad_pt1 = part1(actual_puzzle);
        unsigned long conrad_pt2 = part2(actual_puzzle);

        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;

        assert(conrad_pt1 == 4185);
        assert(conrad_pt2 == 4480);

        return 0;
    }
}