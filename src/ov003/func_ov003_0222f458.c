/* func_ov003_0222f458 @ 0x0222f458, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

struct UnkStruct_0222f458 {
    u8 pad_00[0x204];
    Vec3 unk_204;
    u8 pad_210[0x24d - 0x210];
    s8 unk_24D;
    u8 pad_24E[0x25c - 0x24e];
};

extern struct UnkStruct_0222f458 data_ov003_022617bc[];

int func_ov003_0222f458(Vec3 *dst, int idx)
{
    u8 k = (u8) (idx & 0xf);
    struct UnkStruct_0222f458 *e = &data_ov003_022617bc[k];
    Vec3 *s = &e->unk_204;

    dst->x = s->x;
    dst->y = s->y;
    dst->z = s->z;
    return e->unk_24D;
}
