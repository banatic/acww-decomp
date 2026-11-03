/* field_actor_place_states_9: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222bbd4 @ 0x0222bbd4, 0x10 bytes, Thumb
 * func_ov004_0222bb0c @ 0x0222bb0c, 0xc8 bytes, Thumb
 * func_ov004_0222bb08 @ 0x0222bb08, 0x2 bytes, Thumb
 * func_ov004_0222bacc @ 0x0222bacc, 0x3c bytes, Thumb
 * func_ov004_0222ba44 @ 0x0222ba44, 0x88 bytes, Thumb
 * func_ov004_0222ba24 @ 0x0222ba24, 0x20 bytes, Thumb
 * func_ov004_0222ba1c @ 0x0222ba1c, 0x6 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

struct Pair {
    u8 a;
    u8 b;
};

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int, int);
extern int func_02073908(void *, int);
extern void func_02051e20(Vec3 *);
extern void *data_020ccf94;
extern void func_02010d88(void *self, int *t, int a, int b);
extern void func_02089fc8(void *p);
extern int func_02051e18(void);
extern int func_02008258(void *self, int a);
extern int func_ov004_0222bdf0(void *self, int a, int b, int c);
extern int func_ov004_0222b9d4(void *self, int a, int b, int arg, short v);
extern void func_02010f5c(int);
extern void func_02010d64(int);

void *func_ov004_0222bbd4(char *self, char *a1, int a2)
{
    // DECLS
    // ENDDECLS
    *(int *) (self) = *(int *) (a1);
    *(int *) (self + 0x4) = *(int *) (a1 + 0x4);
    *(int *) (self + 0x8) = *(int *) (a1 + 0x8);
    *(u8 *) (self + 0xc) = a2;
    return self;
}

void func_ov004_0222bb0c(char *self, char *e, int previous)
{
    char *s;
    int cd[2];
    int t;
    Vec3 a;
    Vec3 b;
    int f;
    int ang;
    int m;
    int r;
    int j;
    f = *(unsigned char *) (e + 0xc);
    ang = *(short *) (self + 0x8e);
    s = self + 0x7d4;
    {
        char *o = self + 0x5c;
        a.x = *(int *) (self + 0x5c);
        a.y = *(int *) (o + 4);
        a.z = *(int *) (o + 8);
    }
    m = 0x2000;
    {
        int neg = 0;
        neg = ~neg;
        if (f == 0) {
            m = neg * m;
        }
    }
    j = ((int) (unsigned short) ang >> 4) * 2;
    cd[0] = FX_SinCosTable_[j];
    cd[1] = FX_SinCosTable_[j + 1];
    r = FX_MulFunc(cd[1], 0x1000);
    r = r - FX_MulFunc(cd[0], m);
    t = FX_MulFunc(cd[0], 0x1000);
    t = t + FX_MulFunc(cd[1], m);
    {
        char *o = self + 0x5c;
        a.x = *(int *) o + t;
        a.z = *(int *) (o + 8) + r;
    }
    b.x = a.x;
    b.y = a.y;
    b.z = a.z;
    func_ov004_0222bbd4((char *) s, (char *) (&b), f);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_02051e20(&a);
    }
}

void func_ov004_0222bb08(void *callbackObject, int event) {}

void func_ov004_0222bacc(void *self)
{
    int t[4];
    int *p;

    p = (int *) ((char *) self + 0x7d4);
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_02010d88(self, t, 0x1000, 0x1000);
    func_02089fc8((char *) self + 0x1c4);
}

void func_ov004_0222ba44(char *self)
{
    unsigned char *q;

    switch (func_02051e18()) {
        case 0:
            return;
        case 1:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            break;
        case 2:
            *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
            func_ov004_0222bdf0(self, 0, 6, -1);
            return;
    }
    q = (unsigned char *) (self + 0x7d4);
    if (*(unsigned char *) (self + 0x200) != 0) {
        func_ov004_0222bdf0(self, 0, 6, -1);
    } else {
        func_ov004_0222b9d4(self, q[0xc], 0, 6, -1);
    }
}

void func_ov004_0222ba24(int arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
    func_ov004_0222ba44((char *) arg);
    func_ov004_0222bacc((void *) arg);
}

void func_ov004_0222ba1c(struct Pair *p, u8 a, u8 b)
{
    p->a = a;
    p->b = b;
}
