/* town_generator: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209c988 @ 0x0209c988, 0xe4 bytes, Thumb
 * func_0209c80c @ 0x0209c80c, 0x17c bytes, Thumb
 * func_0209c618 @ 0x0209c618, 0x1f4 bytes, Thumb
 * func_0209c5b0 @ 0x0209c5b0, 0x68 bytes, Thumb
 * func_0209c5a4 @ 0x0209c5a4, 0xc bytes, Thumb
 * func_0209c574 @ 0x0209c574, 0x30 bytes, Thumb
 */

#include "types.h"

extern int func_0209cb88(void *p, int n);
extern int func_0209ca6c(void *p, int a, int b);
extern int func_0209d030(int v);
extern int func_0209d01c(int v, int n);
extern int func_020644cc(int n);
extern void *func_0209cc30(void *self, u32 a, u32 b);
extern int func_02037bc4(void *p);
extern int func_02037b14(void *p);
extern void *func_0209cc10(void *p);
extern unsigned char *func_0206e7bc(void *p, int n);
extern int data_021dc580;
extern unsigned int data_020e35d4;
extern void *func_0209cfe0(void *);
extern int func_0209cec0(void *, void *);
extern void func_0209ce00(void *, void *);
extern void *func_0209cfb8(void *);

int func_0209c988(void *arg, int p2)
{
    if (func_0209cb88(arg, 0xe) == 0) {
        return 0;
    }
    if (func_0209cb88(arg, 0xd) == 0) {
        return 0;
    }
    if (func_0209cb88(arg, 0xc) == 0) {
        return 0;
    }

    if (p2 == 1) {
        return func_0209ca6c(arg, 0xd, 0xb);
    }
    if (p2 == 2) {
        return func_0209ca6c(arg, 0xe, 0xb);
    }
    if (p2 == 3) {
        return func_0209ca6c(arg, 0xa, 0xb);
    }
    if (p2 == 4) {
        return func_0209ca6c(arg, 0xc, 0xb);
    }

    {
        unsigned int i;
        int count = 0;

        for (i = 1; i < 5; i++) {
            if (func_0209d030((int) func_0209cc30(arg, i, 3)) == 9) {
                count++;
            }
        }

        if (count != 0) {
            int pick = func_020644cc(count);
            int seen = 0;

            for (i = 1; i < 5; i++) {
                if (func_0209d030((int) func_0209cc30(arg, i, 3)) == 9) {
                    if (pick == seen) {
                        func_0209d01c((int) func_0209cc30(arg, i, 3), 0xb);
                        return 1;
                    }
                    seen++;
                }
            }
        }
    }

    return 0;
}

int func_0209c80c(void *self)
{
    int k;
    void *p;
    int sel;
    int count;
    u32 i, j;
    int f;
    unsigned int t1, t2, t3, ok;
    void *x, *y;

    count = 0;
    for (i = 1; i < 5; i++) {
        for (j = 1; j < 5; j++) {
            p = (void *) func_0209d030((int) (func_0209cc30(self, j, i)));
            f = func_02037bc4(p);
            t1 = (f & 8) ? 1 : 0;
            if (t1 != 0) {
                goto no1;
            }
            t2 = (f & 4) ? 1 : 0;
            if (t2 != 0) {
                goto no1;
            }
            t3 = (f & 0x80000) ? 1 : 0;
            if (t3 != 0) {
                goto no1;
            }
            if (func_02037b14(p) != 1) {
                goto no1;
            }
            ok = 1;
            goto have1;
        no1:
            ok = 0;
        have1:
            if (ok != 0) {
                count++;
            }
        }
    }
    if (count == 0) {
        goto done0;
    }
    sel = func_020644cc(count);
    k = 0;
    for (i = 1; i < 5; i++) {
        for (j = 1; j < 5; j++) {
            p = (void *) func_0209d030((int) (func_0209cc30(self, j, i)));
            f = func_02037bc4(p);
            t1 = (f & 8) ? 1 : 0;
            if (t1 != 0) {
                goto no2;
            }
            t2 = (f & 4) ? 1 : 0;
            if (t2 != 0) {
                goto no2;
            }
            t3 = (f & 0x80000) ? 1 : 0;
            if (t3 != 0) {
                goto no2;
            }
            if (func_02037b14(p) != 1) {
                goto no2;
            }
            ok = 1;
            goto have2;
        no2:
            ok = 0;
        have2:
            if (ok != 0) {
                if (sel == k) {
                    x = func_0209cc10((void *) func_0209d030((int) (func_0209cc30(self, j, i))));
                    y = (void *) func_0209d030((int) (func_0209cc30(self, j, i)));
                    if (x != y) {
                        func_0209d01c((int) (func_0209cc30(self, j, i)), (int) x);
                        return 1;
                    }
                }
                k++;
            }
        }
    }
done0:
    return 0;
}

int func_0209c618(void *self)
{
    u32 i;
    u32 n;
    u32 k;
    u32 m;

    func_0209d01c((int) (func_0209cc30(self, 0, 0)), 7);
    func_0209d01c((int) (func_0209cc30(self, 1, 0)), 0);
    func_0209d01c((int) (func_0209cc30(self, 2, 0)), 0);
    func_0209d01c((int) (func_0209cc30(self, 3, 0)), 0);
    func_0209d01c((int) (func_0209cc30(self, 4, 0)), 0);
    func_0209d01c((int) (func_0209cc30(self, 5, 0)), 8);

    func_0209d01c((int) (func_0209cc30(self, 0, 5)), 0x35);
    func_0209d01c((int) (func_0209cc30(self, 1, 5)), 0x35);
    func_0209d01c((int) (func_0209cc30(self, 2, 5)), 0x35);
    func_0209d01c((int) (func_0209cc30(self, 3, 5)), 0x35);
    func_0209d01c((int) (func_0209cc30(self, 4, 5)), 0x35);
    func_0209d01c((int) (func_0209cc30(self, 5, 5)), 0x35);

    func_0209d01c((int) (func_0209cc30(self, 0, 1)), 3);
    func_0209d01c((int) (func_0209cc30(self, 0, 2)), 3);
    func_0209d01c((int) (func_0209cc30(self, 0, 3)), 3);
    func_0209d01c((int) (func_0209cc30(self, 0, 4)), 4);

    func_0209d01c((int) (func_0209cc30(self, 5, 1)), 5);
    func_0209d01c((int) (func_0209cc30(self, 5, 2)), 5);
    func_0209d01c((int) (func_0209cc30(self, 5, 3)), 5);
    func_0209d01c((int) (func_0209cc30(self, 5, 4)), 6);

    for (i = 1; i < 5; i++) {
        if (func_0209d030((int) (func_0209cc30(self, i, 1))) == 0x14) {
            func_0209d01c((int) (func_0209cc30(self, i, 0)), 2);
        }
    }

    n = 0;
    for (i = 2; i <= 3; i++) {
        if ((func_02037b14((void *) ((int) func_0209d030((int) (func_0209cc30(self, i, 1)))))) == 0) {
            n++;
        }
    }

    k = (u32) func_020644cc(n);

    m = 0;
    for (i = 2; i <= 3; i++) {
        if ((func_02037b14((void *) ((int) func_0209d030((int) (func_0209cc30(self, i, 1)))))) == 0) {
            if (m == k) {
                func_0209d01c((int) (func_0209cc30(self, i, 0)), 1);
                func_0209d01c((int) (func_0209cc30(self, i, 1)), 0xa);
                return 1;
            }
            m++;
        }
    }
    return 0;
}

void func_0209c5b0(void *self, int n)
{
    unsigned char *p;
    unsigned int y, x;
    unsigned int one = 1;
    int v;

    if (n < 0) {
        v = func_020644cc(524);
    } else {
        v = (unsigned int) n % 524;
    }
    data_021dc580 = v;
    p = func_0206e7bc((char *) self + 0x120, v);
    if (p != 0) {
        y = 1;
        do {
            x = one;
            do {
                func_0209d01c((int) func_0209cc30(self, x, y), *p++);
                x++;
            } while (x < 5);
            y++;
        } while (y < 5);
    }
}

void func_0209c5a4(unsigned int r0)
{
    data_020e35d4 = r0;
}

void func_0209c574(void *param)
{
    char sp[0x140];
    void *ptr;

    func_0209cfe0(sp);
    ptr = (*(void * *) &data_020e35d4);
    func_0209cec0(sp, ptr);
    func_0209ce00(sp, param);
    func_0209cfb8(sp);
}
