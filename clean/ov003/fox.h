/* The fox of overlay 3 (class Obj_ov003_02238630, vtable 0x02238630, receiver part 0x022386f4,
 * 0x2bc bytes), a special character whose message receiver is named "sp_npc_fox"; Crazy Redd
 * is the game's fox, but nothing here names him. It is derived from overlay 9's scene actor
 * (Obj_ov009_022658dc), which runs the rest; its own machine (the word at 0x2b4, ten states)
 * runs through tables of member pointers (ov004/member_pointer.h):
 *
 *   0 idle:        scene event 0 or 1 moves to state 1, event 8 back here. While bit 2 of the
 *                  byte at 0x235 is set, func_0203e0a8 runs on it each frame.
 *   1 visit:       entering it asks main for the character's visit record (func_020b248c on its
 *                  code at 0x136); once main has an answer (func_020b2470, nonzero), whether it
 *                  is 2 is kept in bit 1 of the flags and the talk starts (state 2).
 *   2 talk:        entering it takes the receiver and gives it a message: 0x34 when
 *                  Fox_IsAfterSix says no (then clearing bit 0 of the character's flags when
 *                  bit 1 is clear), else 0x31 when bit 1 is set, 0x32 when func_020ae2c4
 *                  agrees, else 0. Once the link opens it moves to state 3.
 *   3 talk end:    once the link closes it hands the receiver back and lets the scene go on.
 *   4 screen ask:  (message 2 ended) once the link's status is 5, opens group 9 in mode 0xe
 *                  with an argument from the town's data (state 5).
 *   5 screen:      once the screen has closed it says message 3 (after func_020ae270) when
 *                  main's byte 0xc4c is 1, else message 4 (and clears bit 0 of the character's
 *                  flags), and ends the talk (state 3).
 *   6 talk close:  (message 3 or 0x32 ended) once the link closes, state 7.
 *   7 leave:       entering it calls func_02095944(0); once func_02096174 agrees it moves to
 *                  state 8 and hands the receiver back.
 *   8 walk:        until func_02096168 agrees (then state 9) it asks the player once to stand
 *                  at the point func_ov009_0226321c gives (player state 0x39, kind 2).
 *   9 gone:        counts the frames func_02096174 agrees on; after 15 (27 for kind 1, 20 for
 *                  kind 2 of func_ov009_02264c90) it registers something of main's table at
 *                  data_021f69d0 where it stood, turned half round, and sets bit 0 of the
 *                  flags. */
#ifndef CLEAN_OV003_FOX_H
#define CLEAN_OV003_FOX_H

#include "types.h"

enum FoxState {
    FOX_IDLE,
    FOX_VISIT,
    FOX_TALK,
    FOX_TALK_END,
    FOX_SCREEN_ASK,
    FOX_SCREEN,
    FOX_TALK_CLOSE,
    FOX_LEAVE,
    FOX_WALK,
    FOX_GONE,
    FOX_STATES
};

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct FoxLink {
    int unk_00;
    int status;    /* 0 once closed; 5 is what FOX_SCREEN_ASK waits for */
    int requested; /* set to 1 when a message is given */
    u8 unk_0C[0x14 - 0x0c];
    int unk_14; /* set to 1 when message 2 ends */
} FoxLink;

/* Bits of Fox.flags. */
#define FOX_FLAG_GONE 0x01    /* set at the end of FOX_GONE */
#define FOX_FLAG_VISIT_2 0x02 /* the visit record said 2 */

typedef struct Fox {
    const void *vtable; /* data_ov003_02238630 */
    u8 unk_04[0xec - 0x04];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov003_022386f4 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10B[0x12c - 0x10b];
    FoxLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x136 - 0x130];
    u16 code; /* the special character's code (0x5000 to 0x5021) */
    u8 unk_138[0x22c - 0x138];
    int unk_22c;
    int unk_230;
    u8 unk_234;
    u8 flags_235; /* bit 2: FOX_IDLE runs func_0203e0a8 */
    u8 flags;     /* FOX_FLAG_* */
    u8 unk_237[0x2b4 - 0x237];
    int state;  /* enum FoxState */
    u16 frames; /* counted in FOX_GONE */
    u8 asked;   /* the player was asked to stand in FOX_WALK */
    u8 hour;    /* the hour Fox_KeepHour saw */
} Fox;

void Fox_UpdateGone(Fox *fox);
int Fox_EnterGone(Fox *fox);
void Fox_UpdateWalk(Fox *fox);
int Fox_EnterWalk(Fox *fox);
void Fox_UpdateLeave(Fox *fox);
int Fox_EnterLeave(Fox *fox);
void Fox_UpdateTalkClose(Fox *fox);
int Fox_EnterTalkClose(Fox *fox);
void Fox_UpdateScreen(Fox *fox);
int Fox_EnterScreen(Fox *fox);
void Fox_UpdateScreenAsk(Fox *fox);
int Fox_EnterScreenAsk(Fox *fox);
void Fox_UpdateTalkEnd(Fox *fox);
int Fox_EnterTalkEnd(Fox *fox);
void Fox_UpdateTalk(Fox *fox);
int Fox_EnterTalk(Fox *fox);
void Fox_UpdateVisit(Fox *fox);
int Fox_EnterVisit(Fox *fox);
void Fox_UpdateIdle(Fox *fox);
int Fox_EnterIdle(Fox *fox);
void Fox_UpdateState(Fox *fox);
int Fox_SetState(Fox *fox, int state);
int Fox_ReceiverSlot6C(Fox *fox);
void Fox_ReceiverSlot18(Fox *fox);
void Fox_OnMessageEnd(Fox *fox);
void Fox_ReceiverSlot10(Fox *fox);
void Fox_OnSceneEvent(Fox *fox, unsigned int event, int arg);
int Fox_IsAfterSix(Fox *fox);
int Fox_Update(Fox *fox);
int Fox_KeepHour(Fox *fox);
Fox *Fox_DestroyAndFree(Fox *fox);
Fox *Fox_Destroy(Fox *fox);
Fox *Fox_Construct(Fox *fox);
void Fox_New(void);
Fox *Fox_ReceiverDestroyAndFree(void *receiver);
int Fox_ReceiverThunk6C(void *receiver);
void Fox_ReceiverThunk18(void *receiver);
void Fox_ReceiverThunk14(void *receiver);
void Fox_ReceiverThunk10(void *receiver);
Fox *Fox_ReceiverDestroy(void *receiver);

#endif
