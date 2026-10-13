/* func_0204d960 @ 0x0204d960, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_020cb764[4][2];
extern u32 func_02064b2c(u32 a, u32 b, u32 c, u32 *d);

int func_0204d960(u32 *dst, u32 arg)
{
    u32 *src = data_020cb764[0];
    u32 tmp = 0;
    int ok = 1;
    int i;

    for (i = 0; i < 4; i++) {
        dst[0] = func_02064b2c(*src, arg, 4, &tmp);
        if (dst[0] != 0) {
            dst[1] = tmp >> 1;
        } else {
            ok = 0;
            dst[1] = 0;
            break;
        }
        dst += 2;
        src += 2;
    }
    return ok;
}
