/* func_020ff098 @ 0x020ff098, 0x64 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct SPLParticle {
    u8 pad_00[0x2c];
    u8 texture;
} SPLParticle;

typedef struct SPLTexAnim {
    u8 textures[8];
    u8 frameCount;
    u8 step;
    u16 flags;
} SPLTexAnim;

typedef struct SPLResource {
    u8 pad_00[0x10];
    SPLTexAnim *texAnim;
} SPLResource;

void func_020ff098(SPLParticle *ptcl, SPLResource *res, s32 lifeRate)
{
    SPLTexAnim *anim = res->texAnim;
    int i;

    for (i = 0; i < anim->frameCount; i++) {
        if (lifeRate < (i + 1) * anim->step) {
            ptcl->texture = anim->textures[i];
            return;
        }
    }
}
