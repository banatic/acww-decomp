/* Behaviours 17 to 23 of a villager out walking in the town (its behaviour member at 0x8b8,
 * outdoor_villager.h): their starts, their updates and the steps the updates run.
 *
 * Each behaviour is a start and an update, member functions of the behaviour member called
 * with the villager (the table data_ov068_02278484, filled when the overlay starts). An update
 * runs the step its byte `step` names, from a table of member pointers it fills the first time
 * it runs (MemberTable_InitOnce, ov004/member_pointer.h); a step out of the table does
 * nothing. Updates always answer 0, starts 1.
 *
 * - 23: started (elsewhere in the overlay) while this console's player shows an insect or a
 *   fish within sight, once (`shown`): the villager turns to the player, then plays act 0x1a
 *   until the player no longer shows one, the wait is out and the body animation is back at
 *   its first frame; then it stands and behaviour 0 starts.
 * - 22 and 20: after reaction 2 or 1, told of event 1: it turns to the object of its talk's
 *   motion argument and talks (SceneAction_RequestTurnAndTalk); once the action ends its mood
 *   is asked for (4, 1, applied), its event finished, it is unpaired, reaction none, and the
 *   word at 0xf4 set to 1200. Behaviour 20 first waits while animation 0xec plays.
 * - 21: started when the frame count at 0xa06 reaches 100: the villager turns to this
 *   console's player under event kind 6 (EventQueue_RequestKind6), reaction 2, its record's
 *   byte 0x1e halved; it stands, waits 40 frames, then behaviour 0.
 * - 19: started when the byte at 0xa05 is set: animation 0xeb, or 0xec when facing the player
 *   or the third time while `hold_3a` runs (then reaction 1, under event kind 6, turning to the
 *   player and waiting 40 frames); else behaviour 0 with `hold_3a` 1200.
 * - 18: started after an event while the byte at 0xa04 is set: the byte cleared, the effect
 *   at 0xa00 ended, animation 0x12a (0x12b with items 0x1374 to 0x1377 or 0x1380 to 0x139f held,
 *   whose link gets action 18), effect 0x90 at its place (0x91 on ground of attribute 0x13),
 *   func_ov003_02220b44 with the place, and sound 0x7e9: what the player's field actor does in
 *   state 0x75 (clean/ov003/field_actor.c). Its update runs one step, as behaviour 17's last.
 * - 17: its update's five steps (its start and steps are elsewhere in the overlay). */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_ACTS_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_ACTS_H

#include "outdoor_villager.h"
#include "types.h"

int OutdoorVillagerActs_Update23(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Watch23(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Turn23(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Start23(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Update22(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Idle22(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Talk22(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Start22(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Update20(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Idle20(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Talk20(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Wait20(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Start20(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Update21(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Wait21(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Turn21(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Start21(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Update19(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Wait19(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Turn19(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_React19(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Start19(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Update18(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Start18(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_Update17(OutdoorVillagerBehaviour *self, u8 *villager);

#endif
