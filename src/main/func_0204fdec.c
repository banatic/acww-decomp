/* func_0204fdec @ 0x0204fdec, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct Entry {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x48];
    u32 unk_8C;
    u32 unk_90;
    u32 unk_94;
    char pad_98[0xb8];
    u32 unk_150;
    u32 unk_154;
    u32 unk_158;
    s16 unk_15C[3];
    char pad_162[2];
    u32 unk_164;
    u8 unk_168;
    u8 unk_169;
};

struct Src {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
};

struct UnkStruct_0204fdec {
    char pad_00[0x10];
    s16 s0;
    s16 u0;
    s16 s1;
    s16 u1;
    s16 s2;
    s16 u2;
    u8 b0;
    char p0;
    char p1;
    char p2;
    u8 b1;
    char q0;
    char q1;
    char q2;
    u32 w0;
};

extern unsigned char *data_021c8184;
extern int data_020dcd78;
extern void func_0205007c(struct Entry *dst, struct Src *src);

int func_0204fdec(int x, int y, struct Src *src, struct Src *src2)
{
    struct Entry *e;
    struct Src in[1];
    struct Src *d;
    struct UnkStruct_0204fdec *out;
    int r = 0;
    if (data_021c8184 != 0 && x >= 0 && x < data_020dcd78 && y >= 0 && y < 0x3c) {
        e = (struct Entry *) (data_021c8184 + 0x50 + x * 0x16c);
        e->unk_40 = y;
        d = (struct Src *) ((char *) e + 0x8c);
        d->unk_00 = src->unk_00;
        d->unk_04 = src->unk_04;
        d->unk_08 = src->unk_08;
        in[0].unk_00 = src2->unk_00;
        in[0].unk_04 = src2->unk_04;
        in[0].unk_08 = src2->unk_08;
        func_0205007c(e, &in[0]);
        out = (struct UnkStruct_0204fdec *) &in[1];
        e->unk_15C[0] = out->s0;
        e->unk_15C[1] = out->s1;
        e->unk_15C[2] = out->s2;
        e->unk_168 = out->b0;
        {
            u8 *bp = (u8 *) &in[3];
            e->unk_169 = *bp;
        }
        e->unk_164 = in[3].unk_04;
        r = 1;
    }
    return r;
}
