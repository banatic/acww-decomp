/* func_ov004_0221a75c @ 0x0221a75c, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/sp2 -O4,s
 * compiler-emitted symbol: _ZThn236_N18Obj_ov004_0225305817vfunc_02066994_14Ev
 */

#include "types.h"
#include "cpp/ov004/Obj_ov004_02253058.h"

extern "C" int func_0206837c(int h);
extern "C" void func_020ab670(int q, int a, int b);
extern "C" void func_020ab628(int q, int a, u8 *p, int b, u8 *c, int d, int e);
extern "C" void func_020ab5f8(int q);
extern "C" void func_02068388(int h, int a);
extern "C" u8 data_021f43e8;

Obj_ov004_02253058::~Obj_ov004_02253058() {}

void Obj_ov004_02253058::vfunc_02066994_14()
{
    char *s = (char *) this;
    u8 buf[4];
    int h;
    int q;
    if (*(u8 *) (s + 0x10a) == 0) {
        h = *(int *) (s + 0x12c);
        q = func_0206837c(h);
        func_020ab670(q, 2, 1);
        buf[0] = 0xc;
        buf[1] = data_021f43e8;
        func_020ab628(q, 0, &buf[0], 1, &buf[1], 0, 2);
        buf[2] = 0xd;
        buf[3] = data_021f43e8;
        func_020ab628(q, 1, &buf[2], 1, &buf[3], 0, 0);
        func_020ab5f8(q);
        func_02068388(h, 1);
    }
    if (*(u8 *) (s + 0x10a) == 0x19) {
        vfunc_70(5, 0xff);
    }
}
