#include "./main.h"

#include <iostream>
#include <string_view>
#include <fstream>
#include <vector>
#include <sstream>
#include <cassert>

namespace day02
{
    bool pt1_line_safe(std::string line)
    {
        std::stringstream curr_line(line);
        std::string curr_look;
        int prev = 0;
        bool increasing = true;
        bool set_increasing = false;
        while (curr_line >> curr_look)
        {
            int curr = std::stoi(curr_look);
            if (prev != 0)
            {
                int diff = std::abs(prev - curr);
                // std::cout << "\tDBG: Diff " << std::to_string(diff) << std::endl;
                if (diff != 1 && diff != 2 && diff != 3)
                {
                    return false;
                }
                if (set_increasing)
                {
                    if ((prev > curr && increasing) || (curr > prev && !increasing))
                    {
                        return false;
                    }
                }
                else
                {
                    increasing = curr > prev;
                    set_increasing = true;
                }
            }
            prev = curr;
        }
        return true;
    }

    int part1(std::string puzzle_input_in)
    {
        std::ifstream input_file(puzzle_input_in);

        std::string s;
        int safe = 0;
        while (std::getline(input_file, s))
        {
            // std::cout << "DBG: LINE" << std::endl;
            if (pt1_line_safe(s))
            {
                safe++;
            }
        }
        input_file.close();
        return safe;
    }

    bool pt2_line_safe(std::string line)
    {
        if (pt1_line_safe(line))
        {
            return true;
        }
        // OK, now we can remove any 1 level, and then have it be safe on any of those...
        std::stringstream curr_line(line);
        std::vector<long> nums;
        long v = 0;
        while (curr_line >> v)
        {
            nums.push_back(v);
        }

        for (unsigned int i = 0; i < nums.size(); i++)
        {
            // Recreate the string, minus whatever "i" currently is, and test if that is safe
            std::string running_string;
            for (unsigned int j = 0; j < nums.size(); j++)
            {
                if (i != j)
                {
                    running_string += " ";
                    running_string += std::to_string(nums[j]);
                }
            }
            if (pt1_line_safe(running_string))
            {
                return true;
            }
        }
        return false;
    }

    int part2(std::string puzzle_input_in)
    {
        std::ifstream input_file(puzzle_input_in);

        std::string s;
        int safe = 0;
        while (std::getline(input_file, s))
        {
            // std::cout << "DBG: LINE" << std::endl;
            if (pt2_line_safe(s))
            {
                safe++;
            }
        }
        input_file.close();
        return safe;
    }

    int main()
    {

        int test_expected_1 = 2;
        int test_actual_1 = part1("./day02/test_input.txt");
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected 2, got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        int test_expected_2 = 4;
        int test_actual_2 = part2("./day02/test_input.txt");
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected 4, got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        const auto p1 = part1("./day02/puzzle_input.txt");
        std::cout << "\tThe part 1 answer is " << std::to_string(p1) << std::endl;
        const auto p2 = part2("./day02/puzzle_input.txt");
        std::cout << "\tThe part 2 answer is " << std::to_string(p2) << std::endl;
        assert(p1 == 510);
        assert(p2 == 553);
        return 0;
    }
}
