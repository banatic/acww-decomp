/* func_020f8fa8 @ 0x020f8fa8, 0x264 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct UnkStruct_020f8fa8 {
    u8 pad_00[0x14];
    s8 type; // +0x14
    u8 pad_15[0x1c - 0x15];
    int freqA; // +0x1c
    int freqB; // +0x20
    int freqC; // +0x24
    u8 pad_28[0x2a - 0x28];
    u8 flag1; // +0x2a
    u8 pad_2B[0x2c - 0x2b];
    s16 note; // +0x2c
    u8 flag2; // +0x2e
};

extern int FX_Div(int, int);

void func_020f8fa8(struct UnkStruct_020f8fa8 *self)
{
    int r0;
    int r1;

    self->freqA = FX_Div((int) self->note << 12, 0x3000);

    r1 = self->type;
    r0 = self->note;
    switch (r1) {
        case 3:
            r1 = 0x4800;
            break;
        case 4:
        default:
            switch (self->flag1) {
                case 0:
                default:
                    r0 = (s16) (r0 % 96);
                    r1 = 0x3000;
                    break;
                case 1:
                    r0 = (s16) (r0 % 48);
                    r1 = 0x1800;
                    break;
                case 2:
                    r0 = (s16) (r0 % 192);
                    r1 = 0x6000;
                    break;
            }
            break;
    }
    r0 = FX_Div(r0 << 12, r1);
    r0 = r0 + 0xc000;
    if (r0 >= 0x20000) {
        r0 -= 0x20000;
    }
    self->freqC = r0;

    r1 = self->type;
    r0 = self->note;
    switch (r1) {
        case 4:
        default:
            switch (self->flag1) {
                case 0:
                default:
                    r0 = (s16) (r0 % 96);
                    r1 = 0x4ccd;
                    break;
                case 1:
                    r0 = (s16) (r0 % 48);
                    r1 = 0x2666;
                    break;
                case 2:
                    r0 = (s16) (r0 % 192);
                    r1 = 0x999a;
                    break;
            }
            break;
        case 3:
            switch (self->flag1) {
                case 3:
                    r1 = self->flag2;
                    if (r1 == 0) {
                        r0 = (s16) (r0 + 0x90);
                    }
                    r1 = 0xe666;
                    break;
                default:
                    r1 = self->flag2;
                    if (r1 == 0) {
                        r0 = (s16) (r0 + 0x30);
                    }
                    r0 = (s16) (r0 % 96);
                    r1 = 0x4ccd;
                    break;
            }
            break;
    }
    r0 = FX_Div(r0 << 12, r1);
    r0 = r0 + 0x4000;
    if (r0 >= 0x14000) {
        r0 -= 0x14000;
    }
    self->freqB = r0;
}
