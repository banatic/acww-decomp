/* particle_system_2: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020fa9f4 @ 0x020fa9f4, 0x178 bytes, ARM
 * func_020fa820 @ 0x020fa820, 0x1d4 bytes, ARM
 * func_020fa564 @ 0x020fa564, 0x2bc bytes, ARM
 * func_020fa498 @ 0x020fa498, 0xcc bytes, ARM
 * func_020fa3e4 @ 0x020fa3e4, 0xb4 bytes, ARM
 */

#include "types.h"

typedef void *(*Alloc)(unsigned int);

struct Mgr {
    Alloc alloc;
    unsigned int l1h, l1t;
    unsigned int l2h, l2t;
    unsigned int l3h, l3t;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned short unk_24;
    unsigned short unk_26;
    unsigned short unk_28;
    unsigned short unk_2A;
    unsigned int q0 : 6;
    unsigned int q1 : 6;
    unsigned int q2 : 6;
    unsigned int q3 : 6;
    unsigned int b2f : 8;
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
};

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

typedef struct SPLTextureParam {
    u32 fmt : 4;
    u32 s : 4;
    u32 t : 4;
    u32 rest : 20;
} SPLTextureParam;

typedef struct SPLTextureResource {
    u32 magic;
    SPLTextureParam param;
    u8 pad_08[0x14];
    u32 resourceSize;
} SPLTextureResource;

typedef struct SPLTexture {
    const SPLTextureResource *resource;
    u8 pad_04[8];
    SPLTextureParam param;
    u16 width;
    u16 height;
} SPLTexture;

typedef void *(*Alloc_020fa820)(u32);

typedef struct SPLManager {
    Alloc_020fa820 alloc;
    u8 pad_04[0x1c];
    SPLTexture *textures;
    u16 resCount;
    u16 texCount;
} SPLManager;

typedef struct SPLFileHeader {
    u32 magic;
    u32 version;
    u16 resCount;
    u16 texCount;
    u8 pad_0C[0x14];
} SPLFileHeader;

typedef struct SPLResHeader {
    struct {
        u32 pad0 : 8;
        u32 hasA : 1; // bit 8
        u32 hasB : 1; // bit 9
        u32 hasC : 1; // bit 10
        u32 hasD : 1; // bit 11
        u32 pad1 : 4;
        u32 hasE : 1; // bit 16
        u32 pad2 : 7;
        u32 beh0 : 1; // bit 24
        u32 beh1 : 1;
        u32 beh2 : 1;
        u32 beh3 : 1;
        u32 beh4 : 1;
        u32 beh5 : 1; // bit 29
        u32 pad3 : 2;
    } flags;
} SPLResHeader;

typedef void (*SPLBehaviorFn)(void *, void *, void *, void *);

typedef struct SPLBehavior {
    SPLBehaviorFn fn;
    void *data;
} SPLBehavior;

typedef struct SPLResource {
    SPLResHeader *header;   // 0x00
    void *a;                // 0x04
    void *b;                // 0x08
    void *c;                // 0x0c
    void *d;                // 0x10
    void *e;                // 0x14
    SPLBehavior *behaviors; // 0x18
    u16 behaviorCount;      // 0x1c
    u16 pad_1E;
} SPLResource;

typedef struct SPLManager_020fa564 {
    void *(*alloc)(u32 size); // 0x00
    u8 pad_04[0x1c - 4];
    SPLResource *resources; // 0x1c
    u8 pad_20[0x24 - 0x20];
    u16 resourceCount; // 0x24
} SPLManager_020fa564;

typedef struct {
    u32 unk_00;
    unsigned int type : 4;
    unsigned int : 13;
    unsigned int cached : 1;
    unsigned int cacheIndex : 8;
    unsigned int : 6;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
} UnkStruct_020fa498;

typedef struct {
    UnkStruct_020fa498 *p;
    u32 result;
    char pad[0xc];
} Entry;

typedef struct {
    char pad[0x20];
    Entry *entries;
    char pad_24[2];
    u16 count;
} UnkStruct_020fa498_2;

struct UnkStruct_020fa3e4 {
    unsigned int unk_00;
    unsigned int type : 4;
    unsigned int : 28;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
};

struct Entry {
    struct UnkStruct_020fa3e4 *p;
    unsigned int pad_04;
    unsigned int result;
    unsigned int pad_0C;
    unsigned int pad_10;
};

struct UnkStruct_020fa3e4_2 {
    char pad_00[0x20];
    struct Entry *entries;
    char pad_24[2];
    unsigned short count;
};

extern void MI_CpuFill8(void *, int, unsigned int);
extern void func_020ff8ec(unsigned int *, void *);
extern void func_020ff808(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff740(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff6bc(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff5e4(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff4c8(void *behavior, void *particle, void *acceleration, void *emitter);
extern void func_020ff434(void *behavior, void *particle, void *acceleration, void *emitter);
extern void GX_BeginLoadTex(void);
extern void GX_EndLoadTex(void);
extern void GX_LoadTex(const void *pSrc, u32 destSlotAddr, u32 szByte);
extern void GX_BeginLoadTexPltt(void);
extern void GX_EndLoadTexPltt(void);
extern void GX_LoadTexPltt(const void *pData, unsigned int format, unsigned int size);

// SPL manager setup: allocates the manager and fills the emitter and resource free lists.
// b2f is a bitfield so that it packs into the byte at 0x2F.
struct Mgr *func_020fa9f4(Alloc alloc, int a, int b, int c, unsigned short d, unsigned short e)
{
    struct Mgr *m;
    int i;
    char *p;

    m = (struct Mgr *) alloc(0x3c);
    MI_CpuFill8(m, 0, 0x3c);
    m->unk_28 = (unsigned short) a;
    m->unk_2A = (unsigned short) b;
    m->q0 = d;
    m->q1 = e;
    m->q2 = m->q0;
    m->q3 = c;
    m->b2f = 0;
    m->alloc = alloc;
    m->l1t = 0;
    m->l2t = 0;
    m->l3t = 0;
    m->l1h = 0;
    m->l2h = 0;
    m->l3h = 0;
    m->unk_30 = 0;
    p = (char *) alloc(a * 0x84);
    MI_CpuFill8(p, 0, a * 0x84);
    for (i = 0; i < a; i++) {
        func_020ff8ec(&m->l2h, p);
        p += 0x84;
    }
    p = (char *) alloc(b * 0x44);
    MI_CpuFill8(p, 0, b * 0x44);
    for (i = 0; i < b; i++) {
        func_020ff8ec(&m->l3h, p);
        p += 0x44;
    }
    m->unk_1C = 0;
    m->unk_20 = 0;
    m->unk_26 = 0;
    m->unk_24 = m->unk_26;
    return m;
}

void func_020fa820(SPLManager *mgr, const SPLFileHeader *file)
{
    int i;
    int j;
    u32 offset;
    u32 n;
    SPLResourceFlags flags;
    const SPLTextureResource *tex;

    mgr->resCount = file->resCount;
    mgr->texCount = file->texCount;
    offset = sizeof(SPLFileHeader);

    for (i = 0; i < mgr->resCount; i++) {
        flags = *(const SPLResourceFlags *) ((const u8 *) file + offset);
        offset += 0x54;
        if (flags.hasScaleAnim) {
            offset += 0xc;
        }
        if (flags.hasColorAnim) {
            offset += 0xc;
        }
        if (flags.hasAlphaAnim) {
            offset += 8;
        }
        if (flags.hasTexAnim) {
            offset += 0xc;
        }
        if (flags.hasChildResource) {
            offset += 0x14;
        }

        n = flags.hasGravityBehavior + flags.hasRandomBehavior + flags.hasMagnetBehavior + flags.hasSpinBehavior +
            flags.hasCollisionPlaneBehavior + flags.hasConvergenceBehavior;
        if (n != 0) {
            if (flags.hasGravityBehavior) {
                offset += 8;
            }
            if (flags.hasRandomBehavior) {
                offset += 8;
            }
            if (flags.hasMagnetBehavior) {
                offset += 0x10;
            }
            if (flags.hasSpinBehavior) {
                offset += 4;
            }
            if (flags.hasCollisionPlaneBehavior) {
                offset += 8;
            }
            if (flags.hasConvergenceBehavior) {
                offset += 0x10;
            }
        }
    }

    mgr->textures = (SPLTexture *) mgr->alloc(mgr->texCount * sizeof(SPLTexture));
    MI_CpuFill8(mgr->textures, 0, mgr->texCount * sizeof(SPLTexture));

    for (i = 0; i < mgr->texCount; i++) {
        SPLTexture *texture = &mgr->textures[i];
        const SPLTextureResource *texRes = (const SPLTextureResource *) ((const u8 *) file + offset);
        texture->resource = texRes;
        texture->width = (u16) (1 << (texRes->param.s + 3));
        texture->height = (u16) (1 << (texRes->param.t + 3));
        texture->param = texRes->param;
        offset += texRes->resourceSize;
    }
}

void func_020fa564(SPLManager_020fa564 *mgr, u8 *base)
{
    int i;
    u32 off;
    SPLResource *res;
    SPLResHeader h;
    SPLBehavior *p;

    off = 0;
    mgr->resources = mgr->alloc(mgr->resourceCount * sizeof(SPLResource));
    MI_CpuFill8(mgr->resources, 0, mgr->resourceCount * sizeof(SPLResource));

    for (i = 0; i < mgr->resourceCount; i++) {
        res = &mgr->resources[i];
        res->header = (SPLResHeader *) (base + off);
        h = *res->header;
        off += 0x54;

        if (h.flags.hasA) {
            res->a = base + off;
            off += 0xc;
        } else {
            res->a = 0;
        }
        if (h.flags.hasB) {
            res->b = base + off;
            off += 0xc;
        } else {
            res->b = 0;
        }
        if (h.flags.hasC) {
            res->c = base + off;
            off += 8;
        } else {
            res->c = 0;
        }
        if (h.flags.hasD) {
            res->d = base + off;
            off += 0xc;
        } else {
            res->d = 0;
        }
        if (h.flags.hasE) {
            res->e = base + off;
            off += 0x14;
        } else {
            res->e = 0;
        }

        res->behaviorCount = (u16) (h.flags.beh0 + h.flags.beh1 + h.flags.beh2 + h.flags.beh3 + h.flags.beh4 + h.flags.beh5);

        if (res->behaviorCount != 0) {
            res->behaviors = mgr->alloc(res->behaviorCount * sizeof(SPLBehavior));
            p = res->behaviors;
            if (h.flags.beh0) {
                p->data = base + off;
                p->fn = func_020ff808;
                off += 8;
                p++;
            }
            if (h.flags.beh1) {
                p->data = base + off;
                p->fn = func_020ff740;
                off += 8;
                p++;
            }
            if (h.flags.beh2) {
                p->data = base + off;
                p->fn = func_020ff6bc;
                off += 0x10;
                p++;
            }
            if (h.flags.beh3) {
                p->data = base + off;
                p->fn = func_020ff5e4;
                off += 4;
                p++;
            }
            if (h.flags.beh4) {
                p->data = base + off;
                p->fn = func_020ff4c8;
                off += 8;
                p++;
            }
            if (h.flags.beh5) {
                p->data = base + off;
                p->fn = func_020ff434;
                off += 0x10;
            }
        } else {
            res->behaviors = 0;
        }
    }
}

int func_020fa498(UnkStruct_020fa498_2 *self, u32 (*callback)(u32, int))
{
    int i;
    u32 zero = 0;
    u32 one = 1;

    GX_BeginLoadTex();

    for (i = 0; i < self->count; i++) {
        Entry *e = &self->entries[i];
        UnkStruct_020fa498 *p = e->p;

        if (p->cached) {
            u32 idx = p->cacheIndex;
            e->result = self->entries[idx].result;
        } else {
            u32 arg = (p->type == 5) ? one : zero;
            u32 dest = callback(p->unk_08, arg);
            GX_LoadTex((char *) e->p + 0x20, dest, p->unk_08);
            e->result = dest;
        }
    }

    GX_EndLoadTex();
    return 1;
}

int func_020fa3e4(struct UnkStruct_020fa3e4_2 *self, int (*callback)(unsigned int, int))
{
    int i;
    int one = 1;

    GX_BeginLoadTexPltt();

    for (i = 0; i < self->count; i++) {
        struct Entry *e = &self->entries[i];
        struct UnkStruct_020fa3e4 *p = e->p;
        int value = 0;

        if (p->unk_10 != 0) {
            int arg = (p->type == 2) ? one : 0;
            value = callback(p->unk_10, arg);
            GX_LoadTexPltt((char *) e->p + p->unk_0C, value, p->unk_10);
        }

        e->result = value;
    }

    GX_EndLoadTexPltt();
    return 1;
}
