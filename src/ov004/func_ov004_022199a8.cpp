/* func_ov004_022199a8 @ 0x022199a8, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_022525cc19func_ov004_022199a8Ev
 */

#include "cpp/ov004/Obj_ov004_022525cc.h"

#include "types.h"

extern "C" {
void func_ov004_0220d030(void *);
int func_ov004_0220e4b0(void *);
int func_ov004_0220ffbc(void *);
}

int Obj_ov004_022525cc::func_ov004_022199a8()
{
    char *self = (char *) this;
    u32 i;

    func_ov004_0220d030(&unk_84c);
    func_ov004_02219884();
    *(int *) (self + 0x5e4) = *(int *) (self + 0x848);
    for (i = 0; i < 0x4; i++) {
        if (func_ov004_0220e4b0(self + 0x7c4 + (i << 5)) != 0x0) {
            *(int *) (self + (i << 5) + 0x7d4) = *(int *) (self + 0x848);
        }
    }
    func_ov004_0220ffbc(self);
    return 0x1;
}
