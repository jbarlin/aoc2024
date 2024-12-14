#pragma once

#include "./rule.h"

namespace day05
{
    class Puzzle
    {
    private:
        const std::vector<Rule> rules;
        const std::vector<std::vector<unsigned char>> books;
    public:
        Puzzle(const std::vector<Rule> &rules, const std::vector<std::vector<unsigned char>> &books) : rules{rules}, books{books} {};
        const std::vector<std::vector<unsigned char>> compliant_books() const;
        const std::vector<std::vector<unsigned char>> noncompliant_books() const;
        const std::vector<unsigned char> fix_book(const std::vector<unsigned char> &book) const;
    };
}