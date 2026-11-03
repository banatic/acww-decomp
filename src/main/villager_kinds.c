/* villager_kinds: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207b810 @ 0x0207b810, 0x5c bytes, Thumb
 * func_0207b78c @ 0x0207b78c, 0x84 bytes, Thumb
 * func_0207b764 @ 0x0207b764, 0x26 bytes, Thumb
 * func_0207b594 @ 0x0207b594, 0x1d0 bytes, Thumb
 * func_0207b57c @ 0x0207b57c, 0x18 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0207b764 {
    char data[0x2c];
};

extern void *func_0207f270(void *key);
extern void *func_020984e8(void);
extern unsigned int func_0207b86c(void *a, void *key, void *data);
extern void *func_020794d0(void *p);
extern int func_0209bd44(void *x);
extern int func_0209bc40(void *x);
extern int data_020ccf94;
extern int func_02073d90(int);
extern int func_0207cad4(void *);
extern int func_0208150c(void *);
extern int func_02003704(int);
extern int func_0209bd10(unsigned int object);
extern struct UnkStruct_0207b764 *func_02079350(void);
extern void func_0209bd5c(void *);
extern u8 data_021d12b4[];
extern u8 data_021d1248[];
extern u8 data_020cd454[];
extern int func_0207b3dc(char *);
extern void MI_CpuFill8(void *, u8, unsigned int);
extern int func_0209bcd4(int *, int);
extern int func_0207f150(char *);
extern void *func_0207f1c8(char *);
extern void *func_0209b5ec(void *);
extern int func_0209c380(void *);
extern int func_0209c304(void *);
extern u8 func_0209c330(void *);
extern void func_0209bd30(void *, u8, u16 *, u8);
extern int func_020644cc(int);

int func_0207b810(void *a, void *key, void *data)
{
    void *p;
    int result;
    unsigned int r;

    p = func_0207f270(key);
    result = 22;
    if (data == 0) {
        data = func_020984e8();
    }
    if (p != 0 && data != 0) {
        r = func_0207b86c(a, key, data);
        if (r < 22) {
            result = r;
        } else {
            if (func_0209bd44(func_020794d0(p)) != 0) {
                result = func_0209bc40(func_020794d0(p));
            }
        }
    }
    return result;
}

int func_0207b78c(void *param)
{
    int forwarded_value;

    int result;
    int count5;
    int count4;
    int i;
    int v8;
    void *p;

    if (func_02073d90(data_020ccf94) != 0) {
        return 0;
    }

    p = param;
    result = func_0207cad4(p);
    count5 = 0;
    count4 = 0;
    i = 0;
    v8 = 0;

    do {
        if (func_02003704(func_0208150c(p)) != 0) {
            if ((forwarded_value = (int) func_0207b810(param, p, (void *) v8)) == 0x16) {
                count5++;
            } else if (func_0209bd10((unsigned int) forwarded_value) != 1) {
                count4++;
            }
        }
        p = (char *) p + 0x7ec;
        i++;
    } while (i < 8);

    if (result < count4) {
        goto ret0;
    }
    if (((result - count4) >> 1) >= count5) {
        goto ret0;
    }
    return 1;

ret0:
    return 0;
}

void func_0207b764(void)
{
    struct UnkStruct_0207b764 *p;
    int i;

    p = func_02079350();
    for (i = 0; i < 8; i++) {
        func_0209bd5c((void *) (int) func_020794d0((void *) p));
        p++;
    }
}

void func_0207b594(char *self)
{
    void *ctx;
    int excl;
    char *p;
    char *q;
    u8 *e;
    int t;
    void *v;
    void *d;
    u16 w0;
    u16 w1;
    int a;
    int i;
    int j;
    int k;
    int n5;
    int n4;
    int r;
    int r2;
    u8 *g;

    ctx = func_020984e8();
    n5 = 0x11;
    n4 = 8;
    if (ctx == 0) {
        return;
    }
    a = 0;
    excl = func_0207b3dc(self);
    MI_CpuFill8(data_021d12b4, 0, n5);
    MI_CpuFill8(data_021d1248, 0, n4);
    for (i = 0; i < 0xd; i++) {
        if (func_0209bcd4(&a, data_020cd454[i]) != 0) {
            data_021d12b4[a] = 1;
            n5--;
        }
    }
    for (i = 0; i < 8; i++) {
        p = self + i * 0x7ec;
        if (func_02003704((int) ((void *) func_0208150c((void *) p))) == 0) {
            goto mark;
        }
        if (func_0207f150(p) != 3) {
            goto mark;
        }
        if (i == excl) {
            goto mark;
        }
        t = func_0207b810((void *) self, (void *) p, ctx);
        if ((unsigned int) t >= 0x16) {
            continue;
        }
        if (func_0209bd10(t) != 1) {
            continue;
        }
        if (func_0209bcd4(&a, t) == 0) {
            continue;
        }
        data_021d1248[i] = 1;
        n4--;
        data_021d12b4[a] = 1;
        n5--;
        continue;
    mark:
        data_021d1248[i] = 1;
        n4--;
    }
    for (i = 0; i < 8; i++) {
        e = &data_021d1248[i];
        if (data_021d1248[i] != 0) {
            continue;
        }
        q = self + i * 0x7ec;
        v = (func_0209b5ec((void *) func_0207f1c8(q)));
        if (func_0209c380(v) == 0) {
            continue;
        }
        if (func_0209c304(v) != 0) {
            continue;
        }
        d = func_020794d0(func_0207f270((void *) q));
        w0 = 0xfff1;
        func_0209bd30(d, func_0209c330(v), &w0, 0);
        *e = 1;
        n4--;
    }
    while (n4 > 0 && n5 > 0) {
        r = func_020644cc(n4);
        for (j = 0; j < 8; j++) {
            if (data_021d1248[j] == 0) {
                if (r == 0) {
                    d = func_020794d0(func_0207f270((void *) (self + j * 0x7ec)));
                    r2 = func_020644cc(n5);
                    for (k = 0; k < 0x11; k++) {
                        g = &data_021d12b4[k];
                        if (data_021d12b4[k] == 0) {
                            if (r2 == 0) {
                                w1 = 0xfff1;
                                func_0209bd30(d, (u8) (k + 5), &w1, 0);
                                *g = 1;
                                n5--;
                                break;
                            }
                            r2--;
                        }
                    }
                    data_021d1248[j] = 1;
                    n4--;
                    break;
                }
                r--;
            }
        }
    }
}

void func_0207b57c(int r0)
{
    int r4;
    int result;

    r4 = r0;
    result = func_0207b78c((void *) r0);
    if (result != 0) {
        func_0207b594((char *) r4);
    }
}
