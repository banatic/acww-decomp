/* func_020fded0 @ 0x020fded0, 0xd3c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef u16 GXRgb;

#define FX32_SHIFT 12
#define FX32_ONE 0x1000
#define FX32_HALF 0x800
#define FX32_DEC_MASK 0xfff
#define FX32_CONST(x) ((fx32) ((x) * 4096))

typedef struct {
    fx32 x, y, z;
} VecFx32;
typedef struct {
    fx16 x, y, z;
} VecFx16;

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

typedef struct SPLResourceFlags {
    u32 emissionType : 4;
    u32 drawType : 2;
    u32 circleAxis : 2;
    u32 hasScaleAnim : 1;
    u32 hasColorAnim : 1;
    u32 hasAlphaAnim : 1;
    u32 hasTexAnim : 1;
    u32 hasRotation : 1;
    u32 randomInitAngle : 1;
    u32 selfMaintaining : 1;
    u32 followEmitter : 1;
    u32 hasChildResource : 1;
    u32 polygonRotAxis : 2;
    u32 polygonReferencePlane : 1;
    u32 randomizeLoopedAnim : 1;
    u32 drawChildrenFirst : 1;
    u32 hideParent : 1;
    u32 useViewSpace : 1;
    u32 hasGravityBehavior : 1;
    u32 hasRandomBehavior : 1;
    u32 hasMagnetBehavior : 1;
    u32 hasSpinBehavior : 1;
    u32 hasCollisionPlaneBehavior : 1;
    u32 hasConvergenceBehavior : 1;
    u32 hasFixedPolygonID : 1;
    u32 childHasFixedPolygonID : 1;
} SPLResourceFlags;

typedef struct SPLResourceHeader {
    SPLResourceFlags flags;
    VecFx32 emitterBasePos;
    fx32 emissionCount;
    fx32 radius;
    fx32 length;
    VecFx16 axis;
    GXRgb color;
    fx32 initVelPosAmplifier;
    fx32 initVelAxisAmplifier;
    fx32 baseScale;
    fx16 aspectRatio;
    u16 startDelay;
    s16 minRotation;
    s16 maxRotation;
    u16 emitterLifeTime;
    u16 particleLifeTime;
    struct {
        u32 baseScale : 8;
        u32 lifeTime : 8;
        u32 initVel : 8;
        u32 reserved : 8;
    } randomAttenuation;
    struct {
        u32 emissionInterval : 8;
        u32 baseAlpha : 8;
        u32 airResistance : 8;
        u32 textureIndex : 8;
        u32 loopFrames : 8;
        u32 dbbScale : 16;
        u32 reserved2 : 8;
    } misc;
    fx16 polygonX;
    fx16 polygonY;
    u32 userData;
} SPLResourceHeader;

typedef struct SPLColorAnim {
    GXRgb start;
    GXRgb end;
    u32 curve;
    struct {
        u16 randomStartColor : 1;
        u16 loop : 1;
        u16 interpolate : 1;
        u16 reserved : 13;
    } flags;
    u16 pad_0A;
} SPLColorAnim;

typedef struct SPLTexAnim {
    u8 textures[8];
    struct {
        u32 frameCount : 8;
        u32 step : 8;
        u32 randomizeInit : 1;
        u32 loop : 1;
        u32 reserved : 14;
    } param;
} SPLTexAnim;

typedef struct SPLResource {
    SPLResourceHeader *header;
    void *scaleAnim;
    SPLColorAnim *colorAnim;
    void *alphaAnim;
    SPLTexAnim *texAnim;
    void *childResource;
    void *behaviors;
    u16 behaviorCount;
    u16 reserved;
} SPLResource;

typedef struct SPLEmitter {
    struct SPLEmitter *next;
    struct SPLEmitter *prev;
    SPLParticleList particles;
    SPLParticleList childParticles;
    SPLResource *resource;
    u32 state;
    VecFx32 position;
    VecFx32 velocity;
    u16 age;
    fx16 emissionCountFractional;
    VecFx16 axis;
    u16 initAngle;
    fx32 radius;
    fx32 length;
    fx32 initVelPositionAmplifier;
    fx32 initVelAxisAmplifier;
    fx32 baseScale;
    u16 particleLifeTime;
    GXRgb color;
    fx32 collisionPlaneHeight;
    fx16 textureS;
    fx16 textureT;
    fx16 childTextureS;
    fx16 childTextureT;
    struct {
        u32 emissionInterval : 8;
        u32 baseAlpha : 8;
        u32 updateCycle : 3;
        u32 reserved : 13;
    } misc;
    VecFx16 crossAxis1;
    VecFx16 crossAxis2;
    void (*updateCallback)(struct SPLEmitter *, int);
    void *userDataPtr;
    u32 userData;
} SPLEmitter;

extern u32 data_021fd278;
extern fx16 FX_SinCosTable_[];

extern SPLParticle *func_020ff8a8(SPLParticleList *list);
extern void func_020ff8ec(SPLParticleList *list, SPLParticle *ptcl);
extern void func_020ff994(VecFx32 *vec);
extern void func_020ff938(VecFx32 *vec);
extern void func_020fed6c(SPLEmitter *emtr);
extern void func_020fec0c(VecFx32 *ptclPos, VecFx32 *pos, SPLEmitter *emtr);
extern void VEC_Fx16CrossProduct(VecFx16 *a, VecFx16 *b, VecFx16 *out);
extern fx32 VEC_DotProduct(VecFx32 *a, VecFx32 *b);
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);

static __inline u32 SPLRandom_Next(void)
{
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    return data_021fd278;
}

static __inline u32 SPLRandom_U32(u32 bits)
{
    return SPLRandom_Next() >> (32 - bits);
}

static __inline s32 SPLRandom_S32(u32 bits)
{
    return (s32) (SPLRandom_Next() >> (32 - bits));
}

#define SPLRandom_ScaledRangeFX32(num, range) (((num) * (255 - (((range) * (fx32) SPLRandom_U32(8)) >> 8))) >> 8)
#define SPLRandom_DoubleScaledRangeFX32(num, range) ((num) * (255 + (range) - (((range) * (fx32) SPLRandom_U32(8)) >> 7)) >> 8)
#define SPLRandom_RangeFX32(num) (((num) * (s32) SPLRandom_U32(9) - ((num) << 8)) >> 8)
#define SPLRandom_BetweenFX32(min, max) ((fx32) (((max) - (min)) * SPLRandom_U32(12) + ((min) * FX32_ONE)))

static __inline fx16 FX_SinIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1)];
}

static __inline fx16 FX_CosIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1) + 1];
}

void func_020fded0(SPLEmitter *emtr, SPLParticleList *list)
{
    SPLResource *res = emtr->resource;
    SPLResourceHeader *header = res->header;
    int i = 0;
    int totalEmissions;
    fx32 magPos;
    fx32 magAxis;
    fx32 emission;
    fx32 zPoint;
    fx32 zBorder;
    fx32 zUniform;
    fx32 animScale;
    u32 rotation;
    u32 angularVel;
    u32 age;
    u32 lifeRate;
    int emitCountDec;
    int emitType;

    emitCountDec = header->emissionCount + emtr->emissionCountFractional;
    totalEmissions = emitCountDec >> FX32_SHIFT;
    emtr->emissionCountFractional = emitCountDec & FX32_DEC_MASK;

    emitType = header->flags.emissionType;
    if (emitType == 2 || emitType == 3 || emitType == 5 || emitType == 6 || emitType == 7 || emitType == 8 || emitType == 9) {
        func_020fed6c(emtr);
    }

    zPoint = 0;
    zBorder = 0;
    zUniform = 0;
    emission = 0;
    animScale = FX32_ONE;
    rotation = 0;
    angularVel = 0;
    age = 0;
    lifeRate = 0;

    for (i = 0; i < totalEmissions; i++) {
        SPLParticle *ptcl = func_020ff8a8(list);
        if (ptcl == 0) {
            return;
        }

        func_020ff8ec(&emtr->particles, ptcl);

        switch (header->flags.emissionType) {
            case 0:
                ptcl->position.z = zPoint;
                ptcl->position.y = ptcl->position.z;
                ptcl->position.x = ptcl->position.y;
                break;

            case 1:
                func_020ff994(&ptcl->position);
                ptcl->position.x = FX_MUL(ptcl->position.x, emtr->radius);
                ptcl->position.y = FX_MUL(ptcl->position.y, emtr->radius);
                ptcl->position.z = FX_MUL(ptcl->position.z, emtr->radius);
                break;

            case 2: {
                VecFx32 pos;
                func_020ff938(&pos);
                pos.x = FX_MUL(pos.x, emtr->radius);
                pos.y = FX_MUL(pos.y, emtr->radius);
                pos.z = zBorder;
                func_020fec0c(&ptcl->position, &pos, emtr);
            } break;

            case 3: {
                VecFx32 pos;
                fx32 sin;
                fx32 cos;
                int idx = (emission * FX32_CONST(16)) / totalEmissions;
                emission += 1;

                sin = FX_SinIdx(idx);
                cos = FX_CosIdx(idx);
                pos.x = FX_MUL(sin, emtr->radius);
                pos.y = FX_MUL(cos, emtr->radius);
                pos.z = zUniform;
                func_020fec0c(&ptcl->position, &pos, emtr);
            } break;

            case 4:
                func_020ff994(&ptcl->position);
                ptcl->position.x = FX_MUL(FX_MUL(ptcl->position.x, emtr->radius), SPLRandom_RangeFX32(FX32_ONE));
                ptcl->position.y = FX_MUL(FX_MUL(ptcl->position.y, emtr->radius), SPLRandom_RangeFX32(FX32_ONE));
                ptcl->position.z = FX_MUL(FX_MUL(ptcl->position.z, emtr->radius), SPLRandom_RangeFX32(FX32_ONE));
                break;

            case 5: {
                VecFx32 pos;
                func_020ff938(&pos);
                pos.x = FX_MUL(FX_MUL(pos.x, emtr->radius), SPLRandom_RangeFX32(FX32_ONE));
                pos.y = FX_MUL(FX_MUL(pos.y, emtr->radius), SPLRandom_RangeFX32(FX32_ONE));
                func_020fec0c(&ptcl->position, &pos, emtr);
            } break;

            case 8: {
                VecFx32 pos;
                VecFx16 vec;
                func_020ff994(&ptcl->position);
                VEC_Fx16CrossProduct(&emtr->crossAxis1, &emtr->crossAxis2, &vec);
                pos.x = vec.x;
                pos.y = vec.y;
                pos.z = vec.z;
                if (VEC_DotProduct(&pos, &ptcl->position) <= 0) {
                    ptcl->position.x = -ptcl->position.x;
                    ptcl->position.y = -ptcl->position.y;
                    ptcl->position.z = -ptcl->position.z;
                }

                ptcl->position.x = FX_MUL(ptcl->position.x, emtr->radius);
                ptcl->position.y = FX_MUL(ptcl->position.y, emtr->radius);
                ptcl->position.z = FX_MUL(ptcl->position.z, emtr->radius);
            } break;

            case 9: {
                VecFx32 pos;
                VecFx16 vec;
                func_020ff994(&ptcl->position);
                VEC_Fx16CrossProduct(&emtr->crossAxis1, &emtr->crossAxis2, &vec);
                pos.x = vec.x;
                pos.y = vec.y;
                pos.z = vec.z;
                if (VEC_DotProduct(&pos, &ptcl->position) < 0) {
                    ptcl->position.x = -ptcl->position.x;
                    ptcl->position.y = -ptcl->position.y;
                    ptcl->position.z = -ptcl->position.z;
                }

                ptcl->position.x =
                    FX_MUL(FX_MUL(ptcl->position.x, emtr->radius), (SPLRandom_RangeFX32(FX32_ONE) >> 1) + FX32_HALF);
                ptcl->position.y =
                    FX_MUL(FX_MUL(ptcl->position.y, emtr->radius), (SPLRandom_RangeFX32(FX32_ONE) >> 1) + FX32_HALF);
                ptcl->position.z =
                    FX_MUL(FX_MUL(ptcl->position.z, emtr->radius), (SPLRandom_RangeFX32(FX32_ONE) >> 1) + FX32_HALF);
            } break;

            case 6: {
                VecFx32 pos;
                func_020ff938(&ptcl->velocity);
                pos.x = FX_MUL(ptcl->velocity.x, emtr->radius);
                pos.y = FX_MUL(ptcl->velocity.y, emtr->radius);
                pos.z = SPLRandom_RangeFX32(emtr->length);
                func_020fec0c(&ptcl->position, &pos, emtr);
            } break;

            case 7: {
                VecFx32 pos;
                func_020ff938(&ptcl->velocity);
                pos.x = FX_MUL(FX_MUL(ptcl->velocity.x, emtr->radius), SPLRandom_RangeFX32(FX32_ONE));
                pos.y = FX_MUL(FX_MUL(ptcl->velocity.y, emtr->radius), SPLRandom_RangeFX32(FX32_ONE));
                pos.z = SPLRandom_RangeFX32(emtr->length);
                func_020fec0c(&ptcl->position, &pos, emtr);
            } break;
        }

        magPos = SPLRandom_DoubleScaledRangeFX32(emtr->initVelPositionAmplifier, header->randomAttenuation.initVel);
        magAxis = SPLRandom_DoubleScaledRangeFX32(emtr->initVelAxisAmplifier, header->randomAttenuation.initVel);

        {
            VecFx32 posNorm;
            if (header->flags.emissionType == 6) {
                VecFx32 tmp;
                tmp.x = FX_MUL(ptcl->velocity.x, emtr->crossAxis1.x) + FX_MUL(ptcl->velocity.y, emtr->crossAxis2.x);
                tmp.y = FX_MUL(ptcl->velocity.x, emtr->crossAxis1.y) + FX_MUL(ptcl->velocity.y, emtr->crossAxis2.y);
                tmp.z = FX_MUL(ptcl->velocity.x, emtr->crossAxis1.z) + FX_MUL(ptcl->velocity.y, emtr->crossAxis2.z);

                VEC_Normalize(&tmp, &posNorm);
            } else if (ptcl->position.x == 0 && ptcl->position.y == 0 && ptcl->position.z == 0) {
                func_020ff994(&posNorm);
            } else {
                VEC_Normalize(&ptcl->position, &posNorm);
            }

            ptcl->velocity.x = FX_MUL(posNorm.x, magPos) + FX_MUL(emtr->axis.x, magAxis);
            ptcl->velocity.y = FX_MUL(posNorm.y, magPos) + FX_MUL(emtr->axis.y, magAxis);
            ptcl->velocity.z = FX_MUL(posNorm.z, magPos) + FX_MUL(emtr->axis.z, magAxis);
        }

        ptcl->emitterPos = emtr->position;

        ptcl->baseScale = SPLRandom_DoubleScaledRangeFX32(emtr->baseScale, header->randomAttenuation.baseScale);
        ptcl->animScale = animScale;

        if (header->flags.hasColorAnim && res->colorAnim->flags.randomStartColor) {
            u16 clr[3];
            u32 index = SPLRandom_S32(12);
            clr[0] = res->colorAnim->start;
            clr[1] = header->color;
            clr[2] = res->colorAnim->end;
            ptcl->color = clr[index % 3];
        } else {
            ptcl->color = header->color;
        }

        ptcl->visibility.baseAlpha = emtr->misc.baseAlpha;
        ptcl->visibility.animAlpha = 31;

        if (header->flags.randomInitAngle) {
            ptcl->rotation = SPLRandom_S32(32);
        } else {
            ptcl->rotation = rotation;
        }

        if (header->flags.hasRotation) {
            ptcl->angularVelocity = (u32) SPLRandom_BetweenFX32(header->minRotation, header->maxRotation) >> FX32_SHIFT;
        } else {
            ptcl->angularVelocity = angularVel;
        }

        ptcl->lifeTime = SPLRandom_ScaledRangeFX32(emtr->particleLifeTime, header->randomAttenuation.lifeTime) + 1;
        ptcl->age = age;

        if (header->flags.hasTexAnim && res->texAnim->param.randomizeInit) {
            ptcl->texture = res->texAnim->textures[SPLRandom_U32(12) % res->texAnim->param.frameCount];
        } else if (header->flags.hasTexAnim && !res->texAnim->param.randomizeInit) {
            ptcl->texture = res->texAnim->textures[0];
        } else {
            ptcl->texture = header->misc.textureIndex;
        }

        ptcl->loopTimeFactor = 0xFFFF / res->header->misc.loopFrames;
        ptcl->lifeTimeFactor = 0xFFFF / ptcl->lifeTime;

        ptcl->lifeRateOffset = lifeRate;

        if (header->flags.randomizeLoopedAnim) {
            ptcl->lifeRateOffset = (u8) SPLRandom_S32(8);
        }
    }
}
