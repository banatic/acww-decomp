/* func_ov004_02236fa0 @ 0x02236fa0, 0xf4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02236fa0 {
    u8 pad_00[0x158];
    int unk_158;
    int unk_15C;
    u8 pad_160[0x1a8 - 0x160];
    int unk_1A8;
    int unk_1AC;
    u8 pad_1B0[0x1c0 - 0x1b0];
    s16 unk_1C0;
    u8 pad_1C2[0x210 - 0x1c2];
    int unk_210;
    u8 pad_214[0x224 - 0x214];
    int unk_224;
    u8 pad_228[0x252 - 0x228];
    u8 unk_252;
    u8 pad_253[0x255 - 0x253];
    u8 unk_255;
    u8 unk_256;
    u8 pad_257[0x264 - 0x257];
    int unk_264;
    int unk_268;
    u8 pad_26C[0x270 - 0x26c];
    int unk_270;
};

extern void func_020e88dc(void *p, int a, int b);
extern int func_020ea9e4(void *a, void *b);
extern int func_0200322c(void *a, void *b);
extern int func_ov004_02239460(int a, int b);
extern void func_ov004_02239bb4(void *p, int a, int b);

void func_ov004_02236fa0(struct UnkStruct_02236fa0 *self, int k)
{
    if (self->unk_255 == 0) {
        self->unk_252 = self->unk_15C;
        self->unk_256 = 0;
    } else {
        if (self->unk_1AC > self->unk_268) {
            if (k != 0) {
                func_020e88dc(&self->unk_1AC, self->unk_268, self->unk_224 << 2);
            } else {
                func_020e88dc(&self->unk_1AC, self->unk_268, self->unk_224);
            }
        }
        if (func_020ea9e4(&self->unk_1A8, &self->unk_264) <= 0x800) {
            if (self->unk_1AC <= self->unk_268) {
                self->unk_256 = 3;
                self->unk_158 = 0;
                self->unk_270 = func_ov004_02239460(0x3c, 0x78);
            }
        } else {
            self->unk_1C0 = func_0200322c(&self->unk_1A8, &self->unk_264);
            if (k != 0) {
                func_ov004_02239bb4(&self->unk_1A8, self->unk_210 << 1, self->unk_1C0);
            } else {
                func_ov004_02239bb4(&self->unk_1A8, self->unk_210 >> 1, self->unk_1C0);
            }
        }
    }
}
