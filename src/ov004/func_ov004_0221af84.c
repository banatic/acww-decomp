/* func_ov004_0221af84 @ 0x0221af84, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov004_022577ac;
extern void *data_ov004_02257804;

int func_ov004_0221af84(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x154) < 0x40) {
        *(void **) ((char *) &data_ov004_02257804 + (*(u8 *) (self + 0x154) << 2)) = 0x0;
        *(u8 *) ((char *) &data_ov004_022577ac) = (*(u8 *) ((char *) &data_ov004_022577ac) - 0x1);
        *(u8 *) (self + 0x154) = 0xff;
        return 0x1;
    }
    return 0x0;
}
