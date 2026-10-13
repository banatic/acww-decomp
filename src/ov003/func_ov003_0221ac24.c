/* func_ov003_0221ac24 @ 0x0221ac24, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    u32 a;
    u32 b;
    u32 c;
    u8 pad_68[0x2e8 - 0x68];
    u8 byte;
    u8 pad_2E9[0x378 - 0x2e9];
    union {
        u16 u;
        struct {
            u16 : 6;
            u16 b6 : 1;
            u16 : 3;
            u16 b10 : 1;
            u16 : 5;
        } bits;
    } flags;
} UnkStruct_0221ac24;

int func_ov003_0221ac24(UnkStruct_0221ac24 *p, Vec *q)
{
    if (p->flags.bits.b10 == 0 && p->flags.bits.b6 == 0 && p->byte == 0) {
        p->a = q->x;
        p->b = q->y;
        p->c = q->z;
        p->flags.u |= 0x400;
        return 1;
    }
    return 0;
}
