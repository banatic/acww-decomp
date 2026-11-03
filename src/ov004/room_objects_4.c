/* room_objects_4: 10 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223c510 @ 0x0223c510, 0x58 bytes, Thumb
 * func_ov004_0223c4b8 @ 0x0223c4b8, 0x58 bytes, Thumb
 * func_ov004_0223c430 @ 0x0223c430, 0x88 bytes, Thumb
 * func_ov004_0223c40c @ 0x0223c40c, 0x24 bytes, Thumb
 * func_ov004_0223c3b8 @ 0x0223c3b8, 0x54 bytes, Thumb
 * func_ov004_0223c364 @ 0x0223c364, 0x54 bytes, Thumb
 * func_ov004_0223c310 @ 0x0223c310, 0x54 bytes, Thumb
 * func_ov004_0223c2b4 @ 0x0223c2b4, 0x5c bytes, Thumb
 * func_ov004_0223c264 @ 0x0223c264, 0x50 bytes, Thumb
 * func_ov004_0223c1ec @ 0x0223c1ec, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct {
    long a, b, c;
} UnkStruct_0223c510;

typedef struct {
    long a, b, c;
} UnkStruct_0223c4b8;

typedef int (*PF)(void *);

typedef int (*Pred)(void *);

extern unsigned long data_ov004_022595cc;
extern UnkStruct_0223c510 data_ov004_0225964c;
extern int data_ov004_02259640;
extern void func_020012dc(void *object);
extern void __register_global_object(void *, void *destructor, void *);
extern int func_ov004_0223c568(void *, int, UnkStruct_0223c510 *);
extern unsigned long data_ov004_022595c8;
extern UnkStruct_0223c4b8 data_ov004_02259664;
extern int data_ov004_02259658;
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern int func_ov004_0223c5a4(int *v);
extern int func_ov004_0220fe24(void *self, int a1, int a2, int a3, int a4);
extern int func_02030890(int *v);
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cbe8(void *, void *, int);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *, unsigned);
extern unsigned func_ov004_0223c130(void);
extern int func_ov004_0220e5b8(void *arg0);
extern int func_ov004_0220d2b8(void *);
extern int func_02052738(void *, int, int, int);
extern void func_ov004_0220d280(void *p, int a, void *arg);
extern int func_020644cc(int);

int func_ov004_0223c510(void *p0, int p1)
{
    if (!(data_ov004_022595cc & 1)) {
        data_ov004_0225964c.a = 0x2000;
        data_ov004_0225964c.b = 0;
        data_ov004_0225964c.c = 0;
        __register_global_object(&data_ov004_0225964c, ((void *) &func_020012dc), &data_ov004_02259640);
        data_ov004_022595cc |= 1;
    }
    return func_ov004_0223c568(p0, p1, &data_ov004_0225964c);
}

int func_ov004_0223c4b8(void *p0, int p1)
{
    if (!(data_ov004_022595c8 & 1)) {
        data_ov004_02259664.a = 0xffffe000;
        data_ov004_02259664.b = 0;
        data_ov004_02259664.c = 0;
        __register_global_object(&data_ov004_02259664, ((void *) &func_020012dc), &data_ov004_02259658);
        data_ov004_022595c8 |= 1;
    }
    return func_ov004_0223c568(p0, p1, (UnkStruct_0223c510 *) (&data_ov004_02259664));
}

int func_ov004_0223c430(int *self, int ang, int scale)
{
    int yval;
    int xplus;
    int zplus;
    int i2;
    int v[3];

    i2 = ((u16) ang >> 4) << 1;
    zplus = self[2] + FX_MulFunc(scale, FX_SinCosTable_[i2 + 1]);
    yval = self[1];
    xplus = self[0] + FX_MulFunc(scale, FX_SinCosTable_[i2]);
    v[0] = xplus;
    v[1] = yval;
    v[2] = zplus;

    if (func_ov004_0223c5a4(v) != 0) {
        return 0;
    }

    if (func_ov004_0220fe24(v, 0x800, 0x2000, 0x800, 0) == 0) {
        return 1;
    }

    if (func_02030890(v) == -1) {
        goto ret2;
    }
    return 0;
ret2:
    return 2;
}

int func_ov004_0223c40c(void *a, int b)
{
    int r;
    if (func_ov004_0223c430((int *) a, (short) ((short) b), 0x2000) == 2) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

int func_ov004_0223c3b8(void *self, int a)
{
    void *e = func_ov004_0223cbe8(func_ov004_0223cd50(), self, 0);
    if (e != 0 && *(long *) ((char *) e + 0x780) != 0x26) {
        return 0;
    }
    if (func_ov004_0223c430((int *) self, (short) ((short) (a + 0x4000)), 0x2000) == 2) {
        return 1;
    }
    return 0;
}

int func_ov004_0223c364(void *self, int a)
{
    void *e = func_ov004_0223cbe8(func_ov004_0223cd50(), self, 0);
    if (e != 0 && *(long *) ((char *) e + 0x780) != 0x26) {
        return 0;
    }
    if (func_ov004_0223c430((int *) self, (short) ((short) (a + 0xc000)), 0x2000) == 2) {
        return 1;
    }
    return 0;
}

int func_ov004_0223c310(void)
{
    unsigned i = 0;
    int z = 0;
    void *e;
    for (i = 0; i < func_ov004_0223c130(); i++) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
        if (e == 0) {
            continue;
        }
        if (func_ov004_0220e5b8((void *) e) == 0) {
            continue;
        }
        if (func_ov004_0220d2b8((char *) e + 0x740) == 0) {
            continue;
        }
        func_02052738(e, z, 0xff, 1);
    }
    return 1;
}

void func_ov004_0223c2b4(int a, int (*fn)(void *), void *arg)
{
    unsigned int i;
    void *e;

    for (i = 0; i < func_ov004_0223c130(); i++) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
        if (e == 0) {
            continue;
        }
        if (fn != 0) {
            if (fn == 0) {
                continue;
            }
            if (fn(e) == 0) {
                continue;
            }
        }
        if (a == func_ov004_0220d2b8((char *) e + 0x740)) {
            continue;
        }
        func_ov004_0220d280((char *) e + 0x740, a, arg);
    }
}

// fn is tested twice; the second test is redundant in the original as well.
int func_ov004_0223c264(PF fn)
{
    unsigned n = 0, i;
    void *e;
    for (i = 0; i < func_ov004_0223c130(); i++) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
        if (e == 0) {
            continue;
        }
        if (fn == 0 || (fn != 0 && fn(e) != 0 && func_ov004_0220d2b8((char *) e + 0x740) != 0)) {
            n++;
        }
    }
    return n;
}

char *func_ov004_0223c1ec(Pred pred, int v)
{
    int cnt = func_ov004_0223c264((Pred) pred);
    if (cnt != 0) {
        int pick = func_020644cc(cnt);
        int n = 0;
        unsigned int i;
        for (i = 0; i < func_ov004_0223c130(); i++) {
            char *o = (char *) func_ov004_0223cd58(func_ov004_0223ce84(), i);
            if (o != 0) {
                if (pred == 0 || (pred != 0 && pred(o) != 0)) {
                    if (func_ov004_0220d2b8(o + 0x740) != 0) {
                        if (n == pick) {
                            func_ov004_0220d280(o + 0x740, 0, (void *) v);
                            return o;
                        }
                        n++;
                    }
                }
            }
        }
    }
    return 0;
}
