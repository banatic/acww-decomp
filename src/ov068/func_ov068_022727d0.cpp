/* func_ov068_022727d0 @ 0x022727d0, 0x5c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_022727d0Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

extern "C" {
extern int func_ov068_0227207c(void);
extern void func_02055060(Obj_020dd05c *, int, int, int, int, int);
extern void func_ov009_02262ef0(Obj_0213f090 *, int);
}

int Obj_ov068_02277750::func_ov068_022727d0()
{
    unk_2dd = 0;
    if (func_ov068_0227207c() == 0) {
        goto ret0;
    }
    {
        int v = vfunc_68();
        func_02055060(&unk_13c, v, 1, 0x1000, 0, 0);
    }
    func_ov009_02262ef0(&unk_238, 0x88a);
    return 1;
ret0:
    return 0;
}
