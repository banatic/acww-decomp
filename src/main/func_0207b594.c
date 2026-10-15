/* func_0207b594 @ 0x0207b594, 0x1d0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021d12b4[];
extern u8 data_021d1248[];
extern u8 data_020cd454[];

extern void *func_020984e8(void);
extern int func_0207b3dc(char *);
extern void MI_CpuFill8(void *, u8, unsigned int);
extern int func_0209bcd4(int *, int);
extern void *func_0208150c(char *);
extern int func_02003704(void *);
extern int func_0207f150(char *);
extern int func_0207b810(char *, char *, void *);
extern int func_0209bd10(int);
extern void *func_0207f1c8(char *);
extern void *func_0209b5ec(void *);
extern int func_0209c380(void *);
extern int func_0209c304(void *);
extern void *func_0207f270(char *);
extern void *func_020794d0(void *);
extern u8 func_0209c330(void *);
extern void func_0209bd30(void *, u8, u16 *, u8);
extern int func_020644cc(int);

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
        if (func_02003704(func_0208150c(p)) == 0) {
            goto mark;
        }
        if (func_0207f150(p) != 3) {
            goto mark;
        }
        if (i == excl) {
            goto mark;
        }
        t = func_0207b810(self, p, ctx);
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
        d = func_020794d0(func_0207f270(q));
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
                    d = func_020794d0(func_0207f270(self + j * 0x7ec));
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
