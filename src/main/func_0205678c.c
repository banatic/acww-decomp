/* func_0205678c @ 0x0205678c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0205678c_2 {
    void *unk_00;
    u8 pad0[0x1c];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
    u16 unk_24;
    u16 unk_26;
} UnkStruct_0205678c_2;

typedef struct UnkStruct_0205678c {
    u8 pad0[0x18];
    u8 *unk_18;
    u8 pad_1C[4];
    u8 *unk_20;
    u16 unk_24;
    u16 unk_26;
    UnkStruct_0205678c_2 *unk_28;
} UnkStruct_0205678c;

extern u8 *NNS_G3dGetAnmByIdx(void *a, int b);
extern u8 NNS_G3dGetResDictIdxByName(u8 *a, u8 *b);
extern void *NNSi_G3dGetTexPatAnmDataByIdx(u8 *hdr, int i);
extern void func_02056fcc(UnkStruct_0205678c *p, int n, u8 d, int e, int b);

void func_0205678c(UnkStruct_0205678c *p, void *res, int b, int n, u8 d, int e)
{
    u8 *base;
    u8 *q;
    int i;

    p->unk_20 = NNS_G3dGetAnmByIdx(res, 0);
    p->unk_24 = *(u16 *) (p->unk_20 + 4);
    if (n == 0) {
        n = p->unk_24;
    }
    base = p->unk_18 + *(int *) (p->unk_18 + 8);
    for (i = 0; i < p->unk_20[0xd]; i++) {
        q = p->unk_20 + 0xc;
        q = q + *(u16 *) (q + 6);
        p->unk_28[i].unk_22 = NNS_G3dGetResDictIdxByName(base + 4, q + *(u16 *) (q + 2) + (i << 4));
        p->unk_28[i].unk_00 = NNSi_G3dGetTexPatAnmDataByIdx(p->unk_20, i);
        p->unk_28[i].unk_21 = 0xff;
        p->unk_28[i].unk_20 = 0xff;
        p->unk_28[i].unk_24 = 0xffff;
    }
    func_02056fcc(p, n, d, e, b);
}
