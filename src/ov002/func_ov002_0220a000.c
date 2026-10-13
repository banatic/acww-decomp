/* func_ov002_0220a000 @ 0x0220a000, 0x5c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220a000 {
    u8 pad_00[0x20];
    int unk_20;
    int unk_24;
};

extern int func_0208aef0(struct UnkStruct_0220a000 *self);
extern int func_0208aeec(struct UnkStruct_0220a000 *self);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_02209d08(char *p, int x, int y, int a);

void func_ov002_0220a000(struct UnkStruct_0220a000 *self, int x, int y, int a, u8 b)
{
    int t;
    int u;

    t = x - (self->unk_20 + func_0208aef0(self));
    RtcSendPxiCommand(0xb);
    if (t >= -0x30 && t <= 0x30) {
        u = y - (self->unk_24 + func_0208aeec(self));
        if (u >= -0x30 && u <= 0x30) {
            a = b;
        }
    }
    func_ov002_02209d08((char *) self + 0x4c, x, y, a);
}
