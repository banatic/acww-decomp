/* func_ov077_02278b54 @ 0x02278b54, 0x4c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x14];
    u32 unk_14;
} Inner40;

typedef struct {
    u8 pad_00[0x1e];
    u8 state;
    u8 pad_1F[0x40 - 0x1f];
    Inner40 *unk_40;
    u8 pad_44[0xb8 - 0x44];
    u8 *unk_B8;
} UnkStruct_02278b54;

extern void func_ov077_02278e10(UnkStruct_02278b54 *self, int arg);
extern void func_020157b0(UnkStruct_02278b54 *self, int a1, int a2, int a3);
extern void func_02015828(UnkStruct_02278b54 *self, int arg);

void func_ov077_02278b54(UnkStruct_02278b54 *self)
{
    switch (self->state) {
        case 0xf:
            self->unk_40->unk_14 = 0;
            func_ov077_02278e10(self, 2);
            break;
        case 0x17:
            func_020157b0(self, 0xc, self->unk_B8[0x718], 0);
            func_02015828(self, 3);
            func_ov077_02278e10(self, 1);
            break;
    }
}
