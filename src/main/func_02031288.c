/* func_02031288 @ 0x02031288, 0x1f0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

// The Vec3 copies of *a1 and *a2 share one 24-byte struct, which keeps their stack order.

typedef struct {
    int x, y, z;
} UnkStruct_02031288;

typedef struct UnkStruct_02031288_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    u8 pad_0C[0x24 - 0xc];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02031288_2;

typedef struct UnkStruct_02031288_3 {
    u8 pad_00[0x34];
    int unk_34;
    u8 pad_38[0x40 - 0x38];
} UnkStruct_02031288_3;

typedef struct Obj48 {
    void *vt;
    UnkStruct_02031288_2 *a0;
    UnkStruct_02031288 *pp;
    int qx, qy, qz;
    u16 h;
    u8 pad_1A[0x1c - 0x1a];
    int unk_1C;
    int unk_20;
    int unk_24;
} Obj48;

extern int data_021c31a0;
extern u8 data_020da1e8;

extern void func_02031e28(UnkStruct_02031288 *a, UnkStruct_02031288 *b);
extern void func_02031e08(UnkStruct_02031288 *a, UnkStruct_02031288 *b);
extern void VEC_Add(UnkStruct_02031288 *a, UnkStruct_02031288 *b, UnkStruct_02031288 *c);
extern void VEC_Subtract(UnkStruct_02031288 *a, UnkStruct_02031288 *b, UnkStruct_02031288 *c);
extern void func_02031e74(Obj48 *o);
extern void func_02032c8c(UnkStruct_02031288_2 *s);
extern void func_02030ebc(UnkStruct_02031288 *a, UnkStruct_02031288 *b, Obj48 *o, int f, int z, int g);
extern int func_02031bb8(UnkStruct_02031288 *p);
extern void func_02034270(UnkStruct_02031288_3 *w, UnkStruct_02031288 *p, int a, int b);
extern int func_020341c8(UnkStruct_02031288_3 *w, int k);
extern int func_02034184(UnkStruct_02031288_3 *w, int k);
extern void func_0203423c(UnkStruct_02031288_3 *w);
extern void func_02032aec(UnkStruct_02031288_2 *s, int a);
extern void func_020eaca0(UnkStruct_02031288 *d, UnkStruct_02031288 *a, UnkStruct_02031288 *b);
extern void func_02032610(UnkStruct_02031288 *p, int a, int b);
extern void func_02031e68(Obj48 *o);

void func_02031288(UnkStruct_02031288_2 *self, UnkStruct_02031288 *a1, UnkStruct_02031288 *a2, int a3, int a5, int a6, int a7)
{
    struct {
        UnkStruct_02031288 p;
        UnkStruct_02031288 q;
    } t;
    UnkStruct_02031288 sc;
    UnkStruct_02031288 m1;
    UnkStruct_02031288 m2;
    Obj48 ob;
    UnkStruct_02031288_3 w;
    UnkStruct_02031288 out;
    int lim;
    int d;
    int f1;
    int f2;
    int f3;

    t.p.x = a1->x;
    t.p.y = a1->y;
    t.p.z = a1->z;
    t.q.x = a2->x;
    t.q.y = a2->y;
    t.q.z = a2->z;
    lim = (data_021c31a0 + a5) << 1;
    d = t.p.x - a2->x;
    if (d < 0) {
        d = -d;
    }
    if (lim + d > 0xc000) {
        goto reset;
    }
    d = t.p.z - a2->z;
    if (d < 0) {
        d = -d;
    }
    if (lim + d > 0xc000) {
    reset:
        t.q.x = t.p.x;
        t.q.y = t.p.y;
        t.q.z = t.p.z;
    }
    sc.x = a5;
    sc.y = a5;
    sc.z = a5;
    m1.x = t.q.x;
    m1.y = t.q.y;
    m1.z = t.q.z;
    m2.x = t.q.x;
    m2.y = t.q.y;
    m2.z = t.q.z;
    func_02031e28(&m1, &t.p);
    func_02031e08(&m2, &t.p);
    VEC_Add(&m1, &sc, &m1);
    VEC_Subtract(&m2, &sc, &m2);
    func_02031e74(&ob);
    ob.vt = &data_020da1e8;
    ob.a0 = self;
    ob.pp = &t.p;
    ob.qx = t.q.x;
    ob.qy = t.q.y;
    ob.qz = t.q.z;
    ob.h = (u16) a3;
    ob.unk_1C = a5;
    ob.unk_20 = a6;
    ob.unk_24 = a7;
    func_02032c8c(self);
    if (self->unk_00 & 2) {
        f1 = 1;
    } else {
        f1 = 0;
    }
    func_02030ebc(&m2, &m1, &ob, a7, 0, f1);
    if (a7 & 4) {
        if (func_02031bb8(&t.p)) {
            t.p.x = a2->x;
            t.p.y = a2->y;
            t.p.z = a2->z;
        }
    }
    if (a7 & 1) {
        if (self->unk_00 & 2) {
            f2 = 1;
        } else {
            f2 = 0;
        }
        if (a7 & 0x80) {
            f3 = 1;
        } else {
            f3 = 0;
        }
        func_02034270(&w, &t.p, f2, f3);
        if (t.p.y < func_020341c8(&w, 0) + 0x200) {
            self->unk_04 = self->unk_04 | 1;
            self->unk_08 = w.unk_34;
            t.p.y = func_020341c8(&w, 0) + 0x200;
        }
        if (func_02034184(&w, t.p.y) != 0) {
            self->unk_04 = self->unk_04 | 2;
        }
        func_0203423c(&w);
    }
    func_02032aec(self, a3);
    func_020eaca0(&out, &t.p, a1);
    self->unk_24 = out.x;
    self->unk_28 = out.y;
    self->unk_2C = out.z;
    if (a7 & 8) {
        a1->x = t.p.x;
        a1->y = t.p.y;
        a1->z = t.p.z;
    }
    if (a6 != 0) {
        func_02032610(&t.p, a5, a6);
    }
    ob.vt = &data_020da1e8;
    func_02031e68(&ob);
}
