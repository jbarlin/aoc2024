#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "walk_result.h"

namespace day06 {
    const unsigned char CLEAR = 0;
    const unsigned char OBSTICLE = 1;
    
    class Puzzle{
        private:
            const std::pair<unsigned int, unsigned int> start;
        public:
            const std::vector<std::vector<unsigned char>> map;
            const size_t size;
            Puzzle(std::vector<std::vector<unsigned char>> map, std::pair<unsigned int, unsigned int> start, const unsigned int size): start{start},map{map},size{size}{};
            const Point start_point() const;
            WalkResult walk_and_turn_right(const Point pos, const Direction &direction);
            const WalkResult misty_step_and_turn_right(const Point pos, const Direction &direction) const;
            void print();
            const Puzzle with_new_obsticle_at(const Point pt) const;
            const unsigned int count_of_obsticles();
    };
}