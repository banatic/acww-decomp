/* func_ov092_02299084 @ 0x02299084, 0x212 bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02299084 {
    u8 pad_00[0x8d];
    u8 unk_8D;
    u8 pad_8E[3];
    u8 unk_91;
};

extern void func_0206f55c(void);
extern void func_0207000c(int id);

void func_ov092_02299084(struct UnkStruct_02299084 *self)
{
    switch (self->unk_91) {
        case 0:
        case 1:
        case 0x18:
        case 0x1a:
        case 0x20:
        case 0x22:
        case 0x23:
        case 0x27:
        case 0x40:
            func_0206f55c();
            break;
    }
    switch (self->unk_91) {
        case 0x0:
            func_0207000c(0xb);
            break;
        case 0x1:
            func_0207000c(0xa);
            break;
        case 0x2:
        case 0x3:
            func_0207000c(0xd);
            break;
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xa:
            func_0207000c(0xe);
            break;
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            func_0207000c(0xf);
            break;
        case 0x1c:
            func_0207000c(0x10);
            break;
        case 0x1d:
        case 0x1e:
            func_0207000c(0x11);
            break;
        case 0x1f:
        case 0x20:
            func_0207000c(0x2c);
            break;
        case 0x21:
            func_0207000c(0x12);
            break;
        case 0x22:
            func_0207000c(0x13);
            break;
        case 0x24:
            func_0207000c(0x14);
            break;
        case 0x25:
            func_0207000c(0x15);
            break;
        case 0x26:
            func_0207000c(0x16);
            break;
        case 0x27:
            func_0207000c(0x17);
            break;
        case 0x28:
            func_0207000c(0x28);
            break;
        case 0x23:
            func_0207000c(0x29);
            break;
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
            func_0207000c(0x18);
            break;
        case 0x2d:
            func_0207000c(0x19);
            break;
        case 0x2e:
            func_0207000c(0x1a);
            break;
        case 0x2f:
            func_0207000c(0x1b);
            break;
        case 0x30:
            func_0207000c(0x1c);
            break;
        case 0x31:
            func_0207000c(0x1d);
            break;
        case 0x32:
            func_0207000c(0x1e);
            break;
        case 0x33:
            func_0207000c(0x2a);
            break;
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3a:
            func_0207000c(0x1f);
            break;
        case 0x3b:
            func_0207000c(0x20);
            break;
        case 0x3c:
            func_0207000c(0x2d);
            break;
        case 0x3d:
            func_0207000c(0x22);
            break;
        case 0x3e:
            func_0207000c(0x23);
            break;
        case 0x3f:
            func_0207000c(0x25);
            break;
        case 0x40:
            func_0207000c(0x26);
            break;
        case 0x41:
            func_0207000c(0x27);
            break;
        case 0x42:
            func_0207000c(0x2d);
            break;
    }
    self->unk_8D = 0;
}
