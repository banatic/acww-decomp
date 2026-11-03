/* letter_storage_9: 8 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229eae4 @ 0x0229eae4, 0x8 bytes, Thumb
 * func_ov105_0229eaa4 @ 0x0229eaa4, 0x40 bytes, Thumb
 * func_ov105_0229ea6c @ 0x0229ea6c, 0x38 bytes, Thumb
 * func_ov105_0229ea38 @ 0x0229ea38, 0x32 bytes, Thumb
 * func_ov105_0229ea24 @ 0x0229ea24, 0x14 bytes, Thumb
 * func_ov105_0229e9d0 @ 0x0229e9d0, 0x54 bytes, Thumb
 * func_ov105_0229e9a4 @ 0x0229e9a4, 0x2c bytes, Thumb
 * func_ov105_0229e90c @ 0x0229e90c, 0x98 bytes, Thumb
 */

#include "types.h"

extern void func_ov105_0229d77c(void *p);
extern void func_ov094_0229a084(void *p);
extern void func_ov094_0229af20(void *p);
extern void func_ov094_0229bbc0(void *p);
extern void func_ov002_0220af74(void *p);
extern void func_ov105_0229d294(void *);
extern void func_ov094_0229a05c(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov002_022091cc(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int, int);
extern void *data_021fbe94;
extern char data_ov105_0229fb30;
extern char data_ov105_0229fb50;
extern char data_ov105_0229fb74;
extern int func_02002d14(void *, void *, int, int, int, int);
extern int func_02002ca4(void *, void *, int);
extern int func_02002c6c(void *, void *, int, int, int, int);
extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_0220ab84(void *p, int param);
extern int func_ov002_02208054(void *self, int a);
extern void func_ov105_0229db34(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov105_0229d69c(void *self, int a, int b, int c);
extern void func_ov105_0229d9e0(void *self, int n);
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov105_0229c668(void *self);
extern int func_ov105_0229c438(void *self, int a, int b);
extern void func_ov105_0229c3ec(void *self);

void func_ov105_0229ea6c(void *self);

void func_ov105_0229eae4(void *arg0)
{
    func_ov105_0229ea6c((void *) arg0);
}

void func_ov105_0229eaa4(void *param)
{
    func_ov105_0229d77c(param);
    func_ov094_0229a084((char *) param + 0xd84);
    func_ov094_0229af20((char *) param + 0x2fc);
    func_ov094_0229bbc0((char *) param + 0xd5c);
    func_ov002_0220af74((char *) param + 0x5fb8);
}

void func_ov105_0229ea6c(void *self)
{
    func_ov002_022091cc((char *) self + 0x2508);
    func_ov094_0229a05c((char *) self + 0xd84);
    if (func_ov002_02207d5c((char *) self + 0x23bc)) {
        func_ov105_0229d294(self);
    }
}

void func_ov105_0229ea38(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
}

void func_ov105_0229ea24(int a)
{
    func_ov094_0229a29c(a + 0xd84, 0);
}

void func_ov105_0229e9d0(void *receiver)
{
    void *v;
    v = data_021fbe94;
    func_02002d14((void *) &data_ov105_0229fb30, v, 4, 4, 4, 4);
    func_02002ca4((void *) &data_ov105_0229fb50, v, 4);
    func_02002c6c((void *) &data_ov105_0229fb74, v, 4, 0x1e2, 0x1e2, 0x227);
}

void func_ov105_0229e9a4(char *p)
{
    func_ov094_0229a098((void *) ((char *) p + 0xd84));
    func_ov002_0220af94((void *) ((char *) p + 0x5fb8));
    func_ov002_0220ab84(p + 0x5fb8, 0x21);
}

void func_ov105_0229e90c(char *self)
{
    unsigned int ok;
    int n;
    int a;
    int b;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov105_0229db34(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54 + 0x10;
    n = func_ov105_0229d69c(self, a, b, 1);
    if (n != 0x40) {
        func_ov105_0229d9e0(self, n);
        return;
    }

    if (func_ov002_0220a784(self + 0x5fb8, 9) != 0) {
        func_ov105_0229c668(self);
        return;
    }
    if (func_ov105_0229c438(self, a, b) != 0) {
        func_ov105_0229c3ec(self);
    }
}
