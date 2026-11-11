/* The behavior member of a villager out walking in the town (0x8b8 in the villager,
 * outdoor_villager.h): which of its 24 behaviors runs, the one saved to resume, the counters
 * its behaviors share, and behavior 7's call of this console's player.
 *
 * A behavior is a row of the table data_ov068_02278484 (filled when the overlay starts): a
 * start and an update, both member functions of the behavior member called with the villager.
 * Starting one (OutdoorVillagerBehavior_Start) clears its step and runs its start; each frame
 * (OutdoorVillagerBehavior_Tick, from the villager's frame) runs the update of the one
 * running, then counts down the counters below. The counters the walks read while the villager
 * is busy with an action (an event, a talk) are held still.
 *
 * Besides outdoor_villager.h's fields, the member holds (by place):
 * - 0x00 the box of four words around the camera's target within which the villager counts as
 *   on screen (outdoor_villager_walks.h, OutdoorVillagerWalksBox);
 * - 0x28 a word cleared when it is made, 0x2c a countdown (behavior 17's), 0x34 and 0x36 the
 *   held item's check and hold (outdoor_villager_walks.h), 0x3c its walker (main's
 *   path_walker.h);
 * - 0xd8 to 0xde the walks' countdowns (outdoor_villager_walks.h), 0xe4 a word cleared when it
 *   is made, 0xf8 the frames to the next raise of the record's byte 0x1e. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_BEHAVIOR_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_BEHAVIOR_H

#include "ov004/member_pointer.h"
#include "outdoor_villager.h"
#include "types.h"

/* The behaviors there are, and the value of `resume` for none. */
#define OUTDOOR_VILLAGER_BEHAVIORS 24

/* A row of the table data_ov068_02278484. */
typedef struct OutdoorVillagerBehaviorRow {
    MemberPointer start;  /* called with the villager when the behavior starts */
    MemberPointer update; /* called with the villager each frame while it runs */
} OutdoorVillagerBehaviorRow;

int OutdoorVillagerBehavior_IsIdle(OutdoorVillagerBehavior *self);
int OutdoorVillagerBehavior_CallsPlayer(OutdoorVillagerBehavior *self, u8 *villager);
int OutdoorVillagerBehavior_Resume(OutdoorVillagerBehavior *self, u8 *villager);
void OutdoorVillagerBehavior_ClearResume(OutdoorVillagerBehavior *self);
void OutdoorVillagerBehavior_SaveResume(OutdoorVillagerBehavior *self);
void OutdoorVillagerBehavior_SetResume(OutdoorVillagerBehavior *self, int index);
void OutdoorVillagerBehavior_Start(OutdoorVillagerBehavior *self, u8 *villager, int index);
void OutdoorVillagerBehavior_Tick(OutdoorVillagerBehavior *self, u8 *villager);
OutdoorVillagerBehavior *OutdoorVillagerBehavior_Destruct(OutdoorVillagerBehavior *self);
OutdoorVillagerBehavior *OutdoorVillagerBehavior_Construct(OutdoorVillagerBehavior *self);

#endif
