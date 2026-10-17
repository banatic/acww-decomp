/* What a villager out walking in the town (outdoor_villager.h) reads and keeps in the game's
 * records through its town record (its vtable slot 0x64): the state entry of the villager
 * (main's villager_state.h) with its tally, byte 0x18, its kind of the moment (byte 0x1c) and
 * the item it holds; its memory of this console's player; and, during the fishing tourney and
 * the insect contest (the town events 3 and 4 when it was made), the record of the event's
 * winner (data_021f3aa4, main's event_winner.h), which a villager in the contest may beat once
 * a minute with a fish or an insect of its own drawing. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_RECORDS_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_RECORDS_H

#include "main/calendar.h"
#include "main/villager_memories.h"
#include "main/villager_state.h"
#include "types.h"

VillagerTally *OutdoorVillagerRecords_Tally(u8 *villager);
u8 OutdoorVillagerRecords_Byte18(u8 *villager);
void OutdoorVillagerRecords_EachMinute(u8 *villager);
void OutdoorVillagerRecords_CatchFish(u8 *villager, u8 *now);
void OutdoorVillagerRecords_CatchInsect(u8 *villager, u8 *now);
int OutdoorVillagerRecords_InContest(u8 *villager);
void OutdoorVillagerRecords_RefreshItem(u8 *villager);
void OutdoorVillagerRecords_CheckKind(u8 *villager);
void OutdoorVillagerRecords_RedrawKind(u8 *villager);
VillagerMemory *OutdoorVillagerRecords_MemoryOfPlayer(u8 *villager);

#endif
