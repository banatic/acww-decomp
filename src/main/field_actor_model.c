/* field_actor_model: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020058b4 @ 0x020058b4, 0x30 bytes, Thumb
 * func_02005740 @ 0x02005740, 0x174 bytes, Thumb
 * func_02005730 @ 0x02005730, 0x10 bytes, Thumb
 * func_0200570c @ 0x0200570c, 0x24 bytes, Thumb
 * func_02005490 @ 0x02005490, 0x27c bytes, Thumb
 * func_0200545c @ 0x0200545c, 0x34 bytes, Thumb
 */

#include "types.h"

#define SIN(i) FX_SinCosTable_[((i) >> 4) << 1]
#define COS(i) FX_SinCosTable_[(((i) >> 4) << 1) + 1]

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    int m[9];
} Mtx33;

typedef struct {
    u8 pad_00[0x24];
    Vec p;
} UnkStruct_02005740;

typedef struct UnkStruct_02005740_2 {
    u8 pad_00[0x28];
    Mtx33 unk_28;
    Vec unk_4C;
} UnkStruct_02005740_2;

typedef struct UnkStruct_02005740_3 {
    u8 pad_00[0x234];
    u8 sub234[0x45c - 0x234];
    short unk_45C;
    short unk_45E;
    u8 pad_460[0x6f4 - 0x460];
    Vec unk_6F4;
    u8 pad_700[4];
    int unk_704;
} UnkStruct_02005740_3;

typedef struct Hdr {
    u8 unk_00;
    u8 unk_01;
} Hdr;

typedef struct UnkStruct_02005740_4 {
    u8 pad_00[0x2c];
    UnkStruct_02005740_3 *unk_2C;
} UnkStruct_02005740_4;

typedef struct Task {
    Hdr *h;
    UnkStruct_02005740_4 *c;
    u8 pad_08[0x24 - 8];
    void *fn;
    u8 pad_28[0x92 - 0x28];
    u8 state;
    u8 pad_93[0xb4 - 0x93];
    UnkStruct_02005740_2 *p;
} Task;

typedef struct {
    u8 pad_00[0x24];
    Vec p;
} UnkStruct_02005490;

extern void func_02054988(void *param1, void *param2);
extern short FX_SinCosTable_[];
extern UnkStruct_02005740 data_021cfe68;
extern void func_02054f68(Task *t, int k);
extern void func_0205490c(void *a, Task *t);
extern void func_02054ed4(void *a, Task *t, int k);
extern int func_0203f844(Vec *a, Vec *b);
extern int func_0203f758(void);
extern int func_0203f7d0(Vec *d, Vec *s);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_RotX33_(Mtx33 *m, int s, int c);
extern void MTX_Concat33(Mtx33 *d, Mtx33 *a, Mtx33 *b);
extern void func_02055d38(UnkStruct_02005490 *d, u8 k);
extern void func_02054848(UnkStruct_02005490 *d, int n);
extern int func_02055d0c(UnkStruct_02005490 *d, UnkStruct_02005490 *s, int n);
extern void func_02055e7c(UnkStruct_02005490 *d, int n);
extern int func_0205e138(UnkStruct_02005490 *d, int n);
extern int func_0205ddd4(UnkStruct_02005490 *d);
extern void func_020acbc8(Vec *d, int n);
extern int func_0200f290(u8 *self, int n);
extern void func_0205e954(UnkStruct_02005490 *d, UnkStruct_02005490 *s);
extern int func_0200fbe0(u8 *self);
extern void func_0205e8f8(UnkStruct_02005490 *d, UnkStruct_02005490 *s, int n);
extern unsigned char data_020e54a8;
extern int func_020310c8(int);

void func_02005740(Task *self);
void func_02005730(void *arg0);
int func_0200545c(int p0, int p1);

void func_020058b4(void *param1)
{
    void *r4 = param1;
    void *r0 = *(void **) ((char *) r4 + 4);
    void *r1 = *(void **) ((char *) r0 + 0x2c);
    if (r1 != 0) {
        func_02054988((char *) r1 + 0x234, r4);
    }
    *(void **) ((char *) r4 + 0x24) = (void *) (void (*)(void *)) func_02005740;
    *(unsigned char *) ((char *) r4 + 0x92) = 2;
}

void func_02005740(Task *self)
{
    Mtx33 m4;
    Mtx33 m28;
    Vec v4c;
    Mtx33 m58;
    UnkStruct_02005740 b7c;
    Vec vac;
    Vec vb8;
    UnkStruct_02005740_3 *obj;
    Mtx33 *dst;
    Mtx33 *q;
    UnkStruct_02005740_2 *p;
    Vec *w;
    u8 *sp2;
    int v;
    int r;

    func_02054f68(self, 0);
    obj = self->c->unk_2C;
    if (self->h->unk_01 == 0xf && obj != 0) {
        v = obj->unk_45C;
        if (v != 0 || obj->unk_45E != 0) {
            dst = &self->p->unk_28;
            MTX_RotY33_(&m28, SIN((u16) v), COS((u16) v));
            MTX_Concat33(dst, &m28, dst);
            MTX_RotX33_(&m4, SIN((u16) obj->unk_45E), COS((u16) obj->unk_45E));
            MTX_Concat33(dst, &m4, dst);
        }
    }
    obj = self->c->unk_2C;
    if (obj != 0) {
        func_0205490c(obj->sub234, self);
        if (self->h->unk_01 == 0) {
            if (obj->unk_704 == 0x82 || obj->unk_704 == 0x83) {
                p = self->p;
                q = (Mtx33 *) p;
                q = (Mtx33 *) ((u8 *) q + 0x28);
                w = &p->unk_4C;
                v4c.x = p->unk_4C.x;
                v4c.y = w->y;
                v4c.z = w->z;
                vb8.x = p->unk_4C.x;
                vb8.y = w->y;
                vb8.z = w->z;
                r = func_0203f844(&v4c, &vb8);
                w->z = v4c.z;
                w->y = v4c.y - func_0203f758();
                if (r != 0) {
                    MTX_RotX33_(&m58, SIN((u16) r), COS((u16) r));
                    MTX_Concat33(q, &m58, q);
                }
            }
            func_02054ed4(obj->sub234, self, 0);
            b7c = data_021cfe68;
            vac.x = b7c.p.x;
            vac.y = func_0200545c((int) obj, b7c.p.y);
            vac.z = b7c.p.z;
            func_0203f7d0(&obj->unk_6F4, &vac);
        }
    }
    self->fn = (void *) (void (*)(Task *)) func_02005730;
    sp2 = (u8 *) self + 0x92;
    *sp2 = 3;
}

void func_02005730(void *arg0)
{
    unsigned char *ptr;

    *(unsigned int *) ((char *) arg0 + 0x24) = (unsigned int) func_020058b4;
    ptr = (unsigned char *) arg0 + 0x92;
    *ptr = 1;
}

// placeholder, not used directly
void func_0200570c(unsigned int *arg0)
{
    unsigned int *puVar1;
    unsigned int val;
    unsigned int *puVar3;

    puVar1 = (unsigned int *) (arg0 + 0x17);
    val = *puVar1;
    *(unsigned int *) ((unsigned char *) arg0 + 0x6f4) = val;
    val = *(puVar1 + 1);
    *(unsigned int *) ((unsigned char *) arg0 + 0x6f8) = val;
    val = *(puVar1 + 2);
    *(unsigned int *) ((unsigned char *) arg0 + 0x6fc) = val;
    return;
}

void func_02005490(u8 *self)
{
    UnkStruct_02005490 buf;
    Vec v;
    Vec w;
    Vec slot;
    UnkStruct_02005490 m1;
    UnkStruct_02005490 m2;
    int mode;

    (*(UnkStruct_02005490 *) &data_021cfe68) = *(UnkStruct_02005490 *) (self + 0x298);
    func_02055d38((UnkStruct_02005490 *) (self + 0x234), self[0x8e9]);
    func_02054848((UnkStruct_02005490 *) (self + 0x234), 0);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), (UnkStruct_02005490 *) (self + 0x42c), 0xf);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), (UnkStruct_02005490 *) (self + 0x668), 0xe);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), (UnkStruct_02005490 *) (self + 0x698), 0xb);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 7);
    v.x = buf.p.x;
    v.y = buf.p.y;
    v.z = buf.p.z;
    func_0203f7d0((Vec *) (self + 0x6c8), &v);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 4);
    v.x = buf.p.x;
    v.y = buf.p.y;
    v.z = buf.p.z;
    func_0203f7d0((Vec *) (self + 0x6d4), &v);
    func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 0x10);
    v.x = buf.p.x;
    v.y = buf.p.y;
    v.z = buf.p.z;
    func_0203f7d0((Vec *) (self + 0x6e0), &v);
    *(UnkStruct_02005490 *) (self + 0x3f0) = *(UnkStruct_02005490 *) (self + 0x42c);
    func_02055d38((UnkStruct_02005490 *) (self + 0x38c), self[0x8e9]);
    func_02055e7c((UnkStruct_02005490 *) (self + 0x38c), 0);
    if (func_0205e138((UnkStruct_02005490 *) (self + 0x428), 1) < 0x9e) {
        *(UnkStruct_02005490 *) (self + 0x4c8) = *(UnkStruct_02005490 *) (self + 0x42c);
        func_02055d38((UnkStruct_02005490 *) (self + 0x464), self[0x8e9]);
        func_02055e7c((UnkStruct_02005490 *) (self + 0x464), 0);
    }
    if (func_0205ddd4((UnkStruct_02005490 *) (self + 0x59c)) != 0x4b) {
        *(UnkStruct_02005490 *) (self + 0x564) = *(UnkStruct_02005490 *) (self + 0x42c);
        func_02055d38((UnkStruct_02005490 *) (self + 0x500), self[0x8e9]);
        func_02055e7c((UnkStruct_02005490 *) (self + 0x500), 0);
    }
    if (*(int *) (self + 0x6f0) > 0) {
        func_02055d0c((UnkStruct_02005490 *) (self + 0x234), &buf, 1);
        w.x = buf.p.x;
        w.y = buf.p.y;
        w.z = buf.p.z;
        func_0203f7d0(&slot, &w);
        func_020acbc8(&slot, *(int *) (self + 0x6f0));
    }
    if (func_0200f290(self, 0) != 0) {
        func_0205e954((UnkStruct_02005490 *) (self + 0x5a0), (UnkStruct_02005490 *) (self + 0x668));
        switch (func_0200fbe0(self)) {
            case 4:
            case 10:
                mode = 2;
                break;
            case 1:
            case 5:
            case 9:
                mode = 1;
                break;
            default:
                mode = 0;
                break;
        }
        func_0205e8f8(&m1, (UnkStruct_02005490 *) (self + 0x5a0), mode);
        *(UnkStruct_02005490 *) (self + 0x608) = m1;
        if (func_0200fbe0(self) == 4) {
            func_0205e8f8(&m2, (UnkStruct_02005490 *) (self + 0x5a0), 3);
            *(UnkStruct_02005490 *) (self + 0x638) = m2;
        }
    }
}

int func_0200545c(int p0, int p1)
{
    int flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        goto ret1;
    }
    if (func_0200f290((u8 *) p0, 3) != 0) {
        goto call2;
    }
ret1:
    return p1;
call2:
    return func_020310c8(0);
}
