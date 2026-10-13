/* func_020fbda4 @ 0x020fbda4, 0x3d0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef s32 fx32;
typedef s16 fx16;
typedef u16 GXRgb;
typedef volatile u32 vu32;

#define FX32_SHIFT 12
#define FX32_HALF 0x800

#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + FX32_HALF) >> FX32_SHIFT))

typedef struct {
    fx32 x, y, z;
} VecFx32;
typedef struct {
    fx32 unk_00, unk_04, unk_08;
    fx32 unk_0C, unk_10, unk_14;
    fx32 unk_18, unk_1C, unk_20;
    fx32 unk_24, unk_28, unk_2C;
} MtxFx43;

extern fx16 FX_SinCosTable_[];
#define FX_SinIdx(idx) ((fx16) FX_SinCosTable_[((idx) >> 4) << 1])
#define FX_CosIdx(idx) ((fx16) FX_SinCosTable_[(((idx) >> 4) << 1) + 1])

#define reg_G3_MTX_IDENTITY (*(vu32 *) 0x04000454)
#define reg_G3_MTX_TRANS (*(vu32 *) 0x04000470)
#define reg_G3_COLOR (*(vu32 *) 0x04000480)
#define reg_G3_POLYGON_ATTR (*(vu32 *) 0x040004a4)

static __inline void G3_Identity(void)
{
    reg_G3_MTX_IDENTITY = 0;
}
static __inline void G3_Translate(fx32 x, fx32 y, fx32 z)
{
    reg_G3_MTX_TRANS = (u32) x;
    reg_G3_MTX_TRANS = (u32) y;
    reg_G3_MTX_TRANS = (u32) z;
}
static __inline void G3_Color(GXRgb rgb)
{
    reg_G3_COLOR = (u32) rgb;
}

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

typedef struct SPLResourceHeader {
    struct {
        u32 pad0a : 17;
        u32 rotType : 2;  // bits [17:18], drives gRotMtxTable
        u32 quadType : 1; // bit 19, drives gQuadEmitTable
        u32 pad0b : 3;
        u32 useViewSpace : 1;
        u32 pad1 : 8;
    } flags;
    VecFx32 emitterBasePos; // 0x04
    u8 pad_10[0x30 - 0x10];
    fx16 aspectRatio; // 0x30
    u8 pad_32[0x44 - 0x32];
    struct {
        u32 pad0 : 8;
        u32 dbbScale : 16;
        u32 pad1 : 4;
        u32 scaleAnimDir : 3;
        u32 pad2 : 1;
    } misc; // 0x44
    u8 pad_48[0x4c - 0x44 - 4];
    fx16 polygonX; // 0x4c
    fx16 polygonY; // 0x4e
    u8 miscFlags;  // 0x50
} SPLResourceHeader;

typedef struct SPLResource {
    SPLResourceHeader *header;
} SPLResource;

typedef struct SPLEmitter {
    u8 pad0[0x18];
    SPLResource *resource; // 0x18
    u8 pad_1C[0x5a - 0x1c];
    GXRgb color; // 0x5a
    u8 pad_5C[0x60 - 0x5c];
    fx16 textureS;      // 0x60
    fx16 textureT;      // 0x62
    fx16 childTextureS; // 0x64
    fx16 childTextureT; // 0x66
} SPLEmitter;

typedef struct SPLManager {
    u8 pad0[0x30];
    u32 miscPolygonAttr;       // 0x30
    SPLEmitter *emitter;       // 0x34
    const MtxFx43 *viewMatrix; // 0x38
} SPLManager;

typedef fx32 (*SPLDrawCallback)(VecFx32 *p, VecFx32 v);
typedef void (*RotMtxFn)(fx32 sinVal, fx32 cosVal, MtxFx43 *dst);
typedef void (*QuadEmitFn)(fx32 s, fx32 t, fx32 x, fx32 y);

extern RotMtxFn data_0213f268[4];   // 0x0213f268
extern QuadEmitFn data_0213f260[2]; // 0x0213f260

extern void MTX_Scale43_(MtxFx43 *pDst, fx32 x, fx32 y, fx32 z);
extern void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);
extern void MTX_RotX43_(MtxFx43 *mtx, fx32 sinVal, fx32 cosVal);
extern void G3_MultMtx43(const MtxFx43 *m);
extern void G3_LoadMtx43(const MtxFx43 *m);

static __inline void SPLi_SetPolygonAttr(SPLManager *mgr, u32 bits, u32 polygonID, u32 alpha)
{
    reg_G3_POLYGON_ATTR = (mgr->miscPolygonAttr | bits) | (polygonID << 24) | (alpha << 16);
    reg_G3_POLYGON_ATTR;
}

void func_020fbda4(SPLManager *mgr, SPLParticle *ptcl, SPLDrawCallback cb)
{
    MtxFx43 mtx;
    MtxFx43 rotMtx;
    MtxFx43 scaleMtx;
    VecFx32 trs;
    MtxFx43 tiltMtx;
    fx32 sx, sy;
    fx32 sinVal, cosVal;
    fx32 angle;
    s32 alpha;

    alpha = (ptcl->visibility.baseAlpha * (ptcl->visibility.animAlpha + 1)) >> 5;
    SPLi_SetPolygonAttr(mgr, 0xc0, ptcl->visibility.currentPolygonID, alpha);
    if (alpha == 0) {
        return;
    }

    sinVal = FX_SinIdx(ptcl->rotation);
    cosVal = FX_CosIdx(ptcl->rotation);
    data_0213f268[mgr->emitter->resource->header->flags.rotType](sinVal, cosVal, &rotMtx);

    sx = FX_MUL(ptcl->baseScale, mgr->emitter->resource->header->aspectRatio);
    sy = ptcl->baseScale;
    switch (mgr->emitter->resource->header->misc.scaleAnimDir) {
        case 0:
            sx = FX_MUL(sx, ptcl->animScale);
            sy = FX_MUL(sy, ptcl->animScale);
            break;
        case 1:
            sx = FX_MUL(sx, ptcl->animScale);
            break;
        case 2:
            sy = FX_MUL(sy, ptcl->animScale);
            break;
    }

    MTX_Scale43_(&scaleMtx, sx, sy, sy);
    MTX_Concat43(&scaleMtx, &rotMtx, &mtx);

    if (!mgr->emitter->resource->header->flags.useViewSpace) {
        trs.x = ptcl->position.x + ptcl->emitterPos.x;
        trs.y = ptcl->position.y + ptcl->emitterPos.y;
        trs.z = ptcl->position.z + ptcl->emitterPos.z;
        angle = cb(&trs, trs);
        G3_LoadMtx43(mgr->viewMatrix);
    } else {
        trs.x = ptcl->position.x + ptcl->emitterPos.x - mgr->emitter->resource->header->emitterBasePos.x;
        trs.y = ptcl->position.y + ptcl->emitterPos.y - mgr->emitter->resource->header->emitterBasePos.y;
        trs.z = ptcl->position.z + ptcl->emitterPos.z - mgr->emitter->resource->header->emitterBasePos.z;
        angle = cb(&trs, trs);
        G3_Identity();
        G3_Translate(mgr->emitter->resource->header->emitterBasePos.x, mgr->emitter->resource->header->emitterBasePos.y,
                     mgr->emitter->resource->header->emitterBasePos.z);
        G3_MultMtx43(mgr->viewMatrix);
    }

    G3_Translate(trs.x, trs.y, trs.z);

    if (mgr->emitter->resource->header->miscFlags & 0x10) {
        MTX_RotX43_(&tiltMtx, FX_SinIdx(angle), FX_CosIdx(angle));
        G3_MultMtx43(&tiltMtx);
    }
    G3_MultMtx43(&mtx);

    G3_Color((GXRgb) ((((ptcl->color & 0x1f) * (mgr->emitter->color & 0x1f)) >> 5) |
                      ((((ptcl->color & 0x3e0) * (mgr->emitter->color & 0x3e0)) >> 15) << 5) |
                      ((((ptcl->color & 0x7c00) * (mgr->emitter->color & 0x7c00)) >> 25) << 10)));

    data_0213f260[mgr->emitter->resource->header->flags.quadType](mgr->emitter->textureS, mgr->emitter->textureT,
                                                                  mgr->emitter->resource->header->polygonX,
                                                                  mgr->emitter->resource->header->polygonY);
}
