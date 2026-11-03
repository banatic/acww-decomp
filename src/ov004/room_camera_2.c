/* room_camera_2: 27 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022473f4 @ 0x022473f4, 0x44 bytes, Thumb
 * func_ov004_022473a8 @ 0x022473a8, 0x4c bytes, Thumb
 * func_ov004_02247368 @ 0x02247368, 0x3e bytes, Thumb
 * func_ov004_0224732c @ 0x0224732c, 0x3a bytes, Thumb
 * func_ov004_0224730c @ 0x0224730c, 0x20 bytes, Thumb
 * func_ov004_022472ec @ 0x022472ec, 0x20 bytes, Thumb
 * func_ov004_022472c4 @ 0x022472c4, 0x28 bytes, Thumb
 * func_ov004_02247260 @ 0x02247260, 0x64 bytes, Thumb
 * func_ov004_02247238 @ 0x02247238, 0x28 bytes, Thumb
 * func_ov004_022471d4 @ 0x022471d4, 0x64 bytes, Thumb
 * func_ov004_0224719c @ 0x0224719c, 0x38 bytes, Thumb
 * func_ov004_0224716c @ 0x0224716c, 0x30 bytes, Thumb
 * func_ov004_022470cc @ 0x022470cc, 0xa0 bytes, Thumb
 * func_ov004_0224708c @ 0x0224708c, 0x40 bytes, Thumb
 * func_ov004_02247028 @ 0x02247028, 0x64 bytes, Thumb
 * func_ov004_02247008 @ 0x02247008, 0x20 bytes, Thumb
 * func_ov004_02246fa4 @ 0x02246fa4, 0x64 bytes, Thumb
 * func_ov004_02246f90 @ 0x02246f90, 0x14 bytes, Thumb
 * func_ov004_02246f7c @ 0x02246f7c, 0x14 bytes, Thumb
 * func_ov004_02246f64 @ 0x02246f64, 0x18 bytes, Thumb
 * func_ov004_02246ef4 @ 0x02246ef4, 0x70 bytes, Thumb
 * func_ov004_02246ecc @ 0x02246ecc, 0x28 bytes, Thumb
 * func_ov004_02246eb8 @ 0x02246eb8, 0x14 bytes, Thumb
 * func_ov004_02246ea8 @ 0x02246ea8, 0x10 bytes, Thumb
 * func_ov004_02246e98 @ 0x02246e98, 0x10 bytes, Thumb
 * func_ov004_02246e88 @ 0x02246e88, 0x10 bytes, Thumb
 * func_ov004_02246de8 @ 0x02246de8, 0xa0 bytes, Thumb
 */

#include "types.h"

#define S32(o) (*(int *) ((char *) self + (o)))
#define S16(o) (*(short *) ((char *) self + (o)))

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02247260 {
    char unk_00[0x110];
    Vec3 a;
} UnkStruct_02247260;

typedef struct UnkStruct_022471d4 {
    char unk_00[0x110];
    Vec3 a;
} UnkStruct_022471d4;

typedef struct {
    long a, b, c;
} UnkStruct_0224719c;

typedef struct UnkStruct_022470cc {
    char unk_00[0x110];
    Vec3 a;
    char unk_11C[0x1cc - 0x11c];
    Vec3 b;
    int unk_1D8;
} UnkStruct_022470cc;

struct UnkStruct_02247028 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02247028_2 {
    u8 pad_00[0x110];
    struct UnkStruct_02247028 pos;
};

struct UnkStruct_02246fa4 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02246fa4_2 {
    u8 pad_00[0x110];
    struct UnkStruct_02246fa4 pos;
};

typedef struct UnkStruct_02246ef4 {
    char unk_00[0x110];
    Vec3 a;
    char unk_11C[0x1cc - 0x11c];
    Vec3 b;
} UnkStruct_02246ef4;

typedef struct UnkStruct_02246de8 {
    short unk_00, unk_02, unk_04, unk_06, unk_08, unk_0A, unk_0C;
    unsigned char unk_0E;
} UnkStruct_02246de8;

typedef struct UnkStruct_02246de8_2 {
    short unk_00;
    short unk_02;
    int w0, w1, w2, w3, w4, w5, w6;
} UnkStruct_02246de8_2;

extern void func_0203ad68(void);
extern void func_0203c99c(void *, int);
extern void func_0203caa4(void *, int, int);
extern void *data_021fbee8;
extern void func_0203ad58(void);
extern int func_02095794(int argument0);
extern void *data_020ca158;
extern void func_0203be6c(void *p);
extern void func_01ffcbb0(char *buf, void *p);
extern int func_0203c57c(void *p);
extern int func_0203c568(void *p);
extern int func_0203c548(void *p);
extern void func_0203bd84(void *p, char *buf, int a, int b, int c);
extern int func_020b65c4(void);
extern void *data_021c67a4;
extern int func_0203c0ac(void *obj, int id);
extern void func_0203ab34(void *, int);
extern void func_01ffd070(Vec3 *out, void *a, Vec3 *b);
extern void func_020eaad0(Vec3 *out, Vec3 *in, int n);
extern struct UnkStruct_02247028 data_ov004_0224de64;
extern struct UnkStruct_02246fa4 data_ov004_0224de70;
extern void func_ov004_02246c7c(int arg);
extern void func_ov004_02246b6c(int arg);
extern void func_ov004_02246a84(int arg);
extern void func_0203c97c(void *self, void *p);
extern unsigned char data_ov004_0225696c[];
extern unsigned char data_ov004_022569ac[];

int func_ov004_022473f4(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203caa4(self, 0x11, 0x0);
    func_0203c99c(self, 0x0);
    *(int *) (self + 0x110) = *(int *) ((char *) &data_021fbee8);
    *(int *) (self + 0x114) = *(int *) ((char *) &data_021fbee8 + 0x4);
    *(int *) (self + 0x118) = *(int *) ((char *) &data_021fbee8 + 0x8);
    func_0203ad68();
    return 0x1;
}

int func_ov004_022473a8(char *self)
{
    // DECLS
    int v4;
    // ENDDECLS
    func_0203caa4(self, *(int *) ((char *) &data_020ca158 + 0x10), (int) 0x0);
    func_0203c99c((void *) ((int) (self)), (int) (0x0));
    v4 = func_02095794(0x4);
    *(int *) (self + 0x110) = *(int *) ((char *) v4);
    *(int *) (self + 0x114) = *(int *) ((char *) v4 + 0x4);
    *(int *) (self + 0x118) = *(int *) ((char *) v4 + 0x8);
    func_0203ad58();
    return 0x1;
}

void func_ov004_02247368(void *p)
{
    int stackArg;
    char buf[12];
    int v1, v2;
    func_0203be6c(p);
    func_01ffcbb0(buf, p);
    v1 = func_0203c57c(p);
    v2 = func_0203c568(p);
    stackArg = func_0203c548(p);
    func_0203bd84(p, buf, v1, v2, stackArg);
}

int func_ov004_0224732c(void)
{
    int r = 0;
    switch (func_020b65c4()) {
        case 0x1a:
            r = 0;
            break;
        case 0x1b:
            r = 1;
            break;
        case 0x1c:
            r = 2;
            break;
        case 0x1d:
        case 0x1e:
            r = 3;
            break;
    }
    return r;
}

int func_ov004_0224730c(void)
{
    if (data_021c67a4 != 0) {
        return func_0203c0ac(data_021c67a4, 0xb);
    }
    return 0;
}

int func_ov004_022472ec(void)
{
    if (data_021c67a4 != 0) {
        return func_0203c0ac(data_021c67a4, 0xc);
    }
    return 0;
}

int func_ov004_022472c4(char *self)
{
    func_0203caa4(self, func_ov004_0224732c() + 0x12, 0);
    func_0203c99c(self, 0);
    func_0203ad58();
    return 1;
}

void func_ov004_02247260(UnkStruct_02247260 *self)
{
    Vec3 v[2];

    v[0].x = 0;
    v[0].y = 0;
    v[0].z = 0;
    self->a.x = v[0].x;
    self->a.y = v[0].y;
    self->a.z = v[0].z;
    func_0203be6c((void *) self);
    func_01ffcbb0((char *) (&v[1]), (void *) self);
    func_0203bd84((void *) self, (char *) (&v[1]), func_0203c57c((void *) self), func_0203c568((void *) self), func_0203c548((void *) self));
}

int func_ov004_02247238(char *self)
{
    func_0203caa4(self, func_ov004_0224732c() + 0x16, 0);
    func_0203c99c(self, 0);
    func_0203ad58();
    return 1;
}

void func_ov004_022471d4(UnkStruct_022471d4 *self)
{
    Vec3 v[2];

    v[0].x = 0;
    v[0].y = 0;
    v[0].z = 0;
    self->a.x = v[0].x;
    self->a.y = v[0].y;
    self->a.z = v[0].z;
    func_0203be6c((void *) self);
    func_01ffcbb0((char *) (&v[1]), (void *) self);
    func_0203bd84((void *) self, (char *) (&v[1]), func_0203c57c((void *) self), func_0203c568((void *) self), func_0203c548((void *) self));
}

int func_ov004_0224719c(UnkStruct_0224719c *src)
{
    UnkStruct_0224719c *d;
    if ((*(unsigned char * *) &data_021c67a4) != 0) {
        d = (UnkStruct_0224719c *) ((*(unsigned char * *) &data_021c67a4) + 0x1cc);
        d->a = src->a;
        d->b = src->b;
        d->c = src->c;
        return func_0203c0ac((*(unsigned char * *) &data_021c67a4), 0x10);
    }
    return 0;
}

int func_ov004_0224716c(char *self)
{
    // DECLS
    // ENDDECLS
    func_02095794(0x4);
    func_0203caa4(self, 0x1e, 0x0);
    func_0203c99c(self, 0x0);
    func_0203ad58();
    func_0203ab34(self, 0x2f);
    return 0x1;
}

void func_ov004_022470cc(UnkStruct_022470cc *self)
{
    Vec3 t, u, v;
    int *p;
    int d;
    void *o;

    o = (void *) func_02095794(4);
    func_01ffd070(&t, o, &self->b);
    func_020eaad0(&u, &t, 1);
    self->a.x = u.x;
    self->a.y = u.y;
    self->a.z = u.z;
    d = ((int *) o)[2] - *(int *) ((char *) self + 0x1d4);
    if (d < 0) {
        d = -d;
    }
    p = (int *) ((char *) self + 0x118);
    *p = *p + (d >> 1);
    func_0203be6c((void *) self);
    func_01ffcbb0((char *) (&v), (void *) self);
    func_0203bd84((void *) self, (char *) (&v), func_0203c57c((void *) self), func_0203c568((void *) self), func_0203c548((void *) self));
}

int func_ov004_0224708c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203caa4(self, *(int *) ((char *) &data_020ca158 + (0xc * *(int *) (self + 0x1f0)) + (*(int *) (self + 0x1ec) << 2)),
                  0x0);
    func_0203c99c(self, 0x0);
    func_0203ad58();
    return 0x1;
}

void func_ov004_02247028(struct UnkStruct_02247028_2 *self)
{
    struct UnkStruct_02247028 v;

    self->pos.x = data_ov004_0224de64.x;
    self->pos.y = data_ov004_0224de64.y;
    self->pos.z = data_ov004_0224de64.z;
    func_0203be6c((void *) self);
    func_01ffcbb0((char *) (&v), (void *) self);
    func_0203bd84((void *) self, (char *) (&v), func_0203c57c((void *) self), func_0203c568((void *) self), func_0203c548((void *) self));
}

int func_ov004_02247008(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203caa4(self, 0x1d, 0x0);
    func_0203c99c(self, 0x4);
    func_0203ad58();
    return 0x1;
}

void func_ov004_02246fa4(struct UnkStruct_02246fa4_2 *self)
{
    struct UnkStruct_02246fa4 v;

    self->pos.x = data_ov004_0224de70.x;
    self->pos.y = data_ov004_0224de70.y;
    self->pos.z = data_ov004_0224de70.z;
    func_0203be6c((void *) self);
    func_01ffcbb0((char *) (&v), (void *) self);
    func_0203bd84((void *) self, (char *) (&v), func_0203c57c((void *) self), func_0203c568((void *) self), func_0203c548((void *) self));
}

int func_ov004_02246f90(void)
{
    // DECLS
    // ENDDECLS
    return func_0203c0ac((void *) (*(int *) ((char *) &data_021c67a4)), 0xe);
}

int func_ov004_02246f7c(void)
{
    // DECLS
    // ENDDECLS
    return func_0203c0ac((void *) (*(int *) ((char *) &data_021c67a4)), 0xf);
}

int func_ov004_02246f64(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203caa4(self, 0x20, 0x0);
    func_0203ad68();
    return 0x1;
}

void func_ov004_02246ef4(UnkStruct_02246ef4 *self)
{
    Vec3 v;

    self->a.x = self->b.x;
    self->a.y = self->b.y;
    self->a.z = self->b.z;
    func_0203be6c((void *) self);
    func_01ffcbb0((char *) (&v), (void *) self);
    func_0203bd84((void *) self, (char *) (&v), func_0203c57c((void *) self), func_0203c568((void *) self), func_0203c548((void *) self));
}

int func_ov004_02246ecc(Vec3 *src)
{
    Vec3 *d = (Vec3 *) ((*(char * *) &data_021c67a4) + 0x1cc);
    d->x = src->x;
    d->y = src->y;
    d->z = src->z;
    return func_0203c0ac((void *) ((*(char * *) &data_021c67a4)), 0x14);
}

int func_ov004_02246eb8(void)
{
    // DECLS
    // ENDDECLS
    return func_0203c0ac((void *) (*(int *) ((char *) &data_021c67a4)), 0x12);
}

void func_ov004_02246ea8(void)
{
    func_ov004_02246c7c((*(int *) &data_021c67a4));
}

void func_ov004_02246e98(void)
{
    func_ov004_02246b6c((*(int *) &data_021c67a4));
}

void func_ov004_02246e88(void)
{
    func_ov004_02246a84((*(int *) &data_021c67a4));
}

int func_ov004_02246de8(void *self)
{
    UnkStruct_02246de8 *b;
    UnkStruct_02246de8_2 *g;

    b = (UnkStruct_02246de8 *) ((char *) self + 0x21c);
    b->unk_00 = 0;
    b->unk_02 = -1;
    b->unk_04 = 0;
    b->unk_06 = -1;
    b->unk_08 = -1;
    b->unk_0A = 0;
    b->unk_0C = 0xe;
    b->unk_0E &= ~1;
    b->unk_0E &= ~2;
    g = (UnkStruct_02246de8_2 *) data_ov004_022569ac;
    S16(0xfc) = g->unk_00;
    S16(0xfe) = g->unk_02;
    S32(0x100) = g->w0;
    S32(0x104) = g->w1;
    S32(0x108) = g->w2;
    S32(0x10c) = g->w3;
    S32(0x110) = g->w4;
    S32(0x114) = g->w5;
    S32(0x118) = g->w6;
    func_0203c97c(self, (void *) data_ov004_0225696c);
    func_0203ad58();
    return 1;
}
