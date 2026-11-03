/* session_link_5: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02075104 @ 0x02075104, 0x13c bytes, Thumb
 * func_020750fc @ 0x020750fc, 0x8 bytes, Thumb
 * func_020750f4 @ 0x020750f4, 0x8 bytes, Thumb
 * func_02075050 @ 0x02075050, 0xa4 bytes, Thumb
 * func_0207500c @ 0x0207500c, 0x44 bytes, Thumb
 * func_02074fec @ 0x02074fec, 0x20 bytes, Thumb
 * func_02074fa0 @ 0x02074fa0, 0x4c bytes, Thumb
 * func_02074f28 @ 0x02074f28, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02075050 UnkStruct_02075050;

extern void *data_020ccf94;
extern void func_020792a0(void);
extern int func_0208602c(void);
extern void func_02086130(void *);
extern void func_02053010(void);
extern void func_0209d3e4(void);
extern void func_020b316c(void);
extern void func_0203f4c4(void);
extern void func_02070778(void);
extern int func_02073918(void *, int);
extern int func_0204bbd4(unsigned int);
extern void func_020b23ec(int, int);
extern void func_02051e38(int);
extern void func_0209d57c(u8, int);
extern void func_02096204(unsigned int);
extern void func_020ae4f0(void);
extern void func_020731a4(void *, int);
extern unsigned int OS_DisableInterrupts(void);
extern unsigned int OS_EnableInterrupts(void);
extern void DC_FlushAll(void);
extern int func_02077b20(char *p);
extern void func_02073cf0(UnkStruct_02075050 *g, int a, int t);
extern int func_02077b28(char *p);
extern int func_02077b14(char *p);
extern void func_02075240(char *payload, unsigned int length, int player, int index);
extern int func_02073928(UnkStruct_02075050 *g, int a);
extern void func_02073bac(UnkStruct_02075050 *g, int a, int b, unsigned int c);
extern void func_0207399c(UnkStruct_02075050 *g, int a);
extern int func_02073c04(UnkStruct_02075050 *g, int a, int b);
extern unsigned int func_02073044(void);
extern int func_020ec338(unsigned short a, int b, int c);
extern int func_02073364(void *ptr);
extern int func_02073dd4(void *p, int i);
extern int func_02073d28(void *p, int i);
extern int func_02073c90(void *p, int i);
extern void func_02077b50(int a, int b);
extern int func_020738b4(int, int);
extern int func_020738bc(int, int);
extern int func_0207762c(int);
extern void MI_CpuCopy8(int, char *, int);

void func_02075104(int mode)
{
    void *p;
    unsigned int i;
    unsigned int j;
    unsigned int k;
    int n;
    int h;
    u8 b;

    if (mode == 4) {
        func_020792a0();
        func_02086130((void *) func_0208602c());
    }
    func_02053010();
    func_0209d3e4();
    func_020b316c();
    func_0203f4c4();
    func_02070778();
    if (mode < 0) {
        p = data_020ccf94;
        if (func_02073918(p, 0) || func_02073918(p, 4)) {
            if (mode == -4) {
                for (i = 0; i < 0x22; i++) {
                    h = func_0204bbd4(i);
                    func_020b23ec(h, 1);
                    func_020b23ec(h, 2);
                    func_020b23ec(h, 3);
                }
                func_02051e38(1);
                func_02051e38(2);
                func_02051e38(3);
                for (j = 0; j < 0x33; j++) {
                    b = (u8) j;
                    func_0209d57c(b, 1);
                    func_0209d57c(b, 2);
                    func_0209d57c(b, 3);
                }
            } else {
                n = -mode;
                for (i = 0; i < 0x22; i++) {
                    func_020b23ec(func_0204bbd4(i), n);
                }
                func_02051e38(n);
                for (j = 0; j < 0x33; j++) {
                    func_0209d57c((u8) j, n);
                }
            }
        }
    }
    if (mode < 0) {
        if (mode == -4) {
            for (k = 0; k < 4; k++) {
                func_02096204(k);
            }
        } else {
            func_02096204(-mode);
        }
    }
    if (mode == -4) {
        func_020ae4f0();
    }
    if ((mode < 0 ? -mode : mode) < 4) {
        if (mode < 0) {
            mode = -mode;
        }
        func_020731a4(data_020ccf94, mode);
    }
}

void func_020750fc(void)
{
    OS_DisableInterrupts();
}

void func_020750f4(void)
{
    OS_EnableInterrupts();
}

void func_02075050(int a, char *p, unsigned int n)
{
    int t;
    UnkStruct_02075050 *g;
    int q;
    int v;

    DC_FlushAll();
    t = func_02077b20(p);
    if (t != 0) {
        func_02073cf0((*(UnkStruct_02075050 * *) &data_020ccf94), a, t);
    }
    if (func_02077b28(p) != 0) {
        v = func_02077b14(p);
        if (v < 0x18) {
            func_02075240(p + 1, n - 1, a, v);
        }
    } else {
        func_020731a4((void *) ((*(UnkStruct_02075050 * *) &data_020ccf94)), a);
        if (n > 1) {
            g = (*(UnkStruct_02075050 * *) &data_020ccf94);
            func_02073bac(g, a, func_02073928(g, a), n);
            func_0207399c(g, a);
            q = func_02073c04(g, a, func_02073928(g, a));
            func_02073044();
            func_020ec338((unsigned short) a, q, 0x1000);
        }
    }
}

int func_0207500c(int a, int b)
{
    int diff;

    if (b < 0) {
        return 0;
    }
    if (a < 0) {
        return 1;
    }

    diff = a - b;
    if (diff == 0) {
        goto ret1;
    }
    if (diff > 0x3fff) {
        diff -= 0x7fff;
    } else if (diff < -0x3fff) {
        diff = 0x7fff - diff;
    }
    if (diff <= 0) {
        goto ret1;
    }
    return 0;

ret1:
    return 1;
}

int func_02074fec(int a)
{
    return func_0207500c(a, func_02073364(data_020ccf94));
}

void func_02074fa0(void)
{
    int i = 3;
    void *base = data_020ccf94;
    for (; i >= 0; i--) {
        if (func_02073dd4(base, i) != 0) {
            if (func_02073918(base, i) == 0) {
                func_02077b50(func_02073d28(base, i), func_02073c90(base, i));
            }
        }
    }
}

int func_02074f28(char *param0, int param1, int param2)
{
    if (param1 == 0) {
        int result = 0;
        int i = 0x45;
        int gValue = (*(int *) &data_020ccf94);
        char ch;
        int tmp;
        int len;
        do {
            if (func_020738b4(gValue, i) != 0) {
                ch = (char) i;
                MI_CpuCopy8((int) &ch, param0, 1);
                param0++;
                result++;
                tmp = func_020738bc(gValue, i);
                len = func_0207762c(i);
                MI_CpuCopy8(tmp, param0, len);
                param0 += len;
                result += len;
            }
        } while (--i >= 0);
        *param0 = 0x46;
        return result + 1;
    } else {
        MI_CpuCopy8(param1, param0, param2);
        return param2;
    }
}
