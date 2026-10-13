/* func_ov068_022728c4 @ 0x022728c4, 0x38 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_022728c4Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" {
void func_0203e334(void *);
void *func_02055060(Obj_020dd05c *, int, int, int);
}

int Obj_ov068_02277750::func_ov068_022728c4()
{
    int x = vfunc_64();
    volatile int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0203e334(func_02055060(&unk_13c, x, 1, 0x1000));
    return 1;
}
