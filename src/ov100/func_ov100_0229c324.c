/* func_ov100_0229c324 @ 0x0229c324, 0x6c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_020ccf94;
extern int func_02073d90(int g);
extern void func_ov100_0229c2b0(char *self, int a);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void func_02073820(int g);
extern void func_020737f0(int g, u8 *p, int n);
extern void func_02073770(int g, int a, int b);
extern int func_02073d80(int g);

void func_ov100_0229c324(char *self, int b)
{
    u8 buf[0x20];
    int g;

    if (func_02073d90(data_020ccf94) != 0) {
        func_ov100_0229c2b0(self, 8);
        buf[0] = (u8) b;
        MI_CpuCopy8(self + 0x28dc, &buf[1], 0x1e);
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, buf, 0x1f);
        func_02073770(g, 0x16, 4);
        *(u16 *) (self + 0x291a) = (u16) func_02073d80(g);
    }
}
