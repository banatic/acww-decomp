/* A room object of the RMO family (rmo_object.h) built from /roomObj/obj_r_box, that talks
 * with the message file "sp_npc_trash" (vtable 0x022553d8, receiver part 0x02255454 at 0x290,
 * 0x620 bytes). Only one exists at a time: data_ov004_02258490 points to it from its start to
 * its release, and the touch screen's picks ask for it (TouchPick_RoomObject12).
 *
 * It stands in a collision box and a box of touch-pick faces, both 0x2000 wide, 0x4000 deep and
 * 0x2000 high at its position. Its lid (TrashBox lid byte, RmoObject byte 0x24c) is a state
 * kept in the room objects' shared values (main/room_object_state.h, number 0): vtable slot 0x60
 * enters one of four lid states (closed, opening, open, closing), playing joint animation 0
 * (opening) or 1 (closing) once and sounds 0x4d6 and 0x4d7; the opening and closing go on to
 * open and closed when their animation has run out.
 *
 * The scene's events (vtable slot 0x4c) drive its own state (TrashBox.state), through tables of
 * member pointers (member_pointer.h): event 0 starts the talk, event 8 makes it idle. After
 * the talk it opens the lid, opens the pockets' screen (group 9) in mode 0x20 once the lid is
 * open, closes the lid when that screen has closed, and lets the scene go on once the lid is
 * closed. It may be acted on (vtable slot 0x48) by an object within 0x299a of it on the XZ
 * plane that faces it within 0x1200. */
#ifndef CLEAN_OV004_TRASH_BOX_H
#define CLEAN_OV004_TRASH_BOX_H

#include "main/actor.h"
#include "main/collision_box.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "rmo_object.h"
#include "types.h"

typedef struct TrashBox {
    RmoObject base;                                 /* 0x000: base.unk_24c[0] is the lid */
    TalkReceiver receiver;                          /* 0x290: vtable data_ov004_02255454 */
    CollisionBox box;                               /* 0x2d8 */
    TouchPickFace pick_faces[TOUCH_PICK_BOX_FACES]; /* 0x374 */
    s32 state;                                      /* 0x61c: TrashBoxState */
} TrashBox;

enum TrashBoxState {
    TRASH_BOX_IDLE = 0,
    TRASH_BOX_TALK = 1,      /* the talk asked for: waits for it to open */
    TRASH_BOX_TALK_END = 2,  /* waits for the talk to close */
    TRASH_BOX_OPEN_LID = 3,  /* waits for the lid to open */
    TRASH_BOX_POCKETS = 4,   /* the pockets' screen: waits for it to close */
    TRASH_BOX_CLOSE_LID = 5, /* waits for the lid to close */
    TRASH_BOX_STATE_COUNT = 6
};

/* The lid's states (TrashBox.base.unk_24c[0]). */
enum TrashBoxLid {
    TRASH_BOX_LID_CLOSED = 0,
    TRASH_BOX_LID_OPENING = 1,
    TRASH_BOX_LID_OPEN = 2,
    TRASH_BOX_LID_CLOSING = 3,
    TRASH_BOX_LID_COUNT = 4
};

int TrashBox_RemoveBox(TrashBox *self);
int TrashBox_AddBox(TrashBox *self);
void TrashBox_OnAnswer(TrashBox *self);
void TrashBox_AfterMessage(TrashBox *self);
void TrashBox_OnTalkIgnored(TrashBox *self);
void TrashBox_UpdateCloseLid(TrashBox *self);
int TrashBox_EnterCloseLid(TrashBox *self);
void TrashBox_UpdatePockets(TrashBox *self);
int TrashBox_EnterPockets(TrashBox *self);
void TrashBox_UpdateOpenLid(TrashBox *self);
int TrashBox_EnterOpenLid(TrashBox *self);
void TrashBox_UpdateTalkEnd(TrashBox *self);
int TrashBox_EnterTalkEnd(TrashBox *self);
void TrashBox_UpdateTalk(TrashBox *self);
int TrashBox_EnterTalk(TrashBox *self);
void TrashBox_UpdateIdle(TrashBox *self);
int TrashBox_EnterIdle(TrashBox *self);
void TrashBox_UpdateState(TrashBox *self);
int TrashBox_EnterState(TrashBox *self, int state);
void TrashBox_UpdateClosing(TrashBox *self);
int TrashBox_EnterClosing(TrashBox *self);
void TrashBox_UpdateOpen(TrashBox *self);
int TrashBox_EnterOpen(TrashBox *self);
void TrashBox_UpdateOpening(TrashBox *self);
int TrashBox_EnterOpening(TrashBox *self);
void TrashBox_UpdateClosed(TrashBox *self);
int TrashBox_EnterClosed(TrashBox *self);
void TrashBox_UpdateLid(TrashBox *self);
int TrashBox_SetLid(TrashBox *self, u32 lid);
void TrashBox_OnSceneEvent(TrashBox *self, int event);
int TrashBox_MayAct(TrashBox *self, Actor *other);
int TrashBox_Release(TrashBox *self);
int TrashBox_Draw(TrashBox *self);
int TrashBox_Update(TrashBox *self);
int TrashBox_Start(TrashBox *self);
TrashBox *TrashBox_Delete(TrashBox *self);
TrashBox *TrashBox_Destruct(TrashBox *self);
TrashBox *TrashBox_Construct(TrashBox *self);
u32 TrashBox_Current(void);
void TrashBox_Create(void);
TrashBox *TrashBoxReceiver_Delete(void *receiver);
void TrashBoxReceiver_OnAnswer(void *receiver);
void TrashBoxReceiver_AfterMessage(void *receiver);
void TrashBoxReceiver_OnTalkIgnored(void *receiver);
TrashBox *TrashBoxReceiver_Destruct(void *receiver);

#endif
