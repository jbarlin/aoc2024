#include "directions.h"

#include <cassert>
#include <iostream>

namespace point
{
    
    Direction::Direction(char x, char y) : x{x}, y{y}
    {
        assert(-2 < x);
        assert(x < 2);
        assert(-2 < y);
        assert(y < 2);
        assert(x != 0 || y != 0);
    };

    const std::string Direction::as_string() const {
        if (this->operator==(UP))
        {
            return "UP";
        }
        else if (this->operator==(RIGHT))
        {
            return "RIGHT";
        }
        else if (this->operator==(DOWN))
        {
            return "DOWN";
        }
        else
        {
            return "LEFT";
        }
    }

    bool Direction::operator<(const Direction &other) const
    {
        if (this->operator==(UP))
        {
            return false;
        }
        else if (this->operator==(RIGHT))
        {
            return other != UP;
        }
        else if (this->operator==(DOWN))
        {
            return other != UP && other != DOWN;
        }
        else
        {
            return true;
        }
    }

    bool Direction::operator==(const Direction &other) const
    {
        return x == other.x && y == other.y;
    }

    const unsigned char Direction::as_index() const
    {
        if (this->operator==(UP))
        {
            return 0;
        }
        else if (this->operator==(RIGHT))
        {
            return 1;
        }
        else if (this->operator==(DOWN))
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }

    const Direction Direction::turn_right() const
    {
        if (this->operator==(UP))
        {
            return RIGHT;
        }
        else if (this->operator==(RIGHT))
        {
            return DOWN;
        }
        else if (this->operator==(DOWN))
        {
            return LEFT;
        }
        else
        {
            return UP;
        }
    }

    const Direction Direction::turn_around() const
    {
        if (this->operator==(UP))
        {
            return DOWN;
        }
        else if (this->operator==(RIGHT))
        {
            return LEFT;
        }
        else if (this->operator==(DOWN))
        {
            return UP;
        }
        else
        {
            return RIGHT;
        }
    }

    const Direction Direction::turn_left() const
    {
        if (this->operator==(UP))
        {
            return LEFT;
        }
        else if (this->operator==(RIGHT))
        {
            return UP;
        }
        else if (this->operator==(DOWN))
        {
            return RIGHT;
        }
        else
        {
            return DOWN;
        }
    }
}