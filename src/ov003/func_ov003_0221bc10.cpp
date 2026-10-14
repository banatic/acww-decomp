/* func_ov003_0221bc10 @ 0x0221bc10, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221bc10Ev
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

extern "C" {
int func_02096174(void);
void func_0203ee08(void *, void *);
}

void Obj_ov003_02238630::func_ov003_0221bc10()
{
    if (func_02096174()) {
        if (func_ov003_0221bfa8(8)) {
            void *recv = this;
            if (this) {
                recv = (char *) this + 0xec;
            }
            func_0203ee08(this, recv);
        }
    }
}
