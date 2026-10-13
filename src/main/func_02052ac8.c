/* func_02052ac8 @ 0x02052ac8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 c : 1;
    u32 a : 4;
    u32 b : 4;
    u32 flagB : 1;
    u32 flagA : 1;
    u32 h : 16;
} Shared;

extern void func_020521d8(void *, u32, u32, u8, int, u16 *, int, u32);

void func_02052ac8(void *arg0, Shared *data)
{
    u16 h;
    int flagA;
    int flagB;

    h = data->h;
    flagA = data->flagA ? 1 : 0;
    flagB = data->flagB ? 1 : 0;

    func_020521d8(arg0, data->a, data->b, (u8) data->c, flagA, &h, flagB, 0);
}
