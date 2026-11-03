/* cafe_guest_5: 5 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_022746b8 @ 0x022746b8, 0x6 bytes, Thumb
 * func_ov068_022746b0 @ 0x022746b0, 0x6 bytes, Thumb
 * func_ov068_022744b0 @ 0x022744b0, 0x200 bytes, Thumb
 * func_ov068_02274490 @ 0x02274490, 0x20 bytes, Thumb
 * func_ov068_0227440c @ 0x0227440c, 0x84 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_022746b8;

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_022746b0;

typedef struct {
    char pad_00[0x652];
    u16 unk_652;
    char pad_654[0x730 - 0x654];
    int unk_730;
    int unk_734;
    char pad_738[0x74a - 0x738];
    u8 unk_74A;
} UnkStruct_022744b0;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    int unk_B0;
    UnkStruct_022744b0 *volatile unk_B4;
    char pad_B8[4];
    volatile signed char unk_BC;
    volatile signed char unk_BD;
    volatile signed char unk_BE;
    volatile signed char unk_BF;
    volatile signed char unk_C0;
} UnkStruct_022744b0_3;

typedef struct {
    int unk_00;
    u8 unk_04;
} UnkStruct_022744b0_4;

typedef struct {
    int b[10];
} UnkStruct_022744b0_5;

typedef struct {
    int unk_00, w1;
} UnkStruct_022744b0_2;

struct UnkStruct_02274490 {
    char pad_00[0x730];
    int value;
};

struct Main {
    char pad_00[0xb4];
    struct UnkStruct_02274490 *sub;
};

struct UnkStruct_0227440c {
    char b[0x28];
};

struct UnkStruct_0227440c_2 {
    char b[0x24];
};

struct UnkStruct_0227440c_3 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    char *unk_B4;
};

extern int data_ov068_02277ca4[];
extern u8 data_ov068_022767e8[];
extern void *func_020984e8(void);
extern void func_0209e474(UnkStruct_022744b0_2 *z);
extern int func_02099e9c(u16 *p);
extern int func_0202ea80(int a, int b);
extern int func_02099020(void *h, int a);
extern void func_02098ff8(void *h, int a);
extern void *func_02062fbc(UnkStruct_022744b0_5 *c);
extern void *func_02062f4c(UnkStruct_022744b0_5 *c);
extern void *func_02062e50(UnkStruct_022744b0_5 *c);
extern void *func_02062e00(UnkStruct_022744b0_5 *c);
extern void func_020a8874(UnkStruct_022744b0_5 *c, void *p, int n);
extern int func_020a8a70(UnkStruct_022744b0_5 *a, UnkStruct_022744b0_5 *b, int c, int d);
extern void func_020683b4(void *a, int b, UnkStruct_022744b0_5 *c, int d);
extern void func_02015de4(UnkStruct_022744b0_3 *self, u16 *p, int a, int b);
extern int func_020644cc(int a);

void func_ov068_0227440c(struct UnkStruct_0227440c_3 *o, int arg2);

void func_ov068_022746b8(UnkStruct_022746b8 *p, unsigned long v)
{
    p->unk_B0 = v;
}

unsigned long func_ov068_022746b0(UnkStruct_022746b0 *p)
{
    return p->unk_B0;
}

void func_ov068_022744b0(UnkStruct_022744b0_3 *self, UnkStruct_022744b0_4 *out)
{
    u16 s[2];
    u16 w[2];
    UnkStruct_022744b0_2 z;
    UnkStruct_022744b0_5 ctx;
    UnkStruct_022744b0_5 ctx2;
    void *h;
    int v;
    unsigned char b;
    int r;
    unsigned int ok;

    self->unk_BC = -1;
    self->unk_BD = -1;
    self->unk_BE = -1;
    self->unk_BF = -1;
    self->unk_C0 = -1;
    h = func_020984e8();
    out->unk_00 = data_ov068_02277ca4[self->unk_B4->unk_730];
    v = self->unk_B4->unk_730;
    if (v == 7) {
        if ((int) func_ov068_022746b0((UnkStruct_022746b0 *) self) == 0) {
            z.unk_00 = 0;
            z.w1 = 0;
            func_0209e474(&z);
            b = ((unsigned char *) &z)[2];
            if (b < 0x14 && b >= 0x13) {
                s[0] = 0x3530;
                r = func_02099e9c(&s[0]);
                ok = 0;
                if (r != -1) {
                    ok = 1;
                }
                if (ok != 0) {
                    out->unk_04 = 0xe;
                } else {
                    out->unk_04 = 0x13;
                }
            } else if (self->unk_B4->unk_74A != 0) {
                out->unk_04 = 0;
            } else if (func_0202ea80(0xd, 0) != 0) {
                s[1] = 0x3530;
                r = func_02099e9c(&s[1]);
                ok = 0;
                if (r != -1) {
                    ok = 1;
                }
                if (ok != 0) {
                    out->unk_04 = 0xe;
                } else {
                    out->unk_04 = 0x12;
                }
            } else if (func_02099020(h, 7) == 0) {
                out->unk_04 = 1;
                func_02098ff8(h, 7);
            } else if (func_0202ea80(0xc, 1) == 0) {
                out->unk_04 = 2;
            } else {
                out->unk_04 = 3;
            }
        } else {
            if ((int) func_ov068_022746b0((UnkStruct_022746b0 *) self) == 1) {
                func_02062fbc(&ctx);
                func_02062e50(&ctx2);
                func_020a8874(&ctx2, &self->unk_B4->unk_734, 0xa);
                func_020a8a70(&ctx, &ctx2, 0, 0);
                func_020683b4(self->unk_40, 0, &ctx, 7);
                func_02062e00(&ctx2);
                func_02062f4c(&ctx);
            } else if ((int) func_ov068_022746b0((UnkStruct_022746b0 *) self) == 2) {
                w[0] = self->unk_B4->unk_652;
                func_02015de4(self, &w[0], 1, 7);
                w[1] = self->unk_B4->unk_652;
                func_02015de4(self, &w[1], 2, 7);
            }
            out->unk_04 = data_ov068_022767e8[self->unk_B0];
            out->unk_00 = data_ov068_02277ca4[self->unk_B4->unk_730];
        }
    } else {
        if (func_0202ea80(v + 0x21, 1) == 0) {
            out->unk_04 = func_020644cc(3);
        } else {
            out->unk_04 = func_020644cc(5) + 3;
        }
    }
}

void func_ov068_02274490(struct Main *param, int arg2)
{
    if (param->sub->value == 7) {
        func_ov068_0227440c((struct UnkStruct_0227440c_3 *) param, arg2);
    }
}

void func_ov068_0227440c(struct UnkStruct_0227440c_3 *o, int arg2)
{
    unsigned short h[2];
    struct UnkStruct_0227440c a;
    struct UnkStruct_0227440c_2 c;
    switch (o->unk_1E) {
        case 0xc:
        case 0xd:
            h[0] = *(unsigned short *) (o->unk_B4 + 0x652);
            func_02015de4((UnkStruct_022744b0_3 *) o, (u16 *) h, 1, 7);
            break;
        case 0xb:
            func_02062fbc((UnkStruct_022744b0_5 *) (&a));
            func_02062e50((UnkStruct_022744b0_5 *) (&c));
            func_020a8874((UnkStruct_022744b0_5 *) (&c), o->unk_B4 + 0x734, 0xa);
            func_020a8a70((UnkStruct_022744b0_5 *) (&a), (UnkStruct_022744b0_5 *) (&c), 0, 0);
            func_020683b4(o->unk_40, 0, (UnkStruct_022744b0_5 *) (&a), 7);
            func_02062e00((UnkStruct_022744b0_5 *) (&c));
            func_02062f4c((UnkStruct_022744b0_5 *) (&a));
            break;
    }
}
