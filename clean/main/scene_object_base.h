/* The scene objects' base class (vtable 0x020dab34, include/cpp/main/Base_0203f080.h): a process
 * (autoload_2/process.h) that the events of main's queue (event_queue.h) can be about.
 *
 * Each one is registered under an id (its word 0xdc: its class id in the high half and a value
 * of its own in the low half, SceneObjectBase_SetId) in the list data_021c72cc, through the
 * node at 0xd4 whose last word points back at the object; events name their objects by id and
 * find them there (SceneObjectBase_FindAddress).
 *
 * Its own vtable slots, from 0x48 on, are the questions events ask of an object and what they
 * tell it; the base class answers no to each:
 *   0x48  whether another object (this console's player) may act on it (talk to it, check it)
 *   0x4c  told of an event: a code (2 the object underfoot taken, 3 the act starts, 6 the scene
 *         starts, 8 the act ended, the event's byte 0x17 when it runs) and who it is for (4)
 *   0x50  the address of the point others reach it at (the base class: its position, 0x5c)
 *   0x54  another question about the player, asked when 0x48 says no
 *   0x58  a question asked before an event of kind 6 or 7 is about a person shared with a
 *         session
 *   0x5c  (no caller known here)
 *
 * The flags at 0xe8: 4 marks a person (scene_object.h sets it at its set-up), and 1 and 2 pick
 * how this console's player comes to it when an act starts (SceneObjectBase_ApproachKind). The
 * word at 0xe4 is the square of the distance within which the player may act on it (0: any). */
#ifndef CLEAN_MAIN_SCENE_OBJECT_BASE_H
#define CLEAN_MAIN_SCENE_OBJECT_BASE_H

#include <stdint.h>

#include "autoload_2/links.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "ov002/error_message.h" /* MessageReceiver */
#include "types.h"

struct SceneObjectBase;

/* SceneObjectBase.flags */
#define SCENE_OBJECT_BASE_APPROACH_0 0x0001 /* SceneObjectBase_ApproachKind answers 0 */
#define SCENE_OBJECT_BASE_APPROACH_1 0x0002 /* answers 1 (without flag 1) */
#define SCENE_OBJECT_BASE_PERSON 0x0004     /* a person (a field actor or a villager) */

/* What SceneObjectBase_ApproachKind answers when neither flag 1 nor 2 is set: the player does
 * not move. */
#define SCENE_OBJECT_BASE_APPROACH_NONE 2

/* An object's place in the list of registered objects (data_021c72cc). */
typedef struct SceneObjectRegistryNode {
    ListNode link;                  /* 0x00 */
    u32 id;                         /* 0x08 */
    struct SceneObjectBase *object; /* 0x0c: the object this node is in */
} SceneObjectRegistryNode;

typedef struct SceneObjectBase {
    Process process;               /* 0x00 */
    u8 unk_50[0x0c];               /* 0x50 */
    Vec3 position;                 /* 0x5c */
    u8 unk_68[0x26];               /* 0x68 */
    s16 yaw;                       /* 0x8e */
    u8 unk_90[0x44];               /* 0x90 */
    SceneObjectRegistryNode entry; /* 0xd4: entry.id is the object's id */
    s32 reach_squared;             /* 0xe4: 0: no limit */
    u16 flags;                     /* 0xe8: SCENE_OBJECT_BASE_* */
} SceneObjectBase;

/* The vtable slots above, by offset. */
#define SCENE_OBJECT_BASE_SLOT_MAY_ACT 0x48
#define SCENE_OBJECT_BASE_SLOT_ON_EVENT 0x4c
#define SCENE_OBJECT_BASE_SLOT_REACH_POINT 0x50
#define SCENE_OBJECT_BASE_SLOT_ASK_54 0x54
#define SCENE_OBJECT_BASE_SLOT_ASK_58 0x58

typedef int SceneObjectBaseAsk(SceneObjectBase *object, SceneObjectBase *other);
typedef void SceneObjectBaseOnEvent(SceneObjectBase *object, int event, int participant);
typedef Vec3 *SceneObjectBaseReachPoint(SceneObjectBase *object);

/* The function in the vtable slot at `offset` of `object`. */
static inline uintptr_t SceneObjectBase_Slot(const SceneObjectBase *object, u32 offset)
{
    return object->process.vtable[offset / 4];
}

void SceneObjectBase_ClearFlags(SceneObjectBase *object, u16 mask);
void SceneObjectBase_SetFlags(SceneObjectBase *object, u16 mask);
int SceneObjectBase_TestFlags(SceneObjectBase *object, u16 mask);
int SceneObjectBase_IsPerson(SceneObjectBase *object);
void SceneObjectBase_MarkPerson(SceneObjectBase *object);
int SceneObjectBase_ApproachKind(SceneObjectBase *object);
void SceneObjectBase_ClearApproach(SceneObjectBase *object);
void SceneObjectBase_DefaultApproach(SceneObjectBase *object);
void SceneObjectBase_SetReach(SceneObjectBase *object, int distance);
void SceneObjectBase_ReleaseReceiver(SceneObjectBase *object, MessageReceiver *receiver);
void SceneObjectBase_TakeReceiver(SceneObjectBase *object, MessageReceiver *receiver);
int SceneObjectBase_Slot5c(void);
int SceneObjectBase_Ask58(void);
int SceneObjectBase_Ask54(void);
int SceneObjectBase_ReachPointAddress(SceneObjectBase *object);
void SceneObjectBase_OnEvent(void);
int SceneObjectBase_MayAct(void);
int SceneObjectBase_CanAct(SceneObjectBase *target, SceneObjectBase *actor);
int SceneObjectBase_InReach(SceneObjectBase *target, SceneObjectBase *actor);
int SceneObjectBase_Faces(SceneObjectBase *target, SceneObjectBase *viewer, int min, int max);
void *SceneObjectBase_FindActable(void *actor);
int SceneObjectBase_FindAddress(int id);
void SceneObjectBase_SetId(SceneObjectBase *object, u32 value);

#endif
