/* func_020f6f3c @ 0x020f6f3c, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020f6f3c {
    char pad_00[10];
    s8 unk_0A;
    s8 unk_0B;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    s8 unk_0F;
    s8 unk_10;
    s8 unk_11;
} UnkStruct_020f6f3c;

void func_020f6f3c(UnkStruct_020f6f3c *self)
{
    self->unk_0A = 0;
    self->unk_0B = -1;
    self->unk_0C = 0;
    self->unk_11 = -1;
    self->unk_10 = self->unk_11;
    self->unk_0F = self->unk_10;
    self->unk_0E = self->unk_0F;
}
