/* func_ov113_02299cd0 @ 0x02299cd0, 0xb4 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02299cd0 UnkStruct_02299cd0;
struct UnkStruct_02299cd0 {
    u8 unk_00[0x9b];
    u8 unk_9B;
    u8 p1;
    u8 unk_9D;
    u8 unk_9E;
};
extern u8 data_021f6c58;
extern u8 data_021f6c54;

int func_ov113_02299cd0(UnkStruct_02299cd0 *self)
{
    int a, b, t;
    unsigned int v;

    a = data_021f6c58;
    b = data_021f6c54;
    if (b >= 0x54 && b <= 0x70) {
        if (a <= 0x18) {
            self->unk_9B = 5;
            return 1;
        }
        if (a >= 0xe8) {
            self->unk_9B = 4;
            return 1;
        }
        goto fail;
    }
    if (b >= 0xa4 && b <= 0xb4) {
        if (a < 0x20) {
            return 0;
        }
        if (a < 0x50) {
            self->unk_9B = 0;
            return 1;
        }
        if (a < 0x80) {
            self->unk_9B = 1;
            return 1;
        }
        if (a < 0xb0) {
            self->unk_9B = 2;
            return 1;
        }
        if (a < 0xe0) {
            self->unk_9B = 3;
            return 1;
        }
        goto fail;
    }
    if (b >= 0x92 && b <= 0x9e) {
        t = self->unk_9E + 0x44;
        if (a < t) {
            goto fail;
        }
        v = (u8) ((a - t) >> 3);
        if (v >= self->unk_9D) {
            return 0;
        }
        self->unk_9B = (u8) (v + 6);
        return 1;
    }
fail:
    return 0;
}
