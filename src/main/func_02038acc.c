/* func_02038acc @ 0x02038acc, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_020da520;
extern void func_0205577c(void *);
extern void func_020ba01c(void *);
extern void func_02038d30(void *);
extern void func_02038ccc(void *);
extern void func_02038c6c(void *);
extern void MI_CpuFill8(void *, unsigned int, unsigned int);

typedef struct {
    void *unk_00;
    char pad_04[0xa0 - 0x4];
    char pad_A0[0xbc - 0xa0];
    u32 unk_BC;
    u32 unk_C0;
    u32 unk_C4;
    u8 unk_C8;
    u8 unk_C9;
    u8 unk_CA;
    u8 unk_CB;
    u16 unk_CC;
    u16 unk_CE;
    u32 unk_D0;
    u32 unk_D4;
    u32 unk_D8;
    u32 unk_DC;
    u32 unk_E0;
    u32 unk_E4;
    char pad_E8[0x2e8 - 0xe8];
} UnkStruct_02038acc;

UnkStruct_02038acc *func_02038acc(UnkStruct_02038acc *self)
{
    self->unk_00 = (void *) &data_020da520;
    func_0205577c((char *) self + 4);
    func_020ba01c((char *) self + 0xa0);

    self->unk_BC = 0;
    self->unk_C0 = 0;
    self->unk_C4 = 0;
    self->unk_C8 = 0;
    self->unk_C9 = 0;
    self->unk_CA = 0;
    self->unk_CB = 0;
    self->unk_CC = 0;
    self->unk_CE = 0;
    self->unk_D0 = 0;
    self->unk_D4 = 0;
    self->unk_D8 = 0;
    self->unk_DC = 0;
    self->unk_E0 = 0;
    self->unk_E4 = 0;

    func_02038d30((char *) self + 0xe8);
    func_02038ccc((char *) self + 0x1fc);
    func_02038c6c((char *) self + 0x250);
    MI_CpuFill8((char *) self + 0x2e4, 0x11, 0x800);

    return self;
}
