/* func_020bae60 @ 0x020bae60, 0x230 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Head {
    int unk_00;
    int unk_04;
};
struct UnkStruct_020bae60_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};
struct UnkStruct_020bae60 {
    int x;
    int y;
    short z;
};

extern struct Head data_021f75b0;
extern u16 data_021f87c0[];
extern char data_021f75b8[];
extern int data_021f8b44;
extern int data_021f87b8;
extern u8 data_021f6cbc;
extern int data_021f6ce8[];
extern int data_021f6ce0[];
extern u16 data_020e597c[];

extern void *func_020961a8(int a);
extern int func_020655c4(int a);

void func_020bae60(void)
{
    int a;
    int e;
    int slot;
    u16 *pal;
    void *o;
    struct UnkStruct_020bae60_2 *sub;
    int v;
    int angle;
    int j, i, n;
    struct UnkStruct_020bae60 *p;
    struct UnkStruct_020bae60 *end;
    int t1, t2;
    int da, dang;
    int x;
    u16 c;
    unsigned int t;
    int lo, hi;
    int *ap;
    int prod;
    int d;
    int w2;

    a = 0;
    e = 0;
    slot = (data_021f75b0.unk_04 + 1) % 2;
    pal = (u16 *) ((char *) data_021f87c0 + slot * 0x180);
    o = func_020961a8(4);
    if (o != 0) {
        sub = (struct UnkStruct_020bae60_2 *) ((char *) o + 0x5c);
        if (sub != 0) {
            int *gp;
            int w;
            a = sub->unk_00 >> 3;
            gp = &data_021f8b44;
            w = sub->unk_08;
            v = (w - *gp) >> 4;
            if (v < 0) {
                e = (v * -0xb0) >> 8;
            } else {
                e = (-(v * 0x80)) >> 8;
            }
            *gp = w;
        }
    }
    ap = &data_021f87b8;
    angle = *ap + 0x60 + e;
    if (angle >= 0x10000) {
        angle -= 0x10000;
    }
    *ap = angle;

    if (data_021f6cbc == 0) {
        data_021f6cbc = 1;
        for (i = 0; i < 2; i++) {
            data_021f6ce8[i] = a;
            data_021f6ce0[i] = angle;
            p = (struct UnkStruct_020bae60 *) (data_021f75b8 + i * 0x900);
            for (j = 0; j < 0xc0; j++) {
                t1 = (-(j << 8)) / 0xc0;
                p->z = (short) (0x10000 / (t1 + 0x200));
                w2 = (p->z - 0x100) << 7;
                w2 = -w2;
                p->x = a + w2;
                t2 = ((0xc000 * j) / 0xc0 + 0x3000) / 0xc0;
                p->y = angle + 0xc0 * ((t2 * t2) >> 8);
                p++;
            }
        }
    }

    da = a - data_021f6ce8[slot];
    dang = angle - data_021f6ce0[slot];
    if (da != 0 || dang != 0) {
        data_021f6ce8[slot] = a;
        data_021f6ce0[slot] = angle;
        p = (struct UnkStruct_020bae60 *) (data_021f75b8 + slot * 0x900);
        end = (struct UnkStruct_020bae60 *) ((char *) p + 0x900);
        if (dang == 0) {
            for (; p < end; p++) {
                p->x += da;
            }
        } else if (da == 0) {
            for (; p < end; p++) {
                p->y += dang;
            }
        } else {
            for (; p < end; p++) {
                p->x += da;
                p->y += dang;
            }
        }
    }

    n = 0;
    x = func_020655c4(1);
    if (x == data_020e597c[slot]) {
        goto done;
    }
    data_020e597c[slot] = (u16) x;
    c = (u16) (x | 0x1000);
    for (; n < 0x77; n++) {
        *pal = c;
        pal++;
    }
    for (; n < 0x97; n++) {
        prod = x;
        prod = (n - 0x77) * prod;
        d = (int) ((unsigned int) prod >> 5);
        *pal = (u16) ((x - d) | 0x1000);
        pal++;
    }
    for (; n < 0x98; n++) {
        *pal = 0x10;
        pal++;
    }
    for (; n < 0xa8; n++) {
        t = (unsigned int) ((n - 0x98) * 0x10) / 0x10;
        lo = 0x10 - (int) t;
        hi = 0x10 - lo;
        *pal = (u16) (lo | (hi << 8));
        pal++;
    }
    for (; n < 0xc0; n++) {
        *pal = 0x1000;
        pal++;
    }
done:
    data_021f75b0.unk_04 = slot;
}
