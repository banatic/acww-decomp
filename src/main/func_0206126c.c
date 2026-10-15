/* func_0206126c @ 0x0206126c, 0x1d8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0206126c {
    u8 pad_00[0x448];
    u16 unk_448;
    u16 unk_44A;
    u16 unk_44C;
} UnkStruct_0206126c;

typedef struct Child {
    u8 pad_00[0x14c];
    u16 unk_14C;
    u8 pad_14E[4];
    u16 unk_152;
} Child;

extern void func_020614c8(void *p);
extern void func_02053088(void *p);
extern void __register_global_object(void *, void *, void *);
extern void *func_020614c4(void *p);
extern void func_02052ee8(int a, int b, int c, int d, int e);
extern void func_020051b0(void *);

extern int data_021cb500;
extern u16 data_021cb504[5];
extern int data_021cb570, data_021cb594, data_021cb588, data_021cb57c, data_021cb51c;
extern int data_021cb4f8;
extern u16 data_021cb510[5];
extern int data_021cb528, data_021cb534, data_021cb540, data_021cb54c, data_021cb558;

void func_0206126c(UnkStruct_0206126c *self, int idx)
{
    u8 *p;
    int i;
    Child *c0;
    Child *c1;

    p = (u8 *) self;
    for (i = 0; i < 2; i++) {
        func_020614c8(p);
        p += 0x200;
    }
    func_02053088((u8 *) self + 0x400);

    if ((data_021cb500 & 1) == 0) {
        data_021cb504[0] = 0x113e;
        __register_global_object((void *) (&data_021cb504[0]), (((void *) func_020051b0)), (void *) (&data_021cb570));
        data_021cb504[1] = 0x113e;
        __register_global_object((void *) (&data_021cb504[1]), (((void *) func_020051b0)), (void *) (&data_021cb594));
        data_021cb504[2] = 0x113e;
        __register_global_object((void *) (&data_021cb504[2]), (((void *) func_020051b0)), (void *) (&data_021cb588));
        data_021cb504[3] = 0x113e;
        __register_global_object((void *) (&data_021cb504[3]), (((void *) func_020051b0)), (void *) (&data_021cb57c));
        data_021cb504[4] = 0x113e;
        __register_global_object((void *) (&data_021cb504[4]), (((void *) func_020051b0)), (void *) (&data_021cb51c));
        data_021cb500 |= 1;
    }
    self->unk_448 = data_021cb504[idx];

    if ((data_021cb4f8 & 1) == 0) {
        data_021cb510[0] = 0x1182;
        __register_global_object((void *) (&data_021cb510[0]), (((void *) func_020051b0)), (void *) (&data_021cb528));
        data_021cb510[1] = 0x1182;
        __register_global_object((void *) (&data_021cb510[1]), (((void *) func_020051b0)), (void *) (&data_021cb534));
        data_021cb510[2] = 0x1182;
        __register_global_object((void *) (&data_021cb510[2]), (((void *) func_020051b0)), (void *) (&data_021cb540));
        data_021cb510[3] = 0x1182;
        __register_global_object((void *) (&data_021cb510[3]), (((void *) func_020051b0)), (void *) (&data_021cb54c));
        data_021cb510[4] = 0x1182;
        __register_global_object((void *) (&data_021cb510[4]), (((void *) func_020051b0)), (void *) (&data_021cb558));
        data_021cb4f8 |= 1;
    }
    self->unk_44A = data_021cb510[idx];
    self->unk_44C = 0xfff1;

    if (idx != 0) {
        return;
    }

    c0 = (Child *) func_020614c4(self);
    c1 = (Child *) func_020614c4((u8 *) self + 0x200);
    if (c0 != 0) {
        c0->unk_14C = 0x3808;
        c0->unk_152 = 0x374c;
    }
    if (c1 != 0) {
        c1->unk_14C = 0x382c;
        func_02052ee8(6, 0xa, 1, 0, 1);
    }
}
