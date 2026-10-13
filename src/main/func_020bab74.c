/* func_020bab74 @ 0x020bab74, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 pad_00;
    u16 unk_02; // offset 2
    u16 unk_04; // offset 4
} UnkStruct_020bab74;

extern unsigned char data_021f70f0[];
extern unsigned char data_021f7270[];

void func_020bab74(void)
{
    UnkStruct_020bab74 *s1 = (UnkStruct_020bab74 *) data_021f7270;
    UnkStruct_020bab74 *s2 = (UnkStruct_020bab74 *) data_021f70f0;
    volatile u16 tmp;
    volatile u32 *reg = (volatile u32 *) 0x04000000;

    tmp = s1->unk_04;
    *(volatile u16 *) 0x05000400 = tmp;
    *(volatile u16 *) 0x05000000 = s2->unk_02;
    *reg = (*reg) & 0xfffff5ff;
}
