/* func_020922b4 @ 0x020922b4, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020922b4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020922b4;

typedef struct UnkStruct_020922b4_2 {
    char pad0[0x18];
    UnkStruct_020922b4 **unk_18;
    char pad_1C[0x20 - 0x1c];
    int unk_20;
    int unk_24;
    int unk_28;
    char pad_2C[0x44 - 0x2c];
    int unk_44;
    char pad_48[4];
    int unk_4C;
    char pad_50[4];
    int unk_54;
} UnkStruct_020922b4_2;

typedef struct UnkStruct_020922b4_3 {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[0x10 - 0xc];
    s16 unk_10;
} UnkStruct_020922b4_3;

extern UnkStruct_020922b4_3 data_021d5658;
extern int FX_Div(int num, int den);
extern int FX_MulFunc(int a, int b);
extern void func_02090db0(UnkStruct_020922b4_2 *s);

void func_020922b4(UnkStruct_020922b4_2 *s)
{
    UnkStruct_020922b4_3 *g;
    int ang;
    int t;
    int u;
    int x;
    int z;
    int y;

    g = &data_021d5658;
    ang = g->unk_10;
    if (ang < 0xc00) {
        t = FX_Div(ang - 0x600, 0x600);
        x = (s16) ((s16) FX_MulFunc(0x266, t) + 0x266);
        z = (s16) ((s16) FX_MulFunc(0x400, t) + 0x400);
        y = (s16) ((s16) FX_MulFunc(0x52, t) + 0xcd);
    } else {
        u = FX_Div(ang - 0xc00, 0xc00);
        x = (s16) ((s16) FX_MulFunc(0x800, u) + 0x4cd);
        z = (s16) ((s16) FX_MulFunc(0x4cd, u) + 0x800);
        y = (s16) ((s16) FX_MulFunc(0x52, u) + 0x11f);
    }
    s->unk_44 = x;
    s->unk_4C = y;
    s->unk_54 = z;
    s->unk_20 = g->unk_00 + (*s->unk_18)->unk_04;
    s->unk_24 = g->unk_04 + (*s->unk_18)->unk_08;
    s->unk_28 = g->unk_08 + (*s->unk_18)->unk_0C;
    func_02090db0(s);
}
