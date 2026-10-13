/* func_ov004_0222c8c8 @ 0x0222c8c8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0209d3f8();
extern void *data_ov004_02258224;

int func_ov004_0222c8c8(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    v2 = func_0209d3f8(*(int *) ((char *) &data_ov004_02258224), 0x1);
    if (v2 != 0x0) {
        *(u8 *) ((char *) *(int *) ((char *) &data_ov004_02258224) + 0x374) = 0x1;
        return 0x374;
    }
    return v2;
}
