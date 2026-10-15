/* func_ov004_02230c98 @ 0x02230c98, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055060(void *, int, int, int, int, int);
extern int func_ov004_0222c3c4(void *, int);
extern void *data_ov004_022588c8;

void func_ov004_02230c98(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022588c8) != 0x0) {
        func_02055060((char *) *(int *) ((char *) &data_ov004_022588c8) + 0xec,
                      func_ov004_0222c3c4((char *) *(int *) ((char *) &data_ov004_022588c8) + 0x1a4, 0x0), 0x1, 0x1000,
                      ((u32) (*(int *) ((char *) *(int *) ((char *) &data_ov004_022588c8) + 0x18c) << 4) >> 16), 0x0);
    }
}
