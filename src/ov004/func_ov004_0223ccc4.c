/* func_ov004_0223ccc4 @ 0x0223ccc4, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(int a, int b);

int func_ov004_0223ccc4(u8 *base, int arg, int col, int row, u8 page)
{
    u8 *p;
    int id;

    p = base + ((page & 1) << 8) + ((row & 0xf) << 4) + (col & 0xf);
    id = func_ov004_0223cd78(func_ov004_0223ce84(), arg);
    if (id != -1) {
        *p = (u8) id;
        return 1;
    }
    return 0;
}
