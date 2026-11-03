/* tile_requests: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02042d14 @ 0x02042d14, 0x80 bytes, Thumb
 * func_02042ce8 @ 0x02042ce8, 0x2c bytes, Thumb
 * func_02042cd8 @ 0x02042cd8, 0x10 bytes, Thumb
 * func_02042c9c @ 0x02042c9c, 0x3c bytes, Thumb
 * func_02042c58 @ 0x02042c58, 0x44 bytes, Thumb
 * func_02042c40 @ 0x02042c40, 0x18 bytes, Thumb
 * func_02042c28 @ 0x02042c28, 0x18 bytes, Thumb
 * func_02042a9c @ 0x02042a9c, 0x18c bytes, Thumb
 * func_02042a5c @ 0x02042a5c, 0x40 bytes, Thumb
 */

#include "types.h"

struct Coord {
    int x;
    int y;
};

typedef struct {
    int x;
    int y;
} Pt;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02042a9c;

typedef struct {
    u8 f0 : 1;
    u8 f1 : 2;
    u8 f2 : 5;
    u8 g0 : 5;
    u8 g1 : 2;
    u8 g2 : 1;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06[3];
} UnkStruct_02042a9c_2;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
} Entry;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_02042a9c vec;
} UnkStruct_02042a9c_3;

typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned short c;
} Entry_02042a5c;

extern void *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204ee7c(int, int, int);
extern int func_02046024(int, int *, int, int, int, int, int, int, int, int);
extern unsigned short data_020cab3c[];
extern void func_02042f10(void *param1, int param2);
extern void func_02042f08(void *param1);
extern void func_02042e64(unsigned int a);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern unsigned char data_021c7cb4[];
extern void func_02045e24(Pt *p, int k);
extern UnkStruct_02042a9c_3 *func_020961a8(int k);
extern void func_02042ff8(int k, Pt *p);
extern int func_ov003_02221304(int k, int w, Pt *p, UnkStruct_02042a9c *v);
extern int func_ov004_022335b8(int k, int w, Pt *p, UnkStruct_02042a9c *v, int z);
extern void func_ov003_02220e20(int k, int w, Pt *p, UnkStruct_02042a9c *v);
extern Entry data_021c7788[];
extern u8 data_020e54a8;
extern int func_02044858(int);

int func_02042d14(short *param1, int param2, int *param3)
{
    int res = 0;
    int p0 = param3[0];
    int p1 = param3[1];
    int q0 = p0 >> 4;
    int q1 = p1 >> 4;
    int rem1 = p1 - (q1 << 4);
    int val;
    int rem0 = p0 - (q0 << 4);
    void *r = func_0204f5e0(param2, q0, q1, rem0, rem1, res);
    if ((0 != r) && ((*((unsigned short *) r)) == 0xFFF1)) {
        if (func_0204ee7c(param2, param3[0, 0], param3[1]) != 0) {
            int local[2];
            val = param3[1];
            local[0] = param3[0];
            local[1] = val;
            func_02046024(res, local, data_020cab3c[param1[1]], 0xFFF1, res, res, rem1 = res, 3, res, ~res);
            res = 1;
        }
    }
    return res;
}

void func_02042ce8(void *param1)
{
    int i;
    void *ptr = param1;

    for (i = 0; i < 3; i++) {
        func_02042f10(ptr, i);
    }

    func_02042f08((void *) ((char *) ptr + 0x46c));
}

void func_02042cd8(unsigned int a)
{
    func_02042e64(a + 0x46c);
}

int func_02042c9c(unsigned char *p, int *q)
{
    int a;
    int c;
    int r4;
    int shift;

    a = q[0];
    c = q[1];
    r4 = ((a - 16) >> 2) + ((c - 16) << 4);
    shift = (a & 3) << 1;
    if (r4 < 0 || r4 >= 0x400) {
        r4 = 0;
        shift = 0;
    }
    return ((p + r4)[0x6c] >> shift) & 3;
}

void func_02042c58(unsigned char *self, struct Coord *coord, int value)
{
    int x = coord->x;
    int y = coord->y;
    int index = ((x - 16) >> 2) + ((y - 16) << 4);
    int bit = (x & 3) << 1;
    if (index >= 0 && index < 0x400) {
        // empty
    } else {
        index = 0;
        bit = 0;
    }
    self += 0x6c;
    self[index] = (value << bit) | (self[index] & ~(3 << bit));
}

void func_02042c40(void *receiver)
{
    MI_CpuFill8((void *) data_021c7cb4, 0, 0x400);
}

void func_02042c28(unsigned char *p)
{
    int i = 0;
    unsigned char val = i;
    for (; i < 5; i++) {
        p[0] = val;
        *(unsigned short *) (p + 2) = 0xffff;
        p += 4;
    }
}

void func_02042a9c(UnkStruct_02042a9c_2 *self)
{
    volatile u16 hi1;
    volatile u16 lo1;
    volatile u16 hi3;
    volatile u16 lo3;
    volatile u16 t2;
    volatile u16 t1;
    volatile u16 t3;
    Pt a;
    Pt b;
    Pt p1;
    Pt p2;
    Pt p3;
    Pt p4;
    UnkStruct_02042a9c v1;
    UnkStruct_02042a9c v2;
    UnkStruct_02042a9c v3;
    Entry *e;
    volatile u16 *w;
    int k;
    int hi;
    int lo;
    UnkStruct_02042a9c_3 *o;
    UnkStruct_02042a9c *q;
    unsigned int f;
    u16 tmp;

    e = &data_021c7788[self->f1];
    if (e->unk_00 != 0) {
        t1 = e->unk_02;
        tmp = t1;
        lo1 = tmp;
        hi1 = tmp;
        a.x = (int) hi1 >> 8;
        a.y = lo1 & 0xff;
        func_02045e24(&a, 0);
        if (self->f0 == 1) {
            w = self->unk_06;
            for (k = 0; k < 3; w++, k++) {
                if (*w != 0xffff) {
                    tmp = *w;
                    b.x = (int) tmp >> 8;
                    b.y = tmp & 0xff;
                    func_02045e24(&b, 0);
                }
            }
        }
    }
    e->unk_00 = self->f2;
    t2 = self->unk_02;
    e->unk_02 = t2;
    e->unk_01 = self->g1;
    t3 = self->unk_02;
    tmp = t3;
    lo3 = tmp;
    hi3 = tmp;
    hi = (int) hi3 >> 8;
    lo = lo3 & 0xff;
    switch (self->f2) {
        case 0x10:
        case 0x11:
        case 0x12:
            o = func_020961a8(self->f1);
            if (o == 0) {
                break;
            }
            q = &o->vec;
            if (data_020e54a8 == 0) {
                f = 1;
            } else {
                f = 0;
            }
            if (f != 0) {
                v1.a = q->a;
                v1.b = q->b;
                v1.c = q->c;
                p1.x = hi;
                p1.y = lo;
                func_ov003_02221304(self->f1, self->unk_04, &p1, &v1);
            } else {
                v2.a = q->a;
                v2.b = q->b;
                v2.c = q->c;
                p2.x = hi;
                p2.y = lo;
                func_ov004_022335b8(self->f1, self->unk_04, &p2, &v2, 0);
            }
            break;
        case 0xf:
            p3.x = hi;
            p3.y = lo;
            func_02042ff8(self->f1, &p3);
            break;
        case 0x13:
            if (self->unk_04 == 0xfff1) {
                break;
            }
            o = func_020961a8(self->f1);
            if (o == 0) {
                break;
            }
            q = &o->vec;
            v3.a = o->vec.a;
            v3.b = q->b;
            v3.c = q->c;
            p4.x = hi;
            p4.y = lo;
            func_ov003_02220e20(self->f1, self->unk_04, &p4, &v3);
            break;
    }
}

int func_02042a5c(Entry_02042a5c *out, int key)
{
    int ret = 0;
    int i;
    Entry_02042a5c *e;
    volatile unsigned short tmp;

    i = func_02044858(key);
    e = &((Entry_02042a5c *) data_021c7788)[i];
    if (e->a) {
        out->a = e->a;
        tmp = e->c;
        out->c = tmp;
        out->b = e->b;
        e->a = 0;
        ret = 1;
    }
    return ret;
}
