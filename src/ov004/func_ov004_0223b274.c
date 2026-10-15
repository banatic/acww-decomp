/* func_ov004_0223b274 @ 0x0223b274, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov004_022595c0;

void func_ov004_0223b274(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022595c0) != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_022595c0) + 0x2b0) = 0x1;
    }
}
