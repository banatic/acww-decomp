/* func_ov126_022a1c8c @ 0x022a1c8c, 0x104 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov126_022a20c819func_ov126_022a1c8cEv
 */

#include "cpp/ov126/Obj_ov126_022a20c8.h"

typedef Obj_ov126_022a20c8 S;

extern "C" void func_ov126_022a1448(S *self);
extern "C" void func_ov126_022a1434(S *self);

int Obj_ov126_022a20c8::func_ov126_022a1c8c()
{
    static void (S::*g_pmfTable[12])() = {&S::func_ov126_022a1a38, &S::func_ov126_022a19d8, &S::func_ov126_022a19a8,
                                          &S::func_ov126_022a18ac, &S::func_ov126_022a185c, &S::func_ov126_022a17d8,
                                          &S::func_ov126_022a17bc, &S::func_ov126_022a176c, &S::func_ov126_022a1748,
                                          &S::func_ov126_022a172c, &S::func_ov126_022a16fc, &S::func_ov126_022a16d8};
    func_ov126_022a1448(this);
    (this->*g_pmfTable[state])();
    func_ov126_022a1434(this);
    return 1;
}
