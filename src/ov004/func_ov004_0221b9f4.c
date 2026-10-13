/* func_ov004_0221b9f4 @ 0x0221b9f4, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02071298(void *tbl, u16 *p);
extern int data_021f38f8;

int func_ov004_0221b9f4(char *self)
{
    int n = 0;
    unsigned i = *(u8 *) (self + 0x155);
    u16 t;

    for (; i < *(unsigned *) (self + 0x168); i++) {
        t = (*(u16 **) (self + 0x164))[i];
        if (func_02071298(&data_021f38f8, &t)) {
            n++;
        }
    }
    return n;
}
