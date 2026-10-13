/* func_ov129_0229c1f8 @ 0x0229c1f8, 0xe0 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
    char pad_9C[0xa6 - 0x9c];
    u16 unk_A6;
    char pad_A8[2];
    u16 unk_AA;
    char pad_AC[0xb0 - 0xac];
    u8 unk_B0;
    u8 unk_B1;
    char pad_B2[1];
    u8 unk_B3;
    char pad_B4[0x734 - 0xb4];
    char unk_734;
    char pad_735[0x2f98 - 0x735];
    u8 tab[4];
} UnkStruct_0229c1f8;

extern int func_ov129_0229bd4c(UnkStruct_0229c1f8 *self, int a, int b);
extern int func_ov129_0229bbd8(UnkStruct_0229c1f8 *self, int a, int b);
extern int func_ov129_0229bca4(UnkStruct_0229c1f8 *self, int a);
extern void func_ov129_0229c2d8(UnkStruct_0229c1f8 *self);
extern void func_ov127_02299a00(void *p, int a, int b);

void func_ov129_0229c1f8(UnkStruct_0229c1f8 *self)
{
    int idx;
    int k;

    if (func_ov129_0229bd4c(self, self->unk_94, self->unk_98) != 0) {
        if (self->unk_B0 != 0xff && self->unk_B3 != 0xff && self->unk_B0 != self->unk_B3) {
            switch (self->unk_B1) {
                case 1:
                case 2: {
                    int r = func_ov129_0229bbd8(self, self->unk_B3, self->unk_B0);
                    if (r != 0xffff && self->tab[r] == 3) {
                        self->unk_AA = (u16) r;
                    } else if (self->unk_B1 == 2) {
                        if (func_ov129_0229bca4(self, self->unk_B0) != 0) {
                            self->unk_AA = 0xffff;
                        }
                    }
                    break;
                }
            }
        }
        idx = self->unk_AA;
    } else {
        idx = 0xffff;
    }
    if (idx != self->unk_A6) {
        func_ov129_0229c2d8(self);
    }
    if (idx != 0xffff) {
        k = self->tab[idx];
        if (k == 2) {
            func_ov127_02299a00(&self->unk_734, idx, 0xb);
        } else if (k == 3) {
            func_ov127_02299a00(&self->unk_734, idx, 8);
        }
    }
    self->unk_A6 = (u16) idx;
}
