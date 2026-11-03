/* room_object_02253058_7: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02218100 @ 0x02218100, 0x10 bytes, Thumb
 * func_ov004_022180d4 @ 0x022180d4, 0x2c bytes, Thumb
 */

#include "types.h"

extern int func_ov004_0223c5b8(int a, int b);
extern int func_020308a4(int a, int b);

int func_ov004_02218100(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x844) = 0x0;
    return 0x1;
}

int func_ov004_022180d4(int *self)
{
    int r;
    if (func_ov004_0223c5b8(self[0], self[1]) == 0 && func_020308a4(self[0], self[1]) == -1) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
