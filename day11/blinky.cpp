#include "blinky.h"

#include "../utils/numerics.h"

#include <cmath>
#include <cassert>
#include <iostream>

namespace day11
{

    const ull Inky::total_stones_after(const unsigned int target_blinks)
    {
        return find_stone_end_count(starting_position, target_blinks);
    }

    const std::vector<ull> blink(ull input)
    {
        // 0 -> 1
        // if digits mod 2 equals 1, mult by 2024
        // else split in two
        if (input == 0)
        {
            return {1};
        }
        else
        {
            const unsigned int c_digits = numerics::count_of_digits(input);
            if (c_digits % 2 == 1)
            {
                return {input * 2024};
            } else {
                const auto p = numerics::split_number(input, c_digits);
                return {p.first, p.second};
            }
        }
    }

    const ull Inky::find_stone_end_count(const std::vector<ull> input_stones, const unsigned int blinks_remaining)
    {
        if (blinks_remaining == 0)
        {
            return input_stones.size();
        }
        else
        {
            ull result = 0;
            for (ull stone : input_stones)
            {
                auto cache_key = std::make_pair(stone, blinks_remaining);
                // Check if we have seen this before...
                if (cache.contains(cache_key))
                {
                    // We've seen this before!
                    result += cache[cache_key];
                } else {
                    auto out = blink(stone);
                    const ull answer = find_stone_end_count(out, blinks_remaining - 1);
                    cache[cache_key] = answer;
                    result += answer;
                }
            }
            return result;
        }
    };
}