/* More members of the town villagers' talk scenes (villager_talk_replies.h). */
#include "villager_talk_replies.h"

#include "clean.h"
#include "npc_id.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_command.h"
#include "session.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_mode_record.h"
#include "villager_object.h"
#include "villager_residents.h"
#include "villager_state.h"
#include "villager_status.h"
#include "villager_town.h"

/* The villager scene object's town record (town_villager.h), or 0, and its position. */
#define VILLAGER_TALK_REPLIES_OBJECT_RECORD 0x830
#define VILLAGER_TALK_REPLIES_OBJECT_POSITION 0x5c

/* A text set of the talk lines: its texts and a count (a number of lines, or of lines per
 * group). */
typedef struct VillagerTalkRepliesTexts {
    u32 texts;
    u8 count;
} VillagerTalkRepliesTexts;

/* The text sets. */
extern const VillagerTalkRepliesTexts data_020c8ab0;
extern const VillagerTalkRepliesTexts data_020c8a98;
extern const VillagerTalkRepliesTexts data_020c8a88;
/* The text sets of the lines that take precedence (VillagerTalkReplies_LineForSituation). */
extern const VillagerTalkRepliesTexts data_020c89f8;
extern const VillagerTalkRepliesTexts data_020c8b28;
extern const VillagerTalkRepliesTexts data_020c8ca0;
extern const VillagerTalkRepliesTexts data_020c8a38;
extern const VillagerTalkRepliesTexts data_020c8970;
extern const VillagerTalkRepliesTexts data_020c8c88;

/* Tables of three member pointers for 0xb0 to 0xc0 (func_0202da88). */
extern const MemberPointer data_021c249c[3];
extern const MemberPointer data_021c2484[3];
extern const MemberPointer data_021c219c[3];
extern const MemberPointer data_021c2454[3];
extern const MemberPointer data_021c24fc[3];
extern const MemberPointer data_021c2514[3];

/* Member pointer constants the functions here store or hand on. */
extern const MemberPointer data_020d9150;
extern const MemberPointer data_020d9420;
extern const MemberPointer data_020d9280;
extern const MemberPointer data_020d90b0;
extern const MemberPointer data_020d91f8;
extern const MemberPointer data_020d8f60;
extern const MemberPointer data_020d9218;

/* What the choices run (their addresses go into TalkChoiceList's functions), and two ranges
 * of messages for them. */
extern u8 data_021c24b4[];
extern u8 data_021c24cc[];
extern u8 data_021c246c[];
extern u8 data_021c24e4[];
extern u8 data_021c21cc[];
extern u8 data_021c21e4[];
extern u8 data_021c21fc[];
extern u8 data_021c2214[];
extern u8 data_021c21b4[];
extern u8 data_021c1d6c[];
extern const u8 data_020c8928[2];
extern const u8 data_020c8924[2];

extern VillagerTown data_021e5a2c; /* the town's villagers */
extern NetSession *data_020ccf94;  /* the session */

/* The scene's member setters: the three at 0xb0 from a table, the reply, the member run at the
 * command's end and the one at 0xe0. */
extern void func_0202da88(VillagerTalk *talk, const MemberPointer *table);
extern void func_0202da74(VillagerTalk *talk, MemberPointer reply);
extern void func_0202dbf0(VillagerTalk *talk, MemberPointer next);
extern void func_0202dbdc(VillagerTalk *talk, MemberPointer member);
/* A line drawn for the personality (villager_talk.c). */
extern int func_0202da38(VillagerTalk *talk, char *text, u8 *message, int size, int personality, int texts, int per_group,
                         int group, int range);
/* The player's memory noted by the villager (unless the byte 0x13c is set). */
extern void func_0202d8f8(VillagerTalk *talk, u8 **memory, s32 *index, u8 *villager, int player);
/* The talk: its message and text, and its byte 0x18 set. */
extern void func_0206844c(u8 *talk, const u8 *message, int text);
extern void func_02068388(u8 *talk, int cond);
/* A random number below `bound`. */
extern unsigned int func_020644cc(int bound);
/* 0 for a player of this town, 1 for one of another town, 2 for none. */
extern int func_02094ffc(void *player);
/* Refreshes the 8 bytes at data_021f3b68 from data_021cfbcc. */
extern void func_0206e94c(void);
/* Another line function of the scene's classes. */
extern int func_02022454(VillagerTalk *talk);

/* The checks and line choosers of VillagerTalkReplies_LineForSituation, in the order it asks
 * them; each chooser gives a text set (and some a group). */
extern int func_0202c424(VillagerTalk *talk, int *out);
extern void func_0202bcd4(VillagerTalk *talk);
extern int func_0202c420(VillagerTalk *talk);
extern int func_0202c3f0(VillagerTalk *talk);
extern int func_0202c3e4(VillagerTalk *talk, int state);
extern const VillagerTalkRepliesTexts *func_0202c388(VillagerTalk *talk, int *group, u8 *villager);
extern int func_0202c31c(VillagerTalk *talk, s32 *which, u8 *position);
extern const VillagerTalkRepliesTexts *func_0202c2c4(VillagerTalk *talk, s32 which);
extern int func_0202c2a8(VillagerTalk *talk);
extern int func_0202c37c(VillagerTalk *talk, int state);
extern const VillagerTalkRepliesTexts *func_0202c350(VillagerTalk *talk);
extern int func_0202c27c(VillagerTalk *talk, VillagerState *entry);
extern const VillagerTalkRepliesTexts *func_0202c254(VillagerTalk *talk, int *group, VillagerState *entry);
extern int func_0202c248(VillagerTalk *talk, int byte18);
extern int func_0202c23c(VillagerTalk *talk, int byte18);
extern int func_0202c230(VillagerTalk *talk, int byte18);

static u8 *replies_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static u8 *replies_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_REPLIES_OBJECT_RECORD);
}

/* A member pointer whose function takes one argument, called. */
static void replies_call(const MemberPointer *member, VillagerTalk *talk, void *arg)
{
    void *self = MemberPointer_Object(member, talk);
    ((void (*)(void *, void *))(uintptr_t) MemberPointer_Code(member, self))(self, arg);
}

/* The line of the table's line function said: the three members set from `table`, the line
 * asked for (when there is a line function) and given to the talk.
 * REQUIRES: the tables hold a line function (the original then hands an unset line). */
static void replies_say(VillagerTalk *talk, const MemberPointer *table)
{
    VillagerTalkLine line = {0};
    func_0202da88(talk, table);
    if (talk->line.function != 0) {
        replies_call(&talk->line, talk, &line);
    }
    u8 message = line.message;
    func_0206844c(replies_talk(talk), &message, (int) line.text);
}

/* The line drawn for the personality of the talk's villager into the talk's text and
 * message, which `out` then names. */
static void replies_draw(VillagerTalk *talk, VillagerTalkLine *out, u32 texts, int per_group, int group, int range)
{
    func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE,
                  NpcId_Personality(TownVillager_NpcId(replies_record(talk))), (int) texts, per_group, group, range);
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* The player noted in the memory of the talk's villager. */
static void replies_note(VillagerTalk *talk)
{
    func_0202d8f8(talk, &talk->memory, &talk->memory_index, replies_record(talk), 0);
}

/* Two choices offered with cancel choice 1, the reply set and the talk's byte 0x18 set. */
static void replies_offer(VillagerTalk *talk, TalkChoiceList *list, MemberPointer reply)
{
    list->count = 2;
    list->cancel = 1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, list);
    func_0202da74(talk, reply);
    func_02068388(replies_talk(talk), 1);
}

/* func_020203c8: group 17 of the set at 0x020c8ab0, its count the random part. */
void VillagerTalkReplies_LineAb0Group17(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 0x11, data_020c8ab0.count);
}
CLEAN_AS(func_020203c8, VillagerTalkReplies_LineAb0Group17)

/* func_0202042c: group 14 of the set at 0x020c8ab0, its count the random part. */
void VillagerTalkReplies_LineAb0Group14(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 0xe, data_020c8ab0.count);
}
CLEAN_AS(func_0202042c, VillagerTalkReplies_LineAb0Group14)

/* func_02020490: group 12 of the set at 0x020c8ab0, the random part below 2. */
void VillagerTalkReplies_LineAb0Group12(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 0xc, 2);
}
CLEAN_AS(func_02020490, VillagerTalkReplies_LineAb0Group12)

/* func_020204f4: group 10 of the set at 0x020c8ab0, the random part below 2. */
void VillagerTalkReplies_LineAb0Group10(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 10, 2);
}
CLEAN_AS(func_020204f4, VillagerTalkReplies_LineAb0Group10)

/* func_02020558: data_021f3b68 refreshed (func_0206e94c), then the talk's villager marked in
 * the town (VillagerTown_Mark). */
void VillagerTalkReplies_MarkVillager(VillagerTalk *talk, int event)
{
    (void) event;
    func_0206e94c();
    VillagerTown_Mark(&data_021e5a2c, TownVillager_NpcId(replies_record(talk)));
}
CLEAN_AS(func_02020558, VillagerTalkReplies_MarkVillager)

/* func_02020588: group 8 of the set at 0x020c8ab0, the random part below 2; data_020d91f8 is
 * then run at the last message. */
void VillagerTalkReplies_LineAb0Group8(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 8, 2);
    talk->on_last_message = data_020d91f8;
}
CLEAN_AS(func_02020588, VillagerTalkReplies_LineAb0Group8)

/* func_02020600: two choices, message 0x44 running data_021c24b4 and message 0x52 running
 * data_021c24cc, the reply data_020d9150. */
void VillagerTalkReplies_OfferChoices44(VillagerTalk *talk, int event)
{
    (void) event;
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0x44, 0x44, (int) (uintptr_t) data_021c24b4);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0x52, 0x52, (int) (uintptr_t) data_021c24cc);
    replies_offer(talk, &list, data_020d9150);
}
CLEAN_AS(func_02020600, VillagerTalkReplies_OfferChoices44)

/* func_0202066c: group 6 of the set at 0x020c8ab0, the random part below 2. */
void VillagerTalkReplies_LineAb0Group6(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 6, 2);
}
CLEAN_AS(func_0202066c, VillagerTalkReplies_LineAb0Group6)

/* func_020206d0: the line of the table at data_021c249c said, then the scene's command asked
 * for the talk's next line. */
void VillagerTalkReplies_Say249cNextLine(VillagerTalk *talk)
{
    replies_say(talk, data_021c249c);
    SceneCommand_RequestNextLine(&talk->scene);
}
CLEAN_AS(func_020206d0, VillagerTalkReplies_Say249cNextLine)

/* func_02020728: the scene's command asked for a sound, then data_020d8f60 set at 0xe0
 * (func_0202dbdc). */
void VillagerTalkReplies_RequestSound(VillagerTalk *talk)
{
    SceneCommand_RequestSound(&talk->scene);
    func_0202dbdc(talk, data_020d8f60);
}
CLEAN_AS(func_02020728, VillagerTalkReplies_RequestSound)

/* func_02020744: the talk mode 3, then data_020d9218 run when the command ends. */
void VillagerTalkReplies_TalkMode3(VillagerTalk *talk, void *unused)
{
    (void) unused;
    SceneCommand_RequestTalkMode(&talk->scene, 3);
    func_0202dbf0(talk, data_020d9218);
}
CLEAN_AS(func_02020744, VillagerTalkReplies_TalkMode3)

/* func_02020764: the line of the table at data_021c2484 said. */
void VillagerTalkReplies_Say2484(VillagerTalk *talk, int event)
{
    (void) event;
    replies_say(talk, data_021c2484);
}
CLEAN_AS(func_02020764, VillagerTalkReplies_Say2484)

/* func_020207b8: group 20 of the set at 0x020c8ab0, its count the random part. */
void VillagerTalkReplies_LineAb0Group20(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 0x14, data_020c8ab0.count);
}
CLEAN_AS(func_020207b8, VillagerTalkReplies_LineAb0Group20)

/* func_0202081c: two choices, message 0xc4 running data_021c246c and message 0xd0 running
 * data_021c24e4, the reply data_020d9420. */
void VillagerTalkReplies_OfferChoicesC4(VillagerTalk *talk, int event)
{
    (void) event;
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0xc4, 0xc4, (int) (uintptr_t) data_021c246c);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0xd0, 0xd0, (int) (uintptr_t) data_021c24e4);
    replies_offer(talk, &list, data_020d9420);
}
CLEAN_AS(func_0202081c, VillagerTalkReplies_OfferChoicesC4)

/* func_02020888: group 3 of the set at 0x020c8ab0, its count the random part. */
void VillagerTalkReplies_LineAb0Group3(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8ab0.texts, 1, 3, data_020c8ab0.count);
}
CLEAN_AS(func_02020888, VillagerTalkReplies_LineAb0Group3)

/* func_020208ec: unless VillagerTalkReplies_LineForSituation says a line (then the player is
 * only noted), the player is noted, and before the talk of the day (a memory without bit 6) a
 * line of the set at 0x020c8ab0 (its count the lines per group, group 0) with bit 6 then set;
 * otherwise the table data_021c2514, or while the villager is not marked in the town
 * (VillagerTown_IsMarked) one of data_021c2454, data_021c24fc and data_021c2514 at random,
 * whose line function then writes the line. The villager is the one of the talk on entry. */
void VillagerTalkReplies_LineFirstOfDay(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = replies_record(talk);
    if (VillagerTalkReplies_LineForSituation(talk, out) != 0) {
        replies_note(talk);
        return;
    }
    replies_note(talk);
    if (talk->memory != NULL && VillagerMemoryEntry_Bit6((VillagerMemory *) (void *) talk->memory) == 0) {
        func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, NpcId_Personality(TownVillager_NpcId(record)),
                      (int) data_020c8ab0.texts, data_020c8ab0.count, 0, 0);
        out->text = (u32) (uintptr_t) talk->text;
        out->message = talk->message;
        VillagerMemoryEntry_SetBit6((VillagerMemory *) (void *) talk->memory);
        return;
    }
    if (VillagerTown_IsMarked(&data_021e5a2c, TownVillager_NpcId(record)) == 0) {
        switch (func_020644cc(3)) {
            case 0:
                func_0202da88(talk, data_021c2454);
                break;
            case 1:
                func_0202da88(talk, data_021c24fc);
                break;
            default:
                func_0202da88(talk, data_021c2514);
                break;
        }
    } else {
        func_0202da88(talk, data_021c2514);
    }
    if (talk->line.function != 0) {
        replies_call(&talk->line, talk, out);
    }
}
CLEAN_AS(func_020208ec, VillagerTalkReplies_LineFirstOfDay)

/* func_02020a5c: a line that takes precedence over the talk's own; whether there is one. The
 * checks are asked in order and the first that holds gives the text set (and for two of them
 * the group, else 0): func_0202c420 (data_020c89f8), func_0202c3f0 (data_020c8b28) - for both
 * the byte 0x13c is set unless func_0202c424 said 0 -, func_0202c3e4 (func_0202c388),
 * func_0202c31c on the villager's position (func_0202c2c4 with what it found), func_0202c2a8
 * (data_020c8ca0), func_0202c37c (func_0202c350), func_0202c27c on the villager's state entry
 * (func_0202c254), then on its byte 0x18 func_0202c248 (data_020c8a38), func_0202c23c
 * (data_020c8970) and func_0202c230 (data_020c8c88). The line is drawn when a set is given;
 * either way `out` names the talk's text and message and flag 2 of the state entry is set. */
int VillagerTalkReplies_LineForSituation(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = replies_record(talk);
    VillagerState *entry = VillagerStatus_StateEntry(record);
    int byte18 = VillagerState_GetByte18(entry);
    const VillagerTalkRepliesTexts *texts = NULL;
    int said = 0;
    s32 which = -1;
    int group = 0;
    int unused = 0;
    int state = func_0202c424(talk, &unused);
    func_0202bcd4(talk);

    if (func_0202c420(talk) != 0) {
        texts = &data_020c89f8;
        if (state == 0) {
            talk->no_memory = 1;
        }
    } else if (func_0202c3f0(talk) != 0) {
        texts = &data_020c8b28;
        if (state == 0) {
            talk->no_memory = 1;
        }
    } else if (func_0202c3e4(talk, state) != 0) {
        texts = func_0202c388(talk, &group, record);
    } else if (func_0202c31c(talk, &which, talk->villager + VILLAGER_TALK_REPLIES_OBJECT_POSITION) != 0) {
        texts = func_0202c2c4(talk, which);
    } else if (func_0202c2a8(talk) != 0) {
        texts = &data_020c8ca0;
    } else if (func_0202c37c(talk, state) != 0) {
        texts = func_0202c350(talk);
    } else if (func_0202c27c(talk, entry) != 0) {
        texts = func_0202c254(talk, &group, entry);
    } else if (func_0202c248(talk, byte18) != 0) {
        texts = &data_020c8a38;
    } else if (func_0202c23c(talk, byte18) != 0) {
        texts = &data_020c8970;
    } else if (func_0202c230(talk, byte18) != 0) {
        texts = &data_020c8c88;
    }

    if (texts != NULL) {
        func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, NpcId_Personality(TownVillager_NpcId(record)),
                      (int) texts->texts, texts->count, group, 0);
        said = 1;
    }
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
    entry->flags |= VILLAGER_STATE_FLAG_2;
    return said;
}
CLEAN_AS(func_02020a5c, VillagerTalkReplies_LineForSituation)

/* func_02020bf0: the line made by func_02022454 named in `out`. */
void VillagerTalkReplies_Line2454(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_02022454(talk);
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}
CLEAN_AS(func_02020bf0, VillagerTalkReplies_Line2454)

/* func_02020c18: a line of the set at 0x020c8a98, its count the lines per group, group 0. */
void VillagerTalkReplies_Line8a98(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8a98.texts, data_020c8a98.count, 0, 0);
}
CLEAN_AS(func_02020c18, VillagerTalkReplies_Line8a98)

/* func_02020c7c: a line of the set at 0x020c8a88, its count the lines per group, group 1. */
void VillagerTalkReplies_Line8a88Group1(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8a88.texts, data_020c8a88.count, 1, 0);
}
CLEAN_AS(func_02020c7c, VillagerTalkReplies_Line8a88Group1)

/* func_02020ce0: once in three (a random number below 3 at 0) while no session is linked, the
 * villager's mode record (VillagerObject_RecordMode of VillagerStatus_ModeRecord) enters mode
 * 11 and the villager is made the town's newcomer, unless it is in mode 11 already; then group
 * 3 of the set at 0x020c8a88 (its count the lines per group). Otherwise group 2. */
void VillagerTalkReplies_LineNewcomer(VillagerTalk *talk, VillagerTalkLine *out)
{
    int group;
    if (func_020644cc(3) == 0 && Session_IsLinked(data_020ccf94) == 0) {
        u8 *record = replies_record(talk);
        VillagerModeRecord *mode = VillagerObject_RecordMode((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record));
        if (VillagerStatus_IsMode11(record) == 0) {
            VillagerModeRecord_EnterMode11(mode);
            VillagerResidents_SetNewcomerNpc(&data_021e5a2c, TownVillager_NpcId(record));
        }
        group = 3;
    } else {
        group = 2;
    }
    replies_draw(talk, out, data_020c8a88.texts, data_020c8a88.count, group, 0);
}
CLEAN_AS(func_02020ce0, VillagerTalkReplies_LineNewcomer)

/* func_02020d98: two choices, messages 0x37 to 0x39 running data_021c21cc and 0x3a to 0x3c
 * running data_021c21e4, the reply data_020d9280. The list is not cleared first. */
void VillagerTalkReplies_OfferChoices37(VillagerTalk *talk)
{
    TalkChoiceList list;
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0x37, 0x39, (int) (uintptr_t) data_021c21cc);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0x3a, 0x3c, (int) (uintptr_t) data_021c21e4);
    replies_offer(talk, &list, data_020d9280);
}
CLEAN_AS(func_02020d98, VillagerTalkReplies_OfferChoices37)

/* func_02020e00: a line of the set at 0x020c8a88, its count the lines per group, group 0. */
void VillagerTalkReplies_Line8a88Group0(VillagerTalk *talk, VillagerTalkLine *out)
{
    replies_draw(talk, out, data_020c8a88.texts, data_020c8a88.count, 0, 0);
}
CLEAN_AS(func_02020e00, VillagerTalkReplies_Line8a88Group0)

/* func_02020e64: two choices, the messages of data_020c8928 running data_021c21fc once the
 * villager has arrived (VillagerStatus_IsArrived), else data_021c2214 while a session is linked
 * and the current player is of another town or none, else data_021c21b4; and the messages of
 * data_020c8924 running data_021c1d6c; the reply data_020d90b0. The list is not cleared first. */
void VillagerTalkReplies_OfferChoicesByArrival(VillagerTalk *talk)
{
    TalkChoiceList list;
    u8 *first;
    if (VillagerStatus_IsArrived(replies_record(talk)) != 0) {
        first = data_021c21fc;
    } else if (Session_IsLinked(data_020ccf94) != 0 && func_02094ffc(PlayerRecord_Player(PlayerRecords_Current())) != 0) {
        first = data_021c2214;
    } else {
        first = data_021c21b4;
    }
    TalkChoices_SetFrom((int) (uintptr_t) talk, &list, 0, data_020c8928, (u32) (uintptr_t) first);
    TalkChoices_SetFrom((int) (uintptr_t) talk, &list, 1, data_020c8924, (u32) (uintptr_t) data_021c1d6c);
    replies_offer(talk, &list, data_020d90b0);
}
CLEAN_AS(func_02020e64, VillagerTalkReplies_OfferChoicesByArrival)

/* func_02020f14: the line of the table at data_021c219c said. */
void VillagerTalkReplies_Say219c(VillagerTalk *talk)
{
    replies_say(talk, data_021c219c);
}
CLEAN_AS(func_02020f14, VillagerTalkReplies_Say219c)

/* func_02020f68: the player noted in the villager's memory. */
void VillagerTalkReplies_NoteMemory(VillagerTalk *talk)
{
    replies_note(talk);
}
CLEAN_AS(func_02020f68, VillagerTalkReplies_NoteMemory)
