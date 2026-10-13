/* func_ov047_022625c8 @ 0x022625c8, 0xec bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x5c];
    u32 unk_5C;
    u8 pad_60[4];
    u32 unk_64;
    u8 pad_68[0x8e - 0x68];
    s16 unk_8E;
    u8 pad_90[4];
    s16 unk_94;
    u8 pad_96[0x4e8 - 0x96];
    u32 flags;
    u8 pad_4EC[0x72c - 0x4ec];
    u8 unk_72C;
    u8 pad_72D[1];
    u16 unk_72E;
    u8 pad_730[4];
    u16 unk_734;
    u8 pad_736[2];
    u16 unk_738;
} UnkStruct_022625c8;

extern unsigned int data_020ccf94;
extern int func_0202ec58(void *);
extern int func_02073d90(unsigned int);
extern short *func_0209d358(int, int);
extern int func_020a7278(void);
extern int func_0209dcac(void);
extern int func_0202ea40(void *, int *, int);
extern void func_ov047_022624f4(void *, int);

int func_ov047_022625c8(UnkStruct_022625c8 *self)
{
    int local[2];

    if (func_0202ec58(self) == 0) {
        return 0;
    }

    self->unk_72C = 0;
    self->unk_734 = self->unk_8E;
    self->unk_72E = 0xff;
    self->flags |= 2;
    self->unk_738 = 0;

    if (func_02073d90(data_020ccf94) != 0 || func_0209d358(0, 0x4a)[0] != 0) {
        self->flags |= 2;

        if (func_020a7278() != 0) {
            self->unk_5C = 0xf000;
            self->unk_64 = 0x15000;
            self->unk_8E = 0;
            self->unk_94 = 0;
            func_ov047_022624f4(self, 0);
        } else {
            func_ov047_022624f4(self, 6);
        }
        return 1;
    } else {
        if (func_0209dcac() == 2 || func_0209dcac() == 3 || func_0202ea40(self, local, 1) != 0) {
            func_ov047_022624f4(self, 0);
        } else {
            func_ov047_022624f4(self, 2);
        }
        return 1;
    }
}