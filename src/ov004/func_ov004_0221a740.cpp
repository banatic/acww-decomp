/* func_ov004_0221a740 @ 0x0221a740, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/sp2 -O4,s
 * compiler-emitted symbol: _ZThn236_N18Obj_ov004_0225305817vfunc_02066994_18Ev
 */

#include "types.h"
#include "cpp/ov004/Obj_ov004_02253058.h"

extern "C" int func_0206837c(int h);
extern "C" int func_020ab504(int q);
extern "C" void func_0206844c(int h, void *p, int k);
extern "C" u8 data_021f43e8;

Obj_ov004_02253058::~Obj_ov004_02253058() {}

void Obj_ov004_02253058::vfunc_02066994_18()
{
    char *s = (char *) this;
    int r = func_020ab504(func_0206837c(*(int *) (s + 0x12c)));
    if (*(int *) (s + 0x858) == 1) {
        switch (r) {
            case 0:
                func_0206844c(*(int *) (s + 0x12c), &data_021f43e8, 0);
                vfunc_70(6, 0xff);
                break;
            case 1:
                vfunc_70(5, 0xff);
                break;
        }
    } else {
        switch (r) {
            case 0:
                func_0206844c(*(int *) (s + 0x12c), &data_021f43e8, 0);
                vfunc_70(0xa, 0xff);
                break;
            case 1:
                func_0206844c(*(int *) (s + 0x12c), &data_021f43e8, 0);
                vfunc_70(9, 0xff);
                break;
        }
    }
}
