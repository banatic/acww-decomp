/* func_ov009_022634f0 @ 0x022634f0, 0x56 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_022634f0Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" {
int func_ov009_0226321c(Obj_ov009_022658dc *self, int *a, short *b);
void *func_02095794(int);
int func_ov003_02219a64(int a, int *b, int *c, int d);
}

void Obj_ov009_022658dc::func_ov009_022634f0()
{
    struct Locals {
        short b; // offset 0
        int c;   // offset 4
        int a;   // offset 8
        int pad; // offset 12
        int d;   // offset 16
    } loc;

    if (func_ov009_0226321c(this, &loc.a, &loc.b) != 0) {
        loc.c = loc.a;
        if (vfunc_94() == 0) {
            void *ptr = func_02095794(4);
            if (ptr) {
                loc.c = *(int *) ptr;
            }
        }
        if (func_ov003_02219a64(2, &loc.c, &loc.d, (int) loc.b) != 0) {
            func_ov009_022639a0(6);
        }
    }
}
