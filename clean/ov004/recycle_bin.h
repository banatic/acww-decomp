/* The town hall's recycle bin: a room object of the RMO family (rmo_object.h) built from
 * /roomObj/obj_r_box (vtable 0x022553d8, receiver part 0x02255454 at 0x290, 0x620 bytes),
 * that talks with the message file "sp_npc_trash" (message 0: recyclables are collected on
 * Monday and Thursday at 6 a.m.). Only one exists at a time: data_ov004_02258490 points to it from its start to
 * its release, and the touch screen's picks ask for it (TouchPick_RoomObject12).
 *
 * It stands in a collision box and a box of touch-pick faces, both 0x2000 wide, 0x4000 deep and
 * 0x2000 high at its position. Its lid (RecycleBin lid byte, RmoObject byte 0x24c) is a state
 * kept in the room objects' shared values (main/room_object_state.h, number 0): vtable slot 0x60
 * enters one of four lid states (closed, opening, open, closing), playing joint animation 0
 * (opening) or 1 (closing) once and sounds 0x4d6 and 0x4d7; the opening and closing go on to
 * open and closed when their animation has run out.
 *
 * The scene's events (vtable slot 0x4c) drive its own state (RecycleBin.state), through tables of
 * member pointers (member_pointer.h): event 0 starts the talk, event 8 makes it idle. After
 * the talk it opens the lid, opens the recycle bin's screen (group 9 in mode 0x20, overlay 110's
 * PUBLIC_BOX_MODE_RECYCLE) once the lid is open, closes the lid when that screen has closed, and lets the scene go on once the lid is
 * closed. It may be acted on (vtable slot 0x48) by an object within 0x299a of it on the XZ
 * plane that faces it within 0x1200. */
#ifndef CLEAN_OV004_RECYCLE_BIN_H
#define CLEAN_OV004_RECYCLE_BIN_H

#include "main/actor.h"
#include "main/collision_box.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "rmo_object.h"
#include "types.h"

typedef struct RecycleBin {
    RmoObject base;                                 /* 0x000: base.unk_24c[0] is the lid */
    TalkReceiver receiver;                          /* 0x290: vtable data_ov004_02255454 */
    CollisionBox box;                               /* 0x2d8 */
    TouchPickFace pick_faces[TOUCH_PICK_BOX_FACES]; /* 0x374 */
    s32 state;                                      /* 0x61c: RecycleBinState */
} RecycleBin;

enum RecycleBinState {
    RECYCLE_BIN_IDLE = 0,
    RECYCLE_BIN_TALK = 1,      /* the talk asked for: waits for it to open */
    RECYCLE_BIN_TALK_END = 2,  /* waits for the talk to close */
    RECYCLE_BIN_OPEN_LID = 3,  /* waits for the lid to open */
    RECYCLE_BIN_SCREEN = 4,    /* the recycle bin's screen: waits for it to close */
    RECYCLE_BIN_CLOSE_LID = 5, /* waits for the lid to close */
    RECYCLE_BIN_STATE_COUNT = 6
};

/* The lid's states (RecycleBin.base.unk_24c[0]). */
enum RecycleBinLid {
    RECYCLE_BIN_LID_CLOSED = 0,
    RECYCLE_BIN_LID_OPENING = 1,
    RECYCLE_BIN_LID_OPEN = 2,
    RECYCLE_BIN_LID_CLOSING = 3,
    RECYCLE_BIN_LID_COUNT = 4
};

int RecycleBin_RemoveBox(RecycleBin *self);
int RecycleBin_AddBox(RecycleBin *self);
void RecycleBin_OnAnswer(RecycleBin *self);
void RecycleBin_AfterMessage(RecycleBin *self);
void RecycleBin_OnTalkIgnored(RecycleBin *self);
void RecycleBin_UpdateCloseLid(RecycleBin *self);
int RecycleBin_EnterCloseLid(RecycleBin *self);
void RecycleBin_UpdateScreen(RecycleBin *self);
int RecycleBin_EnterScreen(RecycleBin *self);
void RecycleBin_UpdateOpenLid(RecycleBin *self);
int RecycleBin_EnterOpenLid(RecycleBin *self);
void RecycleBin_UpdateTalkEnd(RecycleBin *self);
int RecycleBin_EnterTalkEnd(RecycleBin *self);
void RecycleBin_UpdateTalk(RecycleBin *self);
int RecycleBin_EnterTalk(RecycleBin *self);
void RecycleBin_UpdateIdle(RecycleBin *self);
int RecycleBin_EnterIdle(RecycleBin *self);
void RecycleBin_UpdateState(RecycleBin *self);
int RecycleBin_EnterState(RecycleBin *self, int state);
void RecycleBin_UpdateClosing(RecycleBin *self);
int RecycleBin_EnterClosing(RecycleBin *self);
void RecycleBin_UpdateOpen(RecycleBin *self);
int RecycleBin_EnterOpen(RecycleBin *self);
void RecycleBin_UpdateOpening(RecycleBin *self);
int RecycleBin_EnterOpening(RecycleBin *self);
void RecycleBin_UpdateClosed(RecycleBin *self);
int RecycleBin_EnterClosed(RecycleBin *self);
void RecycleBin_UpdateLid(RecycleBin *self);
int RecycleBin_SetLid(RecycleBin *self, u32 lid);
void RecycleBin_OnSceneEvent(RecycleBin *self, int event);
int RecycleBin_MayAct(RecycleBin *self, Actor *other);
int RecycleBin_Release(RecycleBin *self);
int RecycleBin_Draw(RecycleBin *self);
int RecycleBin_Update(RecycleBin *self);
int RecycleBin_Start(RecycleBin *self);
RecycleBin *RecycleBin_Delete(RecycleBin *self);
RecycleBin *RecycleBin_Destruct(RecycleBin *self);
RecycleBin *RecycleBin_Construct(RecycleBin *self);
u32 RecycleBin_Current(void);
void RecycleBin_Create(void);
RecycleBin *RecycleBinReceiver_Delete(void *receiver);
void RecycleBinReceiver_OnAnswer(void *receiver);
void RecycleBinReceiver_AfterMessage(void *receiver);
void RecycleBinReceiver_OnTalkIgnored(void *receiver);
RecycleBin *RecycleBinReceiver_Destruct(void *receiver);

#endif
