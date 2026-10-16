/* The snowballs and snowmen of overlay 3 (class Obj_ov003_022382ac, vtable 0x022382ac, 0x3a4
 * bytes; its receiver part at 0xec, whose name is "sp_npc_snowman").
 *
 * One object is one ball of snow, drawn with "/snowman/snowball1.nsbmd" (model "SNW0") or, as
 * a snowman's head, with "/snowman/snow_face.nsbmd" ("SNW1"). Up to eight exist at once, kept
 * by their index (the word at 0x08) in overlay 3's table at 0x02262b38:
 *
 *   index 0 and 1: loose balls that roll. Their position and size are kept in main's table
 *                  at 0x021f4ae8 (func_020b03f8) from one visit to the next;
 *   index 2 and up: two per snowman (snowman (index - 2) / 2 of the three main keeps at
 *                  0x021f3b56): the even one is the head, the odd one the body.
 *
 * A ball's size (the word at 0x26c, 0x800 to 0x1400) grows while it rolls over snow and shrinks
 * elsewhere; a player pushes it from behind (Snowman_Push). Leaving the scene, a body stands
 * its snowman's map object (0xb001 to 0xb003) on its tile or on one next to it, and a loose
 * ball saves where it is.
 *
 * Like the other scene objects it is a Base_0203f080 with a message receiver (Base_02066994) at
 * 0xec. Its update runs two state machines through tables of member pointers
 * (ov004/member_pointer.h). The first (the word at 0x39c, 14 states, most of them in overlay
 * 68) moves the ball: states 0-6 are the loose ball's, 9 is a body and 0xb a head. The second
 * (the word at 0x3a0, SnowmanTalkState) is how a snowman talks:
 *
 *   0 idle:     nothing happens; scene event 0 or 1 starts a talk.
 *   1 talk:     entering it takes the receiver, names it, picks one of three messages for the
 *               snowman's face (bits 2-3 of the flags at 0x378), from the first set while flag
 *               0x100 is still set and the second set after, raises the link's request and sets
 *               the receiver's speaker name (message 0x26 of "st_spnpc_name"); flag 0x100 is
 *               cleared. Once the link reports itself open it moves to state 2.
 *   2 talk end: once the link closes it hands the receiver back and lets the scene go on.
 *
 * Scene event 8 makes it idle again. Another actor can talk to it while it stands within 2.5 of
 * it and the first machine is in state 0xb (vtable slot 0x48). */
#ifndef CLEAN_OV003_SNOWMAN_H
#define CLEAN_OV003_SNOWMAN_H

#include "autoload_2/matrix.h" /* Mtx43 */
#include "autoload_2/vector.h" /* Vec3 */
#include "types.h"

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct SnowmanLink {
    int unk_00;
    int open;      /* nonzero while what the request opened is up */
    int requested; /* set to 1 when a talk starts */
} SnowmanLink;

enum SnowmanTalkState { SNOWMAN_TALK_IDLE, SNOWMAN_TALK_OPEN, SNOWMAN_TALK_END, SNOWMAN_TALK_STATES };

/* The first machine's states that this overlay names; the others are overlay 68's. */
enum SnowmanState {
    SNOWMAN_STATE_LOOSE = 0,     /* a loose ball, at rest or rolling */
    SNOWMAN_STATE_KNOCKED = 3,   /* what Snowman_Knock enters */
    SNOWMAN_STATE_LOOSE_END = 7, /* the states below this are the loose ball's */
    SNOWMAN_STATE_BODY = 9,      /* a snowman's body */
    SNOWMAN_STATE_HEAD = 0xb,    /* a snowman's head, which can be talked to */
    SNOWMAN_STATES = 14
};

/* Bits of Snowman.flags. */
#define SNOWMAN_NUMBER_MASK 0x0003        /* bits 0-1: which of the three kept snowmen */
#define SNOWMAN_KIND_SHIFT 2              /* bits 2-3: the face, which three messages of a set */
#define SNOWMAN_FLAG_LAYER_B 0x0010       /* collisions are tested with layer 0xb, else 0 */
#define SNOWMAN_FLAG_CONTACT_2 0x0020     /* the body is registered with contact flag 2 too */
#define SNOWMAN_FLAG_PUSHED 0x0040        /* a player pushed it this frame */
#define SNOWMAN_FLAG_WAS_PUSHED 0x0080    /* ... and the frame before */
#define SNOWMAN_FLAG_FIRST_TALK 0x0100    /* messages 0-0xb while set, 0xc-0x17 after */
#define SNOWMAN_FLAG_CONTACT_MOVED 0x0200 /* the push of a contact was added this frame */
#define SNOWMAN_FLAG_PLACED 0x0400        /* Snowman_Place moved it this frame */

/* A rotation as a quaternion in 20.12 fixed point (x, y, z, then w). */
typedef struct SnowmanQuat {
    fx32 x, y, z, w;
} SnowmanQuat;

/* One of its two models (Obj_020dd03c, 0x9c bytes). */
typedef struct SnowmanModel {
    u8 unk_00[0x64];
    Mtx43 matrix; /* where and how it is drawn */
    u8 unk_94[0x9c - 0x94];
} SnowmanModel;

/* The body other objects touch (vtable 0x02238280, derived from the class whose destructor is
 * func_02089c58), at 0x2a4. */
typedef struct SnowmanBody {
    const void *vtable; /* data_ov003_02238280 */
    u8 unk_04[0x10 - 0x04];
    fx32 push_x; /* how far what touches it pushes it this frame */
    fx32 unk_14;
    fx32 push_z;
    u8 unk_1C[0x3c - 0x1c];
    u8 touched; /* nonzero while something touches it */
    u8 unk_3D[0x44 - 0x3d];
    u8 hit; /* set when it is told of a contact with flag 4 */
    u8 unk_45[0x48 - 0x45];
    int weight; /* handed to func_02089c20; grows with the size */
} SnowmanBody;

typedef struct Snowman {
    const void *vtable; /* data_ov003_022382ac */
    u8 unk_04[0x08 - 0x04];
    u32 index; /* see above */
    u8 unk_0C[0x5c - 0x0c];
    Vec3 position;
    Vec3 last_position; /* where it was when the frame began; collisions run from it */
    u8 unk_74[0xec - 0x74];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov003_02238314 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10B[0x12c - 0x10b];
    SnowmanLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x134 - 0x130];
    SnowmanModel ball_model; /* "SNW0" */
    SnowmanModel face_model; /* "SNW1" */
    fx32 size;               /* 0x800 to 0x1400 */
    fx32 last_size;          /* the size of the frame before */
    u8 collider[0x10];       /* Member_02032c50 */
    u8 collisions;           /* counts what the collider met (func_02031288) */
    u8 unk_285[0x2a4 - 0x285];
    union {
        SnowmanBody body;
        struct {
            u8 body_head[0x4c];
            fx32 velocity_x;
            fx32 velocity_z;
            SnowmanQuat rotation; /* how far it has rolled */
            Vec3 model_offset;    /* added to the position where its models are drawn */
            u8 unk_70[0x78 - 0x70];
            Vec3 start_position; /* the position when the frame began */
        } rolling;
        u8 bytes[0x84];
    } body;
    u8 sound[0x41];     /* a sound emitter (vtable 0x0213f074) */
    u8 last_collisions; /* collisions as last seen */
    u8 rolling_sound;   /* nonzero once sound 0x81c has played for the contact going on */
    u8 unk_36B[0x374 - 0x36b];
    int roll_factor; /* how much of a push it takes, eased towards 1.0 while pushed */
    u16 flags;
    u8 unk_37A[0x394 - 0x37a];
    s16 heading; /* the direction it was last pushed in */
    u8 unk_396[0x39a - 0x396];
    u16 item_under;  /* the item a body's map object replaced, 0xfff1 for none */
    int scene_state; /* the first machine's state (enum SnowmanState) */
    int talk_state;  /* enum SnowmanTalkState */
} Snowman;

/* What it reads of another actor (the one that talks to it, or the player that pushes it). */
typedef struct SnowmanVisitor {
    u8 unk_00[0x5c];
    Vec3 position;
    u8 unk_68[0x8e - 0x68];
    s16 yaw; /* the direction it faces */
} SnowmanVisitor;

/* An entry of main's table of loose balls (func_020b03f8), one per index 0 and 1. */
typedef struct SnowmanSaved {
    Vec3 position;
    fx32 size;
} SnowmanSaved;

void SnowmanTalk_UpdateEnd(Snowman *snowman);
int SnowmanTalk_EnterEnd(void);
void SnowmanTalk_UpdateOpen(Snowman *snowman);
int SnowmanTalk_EnterOpen(Snowman *snowman);
void SnowmanTalk_UpdateIdle(Snowman *snowman);
int SnowmanTalk_EnterIdle(void);
void SnowmanTalk_Update(Snowman *snowman);
int SnowmanTalk_SetState(Snowman *snowman, int state);
void SnowmanTalk_OnSceneEvent(Snowman *snowman, int event);
int SnowmanTalk_CanTalkTo(Snowman *snowman, const SnowmanVisitor *visitor);

void Snowman_UpdateHead(Snowman *snowman);
int Snowman_EnterHead(Snowman *snowman);
void Snowman_UpdateBody(Snowman *snowman);
int Snowman_EnterBody(Snowman *snowman);
void Snowman_UpdateState(Snowman *snowman);
int Snowman_SetState(Snowman *snowman, int state);
int Snowman_KeepDisplacedItem(u16 *item);
int Snowman_ClearTile(const Vec3 *position);
int Snowman_PlaceObjectNearby(int number, Vec3 *position, u16 *replaced);
int Snowman_PlaceObject(int number, Vec3 *position, u16 *replaced);
int Snowman_CanStandAt(Vec3 *position);
void Snowman_Setup(Snowman *snowman);
int Snowman_IsBody(Snowman *snowman);
int Snowman_IsHead(Snowman *snowman);
int Snowman_IsPart(Snowman *snowman);
int Snowman_IsLoose(Snowman *snowman);
int Snowman_CanRoll(Snowman *snowman);
int Snowman_Push(Snowman *snowman, Vec3 *behind, s16 *angle, int *speed, int force, int direction);
int Snowman_Knock(Snowman *snowman, int unused);
int Snowman_Size(Snowman *snowman);
int Snowman_Place(Snowman *snowman, const Vec3 *position);
void Snowman_Roll(Snowman *snowman);
void Snowman_PreUpdate(Snowman *snowman);
void Snowman_UpdateModels(Snowman *snowman, int roll, int direction);
void Snowman_Leave(Snowman *snowman);
int Snowman_Draw(Snowman *snowman);
u32 Snowman_Update(Snowman *snowman);
void Snowman_Init(Snowman *snowman);
void Snowman_Delete(void *block);
void *Snowman_Alloc(int size);
int Snowman_MaxSize(void);
int Snowman_MinSize(void);
Snowman *Snowman_DestroyAndFree(Snowman *snowman);
Snowman *Snowman_Destroy(Snowman *snowman);
Snowman *Snowman_Construct(Snowman *snowman);
void SnowmanBody_OnContact(SnowmanBody *body, int a, int b, int flags);
SnowmanBody *SnowmanBody_Destroy(SnowmanBody *body);
SnowmanBody *SnowmanBody_Construct(SnowmanBody *body);
void Snowman_New(void);
Snowman *Snowman_ReceiverDestroyAndFree(void *receiver);
Snowman *Snowman_ReceiverDestroy(void *receiver);

#endif
