/* func_0202e58c @ 0x0202e58c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_0201c444(void *self);
extern u32 func_0207cec0(void *arg1, u32 arg2);
extern u32 func_0207f270(u32 object);
extern u8 data_021e5a2c[];

typedef struct {
    u8 pad_00[0xEA];
    u16 unk_EA;
    u8 pad_EC[0x830 - 0xEC];
    u32 unk_830;
    u32 unk_834;
} UnkStruct_0202e58c;

void func_0202e58c(UnkStruct_0202e58c *self)
{
    if (((self->unk_EA & 0xF000) >> 12) == 14) {
        self->unk_830 = func_0207cec0(data_021e5a2c, func_0201c444(self));
        if (self->unk_830 != 0) {
            self->unk_834 = func_0207f270(self->unk_830);
        } else {
            self->unk_834 = 0;
        }
    }
}
