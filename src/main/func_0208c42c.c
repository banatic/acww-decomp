/* func_0208c42c @ 0x0208c42c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0208c42c {
    u8 pad_00[0xc4];
    u32 c4;
    u8 pad_C8[8];
    u32 d0;
};

extern unsigned char data_020d0a99[];
extern unsigned char data_020d0a98[];
extern signed char data_020d0a85[];

extern void func_0203aad0(int, int);
extern void RtcSendPxiCommand(int);

void func_0208c42c(struct UnkStruct_0208c42c *self)
{
    int off = self->c4 * 2;
    func_0203aad0(data_020d0a99[off], data_020d0a98[off]);
    if (self->c4 != self->d0) {
        int a = data_020d0a85[self->c4 * 2];
        int b = data_020d0a85[self->d0 * 2];
        int cmd;
        if (a < b) {
            cmd = 0x4d;
        } else if (a > b) {
            cmd = 0x4c;
        } else {
            cmd = 0x4e;
        }
        RtcSendPxiCommand(cmd);
        self->d0 = self->c4;
    }
}
