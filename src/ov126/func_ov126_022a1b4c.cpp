/* func_ov126_022a1b4c @ 0x022a1b4c, 0x140 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov126_022a20c819func_ov126_022a1b4cEv
 */

#include "cpp/ov126/Obj_ov126_022a20c8.h"

typedef Obj_ov126_022a20c8 S;

void Obj_ov126_022a20c8::func_ov126_022a1b4c()
{
    static void (S::*table[17])() = {&S::func_ov126_022a1228, &S::func_ov126_022a11d8, &S::func_ov126_022a117c,
                                     &S::func_ov126_022a1108, &S::func_ov126_022a1038, &S::func_ov126_022a1020,
                                     &S::func_ov126_022a0f40, &S::func_ov126_022a0ec4, &S::func_ov126_022a0e98,
                                     &S::func_ov126_022a0e10, &S::func_ov126_022a0db4, &S::func_ov126_022a0d8c,
                                     &S::func_ov126_022a0d30, &S::func_ov126_022a0d00, &S::func_ov126_022a0cd0,
                                     &S::func_ov126_022a0c64, &S::func_ov126_022a0c34};
    return (this->*table[subState])();
}
