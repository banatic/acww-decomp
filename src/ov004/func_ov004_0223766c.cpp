/* func_ov004_0223766c @ 0x0223766c, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223766c;
typedef void (UnkStruct_0223766c::*PMF)(void);

struct UnkStruct_0223766c {
    u8 pad_00[0x1ee];
    u8 unk_1EE;
    u8 pad_1EF[0x255 - 0x1ef];
    u8 unk_255;
    u8 pad_256[0x259 - 0x256];
    u8 unk_259;
};

extern "C" {
extern PMF data_ov004_0225949c[];
extern int func_ov004_02239460(int a, int b);
extern void func_ov004_02239b80(struct UnkStruct_0223766c *self);
extern void func_ov004_02239768(struct UnkStruct_0223766c *self);
extern void func_ov004_022395d0(struct UnkStruct_0223766c *self, int a, int b);
extern void func_ov004_0223592c(struct UnkStruct_0223766c *self);
void func_ov004_0223766c(struct UnkStruct_0223766c *self);
}

void func_ov004_0223766c(struct UnkStruct_0223766c *self)
{
    if (self->unk_1EE == 2) {
        if (self->unk_259 != 0) {
            if (func_ov004_02239460(0, 0x64) < 0xf) {
                self->unk_255 = 1;
                return;
            }
            self->unk_259 = 0;
        } else {
            if (func_ov004_02239460(0, 0x64) < 0x46) {
                self->unk_255 = 1;
                return;
            }
        }
    }
    (self->*data_ov004_0225949c[self->unk_1EE])();
    func_ov004_02239b80(self);
    if (self->unk_1EE != 2 && self->unk_1EE != 6) {
        func_ov004_02239768(self);
        func_ov004_022395d0(self, 0x1554, 0x3e8);
        func_ov004_0223592c(self);
    }
}
