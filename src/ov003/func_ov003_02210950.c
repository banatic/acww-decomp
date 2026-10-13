/* func_ov003_02210950 @ 0x02210950, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0204f794(u32 *out, u8 a, u8 b);
extern int func_020e8ed8(u32 a, u32 b);
extern int func_02056f94(void *p);
extern void func_020109a0(void *p, int a, int b, int c);
extern void func_0200f268(void *p, int a);
extern void func_0200f27c(void *p, int a);

typedef struct {
    u16 unk_00;
    u8 pad_02[2];
    u32 v0;
    u32 v1;
    u32 v2;
    u16 v3;
    u8 v4;
} UnkStruct_02210950;

void func_ov003_02210950(void *self, void *b)
{
    u32 local[3];
    u8 *b2;
    u8 byte;
    u32 v;
    UnkStruct_02210950 *d;

    b2 = (u8 *) b + 0xc;
    d = (UnkStruct_02210950 *) ((u8 *) self + 0x7d4);
    byte = b2[4];
    func_0204f794(local, b2[2], b2[3]);

    d->unk_00 = *(u16 *) ((u8 *) b + 0xc);
    d->v4 = byte;
    d->v0 = local[0];
    d->v1 = local[1];
    d->v2 = local[2];
    d->v3 = (u16) func_020e8ed8(local[0] - *(u32 *) ((u8 *) self + 0x5c), local[2] - *(u32 *) ((u8 *) self + 0x64));

    v = *(u32 *) ((u8 *) self + 0x704);
    if (v == 0x49) {
        goto case49;
    }
    if (v == 0x4a) {
        goto case4a;
    }
    goto else_block;

case4a:
    func_020109a0(self, 0x51, 3, 0);
    goto done;

case49:
    if (func_02056f94((u8 *) self + 0x2d0) != 0) {
        func_020109a0(self, 0x51, 3, 0);
    }
    goto done;

else_block:
    func_020109a0(self, 0x49, 3, 0);

done:
    func_0200f268(self, 0xd);
    func_0200f27c(self, 0x1c);
}
