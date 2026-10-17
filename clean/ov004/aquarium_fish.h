/* The fish of the museum's aquarium (museum_aquarium.h): one C++ object per kind of fish of
 * the museum's record (index 0-55, item 0x12e8 + index), 0x258 bytes or more, of a class that
 * depends on the kind. Each class's vtable has the fish's set-up (slot 0, reading its swimming
 * values from data_ov004_02247924, AquariumFish_SetSwim), its frame's swim (slot 1) and its
 * two destructors.
 *
 * A fish is a body of the field (FieldPointBody at 0x04, field_body.h) that fish and rocks
 * touch, an animated model (0x64, animated_model.h) loaded from "/fish/<group>/m_fish<index>"
 * into an entry of the aquarium's model pool, and up to four joint animations of its own.
 *
 * Meetings: when its body touches another fish's, both note the meeting
 * (AquariumFish_Meet): the bit of the other's index in `met`, and when the other is bigger
 * (the size byte of the table) or as big and met in a better way, it turns its attention to
 * it (`focus`). AquariumFish_ClearMeetings forgets this frame's at its end. */
#ifndef CLEAN_OV004_AQUARIUM_FISH_H
#define CLEAN_OV004_AQUARIUM_FISH_H

#include "autoload_2/vector.h"
#include "main/animated_model.h"
#include "main/field_body.h"
#include "main/model_pool.h"
#include "types.h"

/* The kinds of fish: those of the river room (the first 35) and of the sea room. */
#define AQUARIUM_FISH_KINDS 56
#define AQUARIUM_RIVER_FISH 35

/* What the table data_ov004_02247924 says of each kind (17 bytes). */
typedef struct AquariumFishInfo {
    u8 size;        /* 0x00: 0-7; the bigger takes another's attention, and weighs more */
    u8 anims;       /* 0x01: the joint animations it loads, 1-4 */
    u8 body_height; /* 0x02: its body's height, in 1/128 units */
    u8 body_radius; /* 0x03: its body's radius, in 1/128 units */
    u8 depth;       /* 0x04: its height in the water, in 1/64 units, 1.0 below */
    u8 swim[11];    /* 0x05: AquariumFish_SetSwim */
    u8 margin;      /* 0x10: how far its ends keep from the glass, in 1/128 units */
} AquariumFishInfo;

/* AquariumFish.state */
enum {
    AQUARIUM_FISH_OFF = 0,     /* not shown */
    AQUARIUM_FISH_LOADING = 1, /* its model is loaded on the next frame */
    AQUARIUM_FISH_SHOWN = 2,
};

/* AquariumFish.mode, as far as read here. */
enum {
    AQUARIUM_FISH_MODE_1 = 1, /* animates at 1.5, does not turn to target_yaw nor mind the ends */
    AQUARIUM_FISH_MODE_2 = 2,
    AQUARIUM_FISH_MODE_3 = 3, /* its animation speed counts its speed three times */
    AQUARIUM_FISH_MODE_5 = 5, /* its animation speed counts a third of its speed */
    AQUARIUM_FISH_MODE_6 = 6, /* becomes 2 at the room's ends */
};

struct AquariumFish;

/* The fish's body: a body at a point (its position), and the fish (vtable 0x02255d28: the
 * position, the identity and AquariumFishBody_Touched). */
typedef struct AquariumFishBody {
    FieldPointBody base;
    struct AquariumFish *owner; /* 0x4c */
} AquariumFishBody;

typedef struct AquariumFish {
    const u32 *vtable;     /* 0x000 */
    AquariumFishBody body; /* 0x004 */
    u8 *anims[4];          /* 0x054: its joint animation files */
    AnimatedModel model;   /* 0x064 */
    int timer;             /* 0x158: frames in its mode (or its class's state) */
    int index;             /* 0x15c: its kind; -1 once released */
    int state;             /* 0x160: AQUARIUM_FISH_* */
    u8 size;               /* 0x164: AquariumFishInfo.size */
    u8 pad_165;            /* 0x165 */
    u16 pool_slot;         /* 0x166: its entry of the aquarium's model pool */
    ModelPoolFiles files;  /* 0x168 */
    Vec3 position;         /* 0x1a8 */
    Vec3 previous;         /* 0x1b4: the position at the end of the last frame */
    s16 yaw;               /* 0x1c0 */
    s16 target_yaw;        /* 0x1c2 */
    s16 pitch;             /* 0x1c4 */
    u8 unk_1c6;            /* 0x1c6: set for the kinds with three animations */
    u8 solid;              /* 0x1c7: its body is entered on the field */
    u8 area;               /* 0x1c8: in the sea room, how wide a part of the tank it keeps to (0-2) */
    u8 yielding;           /* 0x1c9: it makes way for another (yield_to) */
    s8 vertical;           /* 0x1ca: the way it passes another: 1 up, -1 down */
    u8 pad_1cb;
    fx32 level;   /* 0x1cc: the height it passes others at */
    Vec3 ends[2]; /* 0x1d0: its head and its tail */
    u8 focus;     /* 0x1e8: the kind it pays attention to; its own for none */
    u8 yield_to;  /* 0x1e9 */
    u8 meeting;   /* 0x1ea: how it met the one it pays attention to (bit flags) */
    u8 turnbacks; /* 0x1eb: new courses in a row that turned it round from the glass */
    s16 away_yaw; /* 0x1ec */
    u8 mode;      /* 0x1ee: AQUARIUM_FISH_MODE_* */
    u8 pad_1ef;
    u8 hit_glass; /* 0x1f0: an end of it was kept inside the tank this frame */
    u8 meetings;  /* 0x1f1: the fish met this frame */
    u8 pad_1f2[2];
    u32 met[2];       /* 0x1f4: the kinds met this frame, by bit */
    u8 glass_turning; /* 0x1fc: its turn from the glass has begun */
    u8 glass_turn;    /* 0x1fd: AQUARIUM_GLASS_* */
    u8 unk_1fe;       /* 0x1fe */
    u8 pad_1ff;
    s16 glass_step;   /* 0x200: what it turns by each frame from the glass */
    u8 cruise_frames; /* 0x202: how long it cruises (mode 4) */
    u8 rest_frames;   /* 0x203: how long it rests (mode 6) */
    u8 swim_204[4];   /* 0x204 */
    u8 unk_208[4];    /* 0x208 */
    fx32 speed;       /* 0x20c */
    fx32 top_speed;   /* 0x210 */
    int swim_214;     /* 0x214 */
    int swim_218;     /* 0x218 */
    u8 unk_21c[8];    /* 0x21c */
    int swim_224;     /* 0x224 */
    fx32 swim_228;    /* 0x228 */
    u8 unk_22c[3];    /* 0x22c */
    u8 turning;       /* 0x22f: it turns to target_yaw */
    u16 swim_230;     /* 0x230 */
    u8 unk_232[0xa];  /* 0x232 */
    int pitch_steps;  /* 0x23c: how far its pitch has been tilted */
    u8 unk_240[0xc];  /* 0x240 */
    s16 flee_yaw;     /* 0x24c: the way it flees (mode 1) */
    u8 levelling;     /* 0x24e: its pitch goes back to level */
    u8 unk_24f[3];    /* 0x24f */
    u8 last_focus;    /* 0x252: the focus it last reacted to */
    u8 startled;      /* 0x253: it was startled by a tap on the glass */
    u8 focus_frames;  /* 0x254: frames it has kept the same focus */
    u8 unk_255[3];    /* 0x255: the class's own (aquarium_fish_kinds.h) */
} AquariumFish;

void AquariumFish_SetSwim(AquariumFish *fish);
void AquariumFish_TurnFromGlass(AquariumFish *fish);
void AquariumFish_ClearMeetings(AquariumFish *fish);
void AquariumFish_Meet(void *body, AquariumFish **slot, AquariumFish **other);
void AquariumFishBody_Touched(AquariumFishBody *body, int kind, unsigned int index);
void AquariumFish_KeepOffRoomEnds(AquariumFish *fish);
void AquariumFish_UpdateNothing(void);
void AquariumFish_SetUpNothing(void);
void AquariumFish_SetAnimSpeed(AquariumFish *fish, fx32 least);
void AquariumFish_Turn(AquariumFish *fish);
void AquariumFish_SetPassingWays(AquariumFish *fish, AquariumFish **other);

/* The modes a fish swims in (AquariumFish.mode), each a member function of the table
 * data_ov004_0225949c run every frame: it sets off on a new course, speeds up, cruises, slows
 * down and rests, then sets off again; a startled fish flees. */
enum {
    AQUARIUM_MODE_NONE = 0,
    AQUARIUM_MODE_FLEE = 1,
    AQUARIUM_MODE_NEW_COURSE = 2,
    AQUARIUM_MODE_SPEED_UP = 3,
    AQUARIUM_MODE_CRUISE = 4,
    AQUARIUM_MODE_SLOW_DOWN = 5,
    AQUARIUM_MODE_REST = 6,
};

/* AquariumFish.glass_turn: what a fish does about the glass ahead of it. */
enum {
    AQUARIUM_GLASS_NONE = 0,
    AQUARIUM_GLASS_TURN = 1,  /* it turns away by glass_step each frame */
    AQUARIUM_GLASS_ROUND = 2, /* its next course turns it round */
};

/* How it met the one it pays attention to (AquariumFish.meeting): each fish's heading is
 * measured from the line at right angles to the line between them. */
enum {
    AQUARIUM_MEET_CHASING = 0x02,      /* it swims towards the other, which swims away */
    AQUARIUM_MEET_CHASING_SAME = 0x04, /* the same, both turned to the same side */
    AQUARIUM_MEET_CHASED = 0x08,       /* it swims away from the other, which swims towards it */
    AQUARIUM_MEET_CHASED_SAME = 0x10,
    AQUARIUM_MEET_ROCK = 0x20,   /* it touched a rock */
    AQUARIUM_MEET_FACING = 0x40, /* both swim towards, or both away from, each other */
    AQUARIUM_MEET_FACING_SAME = 0x80,
};

/* The state of a model being drawn (NitroSystem's NNSG3dRS), as far as the fish's hook set up
 * before each draw writes it: the hook run for each kind of model command, and when. */
typedef struct AquariumFishHookState {
    u8 unk_00[0x0c];
    u32 hooks[0x20];       /* 0x0c: the address of each command's hook */
    u8 hook_timings[0x20]; /* 0x8c */
} AquariumFishHookState;

int AquariumFish_MeetingWay(AquariumFish *fish, AquariumFish **other);
void AquariumFish_ForgetFocus(AquariumFish *fish);
void AquariumFish_GiveWay(AquariumFish *fish);
void AquariumFish_ReactToFocus(AquariumFish *fish);
void AquariumFish_TurnAtTankEnds(AquariumFish *fish);
void AquariumFish_KeepYawAcross(AquariumFish *fish);
void AquariumFish_ModeEaseOff(AquariumFish *fish);
void AquariumFish_ModeSetOff(AquariumFish *fish);
void AquariumFish_ModeNone(void);
void AquariumFish_ModeFlee(AquariumFish *fish);
AquariumFish *AquariumFish_ModeRest(AquariumFish *fish);
void AquariumFish_ModeSlowDown(AquariumFish *fish);
void AquariumFish_ModeCruise(AquariumFish *fish);
void AquariumFish_ModeSpeedUp(AquariumFish *fish);
void AquariumFish_ModeNewCourse(AquariumFish *fish);
void AquariumFish_SwimByRoom(AquariumFish *fish);
void AquariumFish_SetUpByRoom(AquariumFish *fish);
void AquariumFish_Startle(AquariumFish *fish, const Vec3 *from);
int AquariumFish_CheckTapped(AquariumFish *fish);
int AquariumFish_FindTap(AquariumFish *fish, Vec3 *tap);
void AquariumFish_SetModelHooks(AquariumFishHookState *state);
void AquariumFish_NodeDescAfterHook(AnimatedModelNodeState *state);
void AquariumFish_NodeDescBeforeHook(AnimatedModelNodeState *state);
void AquariumFish_SwimRiver(AquariumFish *fish);
void AquariumFish_SetUpRiver(AquariumFish *fish);
void AquariumFish_SwimSea(AquariumFish *fish);
void AquariumFish_SetUpSea(AquariumFish *fish);

#endif
