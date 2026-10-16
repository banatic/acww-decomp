/* The topics a town villager's talk scene (VillagerTalk, villager_talk.h) can talk about,
 * and the line function that picks one (VillagerTalkTopics_Line).
 *
 * Each topic is a member function of the scene that, when it applies, draws a line for the
 * villager's personality into the talk's text at 0x104 and message at 0x122 and says 1; a
 * topic that says 0 does not apply. The line function first fills the talk's slots 4 to 6,
 * tries two topics of its own (the town event the villager scene started in, and the number
 * of the current player's talks), then draws among the 14 topics of a table at random by the
 * weights of data_020c8ea4, a topic that does not apply taking no further part, until one
 * applies; topic 4 (func_02022454) is drawn once all are out.
 *
 * The topic about other players (VillagerTalkTopics_SayOtherPlayer) picks one of the
 * villager's memories of a player through one of ten member functions, each of which draws
 * a memory at random among those that pass its test (VillagerTalkTopics_PickRandom) and puts
 * what the line names into the talk's slots. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_TOPICS_H
#define CLEAN_MAIN_VILLAGER_TALK_TOPICS_H

#include "calendar.h"
#include "types.h"
#include "villager_memories.h"
#include "villager_talk.h"

#define VILLAGER_TALK_TOPICS_COUNT 14

/* A test of a memory: 1 when it passes. */
typedef int (*VillagerTalkTopicsTest)(u8 *villager, VillagerMemory *memory);

void VillagerTalkTopics_Line(VillagerTalk *talk, VillagerTalkLine *out);
int VillagerTalkTopics_FillSlots(VillagerTalk *talk);
int VillagerTalkTopics_Draw(VillagerTalk *talk, const u8 *weights, int count);
int VillagerTalkTopics_SayEvent10(VillagerTalk *talk);
int VillagerTalkTopics_SayPlayerTalks(VillagerTalk *talk);
int VillagerTalkTopics_SayConstellation(VillagerTalk *talk);
int VillagerTalkTopics_SayDayEvent(VillagerTalk *talk);
int VillagerTalkTopics_SayDated(VillagerTalk *talk);
u32 VillagerTalkTopics_DatedLine12(VillagerTalk *talk, u8 *per_group, int *group, u8 *range, const DateTime *now);
int VillagerTalkTopics_DatedLine14(VillagerTalk *talk, u8 *per_group, int *group, u8 *range, const DateTime *now);
int VillagerTalkTopics_SayOtherPlayer(VillagerTalk *talk);
u32 VillagerTalkTopics_PickWithItem(VillagerTalk *talk, VillagerMemory **list, u32 count);
int VillagerTalkTopics_HasItem(u8 *villager, VillagerMemory *memory);
int VillagerTalkTopics_PickAny(VillagerTalk *talk, VillagerMemory **list, int count);
int VillagerTalkTopics_Any(void);
int VillagerTalkTopics_PickWithValues(VillagerTalk *talk, VillagerMemory **list, int count);
int VillagerTalkTopics_HasValues(u8 *villager, VillagerMemory *memory);
int VillagerTalkTopics_PickLetterOfResident(VillagerTalk *talk, VillagerMemory **list, int count);
int VillagerTalkTopics_HoldsLetterOfResident(u8 *villager, VillagerMemory *memory);
void *VillagerTalkTopics_PickWithText2A(VillagerTalk *talk, VillagerMemory **list, int count);
int VillagerTalkTopics_HasText2A(u8 *villager, VillagerMemory *memory);
void *VillagerTalkTopics_PickLetterOfTown(VillagerTalk *talk, VillagerMemory **list, int count);
int VillagerTalkTopics_HoldsLetterOfTown(u8 *villager, VillagerMemory *memory);
int VillagerTalkTopics_HoldsLetter(u8 *villager, VillagerMemory *memory);
int VillagerTalkTopics_PickUnfond(VillagerTalk *talk, VillagerMemory **list, int count);
int VillagerTalkTopics_IsUnfond(int unused, VillagerMemory *memory);
int VillagerTalkTopics_PickFond(VillagerTalk *talk, VillagerMemory **list, int count);
int VillagerTalkTopics_IsFond(int unused, VillagerMemory *memory);
int VillagerTalkTopics_DaysSinceMet(VillagerMemory *memory);
int VillagerTalkTopics_PickRandom(u8 *villager, VillagerMemory **list, int count, VillagerTalkTopicsTest test);
int VillagerTalkTopics_SayGiftItem(VillagerTalk *talk);
int VillagerTalkTopics_SayByTown(VillagerTalk *talk);
int VillagerTalkTopics_SayByAcre(VillagerTalk *talk);
int VillagerTalkTopics_SayPair(VillagerTalk *talk);

#endif
