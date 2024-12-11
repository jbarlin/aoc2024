#include "blinky.h"

#include <cmath>
#include <cassert>
#include <iostream>

namespace day11
{

    const ull Inky::total_stones_after(const unsigned int target_blinks)
    {
        return find_stone_end_count(starting_position, target_blinks);
    }

    const unsigned int count_of_digits(ull in)
    {
        unsigned int digits = 0;
        while (in > 0)
        {
            in /= 10;
            digits++;
        }
        return digits;
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
            const unsigned int c_digits = count_of_digits(input);
            if (c_digits % 2 == 1)
            {
                return {input * 2024};
            } else {
                // 512_072 / 000 -> 512
                // 512 * 000 = 512_000
                // 512_000 - 512_072 = 72 ???
                // 512_072 is 6 digits, need 3 0's on a 1 - 10^3?
                // 28_676_032 is 8, need 4 0s 

                unsigned int divisor = std::pow(10, c_digits / 2);
                const ull left_half = input / divisor;
                const ull right_half = input - (left_half * divisor);
                return {left_half, right_half};
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