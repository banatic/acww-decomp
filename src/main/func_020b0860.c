/* func_020b0860 @ 0x020b0860, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0209e474(void *);
extern void func_0209e140(void *, int);
extern int func_0209dcdc(void *, void *);

struct bf {
    u16 a : 7;
    u16 b : 4;
    u16 c : 5;
};

int func_020b0860(u16 *param)
{
    u8 local[16];

    *(u32 *) &local[0] = 0;
    *(u32 *) &local[4] = 0;

    func_0209e474(local);

    if (local[2] < 6) {
        func_0209e140(local, 1);
    }

    local[0xa] = local[5];
    local[9] = local[4];
    local[8] = local[3];

    local[0xe] = (u8) ((struct bf *) param)->a;
    local[0xd] = (u8) ((struct bf *) param)->b;
    local[0xc] = (u8) ((struct bf *) param)->c;

    return func_0209dcdc(&local[8], &local[12]);
}
