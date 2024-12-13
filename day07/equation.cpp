#include "equation.h"

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

    const unsigned int count_of_digits(unsigned long long in)
    {
        unsigned int digits = 0;
        while (in > 0)
        {
            in /= 10;
            digits++;
        }
        return digits;
    }

    bool by_concat(unsigned int curr_ix, unsigned long goal, unsigned long curr, const std::vector<unsigned int> &partials)
    {
        const auto part = partials[curr_ix];
        const auto part_sz = count_of_digits(part);
        const auto n_curr = curr * std::pow(10, part_sz);
        const unsigned long joined = n_curr + part;
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

    bool Equation::does_work_pt1()
    {
        bool ans = by_add(0, goal, 0, partials, false);
        return ans;
    }

    bool Equation::does_work_pt2()
    {
        bool ans = by_add(0, goal, 0, partials, true);
        return ans;
    }
}