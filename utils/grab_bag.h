#pragma once

#include <vector>

// As in... weird that it happened twice
namespace nickels {
    typedef std::vector<std::vector<bool>> bvec;

    bvec create_falsy(const unsigned int size);
    bvec create_falsy(const unsigned int max_x, const unsigned int max_y);
    std::vector<std::vector<std::vector<bool>>> create_falsy(const unsigned int max_x, const unsigned int max_y, const unsigned int max_z);
}