/* shadow_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ad720 @ 0x020ad720, 0x2c bytes, Thumb
 * func_020ad4fc @ 0x020ad4fc, 0x224 bytes, Thumb
 * func_020ad408 @ 0x020ad408, 0xf4 bytes, Thumb
 * func_020ad3a0 @ 0x020ad3a0, 0x68 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_020ad4fc UnkStruct_020ad4fc;

typedef struct {
    UnkStruct_020ad4fc *unk_00;
    u32 unk_04;
    u32 unk_08;
    u16 unk_0C;
    u16 unk_0E;
    u32 unk_10;
    u8 unk_14;
    u8 pad_15[3];
} Cell;

typedef struct {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
} Tbl;

struct UnkStruct_020ad4fc {
    u8 pad_00[8];
    int unk_08;
    u8 pad_0C[0x2c - 0xc];
    int unk_2C;
    u8 pad_30[0x34 - 0x30];
    u16 unk_34;
    u8 pad_36[0x42 - 0x36];
    u16 unk_42;
};

typedef struct {
    u8 b[0x24];
} Work;

typedef union {
    u16 raw;
    struct {
        u16 f0 : 5;
        u16 f1 : 5;
        u16 f2 : 5;
        u16 pad : 1;
    } bits;
} UnkStruct_020ad408;

extern void VEC_Normalize(void *a, void *b);
extern void *data_021c9b24;
extern int data_021f47d0;
extern Cell data_021f49a0[3];
extern int data_020e412c;
extern Tbl data_020d1df4[3];
extern int data_020e4148;
extern int data_021f47d8;
extern int data_021f47e8[3];
extern int data_021f4800;
extern int data_021f4904;
extern int data_021f4938;
extern int data_021f496c;
extern int data_021f489c;
extern int data_021f48d0;
extern void *func_02064b18(void *p);
extern void *func_021077e8(void *file);
extern int func_02056064(void *a, int b);
extern UnkStruct_020ad4fc *func_020561cc(void *a, void *b);
extern void func_020e9898(void *a);
extern int func_02064328(void *w, void *a, ...);
extern int func_02057a40(UnkStruct_020ad4fc *o, void *b);
extern int func_020579b8(UnkStruct_020ad4fc *o, void *w);
extern void func_020012dc(void *);
extern void __register_global_object(void *, void *, void *);
extern int func_020ad0c0(void *a, void *b, int c, int d, int e, int f, int g, void *h);
extern int FX_Div(int a, int b);     // 0x01ffc5a4
extern int FX_MulFunc(int a, int b); // 0x01ffcb0c

// 0x021367a8

extern void func_020e96c8(void *a, int b, int c, int d);
extern void func_020e9838(void *a, int b, int c, int d);
extern void MTX_Concat43(void *a, void *b, void *c);
extern u16 func_0206586c(void);  // 0x0206586c
extern int func_020655c4(int a); // 0x020655c4
extern void func_0209def4(u8 *p);
extern u8 data_020e4100;
extern u8 data_020e4104;
extern char data_021fbe48[];
extern char data_0213fee4[];
extern char data_021f486c[];
extern char data_021f4848[];
extern int func_020acea4(void *dst, unsigned int src);

void func_020ad720(void *a, void *b)
{
    VEC_Normalize(a, b);
    VEC_Normalize((char *) a + 0xc, (char *) b + 0xc);
    VEC_Normalize((char *) a + 0x18, (char *) b + 0x18);
}

void func_020ad4fc(int arg)
{
    u32 *p;
    Tbl *e;
    UnkStruct_020ad4fc *resource;
    int t20;
    int t24;
    u8 *cc;
    int v2;
    u32 pv;
    int k;
    void *g1;
    void *h;
    void *t7;
    Cell *c;
    UnkStruct_020ad4fc *o;
    u8 *bb;
    int off;
    int n0;
    u8 *ee;
    int m2;
    u32 q2c;
    u32 i;
    Work w;

    g1 = data_021c9b24;
    if (arg == 0) {
        return;
    }

    data_021f47d0 = 0;
    c = data_021f49a0;
    h = func_02064b18(&data_020e412c);
    resource = (UnkStruct_020ad4fc *) func_021077e8(h);
    func_02056064(resource, 0);
    resource = (UnkStruct_020ad4fc *) func_020561cc(resource, g1);
    func_020e9898(h);

    for (i = 0; i < 3; i++) {
        e = &data_020d1df4[i];
        t7 = data_020d1df4[i].unk_00;
        func_02064328(&w, &data_020e4148, t7);
        c->unk_00 = 0;
        c->unk_04 = 0;
        c->unk_08 = 0;
        c->unk_00 = resource;
        c->unk_14 = e->unk_06;
        t20 = func_02057a40(c->unk_00, t7);
        t24 = func_020579b8(c->unk_00, &w);
        o = (UnkStruct_020ad4fc *) c->unk_00;
        bb = (u8 *) o + 0x3c;
        off = o->unk_42;
        n0 = *(u16 *) (bb + off);
        p = (u32 *) (bb + off + 4 + n0 * t20);
        ee = (u8 *) o + o->unk_34;
        k = *(u16 *) (ee + 6);
        cc = ee + k;
        m2 = *(u16 *) (ee + k);
        v2 = *(u16 *) (cc + m2 * t24 + 4);
        q2c = (u16) o->unk_2C;
        pv = *p;
        c->unk_04 = pv + (u16) o->unk_08;
        c->unk_08 = (u32) v2 + q2c;
        c->unk_04 = c->unk_04 | ((u32) e->unk_04 << 0x12);
        c->unk_04 = c->unk_04 | ((u32) e->unk_05 << 0x10);
        c->unk_10 = (*p >> 0x1a) & 7;
        if (c->unk_10 != 2) {
            c->unk_08 = c->unk_08 >> 1;
        }
        c->unk_0C = (u16) (1 << (((*p >> 0x14) & 7) + 3));
        c->unk_0E = (u16) (1 << (((*p >> 0x17) & 7) + 3));
        c++;
    }

    if ((data_021f47d8 & 1) == 0) {
        data_021f47e8[0] = 0;
        data_021f47e8[1] = 0;
        data_021f47e8[2] = 0x1000;
        __register_global_object((void *) (&data_021f47e8), (((void *) func_020012dc)), (void *) (&data_021f4800));
        data_021f47d8 = data_021f47d8 | 1;
    }
    func_020ad0c0(&data_021f4904, &data_021f47e8, 0x119a, 0x119a, 2, 0x2000, 0, g1);
    func_020ad0c0(&data_021f4938, &data_021f47e8, 0x1666, 0x1666, 2, 0x2000, 0, g1);
    func_020ad0c0(&data_021f496c, &data_021f47e8, 0x2000, 0x2000, 2, 0x2000, 0, g1);
    func_020ad0c0(&data_021f489c, &data_021f47e8, 0x1ccc, 0x1ccc, 0, 0, 0, g1);
    func_020ad0c0(&data_021f48d0, &data_021f47e8, 0x555, 0x1000, 0, 0, 0, g1);
}

void func_020ad408(void)
{
    struct {
        u16 a;
        u8 b;
        u8 c;
        UnkStruct_020ad408 d;
    } l;
    int angle;
    u8 v;

    func_0209def4(&l.b);

    data_021f47d0 = FX_MulFunc((FX_Div((l.b + 60 * ((l.c + 6) % 12)) << 12, 0x2d0000) - 0x800) << 1, 0x1000);

    func_020e96c8(data_021fbe48, 0, 0, 0);
    func_020e9838(data_021fbe48, 0x20000, 0x20000, 0x20000);
    MTX_Concat43(data_021fbe48, data_0213fee4, data_021f486c);
    func_020ad720(data_021f486c, data_021f4848);

    l.a = func_0206586c();
    l.d.raw = l.a;

    angle = (u8) (FX_MulFunc(0x10000, FX_Div(((u8) (l.d.bits.f0 + l.d.bits.f1 + l.d.bits.f2)) << 12, 0x5d000)) >> 12);
    {
        int e = func_020655c4(0);
        v = (u8) (e + angle);
    }
    if (v > 31) {
        v = 31;
    }

    data_020e4104 = v;
    data_020e4100 = v;
}

void func_020ad3a0(void)
{
    unsigned int *p;
    unsigned int v;
    unsigned int i;

    (*(unsigned int *) &data_021f47d0) = 0;
    p = ((unsigned int *) data_021f49a0);
    for (i = 0; i < 3; i++) {
        *p = 0;
        p += 6;
    }
    v = (*(unsigned int *) &data_021c9b24);
    func_020acea4(((unsigned int *) &data_021f4904), v);
    func_020acea4(((unsigned int *) &data_021f4938), v);
    func_020acea4(((unsigned int *) &data_021f496c), v);
    func_020acea4(((unsigned int *) &data_021f489c), v);
    func_020acea4(((unsigned int *) &data_021f48d0), v);
}
