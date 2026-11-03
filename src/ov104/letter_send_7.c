/* letter_send_7: 8 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229ea38 @ 0x0229ea38, 0x8 bytes, Thumb
 * func_ov104_0229e9f8 @ 0x0229e9f8, 0x40 bytes, Thumb
 * func_ov104_0229e9c0 @ 0x0229e9c0, 0x38 bytes, Thumb
 * func_ov104_0229e98c @ 0x0229e98c, 0x32 bytes, Thumb
 * func_ov104_0229e978 @ 0x0229e978, 0x14 bytes, Thumb
 * func_ov104_0229e924 @ 0x0229e924, 0x54 bytes, Thumb
 * func_ov104_0229e8f8 @ 0x0229e8f8, 0x2c bytes, Thumb
 * func_ov104_0229e864 @ 0x0229e864, 0x94 bytes, Thumb
 */

#include "types.h"

extern void func_ov104_0229da90(void *p);
extern void func_ov094_0229a084(void *p);
extern void func_ov094_0229af20(void *p);
extern void func_ov094_0229bbc0(void *p);
extern void func_ov002_0220af74(void *p);
extern void func_ov104_0229d624(void *);
extern void func_ov094_0229a05c(void *);
extern void func_ov002_022091cc(void *);
extern int func_ov002_02207d5c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int, int);
extern void *data_021fbe94;
extern unsigned char data_ov104_0229f730[];
extern unsigned char data_ov104_0229f750[];
extern unsigned char data_ov104_0229f774[];
extern int func_02002d14(void *data, void *param, int a, int b, int c, int d);
extern int func_02002ca4(void *data, void *param, int a);
extern int func_02002c6c(void *data, void *param, int a, int b, int c, int d);
extern int func_ov094_0229a098(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_0220ab38(char *p, int n);
extern int func_ov002_02208054(void *self, int a);
extern void func_ov104_0229dd20(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov104_0229d9bc(void *self, int a, int b, int c);
extern void func_ov104_0229dc68(void *self, int n);
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov104_0229ca44(void *self);
extern void func_ov104_0229c9fc(void *self);

void func_ov104_0229e9c0(void *self);

void func_ov104_0229ea38(void *argument0)
{
    func_ov104_0229e9c0(argument0);
}

void func_ov104_0229e9f8(void *p)
{
    func_ov104_0229da90(p);
    func_ov094_0229a084((void *) ((char *) p + 0xd80));
    func_ov094_0229af20((void *) ((char *) p + 0x2f8));
    func_ov094_0229bbc0((void *) ((char *) p + 0xd58));
    func_ov002_0220af74((void *) ((char *) p + 0x41b4));
}

void func_ov104_0229e9c0(void *self)
{
    func_ov002_022091cc((char *) self + 0x2504);
    func_ov094_0229a05c((char *) self + 0xd80);
    if (func_ov002_02207d5c((char *) self + 0x23b8)) {
        func_ov104_0229d624(self);
    }
}

void func_ov104_0229e98c(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
}

void func_ov104_0229e978(int a)
{
    func_ov094_0229a29c(a + 0xd80, 0);
}

void func_ov104_0229e924(void *self)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov104_0229f730, p, 4, 4, 4, 4);
    func_02002ca4(data_ov104_0229f750, p, 4);
    func_02002c6c(data_ov104_0229f774, p, 4, 0x1e2, 0x1e2, 0x227);
}

void func_ov104_0229e8f8(char *self)
{
    func_ov094_0229a098((void *) ((char *) self + 0xd80));
    func_ov002_0220af94((void *) ((char *) self + 0x41b4));
    func_ov002_0220ab38(self + 0x41b4, 0x65);
}

void func_ov104_0229e864(char *self)
{
    unsigned int ok;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov104_0229dd20(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    n = func_ov104_0229d9bc(self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (n != 0x21) {
        func_ov104_0229dc68(self, n);
        return;
    }

    if (func_ov002_0220a784(self + 0x41b4, 9) != 0) {
        func_ov104_0229ca44(self);
        return;
    }
    if (func_ov002_0220a784(self + 0x41b4, 7) != 0) {
        func_ov104_0229c9fc(self);
    }
}
