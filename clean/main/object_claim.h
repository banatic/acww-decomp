/* Objects claimed through the session (data_020ccf94), and the events about them sent to the
 * other systems: message 23 of the session (session_message.c hands its payload and the
 * sender's slot to ObjectClaim_Dispatch).
 *
 * The session's host (the system in slot 0) keeps, for each slot, the id of the object
 * (scene_object_base.h) that slot's player has claimed (OSiHeapInfo, four words; 0: none). An
 * object may be claimed only while no slot holds it, the slot holds nothing else and it is not
 * the id in data_021c72d4. The host claims and lets go in its own table; another system asks
 * the host with a message and waits for the answer, which the host sends back to it:
 *
 *   payload byte 0   what follows                      sent by
 *   0  claim         the id (4 bytes)                  ObjectClaim_Claim, to slot 0
 *   1  yes, 2  no    nothing                           ObjectClaim_SendAnswer, to the asker
 *   3  let go        nothing                           ObjectClaim_Release, to slot 0
 *   4  an act        the id, then the act              ObjectClaim_SendAct, to the scene
 *   5  an event      the id, then the code             ObjectClaim_SendEvent, to the scene
 *
 * A message's kind (Session_EndMessage) is the slot it is for, or 6 for every system in the
 * scene. The answer this system waits for is kept in the byte data_020dab94
 * (OBJECT_CLAIM_ANSWER_*): 0 while a claim is asked, the message's code (4, 5) while an act or
 * event is out, then 1 or 2 when answered, 6 after a reset. An act (4) is put to the object as
 * one of its questions (scene_object_base.h) about the sender's player: yes tells the object
 * the act starts (code 3) for that player and answers yes. */
#ifndef CLEAN_MAIN_OBJECT_CLAIM_H
#define CLEAN_MAIN_OBJECT_CLAIM_H

#include "types.h"

/* The session message that carries these. */
#define OBJECT_CLAIM_MESSAGE 23

/* Payload byte 0. */
enum ObjectClaimCode {
    OBJECT_CLAIM_CLAIM = 0,
    OBJECT_CLAIM_YES = 1,
    OBJECT_CLAIM_NO = 2,
    OBJECT_CLAIM_RELEASE = 3,
    OBJECT_CLAIM_ACT = 4,
    OBJECT_CLAIM_EVENT = 5,
};

/* data_020dab94 after ObjectClaim_Reset. */
#define OBJECT_CLAIM_ANSWER_NONE 6

/* The slot of the session's host, which keeps the claims. */
#define OBJECT_CLAIM_HOST_SLOT 0
/* A message's kind for every system in the scene. */
#define OBJECT_CLAIM_TO_SCENE 6

/* ObjectClaim_Mode */
#define OBJECT_CLAIM_SHARED 1  /* decided by the other systems */
#define OBJECT_CLAIM_DECIDED 2 /* decided here */

/* ObjectClaim_Ask */
#define OBJECT_CLAIM_ASK_REFUSED 0
#define OBJECT_CLAIM_ASK_ASKED 1
#define OBJECT_CLAIM_ASK_GIVEN 2

void ObjectClaim_HandleObjectMessage(const u8 *payload, int slot);
void ObjectClaim_HandleRelease(const u8 *payload, int slot);
void ObjectClaim_HandleAnswer(const u8 *payload);
void ObjectClaim_HandleClaim(const u8 *payload, int slot);
void ObjectClaim_SendObjectMessage(u32 id, u8 value, u8 code);
void ObjectClaim_SendEvent(int id, int code);
void ObjectClaim_SendAct(int id, int act);
int ObjectClaim_Mode(void);
void ObjectClaim_Release(void);
void ObjectClaim_Claim(u32 id);
int ObjectClaim_Ask(int id);
int ObjectClaim_Clear(int slot);
int ObjectClaim_IsFree(int slot, int id);
void ObjectClaim_SendAnswer(int code, int slot);
void ObjectClaim_Reset(void);
void ObjectClaim_Dispatch(const u8 *payload, int slot);

#endif
