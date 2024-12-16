#include "main.h"
#include "../utils/point.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <map>

#define day15testing true

namespace day15
{

    const uc WALL = '#';
    const uc BOX = 'O';
    const uc START = '@';
    const uc SPACE = '.';

    const uc BX_START = '[';
    const uc BX_END = ']';

    const uc UP_C = '^';
    const auto UP = point::UP;
    const uc DOWN_C = 'v';
    const auto DOWN = point::DOWN;
    const uc LEFT_C = '<';
    const auto LEFT = point::LEFT;
    const uc RIGHT_C = '>';
    const auto RIGHT = point::RIGHT;

    typedef point::Direction Direction;
    typedef point::Point Point;

    struct Puzzle
    {
        const std::vector<Direction> movements;
        const std::vector<std::vector<uc>> map;
        const Point start;
    };

    ull inline goods_positioning_system(const Point p)
    {
        return 100 * p.y + p.x;
    }

    ull gps_map(const std::vector<std::vector<uc>> &map)
    {
        ull sum = 0;
        for (unsigned int y = 0; y < map.size(); y++)
        {
            const auto curr_y = map[y];
            for (unsigned int x = 0; x < curr_y.size(); x++)
            {
                const Point p(x, y);
                if (p.extract_uchar_from_map(map) == BOX || p.extract_uchar_from_map(map) == BX_START)
                {
                    sum += goods_positioning_system(p);
                }
            }
        }

        return sum;
    }

    std::vector<std::vector<uc>> expand_map(const std::vector<std::vector<uc>> &map)
    {
        std::vector<std::vector<uc>> modmap;
        modmap.reserve(map.size());
        for (std::vector<uc> old_x : map)
        {
            std::vector<uc> new_x;
            new_x.reserve(old_x.size() * 2);
            for (char c : old_x)
            {
                switch (c)
                {
                case SPACE:
                    new_x.emplace_back(SPACE);
                    new_x.emplace_back(SPACE);
                    break;
                case WALL:
                    new_x.emplace_back(WALL);
                    new_x.emplace_back(WALL);
                    break;
                case BOX:
                    new_x.emplace_back(BX_START);
                    new_x.emplace_back(BX_END);
                    break;
                default:
                    assert(false);
                    [[assume(false)]];
                    break;
                }
            }
            modmap.emplace_back(new_x);
        }
        return modmap;
    }

    ull part2(const Puzzle &input)
    {
        std::vector<std::vector<uc>> modmap = expand_map(input.map);
        // The rest of this is almost identical to last time!
        unsigned long x = input.start.x * 2; // Double because we are twice as wide!
        unsigned long y = input.start.y;
        const auto max_x = input.map.size() * 2;
        const auto max_y = input.map.size();
#if day15testing
        std::cout << std::endl;
        std::cout << "Pt 2 working map!" << std::endl;
        std::cout << std::endl;
        ull dbg_y = 0;
        ull dbg_x = 0;
        for (std::vector<uc> row : modmap)
        {
            dbg_x = 0;
            for (char c : row)
            {
                if (dbg_x == x && dbg_y == y)
                {
                    std::cout << START;
                }
                else
                {
                    std::cout << c;
                }
                dbg_x++;
            }
            std::cout << std::endl;
            dbg_y++;
        }
#endif
        for (const Direction &d : input.movements)
        {
            // OK, we are going to attempt to move that direction!
            const Point curr(x, y);
            const auto moved_a = curr.move(d);
#if day15testing
            std::cout << "Moving FROM " << curr.as_string() << " TO " << moved_a.as_string() << std::endl;
#endif
            switch (moved_a.extract_uchar_from_map(modmap))
            {
            case SPACE:
                // x, y = moved_a.x, moved_a.y;
                x = moved_a.x;
                y = moved_a.y;
                break;
            case WALL:
                // Do nothing - silly robot!
                break;
            case BX_START:
            case BX_END:
                // Try and move the box along - we can move all boxes all the way along until we hit a wall with the last box!
                //   and sadly that includes moving boxes that are "partially" attached

                // So first let's work out if we can even move - same operation has before! We'll only handle the simple case here
                unsigned long keep_moving_x = moved_a.x;
                unsigned long keep_moving_y = moved_a.y;
                bool was_wall = true;
                while (true)
                {
                    // Keep going until we find something that isn't a box
                    const Point ray(keep_moving_x, keep_moving_y);
                    const auto rn = ray.move(d);
                    const auto v = rn.extract_uchar_from_map(modmap);
                    if (v == BOX || v == BX_END || v == BX_START)
                    {
                        keep_moving_x = rn.x;
                        keep_moving_y = rn.y;
                    }
                    else
                    {

                        was_wall = v == WALL;
                        if (!was_wall)
                        {
                            keep_moving_x = rn.x;
                            keep_moving_y = rn.y;
                        }
                        break;
                    }
                }

                if (!was_wall)
                {

                    // OK, now we need to think about how to move these damned boxes... :'(

                    // we could do exactly as we did before, but each time we "add" a new one to the side, we "add" a new droid to start moving things until we get to the end?
                    //   ... wait, but what if one of the boxes we attempt to push because of that would hit a wall? No movement at all.
                    bool can_move = true;
                    // this is gonna be so slow
                    std::map<Point, uc> replacements;
                    std::vector<Point> rays_to_process;
                    rays_to_process.push_back(curr);

                    // TODO!

                    if (can_move)
                    {
#if day15testing
                        std::cout << "\tREPLACING ITEMS" << std::endl;
#endif
                        for (const auto res : replacements)
                        {
                            modmap[res.first.y][res.first.x] = res.second;
                        }
                        x = moved_a.x;
                        y = moved_a.y;
                    }
                }
                else
                {
                    // Do nothing - thank goodness!
                }
            }
        }

#if day15testing
        std::cout << std::endl;
        std::cout << "Pt 2 result map!" << std::endl;
        std::cout << std::endl;
        dbg_y = 0;
        dbg_x = 0;
        for (std::vector<uc> row : modmap)
        {
            dbg_x = 0;
            for (char c : row)
            {
                if (dbg_x == x && dbg_y == y)
                {
                    std::cout << START;
                }
                else
                {
                    std::cout << c;
                }
                dbg_x++;
            }
            std::cout << std::endl;
            dbg_y++;
        }
#endif
        return gps_map(modmap);
    }

    ull part1(const Puzzle &input)
    {
        unsigned long x = input.start.x;
        unsigned long y = input.start.y;
        std::vector<std::vector<uc>> modmap = input.map;
        for (const Direction &d : input.movements)
        {
            // OK, we are going to attempt to move that direction!
            const Point curr(x, y);
            const auto moved_a = curr.move(d);
            switch (moved_a.extract_uchar_from_map(modmap))
            {
            case SPACE:
                // x, y = moved_a.x, moved_a.y;
                x = moved_a.x;
                y = moved_a.y;
                break;
            case WALL:
                // Do nothing - silly robot!
                break;
            case BOX:
                // Try and move the box along - we can move boxes all the way along until we hit a wall with the last box!
                unsigned long keep_moving_x = moved_a.x;
                unsigned long keep_moving_y = moved_a.y;
                bool was_wall = true;
                while (true)
                {
                    // Keep going until we find something that isn't a box
                    const Point ray(keep_moving_x, keep_moving_y);
                    const auto rn = ray.move(d);
                    const auto v = rn.extract_uchar_from_map(modmap);
                    if (v == BOX)
                    {
                        keep_moving_x = rn.x;
                        keep_moving_y = rn.y;
                    }
                    else
                    {
                        was_wall = v == WALL;
                        if (!was_wall)
                        {
                            keep_moving_x = rn.x;
                            keep_moving_y = rn.y;
                        }
                        break;
                    }
                }
                if (!was_wall)
                {
                    // Move the current box to the space we found!
                    modmap[keep_moving_y][keep_moving_x] = BOX;
                    modmap[moved_a.y][moved_a.x] = SPACE;
                    x = moved_a.x;
                    y = moved_a.y;
                }
                break;
            }
        }
        return gps_map(modmap);
    }

    Puzzle parse_puzzle(const std::string path, const unsigned int max_x, const unsigned int max_y, const unsigned int num_steps)
    {
        std::vector<std::vector<uc>> map;
        map.reserve(max_y);

        std::ifstream input_file(path);
        assert(input_file.is_open());
        std::string input_line;

        unsigned int curr_y = 0;
        unsigned int curr_x = 0;
        unsigned int start_x = 0;
        unsigned int start_y = 0;

        while (std::getline(input_file, input_line))
        {
            if (input_line.length() == 0)
            {
                // stop reading once we hit the directions
                break;
            }
            curr_x = 0;
            std::vector<uc> row;
            row.reserve(max_x);
            for (char c : input_line)
            {
                if (c == START)
                {
                    start_x = curr_x;
                    start_y = curr_y;
                    row.emplace_back(SPACE);
                }
                else if (c == BOX)
                {
                    row.emplace_back(BOX);
                }
                else if (c == SPACE)
                {
                    row.emplace_back(SPACE);
                }
                else if (c == WALL)
                {
                    row.emplace_back(WALL);
                }
                else
                {
                    std::cout << "Oop! Found: " << c << " (ASCII " << std::to_string((int)c) << ")" << std::endl;
                    assert(false);
                    [[assume(false)]];
                }
                curr_x++;
            }
            map.emplace_back(row);
            curr_y++;
        }
        // stopped reading since it is now the directions!
        std::vector<Direction> dirs;
        dirs.reserve(num_steps);
        while (std::getline(input_file, input_line))
        {
            for (char c : input_line)
            {
                switch (c)
                {
                case UP_C:
                    dirs.emplace_back(UP);
                    break;
                case DOWN_C:
                    dirs.emplace_back(DOWN);
                    break;
                case LEFT_C:
                    dirs.emplace_back(LEFT);
                    break;
                case RIGHT_C:
                    dirs.emplace_back(RIGHT);
                    break;
                default:
                    assert(false);
                    [[assume(false)]];
                    break;
                }
            }
        }

        const Point curr_pos = Point(start_x, start_y);
        const Puzzle pz(dirs, map, curr_pos);
        return pz;
    }

    int main()
    {
#if day15testing
        const Puzzle simple = parse_puzzle("./day15/basket_case.txt", 7, 7, 11);
        const ull test_simple = 908;
        ull simple_actual = part1(simple);
        if (simple_actual != test_simple)
        {
            std::cout << "\tFAIL - Pt 1 simple expected " << std::to_string(test_simple) << ", got " << std::to_string(simple_actual) << std::endl;
            return 1;
        }
        ull simple_actual_2 = part2(simple);
        assert(simple_actual_2 != 0);
#endif

        const Puzzle test = parse_puzzle("./day15/test_input.txt", 10, 10, 700);
        std::cout << "\tRead in test input big" << std::endl;
        ull test_expected_1 = 10092;
        ull test_actual_1 = part1(test);
        if (test_actual_1 != test_expected_1)
        {
            std::cout << "\tFAIL - Pt 1 Expected " << std::to_string(test_expected_1) << ", got " << std::to_string(test_actual_1) << std::endl;
            return 1;
        }

        std::cout << "\tPassed Pt 1 tests" << std::endl;

        ull test_expected_2 = 9021;
        ull test_actual_2 = part2(test);
        if (test_actual_2 != test_expected_2)
        {
            std::cout << "\tFAIL - Pt 2 Expected " << std::to_string(test_expected_2) << ", got " << std::to_string(test_actual_2) << std::endl;
            return 1;
        }

        std::cout << "\tPassed tests" << std::endl;

#if !day15testing
        const Puzzle actual = parse_puzzle("./day15/puzzle_input.txt", 50, 50, 20000);
        std::cout << "\tRead in puzzle input" << std::endl;

        ull conrad_pt1 = part1(actual);
        std::cout << "\tPart 1 Answer - " << std::to_string(conrad_pt1) << std::endl;

        ull conrad_pt2 = part2(actual);
        std::cout << "\tPart 2 Answer - " << std::to_string(conrad_pt2) << std::endl;
#endif
        return 0;
    }
}