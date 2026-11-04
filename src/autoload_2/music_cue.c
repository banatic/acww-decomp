/* music_cue: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f9c0c @ 0x020f9c0c, 0xf4 bytes, ARM
 * func_020f9b50 @ 0x020f9b50, 0xbc bytes, ARM
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

typedef struct UnkStruct_020f9b50 UnkStruct_020f9b50;

typedef struct UnkStruct_020f9b50_2 UnkStruct_020f9b50_2;

struct UnkStruct_020f9b50 {
    unsigned char pad_00[0x16];
    short unk_16;
};

struct UnkStruct_020f9b50_2 {
    unsigned char pad_00[0x38];
    unsigned short unk_38;
};

typedef struct {
    unsigned char pad_00[0x2c];
    UnkStruct_020f9b50 *pA;
    unsigned char pad_30[0x3c - 0x30];
    UnkStruct_020f9b50_2 *pB;
} Global;

extern int NNS_SndPlayerReadVariable(Player *player, int varNo, s16 *var);
extern Global data_021fd1bc;
extern int func_020f5e50(void *p, int n);
extern int func_020f5e24(int);
extern int func_020f5c64(void *p, int n);
extern void NNS_SndPlayerSetVolume(void *p, int vol);
extern void func_0210b634(void *p, int a, int b);
extern int FX_Div(int a, int b);
extern void func_0210b604(void *p, int b);

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

void func_020f9b50(void *a, void *b)
{
    int r6, r5;
    int r1v;
    int shifted, res;
    UnkStruct_020f9b50_2 *pB;
    unsigned int flag;

    if (b == 0) {
        return;
    }

    r6 = func_020f5e24(func_020f5e50(b, 0));
    r5 = func_020f5c64(b, 0);

    NNS_SndPlayerSetVolume(a, r6);
    func_0210b634(a, 0xf, r5);

    if (data_021fd1bc.pA == 0) {
        return;
    }

    shifted = data_021fd1bc.pA->unk_16 << 20;
    res = FX_Div(shifted, 0x78000);
    r1v = res >> 12;

    pB = data_021fd1bc.pB;
    flag = (pB != 0);
    if (flag == 0) {
        return;
    }

    if (pB->unk_38 == 0xf0) {
        r1v >>= 1;
    }

    func_0210b604(a, r1v);
}
