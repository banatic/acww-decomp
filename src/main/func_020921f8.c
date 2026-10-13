/* func_020921f8 @ 0x020921f8, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct UnkStruct_020921f8 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020921f8;

typedef struct UnkStruct_020921f8_2 {
    char pad0[0x18];
    UnkStruct_020921f8 **unk_18;
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
    char pad_58[4];
    int unk_5C;
} UnkStruct_020921f8_2;

typedef struct UnkStruct_020921f8_3 {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[0x10 - 0xc];
    s16 unk_10;
} UnkStruct_020921f8_3;

extern UnkStruct_020921f8_3 data_021d5658;
extern int FX_Div(int num, int den);
extern int FX_MulFunc(int a, int b);
extern void func_02090db0(UnkStruct_020921f8_2 *s);

void func_020921f8(UnkStruct_020921f8_2 *s)
{
    int ang;
    int t;
    int x;
    int z;
    int y;
    volatile int w0;
    volatile int w4;
    volatile int w8;

    ang = data_021d5658.unk_10;
    w0 = data_021d5658.unk_00;
    w4 = data_021d5658.unk_04;
    w8 = data_021d5658.unk_08;
    t = FX_Div(ang - 0xC00, 0xC00);
    x = (s16) ((s16) FX_MulFunc(0x4CD, t) + 0xB33);
    z = (s16) ((s16) FX_MulFunc(0x19A, t) + 0x400);
    y = (s16) ((s16) FX_MulFunc(0x19A, t) + 0x333);
    s->unk_44 = x;
    s->unk_4C = y;
    s->unk_54 = z;
    s->unk_20 = w0 + (*s->unk_18)->unk_04;
    s->unk_24 = w4 + (*s->unk_18)->unk_08;
    s->unk_28 = w8 + (*s->unk_18)->unk_0C;
    s->unk_5C = 0x99A;
    func_02090db0(s);
}