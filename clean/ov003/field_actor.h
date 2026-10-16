/* Overlay 3's part of the field actor (class vtable 0x020d82b4, include/cpp/main/Obj_020d82b4.h):
 * the checks the actor's frame update runs while overlay 3 is loaded (func_020058e4), the
 * choice of what to do with the held tool, and states of its state machine (0x5e to 0x6e, 0x71
 * to 0x75, 0x78, 0x80 to 0x82, 0x89 and 0x8f).
 *
 * The state machine: each state has an update, a message handler and an entry function, picked
 * by the state number at 0x7f0 from tables in main; some also have one run when the actor leaves
 * them (from another table in main: states 0x66, 0x63, 0x62, 0x5f and 0x5e here). A state is asked for by queueing a
 * StateRequest on the actor (func_0200e894); the helpers that build one pass a priority (6 for
 * all of them here) and an argument (-1 here unless passed on).
 *
 * The actor's player number (0x800) is compared with the session's (func_02073908) to tell
 * the player at this console from the others. */
#ifndef CLEAN_OV003_FIELD_ACTOR_H
#define CLEAN_OV003_FIELD_ACTOR_H

#include "autoload_2/approach.h" /* Vec3 */
#include "main/frame_ctrl.h"
#include "types.h"

/* A request for a state, as the queue at 0x934 in the actor copies it (0x1c bytes). */
typedef struct StateRequest {
    int state;
    int priority; /* the queue remembers its highest */
    s16 arg;
    u8 unk_0A[2];
    u8 payload[0x10]; /* what the state's entry function reads */
} StateRequest;

/* The two bytes a request for state 0x8f carries, kept at 0x7d4 and again at 0x8f0. */
typedef struct LookArgs {
    u8 track;     /* nonzero: the head follows the target; zero: the state only waits */
    u8 exit_kind; /* where the actor goes once the target is gone: state 5 if nonzero, else 2 */
} LookArgs;

/* Two bytes a request for state 0x73 carries: a tile (func_0204f794 turns it into a point),
 * kept at 0x8f0 to ask for the state again. */
typedef struct TileArgs {
    u8 x;
    u8 z;
} TileArgs;

/* The arguments a request for states 0x68 and 0x69 carries: a point on the ground and two
 * flags. */
typedef struct XZArgs {
    fx32 x;
    fx32 z;
    u8 then_77; /* state 0x69 ends in state 0x77 (facing on) instead of func_0200d4e8 */
    u8 then_69; /* state 0x68: state 0x69 follows; state 0x69: kept, not read */
} XZArgs;

/* The arguments a request for state 0x66 carries: a tile and what follows (State66Work.next). */
typedef struct TileNextArgs {
    u8 x;
    u8 z;
    u8 next;
} TileNextArgs;

/* The arguments a request for states 0x62 and 0x61 carries: an item, a tile and a kind (2 in
 * the requests of states 0x60 and 0x5f). */
typedef struct ItemTileArgs {
    u16 item;
    u8 x;
    u8 z;
    u8 kind;
} ItemTileArgs;

/* The same, as state 0x61 saves it at 0x8f0: the item packed by func_020778b0 (func_02077898
 * reads it back). State 0x5f saves its tile, item and kind the same way. */
typedef struct SavedItemTile {
    u8 item[2];
    u8 x;
    u8 z;
    u8 kind;
} SavedItemTile;

/* The arguments a request for state 0x60 carries: a tile and the step to start at. */
typedef struct TileStepArgs {
    u8 x;
    u8 z;
    u8 step;
} TileStepArgs;

/* The arguments a request for state 0x5f carries: a point, an item and a kind. */
typedef struct PointItemArgs {
    Vec3 point;
    u16 item;
    u8 kind;
} PointItemArgs;

/* State 0x62's work: the request's item and kind, the middle of its tile and the yaw towards
 * it. */
typedef struct State62Work {
    u16 item;
    u8 unk_02[2];
    Vec3 point;
    s16 yaw;
    u8 kind; /* 1: func_0200c9a8 follows; 3: func_02008380 for the actor of this console */
} State62Work;

/* State 0x61's work: the request's item, the yaw towards its tile, the kind and the tile. */
typedef struct State61Work {
    u16 item;
    s16 yaw;
    u8 kind; /* 2 waits for `done` (the word at 0x818 becoming 1) before state 0x62 */
    u8 x;
    u8 z;
    u8 done;
} State61Work;

/* State 0x5f's work: the point, a step (0 to 5) and the request's kind. */
typedef struct State5FWork {
    Vec3 point;
    u8 step;
    u8 kind;
} State5FWork;

/* State 0x5e's work: a flag that picks animation 0x4e over 0x4b after 0x49, and a point. */
typedef struct State5EWork {
    u8 flag;
    u8 unk_01[3];
    Vec3 point;
} State5EWork;

/* State 0x69's work: the yaw to turn to and the tile of the request's point. */
typedef struct State69Work {
    u8 unk_00; /* set to 0 */
    u8 unk_01;
    u16 yaw;
    int tile_x;
    int tile_z;
    u8 then_77;
    u8 then_69;
} State69Work;

/* State 0x68's work: the request's point, the yaw towards it and a frame count. */
typedef struct State68Work {
    fx32 x;
    fx32 z;
    u16 yaw;
    u8 count; /* frames in the state, up to 6; the tile is announced at 5 */
    u8 then_77;
    u8 then_69;
} State68Work;

/* State 0x67's work: the yaw towards the point and the point. */
typedef struct State67Work {
    s16 yaw;
    u8 unk_02[2];
    Vec3 point;
} State67Work;

/* State 0x66's work: the middle of the request's tile, the yaw towards it, a frame count and
 * what follows: 0 not decided yet, 1 state 0x67 at the point, 2 func_0200d4e8. */
typedef struct State66Work {
    Vec3 point;
    u16 yaw;
    u8 count; /* the first two frames only count */
    u8 next;
} State66Work;

/* State 0x74's work: the actor's movement in the frame before, the speed of the animation and
 * a progress that the pad and the movement drive towards 400.0. */
typedef struct State74Work {
    fx32 move_speed;     /* func_0200dc8c (the word at 0x134) in the frame before */
    fx32 anim_speed;     /* the animation's speed, between min_anim_speed and 2.25 */
    fx32 min_anim_speed; /* rises with progress, from 0.5 */
    int effort;          /* this frame's push, in whole units */
    fx32 progress;       /* state 0x75 follows at 400.0 */
    u16 move_angle;      /* func_0200dc80 (the halfword at 0x138) in the frame before */
    u8 unk_16[2];
    int effect; /* the effect's handle (func_020912d4), -1 for none */
} State74Work;

/* The bytes at 0x7d4 that each state uses its own way. */
typedef union FieldActorWork {
    LookArgs look; /* state 0x8f */
    struct {
        int effect; /* the effect's handle (func_020912d4), -1 for none */
        u8 count;   /* state 0x81: frames before the effect starts, then a countdown */
        u8 count2;  /* state 0x81: a second countdown after `count` */
    } effect;       /* states 0x81 and 0x82; state 0x63 uses `effect` only */
    u8 step;        /* states 0x78 (0 to 2) and 0x6e (nonzero once the animation is over) */
    State74Work s74;
    struct {
        fx32 x; /* where the actor walks to and stays: the request's tile */
        fx32 z;
        int effect; /* the effect's handle (func_020912d4), -1 for none */
    } s73;
    struct {
        int tool; /* func_0200fbe0 on entering */
        u8 done;  /* the second animation has started */
    } s71;
    struct {
        int effect; /* the effect's handle (func_020912d4) */
        u8 kind;    /* the request's byte */
    } s6d;
    Vec3 s6a_point; /* state 0x6a: where the actor stands */
    State69Work s69;
    State68Work s68;
    State67Work s67;
    State66Work s66;
    State62Work s62;
    State61Work s61;
    TileStepArgs s60; /* state 0x60: the request's tile and the step */
    State5FWork s5f;
    State5EWork s5e;
    u8 bytes[0x1c];
} FieldActorWork;

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct FieldActorLink {
    int unk_00;
    int open;      /* nonzero while what the request opened is up */
    int requested; /* set to 1 to ask for it */
} FieldActorLink;

/* 48 bytes func_0200ee40 rewrites, which state 0x5f keeps across it. */
typedef struct FieldActorBlock48 {
    u32 words[12];
} FieldActorBlock48;

typedef struct FieldActor {
    const u32 *vtable; /* data_020d82b4 */
    u8 unk_004[0x5c - 0x04];
    Vec3 position;
    u8 unk_068[0x8e - 0x68];
    s16 yaw; /* the direction the body faces */
    u8 unk_090[0x98 - 0x90];
    int unk_098;
    u8 unk_09C[0xc4 - 0x9c];
    Vec3 unk_0C4; /* kept across func_0200ee40 by state 0x5f */
    s16 unk_0D0;  /* kept across func_0200ee40 by state 0x5f */
    u8 unk_0D2[0xec - 0xd2];
    /* A message receiver (Base_02066994) */
    u8 receiver[0x10a - 0xec];
    u8 receiver_unk_1E; /* Base_02066994's byte at 0x1e */
    u8 unk_10B[0x12c - 0x10b];
    FieldActorLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x140 - 0x130];
    u8 unk_140;
    u8 unk_141[3];
    int unk_144;
    u8 unk_148;
    u8 unk_149[0x158 - 0x149];
    Vec3 aim_point; /* the point tools act on when aim_mode is not 1 */
    u8 unk_164[4];
    void *other;     /* the object FieldActor_CheckOther found */
    u8 other_result; /* FieldActor_CheckOther's verdict: 0-4 */
    u8 unk_16D[3];
    int aim_mode; /* 1: tools act on a point ahead of the actor; otherwise on aim_point (some only with 2) */
    u8 unk_174[0x1d2 - 0x174];
    u8 other_kind; /* the kind of object met: 2 and 3 in main's tables, 0x11 and 0x12 here */
    u8 other_id;
    u8 unk_1D4[0x200 - 0x1d4];
    u8 has_other; /* nonzero when other_kind and other_id name an object */
    u8 unk_201[0x234 - 0x201];
    u8 unk_234[0x298 - 0x234]; /* an object func_02054860 updates (to 0x2d0) */
    FieldActorBlock48 unk_298; /* kept across func_0200ee40 by state 0x5f */
    u8 unk_2C8[0x2d0 - 0x2c8];
    FrameCtrl anim; /* the body's animation */
    u8 unk_2E8[0x45c - 0x2e8];
    s16 head_pitch;
    s16 head_yaw; /* relative to the body */
    u8 unk_460[0x5a0 - 0x460];
    u8 held[0x2c]; /* what the actor holds in hand (func_0205eae0, func_0205eb8c) */
    u8 unk_5CC[0x62c - 0x5cc];
    Vec3 unk_62C;
    u8 unk_638[0x68c - 0x638];
    Vec3 unk_68C;
    FieldActorBlock48 unk_698; /* kept across func_0200ee40 by state 0x5f */
    u8 unk_6C8[0x6e0 - 0x6c8];
    Vec3 effect_point; /* where the effects of states 0x73, 0x74 and 0x6d are */
    u32 flags;         /* func_0200f290 tests a bit, func_0200f27c sets one, func_0200f268 clears one */
    u8 unk_6F0[4];
    Vec3 start_position; /* the position when the frame's update began */
    u8 unk_700[4];
    int animation; /* the animation playing: func_020109a0 and func_020109fc set it */
    u8 unk_708[0x70d - 0x708];
    u8 unk_70D[0x7d4 - 0x70d]; /* func_0205dc94 writes here */
    FieldActorWork work;
    int state;
    int unk_7F4;
    int unk_7F8;
    int next_state; /* func_02008258's entry for the state, stored before leaving it */
    int player;
    u8 unk_804[0x80c - 0x804];
    int target; /* a handle func_0200ff28 and func_020438dc find, -1 for none */
    u8 unk_810[4];
    int unk_814;
    int unk_818;
    int unk_81C; /* a progress states 0x60 and 0x5f wait on (5, 6, 0xf and up) */
    u16 item;    /* the item states 0x61, 0x60 and 0x5f act with (ITEM_NONE 0xfff1 for none) */
    u16 unk_822; /* state 0x5f writes the item here and copies it to `item` */
    Vec3 unk_824;
    fx32 unk_830[3]; /* three equal factors (state 0x89; states 0x60 and 0x5f pass the value to func_0200f650) */
    u8 unk_83C[0x8d0 - 0x83c];
    int front_tile[2]; /* the tile ahead, as FieldActor_TrackFrontTile last saw it */
    int tile[2];       /* the tile under the actor, as FieldActor_TrackTile last saw it */
    int pending_tile[2];
    u8 unk_8E8; /* set to 60 when the actor leaves state 0x71 */
    u8 unk_8E9[0x8f0 - 0x8e9];
    union {
        LookArgs look;           /* state 0x8f */
        TileArgs tile;           /* states 0x73 and 0x66 */
        SavedItemTile item_tile; /* states 0x61 and 0x5f */
        TileStepArgs tile_step;  /* state 0x60 */
        u8 left_early;           /* state 0x63: the actor of this console left it before its end */
        /* Points packed by func_02077950 (x, y and z, state 0x6a) or func_020779b8 (x and z,
         * state 0x68, with the request's flags in byte 5). */
        u8 packed[8];
    } saved;
    u8 unk_8F8[0xc84 - 0x8f8];
    s16 unk_C84; /* the message handlers of states 0x74, 0x68 and 0x66 store their argument here
                  * when the actor is already in that state */
} FieldActor;

/* A bit of FieldActor.flags: pending_tile holds a tile to act on. */
#define FIELD_ACTOR_FLAG_PENDING_TILE 0x16

int FieldActor_TryTarget(FieldActor *actor, int tool, ...);
int FieldActor_UseTool(FieldActor *actor, int tool, Vec3 *point);
int FieldActor_TryTool(FieldActor *actor);
int FieldActor_CheckOther(FieldActor *actor);
void FieldActor_UpdateSunLevel(FieldActor *actor);
void FieldActor_FinishPendingTile(FieldActor *actor);
void FieldActor_FindTileTarget(FieldActor *actor);
void FieldActor_TrackTile(FieldActor *actor);
void FieldActor_TrackFrontTile(FieldActor *actor);
int FieldActor_PointsAhead(FieldActor *actor, Vec3 *near, const Vec3 *toward);
int FieldActor_ClassifyAt(FieldActor *actor, const Vec3 *at, const u8 *check_other);
int FieldActor_ClassifyAhead(FieldActor *actor, const u8 *check_other, const u8 *mode, int *tile);
int FieldActor_TryTargetMode2(FieldActor *actor, int *tool);
int FieldActor_ResumeMoving(FieldActor *actor);

void FieldActor_UpdateLook(FieldActor *actor);
void FieldActor_TrackLookTarget(FieldActor *actor);
void FieldActor_LookMessage(FieldActor *actor, int arg);
void FieldActor_EnterLook(FieldActor *actor, const StateRequest *request, int previous);
void LookArgs_Get(const LookArgs *args, u8 *track, u8 *exit_kind);
void LookArgs_Set(LookArgs *args, int track, int exit_kind);
int FieldActor_RequestLook(FieldActor *actor, const u8 *track, int exit_kind, int priority, s16 arg);

void FieldActor_UpdateState89(FieldActor *actor);
void FieldActor_FaceState89Target(FieldActor *actor);
void FieldActor_AnimateState89(FieldActor *actor);
void FieldActor_State89Message(FieldActor *actor, int arg);
void FieldActor_EnterState89(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState89(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState82(FieldActor *actor);
void FieldActor_EndState82(FieldActor *actor);
void FieldActor_AnimateState82(FieldActor *actor);
void FieldActor_FinishState82(FieldActor *actor);
void FieldActor_State82Message(FieldActor *actor, int arg);
void FieldActor_EnterState82(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState82(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState81(FieldActor *actor);
void FieldActor_EndState81(FieldActor *actor);
void FieldActor_AnimateState81(FieldActor *actor);
void FieldActor_FinishState81(FieldActor *actor);
void FieldActor_State81Message(FieldActor *actor, int arg);
void FieldActor_EnterState81(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState81(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState80(FieldActor *actor);
void FieldActor_EndState80(FieldActor *actor);
void FieldActor_AnimateState80(FieldActor *actor);
void FieldActor_FinishState80(FieldActor *actor);
void FieldActor_State80Message(FieldActor *actor, int arg);
void FieldActor_EnterState80(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState80(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState78(FieldActor *actor);
void FieldActor_RunState78(FieldActor *actor);
void FieldActor_State78Message(FieldActor *actor, int arg);
void FieldActor_EnterState78(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState78(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState75(FieldActor *actor);
void FieldActor_EndState75(FieldActor *actor);
void FieldActor_State75Message(FieldActor *actor, int arg);
void FieldActor_EnterState75(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState75(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState74(FieldActor *actor);
void FieldActor_RunState74(FieldActor *actor);
void FieldActor_AnimateState74(FieldActor *actor);
void FieldActor_ExitState74(FieldActor *actor, int next);
void FieldActor_State74Message(FieldActor *actor, int arg);
void FieldActor_EnterState74(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState74(FieldActor *actor, int effect, int priority, int arg);

void FieldActor_UpdateState73(FieldActor *actor);
void FieldActor_RunState73(FieldActor *actor);
void FieldActor_AnimateState73(FieldActor *actor);
void FieldActor_ExitState73(FieldActor *actor, int next);
void FieldActor_State73Message(FieldActor *actor, int arg);
void FieldActor_EnterState73(FieldActor *actor, const StateRequest *request, int previous);
void TileArgs_Get(const TileArgs *args, u8 *x, u8 *z);
void TileArgs_Set(TileArgs *args, int x, int z);
int FieldActor_RequestState73(FieldActor *actor, const int *tile, int priority, int arg);

void FieldActor_UpdateState72(FieldActor *actor);
void FieldActor_EndState72(FieldActor *actor);
void FieldActor_SlowDown(FieldActor *actor);
void FieldActor_State72Message(FieldActor *actor, int arg);
void FieldActor_EnterState72(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState72(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState71(FieldActor *actor);
void FieldActor_RunState71(FieldActor *actor);
void FieldActor_EndState71(FieldActor *actor);
void FieldActor_AnimateState71(FieldActor *actor);
void FieldActor_State71Message(FieldActor *actor, int arg);
void FieldActor_EnterState71(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState71(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState6E(FieldActor *actor);
void FieldActor_RunState6E(FieldActor *actor);
void FieldActor_AnimateState6E(FieldActor *actor);
void FieldActor_State6EMessage(FieldActor *actor, int arg);
void FieldActor_EnterState6E(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState6E(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState6D(FieldActor *actor);
void FieldActor_RunState6D(FieldActor *actor);
void FieldActor_AnimateState6D(FieldActor *actor);
void FieldActor_State6DMessage(FieldActor *actor, int arg);
void FieldActor_EnterState6D(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState6D(FieldActor *actor, char kind, int priority, int arg);

void FieldActor_UpdateState6C(FieldActor *actor);
void FieldActor_RunState6C(FieldActor *actor);
void FieldActor_State6CMessage(FieldActor *actor, int arg);
void FieldActor_EnterState6C(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState6C(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState6B(FieldActor *actor);
void FieldActor_State6BMessage(FieldActor *actor, int arg);
void FieldActor_EnterState6B(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState6B(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState6A(FieldActor *actor);
void FieldActor_EndState6A(FieldActor *actor);
void FieldActor_PlaceState6A(FieldActor *actor);
void FieldActor_State6AMessage(FieldActor *actor, int arg);
void FieldActor_EnterState6A(FieldActor *actor, const StateRequest *request, int previous);
void PackedPoint_Get(const u8 *packed, Vec3 *point);
void PackedPoint_Set(u8 *packed, const Vec3 *point);
void State6A_SetPoint(Vec3 *dst, Vec3 value);
void *FieldActor_RequestState6A(FieldActor *actor, Vec3 point, u32 priority, s16 arg);
void State6A_SetRequestPoint(Vec3 *dst, Vec3 value);

void FieldActor_UpdateState69(FieldActor *actor);
void FieldActor_EndState69(FieldActor *actor);
void FieldActor_TurnState69(FieldActor *actor);
void FieldActor_AnimateState69(FieldActor *actor);
void FieldActor_State69Message(FieldActor *actor, int arg);
void FieldActor_EnterState69(FieldActor *actor, const StateRequest *request, int previous);
void State69Work_Set(State69Work *work, u16 yaw, u32 tile_x, u32 tile_z, u8 then_77, u8 then_69);
int FieldActor_RequestState69(FieldActor *actor, fx32 x, fx32 z, int then_77, u8 then_69, int priority, s16 arg);
void XZArgs_Set69(XZArgs *args, fx32 x, fx32 z, u8 then_77, u8 then_69);

void FieldActor_UpdateState68(FieldActor *actor);
void FieldActor_EndState68Remote(FieldActor *actor);
void FieldActor_EndState68Local(FieldActor *actor);
void FieldActor_TurnState68(FieldActor *actor);
void FieldActor_ExitState68(FieldActor *actor);
void FieldActor_State68Message(FieldActor *actor, int arg);
void FieldActor_EnterState68(FieldActor *actor, const StateRequest *request, int previous);
void PackedXZ_Get(u8 *packed, fx32 *x, fx32 *z, u8 *flags);
void PackedXZ_Set(u8 *packed, fx32 x, fx32 z, int flags);
void State68Work_Set(State68Work *work, int yaw, fx32 x, fx32 z, u8 then_77, u8 then_69);
int FieldActor_RequestState68(FieldActor *actor, fx32 x, fx32 z, int then_77, u8 then_69, int priority, s16 arg);
void XZArgs_Set68(XZArgs *args, fx32 x, fx32 z, u8 then_77, u8 then_69);

void FieldActor_UpdateState67(FieldActor *actor);
void FieldActor_EndState67Remote(FieldActor *actor);
void FieldActor_EndState67Local(FieldActor *actor);
void FieldActor_TurnState67(FieldActor *actor);
void FieldActor_AnimateState67(FieldActor *actor);
void FieldActor_State67Message(FieldActor *actor, int arg);
void FieldActor_EnterState67(FieldActor *actor, const StateRequest *request, int previous);
void State67Work_Set(State67Work *work, s16 yaw, const Vec3 *point);
int FieldActor_RequestState67(FieldActor *actor, const Vec3 *at, int priority, int arg);
void State67_CopyPoint(Vec3 *dst, const Vec3 *src);

void FieldActor_UpdateState66(FieldActor *actor);
void FieldActor_EndState66(FieldActor *actor);
void FieldActor_TurnState66(FieldActor *actor);
void FieldActor_ExitState66(FieldActor *actor, int next);
void FieldActor_State66Message(FieldActor *actor, int arg);
void FieldActor_EnterState66(FieldActor *actor, const StateRequest *request, int previous);
void TileArgs_GetInts(const TileArgs *args, int *tile);
void TileArgs_SetInts(TileArgs *args, const int *tile);
void State66Work_Set(State66Work *work, u8 next, u16 yaw, const Vec3 *point);

int FieldActor_RequestState66(FieldActor *actor, const int *tile, int next, int priority, s16 arg);
void TileNextArgs_Set(TileNextArgs *args, const int *tile, u8 next);

void FieldActor_UpdateState65(FieldActor *actor);
void FieldActor_State65Message(FieldActor *actor, int arg);
void FieldActor_EnterState65(FieldActor *actor, const StateRequest *request, int previous);
int FieldActor_RequestState65(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState64(FieldActor *actor);
void FieldActor_EndState64(FieldActor *actor);
void FieldActor_RunState64(FieldActor *actor);
void FieldActor_State64Message(FieldActor *actor, int arg);
void FieldActor_EnterState64(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState64(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState63(FieldActor *actor);
void FieldActor_EndState63Remote(FieldActor *actor);
void FieldActor_EndState63Local(FieldActor *actor);
void FieldActor_RunState63(FieldActor *actor);
void FieldActor_ExitState63(FieldActor *actor);
void FieldActor_State63Message(FieldActor *actor, int arg);
void FieldActor_EnterState63(FieldActor *actor, const StateRequest *request, int previous);
void SavedFlag_Get(const u8 *saved, u8 *value);
void SavedFlag_Set(u8 *saved, int value);
int FieldActor_RequestState63(FieldActor *actor, int priority, int arg);

void FieldActor_UpdateState62(FieldActor *actor);
void FieldActor_EndState62(FieldActor *actor);
void FieldActor_AnimateState62(FieldActor *actor);
void FieldActor_TurnState62(FieldActor *actor);
void FieldActor_ExitState62(FieldActor *actor);
void FieldActor_State62Message(FieldActor *actor, int arg);
void FieldActor_EnterState62(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState62(FieldActor *actor, u32 kind, const u32 *tile, u16 item, u32 priority, s16 arg);

void FieldActor_UpdateState61(FieldActor *actor);
void FieldActor_EndState61(FieldActor *actor);
void FieldActor_TurnState61(FieldActor *actor);
void FieldActor_State61Message(FieldActor *actor, int arg);
void FieldActor_EnterState61(FieldActor *actor, const StateRequest *request, int previous);
void SavedItemTile_Set(SavedItemTile *saved, int item, char x, char z, u8 kind);
void *FieldActor_RequestState61(FieldActor *actor, u32 kind, const u32 *tile, u16 item, u32 priority, s16 arg);

void FieldActor_UpdateState60(FieldActor *actor);
void FieldActor_RunState60(FieldActor *actor);
void FieldActor_ScaleState60(FieldActor *actor);
void FieldActor_State60Message(FieldActor *actor, int arg);
void FieldActor_EnterState60(FieldActor *actor, const StateRequest *request, int previous);
void TileStepArgs_Get(const TileStepArgs *args, u8 *x, u8 *z, u8 *step);
void TileStepArgs_Set(TileStepArgs *args, int x, int z, int step);
int FieldActor_RequestState60(FieldActor *actor, const int *tile, int step, int priority, s16 arg);

void FieldActor_UpdateState5F(FieldActor *actor);
void FieldActor_RunState5F(FieldActor *actor);
void FieldActor_AnimateState5F(FieldActor *actor);
void FieldActor_ExitState5F(FieldActor *actor, int next);
void FieldActor_State5FMessage(FieldActor *actor, int arg);
void FieldActor_EnterState5F(FieldActor *actor, const StateRequest *request, int previous);
void SavedItemTile_Get(const SavedItemTile *saved, u32 *tile, u16 *item, u8 *kind);
void SavedItemTile_SetTile(SavedItemTile *saved, const int *tile, int item, int kind);
int FieldActor_RequestState5F(FieldActor *actor, const Vec3 *point, int item, int kind, int priority, s16 arg);
int FieldActor_RequestState5FNoItem(FieldActor *actor, const Vec3 *point, int kind, int priority, s16 arg);
void PointItemArgs_Set(PointItemArgs *args, const Vec3 *point, u16 item, u8 kind);

void FieldActor_UpdateState5E(FieldActor *actor);
void FieldActor_EndState5E(FieldActor *actor);
void FieldActor_AnimateState5E(FieldActor *actor);
void FieldActor_ExitState5E(FieldActor *actor);

#endif
