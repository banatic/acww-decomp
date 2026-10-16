/* The particle effects of a tile's map object (tile_effects.h). */
#include "tile_effects.h"

#include "acre_map.h"
#include "acre_tile.h"
#include "clean.h"
#include "linked_map_items.h"
#include "map_item.h"
#include "scene_query.h"
#include "sky.h"

static_assert(sizeof(TileEffectsSource) == 0x18, "TileEffectsSource");
static_assert(offsetof(TileEffectsSource, position) == 0x08, "TileEffectsSource.position");
static_assert(offsetof(TileEffectsSource, angle) == 0x14, "TileEffectsSource.angle");
static_assert(offsetof(ParticleEmitter, position) == 0x20, "ParticleEmitter.position");
static_assert(offsetof(ParticleEmitter, axis) == 0x3c, "ParticleEmitter.axis");
static_assert(offsetof(ParticleEmitter, color) == 0x5a, "ParticleEmitter.color");
static_assert(offsetof(ParticleEmitter, misc) == 0x68, "ParticleEmitter.misc");

extern TileEffectsSource data_021c77a0;
/* Each a word holding the set-up function of an effect's emitters: func_02044cc4 and
 * func_02044b88, the ROM's own entries. */
extern void *data_020db76c;
extern void *data_020db768;
/* The set-up function of effects 0x76-0x78 and 0x94. */
extern void *data_020e25d4;
/* The colour of the second effect for each category: of families B and C, else. */
extern const u16 *const data_020db770[];
extern const u16 *const data_020db7a8[];
/* The colour of the first effect for each category and stage. */
extern const u16 *const data_020db78c[];

/* An effect by number started at `position`; `setup` points at the word holding the function
 * that sets each of its emitters up. */
extern int func_02090c2c(int id, const Vec3 *position, const s16 *angle, void *setup);
/* The category of a code: 0-3 its line in the families, 4 for 0x1a, 0x88 and 0xa4, 5 for 0x1d,
 * 6 for 0x1e, 7 for any other. */
extern int func_02049ec4(const u16 *code);
/* The code's place in its line, from 1. */
extern int func_02049d78(const u16 *code);
/* A random number below `range`. */
extern int func_020644cc(int range);

#define TILE_EFFECTS_BRUSH_RANGE 80
#define TILE_EFFECTS_BRUSH_FIRST_ONLY 70 /* of 80: mode 1 */
#define TILE_EFFECTS_SKY_LIGHT 3         /* the sky's light the colours are tinted by */
#define TILE_EFFECTS_TURNED_AXIS_X 0x400
#define TILE_EFFECTS_TURNED_AXIS_Y 0x1000
#define TILE_EFFECTS_EMIT_INTERVAL 2

static int TileEffects_InRange(u32 code, u32 first, u32 last)
{
    return code >= first && code <= last;
}

/* The ARM's 32-bit sum. */
static s32 TileEffects_Add(s32 a, s32 b)
{
    return (s32) ((u32) a + (u32) b);
}

/* The code on a tile of the town, or NULL. */
static u16 *TileEffects_TownCode(const TileEffectsTile *tile)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return NULL;
    }
    int x = tile->x;
    int z = tile->z;
    int acre_x = x >= 0 ? x >> 4 : ~(~x >> 4);
    int acre_z = z >= 0 ? z >> 4 : ~(~z >> 4);
    return AcreTile_ItemInAcre(town, (u32) acre_x, (u32) acre_z, x & 0xf, z & 0xf, 0);
}

/* func_0204489c: the effects of a struck tile of the town (mode 1). */
void TileEffects_Strike(const TileEffectsTile *tile)
{
    TileEffectsTile at = *tile;
    TileEffects_StartAt(&at, TILE_EFFECTS_MODE_FIRST);
}
CLEAN_AS(func_0204489c, TileEffects_Strike)

/* func_020448b8: the effects of a tile of the town brushed against: mode 1 when a random number
 * below 80 is below 70, else 0. */
void TileEffects_Brush(const TileEffectsTile *tile)
{
    u16 *code = TileEffects_TownCode(tile);
    if (code == NULL) {
        return;
    }
    int mode = func_020644cc(TILE_EFFECTS_BRUSH_RANGE) < TILE_EFFECTS_BRUSH_FIRST_ONLY ? TILE_EFFECTS_MODE_FIRST
                                                                                       : TILE_EFFECTS_MODE_BOTH;
    TileEffectsTile at = *tile;
    TileEffects_StartFor(code, &at, mode);
}
CLEAN_AS(func_020448b8, TileEffects_Brush)

/* func_02044910: the effects of the code on a tile of the town. */
void TileEffects_StartAt(const TileEffectsTile *tile, int mode)
{
    u16 *code = TileEffects_TownCode(tile);
    if (code == NULL) {
        return;
    }
    TileEffectsTile at = *tile;
    TileEffects_StartFor(code, &at, mode);
}
CLEAN_AS(func_02044910, TileEffects_StartAt)

/* func_02044958: the effects of a code of the families on its tile; in mode 0 the tile is also
 * sent on to the other systems with no item (LinkedMapItems_Set in the current scene). */
void TileEffects_StartFor(u16 *code, const TileEffectsTile *tile, int mode)
{
    if (!MapItem_InFamilies(code)) {
        return;
    }
    TileEffectsTile at = *tile;
    TileEffects_Start(code, &at, 0, mode);
    if (mode == TILE_EFFECTS_MODE_BOTH) {
        LinkedMapItems_Set((u8) tile->x, (u8) tile->z, SceneQuery_Current(), ITEM_CODE_NONE, 0);
    }
}
CLEAN_AS(func_02044958, TileEffects_StartFor)

/* func_020449ac: effect 0x94 at the tile's centre, for code 0xe2. */
void TileEffects_StartE2(const TileEffectsTile *tile)
{
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    func_02090c2c(0x94, &centre, NULL, &data_020e25d4);
}
CLEAN_AS(func_020449ac, TileEffects_StartE2)

/* func_020449d4: the effect of codes 0x1f-0x24 at the tile's centre: 0x77 for 0x1f, 0x78 for
 * 0x20, else 0x76. */
void TileEffects_Start1f(const u16 *code, const TileEffectsTile *tile)
{
    int id;
    switch (*code) {
        case 0x1f:
            id = 0x77;
            break;
        case 0x20:
            id = 0x78;
            break;
        default:
            id = 0x76;
            break;
    }
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    func_02090c2c(id, &centre, NULL, &data_020e25d4);
}
CLEAN_AS(func_020449d4, TileEffects_Start1f)

/* func_02044a14: TileEffects_Start with a copy of the tile. */
void TileEffects_StartTurned(u16 *code, const TileEffectsTile *tile, int angle, int mode)
{
    TileEffectsTile at = *tile;
    TileEffects_Start(code, &at, angle, mode);
}
CLEAN_AS(func_02044a14, TileEffects_StartTurned)

/* func_02044a30: the two effects of `code` at the tile's centre, by its category: 0x44 and
 * 0x6a (category 0), 0x42 and 0x68 (1), 0x3e and 0x64 (2), 0x40 and 0x66 for 0x1c and 0xa5
 * else 0x43 and 0x69 (3), 0x41 and 0x67 (4), 0x3f and 0x65 (5), 0x63 and 0x65 (6). The source
 * is set first (data_021c77a0), the second effect left out in mode 1.
 * REQUIRES: a code of categories 0-6 (MapItem_InFamilies).
 * BUG: for another code (0x89 among the codes 0x6e-0xa5 FieldActor_ActState17 hands on) the
 * original starts the effects whose numbers two of the caller's registers hold; Clean sets the
 * source and starts none. */
void TileEffects_Start(u16 *code, const TileEffectsTile *tile, int angle, int mode)
{
    int category = (u8) func_02049ec4(code);
    int first;
    int second;
    switch (category) {
        case 0:
            first = 0x44;
            second = 0x6a;
            break;
        case 1:
            first = 0x42;
            second = 0x68;
            break;
        case 2:
            first = 0x3e;
            second = 0x64;
            break;
        case 3:
            if (*code == 0x1c || *code == 0xa5) {
                first = 0x40;
                second = 0x66;
            } else {
                first = 0x43;
                second = 0x69;
            }
            break;
        case 4:
            first = 0x41;
            second = 0x67;
            break;
        case 5:
            first = 0x3f;
            second = 0x65;
            break;
        case 6:
            first = 0x63;
            second = 0x65;
            break;
        default:
            first = -1;
            second = -1;
            break;
    }

    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    u32 now = *code;
    int families = 0;
    int stage = 0;
    if (TileEffects_InRange(now, 0x6e, 0xa5)) {
        /* Families B and C, the codes after them (0x88, 0xa4, 0xa5) and 0x89. */
        families = 1;
    } else {
        stage = (u8) func_02049d78(code);
    }
    Vec3 place = centre;
    TileEffects_SetSource(&data_021c77a0, mode, (u8) category, (u8) stage, (u8) families, &place, (s16) angle);
    if (first < 0) {
        return;
    }
    func_02090c2c(first, &centre, NULL, &data_020db76c);
    if (mode != TILE_EFFECTS_MODE_FIRST) {
        func_02090c2c(second, &centre, NULL, &data_020db768);
    }
}
CLEAN_AS(func_02044a30, TileEffects_Start)

/* The sky's light tinted by `tint`: each of the three 5-bit channels the product of both over
 * 31, the top bit the light's. */
static u16 TileEffects_Tint(u16 light, u16 tint)
{
    u32 color = light;
    for (int shift = 0; shift <= 10; shift += 5) {
        u32 product = ((u32) (tint >> shift) & 0x1f) * ((u32) (light >> shift) & 0x1f) / 31;
        color = (color & ~(0x1fu << shift)) | (product << shift);
    }
    return (u16) color;
}

/* The emitter at the source's place (and its resource's own offset), its colour the sky's light
 * tinted by `tint`; in mode 2 its axis (0x400, 0x1000, 0) turned about Y by the source's angle,
 * when that leaves it of some length. */
static void TileEffects_Place(ParticleEmitter *emitter, u16 tint, int first)
{
    const TileEffectsSource *source = &data_021c77a0;
    const Vec3 *offset = &emitter->resource->header->base_pos;
    emitter->position.x = TileEffects_Add(source->position.x, offset->x);
    emitter->position.y = TileEffects_Add(source->position.y, offset->y);
    emitter->position.z = TileEffects_Add(source->position.z, offset->z);
    emitter->color = TileEffects_Tint((u16) Sky_LightColor(TILE_EFFECTS_SKY_LIGHT), tint);
    if (first && source->mode == TILE_EFFECTS_MODE_FIRST) {
        /* The low byte of misc: the frames between emissions. */
        ((u8 *) &emitter->misc)[0] = TILE_EFFECTS_EMIT_INTERVAL;
    }
    if (source->mode == TILE_EFFECTS_MODE_TURNED) {
        Vec3 axis = {TILE_EFFECTS_TURNED_AXIS_X, TILE_EFFECTS_TURNED_AXIS_Y, 0};
        Vec_RotateY(&axis, source->angle);
        if (Vec_NormalizeNonZero(&axis) != 0) {
            emitter->axis.x = (fx16) axis.x;
            emitter->axis.y = (fx16) axis.y;
            emitter->axis.z = (fx16) axis.z;
        }
    }
}

/* func_02044b88: an emitter of the second effect set up, its tint from data_020db770 (families
 * B and C) or data_020db7a8 by the category. */
void TileEffects_SetUpSecond(ParticleEmitter *emitter)
{
    const TileEffectsSource *source = &data_021c77a0;
    u16 tint = source->families != 0 ? *data_020db770[source->category] : *data_020db7a8[source->category];
    TileEffects_Place(emitter, tint, 0);
}
CLEAN_AS(func_02044b88, TileEffects_SetUpSecond)

/* func_02044cc4: an emitter of the first effect set up, its tint from data_020db78c by the
 * category and the stage; in mode 1 it gives off particles every other frame. */
void TileEffects_SetUpFirst(ParticleEmitter *emitter)
{
    const TileEffectsSource *source = &data_021c77a0;
    TileEffects_Place(emitter, data_020db78c[source->category][source->stage], 1);
}
CLEAN_AS(func_02044cc4, TileEffects_SetUpFirst)

/* func_02044df8: the source of the effects about to start. */
void TileEffects_SetSource(TileEffectsSource *source, int mode, u8 category, u8 stage, u8 families, const Vec3 *position,
                           s16 angle)
{
    source->mode = (u32) mode;
    source->category = category;
    source->stage = stage;
    source->families = families;
    source->position.x = position->x;
    source->position.y = position->y;
    source->position.z = position->z;
    source->angle = angle;
}
CLEAN_AS(func_02044df8, TileEffects_SetSource)
