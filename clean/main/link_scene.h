/* The linked systems moving between scenes (the link state's first 0x84 bytes, link_state.h).
 *
 * Each slot has a place (LinkStatePlace): the scene it is in, whether it holds that scene's
 * state (the first system in a scene holds it, and hands it on when it leaves), and whether
 * the host lets it move. The host keeps a queue of moves asked of it (session message 8) and
 * lets one system move at a time (LinkScene_LetNextMove); once that system says it arrived
 * (message 10) its place becomes the new scene, as holder when no other system is there
 * (LinkScene_SettleArrival). Changes to places are sent to every system with message 9.
 *
 * A system that moves steps through LinkScenePhase (LinkScene_Step and the scene processes,
 * scene_process_base.h and scene_change.h): a holder that leaves waits for the other systems of
 * its scene to see it go (message 13 sets their `acked` entry) and sends the scene's state to
 * a successor (bundle 15); a system that is not the holder waits for the holder to let it go
 * (message 17 sets `released`). Before entering a scene, it asks that scene's holder for the
 * scene's state (message 14; the holder answers with bundle 16).
 *
 * None of this happens in the scenes a join or a leave passes through
 * (LinkScene_IsLinkingScene). */
#ifndef CLEAN_MAIN_LINK_SCENE_H
#define CLEAN_MAIN_LINK_SCENE_H

#include "link_state.h"
#include "types.h"

#define LINK_SCENE_NONE 0x3f /* a place's scene while it has none */

/* A system's progress through a move (scene_phase). The phases not named here are moved on by
 * the scene processes: 5 to 6 when the scene's process is deleted, 6 to 7 when the next one's
 * creation begins, 7 to 8 by Session_Update, 11 to 12 by the process between scenes, 12 to 13
 * and 13 to 14 as 5 to 7. */
enum LinkScenePhase {
    LINK_SCENE_WAIT_TURN = 0,      /* the move asked: waiting for the host to let it */
    LINK_SCENE_CHOOSE = 1,         /* a successor chosen, when this system holds its scene */
    LINK_SCENE_WAIT_ACKS = 2,      /* holder: the other systems of the scene awaited */
    LINK_SCENE_SEND_STATE = 3,     /* holder: the scene's state to be sent to the successor */
    LINK_SCENE_WAIT_RELEASE = 4,   /* not the holder: the holder's leave awaited */
    LINK_SCENE_LEAVE = 5,          /* the scene may be left */
    LINK_SCENE_WAIT_SUCCESSOR = 8, /* the successor's taking the scene over awaited */
    LINK_SCENE_FIND_HOLDER = 9,    /* the holder of the scene entered looked for */
    LINK_SCENE_WAIT_STATE = 10,    /* that scene's state awaited */
    LINK_SCENE_ENTER = 11,         /* the scene may be entered */
    LINK_SCENE_ARRIVE = 14,        /* the arrival to be told to the host */
    LINK_SCENE_WAIT_SETTLED = 15,  /* the host's settling of the arrival awaited */
    LINK_SCENE_IDLE = 16,
};

void LinkScene_ReleaseLeavingGuest(LinkState *state);
u32 LinkScene_LeavingGuest(LinkState *state);
void LinkScene_SetLeavingGuest(LinkState *state, u32 slot);
u8 LinkScene_Released(LinkState *state);
void LinkScene_SetReleased(LinkState *state, u8 released);
void LinkScene_CheckStateSent(LinkState *state);
int LinkScene_StateSentTo(LinkState *state);
void LinkScene_SetStateSentTo(LinkState *state, int slot);
int LinkScene_StateAsker(LinkState *state);
void LinkScene_SetStateAsker(LinkState *state, int slot);
int LinkScene_NextHolder(LinkState *state);
void LinkScene_SetNextHolder(LinkState *state, int slot);
void LinkScene_AckLeavingHolder(LinkState *state);
int LinkScene_LeavingHolder(LinkState *state);
void LinkScene_SetLeavingHolder(LinkState *state, int slot);
void LinkScene_ResetAcked(LinkState *state);
int LinkScene_Acked(LinkState *state, int slot);
void LinkScene_SetAcked(LinkState *state, int slot, int acked);
int LinkScene_Successor(LinkState *state);
void LinkScene_SetSuccessor(LinkState *state, int slot);
void LinkScene_Step(LinkState *state);
int LinkScene_Phase(LinkState *state);
void LinkScene_SetPhase(LinkState *state, int phase);
u8 LinkScene_EntersFirst(LinkState *state);
void LinkScene_SetEntersFirst(LinkState *state, u8 first);
void LinkScene_SendChanges(LinkState *state);
void LinkScene_SettleArrival(LinkState *state, int *slot, int *mask);
void LinkScene_ReportArrival(LinkState *state);
void LinkScene_PopMove(LinkState *state);
int LinkScene_NextMover(LinkState *state);
void LinkScene_LetNextMove(LinkState *state, int *slot, int *mask);
void LinkScene_HostStep(LinkState *state);
void LinkScene_Empty6C04(void);
void LinkScene_Update(void);
void LinkScene_Empty6C8C(void);
void LinkScene_Empty6C90(void);
void LinkScene_Empty6C94(void);
int LinkScene_IsLinkingScene(int scene);
void LinkScene_SendAskedState(void);
void LinkScene_SendLeftState(void);
void LinkScene_TakeEnteredState(void);
void LinkScene_TakeLeftState(void);
void LinkScene_GlobalPlace(int slot, u8 *scene, u8 *holder, u8 *moving);
void LinkScene_GlobalSetReleased(int released);
void LinkScene_GlobalSetStateAsker(int slot);
void LinkScene_GlobalSetAcked(int slot, int acked);
int LinkScene_GlobalPhase(void);
void LinkScene_GlobalSetPhase(int phase);

#endif
