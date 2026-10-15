/* func_ov004_0222d4d4 @ 0x0222d4d4, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov004_0225827c;

int func_ov004_0222d4d4(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_0225827c) != 0x0 &&
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_0225827c) + 0x24c) == 0x2) {
        return 0x1;
    }
    return 0x0;
}
