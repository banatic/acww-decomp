/* func_02030920 @ 0x02030920, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// keep holds the loaded value because v is reassigned by the fourth flag test.

typedef struct UnkStruct_02030920 {
    u8 pad_00[0xc];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 pad_10[0x1e - 0x10];
} UnkStruct_02030920;

extern UnkStruct_02030920 data_020c907c[];
extern u8 **func_01ffcb5c(int a, int b);

int func_02030920(int x, int y, int flags)
{
    u8 **cellp;
    u8 *base;
    u8 *cell;
    int off;
    int v;
    int keep;
    int a0, a1, a2;
    int t0, t1, t2, t3;
    unsigned int i;

    cellp = func_01ffcb5c(x >> 4, y >> 4);
    if (cellp == 0) {
        goto ret0b;
    }
    base = *cellp;
    x = x & 0xf;
    y = y & 0xf;
    off = x + (y << 4);
    cell = base + off;
    v = base[off];
    keep = v;
    if (flags & 1) {
        a0 = 0xa;
    } else {
        a0 = v;
    }
    if ((flags >> 1) & 1) {
        a1 = 0xa;
    } else {
        a1 = v;
    }
    if ((flags >> 2) & 1) {
        a2 = 0xa;
    } else {
        a2 = v;
    }
    if ((flags >> 3) & 1) {
        v = 0xa;
    }
    i = 0;
    goto test;
body:
    if ((int) i < 0x7c) {
        t0 = data_020c907c[i].unk_0C;
    } else {
        t0 = 0;
    }
    if (a0 == t0) {
        if ((int) i < 0x7c) {
            t1 = data_020c907c[i].unk_0D;
        } else {
            t1 = 0;
        }
        if (a1 == t1) {
            if ((int) i < 0x7c) {
                t2 = data_020c907c[i].unk_0E;
            } else {
                t2 = 0;
            }
            if (a2 == t2) {
                if ((int) i < 0x7c) {
                    t3 = data_020c907c[i].unk_0F;
                } else {
                    t3 = 0;
                }
                if (v == t3) {
                    goto found;
                }
            }
        }
    }
    i++;
test:
    if (i < 0x7c) {
        goto body;
    }
    i = 0;
found:
    if (keep != 0) {
        *cell = (u8) i;
        return 1;
    }
    *cell = 0xa;
    return 0;
ret0b:
    return 0;
}
