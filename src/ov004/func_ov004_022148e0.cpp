/* func_ov004_022148e0 @ 0x022148e0, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225282419func_ov004_022148e0Ev
 */

#include "cpp/ov004/Obj_ov004_02252824.h"

extern "C" {
void func_02054cdc(void *);
int func_02054ec4(void *);
void func_02056ffc(void *);
int func_ov004_0220e4b0(void *);
}

int Obj_ov004_02252824::func_ov004_022148e0()
{
    char *self = (char *) this;

    func_ov004_0221479c();
    if (func_02054ec4(self + 0x538) != 0x0) {
        func_02054cdc(self + 0x538);
    }
    if (func_ov004_0220e4b0(self + 0x7e4) != 0x0) {
        func_02056ffc(self + 0x7e4);
        *(int *) ((char *) *(int *) (self + 0x7fc)) = *(int *) (self + 0x7ec);
    }
    if (func_ov004_0220e4b0(self + 0x804) != 0x0) {
        func_02056ffc(self + 0x804);
        *(int *) ((char *) *(int *) (self + 0x81c)) = *(int *) (self + 0x80c);
    }
    if (func_ov004_0220e4b0(self + 0x824) != 0x0) {
        func_02056ffc(self + 0x824);
        *(int *) ((char *) *(int *) (self + 0x83c)) = *(int *) (self + 0x82c);
    }
    return 0x1;
}
