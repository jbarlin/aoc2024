#include "topography.h"

namespace day10
{

    std::set<Point> distinct_nines(const std::vector<std::vector<unsigned char>> &map, const unsigned int square_size, const unsigned int looking_for, const Point &curr_loc)
    {
        std::set<Point> returnable;
        if (looking_for == 9)
        {
            auto v = curr_loc.get_plus_in_bounds(square_size);
            for (const Point &p : v)
            {
                if (p.extract_value_square_map(map) == 9)
                {
                    returnable.insert(p);
                }
            }
        }
        else
        {
            auto v = curr_loc.get_plus_in_bounds(square_size);
            for (const Point &p : v)
            {
                if (p.extract_value_square_map(map) == looking_for)
                {
                    auto results = distinct_nines(map, square_size, looking_for + 1, p);
                    returnable.insert(results.begin(), results.end());
                }
            }
        }
        return returnable;
    }

    ull distinct_trails(const std::vector<std::vector<unsigned char>> &map, const unsigned int square_size, const unsigned int looking_for, const Point &curr_loc)
    {
        if (looking_for == 9)
        {
            ull count = 0;
            auto v = curr_loc.get_plus_in_bounds(square_size);
            for (const Point &p : v)
            {
                if (p.extract_value_square_map(map) == 9)
                {
                    count += 1;
                }
            }
            return count;
        }
        else
        {
            ull count = 0;
            auto v = curr_loc.get_plus_in_bounds(square_size);
            for (const Point &p : v)
            {
                if (p.extract_value_square_map(map) == looking_for)
                {
                    count += distinct_trails(map, square_size, looking_for + 1, p);
                }
            }
            return count;
        }
    }

    const ull Topography::score_trailheads() const
    {
        ull count = 0;
        for (const Point &p : zeros)
        {
            count += distinct_nines(map, square_size, 1, p).size();
        }
        return count;
    }

    const ull Topography::score_rating() const
    {
        ull count = 0;
        for (const Point &p : zeros)
        {
            count += distinct_trails(map, square_size, 1, p);
        }
        return count;
    }
}