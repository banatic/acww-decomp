/* func_020fdb4c @ 0x020fdb4c, 0xbc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#define FX32_ONE 0x1000

#define reg_G3_TEXCOORD (*(vu32 *) 0x04000488)
#define reg_G3_VTX_10 (*(vu32 *) 0x04000490)
#define reg_G3_BEGIN_VTXS (*(vu32 *) 0x04000500)
#define reg_G3_END_VTXS (*(vu32 *) 0x04000504)

#define GX_BEGIN_QUADS 1

static __inline void G3_Begin(int primitive)
{
    reg_G3_BEGIN_VTXS = (u32) primitive;
}

static __inline void G3_End(void)
{
    reg_G3_END_VTXS = 0;
}

static __inline void G3_TexCoord(fx32 s, fx32 t)
{
    reg_G3_TEXCOORD = (u32) ((u16) (s >> 8) | ((u32) (u16) (t >> 8) << 16));
}

static __inline void G3_Vtx10(fx16 x, fx16 y, fx16 z)
{
    reg_G3_VTX_10 = (u32) ((((x >> 6) & 0x3ff) << 0) | (((y >> 6) & 0x3ff) << 10) | (((z >> 6) & 0x3ff) << 20));
}

void func_020fdb4c(fx32 s, fx32 t, fx32 x, fx32 y)
{
    G3_Begin(GX_BEGIN_QUADS);

    G3_TexCoord(0, 0);
    G3_Vtx10((fx16) (x - FX32_ONE), (fx16) (y + FX32_ONE), 0);
    G3_TexCoord(s, 0);
    G3_Vtx10((fx16) (x + FX32_ONE), (fx16) (y + FX32_ONE), 0);
    G3_TexCoord(s, t);
    G3_Vtx10((fx16) (x + FX32_ONE), (fx16) (y - FX32_ONE), 0);
    G3_TexCoord(0, t);
    G3_Vtx10((fx16) (x - FX32_ONE), (fx16) (y - FX32_ONE), 0);

    G3_End();
}
