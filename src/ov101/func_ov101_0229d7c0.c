/* func_ov101_0229d7c0 @ 0x0229d7c0, 0x90 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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
extern void RtcSendPxiCommand(int a);

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
    RtcSendPxiCommand(0x28);
}
