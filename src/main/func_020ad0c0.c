/* func_020ad0c0 @ 0x020ad0c0, 0x118 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020ad0c0 {
    u8 pad_00[0xc];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[8];
} UnkStruct_020ad0c0;

typedef struct UnkStruct_020ad0c0_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned int unk_14;
    int unk_18;
    int *unk_1C;
    int unk_20;
    int unk_24;
    int *unk_28;
    int *unk_2C;
    UnkStruct_020ad0c0 *unk_30;
} UnkStruct_020ad0c0_2;

extern UnkStruct_020ad0c0 data_021f49a0[];
extern void *data_021fbe94;

extern void *func_020e9948(void *, int);
extern int FX_MulFunc(int, int);
extern int FX_Div(int, int);

int func_020ad0c0(UnkStruct_020ad0c0_2 *p, int *src, int v2, int v3, int a5, int a6, int a7, void *a8)
{
    unsigned int i;
    int *q;
    int *r;
    int t;
    unsigned int n;

    if (a8 == 0) {
        a8 = data_021fbe94;
    }
    p->unk_30 = &data_021f49a0[a5];
    p->unk_00 = src[0];
    p->unk_04 = src[1];
    p->unk_08 = src[2];
    p->unk_0C = v2 >> 1;
    t = p->unk_0C;
    if ((t >> v3) == 0) {
        t = v3;
    }
    p->unk_10 = t;
    p->unk_18 = 0;
    p->unk_14 = (v3 - 0x200) / 0x2000 + 2;
    n = p->unk_14 * 4;
    p->unk_1C = (int *) func_020e9948(a8, n * 2 + p->unk_14 * 0xc);
    p->unk_28 = (int *) ((u8 *) p->unk_1C + n);
    p->unk_2C = (int *) ((u8 *) p->unk_28 + n);
    for (i = 0; i < p->unk_14; i++) {
        if (i == p->unk_14 - 1) {
            p->unk_1C[i] = v3;
        } else {
            p->unk_1C[i] = i << 13;
        }
    }
    if (a6 == 0 && a7 == 0) {
        p->unk_20 = 0;
        p->unk_24 = p->unk_30->unk_0C << 12;
    } else {
        p->unk_20 = FX_MulFunc(p->unk_30->unk_0C << 12, a6);
        p->unk_24 = FX_MulFunc(p->unk_30->unk_0C << 12, a7);
    }
    q = p->unk_1C;
    r = p->unk_28;
    for (i = 0; i < p->unk_14; i++) {
        *r++ = FX_MulFunc(0x1000 - FX_Div(*q, v3), p->unk_30->unk_0E << 12);
        q++;
    }
    return 1;
}
