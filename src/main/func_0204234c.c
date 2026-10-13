/* func_0204234c @ 0x0204234c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void OS_CreateThread(void *a, void (*b)(void *), void *c, void *d, u32 e, u32 f);
extern void func_020ea584(void *a, void *b);
extern void OS_WakeupThreadDirect(void *a);
extern void func_020424b4(void *a);
extern u32 OSi_ThreadInfo[2];
extern u32 data_021fbe94;

typedef struct {
    u8 pad_00[0xc0];
    u32 unk_C0;
    u32 unk_C4;
    u8 unk_C8[0xe0 - 0xc8];
    u32 unk_E0;
    u8 pad_E4[0x10e4 - 0xe4];
    u32 unk_10E4;
    u8 unk_10E8;
    u8 unk_10E9;
    u8 unk_10EA;
} UnkStruct_0204234c;

int func_0204234c(UnkStruct_0204234c *self)
{
    u32 *ptr_10e4;

    if (self->unk_10E8 == 0) {
        return 0;
    }

    self->unk_E0 = 0x3039;
    ptr_10e4 = &self->unk_10E4;
    *ptr_10e4 = 0x3039;
    self->unk_10E9 = 0;
    self->unk_10EA = 1;

    OS_CreateThread(self, func_020424b4, self->unk_C8, ptr_10e4, 0x1000, 0x1e);

    self->unk_C0 = OSi_ThreadInfo[1];
    self->unk_C4 = data_021fbe94;

    func_020ea584((void *) self->unk_C0, (void *) 0);
    func_020ea584(self, (void *) self->unk_C4);
    OS_WakeupThreadDirect(self);

    return 1;
}
