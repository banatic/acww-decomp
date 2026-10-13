/* func_02019af8 @ 0x02019af8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02019af8 {
    u8 pad_00[0x14];
    int unk_14;
    u8 pad_18[0x1];
    u8 unk_19;
    u8 pad_1A[0x0a];
    int unk_24;
    int unk_28;
    u8 pad_2C[0x34];
} UnkStruct_02019af8;

extern int func_02019de8(UnkStruct_02019af8 *self);
extern void func_02019e80(void *a, void *b);
extern void func_02019d94(UnkStruct_02019af8 *self, int p, int x, int y);
extern void func_02019b68(UnkStruct_02019af8 *self);
extern void func_02019b60(UnkStruct_02019af8 *self);
extern void func_02019d78(UnkStruct_02019af8 *self);

void func_02019af8(UnkStruct_02019af8 *self, int param1)
{
    if (self->unk_28 != 0 && (self->unk_28 >= self->unk_14 || func_02019de8(self) != 0 || self->unk_14 == 3)) {
        func_02019e80((u8 *) self + 0x60, (u8 *) self + 0x2c);
        func_02019d94(self, param1, self->unk_24, self->unk_28);
    }

    if (self->unk_19 == 1) {
        func_02019b68(self);
        self->unk_19 = 0;
    } else if (self->unk_19 == 2) {
        func_02019b60(self);
        self->unk_19 = 0;
    }

    func_02019d78(self);
}