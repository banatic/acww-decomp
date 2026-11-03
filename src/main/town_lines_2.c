/* town_lines_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204a198 @ 0x0204a198, 0x68 bytes, Thumb
 * func_0204a150 @ 0x0204a150, 0x48 bytes, Thumb
 * func_0204a034 @ 0x0204a034, 0x11c bytes, Thumb
 * func_02049ff0 @ 0x02049ff0, 0x42 bytes, Thumb
 * func_02049fbc @ 0x02049fbc, 0x32 bytes, Thumb
 * func_02049f74 @ 0x02049f74, 0x48 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0204a150 {
    unsigned short x;
};

struct UnkStruct_02049f74 {
    int unk_00;
    int unk_04;
};

extern unsigned char data_021c7a08[];
extern void func_0204a25c(int, int, int, unsigned short, int);
extern int func_0204b8d4(struct UnkStruct_0204a150 *);
extern int func_0204b910(struct UnkStruct_0204a150 *);
extern int func_0204bbec(u16 *);
extern int func_0204ba94(u16 *);
extern int func_0204f5e0(int a, int b, int c, int d, int e, int f);

void func_0204a198(int p0, unsigned short id, int x, int y)
{
    unsigned char v;
    unsigned char *p;
    int ox, oy, xb, yb;

    v = 0x25;
    switch (id) {
        case 0x26:
            break;
        case 0x5d:
            v = 0x5c;
            break;
        case 0xc8:
            v = 0xc7;
            break;
    }

    ox = x >> 4;
    oy = y >> 4;
    xb = (x - (ox << 4)) >> 3;
    yb = (y - (oy << 4)) >> 3;
    p = data_021c7a08 + ox * 0x90 + oy * 0x24 + 4 + (xb << 1) + yb;
    *p -= 1;

    func_0204a25c(p0, x, y, v, 0);
}

void func_0204a150(int a, struct UnkStruct_0204a150 *b, int c, int d)
{
    unsigned short x = b->x;
    if (func_0204b8d4(b) != 0) {
        x = x - 3;
    } else if (func_0204b910(b) == 0) {
        x = x + 1;
    }
    func_0204a25c(a, c, d, x, 0);
}

int func_0204a034(u16 *p)
{
    int b8, b7, b6, b5, b4, b3, b2, b1, b0;
    int c3, c2, c1, c0;
    int ret;
    u16 v;

    ret = 0;
    if (func_0204bbec(p)) {
        ret = 1;
    } else {
        b8 = 1;
        b7 = 1;
        b6 = 1;
        b5 = 1;
        b4 = 1;
        b3 = 1;
        b2 = 1;
        b1 = 1;
        b0 = 0;
        v = *p;
        if (v >= 0x26 && v <= 0x2a) {
            b0 = 1;
        }
        if (!b0 && !(v >= 0x5d && v <= 0x61)) {
            b1 = 0;
        }
        if (!b1 && !(v >= 0x2f && v <= 0x56)) {
            b2 = 0;
        }
        if (!b2 && !(v >= 0x57 && v <= 0x5b)) {
            b3 = 0;
        }
        if (!b3 && !(v >= 0x66 && v <= 0x68)) {
            b4 = 0;
        }
        if (!b4 && !(v == 0x69)) {
            b5 = 0;
        }
        if (!b5 && !(v >= 0x6a && v <= 0x6c)) {
            b6 = 0;
        }
        if (!b6 && !(v == 0x6d)) {
            b7 = 0;
        }
        if (!b7 && !(v >= 0xc8 && v <= 0xcf)) {
            b8 = 0;
        }
        if (b8 && func_0204ba94(p) == 0) {
            ret = 1;
        } else {
            c3 = 1;
            c2 = 1;
            c1 = 1;
            c0 = 0;
            v = *p;
            if (v >= 0x2b && v <= 0x2e) {
                c0 = 1;
            }
            if (!c0 && !(v >= 0xff && v <= 0x102)) {
                c1 = 0;
            }
            if (!c1 && !(v >= 0x62 && v <= 0x65)) {
                c2 = 0;
            }
            if (!c2 && !(v >= 0xd0 && v <= 0xd3)) {
                c3 = 0;
            }
            if (c3) {
                ret = 1;
            }
        }
    }
    return ret;
}

int func_02049ff0(unsigned short *a)
{
    int flag = 0;
    if (func_0204a034((u16 *) a) != 0) {
        flag = 1;
    } else {
        int r2 = 1;
        int r1 = flag;
        unsigned int val = *a;
        if (val >= 0xe3 && val <= 0xe7) {
            r1 = 1;
        }
        if (r1 == 0) {
            if (val < 0xe8 || val > 0xfb) {
                r2 = 0;
            }
        }
        if (r2 != 0) {
            flag = 1;
        }
    }
    return flag;
}

int func_02049fbc(int a, int *p)
{
    unsigned short *tested_value0;
    int result = 0;
    int x = p[0];
    int y = p[1];
    int high1 = x >> 4;
    int high2 = y >> 4;
    int low2 = y - (high2 << 4);

    if ((tested_value0 = (unsigned short *) (func_0204f5e0(a, high1, high2, x - (high1 << 4), low2, result)))) {
        result = func_02049ff0(tested_value0);
    }
    return result;
}

int func_02049f74(int param0, struct UnkStruct_02049f74 *param1)
{
    unsigned short *result;
    int f0, f1, hi0, hi1, low0, low1;

    f0 = param1->unk_00;
    f1 = param1->unk_04;
    hi0 = f0 >> 4;
    hi1 = f1 >> 4;
    low1 = f1 - (hi1 << 4);
    low0 = f0 - (hi0 << 4);

    result = (unsigned short *) func_0204f5e0(param0, hi0, hi1, low0, low1, 0);

    if (result != 0 && func_0204ba94((u16 *) result) != 0) {
        func_0204a198(param0, *result, param1->unk_00, param1->unk_04);
    }

    return 0;
}
