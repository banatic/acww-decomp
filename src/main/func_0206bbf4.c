/* func_0206bbf4 @ 0x0206bbf4, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02050bdc_unk(int arg);
extern int func_0206c234(void *param1, int param2);
extern void func_0206c1cc(void *param1, u32 param2);
extern void func_02068104(u8 *param1, int param2);
extern void func_020a9318(void *self);

typedef struct {
    u8 pad_00[0x4];
    u32 unk_04;
    u8 pad_08[0x24 - 0x8];
    u8 *unk_24;
    void *unk_28;
    u32 unk_2C;
    u32 unk_30;
    u8 pad_34[0x50 - 0x34];
    u32 unk_50;
    u8 pad_54[0xd9 - 0x54];
    u8 unk_D9;
    u8 pad_DA[0xdc - 0xda];
    u32 unk_DC;
} UnkStruct_0206bbf4;

void func_0206bbf4(UnkStruct_0206bbf4 *self, int arg)
{
    int is10;
    int is3000;

    if (self->unk_D9 != 0) {
        arg = func_02050bdc_unk(arg);
        self->unk_D9 = 0;
    }

    is10 = (arg == 10) ? 1 : 0;
    is3000 = (arg == 0x3000) ? 1 : 0;

    func_0206c234(self->unk_28, arg);

    if (is10) {
        func_0206c1cc(self->unk_28, self->unk_04);
        self->unk_2C++;
        if (self->unk_2C >= 3) {
            self->unk_30 = 2;
        }
    }

    func_02068104(self->unk_24, arg);
    self->unk_24[0x1a4a] = 0;

    if (is3000 == 0 && is10 == 0) {
        self->unk_50++;
    }

    if (self->unk_04 == self->unk_DC) {
        self->unk_DC = 0;
        func_020a9318(self);
    }
}
