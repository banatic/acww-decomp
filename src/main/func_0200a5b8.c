/* func_0200a5b8 @ 0x0200a5b8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200a684(void *a, u32 *b, u8 *c);
extern int func_0200a6a0(void *a, u32 *b, u8 c, int d, int e);

void func_0200a5b8(void *self, int arg)
{
    u8 mode;
    u32 result[2];
    u32 copy[2];

    result[0] = 0;
    result[1] = 0;
    func_0200a684((u8 *) self + 0x8f0, result, &mode);
    copy[0] = result[0];
    copy[1] = result[1];
    func_0200a6a0(self, copy, mode, 6, arg);
}
