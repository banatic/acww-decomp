/* func_ov004_02216598 @ 0x02216598, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02035638(u16 a);
extern void *func_02060b34(u16 *p);

void func_ov004_02216598(char *self, unsigned k, int c)
{
    u16 t;

    if (*(u8 *) (self + 0x844) != 0 && k < 0x46) {
        func_02035638((u16) (k + 0xb0));
        if (c != 0) {
            t = 0xfff1;
            func_02060b34(&t);
        }
        *(u8 *) (self + 0x844) = 0;
    }
}
