#include "./puzzle.h"
#include <fstream>
#include <cassert>
#include <ranges>

namespace day05
{
    bool satisfies_all(const std::vector<unsigned char> &book, const std::vector<Rule> &rules)
    {
        return std::all_of(
            rules.cbegin(),
            rules.cend(),
            [&book](Rule rule)
            {
                return rule.satisfied(book);
            });
    }

    const std::vector<std::vector<unsigned char>> Puzzle::compliant_books() const
    {
        std::vector<std::vector<unsigned char>> answer;
        for (const std::vector<unsigned char> &book : books)
        {
            if (satisfies_all(book, rules))
            {
                answer.push_back(book);
            }
        }
        return answer;
    };

    const std::vector<std::vector<unsigned char>> Puzzle::noncompliant_books() const
    {
        std::vector<std::vector<unsigned char>> answer;

        for (const std::vector<unsigned char> &book : books)
        {
            if (!satisfies_all(book, rules))
            {
                answer.push_back(book);
            }
        }
        return answer;
    };

    const std::vector<unsigned char> Puzzle::fix_book(const std::vector<unsigned char> &book) const
    {
        std::vector<unsigned char> nbook = book;
        while (!satisfies_all(nbook, this->rules))
        {
            for (Rule rule : rules)
            {
                rule.make_happy(nbook);
            }
        }
        return nbook;
    }

}