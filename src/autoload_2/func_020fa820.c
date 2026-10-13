/* func_020fa820 @ 0x020fa820, 0x1d4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

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

typedef void *(*Alloc)(u32);

typedef struct SPLManager {
    Alloc alloc;
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

extern void MI_CpuFill8(void *dst, int c, u32 n);

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
