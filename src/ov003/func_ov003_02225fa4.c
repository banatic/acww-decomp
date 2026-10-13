/* func_ov003_02225fa4 @ 0x02225fa4, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_ov003_0223bd44;
int func_020554ec(void *p, void *tbl, u8 i, u8 j);

int func_ov003_02225fa4(char *self)
{
    char *p = self + 0x3068;
    int i;
    unsigned int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            if (func_020554ec(p, &data_ov003_0223bd44, (u8) i, (u8) j) == 0) {
                return 0;
            }
            p += 0x9c;
        }
    }
    return 1;
}
