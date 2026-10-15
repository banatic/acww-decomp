/* func_ov096_0229e7c4 @ 0x0229e7c4, 0x68 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02066830(unsigned char *a, unsigned char *b);
extern void func_ov096_0229e90c(unsigned char *self, int a);
extern void func_ov096_0229f47c(unsigned char *self, int a, unsigned char *p);
extern void func_ov096_0229e8e0(unsigned char *self, int a);
extern void func_ov096_0229f5e0(unsigned char *self, int a, int b, int c);

void func_ov096_0229e7c4(unsigned char *self, int a)
{
    u16 h;
    u8 b;

    switch (self[0xb1]) {
        case 1:
            func_02066830(self + 0x2f28, self + 0x2e28);
            func_ov096_0229e90c(self, a);
            func_ov096_0229f47c(self, a, self + 0x2f28);
            break;
        case 2:
            h = *(unsigned short *) (self + 0xac);
            b = self[0xb0];
            func_ov096_0229e8e0(self, a);
            func_ov096_0229f5e0(self, a, h, b);
            break;
    }
}
