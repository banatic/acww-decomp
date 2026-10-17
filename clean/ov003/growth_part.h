/* Overlay 3's particle effects of the growth models (growth_model.h): two parts at
 * data_ov003_0223cfa0 (0x20 bytes each), each started by a growth model that plays (once, or
 * twice in modes 4-7) and kept by the effect system (main/effect_system.h) as a kept set.
 *
 * GrowthPart_StartFirst starts a set by the code's group (0x22, or 0x24 in some periods of the
 * day for the trees of group 0; 0x25; 0x27); GrowthPart_StartSecond, only in the periods
 * data_ov003_02236b1c marks, a set of data_ov003_022368ec by group. A part only starts when the
 * table data_ov003_02239f68 has a look for its group, motion, stage and which-part. Each frame
 * the effect system follows the instances (GrowthPart_Follow, GrowthPart_FollowAging): the
 * emitter is placed on the part's motion (rising, or swinging about the tile in modes 4-7),
 * and the part ends once its life runs out. Which effect each set shows is not read from this
 * code. */
#ifndef CLEAN_OV003_GROWTH_PART_H
#define CLEAN_OV003_GROWTH_PART_H

#include "autoload_2/particle.h"
#include "autoload_2/vector.h"
#include "main/effect_system.h"
#include "main/tile_changes.h" /* TileChangesTile */
#include "types.h"

/* GrowthPart.group of a free part. */
#define GROWTH_PART_FREE 3
#define GROWTH_PART_COUNT 2

/* GrowthPart.motion: by mode (data_ov003_0223ac00) at the first start: 1 for mode 0, 0 for
 * mode 1 and 2 for modes 2 and 3 (the emitter above the tile), and these two: */
#define GROWTH_PART_SWING_IN 3 /* modes 4-7: the emitter turns about the tile to an end angle */
#define GROWTH_PART_SWING 4    /* a second start: at the end angle from the start */

typedef struct GrowthPart {
    int group;     /* 0x00: 0 trees, 1 the lines 0x5d-0x65 and 0x6b/0x6d, 2 lines 0xc8-0xd3;
                    * GROWTH_PART_FREE when free */
    int first;     /* 0x04: 1 for a part GrowthPart_StartFirst started, 0 for the second */
    int motion;    /* 0x08: 0-2, GROWTH_PART_SWING_IN or GROWTH_PART_SWING */
    u8 stage;      /* 0x0c: the growth model's stage */
    s8 life;       /* 0x0d: frames left (GrowthPart_FollowAging); below 0 the part ends */
    s8 frames;     /* 0x0e: frames followed (GrowthPart_FollowAging) */
    u8 mode;       /* 0x0f: the growth model's mode */
    int variant;   /* 0x10: the tile's parity for trees, 3 for groups 1 and 2, 2 otherwise */
    Vec3 position; /* 0x14: the tile's centre */
} GrowthPart;

typedef struct GrowthParts {
    GrowthPart parts[GROWTH_PART_COUNT]; /* 0x00 */
    int taken;                           /* 0x40: the part being started, -1 between starts */
} GrowthParts;

/* A look of the table data_ov003_02239f68: what a part's emitter starts with. */
typedef struct GrowthPartLook {
    int life;          /* 0x00 */
    u16 misc;          /* 0x04: the low byte of the emitter's misc word */
    u16 particle_life; /* 0x06 */
    s16 axis_speed;    /* 0x08 */
} GrowthPartLook;

void GrowthPart_InitAll(GrowthParts *parts);
GrowthPart *GrowthPart_StartFirst(GrowthParts *parts, int mode, int stage, const u16 *item, const TileChangesTile *tile,
                                  int count);
GrowthPart *GrowthPart_StartSecond(GrowthParts *parts, int mode, int stage, const u16 *item, const TileChangesTile *tile,
                                   int count);
void GrowthPart_Choose(GrowthParts *parts, GrowthPart *part, int *group, int *set, Vec3 *position, const u16 *item,
                       const TileChangesTile *tile);
GrowthPart *GrowthPart_TakeFree(GrowthParts *parts);
int GrowthPart_Follow(EffectSystemInstance *instance);
int GrowthPart_FollowAging(EffectSystemInstance *instance);
void GrowthPart_Place(EffectSystemInstance *instance);
void GrowthPart_PlaceEmitter(GrowthPart *part, ParticleEmitter *emitter);
void GrowthPart_SetUpEmitter(GrowthPart *part, ParticleEmitter *emitter);
const GrowthPartLook *GrowthPart_Look(const GrowthPart *part);
void GrowthPart_Set(GrowthPart *part, int group, int first, int mode, int stage, const Vec3 *position, int again);
void GrowthPart_Free(GrowthPart *part);

#endif
