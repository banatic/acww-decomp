/* func_ov092_02299324 @ 0x02299324, 0x5c bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02299324 {
    u8 pad_00[0x91];
    u8 unk_91;
};

extern void func_0206efc0(void);
extern void RtcSendPxiCommand(int cmd);
extern void func_02036468(void *p);
extern char *data_021c526c;

void func_ov092_02299324(struct UnkStruct_02299324 *self, int i, int flag)
{
    self->unk_91 = (u8) i;
    switch (i) {
        case 0:
        case 1:
        case 0x43:
            break;
        case 0x44:
            func_0206efc0();
            break;
    }
    switch (i) {
        case 0x43:
        case 0x44:
            if (flag) {
                RtcSendPxiCommand(2);
            }
            func_02036468(data_021c526c + 0x1c4);
            break;
    }
}
