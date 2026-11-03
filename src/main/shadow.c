/* shadow: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ad2e4 @ 0x020ad2e4, 0xbc bytes, Thumb
 * func_020ad2d4 @ 0x020ad2d4, 0x10 bytes, Thumb
 * func_020ad2c4 @ 0x020ad2c4, 0x10 bytes, Thumb
 * func_020ad238 @ 0x020ad238, 0x8c bytes, Thumb
 * func_020ad228 @ 0x020ad228, 0x10 bytes, Thumb
 * func_020ad1f4 @ 0x020ad1f4, 0x34 bytes, Thumb
 * func_020ad1dc @ 0x020ad1dc, 0x18 bytes, Thumb
 * func_020ad1d8 @ 0x020ad1d8, 0x2 bytes, Thumb
 * func_020ad0c0 @ 0x020ad0c0, 0x118 bytes, Thumb
 * func_020aced0 @ 0x020aced0, 0x1f0 bytes, Thumb
 * func_020acea4 @ 0x020acea4, 0x2c bytes, Thumb
 * func_020ace54 @ 0x020ace54, 0x50 bytes, Thumb
 * func_020ace24 @ 0x020ace24, 0x30 bytes, Thumb
 * func_020ace0c @ 0x020ace0c, 0x18 bytes, Thumb
 * func_020acdcc @ 0x020acdcc, 0x40 bytes, Thumb
 */

#include "types.h"

#define REG_A4 (*(volatile u32 *) 0x040004a4)
#define REG_A8 (*(volatile u32 *) 0x040004a8)
#define REG_AC (*(volatile u32 *) 0x040004ac)
#define REG_440 (*(volatile u32 *) 0x04000440)
#define REG_480 (*(volatile u32 *) 0x04000480)
#define REG_488 (*(volatile u32 *) 0x04000488)
#define REG_48C (*(volatile u32 *) 0x0400048c)
#define REG_500 (*(volatile u32 *) 0x04000500)
#define REG_504 (*(volatile u32 *) 0x04000504)
#define REG_448 (*(volatile u32 *) 0x04000448)

typedef struct {
    int v;
} UnkStruct_020ad2e4;

typedef struct {
    UnkStruct_020ad2e4 x, y, z;
} UnkStruct_020ad2e4_2;

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_020ad2e4_3;

typedef struct UnkStruct_020ad0c0 {
    u8 pad_00[0xc];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[8];
} UnkStruct_020ad0c0;

typedef struct UnkStruct_020ad0c0_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned int unk_14;
    int unk_18;
    int *unk_1C;
    int unk_20;
    int unk_24;
    int *unk_28;
    int *unk_2C;
    UnkStruct_020ad0c0 *unk_30;
} UnkStruct_020ad0c0_2;

typedef struct UnkStruct_020aced0 {
    int unk_00;
    int unk_04;
    int unk_08;
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[4];
    u8 unk_14;
} UnkStruct_020aced0;

typedef struct UnkStruct_020aced0_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned int unk_14;
    int unk_18;
    int *unk_1C;
    int unk_20;
    int unk_24;
    int *unk_28;
    int *unk_2C;
    UnkStruct_020aced0 *unk_30;
} UnkStruct_020aced0_2;

typedef struct UnkStruct_020aced0_3 {
    int unk_00;
    int pad_04;
    int unk_08;
} UnkStruct_020aced0_3;

typedef struct V3I {
    int a;
    int b;
    int c;
} V3I;

typedef struct UnkStruct_020acea4 UnkStruct_020acea4;

struct UnkStruct_020acea4 {
    char pad_00[0x1c];
    void *unk_1C;
    char pad_20[0x10];
    unsigned int unk_30;
};

struct UnkStruct_020ace54 {
    char pad_00[0x5c];
    unsigned char *unk_5C;
};

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
} UnkStruct_020ace24;

extern int data_021c67a4;
extern UnkStruct_020ad2e4_2 data_021c67d0;
extern int data_021f47cc;
extern int data_021f47d4;
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern unsigned char data_020e4104;
extern unsigned char data_020e4100;
extern int data_021f47c8;
extern int data_021f4824[3];
extern int data_021f4818;
extern void func_020012dc(void *);
extern void __register_global_object(void *, void *, void *);
extern void func_01ffd070(int *out, int in, int *data_021f4824);
extern int data_021f4904;
extern int data_021f4938;
extern int data_021f496c;
extern unsigned char data_021f489c[];
extern const char data_021f48d0[];
extern UnkStruct_020ad0c0 data_021f49a0[];
extern void *data_021fbe94;
extern void *func_020e9948(void *, int);
extern void NNS_G3dGeFlushBuffer(void);                    // 0x01ff8ccc
extern void G3_LoadMtx43(const void *m);                   // 0x02112134
extern int func_020310c8(int a);                           // 0x020310c8
extern int func_0203f844(void *a, void *b);                // 0x0203f844
extern int func_02065604(void);                            // 0x02065604
extern int data_020d1e0c; // data_020d1e0c
extern int data_021f47d0; // data_021f47d0
extern unsigned char data_021f486c[];
extern void func_020e993c(void *a, void *b);
extern struct UnkStruct_020ace54 data_021f472c;
extern int data_020e40e4;
extern unsigned char *data_021f471c;
extern int data_020e40e0;
int func_020555c8(struct UnkStruct_020ace54 *a, int *b, int c);
void NNSi_G3dModifyMatFlag(unsigned char *a, int b, int c);
extern unsigned int __arm NNS_G3dMdlSetMdlDiff(unsigned int arg0, int arg1, unsigned short arg2);
extern int func_02055454(void *);
extern void func_020acc0c(int, int, int, int);

void func_020aced0(UnkStruct_020aced0_2 *p, UnkStruct_020aced0_3 *st);

int func_020ad2e4(UnkStruct_020ad2e4_3 *a, int b, int c)
{
    UnkStruct_020ad2e4_2 p;
    int t;
    int d;
    int e;

    if (data_021c67a4 == 0) {
        goto retc;
    }
    p.x = data_021c67d0.x;
    p.y = data_021c67d0.y;
    p.z = data_021c67d0.z;
    t = a->unk_08;
    if (p.z.v > t) {
        d = p.z.v - t;
        if (d > 0xb000) {
            c = (u8) (c >> 5);
            goto retc;
        }
        if ((data_021f47cc & 1) == 0) {
            data_021f47d4 = FX_Div(0xf80, 0xb000);
            data_021f47cc |= 1;
        }
        c = (u8) (c - (u8) (FX_MulFunc(FX_MulFunc(c << 12, data_021f47d4), d) >> 12));
        goto retc;
    }
    d = t - p.z.v;
    if (d > b + 0xc000) {
        return 0;
    }
    e = a->unk_00 - p.x.v;
    if (e < 0) {
        e = -e;
    }
    if (e > b + 0xf000) {
        return 0;
    }
retc:
    return c;
}

int func_020ad2d4(int a, int b)
{
    return func_020ad2e4((UnkStruct_020ad2e4_3 *) a, b, (unsigned char) data_020e4104);
}

int func_020ad2c4(int arg0, int arg1)
{
    return func_020ad2e4((UnkStruct_020ad2e4_3 *) arg0, arg1, (unsigned char) data_020e4100);
}

void func_020ad238(int a, unsigned int b)
{
    if (b < 2) {
        return;
    }
    if ((data_021f47c8 & 1) == 0) {
        data_021f4824[0] = 0;
        data_021f4824[1] = 0;
        data_021f4824[2] = 0;
        __register_global_object((void *) (data_021f4824), (((void *) func_020012dc)), (void *) (&data_021f4818));
        data_021f47c8 |= 1;
    }
    {
        int local[3];
        func_01ffd070(local, a, data_021f4824);
        if (b == 2) {
            func_020aced0((UnkStruct_020aced0_2 *) (&data_021f4904), (UnkStruct_020aced0_3 *) local);
        } else if (b == 3) {
            func_020aced0((UnkStruct_020aced0_2 *) (&data_021f4938), (UnkStruct_020aced0_3 *) local);
        } else if (b == 4) {
            func_020aced0((UnkStruct_020aced0_2 *) (&data_021f496c), (UnkStruct_020aced0_3 *) local);
        }
    }
}

void func_020ad228(void *param)
{
    func_020aced0((UnkStruct_020aced0_2 *) ((void *) data_021f489c), (UnkStruct_020aced0_3 *) param);
}

void func_020ad1f4(int param)
{
    int s[3];
    char buffer[16];
    s[0] = 0x166;
    s[1] = 0;
    s[2] = 0xc80;
    func_01ffd070((int *) buffer, param, (int *) s);
    func_020aced0((UnkStruct_020aced0_2 *) data_021f48d0, (UnkStruct_020aced0_3 *) buffer);
}

void *func_020ad1dc(void *r0)
{
    unsigned int *p = (unsigned int *) r0;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[7] = 0;
    p[10] = 0;
    p[11] = 0;
    p[12] = 0;
    return r0;
}

void func_020ad1d8(void *object) {}

int func_020ad0c0(UnkStruct_020ad0c0_2 *p, int *src, int v2, int v3, int a5, int a6, int a7, void *a8)
{
    unsigned int i;
    int *q;
    int *r;
    int t;
    unsigned int n;

    if (a8 == 0) {
        a8 = data_021fbe94;
    }
    p->unk_30 = &data_021f49a0[a5];
    p->unk_00 = src[0];
    p->unk_04 = src[1];
    p->unk_08 = src[2];
    p->unk_0C = v2 >> 1;
    t = p->unk_0C;
    if ((t >> v3) == 0) {
        t = v3;
    }
    p->unk_10 = t;
    p->unk_18 = 0;
    p->unk_14 = (v3 - 0x200) / 0x2000 + 2;
    n = p->unk_14 * 4;
    p->unk_1C = (int *) func_020e9948(a8, n * 2 + p->unk_14 * 0xc);
    p->unk_28 = (int *) ((u8 *) p->unk_1C + n);
    p->unk_2C = (int *) ((u8 *) p->unk_28 + n);
    for (i = 0; i < p->unk_14; i++) {
        if (i == p->unk_14 - 1) {
            p->unk_1C[i] = v3;
        } else {
            p->unk_1C[i] = i << 13;
        }
    }
    if (a6 == 0 && a7 == 0) {
        p->unk_20 = 0;
        p->unk_24 = p->unk_30->unk_0C << 12;
    } else {
        p->unk_20 = FX_MulFunc(p->unk_30->unk_0C << 12, a6);
        p->unk_24 = FX_MulFunc(p->unk_30->unk_0C << 12, a7);
    }
    q = p->unk_1C;
    r = p->unk_28;
    for (i = 0; i < p->unk_14; i++) {
        *r++ = FX_MulFunc(0x1000 - FX_Div(*q, v3), p->unk_30->unk_0E << 12);
        q++;
    }
    return 1;
}

void func_020aced0(UnkStruct_020aced0_2 *p, UnkStruct_020aced0_3 *st)
{
    unsigned int res;
    int *q;
    int *pp;
    int cached;
    unsigned int i;
    int v_lo;
    int v_hi;
    int neg;
    int shift;
    int zx;
    int zy;
    volatile u16 col;
    volatile u16 col2;
    unsigned short p0;
    unsigned short g0;
    unsigned short v0;
    int sy;
    V3I t;
    V3I *cur;

    if (p->unk_30 == 0) {
        return;
    }
    if (p->unk_30->unk_00 == 0) {
        return;
    }
    res = func_020ad2d4((int) st, p->unk_10);
    if (res <= 1) {
        return;
    }
    NNS_G3dGeFlushBuffer();
    REG_A8 = p->unk_30->unk_04;
    REG_AC = p->unk_30->unk_08;
    REG_440 = 1;
    G3_LoadMtx43((const void *) data_021f486c);
    REG_A4 = (res << 16) | ((p->unk_30->unk_14 << 24) | 0x8080);
    q = p->unk_1C;
    pp = p->unk_28;
    cur = (V3I *) p->unk_2C;
    REG_500 = 3;
    cached = p->unk_1C[1];
    i = 0;
    shift = data_020d1e0c;
    zx = i;
    zy = i;
    while (i < p->unk_14) {
        int v1;
        int tb;

        if (i != 0) {
            v1 = cached;
        } else {
            v1 = *q;
        }
        tb = FX_MulFunc(data_021f47d0, v1);
        v_lo = tb + (st->unk_00 - p->unk_0C);
        v_hi = tb + (st->unk_00 + p->unk_0C);
        if (st->unk_08 != p->unk_18) {
            neg = -*q;
            tb = func_020310c8(zx);
            t.a = zy;
            t.b = tb;
            t.c = neg;
            t.c = t.c + st->unk_08;
            func_0203f844(cur, &t);
            cur->b = cur->b >> shift;
            cur->c = cur->c >> shift;
        }
        col = func_02065604();
        col2 = col;
        REG_480 = col2;
        p0 = (u16) ((p->unk_20 << 8) >> 16);
        g0 = (u16) ((*pp << 8) >> 16);
        REG_488 = (u32) p0 | ((u32) g0 << 16);
        sy = (s16) cur->c;
        v0 = (u16) ((v_lo << 11) >> 16);
        REG_48C = (u32) v0 | ((u32) (u16) (s16) cur->b << 16);
        REG_48C = (u16) sy;
        p0 = (u16) ((p->unk_24 << 8) >> 16);
        g0 = (u16) ((*pp << 8) >> 16);
        REG_488 = (u32) p0 | ((u32) g0 << 16);
        sy = (s16) cur->c;
        v0 = (u16) ((v_hi << 11) >> 16);
        REG_48C = (u32) v0 | ((u32) (u16) (s16) cur->b << 16);
        REG_48C = (u16) sy;
        q++;
        pp++;
        cur++;
        i++;
    }
    REG_504 = 0;
    REG_448 = 1;
    p->unk_18 = st->unk_08;
}

int func_020acea4(UnkStruct_020acea4 *ptr, void *arg)
{
    if (arg == 0) {
        arg = data_021fbe94;
    }
    if (ptr->unk_1C != 0) {
        func_020e993c(arg, ptr->unk_1C);
        ptr->unk_1C = 0;
    }
    ptr->unk_30 = 0;
    return 0;
}

int func_020ace54(void)
{
    int r4;
    unsigned char *a;
    unsigned char *p;
    unsigned short off;
    unsigned int delta;
    unsigned char *result;

    if (func_020555c8(&data_021f472c, &data_020e40e4, 0) != 0) {
        r4 = 1;
    } else {
        r4 = 0;
    }

    a = data_021f472c.unk_5C;
    p = a + *(unsigned int *) (a + 8);
    off = *(unsigned short *) (p + 0xa);
    delta = *(unsigned int *) (p + off + 8);
    result = p + delta;
    data_021f471c = result;
    data_020e40e0 = 1;
    NNSi_G3dModifyMatFlag(a, 1, 0x40);

    return r4;
}

void func_020ace24(void)
{
    volatile unsigned short a, b;

    data_020e40e0 = 1;
    a = (unsigned short) func_02065604();
    b = a;
    NNS_G3dMdlSetMdlDiff((*(UnkStruct_020ace24 *) &data_021f472c).unk_5C, 0, b);
}

void func_020ace0c(void)
{
    (*(int *) &data_021f471c) = 0;
    func_02055454(((char *) &data_021f472c));
}

void func_020acdcc(int a0, int a1, int a2, int a3)
{
    int r6;

    if (a3 == 0) {
        a3 = 1;
    }
    r6 = 0x1000;
    if (a3 != 0x1f) {
        r6 = FX_Div((a3 - 1) << 12, 0x1e000);
    }
    func_020acc0c(a0, a1, a2, r6);
}
