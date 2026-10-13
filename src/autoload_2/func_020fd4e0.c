/* func_020fd4e0 @ 0x020fd4e0, 0x4c4 bytes, ARM, module autoload_2
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
#define FX32_ONE 0x1000
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
        u32 pad0 : 23;
        u32 useViewSpace : 1;
        u32 pad1 : 8;
    } flags;
    VecFx32 emitterBasePos; // 0x04
    u8 pad_10[0x30 - 0x10];
    fx16 aspectRatio; // 0x30
    u8 pad_32[0x44 - 0x32];
    struct {
        u32 pad0 : 28;
        u32 scaleAnimDir : 3;
        u32 pad1 : 1;
    } misc; // 0x44
    u8 pad_48[0x4c - 0x48];
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

extern void MTX_MultVec43(const VecFx32 *vec, const MtxFx43 *m, VecFx32 *dst);
extern void MTX_RotX43_(MtxFx43 *mtx, fx32 sinVal, fx32 cosVal);
extern void G3_MultMtx43(const MtxFx43 *m);
extern void func_020fdb4c(fx32 s, fx32 t, fx32 x, fx32 y);

static __inline void SPLi_SetPolygonAttr(SPLManager *mgr, u32 bits, u32 polygonID, u32 alpha)
{
    reg_G3_POLYGON_ATTR = (mgr->miscPolygonAttr | bits) | (polygonID << 24) | (alpha << 16);
    reg_G3_POLYGON_ATTR;
}

void func_020fd4e0(SPLManager *mgr, SPLParticle *ptcl, SPLDrawCallback cb)
{
    VecFx32 trs;
    MtxFx43 mtx;
    MtxFx43 rotMtx;
    fx32 sx, sy;
    fx32 sinVal, cosVal;
    s32 alpha;
    u8 dir = mgr->emitter->resource->header->misc.scaleAnimDir;
    const MtxFx43 *cmr = mgr->viewMatrix;
    fx32 aspect = mgr->emitter->resource->header->aspectRatio;
    fx32 anim = ptcl->animScale;
    GXRgb pcol = ptcl->color;
    GXRgb ecol = mgr->emitter->color;
    fx32 angle;

    alpha = (ptcl->visibility.baseAlpha * (ptcl->visibility.animAlpha + 1)) >> 5;
    SPLi_SetPolygonAttr(mgr, 0xc0, ptcl->visibility.currentPolygonID, alpha);
    if (alpha == 0) {
        return;
    }

    sx = FX_MUL(ptcl->baseScale, aspect);
    sy = ptcl->baseScale;
    if (dir == 0) {
        sx = FX_MUL(sx, anim);
        sy = FX_MUL(sy, anim);
    } else if (dir == 1) {
        sx = FX_MUL(sx, anim);
    } else {
        sy = FX_MUL(sy, anim);
    }

    if (!mgr->emitter->resource->header->flags.useViewSpace) {
        trs.x = ptcl->position.x + ptcl->emitterPos.x;
        trs.y = ptcl->position.y + ptcl->emitterPos.y;
        trs.z = ptcl->position.z + ptcl->emitterPos.z;
        angle = cb(&trs, trs);
        MTX_MultVec43(&trs, cmr, &trs);

        sinVal = FX_SinIdx(ptcl->rotation);
        cosVal = FX_CosIdx(ptcl->rotation);
        mtx.unk_00 = FX_MUL(cosVal, sx);
        mtx.unk_04 = FX_MUL(sinVal, sx);
        mtx.unk_08 = 0;
        mtx.unk_0C = FX_MUL(-sinVal, sy);
        mtx.unk_10 = FX_MUL(cosVal, sy);
        mtx.unk_14 = 0;
        mtx.unk_18 = 0;
        mtx.unk_1C = 0;
        mtx.unk_20 = FX32_ONE;
        mtx.unk_24 = 0;
        mtx.unk_28 = 0;
        mtx.unk_2C = 0;
        G3_Identity();
    } else {
        trs.x = ptcl->position.x + ptcl->emitterPos.x - mgr->emitter->resource->header->emitterBasePos.x;
        trs.y = ptcl->position.y + ptcl->emitterPos.y - mgr->emitter->resource->header->emitterBasePos.y;
        trs.z = ptcl->position.z + ptcl->emitterPos.z - mgr->emitter->resource->header->emitterBasePos.z;
        angle = cb(&trs, trs);
        MTX_MultVec43(&trs, cmr, &trs);

        sinVal = FX_SinIdx(ptcl->rotation);
        cosVal = FX_CosIdx(ptcl->rotation);
        mtx.unk_00 = FX_MUL(cosVal, sx);
        mtx.unk_04 = FX_MUL(sinVal, sx);
        mtx.unk_08 = 0;
        mtx.unk_0C = FX_MUL(-sinVal, sy);
        mtx.unk_10 = FX_MUL(cosVal, sy);
        mtx.unk_14 = 0;
        mtx.unk_18 = 0;
        mtx.unk_1C = 0;
        mtx.unk_20 = FX32_ONE;
        mtx.unk_24 = 0;
        mtx.unk_28 = 0;
        mtx.unk_2C = 0;
        G3_Identity();
        G3_Translate(mgr->emitter->resource->header->emitterBasePos.x, mgr->emitter->resource->header->emitterBasePos.y,
                     mgr->emitter->resource->header->emitterBasePos.z);
    }

    G3_Translate(trs.x, trs.y, trs.z);

    if (mgr->emitter->resource->header->miscFlags & 0x10) {
        MTX_RotX43_(&rotMtx, FX_SinIdx(angle), FX_CosIdx(angle));
        G3_MultMtx43(&rotMtx);
    }
    G3_MultMtx43(&mtx);

    G3_Color((GXRgb) ((((pcol & 0x1f) * (ecol & 0x1f)) >> 5) | ((((pcol & 0x3e0) * (ecol & 0x3e0)) >> 15) << 5) |
                      ((((pcol & 0x7c00) * (ecol & 0x7c00)) >> 25) << 10)));

    func_020fdb4c(mgr->emitter->textureS, mgr->emitter->textureT, mgr->emitter->resource->header->polygonX,
                  mgr->emitter->resource->header->polygonY);
}
