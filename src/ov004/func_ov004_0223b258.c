/* func_ov004_0223b258 @ 0x0223b258, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_ov004_022595c0;

int func_ov004_0223b258(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022595c0) != 0x0) {
        return *(u8 *) ((char *) *(int *) ((char *) &data_ov004_022595c0) + 0x2b0);
    }
    return 0x0;
}
