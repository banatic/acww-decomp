/* func_ov133_0229b1e8 @ 0x0229b1e8, 0x96 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov133_0229b190(u8 *self);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov133_0229ad78(u8 *self, int v);
extern void func_ov133_0229b320(u8 *self, u8 v);

int func_ov133_0229b1e8(u8 *self, int flag)
{
    int i;

    if (self[0xa2] != self[0xa3]) {
        func_ov133_0229b190(self);
        RtcSendPxiCommand(0x35);
        return 1;
    }
    if (self[0x9f] == 0) {
        if (self[0xa4] != 0xa) {
            self[0x9f] = 1;
        } else {
            if (flag) {
                RtcSendPxiCommand(0x34);
            }
            return 0;
        }
    }
    for (i = self[0x9f]; i < 0xc; i++) {
        u8 *p = self + i;
        u8 t = p[0xa4];

        p = self + (i - 1);
        p[0xa4] = t;
    }
    self[0xaf] = 0xa;
    func_ov133_0229ad78(self, 8);
    func_ov133_0229b320(self, self[0x9f] - 1);
    RtcSendPxiCommand(0x35);
    return 1;
}
