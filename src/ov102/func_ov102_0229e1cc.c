/* func_ov102_0229e1cc @ 0x0229e1cc, 0x58 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229e1cc {
    u8 pad_00[0x24d4];
    int unk_24D4;
    u8 pad_24D8[0xd1];
    u8 unk_25A9;
};

extern int func_ov002_02207f3c(struct UnkStruct_0229e1cc *, int);
extern void func_020027f0(int);
extern void func_ov102_0229e4f4(struct UnkStruct_0229e1cc *);
extern void func_ov002_02208090(struct UnkStruct_0229e1cc *, int);
extern void func_ov002_02207e80(struct UnkStruct_0229e1cc *, int, int, int);
extern int func_ov002_02207f60(struct UnkStruct_0229e1cc *);

void func_ov102_0229e1cc(struct UnkStruct_0229e1cc *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(4);
        if (self->unk_25A9 != 0) {
            self->unk_25A9--;
        } else {
            func_ov102_0229e4f4(self);
            func_ov002_02208090(self, 9);
        }
    } else {
        func_ov002_02207e80(self, 4, 0, 0);
        self->unk_24D4 = func_ov002_02207f60(self);
    }
}
