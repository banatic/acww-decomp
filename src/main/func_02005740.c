/* func_02005740 @ 0x02005740, 0x174 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern short FX_SinCosTable_[];
extern UnkStruct_02005740 data_021cfe68;

extern void func_02054f68(Task *t, int k);
extern void func_0205490c(void *a, Task *t);
extern void func_02054ed4(void *a, Task *t, int k);
extern int func_0203f844(Vec *a, Vec *b);
extern int func_0203f758(void);
extern void func_0203f7d0(Vec *d, Vec *s);
extern int func_0200545c(UnkStruct_02005740_3 *o, int v);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_RotX33_(Mtx33 *m, int s, int c);
extern void MTX_Concat33(Mtx33 *d, Mtx33 *a, Mtx33 *b);
extern void func_02005730(Task *t);

#define SIN(i) FX_SinCosTable_[((i) >> 4) << 1]
#define COS(i) FX_SinCosTable_[(((i) >> 4) << 1) + 1]

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
            vac.y = func_0200545c(obj, b7c.p.y);
            vac.z = b7c.p.z;
            func_0203f7d0(&obj->unk_6F4, &vac);
        }
    }
    self->fn = (void *) func_02005730;
    sp2 = (u8 *) self + 0x92;
    *sp2 = 3;
}
