/* func_020c24d8 @ 0x020c24d8, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x8e];
    u8 unk_8E;
    u8 pad_8F[0x2a0 - 0x8e - 1];
    u8 unk_2A0;
    u8 pad_2A1[0x334 - 0x2a0 - 1];
    u8 unk_334;
    u8 pad_335[0x478 - 0x334 - 1];
    u8 unk_478;
    u8 pad_479[0x564 - 0x478 - 1];
    u8 unk_564;
    u8 pad_565[0x724 - 0x564 - 1];
    u32 unk_724;
} SELF;

extern int func_02016884(void *, int, void *);
extern int func_02019de8(void *);
extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_0201b38c(void *, int);
extern void func_0201b388(void *, int);
extern u32 func_020912d4(int, void *, void *, int);
extern u32 func_02091278(u32, void *, void *, int);
extern u16 data_020c80f8;

int func_020c24d8(SELF *self)
{
    if (func_02016884(&self->unk_334, 0x53, &self->unk_2A0) && func_02019de8(&self->unk_564)) {
        func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        func_0201b38c(&self->unk_2A0, 0x54);
        func_0201b388(&self->unk_2A0, 0x54);
    }

    if (self->unk_724 == (u32) -1) {
        self->unk_724 = func_020912d4(0x54, &self->unk_478, &self->unk_8E, 0);
    }
    if (self->unk_724 != (u32) -1) {
        func_02091278(self->unk_724, &self->unk_478, &self->unk_8E, 0);
    }

    return 1;
}
