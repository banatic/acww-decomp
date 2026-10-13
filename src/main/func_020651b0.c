/* func_020651b0 @ 0x020651b0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    struct {
        u8 a;
        u8 b;
    } unk_00;
    u16 raw;
} Pair;

extern unsigned int func_0209def4(u16 *);
extern void func_0209ddd4(Pair p1, Pair p2, Pair *out);

short func_020651b0(void *param)
{
    Pair out;
    Pair p2;
    Pair p1;

    p2.raw = *(u16 *) ((u8 *) param + 8);
    func_0209def4(&p1.raw);
    func_0209ddd4(p1, p2, &out);
    return (short) -(int) (((int) ((out.unk_00.a + out.unk_00.b * 0x3c) << 0xf) / 0x5a0) - 0x4000);
}
