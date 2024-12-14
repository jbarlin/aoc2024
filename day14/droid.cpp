#include "droid.h"

namespace day14
{
    const Droid Droid::after_ticks(const unsigned int ticks, const unsigned int max_x, const unsigned int max_y) const
    {
        return Droid(Point(position, motion, max_x, max_y, ticks), motion, number);
    }

    const std::string Droid::as_string() const{
        return "Droid #" + std::to_string(number) + "@(" + position.as_string() + ")" + motion.as_string();
    }
    
}