/* func_02093678 @ 0x02093678, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Src {
    u32 a;
    u32 b;
    u32 c;
    s16 d;
};
extern struct Src data_021d5658;

struct UnkStruct_02093678 {
    u32 pad_00;
    u32 b;
    u32 c;
    u32 d;
    u32 e;
    u32 unk_14;
    u32 g;
    u16 h;
    s16 i;
    u16 j;
};

void func_02093678(struct UnkStruct_02093678 *self)
{
    u32 *src;
    u32 *p;
    u32 *q;

    src = (u32 *) &data_021d5658;
    p = &self->b;
    self->b = src[0];
    p[1] = src[1];
    p[2] = src[2];

    q = &self->e;
    self->e = 0x1000;
    q[1] = 0x1000;
    q[2] = 0x1000;

    self->h = 0;
    self->i = (s16) ((s16 *) src)[6];
    self->j = 0;
}
