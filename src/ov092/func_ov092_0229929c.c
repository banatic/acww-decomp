/* func_ov092_0229929c @ 0x0229929c, 0x86 bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229929c {
    u8 pad_00[0x8d];
    u8 unk_8D;
    u8 pad_8E[3];
    u8 unk_91;
};

extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_02001c08(int on);
extern void func_0206ef8c(void);
extern void func_0206ef98(void);
extern void func_0206fc98(int code);

void func_ov092_0229929c(struct UnkStruct_0229929c *self)
{
    switch (self->unk_91) {
        case 0x43:
            func_ov002_022080a0((void *) (self), 5);
            break;
        case 0x44:
            func_ov002_022080a0((void *) (self), 0);
            func_02001c08(1);
            func_0206ef8c();
            break;
        case 0:
        case 1:
            func_0206ef98();
            self->unk_8D = 1;
            break;
        case 2:
        case 0x23:
        case 0x35:
        case 0x36:
        case 0x40:
            self->unk_8D = 1;
            func_0206fc98(self->unk_91);
            break;
    }
}
