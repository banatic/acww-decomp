/* particle_draw_2: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020fdb4c @ 0x020fdb4c, 0xbc bytes, ARM
 * func_020fda90 @ 0x020fda90, 0xbc bytes, ARM
 * func_020fd9e4 @ 0x020fd9e4, 0xac bytes, ARM
 */

#include "types.h"

#define FX32_ONE 0x1000
#define reg_G3_TEXCOORD (*(vu32 *) 0x04000488)
#define reg_G3_VTX_10 (*(vu32 *) 0x04000490)
#define reg_G3_BEGIN_VTXS (*(vu32 *) 0x04000500)
#define reg_G3_END_VTXS (*(vu32 *) 0x04000504)
#define GX_BEGIN_QUADS 1
#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> 12))

typedef struct {
    fx32 unk_00, unk_04, unk_08;
    fx32 unk_0C, unk_10, unk_14;
    fx32 unk_18, unk_1C, unk_20;
    fx32 unk_24, unk_28, unk_2C;
} MtxFx43;

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

void func_020fda90(fx32 s, fx32 t, fx32 x, fx32 z)
{
    G3_Begin(GX_BEGIN_QUADS);

    G3_TexCoord(0, 0);
    G3_Vtx10((fx16) (x - FX32_ONE), 0, (fx16) (z + FX32_ONE));
    G3_TexCoord(s, 0);
    G3_Vtx10((fx16) (x + FX32_ONE), 0, (fx16) (z + FX32_ONE));
    G3_TexCoord(s, t);
    G3_Vtx10((fx16) (x + FX32_ONE), 0, (fx16) (z - FX32_ONE));
    G3_TexCoord(0, t);
    G3_Vtx10((fx16) (x - FX32_ONE), 0, (fx16) (z - FX32_ONE));

    G3_End();
}

void func_020fd9e4(fx32 sinVal, fx32 cosVal, MtxFx43 *mtx)
{
    fx32 a, b, d, p, m;

    a = FX_MUL(FX32_ONE - cosVal, 0x555);
    b = FX_MUL(sinVal, 0x93d);
    p = a + b;
    m = a - b;
    d = a + cosVal;

    mtx->unk_00 = d;
    mtx->unk_0C = p;
    mtx->unk_18 = m;
    mtx->unk_24 = 0;
    mtx->unk_04 = m;
    mtx->unk_10 = d;
    mtx->unk_1C = p;
    mtx->unk_28 = 0;
    mtx->unk_08 = p;
    mtx->unk_14 = m;
    mtx->unk_20 = d;
    mtx->unk_2C = 0;
}
