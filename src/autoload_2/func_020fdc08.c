/* func_020fdc08 @ 0x020fdc08, 0x2c8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef u16 GXRgb;

#define FX32_SHIFT 12
#define FX32_ONE 0x1000
#define FX32_CONST(x) ((fx32) ((x) * 4096))

typedef struct {
    fx32 x, y, z;
} VecFx32;

#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> FX32_SHIFT))

typedef struct SPLParticle {
    struct SPLParticle *next;
    struct SPLParticle *prev;
    VecFx32 position;
    VecFx32 velocity;
    u16 rotation;
    s16 angularVelocity;
    u16 lifeTime;
    u16 age;
    u16 loopTimeFactor;
    u16 lifeTimeFactor;
    u8 texture;
    u8 lifeRateOffset;
    struct {
        u16 baseAlpha : 5;
        u16 animAlpha : 5;
        u16 currentPolygonID : 6;
    } visibility;
    fx32 baseScale;
    fx16 animScale;
    GXRgb color;
    VecFx32 emitterPos;
} SPLParticle;

typedef struct SPLParticleList {
    SPLParticle *first;
    int count;
} SPLParticleList;

typedef struct SPLChildResource {
    struct {
        u16 usesBehaviors : 1;
        u16 hasScaleAnim : 1;
        u16 hasAlphaAnim : 1;
        u16 rotationType : 2;
        u16 followEmitter : 1;
        u16 useChildColor : 1;
        u16 drawType : 2;
        u16 polygonRotAxis : 2;
        u16 polygonReferencePlane : 1;
        u16 reserved : 4;
    } flags;
    fx16 randomInitVelMag;
    fx16 endScale;
    u16 lifeTime;
    u8 velocityRatio;
    u8 scaleRatio;
    GXRgb color;
    u8 emissionCount;
    u8 emissionDelay;
    u8 emissionInterval;
    u8 texture;
} SPLChildResource;

typedef struct SPLResource {
    u8 pad_00[0x14];
    SPLChildResource *childResource;
} SPLResource;

typedef struct SPLEmitter {
    u8 pad_00[0x10];
    SPLParticleList childParticles;
    SPLResource *resource;
} SPLEmitter;

extern u32 data_021fd278;
extern SPLParticle *func_020ff8a8(SPLParticleList *list);
extern void func_020ff8ec(SPLParticleList *list, SPLParticle *ptcl);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);

static __inline u32 SPLRandom_Next(void)
{
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    return data_021fd278;
}

static __inline u32 SPLRandom_U32(u32 bits)
{
    return SPLRandom_Next() >> (32 - bits);
}

#define SPLRandom_RangeFX32(num) (((num) * (s32) SPLRandom_U32(9) - ((num) << 8)) >> 8)

void func_020fdc08(SPLParticle *ptcl, SPLEmitter *emtr, SPLParticleList *list)
{
    SPLParticle *child;
    SPLChildResource *childRes = emtr->resource->childResource;
    int i;
    fx32 velRatio;
    fx32 v;
    fx32 sc;
    fx32 denom = FX32_CONST(255);
    fx32 animScale = FX32_ONE;
    u32 rotation = 0;
    u32 angularVel = 0;
    u32 age = 0;
    u32 lifeRate = 0;

    for (i = 0; i < childRes->emissionCount; i++) {
        child = func_020ff8a8(list);
        if (child == 0) {
            return;
        }

        func_020ff8ec(&emtr->childParticles, child);

        child->position = ptcl->position;

        velRatio = FX_Div(childRes->velocityRatio * FX32_ONE, denom);
        v = FX_MUL(ptcl->velocity.x, velRatio);
        child->velocity.x = v + SPLRandom_RangeFX32(childRes->randomInitVelMag);
        v = FX_MUL(ptcl->velocity.y, velRatio);
        child->velocity.y = v + SPLRandom_RangeFX32(childRes->randomInitVelMag);
        v = FX_MUL(ptcl->velocity.z, velRatio);
        child->velocity.z = v + SPLRandom_RangeFX32(childRes->randomInitVelMag);

        child->emitterPos = ptcl->emitterPos;

        sc = (ptcl->baseScale * ptcl->animScale) >> FX32_SHIFT;
        child->baseScale = (sc * (childRes->scaleRatio + 1)) >> 6;
        child->animScale = animScale;

        if (childRes->flags.useChildColor) {
            child->color = childRes->color;
        } else {
            child->color = ptcl->color;
        }

        child->visibility.baseAlpha = (ptcl->visibility.baseAlpha * (ptcl->visibility.animAlpha + 1)) >> 5;
        child->visibility.animAlpha = 31;

        switch (childRes->flags.rotationType) {
            case 0:
                child->rotation = rotation;
                child->angularVelocity = rotation;
                break;
            case 1:
                child->rotation = ptcl->rotation;
                child->angularVelocity = angularVel;
                break;
            case 2:
                child->rotation = ptcl->rotation;
                child->angularVelocity = ptcl->angularVelocity;
                break;
        }

        child->lifeTime = childRes->lifeTime;
        child->age = age;
        child->texture = childRes->texture;
        child->loopTimeFactor = 0xFFFF / (ptcl->lifeTime / 2);
        child->lifeTimeFactor = 0xFFFF / ptcl->lifeTime;
        child->lifeRateOffset = lifeRate;
    }
}
