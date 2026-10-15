/* func_ov068_022762c0 @ 0x022762c0, 0xd4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022762c0 {
    u8 unk_00[0x560];
    u8 unk_560;
    u8 unk_561[0x898 - 0x560 - 1];
    u32 state;
    u8 buf_89c[0xa5e - 0x89c];
    u16 unk_A5E;
    u8 unk_A60;
} UnkStruct_022762c0;

extern int func_ov068_02275c78(UnkStruct_022762c0 *self, int mode);
extern void func_ov068_022761d0(void *dst, UnkStruct_022762c0 *src);
extern void func_ov068_0227647c(UnkStruct_022762c0 *self);
extern int func_020644cc(int arg);

void func_ov068_022762c0(UnkStruct_022762c0 *self, int type, unsigned char param)
{
    switch (type) {
        case 3:
            self->unk_560 = param;
            if (self->state == 0) {
                break;
            }
            if (self->state == 5) {
                self->unk_A5E = (u16) ((func_020644cc(0x28) + 0x3c) * 0x3c);
            }
            func_ov068_02275c78(self, 7);
            break;

        case 0:
            self->unk_560 = param;
            func_ov068_022761d0(self->buf_89c, self);
            func_ov068_02275c78(self, 8);
            break;

        case 1:
            self->unk_560 = param;
            func_ov068_022761d0(self->buf_89c, self);
            if (self->state == 0) {
                func_ov068_02275c78(self, 1);
            } else {
                func_ov068_02275c78(self, 8);
            }
            break;

        case 8:
            self->unk_A60 = 0x14;
            func_ov068_0227647c(self);
            if (self->state == 0xA || self->state == 5) {
                break;
            }
            func_ov068_02275c78(self, 6);
            break;

        case 4:
            func_ov068_02275c78(self, 6);
            break;

        default:
            break;
    }
}
