/* func_020fb8e8 @ 0x020fb8e8, 0xec bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef enum {
    GX_TEXFMT_NONE = 0,
    GX_TEXFMT_A3I5 = 1,
    GX_TEXFMT_PLTT4 = 2,
    GX_TEXFMT_PLTT16 = 3,
    GX_TEXFMT_PLTT256 = 4,
    GX_TEXFMT_COMP4x4 = 5,
    GX_TEXFMT_A5I3 = 6,
    GX_TEXFMT_DIRECT = 7
} GXTexFmt;
typedef enum { GX_TEXGEN_NONE = 0, GX_TEXGEN_TEXCOORD = 1, GX_TEXGEN_NORMAL = 2, GX_TEXGEN_VERTEX = 3 } GXTexGen;
typedef enum {
    GX_TEXSIZE_S8 = 0,
    GX_TEXSIZE_S16 = 1,
    GX_TEXSIZE_S32 = 2,
    GX_TEXSIZE_S64 = 3,
    GX_TEXSIZE_S128 = 4,
    GX_TEXSIZE_S256 = 5,
    GX_TEXSIZE_S512 = 6,
    GX_TEXSIZE_S1024 = 7
} GXTexSizeS;
typedef enum {
    GX_TEXSIZE_T8 = 0,
    GX_TEXSIZE_T16 = 1,
    GX_TEXSIZE_T32 = 2,
    GX_TEXSIZE_T64 = 3,
    GX_TEXSIZE_T128 = 4,
    GX_TEXSIZE_T256 = 5,
    GX_TEXSIZE_T512 = 6,
    GX_TEXSIZE_T1024 = 7
} GXTexSizeT;
typedef enum { GX_TEXREPEAT_NONE = 0, GX_TEXREPEAT_S = 1, GX_TEXREPEAT_T = 2, GX_TEXREPEAT_ST = 3 } GXTexRepeat;
typedef enum { GX_TEXFLIP_NONE = 0, GX_TEXFLIP_S = 1, GX_TEXFLIP_T = 2, GX_TEXFLIP_ST = 3 } GXTexFlip;
typedef enum { GX_TEXPLTTCOLOR0_USE = 0, GX_TEXPLTTCOLOR0_TRNS = 1 } GXTexPlttColor0;
typedef enum {
    GX_MTXMODE_PROJECTION = 0,
    GX_MTXMODE_POSITION = 1,
    GX_MTXMODE_POSITION_VECTOR = 2,
    GX_MTXMODE_TEXTURE = 3
} GXMtxMode;

#define reg_G3_MTX_MODE (*(volatile u32 *) 0x04000440)
#define reg_G3_MTX_IDENTITY (*(volatile u32 *) 0x04000454)
#define reg_G3_MTX_SCALE (*(volatile u32 *) 0x0400046c)
#define reg_G3_TEXIMAGE_PARAM (*(volatile u32 *) 0x040004a8)
#define reg_G3_TEXPLTT_BASE (*(volatile u32 *) 0x040004ac)
#define FX32_ONE 0x1000

#define GX_PACK_TEXIMAGE_PARAM(texFmt, texGen, s, t, repeat, flip, pltt0, addr)                                               \
    ((u32) (((addr) >> 3) | ((texFmt) << 26) | ((texGen) << 30) | ((s) << 20) | ((t) << 23) | ((repeat) << 16) |              \
            ((flip) << 18) | ((pltt0) << 29)))
#define GX_PACK_TEXPLTTBASE_PARAM(addr, texFmt) ((u32) ((addr) >> (4 - ((texFmt) == GX_TEXFMT_PLTT4))))

static inline void G3_MtxMode(GXMtxMode mode)
{
    reg_G3_MTX_MODE = (u32) mode;
}
static inline void G3_Identity()
{
    reg_G3_MTX_IDENTITY = 0;
}
static inline void G3_Scale(fx32 x, fx32 y, fx32 z)
{
    reg_G3_MTX_SCALE = (u32) x;
    reg_G3_MTX_SCALE = (u32) y;
    reg_G3_MTX_SCALE = (u32) z;
}
static inline void G3_TexImageParam(GXTexFmt texFmt, GXTexGen texGen, GXTexSizeS s, GXTexSizeT t, GXTexRepeat repeat,
                                    GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr)
{
    reg_G3_TEXIMAGE_PARAM = GX_PACK_TEXIMAGE_PARAM(texFmt, texGen, s, t, repeat, flip, pltt0, addr);
}
static inline void G3_TexPlttBase(u32 addr, GXTexFmt texfmt)
{
    u32 param = GX_PACK_TEXPLTTBASE_PARAM(addr, texfmt);
    reg_G3_TEXPLTT_BASE = param;
}

typedef union {
    u32 all;
    struct {
        u32 format : 4;
        u32 s : 4;
        u32 t : 4;
        u32 repeat : 2;
        u32 flip : 2;
        u32 palColor0 : 1;
        u32 useSharedTexture : 1;
        u32 sharedTexID : 8;
        u32 : 6;
    };
} SPLTextureParam;

typedef struct {
    const void *resource;
    u32 texAddr;
    u32 palAddr;
    SPLTextureParam param;
    u16 width;
    u16 height;
} SPLTexture;

void func_020fb8e8(SPLTexture *tex)
{
    SPLTextureParam param = tex->param;

    G3_TexImageParam(param.format, GX_TEXGEN_TEXCOORD, param.s, param.t, param.repeat, param.flip, param.palColor0,
                     tex->texAddr);
    G3_TexPlttBase(tex->palAddr, param.format);
    G3_MtxMode(GX_MTXMODE_TEXTURE);
    G3_Identity();
    G3_Scale(tex->width * FX32_ONE, tex->height * FX32_ONE, 0);
    G3_MtxMode(GX_MTXMODE_POSITION);
}
