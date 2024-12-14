#pragma once

#include <utility>

namespace numerics {
    typedef unsigned long long ull;
    typedef unsigned int ui;
    const ui count_of_digits(ull in);
    const ull concat_numbers(const ui a, const ui b);
    const std::pair<ull, ull> split_off_digits(const ull in, const ui to_split_off);
    const std::pair<ull, ull> split_number(const ull in, const ui size);
    const std::pair<ull, ull> split_number(const ull in);
    const ui wrap_addition_upper_bound(const ui original, long long adding, const ui upper_bound);
}