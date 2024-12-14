#include "numerics.h"

#include <cassert>
#include <cmath>

namespace numerics
{
    const ui count_of_digits(ull in)
    {
        ui digits = 0;
        while (in > 0)
        {
            in /= 10;
            digits++;
        }
        return digits;
    }

    const ull concat_numbers(const ui a, const ui b)
    {
        const ui b_sz = count_of_digits(b);
        const ull a_larger = a * std::pow(10, b_sz);
        return a_larger + b;
    }

    const std::pair<ull, ull> split_off_digits(const ull in, const ui to_split_off)
    {
        unsigned int divisor = std::pow(10, to_split_off);
        const ull left_half = in / divisor;
        const ull right_half = in - (left_half * divisor);
        return {left_half, right_half};
    }

    const std::pair<ull, ull> split_number(const ull in, const ui size)
    {
        assert(size % 2 == 0);
        [[assume(size % 2 == 0)]];
        return split_off_digits(in, size / 2);
    }

    const std::pair<ull, ull> split_number(const ull in)
    {
        return split_number(in, count_of_digits(in));
    }

    const ui wrap_addition_upper_bound(const ui original, long long adding, const ui upper_bound)
    {
        const long long ret_val = adding + original;
        return (ret_val < 0) ? (upper_bound - 1 + ((ret_val + 1) % upper_bound)) : (ret_val % upper_bound);
    }
}