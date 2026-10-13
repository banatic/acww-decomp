/* func_ov004_0222daf0 @ 0x0222daf0, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov004_02258310;

int func_ov004_0222daf0(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258310) != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258310) + 0xef6) = 0x1;
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258310) + 0xef7) = 0x1;
        return 0xef7;
    }
}
