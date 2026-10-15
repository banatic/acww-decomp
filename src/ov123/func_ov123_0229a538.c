/* func_ov123_0229a538 @ 0x0229a538, 0x94 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229a538 {
    u8 pad_00[0xa2];
    u8 unk_A2;
    u8 pad_A3;
    u8 unk_A4;
} UnkStruct_0229a538;

extern int func_ov123_0229ac80(UnkStruct_0229a538 *self, int a, int b, u8 c, int d, int e);
extern void func_ov123_0229a5cc(UnkStruct_0229a538 *self, int a, int b, u8 c, int d);
extern void RtcSendPxiCommand(int a);
extern void func_ov123_0229a654(UnkStruct_0229a538 *self, int a, int b, u8 c);
extern void func_ov123_0229a988(UnkStruct_0229a538 *self, u8 c);
extern void func_ov123_0229a918(UnkStruct_0229a538 *self, u8 c);

void func_ov123_0229a538(UnkStruct_0229a538 *self, int a, int b)
{
    u8 st = self->unk_A4;

    if (st <= 2) {
        func_ov123_0229ac80(self, a, b, self->unk_A2, st, 1);
    } else if (st >= 3 && st <= 4) {
        func_ov123_0229a5cc(self, a, b, self->unk_A2, st - 3);
        RtcSendPxiCommand(0x867);
    } else {
        if (st >= 9 && st <= 0xb) {
            RtcSendPxiCommand(0x867);
        }

        switch (self->unk_A4) {
            case 9:
                func_ov123_0229a654(self, a, b, self->unk_A2);
                break;
            case 0xb:
                func_ov123_0229a988(self, self->unk_A2);
                break;
            case 0xa:
                func_ov123_0229a918(self, self->unk_A2);
                break;
        }
    }
}
