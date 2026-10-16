/* The fish of the town's water in overlay 3: their shadows, the fin some of them show, and the
 * fish each player has on the line or in hand.
 *
 * The process (class vtable data_ov003_0223bfcc, derived from data_020da13c's) owns two pools
 * of model heaps: "fish_sdw" (six entries, one per shadow) and "fish_fin" (one entry, for the
 * fin). Its creation (vtable slot 0) loads the shadow model file and sets up the six shadows;
 * each frame (slot 6) every shadow runs the update of its state and the players' fish are
 * moved (func_ov003_02228618).
 *
 * Shadows (data_ov003_0225f76c, six records of 0x24c bytes). The first three are of group 0
 * and the last three of group 1 (the `place` main's CreatureTable picks a kind for). A shadow
 * has a state (0-4) whose entry and update functions are member functions of the process in
 * the table data_ov003_0225f1d0; it is drawn in state 3. It bites at a fishing float of the
 * player at this console (FishShadow_TryBite), is then hooked (`fishing_float`, `player`) and,
 * once caught, hands over to that player's fish (FishShadow_Catch). The kinds 0x34-0x36 show the
 * fin (data_ov003_0225f220) as well.
 *
 * Players' fish (data_ov003_0225f4dc, four records of 0xa4 bytes, one per player). Each shows
 * one model of main's fish display (fish_disp.h) through five states, from the member functions
 * in data_ov003_0225f138:
 *   0 PLAYER_FISH_IDLE  nothing;
 *   1 PLAYER_FISH_TAKE  takes a model and sets the move up (PlayerFish_StepTake);
 *   2 PLAYER_FISH_WAIT  waits while the other console's player is out of sight;
 *   3 PLAYER_FISH_SHOW  moves it by its mode and shows it (PlayerFish_StepShow);
 *   4 PLAYER_FISH_END   gives the model back (PlayerFish_End), then a splash into the water
 *                       and a shadow swimming away when it ended in the water.
 * Its modes: 1 the catch flying from the water to the hand of the player at this console, 2 a
 * catch of another console's player, in that player's hand, 3 and 4 arcs between its two
 * points, 5 the shadow swimming away from the player. Another console's player's fish follows
 * the states main's fish display keeps for it (FishDisp_PlayerState): see PlayerFish_Sync. */
#ifndef CLEAN_OV003_FISH_SHADOW_H
#define CLEAN_OV003_FISH_SHADOW_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/animated_model.h"
#include "main/field_collision.h"
#include "main/fishing_float.h"
#include "main/frame_ctrl.h"
#include "main/model_anim.h"
#include "main/model_object.h"
#include "main/model_pool.h"
#include "main/sound_emitter.h"
#include "types.h"

#define FISH_SHADOW_COUNT 6
#define FISH_SHADOW_GROUP_SIZE 3 /* shadows 0-2 are of group 0, 3-5 of group 1 */
#define FISH_SHADOW_STATES 5
#define PLAYER_FISH_COUNT 4

/* FishShadow.state. The drawing and fleeing ask for state 3. */
#define FISH_SHADOW_NONE 0
#define FISH_SHADOW_PLACED 1 /* set when a place is found for it */
#define FISH_SHADOW_STATE_2 2
#define FISH_SHADOW_SHOWN 3
#define FISH_SHADOW_AWAY 4 /* gone with a timer (the player too far from it) */

/* FishShadow.group_state: 0 or 1 is the group it is placed for, 3 or 4 waits to be placed in
 * group 0 or 1, 5 or 6 found no place in group 0 or 1; 2 is what the constructor sets. */
#define FISH_SHADOW_IN_GROUP0 0
#define FISH_SHADOW_IN_GROUP1 1
#define FISH_SHADOW_NEW 2
#define FISH_SHADOW_WAIT_GROUP0 3
#define FISH_SHADOW_WAIT_GROUP1 4

/* FishShadow.behaviour */
#define FISH_SHADOW_STARTLED 2 /* turned away from a float that landed near it */
#define FISH_SHADOW_FLEEING 5  /* swimming off (func_ov003_02228150) */

/* FishShadow.hook_state */
#define FISH_SHADOW_HOOK_FLEEING 6 /* fled while hooked */
#define FISH_SHADOW_HOOK_DROPPED 7 /* the line dropped (FishShadow_DropLine) */

/* FishShadow.player and PlayerFish.shadow for none. */
#define FISH_SHADOW_NO_PLAYER (-1)
#define PLAYER_FISH_NO_SHADOW (-1)

/* The kind of a fish's shadow model (fish_disp.h, FISH_DISP_KIND_SHADOW). */
#define PLAYER_FISH_KIND_SHADOW 0x3b

/* PlayerFish.state */
#define PLAYER_FISH_IDLE 0
#define PLAYER_FISH_TAKE 1
#define PLAYER_FISH_WAIT 2
#define PLAYER_FISH_SHOW 3
#define PLAYER_FISH_END 4

/* PlayerFish.mode */
#define PLAYER_FISH_HOOKED 1   /* flying from the water to the hand of the player at this console */
#define PLAYER_FISH_REMOTE 2   /* another console's player's catch, in that player's hand */
#define PLAYER_FISH_ARC_BACK 3 /* an arc from point_b to point_a, 1.5 lower */
#define PLAYER_FISH_ARC 4      /* an arc from point_a to point_b */
#define PLAYER_FISH_SWIM 5     /* the shadow swimming away from the player */

/* What a shadow senses of the player (the four bytes at 0x248). */
#define FISH_SHADOW_SENSE_FAR 0   /* the player is 8.0 or more away */
#define FISH_SHADOW_SENSE_NEAR 1  /* the player is near */
#define FISH_SHADOW_SENSE_SOUND 2 /* it plays sound 0x82f for `sound_frames` frames */
typedef struct FishShadowSense {
    u8 alarm;        /* 0-200: up while the player runs near, down otherwise */
    u8 sound_frames; /* frames left of FISH_SHADOW_SENSE_SOUND */
    u8 cooldown;     /* frames before it may go to FISH_SHADOW_SENSE_SOUND again */
    u8 mode;         /* FISH_SHADOW_SENSE_* */
} FishShadowSense;

/* The animated model of a shadow or the fin: main's model object with the frame control and
 * the animation (func_02055210 constructs these 0xb8 bytes, AnimatedModel's first part). */
typedef struct FishShadowModel {
    ModelObject object;      /* 0x00 */
    FrameCtrl frames;        /* 0x9c */
    AnimatedModelAnim *anim; /* 0xb4 */
} FishShadowModel;

typedef struct FishShadow {
    u8 emitter[0x40];            /* 0x000: a sound emitter of the base class B */
    SoundSource source;          /* 0x040: the vtable data_0213f020 */
    CollisionContacts contacts;  /* 0x04c */
    u16 slot;                    /* 0x07c: its entry of the "fish_sdw" pool */
    s8 kind;                     /* 0x07e: the fish's kind (creature_table.h), -1 for none */
    u8 has_fin;                  /* 0x07f: the kinds 0x34-0x36 */
    int state;                   /* 0x080: FISH_SHADOW_* */
    ModelObject unk_84;          /* 0x084 */
    Vec3 position;               /* 0x120 */
    Vec3 unk_12c;                /* 0x12c: set with the position when it is placed */
    s16 yaw;                     /* 0x138 */
    u8 pad_13a[2];               /* 0x13a */
    int unk_13c;                 /* 0x13c */
    s16 unk_140;                 /* 0x140 */
    u8 pad_142[2];               /* 0x142 */
    FishShadowModel model;       /* 0x144 */
    u8 group_state;              /* 0x1fc: FISH_SHADOW_IN_GROUP0 ... */
    u8 alpha;                    /* 0x1fd: the model's alpha, 1-0x1f */
    u8 ground;                   /* 0x1fe: the kind of water it lives in */
    u8 size;                     /* 0x1ff: the kind's size class (CreatureTableInfo.offset_class) */
    u8 behaviour;                /* 0x200: FISH_SHADOW_STARTLED, FISH_SHADOW_FLEEING */
    u8 unk_201;                  /* 0x201 */
    u8 pad_202[2];               /* 0x202 */
    int effect;                  /* 0x204: its effect's handle, -1 for none */
    int tile_x;                  /* 0x208 */
    int tile_z;                  /* 0x20c */
    u8 unk_210;                  /* 0x210 */
    u8 index;                    /* 0x211: its number */
    s16 respawn;                 /* 0x212: frames before it is placed again */
    u8 pad_214[4];               /* 0x214 */
    Vec3 last_position;          /* 0x218: where it was before the last move */
    u8 hook_state;               /* 0x224: FISH_SHADOW_HOOK_* */
    u8 pad_225[2];               /* 0x225 */
    s8 player;                   /* 0x227: the player it is hooked by, FISH_SHADOW_NO_PLAYER for none */
    u8 pad_228[4];               /* 0x228 */
    FishingFloat *fishing_float; /* 0x22c: the float it is on, NULL for none */
    u8 pad_230[0xc];             /* 0x230 */
    u8 hooked;                   /* 0x23c */
    u8 unk_23d;                  /* 0x23d */
    u8 pad_23e[6];               /* 0x23e */
    int timer;                   /* 0x244: -1 for none */
    FishShadowSense sense;       /* 0x248 */
} FishShadow;

/* The fin (data_ov003_0225f220, a global C++ object of 0x13c bytes). */
typedef struct FishFin {
    int state;             /* 0x000: 0 none, 2 loading (FishShadow_TakeFin) */
    u16 slot;              /* 0x004: its entry of the "fish_fin" pool */
    u8 pad_06[2];          /* 0x006 */
    ModelPoolFiles files;  /* 0x008 */
    u8 unk_48[0x10];       /* 0x048 */
    FishShadowModel model; /* 0x058 */
    u8 unk_110[0xc];       /* 0x110 */
    ModelAnim anim;        /* 0x11c: of the class with vtable data_ov003_0223c0d4 */
} FishFin;

/* The process. */
typedef struct FishShadowProcess {
    Process base;      /* 0x00 */
    ModelPool shadows; /* 0x50: "fish_sdw" */
    ModelPool fin;     /* 0x68: "fish_fin" */
    void *shadow_file; /* 0x80: the shadow's model file */
    u8 unk_84;         /* 0x84: cleared each frame */
} FishShadowProcess;

typedef struct PlayerFish {
    u8 emitter[0x40]; /* 0x00: a sound emitter of the base class B */
    int state;        /* 0x40: PLAYER_FISH_IDLE ... */
    int model;        /* 0x44: its model of the fish display, -1 for none */
    int mode;         /* 0x48: PLAYER_FISH_HOOKED ... */
    fx32 gravity;     /* 0x4c: of its flight (FishingFloat_Fly, FishingFloat_Arc) */
    fx32 speed;       /* 0x50: the vertical speed */
    Vec3 position;    /* 0x54 */
    Vec3 point_a;     /* 0x60: where a catch starts in the water, or a point ahead of the player */
    Vec3 point_b;     /* 0x6c: the hand it reached, or the point in the water it is let go to */
    s8 shadow;        /* 0x78: the shadow it was, PLAYER_FISH_NO_SHADOW for none */
    u8 pad_79[3];     /* 0x79 */
    int frames;       /* 0x7c: frames of the move */
    u8 arrived;       /* 0x80: it reached the hand */
    u8 pad_81[3];     /* 0x81 */
    Vec3 scale;       /* 0x84 */
    int kind;         /* 0x90: the fish's kind, or PLAYER_FISH_KIND_SHADOW */
    u8 splash;        /* 0x94: the arc ended in the water */
    u8 pad_95;        /* 0x95 */
    s16 rotation[3];  /* 0x96: about x, y and z */
    int effect;       /* 0x9c: the effect following it, -1 for none */
    u8 unk_a0;        /* 0xa0 */
    u8 pad_a1[3];     /* 0xa1 */
} PlayerFish;

void FishShadow_EnterNone(void);
void FishShadow_SetState(FishShadowProcess *self, int state, FishShadow *fish, int index);
void FishShadow_Update(FishShadowProcess *self, FishShadow *fish, int index);
int FishShadow_Create(FishShadowProcess *self);
void FishShadow_ReleaseFin(FishShadowProcess *self);
int FishShadow_TakeFin(FishShadowProcess *self);
void FishShadow_Reset(FishShadowProcess *self, int index);
int FishShadow_SetState2(FishShadowProcess *self, int index);
FishShadowProcess *FishShadow_DestructFree(FishShadowProcess *self);
FishShadowProcess *FishShadow_Destruct(FishShadowProcess *self);
FishShadowProcess *FishShadow_Construct(FishShadowProcess *self);
PlayerFish *PlayerFish_Destruct(PlayerFish *self);
PlayerFish *PlayerFish_Construct(PlayerFish *self);
void FishShadowSense_Destruct(FishShadowSense *sense);
void FishShadowSense_Construct(FishShadowSense *sense);
FishFin *FishFin_Destruct(FishFin *fin);
FishFin *FishFin_Construct(FishFin *fin);
ModelAnim *FishFinAnim_Destruct(ModelAnim *anim);
FishShadow *FishShadow_DestructRecord(FishShadow *fish);
FishShadow *FishShadow_ConstructRecord(FishShadow *fish);
int PlayerFish_OnRemoteState2(FishShadowProcess *self, unsigned int player);
int PlayerFish_StartRemote(FishShadowProcess *self, unsigned int player, int kind, const Vec3 *point);
int PlayerFish_OnRemoteState1(FishShadowProcess *self, unsigned int player);
void PlayerFish_OnRemoteState0(FishShadowProcess *self, int player);
void PlayerFish_Sync(FishShadowProcess *self);
void PlayerFish_HoldPoint(PlayerFish *self, Actor *actor, Vec3 *out);
int PlayerFish_Swim(PlayerFish *self, const Vec3 *player_position);
int PlayerFish_ArcStep(Vec3 *position, const Vec3 *from, const Vec3 *to, int frame, int height, int frames);
void PlayerFish_StepArc(PlayerFish *self, int back);
void PlayerFish_Splash(PlayerFish *self, int player);
void PlayerFish_End(PlayerFish *self, int player);
int PlayerFish_LetShadowGo(PlayerFish *self);
int PlayerFish_StepEnd(PlayerFish *self, int player);
int PlayerFish_FollowRemote(PlayerFish *self, int player);
int PlayerFish_FollowLocal(PlayerFish *self, int player);
int PlayerFish_StepShow(PlayerFish *self, int player);
int PlayerFish_StepWait(PlayerFish *self, int player);
int PlayerFish_StartArc(PlayerFish *self, unsigned int player);
int PlayerFish_StepTake(PlayerFish *self, int player);
int PlayerFish_StepIdle(void);
void PlayerFish_Update(PlayerFish *self, int player);
void FishShadow_ResetSense(FishShadow *fish);
void FishShadowSense_Reset(FishShadowSense *sense);
void FishShadowSense_StepSound(FishShadowSense *sense, FishShadow *fish);
void FishShadowSense_StepNear(FishShadowSense *sense, FishShadow *fish);
void FishShadowSense_StepFar(FishShadowSense *sense, FishShadow *fish);
void FishShadowSense_Step(FishShadowSense *sense, FishShadow *fish);
void FishShadow_GroundAhead(FishShadow *fish, int *left, int *right, int *ahead);
int FishShadow_IsBlocked(FishShadow *fish);
int FishShadow_CheckMove(FishShadow *fish);
int FishShadow_IsWaterBehind(FishShadow *fish);
int FishShadow_EdgeColumn(FishShadow *fish);
int FishShadow_DropLine(FishShadow *fish);
int FishShadow_Catch(FishShadow *fish, int index);
void FishShadow_TickSplash(void);
int FishShadow_SplashRecent(void);
void FishShadow_NoteSplash(void);
int FishShadow_InBiteRange(const Vec3 *point, int yaw, int player, int kind);
int FishShadow_TryBite(FishShadow *fish);
int FishShadow_FleeFromPlayer(FishShadow *fish);

#endif
