/* The topics of a town villager's talk scene (villager_talk_topics.h). */
#include "villager_talk_topics.h"

#include <string.h>

#include "acre_map.h"
#include "acre_record.h"
#include "clean.h"
#include "constellations.h"
#include "date_time.h"
#include "design.h"
#include "lookups.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "scene_command.h"
#include "scene_query.h"
#include "session.h"
#include "small_texts.h"
#include "town_villager.h"
#include "villager_data.h"
#include "villager_mail.h"
#include "villager_memory_entry.h"
#include "villager_pairs.h"
#include "villager_roster.h"
#include "villager_scene_object.h"
#include "villager_status.h"
#include "villager_town.h"

/* The villager scene object's town record (town_villager.h), or 0, and its position (three
 * words: x, y, z). */
#define VILLAGER_TALK_TOPICS_OBJECT_RECORD 0x830
#define VILLAGER_TALK_TOPICS_OBJECT_POSITION 0x5c

/* The town event (VillagerSceneObject_Event) VillagerTalkTopics_SayEvent10 talks about. */
#define VILLAGER_TALK_TOPICS_EVENT 10
/* A current player has at most this many talks counted (PlayerRecord_Count). */
#define VILLAGER_TALK_TOPICS_TALKS 10
/* The topic drawn once no other is left (func_02022454). */
#define VILLAGER_TALK_TOPICS_LAST 4
#define VILLAGER_TALK_TOPICS_NO_ITEM 0xfff1
#define VILLAGER_TALK_TOPICS_MEMORIES 8
/* The member functions of VillagerTalkTopics_SayOtherPlayer: five for memories of players met,
 * five for the others. */
#define VILLAGER_TALK_TOPICS_PICKERS 10
#define VILLAGER_TALK_TOPICS_PICKER_GROUP 5
/* The tests VillagerTalkTopics_DatedLine12 and VillagerTalkTopics_DatedLine14 ask about. */
#define VILLAGER_TALK_TOPICS_DATED_12 12
#define VILLAGER_TALK_TOPICS_DATED_14 14
/* The bits of the event byte func_02088470 gives. */
#define VILLAGER_TALK_TOPICS_EVENT_KIND(event) ((event) & 3)
#define VILLAGER_TALK_TOPICS_EVENT_SUB(event) (((event) >> 2) & 7)
#define VILLAGER_TALK_TOPICS_EVENT_PART(event) (((event) >> 5) & 7)

/* A text set of the talk lines: its texts and a count (a number of lines, or of lines per
 * group). */
typedef struct VillagerTalkTopicsTexts {
    u32 texts;
    u8 count;
} VillagerTalkTopicsTexts;

/* What one of the members VillagerTalkTopics_SayDated asks gives: the text set (0 for no
 * line) and the line's group, lines per group and random part. */
typedef struct VillagerTalkTopicsDated {
    u32 texts;    /* 0x00 */
    s32 group;    /* 0x04 */
    u8 per_group; /* 0x08 */
    u8 range;     /* 0x09 */
    u8 unk_0a[2]; /* 0x0a */
} VillagerTalkTopicsDated;

/* The text objects, as stack space for the game's constructors. */
typedef struct VillagerTalkTopicsText {
    u32 words[0x24 / 4];
} VillagerTalkTopicsText;

/* The topics: their weights, the copy that is drawn from, the table of their member functions
 * (filled once from constants, bit 0 of the guard) and the constants. */
extern const u8 data_020c8ea4[VILLAGER_TALK_TOPICS_COUNT];
extern u8 data_021c1d34[VILLAGER_TALK_TOPICS_COUNT];
extern u32 data_021c1cf8;
extern MemberPointer data_021c20a4[VILLAGER_TALK_TOPICS_COUNT];
extern const MemberPointer data_020d9468; /* func_02022c2c */
extern const MemberPointer data_020d9040; /* func_02022674 */
extern const MemberPointer data_020d9450; /* func_0202261c */
extern const MemberPointer data_020d9440; /* func_020224c4 */
extern const MemberPointer data_020d9030; /* func_02022454 */
extern const MemberPointer data_020d9020; /* func_020222dc */
extern const MemberPointer data_020d9408; /* VillagerTalkTopics_SayPair */
extern const MemberPointer data_020d9008; /* VillagerTalkTopics_SayByAcre */
extern const MemberPointer data_020d93d0; /* VillagerTalkTopics_SayByTown */
extern const MemberPointer data_020d8ff8; /* VillagerTalkTopics_SayGiftItem */
extern const MemberPointer data_020d8fe8; /* VillagerTalkTopics_SayOtherPlayer */
extern const MemberPointer data_020d8fe0; /* VillagerTalkTopics_SayDated */
extern const MemberPointer data_020d9368; /* VillagerTalkTopics_SayDayEvent */
extern const MemberPointer data_020d9360; /* VillagerTalkTopics_SayConstellation */

/* VillagerTalkTopics_SayDated's two members (filled once, bit 0 of the guard). */
extern u32 data_021c1d0c;
extern MemberPointer data_021c1d44[2];
extern const MemberPointer data_020d90c0; /* VillagerTalkTopics_DatedLine14 */
extern const MemberPointer data_020d90a8; /* VillagerTalkTopics_DatedLine12 */

/* VillagerTalkTopics_SayOtherPlayer's ten members (filled once, bit 0 of the guard). */
extern u32 data_021c1d00;
extern MemberPointer data_021c1f94[VILLAGER_TALK_TOPICS_PICKERS];
extern const MemberPointer data_020d9250; /* VillagerTalkTopics_PickFond */
extern const MemberPointer data_020d92a8; /* VillagerTalkTopics_PickUnfond */
extern const MemberPointer data_020d9190; /* VillagerTalkTopics_PickLetterOfTown */
extern const MemberPointer data_020d9300; /* VillagerTalkTopics_PickWithText2A */
extern const MemberPointer data_020d9318; /* VillagerTalkTopics_PickWithValues */
extern const MemberPointer data_020d9330; /* VillagerTalkTopics_PickAny */
extern const MemberPointer data_020d92c8; /* VillagerTalkTopics_PickWithText2A */
extern const MemberPointer data_020d9418; /* VillagerTalkTopics_PickLetterOfResident */
extern const MemberPointer data_020d9458; /* VillagerTalkTopics_PickLetterOfResident */
extern const MemberPointer data_020d8ef8; /* VillagerTalkTopics_PickWithItem */

/* Member pointer constants for the talk's member events (0x16c). */
extern const MemberPointer data_020d9078;
extern const MemberPointer data_020d9498;
extern const MemberPointer data_020d90f8;
extern const MemberPointer data_020d90f0;

/* The text sets. */
extern const VillagerTalkTopicsTexts data_020c8b80;
extern const VillagerTalkTopicsTexts data_020c8b98;
extern const VillagerTalkTopicsTexts data_020c8bb8;
extern const VillagerTalkTopicsTexts data_020c8a48;
extern const VillagerTalkTopicsTexts data_020c8a50;
extern const VillagerTalkTopicsTexts data_020c8cb8;
extern const VillagerTalkTopicsTexts data_020c8c78;
extern const VillagerTalkTopicsTexts data_020c8c50;
extern const VillagerTalkTopicsTexts data_020c8c98;
/* By whose the current player is (func_02094ffc: 0 this town, else 1). */
extern const VillagerTalkTopicsTexts data_020c8ec4[2];

/* The resource name of the talks line (Personality_FormatResourceName), by address. */
extern u32 data_020c8c20;
/* The group of a day event of each kind (VillagerTalkTopics_SayDayEvent). */
extern const u8 data_020c8934[4];
/* The events VillagerTalkTopics_DatedLine12 and VillagerTalkTopics_DatedLine14 test. */
extern const u32 data_020c8fe0[VILLAGER_TALK_TOPICS_DATED_12];
extern const u32 data_020c9010[VILLAGER_TALK_TOPICS_DATED_14];
/* Defaults of VillagerTalkTopics_SayPair: the villagers' indexes, their groups and the order
 * of their names. */
extern const s32 data_020d9158[2];
extern const s8 data_020d8d20[2];
extern const u32 data_020d91f0[2];
/* What VillagerTalkTopics_SayOtherPlayer hands SceneBase_PutBytes in the place of the size. */
extern u8 data_020d9f68[];

extern VillagerTown data_021e5a2c; /* the town's villagers */
extern NetSession *data_020ccf94;  /* the session */
extern u8 data_021dc7bc[];         /* the town's players (player_records.h) */
extern AcreMap *data_021c80bc;     /* the town's map; null while there is none */
extern u8 data_020e54a8;           /* 0 or 1 */

/* A line drawn for the personality (villager_talk.c). */
extern int func_0202da38(VillagerTalk *talk, char *text, u8 *message, int size, int personality, int texts, int per_group,
                         int group, int range);
/* The talk: a text into its slot `slot`. */
extern void func_02068404(void *talk, int slot, void *text);
/* A random number below `bound`. */
extern unsigned int func_020644cc(int bound);
/* Clears `size` bytes. */
extern void *func_02137550(void *dst, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
/* Something put into the talk's slot `slot`: the first from func_0209c54c of `what`, the
 * second the byte func_020808b0 gives for the villager. */
extern int func_0202bd7c(VillagerTalk *talk, int slot, int what);
extern void func_0202bd40(VillagerTalk *talk, int slot, u8 *villager);
/* The place of a weight drawn at random among `count` byte weights (their sum, a byte), -1
 * when they are all 0. */
extern int func_0202d6e4(const u8 *weights, int count);
/* A random item of one of four lists. */
extern void func_0202d694(u16 *item);
/* Another topic. */
extern int func_02022454(VillagerTalk *talk);
/* Whether the event `event` is on at `when`. */
extern int func_0203fc78(u32 event, const DateTime *when, int arg);
/* Whether the date has an event of the current player's; its kind into `event`. */
extern int func_02088470(int year, int month, int day, u8 *event);
/* Players: whether one is set, the same player, by whose town (0 this, 1 another, 2 none),
 * the town record number (-1 for none) and the town at its start. */
extern int func_020951bc(const DesignCreator *player);
extern int func_0209518c(const DesignCreator *a, const DesignCreator *b);
extern int func_02094ffc(const void *player);
extern int func_02094fec(const DesignCreator *player);
extern const NpcIdHead *func_02095040(const void *player);
/* Text objects: a wide text filled from characters, a label from it, a text emptied, and
 * the constructor and destructor of VillagerTalkTopicsText. */
extern void func_020a8874(void *wide, const u16 *chars, int count);
extern int func_020a8a70(void *label, void *wide, int escape_newlines, int end_code);
extern void func_020a8c1c(void *label);
extern void *func_02094fd4(void *text);
extern void *func_02094fbc(void *text);
/* A town head: constructed, assigned, destructed; and a letter's sender. */
extern void func_020642fc(NpcIdHead *head);
extern void func_020642bc(NpcIdHead *dst, const NpcIdHead *src);
extern void func_020642f8(NpcIdHead *head);
extern const NpcIdHead *func_02065f7c(MailLetter *letter);

/* The tests the pickers hand to VillagerTalkTopics_PickRandom (the game's own functions). */
extern int func_02021ae4(u8 *villager, VillagerMemory *memory);
extern int func_02021b48(u8 *villager, VillagerMemory *memory);
extern int func_02021b8c(u8 *villager, VillagerMemory *memory);
extern int func_02021c08(u8 *villager, VillagerMemory *memory);
extern int func_02021cac(u8 *villager, VillagerMemory *memory);
extern int func_02021d10(u8 *villager, VillagerMemory *memory);
extern int func_02021dcc(u8 *villager, VillagerMemory *memory);
extern int func_02021e44(u8 *villager, VillagerMemory *memory);

static u8 *topics_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_TOPICS_OBJECT_RECORD);
}

static SceneBase *topics_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

/* The line drawn for the personality of the talk's villager into the talk's text and
 * message. */
static void topics_draw(VillagerTalk *talk, u32 texts, int per_group, int group, int range)
{
    func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE,
                  NpcId_Personality(TownVillager_NpcId(topics_record(talk))), (int) texts, per_group, group, range);
}

/* func_02020f9c: the talk's slots filled (VillagerTalkTopics_FillSlots), then the topic of
 * the town event or that of the player's talks, else topics drawn by their weights (a topic
 * that does not apply gets the weight 0) until one applies; a topic out of the table's range
 * (never drawn) makes func_02022454 say the line. `out` names the talk's text and message. */
void VillagerTalkTopics_Line(VillagerTalk *talk, VillagerTalkLine *out)
{
    static const MemberPointer *const topics[VILLAGER_TALK_TOPICS_COUNT] = {
        &data_020d9468, &data_020d9040, &data_020d9450, &data_020d9440, &data_020d9030, &data_020d9020, &data_020d9408,
        &data_020d9008, &data_020d93d0, &data_020d8ff8, &data_020d8fe8, &data_020d8fe0, &data_020d9368, &data_020d9360,
    };
    MemberTable_InitOnce(&data_021c1cf8, data_021c20a4, topics, VILLAGER_TALK_TOPICS_COUNT);

    MI_CpuCopy8(data_020c8ea4, data_021c1d34, VILLAGER_TALK_TOPICS_COUNT);
    VillagerTalkTopics_FillSlots(talk);
    int said = VillagerTalkTopics_SayEvent10(talk);
    if (said == 0) {
        said = VillagerTalkTopics_SayPlayerTalks(talk);
    }
    while (said == 0) {
        int topic = VillagerTalkTopics_Draw(talk, data_021c1d34, VILLAGER_TALK_TOPICS_COUNT);
        if (topic < 0 || topic >= VILLAGER_TALK_TOPICS_COUNT) {
            func_02022454(talk);
            break;
        }
        said = MemberPointer_CallInt(&data_021c20a4[topic], talk);
        if (said == 0) {
            data_021c1d34[topic] = 0;
        }
    }
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}
CLEAN_AS(func_02020f9c, VillagerTalkTopics_Line)

/* func_02021118: the talk's slots 4 (func_0209c54c of 3), 5 (of the villager) and 6
 * (func_0209c54c of 4) filled; the answer of the last. */
int VillagerTalkTopics_FillSlots(VillagerTalk *talk)
{
    func_0202bd7c(talk, 4, 3);
    func_0202bd40(talk, 5, topics_record(talk));
    return func_0202bd7c(talk, 6, 4);
}
CLEAN_AS(func_02021118, VillagerTalkTopics_FillSlots)

/* func_0202114c: a topic drawn by the weights (func_0202d6e4), the last topic when all are
 * 0. */
int VillagerTalkTopics_Draw(VillagerTalk *talk, const u8 *weights, int count)
{
    (void) talk;
    int topic = func_0202d6e4(weights, count);
    if (topic == -1) {
        return VILLAGER_TALK_TOPICS_LAST;
    }
    return topic;
}
CLEAN_AS(func_0202114c, VillagerTalkTopics_Draw)

/* func_02021168: a random bit drawn first; when the villager scene started in the town event
 * 10 and the bit is 0, a line of the set at 0x020c8b80 (its count the lines per group, group
 * 0). */
int VillagerTalkTopics_SayEvent10(VillagerTalk *talk)
{
    unsigned int bit = func_020644cc(2);
    if (VillagerSceneObject_Event(talk->villager) != VILLAGER_TALK_TOPICS_EVENT || bit != 0) {
        return 0;
    }
    topics_draw(talk, data_020c8b80.texts, data_020c8b80.count, 0, 0);
    return 1;
}
CLEAN_AS(func_02021168, VillagerTalkTopics_SayEvent10)

/* func_020211dc: while the current player has had fewer than 10 talks counted (none counted
 * while a session is linked), the text is the resource name data_020c8c20 for the villager's
 * personality and the message the count; the count raised and the talk's first two member
 * events set (data_020d9078 and data_020d9498). */
int VillagerTalkTopics_SayPlayerTalks(VillagerTalk *talk)
{
    int talks = PlayerRecord_Count(PlayerRecords_Current());
    if (Session_IsLinked(data_020ccf94) != 0) {
        talks = VILLAGER_TALK_TOPICS_TALKS;
    }
    if (talks >= VILLAGER_TALK_TOPICS_TALKS) {
        return 0;
    }
    Personality_FormatResourceName(talk->text, VILLAGER_TALK_TEXT_SIZE, (const char *) (uintptr_t) data_020c8c20,
                                   NpcId_Personality(TownVillager_NpcId(topics_record(talk))));
    talk->message = (u8) talks;
    PlayerRecord_RaiseCount(PlayerRecords_Current());
    talk->events[0] = data_020d9078;
    talk->events[1] = data_020d9498;
    return 1;
}
CLEAN_AS(func_020211dc, VillagerTalkTopics_SayPlayerTalks)

/* func_02021284: with data_020e54a8 at 0 and a current player, about the constellation nearest
 * in the sky when it is kept and its creator is set: group 0 of the set at 0x020c8b98 (its
 * count the lines per group) when the current player made it, 1 when a player of this town who
 * has a town record did, 2 when a player of another town than the current one did. The name
 * goes into the talk's slot 0, its creator's name into slot 1 and town into slot 2. */
int VillagerTalkTopics_SayConstellation(VillagerTalk *talk)
{
    if (data_020e54a8 != 0) {
        return 0;
    }
    ConstellationStore *store = (ConstellationStore *) (uintptr_t) Constellations_StoreAddress();
    int number = Constellations_Nearest();
    u8 *current = PlayerRecords_Current();
    int group = -1;
    Constellation *constellation = NULL;
    if (number != -1 && Constellations_IsKept(store, number) != 0 && current != NULL) {
        Constellation *candidate = &store->list[number];
        if (func_020951bc(&candidate->creator) != 0) {
            DesignCreator *player = PlayerRecord_Player(current);
            if (candidate->creator.town_id == player->town_id &&
                memcmp(candidate->creator.town_name, player->town_name, sizeof player->town_name) == 0 &&
                func_0209518c(&candidate->creator, player) != 0) {
                group = 0;
            } else if (func_02094ffc(&candidate->creator) == 0) {
                if (func_02094fec(&candidate->creator) != -1) {
                    group = 1;
                }
            } else if (func_0209518c(&candidate->creator, PlayerRecord_Player(current)) == 0) {
                group = 2;
            }
            if (group != -1) {
                constellation = candidate;
            }
        }
    }
    if (group == -1) {
        return 0;
    }
    topics_draw(talk, data_020c8b98.texts, data_020c8b98.count, group, 0);

    ConstellationsWideName wide;
    ConstellationsLabel label;
    ConstellationsWideName_Construct(&wide);
    ConstellationsLabel_Construct(&label);
    func_020a8874(&wide, constellation->name, CONSTELLATIONS_NAME_LENGTH);
    func_020a8a70(&label, &wide, 0, 0);
    func_02068404(talk->scene.talk, 0, &label);
    ConstellationsLabel_Destruct(&label);
    ConstellationsWideName_Destruct(&wide);

    SceneBase_PutNameAt10(topics_base(talk), &constellation->creator, 1);
    SceneBase_PutNameAt2(topics_base(talk), (unsigned int) (uintptr_t) func_02095040(&constellation->creator), 2);
    return 1;
}
CLEAN_AS(func_02021284, VillagerTalkTopics_SayConstellation)

/* func_02021410: when today has an event of the current player's (func_02088470), a line of the
 * set at 0x020c8bb8: for an event of kind 2 and sub-kind 3 one line per group, group 12 plus
 * the event's part; for others its count the lines per group and the group of the kind
 * (data_020c8934). */
int VillagerTalkTopics_SayDayEvent(VillagerTalk *talk)
{
    int per_group = data_020c8bb8.count;
    int group = 0;
    int said = 0;
    DateTime now = {0};
    u8 event = 0;
    DateTime_Now(&now);
    if (func_02088470(now.year, now.month, now.day, &event) != 0) {
        if (VILLAGER_TALK_TOPICS_EVENT_KIND(event) == 2 && VILLAGER_TALK_TOPICS_EVENT_SUB(event) == 3) {
            per_group = 1;
            group = VILLAGER_TALK_TOPICS_EVENT_PART(event) + 0xc;
        } else {
            group = data_020c8934[VILLAGER_TALK_TOPICS_EVENT_KIND(event)];
        }
        said = 1;
    }
    if (said) {
        topics_draw(talk, data_020c8bb8.texts, per_group, group, 0);
    }
    return said;
}
CLEAN_AS(func_02021410, VillagerTalkTopics_SayDayEvent)

/* One of VillagerTalkTopics_SayDated's members called. */
static u32 topics_call_dated(const MemberPointer *member, VillagerTalk *talk, VillagerTalkTopicsDated *dated,
                             const DateTime *now)
{
    void *self = MemberPointer_Object(member, talk);
    return ((u32 (*)(void *, u8 *, s32 *, u8 *, const DateTime *))(uintptr_t) MemberPointer_Code(member, self))(
        self, &dated->per_group, &dated->group, &dated->range, now);
}

/* func_020214e0: the lines of today's events asked for (VillagerTalkTopics_DatedLine14, then
 * VillagerTalkTopics_DatedLine12); when both give one, the second on a random bit of 0, else
 * the one given. */
int VillagerTalkTopics_SayDated(VillagerTalk *talk)
{
    static const MemberPointer *const members[2] = {&data_020d90c0, &data_020d90a8};
    MemberTable_InitOnce(&data_021c1d0c, data_021c1d44, members, 2);

    VillagerTalkTopicsDated dated[2];
    func_02137550(dated, sizeof dated);
    const VillagerTalkTopicsDated *chosen = NULL;
    DateTime now = {0};
    DateTime_Now(&now);
    for (int i = 0; i < 2; i++) {
        dated[i].texts = topics_call_dated(&data_021c1d44[i], talk, &dated[i], &now);
    }
    if (dated[0].texts != 0) {
        if (dated[1].texts != 0 && func_020644cc(2) == 0) {
            chosen = &dated[1];
        } else {
            chosen = &dated[0];
        }
    } else if (dated[1].texts != 0) {
        chosen = &dated[1];
    }
    if (chosen == NULL) {
        return 0;
    }
    topics_draw(talk, chosen->texts, chosen->per_group, chosen->group, chosen->range);
    return 1;
}
CLEAN_AS(func_020214e0, VillagerTalkTopics_SayDated)

/* func_020215f4: the first of the 12 events of data_020c8fe0 that is on `now` (each tested on
 * a copy of it) gives the set at 0x020c8a48 with one line per group: for the third of each
 * three (index 3k+2) group 5k+4 with a random part below 1, for the others group 2i - i/3
 * with one below 2. 0 when none is on. */
u32 VillagerTalkTopics_DatedLine12(VillagerTalk *talk, u8 *per_group, int *group, u8 *range, const DateTime *now)
{
    (void) talk;
    int found = -1;
    for (int i = 0; i < VILLAGER_TALK_TOPICS_DATED_12; i++) {
        DateTime when;
        MI_CpuCopy8(now, &when, sizeof when);
        if (func_0203fc78(data_020c8fe0[i], &when, 0) != 0) {
            found = i;
            break;
        }
    }
    if (found < 0) {
        return 0;
    }
    if (found % 3 == 2) {
        *group = (found / 3 + 1) * 5 - 1;
        *range = 1;
    } else {
        *group = found * 2 - found / 3;
        *range = 2;
    }
    *per_group = 1;
    return data_020c8a48.texts;
}
CLEAN_AS(func_020215f4, VillagerTalkTopics_DatedLine12)

/* func_02021694: one of the 14 events of data_020c9010 on `now` (each tested on a copy of it)
 * drawn (VillagerRoster_PickBit): one of 0 to 4 is the group, 13 is group 6, and 5 to 12 the
 * villager of that place, when it is not the talk's own, is valid and has a birthday: group
 * 5, its name into the talk's slot 0 and its birthday's month and day into slots 1 and 2.
 * The set at 0x020c8a50 (its count the lines per group, no random part); 0 for no line. */
int VillagerTalkTopics_DatedLine14(VillagerTalk *talk, u8 *per_group, int *group, u8 *range, const DateTime *now)
{
    u16 mask = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TALK_TOPICS_DATED_14; i++) {
        DateTime when;
        MI_CpuCopy8(now, &when, sizeof when);
        if (func_0203fc78(data_020c9010[i], &when, 0) != 0) {
            mask |= (u16) (1u << i);
            count++;
        }
    }
    if (count <= 0) {
        return 0;
    }
    int drawn = VillagerRoster_PickBit(mask, count, VILLAGER_TALK_TOPICS_DATED_14);
    int line = -1;
    if (drawn < 5) {
        line = drawn;
    } else if (drawn > 12) {
        line = 6;
    } else {
        int index = drawn - 5;
        if (index != VillagerStatus_Index(topics_record(talk))) {
            u8 *villager = VillagerRoster_At(&data_021e5a2c, index);
            if (villager != NULL && NpcId_IsValid(TownVillager_NpcId(villager)) != 0) {
                const MonthDay *birthday = VillagerData_Birthday(villager);
                if (birthday != NULL) {
                    line = 5;
                    SceneBase_PutNpcName(topics_base(talk), TownVillager_NpcId(villager), 0);
                    SceneBase_PutNumberAlt(topics_base(talk), (void *) (uintptr_t) birthday->month, 1);
                    SceneBase_PutNumber(topics_base(talk), birthday->day, 2);
                }
            }
        }
    }
    if (line == -1) {
        return 0;
    }
    *group = line;
    *per_group = data_020c8a50.count;
    *range = 0;
    return (int) data_020c8a50.texts;
}
CLEAN_AS(func_02021694, VillagerTalkTopics_DatedLine14)

/* One of VillagerTalkTopics_SayOtherPlayer's members called. */
static u32 topics_call_picker(const MemberPointer *member, VillagerTalk *talk, VillagerMemory **list, int count)
{
    void *self = MemberPointer_Object(member, talk);
    return ((u32 (*)(void *, VillagerMemory **, int))(uintptr_t) MemberPointer_Code(member, self))(self, list, count);
}

/* The memories of `which` group listed and the group's five members asked in a random order
 * until one picks a memory; the memory, and in `slot` the member's place plus `first`. */
static u32 topics_pick_from(VillagerTalk *talk, u8 *villager, const DesignCreator *player, int which, int first, int *slot)
{
    VillagerMemory *list[VILLAGER_TALK_TOPICS_MEMORIES];
    u8 used[VILLAGER_TALK_TOPICS_PICKER_GROUP];
    u32 chosen = 0;
    for (int i = 0; i < VILLAGER_TALK_TOPICS_MEMORIES; i++) {
        list[i] = NULL;
    }
    int count = VillagerMemory_ListOthers(villager, list, player, which);
    if (count <= 0) {
        return 0;
    }
    MI_CpuFill8(used, 0, sizeof used);
    for (int left = VILLAGER_TALK_TOPICS_PICKER_GROUP; left > 0; left--) {
        int skip = (int) func_020644cc(left);
        for (int index = 0; index < VILLAGER_TALK_TOPICS_PICKER_GROUP; index++) {
            if (used[index] != 0) {
                continue;
            }
            if (skip == 0) {
                chosen = topics_call_picker(&data_021c1f94[first + index], talk, list, count);
                if (chosen != 0) {
                    *slot = first + index + 1;
                }
                used[index] = 1;
                break;
            }
            skip--;
        }
        if (chosen != 0) {
            break;
        }
    }
    return chosen;
}

/* func_0202179c: unless this system's slot of the session is taken, a memory of another
 * player picked: with a current player, first among the memories of group 1
 * (VillagerMemory_ListOthers), then of group 0, by the members of the group in a random order.
 * The memory's impression goes into the talk's slot 2 and its player's name into slot 10; the
 * memory is kept at 0x138; a line of the set at 0x020c8cb8 (its count the lines per group) of
 * the group of the member's place (1 to 10, 0 for none); the talk's member events 1 and 2
 * set. */
int VillagerTalkTopics_SayOtherPlayer(VillagerTalk *talk)
{
    static const MemberPointer *const pickers[VILLAGER_TALK_TOPICS_PICKERS] = {
        &data_020d9250, &data_020d92a8, &data_020d9190, &data_020d9300, &data_020d9318,
        &data_020d9330, &data_020d92c8, &data_020d9418, &data_020d9458, &data_020d8ef8,
    };
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0) {
        return 0;
    }
    MemberTable_InitOnce(&data_021c1d00, data_021c1f94, pickers, VILLAGER_TALK_TOPICS_PICKERS);

    const DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    u8 *villager = topics_record(talk);
    u32 chosen = 0;
    int slot = 0;
    if (player != NULL) {
        chosen = topics_pick_from(talk, villager, player, 1, 0, &slot);
        if (chosen == 0) {
            chosen = topics_pick_from(talk, villager, player, 0, VILLAGER_TALK_TOPICS_PICKER_GROUP, &slot);
        }
    }
    if (chosen != 0) {
        VillagerMemory *memory = (VillagerMemory *) (uintptr_t) chosen;
        VillagerTalkTopicsText text;
        func_02094fd4(&text);
        u8 impression = VillagerMemoryEntry_Impression(memory);
        u8 end = 0;
        SceneBase_PutBytes(topics_base(talk), 2, &impression, (int) (uintptr_t) data_020d9f68, &end);
        SceneBase_PutNameAt10(topics_base(talk), VillagerMemoryEntry_Player(memory), 10);
        func_02094fbc(&text);
    }
    talk->record_138 = chosen;
    topics_draw(talk, data_020c8cb8.texts, data_020c8cb8.count, slot, 0);
    talk->events[1] = data_020d90f8;
    talk->events[2] = data_020d90f0;
    return 1;
}
CLEAN_AS(func_0202179c, VillagerTalkTopics_SayOtherPlayer)

/* func_02021a94: a memory with an item (VillagerTalkTopics_HasItem); its town into the talk's
 * slot 9 and its item's name into slot 1. */
u32 VillagerTalkTopics_PickWithItem(VillagerTalk *talk, VillagerMemory **list, u32 count)
{
    u32 memory = (u32) VillagerTalkTopics_PickRandom(topics_record(talk), list, (int) count, func_02021ae4);
    if (memory != 0) {
        VillagerMemory *picked = (VillagerMemory *) (uintptr_t) memory;
        SceneBase_PutNameAt2(topics_base(talk), (unsigned int) VillagerMemoryEntry_Town(picked), 9);
        SceneBase_PutItemName(topics_base(talk), VillagerMemoryEntry_Item(picked), 1, 7);
    }
    return memory;
}
CLEAN_AS(func_02021a94, VillagerTalkTopics_PickWithItem)

/* func_02021ae4: whether the memory's item is set. */
int VillagerTalkTopics_HasItem(u8 *villager, VillagerMemory *memory)
{
    (void) villager;
    const u16 *item = (const u16 *) (uintptr_t) VillagerMemoryEntry_Item(memory);
    return *item != VILLAGER_TALK_TOPICS_NO_ITEM;
}
CLEAN_AS(func_02021ae4, VillagerTalkTopics_HasItem)

/* The memory picked by `test`, and its town put into the talk's slot 9. */
static int topics_pick_town(VillagerTalk *talk, VillagerMemory **list, int count, VillagerTalkTopicsTest test)
{
    int memory = VillagerTalkTopics_PickRandom(topics_record(talk), list, count, test);
    if (memory != 0) {
        SceneBase_PutNameAt2(topics_base(talk),
                             (unsigned int) VillagerMemoryEntry_Town((VillagerMemory *) (uintptr_t) (u32) memory), 9);
    }
    return memory;
}

/* func_02021b08: any memory; its town into the talk's slot 9. */
int VillagerTalkTopics_PickAny(VillagerTalk *talk, VillagerMemory **list, int count)
{
    return topics_pick_town(talk, list, count, func_02021b48);
}
CLEAN_AS(func_02021b08, VillagerTalkTopics_PickAny)

/* func_02021b48 */
int VillagerTalkTopics_Any(void)
{
    return 1;
}
CLEAN_AS(func_02021b48, VillagerTalkTopics_Any)

/* func_02021b4c: a memory with its values set; its town into the talk's slot 9. */
int VillagerTalkTopics_PickWithValues(VillagerTalk *talk, VillagerMemory **list, int count)
{
    return topics_pick_town(talk, list, count, func_02021b8c);
}
CLEAN_AS(func_02021b4c, VillagerTalkTopics_PickWithValues)

/* func_02021b8c */
int VillagerTalkTopics_HasValues(u8 *villager, VillagerMemory *memory)
{
    (void) villager;
    return VillagerMemoryEntry_ValuesSet(memory) == 1;
}
CLEAN_AS(func_02021b8c, VillagerTalkTopics_HasValues)

/* func_02021ba8: a memory of a player of this town whose letter the villager holds; the
 * town of the sender of the villager's letter into the talk's slot 9. */
int VillagerTalkTopics_PickLetterOfResident(VillagerTalk *talk, VillagerMemory **list, int count)
{
    int memory = VillagerTalkTopics_PickRandom(topics_record(talk), list, count, func_02021c08);
    if (memory != 0) {
        const NpcIdHead *sender = func_02065f7c(TownVillager_Letter(topics_record(talk)));
        NpcIdHead town;
        func_020642fc(&town);
        func_020642bc(&town, sender);
        SceneBase_PutNameAt2(topics_base(talk), (unsigned int) (uintptr_t) &town, 9);
        func_020642f8(&town);
    }
    return memory;
}
CLEAN_AS(func_02021ba8, VillagerTalkTopics_PickLetterOfResident)

/* func_02021c08: whether the villager holds a letter of the memory's player and that player
 * is one of the town's. */
int VillagerTalkTopics_HoldsLetterOfResident(u8 *villager, VillagerMemory *memory)
{
    DesignCreator *player = VillagerMemoryEntry_Player(memory);
    if (VillagerMail_HoldsLetterFrom(villager, player) != 1) {
        return 0;
    }
    return PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) (const void *) player) != -1;
}
CLEAN_AS(func_02021c08, VillagerTalkTopics_HoldsLetterOfResident)

/* func_02021c4c: a memory with its text at 0x2a set; the text into the talk's slot 1 and its
 * town into slot 9. */
void *VillagerTalkTopics_PickWithText2A(VillagerTalk *talk, VillagerMemory **list, int count)
{
    int memory = VillagerTalkTopics_PickRandom(topics_record(talk), list, count, func_02021cac);
    if (memory != 0) {
        VillagerMemory *picked = (VillagerMemory *) (uintptr_t) (u32) memory;
        Label22Text label;
        Label22Text_Construct(&label);
        VillagerMemoryEntry_Text2AToLabel(picked, &label);
        func_02068404(talk->scene.talk, 1, &label);
        SceneBase_PutNameAt2(topics_base(talk), (unsigned int) VillagerMemoryEntry_Town(picked), 9);
        Label22Text_Destruct(&label);
    }
    return (void *) (uintptr_t) (u32) memory;
}
CLEAN_AS(func_02021c4c, VillagerTalkTopics_PickWithText2A)

/* func_02021cac */
int VillagerTalkTopics_HasText2A(u8 *villager, VillagerMemory *memory)
{
    (void) villager;
    return VillagerMemoryEntry_Text2ASet(memory) == 1;
}
CLEAN_AS(func_02021cac, VillagerTalkTopics_HasText2A)

/* func_02021cc8: a memory of a player whose letter the villager holds and who is of the town
 * the villager got its last letter in; that town into the talk's slot 9. */
void *VillagerTalkTopics_PickLetterOfTown(VillagerTalk *talk, VillagerMemory **list, int count)
{
    int memory = VillagerTalkTopics_PickRandom(topics_record(talk), list, count, func_02021d10);
    if (memory != 0) {
        SceneBase_PutNameAt2(topics_base(talk), (unsigned int) (uintptr_t) (topics_record(talk) + TOWN_VILLAGER_LETTER_TOWN),
                             9);
    }
    return (void *) (uintptr_t) (u32) memory;
}
CLEAN_AS(func_02021cc8, VillagerTalkTopics_PickLetterOfTown)

/* func_02021d10: whether the villager holds a letter of the memory's player and the player's
 * town is the one the villager got its last letter in (the same first halfword and 12 bytes
 * after it). */
int VillagerTalkTopics_HoldsLetterOfTown(u8 *villager, VillagerMemory *memory)
{
    const NpcIdHead *letter_town = (const NpcIdHead *) (const void *) (villager + TOWN_VILLAGER_LETTER_TOWN);
    if (VillagerMail_HoldsLetterFrom(villager, VillagerMemoryEntry_Player(memory)) == 0) {
        return 0;
    }
    const NpcIdHead *town = func_02095040(VillagerMemoryEntry_Player(memory));
    return town->id == letter_town->id && memcmp(town->data, letter_town->data, sizeof town->data) == 0;
}
CLEAN_AS(func_02021d10, VillagerTalkTopics_HoldsLetterOfTown)

/* func_02021d60: whether the villager holds a letter of the memory's player. */
int VillagerTalkTopics_HoldsLetter(u8 *villager, VillagerMemory *memory)
{
    return VillagerMail_HoldsLetterFrom(villager, VillagerMemoryEntry_Player(memory));
}
CLEAN_AS(func_02021d60, VillagerTalkTopics_HoldsLetter)

/* The memory picked by `test`: its town into the talk's slot 9 and the days since the player
 * was met into slot 0. */
static int topics_pick_days(VillagerTalk *talk, VillagerMemory **list, int count, VillagerTalkTopicsTest test)
{
    int memory = topics_pick_town(talk, list, count, test);
    if (memory != 0) {
        int days = VillagerTalkTopics_DaysSinceMet((VillagerMemory *) (uintptr_t) (u32) memory);
        SceneBase_PutValue(topics_base(talk), days, 0, 10, 0, 0);
    }
    return memory;
}

/* func_02021d78: a memory of a player the villager is not fond of, met days ago. */
int VillagerTalkTopics_PickUnfond(VillagerTalk *talk, VillagerMemory **list, int count)
{
    return topics_pick_days(talk, list, count, func_02021dcc);
}
CLEAN_AS(func_02021d78, VillagerTalkTopics_PickUnfond)

/* func_02021dcc: whether the fondness is 0 or less and the player was met days ago. */
int VillagerTalkTopics_IsUnfond(int unused, VillagerMemory *memory)
{
    (void) unused;
    return VillagerMemoryEntry_Fondness(memory) <= 0 && VillagerTalkTopics_DaysSinceMet(memory) > 0;
}
CLEAN_AS(func_02021dcc, VillagerTalkTopics_IsUnfond)

/* func_02021df0: a memory of a player the villager is fond of, met days ago. */
int VillagerTalkTopics_PickFond(VillagerTalk *talk, VillagerMemory **list, int count)
{
    return topics_pick_days(talk, list, count, func_02021e44);
}
CLEAN_AS(func_02021df0, VillagerTalkTopics_PickFond)

/* func_02021e44: whether the fondness is above 0 and the player was met days ago. */
int VillagerTalkTopics_IsFond(int unused, VillagerMemory *memory)
{
    (void) unused;
    return VillagerMemoryEntry_Fondness(memory) > 0 && VillagerTalkTopics_DaysSinceMet(memory) > 0;
}
CLEAN_AS(func_02021e44, VillagerTalkTopics_IsFond)

/* func_02021e68: the days from the memory's time to now when it is earlier (DateTime_Compare
 * on all six fields says -1), else 0. */
int VillagerTalkTopics_DaysSinceMet(VillagerMemory *memory)
{
    DateTime now = {0};
    const DateTime *when = (const DateTime *) (uintptr_t) VillagerMemoryEntry_When(memory);
    int days = 0;
    DateTime_Now(&now);
    if (DateTime_Compare(when, &now, 0x3f) == -1) {
        days = DateTime_DaysBetween(when, &now);
    }
    return days;
}
CLEAN_AS(func_02021e68, VillagerTalkTopics_DaysSinceMet)

/* func_02021ea8: one of the memories of the list (0 for none) that `test` passes (answers 1)
 * drawn at random; 0 when none passes.
 * REQUIRES: count is at most 8 (the original marks the passing ones in 8 bytes of its stack). */
int VillagerTalkTopics_PickRandom(u8 *villager, VillagerMemory **list, int count, VillagerTalkTopicsTest test)
{
    u8 passed[VILLAGER_TALK_TOPICS_MEMORIES];
    int found = 0;
    MI_CpuFill8(passed, 0, sizeof passed);
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL && test(villager, list[i]) == 1) {
            passed[i] = 1;
            found++;
        }
    }
    if (found <= 0) {
        return 0;
    }
    int skip = (int) func_020644cc(found);
    for (int i = 0; i < count; i++) {
        if (passed[i] == 1) {
            if (skip == 0) {
                return (int) (uintptr_t) list[i];
            }
            skip--;
        }
    }
    return 0;
}
CLEAN_AS(func_02021ea8, VillagerTalkTopics_PickRandom)

/* func_02021f1c: when the current player has a free pocket, a random item (func_0202d694)
 * kept at 0x124; unless it is none its name goes into the talk's slot 0 and a line of the set
 * at 0x020c8c78 (its count the lines per group, group 0) is drawn. */
int VillagerTalkTopics_SayGiftItem(VillagerTalk *talk)
{
    u8 *current = PlayerRecords_Current();
    if (current == NULL || PlayerPockets_FreeSlot(PlayerRecord_Pockets(current)) == -1) {
        return 0;
    }
    u16 item;
    func_0202d694(&item);
    talk->item = item;
    if (talk->item == VILLAGER_TALK_TOPICS_NO_ITEM) {
        return 0;
    }
    SceneBase_PutItemName(topics_base(talk), (int) (uintptr_t) &talk->item, 0, 7);
    topics_draw(talk, data_020c8c78.texts, data_020c8c78.count, 0, 0);
    return 1;
}
CLEAN_AS(func_02021f1c, VillagerTalkTopics_SayGiftItem)

/* func_02021fb8: a line of the set of data_020c8ec4 for a current player of this town, of the
 * next set for one of another town or no current player (its count the lines per group,
 * group 0).
 * REQUIRES: func_02094ffc gives no negative number (the original reads before the table). */
int VillagerTalkTopics_SayByTown(VillagerTalk *talk)
{
    int whose = 2;
    if (PlayerRecords_Current() != NULL) {
        whose = func_02094ffc(PlayerRecord_Player(PlayerRecords_Current()));
    }
    if (whose >= 2) {
        whose = 1;
    }
    topics_draw(talk, data_020c8ec4[whose].texts, data_020c8ec4[whose].count, 0, 0);
    return 1;
}
CLEAN_AS(func_02021fb8, VillagerTalkTopics_SayByTown)

/* func_02022034: a line of the set at 0x020c8c50 (its count the lines per group) by where the
 * villager is: group 3 in the scene of group 11 whose index is the villager's (VillagerStatus_
 * Index); otherwise, with a town map and data_020e54a8 at 0, by the flags of the acre under the
 * villager (its x and z in units of 0x20000): 0 with flag 0x200, 1 with flag 2, 2 with flag
 * 0x800; group 4 for none of these. */
int VillagerTalkTopics_SayByAcre(VillagerTalk *talk)
{
    int group = 4;
    AcreMap *map = data_021c80bc;
    if (SceneQuery_CurrentIn11() != 0 && SceneQuery_CurrentIndexIn11() == VillagerStatus_Index(topics_record(talk))) {
        group = 3;
    } else if (map != NULL && data_020e54a8 == 0) {
        const s32 *position = (const s32 *) (const void *) (talk->villager + VILLAGER_TALK_TOPICS_OBJECT_POSITION);
        int z = position[2] >> 17;
        int x = position[0] >> 17;
        AcreRecord *acre = NULL;
        if ((u32) x < (u32) map->acres_wide && (u32) z < (u32) map->acres_high && map->acres != NULL) {
            acre = (AcreRecord *) (void *) map->acres + (x + z * map->acres_wide);
        }
        if (acre != NULL) {
            if (AcreRecord_HasAnyFlag(acre, 0x200) == 1) {
                group = 0;
            } else if (AcreRecord_HasAnyFlag(acre, 2) == 1) {
                group = 1;
            } else if (AcreRecord_HasAnyFlag(acre, 0x800) == 1) {
                group = 2;
            }
        }
    }
    topics_draw(talk, data_020c8c50.texts, data_020c8c50.count, group, 0);
    return 1;
}
CLEAN_AS(func_02022034, VillagerTalkTopics_SayByAcre)

/* func_0202213c: about two other villagers of the town (VillagerRoster_PickAny, each other
 * than the talk's villager and the one picked before): their names into the talk's slots 7
 * and 8 (the second first when its personality group is 0), and a line of the set at
 * 0x020c8c98 (its count the lines per group) of group a + 3b, where a is 1 for the pair's tier
 * 2 and 2 for a worse one, and b is 1 when both are of group 0 and 2 when both are of another
 * same group (both 0 unless both were picked). */
int VillagerTalkTopics_SayPair(VillagerTalk *talk)
{
    u8 *picked[2];
    s32 index[2];
    s8 group[2];
    const NpcId *excluded[2];
    u32 order[2];
    VillagerTalkTopicsText name;
    int tier_part = 0;
    int group_part = 0;

    func_02137550(picked, sizeof picked);
    index[0] = data_020d9158[0];
    index[1] = data_020d9158[1];
    group[0] = data_020d8d20[0];
    group[1] = data_020d8d20[1];
    func_02137550(excluded, sizeof excluded);
    excluded[0] = TownVillager_NpcId(topics_record(talk));

    int count = 1;
    for (int i = 0; i < 2; i++) {
        picked[i] = VillagerRoster_PickAny(&data_021e5a2c, (const NpcId *const *) excluded, count);
        if (picked[i] != NULL) {
            index[i] = VillagerRoster_IndexOf(&data_021e5a2c, TownVillager_NpcId(picked[i]));
            /* QUIRK: the group is kept in a signed byte. */
            group[i] = (s8) NpcId_PersonalityGroup(TownVillager_NpcId(picked[i]));
        }
        if (count < 2 && picked[i] != NULL) {
            excluded[count] = TownVillager_NpcId(picked[i]);
            count++;
        }
    }

    func_02094fd4(&name);
    order[0] = data_020d91f0[0];
    order[1] = data_020d91f0[1];
    int second_group = group[1];
    if (second_group == 0) {
        order[0] = 1;
        order[1] = 0;
    }
    for (int i = 0; i < 2; i++) {
        func_020a8c1c(&name);
        NpcId_FormatName(TownVillager_NpcId(picked[order[i]]), (char *) &name);
        func_02068404(talk->scene.talk, i + 7, &name);
    }
    func_02094fbc(&name);

    if (index[0] != -1 && index[1] != -1) {
        int tier = VillagerPair_Tier(&data_021e5a2c, index[0], index[1]);
        if (tier == 2) {
            tier_part = 1;
        } else if (tier > 2) {
            tier_part = 2;
        }
        if (group[0] == second_group) {
            group_part = group[0] == 0 ? 1 : 2;
        }
    }
    topics_draw(talk, data_020c8c98.texts, data_020c8c98.count, tier_part + group_part * 3, 0);
    return 1;
}
CLEAN_AS(func_0202213c, VillagerTalkTopics_SayPair)
