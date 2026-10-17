/* Overlay 79: the walrus, the special character of the message archive "sp_npc_walrus" with the
 * model npc_sp/model/wrl, object profile 0x6b (its record at data_ov079_0227a038, which the
 * main module's profile table data_020e3134 points to). Main's spawner (main/spawner.h) makes
 * him from its spawn table's entry of code 0xd013 while event 0x41 is on
 * (Spawner_CheckEvents3e), loading this overlay with him. A scene object of class 0x020da088
 * (special_scene_object.h) with vtable 0x0227a104, 0x724 bytes.
 *
 * He asks the player for an item: through his talk (WalrusTalk, walrus_talk.h, at
 * 0x658) the player gives him an item from the pockets, and for some of them he gives one of
 * his designs in return (walrus_talk.h).
 *
 * He moves as overlay 73's character does (boar.h). His own states (WALRUS_*), a table of C++
 * pointers to member functions (an entry and a run for each state, data_ov079_0227a224, filled
 * by __sinit_ov079_02279e74):
 * - WALRUS_STAND: stands, his footsteps off, until the camera's point comes near him
 *   (Walrus_NearCamera), then WALRUS_WANDER;
 * - WALRUS_WANDER: his footsteps on and his look asked for; while the camera's point is near
 *   he goes to random clear points 12.0 away, or turns to them, stepping aside of what blocks
 *   his way; once the point is away while he moves, WALRUS_STAND;
 * - WALRUS_TALK: turns to the one his talk names and talks;
 * - WALRUS_FINISH: once his action ends, his event finished and WALRUS_DONE;
 * - WALRUS_DONE: nothing.
 * Told the act starts (3, his vtable slot 0x4c) he talks; told of event 0 he finishes; told the
 * act ended (8) he wanders. Leaving (unless the player was sent to an announcement), he picks
 * a new random spot of the town for part 0x04 of the object at data_021d27ac (town_spot.h). */
#ifndef CLEAN_OV079_WALRUS_H
#define CLEAN_OV079_WALRUS_H

#include "autoload_2/vector.h"
#include "ov004/member_pointer.h"
#include "types.h"
#include "walrus_talk.h"

/* The states. */
#define WALRUS_FINISH 0
#define WALRUS_DONE 1
#define WALRUS_WANDER 2
#define WALRUS_STAND 3
#define WALRUS_TALK 4
#define WALRUS_STATES 5

typedef struct Walrus {
    u8 unk_000[0x5c];  /* the scene object (special_scene_object.h, scene_object.h) */
    Vec3 position;     /* 0x05c */
    u8 unk_068[0x26];  /* 0x068 */
    s16 angle;         /* 0x08e: where he faces */
    u8 unk_090[4];     /* 0x090 */
    s16 walk_angle;    /* 0x094: where he walks (scene_probe.h turns its points by it) */
    u8 unk_096[2];     /* 0x096 */
    s32 speed;         /* 0x098: his speed (scene_mover.h) */
    u8 unk_09c[0x5b5]; /* 0x09c: the members to 0x651 (walrus.c names them) */
    u8 countdown;      /* 0x651: WALRUS_WANDER's frames left of his walk or turn */
    u8 unk_652[2];     /* 0x652 */
    s32 state;         /* 0x654: WALRUS_* (Walrus_SetState) */
    WalrusTalk talk;   /* 0x658 */
} Walrus;

/* A state's row: its entry and its run (the null member pointer when it has none); the table,
 * filled by __sinit_ov079_02279e74 (WalrusInit_Tables). */
typedef struct WalrusStateRow {
    MemberPointer enter;
    MemberPointer run;
} WalrusStateRow;
extern WalrusStateRow data_ov079_0227a224[WALRUS_STATES];

/* The object's life and vtable slots. */
Walrus *Walrus_Destruct(Walrus *self);
Walrus *Walrus_DestructDelete(Walrus *self);
void Walrus_OnEvent(Walrus *self, int code);
int Walrus_MayAct(Walrus *self);
int Walrus_ModelName(void);
int Walrus_TextureName(void);
int Walrus_Start(Walrus *self);
int Walrus_Leave(Walrus *self);
int Walrus_Init(Walrus *self);
int Walrus_AnimSpeed(void);
Walrus *Walrus_Create(void);

/* His states. */
int Walrus_UpdateTalk(void);
int Walrus_EnterTalk(Walrus *self);
int Walrus_UpdateDone(void);
int Walrus_UpdateFinish(Walrus *self);
int Walrus_EnterFinish(void);
int Walrus_UpdateStand(Walrus *self);
int Walrus_EnterStand(Walrus *self);
int Walrus_UpdateWander(Walrus *self);
int Walrus_EnterWander(Walrus *self);
void Walrus_SetState(Walrus *self, int state);
int Walrus_Update(Walrus *self);

/* How he moves. */
int Walrus_AvoidObstacle(Walrus *self);
int Walrus_StepAside(Walrus *self);
int Walrus_PointAside(Walrus *self, Vec3 *out, const Vec3 *offset);
int Walrus_RandomPointNear(Walrus *self, fx32 *x, fx32 *z);
int Walrus_NearCamera(Walrus *self);
int Walrus_InBox(int unused, const Vec3 *centre, const Vec3 *point);

/* The overlay's static initialiser (ov079_static_init.c). */
void WalrusInit_Tables(void);

#endif
