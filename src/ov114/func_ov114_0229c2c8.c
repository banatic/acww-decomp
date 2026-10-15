/* func_ov114_0229c2c8 @ 0x0229c2c8, 0xa8 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct UnkStruct_0229c2c8 {
    u8 pad_00[0x12b9];
    u8 unk_12B9;
    u8 pad_12BA;
    u8 unk_12BB;
    u8 unk_12BC;
} UnkStruct_0229c2c8;

extern int func_ov114_0229c1b8(UnkStruct_0229c2c8 *self, unsigned int a);
extern void RtcSendPxiCommand(int a);
extern void func_ov114_0229c6f8(UnkStruct_0229c2c8 *self, u8 a);
extern int func_ov114_0229cee0(UnkStruct_0229c2c8 *self);
extern int func_ov114_0229cf18(UnkStruct_0229c2c8 *self);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void *p);

int func_ov114_0229c2c8(UnkStruct_0229c2c8 *self)
{
    unsigned int v = self->unk_12BC;

    if (v >= 0xd) {
        v -= 0xd;
        if (func_ov114_0229c1b8(self, v) != 0) {
            if (self->unk_12B9 != v) {
                RtcSendPxiCommand(0x29);
            }
            func_ov114_0229c6f8(self, (u8) v);
        }
        return 0;
    }

    switch (v) {
        case 1:
            func_ov114_0229cee0(self);
            return 0;
        case 0:
            func_ov114_0229cf18(self);
            return 0;
        case 2:
            self->unk_12BB = 0;
            return 1;
        case 3:
            self->unk_12BB = 1;
            return 1;
        case 4:
            self->unk_12BB = 2;
            func_ov002_0220a574((char *) self + 0x121c);
            func_ov002_0220a4bc((char *) self + 0x121c);
            return 1;
    }
    return 0;
}
