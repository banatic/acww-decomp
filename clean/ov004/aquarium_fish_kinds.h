/* The classes of the museum's aquarium fish (aquarium_fish.h) that swim in a way of their own,
 * by the kinds the aquarium makes of each (museum_aquarium.c):
 *
 *   kind 48 (vtable 0x02255e2c, 0x1fc bytes)   stays in one place, without a body;
 *   kind 47 (vtable 0x02255e5c)                plays its first two animations by turns and turns
 *                                              back from the front and back glass;
 *   kind 10 (vtable 0x02255e8c, 0x220 bytes)   darts about its home, swaying, then glides and
 *                                              rests;
 *   kinds 12 and 38 (vtable 0x02255d3c)        keep near a home of their own, and kind 38 rests
 *                                              at a point beside it from time to time;
 *   kinds 5 and 6 (vtable 0x02255d54)          rise to the surface now and then;
 *   kind 30 (vtable 0x02255d9c)                follows the player along its tank and snaps;
 *   kind 40 (vtable 0x02255dcc)                when touched, plays its animations 1 to 3 in turn,
 *                                              swimming twice as fast meanwhile.
 *
 * Slot 0 of each vtable sets the fish up, slot 1 runs its frame. The bytes of a fish from 0x255
 * on are its class's own. */
#ifndef CLEAN_OV004_AQUARIUM_FISH_KINDS_H
#define CLEAN_OV004_AQUARIUM_FISH_KINDS_H

#include "aquarium_fish.h"
#include "autoload_2/vector.h"
#include "types.h"

/* Kind 47. */
typedef union AquariumKind47 {
    AquariumFish base;
    struct {
        u8 head[0x255];
        u8 may_swim;    /* 0x255: its mode runs (not while it sets off, until its animation ends) */
        u8 second_anim; /* 0x256: its second animation plays */
    } own;
} AquariumKind47;

/* AquariumKind10.own.state */
enum {
    AQUARIUM_KIND10_START = 2,
    AQUARIUM_KIND10_DART = 4,
    AQUARIUM_KIND10_GLIDE = 5,
    AQUARIUM_KIND10_REST = 6,
};

/* Kind 10: its fields from 0x1fc on are its own. */
typedef union AquariumKind10 {
    AquariumFish base;
    struct {
        u8 head[0x1fc];
        Vec3 home; /* 0x1fc: it turns back to it from 1.375 away while darting */
        s16 sway;  /* 0x208: the angle of its sway */
        u8 pad_20a[2];
        fx32 speed;     /* 0x20c */
        u8 dart_frames; /* 0x210 */
        u8 pad_211;
        u16 rest_frames; /* 0x212 */
        u8 pad_214[4];
        fx32 anim_speed; /* 0x218 */
        u8 state;        /* 0x21c: AQUARIUM_KIND10_* */
    } own;
} AquariumKind10;

/* AquariumHomeFish.own.homing */
enum {
    AQUARIUM_HOMING_OFF = 0,
    AQUARIUM_HOMING_GO = 1,    /* it swims slowly to its rest point */
    AQUARIUM_HOMING_HURRY = 2, /* the same, fast */
    AQUARIUM_HOMING_REST = 3,  /* it rests there */
};

/* Kinds 12 and 38. */
typedef union AquariumHomeFish {
    AquariumFish base;
    struct {
        u8 head[0x255];
        u8 at_home; /* 0x255: kind 38 is within 1.0 of its home */
        u8 homing;  /* 0x256: AQUARIUM_HOMING_* */
        u8 pad_257;
        Vec3 home;         /* 0x258: it keeps within 1.0 of it */
        Vec3 rest_point;   /* 0x264 */
        int rest_frames;   /* 0x270 */
        u32 rest_interval; /* 0x274: frames between rests */
        u32 since_rest;    /* 0x278 */
    } own;
} AquariumHomeFish;

/* Kinds 5 and 6. */
typedef union AquariumRisingFish {
    AquariumFish base;
    struct {
        u8 head[0x255];
        u8 rising;    /* 0x255: it rises to the surface (else it swims on) */
        s8 climb;     /* 0x256: 1 up, -1 down */
        u8 frames_up; /* 0x257: frames cruising at the surface */
        u8 stage;     /* 0x258: 0 going up, 1 coming down, 2 setting off down */
        u8 came_down; /* 0x259: it has just come down from the surface */
    } own;
} AquariumRisingFish;

/* AquariumKind30.own.state: the member function of data_ov004_022593f4 it runs. */
enum {
    AQUARIUM_KIND30_WANDER = 0,
    AQUARIUM_KIND30_FOLLOW = 1,
    AQUARIUM_KIND30_SNAP = 2,
};

/* AquariumKind30.own.snap */
enum {
    AQUARIUM_SNAP_WAIT = 0,
    AQUARIUM_SNAP_LUNGE = 1,
    AQUARIUM_SNAP_DRIFT = 2,
};

/* Kind 30. */
typedef union AquariumKind30 {
    AquariumFish base;
    struct {
        u8 head[0x255];
        u8 state;       /* 0x255: AQUARIUM_KIND30_* */
        u8 at_glass;    /* 0x256: it was kept inside its tank this frame */
        u8 snap;        /* 0x257: AQUARIUM_SNAP_* */
        u8 snap_frames; /* 0x258 */
        u8 count;       /* 0x259: frames near the player, or frames the player has stood still */
    } own;
} AquariumKind30;

/* AquariumKind40.own.phase: the joint animation playing. */
enum {
    AQUARIUM_KIND40_CALM = 0,
    AQUARIUM_KIND40_START = 1,
    AQUARIUM_KIND40_HOLD = 2,
    AQUARIUM_KIND40_END = 3,
};

/* Kind 40. */
typedef union AquariumKind40 {
    AquariumFish base;
    struct {
        u8 head[0x255];
        u8 touched;     /* 0x255: it is to start at the end of its animation */
        u8 phase;       /* 0x256: AQUARIUM_KIND40_* */
        u8 hold_frames; /* 0x257 */
        u8 held;        /* 0x258 */
    } own;
} AquariumKind40;

AquariumFish *AquariumKind48_SetUp(AquariumFish *fish);
void AquariumKind47_TurnAtGlass(AquariumFish *fish);
void AquariumKind47_Swim(AquariumKind47 *fish);
void AquariumKind47_SetUp(AquariumKind47 *fish);
void AquariumKind10_Glide(AquariumKind10 *fish);
void AquariumKind10_Dart(AquariumKind10 *fish);
void AquariumKind10_StartDart(AquariumKind10 *fish);
void AquariumKind10_Swim(AquariumKind10 *fish);
AquariumKind10 *AquariumKind10_SetUp(AquariumKind10 *fish);
void AquariumHomeFish_Settle(AquariumHomeFish *fish);
void AquariumHomeFish_GoToRest(AquariumHomeFish *fish, int hurry);
void AquariumHomeFish_RunHoming(AquariumHomeFish *fish);
void AquariumHomeFish_CheckTapped(AquariumHomeFish *fish);
void AquariumHomeFish_SwimKind12(AquariumHomeFish *fish);
void AquariumHomeFish_SwimKind38(AquariumHomeFish *fish);
int *AquariumHomeFish_Swim(AquariumHomeFish *fish);
void AquariumHomeFish_SetUp(AquariumHomeFish *fish);
void AquariumRisingFish_Climb(AquariumRisingFish *fish);
void AquariumRisingFish_Rise(AquariumRisingFish *fish);
void AquariumRisingFish_Wander(AquariumRisingFish *fish);
void AquariumRisingFish_Swim(AquariumRisingFish *fish);
void AquariumRisingFish_SetUp(AquariumRisingFish *fish);
void AquariumKind30_Drift(AquariumKind30 *fish);
int AquariumKind30_Lunge(AquariumKind30 *fish);
void AquariumKind30_Wait(AquariumKind30 *fish);
void AquariumKind30_Bob(AquariumKind30 *fish);
void AquariumKind30_Snap(AquariumKind30 *fish);
void AquariumKind30_Follow(AquariumKind30 *fish);
void AquariumKind30_Wander(AquariumKind30 *fish);
void AquariumKind30_Swim(AquariumKind30 *fish);
void AquariumKind30_SetUp(AquariumKind30 *fish);
void AquariumKind40_Swim(AquariumKind40 *fish);
void AquariumKind40_SetUp(AquariumKind40 *fish);

#endif
