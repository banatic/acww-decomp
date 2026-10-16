/* The shadows of characters and objects (shadow.h). */
#include "shadow.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "itcm/vector.h"
#include "main/calendar.h"

static_assert(offsetof(ShadowTexture, polygon_id) == 0x14, "ShadowTexture layout");
static_assert(sizeof(ShadowTexture) == 0x18, "ShadowTexture layout");
static_assert(offsetof(ObjShadow, lengths) == 0x1c, "ObjShadow layout");
static_assert(offsetof(ObjShadow, texture) == 0x30, "ObjShadow layout");
static_assert(sizeof(ObjShadow) == 0x34, "ObjShadow layout");

#define FX_ONE 0x1000

/* The holder of a loaded model (func_020555c8 loads, func_02055454 frees, func_02055e7c draws
 * it with a scale). */
typedef struct ShadowModel {
    u8 unk_00[0x5c];
    u8 *model; /* 0x5c: NitroSystem's NNSG3dResMdl */
} ShadowModel;

/* NitroSystem's NNSG3dResMatData, as far as the shadow changes it. */
typedef struct ShadowMaterial {
    u8 unk_00[0x0c];
    u32 polygon_attr;      /* 0x0c: POLYGON_ATTR */
    u32 polygon_attr_mask; /* 0x10: the bits of polygon_attr that replace the shape's */
} ShadowMaterial;

#define POLYGON_ATTR_ALPHA_SHIFT 16
#define POLYGON_ATTR_ALPHA_MASK 0x001f0000u
#define POLYGON_ATTR_ID_SHIFT 24
#define POLYGON_ATTR_ID_MASK 0x3f000000u
#define POLYGON_ATTR_FRONT 0x0080u
#define POLYGON_ATTR_FOG 0x8000u

#define CHARA_SHADOW_ID_FIRST 1
#define CHARA_SHADOW_ID_LAST 11

/* data_021f472c and its first material (NULL while not loaded) */
extern ShadowModel data_021f472c;
extern ShadowMaterial *data_021f471c;
/* The polygon ID the next character's shadow is drawn with. */
extern u32 data_020e40e0;
/* "/shadow/chara_shadow.nsbmd" */
extern const char data_020e40e4[];
/* Nonzero indoors. */
extern u8 data_020e54a8;
/* The matrix the last character's shadow was drawn with, and a copy of it. */
extern Mtx43 data_021fbe48;
extern Mtx43 data_021f4790;

/* The shadows' alphas: the characters' and the objects'. */
extern u8 data_020e4100;
extern u8 data_020e4104;
/* The camera, while it exists, and its position. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;
/* Shadow_FadeAlpha's fade per unit behind the camera, made once (guard bit 0 of
 * data_021f47cc). */
extern u32 data_021f47cc;
extern fx32 data_021f47d4;

/* How far across the object shadows lean per unit behind the object: -1 at 6:00 and 18:00,
 * rising to almost 1 at 5:59 and 17:59. */
extern fx32 data_021f47d0;
/* The view's matrix, scaled by 32 for the object shadows, and its rows normalized. */
extern const Mtx43 data_0213fee4;
extern Mtx43 data_021f486c;
extern Vec3 data_021f4848[3];
/* The textures and the five strips. */
extern ShadowTexture data_021f49a0[SHADOW_TEXTURES];
extern ObjShadow data_021f4904; /* trees of size 2 */
extern ObjShadow data_021f4938; /* size 3 */
extern ObjShadow data_021f496c; /* size 4 */
extern ObjShadow data_021f489c; /* ObjShadow_DrawWide */
extern ObjShadow data_021f48d0; /* ObjShadow_DrawNarrow */
/* The heap the strips' rows go to when none is given, and the one ObjShadow_LoadAll uses. */
extern void *data_021fbe94;
extern void *data_021c9b24;
/* The vertices' y and z shift (5) */
extern const int data_020d1e0c;

/* ObjShadow_DrawTree's offset (0, 0, 0), made once (guard bit 0 of data_021f47c8) */
extern u32 data_021f47c8;
extern Vec3 data_021f4824;
extern u8 data_021f4818[];
/* ObjShadow_LoadAll's origin of every strip (0, 0, 0x1000), made once (guard data_021f47d8) */
extern u32 data_021f47d8;
extern Vec3 data_021f47e8;
extern u8 data_021f4800[];

/* "/shadow/tex_shadow.nsbtx", "%s_pl" and the textures' names and settings. */
extern const char data_020e412c[];
extern const char data_020e4148[];
typedef struct ShadowTextureEntry {
    const char *name;
    u8 flip;   /* TEXIMAGE_PARAM bits 18-19 */
    u8 repeat; /* bits 16-17 */
    u8 polygon_id;
    u8 pad_07;
} ShadowTextureEntry;
extern const ShadowTextureEntry data_020d1df4[SHADOW_TEXTURES];

extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern void MTX_Concat43(const Mtx43 *a, const Mtx43 *b, Mtx43 *product);
extern void VEC_Normalize(const Vec3 *src, Vec3 *dst);
extern void NNS_G3dGeFlushBuffer(void);
extern void G3_LoadMtx43(const Mtx43 *mtx);
extern void NNS_G3dMdlSetMdlDiff(u8 *model, int material, u16 diffuse);
extern void NNSi_G3dModifyMatFlag(u8 *model, int on, int flag);
extern void __register_global_object(void *object, void (*destructor)(void *), void *entry);
extern void func_020012dc(void *object); /* the static objects' destructor */

extern void func_0209def4(Time *now);
extern int func_020310c8(int value);                                 /* the ground's height offset */
extern int func_0203f844(Vec3 *out, const Vec3 *in);                 /* bends a point onto the curved world */
extern int func_0203f8d0(Vec3 *out, Vec3 *in);                       /* the same, returning the slope's angle */
extern int func_02034270(void *probe, const Vec3 *at, int a, int b); /* a ground probe */
extern int func_020341c8(void *probe, int a);                        /* its height */
extern void func_0203423c(void *probe);
extern int func_020b66d8(void);
extern short func_02065604(void); /* the light's colour */
extern short func_0206586c(void); /* a colour of the scene's light */
extern u32 func_020655c4(u32 kind);
extern int func_020555c8(ShadowModel *holder, const char *path, int a);
extern int func_02055454(ShadowModel *holder);
extern void func_02055e7c(ShadowModel *holder, const Vec3 *scale);
extern u8 *func_02064b18(const char *path);         /* reads a file into the current heap */
extern u8 *func_021077e8(u8 *file);                 /* the texture block of a .nsbtx */
extern int func_02056064(u8 *textures, int a);      /* places the textures in VRAM */
extern u8 *func_020561cc(u8 *textures, void *heap); /* copies the block to a heap */
extern int func_02064328(char *out, const char *format, ...);
extern int func_02057a40(const u8 *textures, const char *name); /* a texture's index */
extern int func_020579b8(const u8 *textures, const char *name); /* a palette's index */

/* ARM's arithmetic shift right by a register: counts of 32 or more give the sign. */
static s32 arm_asr(s32 value, u32 count)
{
    count &= 0xff;
    if (count >= 32) {
        return value < 0 ? -1 : 0;
    }
    return value >> count;
}

static int abs_int(int value)
{
    return value < 0 ? -value : value;
}

/* func_020acbc8: a character's shadow under the point (a joint's), a little below it. */
void CharaShadow_DrawUnder(const Vec3 *pos, int size)
{
    Vec3 at = *pos;
    at.y -= func_020310c8(0) + 0x800;
    CharaShadow_Draw(&at, size, 0xe00, FX_ONE);
}
CLEAN_AS(func_020acbc8, CharaShadow_DrawUnder)

/* func_020acc0c: a character's shadow of `size` on the ground under `pos`. Its alpha is the
 * characters' alpha faded with the distance from the camera (Shadow_CharaAlpha), less 31 per
 * `fade_height` of height above the ground, times `scale`; the shadow shrinks with the height
 * too, to nothing at `fade_height` (and stays whole within 5% of it). Outdoors the ground is
 * found with a probe and taken as at most 0; indoors only when func_020b66d8 says so, else 0.
 * QUIRK: the alpha is used without a check against 31; only its low 5 bits reach the
 * material. The polygon ID comes from the counter as it is, which CharaShadow_BeginFrame resets
 * to 1. */
void CharaShadow_Draw(const Vec3 *pos, int size, fx32 fade_height, fx32 scale)
{
    u8 probe[0x40];

    if (size == 0) {
        return;
    }
    int alpha = Shadow_CharaAlpha(pos, size);
    int ground = 0;
    if (data_020e54a8 == 0) {
        func_02034270(probe, pos, 0, 0);
        ground = func_020341c8(probe, 0);
        if (ground > 0) {
            ground = 0;
        }
        func_0203423c(probe);
    } else if (func_020b66d8() != 0) {
        func_02034270(probe, pos, 0, 0);
        ground = func_020341c8(probe, 0);
        func_0203423c(probe);
    }

    int height = pos->y - ground;
    int distance = abs_int(height);
    if (height != 0) {
        int per_unit = FX_Div(0x1f000, fade_height);
        alpha -= FX_MulFunc(distance, per_unit) >> 12;
    }
    if (scale != FX_ONE) {
        alpha = (s32) ((u32) alpha * (u32) scale) >> 12;
    }
    if (alpha <= 1) {
        return;
    }
    if (height != 0) {
        int shrink = FX_Div(-FX_ONE, fade_height);
        int factor = FX_MulFunc(shrink, distance) + FX_ONE;
        if (factor >= 0xf33) {
            factor = FX_ONE;
        }
        size = FX_MulFunc(size, factor);
    }
    if (size <= 0) {
        return;
    }

    Vec3 on_ground = *pos;
    on_ground.y = ground + func_020310c8(0);
    Vec3 bent;
    int slope = func_0203f8d0(&bent, &on_ground);
    Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
    Mtx43_RotateX(&data_021fbe48, slope);
    data_021f4790 = data_021fbe48;

    Vec3 model_scale = {size, FX_ONE, size};
    ShadowMaterial *material = data_021f471c;
    if (material != NULL) {
        material->polygon_attr &= ~POLYGON_ATTR_ALPHA_MASK;
        material->polygon_attr |= ((u32) alpha & 0x1f) << POLYGON_ATTR_ALPHA_SHIFT;
        material->polygon_attr &= ~POLYGON_ATTR_ID_MASK;
        material->polygon_attr |= data_020e40e0 << POLYGON_ATTR_ID_SHIFT;
        material->polygon_attr_mask |= POLYGON_ATTR_ID_MASK | POLYGON_ATTR_ALPHA_MASK;
    }
    func_02055e7c(&data_021f472c, &model_scale);

    data_020e40e0++;
    if (data_020e40e0 > CHARA_SHADOW_ID_LAST) {
        data_020e40e0 = CHARA_SHADOW_ID_FIRST;
    }
}
CLEAN_AS(func_020acc0c, CharaShadow_Draw)

/* func_020acdcc: as CharaShadow_Draw, its alpha scaled by `level` of 1 to 31 (0 counts as 1):
 * (level - 1) / 30, whole at 31. */
void CharaShadow_DrawLevel(const Vec3 *pos, int size, fx32 fade_height, int level)
{
    if (level == 0) {
        level = 1;
    }
    fx32 scale = FX_ONE;
    if (level != 31) {
        scale = FX_Div((int) ((u32) (level - 1) << 12), 0x1e000);
    }
    CharaShadow_Draw(pos, size, fade_height, scale);
}
CLEAN_AS(func_020acdcc, CharaShadow_DrawLevel)

/* func_020ace0c */
void CharaShadow_Unload(void)
{
    data_021f471c = NULL;
    func_02055454(&data_021f472c);
}
CLEAN_AS(func_020ace0c, CharaShadow_Unload)

/* func_020ace24: before the frame's shadows: the polygon IDs start again at 1, and the model's
 * material takes the light's colour as its diffuse colour. */
void CharaShadow_BeginFrame(void)
{
    data_020e40e0 = CHARA_SHADOW_ID_FIRST;
    u16 colour = (u16) func_02065604();
    NNS_G3dMdlSetMdlDiff(data_021f472c.model, 0, colour);
}
CLEAN_AS(func_020ace24, CharaShadow_BeginFrame)

/* func_020ace54: loads the model; returns whether it loaded. Keeps its first material
 * (through the model's material dictionary) for CharaShadow_Draw, restarts the polygon IDs and
 * sets the model's material flag 0x40.
 * QUIRK: the material is looked up through the model even when loading failed. */
int CharaShadow_Load(void)
{
    int loaded = func_020555c8(&data_021f472c, data_020e40e4, 0) != 0;

    u8 *model = data_021f472c.model;
    u8 *materials = model + *(const u32 *) (model + 0x08);    /* NNSG3dResMdl.ofsMat */
    u16 entries = *(const u16 *) (materials + 0x0a);          /* the dictionary's ofsEntry */
    u32 first = *(const u32 *) (materials + 4 + entries + 4); /* the first entry's offset */
    data_021f471c = (ShadowMaterial *) (materials + first);
    data_020e40e0 = CHARA_SHADOW_ID_FIRST;
    NNSi_G3dModifyMatFlag(model, 1, 0x40);
    return loaded;
}
CLEAN_AS(func_020ace54, CharaShadow_Load)

/* func_020acea4: frees the strip's rows to `heap` (the current one, data_021fbe94, when NULL)
 * and unsets its texture. Returns 0. */
int ObjShadow_Free(ObjShadow *shadow, void *heap)
{
    if (heap == NULL) {
        heap = data_021fbe94;
    }
    if (shadow->lengths != NULL) {
        Heap_Free(heap, shadow->lengths);
        shadow->lengths = NULL;
    }
    shadow->texture = NULL;
    return 0;
}
CLEAN_AS(func_020acea4, ObjShadow_Free)

/* The geometry engine's command registers. */
#define REG_MTX_MODE 0x04000440u
#define REG_MTX_POP 0x04000448u
#define REG_COLOR 0x04000480u
#define REG_TEXCOORD 0x04000488u
#define REG_VTX_16 0x0400048cu
#define REG_POLYGON_ATTR 0x040004a4u
#define REG_TEXIMAGE_PARAM 0x040004a8u
#define REG_PLTT_BASE 0x040004acu
#define REG_BEGIN_VTXS 0x04000500u
#define REG_END_VTXS 0x04000504u

#define GX_MTXMODE_POSITION 1
#define GX_BEGIN_QUAD_STRIP 3

static void reg_write(u32 address, u32 value)
{
    *(volatile u32 *) (uintptr_t) address = value;
}

/* 20.12 fixed point as the 12.4 of a texture coordinate. */
static u32 texcoord(fx32 value)
{
    return ((u32) value >> 8) & 0xffff;
}

/* A coordinate scaled down by 32, in the 4.12 of VTX_16. */
static u32 vertex_x(fx32 value)
{
    return ((u32) value >> 5) & 0xffff;
}

/* func_020aced0: the strip of an object at `pos`, unless its texture is unset or the alpha
 * (Shadow_ObjAlpha) is 1 or less. Row i's points are made again when the object's z changed
 * since the last time.
 * QUIRK: every row but the first leans across by the second row's length, not its own.
 * HW: the geometry engine's registers are written in this order: TEXIMAGE_PARAM, PLTT_BASE,
 * MTX_MODE (position), the matrix data_021f486c (G3_LoadMtx43), POLYGON_ATTR (the alpha, the
 * texture's polygon ID, front faces, fog), BEGIN_VTXS (quad strip); per row COLOR, then for the
 * left and the right vertex TEXCOORD and the two words of VTX_16; END_VTXS, and MTX_POP of 1,
 * though nothing here pushed. NNS_G3dGeFlushBuffer comes first. */
void ObjShadow_Draw(ObjShadow *shadow, const Vec3 *pos)
{
    ShadowTexture *texture = shadow->texture;
    if (texture == NULL) {
        return;
    }
    if (texture->block == NULL) {
        return;
    }
    u32 alpha = (u32) Shadow_ObjAlpha(pos, shadow->fade_range);
    if (alpha <= 1) {
        return;
    }

    NNS_G3dGeFlushBuffer();
    reg_write(REG_TEXIMAGE_PARAM, shadow->texture->image_param);
    reg_write(REG_PLTT_BASE, shadow->texture->palette_base);
    reg_write(REG_MTX_MODE, GX_MTXMODE_POSITION);
    G3_LoadMtx43(&data_021f486c);
    reg_write(REG_POLYGON_ATTR, (alpha << POLYGON_ATTR_ALPHA_SHIFT) |
                                    ((u32) shadow->texture->polygon_id << POLYGON_ATTR_ID_SHIFT) | POLYGON_ATTR_FOG |
                                    POLYGON_ATTR_FRONT);
    reg_write(REG_BEGIN_VTXS, GX_BEGIN_QUAD_STRIP);

    fx32 second_length = shadow->lengths[1];
    int shift = data_020d1e0c;
    for (u32 i = 0; i < shadow->rows; i++) {
        fx32 length = i != 0 ? second_length : shadow->lengths[0];
        fx32 lean = FX_MulFunc(data_021f47d0, length);
        fx32 left = lean + (pos->x - shadow->half_width);
        fx32 right = lean + (pos->x + shadow->half_width);
        Vec3 *point = &shadow->points[i];
        if (pos->z != shadow->last_z) {
            Vec3 at;
            at.x = 0;
            at.y = func_020310c8(0);
            at.z = pos->z - shadow->lengths[i];
            func_0203f844(point, &at);
            point->y = arm_asr(point->y, (u32) shift);
            point->z = arm_asr(point->z, (u32) shift);
        }
        reg_write(REG_COLOR, (u16) func_02065604());

        u32 t = texcoord(shadow->row_t[i]);
        reg_write(REG_TEXCOORD, texcoord(shadow->s_left) | (t << 16));
        reg_write(REG_VTX_16, vertex_x(left) | ((u32) point->y << 16));
        reg_write(REG_VTX_16, (u32) point->z & 0xffff);
        reg_write(REG_TEXCOORD, texcoord(shadow->s_right) | (t << 16));
        reg_write(REG_VTX_16, vertex_x(right) | ((u32) point->y << 16));
        reg_write(REG_VTX_16, (u32) point->z & 0xffff);
    }
    reg_write(REG_END_VTXS, 0);
    reg_write(REG_MTX_POP, 1);
    shadow->last_z = pos->z;
}
CLEAN_AS(func_020aced0, ObjShadow_Draw)

/* func_020ad0c0: sets the strip up: `width` across and `length` long, in rows 0x2000 apart
 * (the last at `length`), with texture `texture` across from `s_left` to `s_right` of its
 * width (both 0: the whole width) and down from its height at the object to 0 at the end.
 * The rows go in one block of `heap` (the current one, data_021fbe94, when NULL). Returns 1.
 * QUIRK: the fade range is meant as half the width unless that is shifted to 0 by `length`;
 * ARM shifts by the low byte of `length`, so for the game's lengths it is `length` when its low
 * byte is 32 or more and half the width when it is 0.
 * REQUIRES: length >= 0x200 (fewer than 2 rows otherwise); the block is not checked. */
int ObjShadow_Init(ObjShadow *shadow, const Vec3 *origin, fx32 width, fx32 length, int texture, fx32 s_left, fx32 s_right,
                   void *heap)
{
    if (heap == NULL) {
        heap = data_021fbe94;
    }
    shadow->texture = &data_021f49a0[texture];
    shadow->origin = *origin;
    shadow->half_width = width >> 1;
    fx32 range = shadow->half_width;
    if (arm_asr(range, (u32) length) == 0) {
        range = length;
    }
    shadow->fade_range = range;
    shadow->last_z = 0;
    shadow->rows = (u32) ((length - 0x200) / 0x2000 + 2);

    u32 array_size = shadow->rows * 4;
    shadow->lengths = Heap_Alloc(heap, (int) (array_size * 2 + shadow->rows * sizeof(Vec3)));
    shadow->row_t = (fx32 *) ((u8 *) shadow->lengths + array_size);
    shadow->points = (Vec3 *) ((u8 *) shadow->row_t + array_size);
    for (u32 i = 0; i < shadow->rows; i++) {
        if (i == shadow->rows - 1) {
            shadow->lengths[i] = length;
        } else {
            shadow->lengths[i] = (fx32) (i << 13);
        }
    }

    if (s_left == 0 && s_right == 0) {
        shadow->s_left = 0;
        shadow->s_right = shadow->texture->width << 12;
    } else {
        shadow->s_left = FX_MulFunc(shadow->texture->width << 12, s_left);
        shadow->s_right = FX_MulFunc(shadow->texture->width << 12, s_right);
    }

    fx32 *lengths = shadow->lengths;
    fx32 *row_t = shadow->row_t;
    for (u32 i = 0; i < shadow->rows; i++) {
        row_t[i] = FX_MulFunc(FX_ONE - FX_Div(lengths[i], length), shadow->texture->height << 12);
    }
    return 1;
}
CLEAN_AS(func_020ad0c0, ObjShadow_Init)

/* func_020ad1d8: the strips' destructor, handed to __register_global_object; it does nothing. */
void ObjShadow_Destruct(ObjShadow *shadow)
{
    (void) shadow;
}
CLEAN_AS(func_020ad1d8, ObjShadow_Destruct)

/* func_020ad1dc: an empty strip. last_z and the texture's s are left as they are. */
ObjShadow *ObjShadow_Construct(ObjShadow *shadow)
{
    shadow->origin.x = 0;
    shadow->origin.y = 0;
    shadow->origin.z = 0;
    shadow->half_width = 0;
    shadow->fade_range = 0;
    shadow->rows = 0;
    shadow->lengths = NULL;
    shadow->row_t = NULL;
    shadow->points = NULL;
    shadow->texture = NULL;
    return shadow;
}
CLEAN_AS(func_020ad1dc, ObjShadow_Construct)

/* func_020ad1f4: the narrow strip, from a point (0x166, 0, 0xc80) off `pos`. */
void ObjShadow_DrawNarrow(const Vec3 *pos)
{
    Vec3 offset = {0x166, 0, 0xc80};
    Vec3 at;
    Vec_Add(&at, pos, &offset);
    ObjShadow_Draw(&data_021f48d0, &at);
}
CLEAN_AS(func_020ad1f4, ObjShadow_DrawNarrow)

/* func_020ad228: the wide strip. */
void ObjShadow_DrawWide(const Vec3 *pos)
{
    ObjShadow_Draw(&data_021f489c, pos);
}
CLEAN_AS(func_020ad228, ObjShadow_DrawWide)

/* func_020ad238: the strip of a tree of `size` 2, 3 or 4; none for 0 or 1.
 * QUIRK: the point is moved by a static offset of (0, 0, 0) first, which is made (and handed to
 * __register_global_object) on the first call of size 2 or more. */
void ObjShadow_DrawTree(const Vec3 *pos, u32 size)
{
    if (size < 2) {
        return;
    }
    if ((data_021f47c8 & 1) == 0) {
        data_021f4824.x = 0;
        data_021f4824.y = 0;
        data_021f4824.z = 0;
        __register_global_object(&data_021f4824, func_020012dc, data_021f4818);
        data_021f47c8 |= 1;
    }
    Vec3 at;
    Vec_Add(&at, pos, &data_021f4824);
    if (size == 2) {
        ObjShadow_Draw(&data_021f4904, &at);
    } else if (size == 3) {
        ObjShadow_Draw(&data_021f4938, &at);
    } else if (size == 4) {
        ObjShadow_Draw(&data_021f496c, &at);
    }
}
CLEAN_AS(func_020ad238, ObjShadow_DrawTree)

/* func_020ad2c4 */
int Shadow_CharaAlpha(const Vec3 *pos, int range)
{
    return Shadow_FadeAlpha(pos, range, data_020e4100);
}
CLEAN_AS(func_020ad2c4, Shadow_CharaAlpha)

/* func_020ad2d4 */
int Shadow_ObjAlpha(const Vec3 *pos, int range)
{
    return Shadow_FadeAlpha(pos, range, data_020e4104);
}
CLEAN_AS(func_020ad2d4, Shadow_ObjAlpha)

/* func_020ad2e4: `alpha` for a shadow at `pos`, `range` the reach of what casts it. Without a
 * camera, or behind the camera (lower z), `alpha` as it is; further behind than 0xb000 (11
 * units) alpha / 32; else faded by 31/32 of itself per 11 units. Ahead of the camera, 0 when
 * further than `range` + 12 units ahead or `range` + 15 units across.
 * QUIRK: the faded value is cut to 8 bits; `alpha` is returned unchanged in width otherwise. */
int Shadow_FadeAlpha(const Vec3 *pos, int range, int alpha)
{
    if (data_021c67a4 == 0) {
        return alpha;
    }
    Vec3 camera = data_021c67d0;
    if (camera.z > pos->z) {
        int behind = camera.z - pos->z;
        if (behind > 0xb000) {
            return (u8) (alpha >> 5);
        }
        if ((data_021f47cc & 1) == 0) {
            data_021f47d4 = FX_Div(0xf80, 0xb000);
            data_021f47cc |= 1;
        }
        int fade = FX_MulFunc(FX_MulFunc((int) ((u32) alpha << 12), data_021f47d4), behind) >> 12;
        return (u8) (alpha - (u8) fade);
    }
    if (pos->z - camera.z > range + 0xc000) {
        return 0;
    }
    if (abs_int(pos->x - camera.x) > range + 0xf000) {
        return 0;
    }
    return alpha;
}
CLEAN_AS(func_020ad2e4, Shadow_FadeAlpha)

/* func_020ad3a0: unloads the textures and frees the five strips' rows to data_021c9b24's
 * heap. */
void ObjShadow_FreeAll(void)
{
    data_021f47d0 = 0;
    for (int i = 0; i < SHADOW_TEXTURES; i++) {
        data_021f49a0[i].block = NULL;
    }
    void *heap = data_021c9b24;
    ObjShadow_Free(&data_021f4904, heap);
    ObjShadow_Free(&data_021f4938, heap);
    ObjShadow_Free(&data_021f496c, heap);
    ObjShadow_Free(&data_021f489c, heap);
    ObjShadow_Free(&data_021f48d0, heap);
}
CLEAN_AS(func_020ad3a0, ObjShadow_FreeAll)

/* func_020ad408: once a frame: the lean of the object shadows by the time of day (the minutes
 * since the last 6 o'clock, over 12 hours, from -1 to 1), the object shadows' matrix (the view's
 * scaled by 32) and its normalized rows, and the alpha of both kinds of shadow: the scene's
 * base (func_020655c4) plus up to 16 for a brighter colour from func_0206586c (the sum of its
 * channels over 93), at most 31.
 * QUIRK: the lean is multiplied by 1 (FX_MulFunc), and the alpha's sum cut to 8 bits before
 * the cap. */
void ShadowLight_Update(void)
{
    Time now;
    func_0209def4(&now);
    int minutes = now.minute + 60 * ((now.hour + 6) % 12);
    data_021f47d0 = FX_MulFunc((int) ((u32) (FX_Div(minutes << 12, 720 << 12) - 0x800) << 1), FX_ONE);

    Mtx43_Translation(&data_021fbe48, 0, 0, 0);
    Mtx43_Scale(&data_021fbe48, 32 << 12, 32 << 12, 32 << 12);
    MTX_Concat43(&data_021fbe48, &data_0213fee4, &data_021f486c);
    ShadowLight_NormalizeRows((const Vec3 *) &data_021f486c, data_021f4848);

    u16 colour = (u16) func_0206586c();
    u8 channels = (u8) ((colour & 0x1f) + ((colour >> 5) & 0x1f) + ((colour >> 10) & 0x1f));
    u8 extra = (u8) (FX_MulFunc(16 << 12, FX_Div(channels << 12, 93 << 12)) >> 12);
    u8 alpha = (u8) (func_020655c4(0) + extra);
    if (alpha > SHADOW_ALPHA_MAX) {
        alpha = SHADOW_ALPHA_MAX;
    }
    data_020e4104 = alpha;
    data_020e4100 = alpha;
}
CLEAN_AS(func_020ad408, ShadowLight_Update)

/* func_020ad4fc: unless `load` is 0, loads /shadow/tex_shadow.nsbtx, places its textures in
 * VRAM and keeps the texture block in data_021c9b24's heap (the file is freed), reads the
 * three textures' parameters with their palettes ("<name>_pl"), and sets the five strips up
 * with the origin (0, 0, 0x1000): trees of sizes 2-4 with texture 2 from 2 to 0 of its width,
 * the wide and narrow ones with texture 0 whole. */
void ObjShadow_LoadAll(int load)
{
    void *heap = data_021c9b24;
    if (load == 0) {
        return;
    }
    data_021f47d0 = 0;

    u8 *file = func_02064b18(data_020e412c);
    u8 *block = func_021077e8(file);
    func_02056064(block, 0);
    block = func_020561cc(block, heap);
    Heap_FreeCurrent(file);

    ShadowTexture *texture = data_021f49a0;
    for (int i = 0; i < SHADOW_TEXTURES; i++) {
        const ShadowTextureEntry *entry = &data_020d1df4[i];
        const char *name = data_020d1df4[i].name;
        char palette_name[0x24];
        func_02064328(palette_name, data_020e4148, name);
        texture->block = NULL;
        texture->image_param = 0;
        texture->palette_base = 0;
        texture->block = block;
        texture->polygon_id = entry->polygon_id;
        int tex_index = func_02057a40(texture->block, name);
        int pal_index = func_020579b8(texture->block, palette_name);

        /* NNSG3dResTex: the texture dictionary at 0x3c, its entries (texImageParam first) */
        const u8 *res = texture->block;
        const u8 *tex_dict = res + 0x3c;
        const u8 *tex_entries = tex_dict + *(const u16 *) (res + 0x42);
        const u32 *image = (const u32 *) (tex_entries + 4 + *(const u16 *) tex_entries * tex_index);
        /* the palette dictionary at plttInfo.ofsDict (0x34), its entries (the offset first) */
        const u8 *pal_dict = res + *(const u16 *) (res + 0x34);
        const u8 *pal_entries = pal_dict + *(const u16 *) (pal_dict + 6);
        u16 pal_offset = *(const u16 *) (pal_entries + 4 + *(const u16 *) pal_entries * pal_index);
        u16 pal_vram = (u16) * (const u32 *) (res + 0x2c); /* plttInfo.vramKey */

        texture->image_param = *image + (u16) * (const u32 *) (res + 0x08); /* texInfo.vramKey */
        texture->palette_base = (u32) pal_offset + pal_vram;
        texture->image_param |= (u32) entry->flip << 18;
        texture->image_param |= (u32) entry->repeat << 16;
        texture->format = (*image >> 26) & 7;
        if (texture->format != 2) { /* palettes of 4 colours count in 8 bytes, others 16 */
            texture->palette_base >>= 1;
        }
        texture->width = (u16) (1 << (((*image >> 20) & 7) + 3));
        texture->height = (u16) (1 << (((*image >> 23) & 7) + 3));
        texture++;
    }

    if ((data_021f47d8 & 1) == 0) {
        data_021f47e8.x = 0;
        data_021f47e8.y = 0;
        data_021f47e8.z = FX_ONE;
        __register_global_object(&data_021f47e8, func_020012dc, data_021f4800);
        data_021f47d8 |= 1;
    }
    ObjShadow_Init(&data_021f4904, &data_021f47e8, 0x119a, 0x119a, 2, 0x2000, 0, heap);
    ObjShadow_Init(&data_021f4938, &data_021f47e8, 0x1666, 0x1666, 2, 0x2000, 0, heap);
    ObjShadow_Init(&data_021f496c, &data_021f47e8, 0x2000, 0x2000, 2, 0x2000, 0, heap);
    ObjShadow_Init(&data_021f489c, &data_021f47e8, 0x1ccc, 0x1ccc, 0, 0, 0, heap);
    ObjShadow_Init(&data_021f48d0, &data_021f47e8, 0x555, 0x1000, 0, 0, 0, heap);
}
CLEAN_AS(func_020ad4fc, ObjShadow_LoadAll)

/* func_020ad720: the first three rows of a matrix, each normalized. */
void ShadowLight_NormalizeRows(const Vec3 *rows, Vec3 *normalized)
{
    VEC_Normalize(&rows[0], &normalized[0]);
    VEC_Normalize(&rows[1], &normalized[1]);
    VEC_Normalize(&rows[2], &normalized[2]);
}
CLEAN_AS(func_020ad720, ShadowLight_NormalizeRows)
