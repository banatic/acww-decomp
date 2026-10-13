/* func_ov004_0222fd38 @ 0x0222fd38, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov004_02258558;

int func_ov004_0222fd38(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258558) != 0x0) {
        return ((u32) (*(int *) ((char *) *(int *) ((char *) &data_ov004_02258558) + 0x334) << 4) >> 16);
    }
    return 0x0;
}
