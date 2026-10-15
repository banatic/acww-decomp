/* func_ov004_0222dad8 @ 0x0222dad8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov004_02258310;

void func_ov004_0222dad8(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258310) != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258310) + 0xef8) = 0x1;
    }
}
