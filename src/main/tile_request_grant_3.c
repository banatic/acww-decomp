/* tile_request_grant_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02045ac4 @ 0x02045ac4, 0x78 bytes, Thumb
 * func_02045aa4 @ 0x02045aa4, 0x20 bytes, Thumb
 * func_02045a80 @ 0x02045a80, 0x24 bytes, Thumb
 * func_020459f0 @ 0x020459f0, 0x90 bytes, Thumb
 * func_0204590c @ 0x0204590c, 0xe4 bytes, Thumb
 * func_02045770 @ 0x02045770, 0x19c bytes, Thumb
 */

#include "types.h"

typedef struct Vec {
    int x, y, z;
} Vec;

typedef struct Pair {
    int a, b;
} Pair;

typedef struct Entry {
    char pad_00[0x5c];
    Vec vec;
} Entry;

struct UnkStruct_02045aa4 {
    int a;
    int b;
};

struct UnkStruct_02045aa4_2 {
    int a;
    int b;
};

typedef struct {
    unsigned char pad_00[0x68];
    void *unk_68;
} UnkStruct_02045a80;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02045a80_2;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02045a80_3;

struct Entry_020459f0 {
    unsigned int unk_00;
    unsigned char pad0[0xe];
    unsigned short unk_12;
    unsigned char pad1[0x8];
    unsigned char unk_1C;
    unsigned char pad2;
    signed char unk_1E;
    unsigned char pad3[5];
};

struct Input {
    unsigned int unk_00;
    unsigned int unk_04;
};

struct Pair_020459f0 {
    unsigned int unk_00;
    unsigned int unk_04;
};

struct Big {
    unsigned short hw;
    struct Pair_020459f0 pair;
};

struct Both {
    struct Big pair;
    struct Pair_020459f0 pair2;
};

struct TableEntry {
    unsigned char f0 : 3;
    unsigned char pad0 : 4;
    unsigned char pad1 : 1;
    unsigned char pad2 : 7;
    unsigned char f1 : 1;
    unsigned char pad3 : 2;
    signed char f2 : 4;
    unsigned char pad4 : 2;
    unsigned char pad_03[13];
};

typedef struct {
    int unk_00;
    int pad_04[4];
    int unk_14;
    int unk_18;
} UnkStruct_0204590c;

typedef struct {
    unsigned char unk_00;
    unsigned char b1 : 5;
    unsigned char b1h : 3;
    unsigned char pad_02[4];
    unsigned short unk_06;
} UnkStruct_0204590c_2;

typedef struct {
    int x;
    int z;
} Pt;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    u16 unk_10;
    u16 unk_12;
    int x;
    int z;
    u8 unk_1C;
    u8 unk_1D;
    s8 unk_1E;
    u8 unk_1F;
    int unk_20;
} UnkStruct_02045770;

typedef struct {
    u8 a0 : 2;
    u8 a2 : 2;
    u8 a4 : 2;
    u8 a6 : 2;
    u8 b0 : 5;
    u8 b5 : 2;
    u8 b7 : 1;
    u8 z;
    u8 x;
    u16 tile;
    u16 unk_06;
} UnkStruct_02045770_2;

typedef struct {
    u8 z;
    u8 x;
} UnkStruct_02045770_4;

typedef struct {
    u8 h[2];
    UnkStruct_02045770_4 sub;
    u8 pad[16];
} UnkStruct_02045770_3;

typedef struct {
    u8 pad[0x64];
    int unk_64;
} UnkStruct_02045770_5;

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_0204f794(Vec *out, int a, int b);
extern Entry *func_020961a8(int);
extern int FX_MulFunc(int, int);
extern int func_02044878(int arg);
extern struct Entry_020459f0 data_021c7c48[];
extern struct TableEntry data_021c7884[];
extern int func_02045d80(unsigned int *p, unsigned char arg2);
extern void func_02042ff8(int, int *);
extern void func_02042e10(void *, int *);
extern unsigned short data_020ca658[];
extern int data_021c80b4;
extern void *data_021c80bc;
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_020a7278(void);
extern void func_0204510c(UnkStruct_02045770_2 *w, int a, int b);
extern void func_02073820(UnkStruct_02045770_5 *o);
extern void func_020737f0(UnkStruct_02045770_5 *o, UnkStruct_02045770_2 *w, int n);
extern void func_02073770(UnkStruct_02045770_5 *o, int a, int b);
extern int func_02046024(int a, Pt *b, int c, int d, u8 p5, u8 p6, u8 p7, u8 p8, u8 p9, s8 p10);
extern int func_02045380(UnkStruct_02045770_3 *b, UnkStruct_02045770_2 *w, int c);

int func_02045ac4(Pair *p, int skip)
{
    Vec local;
    int i;
    int res1, res2;

    if (func_02073d90(data_020ccf94) == 0) {
        return 1;
    }

    func_0204f794(&local, p->a, p->b);

    for (i = 0; i < 4; i++) {
        Entry *entry;
        Vec *sub;
        int dx, dz;

        if (i == skip) {
            continue;
        }

        entry = func_020961a8(i);
        if (entry == 0) {
            continue;
        }

        sub = &entry->vec;
        dx = local.x - sub->x;
        dz = local.z - sub->z;

        res1 = FX_MulFunc(dx, dx);
        res2 = FX_MulFunc(dz, dz);

        if (res1 + res2 >= 0x1000) {
            continue;
        }
        return 0;
    }

    return 1;
}

int func_02045aa4(struct UnkStruct_02045aa4 *src, int arg)
{
    struct UnkStruct_02045aa4_2 local;
    int val;
    local.a = src->a;
    local.b = src->b;
    val = func_02044878(arg);
    return func_02045ac4((Pair *) (&local), val);
}

int func_02045a80(UnkStruct_02045a80_2 *param)
{
    void *arg2;
    UnkStruct_02045a80_3 local;

    arg2 = (*(UnkStruct_02045a80 * *) &data_020ccf94)->unk_68;
    local.unk_00 = param->unk_00;
    local.unk_04 = param->unk_04;
    return func_02045ac4((Pair *) (&local), (int) arg2);
}

int func_020459f0(int index, struct Input *p)
{
    struct Both both;
    int result;
    struct Entry_020459f0 *entry;
    struct TableEntry *te;
    unsigned char arg2;
    int tmp;

    both.pair.hw = 0xfff1;
    result = 0;
    entry = &data_021c7c48[index];
    both.pair.hw = entry->unk_12;
    arg2 = entry->unk_1C;
    both.pair.pair.unk_00 = p->unk_00;
    both.pair.pair.unk_04 = p->unk_04;
    tmp = func_02045d80(&both.pair.pair.unk_00, arg2);
    if (tmp < 0) {
        both.pair2.unk_00 = p->unk_00;
        both.pair2.unk_04 = p->unk_04;
        if (func_02045a80((UnkStruct_02045a80_2 *) (&both.pair2)) != 0) {
            result = 1;
        }
    } else {
        te = &data_021c7884[tmp];
        if (te->f0 == (unsigned char) (entry->unk_00 & 3)) {
            if (te->f2 == entry->unk_1E) {
                if (te->f1 != 0) {
                    result = 1;
                }
            }
        }
    }
    return result;
}

int func_0204590c(UnkStruct_0204590c_2 *p, UnkStruct_0204590c *q)
{
    volatile unsigned short t = 0xfff1;
    int ret = 0;

    t = p->unk_06;
    switch (p->b1) {
        case 19: {
            int ok = 0;
            unsigned short lo = t;
            unsigned short hi = t;
            if (hi >= 0x1518 && lo <= 0x151c) {
                ok = 1;
            }
            if (ok) {
                p->unk_06 = data_020ca658[lo - 0x1518];
            } else {
                switch (lo) {
                    case 0x1548:
                        p->unk_06 = 0xc8;
                        break;
                    case 0x151d:
                        p->unk_06 = 0x26;
                        break;
                    case 0x151e:
                        p->unk_06 = 0x5d;
                        break;
                }
            }
            break;
        }
        case 15: {
            int v[2];
            int r = func_02044878(q->unk_00);
            v[0] = q->unk_14;
            v[1] = q->unk_18;
            func_02042ff8(r, v);
            ret = 1;
            break;
        }
        case 12:
        case 13:
        case 23:
            ret = 1;
            break;
        case 14: {
            int w[2];
            w[0] = q->unk_14;
            w[1] = q->unk_18;
            func_02042e10(&data_021c80b4, w);
            break;
        }
    }
    return ret;
}

/* FAKEMATCH: the empty if keeps the x/z copies loaded before the bb.sub pointer is formed; without it the stores are scheduled differently */
void func_02045770(u8 idx, int p1)
{
    UnkStruct_02045770_2 w;
    Pt pt;
    Pt pt2;
    UnkStruct_02045770_3 bb;
    void *ctx;
    UnkStruct_02045770 *s;
    u16 *e;
    int x;
    int z;
    int cx;
    int cz;
    UnkStruct_02045770_5 *obj;
    UnkStruct_02045770_4 *q;
    s8 sb;
    ctx = data_021c80bc;
    s = &((UnkStruct_02045770 *) data_021c7c48)[idx];
    if (ctx == 0) {
        s->unk_08 = 3;
        return;
    }
    x = s->x;
    z = s->z;
    cx = x >> 4;
    cz = z >> 4;
    e = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (e == 0) {
        s->unk_08 = 3;
        return;
    }
    pt.x = x;
    pt.z = z;
    if (func_020459f0(idx, (struct Input *) (&pt)) == 0) {
        s->unk_08 = 3;
        return;
    }
    w.a0 = s->unk_00;
    w.a2 = idx;
    w.a4 = s->unk_1D;
    w.b0 = s->unk_0C;
    w.x = x;
    w.z = z;
    w.tile = *e;
    w.unk_06 = s->unk_10;
    w.b5 = p1;
    w.b7 = s->unk_1C;
    obj = (*(UnkStruct_02045770_5 * *) &data_020ccf94);
    if (func_02073d90((int) obj) != 0) {
        if (func_020a7278() != 0) {
            func_0204510c(&w, 1, obj->unk_64);
            return;
        }
        obj = (*(UnkStruct_02045770_5 * *) &data_020ccf94);
        func_02073820(obj);
        func_020737f0(obj, &w, 8);
        func_02073770(obj, 0x31, 6);
        return;
    }
    s->unk_08 = 2;
    if (func_0204590c((UnkStruct_0204590c_2 *) (&w), (UnkStruct_0204590c *) s) != 0) {
        return;
    }
    sb = s->unk_1E;
    pt2.x = s->x;
    pt2.z = s->z;
    if (func_02046024(0, &pt2, w.unk_06, w.tile, w.b0, w.a4, w.b5, 4, w.b7, sb) == 0) {
        s->unk_08 = 3;
        return;
    }
    {
        int bx = s->x;
        int bz = s->z;
        if ((!idx) && (!idx)) {
        }
        q = &bb.sub;
        q->x = bx;
        q->z = bz;
    }
    func_02045380(&bb, &w, 0);
}
