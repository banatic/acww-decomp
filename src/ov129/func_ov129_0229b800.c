/* func_ov129_0229b800 @ 0x0229b800, 0x5c bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229b800 {
    u8 pad_00[0xb1];
    u8 unk_B1;
} UnkStruct_0229b800;

extern int func_ov129_0229b9d8(UnkStruct_0229b800 *self);
extern int func_ov129_0229b910(UnkStruct_0229b800 *self);
extern int func_ov129_0229b85c(UnkStruct_0229b800 *self);
extern void RtcSendPxiCommand(int a);
extern void func_ov129_0229bee4(UnkStruct_0229b800 *self, int a);

int func_ov129_0229b800(UnkStruct_0229b800 *self)
{
    int r = 0;

    switch (self->unk_B1) {
        case 0:
            r = func_ov129_0229b9d8(self);
            break;
        case 1:
            r = func_ov129_0229b910(self);
            break;
        case 2:
            r = func_ov129_0229b85c(self);
            break;
    }

    if (r == 1) {
        RtcSendPxiCommand(0x880);
    }
    switch (r) {
        case 1:
        case 2:
            func_ov129_0229bee4(self, 1);
            break;
    }
    return r;
}
