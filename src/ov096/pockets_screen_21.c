/* pockets_screen_21: 6 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_022a1424 @ 0x022a1424, 0x8 bytes, Thumb
 * func_ov096_022a13f0 @ 0x022a13f0, 0x34 bytes, Thumb
 * func_ov096_022a13b4 @ 0x022a13b4, 0x3c bytes, Thumb
 * func_ov096_022a1394 @ 0x022a1394, 0x1e bytes, Thumb
 * func_ov096_022a1384 @ 0x022a1384, 0x10 bytes, Thumb
 * func_ov096_022a128c @ 0x022a128c, 0xf8 bytes, Thumb
 */

#include "types.h"

extern void func_ov096_0229f83c(void *unused0);
extern void func_ov094_0229a084(void *);
extern void func_ov094_0229af20(void *);
extern void func_ov094_0229bbc0(void *);
extern void func_ov096_0229c3c4(char *p);
extern void func_ov002_022091cc(char *p);
extern void func_ov094_0229a05c(char *p);
extern int func_ov002_02207d5c(char *p);
extern void func_ov096_0229eb98(char *p);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern int func_ov094_0229a098(void *receiver);
extern int func_ov002_02208054(void *self, int a);
extern void func_ov096_0229fbbc(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov096_0229f75c(void *self, int a, int b, int c);
extern void func_ov096_0229fa44(void *self, int n);
extern int func_ov096_0229f4f8(void *self, int a, int b, int c);
extern int func_ov096_0229f39c(void *self, int a, int b);
extern void func_ov096_0229cc74(void *self, int a, int b);
extern int func_ov096_0229f320(void *self, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_02299c74(void *p, int v);
extern int func_ov096_0229f3bc(void *self, int a, int b);

void func_ov096_022a13b4(char *p);

void func_ov096_022a1424(void *argument0)
{
    func_ov096_022a13b4((char *) argument0);
}

void func_ov096_022a13f0(void *self)
{
    func_ov096_0229f83c(self);
    func_ov094_0229a084((char *) self + 0xde0);
    func_ov094_0229af20((char *) self + 0x358);
    func_ov094_0229bbc0((char *) self + 0xdb8);
}

void func_ov096_022a13b4(char *p)
{
    func_ov096_0229c3c4(p);
    func_ov002_022091cc(p + 0x2564);
    func_ov094_0229a05c(p + 0x0de0);
    if (func_ov002_02207d5c(p + 0x2418)) {
        func_ov096_0229eb98(p);
    }
}

void func_ov096_022a1394(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

int func_ov096_022a1384(int arg)
{
    return func_ov094_0229a098((void *) (arg + 0xde0));
}

void func_ov096_022a128c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        *(u8 *) (self + 0xb5) = 0;
        func_ov096_0229fbbc(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov096_0229f75c(self, a, b, 1);
    if (n != 0x26) {
        func_ov096_0229fa44(self, n);
        return;
    }
    n = func_ov096_0229f4f8(self, a, b, 1);
    if (n != 0x26) {
        func_ov096_0229fa44(self, n);
        return;
    }
    if (func_ov096_0229f39c(self, a, b) != 0) {
        func_ov096_0229cc74(self, 0x25, 0);
        return;
    }
    switch (func_ov096_0229f320(self, a, b)) {
        case 1:
            func_ov096_0229cc74(self, 0x27, 0);
            break;
        case 2:
            func_ov002_02208098((void *) (self), 9);
            func_ov094_02299c74(self + 0xde0, *(u8 *) (self + 0xbf));
            break;
        default:
            if (func_ov096_0229f3bc(self, a, b) != 0) {
                func_ov096_0229cc74(self, 0x24, 0);
            }
            break;
    }
}
