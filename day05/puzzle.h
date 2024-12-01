#pragma once

#include "./rule.h"

namespace day05
{
    class Puzzle
    {
    private:
        std::vector<Rule> rules;
        std::vector<std::vector<unsigned char>> books;
    public:
        Puzzle(std::string input_file);
        std::vector<std::vector<unsigned char>> compliant_books();
        std::vector<std::vector<unsigned char>> noncompliant_books();
        void fix_book(std::vector<unsigned char> &book);
    };
}