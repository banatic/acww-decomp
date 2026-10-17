/* Overlay 3's particle effects of the growth models (growth_part.h). */
#include "growth_part.h"

#include "clean.h"
#include "main/acre_tile.h"
#include "main/town_record.h"

static_assert(sizeof(GrowthPart) == 0x20, "a part");
static_assert(offsetof(GrowthPart, variant) == 0x10, "variant");
static_assert(offsetof(GrowthParts, taken) == 0x40, "taken");
static_assert(offsetof(GrowthPartLook, axis_speed) == 0x08, "axis_speed");
static_assert(offsetof(EffectSystemInstance, emitter) == 0x0c, "emitter");
static_assert(offsetof(ParticleEmitter, radius) == 0x44, "radius");
static_assert(offsetof(ParticleEmitter, axis_speed) == 0x50, "axis_speed");
static_assert(offsetof(ParticleEmitter, particle_life) == 0x58, "particle_life");
static_assert(offsetof(ParticleEmitter, misc) == 0x68, "misc");
static_assert(offsetof(ParticleEmitter, user_data) == 0x80, "user_data");

/* The parts. */
extern GrowthParts data_ov003_0223cfa0;
/* The kept sets' set-ups (two words for each of two emitters): GrowthPart_Place, then
 * GrowthPart_FollowAging or GrowthPart_Follow, as the game's symbols. */
typedef struct GrowthPartSetups {
    void *words[4];
} GrowthPartSetups;
extern const GrowthPartSetups data_ov003_0223a1b8; /* the first start's */
extern const GrowthPartSetups data_ov003_0223a188; /* the second start's */
/* The motion by mode of a first start. */
extern const int data_ov003_0223ac00[];
/* Whether group 0 starts set 0x24 instead of 0x22, by the tile's parity (rows of 23) and the
 * period of the day. */
extern const u8 data_ov003_02236b88[];
#define GROWTH_PART_PERIODS 23
/* Whether the second start happens, by the period of the day. */
extern const u8 data_ov003_02236b1c[];
/* The second start's set by group. */
extern const int data_ov003_022368ec[];
/* The emitter's distance from the tile's centre and its radius, by group and stage. */
extern const int data_ov003_02236bb8[][4];
extern const int data_ov003_02236be8[][4];
/* The looks: by group, motion, stage and which part (GrowthPart.first), each level NULL for
 * none. */
typedef const GrowthPartLook *const *GrowthPartLookPair;
typedef const GrowthPartLookPair *GrowthPartLookStages;
typedef const GrowthPartLookStages *GrowthPartLookMotions;
extern const GrowthPartLookMotions data_ov003_02239f68[];
/* NitroSDK's table of sines and cosines, by angle >> 4. */
extern const fx16 FX_SinCosTable_[];

/* The sets of a first start. */
#define GROWTH_PART_SET_TREE 0x22
#define GROWTH_PART_SET_TREE_PERIOD 0x24
#define GROWTH_PART_SET_GROUP_1 0x25
#define GROWTH_PART_SET_GROUP_2 0x27

/* Writes the low byte of a word (the DS is little-endian). */
static void growth_part_set_low_byte(void *word, u8 value)
{
    *(u8 *) word = value;
}

/* func_ov003_02223c58: both parts free and none being started. */
void GrowthPart_InitAll(GrowthParts *parts)
{
    for (int i = 0; i < GROWTH_PART_COUNT; i++) {
        GrowthPart_Free(&parts->parts[i]);
    }
    parts->taken = -1;
}
CLEAN_AS(func_ov003_02223c58, GrowthPart_InitAll)

/* func_ov003_02223c7c: the first part of a growth model of `mode` at `stage` (the code `item`
 * at `tile`; `count`: the times the model started parts before): a free part (none: NULL)
 * takes the group and set of the code (GrowthPart_Choose), the tile's centre, its motion by
 * mode (GROWTH_PART_SWING after the first time); when the table has a look for it, the set
 * starts at the tile's centre with the set-ups of data_ov003_0223a1b8, else the part is free
 * again. */
GrowthPart *GrowthPart_StartFirst(GrowthParts *parts, int mode, int stage, const u16 *item, const TileChangesTile *tile,
                                  int count)
{
    GrowthPartSetups setups = data_ov003_0223a1b8;
    GrowthPart *part = GrowthPart_TakeFree(parts);
    if (part == NULL) {
        return NULL;
    }
    TileChangesTile at = *tile;
    int group;
    int set;
    Vec3 position;
    GrowthPart_Choose(parts, part, &group, &set, &position, item, &at);
    Vec3 start = position;
    GrowthPart_Set(part, group, 1, mode, stage, &start, count);
    if (GrowthPart_Look(part) != NULL) {
        EffectSystem_StartKeptSet(set, &position, NULL, setups.words);
    } else {
        part->group = GROWTH_PART_FREE;
    }
    parts->taken = -1;
    return part;
}
CLEAN_AS(func_ov003_02223c7c, GrowthPart_StartFirst)

/* func_ov003_02223d14: the second part, as GrowthPart_StartFirst but only in the periods of the
 * day data_ov003_02236b1c marks (else NULL), with the set of its group from
 * data_ov003_022368ec and the set-ups of data_ov003_0223a188. */
GrowthPart *GrowthPart_StartSecond(GrowthParts *parts, int mode, int stage, const u16 *item, const TileChangesTile *tile,
                                   int count)
{
    GrowthPartSetups setups = data_ov003_0223a188;
    if (data_ov003_02236b1c[TownRecord_Period()] == 0) {
        return NULL;
    }
    GrowthPart *part = GrowthPart_TakeFree(parts);
    if (part == NULL) {
        return NULL;
    }
    TileChangesTile at = *tile;
    int group;
    int unused_set;
    Vec3 position;
    GrowthPart_Choose(parts, part, &group, &unused_set, &position, item, &at);
    Vec3 start = position;
    GrowthPart_Set(part, group, 0, mode, stage, &start, count);
    if (GrowthPart_Look(part) != NULL) {
        EffectSystem_StartKeptSet(data_ov003_022368ec[group], &position, NULL, setups.words);
    } else {
        part->group = GROWTH_PART_FREE;
    }
    parts->taken = -1;
    return part;
}
CLEAN_AS(func_ov003_02223d14, GrowthPart_StartSecond)

/* func_ov003_02223dc8: the group, variant and first set of the code `item`: the lines
 * 0x26-0x2e and code 0x67 group 0 with the tile's parity, set 0x22 (0x24 when
 * data_ov003_02236b88 marks the parity and the period of the day); the lines 0x5d-0x65 and codes
 * 0x6b and 0x6d group 1, variant 3, set 0x25; the lines 0xc8-0xd3 group 2, variant 3, set
 * 0x27; any other code group 0, variant 2, set 0x22. `position` becomes the tile's centre. */
void GrowthPart_Choose(GrowthParts *parts, GrowthPart *part, int *group, int *set, Vec3 *position, const u16 *item,
                       const TileChangesTile *tile)
{
    (void) parts;
    u8 period = TownRecord_Period();
    u16 code = *item;
    if ((code >= 0x26 && code <= 0x2e) || code == 0x67) {
        int parity = (tile->x ^ tile->z) & 1;
        *group = 0;
        part->variant = parity;
        *set = data_ov003_02236b88[parity * GROWTH_PART_PERIODS + period] != 0 ? GROWTH_PART_SET_TREE_PERIOD
                                                                               : GROWTH_PART_SET_TREE;
    } else if ((code >= 0x5d && code <= 0x65) || code == 0x6d || code == 0x6b) {
        *group = 1;
        part->variant = 3;
        *set = GROWTH_PART_SET_GROUP_1;
    } else if (code >= 0xc8 && code <= 0xd3) {
        *group = 2;
        part->variant = 3;
        *set = GROWTH_PART_SET_GROUP_2;
    } else {
        *group = 0;
        part->variant = 2;
        *set = GROWTH_PART_SET_TREE;
    }
    AcreTile_TileCentre(position, (u32) tile->x, (u32) tile->z);
}
CLEAN_AS(func_ov003_02223dc8, GrowthPart_Choose)

/* func_ov003_02223e88: the first free part, which becomes the one being started; NULL when both
 * are taken. */
GrowthPart *GrowthPart_TakeFree(GrowthParts *parts)
{
    for (int i = 0; i < GROWTH_PART_COUNT; i++) {
        if (parts->parts[i].group == GROWTH_PART_FREE) {
            parts->taken = i;
            return &parts->parts[i];
        }
    }
    return NULL;
}
CLEAN_AS(func_ov003_02223e88, GrowthPart_TakeFree)

/* func_ov003_02223ea8 (the follow function of the second emitters): the instance is followed
 * as the effect system's (EffectSystem_FollowTinted); while its part (the instance's byte 0x0a)
 * is not free its emitter is placed (GrowthPart_PlaceEmitter) and the answer is 1; then 0. */
int GrowthPart_Follow(EffectSystemInstance *instance)
{
    EffectSystem_FollowTinted(instance);
    GrowthPart *part = &data_ov003_0223cfa0.parts[instance->unk_0a[0]];
    if (part->group == GROWTH_PART_FREE) {
        return 0;
    }
    GrowthPart_PlaceEmitter(part, instance->emitter);
    return 1;
}
CLEAN_AS(func_ov003_02223ea8, GrowthPart_Follow)

/* func_ov003_02223edc (the follow function of the first emitters): the part loses a frame of
 * life (when none is left it is free) and counts a frame; then GrowthPart_Follow. */
int GrowthPart_FollowAging(EffectSystemInstance *instance)
{
    GrowthPart *part = &data_ov003_0223cfa0.parts[instance->unk_0a[0]];
    int life = part->life;
    if (life - 1 < 0) {
        part->group = GROWTH_PART_FREE;
    }
    part->life = (s8) (life - 1);
    part->frames = (s8) (part->frames + 1);
    return GrowthPart_Follow(instance);
}
CLEAN_AS(func_ov003_02223edc, GrowthPart_FollowAging)

/* func_ov003_02223f0c (the place function of all the emitters): the instance placed as the
 * effect system's (EffectSystem_PlaceInstance), then given the part being started (part 0
 * when none is), its byte 0x0a naming it; its emitter is placed (GrowthPart_PlaceEmitter) and
 * set up from the part's look (GrowthPart_SetUpEmitter), with the radius of the part's group
 * and stage and the variant in the low byte of its user data. */
void GrowthPart_Place(EffectSystemInstance *instance)
{
    ParticleEmitter *emitter = instance->emitter;
    EffectSystem_PlaceInstance(instance);
    instance->unk_0a[0] = (u8) data_ov003_0223cfa0.taken;
    int index = data_ov003_0223cfa0.taken;
    if (index < 0) {
        index = 0;
    }
    GrowthPart *part = &data_ov003_0223cfa0.parts[index];
    GrowthPart_PlaceEmitter(part, emitter);
    instance->unk_0a[0] = (u8) index;
    GrowthPart_SetUpEmitter(part, emitter);
    emitter->radius = data_ov003_02236be8[part->group][part->stage];
    growth_part_set_low_byte(&emitter->user_data, (u8) part->variant);
}
CLEAN_AS(func_ov003_02223f0c, GrowthPart_Place)

/* func_ov003_02223f6c: the emitter's position: the part's position plus the distance of its
 * group and stage (data_ov003_02236bb8), straight up, or for GROWTH_PART_SWING_IN and
 * GROWTH_PART_SWING turned about Z by an end angle by mode (-0x4000 for 4, 0x4000 for 5,
 * -0x2000 for 6, 0x2000 for 7); GROWTH_PART_SWING_IN reaches it in 16 frames (modes 4 and 5)
 * or 9 (modes 6 and 7), in steps of the end angle times the frames over that count. Then plus
 * the base position of the emitter's resource.
 * REQUIRES: the two swinging motions only in modes 4-7 (as data_ov003_0223ac00 and the growth
 * models give them); for other modes the original turns by values it never set (here 0). */
void GrowthPart_PlaceEmitter(GrowthPart *part, ParticleEmitter *emitter)
{
    int distance = data_ov003_02236bb8[part->group][part->stage];
    Vec3 position;
    if (part->motion == GROWTH_PART_SWING_IN || part->motion == GROWTH_PART_SWING) {
        int angle = 0;
        int frames_to_end = 16;
        switch (part->mode) {
            case 4:
                angle = -0x4000;
                break;
            case 5:
                angle = 0x4000;
                break;
            case 6:
                angle = -0x2000;
                frames_to_end = 9;
                break;
            case 7:
                angle = 0x2000;
                frames_to_end = 9;
                break;
        }
        if (part->motion == GROWTH_PART_SWING_IN && part->frames < frames_to_end) {
            angle = (s16) (part->frames * angle / frames_to_end);
        }
        int index = ((u16) angle >> 4) * 2;
        position.x = part->position.x + (FX_SinCosTable_[index] * distance >> 12);
        position.y = part->position.y + (FX_SinCosTable_[index + 1] * distance >> 12);
        position.z = part->position.z;
    } else {
        position.x = part->position.x;
        position.y = part->position.y + distance;
        position.z = part->position.z;
    }
    const Vec3 *base = &emitter->resource->header->base_pos;
    emitter->position.x = position.x + base->x;
    emitter->position.y = position.y + base->y;
    emitter->position.z = position.z + base->z;
}
CLEAN_AS(func_ov003_02223f6c, GrowthPart_PlaceEmitter)

/* func_ov003_0222409c: the emitter takes the part's look (the low byte of its misc word, its
 * particles' life, its axis speed) and the part its life.
 * REQUIRES: the part has a look (only such parts start). */
void GrowthPart_SetUpEmitter(GrowthPart *part, ParticleEmitter *emitter)
{
    const GrowthPartLook *look = GrowthPart_Look(part);
    growth_part_set_low_byte(&emitter->misc, (u8) look->misc);
    emitter->particle_life = look->particle_life;
    emitter->axis_speed = look->axis_speed;
    part->life = (s8) look->life;
}
CLEAN_AS(func_ov003_0222409c, GrowthPart_SetUpEmitter)

/* func_ov003_022240cc: the part's look, or NULL. */
const GrowthPartLook *GrowthPart_Look(const GrowthPart *part)
{
    GrowthPartLookMotions motions = data_ov003_02239f68[part->group];
    if (motions == NULL) {
        return NULL;
    }
    GrowthPartLookStages stages = motions[part->motion];
    if (stages == NULL) {
        return NULL;
    }
    GrowthPartLookPair pair = stages[part->stage];
    if (pair == NULL) {
        return NULL;
    }
    return pair[part->first];
}
CLEAN_AS(func_ov003_022240cc, GrowthPart_Look)

/* func_ov003_022240fc: the part set for a start: no frames yet, its motion by mode
 * (data_ov003_0223ac00), or GROWTH_PART_SWING when `again` is set. */
void GrowthPart_Set(GrowthPart *part, int group, int first, int mode, int stage, const Vec3 *position, int again)
{
    part->group = group;
    part->first = first;
    part->frames = 0;
    /* A field at a time, as the ROM copies (the point may overlap the part). */
    part->position.x = position->x;
    part->position.y = position->y;
    part->position.z = position->z;
    part->mode = (u8) mode;
    part->motion = again == 0 ? data_ov003_0223ac00[mode] : GROWTH_PART_SWING;
    part->stage = (u8) stage;
}
CLEAN_AS(func_ov003_022240fc, GrowthPart_Set)

/* func_ov003_02224138: the part free. */
void GrowthPart_Free(GrowthPart *part)
{
    part->group = GROWTH_PART_FREE;
}
CLEAN_AS(func_ov003_02224138, GrowthPart_Free)
