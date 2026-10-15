/* func_ov004_022299fc @ 0x022299fc, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022299fc {
    int a;
    int b;
    int c;
};

struct UnkStruct_022299fc_2 {
    u8 pad_00[0x5c];
    u8 head[0x8e - 0x5c];
    u8 body[0x7d4 - 0x8e];
    u8 out[4];
};

extern int data_ov004_02247780;
extern void func_020109a0(struct UnkStruct_022299fc_2 *self, int a, int b, unsigned short d);
extern void func_0200fa1c(struct UnkStruct_022299fc *v, struct UnkStruct_022299fc_2 *self, void *a, void *b, void *c);
extern void func_ov004_02229a3c(void *p, int a, int b);

void func_ov004_022299fc(struct UnkStruct_022299fc_2 *self, void *message, int previous)
{
    struct UnkStruct_022299fc v;

    func_020109a0(self, 0x1f, 3, 0);
    func_0200fa1c(&v, self, &self->head, &self->body, &data_ov004_02247780);
    func_ov004_02229a3c(&self->out, v.a, v.c);
}
