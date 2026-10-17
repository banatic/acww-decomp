/* The gatekeeper's own states 9 to 0x11 (gatekeeper.h): a table of C++ pointers to member
 * functions at data_ov048_022647a8, an entry and a run for each state (filled at start-up by
 * __sinit_ov048_022639b0). func_ov048_022635f4 enters a state (its entry, when it has one, must
 * agree) and func_ov048_02263638 runs it each frame.
 *
 * - 9 and 10 (0xa) step through four and six steps of their own (Gatekeeper.setup_step), each
 *   step until it agrees; so does 0xb, whose four steps show line 0x7b with the name of the
 *   player the link serves, walk that player to a point, clear its record and take the scene's
 *   exit 1 (Gatekeeper_RunStateB).
 * - 0xc and 0xd leave for scene 0xc or 0x2e once talk 0 is gone, after a connection as a local
 *   child (GatekeeperTalk_WaitStatus0 and GatekeeperTalk_WaitStatus1); 0xe leaves for scene 0x2e.
 * - 0xf and 0x11 wait for the shared slots of the scene object (scene_share.h) to settle after
 *   an act ended or an event for another system; 0x10 does nothing. */
#ifndef CLEAN_OV048_GATEKEEPER_STATES_H
#define CLEAN_OV048_GATEKEEPER_STATES_H

#include "gatekeeper.h"
#include "types.h"

/* States this code asks for, besides gatekeeper.h's. */
#define GATEKEEPER_STATE_3 3

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

#endif
