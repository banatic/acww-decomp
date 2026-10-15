/* func_ov054_022608ac @ 0x022608ac, 0x1dc bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov054_0226300419func_ov054_022608acEj
 */

#include "cpp/ov054/Obj_ov054_02263004.h"

typedef Obj_ov054_02263004 S;
typedef void (S::*PMF)();

extern int data_ov054_022629a0[];
extern PMF *data_ov054_02262f3c[];

extern "C" int func_020160b4(S *self);
extern "C" int func_020ab504(void *);

// The result code of the caller is handed on but never read here.
void Obj_ov054_02263004::func_ov054_022608ac(unsigned int arg)
{
    int n;

    n = func_020ab504((void *) func_020160b4(this));

    static PMF t0[2] = {&S::func_ov054_02260894, &S::func_ov054_02260860};
    static PMF t1[4] = {&S::func_ov054_02260894, &S::func_ov054_022607b8, &S::func_ov054_0226083c, &S::func_ov054_02260860};
    static PMF t2[5] = {&S::func_ov054_02260894, &S::func_ov054_022607ec, &S::func_ov054_022607b8, &S::func_ov054_0226083c,
                        &S::func_ov054_02260860};
    static PMF t3[3] = {&S::func_ov054_02260894, &S::func_ov054_022607b8, &S::func_ov054_02260860};
    static PMF t4[4] = {&S::func_ov054_02260894, &S::func_ov054_022607ec, &S::func_ov054_022607b8, &S::func_ov054_02260860};

    if (n < data_ov054_022629a0[page]) {
        (this->*data_ov054_02262f3c[page][n])();
    }
}
