/* func_020ff0fc @ 0x020ff0fc, 0xdc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct SPLParticle {
    u8 pad_00[0x2e];
    struct {
        u16 baseAlpha : 5;
        u16 animAlpha : 5;
        u16 currentPolygonID : 6;
    } visibility;
} SPLParticle;

typedef struct SPLAlphaAnim {
    struct {
        u16 startAlpha : 5;
        u16 midAlpha : 5;
        u16 endAlpha : 5;
        u16 reserved : 1;
    } alpha;
    u8 randomRange;
    u8 flags;
    u8 startTime;
    u8 endTime;
} SPLAlphaAnim;

typedef struct SPLResource {
    u8 pad_00[0xc];
    SPLAlphaAnim *alphaAnim;
} SPLResource;

extern u32 data_021fd278;

static __inline u32 SPLRandom_Next(void)
{
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    return data_021fd278;
}

static __inline u32 SPLRandom_U32(u32 bits)
{
    return SPLRandom_Next() >> (32 - bits);
}

#define SPLRandom_ScaledRangeFX32(num, range) (((num) * (255 - (((range) * (fx32) SPLRandom_U32(8)) >> 8))) >> 8)

void func_020ff0fc(SPLParticle *ptcl, SPLResource *res, s32 lifeRate)
{
    SPLAlphaAnim *anim = res->alphaAnim;
    int startTime = anim->startTime;
    int endTime = anim->endTime;
    s32 alpha;

    if (lifeRate < startTime) {
        alpha = (lifeRate * (anim->alpha.midAlpha - anim->alpha.startAlpha)) / startTime + anim->alpha.startAlpha;
    } else if (lifeRate < endTime) {
        alpha = anim->alpha.midAlpha;
    } else {
        alpha = ((lifeRate - 255) * (anim->alpha.endAlpha - anim->alpha.midAlpha)) / (255 - endTime) + anim->alpha.endAlpha;
    }

    ptcl->visibility.animAlpha = SPLRandom_ScaledRangeFX32(alpha, anim->randomRange);
}
