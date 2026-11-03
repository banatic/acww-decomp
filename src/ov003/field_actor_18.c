/* field_actor_18: 12 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02210b38 @ 0x02210b38, 0x2 bytes, Thumb
 * func_ov003_02210b28 @ 0x02210b28, 0x10 bytes, Thumb
 * func_ov003_02210a64 @ 0x02210a64, 0xc4 bytes, Thumb
 * func_ov003_02210a44 @ 0x02210a44, 0x20 bytes, Thumb
 * func_ov003_022109f8 @ 0x022109f8, 0x4c bytes, Thumb
 * func_ov003_02210950 @ 0x02210950, 0xa8 bytes, Thumb
 * func_ov003_0221094c @ 0x0221094c, 0x2 bytes, Thumb
 * func_ov003_022108c0 @ 0x022108c0, 0x8c bytes, Thumb
 * func_ov003_022108b0 @ 0x022108b0, 0x10 bytes, Thumb
 * func_ov003_022107ac @ 0x022107ac, 0x104 bytes, Thumb
 * func_ov003_022106e4 @ 0x022106e4, 0xc8 bytes, Thumb
 * func_ov003_022106a4 @ 0x022106a4, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x7d6];
    short unk_7D6;
} UnkStruct_02210b28;

struct S7D4 {
    u16 unk_00;
    u8 pad_02[2];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
};

struct UnkStruct_02210a64 {
    u8 pad_00[0x2d0];
    u8 sub_2d0[0x434];
    u32 unk_704;
    u8 pad_708[0xcc];
    struct S7D4 unk_7D4;
    u8 pad_7DC[0x14];
    u32 unk_7F0;
    u8 pad_7F4[0x8];
    u32 unk_7FC;
    u32 unk_800;
    u8 pad_804[0x14];
    u32 unk_818;
};

typedef struct {
    u16 unk_00;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
} UnkStruct_022109f8;

typedef struct {
    u8 pad_00[0xc];
    UnkStruct_022109f8 sub;
    u8 pad_12[0xa];
} Buf;

typedef struct {
    u16 unk_00;
    u8 pad_02[2];
    u32 v0;
    u32 v1;
    u32 v2;
    u16 v3;
    u8 v4;
} UnkStruct_02210950;

typedef struct {
    int x, y, z;
} Vec;

struct S7d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

struct UnkStruct_022108c0_2 {
    char pad_00[0x7d4];
    struct S7d4 unk_7D4;
    char pad_7E4[0x800 - 0x7e4];
    void *unk_800;
};

struct UnkStruct_022108c0 {
    Vec a, b, c;
};

typedef struct {
    char pad_00[0x7e4];
    short unk_7E4;
} UnkStruct_022108b0;

typedef struct {
    int pad_00;
    int a;
    int b;
    int c;
} UnkStruct_022107ac;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x2d8 - 0x90];
    unsigned int unk_2D8;
    char pad_2DC[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    UnkStruct_022107ac sub;
    char pad_7E4[0x800 - 0x7e4];
    int unk_800;
} UnkStruct_022107ac_2;

typedef struct UnkStruct_022106e4_2 {
    u8 pad_00[0x12];
    u8 unk_12;
} UnkStruct_022106e4_2;

typedef struct UnkStruct_022106e4 UnkStruct_022106e4;

struct UnkStruct_022106e4 {
    u8 pad_00[0x2d0];
    u8 pad_2D0[0x704 - 0x2d0];
    u32 unk_704;
    u8 pad_708[0x7d4 - 0x708];
    UnkStruct_022106e4_2 sub7d4;
    u8 pad_7E7[0x7f0 - (0x7d4 + 0x13)];
    u32 unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    u32 unk_7FC;
    u32 unk_800;
};

extern void func_0200fb34(void *self, short val);
extern int func_02073908(void *p, u32 v);
extern u32 func_02008258(void *p, u32 v);
extern int func_02056f94(void *p);
extern void func_020109fc(void *p, int a, int b, int c);
extern void func_02010f5c(int arg);
extern void func_02010d64(void *);
extern unsigned int func_0200e92c(Buf *);
extern void func_0200e90c(Buf *, int, u32, short);
extern void *func_0200e894(void *, Buf *);
extern int func_0200e91c(Buf *);
extern void func_0204f794(u32 *out, u8 a, u8 b);
extern int func_020e8ed8(u32 a, u32 b);
extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern void func_0200f268(void *p, int a);
extern unsigned int *func_0200f27c(void *p, int a);
extern int func_0200f290(void *, int);
extern int func_ov003_022211bc(void *, void *);
extern void func_ov003_02221150(void *, void *);
extern unsigned char data_020ccf94[];
extern void *data_021c80bc;
extern int func_020912d4(int a, void *b, void *c, int d);
extern unsigned short *func_0204f5a8(void *a, void *b, int c);
extern int func_0200f328(void *self, int a);
extern int func_0200c9a8(UnkStruct_022106e4 *, int, int, int);
extern void func_0203ee08(UnkStruct_022106e4 *, void *);
extern int func_02008380(UnkStruct_022106e4 *, int, int, int);
extern int func_0200d4e8(UnkStruct_022106e4 *, int, int, int);
extern int func_0200f434(void *p, void *q);

void *func_ov003_022109f8(void *a0, u32 a1, u32 *a2, u16 a3, u32 a4, short a5);

void func_ov003_02210b38(void *receiver, int event) {}

void func_ov003_02210b28(UnkStruct_02210b28 *self)
{
    func_0200fb34(self, self->unk_7D6);
}

void func_ov003_02210a64(struct UnkStruct_02210a64 *self)
{
    struct S7D4 *r4 = &self->unk_7D4;
    u32 args[2];
    u8 f5, f6;

    if (func_02073908((*(void * *) data_020ccf94), self->unk_800) == 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    } else {
        if (self->unk_818 == 1) {
            r4->unk_07 = 1;
        }
        if (func_02056f94(&self->sub_2d0) != 0 || self->unk_704 == 0x4a) {
            if (func_02056f94(&self->sub_2d0) != 0) {
                func_020109fc(self, 0x4a, 3, 0);
            }
            if (r4->unk_04 != 2 || r4->unk_07 != 0) {
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                f6 = r4->unk_06;
                f5 = r4->unk_05;
                args[0] = f5;
                args[1] = f6;
                func_ov003_022109f8(self, (u8) r4->unk_04, args, r4->unk_00, 6, -1);
            }
        }
    }
}

void func_ov003_02210a44(void *r0)
{
    func_ov003_02210b28((UnkStruct_02210b28 *) r0);
    func_02010f5c((int) r0);
    func_02010d64(r0);
    func_ov003_02210a64((struct UnkStruct_02210a64 *) r0);
}

void *func_ov003_022109f8(void *a0, u32 a1, u32 *a2, u16 a3, u32 a4, short a5)
{
    Buf buf;
    UnkStruct_022109f8 *p;
    void *ret;

    func_0200e92c(&buf);
    p = &buf.sub;
    func_0200e90c(&buf, 0x62, a4, a5);
    p->unk_04 = (u8) a1;
    p->unk_02 = (u8) a2[0];
    p->unk_03 = (u8) a2[1];
    p->unk_00 = a3;
    ret = func_0200e894(a0, &buf);
    func_0200e91c(&buf);
    return ret;
}

void func_ov003_02210950(void *self, void *b, int previous)
{
    u32 local[3];
    u8 *b2;
    u8 byte;
    u32 v;
    UnkStruct_02210950 *d;

    b2 = (u8 *) b + 0xc;
    d = (UnkStruct_02210950 *) ((u8 *) self + 0x7d4);
    byte = b2[4];
    func_0204f794(local, b2[2], b2[3]);

    d->unk_00 = *(u16 *) ((u8 *) b + 0xc);
    d->v4 = byte;
    d->v0 = local[0];
    d->v1 = local[1];
    d->v2 = local[2];
    d->v3 = (u16) func_020e8ed8(local[0] - *(u32 *) ((u8 *) self + 0x5c), local[2] - *(u32 *) ((u8 *) self + 0x64));

    v = *(u32 *) ((u8 *) self + 0x704);
    if (v == 0x49) {
        goto case49;
    }
    if (v == 0x4a) {
        goto case4a;
    }
    goto else_block;

case4a:
    func_020109a0(self, 0x51, 3, 0);
    goto done;

case49:
    if (func_02056f94((u8 *) self + 0x2d0) != 0) {
        func_020109a0(self, 0x51, 3, 0);
    }
    goto done;

else_block:
    func_020109a0(self, 0x49, 3, 0);

done:
    func_0200f268(self, 0xd);
    func_0200f27c(self, 0x1c);
}

void func_ov003_0221094c(void *receiver, int event) {}

void func_ov003_022108c0(struct UnkStruct_022108c0_2 *o)
{
    struct UnkStruct_022108c0 t;
    void *g = *(void **) data_020ccf94;
    struct S7d4 *p;
    if (func_02073908(g, (u32) o->unk_800) != 0) {
        return;
    }
    if (func_0200f290(o, 0x1c) == 0) {
        return;
    }
    p = &o->unk_7D4;
    t.a.x = p->unk_04;
    t.a.y = p->unk_08;
    t.a.z = p->unk_0C;
    if (func_02073908(g, (u32) o->unk_800) != 0) {
        t.b.x = t.a.x;
        t.b.y = t.a.y;
        t.b.z = t.a.z;
        func_ov003_022211bc(o->unk_800, &t.b);
    } else {
        t.c.x = t.a.x;
        t.c.y = t.a.y;
        t.c.z = t.a.z;
        func_ov003_02221150(o->unk_800, &t.c);
    }
    func_0200f268(o, 0x1c);
}

void func_ov003_022108b0(UnkStruct_022108b0 *self)
{
    func_0200fb34((void *) self, self->unk_7E4);
}

void func_ov003_022107ac(UnkStruct_022107ac_2 *self)
{
    if (self->unk_704 != 0x49) {
        short s;
        int w0[3];
        int w1[3];
        int w2[3];
        UnkStruct_022107ac *p;
        int v;
        unsigned short *res;
        int cond;

        p = &self->sub;
        w0[0] = p->a;
        w0[1] = p->b;
        w0[2] = p->c;
        s = self->unk_8E;
        v = (self->unk_2D8 << 4) >> 16;

        switch (v) {
            case 1:
                func_020912d4(9, w0, &s, 0);
                break;
            case 5:
                if (func_02073908((*(void * *) data_020ccf94), self->unk_800)) {
                    w1[0] = w0[0];
                    w1[1] = w0[1];
                    w1[2] = w0[2];
                    func_ov003_022211bc((void *) self->unk_800, (void *) w1);
                } else {
                    res = func_0204f5a8(data_021c80bc, w0, 0);
                    cond = 0;
                    if (res[0] >= 0xfc && res[0] <= 0xfd) {
                        cond = 1;
                    }
                    if (cond) {
                        w2[0] = w0[0];
                        w2[1] = w0[1];
                        w2[2] = w0[2];
                        func_ov003_02221150((void *) self->unk_800, (void *) w2);
                    }
                }
                func_0200f268(self, 0x1c);
                break;
            case 7:
                func_0200f328(self, 0x843);
                func_0200f27c(self, 9);
                break;
            case 0x15:
                func_020912d4(0xa, w0, 0, 0);
                break;
            default:
                break;
        }
    }
    func_02010f5c((int) self);
}

void func_ov003_022106e4(UnkStruct_022106e4 *self)
{
    UnkStruct_022106e4_2 *p;
    u8 mode;
    void *base;

    if (func_02056f94((char *) self + 0x2d0) == 0) {
        return;
    }

    p = &self->sub7d4;

    if (self->unk_704 == 0x49) {
        func_020109a0((void *) self, 0x51, 3, 0);
        return;
    }

    self->unk_7FC = (int) func_02008258((void *) self, self->unk_7F0);
    mode = p->unk_12;

    if (mode == 1) {
        func_0200c9a8(self, 3, 5, -1);
        return;
    }

    if (func_02073908((void *) ((*(u32 *) data_020ccf94)), self->unk_800) != 0 && mode == 3) {
        if (func_0200f290((void *) self, 0x11) != 0) {
            func_0200f268((void *) self, 0x11);
            base = (char *) self;
            if (self != 0) {
                base = (char *) self + 0xec;
            }
            func_0203ee08(self, base);
        }
        func_02008380(self, 3, 1, -1);
    } else {
        func_0200d4e8(self, 3, 1, -1);
    }
}

void func_ov003_022106a4(void *p)
{
    int *base;
    int tmp[3];
    int i;

    func_ov003_022108b0((UnkStruct_022108b0 *) p);
    func_ov003_022107ac((UnkStruct_022107ac_2 *) p);

    base = (int *) ((char *) p + 0x7d4);
    tmp[0] = base[1];
    tmp[1] = base[2];
    tmp[2] = base[3];

    func_0200f434(p, tmp);
    func_02010d64(p);
    func_ov003_022106e4((UnkStruct_022106e4 *) p);
}
