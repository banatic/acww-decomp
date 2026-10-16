/* Two processes that keep the field actors of the session's other players in step with what
 * those players report (session_players.h). Each is a base process of 0x50 bytes with nothing
 * of its own; their creation, deletion and drawing do nothing.
 *
 * The spawning process (profile data_020e2f80, vtable data_020e2f90) makes the actors: in the
 * scenes 0xd, 0x2f and 0xe, once, the actor of the player a link activity serves, at a fixed
 * place; elsewhere, while this system's player has its actor, the actor of each other player
 * that reports a state in the current scene (state 2 at its reported point and yaw) or, while
 * flag 0x1b of this system's actor is set, that was last reported in the current scene (in its
 * last reported state, at its last reported place). While that flag is clear, the actor of a
 * player that no longer reports a state in the current scene is deleted.
 *
 * The reporting process (profile data_020e2fd8, vtable data_020e2fe8) keeps what each other
 * player reports as its last place, outside the scenes of the link activities, and has this
 * system's player's point, yaw and state sent to the others. */
#ifndef CLEAN_MAIN_PLAYER_PROCESSES_H
#define CLEAN_MAIN_PLAYER_PROCESSES_H

#include "autoload_2/process.h"
#include "types.h"

int PlayerSpawnProcess_Delete(void);
int PlayerSpawnProcess_Draw(void);
int PlayerSpawnProcess_Execute(void);
int PlayerSpawnProcess_Create(void);
Process *PlayerSpawnProcess_DestructFree(Process *self);
Process *PlayerSpawnProcess_Destruct(Process *self);
Process *PlayerSpawnProcess_Construct(Process *self);
void PlayerSpawnProcess_Spawn(void);

int PlayerReportProcess_Delete(void);
int PlayerReportProcess_Draw(void);
int PlayerReportProcess_Execute(void);
int PlayerReportProcess_Create(void);
Process *PlayerReportProcess_DestructFree(Process *self);
Process *PlayerReportProcess_Destruct(Process *self);

#endif
