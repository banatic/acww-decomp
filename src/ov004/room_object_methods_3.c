/* room_object_methods_3: 2 functions, module ov004
 * mwccarm 1.2/base -O1,s
 * func_ov004_022112c4 @ 0x022112c4, 0x44 bytes, Thumb
 * func_ov004_02211294 @ 0x02211294, 0x2e bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02211294 {
    u16 pad_00[6];
    u16 unk_0C;
};

extern int func_ov004_0220d2b8(void *p);

int func_ov004_022112c4(unsigned char *self)
{
    unsigned short v;
    int a, b;
    v = *(unsigned short *) (self + 0xc);
    a = (v == 0x3b) ? 1 : 0;
    if (a != 0 || (b = ((v == 0x3c) ? 1 : 0)) != 0) {
        if (func_ov004_0220d2b8(self + 0x740) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_ov004_02211294(struct UnkStruct_02211294 *self)
{
    int ok = 1;
    u16 v = self->unk_0C;
    int a = (v == 0x36) ? 1 : 0;
    if (a == 0) {
        int b = (v == 0x37) ? 1 : 0;
        if (b == 0) {
            ok = 0;
        }
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}
