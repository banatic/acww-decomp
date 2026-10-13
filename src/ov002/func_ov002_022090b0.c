/* func_ov002_022090b0 @ 0x022090b0, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220914c(void *self, int v);
extern int func_ov002_02208a8c(void *self, int a, u8 b);
extern void RtcSendPxiCommand(int cmd);

void func_ov002_022090b0(char *self, int v)
{
    func_ov002_0220914c(self, v);
    if (func_ov002_02208a8c(self, *(u8 *) (self + 0x20), v) == 0xf) {
        RtcSendPxiCommand(0x2a);
    } else {
        RtcSendPxiCommand(0x29);
    }
}
