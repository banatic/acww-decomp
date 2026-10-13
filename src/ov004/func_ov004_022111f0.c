/* func_ov004_022111f0 @ 0x022111f0, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220cdd8(void *self, int k);
extern void *func_ov004_0220fde0(void *self);
extern int func_ov004_0223a730(void *p);
extern u16 data_ov004_0224fd38;

int func_ov004_022111f0(char *self)
{
    int r;

    if (!func_ov004_0220cdd8(self, 0) && !func_ov004_0220cdd8(self, 5)) {
        switch (*(int *) (self + 0x780)) {
            case 0x10:
                return 1;
            case 0x11:
            case 0x2b:
                r = func_ov004_0223a730(func_ov004_0220fde0(self));
                if (r != data_ov004_0224fd38) {
                    return 1;
                }
                return 0;
        }
    }
    return 0;
}
