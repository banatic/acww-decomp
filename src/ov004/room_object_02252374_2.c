/* room_object_02252374_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02213fa4 @ 0x02213fa4, 0x4 bytes, Thumb
 * func_ov004_02213fa0 @ 0x02213fa0, 0x4 bytes, Thumb
 * func_ov004_02213f8c @ 0x02213f8c, 0x14 bytes, Thumb
 * func_ov004_02213f78 @ 0x02213f78, 0x14 bytes, Thumb
 * func_ov004_02213f64 @ 0x02213f64, 0x14 bytes, Thumb
 */

#include "types.h"

extern int func_0205265c(void *, int, int, int);
extern const u8 data_ov004_02247664[];

int func_ov004_02213fa4(void)
{
    return 1;
}

int func_ov004_02213fa0(void)
{
    return 1;
}

int func_ov004_02213f8c(char *self)
{
    // DECLS
    // ENDDECLS
    return func_0205265c(self, 0x1, 0xff, 0x1);
}

int func_ov004_02213f78(char *self)
{
    // DECLS
    // ENDDECLS
    return func_0205265c(self, 0x0, 0xff, 0x1);
}

u8 func_ov004_02213f64(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247664[i];
    }
    return 0;
}
