/* func_ov096_0229ef30 @ 0x0229ef30, 0x124 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xb4];
    u8 unk_B4;
} UnkStruct_0229ef30;

extern int func_ov096_0229f830(UnkStruct_0229ef30 *self, int a);
extern int func_ov096_0229f820(UnkStruct_0229ef30 *self, int a);
extern int func_ov096_0229f150(UnkStruct_0229ef30 *self, int a);
extern int func_ov096_0229f054(UnkStruct_0229ef30 *self, int a);
extern int func_02065f18(int h);
extern int func_02065ec0(int h);
extern int func_ov094_02299a54(int b);
extern int func_ov094_02299b04(int b);
extern int func_ov096_0229e158(UnkStruct_0229ef30 *self);
extern int func_0204c878(volatile u16 *p);

int func_ov096_0229ef30(UnkStruct_0229ef30 *self, int a, int b, int c)
{
    volatile u16 t;
    int h;
    int k;
    int d;
    unsigned int ok;
    u16 lo, hi;

    t = 0xfff1;
    if (func_ov096_0229f830(self, a) != 0) {
        return 0;
    }
    if (func_ov096_0229f820(self, a) != 0) {
        if (func_ov096_0229f150(self, a) != 0) {
            return 6;
        }
        if (c == 1) {
            return 5;
        }
        if (c == 2) {
            return 1;
        }
        h = func_ov096_0229f054(self, a);
        if (func_02065f18(h) != 0xfff1) {
            return 3;
        }
        k = func_02065ec0(h);
        if (k == 7 || k == 8 || func_ov094_02299a54(b) != 0) {
            return 2;
        }
        if (func_ov094_02299b04(b) != 0) {
            return 4;
        }
        t = (u16) b;
        ok = 0;
        lo = t;
        hi = t;
        if (hi >= 0x1492 && lo <= 0x14fd) {
            ok = 1;
        }
        if (ok != 0 && self->unk_B4 == 0x25) {
            return 5;
        }
        return 0;
    }
    if (a == 0x25) {
        if (c != 0) {
            return 6;
        }
        t = (u16) b;
        ok = 0;
        lo = t;
        hi = t;
        if (hi >= 0x1492 && lo <= 0x14fd) {
            ok = 1;
        }
        if (ok == 0) {
            return 6;
        }
        d = 0x1869f - func_ov096_0229e158(self);
        if (d < func_0204c878(&t)) {
            return 6;
        }
        return 0;
    }
    switch (a) {
        case 0x24:
            return 6;
        default:
            return 6;
    }
}
