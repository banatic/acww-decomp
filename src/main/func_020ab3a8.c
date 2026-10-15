/* func_020ab3a8 @ 0x020ab3a8, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020ab3a8_2 {
    u8 data[0x90];
} UnkStruct_020ab3a8_2;

typedef struct UnkStruct_020ab3a8 {
    UnkStruct_020ab3a8_2 elems[4];
    u8 pad_240[0x98];
    int unk_2D8;
    u8 unk_2DC;
    u8 pad_2DD[0x77];
    int unk_354;
    u8 pad_358[0x8];
    int unk_360;
} UnkStruct_020ab3a8;

extern u8 *func_020ab788(UnkStruct_020ab3a8_2 *elem);
extern u8 *func_020ab794(UnkStruct_020ab3a8_2 *elem);
extern void *func_020ab78c(UnkStruct_020ab3a8_2 *elem);
extern void *func_020a82ac(void *object);
extern void func_020a82bc(void *dst, int value);

void func_020ab3a8(UnkStruct_020ab3a8 *self, int param)
{
    int threshold;
    int sum;
    u32 i;
    int index;
    UnkStruct_020ab3a8_2 *elem;

    threshold = (param << 4) >> 12;
    if (threshold >= 16) {
        threshold = 15;
    }

    sum = 0;
    index = 3;
    i = 0;

    while (i < 4) {
        elem = &self->elems[i];
        sum += func_020ab788(elem)[0];
        if (threshold < sum) {
            index = i;
            break;
        }
        i++;
    }

    elem = &self->elems[index];
    self->unk_2D8 = index;
    self->unk_2DC = func_020ab794(elem)[0];
    func_020a82bc(&self->unk_354, (int) func_020a82ac(func_020ab78c(elem)));
    self->unk_360 = threshold;
}
