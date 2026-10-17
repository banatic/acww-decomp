/* Overlay 73: the special character of the message archive "sp_npc_boar" with the model
 * npc_sp/model/boa, object profile 0x6f (its record at data_ov073_02279a34, which the main
 * module's profile table data_020e3134 points to). Main's spawner (main/spawner.h) makes it
 * from its spawn table's entry of code 0xd002 while event 0x3b is on (Spawner_CheckD002In),
 * loading this overlay with it. A scene object of class 0x020da088 (special_scene_object.h)
 * with vtable 0x02279b00, 0x724 bytes.
 *
 * It sells the counted items 0x1531-0x153a by tens at the week's turnip price and item 0x1567
 * once a week, through its talk (BoarTalk, boar_talk.h, at 0x658).
 *
 * Its own states (BOAR_*), a table of C++ pointers to member functions (an entry and a run for
 * each state, data_ov073_02279c14, filled by __sinit_ov073_0227985c):
 * - BOAR_STAND: stands, its footsteps off, until the camera's point comes near it
 *   (Boar_NearCamera), then BOAR_WANDER;
 * - BOAR_WANDER: its footsteps on and its look asked for; while the camera's point is near it
 *   goes to random clear points 12.0 away, or turns to them, stepping aside of what blocks its
 *   way; once the point is away while it moves, BOAR_STAND;
 * - BOAR_TALK: turns to the one its talk names and talks;
 * - BOAR_FINISH: once its action ends, its event finished and BOAR_DONE;
 * - BOAR_DONE: nothing.
 * Told of event 3 (its vtable slot 0x4c, the act starts) it talks; told of event 0 it finishes;
 * told the act ended (8) it wanders. Leaving, it keeps where it stood (town_spot.h). */
#ifndef CLEAN_OV073_BOAR_H
#define CLEAN_OV073_BOAR_H

#include "autoload_2/vector.h"
#include "boar_talk.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The states. */
#define BOAR_FINISH 0
#define BOAR_DONE 1
#define BOAR_WANDER 2
#define BOAR_STAND 3
#define BOAR_TALK 4
#define BOAR_STATES 5

typedef struct Boar {
    u8 unk_000[0x5c];  /* the scene object (special_scene_object.h, scene_object.h) */
    Vec3 position;     /* 0x05c */
    u8 unk_068[0x26];  /* 0x068 */
    s16 angle;         /* 0x08e: where it faces */
    u8 unk_090[4];     /* 0x090 */
    s16 walk_angle;    /* 0x094: where it walks (scene_probe.h turns its points by it) */
    u8 unk_096[2];     /* 0x096 */
    s32 speed;         /* 0x098: its speed (scene_mover.h) */
    u8 unk_09c[0x5b5]; /* 0x09c: the members to 0x651 (boar.c names them) */
    u8 countdown;      /* 0x651: BOAR_WANDER's frames left of its walk or turn */
    u8 unk_652[2];     /* 0x652 */
    s32 state;         /* 0x654: BOAR_* (Boar_SetState) */
    BoarTalk talk;     /* 0x658 */
} Boar;

/* A state's row: its entry and its run (the null member pointer when it has none); the table,
 * filled by __sinit_ov073_0227985c (BoarInit_Tables). */
typedef struct BoarStateRow {
    MemberPointer enter;
    MemberPointer run;
} BoarStateRow;
extern BoarStateRow data_ov073_02279c14[BOAR_STATES];

/* The object's life and vtable slots. */
Boar *Boar_Destruct(Boar *self);
Boar *Boar_DestructDelete(Boar *self);
void Boar_OnEvent(Boar *self, int code);
int Boar_MayAct(Boar *self);
int Boar_ModelName(void);
int Boar_TextureName(void);
int Boar_Start(Boar *self);
int Boar_Leave(Boar *self);
int Boar_Init(Boar *self);
int Boar_AnimSpeed(void);
Boar *Boar_Create(void);

/* Its states. */
int Boar_UpdateTalk(void);
int Boar_EnterTalk(Boar *self);
int Boar_UpdateDone(void);
int Boar_UpdateFinish(Boar *self);
int Boar_EnterFinish(void);
int Boar_UpdateStand(Boar *self);
int Boar_EnterStand(Boar *self);
int Boar_UpdateWander(Boar *self);
int Boar_EnterWander(Boar *self);
void Boar_SetState(Boar *self, int state);
int Boar_Update(Boar *self);

/* How it moves. */
int Boar_AvoidObstacle(Boar *self);
int Boar_StepAside(Boar *self);
int Boar_PointAside(Boar *self, Vec3 *out, const Vec3 *offset);
int Boar_RandomPointNear(Boar *self, fx32 *x, fx32 *z);
int Boar_NearCamera(Boar *self);
int Boar_InBox(int unused, const Vec3 *centre, const Vec3 *point);

/* The overlay's static initialiser (ov073_static_init.c). */
void BoarInit_Tables(void);

#endif
