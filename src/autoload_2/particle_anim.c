/* particle_anim: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ff3a4 @ 0x020ff3a4, 0x90 bytes, ARM
 * func_020ff1d8 @ 0x020ff1d8, 0x1cc bytes, ARM
 * func_020ff0fc @ 0x020ff0fc, 0xdc bytes, ARM
 * func_020ff098 @ 0x020ff098, 0x64 bytes, ARM
 * func_020ff04c @ 0x020ff04c, 0x4c bytes, ARM
 * func_020feff4 @ 0x020feff4, 0x58 bytes, ARM
 */

#include "types.h"

#define RGB(r, g, b) ((u16) ((r) | ((g) << 5) | ((b) << 10)))
#define SPLRandom_ScaledRangeFX32(num, range) (((num) * (255 - (((range) * (fx32) SPLRandom_U32(8)) >> 8))) >> 8)

typedef struct {
    short a;
    short b;
    short c;
    unsigned char lo;
    unsigned char hi;
} Table;

typedef struct {
    int pad_00;
    Table *tab;
} UnkStruct_020ff3a4;

typedef struct {
    char pad_00[0x34];
    short value;
} Output;

typedef struct {
    u16 unk_00;
    u16 c1;
    u8 t0, t1, t2, pad_07;
    u16 f0 : 2;
    u16 interp : 1;
} Anim;

typedef struct {
    u8 pad_00[0x22];
    u16 base;
} Res;

typedef struct {
    Res *res;
    int pad_04;
    Anim *anim;
} Emtr;

typedef struct {
    u8 pad_00[0x36];
    u16 color;
} Ptcl;

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

typedef struct SPLParticle_020ff098 {
    u8 pad_00[0x2c];
    u8 texture;
} SPLParticle_020ff098;

typedef struct SPLTexAnim {
    u8 textures[8];
    u8 frameCount;
    u8 step;
    u16 flags;
} SPLTexAnim;

typedef struct SPLResource_020ff098 {
    u8 pad_00[0x10];
    SPLTexAnim *texAnim;
} SPLResource_020ff098;

struct UnkStruct_020ff04c {
    char pad_00[4];
    short s;
};

struct UnkStruct_020ff04c_2 {
    char pad_00[20];
    struct UnkStruct_020ff04c *b;
};

struct UnkStruct_020ff04c_3 {
    char pad_00[52];
    unsigned short unk_34;
};

typedef struct {
    char pad_00[0x2e];
    unsigned short unk_2E;
} UnkStruct_020feff4;

extern u32 data_021fd278;

void func_020ff3a4(Output *out, const UnkStruct_020ff3a4 *outer, int x)
{
    const Table *t = outer->tab;
    unsigned char lo = t->lo;
    unsigned char hi = t->hi;

    if (x < lo) {
        out->value = t->a + x * (t->b - t->a) / lo;
        return;
    }
    if (x < hi) {
        out->value = t->b;
        return;
    }
    out->value = t->c + (x - 255) * (t->c - t->b) / (255 - hi);
}

void func_020ff1d8(Ptcl *ptcl, Emtr *emtr, int t)
{
    Anim *a = emtr->anim;
    int t0 = a->t0;
    Res *res = emtr->res;
    int t1 = a->t1;
    int t2 = a->t2;
    u16 src, dst;
    int dr, sr, dg, sg, db, sb;

    if (t < t0) {
        ptcl->color = a->unk_00;
        return;
    }
    if (t < t1) {
        dst = res->base;
        src = a->unk_00;
        dr = dst & 0x1f;
        dg = (dst >> 5) & 0x1f;
        db = (dst >> 10) & 0x1f;
        sr = src & 0x1f;
        sg = (src >> 5) & 0x1f;
        sb = (src >> 10) & 0x1f;
        if (!a->interp) {
            ptcl->color = RGB(dr, dg, db);
            return;
        }
        ptcl->color = RGB(sr + (t - t0) * (dr - sr) / (t1 - t0), sg + (t - t0) * (dg - sg) / (t1 - t0),
                          sb + (t - t0) * (db - sb) / (t1 - t0));
        return;
    }
    if (t < t2) {
        u16 src2, dst2;
        int sr2, dr2, sg2, dg2, db2, sb2;

        dst2 = a->c1;
        src2 = res->base;
        dr2 = dst2 & 0x1f;
        dg2 = (dst2 >> 5) & 0x1f;
        sr2 = src2 & 0x1f;
        sg2 = (src2 >> 5) & 0x1f;
        sb2 = (src2 >> 10) & 0x1f;
        db2 = (dst2 >> 10) & 0x1f;
        if (!a->interp) {
            ptcl->color = RGB(dr2, dg2, db2);
            return;
        }
        ptcl->color = RGB(sr2 + (t - t1) * (dr2 - sr2) / (t2 - t1), sg2 + (t - t1) * (dg2 - sg2) / (t2 - t1),
                          sb2 + (t - t1) * (db2 - sb2) / (t2 - t1));
        return;
    }
    ptcl->color = a->c1;
}

static __inline u32 SPLRandom_Next(void)
{
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    return data_021fd278;
}

static __inline u32 SPLRandom_U32(u32 bits)
{
    return SPLRandom_Next() >> (32 - bits);
}

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

void func_020ff098(SPLParticle_020ff098 *ptcl, SPLResource_020ff098 *res, s32 lifeRate)
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

void func_020ff04c(struct UnkStruct_020ff04c_3 *out, struct UnkStruct_020ff04c_2 *a, int v)
{
    short s;
    int delta;
    int factor;
    int prod;
    int ratio;

    s = a->b->s;
    delta = s - 0x1000;
    factor = v - 255;
    prod = delta * factor;
    ratio = prod / 255;
    out->unk_34 = (unsigned short) (s + ratio);
}

void func_020feff4(UnkStruct_020feff4 *p, int unused, int v)
{
    unsigned short tmp;
    unsigned short q;

    q = ((255 - v) * 31) / 255;
    tmp = p->unk_2E;
    p->unk_2E = (tmp & ~0x3e0) | ((q & 0x1f) << 5);
}
