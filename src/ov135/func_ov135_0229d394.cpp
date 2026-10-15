/* func_ov135_0229d394 @ 0x0229d394, 0x94 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov135_0229d61019func_ov135_0229d394Ev
 */

#include "cpp/ov135/Obj_ov135_0229d610.h"

typedef Obj_ov135_0229d610 S;
typedef void (S::*PMF)();

#define STATE_func_ov135_0229d1b0 (PMF) & S::func_ov135_0229d1b0

extern "C" void func_ov135_0229d08c(void *);
extern "C" void func_ov135_0229d07c(void *);

int Obj_ov135_0229d610::func_ov135_0229d394()
{
    static void (S::*pmfs[4])() = {&S::func_ov135_0229d1d8, STATE_func_ov135_0229d1b0, &S::func_ov135_0229d178,
                                   &S::func_ov135_0229d148};
    func_ov135_0229d08c(this);

    (this->*pmfs[state])();

    func_ov135_0229d07c(this);
    return 1;
}

#undef STATE_func_ov135_0229d1b0
