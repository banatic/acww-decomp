/* func_ov004_02223c1c @ 0x02223c1c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02035638(int a);
extern void func_02035684(int a, int b, int c);
void func_ov004_02223c1c(char *self)
{
    int v = *(u8 *) (self + 0x1e);
    if (v >= 0x30 && v <= 0x3b) {
        func_02035638(0x3e);
        func_02035684(0xc, 6, 0x1a);
    }
}
