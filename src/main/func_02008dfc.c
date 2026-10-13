/* func_02008dfc @ 0x02008dfc, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02008dfc {
    u8 pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02008dfc;

typedef struct Saved {
    unsigned int c4, c8, cc;
} Saved;

typedef struct UnkStruct_02008dfc_2 {
    u8 pad_00[0xc4];
    unsigned int unk_C4;
    unsigned int unk_C8;
    unsigned int unk_CC;
    short unk_D0;
    u8 pad_D2[0x298 - 0xd2];
    UnkStruct_02008dfc unk_298;
    u8 pad_2C8[0x698 - 0x2c8];
    UnkStruct_02008dfc unk_698;
} UnkStruct_02008dfc_2;

extern void func_02010f5c(UnkStruct_02008dfc_2 *);
extern void func_0200ee40(UnkStruct_02008dfc_2 *);
extern void func_02010d64(UnkStruct_02008dfc_2 *);
extern void func_02008ea8(UnkStruct_02008dfc_2 *);

void func_02008dfc(UnkStruct_02008dfc_2 *self)
{
    short v3;
    volatile Saved saved;
    UnkStruct_02008dfc blkA, blkB;
    unsigned int *p;

    func_02010f5c(self);
    p = &self->unk_C4;
    saved.c4 = self->unk_C4;
    saved.c8 = p[1];
    saved.cc = p[2];
    v3 = self->unk_D0;
    blkA = self->unk_298;
    blkB = self->unk_698;
    func_0200ee40(self);
    func_02010d64(self);
    func_02008ea8(self);
    self->unk_C4 = saved.c4;
    self->unk_C8 = saved.c8;
    self->unk_CC = saved.cc;
    self->unk_D0 = v3;
    self->unk_298 = blkA;
    self->unk_698 = blkB;
}
