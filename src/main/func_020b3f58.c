/* func_020b3f58 @ 0x020b3f58, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bba8(volatile u16 *);
extern u16 func_0204bb68(int);
extern int func_0204bb00(volatile u16 *);
extern u16 func_0204bae8(int);

int func_020b3f58(u16 param)
{
    volatile u16 x;
    u16 id;
    int ok;

    x = param;
    if (func_0204bba8(&x)) {
        x = func_0204bb68(0);
    }
    if (func_0204bb00(&x)) {
        x = func_0204bae8(0);
    }
    ok = 0;
    id = x;
    if (x >= 0x5000 && id <= 0x5021) {
        ok = 1;
    }
    if (ok) {
        return id & 0xfff;
    }
    return -1;
}
