/* func_0200ec4c @ 0x0200ec4c, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200ec4c {
    unsigned char pad_00[0x12c];
    int unk_12C;
    unsigned char pad_130[0x7d7 - 0x130];
    u8 unk_7D7;
    unsigned char pad_7D8[0x7dc - 0x7d8];
    u8 unk_7DC;
    unsigned char pad_7DD[0x81c - 0x7dd];
    int unk_81C;
} UnkStruct_0200ec4c;

typedef struct Other {
    unsigned char pad_00[0x248];
    int unk_248;
} Other;

typedef struct Blk {
    int w[0x28 / 4];
} Blk;

extern Other *data_021c526c;

extern void func_0206844c(int h, u8 *p, int k);
extern void *func_02062f90(Blk *out, u16 *src);
extern void func_020683b4(int h, int k, Blk *b, int n);
extern void *func_02062f4c(Blk *b);

void func_0200ec4c(UnkStruct_0200ec4c *self)
{
    struct {
        u8 b[6];
        u16 h6;
        u16 h8;
    } m;
    Blk big1;
    Blk big2;
    int v;

    v = self->unk_81C;
    if (v >= 0xf) {
        return;
    }
    switch (v) {
        case 0:
            m.b[0] = 0x3d;
            func_0206844c(self->unk_12C, &m.b[0], 0);
            break;
        case 4:
            m.b[1] = 0x3e;
            func_0206844c(self->unk_12C, &m.b[1], 0);
            break;
        case 2:
            m.b[2] = 3;
            func_0206844c(self->unk_12C, &m.b[2], 0);
            break;
        case 1:
            m.b[3] = 0x3c;
            func_0206844c(self->unk_12C, &m.b[3], 0);
            self->unk_81C = 9;
            break;
        case 5:
        case 6:
            data_021c526c->unk_248 = 0xb;
            break;
        case 13:
            m.b[4] = 0x3f;
            func_0206844c(self->unk_12C, &m.b[4], 0);
            m.h6 = (u16) (self->unk_7DC + 0x12b0);
            func_02062f90(&big1, &m.h6);
            func_020683b4(self->unk_12C, 0, &big1, 7);
            func_02062f4c(&big1);
            self->unk_81C = 8;
            break;
        case 14:
            m.b[5] = 0x3f;
            func_0206844c(self->unk_12C, &m.b[5], 0);
            self->unk_81C = 8;
            m.h8 = (u16) (self->unk_7D7 + 0x12e8);
            func_02062f90(&big2, &m.h8);
            func_020683b4(self->unk_12C, 0, &big2, 7);
            func_02062f4c(&big2);
            break;
    }
}
