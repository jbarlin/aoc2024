#include "./day01/main.h"
#include "./day02/main.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int day = std::stoi(argv[1]);
        switch (day)
        {
        case 2:
            std::cout << "Day 2" << std::endl;
            return day02::main();
            break;
        case 1:
            std::cout << "Day 1" << std::endl;
            return day01::main();
            break;
        default:
            break;
        }
    }
    else
    {
        std::cout << "Day 1" << std::endl;
        day01::main();
        std::cout << "Day 2" << std::endl;
        day02::main();
    }

    return 0;
}