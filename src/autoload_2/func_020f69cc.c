/* func_020f69cc @ 0x020f69cc, 0xb4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa];
    u8 unk_0A; // 0xa
    s8 unk_0B; // 0xb
    u8 unk_0C; // 0xc
    u8 pad_0D; // 0xd
    s8 unk_0E; // 0xe
    s8 unk_0F; // 0xf
} UnkStruct_020f69cc;

extern void func_020f6eb4(UnkStruct_020f69cc *self);
extern int func_020f6a80(UnkStruct_020f69cc *self);
extern void func_020f6f3c(UnkStruct_020f69cc *self);
extern void func_020f6ba0(UnkStruct_020f69cc *self);

int func_020f69cc(UnkStruct_020f69cc *self)
{
    int result;
    int r;

    result = -1;

    if (self->unk_0A == 0) {
        goto out;
    }

    if (self->unk_0E == -1) {
        func_020f6eb4(self);
        goto out;
    }

    r = 0;
    if (self->unk_0C == self->unk_0F) {
        r = func_020f6a80(self);
    }

    if (r != 0) {
        func_020f6f3c(self);
        goto out_load;
    }

    if (self->unk_0C == 0 || self->unk_0C == self->unk_0E) {
        self->unk_0C = 0;
        self->unk_0B = self->unk_0B + 1;
        func_020f6ba0(self);
    }

    self->unk_0C = self->unk_0C + 1;

out_load:
    result = self->unk_0B;

out:
    return result;
}
