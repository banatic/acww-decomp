/* func_ov002_02209b94 @ 0x02209b94, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02070adc(void *self, int a, int b, int c, int d, int e, int f);

void func_ov002_02209b94(char *self, int i)
{
    u8 a;

    a = *(u8 *) (self + 0x6f);
    if (i >= 0) {
        a = i & 0xf;
    }
    func_02070adc(self, *(u8 *) (self + 0x6e), *(u16 *) (self + 0x6c), 0xd, a, *(u8 *) (self + 0x70), 0);
}
