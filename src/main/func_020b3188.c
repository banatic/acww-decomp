/* func_020b3188 @ 0x020b3188, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern void func_0209def4(void *);
extern int FX_Div(int, int);
extern void MTX_RotZ33_(Mtx33 *, int, int);
extern void MTX_Concat33(Mtx33 *, Mtx33 *, Mtx33 *);
extern short FX_SinCosTable_[];

void func_020b3188(UnkStruct_020b3188 *self)
{
    u8 buf[4];
    Mtx33 m;
    Mtx33 *dst;
    int d, ang, idx;

    dst = &self->node->mtx;
    func_0209def4(buf);
    d = FX_Div((buf[0] % 0x3c) << 12, 0x0003c000);
    ang = -((0xffff * d) >> 12);
    idx = ((unsigned short) (short) ang >> 4) * 2;
    MTX_RotZ33_(&m, FX_SinCosTable_[idx], FX_SinCosTable_[idx + 1]);
    if ((self->node->flags & 2) != 0) {
        *dst = m;
    } else {
        MTX_Concat33(dst, &m, dst);
    }
    self->node->flags &= ~2;
}
