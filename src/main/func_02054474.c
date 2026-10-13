/* func_02054474 @ 0x02054474, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_01ffcc10(void);
extern void func_02054a9c(void *self, void *arg);
extern void func_02054524(void *self, void *param);
extern void func_020549d8(void *self, void *param);
extern void func_02054d80(void *self, void *param);

typedef struct {
    void *ptr;
} Param;

typedef struct {
    unsigned char pad_00[0xB4];
    u32 unk_B4;                  // 0xB4
    unsigned char pad_B8[0x3C];  // 0xB8 .. 0xF4
    u32 unk_F4;                  // 0xF4
    unsigned char pad_F8[0x54];  // 0xF8 .. 0x14C
    u32 unk_14C;                 // 0x14C
    u32 unk_150;                 // 0x150
    u32 unk_154;                 // 0x154
    unsigned char pad_158[0x54]; // 0x158 .. 0x1AC
    u32 unk_1AC;                 // 0x1AC
    u32 unk_1B0;                 // 0x1B0
} UnkStruct_02054474;

void func_02054474(UnkStruct_02054474 *self, void *param)
{
    unsigned char t;
    u32 bit1, bit2;
    Param *p = (Param *) param;

    if (func_01ffcc10() != 0) {
        return;
    }

    t = ((unsigned char *) p->ptr)[1];

    if (t >= 0x20) {
        bit1 = self->unk_1B0 & (1 << (t - 0x20));
    } else {
        bit1 = self->unk_1AC & (1 << t);
    }
    if (bit1) {
        func_02054a9c(self, (void *) self->unk_154);
        func_02054524(self, param);
        return;
    }

    if (t >= 0x20) {
        bit2 = self->unk_150 & (1 << (t - 0x20));
    } else {
        bit2 = self->unk_14C & (1 << t);
    }
    if (bit2) {
        func_02054a9c(self, (void *) self->unk_F4);
        func_020549d8(self, param);
        return;
    }

    func_02054a9c(self, (void *) self->unk_B4);
    func_02054d80(self, param);
}
