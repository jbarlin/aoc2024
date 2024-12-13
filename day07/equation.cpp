#include "equation.h"
#include "../utils/numerics.h"

#include <ranges>
#include <iostream>
#include <cmath>

namespace day07
{

    bool by_add(unsigned int curr_ix, unsigned long goal, unsigned long curr, const std::vector<unsigned int> &partials, const bool concat);
    bool by_mult(unsigned int curr_ix, unsigned long goal, unsigned long curr, const std::vector<unsigned int> &partials, const bool concat);
    bool by_concat(unsigned int curr_ix, unsigned long goal, unsigned long curr, const std::vector<unsigned int> &partials);

    bool by_add(unsigned int curr_ix, unsigned long goal, unsigned long curr, const std::vector<unsigned int> &partials, const bool concat)
    {
        const unsigned long addit = curr + partials[curr_ix];
        if (curr_ix == (partials.size() - 1))
        {
            return goal == addit;
        }
        else if (addit > goal)
        {
            return false;
        }
        else
        {
            return by_add(curr_ix + 1, goal, addit, partials, concat) ||
                   by_mult(curr_ix + 1, goal, addit, partials, concat) ||
                   (concat && by_concat(curr_ix + 1, goal, addit, partials));
        }
    }

    bool by_mult(unsigned int curr_ix, unsigned long goal, unsigned long curr, const std::vector<unsigned int> &partials, const bool concat)
    {
        const unsigned long mutli = curr * partials[curr_ix];
        if (curr_ix == (partials.size() - 1))
        {
            return goal == mutli;
        }
        else if (mutli > goal)
        {
            return false;
        }
        else
        {
            return by_add(curr_ix + 1, goal, mutli, partials, concat) ||
                   by_mult(curr_ix + 1, goal, mutli, partials, concat) ||
                   (concat && by_concat(curr_ix + 1, goal, mutli, partials));
        }
    }

    bool by_concat(unsigned int curr_ix, unsigned long goal, unsigned long curr, const std::vector<unsigned int> &partials)
    {
        const auto part = partials[curr_ix];
        const unsigned long joined = numerics::concat_numbers(curr, part);

        if (curr_ix == (partials.size() - 1))
        {
            return goal == joined;
        }
        else if (joined > goal)
        {
            return false;
        }
        else
        {
            return by_add(curr_ix + 1, goal, joined, partials, true) ||
                   by_mult(curr_ix + 1, goal, joined, partials, true) ||
                   by_concat(curr_ix + 1, goal, joined, partials);
        }
    }

    bool by_sub(const unsigned int curr_ix, const unsigned long curr, const std::vector<unsigned int> &partials, const bool concat);
    bool by_div(const unsigned int curr_ix, const unsigned long curr, const std::vector<unsigned int> &partials, const bool concat);
    bool by_split(const unsigned int curr_ix, const unsigned long curr, const std::vector<unsigned int> &partials);

    bool by_div(const unsigned int curr_ix, const unsigned long curr, const std::vector<unsigned int> &partials, const bool concat)
    {
        const auto lookat = partials[curr_ix];
        if (curr_ix == 0)
        {
            return curr == lookat;
        }
        else if (curr % lookat != 0)
        {
            return false;
        }
        else
        {
            const unsigned long nx = curr / lookat;
            return by_sub(curr_ix - 1, nx, partials, concat) ||
                   by_div(curr_ix - 1, nx, partials, concat) ||
                   (concat && by_split(curr_ix - 1, nx, partials));
        }
    }

    bool by_sub(const unsigned int curr_ix, const unsigned long curr, const std::vector<unsigned int> &partials, const bool concat)
    {
        const auto lookat = partials[curr_ix];
        if (curr_ix == 0)
        {
            return curr == lookat;
        }
        else if (lookat > curr)
        {
            return false;
        }
        else
        {
            const unsigned long nx = curr - lookat;
            return by_sub(curr_ix - 1, nx, partials, concat) ||
                   by_div(curr_ix - 1, nx, partials, concat) ||
                   (concat && by_split(curr_ix - 1, nx, partials));
        }
    }

    bool by_split(const unsigned int curr_ix, const unsigned long curr, const std::vector<unsigned int> &partials)
    {
        if (curr_ix == 0)
        {
            return false;
        }
        const auto lookat = partials[curr_ix];
        if (lookat > curr)
        {
            return false;
        }
        const auto split = numerics::split_off_digits(curr, numerics::count_of_digits(lookat));
        if (split.second == lookat)
        {
            const unsigned long nx = split.first;
            return by_sub(curr_ix - 1, nx, partials, true) ||
                   by_div(curr_ix - 1, nx, partials, true) ||
                   by_split(curr_ix - 1, nx, partials);
        }
        else
        {
            return false;
        }
    }

    bool Equation::does_work_pt1()
    {
        // bool ans = by_add(0, goal, 0, partials, false);
        // return ans;
        const auto curr_ix = partials.size() - 1;
        return by_div(curr_ix, goal, partials, false) ||
                by_sub(curr_ix, goal, partials, false);
    }

    bool Equation::does_work_pt2()
    {
        // bool ans = by_add(0, goal, 0, partials, true);
        // return ans;
        const auto curr_ix = partials.size() - 1;
        return by_div(curr_ix, goal, partials, true) ||
                by_sub(curr_ix, goal, partials, true) || 
                by_split(curr_ix, goal, partials);
    }
}