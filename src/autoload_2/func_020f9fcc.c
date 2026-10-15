/* func_020f9fcc @ 0x020f9fcc, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    u16 unk_04;
    u8 pad_06[2];
    u8 unk_08;
    u8 pad_09[6];
    u8 unk_0F;
} Self3;

extern int func_020eed18(int, int);
extern int NNS_SndArcPlayerStartSeq(void *handle, int seqNo);

void func_020f9fcc(Self3 *self, int mode)
{
    switch (mode) {
        case 0:
            self->unk_08 = 0;
            self->unk_0F = 0;
            func_020eed18((int) self, 0);
            break;
        case 1:
            self->unk_08 = 1;
            NNS_SndArcPlayerStartSeq(self, self->unk_04);
            break;
        case 2:
            self->unk_08 = 2;
            break;
    }
}
