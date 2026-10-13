/* func_ov141_0229ac60 @ 0x0229ac60, 0xa0 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov141_0229af4819func_ov141_0229ac60Ev
 */

#include "cpp/ov141/Obj_ov141_0229af48.h"

extern "C" void func_ov141_0229a934(void *);
extern "C" void func_ov141_0229a91c(void *);

int Obj_ov141_0229af48::func_ov141_0229ac60()
{
    static void (Obj_ov141_0229af48::*table[5])() = {
        &Obj_ov141_0229af48::func_ov141_0229ab04, &Obj_ov141_0229af48::func_ov141_0229aac4,
        &Obj_ov141_0229af48::func_ov141_0229aa94, &Obj_ov141_0229af48::func_ov141_0229aa54,
        &Obj_ov141_0229af48::func_ov141_0229aa28};
    func_ov141_0229a934(this);
    (this->*table[state])();
    func_ov141_0229a91c(this);
    return 1;
}
