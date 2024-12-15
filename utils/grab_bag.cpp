#include "./grab_bag.h"

#include <cassert>

namespace nickels
{

    std::vector<std::vector<std::vector<bool>>> create_falsy(const unsigned int max_x, const unsigned int max_y, const unsigned int max_z)
    {
        // done goofed just assert pls
        assert(max_x == max_y);
        std::vector<std::vector<std::vector<bool>>> res;
        res.reserve(max_y);
        for (unsigned int y = 0; y < max_y; y++)
        {
            std::vector<std::vector<bool>> res_x_line;
            res_x_line.reserve(max_z);
            for (unsigned int x = 0; x < max_x; x++)
            {
                std::vector<bool> res_z_line;
                res_z_line.resize(max_z, false);
                res_x_line.emplace_back(res_z_line);
            }
            res.emplace_back(res_x_line);
        }
        return res;
    }

    bvec create_falsy(const unsigned int max_x, const unsigned int max_y)
    {
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