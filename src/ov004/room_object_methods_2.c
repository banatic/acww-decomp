/* room_object_methods_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02211280 @ 0x02211280, 0x14 bytes, Thumb
 * func_ov004_0221124c @ 0x0221124c, 0x34 bytes, Thumb
 * func_ov004_022111f0 @ 0x022111f0, 0x5c bytes, Thumb
 */

#include "types.h"

extern int func_ov004_0220cdd8(void *self, int k);
extern void *func_ov004_0220fde0(void *self);
extern int func_ov004_0223a730(void *p);
extern u16 data_ov004_0224fd38;

int func_ov004_02211280(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x780) == 0x18) {
        return 0x1;
    }
    return 0x0;
}

int func_ov004_0221124c(void *self)
{
    if (func_ov004_0220cdd8(self, 0) == 0 && func_ov004_0220cdd8(self, 5) == 0 && *(int *) ((char *) self + 0x780) == 0x10) {
        return 1;
    }
    return 0;
}

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
