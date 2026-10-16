/* What each of the sky's objects does by its kind (sky_objects.h): the three tables of member
 * functions an object is set up, run and taken down through (SkyObjectKinds_SetUp,
 * SkyObjectKinds_Run, SkyObjectKinds_TakeDown, one entry per kind 0 to 12), and what the
 * kinds' functions share:
 *
 * - an entry made free (SkyObjectKinds_Remove: its slot released) and its fields reset;
 * - its cell animation started from the table data_020e7880 (SkyObjectKinds_StartAnimation);
 * - a path across the town's six acres, west to east or back (SkyObjectKinds_StartPath,
 *   SkyObjectKinds_Advance), placed on the sky (SkyObjectKinds_Place): the farther north of the
 *   point the camera looks at, the lower (towards the horizon) and smaller, bobbing by a sine;
 * - sounds from the object, heard from its point (SkyObjectKinds_Play and the others).
 *
 * Kind 12's functions are here (SkyKind12_...), the shots' (kind 11) in sky_shots.h. */
#ifndef CLEAN_MAIN_SKY_OBJECT_KINDS_H
#define CLEAN_MAIN_SKY_OBJECT_KINDS_H

#include "autoload_2/vector.h"
#include "screen_icon.h" /* CellAnim */
#include "sky_objects.h"
#include "types.h"

#define SKY_OBJECT_KINDS 13            /* the kinds the tables have an entry for, 0 to 12 */
#define SKY_ANIMATION_NONE 0x2e        /* SkyObjectBody.animation: none */
#define SKY_OBJECT_VIEW_MIN (-0xa000)  /* an object is out of view left of x -10 or above y -10 */
#define SKY_OBJECT_VIEW_RIGHT 0x10a000 /* right of x 266 */
#define SKY_OBJECT_VIEW_BOTTOM 0xca000 /* below y 202 */

/* An entry of data_020e7880: a cell animation. */
typedef struct SkyAnimation {
    const void *cells; /* 0x00 */
    s32 count;         /* 0x04 */
    s32 hold;          /* 0x08: stop on the last frame */
} SkyAnimation;

/* A SkyObject (the same 0x74 bytes) with the fields the kinds' functions use named. */
typedef struct SkyObjectBody {
    s32 kind;      /* 0x00 */
    s32 state;     /* 0x04 */
    s32 resource;  /* 0x08 */
    s32 animation; /* 0x0c: in data_020e7880 */
    CellAnim anim; /* 0x10 */
    s32 slot;      /* 0x24 */
    s32 distance;  /* 0x28: along its path (SkyObjectKinds_Advance) */
    u16 phase;     /* 0x2c: the angle of its bobbing */
    u8 forward;    /* 0x2e: it goes west to east along the path */
    u8 can_hit;    /* 0x2f: a shot that can hit (SkyShots_HitsBox) */
    u8 hit;        /* 0x30: a shot that hit */
    u8 hidden;     /* 0x31 */
    u8 unk_32[2];  /* 0x32 */
    Vec3 position; /* 0x34 */
    Vec3 velocity; /* 0x40 */
    fx32 scale_x;  /* 0x4c */
    fx32 scale_y;  /* 0x50 */
    u16 rotation;  /* 0x54 */
    u8 unk_56;     /* 0x56 */
    u8 unk_57;     /* 0x57 */
    s32 priority;  /* 0x58 */
    u8 radius;     /* 0x5c */
    s8 palette;    /* 0x5d */
    u8 unk_5e[2];  /* 0x5e */
    union {
        u32 words[5];    /* 0x60 */
        struct {         /* kind 12 */
            u32 param;   /* 0x60 */
            s32 delay;   /* 0x64: frames before it moves */
            u32 unk_68;  /* 0x68 */
            fx32 pull_x; /* 0x6c: added to the velocity each frame */
            fx32 pull_y; /* 0x70 */
        };
        struct {             /* a shot (kind 11) */
            s32 shot_timer;  /* 0x60: frames before it moves */
            s32 shot_player; /* 0x64 */
            u32 shot_flags;  /* 0x68: its parameter, bit 31: fired far from the camera */
        };
    };
} SkyObjectBody;

static inline SkyObjectBody *SkyObject_Body(SkyObject *object)
{
    return (SkyObjectBody *) (void *) object;
}

/* Out of view: left of x -10, right of x 266, above y -10 or below y 202. */
static inline int SkyObject_OutOfView(const Vec3 *position)
{
    return position->y < SKY_OBJECT_VIEW_MIN || position->y > SKY_OBJECT_VIEW_BOTTOM || position->x < SKY_OBJECT_VIEW_MIN ||
           position->x > SKY_OBJECT_VIEW_RIGHT;
}

void SkyObjectKinds_PlayHeldAt(SkyObject *object, int index, int number);
void SkyObjectKinds_Play(SkyObject *object, int number);
void SkyObjectKinds_PlayHeld(SkyObject *object, int number);
int SkyObjectKinds_FlatPoint(const SkyObject *object, Vec3 *point);
void SkyObjectKinds_DepthPoint(const SkyObject *object, Vec3 *point);
void SkyObjectKinds_SoundPoint(Vec3 *point, fx32 x, fx32 y, fx32 scale);
void SkyObjectKinds_PlaceOnPath(SkyObject *object, fx32 sway);
void SkyObjectKinds_Place(SkyObject *object, const Vec3 *at, fx32 sway);
int SkyObjectKinds_Advance(SkyObject *object, int step, fx32 sway, int phase_step);
void SkyObjectKinds_StartPath(SkyObject *object, u8 forward, fx32 sway);
void SkyObjectKinds_Remove(SkyObject *object);
void SkyObjectKinds_StartAnimation(SkyObject *object);
void SkyObjectKinds_TakeDown(SkyObject *object);
void SkyObjectKinds_Run(SkyObject *object);
void SkyObjectKinds_SetUp(SkyObject *object, int param);
void SkyObjectKinds_Free(SkyObject *object);
void SkyObjectKinds_Reset(SkyObject *object);
SkyObject *SkyObjectKinds_Construct(SkyObject *object);
void SkyKind12_TakeDown(SkyObject *object);
void SkyKind12_Run(SkyObject *object);
void SkyKind12_SetUp(SkyObject *object, int param);
void SkyKind10_TakeDown(SkyObject *object);

/* Kind 10 (entry 32, kept by SkyEvents_UpdateKind10): animation 0x15 at (176, 103), which
 * does nothing more each frame. Kind 8 (entry 59, with the thunder of heavy rain): one of eight animations at a
 * random place of the screen's upper half, done once it has played. */
void SkyKind10_Run(void);
void SkyKind10_SetUp(SkyObject *object);
void SkyKind8_TakeDown(SkyObject *object);
void SkyKind8_Run(SkyObject *object);
void SkyKind8_SetUp(SkyObject *object);

#endif
