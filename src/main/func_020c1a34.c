/* func_020c1a34 @ 0x020c1a34, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_020e7ad8;
extern u32 func_020984e8(void);
extern u32 func_020c1b20(void *self);
extern void func_02098ff8(u32 a, u32 b);
extern u32 func_020644cc(u32 a);
extern int func_0202ea80(u32 a, u32 b);

struct UnkStruct_020c1a34 {
    u8 pad_00[0xb0];
    u8 *data;
};

struct UnkStruct_020c1a34_2 {
    u32 a;
    u8 b;
};

void func_020c1a34(struct UnkStruct_020c1a34 *self, struct UnkStruct_020c1a34_2 *out)
{
    u32 r;
    u32 idx;

    r = func_020984e8();
    out->a = data_020e7ad8;
    idx = func_020c1b20(self);

    switch (idx) {
        case 0:
            func_02098ff8(r, 0x33);
            out->b = 0;
            break;
        case 1:
            func_02098ff8(r, 0x33);
            out->b = func_020644cc(3) + 1;
            break;
        case 2:
            out->b = func_020644cc(3) + 4;
            func_0202ea80(0x29, 1);
            break;
        case 3:
            out->b = func_020644cc(3) + 7;
            break;
        case 4:
            out->b = func_020644cc(3) + 0x19;
            break;
        case 5:
            out->b = func_020644cc(3) + 0x22;
            break;
        case 6:
            out->b = 0x14;
            break;
    }

    self->data[0x711] = 0;
}
