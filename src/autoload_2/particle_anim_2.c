/* particle_anim_2: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ff5e4 @ 0x020ff5e4, 0xd8 bytes, ARM
 * func_020ff4c8 @ 0x020ff4c8, 0x11c bytes, ARM
 */

#include "types.h"

#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> 12))

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

typedef struct SPLParticle_020ff4c8 {
    u8 pad_00[8];
    VecFx32 position;
    VecFx32 velocity;
    u8 pad_20[4];
    u16 lifeTime;
    u16 age;
    u8 pad_28[0x10];
    VecFx32 emitterPos;
} SPLParticle_020ff4c8;

typedef struct SPLEmitter {
    u8 pad_00[0x5c];
    fx32 collisionPlaneHeight;
} SPLEmitter;

typedef struct SPLCollisionPlaneBehavior {
    fx32 y;
    fx16 elasticity;
    struct {
        u16 collisionType : 2;
        u16 reserved : 14;
    } flags;
} SPLCollisionPlaneBehavior;

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

void func_020ff4c8(SPLCollisionPlaneBehavior *behavior, SPLParticle_020ff4c8 *ptcl, VecFx32 *velocity, SPLEmitter *emtr)
{
    fx32 y = behavior->y;

    if (emtr->collisionPlaneHeight != (fx32) 0x80000000) {
        y = emtr->collisionPlaneHeight;
    }

    switch (behavior->flags.collisionType) {
        case 0:
            if (ptcl->emitterPos.y < y && ptcl->emitterPos.y + ptcl->position.y > y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->age = ptcl->lifeTime;
            } else if (ptcl->emitterPos.y >= y && ptcl->emitterPos.y + ptcl->position.y < y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->age = ptcl->lifeTime;
            }
            break;

        case 1:
            if (ptcl->emitterPos.y < y && ptcl->emitterPos.y + ptcl->position.y > y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->velocity.y = -FX_MUL(ptcl->velocity.y, behavior->elasticity);
            } else if (ptcl->emitterPos.y >= y && ptcl->emitterPos.y + ptcl->position.y < y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->velocity.y = -FX_MUL(ptcl->velocity.y, behavior->elasticity);
            }
            break;
    }
}
