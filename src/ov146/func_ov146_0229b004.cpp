/* func_ov146_0229b004 @ 0x0229b004, 0x94 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov146_0229b68019func_ov146_0229b004Ev
 */

#include "cpp/ov146/Obj_ov146_0229b680.h"

extern "C" void func_ov146_0229aca0(void *);
extern "C" void func_ov146_0229ac18(void *);

typedef void (Obj_ov146_0229b680::*StateHandler)();

#define DISCARD_HANDLER(Class, Method) (StateHandler) & Class::Method

int Obj_ov146_0229b680::func_ov146_0229b004()
{
    static StateHandler pmf[4] = {&Obj_ov146_0229b680::func_ov146_0229ae90, &Obj_ov146_0229b680::func_ov146_0229ae60,
                                  &Obj_ov146_0229b680::func_ov146_0229ae28,
                                  DISCARD_HANDLER(Obj_ov146_0229b680, func_ov146_0229adf8)};
    func_ov146_0229aca0(this);
    (this->*pmf[state])();
    func_ov146_0229ac18(this);
    return 1;
}

#undef DISCARD_HANDLER
