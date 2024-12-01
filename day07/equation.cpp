#include "equation.h"

#include <ranges>
#include <iostream>

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
        const unsigned long joined = std::stoul(std::to_string(curr) + std::to_string(partials[curr_ix]));
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