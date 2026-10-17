/* The gatekeeper's own states 0 to 0x11 (gatekeeper.h): a table of C++ pointers to member
 * functions at data_ov048_022647a8, an entry and a run for each state (filled at start-up by
 * __sinit_ov048_022639b0). Gatekeeper_SetState enters a state (its entry, when it has one, must
 * agree) and Gatekeeper_UpdateState runs it each frame (vtable slot 0x68).
 *
 * - 0: asks for a talk (an event of kind 6) each frame: the player is back from another town.
 * - 1: stands and calls the player once near (Gatekeeper_CallPlayer); 2: turns to the one it
 *   talks with and talks; 3: nothing; 4: turns back to the angle it started with, then 1.
 * - 5: walks the player to (16.0, 0, 17.5), then the event ends; 6: opens the town to visitors
 *   (hosts the Wi-Fi Connection's game or starts a local session as its parent); 7: closes it.
 * - 8 and 0xa step through the same six steps (Gatekeeper.setup_step): the player walks through
 *   the gate while the two gatekeepers (this one and the other, profile 0x73, overlay 4's
 *   gatekeeper2.h) turn and play animations 0x81 and 0x82; 8 then closes the screen and sets
 *   the activity's flag 0x3c08, 0xa takes the scene's exit 0.
 * - 9 and 0xb step through four steps: a player arrives and is named in line 0x67 (9, the
 *   player of the activity's slot 0x3c1c) or line 0x7b (0xb, the player the link serves), and
 *   the scene's exit 1 is taken (Gatekeeper_RunState9, Gatekeeper_RunStateB).
 * - 0xc and 0xd leave for scene 0xc or 0x2e once talk 0 is gone, after a connection as a local
 *   child (GatekeeperTalk_WaitStatus0 and GatekeeperTalk_WaitStatus1); 0xe leaves for scene 0x2e.
 * - 0xf and 0x11 wait for the shared slots of the scene object (scene_share.h) to settle after
 *   an act ended or an event for another system; 0x10 does nothing. */
#ifndef CLEAN_OV048_GATEKEEPER_STATES_H
#define CLEAN_OV048_GATEKEEPER_STATES_H

#include "gatekeeper.h"
#include "types.h"

int Gatekeeper_RunState10(void);
int Gatekeeper_EnterState10(void);
int Gatekeeper_RunState11(Gatekeeper *self);
int Gatekeeper_EnterState11(void);
int Gatekeeper_RunStateF(Gatekeeper *self);
int Gatekeeper_EnterStateF(void);
int Gatekeeper_RunStateE(Gatekeeper *self);
int Gatekeeper_EnterStateE(void);
int Gatekeeper_RunStateD(Gatekeeper *self);
int Gatekeeper_EnterStateD(void);
int Gatekeeper_RunStateC(Gatekeeper *self);
int Gatekeeper_EnterStateC(void);
int Gatekeeper_RunStateB(Gatekeeper *self);
int Gatekeeper_EnterStateB(Gatekeeper *self);
int Gatekeeper_StateBTakeExit(void);
int Gatekeeper_StateBClearRecord(void);
int Gatekeeper_StateBMovePlayer(void);
int Gatekeeper_StateBSayName(Gatekeeper *self);
void Gatekeeper_RunStateA(Gatekeeper *self);
void Gatekeeper_EnterStateA(Gatekeeper *self);
int Gatekeeper_RunState9(Gatekeeper *self);
int Gatekeeper_EnterState9(Gatekeeper *self);
int Gatekeeper_State9TakeExit(void);
int Gatekeeper_State9CloseTalk(void);
int Gatekeeper_State9SayName(Gatekeeper *self);
int Gatekeeper_State9WalkIn(void);
int Gatekeeper_RunState8(Gatekeeper *self);
int Gatekeeper_EnterState8(Gatekeeper *self);
int Gatekeeper_PassLeave(Gatekeeper *self);
int Gatekeeper_PassAnimate(Gatekeeper *self);
int Gatekeeper_PassWalkThrough(Gatekeeper *self);
int Gatekeeper_PassOtherTurns(Gatekeeper *self);
int Gatekeeper_PassTurn(Gatekeeper *self);
int Gatekeeper_PassWalkToGate(Gatekeeper *self);
int Gatekeeper_RunState7(Gatekeeper *self);
int Gatekeeper_EnterState7(Gatekeeper *self);
int Gatekeeper_RunState6(Gatekeeper *self);
int Gatekeeper_EnterState6(Gatekeeper *self);
int Gatekeeper_RunState5(Gatekeeper *self);
int Gatekeeper_EnterState5(Gatekeeper *self);
int Gatekeeper_RunState4(Gatekeeper *self);
int Gatekeeper_EnterState4(Gatekeeper *self);
int Gatekeeper_RunState3(void);
int Gatekeeper_EnterState3(void);
int Gatekeeper_RunState2(Gatekeeper *self);
int Gatekeeper_EnterState2(Gatekeeper *self);
int Gatekeeper_RunState1(Gatekeeper *self);
int Gatekeeper_EnterState1(Gatekeeper *self);
int Gatekeeper_RunState0(Gatekeeper *self);
int Gatekeeper_EnterState0(void);
void Gatekeeper_InitTables(void);

#endif
