/* func_ov066_0226a810 @ 0x0226a810, 0xb4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern void *func_ov066_02266908(u32 size, u32 type);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void DC_StoreRange(void *dest, u32 size);
extern void OS_CreateAlarm(void *ptr);

typedef struct UnkStruct_0226a810 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
    void *unk_04;
    void *unk_08;
    u32 unk_0C;
} UnkStruct_0226a810;

void func_ov066_0226a810(UnkStruct_0226a810 *self, u8 b, int count)
{
    u32 size;
    int i, off;

    size = count * 0xe0;

    self->unk_00 = b;
    self->unk_01 = 0;
    self->unk_02 = (u8) count;
    self->unk_0C = 0;

    self->unk_04 = func_ov066_02266908(size, 0x20);
    self->unk_08 = func_ov066_02266908(count * 0x2c, 0x20);

    {
        volatile u32 d = 0;
        MIi_CpuClearFast(d, self->unk_04, size);
    }
    DC_StoreRange(self->unk_04, size);

    i = 0;
    if (count <= 0) {
        return;
    }
    off = i;
    do {
        OS_CreateAlarm((char *) self->unk_08 + off);
        i++;
        off += 0x2c;
    } while (i < count);
}
