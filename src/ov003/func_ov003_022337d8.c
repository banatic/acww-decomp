/* func_ov003_022337d8 @ 0x022337d8, 0xb8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02233720(void *self);
extern void func_ov003_022353a4(void *self, int a, int b);
extern void func_ov003_022319bc(void *self, short *p);
extern int func_ov003_022350cc(void *self);
extern int func_ov003_02235834(void *self, int a, int b);

void func_ov003_022337d8(char *self)
{
    short v;
    int *s;
    int *d;

    switch (*(u8 *) (self + 0x251)) {
        case 0:
            func_ov003_02233720(self);
            break;
        case 9:
        case 0xb:
            if (*(short *) (self + 0x242) == 0) {
                func_ov003_022353a4(self, 1, 0);
            }
            func_ov003_022319bc(self, (short *) (self + 0x242));
            break;
        case 7:
            *(u8 *) (self + 0x251) = 0;
            *(short *) (self + 0x23a) = *(short *) (self + 0x23a) + *(short *) (self + 0x240);
            break;
        case 0x13:
            *(char *) (self + 0x24a) = 0;
            *(u8 *) (self + 0x251) = 0;
            v = *(short *) (self + 0x23a);
            func_ov003_02235834(self, v, func_ov003_022350cc(self));
            s = (int *) (self + 0x204);
            d = (int *) (self + 0x1c8);
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            break;
    }
}
