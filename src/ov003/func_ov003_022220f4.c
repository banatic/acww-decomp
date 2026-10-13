/* func_ov003_022220f4 @ 0x022220f4, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} VecFx32;

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx16 FX_SinCosTable_[];
extern void func_ov003_02222860(void *);

static __inline fx16 FX_SinIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1)];
}

typedef struct {
    char pad_00[0x18];
    VecFx32 pos; // 0x18
    fx32 unk_24;
    char pad_28[8];
    VecFx32 vel; // 0x30
    char pad_3C[0x12];
    unsigned short angle; // 0x4e
} UnkStruct_022220f4;

void func_ov003_022220f4(UnkStruct_022220f4 *self)
{
    VEC_Add(&self->pos, &self->vel, &self->pos);
    self->angle += 0x888;
    self->unk_24 = FX_SinIdx((unsigned short) (short) self->angle) >> 1;
    if (self->pos.y < 0) {
        self->pos.y = 0;
        self->vel.x = 0;
        self->vel.y = 0;
        self->vel.z = 0;
        func_ov003_02222860(self);
    }
}
