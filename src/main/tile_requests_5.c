/* tile_requests_5: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020445c0 @ 0x020445c0, 0x190 bytes, Thumb
 * func_0204457c @ 0x0204457c, 0x42 bytes, Thumb
 * func_02044540 @ 0x02044540, 0x3c bytes, Thumb
 * func_02044534 @ 0x02044534, 0xc bytes, Thumb
 * func_02044528 @ 0x02044528, 0xc bytes, Thumb
 * func_02044390 @ 0x02044390, 0x198 bytes, Thumb
 * func_02044168 @ 0x02044168, 0x228 bytes, Thumb
 * func_02043ed8 @ 0x02043ed8, 0x290 bytes, Thumb
 * func_02043e88 @ 0x02043e88, 0x50 bytes, Thumb
 * func_02043db4 @ 0x02043db4, 0xd2 bytes, Thumb
 * func_02043d84 @ 0x02043d84, 0x2e bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02044540 {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_02044540_2 {
    char pad_00[0x1c];
    unsigned char flag;
};

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02044390;

typedef struct {
    int a;
    int b;
} Pair;

struct Pair {
    int a;
    int b;
};

typedef struct {
    int x;
    int y;
} Pair_02043ed8;

typedef struct {
    u8 unk_00;
    u16 unk_02;
    u16 unk_04;
} UnkStruct_02043ed8;

typedef struct {
    int x;
    int y;
} Pair_02043e88;

typedef struct {
    int x;
    int y;
} Point;

struct Pair_02043d84 {
    unsigned int a;
    unsigned int b;
};

extern unsigned short data_020ca64c[];
extern int func_0204482c(void *arg1);
extern void func_02044750(unsigned short *out, unsigned char *flag, unsigned short val);
extern int func_02073dd4(struct UnkStruct_02044540 *ptr, int arg);
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern unsigned char data_021c779c[];
extern int func_0204ba40(unsigned short *);
extern int func_0204b7a0(unsigned short *);
extern int func_0204b910(unsigned short *);
extern int func_02042f20(void *tbl, void *a0, int kind, Pair *pr, int w, int v, int z0, int z1, int a3, int m1);
extern int data_021c7c48;
extern int data_020caaf8[];
extern void *data_020ccf94;
extern int func_0204ba94(u16 *);
extern int func_02042c9c(int *, struct Pair *);
extern int func_02073d90(void *);
extern int func_020984d4(void);
extern int func_0204eda8(void *node, int x, int y);
extern int func_0204a034(u16 *t);
extern int func_0204b3d0(u16 *t);
extern int func_0204f294(void *node, int x, int y);
extern void *func_0204e414(void);
extern int func_0204f5e0(void *node, int x4, int y4, int x_rem, int y_rem, int arg5);
extern void *func_02044858(void *);

int func_020445c0(unsigned short *out, unsigned short *out2, unsigned short id)
{
    volatile unsigned short v;
    unsigned int ok;
    unsigned short a, b;
    unsigned short c, d;
    unsigned int ok3;
    unsigned short e, f;
    int idx;
    int ret;

    v = 0xfff1;
    ret = 1;
    v = id;

    ok = 0;
    a = v;
    b = v;
    if (b >= 0x1408 && a <= 0x1428) {
        ok = 1;
    }
    if (ok != 0) {
        *out = (a >= 0x1408 && a <= 0x1428) ? (a - 0x1408) : -1;
        goto end;
    }
    if (a >= 0x1471 && a <= 0x1491) {
        *out = (a >= 0x1471 && a <= 0x1491) ? (a - 0x1471) : -1;
        goto end;
    }
    if (a >= 0x137c && a <= 0x137c) {
        *out = 0x1e;
        goto end;
    }
    if (a >= 0x14fe && a <= 0x1517) {
        idx = (a >= 0x14fe && a <= 0x1517) ? (a - 0x14fe) : -1;
        *out = idx;
        *out2 = ((unsigned int) idx < 0x21) ? (unsigned short) (idx + 0x1408) : 0x1408;
        goto end;
    }
    if (a >= 0x151d && a <= 0x151e) {
        if (a == 0x151d) {
            *out = 0x26;
            *out2 = 0x26;
        } else {
            *out = 0x5d;
            *out2 = 0x5d;
        }
        goto end;
    }
    if (func_0204ba94((u16 *) (&v)) != 0) {
        ok = 0;
        c = v;
        d = v;
        if (d >= 0xc8 && c <= 0xcf) {
            ok = 1;
        }
        if (ok != 0) {
            *out = 0xc8;
        } else {
            *out = 0x26;
        }
        goto end;
    }
    ok3 = 0;
    e = v;
    f = v;
    if (f >= 0x1518 && e <= 0x151c) {
        ok3 = 1;
    }
    if (ok3 != 0) {
        idx = (e >= 0x1518 && e <= 0x151c) ? (e - 0x1518) : -1;
        *out = data_020ca64c[idx];
        goto end;
    }
    if (id == 0x1548) {
        *out = 0xc8;
        goto end;
    }
    if (id == 0x1567) {
        *out = 0xd4;
        *out2 = 0x1408;
        goto end;
    }
    ret = 0;
end:
    return ret;
}

void func_0204457c(void *arg1, unsigned short *out, void *arg3, unsigned char *flag, unsigned short val)
{
    *out = val;
    *flag = 1;
    if (func_020445c0(out, (unsigned short *) arg3, val)) {
        *flag = 0;
        return;
    }
    if (func_0204482c(arg1)) {
        func_02044750(out, flag, val);
    }
}

int func_02044540(void)
{
    int ret = 0;

    if (func_02073dd4((*(struct UnkStruct_02044540 **) &data_020ccf94),
                      (*(struct UnkStruct_02044540 **) &data_020ccf94)->unk_64) != 0) {
        goto end;
    }
    if (func_02099020(func_020984e8(), 1) != 0) {
        goto end;
    }
    if ((*(struct UnkStruct_02044540_2 *) data_021c779c).flag != 0) {
        goto end;
    }
    ret = 1;
end:
    return ret;
}

void func_02044534(void)
{
    data_021c779c[0x1c] = 1;
}

void func_02044528(void)
{
    ((char *) data_021c779c)[0x1c] = 0;
}

int func_02044390(void *a0, unsigned short *p, UnkStruct_02044390 *ctx, int a3)
{
    int result;
    int i, h, g, f, e, d, c, b, a;
    int kind;
    int n;
    unsigned int v;
    unsigned int ok2;
    unsigned int w;
    Pair pr;

    a = 0;
    result = -1;
    i = 1;
    h = 1;
    g = 1;
    f = 1;
    e = 1;
    d = 1;
    c = 1;
    b = 1;

    v = *p;
    if (v >= 0x26 && v <= 0x2a) {
        a = 1;
    }
    if (a == 0) {
        if (!(v >= 0x5d && v <= 0x61)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(v >= 0x2f && v <= 0x56)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!(v >= 0x57 && v <= 0x5b)) {
            d = 0;
        }
    }
    if (d == 0) {
        if (!(v >= 0x66 && v <= 0x68)) {
            e = 0;
        }
    }
    if (e == 0) {
        if (v != 0x69) {
            f = 0;
        }
    }
    if (f == 0) {
        if (!(v >= 0x6a && v <= 0x6c)) {
            g = 0;
        }
    }
    if (g == 0) {
        if (v != 0x6d) {
            h = 0;
        }
    }
    if (h == 0) {
        if (!(v >= 0xc8 && v <= 0xcf)) {
            i = 0;
        }
    }
    if (i != 0) {
        if (func_0204ba94((u16 *) p) == 0 && func_0204ba40(p) == 0) {
            kind = 1;
            n = func_0204b7a0(p) - 1;
            ok2 = 0;
            v = *p;
            if (v >= 0x26 && v <= 0x2a) {
                ok2 = 1;
            }
            if (ok2 != 0 || (v >= 0x57 && v <= 0x5b) || (v >= 0x66 && v <= 0x68) || v == 0x69) {
                w = (unsigned short) (n + 0x27);
            } else {
                w = (unsigned short) (n + 0x5e);
            }
            if (v == 0x67 || v == 0x6b) {
                if (func_02044540() != 0) {
                    kind = 2;
                } else {
                    w = *p;
                }
            } else if ((v >= 0x2f && v <= 0x56) || (v >= 0xc8 && v <= 0xcf)) {
                if (func_0204b910(p) != 0) {
                    w = (unsigned short) (*p + 1);
                } else {
                    w = *p;
                }
            } else if (v >= 0x57 && v <= 0x5b) {
                if (func_0204b910(p) == 0) {
                    w = *p;
                }
            } else if (v == 0x6d) {
                w = v;
            }
            v = *p;
            pr.a = ctx->unk_00;
            pr.b = ctx->unk_04;
            result = func_02042f20(((unsigned char *) &data_021c7c48), a0, kind, &pr, w, v, 0, 0, a3, -1);
        }
    }
    return result;
}

int func_02044168(int p0, u16 *pv, struct Pair *p2, int p3)
{
    int kind;
    int A;
    int R;
    struct Pair t1;
    struct Pair t2;
    u16 v;
    int idx;
    unsigned int ok;
    u16 w;
    int q;

    kind = 0;
    A = 0;
    R = -1;
    v = *pv;
    if (((v >= 0x26 && v <= 0x2a) || (v >= 0x5d && v <= 0x61) || (v >= 0x2f && v <= 0x56) || (v >= 0x57 && v <= 0x5b) ||
         (v >= 0x66 && v <= 0x68) || v == 0x69 || (v >= 0x6a && v <= 0x6c) || v == 0x6d || (v >= 0xc8 && v <= 0xcf)) &&
        func_0204ba94(pv) == 0) {
        idx = func_0204b7a0((unsigned short *) pv) - 1;
        kind = 6;
        t1.a = p2->a;
        t1.b = p2->b;
        A = (u8) func_02042c9c(&data_021c7c48, &t1);
        if (p3 != 2) {
            if (A >= data_020caaf8[idx]) {
                ok = 0;
                w = *pv;
                if (w >= 0xc8 && w <= 0xcf) {
                    ok = 1;
                }
                if (ok > 0) {
                    v = (u16) (idx + 0xd0);
                } else if ((w >= 0x5d && w <= 0x61) || w == 0x6d) {
                    v = (u16) (idx + 0x62);
                } else if (w >= 0x2f && w <= 0x56) {
                    v = (u16) (idx + 0xff);
                } else {
                    v = (u16) (idx + 0x2b);
                }
            } else {
                ok = 0;
                w = *pv;
                if (w >= 0x26 && w <= 0x2a) {
                    ok = 1;
                }
                if (ok > 0 || (w >= 0x57 && w <= 0x5b) || (w >= 0x66 && w <= 0x68) || w == 0x69) {
                    v = (u16) (idx + 0x27);
                } else {
                    v = (u16) (idx + 0x5e);
                }
                if (w == 0x67 || w == 0x6b) {
                    if (func_02044540() != 0) {
                        kind = 7;
                    } else {
                        v = *pv;
                    }
                } else if ((w >= 0x2f && w <= 0x56) || (w >= 0xc8 && w <= 0xcf)) {
                    if (func_0204b910((unsigned short *) pv) != 0) {
                        v = (u16) (*pv + 1);
                    } else {
                        v = *pv;
                    }
                } else if (w == 0x6d) {
                    v = w;
                }
            }
        }
    } else {
        ok = 0;
        w = *pv;
        if (w >= 0xe3 && w <= 0xe7) {
            ok = 1;
        }
        if (ok > 0) {
            kind = 0xd;
        } else if (w >= 0xe8 && w <= 0xfb) {
            kind = 0xc;
            if (func_02073d90(data_020ccf94) == 0) {
                q = (*pv - 0xe8) / 5;
                if (q == func_020984d4()) {
                    if (p3 != 2) {
                        kind = 0xe;
                    }
                }
            }
        } else {
            switch ((w & 0xf000) >> 12) {
                case 0:
                    if (w == 0x1b || w == 0x89) {
                        kind = 0x17;
                    }
                    break;
                case 1:
                case 3:
                case 4:
                    kind = 0xc;
                    break;
                case 2:
                    break;
            }
        }
    }
    if (kind != 0) {
        w = *pv;
        t2.a = p2->a;
        t2.b = p2->b;
        R = func_02042f20((void *) (&data_021c7c48), (void *) p0, kind, (Pair *) (&t2), v, w, A, 0, p3, -1);
    }
    return R;
}

int func_02043ed8(void *self, void *node, u16 *t, Pair_02043ed8 *pt, unsigned short extra, int q)
{
    int ret;
    UnkStruct_02043ed8 info;
    Pair_02043ed8 tmp;
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
        func_0204457c(self, (unsigned short *) (&info.unk_02), (void *) (&info.unk_04), (unsigned char *) (&info.unk_00),
                      extra);
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
        ret = func_02042f20(&data_021c7c48, self, kind, (Pair *) (&tmp), info.unk_02, info.unk_04, info.unk_00, 0, q, -1);
    }
    return ret;
}

int func_02043e88(int a0, unsigned short *a1, int *a2, int a3)
{
    Pair_02043e88 tmp;
    int ret;
    unsigned short v;

    ret = -1;
    if (func_0204482c((void *) a0) != 0) {
        v = *a1;
        tmp.x = a2[0];
        tmp.y = a2[1];
        ret = func_02042f20((void *) (&data_021c7c48), (void *) a0, 0xf, (Pair *) (&tmp), v, v, 0, 0, a3, -1);
    }
    return ret;
}

int func_02043db4(void *self, Point *pos, int op, int q, u16 extra)
{
    void *node;
    int result;
    int t;

    node = func_0204e414();
    result = -1;
    if (node != 0) {
        int x = pos->x;
        int y = pos->y;
        int x4 = x >> 4;
        int y4 = y >> 4;
        int y_rem = y - (y4 << 4);
        int x_rem = x - (x4 << 4);
        t = func_0204f5e0(node, x4, y4, x_rem, y_rem, 0);
        if (t != 0) {
            switch (op) {
                case 0: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02044390(self, (unsigned short *) t, (UnkStruct_02044390 *) (&pt), q);
                    break;
                }
                case 1: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02044168((int) self, (u16 *) t, (struct Pair *) (&pt), q);
                    break;
                }
                case 2: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02043ed8(self, node, (u16 *) t, (Pair_02043ed8 *) (&pt), (u16) extra, q);
                    break;
                }
                case 3:
                    break;
                case 4: {
                    Point pt;
                    pt.x = pos->x;
                    pt.y = pos->y;
                    result = func_02043e88((int) self, (unsigned short *) t, (int *) (&pt), q);
                    break;
                }
            }
        }
    }
    return result;
}

int func_02043d84(void *a, struct Pair_02043d84 *src, int c, int d, unsigned short e)
{
    struct Pair_02043d84 local;
    void *p;

    p = func_02044858(a);
    local.a = src->a;
    local.b = src->b;
    return func_02043db4(p, (Point *) (&local), c, d, (unsigned short) e);
}
