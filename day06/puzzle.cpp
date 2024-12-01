#include "puzzle.h"
#include <fstream>
#include <cassert>
#include <memory>

namespace day06
{
    void Puzzle::print() {
        for(unsigned int y = 0; y < map.size(); y++){
            for(unsigned int x = 0; x < map.size(); x++){
                std::cout << std::to_string(map[y][x]);
            }
            std::cout << std::endl;
        }
    }

    const Point Puzzle::start_point() const
    {
        return Point(start);
    }

    const Puzzle Puzzle::with_new_obsticle_at(const Point pt) const {
        std::vector<std::vector<unsigned char>> n_map = map;
        n_map[pt.y][pt.x] = 1;
        return Puzzle(n_map, start, size);
    }
    const unsigned int Puzzle::count_of_obsticles(){
        unsigned int ct = 0;
        for(unsigned int y = 0; y < size; y++){
            for (unsigned int x = 0; x < size; x++){
                ct += map[y][x];
            }
        }
        return ct;
    }

    const WalkResult Puzzle::misty_step_and_turn_right(const Point pos, const Direction &direction) const
    {
        // I am currently facing dir, move as far as possible, then turn right
        Direction n_dir = direction;
        std::set<Point> points;
        auto ref = std::ref(pos);
        unsigned long steps = 0;
        while (true)
        {
            if (!ref.get().can_move_sq(n_dir, size))
            {
                return WalkResult(steps, n_dir, points);
            }
            else
            {
                const Point a = ref.get();
                const Point next_point = a.move(n_dir);

                assert(next_point.x != a.x || next_point.y != a.y);

                unsigned char lk = next_point.extract_value_square_map(map);
                if (lk == 1)
                {
                    return WalkResult(Point(a.x, a.y), steps, n_dir.turn_right(), points);
                }
                else
                {
                    ref = std::ref(next_point);
                }
            }
        }
    }


    WalkResult Puzzle::walk_and_turn_right(const Point pos, const Direction &direction)
    {
        // I am currently facing dir, move as far as possible, then turn right
        Direction n_dir = direction;
        std::set<Point> points;
        auto ref = std::ref(pos);
        points.insert(pos);
        unsigned long steps = 0;
        while (true)
        {
            if (!ref.get().can_move_sq(n_dir, size))
            {
                return WalkResult(steps, n_dir, points);
            }
            else
            {
                const Point a = ref.get();
                const Point next_point = a.move(n_dir);

                assert(next_point.x != a.x || next_point.y != a.y);

                unsigned char lk = next_point.extract_value_square_map(map);
                if (lk == 1)
                {
                    return WalkResult(Point(a.x, a.y), steps, n_dir.turn_right(), points);
                }
                else
                {
                    ref = std::ref(next_point);
                    points.insert(next_point);
                    steps++;
                }
            }
        }
    }
}