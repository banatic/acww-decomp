/* Behaviours 17 to 23 of a villager out walking in the town (its behaviour member at 0x8b8,
 * outdoor_villager.h): their starts, their updates and the steps the updates run. 17 and 18:
 * it falls into a pitfall and climbs out; 19 and 20: it is hit with a net, and its talk after
 * the third hit; 21 and 22: the player pushes against it, and its talk after; 23: the player
 * shows it an insect or a fish.
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
 *   is asked for (4, 1, applied), its event finished, it is unpaired, reaction none, and
 *   `call_cooldown` set to 1200. Behaviour 20 first waits while animation 0xec plays.
 * - 21: started when the player has pushed against it for 100 frames (the count at 0xa06,
 *   OutdoorVillagerObject_CountPushed): the villager turns to this console's player under event
 *   kind 6 (EventQueue_RequestKind6), reaction 2, its record's byte 0x1e halved; it stands,
 *   waits 40 frames, then behaviour 0.
 * - 19: started when the byte at 0xa05 is set (this console's player hit it with the net or the
 *   golden net, items 0x1376 and 0x1377): animation 0xeb, or 0xec when facing the player or the
 *   third time while `net_hits_timer` runs (then reaction 1, under event kind 6, turning to the player
 *   and waiting 40 frames); else behaviour 0 with `net_hits_timer` 1200.
 * - 18, climbing out of the pitfall: started after an event while the byte at 0xa04 (stuck in
 *   the pitfall) is set: the byte cleared, the effect at 0xa00 ended, animation 0x12a (0x12b
 *   with items 0x1374 to 0x1377 or 0x1380 to 0x139f held, whose link gets action 18), effect
 *   0x90 at its place (0x91 on ground of attribute 0x13), func_ov003_02220b44 with the place,
 *   and sound 0x7e9: what the player's field actor does in state 0x75
 *   (clean/ov003/field_actor.c). Its update runs one step, as behaviour 17's last.
 * - 17, falling into a pitfall (started when it stands on a marked pitfall seed, item 0x1566,
 *   OutdoorVillagerWalks_OnPitfall): what the player's field actor does in states 0x73 to 0x75
 *   (falling in, stuck, climbing out): animation 0x127 while it steps onto the middle of its
 *   tile, 0x128 with effect 0x8e (0x8f on ground of attribute 0x13) and sound 0x7e8, then 0x129
 *   at speed 0x1400 with effect 0x4c following it for 100 frames, the byte at 0xa04 set
 *   meanwhile, then behaviour 18's leaving. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_ACTS_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_ACTS_H

#include "outdoor_villager.h"
#include "types.h"

int OutdoorVillagerActs_Update23(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Watch23(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Turn23(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Start23(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_UpdatePushedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_IdlePushedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_TalkPushedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_StartPushedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_UpdateNettedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_IdleNettedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_TalkNettedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_WaitNettedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_StartNettedTalk(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_UpdatePushed(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_WaitPushed(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_TurnPushed(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_StartPushed(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_UpdateNetted(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_WaitNetted(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_TurnNetted(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_ReactNetted(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_StartNetted(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_UpdateClimbOut(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_StartClimbOut(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_UpdatePitfall(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerActs_StartPitfall(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_Approach(fx32 *value, fx32 target, fx32 rate, fx32 most, fx32 least);
void OutdoorVillagerActs_StepOntoPitfall(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_EnterPitfall(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_BeginPitfall(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_StayPitfall(OutdoorVillagerBehaviour *self, u8 *villager);
void OutdoorVillagerActs_LeavePitfall(OutdoorVillagerBehaviour *self, u8 *villager);

#endif
