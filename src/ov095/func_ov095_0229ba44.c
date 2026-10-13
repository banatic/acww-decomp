/* func_ov095_0229ba44 @ 0x0229ba44, 0xf0 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229ba44 {
    u8 pad_00[4];
} UnkStruct_0229ba44;

extern void func_ov095_0229b3ec(UnkStruct_0229ba44 *self);
extern int func_ov095_0229bebc(UnkStruct_0229ba44 *self, int cmd);
extern void func_ov095_0229c104(UnkStruct_0229ba44 *self, int arg);
extern void func_ov095_0229c134(UnkStruct_0229ba44 *self, int arg);
extern void func_ov095_0229c178(UnkStruct_0229ba44 *self, int arg);
extern void func_ov095_0229c1c4(UnkStruct_0229ba44 *self, int cmd, int arg);
extern void RtcSendPxiCommand(int a);

int func_ov095_0229ba44(UnkStruct_0229ba44 *self, int cmd, int arg)
{
    if (cmd == 0xa) {
        func_ov095_0229b3ec(self);
    }

    if (func_ov095_0229bebc(self, cmd) == 0) {
        func_ov095_0229c104(self, arg);
        return 0;
    }

    switch (cmd) {
        case 0x101:
        case 0x102:
            return 2;
        case 0x11f:
            func_ov095_0229c134(self, arg);
            RtcSendPxiCommand(0x18);
            return 2;
        case 0x120:
            func_ov095_0229c178(self, arg);
            RtcSendPxiCommand(0x18);
            return 2;
        case 0x107:
        case 0x108:
        case 0x109:
            func_ov095_0229c1c4(self, cmd, arg);
            RtcSendPxiCommand(0x18);
            return 2;
        case 0x121:
        case 0x122:
        case 0x123:
            return 2;
        default:
            break;
    }
    func_ov095_0229c104(self, arg);
    return 0;
}
