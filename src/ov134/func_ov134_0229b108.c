/* func_ov134_0229b108 @ 0x0229b108, 0x60 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229b108 {
    u8 pad_00[0x92];
    u16 unk_92;
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x9e - 0x96 - 2];
    u8 unk_9E;
} UnkStruct_0229b108;

extern void func_ov134_0229afec(UnkStruct_0229b108 *self, int a, int b);
extern void func_ov134_0229afc0(UnkStruct_0229b108 *self, int a, int b);
extern int func_ov134_0229ae9c(UnkStruct_0229b108 *self, u16 a, u16 b);
extern void func_0200467c(int a);

void func_ov134_0229b108(UnkStruct_0229b108 *self, int a, int b)
{
    u16 v;
    int d;

    switch (self->unk_9E) {
        case 0:
            func_ov134_0229afec(self, a, b);
            v = self->unk_92;
            break;
        case 1:
            func_ov134_0229afc0(self, a, b);
            v = self->unk_94;
            break;
        default:
            return;
    }

    d = func_ov134_0229ae9c(self, self->unk_96, v);
    if (d < -1000 || d > 1000) {
        func_0200467c(0x1a);
        self->unk_96 = v;
    }
}
