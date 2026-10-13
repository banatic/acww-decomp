/* func_ov003_02233d68 @ 0x02233d68, 0xe4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02234d70(void *self);
extern void func_ov003_02235934(void *self, int a);
extern void func_ov003_02234030(void *self, int a);
extern int func_ov003_02233a14(void *self, short *p);
extern void func_ov003_02233a94(void *self);
extern void func_ov003_022339bc(void *self);
extern void func_020550e4(void *p, int a);
extern void func_ov003_02233cb8(void *self, short *p);

void func_ov003_02233d68(char *self)
{
    short *p;
    u8 s;

    p = (short *) (self + 0x242);
    s = *(u8 *) (self + 0x251);
    if (s != 0xb && s != 9 && s != 4) {
        func_ov003_02234d70(self);
    }
    func_ov003_02235934(self, 4);
    switch (s) {
        case 3:
        case 0xf:
            func_ov003_02234030(self, 1);
            break;
        case 7:
            *(u8 *) (self + 0x251) = 0xf;
            *(int *) (self + 0x21c) |= 0xf00;
            func_ov003_02233a14(self, p);
            break;
        case 9:
        case 0xb:
            *(char *) (self + 0x24a) = 1;
        case 4:
        case 0x11:
            func_ov003_02233a94(self);
            break;
        case 0x13:
            func_ov003_022339bc(self);
            if ((((unsigned int) *(int *) (self + 0xf4)) << 4) >> 16 != 0) {
                func_020550e4(self + 0x50, 0);
            }
            if (func_ov003_02233a14(self, p) == 0) {
                func_ov003_02233cb8(self, p);
                *(int *) (self + 0x21c) = 0;
            }
            break;
    }
}
