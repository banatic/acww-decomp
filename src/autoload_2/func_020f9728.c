/* func_020f9728 @ 0x020f9728, 0xb4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#pragma optimize_for_speed

typedef struct {
    u8 pad_00[0x3c];
    u32 unk_3C;
} Work;
extern Work data_021fd1bc;

typedef struct Player Player;
extern Player data_021fd1f8;

typedef struct {
    u8 pad_00[8];
    u8 unk_08;
    u8 pad_09;
    u8 unk_0A;
    u8 pad_0B[5];
    s8 unk_10;
    u8 pad_11;
    s16 unk_12;
} UnkStruct_020f9728;

void NNS_SndArcPlayerStartSeq(Player *p, int seq);
void NNS_SndPlayerReadGlobalVariable(int varIndex, s16 *value);
void NNS_SndPlayerReadVariable(Player *p, int varIndex, s16 *value);
void func_020f96b0(UnkStruct_020f9728 *self);

void func_020f9728(UnkStruct_020f9728 *self)
{
    unsigned int flag;
    s16 val, val2, val3;

    flag = (data_021fd1bc.unk_3C != 0) ? 1 : 0;
    if (flag != 0) {
        goto skip;
    }
    NNS_SndArcPlayerStartSeq(&data_021fd1f8, 0xf8);
skip:
    NNS_SndPlayerReadGlobalVariable(1, &val);
    NNS_SndPlayerReadGlobalVariable(2, &val2);
    NNS_SndPlayerReadVariable(&data_021fd1f8, 6, &val3);

    self->unk_0A = (val2 != self->unk_10) ? 1 : 0;
    self->unk_10 = (s8) val2;
    self->unk_12 = val3;

    if (self->unk_08 != 0) {
        return;
    }
    func_020f96b0(self);
}
