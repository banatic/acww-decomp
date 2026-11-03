/* field_camera_modes: 11 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226e164 @ 0x0226e164, 0x20 bytes, Thumb
 * func_ov068_0226e0f8 @ 0x0226e0f8, 0x6c bytes, Thumb
 * func_ov068_0226e008 @ 0x0226e008, 0xf0 bytes, Thumb
 * func_ov068_0226de04 @ 0x0226de04, 0x204 bytes, Thumb
 * func_ov068_0226ddec @ 0x0226ddec, 0x18 bytes, Thumb
 * func_ov068_0226dd7c @ 0x0226dd7c, 0x70 bytes, Thumb
 * func_ov068_0226dd34 @ 0x0226dd34, 0x48 bytes, Thumb
 * func_ov068_0226dcc0 @ 0x0226dcc0, 0x74 bytes, Thumb
 * func_ov068_0226dc64 @ 0x0226dc64, 0x5c bytes, Thumb
 * func_ov068_0226dc08 @ 0x0226dc08, 0x5c bytes, Thumb
 * func_ov068_0226dabc @ 0x0226dabc, 0x14c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    Vec3 sub;
} Other;

typedef struct {
    char pad_00[0x21c];
    Other *ptr;
} UnkStruct_0226e0f8;

typedef struct Vec3_0226e008 {
    s32 x;
    s32 y;
    s32 z;
} Vec3_0226e008;

typedef struct Subst {
    u16 type;
    u16 type2;
    s32 dest[3];
    Vec3_0226e008 *vec;
    s32 counter;
} Subst;

typedef struct UnkStruct_0226e008 {
    u8 pad_00[0x110];
    s32 pos[3];
    u8 pad_11C[0x100];
    Subst sub;
} UnkStruct_0226e008;

typedef struct {
    short unk_00;
    short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_0226de04;

typedef struct {
    unsigned short a, b;
} UnkStruct_0226de04_2;

typedef struct {
    int a, b, c, d;
} Blk;

struct UnkStruct_0226dd7c {
    int a;
    int b;
    int c;
};

typedef struct {
    char pad_00[0x1fc];
    int unk_1FC;
} UnkStruct_0226dd34;

typedef struct {
    fx32 x, y, z;
} Vec;

typedef struct {
    char pad_00[0x110];
    fx32 unk_110, unk_114, unk_118;
} UnkStruct_0226dcc0;

struct TableEntry {
    unsigned short x;
    unsigned short y;
    unsigned char pad_04[8];
};

struct UnkStruct_0226dc64 {
    unsigned char pad_00[0x21c];
    unsigned short unk_21C;
    unsigned char pad_21E[2];
    unsigned short unk_220;
    unsigned char pad_222[2];
    unsigned char unk_224;
};

typedef struct {
    unsigned char pad[0x21e];
    unsigned short v1;
    unsigned char pad_220[2];
    unsigned short v2;
    unsigned char pad_224;
    unsigned char idx;
} UnkStruct_0226dc08;

typedef struct {
    unsigned short w;
    unsigned char pad[10];
} TabEntry;

typedef struct {
    char pad_00[0x174];
    short unk_174;
    char pad_176[0x21c - 0x176];
    short unk_21C;
    short unk_21E;
    unsigned char unk_220;
    unsigned char pad_221;
    unsigned char unk_222;
    unsigned char pad_223;
    unsigned char unk_224;
    unsigned char unk_225;
} UnkStruct_0226dabc;

extern void func_0203caa4(int, int, int);
extern void func_0203c99c(int, int);
extern void func_0203ad68(void);
extern void func_0203bc50(UnkStruct_0226e0f8 *self, Vec3 *v);
extern void func_01ffcbb0(int *buf, UnkStruct_0226e0f8 *self);
extern void func_0203bd84(UnkStruct_0226e0f8 *self, int *buf, int a, int b, int c);
extern int func_0204f490(Vec3_0226e008 *a, s32 *b, s32 *c, s32 *d, s32 *e, u16 *f, u16 *g, int h, int i);
extern void func_0204f7ac(s32 *out, s32 v0, s32 v1, s32 v2, s32 v3);
extern Vec3_0226e008 *data_021c80bc;
extern void VEC_Add(Vec3 *d, int k, Vec3 *s);
extern int func_020e88dc(void *p, int a, int b);
extern int func_020e908c(void *p, Vec3 *v, int a, int b, int c);
extern int func_020e89dc(void *p, int a, int b);
extern void func_0203be6c(void *self);
extern int func_0203c57c(void *self);
extern int func_0203c568(void *self);
extern int func_0203c548(void *self);
extern int data_ov068_02277288;
extern int data_ov068_02277280;
extern int data_ov068_02277284;
extern unsigned short data_ov068_022772d4[][2];
extern int data_ov068_022767cc[];
extern int data_ov068_022772f0[];
extern struct UnkStruct_0226dd7c data_021fbee8;
extern void *func_02095794(int);
extern void func_0203ad58(void);
extern void func_0203c40c(void *p, int a);
extern int func_020644cc(int val);
extern struct TableEntry data_020ca17c[];
extern TabEntry data_020ca17e[];
extern int func_020e8840(void *);
extern int FX_MulFunc(int, int);
extern unsigned char data_020ca180[];
extern unsigned char data_020ca184[];
extern unsigned char FX_SinCosTable_[];

void func_ov068_0226dc64(struct UnkStruct_0226dc64 *self, unsigned char v);
int func_ov068_0226dabc(UnkStruct_0226dabc *self);

int func_ov068_0226e164(int a)
{
    int zero = 0;
    func_0203caa4(a, zero, zero);
    func_0203c99c(a, 0);
    func_0203ad68();
    return 1;
}

void func_ov068_0226e0f8(UnkStruct_0226e0f8 *self)
{
    Other *other;
    Vec3 *sub;
    int a, b, c;
    Vec3 v;
    int buf[4];

    other = self->ptr;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    if (other != 0) {
        sub = &other->sub;
        v.x = other->sub.x;
        v.y = sub->y;
        v.z = sub->z;
    }
    func_0203bc50(self, &v);
    func_0203be6c((void *) self);
    func_01ffcbb0(buf, self);
    a = func_0203c57c((void *) self);
    b = func_0203c568((void *) self);
    c = func_0203c548((void *) self);
    func_0203bd84(self, buf, a, b, c);
}

int func_ov068_0226e008(UnkStruct_0226e008 *self)
{
    Vec3_0226e008 *g;
    u16 arr[2];
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;
    s32 out[3];
    Subst *p;
    func_0203caa4((int) self, 0, 0);
    func_0203c99c((int) self, 0);
    func_0203ad68();
    g = data_021c80bc;
    v0 = 0;
    v1 = 0;
    v2 = 0;
    v3 = 0;
    p = &self->sub;
    p->type = 0x3c;
    p->type2 = 0;
    if (g) {
        arr[0] = 0x5014;
        arr[1] = 0x501a;
        if (func_0204f490(g, &v0, &v1, &v2, &v3, arr, arr + 1, 1, 0) == 1) {
            func_0204f7ac(out, v0, v1, v2, v3);
            p->vec = (*(Vec3_0226e008 * *) data_ov068_022772f0);
            self->pos[0] = out[0];
            self->pos[1] = out[1];
            self->pos[2] = out[2];
        }
    }
    p->dest[0] = self->pos[0];
    p->dest[1] = self->pos[1];
    p->dest[2] = self->pos[2];
    self->pos[0] += p->vec->x;
    self->pos[1] += p->vec->y;
    self->pos[2] += p->vec->z;
    p->counter = 0;
    return 1;
}

void func_ov068_0226de04(void *self)
{
    UnkStruct_0226de04 *s = (UnkStruct_0226de04 *) ((char *) self + 0x21c);
    Vec3 v;
    void *ctx;
    int l18, f1, f2, f3;
    UnkStruct_0226de04_2 e;
    int a2c, a30, a34, a38;
    Vec3 out;
    Blk t54;
    int ta, tb, tc;
    int t1, t2, tw;

    v.x = s->unk_04;
    v.y = s->unk_08;
    v.z = s->unk_0C;
    VEC_Add(&v, s->unk_10, &v);
    func_020e88dc((char *) s + 0x14, data_ov068_02277288, data_ov068_02277280);
    if (func_020e908c((char *) self + 0x110, &v, data_ov068_02277284, s->unk_14, 8) == 0) {
        if (func_020e89dc(s, 0, 1) != 0) {
            s->unk_00 = 0x3c;
            if (func_020e89dc((char *) s + 2, 7, 1) != 0) {
                s->unk_02 = 0;
            }
            ctx = (*(void * *) &data_021c80bc);
            l18 = 0;
            a2c = 0;
            a30 = 0;
            a34 = 0;
            a38 = 0;
            if (ctx != 0) {
                f1 = l18;
                f2 = l18;
                f3 = l18;
                do {
                    if (data_ov068_022772d4[s->unk_02][0] >= 0x5001 && data_ov068_022772d4[s->unk_02][0] <= 0x5008) {
                        t1 = 1;
                    } else {
                        t1 = f1;
                    }
                    if (t1 != 0) {
                        data_ov068_022772d4[s->unk_02][0]++;
                        if (data_ov068_022772d4[s->unk_02][0] > 0x5008) {
                            data_ov068_022772d4[s->unk_02][0] = 0x5001;
                        }
                        data_ov068_022772d4[s->unk_02][1] = data_ov068_022772d4[s->unk_02][0];
                    } else {
                        if (data_ov068_022772d4[s->unk_02][0] >= 0x500d && data_ov068_022772d4[s->unk_02][0] <= 0x5010) {
                            t2 = 1;
                        } else {
                            t2 = f2;
                        }
                        if (t2 != 0) {
                            data_ov068_022772d4[s->unk_02][0]++;
                            if (data_ov068_022772d4[s->unk_02][0] > 0x5010) {
                                data_ov068_022772d4[s->unk_02][0] = 0x500d;
                            }
                            data_ov068_022772d4[s->unk_02][1] = data_ov068_022772d4[s->unk_02][0];
                            l18 = data_ov068_022772d4[s->unk_02][0] - 0x500d;
                        }
                    }
                    e.a = data_ov068_022772d4[s->unk_02][0];
                    e.b = data_ov068_022772d4[s->unk_02][1];
                } while (func_0204f490((Vec3_0226e008 *) ctx, (s32 *) (&a2c), (s32 *) (&a30), (s32 *) (&a34), (s32 *) (&a38), (u16 *) (&e.a), (u16 *) (&e.b), data_ov068_022767cc[s->unk_02], f3) == 0);
                func_0204f7ac((s32 *) (&out), a2c, a30, a34, a38);
                s->unk_04 = out.x;
                s->unk_08 = out.y;
                s->unk_0C = out.z;
                tw = data_ov068_022772f0[s->unk_02];
                l18 = l18 * 0xc;
                s->unk_10 = tw + l18;
                s->unk_14 = 0;
            }
        }
    }
    func_0203be6c(self);
    func_01ffcbb0((int *) (&t54), (UnkStruct_0226e0f8 *) self);
    ta = func_0203c57c(self);
    tb = func_0203c568(self);
    tc = func_0203c548(self);
    func_0203bd84((UnkStruct_0226e0f8 *) self, (int *) (&t54), ta, tb, tc);
}

int func_ov068_0226ddec(int param1)
{
    func_0203caa4(param1, 0x1a, 0);
    func_0203ad68();
    return 1;
}

void func_ov068_0226dd7c(int obj)
{
    int a;
    int b;
    int c;
    struct UnkStruct_0226dd7c s;
    int buf[4];
    struct UnkStruct_0226dd7c *p;

    s.a = data_021fbee8.a;
    s.b = data_021fbee8.b;
    s.c = data_021fbee8.c;
    p = func_02095794(4);
    if (p != 0) {
        s.a = p->a;
        s.b = p->b;
        s.c = p->c;
    }
    func_0203bc50((UnkStruct_0226e0f8 *) obj, (Vec3 *) (&s));
    func_0203be6c((void *) obj);
    func_01ffcbb0((int *) buf, (UnkStruct_0226e0f8 *) obj);
    a = func_0203c57c((void *) obj);
    b = func_0203c568((void *) obj);
    c = func_0203c548((void *) obj);
    func_0203bd84((UnkStruct_0226e0f8 *) obj, (int *) buf, a, b, c);
}

int func_ov068_0226dd34(UnkStruct_0226dd34 *p)
{
    func_0203caa4((int) p, 16, 0);
    func_0203c99c((int) p, 0);
    if (p->unk_1FC == 2) {
        func_0203ad58();
    } else {
        func_0203ad68();
    }
    func_0203c40c(p, 0x1c71);
    func_ov068_0226dc64((struct UnkStruct_0226dc64 *) p, 0);
    return 1;
}

void func_ov068_0226dcc0(UnkStruct_0226dcc0 *self)
{
    Vec loc;
    int a, b;
    self->unk_110 = (*(Vec *) &data_021fbee8).x;
    self->unk_114 = (*(Vec *) &data_021fbee8).y;
    self->unk_118 = (*(Vec *) &data_021fbee8).z;
    self->unk_114 += func_ov068_0226dabc((UnkStruct_0226dabc *) self);
    func_0203be6c(self);
    func_01ffcbb0((int *) (&loc), (UnkStruct_0226e0f8 *) self);
    a = func_0203c57c(self);
    b = func_0203c568(self);
    func_0203bd84((UnkStruct_0226e0f8 *) self, (int *) (&loc), a, b, func_0203c548(self));
}

void func_ov068_0226dc64(struct UnkStruct_0226dc64 *self, unsigned char v)
{
    self->unk_224 = v;
    if (self->unk_224 >= 4) {
        self->unk_224 = 0;
    }

    self->unk_220 = data_020ca17c[self->unk_224].x;
    self->unk_220 += func_020644cc(data_020ca17c[self->unk_224].y);
    self->unk_21C = 0;
}

void func_ov068_0226dc08(UnkStruct_0226dc08 *self, unsigned char arg)
{
    self->idx = arg;
    if (self->idx >= 4) {
        self->idx = 0;
    }

    self->v2 = ((TabEntry *) data_020ca17c)[self->idx].w;
    self->v2 = (unsigned short) (self->v2 + func_020644cc(data_020ca17e[self->idx].w));
    self->v1 = 0;
}

int func_ov068_0226dabc(UnkStruct_0226dabc *self)
{
    short val, val2, s5, s4, t, t2;
    unsigned char b, b2, b5, b4;
    unsigned char *p224, *p225;
    int idx5, idx5b, idx4, idx4b, q, q2, r, r2, w, w2, res, res2, r0, sum, sum2;

    if (func_020e8840(&self->unk_220) == 0) {
        val = self->unk_21C;
        if (val < 0) {
            val = -val;
        }
        if (val < 0x100) {
            b = self->unk_224;
            if (b == 0) {
                r0 = func_020644cc(0x64);
                if (r0 < 0x50) {
                    self->unk_224 = 1;
                } else {
                    self->unk_224 = 2;
                }
            } else {
                if (b == 2) {
                    self->unk_224 = 1;
                } else {
                    self->unk_224 = 0;
                }
            }
            func_ov068_0226dc64((struct UnkStruct_0226dc64 *) self, self->unk_224);
        }
    }

    if (func_020e8840(&self->unk_222) == 0) {
        val2 = self->unk_21E;
        if (val2 < 0) {
            val2 = -val2;
        }
        if (val2 < 0x100) {
            b2 = self->unk_225;
            if (b2 == 0) {
                self->unk_225 = 1;
            } else {
                if (b2 == 2) {
                    self->unk_225 = 1;
                } else {
                    self->unk_225 = 0;
                }
            }
            func_ov068_0226dc08((UnkStruct_0226dc08 *) self, self->unk_225);
        }
    }

    p225 = &self->unk_225;
    b5 = *p225;
    idx5 = b5 * 12;
    s5 = *(short *) (data_020ca180 + idx5);
    if (s5 != 0) {
        sum = self->unk_21E + (int) s5;
        self->unk_21E = (short) sum;
        q = (unsigned short) self->unk_21E >> 4;
        r = q * 4;
        t = *(short *) (FX_SinCosTable_ + r);
        b5 = *p225;
        idx5b = b5 * 12;
        w = *(int *) (data_020ca184 + idx5b);
        res = FX_MulFunc(t, w);
        self->unk_174 = (short) res;
    }

    p224 = &self->unk_224;
    b4 = *p224;
    idx4 = b4 * 12;
    s4 = *(short *) (data_020ca180 + idx4);
    if (s4 != 0) {
        sum2 = self->unk_21C + (int) s4;
        self->unk_21C = (short) sum2;
        q2 = (unsigned short) self->unk_21C >> 4;
        r2 = q2 * 4;
        t2 = *(short *) (FX_SinCosTable_ + r2);
        b4 = *p224;
        idx4b = b4 * 12;
        w2 = *(int *) (data_020ca184 + idx4b);
        res2 = FX_MulFunc(t2, w2);
        return res2;
    } else {
        return 0;
    }
}
