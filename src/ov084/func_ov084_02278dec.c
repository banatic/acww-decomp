/* func_ov084_02278dec @ 0x02278dec, 0x174 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 a, b, c, d;
    int e;
    int g;
} UnkStruct_02278dec;
typedef struct {
    void *fn;
    u8 st;
} UnkStruct_02278dec_2;

extern char data_ov084_02279558;
extern char data_ov084_02279568;

extern void func_020984e8(void);
extern void func_02099640(void);
extern int func_02099e9c(u16 *p);
extern int func_0202ea80(int a, int b);
extern int func_020a13d0(void);
extern void func_02095764(UnkStruct_02278dec *s, int a);
extern void *func_0208602c(void);
extern int func_02086108(void *g, int a);
extern void func_020860f0(void *g, int a);
extern int func_020644cc(int a);
extern void func_0209e474(int *p);
extern int func_0209de44(int a, int b, int c, int d);

void func_ov084_02278dec(char *self, UnkStruct_02278dec_2 *out)
{
    UnkStruct_02278dec s;
    int r;
    int f;
    u16 a0, a1;
    void *q;

    func_020984e8();
    func_02099640();
    out->fn = &data_ov084_02279558;

    if (*(int *) (self + 0xb4) == -1) {
        s.b = 0x37e0;
        *(int *) (self + 0xb4) = func_02099e9c(&s.b);
        if (*(int *) (self + 0xb4) >= 0) {
            out->fn = &data_ov084_02279568;
            out->st = 0;
            return;
        }
    }

    if (func_0202ea80(0x1e, 1) != 0) {
        func_02095764(&s, func_020a13d0());
        s.c = 0x137e;
        r = func_02099e9c(&s.c);
        f = 0;
        if (r == -1) {
            f = 1;
        }
        if (f == 0) {
            s.d = 0x137f;
            r = func_02099e9c(&s.d);
            f = 0;
            if (r == -1) {
                f = 1;
            }
            if (f == 0) {
                goto ok;
            }
        }
        f = 0;
        a0 = *(volatile u16 *) &s.a;
        a1 = *(volatile u16 *) &s.a;
        if (a1 >= 0x137e && a0 <= 0x137f) {
            f = 1;
        }
        if (f == 0) {
            out->st = 6;
            return;
        }
    ok:
        if (func_02086108(func_0208602c(), 3) == 0) {
            out->st = 7;
            return;
        }
        out->st = (u8) (func_020644cc(4) + 0xd);
        return;
    }

    if (func_02086108(func_0208602c(), 2) != 0) {
        return;
    }
    func_020860f0(func_0208602c(), 2);
    q = *(void **) (self + 0xb0);
    if (*((u8 *) q + 0x714) == 1) {
        out->st = 0;
        return;
    }
    s.e = 0;
    s.g = 0;
    func_0209e474(&s.e);
    r = func_0209de44(((u8 *) &s)[0xd], ((u8 *) &s)[0xc], 6, 5);
    if (r == -1) {
        q = *(void **) (self + 0xb0);
        if (*((u8 *) q + 0x714) <= 3) {
            out->st = 1;
        } else {
            out->st = 2;
        }
    } else {
        q = *(void **) (self + 0xb0);
        if (*((u8 *) q + 0x714) <= 4) {
            out->st = 1;
        } else {
            out->st = 2;
        }
    }
}
