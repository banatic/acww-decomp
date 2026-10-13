/* func_ov004_02222098 @ 0x02222098, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_020c80f8;
extern int func_02019c6c(char *p, int a, int b);
int func_ov004_02222098(char *self)
{
    return func_02019c6c(self + 0x564, 1, data_020c80f8);
}
