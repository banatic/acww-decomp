/* func_ov122_0229fa90 @ 0x0229fa90, 0x58 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206e224(char *p);
extern int func_02051d08(char *p, int a);

typedef struct {
    u8 pad_00[0x9c];
    u32 unk_9C;                   // 0x9c
    u32 unk_A0;                   // 0xa0
    u8 pad_A4[0xaa - 0xa4];       // 0xa4 .. 0xa9
    u8 unk_AA;                    // 0xaa
    u8 pad_AB[1];                 // 0xab
    u8 unk_AC;                    // 0xac
    u8 pad_AD[0xbc - 0xad];       // 0xad .. 0xbb
    u8 *unk_BC;                   // 0xbc
    u8 pad_C0[0x3ce8 - 0xc0];     // up to 0x3ce7
    char unk_3CE8;                // 0x3ce8
    u8 pad_3CE9[0x41e0 - 0x3ce9]; // up to 0x41df
    char unk_41E0;                // 0x41e0
} UnkStruct_0229fa90;

void func_ov122_0229fa90(UnkStruct_0229fa90 *self)
{
    int a;
    int ret1;
    int ret2;
    u8 b;

    a = self->unk_AC;
    b = self->unk_AA;

    if (b == 1) {
        ret1 = func_0206e224(&self->unk_3CE8);
        a += (self->unk_BC[0xf8] + ret1);
    }

    ret2 = func_02051d08(&self->unk_41E0, a);
    self->unk_9C = (u8) (ret2 + 0x30);
    self->unk_A0 = 0x28;
}
