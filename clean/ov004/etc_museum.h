/* The "obj_etc_museum" scene object of overlay 4 (class vtable 0x022533e0, receiver part
 * 0x02253454, 0x170 bytes): a spot of the museum's rooms that, talked to, tells about the
 * exhibits of a list and who gave them, from the museum's record (main/museum_record.h,
 * data_021f38f8).
 *
 * func_ov004_022453c0 makes them (EtcMuseum_Spawn) with a kind, a list of exhibits (numbers
 * within one group of the record), the angle the player may face away from it by and a message.
 * The kind picks the record's group the exhibits are in (func_ov004_0221bad0 makes the item
 * codes):
 *   0  group C (0x12b0 on), 1  group B (0x12e8 on), 2  group D (0x3894 on, 4 apart),
 *   3  group A (0x450c on, 4 apart);
 *   4  a lone one (EtcMuseum_SpawnLone, from func_ov004_02241e88) with no exhibits, put before
 *      this console's player when it is created; it asks for an event about itself once, says
 *      who gave item 0x12e4 (or that nobody did) and is deleted after.
 * Up to 32 of kinds 0-3 exist at once: a table at data_ov004_0225797c holds them by their index
 * (the byte at 0x154), with their count at data_ov004_02257908; main's pen picking reads it
 * (touch pick kind 14, TouchPick_RoomEntry20). The byte data_ov004_02257904 is set while the
 * lone one exists.
 *
 * Its update runs one of four states (the word at 0x134):
 *   0 idle:     the lone one asks for its event, or is deleted once it has talked.
 *   1 talk:     entering it picks the message from the exhibits given (the first one given
 *               becomes the current one) and asks the talk to open; on to 2 once it is up.
 *   2 open:     once the talk has closed it releases the receiver and ends the event.
 *   3 lone talk: the lone one's talk; on to 2 once it is up.
 * Events: 0 enters state 1, 1 state 3, 8 state 0.
 *
 * Through its receiver the talk tells it when a message begins (EtcMuseum_OnMessageBegun puts
 * the exhibits' names and their givers in it), ends (EtcMuseum_OnMessageEnded offers to go on
 * when exhibits are left) and the player's answer (EtcMuseum_OnAnswer). */
#ifndef CLEAN_OV004_ETC_MUSEUM_H
#define CLEAN_OV004_ETC_MUSEUM_H

#include "autoload_2/vector.h"
#include "main/scene_object_base.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "types.h"

enum EtcMuseumState { ETC_MUSEUM_IDLE, ETC_MUSEUM_TALK, ETC_MUSEUM_OPEN, ETC_MUSEUM_LONE_TALK, ETC_MUSEUM_STATES };

/* EtcMuseum.kind */
enum EtcMuseumKind {
    ETC_MUSEUM_GROUP_C = 0,
    ETC_MUSEUM_GROUP_B = 1,
    ETC_MUSEUM_GROUP_D = 2,
    ETC_MUSEUM_GROUP_A = 3,
    ETC_MUSEUM_LONE = 4
};

#define ETC_MUSEUM_MAX 32
/* EtcMuseum.index of one in no entry of the table. */
#define ETC_MUSEUM_NO_INDEX 0xff

typedef struct EtcMuseum {
    SceneObjectBase base;   /* 0x000: its vtable data_ov004_022533e0 */
    TalkReceiver receiver;  /* 0x0ec: its vtable data_ov004_02253454 */
    s32 state;              /* 0x134: enum EtcMuseumState */
    TouchPickSphere sphere; /* 0x138: where the pen picks it */
    u8 index;               /* 0x154: its entry in the table, ETC_MUSEUM_NO_INDEX for none */
    u8 current;             /* 0x155: the exhibit talked about (an index into `items`) */
    u8 unk_156[2];          /* 0x156 */
    s32 face_angle;         /* 0x158: how far from facing it the player may turn */
    u32 kind;               /* 0x15c: enum EtcMuseumKind */
    s16 complete_message;   /* 0x160: group A's message once every exhibit is given */
    u8 unk_162[2];          /* 0x162 */
    u16 *items;             /* 0x164: the exhibits' item codes (from the current heap) */
    u32 count;              /* 0x168: how many */
    u8 talks;               /* 0x16c: the lone one's talks */
    u8 unk_16d[3];          /* 0x16d */
} EtcMuseum;

int EtcMuseum_SpawnLone(void);
void EtcMuseum_Spawn(int kind, Vec3 *position, int yaw, int face_angle, s16 complete_message, const u8 *exhibits, int count);
EtcMuseum *EtcMuseum_Get(int index);
void EtcMuseum_UpdateLoneTalk(EtcMuseum *museum);
int EtcMuseum_EnterLoneTalk(EtcMuseum *museum);
void EtcMuseum_UpdateOpen(EtcMuseum *museum);
int EtcMuseum_EnterOpen(EtcMuseum *museum);
void EtcMuseum_UpdateTalk(EtcMuseum *museum);
int EtcMuseum_EnterTalk(EtcMuseum *museum);
void EtcMuseum_UpdateIdle(EtcMuseum *museum);
int EtcMuseum_EnterIdle(EtcMuseum *museum);
void EtcMuseum_Update(EtcMuseum *museum);
int EtcMuseum_SetState(EtcMuseum *museum, int state);
void EtcMuseum_OnAnswer(EtcMuseum *museum);
void EtcMuseum_OnMessageEnded(EtcMuseum *museum);
void EtcMuseum_OnMessageBegun(EtcMuseum *museum);
void EtcMuseum_HandleEvent(EtcMuseum *museum, int event);
int EtcMuseum_IsFacedBy(EtcMuseum *museum, const SceneObjectBase *viewer);
int EtcMuseum_IsLone(EtcMuseum *museum);
void EtcMuseum_NextGiven(EtcMuseum *museum);
int EtcMuseum_CountGivenLeft(EtcMuseum *museum);
int EtcMuseum_AllGiven(EtcMuseum *museum);
int EtcMuseum_AnyGiven(EtcMuseum *museum);
int EtcMuseum_MakeItems(EtcMuseum *museum);
int EtcMuseum_Unregister(EtcMuseum *museum);
int EtcMuseum_Register(EtcMuseum *museum);
void EtcMuseum_ClearTableIfEmpty(void);
int EtcMuseum_OnDelete(EtcMuseum *museum);
int EtcMuseum_Draw(void);
int EtcMuseum_Execute(EtcMuseum *museum);
int EtcMuseum_OnCreate(EtcMuseum *museum);
EtcMuseum *EtcMuseum_Delete(EtcMuseum *museum);
EtcMuseum *EtcMuseum_Destroy(EtcMuseum *museum);
EtcMuseum *EtcMuseum_Construct(EtcMuseum *museum);
void EtcMuseum_New(void);
EtcMuseum *EtcMuseumReceiver_Delete(void *receiver);
void EtcMuseumReceiver_OnAnswer(void *receiver);
void EtcMuseumReceiver_OnMessageEnded(void *receiver);
void EtcMuseumReceiver_OnMessageBegun(void *receiver);
EtcMuseum *EtcMuseumReceiver_Destroy(void *receiver);

#endif
