#pragma once

namespace point{
    class Direction{
        private:        
        public:
            const char x;
            const char y;
            Direction(char x, char y);
            const Direction turn_right() const;
            const Direction turn_around() const;
            const Direction turn_left() const;
            bool operator== (const Direction & other) const;
            bool operator< (const Direction & other) const;
            const unsigned char as_index() const;
    };
    const Direction UP = Direction(0, -1);
    const Direction RIGHT = Direction(1, 0);
    const Direction DOWN = Direction(0, 1);
    const Direction LEFT = Direction(-1, 0);
}