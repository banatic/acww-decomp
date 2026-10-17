/* Overlay 78: the camel, the special character of the message file "sp_npc_camel" with the
 * model npc_sp/model/cml, object profile 0x6a (her record at data_ov078_02279a60, which main's
 * profile table data_020e3134 points to). Main's spawner (main/spawner.h) makes her from its
 * spawn table's entry of code 0xd003, loading this overlay with her. A scene object of class
 * 0x020da088 (special_scene_object.h) with vtable 0x02279b2c, 0x714 bytes.
 *
 * Her talk (CamelTalk, camel_talk.h, at 0x658) hands the player a villager's errand (the entry
 * at 0x94 of the player's villager part, villager_part_entry.h) and, once it is done, lets the
 * player choose one of two items drawn for her reward; she also takes item 0x13ac from the
 * pockets for another item.
 *
 * She moves as overlay 73's character does (ov073/boar.h). Her own states (CAMEL_*), a table
 * of C++ pointers to member functions (an entry and a run for each state,
 * data_ov078_02279c48, filled by __sinit_ov078_022798ac):
 * - CAMEL_STAND: stands, her footsteps off, until the camera's point comes near her
 *   (Camel_NearCamera), then CAMEL_WANDER;
 * - CAMEL_WANDER: her footsteps on and her look asked for; while the camera's point is near
 *   she goes to random clear points 12.0 away, or turns to them, stepping aside of what blocks
 *   her way; once the point is away while she moves, CAMEL_STAND;
 * - CAMEL_TALK: turns to the one her talk names and talks;
 * - CAMEL_FINISH: once her action ends, her event finished and CAMEL_DONE;
 * - CAMEL_DONE: nothing.
 * Told of event 3 (her vtable slot 0x4c) she talks; told of event 1 her talk is set up the same
 * way but she finishes; told of event 0 she finishes; told the act ended (8) she wanders.
 * Leaving, she keeps where she stood (town_spot.h). */
#ifndef CLEAN_OV078_CAMEL_H
#define CLEAN_OV078_CAMEL_H

#include "autoload_2/vector.h"
#include "camel_talk.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The states. */
#define CAMEL_FINISH 0
#define CAMEL_DONE 1
#define CAMEL_WANDER 2
#define CAMEL_STAND 3
#define CAMEL_TALK 4
#define CAMEL_STATES 5

typedef struct Camel {
    u8 unk_000[0x5c];  /* the scene object (special_scene_object.h, scene_object.h) */
    Vec3 position;     /* 0x05c */
    u8 unk_068[0x26];  /* 0x068 */
    s16 angle;         /* 0x08e: where she faces */
    u8 unk_090[4];     /* 0x090 */
    s16 walk_angle;    /* 0x094: where she walks (scene_probe.h turns her points by it) */
    u8 unk_096[2];     /* 0x096 */
    s32 speed;         /* 0x098: her speed (scene_mover.h) */
    u8 unk_09c[0x5b5]; /* 0x09c: the members to 0x651 (camel.c names them) */
    u8 countdown;      /* 0x651: CAMEL_WANDER's frames left of her walk or turn */
    u8 unk_652[2];     /* 0x652 */
    s32 state;         /* 0x654: CAMEL_* (Camel_SetState) */
    CamelTalk talk;    /* 0x658 */
} Camel;

/* A state's row: its entry and its run (the null member pointer when it has none); the table,
 * filled by __sinit_ov078_022798ac (CamelInit_Tables). */
typedef struct CamelStateRow {
    MemberPointer enter;
    MemberPointer run;
} CamelStateRow;
extern CamelStateRow data_ov078_02279c48[CAMEL_STATES];

/* The object's life and vtable slots. */
Camel *Camel_Destruct(Camel *self);
Camel *Camel_DestructDelete(Camel *self);
void Camel_OnEvent(Camel *self, unsigned int code);
int Camel_MayAct(Camel *self);
int Camel_ModelName(void);
int Camel_TextureName(void);
int Camel_Start(Camel *self);
int Camel_Leave(Camel *self);
int Camel_Init(Camel *self);
int Camel_AnimSpeed(void);
Camel *Camel_Create(void);

/* Her states. */
int Camel_UpdateTalk(void);
int Camel_EnterTalk(Camel *self);
int Camel_UpdateDone(void);
int Camel_UpdateFinish(Camel *self);
int Camel_EnterFinish(void);
int Camel_UpdateStand(Camel *self);
int Camel_EnterStand(Camel *self);
int Camel_UpdateWander(Camel *self);
int Camel_EnterWander(Camel *self);
void Camel_SetState(Camel *self, int state);
int Camel_Update(Camel *self);

/* How she moves. */
int Camel_AvoidObstacle(Camel *self);
int Camel_StepAside(Camel *self);
int Camel_PointAside(Camel *self, Vec3 *out, const Vec3 *offset);
int Camel_RandomPointNear(Camel *self, fx32 *x, fx32 *z);
int Camel_NearCamera(Camel *self);
int Camel_InBox(int unused, const Vec3 *centre, const Vec3 *point);

/* The overlay's static initialiser (ov078_static_init.c). */
void CamelInit_Tables(void);

#endif
