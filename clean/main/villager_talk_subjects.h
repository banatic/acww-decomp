/* More topics of a town villager's talk scene (VillagerTalk, villager_talk.h): members that,
 * when they apply, draw a line for the villager's personality into the talk's text at 0x104
 * and message at 0x122 and say 1, as the topics of villager_talk_topics.h do. Some are in
 * VillagerTalkTopics_Line's table; others are asked about through two tables of eight members
 * (by the kind in the villager's state entry, VillagerTalkSubjects_SayByStateKind, and by the
 * villager's mode, VillagerTalkSubjects_SayByMode).
 *
 * Many are about what the villager holds (func_0202e118 gives the item of its state entry,
 * 0xfff1 for none): nothing or one of the items 0x1380-0x139f, the item 0x1369, 0x1378, or
 * 0x1374 and 0x1376 (with which it talks of a fish, 0x12e8-0x131f, or an insect,
 * 0x12b0-0x12e7, picked for the date). Two talk of a creature that may be caught at this date
 * (the creature tables of creature_table.h). */
#ifndef CLEAN_MAIN_VILLAGER_TALK_SUBJECTS_H
#define CLEAN_MAIN_VILLAGER_TALK_SUBJECTS_H

#include "creature_table.h"
#include "types.h"
#include "villager_talk.h"

/* A text set of the talk lines: its texts and a count (a number of lines, or of lines per
 * group). */
typedef struct VillagerTalkSubjectsTexts {
    u32 texts;
    u8 count;
} VillagerTalkSubjectsTexts;

int VillagerTalkSubjects_SayStateFlags(VillagerTalk *talk);
int VillagerTalkSubjects_SayLast(VillagerTalk *talk);
int VillagerTalkSubjects_SayDesignClothes(VillagerTalk *talk);
int VillagerTalkSubjects_Say8c80(VillagerTalk *talk);
int VillagerTalkSubjects_SayByStateKind(VillagerTalk *talk);
int VillagerTalkSubjects_SayHolding8af8(VillagerTalk *talk);
int VillagerTalkSubjects_SayHoldingOnAcre(VillagerTalk *talk);
int VillagerTalkSubjects_SayHolding1378(VillagerTalk *talk);
int VillagerTalkSubjects_SayHolding8a68(VillagerTalk *talk);
int VillagerTalkSubjects_SayHoldingNamed(VillagerTalk *talk);
int VillagerTalkSubjects_SayHolding1369(VillagerTalk *talk);
int VillagerTalkSubjects_SayFishWith1374(VillagerTalk *talk);
int VillagerTalkSubjects_SayInsectWith1376(VillagerTalk *talk);
void VillagerTalkSubjects_SayForMode(VillagerTalk *talk, int mode, const VillagerTalkSubjectsTexts *texts);
int VillagerTalkSubjects_SayByMode(VillagerTalk *talk);
int VillagerTalkSubjects_Say8d70(VillagerTalk *talk);
int VillagerTalkSubjects_Say8a08(VillagerTalk *talk);
int VillagerTalkSubjects_Say8a10(VillagerTalk *talk);
int VillagerTalkSubjects_Say8b70(VillagerTalk *talk);
int VillagerTalkSubjects_Say8db0(VillagerTalk *talk);
int VillagerTalkSubjects_Say8dc0(VillagerTalk *talk);
int VillagerTalkSubjects_SayCatchA(VillagerTalk *talk);
int VillagerTalkSubjects_CatchGroupA(unsigned int kind);
void VillagerTalkSubjects_PutCatchKind(VillagerTalk *talk, int value, u16 *item, int choice, CreatureTablePeriod lists,
                                       int slot);
int VillagerTalkSubjects_SayCatchB(VillagerTalk *talk);

#endif
