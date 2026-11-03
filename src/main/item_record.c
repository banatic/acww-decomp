/* item_record: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203cfa4 @ 0x0203cfa4, 0x2 bytes, Thumb
 * func_0203cfa0 @ 0x0203cfa0, 0x2 bytes, Thumb
 * func_0203cf40 @ 0x0203cf40, 0x60 bytes, Thumb
 * func_0203cf38 @ 0x0203cf38, 0x8 bytes, Thumb
 * func_0203cdf8 @ 0x0203cdf8, 0x140 bytes, Thumb
 * func_0203cdcc @ 0x0203cdcc, 0x2c bytes, Thumb
 * func_0203cd2c @ 0x0203cd2c, 0xa0 bytes, Thumb
 * func_0203cd1c @ 0x0203cd1c, 0x10 bytes, Thumb
 * func_0203cc54 @ 0x0203cc54, 0xc6 bytes, Thumb
 * func_0203cc38 @ 0x0203cc38, 0x1c bytes, Thumb
 * func_0203cc1c @ 0x0203cc1c, 0x1c bytes, Thumb
 * func_0203cc18 @ 0x0203cc18, 0x4 bytes, Thumb
 * func_0203cc14 @ 0x0203cc14, 0x4 bytes, Thumb
 * func_0203cc04 @ 0x0203cc04, 0x10 bytes, Thumb
 * func_0203cbf4 @ 0x0203cbf4, 0x10 bytes, Thumb
 * func_0203cbd0 @ 0x0203cbd0, 0x22 bytes, Thumb
 */

#include "types.h"

extern void func_02061b1c(unsigned short *, int, int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern int func_0204bd5c(unsigned short *);
extern void *func_020984e8(void);
extern int func_0204bd08(unsigned short *v);
extern int func_0204c2b4(unsigned short *v);
extern int func_020996ac(void *p);
extern int func_0204bc50(int a, int b);

int func_0203cc18(void);
int func_0203cc14(void);
int func_0203cc04(void);
int func_0203cbf4(void);

void func_0203cfa4(void *object) {}

void func_0203cfa0(void *object) {}

void func_0203cf40(unsigned char *p)
{
    unsigned int i;
    for (i = 0; i < 0x100; i++) {
        p[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        (p + i)[0x100] = 0;
    }
    for (i = 0; i < 9; i++) {
        (p + i)[0x109] = 0;
    }
    for (i = 0; i < 9; i++) {
        (p + i)[0x112] = 0;
    }
    for (i = 0; i < 8; i++) {
        (p + i)[0x11b] = 0;
    }
}

void func_0203cf38(unsigned char *argument0)
{
    func_0203cf40((unsigned char *) argument0);
}

char *func_0203cdf8(int base, unsigned char *out, int code)
{
    unsigned short h;

    func_02061b1c(&h, code, 1);
    if (func_0204bcdc(&h)) {
        int val;
        val = func_0204bc64(&h);
        *out = (unsigned char) (1 << (val & 7));
        return (char *) (base + (val >> 3));
    } else {
        int cond1;
        int delta;

        cond1 = (h >= 0x1100 && h <= 0x1143);
        if (cond1) {
            delta = (h >= 0x1100 && h <= 0x1143) ? h - 0x1100 : -1;
            *out = (unsigned char) (1 << (delta & 7));
            return (char *) (base + 0x100 + (delta >> 3));
        } else if (h >= 0x1144 && h <= 0x1187) {
            delta = (h >= 0x1144 && h <= 0x1187) ? h - 0x1144 : -1;
            *out = (unsigned char) (1 << (delta & 7));
            return (char *) (base + 0x109 + (delta >> 3));
        } else if (h >= 0x1323 && h <= 0x1368) {
            delta = (h >= 0x1323 && h <= 0x1368) ? h - 0x1323 : -1;
            *out = (unsigned char) (1 << (delta & 7));
            return (char *) (base + 0x112 + (delta >> 3));
        } else if (h >= 0x1000 && h <= 0x10ff) {
            int val;
            val = func_0204bd5c(&h);
            *out = (unsigned char) (1 << (val & 7));
            return (char *) (base + 0x11b + (val >> 3));
        } else {
            *out = 0;
            return 0;
        }
    }
}

int func_0203cdcc(int param1, int param2)
{
    unsigned char c;
    unsigned char *p;

    p = (unsigned char *) func_0203cdf8(param1, &c, param2);
    if (p != 0) {
        if (*p & c) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

int func_0203cd2c(int a, u16 *p, int mode, int set)
{
    u8 mask;
    u8 *slot;

    if (mode == 0) {
        unsigned int ok = 0;
        u16 v = *p;
        if (v >= 0x12e8 && v <= 0x131f) {
            ok = 1;
        }
        if (ok || (v >= 0x12b0 && v <= 0x12e7) || (v >= 0x4384 && v <= 0x4463) || (v >= 0x42a4 && v <= 0x4383)) {
            return 0;
        }
    }
    slot = (u8 *) func_0203cdf8(a, (unsigned char *) (&mask), (int) p);
    if (slot != 0) {
        if (set != 0) {
            *slot |= mask;
        } else {
            *slot &= ~mask;
        }
        return 1;
    }
    return 0;
}

int func_0203cd1c(int object, unsigned short *item, int mode)
{
    return func_0203cd2c(object, (u16 *) item, mode, 1);
}

int func_0203cc54(int a, int n)
{
    void *p = func_020984e8();
    unsigned int cnt = 0;
    unsigned short v[6];

    v[0] = (unsigned short) a;
    if (p == 0) {
        return cnt;
    }

    if (func_0204bd08(v)) {
        unsigned int i;

        for (i = 0; i < n; i++) {
            v[1] = (unsigned short) (a + i);
            func_02061b1c(&v[4], (int) (&v[1]), 1);
            v[1] = v[4];
            if (func_0204c2b4(&v[1])) {
                if (func_0203cdcc(func_020996ac(p), (int) (&v[1]))) {
                    cnt++;
                }
            }
        }
        return cnt;
    } else {
        int zero;
        int base;
        unsigned int i;

        if (func_0204bcdc(v)) {
            v[2] = (unsigned short) a;
            base = func_0204bc64(&v[2]);
            zero = 0;
            for (i = 0; i < n; i++) {
                v[3] = (unsigned short) func_0204bc50(base + (int) i, zero);
                if (func_0204c2b4(&v[3])) {
                    if (func_0203cdcc(func_020996ac(p), (int) (&v[3]))) {
                        cnt++;
                    }
                }
            }
        }
        return cnt;
    }
}

int func_0203cc38(void)
{
    int a = func_0203cc04();
    int b = func_0203cc18();
    if (a == b) {
        return 1;
    } else {
        return 0;
    }
}

int func_0203cc1c(void)
{
    int a;
    int b;
    int result;

    a = func_0203cbf4();
    b = func_0203cc14();
    if (a == b) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0203cc18(void)
{
    return 56;
}

int func_0203cc14(void)
{
    return 56;
}

int func_0203cc04(void)
{
    return func_0203cc54(4840, 56);
}

int func_0203cbf4(void)
{
    return func_0203cc54(0x12b0, 0x38);
}

int func_0203cbd0(int param)
{
    int result = (int) func_020984e8();
    if (result != 0) {
        return func_0203cd1c(func_020996ac((void *) result), (unsigned short *) param, 1);
    } else {
        return 0;
    }
}
