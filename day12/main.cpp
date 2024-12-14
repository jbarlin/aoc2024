#include "main.h"
#include "../utils/point.h"
#include "../utils/grab_bag.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <set>

namespace day12
{
    typedef std::vector<std::vector<uc>> puzzle;
    typedef std::vector<std::vector<bool>> bvec;

    typedef point::Point Point;

    struct running
    {
        ull area;
        ull perimeter;

        // Corners == sides!
        ull corner;
    };

    struct answer
    {
        ull part1;
        ull part2;
    };

    running fill_out_from_cell(const Point p, const puzzle &input, bvec &seen, const unsigned int size, const unsigned char curr)
    {
        running ans(0, 0, 0);
        const auto x = p.x;
        const auto y = p.y;
        if (!seen[x][y])
        {
            seen[x][y] = true;
            ans.area++;

            const auto nx_up = Point(x, y - 1);
            const auto nx_down = Point(x, y + 1);
            const auto nx_left = Point(x - 1, y);
            const auto nx_right = Point(x + 1, y);

            const bool UP = !((nx_up).inside(size) && (((nx_up)).extract_uchar_from_map(input) == curr));
            const bool UP_RIGHT = !((Point(x + 1, y - 1)).inside(size) && (((Point(x + 1, y - 1))).extract_uchar_from_map(input) == curr));
            const bool RIGHT = !((nx_right).inside(size) && (((nx_right)).extract_uchar_from_map(input) == curr));
            const bool DOWN_RIGHT = !((Point(x + 1, y + 1)).inside(size) && (((Point(x + 1, y + 1))).extract_uchar_from_map(input) == curr));
            const bool DOWN = !((nx_down).inside(size) && (((nx_down)).extract_uchar_from_map(input) == curr));
            const bool DOWN_LEFT = !((Point(x - 1, y + 1)).inside(size) && (((Point(x - 1, y + 1))).extract_uchar_from_map(input) == curr));
            const bool LEFT = !((nx_left).inside(size) && (((nx_left)).extract_uchar_from_map(input) == curr));
            const bool UP_LEFT = !((Point(x - 1, y - 1)).inside(size) && (((Point(x - 1, y - 1))).extract_uchar_from_map(input) == curr));

            if (DOWN)
            {
                ans.perimeter++;
            }
            else
            {
                auto b = fill_out_from_cell(nx_down, input, seen, size, curr);
                ans.area += b.area;
                ans.perimeter += b.perimeter;
                ans.corner += b.corner;
            }

            if (UP)
            {
                ans.perimeter++;
            }
            else
            {
                auto b = fill_out_from_cell(nx_up, input, seen, size, curr);
                ans.area += b.area;
                ans.perimeter += b.perimeter;
                ans.corner += b.corner;
            }

            if (RIGHT)
            {
                ans.perimeter++;
            }
            else
            {
                auto b = fill_out_from_cell(nx_right, input, seen, size, curr);
                ans.area += b.area;
                ans.perimeter += b.perimeter;
                ans.corner += b.corner;
            }

            if (LEFT)
            {
                ans.perimeter++;
            }
            else
            {
                auto b = fill_out_from_cell(nx_left, input, seen, size, curr);
                ans.area += b.area;
                ans.perimeter += b.perimeter;
                ans.corner += b.corner;
            }

            // For a corner, all three of them must either be:
            //  * Out of bounds; or
            //  * Not the same as this point

            // UPDATE: You also need the case where e.g. DOWN and LEFT are same as us, but not DOWN_LEFT
            // FURTHER UPDATE: Corners also include where DOWN and LEFT are different and DOWN_LEFT is same since we don't fence diagonally
            if (LEFT == UP && (UP_LEFT || UP != UP_LEFT))
            {
                ans.corner++;
            }
            if (UP == RIGHT && (UP_RIGHT || UP != UP_RIGHT))
            {
                ans.corner++;
            }
            if (RIGHT == DOWN && (DOWN_RIGHT || DOWN != DOWN_RIGHT))
            {
                ans.corner++;
            }
            if (DOWN == LEFT && (DOWN_LEFT || DOWN != DOWN_LEFT))
            {
                ans.corner++;
            }
        }
        return ans;
    }

    answer compute_answer(const puzzle &input)
    {
        const unsigned int size = input.size();
        answer ans(0, 0);
        bvec seen = nickels::create_falsy(size);

        for (unsigned int y = 0; y < size; y++)
        {
            for (unsigned int x = 0; x < size; x++)
            {
                const Point p(x, y);
                if (!seen[x][y])
                {
                    // New plot!
                    const auto value = p.extract_uchar_from_map(input);
                    auto b = fill_out_from_cell(p, input, seen, size, value);
                    ans.part1 += (b.area * b.perimeter);
                    ans.part2 += (b.area * b.corner);
                }
            }
        }

        return ans;
    }

    puzzle parse_puzzle(std::string path, unsigned int size)
    {
        std::vector<std::vector<uc>> out;
        out.reserve(size);

        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::string input_line;

        while (std::getline(input_file, input_line))
        {
            std::vector<uc> items;
            items.reserve(size);
            for (char c : input_line)
            {
                items.emplace_back(c);
            }
            out.emplace_back(items);
        }

        return out;
    }

    int main()
    {
        const puzzle test = parse_puzzle("./day12/test_input.txt", 10);

        std::cout << "\tRead in test input" << std::endl;
        ull test_expected_1 = 1930;
        answer test_answer = compute_answer(test);
        if (test_answer.part1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_answer.part1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        ull test_expected_2 = 1206;
        if (test_answer.part2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_answer.part2) << std::endl;
            return 1;
        }

        std::cout << "\tPassed tests" << std::endl;

        const puzzle actual = parse_puzzle("./day12/puzzle_input.txt", 140);
        std::cout << "\tRead in puzzle input" << std::endl;

        answer puzzle_answer = compute_answer(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(puzzle_answer.part1) << std::endl;
        std::cout << "\tPart 2 Answer - " << std::to_string(puzzle_answer.part2) << std::endl;

        assert(puzzle_answer.part1 == 1549354);
        assert(puzzle_answer.part2 == 937032);

        return 0;
    }
}