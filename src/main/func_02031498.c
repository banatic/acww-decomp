/* func_02031498 @ 0x02031498, 0x170 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Cell {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 pad_14[4];
} Cell;

extern u8 data_020c9090[];
extern void *func_01ffcb5c(int a, int b);
extern void func_02034448(Cell *c, int x, int y, int k);

int func_02031498(int *p0, int *p1, int gx, int gy)
{
    int bx;
    int by;
    int oy;
    int res;
    int yy;
    int c0;
    int c1;
    int c2;
    int c3;
    int c4;
    Cell A;
    Cell B;
    Cell C;
    int ix;
    int f2;
    int f1;
    int g;
    int h;
    int q;
    int w;

    if (func_01ffcb5c(gx, gy) == 0) {
        return 4;
    }
    bx = gx << 4;
    by = gy << 4;
    oy = 0;
    c0 = 0;
    c1 = 0;
    c2 = 0;
    c3 = 0;
    c4 = 0;
    goto touter;
obody:
    ix = c0;
    yy = by + oy;
    goto tinner;
ibody:
    *p0 = bx + ix;
    *p1 = yy;
    func_02034448(&A, *p0, *p1, c1);
    func_02034448(&B, *p0 + 1, *p1, c2);
    res = c3;
    f2 = c3;
    f1 = c3;
    if (A.unk_10 == 0x14 && A.unk_11 == 0x14) {
        f1 = 1;
    }
    if (f1 != 0) {
        if (A.unk_12 == 0x14) {
            f2 = 1;
        }
    }
    if (f2 != 0) {
        if (A.unk_13 == 0x14) {
            res = 1;
        }
    }
    if (res != 0) {
        if (B.unk_10 == 0x14 && B.unk_11 == 0x14 && B.unk_12 == 0x14 && B.unk_13 == 0x14) {
            g = 1;
        } else {
            g = c4;
        }
        if (g != 0) {
            func_02034448(&C, *p0 + 2, *p1, 0);
            if (C.unk_10 == 0x14 && C.unk_11 == 0x14 && C.unk_12 == 0x14 && C.unk_13 == 0x14) {
                h = 1;
            } else {
                h = 0;
            }
            if (h != 0) {
                return 1;
            }
            return 0;
        }
    }
    if (A.unk_10 != 0x14 && A.unk_11 != 0x14 && A.unk_12 == 0x14 && A.unk_13 == 0x14 && B.unk_10 != 0x14 && B.unk_11 == 0x14 &&
        B.unk_12 == 0x14) {
        q = B.unk_13;
        if (q != 0x14) {
            if (q < 0x7c) {
                w = data_020c9090[q * 0x1e];
            } else {
                w = 0;
            }
            if (w == 0) {
                return 2;
            }
            return 3;
        }
    }
    ix++;
tinner:
    if (ix < 0x10) {
        goto ibody;
    }
    oy++;
touter:
    if (oy < 0x10) {
        goto obody;
    }
    return 4;
}
