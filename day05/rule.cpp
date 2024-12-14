#include "rule.h"

#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

namespace day05
{

    // Stolen wholesale from https://stackoverflow.com/questions/45447361/how-to-move-certain-elements-of-stdvector-to-a-new-index-within-the-vector
    template <typename t>
    void move(std::vector<t> &v, size_t oldIndex, size_t newIndex)
    {
        if (oldIndex > newIndex)
        {
            std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
        }
        else
        {
            std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
        }
    }

    Rule::Rule(unsigned char before, unsigned char after) : before{before}, after{after}
    {
    }

    void Rule::make_happy(std::vector<unsigned char> &book)
    {
        bool found_before = false;
        bool found_after = false;
        unsigned int bef_ix = 0;
        unsigned int aft_ix = 0;
        for (unsigned int i = 0; i < book.size(); i++)
        {
            if (book[i] == before)
            {
                found_before = true;
                bef_ix = i;
            }
            else if (book[i] == after)
            {
                found_after = true;
                aft_ix = i;
            }
        }

        if (found_before && found_after && aft_ix < bef_ix)
        {
            move(book, aft_ix, bef_ix);
        }
    }

    bool Rule::satisfied(const std::vector<unsigned char> &book)
    {
        bool found_before = false;
        bool found_after = false;
        unsigned int bef_ix = 0;
        unsigned int aft_ix = 0;
        for (unsigned int i = 0; i < book.size(); i++)
        {
            if (book[i] == before)
            {
                found_before = true;
                bef_ix = i;
            }
            else if (book[i] == after)
            {
                found_after = true;
                aft_ix = i;
            }
        }
        return (!found_before) || (!found_after) || (bef_ix < aft_ix);
    };
}