/* The approaches of a town villager's talk scene (villager_talk_approach.h). */
#include "villager_talk_approach.h"

#include "calendar.h"
#include "clean.h"
#include "current_pockets.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "room_score.h"
#include "scene_base.h"
#include "town_villager.h"
#include "villager_items.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_mode_record.h"
#include "villager_object.h"
#include "villager_status.h"
#include "villager_talk_greeting.h"
#include "villager_talk_topics.h"
#include "villager_town.h"
#include "item_traits.h"
#include "main_random.h"
#include "talk_item_draw.h"
#include "villager_talk_scene.h"

/* The villager scene object's town record (town_villager.h), and its byte that picks the group
 * of the catchphrase's lines. */
#define VILLAGER_TALK_APPROACH_RECORD 0x830
#define VILLAGER_TALK_APPROACH_HABIT_BYTE 0x824

#define VILLAGER_TALK_APPROACH_NO_ITEM 0xfff1
/* The item classes of the five modes of group 0 (insect, fish, kind item, clothes, furniture). */
#define VILLAGER_TALK_APPROACH_MODES 5
#define VILLAGER_TALK_APPROACH_POCKETS 15
/* What SceneBase_PutItemName and SceneBase_PutValue are told. */
#define VILLAGER_TALK_APPROACH_ITEM_KIND 7
#define VILLAGER_TALK_APPROACH_BELLS_FORMAT 10

/* A price: the worth times a random factor from 0xccd to 0x199a (4096ths). */
#define VILLAGER_TALK_APPROACH_FACTOR_BASE 0xccd
#define VILLAGER_TALK_APPROACH_SELL_MAX 3000
/* The fondness from which the villager offers its picture; the pictures of the 156 villagers
 * are the items from 0x47d8, four apart. */
#define VILLAGER_TALK_APPROACH_PICTURE_FOND 0x50
#define VILLAGER_TALK_APPROACH_PICTURE_FIRST 0x47d8
#define VILLAGER_TALK_APPROACH_PICTURES 0x9c

/* A text set of the talk lines: its texts and a count (of lines per group, or of the random
 * part). */
typedef struct VillagerTalkApproachTexts {
    u32 texts;
    u8 count;
} VillagerTalkApproachTexts;

extern const VillagerTalkApproachTexts data_020c8be8; /* "ap_sell" */
extern const VillagerTalkApproachTexts data_020c8a30; /* "ap_trade" */
extern const VillagerTalkApproachTexts data_020c89a0; /* "ap_buy" */
extern const VillagerTalkApproachTexts data_020c8ca8; /* "ap_present2" */
extern const VillagerTalkApproachTexts data_020c89e8; /* "ap_present1" */
extern const VillagerTalkApproachTexts data_020c89c8; /* "ap_mail" */
extern const VillagerTalkApproachTexts data_020c8b20; /* "ap_nickn" */
extern const VillagerTalkApproachTexts data_020c8b38; /* "ap_item" */
extern const VillagerTalkApproachTexts data_020c8b18; /* "ap_habit" */

/* The approaches' weights (10, 10, 10, 10, 14, 14, 8, 10, 14). */
extern const u8 data_020c8e68[VILLAGER_TALK_APPROACH_COUNT];
/* The item class of each mode of group 0 (CurrentPockets_MarkClass). */
extern const u32 data_020c8f38[VILLAGER_TALK_APPROACH_MODES];

/* The table of the nine approaches, filled once from constants (bit 0 of the guard). */
extern u32 data_021c1cfc;
extern MemberPointer data_021c1f4c[VILLAGER_TALK_APPROACH_COUNT];
extern const MemberPointer data_020d8ec8; /* VillagerTalkApproach_Catchphrase */
extern const MemberPointer data_020d8ea8; /* VillagerTalkApproach_Mail */
extern const MemberPointer data_020d8dd8; /* VillagerTalkApproach_Picture */
extern const MemberPointer data_020d8ed8; /* VillagerTalkApproach_Nickname */
extern const MemberPointer data_020d8de0; /* VillagerTalkApproach_Present1 */
extern const MemberPointer data_020d8dd0; /* VillagerTalkApproach_Present2 */
extern const MemberPointer data_020d8eb0; /* VillagerTalkApproach_Buy */
extern const MemberPointer data_020d9088; /* VillagerTalkApproach_Trade */
extern const MemberPointer data_020d9258; /* VillagerTalkApproach_Sell */

/* The five member functions VillagerTalkApproach_Line sets at 0x16c (events 12 to 16). */
extern const MemberPointer data_020d93a8;
extern const MemberPointer data_020d9160;
extern const MemberPointer data_020d9148;
extern const MemberPointer data_020d91e8;
extern const MemberPointer data_020d90d0;

/* Tables of three member pointers for 0xb0 to 0xc0. */
extern const MemberPointer data_021c2704[3];
extern const MemberPointer data_021c2794[3];

extern VillagerTown data_021e5a2c; /* the town's villagers */

/* The game's test of a memory VillagerTalkApproach_Mail hands VillagerTalkTopics_PickRandom
 * (VillagerTalkTopics_HoldsLetter). */
extern int func_02021d60(u8 *villager, VillagerMemory *memory);
/* The C library's copy as the SDK has it. */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static u8 *approach_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_APPROACH_RECORD);
}

static int approach_personality(u8 *record)
{
    return NpcId_Personality(TownVillager_NpcId(record));
}

static VillagerMemory *approach_memory(const VillagerTalk *talk)
{
    return (VillagerMemory *) (void *) talk->memory;
}

/* The villager's mode (villager_mode_record.h). */
static int approach_mode(u8 *record)
{
    return VillagerModeRecord_Mode(VillagerObject_RecordMode((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record)));
}

/* A line of `texts` (`per_group` lines a group, group `group`, the random part below `range`)
 * drawn for `personality` into the talk's text and message. */
static void approach_draw(VillagerTalk *talk, int personality, u32 texts, int per_group, int group, int range)
{
    VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE, personality, (int) texts, per_group,
                               group, range);
}

/* A line of `texts` (its count the lines a group, group 0) for the villager's personality. */
static void approach_say(VillagerTalk *talk, const VillagerTalkApproachTexts *texts)
{
    approach_draw(talk, approach_personality(approach_record(talk)), texts->texts, texts->count, 0, 0);
}

/* The gift at 0x19c: a random one of the villager's items (0x19e set), else when it has none
 * a random item of func_0202d694 (0x19e cleared). */
static void approach_gift_from_items(VillagerTalk *talk, u8 *record)
{
    u16 item;
    VillagerItems_Random(&item, record);
    talk->gift = item;
    if (talk->gift != VILLAGER_TALK_APPROACH_NO_ITEM) {
        talk->gift_from_items = 1;
    } else {
        u16 drawn;
        TalkItemDraw_OfKinds(&drawn);
        talk->gift = drawn;
        talk->gift_from_items = 0;
    }
}

/* The current player's bells, those of the bags in the pockets with them. */
static int approach_player_bells(void)
{
    return PlayerPockets_Bells(PlayerRecord_Pockets(PlayerRecords_Current()), 1);
}

/* func_0202afdc: the approach line. The table of the nine approaches filled once; the player
 * noted in the villager's memory; then approaches drawn by the weights (VillagerTalkTopics_Draw)
 * and run until one applies, one that does not taking no further part. A draw outside the nine
 * runs one of the first two at random instead (VillagerTalkTopics_Draw gives none, and the
 * first approach always applies). `out` names the talk's text and message; the talk's slots 4
 * and 6 get random words of the archives 3 and 4, slot 0 the item at 0x124 and slots 1 and 2 the
 * gift at 0x19c (when there are), and the five members at 0x16c are set. */
void VillagerTalkApproach_Line(VillagerTalk *talk, VillagerTalkLine *out)
{
    static const MemberPointer *const approaches[VILLAGER_TALK_APPROACH_COUNT] = {
        &data_020d8ec8, &data_020d8ea8, &data_020d8dd8, &data_020d8ed8, &data_020d8de0,
        &data_020d8dd0, &data_020d8eb0, &data_020d9088, &data_020d9258,
    };
    MemberTable_InitOnce(&data_021c1cfc, data_021c1f4c, approaches, VILLAGER_TALK_APPROACH_COUNT);

    u8 weights[VILLAGER_TALK_APPROACH_COUNT];
    MI_CpuCopy8(data_020c8e68, weights, VILLAGER_TALK_APPROACH_COUNT);
    VillagerTalkScene_NoteMemory(talk, &talk->memory, &talk->memory_index, approach_record(talk), 0);
    int applied = 0;
    while (applied == 0) {
        int which = VillagerTalkTopics_Draw(talk, weights, VILLAGER_TALK_APPROACH_COUNT);
        if (which >= 0 && which < VILLAGER_TALK_APPROACH_COUNT) {
            applied = MemberPointer_CallInt(&data_021c1f4c[which], talk);
            if (applied == 0) {
                weights[which] = 0;
            }
        } else {
            MemberPointer_CallInt(&data_021c1f4c[MainRandom_Below(2)], talk);
            break;
        }
    }
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;

    SceneBase *base = (SceneBase *) (void *) talk;
    VillagerTalkGreeting_PutRandomWord(talk, 4, 3);
    VillagerTalkGreeting_PutRandomWord(talk, 6, 4);
    if (talk->item != VILLAGER_TALK_APPROACH_NO_ITEM) {
        SceneBase_PutItemName(base, (int) (uintptr_t) &talk->item, 0, VILLAGER_TALK_APPROACH_ITEM_KIND);
    }
    if (talk->gift != VILLAGER_TALK_APPROACH_NO_ITEM) {
        SceneBase_PutItemName(base, (int) (uintptr_t) &talk->gift, 1, VILLAGER_TALK_APPROACH_ITEM_KIND);
        SceneBase_PutItemName(base, (int) (uintptr_t) &talk->gift, 2, VILLAGER_TALK_APPROACH_ITEM_KIND);
    }
    talk->events[0] = data_020d93a8;
    talk->events[1] = data_020d9160;
    talk->events[2] = data_020d9148;
    talk->events[3] = data_020d91e8;
    talk->events[4] = data_020d90d0;
}
CLEAN_AS(func_0202afdc, VillagerTalkApproach_Line)

/* func_0202b220 ("ap_sell"): the villager sells the player a gift. The villager's mode is read
 * (and not used). With a free pocket, the gift is one of the villager's items or a random one;
 * its price is the worth times the random factor, less three times RoomScore_HouseLowX when the
 * price is above that, rounded and at most 3000, and must be within the player's bells. The
 * price is kept at 0x1a0 and shown in the talk's slot 2. */
int VillagerTalkApproach_Sell(VillagerTalk *talk)
{
    u8 *record = approach_record(talk);
    (void) approach_mode(record);
    if (CurrentPockets_FreeSlot() == -1) {
        return 0;
    }
    approach_gift_from_items(talk, record);
    if (talk->gift == VILLAGER_TALK_APPROACH_NO_ITEM) {
        return 0;
    }

    int factor = MainRandom_BelowB(VILLAGER_TALK_APPROACH_FACTOR_BASE) + VILLAGER_TALK_APPROACH_FACTOR_BASE;
    int price = (factor * ItemTraits_Price(&talk->gift)) >> 12;
    int discount = 3 * RoomScore_HouseLowX();
    talk->bells = VillagerTalkApproach_RoundBells(price - (price > discount ? discount : 0));
    if (talk->bells > VILLAGER_TALK_APPROACH_SELL_MAX) {
        talk->bells = VILLAGER_TALK_APPROACH_SELL_MAX;
    }
    if (talk->bells > approach_player_bells()) {
        return 0;
    }

    approach_draw(talk, approach_personality(record), data_020c8be8.texts, data_020c8be8.count, 0, 0);
    SceneBase_PutValue((SceneBase *) (void *) talk, talk->bells, 2, VILLAGER_TALK_APPROACH_BELLS_FORMAT, 0, 0);
    return 1;
}
CLEAN_AS(func_0202b220, VillagerTalkApproach_Sell)

/* func_0202b354 ("ap_trade"): when the player has an item the villager's mode asks for (into
 * 0x124), the villager offers one of its items or a random one for it. */
int VillagerTalkApproach_Trade(VillagerTalk *talk)
{
    u8 *record = approach_record(talk);
    u16 wanted;
    VillagerTalkApproach_PickPocketItem(&wanted, (unsigned int) approach_mode(record));
    talk->item = wanted;
    if (talk->item == VILLAGER_TALK_APPROACH_NO_ITEM) {
        return 0;
    }
    approach_gift_from_items(talk, record);
    approach_draw(talk, approach_personality(record), data_020c8a30.texts, data_020c8a30.count, 0, 0);
    return 1;
}
CLEAN_AS(func_0202b354, VillagerTalkApproach_Trade)

/* func_0202b420 ("ap_buy"): when the player has an item the villager's mode asks for (into
 * 0x124), the villager offers to buy it: the worth times the random factor in 16384ths, plus
 * three times RoomScore_HouseLowX, rounded; kept at 0x1a0 and shown in the talk's slot 1.
 * QUIRK: the offer is dropped when it is more than the player's own bells. */
int VillagerTalkApproach_Buy(VillagerTalk *talk)
{
    u8 *record = approach_record(talk);
    u16 wanted;
    VillagerTalkApproach_PickPocketItem(&wanted, (unsigned int) approach_mode(record));
    talk->item = wanted;
    if (talk->item == VILLAGER_TALK_APPROACH_NO_ITEM) {
        return 0;
    }

    int factor = MainRandom_BelowB(VILLAGER_TALK_APPROACH_FACTOR_BASE) + VILLAGER_TALK_APPROACH_FACTOR_BASE;
    int worth = ItemTraits_Price(&talk->item);
    int scaled = worth * factor;
    int extra = 3 * RoomScore_HouseLowX();
    talk->bells = (scaled >> 14) + extra;
    talk->bells = VillagerTalkApproach_RoundBells(talk->bells);
    if (talk->bells > approach_player_bells()) {
        return 0;
    }

    approach_draw(talk, approach_personality(record), data_020c89a0.texts, data_020c89a0.count, 0, 0);
    SceneBase_PutValue((SceneBase *) (void *) talk, talk->bells, 1, VILLAGER_TALK_APPROACH_BELLS_FORMAT, 0, 0);
    return 1;
}
CLEAN_AS(func_0202b420, VillagerTalkApproach_Buy)

/* func_0202b510: bells rounded to the nearest ten, at least 10. */
int VillagerTalkApproach_RoundBells(int bells)
{
    int rounded = (bells + 5) / 10 * 10;
    return rounded < 10 ? 10 : rounded;
}
CLEAN_AS(func_0202b510, VillagerTalkApproach_RoundBells)

/* func_0202b52c: for a mode of group 0 (0-4), one of the current player's pockets holding an
 * item of the mode's class (data_020c8f38), drawn at random; its item into `*out`, 0xfff1 when
 * there is none or the mode is another. */
void VillagerTalkApproach_PickPocketItem(u16 *out, unsigned int mode)
{
    *out = VILLAGER_TALK_APPROACH_NO_ITEM;
    if (VillagerModeRecord_GroupOfMode(mode) != 0 || mode >= VILLAGER_TALK_APPROACH_MODES) {
        return;
    }
    PocketsMarks marks;
    if (CurrentPockets_MarkClass(&marks, (int) data_020c8f38[mode]) == 0) {
        return;
    }
    int pick = MainRandom_Below(marks.count);
    for (int slot = 0; slot < VILLAGER_TALK_APPROACH_POCKETS; slot++) {
        if (((marks.slots >> slot) & 1) == 0) {
            continue;
        }
        if (pick == 0) {
            *out = CurrentPockets_Item((u32) slot);
            return;
        }
        pick--;
    }
}
CLEAN_AS(func_0202b52c, VillagerTalkApproach_PickPocketItem)

/* func_0202b598 ("ap_present2"): with a free pocket, a random gift (func_0202d694). */
int VillagerTalkApproach_Present2(VillagerTalk *talk)
{
    if (CurrentPockets_FreeSlot() == -1) {
        return 0;
    }
    u16 item;
    TalkItemDraw_OfKinds(&item);
    talk->gift = item;
    talk->gift_from_items = 0;
    approach_say(talk, &data_020c8ca8);
    return 1;
}
CLEAN_AS(func_0202b598, VillagerTalkApproach_Present2)

/* func_0202b61c ("ap_present1"): with a free pocket, a gift of the villager's items, or a
 * random one when it has none. */
int VillagerTalkApproach_Present1(VillagerTalk *talk)
{
    if (CurrentPockets_FreeSlot() == -1) {
        return 0;
    }
    u8 *record = approach_record(talk);
    approach_gift_from_items(talk, record);
    approach_draw(talk, approach_personality(record), data_020c89e8.texts, data_020c89e8.count, 0, 0);
    return 1;
}
CLEAN_AS(func_0202b61c, VillagerTalkApproach_Present1)

/* func_0202b6c8 ("ap_mail"): among the villager's memories of other players than the current
 * one (VillagerMemory_ListOthers, up to eight), one of whom the villager holds a letter, kept
 * at 0x138; group 0 of the lines when there is one, else group 1. Always applies. */
int VillagerTalkApproach_Mail(VillagerTalk *talk)
{
    u8 *record = approach_record(talk);
    VillagerMemory *list[8];
    for (int i = 0; i < 8; i++) {
        list[i] = NULL;
    }
    int count = VillagerMemory_ListOthers(record, list, PlayerRecord_Player(PlayerRecords_Current()), 2);
    if (count > 0) {
        talk->record_138 = (u32) VillagerTalkTopics_PickRandom(record, list, count, func_02021d60);
    }
    int none = talk->record_138 == 0 ? 1 : 0;
    approach_draw(talk, approach_personality(approach_record(talk)), data_020c89c8.texts, data_020c89c8.count, none, 0);
    return 1;
}
CLEAN_AS(func_0202b6c8, VillagerTalkApproach_Mail)

/* func_0202b770 ("ap_nickn"): with a memory of the player that is not unfond, when the town's
 * date at 0x404c is far enough from today (VillagerTown_IsFarFromDate404C); the talk's line
 * functions then set from data_021c2794. */
int VillagerTalkApproach_Nickname(VillagerTalk *talk)
{
    Date today;
    Calendar_Today(&today);
    if (approach_memory(talk) == NULL || VillagerMemoryEntry_Fondness(approach_memory(talk)) < 0) {
        return 0;
    }
    if (VillagerTown_IsFarFromDate404C(&data_021e5a2c, &today) == 0) {
        return 0;
    }
    approach_draw(talk, approach_personality(approach_record(talk)), data_020c8b20.texts, data_020c8b20.count, 0, 0);
    VillagerTalkScene_SetLines(talk, data_021c2794);
    return 1;
}
CLEAN_AS(func_0202b770, VillagerTalkApproach_Nickname)

/* func_0202b800 ("ap_item"): with a memory of the player, the villager's picture. Group 0 of
 * the lines when it was given before (bit 4 of the memory), else 1 when the memory is at least
 * 0x50 fond and the player has a free pocket (bit 4 then set), 2 when the pockets are full, 3
 * when not fond enough. The gift at 0x19c is the villager's picture (0x47d8 for a villager
 * without a valid NpcId or a number of 156 or more). Says 0 only without a memory. */
int VillagerTalkApproach_Picture(VillagerTalk *talk)
{
    VillagerMemory *memory = approach_memory(talk);
    if (memory == NULL) {
        return 0;
    }
    int group = 0;
    if (VillagerMemoryEntry_Bit4(approach_memory(talk)) == 0) {
        if (VillagerMemoryEntry_Fondness(approach_memory(talk)) >= VILLAGER_TALK_APPROACH_PICTURE_FOND) {
            if (CurrentPockets_FreeSlot() != -1) {
                VillagerMemoryEntry_SetBit4(approach_memory(talk));
                group = 1;
            } else {
                group = 2;
            }
        } else {
            group = 3;
        }
    }
    approach_draw(talk, approach_personality(approach_record(talk)), data_020c8b38.texts, data_020c8b38.count, group, 0);

    unsigned int number = 0;
    if (NpcId_IsValid(TownVillager_NpcId(approach_record(talk))) != 0) {
        number = (unsigned int) NpcId_Number(TownVillager_NpcId(approach_record(talk)));
    }
    talk->gift = (u16) (number < VILLAGER_TALK_APPROACH_PICTURES ? VILLAGER_TALK_APPROACH_PICTURE_FIRST + number * 4
                                                                 : VILLAGER_TALK_APPROACH_PICTURE_FIRST);
    return 1;
}
CLEAN_AS(func_0202b800, VillagerTalkApproach_Picture)

/* func_0202b8dc ("ap_habit"): the catchphrase: nine lines a group, the group the low bit of the
 * villager scene object's byte 0x824; the talk's line functions then set from data_021c2704.
 * Always applies. */
int VillagerTalkApproach_Catchphrase(VillagerTalk *talk)
{
    int personality = approach_personality(approach_record(talk));
    int group = talk->villager[VILLAGER_TALK_APPROACH_HABIT_BYTE] & 1;
    approach_draw(talk, personality, data_020c8b18.texts, 9, group, data_020c8b18.count);
    VillagerTalkScene_SetLines(talk, data_021c2704);
    return 1;
}
CLEAN_AS(func_0202b8dc, VillagerTalkApproach_Catchphrase)
