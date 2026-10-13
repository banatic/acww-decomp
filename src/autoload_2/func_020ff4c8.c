/* func_020ff4c8 @ 0x020ff4c8, 0x11c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> 12))

typedef struct {
    fx32 x, y, z;
} VecFx32;

typedef struct SPLParticle {
    u8 pad_00[8];
    VecFx32 position;
    VecFx32 velocity;
    u8 pad_20[4];
    u16 lifeTime;
    u16 age;
    u8 pad_28[0x10];
    VecFx32 emitterPos;
} SPLParticle;

typedef struct SPLEmitter {
    u8 pad_00[0x5c];
    fx32 collisionPlaneHeight;
} SPLEmitter;

typedef struct SPLCollisionPlaneBehavior {
    fx32 y;
    fx16 elasticity;
    struct {
        u16 collisionType : 2;
        u16 reserved : 14;
    } flags;
} SPLCollisionPlaneBehavior;

void func_020ff4c8(SPLCollisionPlaneBehavior *behavior, SPLParticle *ptcl, VecFx32 *velocity, SPLEmitter *emtr)
{
    fx32 y = behavior->y;

    if (emtr->collisionPlaneHeight != (fx32) 0x80000000) {
        y = emtr->collisionPlaneHeight;
    }

    switch (behavior->flags.collisionType) {
        case 0:
            if (ptcl->emitterPos.y < y && ptcl->emitterPos.y + ptcl->position.y > y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->age = ptcl->lifeTime;
            } else if (ptcl->emitterPos.y >= y && ptcl->emitterPos.y + ptcl->position.y < y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->age = ptcl->lifeTime;
            }
            break;

        case 1:
            if (ptcl->emitterPos.y < y && ptcl->emitterPos.y + ptcl->position.y > y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->velocity.y = -FX_MUL(ptcl->velocity.y, behavior->elasticity);
            } else if (ptcl->emitterPos.y >= y && ptcl->emitterPos.y + ptcl->position.y < y) {
                ptcl->position.y = y - ptcl->emitterPos.y;
                ptcl->velocity.y = -FX_MUL(ptcl->velocity.y, behavior->elasticity);
            }
            break;
    }
}
