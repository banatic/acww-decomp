/* The chests: a class of overlay 4's room objects (vtable 0x0225211c, receiver part 0x022521c8,
 * 0x868 bytes) whose receiver part is named "obj_etc_nchest". Kinds 0xb, 0xc and 0xd (RoomObject.unk_780) are
 * the chests 0 to 2 (Chest_Index); kind 0xf has other animations. It runs two state machines
 * besides the base class's (room_object.h), each through tables of member pointers
 * (member_pointer.h):
 *
 * - its lid (Chest.lid), entered through vtable slot 0x70: closed (the switch on), opening
 *   (sound 1, the animations of variant 0 once), open (the switch off) and closing (sound 2).
 *   Touching it closed asks the scene for an event (func_0203e0a8); a chest of kind 0xb does so
 *   only when the cells in front of it are free, else the touch is undone. In mode 2 (unk_76C)
 *   it opens and closes by itself;
 * - its talk (Chest.talk_step): the scene's event 1 (vtable slot 0x4c) starts the menu when
 *   func_020b67d4 and Room_Check0220fed0 allow it, else a talk; event 8 ends either. Both first
 *   send actor 4 (func_02096718(4)) message 0x2d with the chest's index and its entry's values
 *   (func_ov004_0222c030) and wait for func_ov004_0222c2b0, then open the lid; the menu opens
 *   group 9 in mode 0x22, the talk takes the receiver and sets its state byte to one of 16
 *   values. Both end by sending actor 4 message 0x2f with the index (func_ov004_0222c00c) and
 *   closing the lid, after which the scene goes on (func_0203e020).
 *
 * Once its model is bound it binds the animations of variant 0, its lid starts closed when its
 * switch is on (or func_ov004_0223c10c says so), else open, and it does not talk; each frame it
 * runs the talk, then the lid. It is idle when the base class says so and it does not talk. */
#ifndef CLEAN_OV004_CHEST_H
#define CLEAN_OV004_CHEST_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct Chest {
    RoomObject base;
    Glow unk_844; /* built by Glow_Construct and taken down by Glow_Destruct, otherwise unused here */
    u8 lid;       /* ChestLid */
    u8 unk_861[3];
    s32 talk_step; /* ChestTalkStep */
} Chest;

enum ChestLid {
    CHEST_LID_CLOSED = 0,
    CHEST_LID_OPENING = 1,
    CHEST_LID_OPEN = 2,
    CHEST_LID_CLOSING = 3,
    CHEST_LID_STATE_COUNT = 4
};

enum ChestTalkStep {
    CHEST_TALK_NONE = 0,
    CHEST_MENU_NEXT = 1,     /* the next frame sends the message */
    CHEST_MENU_ANNOUNCE = 2, /* sends message 0x2d, waits for func_ov004_0222c2b0 */
    CHEST_MENU_OPEN = 3,     /* opens the lid, waits for it to be open */
    CHEST_MENU = 4,          /* opens the menu, waits for it to close */
    CHEST_MENU_CLOSE = 5,    /* closes the lid, waits for it to be closed */
    CHEST_TALK_NEXT = 6,
    CHEST_TALK_ANNOUNCE = 7,
    CHEST_TALK_OPEN = 8,
    CHEST_TALK = 9,      /* takes the receiver, waits for the link to open */
    CHEST_TALK_END = 10, /* waits for the link to close */
    CHEST_TALK_CLOSE = 11,
    CHEST_TALK_STEP_COUNT = 12
};

void Chest_UpdateTalkClose(Chest *chest);
int Chest_EnterTalkClose(Chest *chest);
void Chest_UpdateTalkEnd(Chest *chest);
int Chest_EnterTalkEnd(Chest *chest);
void Chest_UpdateTalk(Chest *chest);
int Chest_EnterTalk(Chest *chest);
void Chest_UpdateTalkOpen(Chest *chest);
int Chest_EnterTalkOpen(Chest *chest);
void Chest_UpdateTalkAnnounce(Chest *chest);
int Chest_EnterTalkAnnounce(Chest *chest);
void Chest_UpdateTalkNext(Chest *chest);
int Chest_EnterTalkNext(Chest *chest);
void Chest_UpdateMenuClose(Chest *chest);
int Chest_EnterMenuClose(Chest *chest);
int Chest_UpdateMenu(Chest *chest);
int Chest_EnterMenu(Chest *chest);
void Chest_UpdateMenuOpen(Chest *chest);
int Chest_EnterMenuOpen(Chest *chest);
void Chest_UpdateMenuAnnounce(Chest *chest);
int Chest_EnterMenuAnnounce(Chest *chest);
void Chest_UpdateMenuNext(Chest *chest);
int Chest_EnterMenuNext(Chest *chest);
void Chest_UpdateTalkNone(Chest *chest);
int Chest_EnterTalkNone(Chest *chest);
void Chest_UpdateTalkStep(Chest *chest);
int Chest_EnterTalkStep(Chest *chest, int step);
int Chest_Index(Chest *chest);
void Chest_OnSceneEvent(Chest *chest, int event);
void Chest_UpdateLidClosing(Chest *chest);
int Chest_EnterLidClosing(Chest *chest);
void Chest_UpdateLidOpen(Chest *chest);
int Chest_EnterLidOpen(Chest *chest);
void Chest_UpdateLidOpening(Chest *chest);
int Chest_EnterLidOpening(Chest *chest);
void Chest_UpdateLidClosed(Chest *chest);
int Chest_EnterLidClosed(Chest *chest);
void Chest_UpdateLid(Chest *chest);
int Chest_EnterLid(Chest *chest, unsigned int state, int value);
u8 Chest_LidStateIsOn(Chest *chest, unsigned int state);
int Chest_IsIdle(Chest *chest);
int Chest_Vfunc0C(void);
int Chest_Update(Chest *chest);
int Chest_Start(Chest *chest);
Chest *Chest_Delete(Chest *chest);
Chest *Chest_Destroy(Chest *chest);
Chest *Chest_Construct(Chest *chest);
void Chest_Create(void);
Chest *ChestReceiver_Delete(void *receiver);
Chest *ChestReceiver_Destroy(void *receiver);

#endif
