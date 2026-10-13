/* func_ov003_022314fc @ 0x022314fc, 0x1e4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020961a8(int n);
extern int func_0200322c(void *a, void *b);
extern void func_ov003_02231104(void *self);
extern int func_020644cc(int n);
extern void func_ov003_0223126c(void *self, short *t);
extern void func_ov003_02230e18(void *self, short *t);
extern void func_ov003_02233178(void *self, short *t);

void func_ov003_022314fc(char *self)
{
    short *t = (short *) (self + 0x242);
    void *p;

    if ((u8) (s8) (*(s8 *) (self + 0x24d) - 0xe) <= 1 && (u16) (*(int *) (self + 0xf4) >> 12) != 0 &&
        (*(u8 *) (self + 0x251) == 4 || *(u8 *) (self + 0x251) == 0x13)) {
        p = func_020961a8(4);
        if (p != 0) {
            *(u16 *) (self + 0x23a) = (u16) func_0200322c(self + 0x204, (char *) p + 0x5c);
        }
        *(u8 *) (self + 0x251) = 0x13;
    }

    switch (*(u8 *) (self + 0x251)) {
        case 4:
            func_ov003_02231104(self);
            if (*(s8 *) (self + 0x24d) == 0x1a) {
                if (*t > 0x140 || (*t % 0x14 == 0 && func_020644cc(0x64) > 0x5a && *t > 0xa0)) {
                    *(u8 *) (self + 0x251) = 0x13;
                    *t = 0;
                }
            } else {
                if (*t > 0xa0 || (*t % 0x14 == 0 && func_020644cc(0x64) > 0x5a && *t > 0x50)) {
                    *(u8 *) (self + 0x251) = 0x13;
                    *t = 0;
                }
            }
            func_ov003_0223126c(self, t);
            break;
        case 7:
            *(u8 *) (self + 0x251) = 9;
            *(u16 *) (self + 0x23a) = (u16) * (short *) (self + 0x240);
            *t = 0;
            // falls through
        case 9:
            func_ov003_02230e18(self, t);
            break;
        case 0xb:
            if (*(s8 *) (self + 0x24d) == 0x1a) {
                func_ov003_02233178(self, t);
            } else {
                func_ov003_02230e18(self, t);
            }
            break;
        case 0x13:
            if (*(s8 *) (self + 0x24d) == 0x1a) {
                if ((u16) (*(int *) (self + 0xf4) >> 12) == 2) {
                    if (*t > 0xa0 || (*t % 0x14 == 0 && func_020644cc(0x64) > 0x55 && *t >= 0x28)) {
                        *t = 0;
                        *(u8 *) (self + 0x251) = 4;
                    }
                }
            } else {
                if (*t > 0x38 || (*t % 5 == 0 && func_020644cc(0x64) > 0x55 && *t > 0)) {
                    *(u8 *) (self + 0x251) = 4;
                    *t = 0;
                }
            }
            func_ov003_0223126c(self, t);
            break;
    }
    *t = *t + 1;
}
