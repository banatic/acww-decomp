/* func_ov004_02246900 @ 0x02246900, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov093_02299418();
extern void *data_ov004_0225ff50;
extern void *data_ov004_0225ff54;

int func_ov004_02246900(char *self)
{
    // DECLS
    // ENDDECLS
    if ((*(u8 *) ((char *) &data_ov004_0225ff50) & 0x1) != 0x0) {
        return func_ov093_02299418(*(int *) ((char *) &data_ov004_0225ff54), (*(u8 *) ((char *) &data_ov004_0225ff50) & 0x1));
    }
    return 0x0;
}
