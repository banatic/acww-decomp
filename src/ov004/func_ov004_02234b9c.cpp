/* func_ov004_02234b9c @ 0x02234b9c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02234b9c;
struct UnkStruct_02234b9c_2;
struct UnkStruct_02234b9c_3;

typedef void (UnkStruct_02234b9c::*PMF)(UnkStruct_02234b9c_2 *, int);

struct UnkStruct_02234b9c_3 {
    u8 pad_00[0x160];
    int unk_160;
};
struct UnkStruct_02234b9c_2 {
    UnkStruct_02234b9c_3 *p;
};

extern "C" {
extern PMF data_ov004_0225940c[3];

void func_ov004_02234b9c(UnkStruct_02234b9c *self, UnkStruct_02234b9c_2 *x, int a);
}

void func_ov004_02234b9c(UnkStruct_02234b9c *self, UnkStruct_02234b9c_2 *x, int a)
{
    u8 i;
    i = (u8) x->p->unk_160;
    if (i < 3) {
        (self->*data_ov004_0225940c[i])(x, a);
    }
}
