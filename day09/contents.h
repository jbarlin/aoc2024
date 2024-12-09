#pragma once

namespace day09
{

    typedef unsigned long long ull;
    struct Free {
        ull start_posn;
        ull size;

        Free(ull st, ull sz){
            start_posn = st;
            size = sz;
        }
    };

    struct File{
        ull start_posn;
        ull size;
        ull id;

        File(ull st, ull sz, ull i){
            start_posn = st;
            size = sz;
            id = i;
        }
    };
}