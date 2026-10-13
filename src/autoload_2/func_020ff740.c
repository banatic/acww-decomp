/* func_020ff740 @ 0x020ff740, 0xc8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} VecFx32;
typedef struct {
    fx16 x, y, z;
} VecFx16;

typedef struct SPLParticle {
    u8 pad_00[0x26];
    u16 age;
} SPLParticle;

typedef struct SPLRandomBehavior {
    VecFx16 magnitude;
    u16 interval;
} SPLRandomBehavior;

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

#define SPLRandom_RangeFX32(num) (((num) * (s32) SPLRandom_U32(9) - ((num) << 8)) >> 8)

void func_020ff740(SPLRandomBehavior *behavior, SPLParticle *ptcl, VecFx32 *velocity)
{
    if (ptcl->age % behavior->interval == 0) {
        velocity->x += SPLRandom_RangeFX32(behavior->magnitude.x);
        velocity->y += SPLRandom_RangeFX32(behavior->magnitude.y);
        velocity->z += SPLRandom_RangeFX32(behavior->magnitude.z);
    }
}
