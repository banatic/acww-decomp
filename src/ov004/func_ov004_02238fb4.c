/* func_ov004_02238fb4 @ 0x02238fb4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02238f70(void *);
extern void func_ov004_02238f14(void *);
extern void func_ov004_02238eb0(void *);

void func_ov004_02238fb4(char *self)
{
    switch (*(u8 *) (self + 0x281)) {
        case 1:
            func_ov004_02238f70(self);
            break;
        case 2:
            func_ov004_02238f14(self);
            break;
        case 3:
            func_ov004_02238eb0(self);
            break;
    }
}
