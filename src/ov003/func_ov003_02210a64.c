/* func_ov003_02210a64 @ 0x02210a64, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern int func_02073908(void *p, u32 v);
extern u32 func_02008258(void *p, u32 v);
extern int func_02056f94(void *p);
extern void func_020109fc(void *p, int a, int b, int c);
extern void func_ov003_022109f8(void *p, u8 a, u32 *b, u16 c, int d, int e);

struct S7D4 {
    u16 unk_00;
    u8 pad_02[2];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
};

struct UnkStruct_02210a64 {
    u8 pad_00[0x2d0];
    u8 sub_2d0[0x434];
    u32 unk_704;
    u8 pad_708[0xcc];
    struct S7D4 unk_7D4;
    u8 pad_7DC[0x14];
    u32 unk_7F0;
    u8 pad_7F4[0x8];
    u32 unk_7FC;
    u32 unk_800;
    u8 pad_804[0x14];
    u32 unk_818;
};

void func_ov003_02210a64(struct UnkStruct_02210a64 *self)
{
    struct S7D4 *r4 = &self->unk_7D4;
    u32 args[2];
    u8 f5, f6;

    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    } else {
        if (self->unk_818 == 1) {
            r4->unk_07 = 1;
        }
        if (func_02056f94(&self->sub_2d0) != 0 || self->unk_704 == 0x4a) {
            if (func_02056f94(&self->sub_2d0) != 0) {
                func_020109fc(self, 0x4a, 3, 0);
            }
            if (r4->unk_04 != 2 || r4->unk_07 != 0) {
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                f6 = r4->unk_06;
                f5 = r4->unk_05;
                args[0] = f5;
                args[1] = f6;
                func_ov003_022109f8(self, r4->unk_04, args, r4->unk_00, 6, -1);
            }
        }
    }
}
