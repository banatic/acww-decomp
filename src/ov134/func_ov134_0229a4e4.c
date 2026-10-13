/* func_ov134_0229a4e4 @ 0x0229a4e4, 0xe2 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229a4e4 UnkStruct_0229a4e4;
struct UnkStruct_0229a4e4 {
    u8 pad_00[0x60];
    u32 unk_60;
    u8 pad_64[0xa4 - 0x64];
    u8 unk_A4;
    u8 unk_A5;
    u8 pad_A6[0xa9 - 0xa6];
    u8 unk_A9;
    u8 pad_AA[0xaf - 0xaa];
    u8 unk_AF;
};

extern void func_02002708(int);
extern void func_02001b7c(int);
extern void func_02001b6c(int);
extern void func_ov134_02299f74(UnkStruct_0229a4e4 *);
extern void func_ov134_022995b0(UnkStruct_0229a4e4 *, int);
extern int func_ov134_0229aa4c(UnkStruct_0229a4e4 *, int);
extern void func_ov134_02299a00(UnkStruct_0229a4e4 *);
extern void func_ov134_022995d4(UnkStruct_0229a4e4 *, int);

int func_ov134_0229a4e4(UnkStruct_0229a4e4 *self)
{
    switch (self->unk_A9) {
        case 0:
            self->unk_A9 = 1;
            func_02002708(self->unk_A4);
            func_02001b7c(1);
            self->unk_AF--;
            func_ov134_02299f74(self);
            break;
        case 1:
            if (self->unk_AF != 0) {
                self->unk_AF--;
                func_ov134_02299f74(self);
            } else {
                func_02001b6c(1);
                self->unk_A9 = 2;
                self->unk_AF = 0;
                func_ov134_022995b0(self, 4);
                self->unk_60 = (u32) (func_ov134_0229aa4c(self, self->unk_A5) << 3);
                func_ov134_02299a00(self);
            }
            break;
        case 2:
            if (self->unk_AF < 3) {
                self->unk_AF++;
                func_ov134_022995d4(self, self->unk_AF);
            } else {
                self->unk_A9 = 8;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 8:
            return 1;
    }
    return 0;
}
