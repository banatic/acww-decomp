/* func_0201a518 @ 0x0201a518, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    s16 value;
    u8 unk_02;
    u8 unk_03;
} Elem;

typedef struct {
    int slots[4];  // 0x00
    Elem elems[3]; // 0x10
    int unk_1C;    // 0x1c
    int unk_20;    // 0x20
    u8 pad_24;     // 0x24
    u8 unk_25;     // 0x25
    u8 pad_26;     // 0x26
    u8 unk_27;     // 0x27
} UnkStruct_0201a518_2;

typedef struct {
    char data[28];
} UnkStruct_0201a518;

extern int func_0201a6f8(int *a);
extern int func_020912ac(int p0, short p1, int p2, void *p3);
extern void func_0201a720(int unused, int *ptr, int count);
extern UnkStruct_0201a518 *func_02018fdc(unsigned int idx);
extern void func_0201a608(UnkStruct_0201a518_2 *a, void *b);

void func_0201a518(UnkStruct_0201a518_2 *self, int param2, int param3, int param4, u16 param5, int param6)
{
    Elem *e = &self->elems[param6];
    s16 value = e->value;

    if (value < 0 || value >= 0x66) {
        return;
    }
    if (self->unk_1C != param4 || self->unk_1C == 0x137) {
        return;
    }

    if (e->unk_02 == param5) {
        int slot = func_0201a6f8((int *) self);
        if (slot != -1) {
            self->slots[slot] = func_020912ac((u16) e->value, self->unk_27, param2, &param3);
            if (e->unk_03 == 0) {
                func_0201a720((int) self, (int *) e, 1);
            }
        }
    }

    {
        UnkStruct_0201a518 *rec = func_02018fdc(self->unk_25);
        char *p = (char *) rec + 12 * self->unk_20;
        s16 v2 = *(s16 *) (p + 10);
        if (v2 == param5) {
            func_0201a608(self, e);
        }
    }
}
