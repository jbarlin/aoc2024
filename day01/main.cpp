#include "./main.h"

#include <iostream>
#include <string_view>
#include <fstream>
#include <vector>

namespace day01
{

    int main()
    {
        std::ifstream input_file("./day01/puzzle_input.txt");

        std::vector<long> left_list(6);
        std::vector<long> right_list(6);
        // The delim is three spaces
        std::string delimiter = "   ";

        std::string s;
        while (std::getline(input_file, s))
        {
            left_list.push_back(
                std::stol(s.substr(0, s.find(delimiter))));
            s.erase(0, s.find(delimiter) + delimiter.length());
            right_list.push_back(
                std::stol(s));
        }

        std::sort(left_list.begin(), left_list.end());
        std::sort(right_list.begin(), right_list.end());

        std::vector<std::pair<long, long>> pairs(left_list.size());
        for (unsigned i = 0; i < left_list.size(); i++)
        {
            pairs[i] = std::make_pair(left_list[i], right_list[i]);
        }

        unsigned long long diff = 0;
        for (const auto &item : pairs)
        {
            diff += (unsigned long long) std::abs(item.second - item.first);
        }

        std::cout << "\tThe part 1 answer is " << std::to_string(diff) << std::endl;

        unsigned long long similar = 0;
        for (const auto &item : left_list)
        {
            unsigned int mult = 0;

            for (const auto &rh : right_list)
            {
                mult += (rh == item) ? 1 : 0;
            }

            similar += (unsigned long long) (item * mult);
        }

        std::cout << "\tThe part 2 answer is " << std::to_string(similar) << std::endl;

        return 0;
    }
}