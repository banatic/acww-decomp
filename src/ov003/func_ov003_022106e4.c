/* func_ov003_022106e4 @ 0x022106e4, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022106e4_2 {
    u8 pad_00[0x12];
    u8 unk_12;
} UnkStruct_022106e4_2;

typedef struct UnkStruct_022106e4 UnkStruct_022106e4;
struct UnkStruct_022106e4 {
    u8 pad_00[0x2d0];
    u8 pad_2D0[0x704 - 0x2d0];
    u32 unk_704;
    u8 pad_708[0x7d4 - 0x708];
    UnkStruct_022106e4_2 sub7d4;
    u8 pad_7E7[0x7f0 - (0x7d4 + 0x13)];
    u32 unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    u32 unk_7FC;
    u32 unk_800;
};

extern int func_02056f94(void *);
extern void func_020109a0(UnkStruct_022106e4 *, int b, int c, unsigned short d);
extern int func_02008258(UnkStruct_022106e4 *, u32);
extern int func_0200c9a8(UnkStruct_022106e4 *, int, int, int);
extern int func_02073908(u32, u32);
extern int func_0200f290(UnkStruct_022106e4 *, int);
extern void func_0200f268(UnkStruct_022106e4 *, int);
extern void func_0203ee08(UnkStruct_022106e4 *, void *);
extern int func_02008380(UnkStruct_022106e4 *, int, int, int);
extern int func_0200d4e8(UnkStruct_022106e4 *, int, int, int);
extern u32 data_020ccf94;

void func_ov003_022106e4(UnkStruct_022106e4 *self)
{
    UnkStruct_022106e4_2 *p;
    u8 mode;
    void *base;

    if (func_02056f94((char *) self + 0x2d0) == 0) {
        return;
    }

    p = &self->sub7d4;

    if (self->unk_704 == 0x49) {
        func_020109a0(self, 0x51, 3, 0);
        return;
    }

    self->unk_7FC = func_02008258(self, self->unk_7F0);
    mode = p->unk_12;

    if (mode == 1) {
        func_0200c9a8(self, 3, 5, -1);
        return;
    }

    if (func_02073908(data_020ccf94, self->unk_800) != 0 && mode == 3) {
        if (func_0200f290(self, 0x11) != 0) {
            func_0200f268(self, 0x11);
            base = (char *) self;
            if (self != 0) {
                base = (char *) self + 0xec;
            }
            func_0203ee08(self, base);
        }
        func_02008380(self, 3, 1, -1);
    } else {
        func_0200d4e8(self, 3, 1, -1);
    }
}
