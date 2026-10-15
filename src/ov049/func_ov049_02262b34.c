/* func_ov049_02262b34 @ 0x02262b34, 0xcc bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02262b34 {
    u8 pad_00[0x5c];
    u32 unk_5C;
    u8 pad_60[4];
    u32 unk_64;
    u8 pad_68[0x26];
    u16 unk_8E;
    u8 pad_90[4];
    u16 unk_94;
    u8 pad_96[0x452];
    u32 unk_4E8;
    u8 pad_4EC[0x489];
    u8 unk_975;
} UnkStruct_02262b34;

extern int data_020ccf94;
extern int func_0202ec58(UnkStruct_02262b34 *self);
extern int func_02073d90(int x);
extern short *func_0209d358(int a, int b);
extern int func_020a7278(void);
extern int func_020b65b8(void);
extern int func_02030864(int x);
extern int func_0202ea40(UnkStruct_02262b34 *self, void *buf, int n);
extern void func_ov049_02262a94(UnkStruct_02262b34 *self, int n);

int func_ov049_02262b34(UnkStruct_02262b34 *self)
{
    u8 local[8];

    if (func_0202ec58(self) == 0) {
        return 0;
    }

    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        if (func_020a7278() != 0) {
            self->unk_4E8 |= 2;
            self->unk_5C = 0xd000;
            self->unk_64 = 0x19000;
            self->unk_8E = 0;
            self->unk_94 = 0;
            func_ov049_02262a94(self, 0xa);
        } else {
            self->unk_4E8 |= 2;
            func_ov049_02262a94(self, 8);
        }
    } else {
        if (func_020b65b8() == 0) {
            func_ov049_02262a94(self, 0);
        } else {
            func_ov049_02262a94(self, 1);
        }
        func_02030864(0);
        if (func_0202ea40(self, local, 2) != 0) {
            self->unk_975 = 1;
        }
    }

    return 1;
}
