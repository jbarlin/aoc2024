#include "./grab_bag.h"

namespace nickels
{
    bvec create_falsy(const unsigned int max_x, const unsigned int max_y){
        bvec res;
        res.reserve(max_y);
        for (unsigned int y = 0; y < max_y; y++)
        {
            std::vector<bool> res_x_line;
            res_x_line.resize(max_x, false);
            res.emplace_back(res_x_line);
        }
        return res;
    }

    bvec create_falsy(const unsigned int size)
    {
        return create_falsy(size, size);
    }
}