/* particle_system_4: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020fb640 @ 0x020fb640, 0x2a4 bytes, ARM
 * func_020fadf8 @ 0x020fadf8, 0x848 bytes, ARM
 * func_020fad1c @ 0x020fad1c, 0xdc bytes, ARM
 * func_020fac60 @ 0x020fac60, 0xbc bytes, ARM
 * func_020fabe8 @ 0x020fabe8, 0x78 bytes, ARM
 */

#include "types.h"

#define FX32_SHIFT 12
#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> FX32_SHIFT))

struct UnkStruct_020fb640_2 {
    u16 a;
    u16 b;
    u16 c;
};

struct UnkStruct_020fb640_3 {
    u32 b0_lo : 16;
    u32 b0_t : 1;
    u32 b0_hi : 15;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    struct UnkStruct_020fb640_2 unk_1C;
    u16 unk_22;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    u16 unk_38;
    u16 unk_3A;
    int unk_3C;
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
    u32 f44_lo : 24;
    u32 f44_a : 2;
    u32 f44_b : 2;
    u32 f44_hi : 4;
    u32 f48_x : 1;
    u32 f48_y : 1;
    u32 f48_hi : 30;
};

struct UnkStruct_020fb640_5 {
    char pad[0x10];
    u32 f10_a : 2;
    u32 f10_b : 2;
    u32 f10_c : 1;
    u32 f10_d : 1;
    u32 f10_hi : 26;
};

struct UnkStruct_020fb640_4 {
    struct UnkStruct_020fb640_3 *hdr;
    char pad[0x14 - 4];
    struct UnkStruct_020fb640_5 *sub;
};

struct UnkStruct_020fb640 {
    int x;
    int y;
    int z;
};

union U68 {
    u32 w;
    struct {
        u8 a;
        u8 b;
    } c;
};

struct UnkStruct_020fb640_6 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    struct UnkStruct_020fb640_4 *unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    short unk_38;
    short unk_3A;
    struct UnkStruct_020fb640_2 unk_3C;
    short unk_42;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    int unk_54;
    short unk_58;
    short unk_5A;
    int unk_5C;
    short unk_60;
    short unk_62;
    short unk_64;
    short unk_66;
    union U68 unk_68;
    char pad_6C[0x78 - 0x6c];
    int unk_78;
    int unk_7C;
    int unk_80;
};

typedef u16 GXRgb;

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

typedef struct VecFx32_020fad1c {
    int x, y, z;
} VecFx32_020fad1c;

typedef int (*SPLDrawCallback)(VecFx32_020fad1c *, VecFx32_020fad1c);

typedef struct SPLManager_020fad1c SPLManager_020fad1c;

typedef struct SPLEmitter_020fad1c SPLEmitter_020fad1c;

typedef struct SPLResource_020fad1c SPLResource_020fad1c;

typedef struct SPLHeader SPLHeader;

typedef struct SPLTexture SPLTexture;

typedef struct SPLParticle_020fad1c SPLParticle_020fad1c;

typedef void (*ParticleDraw)(SPLManager_020fad1c *self, SPLParticle_020fad1c *node, SPLDrawCallback arg2);

typedef void (*TextureBind)(SPLTexture *elem);

struct SPLParticle_020fad1c {
    SPLParticle_020fad1c *next;
    unsigned char pad0[0x28];
    unsigned char byte;
};

struct SPLHeader {
    unsigned int low : 4;
    unsigned int mode : 2;
    unsigned int mid : 5;
    unsigned int flag : 1;
    unsigned int high : 20;
    unsigned char pad0[0x3f];
    unsigned char byte;
};

struct SPLResource_020fad1c {
    SPLHeader *r;
};

struct SPLEmitter_020fad1c {
    unsigned char pad0[0x8];
    SPLParticle_020fad1c *list;
    unsigned char pad1[0xc];
    SPLResource_020fad1c *c;
};

struct SPLTexture {
    unsigned char data[0x14];
};

struct SPLManager_020fad1c {
    unsigned char pad0[0x20];
    SPLTexture *base;
    unsigned char pad1[0x10];
    SPLEmitter_020fad1c *b;
};

typedef struct UnkStruct_020fac60 UnkStruct_020fac60;

typedef struct UnkStruct_020fac60_2 UnkStruct_020fac60_2;

typedef struct UnkStruct_020fac60_3 UnkStruct_020fac60_3;

typedef struct UnkStruct_020fac60_4 UnkStruct_020fac60_4;

typedef struct UnkStruct_020fac60_5 UnkStruct_020fac60_5;

typedef struct UnkStruct_020fac60_6 UnkStruct_020fac60_6;

typedef struct Node Node;

typedef void (*Callback)(UnkStruct_020fac60 *self, Node *node, void *arg2);

struct Node {
    Node *next;
};

struct UnkStruct_020fac60_4 {
    unsigned int lower : 16;
    unsigned int bit16 : 1;
    unsigned int upper : 15;
};

struct UnkStruct_020fac60_5 {
    unsigned short lower : 7;
    unsigned short mode : 2;
    unsigned short upper : 7;
    unsigned char pad[0xd];
    unsigned char byte;
};

struct UnkStruct_020fac60_3 {
    UnkStruct_020fac60_4 *d;
    unsigned char pad[0x10];
    UnkStruct_020fac60_5 *e;
};

struct UnkStruct_020fac60_2 {
    unsigned char pad_00[0x10];
    Node *list;
    unsigned char pad1[0x4];
    UnkStruct_020fac60_3 *c;
};

struct UnkStruct_020fac60_6 {
    unsigned char data[0x14];
};

struct UnkStruct_020fac60 {
    unsigned char pad_00[0x20];
    UnkStruct_020fac60_6 *base;
    unsigned char pad1[0x10];
    UnkStruct_020fac60_2 *b;
};

typedef struct Flags {
    unsigned : 21;
    unsigned bit21 : 1;
    unsigned bit22 : 1;
} Flags;

typedef struct UnkStruct_020fabe8 {
    Flags *flags;
} UnkStruct_020fabe8;

typedef struct Mid {
    char pad_00[0x18];
    UnkStruct_020fabe8 *inner;
} Mid;

typedef struct UnkStruct_020fabe8_2 {
    char pad_00[0x34];
    Mid *mid;
} UnkStruct_020fabe8_2;

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
extern void func_020fb8e8(SPLTexture *elem);
extern void func_020fb8e4(SPLTexture *elem);
extern void func_020fd4e0(SPLManager_020fad1c *self, SPLParticle_020fad1c *node, SPLDrawCallback arg2);
extern void func_020fc8c4(SPLManager_020fad1c *self, SPLParticle_020fad1c *node, SPLDrawCallback arg2);
extern void func_020fbda4(SPLManager_020fad1c *self, SPLParticle_020fad1c *node, SPLDrawCallback arg2);
extern void func_020fd01c(UnkStruct_020fac60 *self, Node *node, void *arg2);
extern void func_020fc174(UnkStruct_020fac60 *self, Node *node, void *arg2);
extern void func_020fb9d4(UnkStruct_020fac60 *self, Node *node, void *arg2);

void func_020fb640(struct UnkStruct_020fb640_6 *p, struct UnkStruct_020fb640_4 *a, struct UnkStruct_020fb640 *b)
{
    p->unk_18 = a;
    p->unk_1C = 0;
    p->unk_20 = b->x + p->unk_18->hdr->unk_04;
    p->unk_24 = b->y + p->unk_18->hdr->unk_08;
    p->unk_28 = b->z + p->unk_18->hdr->unk_0C;
    p->unk_2C = p->unk_30 = p->unk_34 = 0;
    p->unk_38 = 0;
    p->unk_3A = 0;
    p->unk_3C = p->unk_18->hdr->unk_1C;
    p->unk_42 = 0;
    p->unk_44 = p->unk_18->hdr->unk_14;
    p->unk_48 = p->unk_18->hdr->unk_18;
    p->unk_4C = p->unk_18->hdr->unk_24;
    p->unk_50 = p->unk_18->hdr->unk_28;
    p->unk_54 = p->unk_18->hdr->unk_2C;
    p->unk_58 = p->unk_18->hdr->unk_3A;
    p->unk_5A = 0x7fff;
    p->unk_68.c.a = p->unk_18->hdr->unk_40;
    p->unk_68.c.b = p->unk_18->hdr->unk_41;
    p->unk_68.w &= ~0x70000;
    p->unk_68.w &= 0x7ffff;
    p->unk_5C = (int) 0x80000000;
    p->unk_60 = (short) (0x1000 << p->unk_18->hdr->f44_a);
    p->unk_62 = (short) (0x1000 << p->unk_18->hdr->f44_b);
    if (p->unk_18->hdr->f48_x) {
        p->unk_60 *= -1;
    }
    if (p->unk_18->hdr->f48_y) {
        p->unk_62 *= -1;
    }
    if (p->unk_18->hdr->b0_t) {
        p->unk_64 = (short) (0x1000 << p->unk_18->sub->f10_a);
        p->unk_66 = (short) (0x1000 << p->unk_18->sub->f10_b);
        if (p->unk_18->sub->f10_c) {
            p->unk_64 *= -1;
        }
        if (p->unk_18->sub->f10_d) {
            p->unk_66 *= -1;
        }
    }
    p->unk_00 = p->unk_04 = 0;
    p->unk_08 = p->unk_10 = 0;
    p->unk_0C = p->unk_14 = 0;
    p->unk_78 = 0;
    p->unk_7C = 0;
    p->unk_80 = 0;
}

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

void func_020fad1c(SPLManager_020fad1c *self, SPLDrawCallback arg2)
{
    SPLEmitter_020fad1c *b;
    SPLHeader *r;
    SPLParticle_020fad1c *node;
    int idx;
    TextureBind emit;
    ParticleDraw cb = 0;

    b = self->b;
    r = b->c->r;
    idx = r->byte;
    func_020fb8e8(&self->base[idx]);
    switch (r->mode) {
        case 0:
            cb = func_020fd4e0;
            break;
        case 1:
            cb = func_020fc8c4;
            break;
        case 2:
            cb = func_020fbda4;
            break;
        default:
            break;
    }
    emit = r->flag ? func_020fb8e8 : func_020fb8e4;
    node = b->list;
    if (node != 0) {
        do {
            emit(&self->base[node->byte]);
            cb(self, node, arg2);
            node = node->next;
        } while (node != 0);
    }
}

void func_020fac60(UnkStruct_020fac60 *self, void *arg2)
{
    UnkStruct_020fac60_2 *b;
    UnkStruct_020fac60_3 *c;
    UnkStruct_020fac60_5 *e;
    Node *node;
    int idx;
    Callback cb = 0;

    b = self->b;
    c = b->c;
    if (!c->d->bit16) {
        return;
    }
    e = c->e;
    idx = e->byte;
    func_020fb8e8((SPLTexture *) (&self->base[idx]));
    e = c->e;
    switch (e->mode) {
        case 0:
            cb = func_020fd01c;
            break;
        case 1:
            cb = func_020fc174;
            break;
        case 2:
            cb = func_020fb9d4;
            break;
        default:
            break;
    }
    node = b->list;
    if (node != 0) {
        do {
            cb(self, node, arg2);
            node = node->next;
        } while (node != 0);
    }
}

void func_020fabe8(void *a, void *b)
{
    Flags *fp;

    fp = ((UnkStruct_020fabe8_2 *) a)->mid->inner->flags;

    if (fp->bit21) {
        func_020fac60((UnkStruct_020fac60 *) a, b);
        if (fp->bit22) {
            return;
        }
        func_020fad1c((SPLManager_020fad1c *) a, (SPLDrawCallback) b);
    } else {
        if (!fp->bit22) {
            func_020fad1c((SPLManager_020fad1c *) a, (SPLDrawCallback) b);
        }
        func_020fac60((UnkStruct_020fac60 *) a, b);
    }
}
