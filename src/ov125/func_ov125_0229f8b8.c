/* func_ov125_0229f8b8 @ 0x0229f8b8, 0x34 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x87c];
    u8 value;
} UnkStruct_0229f8b8;

extern void func_ov125_0229f75c(UnkStruct_0229f8b8 *self, int arg);

int func_ov125_0229f8b8(UnkStruct_0229f8b8 *self, unsigned int min, unsigned int max)
{
    u8 v = self->value;
    if (v < min) {
        goto fail;
    }
    if (v > max) {
        goto fail;
    }
    if (v == min) {
        self->value = (u8) max;
        func_ov125_0229f75c(self, 4);
    } else {
        self->value = (u8) (v - 1);
    }
    return 1;
fail:
    return 0;
}
