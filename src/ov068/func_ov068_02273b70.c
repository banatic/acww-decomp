/* func_ov068_02273b70 @ 0x02273b70, 0x10c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02273b70 {
    u8 pad_00[0x652];
    u16 unk_652;
    u32 unk_654;
    u8 pad1[0x730 - (0x654 + 4)];
    u32 unk_730;
    u8 pad2[0x748 - (0x730 + 4)];
    u16 unk_748;
    u8 unk_74A;
    u8 unk_74B;
} UnkStruct_02273b70;

typedef struct UnkStruct_02273b70_2 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad1[0xb4 - (0x40 + 4)];
    UnkStruct_02273b70 *sub;
} UnkStruct_02273b70_2;

typedef struct UnkStruct_02273b70_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
    u16 unk_04;
    u16 pad2;
} UnkStruct_02273b70_3;

extern int func_020e8840(void *);
extern void func_0206844c(u32, void *, u32);
extern int func_0209a000(void *, int _x);
extern int func_0202ea80(int, int);
extern void func_ov004_02246988(void);
extern void func_02035638(u16);
extern void func_02064da0(int, int);
extern void func_02064db8(int, int, int);
extern void func_ov068_022740f8(UnkStruct_02273b70_2 *, int);
extern u32 data_ov068_02277ca4[];

void func_ov068_02273b70(UnkStruct_02273b70_2 *self)
{
    UnkStruct_02273b70_3 local;

    if (func_020e8840(&self->sub->unk_748) != 0) {
        return;
    }

    self->sub->unk_74A = 0;

    if (self->sub->unk_74B != 0) {
        local.unk_00 = 0xb;
        func_0206844c(self->unk_40, &local.unk_00, data_ov068_02277ca4[self->sub->unk_730]);
    } else {
        local.unk_04 = self->sub->unk_652;
        if (func_0209a000(&local.unk_04, 0) != 0) {
            goto L_funcD;
        }
        local.unk_01 = 0xd;
        func_0206844c(self->unk_40, &local.unk_01, data_ov068_02277ca4[self->sub->unk_730]);
        goto L_after;
    L_funcD:
        func_0202ea80(0xd, 1);
        local.unk_02 = 0xc;
        func_0206844c(self->unk_40, &local.unk_02, data_ov068_02277ca4[self->sub->unk_730]);
    }
L_after:
    func_ov004_02246988();
    func_02035638((u16) self->sub->unk_654);
    self->sub->unk_748 = 0x1e;
    func_02064da0(1, 1);
    func_02064db8(0, 0x1e, 0);
    func_ov068_022740f8(self, 5);
}