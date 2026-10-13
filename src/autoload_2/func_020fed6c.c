/* func_020fed6c @ 0x020fed6c, 0x288 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#define FX32_SHIFT 12
#define FX32_ONE 0x1000

typedef struct {
    fx16 x, y, z;
} VecFx16;

#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> FX32_SHIFT))

typedef struct SPLResourceFlags {
    u32 emissionType : 4;
    u32 drawType : 2;
    u32 circleAxis : 2;
    u32 rest : 24;
} SPLResourceFlags;

typedef struct SPLResourceHeader {
    SPLResourceFlags flags;
} SPLResourceHeader;

typedef struct SPLResource {
    SPLResourceHeader *header;
} SPLResource;

typedef struct SPLEmitter {
    u8 pad_00[0x18];
    SPLResource *resource;
    u8 pad_1C[0x20];
    VecFx16 axis;
    u8 pad_42[0x2a];
    VecFx16 crossAxis1;
    VecFx16 crossAxis2;
} SPLEmitter;

extern VecFx16 data_0213f270;
extern void VEC_Fx16Normalize(const VecFx16 *src, VecFx16 *dst);
extern fx32 VEC_Fx16DotProduct(const VecFx16 *a, const VecFx16 *b);

void func_020fed6c(SPLEmitter *emtr)
{
    VecFx16 up = data_0213f270;
    VecFx16 axis;
    fx32 dot;

    switch (emtr->resource->header->flags.circleAxis) {
        case 2:
            axis.x = FX32_ONE;
            axis.y = 0;
            axis.z = 0;
            break;
        case 1:
            axis.x = 0;
            axis.y = FX32_ONE;
            axis.z = 0;
            break;
        case 0:
            axis.x = 0;
            axis.y = 0;
            axis.z = FX32_ONE;
            break;
        default:
            VEC_Fx16Normalize(&emtr->axis, &axis);
            break;
    }

    dot = VEC_Fx16DotProduct(&up, &axis);
    if (dot == FX32_ONE || dot == -FX32_ONE) {
        up.x = FX32_ONE;
        up.y = 0;
        up.z = 0;
    }

    emtr->crossAxis1.x = FX_MUL(axis.y, up.z) - FX_MUL(axis.z, up.y);
    emtr->crossAxis1.y = FX_MUL(axis.z, up.x) - FX_MUL(axis.x, up.z);
    emtr->crossAxis1.z = FX_MUL(axis.x, up.y) - FX_MUL(axis.y, up.x);

    emtr->crossAxis2.x = FX_MUL(axis.y, emtr->crossAxis1.z) - FX_MUL(axis.z, emtr->crossAxis1.y);
    emtr->crossAxis2.y = FX_MUL(axis.z, emtr->crossAxis1.x) - FX_MUL(axis.x, emtr->crossAxis1.z);
    emtr->crossAxis2.z = FX_MUL(axis.x, emtr->crossAxis1.y) - FX_MUL(axis.y, emtr->crossAxis1.x);

    VEC_Fx16Normalize(&emtr->crossAxis1, &emtr->crossAxis1);
    VEC_Fx16Normalize(&emtr->crossAxis2, &emtr->crossAxis2);
}
