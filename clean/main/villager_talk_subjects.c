/* More topics of a town villager's talk scene (villager_talk_subjects.h). */
#include "villager_talk_subjects.h"

#include <string.h>

#include "acre_map.h"
#include "acre_tile.h"
#include "clean.h"
#include "creature_weight.h"
#include "date_time.h"
#include "design.h"
#include "design_info.h"
#include "npc_id.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "town_villager.h"
#include "villager_mode_record.h"
#include "villager_object.h"
#include "villager_roster.h"
#include "villager_state.h"
#include "villager_status.h"
#include "creature_draw.h"
#include "insect_draw.h"
#include "player_id.h"
#include "villager_scene_held.h"
#include "villager_talk_greeting.h"
#include "villager_talk_scene.h"

/* The villager scene object's town record (town_villager.h), or 0, and its position (three
 * words: x, y, z). */
#define VILLAGER_TALK_SUBJECTS_OBJECT_RECORD 0x830
#define VILLAGER_TALK_SUBJECTS_OBJECT_POSITION 0x5c

#define VILLAGER_TALK_SUBJECTS_NO_ITEM 0xfff1
/* The members of the two tables of eight (by a kind of the villager's). */
#define VILLAGER_TALK_SUBJECTS_KINDS 8
/* The talk's slots VillagerTalkSubjects_SayLast fills. */
#define VILLAGER_TALK_SUBJECTS_SLOTS 6
/* The groups VillagerTalkSubjects_SayStateFlags draws among. */
#define VILLAGER_TALK_SUBJECTS_FLAG_GROUPS 7
/* The flag of an acre VillagerTalkSubjects_SayHoldingOnAcre asks for (AcreTile_AcreHasFlags). */
#define VILLAGER_TALK_SUBJECTS_ACRE_FLAG 8
/* A position in acres: the world position (fixed point, 12 bits) shifted by 17. */
#define VILLAGER_TALK_SUBJECTS_ACRE_SHIFT 17

/* The items. */
#define VILLAGER_TALK_SUBJECTS_ITEM_1380_FIRST 0x1380
#define VILLAGER_TALK_SUBJECTS_ITEM_1380_LAST 0x139f
#define VILLAGER_TALK_SUBJECTS_DESIGN_FIRST 0x12a8 /* clothes made from a design */
#define VILLAGER_TALK_SUBJECTS_DESIGN_LAST 0x12af
#define VILLAGER_TALK_SUBJECTS_FISH_FIRST 0x12e8
#define VILLAGER_TALK_SUBJECTS_FISH_LAST 0x131f
#define VILLAGER_TALK_SUBJECTS_INSECT_FIRST 0x12b0
#define VILLAGER_TALK_SUBJECTS_INSECT_LAST 0x12e7

/* The villager's modes (villager_house_items.h): an insect caught, a fish caught. */
#define VILLAGER_TALK_SUBJECTS_MODE_INSECT 0
#define VILLAGER_TALK_SUBJECTS_MODE_FISH 1
#define VILLAGER_TALK_SUBJECTS_MODE_5 5
/* No mode: the eight kinds go from 0 to 7 (VillagerModeRecord_IsKindMode). */
#define VILLAGER_TALK_SUBJECTS_NO_MODE 8

/* The places of the five weighted choices of a catch (func_0202cb70, func_0202d060). */
#define VILLAGER_TALK_SUBJECTS_CHOICES 5
/* The groups of a catch's line: three for each half of the choices. */
#define VILLAGER_TALK_SUBJECTS_CATCH_HALF 3
#define VILLAGER_TALK_SUBJECTS_CATCH_TIME_SLOTS 3
#define VILLAGER_TALK_SUBJECTS_CATCH_PLACES 2

/* What a catch is worked out into: the item, the date, which of the choices, two values. */
typedef struct VillagerTalkSubjectsCatch {
    u8 value_byte; /* 0x00: VillagerTalkSubjects_SayCatchB puts it into slot 3 */
    u8 end;        /* 0x01 */
    u16 item;      /* 0x02 */
    DateTime when; /* 0x04 */
    s32 choice;    /* 0x0c */
    s32 kind;      /* 0x10 */
    s32 value;     /* 0x14 */
} VillagerTalkSubjectsCatch;

/* The same for VillagerTalkSubjects_SayCatchA, whose item comes first. */
typedef struct VillagerTalkSubjectsCatchA {
    u16 item;      /* 0x00 */
    u8 unk_02[2];  /* 0x02 */
    DateTime when; /* 0x04 */
    s32 choice;    /* 0x0c */
    s32 kind;      /* 0x10 */
    s32 value;     /* 0x14 */
} VillagerTalkSubjectsCatchA;

/* The four halfwords VillagerTalkSubjects_SayFishWith1374 and _SayInsectWith1376 keep: the
 * item drawn (filled by func_0202cac4 or func_0202cfa8 from the first) and the held item. */
typedef struct VillagerTalkSubjectsDrawn {
    u16 item;   /* 0x00 */
    u16 held;   /* 0x02 */
    u16 unk[2]; /* 0x04 */
} VillagerTalkSubjectsDrawn;

static_assert(offsetof(VillagerTalkSubjectsCatch, choice) == 0x0c, "VillagerTalkSubjectsCatch choice");
static_assert(offsetof(VillagerTalkSubjectsCatch, value) == 0x14, "VillagerTalkSubjectsCatch value");
static_assert(offsetof(VillagerTalkSubjectsCatchA, value) == 0x14, "VillagerTalkSubjectsCatchA value");

/* The text sets. */
extern const VillagerTalkSubjectsTexts data_020c8cb0;
extern const VillagerTalkSubjectsTexts data_020c8cc0;
extern const VillagerTalkSubjectsTexts data_020c8cc8;
extern const VillagerTalkSubjectsTexts data_020c8c80;
extern const VillagerTalkSubjectsTexts data_020c8af8;
extern const VillagerTalkSubjectsTexts data_020c8d00;
extern const VillagerTalkSubjectsTexts data_020c8b08;
extern const VillagerTalkSubjectsTexts data_020c8a68;
extern const VillagerTalkSubjectsTexts data_020c8d28;
extern const VillagerTalkSubjectsTexts data_020c8d30;
extern const VillagerTalkSubjectsTexts data_020c8d40;
extern const VillagerTalkSubjectsTexts data_020c8b48;
extern const VillagerTalkSubjectsTexts data_020c8d70;
extern const VillagerTalkSubjectsTexts data_020c8a08;
extern const VillagerTalkSubjectsTexts data_020c8a10;
extern const VillagerTalkSubjectsTexts data_020c8b70;
extern const VillagerTalkSubjectsTexts data_020c8db0;
extern const VillagerTalkSubjectsTexts data_020c8dc0;
extern const VillagerTalkSubjectsTexts data_020c8a20;
extern const VillagerTalkSubjectsTexts data_020c8b88;

/* What VillagerTalkSubjects_SayLast puts into the talk's slots 0 to 5 (func_0202bd7c). */
extern const u8 data_020c8960[VILLAGER_TALK_SUBJECTS_SLOTS];
/* What the catch topics hand SceneBase_PutBytes in the place of the size. */
extern u8 data_020d9f74[];
extern u8 data_020d9f84[];

/* The member tables by the state entry's kind and by the villager's mode (filled once from
 * constants, bit 0 of the guard). */
extern u32 data_021c1cec;
extern MemberPointer data_021c1ec4[VILLAGER_TALK_SUBJECTS_KINDS];
extern const MemberPointer data_020d92d8;
extern const MemberPointer data_020d8fa8;
extern const MemberPointer data_020d92e0;
extern const MemberPointer data_020d9298;
extern const MemberPointer data_020d93a0;
extern const MemberPointer data_020d8fa0;
extern const MemberPointer data_020d91e0;
extern const MemberPointer data_020d9288;
extern u32 data_021c1d08;
extern MemberPointer data_021c1e44[VILLAGER_TALK_SUBJECTS_KINDS];
extern const MemberPointer data_020d9410;
extern const MemberPointer data_020d9400;
extern const MemberPointer data_020d93f0;
extern const MemberPointer data_020d93e8;
extern const MemberPointer data_020d93e0;
extern const MemberPointer data_020d93c8;
extern const MemberPointer data_020d93b8;
extern const MemberPointer data_020d93b0;

extern u8 data_020e54a8;              /* 0 or 1 */
extern AcreMap *data_021c80bc;        /* the town's map; null while there is none */
extern const NpcIdHead data_021dc7aa; /* the head at 2 of the state block data_021dc7a8 */

/* A fish or an insect for the date drawn into the halfword at `item` (0xfff1 or out of range
 * when none was found). */
extern void func_0202cac4(u16 *item);
extern void func_0202cfa8(u16 *item);

static u8 *subjects_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_SUBJECTS_OBJECT_RECORD);
}

static SceneBase *subjects_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

/* The line drawn for the personality of the talk's villager into the talk's text and
 * message. */
static void subjects_draw(VillagerTalk *talk, u32 texts, int per_group, int group, int range)
{
    VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE,
                               NpcId_Personality(TownVillager_NpcId(subjects_record(talk))), (int) texts, per_group, group,
                               range);
}

/* A line of a text set, its count the lines per group. */
static int subjects_say(VillagerTalk *talk, const VillagerTalkSubjectsTexts *texts, int group)
{
    subjects_draw(talk, texts->texts, texts->count, group, 0);
    return 1;
}

/* The villager's mode (its mode record, villager_mode_record.h). */
static int subjects_mode(u8 *record)
{
    return VillagerModeRecord_Mode(VillagerObject_RecordMode((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record)));
}

/* The item the villager holds (func_0202e118). */
static u16 subjects_held(VillagerTalk *talk)
{
    u16 item;
    VillagerSceneHeld_Item(&item, talk->villager);
    return item;
}

/* Whether the villager holds nothing or one of the items 0x1380-0x139f. */
static int subjects_holds_none_or_1380(u16 item)
{
    return item == VILLAGER_TALK_SUBJECTS_NO_ITEM ||
           (item >= VILLAGER_TALK_SUBJECTS_ITEM_1380_FIRST && item <= VILLAGER_TALK_SUBJECTS_ITEM_1380_LAST);
}

/* Whether two town heads are the same: the halfword and the 12 bytes after it. */
static int subjects_same_head(const NpcIdHead *a, const NpcIdHead *b)
{
    return a->id == b->id && memcmp(a->data, b->data, sizeof a->data) == 0;
}

/* func_020222dc: about the flags of the villager's state entry (none without a record or an
 * entry, nor while the entry's word 0x20 is negative): of the halfword 0x24, bits 0-4 count as
 * one choice and bits 5-10 as one each; a choice drawn among those set (VillagerRoster_PickBit,
 * 7 when none) is the group of a line of the set at 0x020c8cb0, its count the lines per group,
 * and the word 0x20 goes into the talk's slot 0 (format 6). */
int VillagerTalkSubjects_SayStateFlags(VillagerTalk *talk)
{
    VillagerState *entry = NULL;
    if (subjects_record(talk) != NULL) {
        entry = VillagerStatus_StateEntry(subjects_record(talk));
    }
    if (entry == NULL || (s32) entry->word_20 < 0) {
        return 0;
    }
    int value = (s32) entry->word_20;
    unsigned int flags = entry->half_24;
    unsigned int mask = 0;
    int count = 0;
    if ((flags & 0x1f) != 0) {
        mask |= 1;
        count++;
    }
    for (int bit = 1; bit < VILLAGER_TALK_SUBJECTS_FLAG_GROUPS; bit++) {
        if ((flags & (0x10u << bit)) != 0) {
            mask |= 1u << bit;
            count++;
        }
    }
    unsigned int group = (unsigned int) VillagerRoster_PickBit(mask, count, VILLAGER_TALK_SUBJECTS_FLAG_GROUPS);
    if (group >= VILLAGER_TALK_SUBJECTS_FLAG_GROUPS) {
        group = VILLAGER_TALK_SUBJECTS_FLAG_GROUPS;
    }
    subjects_draw(talk, data_020c8cb0.texts, data_020c8cb0.count, (int) group, 0);
    SceneBase_PutValue(subjects_base(talk), value, 0, 6, 0, 0);
    return 1;
}
CLEAN_AS(func_020222dc, VillagerTalkSubjects_SayStateFlags)

/* func_02022454: the topic drawn once no other applies: a line of the set at 0x020c8cc0 (its
 * count the lines per group, group 0), then the talk's slots 0 to 5 filled from
 * data_020c8960. */
int VillagerTalkSubjects_SayLast(VillagerTalk *talk)
{
    subjects_draw(talk, data_020c8cc0.texts, data_020c8cc0.count, 0, 0);
    for (int slot = 0; slot < VILLAGER_TALK_SUBJECTS_SLOTS; slot++) {
        VillagerTalkGreeting_PutRandomWord(talk, slot, data_020c8960[slot]);
    }
    return 1;
}
CLEAN_AS(func_02022454, VillagerTalkSubjects_SayLast)

/* func_020224c4: about the villager's clothes, while there is a current player: group 0 of the
 * set at 0x020c8cc8 (its count the lines per group) when they are not made from a design; for a
 * design's clothes (0x12a8-0x12af), by the design's creator: group 1 when it is the current
 * player, else, when they are not the same player (func_0209518c), group 2 when the creator's
 * town is the one at data_021dc7aa and 3 when not; the creator then goes into the talk's slots
 * 0 (name) and 1 (town). No line when the creator is the same player by func_0209518c but not
 * by town and name. */
int VillagerTalkSubjects_SayDesignClothes(VillagerTalk *talk)
{
    u8 *record = subjects_record(talk);
    u16 clothes = *TownVillager_Clothes(record);
    int group = -1;
    DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }

    if (player != NULL) {
        if (clothes >= VILLAGER_TALK_SUBJECTS_DESIGN_FIRST && clothes <= VILLAGER_TALK_SUBJECTS_DESIGN_LAST) {
            unsigned int design = (unsigned int) (uintptr_t) TownVillager_Design(record);
            DesignCreator *creator = DesignInfo_Creator((DesignInfo *) (uintptr_t) Design_Info(design));
            /* QUIRK: func_0209518c is asked a second time when the town and name match but it
             * says they are not the same player. */
            if (player->town_id == creator->town_id &&
                memcmp(player->town_name, creator->town_name, sizeof player->town_name) == 0 &&
                PlayerId_SamePlayer(player, creator) != 0) {
                group = 1;
            } else if (PlayerId_SamePlayer(player, creator) == 0) {
                group = subjects_same_head((const NpcIdHead *) PlayerId_Town(creator), &data_021dc7aa) ? 2 : 3;
            }
            if (group != -1) {
                SceneBase_PutNameAt10(subjects_base(talk), DesignInfo_Creator((DesignInfo *) (uintptr_t) Design_Info(design)),
                                      0);
                const NpcIdHead *town =
                    (const NpcIdHead *) (PlayerId_Town(DesignInfo_Creator((DesignInfo *) (uintptr_t) Design_Info(design))));
                SceneBase_PutNameAt2(subjects_base(talk), (unsigned int) (uintptr_t) town, 1);
            }
        } else {
            group = 0;
        }
    }

    if (group == -1) {
        return 0;
    }
    return subjects_say(talk, &data_020c8cc8, group);
}
CLEAN_AS(func_020224c4, VillagerTalkSubjects_SayDesignClothes)

/* func_0202261c: a line of the set at 0x020c8c80. */
int VillagerTalkSubjects_Say8c80(VillagerTalk *talk)
{
    return subjects_say(talk, &data_020c8c80, 0);
}
CLEAN_AS(func_0202261c, VillagerTalkSubjects_Say8c80)

/* func_02022674: with data_020e54a8 at 0, the member of a table of eight (data_021c1ec4) for
 * the kind in the byte 0x1c of the villager's state entry, when it is one of the eight; its
 * answer, else 0. */
int VillagerTalkSubjects_SayByStateKind(VillagerTalk *talk)
{
    static const MemberPointer *const members[VILLAGER_TALK_SUBJECTS_KINDS] = {
        &data_020d92d8, &data_020d8fa8, &data_020d92e0, &data_020d9298,
        &data_020d93a0, &data_020d8fa0, &data_020d91e0, &data_020d9288,
    };
    MemberTable_InitOnce(&data_021c1cec, data_021c1ec4, members, VILLAGER_TALK_SUBJECTS_KINDS);

    if (data_020e54a8 != 0) {
        return 0;
    }
    int kind = VillagerState_GetByte1C(VillagerStatus_StateEntry(subjects_record(talk)));
    if (VillagerModeRecord_IsKindMode((unsigned int) kind) == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&data_021c1ec4[kind], talk);
}
CLEAN_AS(func_02022674, VillagerTalkSubjects_SayByStateKind)

/* func_02022768: while the villager holds nothing or one of the items 0x1380-0x139f, the line
 * of the set at 0x020c8af8 for mode 7. */
int VillagerTalkSubjects_SayHolding8af8(VillagerTalk *talk)
{
    if (!subjects_holds_none_or_1380(subjects_held(talk))) {
        return 0;
    }
    VillagerTalkSubjects_SayForMode(talk, 7, &data_020c8af8);
    return 1;
}
CLEAN_AS(func_02022768, VillagerTalkSubjects_SayHolding8af8)

/* func_020227bc: on a map, in an acre with the flag 8 where the villager stands, and while it
 * holds nothing or one of the items 0x1380-0x139f, the line of the set at 0x020c8d00 for mode
 * 6. The held item is asked for first. */
int VillagerTalkSubjects_SayHoldingOnAcre(VillagerTalk *talk)
{
    AcreMap *map = data_021c80bc;
    u16 item = subjects_held(talk);
    if (map == NULL) {
        return 0;
    }
    const s32 *position = (const s32 *) (void *) (talk->villager + VILLAGER_TALK_SUBJECTS_OBJECT_POSITION);
    int acre_x = position[0] >> VILLAGER_TALK_SUBJECTS_ACRE_SHIFT;
    int acre_z = position[2] >> VILLAGER_TALK_SUBJECTS_ACRE_SHIFT;
    if (AcreTile_AcreHasFlags(map, (u32) acre_x, (u32) acre_z, VILLAGER_TALK_SUBJECTS_ACRE_FLAG) == NULL) {
        return 0;
    }
    if (!subjects_holds_none_or_1380(item)) {
        return 0;
    }
    VillagerTalkSubjects_SayForMode(talk, 6, &data_020c8d00);
    return 1;
}
CLEAN_AS(func_020227bc, VillagerTalkSubjects_SayHoldingOnAcre)

/* func_02022840: while the villager holds the item 0x1378, a line of the set at 0x020c8b08 (its
 * count the lines per group): group 0 in mode 5, else 2. */
int VillagerTalkSubjects_SayHolding1378(VillagerTalk *talk)
{
    if (subjects_held(talk) != 0x1378) {
        return 0;
    }
    int group = subjects_mode(subjects_record(talk)) != VILLAGER_TALK_SUBJECTS_MODE_5 ? 2 : 0;
    return subjects_say(talk, &data_020c8b08, group);
}
CLEAN_AS(func_02022840, VillagerTalkSubjects_SayHolding1378)

/* func_020228e4: while the villager holds nothing or one of the items 0x1380-0x139f, the line
 * of the set at 0x020c8a68 for mode 4. */
int VillagerTalkSubjects_SayHolding8a68(VillagerTalk *talk)
{
    if (!subjects_holds_none_or_1380(subjects_held(talk))) {
        return 0;
    }
    VillagerTalkSubjects_SayForMode(talk, 4, &data_020c8a68);
    return 1;
}
CLEAN_AS(func_020228e4, VillagerTalkSubjects_SayHolding8a68)

/* func_02022938: while the villager holds nothing or one of the items 0x1380-0x139f, the line
 * of the set at 0x020c8d28 for mode 3, and the villager put into the talk's slot 5. */
int VillagerTalkSubjects_SayHoldingNamed(VillagerTalk *talk)
{
    if (!subjects_holds_none_or_1380(subjects_held(talk))) {
        return 0;
    }
    VillagerTalkSubjects_SayForMode(talk, 3, &data_020c8d28);
    VillagerTalkGreeting_PutByte29(talk, 5, subjects_record(talk));
    return 1;
}
CLEAN_AS(func_02022938, VillagerTalkSubjects_SayHoldingNamed)

/* func_020229a0: while the villager holds the item 0x1369, the line of the set at 0x020c8d30
 * for mode 2. */
int VillagerTalkSubjects_SayHolding1369(VillagerTalk *talk)
{
    if (subjects_held(talk) != 0x1369) {
        return 0;
    }
    VillagerTalkSubjects_SayForMode(talk, 2, &data_020c8d30);
    return 1;
}
CLEAN_AS(func_020229a0, VillagerTalkSubjects_SayHolding1369)

/* A fish or an insect drawn for the date while the villager holds `held`: none unless it holds
 * `tool`; then the item drawn by `draw` and, when it is in [first, last], its name put into the
 * talk's slot 0 and a line of `texts` (its count the lines per group): group 0 in mode `mode`,
 * else `other`. */
static int subjects_say_drawn(VillagerTalk *talk, u16 tool, int mode, int other, void (*draw)(u16 *item), u16 first, u16 last,
                              const VillagerTalkSubjectsTexts *texts)
{
    VillagerTalkSubjectsDrawn drawn;
    drawn.held = subjects_held(talk);
    if (drawn.held != tool) {
        return 0;
    }
    int group = subjects_mode(subjects_record(talk)) != mode ? other : 0;
    drawn.item = VILLAGER_TALK_SUBJECTS_NO_ITEM;
    draw(&drawn.item);
    if (drawn.item < first || drawn.item > last) {
        return 0;
    }
    SceneBase_PutItemName(subjects_base(talk), (int) (uintptr_t) &drawn.item, 0, 7);
    return subjects_say(talk, texts, group);
}

/* func_020229ec: while the villager holds the item 0x1374, a fish for the date (func_0202cac4)
 * named in the talk's slot 0 and a line of the set at 0x020c8d40: group 0 when the villager is
 * in the mode of a fish caught, else 1. None when no fish was drawn. */
int VillagerTalkSubjects_SayFishWith1374(VillagerTalk *talk)
{
    return subjects_say_drawn(talk, 0x1374, VILLAGER_TALK_SUBJECTS_MODE_FISH, 1, func_0202cac4,
                              VILLAGER_TALK_SUBJECTS_FISH_FIRST, VILLAGER_TALK_SUBJECTS_FISH_LAST, &data_020c8d40);
}
CLEAN_AS(func_020229ec, VillagerTalkSubjects_SayFishWith1374)

/* func_02022ad4: while the villager holds the item 0x1376, an insect for the date
 * (func_0202cfa8) named in the talk's slot 0 and a line of the set at 0x020c8b48: group 0 when
 * the villager is in the mode of an insect caught, else 2. None when no insect was drawn. */
int VillagerTalkSubjects_SayInsectWith1376(VillagerTalk *talk)
{
    return subjects_say_drawn(talk, 0x1376, VILLAGER_TALK_SUBJECTS_MODE_INSECT, 2, func_0202cfa8,
                              VILLAGER_TALK_SUBJECTS_INSECT_FIRST, VILLAGER_TALK_SUBJECTS_INSECT_LAST, &data_020c8b48);
}
CLEAN_AS(func_02022ad4, VillagerTalkSubjects_SayInsectWith1376)

/* func_02022bbc: a line of `texts` (its count the lines per group): group 0 when the villager
 * is in mode `mode`, else 1. */
void VillagerTalkSubjects_SayForMode(VillagerTalk *talk, int mode, const VillagerTalkSubjectsTexts *texts)
{
    int group = mode != subjects_mode(subjects_record(talk)) ? 1 : 0;
    subjects_draw(talk, texts->texts, texts->count, group, 0);
}
CLEAN_AS(func_02022bbc, VillagerTalkSubjects_SayForMode)

/* func_02022c2c: with data_020e54a8 at 0 and a record, the member of a table of eight
 * (data_021c1e44) for the villager's mode, when it is one of the eight kinds; its answer, else
 * 0. */
int VillagerTalkSubjects_SayByMode(VillagerTalk *talk)
{
    static const MemberPointer *const members[VILLAGER_TALK_SUBJECTS_KINDS] = {
        &data_020d9410, &data_020d9400, &data_020d93f0, &data_020d93e8,
        &data_020d93e0, &data_020d93c8, &data_020d93b8, &data_020d93b0,
    };
    MemberTable_InitOnce(&data_021c1d08, data_021c1e44, members, VILLAGER_TALK_SUBJECTS_KINDS);

    int mode = VILLAGER_TALK_SUBJECTS_NO_MODE;
    if (data_020e54a8 == 0 && subjects_record(talk) != NULL) {
        mode = subjects_mode(subjects_record(talk));
    }
    if (VillagerModeRecord_IsKindMode((unsigned int) mode) == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&data_021c1e44[mode], talk);
}
CLEAN_AS(func_02022c2c, VillagerTalkSubjects_SayByMode)

/* func_02022d2c: a line of the set at 0x020c8d70. */
int VillagerTalkSubjects_Say8d70(VillagerTalk *talk)
{
    return subjects_say(talk, &data_020c8d70, 0);
}
CLEAN_AS(func_02022d2c, VillagerTalkSubjects_Say8d70)

/* func_02022d84: a line of the set at 0x020c8a08. */
int VillagerTalkSubjects_Say8a08(VillagerTalk *talk)
{
    return subjects_say(talk, &data_020c8a08, 0);
}
CLEAN_AS(func_02022d84, VillagerTalkSubjects_Say8a08)

/* func_02022ddc: a line of the set at 0x020c8a10. */
int VillagerTalkSubjects_Say8a10(VillagerTalk *talk)
{
    return subjects_say(talk, &data_020c8a10, 0);
}
CLEAN_AS(func_02022ddc, VillagerTalkSubjects_Say8a10)

/* func_02022e34: a line of the set at 0x020c8b70. */
int VillagerTalkSubjects_Say8b70(VillagerTalk *talk)
{
    return subjects_say(talk, &data_020c8b70, 0);
}
CLEAN_AS(func_02022e34, VillagerTalkSubjects_Say8b70)

/* func_02022e8c: a line of the set at 0x020c8db0. */
int VillagerTalkSubjects_Say8db0(VillagerTalk *talk)
{
    return subjects_say(talk, &data_020c8db0, 0);
}
CLEAN_AS(func_02022e8c, VillagerTalkSubjects_Say8db0)

/* func_02022ee4: a line of the set at 0x020c8dc0. */
int VillagerTalkSubjects_Say8dc0(VillagerTalk *talk)
{
    return subjects_say(talk, &data_020c8dc0, 0);
}
CLEAN_AS(func_02022ee4, VillagerTalkSubjects_Say8dc0)

/* func_02022f3c: about a creature of today's lists (CreatureTable_Lists for the month and the
 * half of it): when func_0202cb70 works one out, its name goes into the talk's slot 0, its
 * value into slot 1 (VillagerTalkSubjects_PutCatchKind) and a line of the set at 0x020c8a20 is
 * drawn: group 3 * (the choice is 3 or more) + VillagerTalkSubjects_CatchGroupA of its kind. */
int VillagerTalkSubjects_SayCatchA(VillagerTalk *talk)
{
    VillagerTalkSubjectsCatchA catch_ = {0};
    catch_.choice = VILLAGER_TALK_SUBJECTS_CHOICES;
    catch_.item = VILLAGER_TALK_SUBJECTS_NO_ITEM;
    DateTime_Now(&catch_.when);
    u8 month = catch_.when.month;
    void *lists = CreatureTable_Lists(month, (unsigned int) CreatureTable_IsSecondHalf(catch_.when.day));
    if (lists == NULL) {
        return 0;
    }
    if (CreatureDraw_FishByWeights(&catch_.item, (int *) &catch_.choice, (int *) &catch_.kind, (int *) &catch_.value, lists) !=
        1) {
        return 0;
    }
    int group = (catch_.choice >= 3 ? 1 : 0) * VILLAGER_TALK_SUBJECTS_CATCH_HALF +
                VillagerTalkSubjects_CatchGroupA((unsigned int) catch_.kind);
    SceneBase_PutItemName(subjects_base(talk), (int) (uintptr_t) &catch_.item, 0, 7);
    VillagerTalkSubjects_PutCatchKind(talk, catch_.value, &catch_.item, catch_.choice, *(CreatureTablePeriod *) lists, 1);
    return subjects_say(talk, &data_020c8a20, group);
}
CLEAN_AS(func_02022f3c, VillagerTalkSubjects_SayCatchA)

/* func_02023010: the group of a catch's kind: 0 for 0, 2 and 4 (and kinds past 6), 1 for 5
 * and 6, 2 for 1 and 3. */
int VillagerTalkSubjects_CatchGroupA(unsigned int kind)
{
    switch (kind) {
        case 5:
        case 6:
            return 1;
        case 1:
        case 3:
            return 2;
        default:
            return 0;
    }
}
CLEAN_AS(func_02023010, VillagerTalkSubjects_CatchGroupA)

/* func_02023040: the byte `value` put into the talk's slot `slot` (SceneBase_PutBytes, with
 * data_020d9f74 in the place of the size), or 3 when the item is a fish, `choice` is at most 1
 * and none of the period's three time slots has lists. For such a fish, the two lists of the
 * first time slot that has them are looked through for the fish's place with a weight in band
 * 0 or 1 (CreatureWeight_BandA).
 * BUG: what the look finds is never used: its test (more entries looked at than the list has)
 * cannot hold, so only lists that are all missing give 3. */
void VillagerTalkSubjects_PutCatchKind(VillagerTalk *talk, int value, u16 *item, int choice, CreatureTablePeriod lists,
                                       int slot)
{
    u8 byte = (u8) value;
    unsigned int code = *item;
    if (lists != NULL && code >= VILLAGER_TALK_SUBJECTS_FISH_FIRST && code <= VILLAGER_TALK_SUBJECTS_FISH_LAST &&
        choice <= 1) {
        int place = (int) code - VILLAGER_TALK_SUBJECTS_FISH_FIRST;
        int time_slot;
        for (time_slot = 0; time_slot < VILLAGER_TALK_SUBJECTS_CATCH_TIME_SLOTS; time_slot++) {
            const CreatureTableList *places = lists[time_slot];
            if (places == NULL) {
                continue;
            }
            for (int at = 0; at < VILLAGER_TALK_SUBJECTS_CATCH_PLACES; at++) {
                const u8 *entry = places[at].entries;
                if (entry == NULL) {
                    continue;
                }
                for (int i = 0; i < places[at].count; i++, entry += 3) {
                    if (entry[0] == place && CreatureWeight_BandA(entry[2]) <= 1) {
                        break;
                    }
                }
            }
            break;
        }
        if (time_slot == VILLAGER_TALK_SUBJECTS_CATCH_TIME_SLOTS) {
            byte = 3;
        }
    }
    u8 bytes[2] = {byte, 0};
    SceneBase_PutBytes(subjects_base(talk), slot, &bytes[0], (int) (uintptr_t) data_020d9f74, &bytes[1]);
}
CLEAN_AS(func_02023040, VillagerTalkSubjects_PutCatchKind)

/* func_02023124: about a creature for today's month: when func_0202d060 works one out, its
 * name goes into the talk's slot 0, its value (less 1 from 3 on) into slot 3 and a line of the
 * set at 0x020c8b88 is drawn: group 3 * (the choice is 3 or more) + func_0202c9c0 of its kind. */
int VillagerTalkSubjects_SayCatchB(VillagerTalk *talk)
{
    VillagerTalkSubjectsCatch catch_ = {0};
    catch_.choice = VILLAGER_TALK_SUBJECTS_CHOICES;
    catch_.item = VILLAGER_TALK_SUBJECTS_NO_ITEM;
    DateTime_Now(&catch_.when);
    if (InsectDraw_ByWeights(&catch_.item, (int *) &catch_.choice, (int *) &catch_.kind, (int *) &catch_.value,
                             &catch_.when) != 1) {
        return 0;
    }
    int group = (catch_.choice >= 3 ? 1 : 0) * VILLAGER_TALK_SUBJECTS_CATCH_HALF + CreatureDraw_PlaceGroup(catch_.kind);
    SceneBase_PutItemName(subjects_base(talk), (int) (uintptr_t) &catch_.item, 0, 7);
    if (catch_.value >= 3) {
        catch_.value--;
    }
    catch_.value_byte = (u8) catch_.value;
    catch_.end = 0;
    SceneBase_PutBytes(subjects_base(talk), 3, &catch_.value_byte, (int) (uintptr_t) data_020d9f84, &catch_.end);
    return subjects_say(talk, &data_020c8b88, group);
}
CLEAN_AS(func_02023124, VillagerTalkSubjects_SayCatchB)
