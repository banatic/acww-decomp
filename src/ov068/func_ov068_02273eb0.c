/* func_ov068_02273eb0 @ 0x02273eb0, 0x140 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct InitRet {
    u8 pad_00[4];
    u32 unk_04;
} InitRet;

typedef struct UnkStruct_02273eb0 {
    u8 pad_00[0x652];
    u16 unk_652;
    u32 unk_654;
    u8 pad1[0x748 - 0x658];
    u16 unk_748;
    u8 pad_74A[0x74b - 0x74a];
    u8 unk_74B;
} UnkStruct_02273eb0;

typedef struct UnkStruct_02273eb0_2 {
    u8 pad_00[0xb4];
    UnkStruct_02273eb0 *base;
    u8 pad1[0xd0 - 0xb8];
    u8 unk_D0;
} UnkStruct_02273eb0_2;

extern InitRet *func_020682e0(int);
extern void func_02064da0(int, int);
extern void func_02064db8(int, int, int);
extern void func_0201acbc(void *, int, int, int, int, int);
extern int func_020e8840(void *);
extern void func_ov004_02246ea8(void);
extern int func_020644cc(int);
extern s16 *func_0209d358(int, int);
extern void func_020356c4(int, int, int, int);
extern void func_ov004_02246a2c(void);
extern void func_ov068_022740f8(UnkStruct_02273eb0_2 *, int);

void func_ov068_02273eb0(UnkStruct_02273eb0_2 *self)
{
    volatile unsigned char _frame[8];
    u16 val;
    u32 result;

    (void) &_frame;
    if (func_020682e0(0)->unk_04 != 5) {
        return;
    }

    if (self->base->unk_748 == 0x2d) {
        func_02064da0(0, 30);
        func_02064db8(1, 1, 0);
        func_0201acbc((void *) ((char *) self->base + 0x3b0), 0, 0xfffff3e8, 0, 0x276, 0x276);
    }

    if (func_020e8840(&self->base->unk_748) != 0) {
        return;
    }

    func_ov004_02246ea8();
    self->base->unk_654 = 0;

    if (self->base->unk_74B != 0) {
        self->base->unk_654 = func_020644cc(3) + 0xa9;

        if (*func_0209d358(0, 0x4e) != 0) {
            int idx;
            idx = *func_0209d358(0, 0x4e) - 1;
            if (idx < 0) {
                idx = 0;
            } else if (idx > 3) {
                idx = 3;
            }
            self->base->unk_654 = idx + 0xa9;
        }
    } else {
        val = self->base->unk_652;
        if (val >= 0x1323 && val <= 0x1368) {
            result = val - 0x1323;
        } else {
            result = -1;
        }

        self->base->unk_654 = result + 0x63;
    }

    func_020356c4(0xf, (u16) self->base->unk_654, 0x7f, 0);
    self->unk_D0 = 0;
    func_ov004_02246a2c();
    func_ov068_022740f8(self, 3);
}