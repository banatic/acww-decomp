/* func_02030a18 @ 0x02030a18, 0x168 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02030a18 {
    u8 pad_00[6];
    short unk_06;
    u8 pad_08[0xc - 8];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 pad_10[0x1e - 0x10];
} UnkStruct_02030a18;

extern UnkStruct_02030a18 data_020c907c[];
extern u8 data_020c9082[];
extern u8 data_020c9088[];
extern u8 data_020c9089[];
extern u8 data_020c908a[];
extern u8 data_020c908b[];

extern u8 **func_01ffcb5c(int a, int b);

int func_02030a18(int x, int y)
{
    u8 **cellp;
    u8 *base;
    u8 *cell;
    int off;
    int v;
    int k;
    int a7;
    int a4;
    int a5;
    int a6;
    int t;
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
    if (v < 0x7c) {
        k = *(short *) (data_020c9082 + v * 0x1e);
        if (k > 0) {
            k = 1;
        }
    } else {
        k = -1;
    }
    if (k != 1) {
        goto ret1;
    }
    if (v == 3) {
        *cell = 0x1d;
        return 1;
    }
    if (v == 9) {
        *cell = 0x1e;
        return 1;
    }
    if (v < 0x7c) {
        a7 = data_020c9088[v * 0x1e];
    } else {
        a7 = 0;
    }
    if (v < 0x7c) {
        a4 = data_020c9089[v * 0x1e];
    } else {
        a4 = 0;
    }
    if (v < 0x7c) {
        a5 = data_020c908a[v * 0x1e];
    } else {
        a5 = 0;
    }
    if (v < 0x7c) {
        a6 = data_020c908b[v * 0x1e];
    } else {
        a6 = 0;
    }
    i = 0;
    goto test;
body:
    if ((int) i < 0x7c) {
        t = data_020c907c[i].unk_06;
        if (t > 0) {
            t = 1;
        }
    } else {
        t = -1;
    }
    if (t == 0) {
        if ((int) i < 0x7c) {
            t = data_020c907c[i].unk_0C;
        } else {
            t = 0;
        }
        if (a7 == t) {
            if ((int) i < 0x7c) {
                t = data_020c907c[i].unk_0D;
            } else {
                t = 0;
            }
            if (a4 == t) {
                if ((int) i < 0x7c) {
                    t = data_020c907c[i].unk_0E;
                } else {
                    t = 0;
                }
                if (a5 == t) {
                    if ((int) i < 0x7c) {
                        t = data_020c907c[i].unk_0F;
                    } else {
                        t = 0;
                    }
                    if (a6 == t) {
                        *cell = (u8) i;
                        return 1;
                    }
                }
            }
        }
    }
    i++;
test:
    if (i < 0x7c) {
        goto body;
    }
    return 0;
ret1:
    return 1;
ret0b:
    return 0;
}
