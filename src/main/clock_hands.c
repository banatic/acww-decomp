/* clock_hands: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b3220 @ 0x020b3220, 0xf0 bytes, Thumb
 * func_020b3188 @ 0x020b3188, 0x98 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 unk_00, unk_01, unk_02, unk_03;
} UnkStruct_020b3220;

typedef struct {
    int m[9];
} M33;

typedef struct {
    int flags;
} UnkStruct_020b3220_2;

typedef struct {
    char pad_00[0xb4];
    UnkStruct_020b3220_2 *h;
} UnkStruct_020b3220_3;

typedef struct {
    int m[9];
} Mtx33;

typedef struct Node {
    unsigned int flags;
    char pad_04[0x28 - 4];
    Mtx33 mtx;
} Node;

typedef struct UnkStruct_020b3188 {
    char pad_00[0xb4];
    Node *node;
} UnkStruct_020b3188;

extern int data_021f4b30;
extern int data_021fbdd0;
extern int data_021f4b34;
extern int data_020e50d0;
extern short FX_SinCosTable_[];
extern void func_0209def4(UnkStruct_020b3220 *b);
extern int FX_Div(int a, int b);
extern void MTX_RotZ33_(M33 *m, int s, int c);
extern void MTX_Concat33(M33 *d, M33 *a, M33 *b);

void func_020b3220(UnkStruct_020b3220_3 *self)
{
    UnkStruct_020b3220 v;
    M33 mtx;
    M33 *dst;
    int a, b, j;

    dst = (M33 *) ((char *) self->h + 0x28);
    func_0209def4(&v);
    if (data_021f4b30 != data_021fbdd0) {
        a = (short) -((FX_Div((v.unk_01 % 12) << 12, 0xc000) * 0xffff) >> 12);
        b = (short) ((FX_Div(v.unk_00 << 12, 0x3c000) * 0x1555) >> 12);
        j = ((u16) (short) (a - b) >> 4) * 2;
        data_021f4b34 = FX_SinCosTable_[j];
        data_020e50d0 = FX_SinCosTable_[j + 1];
        data_021f4b30 = data_021fbdd0;
    }
    MTX_RotZ33_(&mtx, data_021f4b34, data_020e50d0);
    if ((self->h->flags & 2) != 0) {
        *dst = mtx;
    } else {
        MTX_Concat33(dst, &mtx, dst);
    }
    self->h->flags &= ~2;
}

void func_020b3188(UnkStruct_020b3188 *self)
{
    u8 buf[4];
    Mtx33 m;
    Mtx33 *dst;
    int d, ang, idx;

    dst = &self->node->mtx;
    func_0209def4((UnkStruct_020b3220 *) buf);
    d = FX_Div((buf[0] % 0x3c) << 12, 0x0003c000);
    ang = -((0xffff * d) >> 12);
    idx = ((unsigned short) (short) ang >> 4) * 2;
    MTX_RotZ33_((M33 *) (&m), FX_SinCosTable_[idx], FX_SinCosTable_[idx + 1]);
    if ((self->node->flags & 2) != 0) {
        *dst = m;
    } else {
        MTX_Concat33((M33 *) dst, (M33 *) (&m), (M33 *) dst);
    }
    self->node->flags &= ~2;
}
