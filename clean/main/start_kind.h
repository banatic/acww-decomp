/* How the game is started from the title's menu (overlay 147 sets it, StartKind_Apply acts on
 * it when the game starts; data_021f3c30, 0 while none is set):
 *
 *   START_KIND_NEW_TOWN    the state block is set up anew and a player is made in it;
 *   START_KIND_NEW_PLAYER  a player is made in the town as it is;
 *   START_KIND_PLAYER_0    session player 0 gets record 0 and func_0203d394 runs;
 *   START_KIND_UNCHANGED   nothing is done.
 *
 * The activity's process (func_020a4454) picks START_KIND_PLAYER_0 when flag 0x12 of the state
 * block is set and START_KIND_UNCHANGED otherwise. Overlays 4, 51, 54 and 68 and the start menu
 * ask for the first two (a talk of "sp_etc_sequence4" in place of "sp_etc_sequence2"). */
#ifndef CLEAN_MAIN_START_KIND_H
#define CLEAN_MAIN_START_KIND_H

#include "types.h"

enum StartKind {
    START_KIND_NONE = 0,
    START_KIND_NEW_TOWN = 1,
    START_KIND_NEW_PLAYER = 2,
    START_KIND_PLAYER_0 = 3,
    START_KIND_UNCHANGED = 4,
};

void StartKind_Clear(void);
int StartKind_IsUnchanged(void);
int StartKind_IsPlayer0(void);
int StartKind_IsNewPlayer(void);
int StartKind_IsNewTown(void);
int StartKind_IsSet(void);
void StartKind_SetUnchanged(void);
void StartKind_SetPlayer0(void);
void StartKind_SetNewPlayer(void);
void StartKind_SetNewTown(void);
void StartKind_Apply(void);

#endif
