/* func_020c0f8c @ 0x020c0f8c, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x24];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    u16 unk_54;
    char pad_56[2];
    int unk_58;
} UnkStruct_020c0f8c;

extern int func_020644cc(int);
extern int func_020e8ed8(int a, int b);
extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern void func_020bf220(UnkStruct_020c0f8c *p, int a, int b);
extern unsigned char data_021fba88[];

void func_020c0f8c(UnkStruct_020c0f8c *p)
{
    int dx;
    int dy;
    int a;
    int idx;
    int s;
    int c;

    p->unk_4C = 0x1000;
    p->unk_50 = 0x800;
    if (func_020644cc(2) == 0) {
        dx = (func_020644cc(0x3c) + 0xc4) << 12;
        dy = 0;
    } else {
        dx = 0x00100000;
        dy = func_020644cc(0x30) << 12;
    }
    a = func_020e8ed8(((func_020644cc(0x17) + 0x80) << 12) - dy, -dx);
    idx = ((unsigned short) a >> 4) << 1;
    s = FX_SinCosTable_[idx];
    c = FX_SinCosTable_[idx + 1];
    dx = dx - 0x23 * c;
    dy = dy - 0x23 * s;
    p->unk_34 = dx;
    p->unk_38 = dy;
    p->unk_3C = 0;
    p->unk_40 = FX_MulFunc(c, 0x7800);
    p->unk_44 = FX_MulFunc(s, 0x7800);
    p->unk_48 = 0;
    p->unk_54 = (u16) (a - 0x4000);
    p->unk_0C = 0x11;
    p->unk_58 = 3;
    data_021fba88[0x10] = 0;
    func_020bf220(p, 6, 0x801);
}
