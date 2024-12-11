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

    Puzzle::Puzzle(std::string path)
    {
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
    }

    std::vector<std::vector<unsigned char>> Puzzle::compliant_books()
    {
        std::vector<std::vector<unsigned char>> answer;
        for (std::vector<unsigned char> book : books)
        {
            if (satisfies_all(book, rules))
            {
                answer.push_back(book);
            }
        }
        return answer;
    };

    std::vector<std::vector<unsigned char>> Puzzle::noncompliant_books()
    {
        std::vector<std::vector<unsigned char>> answer;

        for (std::vector<unsigned char> book : books)
        {
            if (!satisfies_all(book, rules))
            {
                answer.push_back(book);
            }
        }
        return answer;
    };

    void Puzzle::fix_book(std::vector<unsigned char> &book)
    {
        while (!satisfies_all(book, rules))
        {
            for (Rule rule : rules)
            {
                rule.make_happy(book);
            }
        }
    }

}