/* town_insect_5: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222f524 @ 0x0222f524, 0x4c bytes, Thumb
 * func_ov003_0222f490 @ 0x0222f490, 0x94 bytes, Thumb
 * func_ov003_0222f458 @ 0x0222f458, 0x38 bytes, Thumb
 * func_ov003_0222f320 @ 0x0222f320, 0x138 bytes, Thumb
 * func_ov003_0222efc0 @ 0x0222efc0, 0x360 bytes, Thumb
 * func_ov003_0222ef80 @ 0x0222ef80, 0x40 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222f524 {
    u8 pad_00[0x24d];
    s8 unk_24D;
    u8 pad_24E[6];
    u8 unk_254;
    u8 unk_255;
    u8 pad_256[0x25c - 0x256];
};

struct UnkStruct_0222f490 {
    u8 pad_00[0x24d];
    s8 unk_24D;
    u8 pad_24E[0x25c - 0x24e];
};

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

struct UnkStruct_0222f458 {
    u8 pad_00[0x204];
    Vec3 unk_204;
    u8 pad_210[0x24d - 0x210];
    s8 unk_24D;
    u8 pad_24E[0x25c - 0x24e];
};

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222f320;

typedef struct {
    int x, y, z;
} UnkStruct_0222efc0;

extern struct UnkStruct_0222f524 data_ov003_022617bc[];
extern UnkStruct_0222f320 *data_020ccf94;
extern volatile u8 data_ov003_02260534;
extern u8 data_ov003_02260538;
extern char data_ov003_02260bf0[];
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern void func_ov003_0222d300(void);
extern int func_ov003_0222da9c(void *self, int a, int b, int c);
extern int func_ov003_0222d484(s8 *a, s8 *b, int c);
extern int func_ov003_0222db40(void *self, int a, u8 b, int c);
extern void func_ov068_0226fe00(char *p);
extern int func_02096614(int *a, int *b, int *c, int d, int e);
extern void func_ov003_0222dec4(void *self, int a, int b, int c, int d);
extern void func_ov003_0222ddb8(void *self, int a);
extern int func_ov003_02235ce8(char *a, int i, int k, UnkStruct_0222efc0 *p, int m, int n);
extern int func_ov003_02235c34(char *a, int i, signed char *kd, int *n, int *m, u8 *msg);
extern void func_ov003_0222fe18(char *a, char *e, int k);
extern int func_ov003_0222ee10(char *a, char *e);
extern void func_ov003_0222fa20(char *a, char *e, int mode);
extern int func_020ba4e4(void);
extern int func_ov003_0222d248(int k, int r);
extern void func_ov003_0222f6b0(char *a, char *e, int f, int mode);
extern void func_020042c0(char *p, UnkStruct_0222efc0 *v);
extern void func_02073820(char *g);
extern void func_020737f0(char *g, u8 *p, int n);
extern void func_02073770(char *g, int a, int b);
extern int func_020ea990(void *p, int *blk);

int func_ov003_0222ef80(int a, unsigned char *obj, int idx, int c, int e);

int func_ov003_0222f524(u8 *out, int idx)
{
    u8 k = (u8) (idx & 0xf);
    struct UnkStruct_0222f524 *e = &data_ov003_022617bc[k];
    int v = e->unk_24D;

    if (v >= 0) {
        if (e->unk_254 >= e->unk_255) {
            *out = 1;
        } else {
            *out = 0;
        }
    }
    return v;
}

int func_ov003_0222f490(int idx)
{
    u8 k = (u8) (idx & 0xf);
    struct UnkStruct_0222f490 *e = &((struct UnkStruct_0222f490 *) data_ov003_022617bc)[k];

    switch (e->unk_24D) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 31:
        case 33:
        case 34:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 52:
            return 1;
        default:
            return 0;
    }
}

int func_ov003_0222f458(Vec3 *dst, int idx)
{
    u8 k = (u8) (idx & 0xf);
    struct UnkStruct_0222f458 *e = &((struct UnkStruct_0222f458 *) data_ov003_022617bc)[k];
    Vec3 *s = &e->unk_204;

    dst->x = s->x;
    dst->y = s->y;
    dst->z = s->z;
    return e->unk_24D;
}

void func_ov003_0222f320(void *self)
{
    s8 b[4];
    int x;
    int y;
    int z;
    int on;
    u8 v;
    u8 i;

    on = func_02073dd4(data_020ccf94, data_020ccf94->unk_64);
    if (on == 0 || func_020a7278() != 0) {
        if (data_ov003_02260534 % 0x14 == 0) {
            func_ov003_0222d300();
        }
        data_ov003_02260534 = data_ov003_02260534 + 1;
        v = data_ov003_02260534;
        if (v == 0x3c) {
            func_ov003_0222da9c(self, 1, 0, -1);
            data_ov003_02260534 = 0;
        } else if (v == 0x28 && on == 0) {
            b[0] = 0;
            b[1] = -1;
            if (func_ov003_0222d484(&b[0], &b[1], 1) != 0 && func_ov003_0222da9c(self, 1, b[0], b[1]) != 0) {
                data_ov003_02260534 = 0;
            }
        } else if (v == 0x14 && on == 0) {
            b[2] = 0;
            b[3] = -1;
            if (func_ov003_0222d484(&b[2], &b[3], 0) != 0 && func_ov003_0222db40(self, b[2], (u8) b[3], 2) != 0) {
                func_ov068_0226fe00(data_ov003_02260bf0);
                data_ov003_02260538 = 0;
            }
        }
    }
    if (on != 0) {
        for (i = 0; i < 4; i++) {
            if (func_02096614(&x, &y, &z, -1, i) != 0 && *(u8 *) &x == 0) {
                func_ov003_0222dec4(self, 1, i, y, z);
            }
        }
    } else {
        func_ov003_0222ddb8(self, 1);
        func_ov003_0222ddb8(self, 2);
    }
}

void func_ov003_0222efc0(char *a)
{
    char *e;
    UnkStruct_0222efc0 *p204;
    UnkStruct_0222efc0 *p1d4;
    UnkStruct_0222efc0 *q;
    s16 *p242;
    UnkStruct_0222efc0 w;
    UnkStruct_0222efc0 w2;
    int state;
    char *g;
    int n, m;
    int neg;
    int v;
    int kk;
    signed char kd;
    u8 i;
    u8 msg;

    e = ((char *) data_ov003_022617bc);
    n = 0;
    m = 0;
    i = 0;
    g = (*(char * *) &data_020ccf94);
    neg = -1;
    for (; i < 8; i++) {
        state = *(u8 *) (e + 0x250);
        if (func_02073dd4((void *) g, *(int *) (g + 0x64)) != 0) {
            p204 = (UnkStruct_0222efc0 *) (e + 0x204);
            p1d4 = (UnkStruct_0222efc0 *) (e + 0x1d4);
            kd = neg;
            if (func_ov003_02235ce8(a, i, *(signed char *) (e + 0x24d), p1d4, *(u8 *) (e + 0x254), 1) != 0) {
                goto sw;
            }
            msg = 0;
            if (func_ov003_02235c34(a, i, &kd, &n, &m, &msg) == 0) {
                goto sw;
            }
            if (state == 0) {
                if (n > 1) {
                    if (kd >= 0) {
                        p204->x = n;
                        p204->z = m;
                        p1d4->x = p204->x;
                        p1d4->y = p204->y;
                        p1d4->z = p204->z;
                        *(signed char *) (e + 0x24d) = kd;
                        *(u8 *) (e + 0x248) = 1;
                        *(u8 *) (e + 0x249) = 0;
                        q = (UnkStruct_0222efc0 *) (e + 0x1c8);
                        q->x = p204->x;
                        q->y = p204->y;
                        q->z = p204->z;
                        *(u8 *) (e + 0x250) = 2;
                    }
                }
            } else if (msg == 0xff || n == 1) {
                if (kd == 0x1e) {
                    v = *(u8 *) (e + 0x251);
                    if (v == 9 || v == 0x11) {
                        goto sw;
                    }
                }
                func_ov003_0222fe18(a, e, 1);
            } else {
                if (p1d4->x != n || p1d4->z != m) {
                    p1d4->x = n;
                    p1d4->z = m;
                    q = (UnkStruct_0222efc0 *) (e + 0x1c8);
                    q->x = p204->x;
                    q->y = p204->y;
                    q->z = p204->z;
                }
                *(u8 *) (e + 0x254) = msg;
            }
        }
    sw:
        switch (state) {
            case 2:
                if (func_020a7278() == 0 && func_02073dd4((void *) g, *(int *) (g + 0x64)) != 0) {
                    if (kd != *(signed char *) (e + 0x24d) && n > 0) {
                        func_ov003_0222fe18(a, e, 1);
                    } else if (func_ov003_0222ee10(a, e) != 0) {
                        func_ov003_0222fa20(a, e, 0);
                    }
                } else {
                    func_ov003_0222fa20(a, e, 0);
                }
                break;
            case 3:
                if (func_02073dd4((void *) g, *(int *) (g + 0x64)) != 0) {
                    if (func_020a7278() == 0) {
                        if (func_ov003_0222ef80((int) a, (unsigned char *) e, kd, n, m) != 0) {
                            *(u8 *) (e + 0x251) = 0xa;
                            func_ov003_0222fe18(a, e, 1);
                        }
                    }
                    kk = *(signed char *) (e + 0x24d);
                    if (func_ov003_0222d248(kk, func_020ba4e4()) == 5) {
                        *(u8 *) (e + 0x246) = 0;
                    } else {
                        *(u8 *) (e + 0x246) = 1;
                    }
                }
                func_ov003_0222f6b0(a, e, i, 1);
                break;
            case 4:
                if (func_02073dd4((void *) g, *(int *) (g + 0x64)) == 0) {
                    *(u8 *) (e + 0x251) = 0xa;
                    func_ov003_0222fe18(a, e, 1);
                } else if (func_020a7278() != 0) {
                    p242 = (s16 *) (e + 0x242);
                    p204 = (UnkStruct_0222efc0 *) (e + 0x204);
                    w.x = p204->x;
                    w.y = p204->y;
                    w.z = p204->z;
                    func_020042c0(e + 0x174, &w);
                    if (*(u8 *) (e + 0x254) != 0xff) {
                        *(u8 *) (e + 0x254) = 0xff;
                        i = i | 0x10;
                        p1d4 = (UnkStruct_0222efc0 *) (e + 0x1d4);
                        p1d4->x = 1;
                        p1d4->y = 1;
                        p1d4->z = 1;
                        p204 = (UnkStruct_0222efc0 *) (e + 0x204);
                        p204->x = 1;
                        p204->y = 1;
                        p204->z = 1;
                        func_02073820(g);
                        func_020737f0(g, &i, 1);
                        func_02073770(g, 0x30, 7);
                    }
                    *p242 = *p242 + 1;
                    if (*p242 > 0xc8) {
                        *(u8 *) (e + 0x251) = 0xa;
                        func_ov003_0222fe18(a, e, 1);
                    }
                } else {
                    p204 = (UnkStruct_0222efc0 *) (e + 0x204);
                    w2.x = p204->x;
                    w2.y = p204->y;
                    w2.z = p204->z;
                    func_020042c0(e + 0x174, &w2);
                    if (*(u8 *) (e + 0x254) == 0xff) {
                        *(u8 *) (e + 0x251) = 0xa;
                    }
                    if (*(u8 *) (e + 0x251) == 0xa) {
                        func_ov003_0222fe18(a, e, 1);
                    }
                }
                break;
        }
        e = e + 0x25c;
    }
}

int func_ov003_0222ef80(int a, unsigned char *obj, int idx, int c, int e)
{
    int v = (signed char) obj[0x24d];
    int blk[3];

    if (c == 0) {
        return 0;
    }
    if (v < 0 || v != idx) {
        return 1;
    }
    blk[0] = c;
    blk[1] = 0;
    blk[2] = e;
    func_020ea990(obj + 0x204, blk);
    return 0;
}
