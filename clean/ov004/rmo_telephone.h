/* A room object of the RMO family (rmo_object.h; vtable 0x022558f8, receiver part 0x02255974
 * at 0x290, 0x644 bytes) built from /roomObj/obj_telephone, that talks with the message file
 * "sp_etc_sequence1". Not the room objects' telephone of telephone.h. Only one exists at a
 * time: data_ov004_022588c8 points to it from its start to its release.
 *
 * Its state (RmoTelephone.state, 0 to 14) has an entry and an update, as pairs of member
 * pointers in the table data_ov004_022588d8 (filled by __sinit_ov004_0224ebd8); one of them may
 * be none. RmoTelephone_EnterState enters a state (running its entry, then setting it whatever the
 * entry did) and RmoTelephone_Update runs the state's update each frame. The states these
 * functions belong to:
 *
 * - 10: its talk started over its receiver (message 0xe); on once the talk has opened (11);
 * - 11 and 12: once the talk has closed, its receiver let go and on to state 7;
 * - 13: once the talk is gone, the screen of group 0x30 opened and on to 14;
 * - 14: once that screen has closed, the talk shows message 0x10 or 0x18, then state 12 (in
 *   scene 6) or 4.
 *
 * Other overlay 4 code restarts the body's first joint animation from its end, forwards or
 * backwards, or from its start, and asks for state 10. */
#ifndef CLEAN_OV004_RMO_TELEPHONE_H
#define CLEAN_OV004_RMO_TELEPHONE_H

#include "main/collision_box.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "rmo_object.h"
#include "types.h"

typedef struct RmoTelephone {
    RmoObject base;                                 /* 0x000 */
    TalkReceiver receiver;                          /* 0x290: vtable data_ov004_02255974 */
    CollisionBox box;                               /* 0x2d8 */
    TouchPickFace pick_faces[TOUCH_PICK_BOX_FACES]; /* 0x374 */
    u8 unk_61c[0x1c];                               /* 0x61c: built by TouchPickSphere_Construct */
    s32 state;                                      /* 0x638: 0 to 14 */
    u8 talking;                                     /* 0x63c: set while it holds the talk */
    u8 unk_63d[3];                                  /* 0x63d */
    s32 unk_640;                                    /* 0x640 */
} RmoTelephone;

void RmoTelephone_PlayFromEnd(void);
void RmoTelephone_PlayBackFromEnd(void);
void RmoTelephone_PlayFromStart(void);
int RmoTelephone_EnterState10Current(void);
int RmoTelephone_IsTalking(void);
void RmoTelephone_StartTalk(RmoTelephone *self, const char *name, u8 message);
void RmoTelephone_UpdateState14(RmoTelephone *self);
void RmoTelephone_EnterState14(void);
void RmoTelephone_UpdateState13(RmoTelephone *self);
void RmoTelephone_EnterState13(void);
void RmoTelephone_UpdateState12(RmoTelephone *self);
void RmoTelephone_EnterState12(void);
void RmoTelephone_UpdateState11(RmoTelephone *self);
void RmoTelephone_EnterState11(void);
void RmoTelephone_UpdateState10(RmoTelephone *self);

/* The rest of the class. It stands at a fixed point (data_ov004_022478d0, also what vtable
 * slot 0x50 answers) in a box of touch-pick faces (kind 13) 0x2000 on each side; its collision
 * box is built and taken down but never put on the field here. Its other states:
 *
 * - 0: waits; touched by the pen while this system's player may act on it (near the point and
 *   facing it), it asks the event queue for an event of kind 6 about it;
 * - 1: the player's action 0x7d and sound 0x4d4; once the body's animation has run out, 2;
 * - 2: the talk started over its receiver: message 0xe, or 0x1d in a linked session; once the
 *   talk has opened, 3;
 * - 3 and 4: once the talk has closed, 5;
 * - 5: the player's action 0x7f and sound 0x4d5; once the body's animation has run out, its
 *   receiver handed back, the event finished and 6;
 * - 6: nothing;
 * - 7: with the screen shown, the pen picking a face of kind 13 enters state 10;
 * - 8: holds the talk; with the screen shown, 9;
 * - 9: the talk shows message 0x22; once it has closed, 7.
 *
 * The scene's events (vtable slot 0x4c): 0 and 1 enter state 1, 8 enters state 0. Started in
 * scene 6 it waits in state 7, or in state 8 the first time (flag 0 of the state block, set
 * then); elsewhere in state 0.
 *
 * Its talk's messages change the player's options (main/player_options.h): message 0xe (and
 * 0x1f) offers a list of answers whose pick leads to the next message; messages 0x14, 0x17,
 * 0x1a, 0x1b and 0x11 set the options' flag, flags 0x13 and 0x14 of the state block, the sound
 * and the setting, and messages 0x2a to 0x2c put the setting back on their second answer. */

/* A list of answers the talk offers (RmoTelephone_OfferAnswers). */
typedef struct RmoTelephoneAnswers {
    const u8 *messages;
    u8 count;
} RmoTelephoneAnswers;

int RmoTelephone_EnterState10(RmoTelephone *self);
void RmoTelephone_UpdateState9(RmoTelephone *self);
void RmoTelephone_EnterState9(RmoTelephone *self);
void RmoTelephone_UpdateState8(RmoTelephone *self);
RmoTelephone *RmoTelephone_EnterState8(RmoTelephone *self);
void RmoTelephone_UpdateState7(RmoTelephone *self);
void RmoTelephone_EnterState7(void);
void RmoTelephone_UpdateState6(void);
void RmoTelephone_EnterState6(void);
void RmoTelephone_UpdateState5(RmoTelephone *self);
int RmoTelephone_EnterState5(RmoTelephone *self);
void RmoTelephone_UpdateState4(RmoTelephone *self);
void RmoTelephone_EnterState4(void);
void RmoTelephone_UpdateState3(RmoTelephone *self);
void RmoTelephone_EnterState3(void);
void RmoTelephone_UpdateState2(RmoTelephone *self);
void RmoTelephone_EnterState2(RmoTelephone *self);
void RmoTelephone_UpdateState1(RmoTelephone *self);
int RmoTelephone_EnterState1(RmoTelephone *self);
void RmoTelephone_UpdateState0(RmoTelephone *self);
void RmoTelephone_EnterState0(void);
void RmoTelephone_EnterState(RmoTelephone *self, int state);
void RmoTelephone_OnAnswer(RmoTelephone *self);
void RmoTelephone_OfferAnswers(RmoTelephone *self, const RmoTelephoneAnswers *answers, int cancel);
void RmoTelephone_AfterMessage(RmoTelephone *self);
void RmoTelephone_OnMessageBegun(RmoTelephone *self);
const Vec3 *RmoTelephone_Position(void);
void RmoTelephone_OnSceneEvent(RmoTelephone *self, int event);
int RmoTelephone_MayAct(RmoTelephone *self, Actor *other);
int RmoTelephone_Release(RmoTelephone *self);
int RmoTelephone_Draw(RmoTelephone *self);
int RmoTelephone_Update(RmoTelephone *self);
int RmoTelephone_Start(RmoTelephone *self);
RmoTelephone *RmoTelephone_Delete(RmoTelephone *self);
RmoTelephone *RmoTelephone_Destruct(RmoTelephone *self);
RmoTelephone *RmoTelephone_Construct(RmoTelephone *self);
u32 RmoTelephone_Current(void);
void RmoTelephone_Create(void);
RmoTelephone *RmoTelephoneReceiver_Delete(void *receiver);
void RmoTelephoneReceiver_OnAnswer(void *receiver);
void RmoTelephoneReceiver_AfterMessage(void *receiver);
void RmoTelephoneReceiver_OnMessageBegun(void *receiver);
RmoTelephone *RmoTelephoneReceiver_Destruct(void *receiver);

#endif
