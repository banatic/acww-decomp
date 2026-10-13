/* func_ov133_0229bb34 @ 0x0229bb34, 0x2e bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229bb34 {
    u8 pad_00[0x9a];
    volatile u8 n;
    u8 pad_9B[0x15];
    u8 slots[1];
};

u8 *func_ov133_0229bb34(struct UnkStruct_0229bb34 *self)
{
    if (self->n >= 1) {
        return self->slots;
    }
    self->n = self->n + 1;
    return self->slots + (self->n - 1) * 0x6c;
}
