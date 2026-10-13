/* func_ov068_02275934 @ 0x02275934, 0x60 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern volatile struct {
    u32 a;
    u32 b;
} data_0213dd98;

typedef struct {
    char pad_00[0x5c];
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    char pad_68[0x510 - 0x68];
    u8 unk_510;
    char pad_511[0xa44 - 0x511];
    u32 unk_A44;
    u32 unk_A48;
    char pad_A4C[0xa50 - 0xa4c];
    u8 unk_A50;
    char pad_A51[0xa70 - 0xa51];
    u32 unk_A70;
    u32 unk_A74;
    volatile u32 unk_A78;
} UnkStruct_02275934;

int func_ov068_02275934(UnkStruct_02275934 *self)
{
    u32 a, b;
    self->unk_A70 = self->unk_5C;
    self->unk_A74 = self->unk_60;
    self->unk_A78 = self->unk_64;
    self->unk_A78 -= 0x2000;

    a = data_0213dd98.a;
    b = data_0213dd98.b;
    self->unk_A44 = a;
    self->unk_A48 = b;

    self->unk_510 = 1;
    self->unk_A50 = 0x28;
    return 1;
}
