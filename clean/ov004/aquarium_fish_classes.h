/* More classes of the museum's aquarium fish (aquarium_fish.h, aquarium_fish_kinds.h), by the
 * kinds the aquarium makes of each (museum_aquarium.c):
 *
 *   kind 37 (vtable 0x02255de4, 0x26c bytes)       keeps within 1.0 of a home of its own,
 *                                                  climbing, coasting and sinking, its pitch
 *                                                  rocking;
 *   kind 35 (vtable 0x02255dfc, 0x278 bytes)       the same with a home of its own, and a point
 *                                                  for its body;
 *   kind 36 (vtable 0x02255e14, 0x28c bytes)       climbs, coasts and sinks, its scale pulsing;
 *                                                  meeting a new fish it darts away, pulsing
 *                                                  faster;
 *   kind 15 (vtable 0x02255e44, 0x210 bytes)       stays at the origin without a body, its
 *                                                  animation speeding up, holding, slowing down
 *                                                  and stopping in turn;
 *   kind 11 (vtable 0x02255e74, 0x214 bytes)       sits on the room's node "hasu1" without a
 *                                                  body, playing its animation a few times with
 *                                                  a sound, then waiting;
 *   kinds 52 to 54 (vtable 0x02255d6c)             swim to and fro along the sea tank at a z of
 *                                                  their own, without a body;
 *   kinds 50 and 51 (vtable 0x02255d84)            swim to and fro along the sea tank without
 *                                                  stopping (the modes of data_ov004_0225946c).
 *
 * Slot 0 of each vtable sets the fish up, slot 1 runs its frame. Kinds 35, 36 and 37 share
 * their climbing (AquariumClimber). */
#ifndef CLEAN_OV004_AQUARIUM_FISH_CLASSES_H
#define CLEAN_OV004_AQUARIUM_FISH_CLASSES_H

#include "aquarium_fish.h"
#include "autoload_2/vector.h"
#include "main/sound_emitter.h"
#include "types.h"

/* AquariumClimber.own.climb, and the ways of AquariumClimber_Drift. */
enum {
    AQUARIUM_CLIMB_UP = 0,    /* it climbs ever faster */
    AQUARIUM_CLIMB_COAST = 1, /* it climbs ever slower, to a stop */
    AQUARIUM_CLIMB_SINK = 2,  /* it sinks ever faster */
};

/* What kinds 35, 36 and 37 share. */
typedef union AquariumClimber {
    AquariumFish base;
    struct {
        u8 head[0x21c];
        int climb_frames; /* 0x21c: frames in its climb */
        u8 pad_220[0x255 - 0x220];
        u8 climb; /* 0x255: AQUARIUM_CLIMB_* */
    } own;
} AquariumClimber;

/* Kind 37. */
typedef union AquariumKind37 {
    AquariumFish base;
    AquariumClimber climber;
    struct {
        u8 head[0x255];
        u8 climb; /* 0x255 */
        u8 pad_256[2];
        Vec3 home;       /* 0x258: it keeps within 1.0 of it */
        u8 pitch_up;     /* 0x264: its pitch rocks up (else down) */
        u8 pad_265[3];   /* 0x265 */
        int pitch_count; /* 0x268 */
    } own;
} AquariumKind37;

/* Kind 35. */
typedef union AquariumKind35 {
    AquariumFish base;
    AquariumClimber climber;
    struct {
        u8 head[0x255];
        u8 climb; /* 0x255 */
        u8 pad_256[2];
        Vec3 home;       /* 0x258: it turns back to it from 1.0 away while it swims on */
        Vec3 body_point; /* 0x264: where its body is (AquariumClimber_PlaceBody) */
        u8 pitch_up;     /* 0x270 */
        u8 pad_271[3];
        int pitch_count; /* 0x274 */
    } own;
} AquariumKind35;

/* AquariumKind36.own.pulse */
enum {
    AQUARIUM_PULSE_START = 0,
    AQUARIUM_PULSE_GROW = 1,   /* its scale grows from the least to 1.0 */
    AQUARIUM_PULSE_SHRINK = 2, /* and shrinks back */
};

/* AquariumKind36.own.dodge */
enum {
    AQUARIUM_DODGE_NONE = 0,
    AQUARIUM_DODGE_START = 1,
    AQUARIUM_DODGE_SPEED_UP = 2,
    AQUARIUM_DODGE_SLOW_DOWN = 3,
};

/* Kind 36. */
typedef union AquariumKind36 {
    AquariumFish base;
    AquariumClimber climber;
    struct {
        u8 head[0x255];
        u8 climb; /* 0x255 */
        u8 pad_256[2];
        Vec3 scale;       /* 0x258: the scale it is drawn at, the same along each axis */
        u8 pulse;         /* 0x264: AQUARIUM_PULSE_* */
        u8 pad_265[3];    /* 0x265 */
        int pulse_frames; /* 0x268 */
        Vec3 body_point;  /* 0x26c: where its body is (AquariumClimber_PlaceBody) */
        fx32 pulse_rate;  /* 0x278: how fast its scale changes, by the frame */
        fx32 least_scale; /* 0x27c */
        u8 pulses;        /* 0x280: fast pulses left */
        u8 dodge;         /* 0x281: AQUARIUM_DODGE_* */
        s16 dodge_yaw;    /* 0x282: set as it starts to dart, not read */
        u8 pitch_up;      /* 0x284 */
        u8 pad_285[3];
        int pitch_count; /* 0x288 */
    } own;
} AquariumKind36;

/* AquariumKind15.own.state: the member function of data_ov004_02259444 it runs. */
enum {
    AQUARIUM_KIND15_START = 0,
    AQUARIUM_KIND15_SPEED_UP = 1,
    AQUARIUM_KIND15_HOLD = 2,
    AQUARIUM_KIND15_SLOW_DOWN = 3,
    AQUARIUM_KIND15_STILL = 4,
};

/* Kind 15: its fields from 0x200 on are its own. */
typedef union AquariumKind15 {
    AquariumFish base;
    struct {
        u8 head[0x200];
        fx32 speed_up;   /* 0x200: what its animation speed grows by, by the frame (times 5) */
        fx32 slow_down;  /* 0x204 */
        fx32 top_speed;  /* 0x208 */
        u8 hold_frames;  /* 0x20c */
        u8 still_frames; /* 0x20d */
        u8 state;        /* 0x20e: AQUARIUM_KIND15_* */
    } own;
} AquariumKind15;

/* AquariumKind11.own.state */
enum {
    AQUARIUM_KIND11_START = 2,
    AQUARIUM_KIND11_PLAY = 4,
    AQUARIUM_KIND11_WAIT = 6,
};

/* Kind 11: its fields from 0x1fc on are its own. */
typedef union AquariumKind11 {
    AquariumFish base;
    struct {
        u8 head[0x1fc];
        SoundSource sound; /* 0x1fc */
        u16 wait_frames;   /* 0x208 */
        u8 loops;          /* 0x20a: the times its animation plays */
        u8 pad_20b;
        fx32 anim_speed; /* 0x20c */
        u8 loops_done;   /* 0x210 */
        u8 state;        /* 0x211: AQUARIUM_KIND11_* */
    } own;
} AquariumKind11;

void AquariumKind37_Swim(AquariumKind37 *fish);
void AquariumKind37_SetUp(AquariumKind37 *fish);
void AquariumKind35_Swim(AquariumKind35 *fish);
void AquariumKind35_SetUp(AquariumKind35 *fish);
AquariumKind15 *AquariumKind15_Still(AquariumKind15 *fish);
void AquariumKind15_SlowDown(AquariumKind15 *fish);
void AquariumKind15_Hold(AquariumKind15 *fish);
void AquariumKind15_SpeedUp(AquariumKind15 *fish);
void AquariumKind15_Start(AquariumKind15 *fish);
void AquariumKind15_Swim(AquariumKind15 *fish);
AquariumKind15 *AquariumKind15_SetUp(AquariumKind15 *fish);
void AquariumKind11_PlayLoops(AquariumKind11 *fish);
void AquariumKind11_StartLoops(AquariumKind11 *fish);
void AquariumKind11_Swim(AquariumKind11 *fish);
void AquariumKind11_SetUp(AquariumKind11 *fish);
void AquariumLaneFish_Pace(AquariumFish *fish, int low, int high);
void AquariumLaneFish_Swim(AquariumFish *fish);
void AquariumLaneFish_SetUp(AquariumFish *fish);
void AquariumNonstopFish_Pace(AquariumFish *fish, int left, int right);
void AquariumNonstopFish_Swim(AquariumFish *fish);
void AquariumNonstopFish_SetUp(AquariumFish *fish);
void AquariumClimber_PlaceBody(AquariumFish *fish, Vec3 *out);
void AquariumKind36_Shrink(AquariumKind36 *fish);
void AquariumKind36_Grow(AquariumKind36 *fish);
void AquariumKind36_StartPulse(AquariumKind36 *fish);
void AquariumKind36_Pulse(AquariumKind36 *fish);
void AquariumKind36_DodgeSlowDown(AquariumKind36 *fish);
void AquariumKind36_DodgeSpeedUp(AquariumKind36 *fish);
void AquariumKind36_StartDodge(AquariumKind36 *fish);
void AquariumKind36_Dodge(AquariumKind36 *fish);
void AquariumClimber_Sway(s16 *pitch, u8 *up, int *count, int most, int rate);
void AquariumKind36_Swim(AquariumKind36 *fish);
void AquariumKind36_SetUp(AquariumKind36 *fish);
void AquariumClimber_Drift(AquariumClimber *fish, int accel, int most, unsigned int way);

#endif
