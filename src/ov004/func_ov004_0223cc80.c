/* func_ov004_0223cc80 @ 0x0223cc80, 0x42 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(void *, int);

int func_ov004_0223cc80(char *base, int a1, int a2, int a3, u8 a4)
{
    u8 *p = (u8 *) (base + ((a4 & 1) << 8) + ((a3 & 0xf) << 4) + (a2 & 0xf));
    if (func_ov004_0223cd78(func_ov004_0223ce84(), a1) != -1) {
        *p = 0xff;
        return 1;
    }
    return 0;
}
