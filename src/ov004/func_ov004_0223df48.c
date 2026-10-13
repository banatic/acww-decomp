/* func_ov004_0223df48 @ 0x0223df48, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223df48 {
    u8 pad_00[0x5c];
    int a;
    int b;
    int c;
    u8 pad_68[0x6c - 0x68];
    int d;
    u8 pad_70[0x98 - 0x70];
    int e;
    u8 pad_9C[0xd4 - 0x9c];
    int unk_D4;
    u8 pad_D8[0x114 - 0xd8];
    u8 out[4];
};

extern void func_ov004_0223df88(struct UnkStruct_0223df48 *self);
extern void func_020042c0(void *p, int *t);

void func_ov004_0223df48(struct UnkStruct_0223df48 *self)
{
    int t[4];
    int *p;

    self->e = self->unk_D4;
    func_ov004_0223df88(self);
    self->b = self->d;
    p = (int *) ((char *) self + 0x5c);
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_020042c0(&self->out, t);
}
