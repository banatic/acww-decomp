/* carried_items: 15 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220d9a4 @ 0x0220d9a4, 0x18 bytes, Thumb
 * func_ov004_0220d9a0 @ 0x0220d9a0, 0x2 bytes, Thumb
 * func_ov004_0220d94c @ 0x0220d94c, 0x54 bytes, Thumb
 * func_ov004_0220d938 @ 0x0220d938, 0x14 bytes, Thumb
 * func_ov004_0220d934 @ 0x0220d934, 0x4 bytes, Thumb
 * func_ov004_0220d930 @ 0x0220d930, 0x4 bytes, Thumb
 * func_ov004_0220d904 @ 0x0220d904, 0x2c bytes, Thumb
 * func_ov004_0220d870 @ 0x0220d870, 0x94 bytes, Thumb
 * func_ov004_0220d840 @ 0x0220d840, 0x30 bytes, Thumb
 * func_ov004_0220d824 @ 0x0220d824, 0x1c bytes, Thumb
 * func_ov004_0220d800 @ 0x0220d800, 0x22 bytes, Thumb
 * func_ov004_0220d7f0 @ 0x0220d7f0, 0x10 bytes, Thumb
 * func_ov004_0220d7cc @ 0x0220d7cc, 0x22 bytes, Thumb
 * func_ov004_0220d788 @ 0x0220d788, 0x42 bytes, Thumb
 * func_ov004_0220d6b8 @ 0x0220d6b8, 0xd0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int m[12];
} Mtx43;

typedef struct {
    char b[16];
} UnkStruct_0220d7f0;

struct UnkStruct_0220d788 {
    u8 pad_00[4];
};

struct UnkStruct_0220d6b8 {
    int data[9];
};

struct UnkStruct_0220d6b8_2 {
    int unk_00;
    int unk_04;
};

extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern Mtx43 data_021fbe48;
extern void func_020e9868(Mtx43 *m, int a, int b, int c);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);
extern void func_ov004_02233b10(int id, Vec3 *a, Vec3 *b, int c, int d, int e);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern char *func_ov004_0220db94(struct UnkStruct_0220d6b8 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220d6b8 *l, int a, int b);
extern struct UnkStruct_0220d6b8_2 *func_ov004_0220db5c(struct UnkStruct_0220d6b8 *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220d6b8 *l);
extern void func_ov004_0220db90(struct UnkStruct_0220d6b8 *l);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern int func_0204bc90(u16 *p);
extern int func_0204bd08(u16 *p);
extern void *data_021c80bc;

void *func_ov004_0220d938(char *self);
void func_ov004_0220d800(char *self);
UnkStruct_0220d7f0 *func_ov004_0220d7f0(char *self, unsigned int i);

void *func_ov004_0220d9a4(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x2) = 0xfff1;
    func_ov004_0220d938((char *) self);
    return self;
}

void func_ov004_0220d9a0(void *object) {}

int func_ov004_0220d94c(u16 *p)
{
    u16 t;
    int x;

    if (func_0204bcdc(p + 1)) {
        t = 0xfff1;
        x = (func_0204bc64(p + 1) == func_0204bc64(&t)) ? 1 : 0;
    } else {
        x = (p[1] == 0xfff1) ? 1 : 0;
    }
    if (x == 0) {
        return 1;
    }
    return 0;
}

void *func_ov004_0220d938(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x2) = 0xfff1;
    *(void **) (self + 0x4) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
    return self;
}

void *func_ov004_0220d934(void *self)
{
    return (char *) self + 0x4;
}

void *func_ov004_0220d930(void *self)
{
    return (char *) self + 0x2;
}

int func_ov004_0220d904(char *self, u16 *b, Vec3 *c)
{
    int r;
    if (func_ov004_0220d94c((u16 *) self) == 0) {
        *(u16 *) (self + 2) = *b;
        *(int *) (self + 4) = c->x;
        *(int *) (self + 8) = c->y;
        *(int *) (self + 0xc) = c->z;
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

void func_ov004_0220d870(void *self, char *b)
{
    Vec3 v;
    Vec3 out;
    Vec3 w;
    Vec3 s;
    int px, py, pz;

    if (func_ov004_0220d94c((u16 *) self) != 0) {
        data_021fbe48 = *(Mtx43 *) (b + 0x59c);
        pz = ((Vec3 *) func_ov004_0220d934(self))->z;
        py = ((Vec3 *) func_ov004_0220d934(self))->y;
        px = ((Vec3 *) func_ov004_0220d934(self))->x;
        func_020e9868(&data_021fbe48, px, py, pz);
        v.x = 0;
        v.y = 0;
        v.z = 0;
        MTX_MultVec43(&v, &data_021fbe48, &out);
        w.x = out.x;
        w.y = out.y;
        w.z = out.z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov004_02233b10(*(u16 *) func_ov004_0220d930(self), &w, &s, 0, 0, 0);
    }
}

void *func_ov004_0220d840(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self + 0x4, 0x4, 0x10, ((void (*)(void *)) func_ov004_0220d9a4), ((void (*)(void *)) func_ov004_0220d9a0));
    func_ov004_0220d800((char *) self);
    return self;
}

void *func_ov004_0220d824(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_cleanup(self + 0x4, 0x4, 0x10, ((void (*)(void *)) func_ov004_0220d9a0));
    return self;
}

void func_ov004_0220d800(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x4; i++) {
        func_ov004_0220d938((char *) ((int) func_ov004_0220d7f0(self, i)));
    }
}

UnkStruct_0220d7f0 *func_ov004_0220d7f0(char *self, unsigned int i)
{
    if (i < 4) {
        return (UnkStruct_0220d7f0 *) (self + 4) + i;
    }
    return (UnkStruct_0220d7f0 *) (self + 4);
}

void func_ov004_0220d7cc(char *self, int a1)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x4; i++) {
        func_ov004_0220d870((void *) ((int) func_ov004_0220d7f0(self, i)), (char *) (a1));
    }
}

int func_ov004_0220d788(struct UnkStruct_0220d788 *self, int a, int b)
{
    u32 i;

    for (i = 0; i < 4; i++) {
        if (!func_ov004_0220d94c((u16 *) ((void *) func_ov004_0220d7f0((char *) self, i)))) {
            func_ov004_0220d904((char *) ((void *) func_ov004_0220d7f0((char *) self, i)), (u16 *) a, (Vec3 *) b);
            return 1;
        }
    }
    return 0;
}

int func_ov004_0220d6b8(void *unused, char *self)
{
    int u;
    int v;
    u16 tmp;
    struct UnkStruct_0220d6b8 l;
    void *g;
    unsigned int i;
    int sentinel;
    int a, b, ai, bi, ok;
    u16 *p;

    func_ov004_0220db94(&l);
    func_ov004_0220f27c(self, &l, 0, 0);
    g = data_021c80bc;
    u = 0;
    sentinel = 0xfff1;
    v = 0;
    for (i = 0; i < func_ov004_0220db68(&l); i++) {
        b = func_ov004_0220db5c(&l, i)->unk_04;
        a = func_ov004_0220db5c(&l, i)->unk_00;
        ai = a >> 4;
        bi = b >> 4;
        p = func_0204f5e0(g, ai, bi, a - (ai << 4), b - (bi << 4), 1);
        if (p != 0 && func_0204bc90(p) == 0 && func_0204bd08(p) == 0) {
            if (func_0204bcdc(p) != 0) {
                tmp = (u16) sentinel;
                ok = (func_0204bc64(p) == func_0204bc64(&tmp)) ? 1 : u;
            } else {
                ok = (*p == (u16) sentinel) ? 1 : v;
            }
            if (ok == 0) {
                func_ov004_0220db90(&l);
                return 0;
            }
        }
    }
    func_ov004_0220db90(&l);
    return 1;
}
