/* func_ov092_02298f5c @ 0x02298f5c, 0x110 bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02298f5c {
    u8 pad_00[0x8c];
    u8 unk_8C;
    u8 unk_8D;
    u8 pad_8E[3];
    u8 unk_91;
} UnkStruct_02298f5c;

extern char *data_021c526c;

extern int func_0206fca4(void);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_0206ef98(void);
extern void func_0206ead8(int arg);
extern void func_0200467c(int arg);
extern void func_020045ac(int arg);
extern void func_02036470(void *p, int arg);

void func_ov092_02298f5c(UnkStruct_02298f5c *self)
{
    u8 *p;

    self->unk_91 = func_0206fca4();
    self->unk_8D = 1;

    if (self->unk_91 == 0) {
        func_ov002_022080a0((void *) (self), 2);
    } else {
        self->unk_8C = 0;
        func_ov002_022080a0((void *) (self), 0);
        func_0206ef98();
    }

    switch (self->unk_91) {
        case 0x2d:
        case 0x2e:
            func_0206ead8(3);
            break;
        case 0xf:
            func_0206ead8(1);
            break;
        case 0x10:
            func_0206ead8(2);
            break;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
            func_0206ead8(0);
            break;
        default:
            break;
    }

    switch (self->unk_91) {
        case 0:
            func_0200467c(0x11);
            break;
        default:
            func_0200467c(1);
            break;
        case 3:
            func_020045ac(1);
            break;
    }

    p = &self->unk_91;
    switch (*p) {
        case 0x2d:
        case 0x2e:
            func_02036470(data_021c526c + 0x1c4, 1);
            break;
        case 0x3f:
            func_02036470(data_021c526c + 0x1c4, 2);
            break;
        default:
            func_02036470(data_021c526c + 0x1c4, 0);
            break;
    }
}
