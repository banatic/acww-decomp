/* town_generator_2: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209d048 @ 0x0209d048, 0x20 bytes, Thumb
 * func_0209d03c @ 0x0209d03c, 0xa bytes, Thumb
 * func_0209d038 @ 0x0209d038, 0x2 bytes, Thumb
 * func_0209d034 @ 0x0209d034, 0x4 bytes, Thumb
 * func_0209d030 @ 0x0209d030, 0x4 bytes, Thumb
 * func_0209d02c @ 0x0209d02c, 0x4 bytes, Thumb
 * func_0209d01c @ 0x0209d01c, 0xe bytes, Thumb
 * func_0209d014 @ 0x0209d014, 0x8 bytes, Thumb
 * func_0209cfe0 @ 0x0209cfe0, 0x34 bytes, Thumb
 * func_0209cfb8 @ 0x0209cfb8, 0x28 bytes, Thumb
 * func_0209cf80 @ 0x0209cf80, 0x38 bytes, Thumb
 * func_0209cf70 @ 0x0209cf70, 0x10 bytes, Thumb
 * func_0209cec0 @ 0x0209cec0, 0xb0 bytes, Thumb
 * func_0209ce34 @ 0x0209ce34, 0x8c bytes, Thumb
 * func_0209ce00 @ 0x0209ce00, 0x34 bytes, Thumb
 * func_0209ccd4 @ 0x0209ccd4, 0x12c bytes, Thumb
 * func_0209cc84 @ 0x0209cc84, 0x50 bytes, Thumb
 * func_0209cc30 @ 0x0209cc30, 0x54 bytes, Thumb
 * func_0209cc10 @ 0x0209cc10, 0x20 bytes, Thumb
 * func_0209cb88 @ 0x0209cb88, 0x88 bytes, Thumb
 */

#include "types.h"

extern unsigned char data_020d1ac0[];
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_0206e8c4(void *ptr);
extern int func_0206e8b4(void *ptr);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern char data_020e35ec[];
extern int func_0206e890(void *p1, char *p2, int p3, int p4);
extern void func_0206e854(void *p);
extern void func_0206e808(int a);
extern void func_0209c5b0(void *self, int val);
extern int func_0209c618(void *self);
extern int func_0209c80c(void *self);
extern int func_0209c988(void *self, int arg);
extern void MI_CpuFill8(void *, int, int);
extern int func_02064328(int *, int, int, int);
extern int func_0206487c(int *);
extern int data_020e35d8;
extern int func_02037c0c(u32 a);
extern int func_020644cc(u32 a);
extern unsigned int data_021dc584;
extern unsigned char data_021dc58c;
extern unsigned char data_021dc594;
extern void __register_global_object(void *, void *, void *);
extern int func_02037bc4(int);
extern int func_02037bec(int);

int func_0209ce34(void *self);
int func_0209ccd4(int param);
int func_0209cc84(int arg);
unsigned char *func_0209cc30(unsigned char *base, unsigned int a1, unsigned int a2);

int func_0209d048(int val)
{
    int *p = (int *) data_020d1ac0;
    unsigned int i = 0;
    while (i < 6) {
        if (*p == val) {
            return 1;
        }
        p++;
        i++;
    }
    return 0;
}

void func_0209d03c(int *p)
{
    p[0] = 0x36;
    p[1] = 0;
}

void func_0209d038(void *object) {}

int func_0209d034(int *p0)
{
    return p0[1];
}

int func_0209d030(int *p0)
{
    return p0[0];
}

void func_0209d02c(int *p0, int p1)
{
    p0[1] = p1;
}

int func_0209d01c(int *r0, int r1)
{
    if (r1 < 0x37) {
        *r0 = r1;
        return 1;
    }
    return 0;
}

void *func_0209d014(unsigned char *p, int i)
{
    return (p) + i * 6;
}

void *func_0209cfe0(void *ptr)
{
    __cxa_vec_ctor((void *) (ptr), 0x24, 8, (void (*)(void *))(void (*)(void *)) func_0209d03c,
                   (void (*)(void *)) func_0209d038);
    func_0206e8c4((char *) ptr + 0x120);
    return ptr;
}

void *func_0209cfb8(void *obj)
{
    func_0206e8b4((char *) obj + 0x120);
    __cxa_vec_cleanup((void *) (obj), 0x24, 8, (void (*)(void *)) func_0209d038);
    return obj;
}

int func_0209cf80(void *param)
{
    if (func_0206e890((char *) param + 0x120, data_020e35ec, 0x10, 0x20c)) {
        func_0206e854((char *) param + 0x120);
        return 1;
    } else {
        return 0;
    }
}

void func_0209cf70(int a)
{
    func_0206e808(a + 0x120);
}

int func_0209cec0(void *self, int arg2)
{
    int r4;
    int r6;
    int r7;

    r4 = 0;
    func_0209cf80(self);
    r7 = ~r4;
    goto outer_test;

outer_body:
    func_0209c5b0(self, r7);
    r4 = (func_0209c618(self) & 1) ? 1 : 0;
    r4 = (r4 & func_0209c80c(self)) ? 1 : 0;
    r4 = (r4 & func_0209c988(self, arg2)) ? 1 : 0;
    if (r4 == 0) {
        goto outer_test;
    }

    r6 = 0;
    goto inner_test;

inner_body:
    r6 = (func_0209ccd4((int) self) & 1) ? 1 : 0;
    r6 = (r6 & func_0209cc84((int) self)) ? 1 : 0;
    if ((unsigned int) func_0209ce34(self) > 0x1ffb8u) {
        r4 = 0;
    }

inner_test:
    if (r6 == 0) {
        goto inner_body;
    }

outer_test:
    if (r4 == 0) {
        goto outer_body;
    }

    func_0209cf70((int) self);
    return 1;
}

int func_0209ce34(void *self)
{
    int sum;
    volatile int addend;
    unsigned int outer;
    unsigned int inner;
    unsigned char tmp[30];
    unsigned char buf[0x86];

    MI_CpuFill8(buf, 0, 0x86);
    sum = 0;
    outer = 0;
    addend = sum;
    for (; outer < 6; outer++) {
        for (inner = 0; inner < 6; inner++) {
            if (buf[func_0209d034((int *) func_0209cc30((unsigned char *) self, inner, outer))] == 0) {
                {
                    int v = func_0209d034((int *) func_0209cc30((unsigned char *) self, inner, outer));
                    func_02064328((int *) tmp, (int) &data_020e35d8, v >> 4, v);
                    sum += addend + func_0206487c((int *) tmp);
                }
                buf[func_0209d034((int *) func_0209cc30((unsigned char *) self, inner, outer))] = 1;
            }
        }
    }
    return sum;
}

void func_0209ce00(int arg0, unsigned char *out)
{
    unsigned int i, j;
    unsigned int start = 0;
    for (i = 0; i < 6; i++) {
        for (j = start; j < 6; j++) {
            *out++ = (unsigned char) func_0209d034((int *) ((int) func_0209cc30((unsigned char *) arg0, (int) j, (int) i)));
        }
    }
}

int func_0209ccd4(int param)
{
    int ret = 1;
    u32 sp8 = 0;
    u32 spc;
    u32 sp10;
    u32 sp14 = 0;
    u32 sp18 = 0;
    u32 sp1c = 0;
    u32 sp20 = 0;
    u32 sp24 = 0;
    u32 sp28 = 0;
    u32 sp2c = 0;
    int sp30 = 0;
    unsigned char sp34[0x86];
    u32 r6;
    int r7;
    u32 r5, r4;
    void *res;

    MI_CpuFill8(sp34, 0, 0x86);

    for (sp8 = 0; sp8 < 6; sp8++) {
        for (r6 = sp14; r6 < 6; r6++) {
            r7 = func_0209d030((int *) (void *) func_0209cc30((unsigned char *) param, r6, sp8));

            r5 = sp18;
            r4 = r5;
            do {
                if (r7 == func_02037c0c(r4) && sp34[r4] == 0) {
                    r5++;
                }
                r4++;
            } while (r4 < 0x86);

            if (r5 != 0) {
                spc = func_020644cc(r5);
                r4 = sp1c;
                r5 = r4;
                while (r5 < 0x86) {
                    if (r7 == func_02037c0c(r5) && sp34[r5] == 0) {
                        if (r4 == spc) {
                            goto found1;
                        }
                        r4++;
                    }
                    r5++;
                }
                r5 = sp20;
            found1:
                res = (void *) func_0209cc30((unsigned char *) param, r6, sp8);
                func_0209d02c((int *) res, r5);
                sp34[r5] = 1;
            } else {
                r5 = sp24;
                r4 = r5;
                do {
                    if (r7 == func_02037c0c(r4)) {
                        r5++;
                    }
                    r4++;
                } while (r4 < 0x86);

                if (r5 != 0) {
                    sp10 = func_020644cc(r5);
                    r4 = sp28;
                    r5 = r4;
                    while (r5 < 0x86) {
                        if (r7 == func_02037c0c(r5)) {
                            if (r4 == sp10) {
                                goto found2;
                            }
                            r4++;
                        }
                        r5++;
                    }
                    r5 = sp2c;
                found2:
                    res = (void *) func_0209cc30((unsigned char *) param, r6, sp8);
                    func_0209d02c((int *) res, r5);
                    sp34[r5] = 1;
                } else {
                    ret = sp30;
                    res = (void *) func_0209cc30((unsigned char *) param, r6, sp8);
                    func_0209d02c((int *) res, 0x14);
                }
            }
        }
    }
    return ret;
}

int func_0209cc84(int arg)
{
    unsigned int i, j, k;
    unsigned int base = 1;
    for (i = base; i < 5; i++) {
        for (j = base; j < 5; j++) {
            for (k = 0; k < 6; k++) {
                if (((int *) data_020d1ac0)[k] == func_0209d034((int *) (int) func_0209cc30((unsigned char *) arg, j, i))) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

unsigned char *func_0209cc30(unsigned char *base, unsigned int a1, unsigned int a2)
{
    unsigned int ret;

    ret = (unsigned int) func_0209d014((unsigned char *) a1, a2);
    if (ret < 0x24) {
        return base + (ret << 3);
    }
    if ((data_021dc584 & 1) == 0) {
        func_0209d03c((int *) (&data_021dc58c));
        __register_global_object((void *) (&data_021dc58c), (((void *) func_0209d038)), (void *) (&data_021dc594));
        data_021dc584 |= 1;
    }
    return &data_021dc58c;
}

int func_0209cc10(int a)
{
    int result = func_02037bec(func_02037bc4(a) | 0x100);
    if (result == 0x36) {
        result = a;
    }
    return result;
}

int func_0209cb88(int p1, int p2)
{
    unsigned int count = 0;
    unsigned int outer1, outer2;
    unsigned int inner1, inner2;
    unsigned int one = 1;
    unsigned int one2 = 1;
    unsigned int result, counter;

    outer1 = 1;
    do {
        inner1 = one;
        do {
            if (func_0209d030((int *) (int) func_0209cc30((unsigned char *) p1, inner1, outer1)) == 9) {
                count++;
            }
            inner1++;
        } while (inner1 < 5);
        outer1++;
    } while (outer1 < 5);

    result = func_020644cc(count);

    counter = 0;
    outer2 = 1;
    while (outer2 < 5) {
        inner2 = one2;
        while (inner2 < 5) {
            if (func_0209d030((int *) (int) func_0209cc30((unsigned char *) p1, inner2, outer2)) == 9) {
                if (result == counter) {
                    func_0209d01c((int *) ((int) func_0209cc30((unsigned char *) p1, inner2, outer2)), p2);
                    return 1;
                } else {
                    counter++;
                }
            }
            inner2++;
        }
        outer2++;
    }
    return 0;
}
