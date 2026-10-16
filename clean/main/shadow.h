/* The shadows of the field: the round shadow under characters and the long shadows the sun
 * casts behind some objects.
 *
 * A character's shadow is the model /shadow/chara_shadow.nsbmd (held at data_021f472c), drawn
 * flat on the ground under the character, scaled by its size and faded with its height above
 * the ground and its distance from the camera. Each shadow drawn in a frame gets the next
 * polygon ID of 1 to 11, so that overlapping shadows do not darken each other.
 *
 * An object's shadow (ObjShadow) is a strip of quads drawn straight to the geometry engine,
 * textured with one of the three textures of /shadow/tex_shadow.nsbtx (obj_sdw_gr, obj_sdw_fc,
 * obj_sdw_tr), running back from the object along -z and leaning across with the time of day
 * (ShadowLight_Update). Five strips exist, set up together (ObjShadow_LoadAll).
 *
 * Both fade with the light: ShadowLight_Update sets the alpha of both kinds from the colour of
 * the light and the scene's base value, at most 31. */
#ifndef CLEAN_MAIN_SHADOW_H
#define CLEAN_MAIN_SHADOW_H

#include "autoload_2/vector.h"
#include "types.h"

#define SHADOW_TEXTURES 3
#define SHADOW_ALPHA_MAX 31

/* data_021f49a0: a texture of /shadow/tex_shadow.nsbtx as the geometry engine takes it. */
typedef struct ShadowTexture {
    const u8 *block;  /* the texture block, copied to the heap; NULL when not loaded */
    u32 image_param;  /* 0x04: TEXIMAGE_PARAM */
    u32 palette_base; /* 0x08: PLTT_BASE */
    u16 width;        /* 0x0c: in texels */
    u16 height;       /* 0x0e */
    u32 format;       /* 0x10: GX_TEXFMT_* */
    u8 polygon_id;    /* 0x14 */
    u8 pad_15[3];
} ShadowTexture;

/* An object's shadow: rows of two vertices each, `half_width` either side of the object's x,
 * at the distances `lengths` behind it. */
typedef struct ObjShadow {
    Vec3 origin;            /* 0x00: kept, not used for drawing */
    fx32 half_width;        /* 0x0c */
    fx32 fade_range;        /* 0x10: how far from the camera it fades out (Shadow_FadeAlpha) */
    u32 rows;               /* 0x14 */
    fx32 last_z;            /* 0x18: the object's z when `points` were made */
    fx32 *lengths;          /* 0x1c: per row, how far behind the object; one heap block with
                              `row_t` and `points` */
    fx32 s_left;            /* 0x20: the texture's s at the left vertices */
    fx32 s_right;           /* 0x24 */
    fx32 *row_t;            /* 0x28: per row, the texture's t */
    Vec3 *points;           /* 0x2c: per row, its point bent onto the curved world, y and z
                              scaled down by 32 */
    ShadowTexture *texture; /* 0x30: NULL when not set up */
} ObjShadow;

void CharaShadow_DrawUnder(const Vec3 *pos, int size);
void CharaShadow_Draw(const Vec3 *pos, int size, fx32 fade_height, fx32 scale);
void CharaShadow_DrawLevel(const Vec3 *pos, int size, fx32 fade_height, int level);
void CharaShadow_Unload(void);
void CharaShadow_BeginFrame(void);
int CharaShadow_Load(void);
int ObjShadow_Free(ObjShadow *shadow, void *heap);
void ObjShadow_Draw(ObjShadow *shadow, const Vec3 *pos);
int ObjShadow_Init(ObjShadow *shadow, const Vec3 *origin, fx32 width, fx32 length, int texture, fx32 s_left, fx32 s_right,
                   void *heap);
void ObjShadow_Destruct(ObjShadow *shadow);
ObjShadow *ObjShadow_Construct(ObjShadow *shadow);
void ObjShadow_DrawNarrow(const Vec3 *pos);
void ObjShadow_DrawWide(const Vec3 *pos);
void ObjShadow_DrawTree(const Vec3 *pos, u32 size);
int Shadow_CharaAlpha(const Vec3 *pos, int range);
int Shadow_ObjAlpha(const Vec3 *pos, int range);
int Shadow_FadeAlpha(const Vec3 *pos, int range, int alpha);
void ObjShadow_FreeAll(void);
void ShadowLight_Update(void);
void ObjShadow_LoadAll(int load);
void ShadowLight_NormalizeRows(const Vec3 *rows, Vec3 *normalized);

#endif
