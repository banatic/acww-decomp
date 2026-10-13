/* func_ov004_02228774 @ 0x02228774, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02228774 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02228774_2 {
    u8 pad_00[0x5c];
    struct UnkStruct_02228774 cur;
    u8 pad_68[0x7d4 - 0x68];
    struct UnkStruct_02228774 want;
    u8 pad_7E0[0x800 - 0x7e0];
    int room;
};

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_02051e38(int a);

void func_ov004_02228774(struct UnkStruct_02228774_2 *self)
{
    struct UnkStruct_02228774 *src;
    struct UnkStruct_02228774 *dst;

    if (func_02073908(data_020ccf94, self->room)) {
        func_02051e38(0);
    }
    src = &self->want;
    dst = &self->cur;
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}
