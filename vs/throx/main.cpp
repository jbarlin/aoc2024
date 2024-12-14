#include "./day1/main.h"
#include "./day2/main.h"
#include "./day3/main.h"
#include "./day4/main.h"
#include "./day5/main.h"
#include "./day6/main.h"
#include "./day7/main.h"
#include "./day8/main.h"
#include "./day9/main.h"
#include "./day10/main.h"
#include "./day11/main.h"
#include "./day12/main.h"
#include "./day13/main.h"

#include <iostream>
#include <iosfwd>
#include <cassert>
#include <fstream>
#include <sstream>

void redirect_cin_file(const std::string inputFile) {
    std::ifstream input_file(inputFile);
    assert(input_file.is_open());
    
    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::string fileContent = buffer.str();

    // Redirect standard input
    std::streambuf* cin_backup = std::cin.rdbuf(); 
    std::istringstream ss(fileContent);
    std::cin.rdbuf(ss.rdbuf()); 
}

int d1()
{
    redirect_cin_file("./day01/test_input.txt");
    day1::main();
    redirect_cin_file("./day01/puzzle_input.txt");
    day1::main();
    return 0;
}

int d2()
{
    redirect_cin_file("./day02/test_input.txt");
    day2::main();
    redirect_cin_file("./day02/puzzle_input.txt");
    day2::main();
    return 0;
}

int d3()
{
    redirect_cin_file("./day03/test_input.txt");
    day3::main();
    redirect_cin_file("./day03/puzzle_input.txt");
    day3::main();
    return 0;
}

int d4()
{
    redirect_cin_file("./day04/test_input.txt");
    day4::main();
    redirect_cin_file("./day04/puzzle_input.txt");
    day4::main();
    return 0;
}

int d5()
{
    redirect_cin_file("./day05/test_input.txt");
    day5::main();
    redirect_cin_file("./day05/puzzle_input.txt");
    day5::main();
    return 0;
}

int d6()
{
    redirect_cin_file("./day06/test_input.txt");
    day6::main();
    redirect_cin_file("./day06/puzzle_input.txt");
    day6::main();
    return 0;
}

int d7()
{
    redirect_cin_file("./day07/test_input.txt");
    day7::main();
    redirect_cin_file("./day07/puzzle_input.txt");
    day7::main();
    return 0;
}

int d8()
{
    redirect_cin_file("./day08/test_input.txt");
    day8::main();
    redirect_cin_file("./day08/puzzle_input.txt");
    day8::main();
    return 0;
}

int d9()
{
    redirect_cin_file("./day09/test_input.txt");
    day9::main();
    redirect_cin_file("./day09/puzzle_input.txt");
    day9::main();
    return 0;
}

int d10()
{
    redirect_cin_file("./day10/test_input.txt");
    day10::main();
    redirect_cin_file("./day10/puzzle_input.txt");
    day10::main();
    return 0;
}

int d11()
{
    redirect_cin_file("./day11/test_input.txt");
    day11::main();
    redirect_cin_file("./day11/puzzle_input.txt");
    day11::main();
    return 0;
}

int d12()
{
    redirect_cin_file("./day12/test_input.txt");
    day12::main();
    redirect_cin_file("./day12/puzzle_input.txt");
    day12::main();
    return 0;
}

int d13()
{
    redirect_cin_file("./day13/test_input.txt");
    day13::main();
    redirect_cin_file("./day13/puzzle_input.txt");
    day13::main();
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
    std::cout << "Day 9" << std::endl;
    d9();
    std::cout << "Day 10" << std::endl;
    d10();
    std::cout << "Day 11" << std::endl;
    d11();
    std::cout << "Day 12" << std::endl;
    d12();
    std::cout << "Day 13" << std::endl;
    d13();
    return 0;
}

int run_day(const int day)
{
    switch (day)
    {
    case 13:
        std::cout << "Day 13" << std::endl;
        return d13();
        break;
    case 12:
        std::cout << "Day 12" << std::endl;
        return d12();
        break;
    case 11:
        std::cout << "Day 11" << std::endl;
        return d11();
        break;
    case 10:
        std::cout << "Day 10" << std::endl;
        return d10();
        break;
    case 9:
        std::cout << "Day 9" << std::endl;
        return d9();
        break;
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