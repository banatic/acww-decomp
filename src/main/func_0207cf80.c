/* func_0207cf80 @ 0x0207cf80, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Unk0x7EC {
    u8 data[0x7ec];
} Unk0x7EC;

typedef struct UnkStruct_0207cf80 {
    Unk0x7EC arr[8];  // 0x000
    char objA[0x1c];  // 0x3f60
    char objB[0x14];  // 0x3f7c
    char objC[0xbc];  // 0x3f90
    u8 flag1;         // 0x404c
    u8 flag2;         // 0x404d
    u8 flag3;         // 0x404e
    u8 flag4;         // 0x404f
    u32 word1;        // 0x4050
    u32 word2;        // 0x4054
    u32 word3;        // 0x4058
    u32 word4;        // 0x405c
    char buf[20];     // 0x4060
    signed char neg2; // 0x4074
    signed char neg1; // 0x4075
    u8 pad_4076[2];   // 0x4076
    char small[2];    // 0x4078
} UnkStruct_0207cf80;

extern void func_02081660(void *p);
extern void func_02079cb0(void *p);
extern void func_0207a318(void *p);
extern void func_0209a77c(void *p);
extern void MI_CpuFill8(void *p, int v, int len);

void func_0207cf80(UnkStruct_0207cf80 *self)
{
    int i;

    for (i = 0; i < 8; i++) {
        func_02081660(&self->arr[i]);
    }

    func_02079cb0(self->objA);
    func_0207a318(self->objB);
    func_0209a77c(self->objC);

    self->flag1 = 1;
    self->flag2 = 1;
    self->flag3 = 0;
    self->flag4 = 0;
    self->word1 = 0;
    self->word2 = 0;
    self->word3 = 0;
    self->word4 = 0;

    self->neg1 = -1;
    self->neg2 = -1;

    MI_CpuFill8(self->small, 0, 2);
    MI_CpuFill8(self->buf, 0, 20);
}
