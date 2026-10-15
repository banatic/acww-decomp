/* func_020f9c0c @ 0x020f9c0c, 0xf4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u32 flag;
    u16 pad_04;
    u16 packed;
    u8 pad_08;
    u8 unk_09;
    u8 unk_0A;
} Player;

extern int NNS_SndPlayerReadVariable(Player *player, int varNo, s16 *var);

void func_020f9c0c(Player *player)
{
    unsigned int flag;
    s16 val;
    s16 val2;
    s16 vars[4];
    int i;
    int shift;

    flag = (player->flag != 0) ? 1 : 0;
    if (flag == 0) {
        return;
    }

    NNS_SndPlayerReadVariable(player, 0, &val);
    NNS_SndPlayerReadVariable(player, 1, &vars[0]);
    NNS_SndPlayerReadVariable(player, 2, &vars[1]);
    NNS_SndPlayerReadVariable(player, 3, &vars[2]);
    NNS_SndPlayerReadVariable(player, 4, &vars[3]);
    NNS_SndPlayerReadVariable(player, 5, &val2);

    player->unk_09 = (u8) val;
    player->unk_0A = (u8) val2;

    if (vars[0] < 0) {
        return;
    }

    for (i = 0, shift = 0; i < 4; i++, shift += 4) {
        player->packed |= vars[3 - i] << shift;
    }
}
