/* func_ov004_0221ba40 @ 0x0221ba40, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02071298(void *tbl, u16 *p);
extern int data_021f38f8;

int func_ov004_0221ba40(char *self)
{
    unsigned i;
    u16 t;

    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
        t = (*(u16 **) (self + 0x164))[i];
        if (!func_02071298(&data_021f38f8, &t)) {
            return 0;
        }
    }
    return 1;
}
