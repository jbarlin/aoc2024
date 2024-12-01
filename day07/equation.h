#pragma once

#include <vector>

namespace day07 {
    class Equation{
        private:
            
            
        public:
            const unsigned long goal;
            const std::vector<unsigned int> partials;
            bool does_work_pt1();
            bool does_work_pt2();
            Equation(unsigned long goal, const std::vector<unsigned int> &partials): goal{goal},partials{partials}{

            }
    };
}