/* func_ov003_0221bbac @ 0x0221bbac, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_0223863019func_ov003_0221bbacEv
 */

#include "cpp/ov003/Obj_ov003_02238630.h"

extern "C" {
int func_02096168(void);
int func_ov009_0226321c(void *self, int *a, short *s);
int func_ov003_02219a64(int n, int *a, int *b, short val);
}

void Obj_ov003_02238630::func_ov003_0221bbac()
{
    short s;
    int a[2];
    int b[2];
    short *ps;

    if (func_02096168()) {
        func_ov003_0221bfa8(9);
        return;
    }
    if (unk_2ba != 0) {
        return;
    }

    if (func_ov009_0226321c(this, a, &s)) {
        ps = &s;
        if (func_ov003_02219a64(2, a, b, *ps)) {
            unk_2ba = 1;
        }
    }
}
