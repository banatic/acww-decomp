/* Single values kept next to the current activity (activity.h):
 *
 *   a flag (data_021f3c08) the activity clears when it is made (func_020a503c) and overlay 48
 *   sets; a step of the activity (func_020a3ea4) waits for it;
 *   a slot number (data_021f3c1c) set by func_020a5750 and overlay 48 (this system's AID): the
 *   activity marks that slot taken and sends its player record to it (func_020a3abc), and in
 *   scene 0x2f it numbers the player's field actor (SceneBase_PlayerActorId);
 *   the received state block (data_021f3c24) the activity allocates (town_pack.h);
 *   a town record number (data_021f3c34) the title's menu (overlay 147) sets, whose record the
 *   activity reads (func_020a4840). */
#ifndef CLEAN_MAIN_ACTIVITY_VARS_H
#define CLEAN_MAIN_ACTIVITY_VARS_H

#include "state_block.h"
#include "types.h"

void ActivityVars_SetFlag3C08(void);
u8 ActivityVars_Flag3C08(void);
StateBlock *ActivityVars_ReceivedBlock(void);
void ActivityVars_SetSlot3C1C(u32 slot);
u8 ActivityVars_Slot3C1C(void);
void ActivityVars_SetTownPlayer(int number);

#endif
