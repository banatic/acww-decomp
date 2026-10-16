/* A town villager's nickname for the player and its catchphrase, in the talk scene
 * (villager_talk_nickname.h). */
#include "villager_talk_nickname.h"

#include "calendar.h"
#include "clean.h"
#include "group_params.h"
#include "message_reader.h"
#include "npc_id.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_command.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_town.h"

/* The villager scene object's town record (town_villager.h), and a byte that picks the
 * catchphrase's message. */
#define VILLAGER_TALK_NICKNAME_RECORD 0x830
#define VILLAGER_TALK_NICKNAME_HABIT_BYTE 0x824

/* The nickname's length in characters, and the text screen it is typed on. */
#define VILLAGER_TALK_NICKNAME_CHARS 6
#define VILLAGER_TALK_NICKNAME_TEXT_MODE 0x11
#define VILLAGER_TALK_NICKNAME_TEXT_BYTES 0x40
/* The fondness from which the villager offers to change the nickname. */
#define VILLAGER_TALK_NICKNAME_FOND 0x40

/* The nickname messages: eight per personality from a base by personality. */
#define VILLAGER_TALK_NICKNAME_MESSAGES 8
#define VILLAGER_TALK_NICKNAME_PERSONALITIES 6

/* A text set of the talk lines: its texts and the lines a group has. */
typedef struct VillagerTalkNicknameTexts {
    u32 texts;
    u8 count;
} VillagerTalkNicknameTexts;

/* A label the talk shows (the text of a name, 32 bytes). */
typedef struct VillagerTalkNicknameLabel {
    u32 words[8];
} VillagerTalkNicknameLabel;

extern const VillagerTalkNicknameTexts data_020c8af0; /* "etc_connect" */
extern const VillagerTalkNicknameTexts data_020c8b20; /* "ap_nickn" */
extern const VillagerTalkNicknameTexts data_020c8b18; /* "ap_habit" */
extern const u8 data_020c8968[VILLAGER_TALK_NICKNAME_PERSONALITIES];

/* The text typed on the text screen. */
extern u8 data_021c1e84[VILLAGER_TALK_NICKNAME_TEXT_BYTES];

/* Tables of three member pointers for 0xb0 to 0xc0, which the choices also run. */
extern const MemberPointer data_021c27ac[3];
extern const MemberPointer data_021c27c4[3];
extern const MemberPointer data_021c27dc[3];
extern const MemberPointer data_021c27f4[3];
extern const MemberPointer data_021c280c[3];
extern const MemberPointer data_021c2824[3];

/* Member pointer constants the functions here set. */
extern const MemberPointer data_020d9178; /* VillagerTalkNickname_Keep */
extern const MemberPointer data_020d93d8; /* the reply func_020288bc */
extern const MemberPointer data_020d8f68; /* the reply func_020288bc */
extern const MemberPointer data_020d8f88; /* the reply func_020288bc */

extern VillagerTown data_021e5a2c; /* the town's villagers */

/* The scene's member setters: the three at 0xb0 from a table, the reply, the member run at the
 * command's end. */
extern void func_0202da88(VillagerTalk *talk, const MemberPointer *table);
extern void func_0202da74(VillagerTalk *talk, MemberPointer reply);
extern void func_0202dbf0(VillagerTalk *talk, MemberPointer next);
/* A line drawn for the personality (villager_talk.h). */
extern int func_0202da38(VillagerTalk *talk, char *text, u8 *message, int size, int personality, int texts, int per_group,
                         int group, int range);
/* The talk: a label put into its slot, its message and text set (only while it is on the
 * message data_021f43f8, func_02068484), its byte 0x18 set. */
extern void func_02068404(u8 *talk, int slot, VillagerTalkNicknameLabel *label);
extern void func_0206844c(u8 *talk, const u8 *message, int text);
extern int func_02068484(u8 *talk, const u8 *message, int text);
extern void func_02068388(u8 *talk, int cond);
/* A label constructed and destructed; a player's name put into one; one copied. */
extern void *func_02094fd4(VillagerTalkNicknameLabel *label);
extern void *func_02094fbc(VillagerTalkNicknameLabel *label);
extern void *func_02095074(const DesignCreator *player, VillagerTalkNicknameLabel *label);
extern void *func_020a8bb8(VillagerTalkNicknameLabel *label, const VillagerTalkNicknameLabel *from);
/* A random number below `bound`. */
extern int func_020644cc(int bound);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static u8 *nickname_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static u8 *nickname_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_NICKNAME_RECORD);
}

static VillagerMemory *nickname_memory(const VillagerTalk *talk)
{
    return (VillagerMemory *) (void *) talk->memory;
}

static int nickname_personality(const VillagerTalk *talk)
{
    return NpcId_Personality(TownVillager_NpcId(nickname_record(talk)));
}

/* `out` names the talk's text and message. */
static void nickname_name(VillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* The text of `texts` for the villager's personality into the talk's text, the message
 * `message`; `out` names them. */
static void nickname_resource_line(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkNicknameTexts *texts,
                                   u8 message)
{
    int personality = nickname_personality(talk);
    Personality_FormatResourceName(talk->text, VILLAGER_TALK_TEXT_SIZE, (const char *) (uintptr_t) texts->texts, personality);
    talk->message = message;
    nickname_name(talk, out);
}

/* The line of the line function at 0xb0, when there is one.
 * REQUIRES: a line function set (the original then hands on an unset line). */
static VillagerTalkLine nickname_set_line(VillagerTalk *talk)
{
    VillagerTalkLine line = {0};
    if (talk->line.function != 0) {
        void *self = MemberPointer_Object(&talk->line, talk);
        ((void (*)(void *, VillagerTalkLine *))(uintptr_t) MemberPointer_Code(&talk->line, self))(self, &line);
    }
    return line;
}

/* Two choices (messages `first` and `second`, running the tables `first_runs` and
 * `second_runs`, no cancel choice) with the reply `reply`; the talk's byte 0x18 set. */
static void nickname_offer(VillagerTalk *talk, int first, const MemberPointer *first_runs, int second,
                           const MemberPointer *second_runs, MemberPointer reply)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, (u8) first, (u8) first, (int) (uintptr_t) first_runs);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, (u8) second, (u8) second, (int) (uintptr_t) second_runs);
    list.count = 2;
    list.cancel = -1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    func_0202da74(talk, reply);
    func_02068388(nickname_talk(talk), 1);
}

/* func_0202a5e8: a line of the set "etc_connect" (group 0) for the villager's personality. */
void VillagerTalkNickname_LineConnect(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, nickname_personality(talk),
                  (int) data_020c8af0.texts, data_020c8af0.count, 0, 0);
    nickname_name(talk, out);
}
CLEAN_AS(func_0202a5e8, VillagerTalkNickname_LineConnect)

/* func_0202a64c: the "ap_nickn" text for the personality, message 1. */
void VillagerTalkNickname_Line1(VillagerTalk *talk, VillagerTalkLine *out)
{
    nickname_resource_line(talk, out, &data_020c8b20, 1);
}
CLEAN_AS(func_0202a64c, VillagerTalkNickname_Line1)

/* func_0202a6a4: the "ap_nickn" text for the personality, message 5. */
void VillagerTalkNickname_Line5(VillagerTalk *talk, VillagerTalkLine *out)
{
    nickname_resource_line(talk, out, &data_020c8b20, 5);
}
CLEAN_AS(func_0202a6a4, VillagerTalkNickname_Line5)

/* func_0202a6fc: in the place of a line, the text screen asked for (`unused` is left alone). */
void VillagerTalkNickname_AskTextLine(VillagerTalk *talk, VillagerTalkLine *unused)
{
    (void) unused;
    VillagerTalkNickname_AskText(talk, 0);
}
CLEAN_AS(func_0202a6fc, VillagerTalkNickname_AskTextLine)

/* func_0202a708: two choices: 0x4a running data_021c280c and 0x49 running data_021c27f4, the
 * reply data_020d93d8. */
void VillagerTalkNickname_OfferRetype(VillagerTalk *talk)
{
    nickname_offer(talk, 0x4a, data_021c280c, 0x49, data_021c27f4, data_020d93d8);
}
CLEAN_AS(func_0202a708, VillagerTalkNickname_OfferRetype)

/* func_0202a774: the "ap_nickn" text for the personality, message 4. */
void VillagerTalkNickname_Line4(VillagerTalk *talk, VillagerTalkLine *out)
{
    nickname_resource_line(talk, out, &data_020c8b20, 4);
}
CLEAN_AS(func_0202a774, VillagerTalkNickname_Line4)

/* func_0202a7cc: after the text screen: when it was confirmed (GroupParams_C4CIs1), the talk's
 * line functions set from data_021c27dc and the six characters typed kept as the nickname (in
 * the talk's memory when it is in use, else in a memory of the current player the villager
 * makes, kept at 0x12c), then shown in the talk's slot 0. Then the line of the line function
 * said. */
void VillagerTalkNickname_Keep(VillagerTalk *talk)
{
    if (GroupParams_C4CIs1() != 0) {
        u8 *record = nickname_record(talk);
        func_0202da88(talk, data_021c27dc);
        if (nickname_memory(talk) != NULL && VillagerMemoryEntry_InUse(nickname_memory(talk)) != 0) {
            VillagerMemoryEntry_SetNicknameChars(nickname_memory(talk), GroupParams_Text(), VILLAGER_TALK_NICKNAME_CHARS);
        } else {
            const u16 *chars = GroupParams_Text();
            const DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
            talk->memory =
                (u8 *) (void *) VillagerMemory_SetNicknameChars(record, chars, VILLAGER_TALK_NICKNAME_CHARS, player);
        }
        if (nickname_memory(talk) != NULL) {
            VillagerTalkNicknameLabel label;
            func_02094fd4(&label);
            VillagerMemoryEntry_NicknameToLabel(nickname_memory(talk), &label);
            func_02068404(nickname_talk(talk), 0, &label);
            func_02094fbc(&label);
        }
    }
    VillagerTalkLine line = nickname_set_line(talk);
    u8 message = line.message;
    func_0206844c(nickname_talk(talk), &message, (int) line.text);
}
CLEAN_AS(func_0202a7cc, VillagerTalkNickname_Keep)

/* func_0202a8a4: the text screen (mode 0x11, six characters into data_021c1e84, cleared first)
 * asked for, with VillagerTalkNickname_Keep at the command's end. */
void VillagerTalkNickname_AskText(VillagerTalk *talk, int unused)
{
    (void) unused;
    MI_CpuFill8(data_021c1e84, 0, VILLAGER_TALK_NICKNAME_TEXT_BYTES);
    SceneCommand_SetScreenText(&talk->scene, VILLAGER_TALK_NICKNAME_TEXT_MODE, (u32) (uintptr_t) data_021c1e84,
                               VILLAGER_TALK_NICKNAME_CHARS, 0);
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_MODE_TEXT);
    func_0202dbf0(talk, data_020d9178);
}
CLEAN_AS(func_0202a8a4, VillagerTalkNickname_AskText)

/* func_0202a8e8: the "ap_nickn" text for the personality, message 3. */
void VillagerTalkNickname_Line3(VillagerTalk *talk, VillagerTalkLine *out)
{
    nickname_resource_line(talk, out, &data_020c8b20, 3);
}
CLEAN_AS(func_0202a8e8, VillagerTalkNickname_Line3)

/* func_0202a940: when the villager's memory of the player is at least 0x40 fond, two choices
 * (0x47 running data_021c27c4, 0x48 running data_021c280c) with the reply data_020d8f68;
 * otherwise the line of the table data_021c280c said while the talk is on its message. */
void VillagerTalkNickname_OfferIfFond(VillagerTalk *talk)
{
    if (nickname_memory(talk) != NULL && VillagerMemoryEntry_Fondness(nickname_memory(talk)) >= VILLAGER_TALK_NICKNAME_FOND) {
        nickname_offer(talk, 0x47, data_021c27c4, 0x48, data_021c280c, data_020d8f68);
    } else {
        func_0202da88(talk, data_021c280c);
        VillagerTalkLine line = nickname_set_line(talk);
        u8 message = line.message;
        func_02068484(nickname_talk(talk), &message, (int) line.text);
    }
}
CLEAN_AS(func_0202a940, VillagerTalkNickname_OfferIfFond)

/* func_0202aa04: a nickname picked for the current player (VillagerTalkNickname_Load with the
 * player's name, the name itself when none loads) and kept: in the talk's memory, with the
 * town's date at 0x404c set to today, or else in a memory of the player the villager makes;
 * then shown in the talk's slot 0. */
void VillagerTalkNickname_Pick(VillagerTalk *talk)
{
    VillagerTalkNicknameLabel nickname;
    VillagerTalkNicknameLabel name;
    const DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
    func_02094fd4(&nickname);
    func_02094fd4(&name);
    func_02095074(player, &name);
    if (VillagerTalkNickname_Load(&nickname, &name, (unsigned int) nickname_personality(talk)) == 0) {
        func_020a8bb8(&nickname, &name);
    }
    if (nickname_memory(talk) != NULL) {
        Date today;
        Calendar_Today(&today);
        VillagerMemoryEntry_SetNickname(nickname_memory(talk), &nickname);
        VillagerTown_SetDate404C(&data_021e5a2c, &today);
    } else {
        VillagerMemory_SetNickname(nickname_record(talk), &nickname, player);
    }
    func_02068404(nickname_talk(talk), 0, &nickname);
    func_02094fbc(&name);
    func_02094fbc(&nickname);
}
CLEAN_AS(func_0202aa04, VillagerTalkNickname_Pick)

/* func_0202aab0: one of the eight nickname messages of `personality` (from the base
 * data_020c8968, 0 for none) loaded into `text` with `name`, the eight tried in a random order
 * until one loads; whether one did. */
int VillagerTalkNickname_Load(void *text, void *name, unsigned int personality)
{
    int base = personality < VILLAGER_TALK_NICKNAME_PERSONALITIES ? data_020c8968[personality] : 0;
    u8 untried = 0xff;
    int left = VILLAGER_TALK_NICKNAME_MESSAGES;
    for (int tries = 0; tries < VILLAGER_TALK_NICKNAME_MESSAGES; tries++) {
        int pick = func_020644cc(left);
        for (int i = 0; i < VILLAGER_TALK_NICKNAME_MESSAGES; i++) {
            if (((untried >> i) & 1) == 0) {
                continue;
            }
            if (pick == 0) {
                u8 message = (u8) (i + base);
                if (MessageReader_LoadNickname(text, name, &message) != 0) {
                    return 1;
                }
                untried = (u8) (untried & ~(1u << i));
                break;
            }
            pick--;
        }
        left--;
    }
    return 0;
}
CLEAN_AS(func_0202aab0, VillagerTalkNickname_Load)

/* func_0202ab30: the "ap_nickn" text for the personality, message 2. */
void VillagerTalkNickname_Line2(VillagerTalk *talk, VillagerTalkLine *out)
{
    nickname_resource_line(talk, out, &data_020c8b20, 2);
}
CLEAN_AS(func_0202ab30, VillagerTalkNickname_Line2)

/* func_0202ab88: two choices: 0x45 running data_021c27ac and 0x46 running data_021c2824, the
 * reply data_020d8f88. */
void VillagerTalkNickname_OfferChange(VillagerTalk *talk)
{
    nickname_offer(talk, 0x45, data_021c27ac, 0x46, data_021c2824, data_020d8f88);
}
CLEAN_AS(func_0202ab88, VillagerTalkNickname_OfferChange)

/* func_0202abf4: the "ap_habit" text (the catchphrase) for the personality, message 2 when the
 * villager scene object's byte 0x824 is 0, else 3. */
void VillagerTalkNickname_LineHabit(VillagerTalk *talk, VillagerTalkLine *out)
{
    int personality = nickname_personality(talk);
    Personality_FormatResourceName(talk->text, VILLAGER_TALK_TEXT_SIZE, (const char *) (uintptr_t) data_020c8b18.texts,
                                   personality);
    talk->message = talk->villager[VILLAGER_TALK_NICKNAME_HABIT_BYTE] == 0 ? 2 : 3;
    nickname_name(talk, out);
}
CLEAN_AS(func_0202abf4, VillagerTalkNickname_LineHabit)

/* The catchphrase typed on the text screen (VillagerTalkNickname_AskHabitText) and the text of
 * 10 characters the villager's memory of the player keeps at 0x3e, picked by the villager
 * scene object's byte 0x824: 0 for the catchphrase, else the text. */
#include "villager_catchphrase.h"

#define VILLAGER_TALK_NICKNAME_HABIT_CHARS 4
#define VILLAGER_TALK_NICKNAME_HABIT_MODE 0x15
#define VILLAGER_TALK_NICKNAME_TEXT3E_CHARS 10
#define VILLAGER_TALK_NICKNAME_TEXT3E_MODE 0x16

/* Tables of three member pointers for 0xb0 to 0xc0, which the choices also run. */
extern const MemberPointer data_021c2734[3];
extern const MemberPointer data_021c274c[3];
extern const MemberPointer data_021c2764[3];
extern const MemberPointer data_021c271c[3];
extern const MemberPointer data_021c277c[3];

/* Member pointer constants the functions here set. */
extern const MemberPointer data_020d9268; /* the reply func_020288bc */
extern const MemberPointer data_020d8f78; /* the reply func_020288bc */
extern const MemberPointer data_020d9260; /* VillagerTalkNickname_KeepHabit */

/* Two choices of ranges of messages (`first` to `first_last` running the table `first_runs`,
 * `second` to `second_last` running `second_runs`, no cancel choice) with the reply `reply`;
 * the talk's byte 0x18 set. */
static void nickname_offer_ranges(VillagerTalk *talk, int first, int first_last, const MemberPointer *first_runs, int second,
                                  int second_last, const MemberPointer *second_runs, MemberPointer reply)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, (u8) first, (u8) first_last, (int) (uintptr_t) first_runs);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, (u8) second, (u8) second_last, (int) (uintptr_t) second_runs);
    list.count = 2;
    list.cancel = -1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    func_0202da74(talk, reply);
    func_02068388(nickname_talk(talk), 1);
}

/* func_0202ac64: a line of the set "ap_habit" (five lines a group, the group the low bit of the
 * villager scene object's byte 0x824) with 7 added to its message; `out` names it, and the bit
 * is then flipped, so the next line comes from the other group. */
void VillagerTalkNickname_LineHabitFlip(VillagerTalk *talk, VillagerTalkLine *out)
{
    int personality = nickname_personality(talk);
    int group = talk->villager[VILLAGER_TALK_NICKNAME_HABIT_BYTE] & 1;
    func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, personality, (int) data_020c8b18.texts, 5, group,
                  data_020c8b18.count);
    talk->message += 7;
    nickname_name(talk, out);
    talk->villager[VILLAGER_TALK_NICKNAME_HABIT_BYTE] = (u8) ((talk->villager[VILLAGER_TALK_NICKNAME_HABIT_BYTE] + 1) & 1);
}
CLEAN_AS(func_0202ac64, VillagerTalkNickname_LineHabitFlip)

/* func_0202acec: two choices: 0x4a running data_021c2764 and 0x49 running data_021c2734, the
 * reply data_020d9268. */
void VillagerTalkNickname_OfferRetypeHabit(VillagerTalk *talk)
{
    nickname_offer(talk, 0x4a, data_021c2764, 0x49, data_021c2734, data_020d9268);
}
CLEAN_AS(func_0202acec, VillagerTalkNickname_OfferRetypeHabit)

/* func_0202ad58: the "ap_habit" text for the personality, message 6 when the villager scene
 * object's byte 0x824 is 0, else 11. */
void VillagerTalkNickname_LineHabit6(VillagerTalk *talk, VillagerTalkLine *out)
{
    int personality = nickname_personality(talk);
    Personality_FormatResourceName(talk->text, VILLAGER_TALK_TEXT_SIZE, (const char *) (uintptr_t) data_020c8b18.texts,
                                   personality);
    talk->message = talk->villager[VILLAGER_TALK_NICKNAME_HABIT_BYTE] == 0 ? 6 : 11;
    nickname_name(talk, out);
}
CLEAN_AS(func_0202ad58, VillagerTalkNickname_LineHabit6)

/* func_0202adc8: in the place of a line, the text screen of VillagerTalkNickname_AskHabitText
 * asked for (`unused` is left alone). */
void VillagerTalkNickname_AskHabitTextLine(VillagerTalk *talk, VillagerTalkLine *unused)
{
    (void) unused;
    VillagerTalkNickname_AskHabitText(talk, 0);
}
CLEAN_AS(func_0202adc8, VillagerTalkNickname_AskHabitTextLine)

/* func_0202add4: after the text screen: when it was confirmed (GroupParams_C4CIs1), the talk's
 * line functions set from data_021c274c and the characters typed kept: for byte 0x824 at 0 the
 * four as the villager's catchphrase, else ten as the text 0x3e of the talk's memory when it
 * is in use, or of a memory of the current player the villager makes. Then the line of the
 * line function said. The town record is the one of the talk on entry. */
void VillagerTalkNickname_KeepHabit(VillagerTalk *talk)
{
    if (GroupParams_C4CIs1() != 0) {
        u8 *record = nickname_record(talk);
        func_0202da88(talk, data_021c274c);
        if (talk->villager[VILLAGER_TALK_NICKNAME_HABIT_BYTE] == 0) {
            VillagerCatchphrase_Set(record, GroupParams_Text(), VILLAGER_TALK_NICKNAME_HABIT_CHARS);
        } else if (nickname_memory(talk) != NULL && VillagerMemoryEntry_InUse(nickname_memory(talk)) != 0) {
            VillagerMemoryEntry_SetText3E(nickname_memory(talk), GroupParams_Text(), VILLAGER_TALK_NICKNAME_TEXT3E_CHARS);
        } else {
            const u16 *chars = GroupParams_Text();
            const DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
            VillagerMemory_SetText3E(record, chars, VILLAGER_TALK_NICKNAME_TEXT3E_CHARS, player);
        }
    }
    VillagerTalkLine line = nickname_set_line(talk);
    u8 message = line.message;
    func_0206844c(nickname_talk(talk), &message, (int) line.text);
}
CLEAN_AS(func_0202add4, VillagerTalkNickname_KeepHabit)

/* func_0202aea0: the text screen asked for, into data_021c1e84 (cleared first): for byte 0x824
 * at 0 mode 0x15 with four characters (the catchphrase), else mode 0x16 with ten; with
 * VillagerTalkNickname_KeepHabit at the command's end. */
void VillagerTalkNickname_AskHabitText(VillagerTalk *talk, int unused)
{
    (void) unused;
    MI_CpuFill8(data_021c1e84, 0, VILLAGER_TALK_NICKNAME_TEXT_BYTES);
    if (talk->villager[VILLAGER_TALK_NICKNAME_HABIT_BYTE] == 0) {
        SceneCommand_SetScreenText(&talk->scene, VILLAGER_TALK_NICKNAME_HABIT_MODE, (u32) (uintptr_t) data_021c1e84,
                                   VILLAGER_TALK_NICKNAME_HABIT_CHARS, 0);
    } else {
        SceneCommand_SetScreenText(&talk->scene, VILLAGER_TALK_NICKNAME_TEXT3E_MODE, (u32) (uintptr_t) data_021c1e84,
                                   VILLAGER_TALK_NICKNAME_TEXT3E_CHARS, 0);
    }
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_MODE_TEXT);
    func_0202dbf0(talk, data_020d9260);
}
CLEAN_AS(func_0202aea0, VillagerTalkNickname_AskHabitText)

/* func_0202af08: a line of the set "ap_habit" (four lines a group, group 1). */
void VillagerTalkNickname_LineHabitGroup1(VillagerTalk *talk, VillagerTalkLine *out)
{
    func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, nickname_personality(talk),
                  (int) data_020c8b18.texts, 4, 1, data_020c8b18.count);
    nickname_name(talk, out);
}
CLEAN_AS(func_0202af08, VillagerTalkNickname_LineHabitGroup1)

/* func_0202af6c: two choices: messages 0x4b to 0x4f running data_021c271c and 0x50 to 0x54
 * running data_021c277c, the reply data_020d8f78. */
void VillagerTalkNickname_OfferHabit(VillagerTalk *talk)
{
    nickname_offer_ranges(talk, 0x4b, 0x4f, data_021c271c, 0x50, 0x54, data_021c277c, data_020d8f78);
}
CLEAN_AS(func_0202af6c, VillagerTalkNickname_OfferHabit)
