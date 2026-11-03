/* room_object_switch_shown_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221259c @ 0x0221259c, 0x4 bytes, Thumb
 * func_ov004_02212578 @ 0x02212578, 0x24 bytes, Thumb
 * func_ov004_02212564 @ 0x02212564, 0x14 bytes, Thumb
 * func_ov004_02212550 @ 0x02212550, 0x14 bytes, Thumb
 * func_ov004_0221253c @ 0x0221253c, 0x14 bytes, Thumb
 */

#include "types.h"

extern int func_0205265c(void *, int, int, int);
extern const u8 data_ov004_02247670[];

int func_ov004_0221259c(void)
{
    return 1;
}

int func_ov004_02212578(char *self)
{
    if (*(u8 *) (self + 0x845) != 0) {
        return 1;
    }
    if (*(u8 *) (self + 0x844) == 1) {
        return 1;
    }
    return 0;
}

int func_ov004_02212564(char *self)
{
    // DECLS
    // ENDDECLS
    return func_0205265c(self, 0x0, 0xff, 0x1);
}

int func_ov004_02212550(char *self)
{
    // DECLS
    // ENDDECLS
    return func_0205265c(self, 0x1, 0xff, 0x1);
}

u8 func_ov004_0221253c(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247670[i];
    }
    return 0;
}
