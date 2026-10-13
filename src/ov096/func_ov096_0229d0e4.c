/* func_ov096_0229d0e4 @ 0x0229d0e4, 0x86 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229d0e4 {
    u8 pad_00[0xbb];
    u8 unk_BB;
} UnkStruct_0229d0e4;

extern void RtcSendPxiCommand(int a);

int func_ov096_0229d0e4(UnkStruct_0229d0e4 *self)
{
    switch (self->unk_BB) {
        case 18:
        case 19:
            RtcSendPxiCommand(0x50);
            break;
        case 20:
            RtcSendPxiCommand(0x71);
            break;
        case 9:
            RtcSendPxiCommand(0x24);
            return 0;
        case 2:
        case 22:
        case 23:
            RtcSendPxiCommand(0x25);
            return 0;
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            return 0;
        default:
            break;
    }
    return 1;
}
