/* func_020bedf4 @ 0x020bedf4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020becbc(void *self, int arg);
extern void MI_CpuFill8(void *dst, int value, u32 size);

typedef struct {
    u16 item;
} Slot;

typedef struct {
    int unk_00;
    u8 flags[4];
    u16 unk_08;
    Slot slots[15];
    u8 pal[0x20];
} UnkStruct_020bedf4;

// The empty slot every entry starts as.
extern Slot data_020d22c0;

UnkStruct_020bedf4 *func_020bedf4(UnkStruct_020bedf4 *self)
{
    Slot *end;
    Slot *dst;
    Slot v;

    self->unk_00 = 0;
    self->unk_08 = 0;
    func_020becbc(self, -1);
    end = self->slots + 15;
    dst = self->slots;
    v = data_020d22c0;
    while (dst < end) {
        *dst++ = v;
    }
    MI_CpuFill8(self->pal, 0, sizeof(self->pal));
    return self;
}
