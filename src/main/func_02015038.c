/* func_02015038 @ 0x02015038, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[8];
    u32 unk_4C;
    u8 pad_50[0xac - 0x50];
    u8 unk_AC;
} UnkStruct_02015038;

extern u16 data_020c80f8;
extern int func_02019d0c(u32 p1, int p2, int p3, int p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u16 p10, u32 p11);
extern void func_0201600c(UnkStruct_02015038 *self);
extern void func_02068440(u32 handle);

int func_02015038(UnkStruct_02015038 *self)
{
    u32 fc = self->unk_4C;

    if (fc != 0 && self->unk_40 != 0) {
        if (func_02019d0c(fc + 0x564, 0x10, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0) != 0) {
            func_0201600c(self);
            func_02068440(self->unk_40);
            self->unk_AC = 1;
        }
    }
    return 0;
}
