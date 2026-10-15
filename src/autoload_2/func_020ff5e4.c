/* func_020ff5e4 @ 0x020ff5e4, 0xd8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} VecFx32;
typedef struct {
    fx32 unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14, unk_18, unk_1C, unk_20;
} MtxFx33;

typedef struct SPLParticle {
    u8 pad_00[8];
    VecFx32 position;
} SPLParticle;

typedef struct SPLSpinBehavior {
    u16 angle;
    u16 axis;
} SPLSpinBehavior;

extern fx16 FX_SinCosTable_[];
extern void MTX_RotX33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotZ33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);

static __inline fx16 FX_SinIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1)];
}

static __inline fx16 FX_CosIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1) + 1];
}

void func_020ff5e4(SPLSpinBehavior *behavior, SPLParticle *ptcl, void *acceleration, void *emitter)
{
    MtxFx33 mtx;

    switch (behavior->axis) {
        case 0:
            MTX_RotX33_(&mtx, FX_SinIdx(behavior->angle), FX_CosIdx(behavior->angle));
            break;
        case 1:
            MTX_RotY33_(&mtx, FX_SinIdx(behavior->angle), FX_CosIdx(behavior->angle));
            break;
        case 2:
            MTX_RotZ33_(&mtx, FX_SinIdx(behavior->angle), FX_CosIdx(behavior->angle));
            break;
    }

    MTX_MultVec33(&ptcl->position, &mtx, &ptcl->position);
}
