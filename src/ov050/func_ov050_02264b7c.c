/* func_ov050_02264b7c @ 0x02264b7c, 0x178 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02264b7c {
    u8 pad_00[0x8];
    u32 mode;
    u8 pad_0C[0x50];
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    u8 pad_68[0x6c8];
    u16 unk_730;
    u8 pad_732[0xe];
    u8 unk_740;
};

extern int func_0202edc8(void);
extern void func_0201c280(void *a, void *b);
extern void func_ov050_02263648(void *a, void *b);
extern int func_ov050_022604bc(void *a);
extern void func_0202edfc(void *a, int b, int c);
extern void func_0201c3f4(void *a, int b);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern int func_02073d90(int arg);
extern void *func_0209d358(int a, int b);
extern u16 data_020c80f8;
extern int data_020ccf94;

int func_ov050_02264b7c(struct UnkStruct_02264b7c *self)
{
    if (!func_0202edc8()) {
        return 0;
    }

    func_0201c280(self, (char *) self + 0x658);
    func_ov050_02263648((char *) self + 0x658, self);

    if (func_ov050_022604bc(self)) {
        func_0202edfc(self, 0xccd, 0x2000);
        func_0201c3f4(self, 0xb00);
    }

    self->unk_730 = data_020c80f8;
    func_0201af28((char *) self + 0x350, 2, 0x400, 0x133, 0x199);

    if (func_02073d90(data_020ccf94) == 0 && *(s16 *) func_0209d358(0, 0x4a) == 0) {
        goto skip_switch;
    }

    switch (self->mode) {
        case 0xd00f:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x11000;
            break;
        case 0xd010:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x13000;
            break;
        case 0xd019:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x19000;
            break;
        case 0xd01a:
            self->unk_5C = 0x13000;
            self->unk_60 = 0;
            self->unk_64 = 0x17000;
            break;
        case 0xd01b:
            self->unk_5C = 0xf000;
            self->unk_60 = 0;
            self->unk_64 = 0x15000;
            break;
        case 0xd01c:
            self->unk_5C = 0x11000;
            self->unk_60 = 0;
            self->unk_64 = 0x13000;
            break;
        default:
            break;
    }

skip_switch:
    self->unk_740 = 0;
    return 1;
}
