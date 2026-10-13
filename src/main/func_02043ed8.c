/* func_02043ed8 @ 0x02043ed8, 0x290 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pair;
typedef struct {
    u8 unk_00;
    u16 unk_02;
    u16 unk_04;
} UnkStruct_02043ed8;

extern int func_0204eda8(void *node, int x, int y);
extern int func_02073d90(void *p);
extern int func_020984d4(void);
extern void func_0204457c(void *self, u16 *a, u16 *b, u8 *c, int d);
extern int func_0204a034(u16 *t);
extern int func_0204ba94(u16 *t);
extern int func_0204b3d0(u16 *t);
extern int func_0204f294(void *node, int x, int y);
extern int func_02042f20(void *g, void *self, int kind, Pair *w, int p5, int p6, int p7, int p8, int p9, int p10);

extern void *data_020ccf94;
extern int data_021c7c48;

int func_02043ed8(void *self, void *node, u16 *t, Pair *pt, unsigned short extra, int q)
{
    int ret;
    UnkStruct_02043ed8 info;
    Pair tmp;
    int kind;
    unsigned int v;
    int qd;
    unsigned int b;
    unsigned int a;
    unsigned int f;
    unsigned int w;
    int hi;

    kind = 0x17;
    ret = -1;
    if (func_0204eda8(node, pt->x, pt->y) == 0) {
        w = 0xfc;
    } else {
        w = 0xfd;
    }
    info.unk_02 = w;
    info.unk_00 = 0;
    info.unk_04 = *t;
    v = *t;
    if (v == 0xfff1) {
        switch (func_0204eda8(node, pt->x, pt->y)) {
            case 0:
            case 1:
                kind = 8;
                break;
            case 2:
                kind = 0xc;
                info.unk_02 = v;
                break;
            case 3:
                kind = 0x17;
                info.unk_02 = v;
                break;
        }
        goto done;
    }
    if (v >= 0xe3 && v <= 0xe7) {
        kind = 0xd;
        info.unk_02 = v;
        goto done;
    }
    if (v >= 0xe8 && v <= 0xfb) {
        kind = 0xc;
        info.unk_02 = v;
        if (func_02073d90(data_020ccf94) != 0) {
            goto done;
        }
        qd = (*t - 0xe8) / 5;
        if (qd != func_020984d4()) {
            goto done;
        }
        kind = 0xe;
        goto done;
    }
    if (v >= 0xfc && v <= 0xfd) {
        info.unk_02 = extra;
        info.unk_04 = extra;
        kind = 0x13;
        if (extra == 0xfff1) {
            goto done;
        }
        func_0204457c(self, &info.unk_02, &info.unk_04, &info.unk_00, extra);
        goto done;
    }
    if ((v >= 0x2b && v <= 0x2e) || (v >= 0xff && v <= 0x102) || (v >= 0x62 && v <= 0x65) || (v >= 0xd0 && v <= 0xd3)) {
        kind = 0xb;
        goto done;
    }
    if (func_0204a034(t) != 0 || v == 0x1b || v == 0x89) {
        kind = 0xc;
        info.unk_02 = *t;
        goto done;
    }
    a = b = 1;
    w = *t;
    if (w != 0x25 && w != 0x5c) {
        a = 0;
    }
    if (a == 0) {
        if (w != 0xc7) {
            b = 0;
        }
    }
    if (b != 0 ||
        ((w >= 0x26 && w <= 0x2a) || (w >= 0x5d && w <= 0x61) || (w >= 0x2f && w <= 0x56) || (w >= 0x57 && w <= 0x5b) ||
         (w >= 0x66 && w <= 0x68) || w == 0x69 || (w >= 0x6a && w <= 0x6c) || w == 0x6d || (w >= 0xc8 && w <= 0xcf)) &&
            func_0204ba94(t) != 0) {
        kind = 0xb;
        goto done;
    }
    if (func_0204b3d0(t) != 0) {
        goto lbl8;
    }
    f = 0;
    w = *t;
    if (w >= 0x21 && w <= 0x24) {
        f = 1;
    }
    if (f > 0) {
        goto lbl8;
    }
    if (w >= 0x1f && w <= 0x20) {
        goto lbl8;
    }
    if (w == 0xe2) {
    lbl8:
        kind = 8;
        goto done;
    }
    if (func_0204f294(node, pt->x, pt->y) == 0) {
        b = 1;
        a = 0;
        w = *t;
        if (w >= 0xd4 && w <= 0xda) {
            a = b;
        }
        if (a == 0) {
            if (w < 0xdb || w > 0xe1) {
                b = 0;
            }
        }
        if (b == 0) {
            goto hiblk;
        }
    }
    kind = 9;
    f = 0;
    w = *t;
    if (w >= 0xd4 && w <= 0xda) {
        f = 1;
    }
    if (f != 0) {
        info.unk_04 = w + 0x1467;
    } else {
        info.unk_04 = w + 0x1460;
    }
    goto done;
hiblk:
    hi = ((int) (w & 0xf000)) >> 12;
    if (hi == 1) {
        goto setc;
    }
    if (hi == 3) {
        goto setc;
    }
    if (hi != 4) {
        goto done;
    }
setc:
    kind = 0xc;
    info.unk_02 = w;
done:
    if (kind != 0) {
        tmp.x = pt->x;
        tmp.y = pt->y;
        ret = func_02042f20(&data_021c7c48, self, kind, &tmp, info.unk_02, info.unk_04, info.unk_00, 0, q, -1);
    }
    return ret;
}
