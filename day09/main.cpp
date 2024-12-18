#include "main.h"

namespace day09
{
    ull part2(const Disk &disk)
    {
        const Disk defragmented = disk.defragment_contigous();
        return defragmented.checksum();
    }

    ull part1(const Disk &disk)
    {
        const Disk defragmented = disk.defragment();
        return defragmented.checksum();
    }

    std::string read_only_line(const std::string path)
    {
        std::ifstream input_file(path);
        assert(input_file.is_open());

        std::string input_line;
        while (std::getline(input_file, input_line)){

        }
        input_file.close();
        return input_line;
    }

    Disk parse_puzzle(const std::string path)
    {
        std::vector<Free> frees;
        std::vector<File> files;
        const std::string input_line = read_only_line(path);
        ull file_id = 0;
        ull posn = 0;
        bool is_file = true;
        for (char c : input_line)
        {
            unsigned int size = c - 48;
            if (is_file)
            {
                files.push_back(File(posn, size, file_id));
                file_id++;
            }
            else
            {
                frees.push_back(Free(posn, size));
            }
            is_file = (!is_file);
            posn += size;
        }
        return Disk(frees, files);
    }

    int main()
    {
        const Disk test = parse_puzzle("./day09/test_input.txt");

        std::cout << "\tRead in test input" << std::endl;
        ull test_expected_1 = 1928;
        ull test_actual_1 = part1(test);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        ull test_expected_2 = 2858;
        ull test_actual_2 = part2(test);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }
        std::cout << "\tPassed tests" << std::endl;

        // 3350727456176
        const Disk actual = parse_puzzle("./day09/puzzle_input.txt");
        std::cout << "\tRead in puzzle input" << std::endl;

        ull conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        ull conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;

        assert(conrad_pt1 == 6378826667552);
        assert(conrad_pt2 == 6413328569890);

        /*
        // Evil input from https://old.reddit.com/r/adventofcode/comments/1haauty/2024_day_9_part_2_bonus_test_case_that_might_make/
        const Disk evil = parse_puzzle("./day09/basket_case.txt");
        std::cout << "\tRead in evil input" << std::endl;
        ull evil_ans = part2(evil);
        std::cout << "\tEvil Part 2 Answer - " << std::to_string(evil_ans) << std::endl;

        assert(evil_ans == 97898222299196);

        const Disk vevil = parse_puzzle("./day09/really_evil_input.txt");
        std::cout << "\tRead in very evil input" << std::endl;
        ull vevil_ans = part2(vevil);
        std::cout << "\tVery Evil Part 2 Answer - " << std::to_string(vevil_ans) << std::endl;
        // 2.7 secs!
        assert(vevil_ans == 5799706413896802);
        */
        return 0;
    }
}