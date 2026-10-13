/* func_ov004_022358c0 @ 0x022358c0, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022358c0 {
    int a;
    ~UnkStruct_022358c0() {}
};

extern "C" {
extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);
}
extern "C" void func_ov004_022358c0(char *self, int cap)
{
    UnkStruct_022358c0 t;
    int v;
    u8 m = *(u8 *) (self + 0x1ee);
    if (m == 1) {
        v = 0x1800;
    } else {
        v = *(int *) (self + 0x20c);
        if (m == 3) {
            v = 3 * v;
        } else if (m == 5) {
            v = v / 3;
        }
        v = FX_Div(v, *(int *) (self + 0x210));
        v = FX_MulFunc(v, 0x1800);
        if (v < cap) {
            v = cap;
        } else if (v > 0x1800) {
            v = 0x1800;
        }
    }
    *(int *) (self + 0x110) = v;
}
