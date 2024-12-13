#pragma once

#include "../utils/point.h"

namespace day13
{

    typedef unsigned long long ull;
    typedef point::Point Point;

    class Machine
    {
    public:
        const Point a_btn;
        const Point b_btn;
        const Point prize;
        const unsigned int number;
        Machine(const Point &a, const Point &b, const Point &p, const unsigned int number) : a_btn{a}, b_btn{b}, prize{p}, number{number} {};
        const ull cheapest_prize_win(const unsigned int a_btn_cost, const unsigned int b_btn_cost, const unsigned int limit_presses, const ull offset) const;
    };
}