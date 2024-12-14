#include "./main.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

namespace day04
{

    const unsigned char NO = 0;
    const unsigned char X = 1;
    const unsigned char M = 2;
    const unsigned char A = 4;
    const unsigned char S = 8;

    std::vector<std::vector<unsigned char>> create_word_search(std::string path, unsigned int square_size)
    {
        std::ifstream input_file(path);
        assert(input_file.is_open());

        std::vector<std::vector<unsigned char>> word_search;
        word_search.reserve(square_size);

        std::string input_line;
        int line_length = 0;
        while (std::getline(input_file, input_line))
        {
            if (line_length == 0)
            {
                line_length = input_line.size();
            }
            // Read in each character into a vector
            std::vector<unsigned char> line_reps;
            line_reps.reserve(line_length);
            for (char &c : input_line)
            {
                switch (c)
                {
                case 'X':
                    line_reps.emplace_back(X);
                    break;
                case 'M':
                    line_reps.emplace_back(M);
                    break;
                case 'A':
                    line_reps.emplace_back(A);
                    break;
                case 'S':
                    line_reps.emplace_back(S);
                    break;
                default:
                    line_reps.emplace_back(NO);
                    break;
                }
            }
            line_reps.shrink_to_fit();
            word_search.emplace_back(line_reps);
        }
        word_search.shrink_to_fit();
        input_file.close();
        return word_search;
    }

    unsigned char get_from_puzzle(const std::vector<std::vector<unsigned char>> &word_search, unsigned int want_x, unsigned int want_y)
    {
        return word_search[want_y][want_x];
    }

    unsigned char p1_right_to_left(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_x >= 3 &&
                       get_from_puzzle(word_search, curr_x - 1, curr_y) == M &&
                       get_from_puzzle(word_search, curr_x - 2, curr_y) == A &&
                       get_from_puzzle(word_search, curr_x - 3, curr_y) == S
                   ? 1
                   : 0;
    }

    unsigned char p1_left_to_right(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_x + 3 < size &&
                       get_from_puzzle(word_search, curr_x + 1, curr_y) == M &&
                       get_from_puzzle(word_search, curr_x + 2, curr_y) == A &&
                       get_from_puzzle(word_search, curr_x + 3, curr_y) == S
                   ? 1
                   : 0;
    }

    unsigned char p1_top_to_bottom(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_y + 3 < size &&
                       get_from_puzzle(word_search, curr_x, curr_y + 1) == M &&
                       get_from_puzzle(word_search, curr_x, curr_y + 2) == A &&
                       get_from_puzzle(word_search, curr_x, curr_y + 3) == S
                   ? 1
                   : 0;
    }

    unsigned char p1_bottom_to_top(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_y >= 3 &&
                       get_from_puzzle(word_search, curr_x, curr_y - 1) == M &&
                       get_from_puzzle(word_search, curr_x, curr_y - 2) == A &&
                       get_from_puzzle(word_search, curr_x, curr_y - 3) == S
                   ? 1
                   : 0;
    }

    unsigned char p1_diag_top_left(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_x + 3 < size &&
                       curr_y + 3 < size &&
                       get_from_puzzle(word_search, curr_x + 1, curr_y + 1) == M &&
                       get_from_puzzle(word_search, curr_x + 2, curr_y + 2) == A &&
                       get_from_puzzle(word_search, curr_x + 3, curr_y + 3) == S
                   ? 1
                   : 0;
    }

    unsigned char p1_diag_bottom_left(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_x + 3 < size &&
                       curr_y >= 3 &&
                       get_from_puzzle(word_search, curr_x + 1, curr_y - 1) == M &&
                       get_from_puzzle(word_search, curr_x + 2, curr_y - 2) == A &&
                       get_from_puzzle(word_search, curr_x + 3, curr_y - 3) == S
                   ? 1
                   : 0;
    }

    unsigned char p1_diag_top_right(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_x >= 3 &&
                       curr_y + 3 < size &&
                       get_from_puzzle(word_search, curr_x - 1, curr_y + 1) == M &&
                       get_from_puzzle(word_search, curr_x - 2, curr_y + 2) == A &&
                       get_from_puzzle(word_search, curr_x - 3, curr_y + 3) == S
                   ? 1
                   : 0;
    }

    unsigned char p1_diag_bottom_right(const std::vector<std::vector<unsigned char>> &word_search, unsigned int curr_x, unsigned int curr_y, unsigned int size)
    {
        return curr_x >= 3 &&
                       curr_y >= 3 &&
                       get_from_puzzle(word_search, curr_x - 1, curr_y - 1) == M &&
                       get_from_puzzle(word_search, curr_x - 2, curr_y - 2) == A &&
                       get_from_puzzle(word_search, curr_x - 3, curr_y - 3) == S
                   ? 1
                   : 0;
    }

    unsigned long part1(const std::vector<std::vector<unsigned char>> &word_search, unsigned int size)
    {

        unsigned long count = 0;
        // OK, now we need to search through the word_search
        for (unsigned int curr_y = 0; curr_y < size; curr_y++)
        {
            for (unsigned int curr_x = 0; curr_x < size; curr_x++)
            {
                if (get_from_puzzle(word_search, curr_x, curr_y) == X)
                {
                    count += p1_left_to_right(word_search, curr_x, curr_y, size);
                    count += p1_right_to_left(word_search, curr_x, curr_y, size);
                    count += p1_top_to_bottom(word_search, curr_x, curr_y, size);
                    count += p1_bottom_to_top(word_search, curr_x, curr_y, size);
                    count += p1_diag_top_left(word_search, curr_x, curr_y, size);
                    count += p1_diag_bottom_left(word_search, curr_x, curr_y, size);
                    count += p1_diag_top_right(word_search, curr_x, curr_y, size);
                    count += p1_diag_bottom_right(word_search, curr_x, curr_y, size);
                }
            }
        }

        return count;
    }

    unsigned long part2(const std::vector<std::vector<unsigned char>> &word_search, unsigned int size)
    {

        unsigned long count = 0;
        // OK, now we need to search through the word_search
        for (unsigned int curr_y = 1; curr_y < size - 1; curr_y++)
        {
            std::vector<unsigned char> curr_line = word_search[curr_y];
            for (unsigned int curr_x = 1; curr_x < size - 1; curr_x++)
            {
                if (get_from_puzzle(word_search, curr_x, curr_y) == A)
                {
                    // I am at "A"
                    unsigned char tl = get_from_puzzle(word_search, curr_x - 1, curr_y - 1);
                    unsigned char bl = get_from_puzzle(word_search, curr_x - 1, curr_y + 1);
                    unsigned char tr = get_from_puzzle(word_search, curr_x + 1, curr_y - 1);
                    unsigned char br = get_from_puzzle(word_search, curr_x + 1, curr_y + 1);
                    /*
                        MS  SM  SS  MM
                        MS  SM  MM  SS
                    */
                    count += tl == M && br == S && bl == M && tr == S ? 1 : 0;
                    count += tl == S && br == M && bl == S && tr == M ? 1 : 0;
                    count += tl == M && tr == M && bl == S && br == S ? 1 : 0;
                    count += tl == S && tr == S && bl == M && br == M ? 1 : 0;
                }
            }
        }

        return count;
    }

    int main()
    {

        std::vector<std::vector<unsigned char>> test_input = create_word_search("./day04/test_input.txt", 10);
        std::cout << "\tRead in test input" << std::endl;
        long test_expected_1 = 18;
        long test_actual_1 = part1(test_input, 10);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        long test_expected_2 = 9;
        long test_actual_2 = part2(test_input, 10);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }
        std::cout << "\tPassed tests" << std::endl;
        std::vector<std::vector<unsigned char>> puzzle_input = create_word_search("./day04/puzzle_input.txt", 140);
        std::cout << "\tRead in puzzle input" << std::endl;

        unsigned long conrad_pt1 = part1(puzzle_input, 140);
        unsigned long conrad_pt2 = part2(puzzle_input, 140);

        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;

        assert(conrad_pt1 == 2545);
        assert(conrad_pt2 == 1886);

        return 0;
    }
}