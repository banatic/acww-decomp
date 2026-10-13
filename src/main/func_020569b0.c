/* func_020569b0 @ 0x020569b0, 0x86 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020569b0 {
    int unk_00;
    int unk_04;
    u8 pad_08[0x20 - 8];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 pad_23;
    u16 unk_24;
};

extern int NNS_G3dGetResDictIdxByName(void *a, void *b);
extern void func_02056968(struct UnkStruct_020569b0 *s, int a, int b);

void func_020569b0(struct UnkStruct_020569b0 *a, unsigned int b, unsigned char *c, int d, int e)
{
    u8 i;
    unsigned char *p;
    int w0m1;
    u16 w0;
    u8 ret;

    if (a->unk_22 == 0xff) {
        return;
    }
    if (b == a->unk_24) {
        return;
    }
    a->unk_24 = (u16) b;

    p = c + *(u16 *) ((int) a->unk_00 + 6);
    i = 0;
    w0 = *(u16 *) (int) a->unk_00;
    w0m1 = w0 - 1;
    while (i < w0m1) {
        if (*(u16 *) (p + 4) > b) {
            break;
        }
        p += 4;
        i = (u8) (i + 1);
    }

    if (a->unk_21 == i) {
        return;
    }
    a->unk_21 = i;

    ret = (u8) NNS_G3dGetResDictIdxByName((void *) (d + 0x3c), c + *(u16 *) (c + 8) + (p[2] << 4));
    if (ret == a->unk_20) {
        return;
    }
    a->unk_20 = ret;

    func_02056968(a, e, d);
}
