/* func_ov003_02221f50 @ 0x02221f50, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y;
} UnkStruct_02221f50;

extern void func_0204f794(void *, int, int);
extern fx16 FX_SinCosTable_[];
extern void func_ov003_02224140(int, int, int, int);

static __inline fx16 FX_SinIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1)];
}
static __inline fx16 FX_CosIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1) + 1];
}

typedef struct {
    char pad_00[0x30];
    fx32 unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
    char pad_48[0x58];
    unsigned char unk_A0;
} UnkStruct_02221f50_2;

void func_ov003_02221f50(UnkStruct_02221f50_2 *self, UnkStruct_02221f50 *p, int a)
{
    func_0204f794((char *) self + 0x18, p->x, p->y);
    self->unk_30 = (FX_SinIdx((unsigned short) a) * 0x400) >> 12;
    self->unk_34 = 0x1000;
    self->unk_38 = (FX_CosIdx((unsigned short) a) * 0x400) >> 12;
    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;
    self->unk_A0 = 0;
    func_ov003_02224140(p->x, p->y, 0xfff1, 0);
}
