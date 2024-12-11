#pragma once

#include <map>
#include <vector>

namespace day11 {

    typedef unsigned long long ull;

    class Inky{
        private:
        public:
            // So I think what we want to cache is the (stone, blink) -> final answer
            //   I'm guessing we will have a lot of repeating ones? The input is small though...
            // Or maybe stone -> stones?
            std::map<std::pair<ull, unsigned int>, ull> cache;
            const std::vector<ull> starting_position;
            Inky(const std::vector<ull> &start): cache{std::map<std::pair<ull, unsigned int>, ull>()}, starting_position{start}{};
            const ull find_stone_end_count(const std::vector<ull> input_stone, const unsigned int blinks_remaining);
            const ull total_stones_after(const unsigned int target_blinks);

    };
}