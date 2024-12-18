#include "./day01/main.h"
#include "./day02/main.h"
#include "./day03/main.h"
#include "./day04/main.h"
#include "./day05/main.h"
#include "./day06/main.h"
#include "./day07/main.h"
#include "./day08/main.h"
#include "./day09/main.h"
#include "./day10/main.h"
#include "./day11/main.h"
#include "./day12/main.h"
#include "./day13/main.h"
#include "./day14/main.h"
#include "./day15/main.h"
#include "./day16/main.h"

#include <iostream>
#include <cassert>

int run_all_days()
{
    std::cout << "Day 1" << std::endl;
    assert(day01::main() == 0);
    std::cout << "Day 2" << std::endl;
    assert(day02::main() == 0);
    std::cout << "Day 3" << std::endl;
    assert(day03::main() == 0);
    std::cout << "Day 4" << std::endl;
    assert(day04::main() == 0);
    std::cout << "Day 5" << std::endl;
    assert(day05::main() == 0);
    std::cout << "Day 6" << std::endl;
    assert(day06::main() == 0);
    std::cout << "Day 7" << std::endl;
    assert(day07::main() == 0);
    std::cout << "Day 8" << std::endl;
    assert(day08::main() == 0);
    std::cout << "Day 9" << std::endl;
    assert(day09::main() == 0);
    std::cout << "Day 10" << std::endl;
    assert(day10::main() == 0);
    std::cout << "Day 11" << std::endl;
    assert(day11::main() == 0);
    std::cout << "Day 12" << std::endl;
    assert(day12::main() == 0);
    std::cout << "Day 13" << std::endl;
    assert(day13::main() == 0);
    std::cout << "Day 14" << std::endl;
    assert(day14::main() == 0);
    std::cout << "Day 15" << std::endl;
    // assert(day15::main() == 0);
    std::cout << "Day 16" << std::endl;
    assert(day16::main() == 0);
    return 0;
}

int run_day(const int day)
{
    switch (day)
    {
    case 16:
        std::cout << "Day 16" << std::endl;
        return day16::main();
        break;
    case 15:
        std::cout << "Day 15" << std::endl;
        // return day15::main();
        return 0;
        break;
    case 14:
        std::cout << "Day 14" << std::endl;
        return day14::main();
        break;
    case 13:
        std::cout << "Day 13" << std::endl;
        return day13::main();
        break;
    case 12:
        std::cout << "Day 12" << std::endl;
        return day12::main();
        break;
    case 11:
        std::cout << "Day 11" << std::endl;
        return day11::main();
        break;
    case 10:
        std::cout << "Day 10" << std::endl;
        return day10::main();
        break;
    case 9:
        std::cout << "Day 9" << std::endl;
        return day09::main();
        break;
    case 8:
        std::cout << "Day 8" << std::endl;
        return day08::main();
        break;
    case 7:
        std::cout << "Day 7" << std::endl;
        return day07::main();
        break;
    case 6:
        std::cout << "Day 6" << std::endl;
        return day06::main();
        break;
    case 5:
        std::cout << "Day 5" << std::endl;
        return day05::main();
        break;
    case 4:
        std::cout << "Day 4" << std::endl;
        return day04::main();
        break;
    case 3:
        std::cout << "Day 3" << std::endl;
        return day03::main();
        break;
    case 2:
        std::cout << "Day 2" << std::endl;
        return day02::main();
        break;
    case 1:
        std::cout << "Day 1" << std::endl;
        return day01::main();
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