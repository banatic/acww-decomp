/* func_ov110_0229c5a0 @ 0x0229c5a0, 0xd8 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xf5];
    u8 unk_F5;
    u8 pad_F6[0x22e0 - 0xf6];
    u8 unk_22E0;
} UnkStruct_0229c5a0;

extern void func_ov110_0229c2a8(UnkStruct_0229c5a0 *self, int arg);
extern int func_ov110_0229d5e4(UnkStruct_0229c5a0 *self, u8 value);
extern int func_ov110_0229d5d4(UnkStruct_0229c5a0 *self, u8 value);
extern int func_ov110_0229d5c8(UnkStruct_0229c5a0 *self, u8 value);
extern void func_ov110_0229c7f0(UnkStruct_0229c5a0 *self, int arg1, int arg2);
extern void func_ov110_0229c6ec(UnkStruct_0229c5a0 *self, int arg1, int arg2);
extern void func_ov110_0229c678(UnkStruct_0229c5a0 *self, int arg1);
extern void func_ov110_0229c2b8(UnkStruct_0229c5a0 *self, int arg);
extern void func_ov002_0220a314(void *arg);
extern void func_ov002_0220a2b4(void *arg);

int func_ov110_0229c5a0(UnkStruct_0229c5a0 *self, int arg1, int arg2)
{
    u8 initial = self->unk_F5;

    func_ov110_0229c2a8(self, 0x30);
    func_ov110_0229c2a8(self, 0x100);

    if (arg1 == 0) {
        return 0;
    }

    if (func_ov110_0229d5e4(self, self->unk_F5) != 0) {
        func_ov110_0229c7f0(self, arg1, arg2);
    } else if (func_ov110_0229d5d4(self, self->unk_F5) != 0) {
        func_ov110_0229c6ec(self, arg1, arg2);
    } else if (func_ov110_0229d5c8(self, self->unk_F5) != 0) {
        func_ov110_0229c678(self, arg1);
    }

    if (func_ov110_0229d5c8(self, self->unk_F5) != func_ov110_0229d5c8(self, initial)) {
        if (func_ov110_0229d5c8(self, self->unk_F5) != 0) {
            func_ov002_0220a314(&self->unk_22E0);
        } else {
            func_ov002_0220a2b4(&self->unk_22E0);
        }
        func_ov110_0229c2b8(self, 0x100);
    }

    return (initial != self->unk_F5) ? 1 : 0;
}
