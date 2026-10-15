/* func_ov047_02260a88 @ 0x02260a88, 0x8c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov047_02262fc0[];

int func_020160b4(void *object);
int func_020ab504(void *argument0);
int func_0209f150(const void *p, int n);
void func_0206844c(void *dst, void *src, void *fmt);
int func_0202ea40(void *obj, void *buf, int n);
void func_0202ea28(void *obj, void *buf);

struct UnkStruct_02260a88 {
    u8 pad_00[0x1e];
    u8 unk_1E;
    u8 pad_1F[0x40 - 0x1f];
    u32 unk_40;
    u8 pad_44[0xb0 - 0x44];
    u32 unk_B0;
    u32 unk_B4;
    u8 pad_B8[0xd0 - 0xb8];
    u32 unk_D0;
};

extern unsigned char data_021dc7a8[];

void func_ov047_02260a88(struct UnkStruct_02260a88 *self, int event)
{
    u8 buf[8];
    u32 r;
    int k;

    k = (int) self->unk_1E;
    if (k > 0x15) {
        return;
    }

    r = func_020ab504((void *) func_020160b4(self));
    self->unk_D0 = 0xff;
    if (r != 0) {
        if (func_0209f150((void *) data_021dc7a8, 0xc)) {
            self->unk_D0 = 0x47;
        } else {
            self->unk_D0 = 0x48;
        }
        self->unk_B0 = 0;
        buf[1] = (u8) self->unk_D0;
        func_0206844c((void *) self->unk_40, &buf[1], data_ov047_02262fc0);
    } else {
        if (func_0202ea40((void *) self->unk_B4, buf, 1) == 0) {
            return;
        }
        func_0202ea28((void *) self->unk_B4, buf);
    }
}