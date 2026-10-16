/* The greetings of a town villager's talk scene (VillagerTalk, villager_talk.h): the line the
 * villager opens a talk with (VillagerTalkGreeting_Line, the text sets "ai_*"), the checks it
 * asks in turn (VillagerTalkReplies_LineForSituation of villager_talk_replies.h asks most of
 * them too), the line of a talk of two villagers with the player ("3p_*") and the helpers that
 * put words into the talk's slots.
 *
 * VillagerTalkGreeting_SinceLastTalk sorts the player by the villager's memory of them:
 *   0  no memory (a first meeting: "ai_first", "ai_nfirst" or "ai_mfirst" by how the villager
 *      came to the town)
 *   1  met on an earlier day (or the memory's date is ahead of now), not greeted yet today
 *   2  met today, or greeted already (flag 2 of the villager's state entry)
 *   3  7 days or more ago ("ai_7days"), 4  30 days or more ("ai_30days")
 *   5  the memory's town is not this town ("ai_foreign")
 *   6  the current player is of another town than the memory's player ("ai_mfirst")
 * A player of another town is only sorted into 1 and 2.
 *
 * The other greetings, in the order VillagerTalkGreeting_Line asks for them: a fall
 * ("ai_fall", never), running ("ai_run"), fleas ("ai_flea"), bee stings ("ai_bee", once: flag 0
 * of the state entry), a poisonous insect near ("ai_poison", the insects 0x36 and 0x37 within
 * 0x6000), the villager's mood (byte 0x18 of its state entry: 2 "ai_anger", 3 "ai_sad", 4
 * "ai_tire"), a password of the fox's shop, a fortune (a lucky item), being in a shop, indoors,
 * the weather (rain, snow; "ai_today" otherwise), the villager's craze ("ai_boom"), its
 * persistence ("ai_persis") and its joy ("ai_joy"). */
#ifndef CLEAN_MAIN_VILLAGER_TALK_GREETING_H
#define CLEAN_MAIN_VILLAGER_TALK_GREETING_H

#include "autoload_2/vector.h"
#include "types.h"
#include "villager_state.h"
#include "villager_talk.h"

/* A text set of the talk lines: its texts and a count (of lines per group). */
typedef struct VillagerTalkGreetingTexts {
    u32 texts;
    u8 count;
} VillagerTalkGreetingTexts;

void VillagerTalkGreeting_LineThree(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkGreeting_SayByKnownObject(VillagerTalk *talk);
void VillagerTalkGreeting_NoteMemory(VillagerTalk *talk, void *unused);
void VillagerTalkGreeting_FillSlots(VillagerTalk *talk);
void VillagerTalkGreeting_PutByte29(VillagerTalk *talk, int slot, u8 *villager);
int VillagerTalkGreeting_PutRandomWord(VillagerTalk *talk, int slot, int archive);
void VillagerTalkGreeting_Line(VillagerTalk *talk, VillagerTalkLine *out);
int VillagerTalkGreeting_IsTired(VillagerTalk *talk, int mood);
int VillagerTalkGreeting_IsSad(VillagerTalk *talk, int mood);
int VillagerTalkGreeting_IsAngry(VillagerTalk *talk, int mood);
const VillagerTalkGreetingTexts *VillagerTalkGreeting_BeeTexts(VillagerTalk *talk, int *group, VillagerState *entry);
int VillagerTalkGreeting_IsStung(VillagerTalk *talk, VillagerState *entry);
int VillagerTalkGreeting_HasFlea(VillagerTalk *talk);
const VillagerTalkGreetingTexts *VillagerTalkGreeting_PoisonTexts(VillagerTalk *talk, int kind);
int VillagerTalkGreeting_FindPoisonous(VillagerTalk *talk, int *kind, const Vec3 *position);
const VillagerTalkGreetingTexts *VillagerTalkGreeting_ForeignTexts(VillagerTalk *talk);
int VillagerTalkGreeting_IsForeign(VillagerTalk *talk, int since);
int VillagerTalkGreeting_FirstTexts(VillagerTalk *talk, int *group, u8 *villager);
int VillagerTalkGreeting_IsFirst(VillagerTalk *talk, int since);
int VillagerTalkGreeting_IsRun(VillagerTalk *talk);
int VillagerTalkGreeting_IsFallen(VillagerTalk *talk);
int VillagerTalkGreeting_SinceLastTalk(VillagerTalk *talk, int *days);
int VillagerTalkGreeting_FindNearInsect(Vec3 *at, const s8 *kinds, int count, const Vec3 *position, fx32 distance);
int VillagerTalkGreeting_FindInList(int value, const s8 *list, int count);

#endif
