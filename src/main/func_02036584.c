/* func_02036584 @ 0x02036584, 0xc2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_020b65c4(void);
extern int func_02036648(void);
extern int func_0203736c(int a, int b, int c, int d, int e, int f, int g);
extern void func_02035684(int a, int b, int c);
extern void func_020356c4(int a, int b, int c, int d);

struct UnkStruct_02036584 {
    u8 pad_00[0xc];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
};

void func_02036584(struct UnkStruct_02036584 *self)
{
    int r5, r1, r2;
    unsigned int r0;

    r5 = func_020984e8();
    if (r5 != 0) {
        if (func_02099020(r5, 0x23) != 0 || func_02099020(r5, 1) != 0) {
            r5 = 1;
        } else {
            r5 = 0;
        }
    } else {
        r5 = 0;
    }

    r0 = func_020b65c4();
    r2 = (r0 == 0x1f) ? 1 : 0;
    r1 = 1;
    r0 = (unsigned char) (r0 + 0xe6);
    if (!(r0 <= 4) && (r2 == 0)) {
        r1 = 0;
    }

    if (r5 != 0 || r1 == 0) {
        return;
    }

    r5 = func_02036648();

    if (self->unk_0C == 0) {
        if (func_0203736c(r5, 0x16, 0x31, 0x32, 0x16, 0x32, 0) != 0) {
            func_02035684(0x10, 0xc8, 0);
            self->unk_0C = 1;
        }
    }

    if (self->unk_0D == 0) {
        if (func_0203736c(r5, 0x16, 0x32, 0, 0, 0, 0) != 0 || self->unk_0E != 0) {
            func_020356c4(0xf, 0x51, 0x7f, 0);
            self->unk_0D = 1;
        }
    }
}
