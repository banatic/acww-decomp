/* func_ov116_0229e5e8 @ 0x0229e5e8, 0xcc bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov116_0229e8b819func_ov116_0229e5e8Ev
 */

#include "cpp/ov116/Obj_ov116_0229e8b8.h"

typedef Obj_ov116_0229e8b8 S;
typedef void (S::*PMF)();

#define DISCARD_HANDLER(Class, Method) (PMF) & Class::Method

void Obj_ov116_0229e8b8::func_ov116_0229e5e8()
{
    static PMF table[9] = {&S::func_ov116_0229e228,
                           &S::func_ov116_0229e1f0,
                           &S::func_ov116_0229e168,
                           &S::func_ov116_0229e140,
                           DISCARD_HANDLER(S, func_ov116_0229e0e8),
                           &S::func_ov116_0229e0c0,
                           &S::func_ov116_0229e074,
                           &S::func_ov116_0229e010,
                           &S::func_ov116_0229dfc0};
    int idx = subState;
    (this->*table[idx])();
}

#undef DISCARD_HANDLER
