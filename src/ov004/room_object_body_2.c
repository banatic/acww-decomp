/* room_object_body_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220f9c8 @ 0x0220f9c8, 0xe4 bytes, Thumb
 * func_ov004_0220f994 @ 0x0220f994, 0x34 bytes, Thumb
 * func_ov004_0220f8c0 @ 0x0220f8c0, 0xd4 bytes, Thumb
 * func_ov004_0220f7f0 @ 0x0220f7f0, 0xd0 bytes, Thumb
 * func_ov004_0220f7d4 @ 0x0220f7d4, 0x1c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0220f7f0 {
    int data[9];
};

struct UnkStruct_0220f7f0_2 {
    int unk_00;
    int unk_04;
};

extern int func_ov004_0220e5c8(void *self);
extern void func_ov004_0220faac(void *self, Vec3 *v);
extern void func_ov004_0220fefc(void *self, Vec3 *v);
extern void func_ov004_0220dfe8(void *p, void *self);
extern int *func_ov004_0223ce84(void);
extern int func_ov004_0220d4c0(void *p);
extern int func_ov004_0223cd58(int *a, int b);
extern int func_020321bc(void *p, int x, int z, int k, Vec3 *c, int h, Vec3 *b);
extern int func_ov004_0223cd78(int *a, int v);
extern int FX_MulFunc(int a, int b);
extern int func_020b67ac(void);
extern int func_020b6590(void);
extern int func_020b7dc8(int h, void *o, Vec3 *v, int x, int z, int y, int k, int f, int c);
extern int func_02032180(void *);
extern void func_ov004_0220dfe0(void *);
extern int func_02032214(void *p, Vec3 *a, int k, Vec3 *b);
extern int func_020b7e04(int h, void *o);
extern char *func_ov004_0220db94(struct UnkStruct_0220f7f0 *l);
extern void func_ov004_0220f27c(void *self, struct UnkStruct_0220f7f0 *l, int a, int b);
extern struct UnkStruct_0220f7f0_2 *func_ov004_0220db5c(struct UnkStruct_0220f7f0 *l, unsigned int i);
extern unsigned int func_ov004_0220db68(struct UnkStruct_0220f7f0 *l);
extern void func_ov004_0220db90(struct UnkStruct_0220f7f0 *l);
extern u16 *func_0204f5e0(void *g, int a, int b, int c, int d, int e);
extern int func_0204bd08(u16 *p);
extern void func_0204f794(Vec3 *v, int a, int b);
extern int func_ov004_0223c5b8(int a, int b);
extern void *func_020b7d3c(int h, void *o, Vec3 *v, int a, int b, int c, int d);
extern void *data_021c80bc;
extern int data_ov004_02247634[];
extern int func_ov004_0220ccf8(char *self, int v);

void func_ov004_0220f9c8(char *self)
{
    Vec3 a;
    Vec3 b;
    Vec3 c;
    int t;
    int f;
    int idx;

    if (func_ov004_0220e5c8(self) == 0) {
        func_ov004_0220faac(self, &a);
        t = *(int *) (self + 0x15c);
        b.x = t;
        b.y = t;
        b.z = t;
        func_ov004_0220fefc(self, &c);
        if (*(u8 *) (self + 0x78c) == 0) {
            func_ov004_0220dfe8(self + 0x62c, self);
            func_ov004_0223cd58(func_ov004_0223ce84(), func_ov004_0220d4c0(self + 0x17c));
            func_020321bc(self + 0x62c, a.x, a.z, 0x4000, &c, *(short *) (self + 0x8e), &b);
        }
        idx = (u8) func_ov004_0223cd78(func_ov004_0223ce84(), (int) self);
        a.x = FX_MulFunc(a.x, 0xc00);
        a.z = FX_MulFunc(a.z, 0xc00);
        if (func_020b67ac() != 0) {
            f = 0xf;
        } else {
            f = 8;
        }
        func_020b7dc8(func_020b6590(), self + 0x28c, &c, a.x, a.z, a.y, *(short *) (self + 0x8e), f, idx);
    }
}

void func_ov004_0220f994(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov004_0220e5c8(self) == 0x0 && *(u8 *) (self + 0x78c) == 0x0) {
        func_02032180(self + 0x62c);
        func_ov004_0220dfe0(self + 0x62c);
        return;
    }
}

void func_ov004_0220f8c0(char *self)
{
    Vec3 a;
    Vec3 b;
    Vec3 c;
    int flag;
    int t;
    int idx;

    if (func_ov004_0220e5c8(self) == 0) {
        func_ov004_0220faac(self, &a);
        t = *(int *) (self + 0x15c);
        b.x = t;
        b.y = t;
        b.z = t;
        func_ov004_0220fefc(self, &c);
        flag = 0;
        if (*(u8 *) (self + 0x78c) == 0) {
            if (*(u8 *) (self + 0x6c4) != 0) {
                flag = func_02032214(self + 0x62c, &c, *(short *) (self + 0x8e), &b);
            } else {
                flag = 1;
            }
        }
        a.x = FX_MulFunc(a.x, 0xc00);
        a.z = FX_MulFunc(a.z, 0xc00);
        if (flag != 0) {
            idx = (u8) func_ov004_0223cd78(func_ov004_0223ce84(), (int) self);
            if (func_020b67ac() != 0) {
                flag = 0xf;
            } else {
                flag = 8;
            }
            func_020b7dc8(func_020b6590(), self + 0x28c, &c, a.x, a.z, a.y, *(short *) (self + 0x8e), flag, idx);
        } else {
            func_020b7e04(func_020b6590(), self + 0x28c);
        }
    }
}

void func_ov004_0220f7f0(char *self)
{
    void *g;
    struct UnkStruct_0220f7f0 l;
    Vec3 v;
    unsigned int i;
    int a, b, ai, bi;
    u16 *p;

    if (*(u8 *) (self + 0x288) == 0 && *(int *) (self + 0x788) == 1) {
        func_ov004_0220db94(&l);
        func_ov004_0220f27c(self, &l, 0, 0);
        g = data_021c80bc;
        for (i = 0; i < func_ov004_0220db68(&l); i++) {
            a = func_ov004_0220db5c(&l, i)->unk_00;
            b = func_ov004_0220db5c(&l, i)->unk_04;
            ai = a >> 4;
            bi = b >> 4;
            p = func_0204f5e0(g, ai, bi, a - (ai << 4), b - (bi << 4), 1);
            if (p != 0 && func_0204bd08(p) != 0) {
                func_0204f794(&v, a, b);
                v.y = func_ov004_0223c5b8(a, b);
                func_020b7d3c(func_020b6590(), self + 0x1d0 + i * 32, &v, 0xccd, 0x100, 0xa, 0xff);
            }
        }
        func_ov004_0220db90(&l);
    }
}

int func_ov004_0220f7d4(char *self)
{
    return func_ov004_0220ccf8(self, data_ov004_02247634[*(int *) (self + 0x76c)]);
}
