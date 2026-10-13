/* func_020574c4 @ 0x020574c4, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[0x78 - 0xc];
    u8 *unk_78;
    u32 unk_7C;
} UnkStruct_020574c4;

extern void *NNSi_G3dGetTexPatAnmFV(u32, u32, u32);
extern int NNSi_G3dGetTexPatAnmTexNameByIdx(u32, u8);
extern int NNSi_G3dGetTexPatAnmPlttNameByIdx(u32, u8);
extern int NNS_G3dGetResDictIdxByName(u8 *, int);

void func_020574c4(UnkStruct_020574c4 *s, int *out2, int *out1)
{
    u8 *v;
    int a, b, x, x2;

    *out1 = -1;
    *out2 = *out1;
    v = NNSi_G3dGetTexPatAnmFV(s->unk_7C, 0, (s->unk_08 << 4) >> 16);
    if (v != 0) {
        a = NNSi_G3dGetTexPatAnmTexNameByIdx(s->unk_7C, v[2]);
        b = NNSi_G3dGetTexPatAnmPlttNameByIdx(s->unk_7C, v[3]);
        if (a != 0) {
            x = NNS_G3dGetResDictIdxByName(s->unk_78 + 0x3c, a);
        } else {
            x = -1;
        }
        *out2 = x;
        {
            u8 *addr = s->unk_78 + *(u16 *) (s->unk_78 + 0x34);
            if (b != 0) {
                x2 = NNS_G3dGetResDictIdxByName(addr, b);
            } else {
                x2 = -1;
            }
            *out1 = x2;
        }
    }
}
