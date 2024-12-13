#include "machine.h"

#include <numeric>

namespace day13
{

    /*
        So what we want is:
        a_presses*a_x + b_presses*b_x = prize_x
        a_presses*y_x + b_presses*b_y = prize_y

        Linear algebra is a throw-back and a half!
        ...
        ...
        This will only give one answer though? If it exists? And he talks about cheapest... :/

        The first test case is:
            Button A: X+94, Y+34
            Button B: X+22, Y+67
            Prize: X=8400, Y=5400
        Which becomes:
            A(94) + B(22) = 8400
            A(34) + B(67) = 5400
    */
    const ull Machine::cheapest_prize_win(
        const unsigned int a_btn_cost,
        const unsigned int b_btn_cost,
        const unsigned int limit_presses,
        const ull offset) const
    {
        // We need to unpack these to long long otherwise the math no work :'(
        //   this is because the various equations can be negative, which doesn't solve well
        const long long a_btn_x = this->a_btn.x;
        const long long a_btn_y = this->a_btn.y;
        const long long b_btn_x = this->b_btn.x;
        const long long b_btn_y = this->b_btn.y;
        const long long prize_x = this->prize.x + offset;
        const long long prize_y = this->prize.y + offset;

        const long long denominator = a_btn_x*b_btn_y - a_btn_y*b_btn_x;
        const long long A = (prize_x*b_btn_y - prize_y*b_btn_x) / denominator;
        const long long B = (a_btn_x*prize_y - a_btn_y*prize_x) / denominator;

        if(Point(A*a_btn_x + B*b_btn_x, A*a_btn_y + B*b_btn_y) == Point(prize_x, prize_y)) {
            return (a_btn_cost * A) + (b_btn_cost * B);
        }
        return 0;

    }
}