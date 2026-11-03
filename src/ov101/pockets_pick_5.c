/* pockets_pick_5: 7 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229d91c @ 0x0229d91c, 0x8 bytes, Thumb
 * func_ov101_0229d8e0 @ 0x0229d8e0, 0x3c bytes, Thumb
 * func_ov101_0229d8a8 @ 0x0229d8a8, 0x38 bytes, Thumb
 * func_ov101_0229d888 @ 0x0229d888, 0x1e bytes, Thumb
 * func_ov101_0229d874 @ 0x0229d874, 0x14 bytes, Thumb
 * func_ov101_0229d850 @ 0x0229d850, 0x24 bytes, Thumb
 * func_ov101_0229d7c0 @ 0x0229d7c0, 0x90 bytes, Thumb
 */

#include "types.h"

extern void func_ov101_0229ce44(void *p);
extern void func_ov094_0229a084(void *p);
extern void func_ov094_0229af20(void *p);
extern void func_ov094_0229bbc0(void *p);
extern void func_ov002_0220af74(void *p);
extern void func_ov101_0229caac(void *p);
extern int func_ov002_02207d5c(void *p);
extern void func_ov002_022091cc(void *p);
extern void func_ov094_0229a05c(void *p);
extern void func_020029e8(int a, int b);
extern void func_020028bc(int a, int b, int c, int d);
extern void func_ov094_0229a29c(void *ptr, int arg);
extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_02208054(void *self, int a);
extern void func_ov101_0229cfa0(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov101_0229cdd0(void *self, int a, int b, int c);
extern void func_ov101_0229cef8(void *self, int n);
extern int func_ov002_0220a784(void *p, int a);
extern void *func_ov002_0220a720(void *p, int a);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_0200467c(int a);

void func_ov101_0229d8a8(void *p);

void func_ov101_0229d91c(void *arg0)
{
    func_ov101_0229d8a8((void *) arg0);
}

void func_ov101_0229d8e0(char *obj)
{
    func_ov101_0229ce44(obj);
    func_ov094_0229a084(obj + 0xb7c);
    func_ov094_0229af20(obj + 0xf4);
    func_ov094_0229bbc0(obj + 0xb54);
    func_ov002_0220af74(obj + 0x2810);
}

void func_ov101_0229d8a8(void *p)
{
    func_ov002_022091cc((char *) p + 0x2300);
    func_ov094_0229a05c((char *) p + 0xb7c);
    if (func_ov002_02207d5c((char *) p + 0x21b4)) {
        func_ov101_0229caac(p);
    }
}

void func_ov101_0229d888(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov101_0229d874(void *p)
{
    func_ov094_0229a29c((char *) p + 0xb7c, 0);
}

void func_ov101_0229d850(void *self)
{
    func_ov094_0229a098((void *) ((char *) self + 0xb7c));
    func_ov002_0220af94((void *) ((char *) self + 0x2810));
}

void func_ov101_0229d7c0(char *self)
{
    unsigned int ok;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov101_0229cfa0(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    n = func_ov101_0229cdd0(self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (n != 0x10) {
        func_ov101_0229cef8(self, n);
        return;
    }

    if (func_ov002_0220a784(self + 0x2810, 9) == 0) {
        return;
    }
    func_ov002_0220a720(self + 0x2810, 9);
    func_ov002_02208098(self, 0x17);
    func_0200467c(0x28);
}
