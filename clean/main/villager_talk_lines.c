/* More members of the town villagers' talk scenes (villager_talk_lines.h). */
#include "villager_talk_lines.h"

#include <string.h>

#include "calendar.h"
#include "clean.h"
#include "current_pockets.h"
#include "date_time.h"
#include "group_params.h"
#include "item_code.h"
#include "lookups.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "state_block.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"

/* The villager scene object's town record (town_villager.h), or 0. */
#define VILLAGER_TALK_LINES_OBJECT_RECORD 0x830
/* The talk's word that asks for the next line (scene_command.h). */
#define VILLAGER_TALK_LINES_TALK_NEXT 2

#define VILLAGER_TALK_LINES_NO_ITEM 0xfff1

/* A text set of the talk lines: its texts and a count (a number of lines, or of lines per
 * group). */
typedef struct VillagerTalkLinesTexts {
    u32 texts;
    u8 count;
} VillagerTalkLinesTexts;

/* An item list: func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063cc8
 * destructs it. */
typedef struct VillagerTalkLinesItemList {
    u32 kind;
    u32 group;
} VillagerTalkLinesItemList;

/* The text sets. */
extern const VillagerTalkLinesTexts data_020c8d60;
extern const VillagerTalkLinesTexts data_020c8ba0;
extern const VillagerTalkLinesTexts data_020c8bd8;
extern const VillagerTalkLinesTexts data_020c8bf0;
extern const VillagerTalkLinesTexts data_020c8a60;
extern const VillagerTalkLinesTexts data_020c8ce8;
extern const VillagerTalkLinesTexts data_020c8c68;

/* Tables of three member pointers for 0xb0 to 0xc0 (func_0202da88). */
extern const MemberPointer data_021c2394[3];
extern const MemberPointer data_021c23dc[3];
extern const MemberPointer data_021c23f4[3];
extern const MemberPointer data_021c240c[3];
extern const MemberPointer data_021c2424[3];
extern const MemberPointer data_021c208c[3];
extern const MemberPointer data_021c2044[3];
extern const MemberPointer data_021c205c[3];
extern const MemberPointer data_021c2074[3];
extern const MemberPointer data_021c25d4[3];
extern const MemberPointer data_021c25bc[3];
extern const MemberPointer data_021c25ec[3];
extern const MemberPointer data_021c2574[3];
extern const MemberPointer data_021c252c[3];
extern const MemberPointer data_021c255c[3];
extern const MemberPointer data_021c258c[3];
extern const MemberPointer data_021c2544[3];
extern const MemberPointer data_021c202c[3];
extern const MemberPointer data_021c1fe4[3];
extern const MemberPointer data_021c1ffc[3];
extern const MemberPointer data_021c2014[3];
extern const MemberPointer data_021c237c[3];
extern const MemberPointer data_021c2334[3];
extern const MemberPointer data_021c22ec[3];
extern const MemberPointer data_021c22d4[3];
extern const MemberPointer data_021c2304[3];
extern const MemberPointer data_021c2364[3];

/* Member pointer constants the functions here store. */
extern const MemberPointer data_020d9048;
extern const MemberPointer data_020d8e28;
extern const MemberPointer data_020d9070;
extern const MemberPointer data_020d90c8;
extern const MemberPointer data_020d90e8;
extern const MemberPointer data_020d9430;
extern const MemberPointer data_020d9390;
extern const MemberPointer data_020d9310;
extern const MemberPointer data_020d8e88;
extern const MemberPointer data_020d91d8;

/* What the choices run (their addresses go into TalkChoiceList's functions), and two ranges
 * of messages for them. */
extern u8 data_021c25a4[];
extern u8 data_021c234c[];
extern u8 data_021c231c[];
extern u8 data_021c1e14[];
extern u8 data_021c1d6c[];
extern const u8 data_020c8928[2];
extern const u8 data_020c8924[2];

/* The talk's last message (the message handed when a line is not said). */
extern u8 data_021f43e8;
/* A text shown on the screen of mode 23. */
extern u8 data_021c1e84[];
/* The record of an item and the people it is about (villager_talk_lines.h). */
extern u8 data_021f3aa4[];
/* The state block (state_block.h). */
extern u32 data_021dc7a8[];
/* The item list kinds VillagerTalk_GiveItemFor1546 draws from. */
extern const u32 data_020c8e98[3];

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
/* A line that takes precedence over the talk's own, written into `out`; whether there was. */
extern int func_02020a5c(VillagerTalk *talk, VillagerTalkLine *out);
/* Other line functions of the scene's classes. */
extern void func_0202bdb4(VillagerTalk *talk, VillagerTalkLine *out);
extern void func_0202a5e8(VillagerTalk *talk, VillagerTalkLine *out);
/* The talk: its message and text set, and its byte 0x18 set. */
extern void func_0206844c(u8 *talk, const u8 *message, int text);
extern void func_02068388(u8 *talk, int cond);
/* A random number below `bound`. */
extern unsigned int func_020644cc(int bound);
/* The days since the town's event `event` this year (func_0209e380), -1 without one. */
extern int func_0203fdc4(int event);
/* Whether the player is set up (func_02064294) with its halfword 0xe set. */
extern int func_020951bc(u8 *player);
/* The parts of the record at data_021f3aa4: its address, the NpcId at 0x1e, that at 0x2e, the
 * item at 0x3e (copied) and the size at 0x40. */
extern u8 *func_020867e0(u8 *record);
extern NpcId *func_020867a0(u8 *record);
extern NpcId *func_0208675c(u8 *record);
extern void func_0208674c(u16 *item, u8 *record);
extern int func_02086744(u8 *record);
/* Item lists. */
extern void func_02063ccc(VillagerTalkLinesItemList *list, int kind, int group);
extern void func_02063cc8(VillagerTalkLinesItemList *list);
extern void func_020638d4(u16 *item, VillagerTalkLinesItemList *list, int a, int b, int c, int d, int e);
/* Item records: `*item` marked as had. */
extern int OSi_DoUnlockByWord__main_0203cd2c(u8 *items, u16 *item, int mode, int set);
/* The predicates this file hands to the game (the game's own functions; the first returns a
 * halfword where PocketPredicate has an int, which the ARM caller reads alike). */
extern u16 func_0201f520(u16 *item, int state);
extern int func_0201f550(u16 *item);

static u8 *lines_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneBase *lines_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static u8 *lines_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_LINES_OBJECT_RECORD);
}

static VillagerMemory *lines_memory(const VillagerTalk *talk)
{
    return (VillagerMemory *) (void *) talk->memory;
}

/* A member pointer whose function takes one argument, called. */
static void lines_call(const MemberPointer *member, VillagerTalk *talk, void *arg)
{
    void *self = MemberPointer_Object(member, talk);
    ((void (*)(void *, void *))(uintptr_t) MemberPointer_Code(member, self))(self, arg);
}

/* The line of the table's line function said: the three members set from `table`, the talk
 * asked for its next line when `next` is set (and it has a talk), the line asked for and given
 * to the talk.
 * REQUIRES: the tables hold a line function (the original then reads an unset line). */
static void lines_say(VillagerTalk *talk, const MemberPointer *table, int next)
{
    VillagerTalkLine line = {0};
    func_0202da88(talk, table);
    if (next && talk->scene.talk != NULL) {
        talk->scene.talk[VILLAGER_TALK_LINES_TALK_NEXT] = 1;
    }
    if (talk->line.function != 0) {
        lines_call(&talk->line, talk, &line);
    }
    u8 message = line.message;
    func_0206844c(lines_talk(talk), &message, (int) line.text);
}

/* The line drawn for the personality of the villager `record` into the talk's text and
 * message, which `out` then names. */
static void lines_draw_for(VillagerTalk *talk, VillagerTalkLine *out, u8 *record, u32 texts, int per_group, int group,
                           int range)
{
    func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, NpcId_Personality(TownVillager_NpcId(record)),
                  (int) texts, per_group, group, range);
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* As lines_draw_for, for the talk's villager. */
static void lines_draw(VillagerTalk *talk, VillagerTalkLine *out, u32 texts, int per_group, int group, int range)
{
    lines_draw_for(talk, out, lines_record(talk), texts, per_group, group, range);
}

/* The player noted in the memory of the villager `record`. */
static void lines_note(VillagerTalk *talk, u8 *record)
{
    func_0202d8f8(talk, &talk->memory, &talk->memory_index, record, 0);
}

/* The player noted, and bit 6 of the memory set when there is one. */
static void lines_note_and_mark(VillagerTalk *talk, u8 *record)
{
    lines_note(talk, record);
    if (talk->memory != NULL) {
        VillagerMemoryEntry_SetBit6(lines_memory(talk));
    }
}

/* Whether the talk has a memory of the player with bit 6 set. */
static int lines_talked_today(VillagerTalk *talk)
{
    return talk->memory != NULL && VillagerMemoryEntry_Bit6(lines_memory(talk)) != 0;
}

/* Whether two NpcIds are the same person: the first halfword, the 12 bytes after it and the
 * number. */
static int lines_same_npc(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof a->head.data) == 0 && a->number == b->number;
}

/* func_0201e890 */
void VillagerTalk_Line2bdb4(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_0202bdb4(talk, out);
}
CLEAN_AS(func_0201e890, VillagerTalk_Line2bdb4)

/* func_0201e898: a line by the clock and the hours of the villager's personality
 * (Lookups_DayWindow). On the 31st of a month before 23:00 the table data_021c2394; else,
 * unless func_02020a5c says a line (then the player is only noted), on the 31st the table
 * data_021c23dc, and on other days data_021c23f4 before the end of the hours, then
 * data_021c240c, or data_021c2424 once the talk of the day was had; on other days than the
 * 31st the year (2000 + the clock's) also goes into slot 0. The table's line function writes
 * the line, then the player is noted and bit 6 of the memory set. The villager is the one of
 * the talk on entry. */
void VillagerTalk_LineByDayWindow(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = lines_record(talk);
    DateTime now = {0};
    DateTime_Now(&now);

    int before_23 = now.day == 31 && now.hour < 23;
    if (!before_23 && func_02020a5c(talk, out) != 0) {
        lines_note(talk, record);
        return;
    }

    if (now.day == 31) {
        func_0202da88(talk, now.hour < 23 ? data_021c2394 : data_021c23dc);
    } else {
        const DayWindow *window = Lookups_DayWindow((u32) NpcId_Personality(TownVillager_NpcId(record)));
        if (now.hour < window->end_hour || (now.hour == window->end_hour && now.minute < window->end_minute)) {
            func_0202da88(talk, data_021c23f4);
        } else if (!lines_talked_today(talk)) {
            func_0202da88(talk, data_021c240c);
        } else {
            func_0202da88(talk, data_021c2424);
        }
        SceneBase_PutValue(lines_base(talk), now.year + 2000, 0, 4, 0, 0);
    }

    if (talk->line.function != 0) {
        lines_call(&talk->line, talk, out);
    }
    lines_note_and_mark(talk, record);
}
CLEAN_AS(func_0201e898, VillagerTalk_LineByDayWindow)

/* func_0201e9e0 */
void VillagerTalk_OfferChoices1e14A(VillagerTalk *talk)
{
    VillagerTalk_OfferChoices1e14(talk);
}
CLEAN_AS(func_0201e9e0, VillagerTalk_OfferChoices1e14A)

/* func_0201e9e8 */
void VillagerTalk_Line2a5e8A(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_0202a5e8(talk, out);
}
CLEAN_AS(func_0201e9e8, VillagerTalk_Line2a5e8A)

/* func_0201e9f0: the line of the table at data_021c208c said. */
void VillagerTalk_Say208c(VillagerTalk *talk)
{
    lines_say(talk, data_021c208c, 0);
}
CLEAN_AS(func_0201e9f0, VillagerTalk_Say208c)

/* func_0201ea44: a line of the set at 0x020c8d60 (group 0, its count the random range). */
void VillagerTalk_Line8d60(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8d60.texts, 1, 0, data_020c8d60.count);
}
CLEAN_AS(func_0201ea44, VillagerTalk_Line8d60)

/* func_0201eaa8: a line of the set at 0x020c8d60 about the person at 0x2e of data_021f3aa4:
 * group 12 when it is this villager, else 15; a valid person's name goes into slot 1. */
void VillagerTalk_Line8d60AboutNpc(VillagerTalk *talk, VillagerTalkLine *out)
{
    NpcId *npc = func_0208675c(data_021f3aa4);
    const NpcId *self = TownVillager_NpcId(lines_record(talk));
    int group = lines_same_npc(npc, self) ? 12 : 15;
    if (NpcId_IsValid(npc) != 0) {
        SceneBase_PutNpcName(lines_base(talk), npc, 1);
    }
    lines_draw(talk, out, data_020c8d60.texts, 1, group, data_020c8d60.count);
}
CLEAN_AS(func_0201eaa8, VillagerTalk_Line8d60AboutNpc)

/* func_0201eb5c: a line of the set at 0x020c8d60 by the days since the town's event 17 (none
 * counted as 0): on its day group 3 (range 2), up to 5 days after group 5 (range 3); later,
 * with the state block's flag 17 and a valid person at 0x1e of data_021f3aa4, group 11
 * (range 1) when that is this villager, else group 8 (range 3), with the person's name in slot
 * 0; else group 18 (range 2). The villager compared is the one of the talk on entry. */
void VillagerTalk_Line8d60SinceEvent17(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = lines_record(talk);
    NpcId *npc = func_020867a0(data_021f3aa4);
    int days = func_0203fdc4(0x11);
    if (days < 0) {
        days = 0;
    }

    int range;
    int group;
    if (days == 0) {
        range = 2;
        group = 3;
    } else if (days <= 5) {
        range = 3;
        group = 5;
    } else if (StateBlock_TestFlag(data_021dc7a8, 0x11) != 0 && NpcId_IsValid(npc) != 0) {
        if (lines_same_npc(npc, TownVillager_NpcId(record))) {
            range = 1;
            group = 0xb;
        } else {
            range = 3;
            group = 8;
        }
        SceneBase_PutNpcName(lines_base(talk), npc, 0);
    } else {
        range = 2;
        group = 0x12;
    }
    lines_draw(talk, out, data_020c8d60.texts, 1, group, range);
}
CLEAN_AS(func_0201eb5c, VillagerTalk_Line8d60SinceEvent17)

/* func_0201ec58: unless func_02020a5c says a line (then the player is only noted), a table by
 * chance: before the talk of the day data_021c2044; after it a random number below 2 (below 3
 * when the town's event 17 was 6 days ago) picks data_021c205c (0, with a valid person at 0x2e
 * of data_021f3aa4), data_021c2074 (1, or 0 without one) or data_021c2044 (2). The table's line
 * function writes the line, then the player is noted and bit 6 of the memory set. */
void VillagerTalk_LineRandom2044(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = lines_record(talk);
    NpcId *npc = func_0208675c(data_021f3aa4);
    if (func_02020a5c(talk, out) != 0) {
        lines_note(talk, record);
        return;
    }

    int bound = 2;
    if (func_0203fdc4(0x11) == 6 && lines_talked_today(talk)) {
        bound = 3;
    }
    int pick = (int) func_020644cc(bound);
    if (!lines_talked_today(talk) || pick == 2) {
        func_0202da88(talk, data_021c2044);
    } else if (pick == 0 && NpcId_IsValid(npc) != 0) {
        func_0202da88(talk, data_021c205c);
    } else {
        func_0202da88(talk, data_021c2074);
    }

    if (talk->line.function != 0) {
        lines_call(&talk->line, talk, out);
    }
    lines_note_and_mark(talk, record);
}
CLEAN_AS(func_0201ec58, VillagerTalk_LineRandom2044)

/* func_0201ed68: group 15 of the set at 0x020c8ba0, the random part below 2. */
void VillagerTalk_Line8ba0Group15(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ba0.texts, 1, 0xf, 2);
}
CLEAN_AS(func_0201ed68, VillagerTalk_Line8ba0Group15)

/* func_0201edcc: the villager gives an item for the player's item at 0x124: 0x1566 for 0x1546
 * (compared by item without its variant when it has one), else one drawn from the list of a
 * kind of data_020c8e98 picked at random. It becomes the gift at 0x19c, is put into the
 * player's first free pocket and marked as had, and is shown (motion 13) with its name in slot
 * 0. QUIRK: without a free pocket the gift replaces the first pocket. */
void VillagerTalk_GiveItemFor1546(VillagerTalk *talk)
{
    u8 *player = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(player);
    int slot = PlayerPockets_FreeSlot(pockets);
    if (slot == -1) {
        slot = 0;
    }

    int is_1546;
    if (ItemCode_HasVariant(&talk->item)) {
        ItemCode wanted = 0x1546;
        int held = ItemCode_VariantItem(&talk->item);
        is_1546 = held == ItemCode_VariantItem(&wanted);
    } else {
        is_1546 = talk->item == 0x1546;
    }

    if (is_1546) {
        talk->gift = 0x1566;
    } else {
        int kind = (int) func_020644cc(3);
        VillagerTalkLinesItemList list;
        u16 item;
        func_02063ccc(&list, (int) data_020c8e98[kind], 0);
        func_020638d4(&item, &list, 0, 0, 1, 1, 0);
        talk->gift = item;
        func_02063cc8(&list);
    }

    PlayerPockets_SetSlot(pockets, &talk->gift, slot, 0);
    OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(player), &talk->gift, 0, 1);
    SceneCommand_RequestMotion13(&talk->scene, &talk->gift, 0, 5, 0);
    if (talk->gift != VILLAGER_TALK_LINES_NO_ITEM) {
        SceneBase_PutItemName(lines_base(talk), (int) (uintptr_t) &talk->gift, 0, 7);
    }
}
CLEAN_AS(func_0201edcc, VillagerTalk_GiveItemFor1546)

/* func_0201eed8: group 19 of the set at 0x020c8ba0, the random part below 2. */
void VillagerTalk_Line8ba0Group19(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ba0.texts, 1, 0x13, 2);
}
CLEAN_AS(func_0201eed8, VillagerTalk_Line8ba0Group19)

/* func_0201ef3c: by chance growing with the villager's fondness of the player (fondness +
 * 0x100 above a random number below 0x200), the line of the table at data_021c25d4 said; else
 * the talk goes to its last message with the set at 0x020c8ba0. */
void VillagerTalk_SayIfFond(VillagerTalk *talk)
{
    int fondness = 0;
    if (talk->memory != NULL) {
        fondness = VillagerMemoryEntry_Fondness(lines_memory(talk));
    }
    if (fondness + 0x100 > (int) func_020644cc(0x200)) {
        lines_say(talk, data_021c25d4, 0);
    } else {
        func_0206844c(lines_talk(talk), &data_021f43e8, (int) data_020c8ba0.texts);
    }
}
CLEAN_AS(func_0201ef3c, VillagerTalk_SayIfFond)

/* func_0201efd4: group 17 of the set at 0x020c8ba0, the random part below 2. */
void VillagerTalk_Line8ba0Group17(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ba0.texts, 1, 0x11, 2);
}
CLEAN_AS(func_0201efd4, VillagerTalk_Line8ba0Group17)

/* func_0201f038: the line of the table at data_021c25bc said, the talk asked for its next
 * line first. */
void VillagerTalk_Say25bcNext(VillagerTalk *talk)
{
    lines_say(talk, data_021c25bc, 1);
}
CLEAN_AS(func_0201f038, VillagerTalk_Say25bcNext)

/* func_0201f094: when the pockets screen gave a pocket (GroupParams_C4CIs1), its item is taken
 * as the item at 0x124: the pocket emptied, the item taken (motion 14) and data_020d9048 set
 * at 0xe0. Else the line of the table at data_021c25ec is said, the talk asked for its next
 * line first. */
void VillagerTalk_TakePocketOrSay(VillagerTalk *talk)
{
    if (GroupParams_C4CIs1()) {
        u8 slot = GroupParams_Arg();
        PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
        talk->item = *PlayerPockets_Slot(pockets, slot);
        u16 none = VILLAGER_TALK_LINES_NO_ITEM;
        CurrentPockets_Set(&none, 0, slot);
        SceneCommand_RequestMotion14(&talk->scene, &talk->item, 0, 5, 0);
        func_0202dbdc(talk, data_020d9048);
        return;
    }
    lines_say(talk, data_021c25ec, 1);
}
CLEAN_AS(func_0201f094, VillagerTalk_TakePocketOrSay)

/* func_0201f150: the pockets screen opened on the items 0x1542-0x1546 (the game's
 * func_0201f520, with 13, staying on the line), then data_020d8e28 at the command's end. */
void VillagerTalk_AskPocket1542(VillagerTalk *talk)
{
    SceneCommand_SetPocketPredicate(&talk->scene, (PocketPredicate) (void (*)(void)) func_0201f520, 13, 1);
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_POCKETS);
    func_0202dbf0(talk, data_020d8e28);
}
CLEAN_AS(func_0201f150, VillagerTalk_AskPocket1542)

/* func_0201f180: two choices offered with cancel choice 1: messages 0x5b-0x5d running
 * data_021c25a4 and 0x5e-0x60 running data_021c25ec; the reply data_020d9070; the talk's byte
 * 0x18 set. */
void VillagerTalk_OfferChoices5b(VillagerTalk *talk)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0x5b, 0x5d, (int) (uintptr_t) data_021c25a4);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0x5e, 0x60, (int) (uintptr_t) data_021c25ec);
    list.count = 2;
    list.cancel = 1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    func_0202da74(talk, data_020d9070);
    func_02068388(lines_talk(talk), 1);
}
CLEAN_AS(func_0201f180, VillagerTalk_OfferChoices5b)

/* func_0201f1f0: group 13 of the set at 0x020c8ba0, the random part below 2. */
void VillagerTalk_Line8ba0Group13(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ba0.texts, 1, 0xd, 2);
}
CLEAN_AS(func_0201f1f0, VillagerTalk_Line8ba0Group13)

/* func_0201f254 */
void VillagerTalk_OfferChoices1e14B(VillagerTalk *talk)
{
    VillagerTalk_OfferChoices1e14(talk);
}
CLEAN_AS(func_0201f254, VillagerTalk_OfferChoices1e14B)

/* func_0201f25c */
void VillagerTalk_Line2a5e8B(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_0202a5e8(talk, out);
}
CLEAN_AS(func_0201f25c, VillagerTalk_Line2a5e8B)

/* func_0201f264: the line of the table at data_021c2574 said. */
void VillagerTalk_Say2574(VillagerTalk *talk)
{
    lines_say(talk, data_021c2574, 0);
}
CLEAN_AS(func_0201f264, VillagerTalk_Say2574)

/* func_0201f2b8: group 7 of the set at 0x020c8ba0. */
void VillagerTalk_Line8ba0Group7(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ba0.texts, 1, 7, data_020c8ba0.count);
}
CLEAN_AS(func_0201f2b8, VillagerTalk_Line8ba0Group7)

/* func_0201f31c: group 10 of the set at 0x020c8ba0. */
void VillagerTalk_Line8ba0Group10(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ba0.texts, 1, 10, data_020c8ba0.count);
}
CLEAN_AS(func_0201f31c, VillagerTalk_Line8ba0Group10)

/* func_0201f380: a line of the set at 0x020c8ba0 by the days since the town's event 16 (none
 * counted as 0): on its day group 0 (range 2), up to 5 days after group 2 (range 3), later
 * group 5 (range 2). */
void VillagerTalk_Line8ba0SinceEvent16(VillagerTalk *talk, VillagerTalkLine *out)
{
    int days = func_0203fdc4(0x10);
    if (days < 0) {
        days = 0;
    }
    int range;
    int group;
    if (days == 0) {
        range = 2;
        group = 0;
    } else if (days <= 5) {
        range = 3;
        group = 2;
    } else {
        range = 2;
        group = 5;
    }
    lines_draw(talk, out, data_020c8ba0.texts, 1, group, range);
}
CLEAN_AS(func_0201f380, VillagerTalk_Line8ba0SinceEvent16)

/* func_0201f40c: two random bits drawn first; unless func_02020a5c says a line (then the
 * player is only noted), before the talk of the day the table data_021c252c; after it, on the
 * first bit 0 data_021c255c, else on the second bit 0 data_021c258c when the player has an
 * item 0x1542-0x1546 (data_021c255c when not), else data_021c2544. The table's line function
 * writes the line, then the player is noted and bit 6 of the memory set. */
void VillagerTalk_LineRandom252c(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = lines_record(talk);
    unsigned int first = func_020644cc(10) & 1;
    unsigned int second = func_020644cc(10) & 1;
    if (func_02020a5c(talk, out) != 0) {
        lines_note(talk, record);
        return;
    }

    if (!lines_talked_today(talk)) {
        func_0202da88(talk, data_021c252c);
    } else if (first == 0) {
        func_0202da88(talk, data_021c255c);
    } else if (second == 0) {
        PocketsMarks marks;
        if (CurrentPockets_Mark(&marks, func_0201f550) > 0) {
            func_0202da88(talk, data_021c258c);
        } else {
            func_0202da88(talk, data_021c255c);
        }
    } else {
        func_0202da88(talk, data_021c2544);
    }

    if (talk->line.function != 0) {
        lines_call(&talk->line, talk, out);
    }
    lines_note_and_mark(talk, record);
}
CLEAN_AS(func_0201f40c, VillagerTalk_LineRandom252c)

/* func_0201f520 (a pocket predicate): 1 for an item 0x1542-0x1546 in state 0. */
u16 VillagerTalk_Pick1542Item(u16 *item, int state)
{
    return *item >= 0x1542 && *item <= 0x1546 && state == 0;
}
CLEAN_AS(func_0201f520, VillagerTalk_Pick1542Item)

/* func_0201f550 (a pocket test): whether the item is one of 0x1542-0x1546. */
int VillagerTalk_Is1542Item(u16 *item)
{
    return *item >= 0x1542 && *item <= 0x1546;
}
CLEAN_AS(func_0201f550, VillagerTalk_Is1542Item)

/* func_0201f570 */
void VillagerTalk_OfferChoices1e14C(VillagerTalk *talk)
{
    VillagerTalk_OfferChoices1e14(talk);
}
CLEAN_AS(func_0201f570, VillagerTalk_OfferChoices1e14C)

/* func_0201f578 */
void VillagerTalk_Line2a5e8C(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_0202a5e8(talk, out);
}
CLEAN_AS(func_0201f578, VillagerTalk_Line2a5e8C)

/* func_0201f580: the line of the table at data_021c202c said. */
void VillagerTalk_Say202c(VillagerTalk *talk)
{
    lines_say(talk, data_021c202c, 0);
}
CLEAN_AS(func_0201f580, VillagerTalk_Say202c)

/* func_0201f5d4: group 10 of the set at 0x020c8bd8. */
void VillagerTalk_Line8bd8Group10(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8bd8.texts, 1, 10, data_020c8bd8.count);
}
CLEAN_AS(func_0201f5d4, VillagerTalk_Line8bd8Group10)

/* func_0201f638: group 13 of the set at 0x020c8bd8. */
void VillagerTalk_Line8bd8Group13(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8bd8.texts, 1, 13, data_020c8bd8.count);
}
CLEAN_AS(func_0201f638, VillagerTalk_Line8bd8Group13)

/* func_0201f69c: a line of the set at 0x020c8bd8 by the days since the town's event 14 (none
 * counted as 0): on its day group 0 (range 2), 1 or 2 days after group 2 (range 3), 3 to 5
 * days after group 5 (range 3), later group 8 (range 2). */
void VillagerTalk_Line8bd8SinceEvent14(VillagerTalk *talk, VillagerTalkLine *out)
{
    int days = func_0203fdc4(14);
    if (days < 0) {
        days = 0;
    }
    int range;
    int group;
    if (days == 0) {
        range = 2;
        group = 0;
    } else if (days <= 2) {
        range = 3;
        group = 2;
    } else if (days <= 5) {
        range = 3;
        group = 5;
    } else {
        range = 2;
        group = 8;
    }
    lines_draw(talk, out, data_020c8bd8.texts, 1, group, range);
}
CLEAN_AS(func_0201f69c, VillagerTalk_Line8bd8SinceEvent14)

/* func_0201f738: a random bit drawn first; unless func_02020a5c says a line (then the player
 * is only noted), before the talk of the day the table data_021c1fe4, after it data_021c2014
 * on bit 0 and data_021c1ffc on bit 1. The table's line function writes the line, then the
 * player is noted and bit 6 of the memory set. */
void VillagerTalk_LineRandom1fe4(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = lines_record(talk);
    unsigned int bit = func_020644cc(10) & 1;
    if (func_02020a5c(talk, out) != 0) {
        lines_note(talk, record);
        return;
    }

    if (!lines_talked_today(talk)) {
        func_0202da88(talk, data_021c1fe4);
    } else if (bit == 0) {
        func_0202da88(talk, data_021c2014);
    } else {
        func_0202da88(talk, data_021c1ffc);
    }

    if (talk->line.function != 0) {
        lines_call(&talk->line, talk, out);
    }
    lines_note_and_mark(talk, record);
}
CLEAN_AS(func_0201f738, VillagerTalk_LineRandom1fe4)

/* func_0201f814: the player noted and bit 6 of the memory set. */
void VillagerTalk_NoteAndMarkMemory(VillagerTalk *talk)
{
    lines_note_and_mark(talk, lines_record(talk));
}
CLEAN_AS(func_0201f814, VillagerTalk_NoteAndMarkMemory)

/* A line of the set `texts` about the item of data_021f3aa4. Unless func_02020a5c says a line
 * (then the player is only noted), after the talk of the day and with the record's item in
 * first-last: group 3 when the person at 0x1e of the record is valid and is this villager;
 * when valid and another, the group of the clock's hour (VillagerTalk_GroupForHour), and the
 * person's name in slot 1; when not valid but the record's player is set up, the hour's group
 * and the player's name in slot 1; else group 0; then the record's size (by `put_size`) into
 * slot 0 and the item's name into slot 0. Else group 0. Then `last` is run at the last
 * message. The villager is the one of the talk on entry. */
static void lines_item_line(VillagerTalk *talk, VillagerTalkLine *out, u16 first, u16 last,
                            const VillagerTalkLinesTexts *texts, void (*put_size)(VillagerTalk *talk, int size),
                            const MemberPointer *at_last)
{
    if (func_02020a5c(talk, out) != 0) {
        lines_note(talk, lines_record(talk));
        return;
    }

    u8 *record = lines_record(talk);
    u16 item;
    func_0208674c(&item, data_021f3aa4);
    DateTime now = {0};
    DateTime_Now(&now);

    int group = 0;
    if (lines_talked_today(talk) && item >= first && item <= last) {
        u8 *player = func_020867e0(data_021f3aa4);
        NpcId *npc = func_020867a0(data_021f3aa4);
        if (NpcId_IsValid(npc) != 0) {
            if (lines_same_npc(npc, TownVillager_NpcId(record))) {
                group = 3;
            } else {
                group = VillagerTalk_GroupForHour(now.hour);
            }
            SceneBase_PutNpcName(lines_base(talk), npc, 1);
        } else if (func_020951bc(player) != 0) {
            group = VillagerTalk_GroupForHour(now.hour);
            SceneBase_PutNameAt10(lines_base(talk), func_020867e0(data_021f3aa4), 1);
        }
        put_size(talk, func_02086744(data_021f3aa4));
        SceneBase_PutItemName(lines_base(talk), (int) (uintptr_t) &item, 0, 7);
    }

    lines_draw_for(talk, out, record, texts->texts, 1, group, texts->count);
    talk->on_last_message = *at_last;
}

/* The size in whole units (its fraction dropped, rounding down). */
static void lines_put_whole_size(VillagerTalk *talk, int size)
{
    SceneBase_PutValue(lines_base(talk), size >> 12, 0, 3, 0, 0);
}

/* The size with its fraction. */
static void lines_put_decimal_size(VillagerTalk *talk, int size)
{
    SceneBase_PutDecimal(lines_base(talk), size, 0, 1, 3);
}

/* func_0201f858: lines_item_line for the items 0x12b0-0x12e7 and the set at 0x020c8bf0, the
 * size in whole units; data_020d90c8 at the last message. */
void VillagerTalk_LineItem12b0(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_item_line(talk, out, 0x12b0, 0x12e7, &data_020c8bf0, lines_put_whole_size, &data_020d90c8);
}
CLEAN_AS(func_0201f858, VillagerTalk_LineItem12b0)

/* func_0201fa14: as VillagerTalk_NoteAndMarkMemory. */
void VillagerTalk_NoteAndMarkMemoryAgain(VillagerTalk *talk)
{
    lines_note_and_mark(talk, lines_record(talk));
}
CLEAN_AS(func_0201fa14, VillagerTalk_NoteAndMarkMemoryAgain)

/* func_0201fa58: lines_item_line for the items 0x12e8-0x131f and the set at 0x020c8a60, the
 * size with its fraction; data_020d90e8 at the last message. */
void VillagerTalk_LineItem12e8(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_item_line(talk, out, 0x12e8, 0x131f, &data_020c8a60, lines_put_decimal_size, &data_020d90e8);
}
CLEAN_AS(func_0201fa58, VillagerTalk_LineItem12e8)

/* func_0201fc14: the group of a line by the hour: 6 at 6, 9, 12 and 15 o'clock, 12 at 8, 11,
 * 14 and 17 o'clock, else 9. */
int VillagerTalk_GroupForHour(int hour)
{
    switch (hour) {
        case 6:
        case 9:
        case 12:
        case 15:
            return 6;
        case 8:
        case 11:
        case 14:
        case 17:
            return 12;
        default:
            return 9;
    }
}
CLEAN_AS(func_0201fc14, VillagerTalk_GroupForHour)

/* func_0201fc4c */
void VillagerTalk_OfferChoices1e14D(VillagerTalk *talk)
{
    VillagerTalk_OfferChoices1e14(talk);
}
CLEAN_AS(func_0201fc4c, VillagerTalk_OfferChoices1e14D)

/* func_0201fc54 */
void VillagerTalk_Line2a5e8D(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_0202a5e8(talk, out);
}
CLEAN_AS(func_0201fc54, VillagerTalk_Line2a5e8D)

/* func_0201fc5c: the line of the table at data_021c237c said. */
void VillagerTalk_Say237c(VillagerTalk *talk)
{
    lines_say(talk, data_021c237c, 0);
}
CLEAN_AS(func_0201fc5c, VillagerTalk_Say237c)

/* func_0201fcb0: group 4 of the set at 0x020c8ce8, the random part below 3. */
void VillagerTalk_Line8ce8Group4(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ce8.texts, 1, 4, 3);
}
CLEAN_AS(func_0201fcb0, VillagerTalk_Line8ce8Group4)

/* func_0201fd14: group 10 of the set at 0x020c8ce8. */
void VillagerTalk_Line8ce8Group10(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ce8.texts, 1, 10, data_020c8ce8.count);
}
CLEAN_AS(func_0201fd14, VillagerTalk_Line8ce8Group10)

/* func_0201fd78: group 14 of the set at 0x020c8ce8. */
void VillagerTalk_Line8ce8Group14(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ce8.texts, 1, 14, data_020c8ce8.count);
}
CLEAN_AS(func_0201fd78, VillagerTalk_Line8ce8Group14)

/* func_0201fddc: VillagerTalk_StoreText, then the line of the table at data_021c2334 said. */
void VillagerTalk_StoreTextSay2334(VillagerTalk *talk)
{
    VillagerTalk_StoreText(talk);
    lines_say(talk, data_021c2334, 0);
}
CLEAN_AS(func_0201fddc, VillagerTalk_StoreTextSay2334)

/* The text data_021c1e84 shown on the screen of mode 23 (10 units, staying on the line), then
 * `next` at the command's end. */
static void lines_show_text(VillagerTalk *talk, MemberPointer next)
{
    SceneCommand_SetScreenText(&talk->scene, 23, (u32) (uintptr_t) data_021c1e84, 10, 0);
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_MODE_TEXT);
    func_0202dbf0(talk, next);
}

/* func_0201fe34: lines_show_text, then data_020d9430. */
void VillagerTalk_ShowText9430(VillagerTalk *talk, int event)
{
    (void) event;
    lines_show_text(talk, data_020d9430);
}
CLEAN_AS(func_0201fe34, VillagerTalk_ShowText9430)

/* func_0201fe6c: group 12 of the set at 0x020c8ce8. */
void VillagerTalk_Line8ce8Group12(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ce8.texts, 1, 12, data_020c8ce8.count);
}
CLEAN_AS(func_0201fe6c, VillagerTalk_Line8ce8Group12)

/* func_0201fed0: two choices offered (messages 0x5a running data_021c234c and 0x6f running
 * data_021c231c, no cancel choice) with the reply data_020d9390; the talk's byte 0x18 set. */
void VillagerTalk_OfferChoices5a(VillagerTalk *talk)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0x5a, 0x5a, (int) (uintptr_t) data_021c234c);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0x6f, 0x6f, (int) (uintptr_t) data_021c231c);
    list.count = 2;
    list.cancel = -1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    func_0202da74(talk, data_020d9390);
    func_02068388(lines_talk(talk), 1);
}
CLEAN_AS(func_0201fed0, VillagerTalk_OfferChoices5a)

/* func_0201ff3c: group 7 of the set at 0x020c8ce8, the random part below 3. */
void VillagerTalk_Line8ce8Group7(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ce8.texts, 1, 7, 3);
}
CLEAN_AS(func_0201ff3c, VillagerTalk_Line8ce8Group7)

/* func_0201ffa0: group 2 of the set at 0x020c8ce8, and bit 6 of the memory set when there is
 * one. */
void VillagerTalk_Line8ce8Group2(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ce8.texts, 1, 2, data_020c8ce8.count);
    if (talk->memory != NULL) {
        VillagerMemoryEntry_SetBit6(lines_memory(talk));
    }
}
CLEAN_AS(func_0201ffa0, VillagerTalk_Line8ce8Group2)

/* func_02020014: VillagerTalk_StoreText, then the line of the table at data_021c22ec said. */
void VillagerTalk_StoreTextSay22ec(VillagerTalk *talk)
{
    VillagerTalk_StoreText(talk);
    lines_say(talk, data_021c22ec, 0);
}
CLEAN_AS(func_02020014, VillagerTalk_StoreTextSay22ec)

/* func_0202006c: when the screen gave a text (GroupParams_C4CIs1), its first 10 units become
 * the text at 0x2a of the villager's memory of the player; without a memory, of the memory the
 * villager has of the current player (VillagerMemory_SetText2A). */
void VillagerTalk_StoreText(VillagerTalk *talk)
{
    if (!GroupParams_C4CIs1()) {
        return;
    }
    u8 *record = lines_record(talk);
    if (talk->memory != NULL) {
        u16 *text = GroupParams_Text();
        VillagerMemoryEntry_SetText2A(lines_memory(talk), text, 10);
    } else {
        u16 *text = GroupParams_Text();
        DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
        VillagerMemory_SetText2A(record, text, 10, player);
    }
}
CLEAN_AS(func_0202006c, VillagerTalk_StoreText)

/* func_020200cc: lines_show_text, then data_020d9310. */
void VillagerTalk_ShowText9310(VillagerTalk *talk, int event)
{
    (void) event;
    lines_show_text(talk, data_020d9310);
}
CLEAN_AS(func_020200cc, VillagerTalk_ShowText9310)

/* func_02020104: a line of the set at 0x020c8ce8, its count the lines per group, group 0. */
void VillagerTalk_Line8ce8(VillagerTalk *talk, VillagerTalkLine *out)
{
    lines_draw(talk, out, data_020c8ce8.texts, data_020c8ce8.count, 0, 0);
}
CLEAN_AS(func_02020104, VillagerTalk_Line8ce8)

/* func_02020168: unless func_02020a5c says a line (then the player is only noted), before the
 * talk of the day the table data_021c22d4, after it data_021c2304 three times in ten (a random
 * number below 100 under 30) and data_021c2364 otherwise; the player is noted, then the
 * table's line function writes the line. */
void VillagerTalk_LineRandom22d4(VillagerTalk *talk, VillagerTalkLine *out)
{
    if (func_02020a5c(talk, out) != 0) {
        lines_note(talk, lines_record(talk));
        return;
    }
    if (!lines_talked_today(talk)) {
        func_0202da88(talk, data_021c22d4);
    } else if ((int) func_020644cc(100) < 30) {
        func_0202da88(talk, data_021c2304);
    } else {
        func_0202da88(talk, data_021c2364);
    }
    lines_note(talk, lines_record(talk));
    if (talk->line.function != 0) {
        lines_call(&talk->line, talk, out);
    }
}
CLEAN_AS(func_02020168, VillagerTalk_LineRandom22d4)

/* func_02020234: the player noted. */
void VillagerTalk_NoteMemoryOnEvent(VillagerTalk *talk, void *event)
{
    (void) event;
    lines_note(talk, lines_record(talk));
}
CLEAN_AS(func_02020234, VillagerTalk_NoteMemoryOnEvent)

/* func_02020268: unless func_02020a5c says a line, a line of the set at 0x020c8c68 (its count
 * the lines per group) by the clock, on a random bit: on 0 by the hour, group 0 at 19, 1 at
 * 20 and 21, else 2; on 1 by the week of the month (days 1-7 are week 0), one less from the
 * third week when the month has a fifth Saturday (Calendar_NthWeekday), week 5 and later
 * counted as 0, plus 3. Either way data_020d8e88 is run at the last message. The villager is
 * the one of the talk on entry. */
void VillagerTalk_LineByCalendar(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = lines_record(talk);
    if (func_02020a5c(talk, out) == 0) {
        DateTime now = {0};
        unsigned int group = func_020644cc(10) & 1;
        DateTime_Now(&now);
        if (group == 0) {
            if (now.hour < 19) {
                group = 2;
            } else if (now.hour < 20) {
                group = 0;
            } else if (now.hour < 22) {
                group = 1;
            } else {
                group = 2;
            }
        } else {
            group = now.day != 0 ? (unsigned int) (now.day - 1) / 7 : 0;
            if (Calendar_NthWeekday(now.year, now.month, 6, 5) != -1 && group >= 2) {
                group--;
            }
            if (group >= 5) {
                group = 0;
            }
            group += 3;
        }
        lines_draw_for(talk, out, record, data_020c8c68.texts, data_020c8c68.count, (int) group, 0);
    }
    talk->on_last_message = data_020d8e88;
}
CLEAN_AS(func_02020268, VillagerTalk_LineByCalendar)

/* func_02020360: two choices offered with cancel choice 1: the messages of data_020c8928
 * running data_021c1e14 and those of data_020c8924 running data_021c1d6c; the reply
 * data_020d91d8; the talk's byte 0x18 set. The list is not cleared first. */
void VillagerTalk_OfferChoices1e14(VillagerTalk *talk)
{
    TalkChoiceList list;
    TalkChoices_SetFrom((int) (uintptr_t) talk, &list, 0, data_020c8928, (u32) (uintptr_t) data_021c1e14);
    TalkChoices_SetFrom((int) (uintptr_t) talk, &list, 1, data_020c8924, (u32) (uintptr_t) data_021c1d6c);
    list.count = 2;
    list.cancel = 1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    func_0202da74(talk, data_020d91d8);
    func_02068388(lines_talk(talk), 1);
}
CLEAN_AS(func_02020360, VillagerTalk_OfferChoices1e14)
