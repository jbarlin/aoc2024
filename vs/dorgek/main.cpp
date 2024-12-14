#include "./src/aoc/day01.h"
#include "./src/aoc/day02.h"
#include "./src/aoc/day03.h"
#include "./src/aoc/day04.h"
#include "./src/aoc/day05.h"
#include "./src/aoc/day06.h"
#include "./src/aoc/day07.h"
#include "./src/aoc/day08.h"

#include <iostream>
#include <cassert>

int d1()
{
    day01::partOne("day01/test_input.txt");
    day01::partTwo("day01/test_input.txt");
    day01::partOne("day01/puzzle_input.txt");
    day01::partTwo("day01/puzzle_input.txt");
    return 0;
}

int d2()
{
    day02::partOne("day02/test_input.txt");
    day02::partTwo("day02/test_input.txt");
    day02::partOne("day02/puzzle_input.txt");
    day02::partTwo("day02/puzzle_input.txt");
    return 0;
}

int d3()
{
    day03::partOne("day03/test_input.txt");
    day03::partTwo("day03/test_input.txt");
    day03::partOne("day03/puzzle_input.txt");
    day03::partTwo("day03/puzzle_input.txt");
    return 0;
}

int d4()
{
    day04::partOne("day04/test_input.txt");
    day04::partTwo("day04/test_input.txt");
    day04::partOne("day04/puzzle_input.txt");
    day04::partTwo("day04/puzzle_input.txt");
    return 0;
}

int d5()
{
    day05::partOne("day05/test_input.txt");
    day05::partTwo("day05/test_input.txt");
    day05::partOne("day05/puzzle_input.txt");
    day05::partTwo("day05/puzzle_input.txt");
    return 0;
}

int d6()
{
    day06::partOne("day06/test_input.txt");
    day06::partTwo("day06/test_input.txt");
    day06::partOne("day06/puzzle_input.txt");
    day06::partTwo("day06/puzzle_input.txt");
    return 0;
}

int d7()
{
    day07::partOne("day07/test_input.txt");
    day07::partTwo("day07/test_input.txt");
    day07::partOne("day07/puzzle_input.txt");
    day07::partTwo("day07/puzzle_input.txt");
    return 0;
}

int d8()
{
    day08::partOne("day08/test_input.txt");
    day08::partTwo("day08/test_input.txt");
    day08::partOne("day08/puzzle_input.txt");
    day08::partTwo("day08/puzzle_input.txt");
    return 0;
}

int run_all_days()
{
    std::cout << "Day 1" << std::endl;
    d1();
    std::cout << "Day 2" << std::endl;
    d2();
    std::cout << "Day 3" << std::endl;
    d3();
    std::cout << "Day 4" << std::endl;
    d4();
    std::cout << "Day 5" << std::endl;
    d5();
    std::cout << "Day 6" << std::endl;
    d6();
    std::cout << "Day 7" << std::endl;
    d7();
    std::cout << "Day 8" << std::endl;
    d8();
    return 0;
}

int run_day(const int day)
{
    switch (day)
    {
    case 8:
        std::cout << "Day 8" << std::endl;
        return d8();
        break;
    case 7:
        std::cout << "Day 7" << std::endl;
        return d7();
        break;
    case 6:
        std::cout << "Day 6" << std::endl;
        return d6();
        break;
    case 5:
        std::cout << "Day 5" << std::endl;
        return d5();
        break;
    case 4:
        std::cout << "Day 4" << std::endl;
        return d4();
        break;
    case 3:
        std::cout << "Day 3" << std::endl;
        return d3();
        break;
    case 2:
        std::cout << "Day 2" << std::endl;
        return d2();
        break;
    case 1:
        std::cout << "Day 1" << std::endl;
        return d1();
        break;
    default:
        return run_all_days();
        break;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        const unsigned int dayFrom = std::stoi(argv[1]);
        const unsigned int dayTo = std::stoi(argv[2]);
        if (dayFrom < dayTo)
        {
            for (unsigned int i = dayFrom; i <= dayTo; i++)
            {
                assert(run_day(i) == 0);
            }
        }
        else
        {
            for (unsigned int i = dayFrom; i >= dayTo; i--)
            {
                assert(run_day(i) == 0);
            }
        }
    }
    else if (argc == 2)
    {
        const int day = std::stoi(argv[1]);
        return run_day(day);
    }
    else
    {
        return run_all_days();
    }

    return 0;
}