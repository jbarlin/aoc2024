#include "main.h"
#include "droid.h"
#include "../utils/grab_bag.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>

namespace day14
{

    struct puzzle
    {
        const std::vector<Droid> droids;
        const unsigned int x_tiles;
        const unsigned int y_tiles;
    };

    std::vector<Droid> ticks(const std::vector<Droid> &input_droids, unsigned int ticks, const unsigned int max_x, const unsigned int max_y)
    {
        std::vector<Droid> resulting_droids;
        resulting_droids.reserve(input_droids.size());
        for (const Droid &d : input_droids)
        {
            const auto nd = d.after_ticks(ticks, max_x, max_y);
            resulting_droids.emplace_back(nd);
        }
        return resulting_droids;
    }

    ull part2(const puzzle &input)
    {
        // OK, this... isn't gonna be fun
        // OK, so this is +1 second already
        ull seconds = 100;

        const auto max_x = input.x_tiles;
        const auto max_y = input.y_tiles;

        while (seconds <= 1000000)
        {
            seconds++;
            // For something visual you'd have to be able to see all the droids right?
            auto seen = nickels::create_falsy(max_x, max_y);
            bool same_spot = false;
            for (const Droid &d : input.droids)
            {
                const auto nd = d.after_ticks(seconds, max_x, max_y);
                if (seen[nd.position.y][nd.position.x])
                {
                    same_spot = true;
                    break;
                }
                else
                {
                    seen[nd.position.y][nd.position.x] = true;
                }
            }
            if (!same_spot)
            {
                return seconds;
            }
        }
        assert(false);
        return 0;
    }

    std::pair<ull, std::vector<Droid>> part1(const puzzle &input)
    {
        ull top_left = 0;
        ull top_right = 0;
        ull bottom_left = 0;
        ull bottom_right = 0;

        std::vector<Droid> resulting_droids = ticks(input.droids, 100, input.x_tiles, input.y_tiles);

        const unsigned int mid_x = input.x_tiles / 2;
        const unsigned int mid_y = input.y_tiles / 2;
        for (const Droid &d : resulting_droids)
        {
            if (d.position.x < mid_x)
            {
                if (d.position.y < mid_y)
                {
                    top_left++;
                }
                else if (d.position.y > mid_y)
                {
                    bottom_left++;
                }
            }
            else if (d.position.x > mid_x)
            {
                if (d.position.y < mid_y)
                {
                    top_right++;
                }
                else if (d.position.y > mid_y)
                {
                    bottom_right++;
                }
            }
        }

        return std::make_pair(top_left * top_right * bottom_left * bottom_right, resulting_droids);
    }

    puzzle parse_puzzle(const std::string path, const unsigned int lines, const unsigned int x_tiles, const unsigned int y_tiles)
    {
        std::vector<Droid> out;
        out.reserve(lines);

        const auto equals_delim = "=";
        const auto comma_delim = ",";
        const auto space_delim = " ";

        std::ifstream input_file(path);
        assert(input_file.is_open());

        std::string input_line;

        unsigned int count = 0;

        while (std::getline(input_file, input_line))
        {
            // p=0,4 v=3,-3
            input_line.erase(0, input_line.find(equals_delim) + 1);
            const unsigned int posn_x = std::stoi(input_line.substr(0, input_line.find(comma_delim)));
            input_line.erase(0, input_line.find(comma_delim) + 1);
            const unsigned int posn_y = std::stoi(input_line.substr(0, input_line.find(space_delim)));
            // v
            input_line.erase(0, input_line.find(equals_delim) + 1);
            const signed int vec_x = std::stoi(input_line.substr(0, input_line.find(comma_delim)));
            input_line.erase(0, input_line.find(comma_delim) + 1);
            const signed int vec_y = std::stoi(input_line);
            const auto d = Droid(Point(posn_x, posn_y), Motion(vec_x, vec_y), count);
            out.emplace_back(d);
            count++;
        }

        puzzle result(out, x_tiles, y_tiles);
        return result;
    }

    int main()
    {
        const puzzle test = parse_puzzle("./day14/test_input.txt", 12, 11, 7);

        std::cout << "\tRead in test input" << std::endl;
        ull test_expected_1 = 12;
        std::pair<ull, std::vector<Droid>> test_actual_1 = part1(test);
        if (test_actual_1.first != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1.first) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests - only 1 test again" << std::endl;

        const puzzle actual = parse_puzzle("./day14/puzzle_input.txt", 500, 101, 103);
        std::cout << "\tRead in puzzle input" << std::endl;

        std::pair<ull, std::vector<Droid>> conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1.first) << std::endl;

        ull conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;

        assert(conrad_pt1.first == 232253028);
        assert(conrad_pt2 == 8179);

        return 0;
    }
}