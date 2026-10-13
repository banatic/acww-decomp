/* func_020fadf8 @ 0x020fadf8, 0x848 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef u16 GXRgb;

#define FX32_SHIFT 12
#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> FX32_SHIFT))

typedef struct {
    fx32 x, y, z;
} VecFx32;

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
    u32 f00 : 8;
    u32 hasScaleAnim : 1;
    u32 hasColorAnim : 1;
    u32 hasAlphaAnim : 1;
    u32 hasTexAnim : 1;
    u32 f12 : 3;
    u32 followEmitter : 1;
    u32 hasChildResource : 1;
    u32 f17 : 13;
    u32 fixedPolygonID : 1;
    u32 childFixedPolygonID : 1;
} SPLResourceFlags;

typedef struct SPLResourceHeader {
    SPLResourceFlags flags;
    u8 pad_04[0x34];
    u16 emitterLifeTime;
    u8 pad_3A[8];
    u8 airResistance;
} SPLResourceHeader;

typedef struct SPLScaleAnim {
    u8 pad_00[8];
    u16 loop : 1;
    u16 rest : 15;
} SPLScaleAnim;

typedef struct SPLColorAnim {
    u8 pad_00[8];
    u16 randomizeInit : 1;
    u16 loop : 1;
    u16 rest : 14;
} SPLColorAnim;

typedef struct SPLAlphaAnim {
    u8 pad_00[2];
    u16 randomRange : 8;
    u16 loop : 1;
    u16 rest : 7;
} SPLAlphaAnim;

typedef struct SPLTexAnim {
    u8 textures[8];
    u32 frameCount : 8;
    u32 step : 8;
    u32 randomizeInit : 1;
    u32 loop : 1;
    u32 rest : 14;
} SPLTexAnim;

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

struct SPLEmitter;
typedef struct SPLBehavior SPLBehavior;

typedef struct SPLBehaviorEntry {
    void (*func)(SPLBehavior *behavior, SPLParticle *ptcl, VecFx32 *acc, struct SPLEmitter *emtr);
    SPLBehavior *behavior;
} SPLBehaviorEntry;

typedef struct SPLResource {
    SPLResourceHeader *header;
    SPLScaleAnim *scaleAnim;
    SPLColorAnim *colorAnim;
    SPLAlphaAnim *alphaAnim;
    SPLTexAnim *texAnim;
    SPLChildResource *childResource;
    SPLBehaviorEntry *behaviors;
    u16 behaviorCount;
    u16 pad_1E;
} SPLResource;

typedef struct SPLEmitter {
    u8 pad_00[8];
    SPLParticleList particles;
    SPLParticleList childParticles;
    SPLResource *resource;
    struct {
        u32 b0 : 1;
        u32 b1 : 1;
        u32 b2 : 1;
        u32 b3 : 1;
        u32 emissionActive : 1;
        u32 rest : 27;
    } flags;
    VecFx32 position;
    VecFx32 velocity;
    u16 age;
    u8 pad_3A[0x2e];
    u8 emissionInterval;
    u8 pad_69[0xf];
    void (*callback)(struct SPLEmitter *emtr, u32 reason);
} SPLEmitter;

typedef struct SPLManager {
    u8 pad_00[0x14];
    SPLParticleList inactiveParticles;
    u8 pad_1C[0x10];
    struct {
        u32 polygonIDMin : 6;
        u32 polygonIDMax : 6;
        u32 polygonID : 6;
        u32 childPolygonID : 6;
        u32 rest : 8;
    } gfx;
} SPLManager;

typedef struct SPLAnimProc {
    void (*func)(SPLParticle *ptcl, SPLResource *res, s32 rate);
    s32 useLoopRate;
} SPLAnimProc;

extern void func_020ff3a4(SPLParticle *ptcl, SPLResource *res, s32 rate);
extern void func_020ff1d8(SPLParticle *ptcl, SPLResource *res, s32 rate);
extern void func_020ff0fc(SPLParticle *ptcl, SPLResource *res, s32 rate);
extern void func_020ff098(SPLParticle *ptcl, SPLResource *res, s32 rate);
extern void func_020ff04c(SPLParticle *ptcl, SPLResource *res, s32 rate);
extern void func_020feff4(SPLParticle *ptcl, SPLResource *res, s32 rate);

extern void func_020fded0(SPLEmitter *emtr, SPLParticleList *list);
extern void func_020fdc08(SPLParticle *ptcl, SPLEmitter *emtr, SPLParticleList *list);
extern SPLParticle *func_020ff83c(SPLParticleList *list, SPLParticle *ptcl);
extern void func_020ff8ec(SPLParticleList *list, SPLParticle *ptcl);

void func_020fadf8(SPLManager *mgr, SPLEmitter *emtr)
{
    SPLResource *res = emtr->resource;
    SPLParticle *ptcl;
    SPLParticle *next;
    s32 i;
    SPLChildResource *childRes = res->childResource;
    SPLResourceHeader *header = res->header;
    SPLResourceFlags flags = header->flags;
    s32 numProcs = 0;
    s32 airResistance = header->airResistance + 0x180;
    s32 numBehaviors = res->behaviorCount;
    u8 rate[2];
    SPLAnimProc procs[4];
    SPLAnimProc childProcs[4];
    VecFx32 acc;

    if (emtr->callback != 0) {
        emtr->callback(emtr, numProcs);
    }

    if (header->emitterLifeTime == 0 || emtr->age < header->emitterLifeTime) {
        if (emtr->age % emtr->emissionInterval == 0) {
            if (!emtr->flags.b0 && !emtr->flags.b1 && emtr->flags.emissionActive) {
                func_020fded0(emtr, &mgr->inactiveParticles);
            }
        }
    }

    if (flags.hasScaleAnim) {
        procs[numProcs].func = func_020ff3a4;
        procs[numProcs].useLoopRate = res->scaleAnim->loop;
        numProcs++;
    }
    if (flags.hasColorAnim && !res->colorAnim->randomizeInit) {
        procs[numProcs].func = func_020ff1d8;
        procs[numProcs++].useLoopRate = res->colorAnim->loop;
    }
    if (flags.hasAlphaAnim) {
        procs[numProcs].func = func_020ff0fc;
        procs[numProcs++].useLoopRate = res->alphaAnim->loop;
    }
    if (flags.hasTexAnim && !res->texAnim->randomizeInit) {
        procs[numProcs].func = func_020ff098;
        procs[numProcs].useLoopRate = res->texAnim->loop;
        numProcs++;
    }

    ptcl = emtr->particles.first;
    while (ptcl != 0) {
        next = ptcl->next;
        rate[0] = (ptcl->lifeTimeFactor * ptcl->age) >> 8;
        rate[1] = ptcl->lifeRateOffset + ((ptcl->loopTimeFactor * ptcl->age) >> 8);

        for (i = 0; i < numProcs; i++) {
            procs[i].func(ptcl, res, rate[procs[i].useLoopRate]);
        }

        acc.x = acc.y = acc.z = 0;

        if (flags.followEmitter) {
            ptcl->emitterPos = emtr->position;
        }

        for (i = 0; i < numBehaviors; i++) {
            res->behaviors[i].func(res->behaviors[i].behavior, ptcl, &acc, emtr);
        }

        ptcl->rotation += ptcl->angularVelocity;

        ptcl->velocity.x = (ptcl->velocity.x * airResistance) >> 9;
        ptcl->velocity.y = (ptcl->velocity.y * airResistance) >> 9;
        ptcl->velocity.z = (ptcl->velocity.z * airResistance) >> 9;

        ptcl->velocity.x += acc.x;
        ptcl->velocity.y += acc.y;
        ptcl->velocity.z += acc.z;

        ptcl->position.x += ptcl->velocity.x + emtr->velocity.x;
        ptcl->position.y += ptcl->velocity.y + emtr->velocity.y;
        ptcl->position.z += ptcl->velocity.z + emtr->velocity.z;

        if (flags.hasChildResource) {
            fx32 t =
                (ptcl->age << FX32_SHIFT) - (FX_MUL(ptcl->lifeTime << FX32_SHIFT, childRes->emissionDelay << FX32_SHIFT) >> 8);
            if (t >= 0) {
                if ((t >> FX32_SHIFT) % childRes->emissionInterval == 0) {
                    func_020fdc08(ptcl, emtr, &mgr->inactiveParticles);
                }
            }
        }

        if (emtr->resource->header->flags.fixedPolygonID) {
            ptcl->visibility.currentPolygonID = mgr->gfx.childPolygonID;
        } else {
            ptcl->visibility.currentPolygonID = mgr->gfx.polygonID;
            mgr->gfx.polygonID = mgr->gfx.polygonID + 1;
            if (mgr->gfx.polygonID > mgr->gfx.polygonIDMax) {
                mgr->gfx.polygonID = mgr->gfx.polygonIDMin;
            }
        }

        ptcl->age++;
        if (ptcl->age > ptcl->lifeTime) {
            func_020ff8ec(&mgr->inactiveParticles, func_020ff83c(&emtr->particles, ptcl));
        }

        ptcl = next;
    }

    if (flags.hasChildResource) {
        numProcs = 0;
        if (childRes->flags.hasScaleAnim) {
            childProcs[numProcs].func = func_020ff04c;
            childProcs[numProcs].useLoopRate = 0;
            numProcs++;
        }
        if (childRes->flags.hasAlphaAnim) {
            childProcs[numProcs].func = func_020feff4;
            childProcs[numProcs].useLoopRate = 0;
            numProcs++;
        }
        if (!childRes->flags.usesBehaviors) {
            numBehaviors = 0;
        }

        ptcl = emtr->childParticles.first;
        while (ptcl != 0) {
            next = ptcl->next;
            rate[0] = (ptcl->age << 8) / ptcl->lifeTime;

            for (i = 0; i < numProcs; i++) {
                childProcs[i].func(ptcl, res, rate[0]);
            }

            acc.x = acc.y = acc.z = 0;

            if (childRes->flags.followEmitter) {
                ptcl->emitterPos = emtr->position;
            }

            for (i = 0; i < numBehaviors; i++) {
                res->behaviors[i].func(res->behaviors[i].behavior, ptcl, &acc, emtr);
            }

            ptcl->rotation += ptcl->angularVelocity;

            ptcl->velocity.x = (ptcl->velocity.x * airResistance) >> 9;
            ptcl->velocity.y = (ptcl->velocity.y * airResistance) >> 9;
            ptcl->velocity.z = (ptcl->velocity.z * airResistance) >> 9;

            ptcl->velocity.x += acc.x;
            ptcl->velocity.y += acc.y;
            ptcl->velocity.z += acc.z;

            ptcl->position.x += ptcl->velocity.x + emtr->velocity.x;
            ptcl->position.y += ptcl->velocity.y + emtr->velocity.y;
            ptcl->position.z += ptcl->velocity.z + emtr->velocity.z;

            if (emtr->resource->header->flags.childFixedPolygonID) {
                ptcl->visibility.currentPolygonID = mgr->gfx.childPolygonID;
            } else {
                ptcl->visibility.currentPolygonID = mgr->gfx.polygonID;
                mgr->gfx.polygonID = mgr->gfx.polygonID + 1;
                if (mgr->gfx.polygonID > mgr->gfx.polygonIDMax) {
                    mgr->gfx.polygonID = mgr->gfx.polygonIDMin;
                }
            }

            ptcl->age++;
            if (ptcl->age > ptcl->lifeTime) {
                func_020ff8ec(&mgr->inactiveParticles, func_020ff83c(&emtr->childParticles, ptcl));
            }

            ptcl = next;
        }
    }

    emtr->age++;

    if (emtr->callback != 0) {
        emtr->callback(emtr, 1);
    }
}
