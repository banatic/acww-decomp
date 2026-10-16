/* Members of the town villagers' talk scenes about the object a villager keeps
 * (villager_talk_object.h). */
#include "villager_talk_object.h"

#include "calendar.h"
#include "clean.h"
#include "current_pockets.h"
#include "date_time.h"
#include "furniture_info.h"
#include "group_params.h"
#include "item_attributes.h"
#include "item_code.h"
#include "item_object.h"
#include "item_record.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "room_score.h"
#include "scene_base.h"
#include "scene_command.h"
#include "session.h"
#include "session_villager.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_data.h"
#include "villager_house_items.h"
#include "villager_items.h"
#include "villager_memory_entry.h"
#include "villager_mode.h"
#include "villager_state.h"
#include "villager_status.h"

/* The villager scene object's town record (town_villager.h). */
#define VILLAGER_TALK_OBJECT_RECORD 0x830
/* The talk's villager object (villager_object.h). */
#define VILLAGER_TALK_OBJECT_VILLAGER_OBJECT 0x164

#define VILLAGER_TALK_OBJECT_NO_ITEM 0xfff1
#define VILLAGER_TALK_OBJECT_NO_MEMORY (-1)

/* The object types of group 0 (the villager's modes, villager_house_items.h). */
#define VILLAGER_TALK_OBJECT_TYPE_INSECT 0
#define VILLAGER_TALK_OBJECT_TYPE_FISH 1
#define VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM 2
#define VILLAGER_TALK_OBJECT_TYPE_CLOTHES 3
#define VILLAGER_TALK_OBJECT_TYPE_FURNITURE 4
/* The places within group 0 the tables by place cover. */
#define VILLAGER_TALK_OBJECT_GROUP_PLACES 5

#define VILLAGER_TALK_OBJECT_INSECT_FIRST 0x12b0
#define VILLAGER_TALK_OBJECT_INSECT_LAST 0x12e7
#define VILLAGER_TALK_OBJECT_FISH_FIRST 0x12e8
#define VILLAGER_TALK_OBJECT_FISH_LAST 0x131f
#define VILLAGER_TALK_OBJECT_CLOTHES_FIRST 0x11a8
#define VILLAGER_TALK_OBJECT_CLOTHES_LAST 0x12a7
#define VILLAGER_TALK_OBJECT_CLOTHES_COUNT 0x100
#define VILLAGER_TALK_OBJECT_BAG_FIRST 0x1492
#define VILLAGER_TALK_OBJECT_BAG_LAST 0x14fd

/* The pockets screen asked for: the item mask or predicate's argument and "stay on line". */
#define VILLAGER_TALK_OBJECT_POCKET_ARG 13

/* The sound effects the talk plays (0x15a). */
#define VILLAGER_TALK_OBJECT_SOUND_5E 0x5e
#define VILLAGER_TALK_OBJECT_SOUND_5F 0x5f

/* A reward given in bells: in a step before 2 a chance of 30 in 100 for bells from 500, in a
 * later step for bells from 700, each plus four times RoomScore_HouseLowX. */
#define VILLAGER_TALK_OBJECT_BELLS_CHANCE 30
#define VILLAGER_TALK_OBJECT_BELLS_EARLY 500
#define VILLAGER_TALK_OBJECT_BELLS_LATE 700

/* A text set of the talk lines: its texts and a count (a number of lines, or of lines per
 * group). */
typedef struct VillagerTalkObjectTexts {
    u32 texts;
    u8 count;
} VillagerTalkObjectTexts;

/* Text sets, and texts given by their address. */
extern const VillagerTalkObjectTexts data_020d9128;
extern const VillagerTalkObjectTexts data_020d9338;
extern const VillagerTalkObjectTexts data_020c8fb8[];
extern const VillagerTalkObjectTexts data_020d9208;
extern const VillagerTalkObjectTexts data_020c8b30;
extern const VillagerTalkObjectTexts data_020c8c60;
extern const VillagerTalkObjectTexts data_020d8fb8;
extern const VillagerTalkObjectTexts data_020d90a0;
extern const VillagerTalkObjectTexts data_020c8d08;
extern const VillagerTalkObjectTexts data_020c8d20;
extern const VillagerTalkObjectTexts data_020c8b10;
extern const VillagerTalkObjectTexts data_020c8b00;
extern const VillagerTalkObjectTexts data_020c8ad0;
extern const VillagerTalkObjectTexts data_020c8ac0;
extern const VillagerTalkObjectTexts data_020c8d38;
extern const VillagerTalkObjectTexts data_020c8cd0;
extern const VillagerTalkObjectTexts data_020c8ce0;
extern const VillagerTalkObjectTexts data_020c8ad8;
extern const VillagerTalkObjectTexts data_020c8b58;
extern const VillagerTalkObjectTexts data_020c8a58;
extern const VillagerTalkObjectTexts data_020c8d58;
extern const VillagerTalkObjectTexts data_020c8ae8;
extern const VillagerTalkObjectTexts data_020c8aa0;
extern const VillagerTalkObjectTexts data_020c8ae0;
extern const VillagerTalkObjectTexts data_020d92f8;
extern const VillagerTalkObjectTexts data_020d9308;
extern const VillagerTalkObjectTexts data_020c8d48;
extern const VillagerTalkObjectTexts data_020c8d50;
extern u8 data_020c8e74[];
extern u8 data_020c8e80[];
extern u8 data_020c8e8c[];
extern u8 data_020d9a9c[];
extern u8 data_020d9aa8[];
extern u8 data_020d9ab4[];
extern u8 data_020c8e50[];
extern u8 data_020c8e5c[];
extern u8 data_020d96c4[];

/* Texts by the place of the talk's object in group 0, by the villager object's step, and by
 * both (five addresses of tables by step). */
extern const u32 data_020d9d38[VILLAGER_TALK_OBJECT_GROUP_PLACES];
extern const u32 data_020d9d24[VILLAGER_TALK_OBJECT_GROUP_PLACES];
extern const u32 data_020d9dd4[7];
extern const u32 data_020d9d10[VILLAGER_TALK_OBJECT_GROUP_PLACES];

/* The game's item functions by the villager object's step: five taking (out, villager object,
 * villager) and seven taking (out, villager data byte 0x29, a copy of the villager's
 * clothes). */
extern const u32 data_020c8f24[5];
extern const u32 data_020c8f7c[7];

/* Tables of three member pointers for 0xb0 to 0xc0 (func_0202da88). */
extern const MemberPointer data_021c2e9c[3];
extern const MemberPointer data_021c2e84[3];
extern const MemberPointer data_021c2e6c[3];
extern const MemberPointer data_021c2e54[3];
extern const MemberPointer data_021c2e3c[3];
extern const MemberPointer data_021c2e24[3];
extern const MemberPointer data_021c2e0c[3];
extern const MemberPointer data_021c2adc[3];
extern const MemberPointer data_021c2ddc[3];
extern const MemberPointer data_021c2dc4[3];
extern const MemberPointer data_021c2dac[3];
extern const MemberPointer data_021c2d94[3];
extern const MemberPointer data_021c2d64[3];
extern const MemberPointer data_021c2d4c[3];
extern const MemberPointer data_021c2d34[3];
extern const MemberPointer data_021c2d1c[3];
extern const MemberPointer data_021c2cec[3];

/* Member pointer constants the functions here store. */
extern const MemberPointer data_020d9120;
extern const MemberPointer data_020d9270;
extern const MemberPointer data_020d8e30;
extern const MemberPointer data_020d91a8;
extern const MemberPointer data_020d9348;
extern const MemberPointer data_020d9180;
extern const MemberPointer data_020d9018;
extern const MemberPointer data_020d9200;
extern const MemberPointer data_020d8f10;
extern const MemberPointer data_020d8e80;
extern const MemberPointer data_020d9050;
extern const MemberPointer data_020d8f18;
extern const MemberPointer data_020d8f70;
extern const MemberPointer data_020d9230;
extern const MemberPointer data_020d91c0;
extern const MemberPointer data_020d8f38;
extern const MemberPointer data_020d8fd0;
extern const MemberPointer data_020d8f90;
extern const MemberPointer data_020d9398;
extern const MemberPointer data_020d8f28;
extern const MemberPointer data_020d92e8;
extern const MemberPointer data_020d92f0;
extern const MemberPointer data_020d9370;
extern const MemberPointer data_020d9380;
extern const MemberPointer data_020d9388;

/* What the choices of VillagerTalkObject_OfferChoices1f run (their addresses go into
 * TalkChoiceList's functions). */
extern u8 data_021c2ca4[];
extern u8 data_021c2cbc[];

/* What VillagerTalkObject_PutItemNames hands SceneBase_PutBytes in the place of the size. */
extern u8 data_020d9f94[];

extern NetSession *data_020ccf94;

/* The scene's member setters: the three at 0xb0 from a table, the reply, the member run at the
 * command's end, the ones at 0xe0 and 0xe8. */
extern void func_0202da88(VillagerTalk *talk, const MemberPointer *table);
extern void func_0202da74(VillagerTalk *talk, MemberPointer reply);
extern void func_0202dbf0(VillagerTalk *talk, MemberPointer next);
extern void func_0202dbdc(VillagerTalk *talk, MemberPointer member);
extern void func_0202db48(VillagerTalk *talk, MemberPointer member);
/* A line drawn for the personality (villager_talk.h). */
extern int func_0202da38(VillagerTalk *talk, char *text, u8 *message, int size, int personality, int texts, int per_group,
                         int group, int range);
/* The talk's object at 0x154. */
extern ItemObject *func_0202d9c4(VillagerTalk *talk);
/* The villager scene object's motion (at its 0x564) asked for kind 2. */
extern int func_0202d730(VillagerTalk *talk);
/* An item drawn from one of two sets of item lists into `*item` (for 0, or for a player's
 * record). */
extern void func_0202d5e4(u16 *item, int arg);
extern void func_0202d5cc(u16 *item, int arg);
/* `bells` rounded to the nearest 10, at least 10. */
extern int func_0202b510(int bells);
/* The item of a bag holding `bells` (0x1492 when there is none). */
extern void func_02027170(u16 *item, int bells);
/* The pockets the player has an item matching the given one in, as a mask of 15 bits: by the
 * villager object's item, or by an item. */
extern u16 func_02029910(VillagerObject *object);
extern u16 func_02029a18(u16 *item);
/* Pocket predicates the scene is handed (the game's). */
extern int func_02029e18(u16 *item, int state);
extern int func_02029e5c(u16 *item, int state);
extern int func_02029ea0(u16 *item, int state);
extern int func_0202a17c(u16 *item, int state);
extern int func_0202a12c(u16 *item, int state);
/* A value of the item's data, 0 when it has none. */
extern int func_0204c228(u16 *item);
/* The value of an item in bells. */
extern int func_0204c878(u16 *item);
/* An item drawn from `count` codes from `first`. */
extern void func_02063414(u16 *item, int first, int count, int c, int d, u8 *record, int f, int g, int h, int i);
/* A random number below `bound`. */
extern int func_020644cc(int bound);
/* The talk: its message and text, and its byte 0x18 set; the message and text set only while
 * the talk is on the message data_021f43f8 (1 then, else 0). */
extern void func_0206844c(u8 *talk, const u8 *message, int text);
extern int func_02068484(u8 *talk, const u8 *message, int text);
extern void func_02068388(u8 *talk, int cond);

static u8 *object_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneBase *object_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static u8 *object_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_OBJECT_RECORD);
}

static VillagerObject *object_villager_object(const VillagerTalk *talk)
{
    return *(VillagerObject **) (void *) ((u8 *) talk + VILLAGER_TALK_OBJECT_VILLAGER_OBJECT);
}

static ItemObject *object_villager_item_object(const VillagerTalk *talk)
{
    return (ItemObject *) (void *) VillagerObject_Base(object_villager_object(talk));
}

static int object_type(VillagerTalk *talk)
{
    return ItemObject_Type(func_0202d9c4(talk));
}

/* The line drawn for the personality of the talk's villager into the talk's text and
 * message. */
static void object_draw(VillagerTalk *talk, u32 texts, int per_group, int group, int range)
{
    func_0202da38(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE,
                  NpcId_Personality(TownVillager_NpcId(object_record(talk))), (int) texts, per_group, group, range);
}

/* `out` names the talk's text and message. */
static void object_name(VillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

/* A line of a text set (its count the lines per group, group 0) named in `out`. */
static void object_line(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkObjectTexts *texts)
{
    object_draw(talk, texts->texts, texts->count, 0, 0);
    object_name(talk, out);
}

/* The talk told to show its next line (word 8 of the talk), when there is a talk. */
static void object_next_line(VillagerTalk *talk)
{
    if (talk->scene.talk != NULL) {
        talk->scene.talk[2] = 1;
    }
}

/* The line of the table's line function (set already) asked for when there is one.
 * REQUIRES: the tables hold a line function (the original then hands on an unset line). */
static VillagerTalkLine object_set_line(VillagerTalk *talk)
{
    VillagerTalkLine line = {0};
    if (talk->line.function != 0) {
        void *self = MemberPointer_Object(&talk->line, talk);
        ((void (*)(void *, VillagerTalkLine *))(uintptr_t) MemberPointer_Code(&talk->line, self))(self, &line);
    }
    return line;
}

/* The line of the table's line function given to the talk. */
static void object_say_set(VillagerTalk *talk)
{
    VillagerTalkLine line = object_set_line(talk);
    u8 message = line.message;
    func_0206844c(object_talk(talk), &message, (int) line.text);
}

/* The three members set from `table` and their line said. */
static void object_say(VillagerTalk *talk, const MemberPointer *table)
{
    func_0202da88(talk, table);
    object_say_set(talk);
}

/* The three members set from `table` and their line said only while the talk is on the
 * message data_021f43f8 (func_02068484). */
static void object_say_if_on(VillagerTalk *talk, const MemberPointer *table)
{
    func_0202da88(talk, table);
    VillagerTalkLine line = object_set_line(talk);
    u8 message = line.message;
    func_02068484(object_talk(talk), &message, (int) line.text);
}

/* A line of the set `fallback`, or of the set whose texts `by_place` gives for the place of
 * the talk's object in its group (places 0-4), named in `out` when there are texts. */
static int object_line_by_place(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkObjectTexts *fallback,
                                const u32 *by_place)
{
    VillagerTalkObjectTexts texts = *fallback;
    int place = 0;
    ItemObject_PlaceInGroup(func_0202d9c4(talk), &place);
    if (place < VILLAGER_TALK_OBJECT_GROUP_PLACES) {
        texts.texts = by_place[place];
    }
    if (texts.texts == 0) {
        return 0;
    }
    object_line(talk, out, &texts);
    return 1;
}

/* func_020240f4: a line of the set data_020d9128, its texts by the place of the talk's object
 * in its group (data_020d9d38); `out` is left alone when there are none. Then data_020d9120
 * set at 0xe8. */
void VillagerTalkObject_LineByPlace9d38(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line_by_place(talk, out, &data_020d9128, data_020d9d38);
    func_0202db48(talk, data_020d9120);
}
CLEAN_AS(func_020240f4, VillagerTalkObject_LineByPlace9d38)

/* func_02024194: a line of the set data_020d9338, its texts by the place of the talk's object
 * in its group (data_020d9d24); `out` is left alone when there are none. */
void VillagerTalkObject_LineByPlace9d24(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line_by_place(talk, out, &data_020d9338, data_020d9d24);
}
CLEAN_AS(func_02024194, VillagerTalkObject_LineByPlace9d24)

/* func_02024228: the villager object's object given the value 3 in its low bits and that sent
 * to the others in the session (byte 0x0b); when this system has no taken slot in the session,
 * the villager's mode object finished and its state entry given flag 1. */
void VillagerTalkObject_MarkDone(VillagerTalk *talk)
{
    u8 *record = object_record(talk);
    ItemObject_SetLow5(object_villager_item_object(talk), 3);
    SessionVillager_SendObjectByte0B(object_record(talk), 3);
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) == 0) {
        VillagerMode_FinishObject(record);
        VillagerState_SetFlag1UnlessScene(VillagerStatus_StateEntry(record));
    }
}
CLEAN_AS(func_02024228, VillagerTalkObject_MarkDone)

/* func_02024288: a line of the set data_020c8fb8[place] for an object of group 0 whose place
 * the talk's object gives (ItemObject_PlaceInGroup answers nonzero), else of data_020c8fb8[0];
 * then data_020d9270 run at the last message. */
void VillagerTalkObject_LineByGroupPlace(VillagerTalk *talk, VillagerTalkLine *out)
{
    const VillagerTalkObjectTexts *texts = &data_020c8fb8[0];
    if (ItemObject_Group(func_0202d9c4(talk)) == 0) {
        int place = 0;
        if (ItemObject_PlaceInGroup(func_0202d9c4(talk), &place) != 0) {
            texts = &data_020c8fb8[place];
        }
    }
    object_line(talk, out, texts);
    talk->on_last_message = data_020d9270;
}
CLEAN_AS(func_02024288, VillagerTalkObject_LineByGroupPlace)

/* func_02024328: a line of the texts data_020c8e74 for an object of type 2, data_020c8e80 for
 * type 3, else data_020c8e8c (with the count of data_020d9208); then data_020d8e30 run at the
 * last message. */
void VillagerTalkObject_LineByType8e74(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkObjectTexts texts = data_020d9208;
    switch (object_type(talk)) {
        case VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM:
            texts.texts = (u32) (uintptr_t) data_020c8e74;
            break;
        case VILLAGER_TALK_OBJECT_TYPE_CLOTHES:
            texts.texts = (u32) (uintptr_t) data_020c8e80;
            break;
        default:
            texts.texts = (u32) (uintptr_t) data_020c8e8c;
            break;
    }
    object_line(talk, out, &texts);
    talk->on_last_message = data_020d8e30;
}
CLEAN_AS(func_02024328, VillagerTalkObject_LineByType8e74)

/* func_020243d8: the line of the table data_021c2e9c said once the villager object has reached
 * the last step for the talk object's type, else that of data_021c2e84. */
void VillagerTalkObject_SayByLastStep(VillagerTalk *talk)
{
    int steps = VillagerObject_StepsForType(object_type(talk));
    if (VillagerObject_Step(object_villager_object(talk)) >= steps - 1) {
        object_say(talk, data_021c2e9c);
    } else {
        object_say(talk, data_021c2e84);
    }
}
CLEAN_AS(func_020243d8, VillagerTalkObject_SayByLastStep)

/* func_0202445c: the gift at 0x19c shown (motion 13), then data_020d91a8 at the command's
 * end. */
void VillagerTalkObject_ShowGift91a8(VillagerTalk *talk)
{
    SceneCommand_RequestMotion13(&talk->scene, &talk->gift, 0, 5, 0);
    func_0202dbf0(talk, data_020d91a8);
}
CLEAN_AS(func_0202445c, VillagerTalkObject_ShowGift91a8)

/* The item at 0x124, when there is one, noted in the player's memory and sent to the others in
 * the session, when the talk has the memory and its place. */
static void object_note_item(VillagerTalk *talk, u8 *record)
{
    if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM && talk->memory != NULL &&
        talk->memory_index != VILLAGER_TALK_OBJECT_NO_MEMORY) {
        VillagerMemoryEntry_SetItem((VillagerMemory *) (void *) talk->memory, &talk->item);
        SessionVillager_SendEntryItem(record, talk->memory_index, &talk->item);
    }
}

/* func_0202448c: the reward given (VillagerTalkObject_GiveReward); the item the villager keeps
 * is the item at 0x124, or for an object of type 3 (clothes) the gift at 0x19c, which is
 * emptied first; it goes into the villager's items when there is one. The item at 0x124 is
 * noted in the player's memory, then a line of the set data_020c8b30 and the sound 0x5f. */
void VillagerTalkObject_LineTakeItemType3(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = object_record(talk);
    u16 kept = talk->item;
    if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_CLOTHES) {
        kept = talk->gift;
        talk->gift = VILLAGER_TALK_OBJECT_NO_ITEM;
    }
    VillagerTalkObject_GiveReward(talk);
    if (kept != VILLAGER_TALK_OBJECT_NO_ITEM) {
        VillagerItems_Add(record, &kept);
    }
    object_note_item(talk, record);
    object_line(talk, out, &data_020c8b30);
    talk->sound = VILLAGER_TALK_OBJECT_SOUND_5F;
}
CLEAN_AS(func_0202448c, VillagerTalkObject_LineTakeItemType3)

/* A bag of bells as the gift: `base` plus four times RoomScore_HouseLowX, rounded to tens, kept
 * at 0x1a0. */
static void object_bells_gift(VillagerTalk *talk, int base)
{
    u16 bag;
    talk->bells = RoomScore_HouseLowX() * 4 + base;
    talk->bells = func_0202b510(talk->bells);
    func_02027170(&bag, talk->bells);
    talk->gift = bag;
}

/* A gift drawn from the villager's items (a random one when `random`, else the most valuable)
 * and taken from them when there is one; else, with a chance of 30 in 100, a bag of bells from
 * `base`. The chance is `chance`, or drawn now when `fresh_chance`. */
static void object_items_gift(VillagerTalk *talk, u8 *record, int random, int fresh_chance, int chance, int base)
{
    u16 item;
    if (random) {
        VillagerItems_Random(&item, record);
    } else {
        VillagerItems_MostValuable(&item, record);
    }
    talk->gift = item;
    if (talk->gift != VILLAGER_TALK_OBJECT_NO_ITEM) {
        VillagerItems_Remove(record, &talk->gift);
    } else {
        if (fresh_chance) {
            chance = func_020644cc(100);
        }
        if (chance < VILLAGER_TALK_OBJECT_BELLS_CHANCE) {
            object_bells_gift(talk, base);
        }
    }
}

/* A gift drawn for `arg` by func_0202d5cc for clothes, else by func_0202d5e4. */
static void object_drawn_gift(VillagerTalk *talk, int clothes, int arg)
{
    u16 item;
    if (clothes) {
        func_0202d5cc(&item, arg);
    } else {
        func_0202d5e4(&item, arg);
    }
    talk->gift = item;
}

/* func_02024580: the player's reward for the villager object, as the gift at 0x19c, by the
 * talk object's type and the villager object's step (nothing without a villager object):
 *   types 0-2 and 4: in steps 0-1, a chance of 30 in 100 (drawn first) of a bag of bells from
 *     500; in steps 2-3 (types 0-2) or 2-4 (type 4) the villager's most valuable item, or a new
 *     chance of 30 in 100 of a bag from 700; in later steps an item of func_0202d5e4;
 *   type 3: in steps 0-1 a random one of the villager's items, else the bag from 500 on the
 *     first chance; in steps 2-4 as the others; later an item of func_0202d5cc;
 * an item taken from the villager's items is removed from them, and without a gift after that
 * an item of func_0202d5e4 (func_0202d5cc for type 3) for 0. A bag puts its bells into the
 * current player's pockets (as bags) and its count into the talk's slot 1; another gift goes
 * into the first free pocket, is marked as had and its name goes into slot 1.
 * QUIRK: in steps 0-1 without the chance the gift at 0x19c is left as it was, and without a
 * free pocket the gift is not given but still named; another type leaves the gift as it was. */
void VillagerTalkObject_GiveReward(VillagerTalk *talk)
{
    if (object_villager_object(talk) == NULL) {
        return;
    }
    u8 *player = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(player);
    u8 *record = object_record(talk);
    ItemObject *object = object_villager_item_object(talk);
    int chance = func_020644cc(100);
    int step = VillagerObject_Step(object_villager_object(talk));
    switch (ItemObject_Type(object)) {
        case VILLAGER_TALK_OBJECT_TYPE_INSECT:
        case VILLAGER_TALK_OBJECT_TYPE_FISH:
        case VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM:
            switch (step) {
                case 0:
                case 1:
                    if (chance < VILLAGER_TALK_OBJECT_BELLS_CHANCE) {
                        object_bells_gift(talk, VILLAGER_TALK_OBJECT_BELLS_EARLY);
                    }
                    break;
                case 2:
                case 3:
                    object_items_gift(talk, record, 0, 1, 0, VILLAGER_TALK_OBJECT_BELLS_LATE);
                    break;
                default:
                    object_drawn_gift(talk, 0, (int) (uintptr_t) player);
                    break;
            }
            if (talk->gift == VILLAGER_TALK_OBJECT_NO_ITEM) {
                object_drawn_gift(talk, 0, 0);
            }
            break;
        case VILLAGER_TALK_OBJECT_TYPE_CLOTHES:
            switch (step) {
                case 0:
                case 1:
                    object_items_gift(talk, record, 1, 0, chance, VILLAGER_TALK_OBJECT_BELLS_EARLY);
                    break;
                case 2:
                case 3:
                case 4:
                    object_items_gift(talk, record, 0, 1, 0, VILLAGER_TALK_OBJECT_BELLS_LATE);
                    break;
                default:
                    object_drawn_gift(talk, 1, (int) (uintptr_t) player);
                    break;
            }
            if (talk->gift == VILLAGER_TALK_OBJECT_NO_ITEM) {
                object_drawn_gift(talk, 1, 0);
            }
            break;
        case VILLAGER_TALK_OBJECT_TYPE_FURNITURE:
            switch (step) {
                case 0:
                case 1:
                    if (chance < VILLAGER_TALK_OBJECT_BELLS_CHANCE) {
                        object_bells_gift(talk, VILLAGER_TALK_OBJECT_BELLS_EARLY);
                    }
                    break;
                case 2:
                case 3:
                case 4:
                    object_items_gift(talk, record, 0, 1, 0, VILLAGER_TALK_OBJECT_BELLS_LATE);
                    break;
                default:
                    object_drawn_gift(talk, 0, (int) (uintptr_t) player);
                    break;
            }
            if (talk->gift == VILLAGER_TALK_OBJECT_NO_ITEM) {
                object_drawn_gift(talk, 0, 0);
            }
            break;
        default:
            break;
    }

    u16 gift = talk->gift;
    if (gift >= VILLAGER_TALK_OBJECT_BAG_FIRST && gift <= VILLAGER_TALK_OBJECT_BAG_LAST) {
        PlayerPockets_AddBells(pockets, talk->bells, 1);
    } else if (gift != VILLAGER_TALK_OBJECT_NO_ITEM) {
        int slot = PlayerPockets_FreeSlot(pockets);
        if (slot != -1) {
            PlayerPockets_SetSlot(pockets, &talk->gift, slot, 0);
            ItemRecord_SetBit((ItemRecord *) (void *) PlayerRecord_ItemRecord(player), &talk->gift, 0, 1);
        }
    }
    gift = talk->gift;
    if (gift >= VILLAGER_TALK_OBJECT_BAG_FIRST && gift <= VILLAGER_TALK_OBJECT_BAG_LAST) {
        SceneBase_PutCount(object_base(talk), talk->bells, 1, 4, 1, 0, 0);
    } else if (gift != VILLAGER_TALK_OBJECT_NO_ITEM) {
        SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &talk->gift, 1, 7);
    }
}
CLEAN_AS(func_02024580, VillagerTalkObject_GiveReward)

/* func_02024978: the line of the table data_021c2e6c said while the talk is on the message
 * data_021f43f8. */
void VillagerTalkObject_SayIfOn2e6c(VillagerTalk *talk)
{
    object_say_if_on(talk, data_021c2e6c);
}
CLEAN_AS(func_02024978, VillagerTalkObject_SayIfOn2e6c)

/* func_020249cc: a line of the set data_020c8c60. */
void VillagerTalkObject_Line8c60(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, &data_020c8c60);
}
CLEAN_AS(func_020249cc, VillagerTalkObject_Line8c60)

/* func_02024a30: the line of the table data_021c2e6c said for an object of type 2; else that
 * of data_021c2e54, after the villager's motion of kind 2 (func_0202d730) for type 3. */
void VillagerTalkObject_SayByType2e6c(VillagerTalk *talk)
{
    if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM) {
        object_say(talk, data_021c2e6c);
    } else {
        if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_CLOTHES) {
            func_0202d730(talk);
        }
        object_say(talk, data_021c2e54);
    }
}
CLEAN_AS(func_02024a30, VillagerTalkObject_SayByType2e6c)

/* The pocket the pockets screen gave (GroupParams_Arg) emptied. */
static void object_empty_pocket(void)
{
    int slot = GroupParams_Arg();
    u16 none = VILLAGER_TALK_OBJECT_NO_ITEM;
    CurrentPockets_Set(&none, 0, slot);
}

/* func_02024ab4: the pocket the pockets screen gave emptied; for an object of type 3 the
 * villager's motion 15, and the villager's clothes become the gift at 0x19c when they are
 * clothes (0x11a8-0x12a7); for other types the motion 16. Then data_020d9348 at the command's
 * end. */
void VillagerTalkObject_EmptyPocketAndMotion(VillagerTalk *talk)
{
    object_empty_pocket();
    if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_CLOTHES) {
        SceneCommand_RequestMotion15(&talk->scene);
        u16 clothes = *TownVillager_Clothes(object_record(talk));
        if (clothes >= VILLAGER_TALK_OBJECT_CLOTHES_FIRST && clothes <= VILLAGER_TALK_OBJECT_CLOTHES_LAST) {
            talk->gift = *TownVillager_Clothes(object_record(talk));
        }
    } else {
        SceneCommand_RequestMotion16(&talk->scene);
    }
    func_0202dbf0(talk, data_020d9348);
}
CLEAN_AS(func_02024ab4, VillagerTalkObject_EmptyPocketAndMotion)

/* func_02024b4c: the talk told to show its next line, then a line of the texts data_020d9a9c
 * for an object of type 2, data_020d9aa8 for type 3, else data_020d9ab4 (with the count of
 * data_020d8fb8). */
void VillagerTalkObject_LineByType9a9c(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkObjectTexts texts = data_020d8fb8;
    switch (object_type(talk)) {
        case VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM:
            texts.texts = (u32) (uintptr_t) data_020d9a9c;
            break;
        case VILLAGER_TALK_OBJECT_TYPE_CLOTHES:
            texts.texts = (u32) (uintptr_t) data_020d9aa8;
            break;
        default:
            texts.texts = (u32) (uintptr_t) data_020d9ab4;
            break;
    }
    object_next_line(talk);
    object_draw(talk, texts.texts, texts.count, 0, 0);
    object_name(talk, out);
}
CLEAN_AS(func_02024b4c, VillagerTalkObject_LineByType9a9c)

/* func_02024bf8: the talk told to show its next line, then group 1 of the texts data_020c8e50
 * (three lines per group, a random part of 2), or for an object of type 4 of data_020c8e5c
 * (a random part of 3); then data_020d9180 run at the last message. */
void VillagerTalkObject_LineGroupByType(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *texts = data_020c8e50;
    int range = 2;
    if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_FURNITURE) {
        texts = data_020c8e5c;
        range = 3;
    }
    object_next_line(talk);
    object_draw(talk, (u32) (uintptr_t) texts, 3, 1, range);
    object_name(talk, out);
    talk->on_last_message = data_020d9180;
}
CLEAN_AS(func_02024bf8, VillagerTalkObject_LineGroupByType)

/* func_02024c90: the villager's motion 17. */
void VillagerTalkObject_Motion17(VillagerTalk *talk)
{
    SceneCommand_RequestMotion17(&talk->scene);
}
CLEAN_AS(func_02024c90, VillagerTalkObject_Motion17)

/* func_02024c98: the talk told to show its next line, then a line of the set data_020d90a0, its
 * texts data_020d96c4 for an object of type 4; then data_020d9018 run at the last message. */
void VillagerTalkObject_LineByType96c4(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkObjectTexts texts = data_020d90a0;
    if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_FURNITURE) {
        texts.texts = (u32) (uintptr_t) data_020d96c4;
    }
    object_next_line(talk);
    object_line(talk, out, &texts);
    talk->on_last_message = data_020d9018;
}
CLEAN_AS(func_02024c98, VillagerTalkObject_LineByType96c4)

/* Whether the item `a` is the item `b`: for items with variants the variant item compared
 * (ItemCode_VariantItem), for others the codes. */
static int object_same_item(u16 *a, u16 *b)
{
    if (ItemCode_HasVariant(a)) {
        int variant = ItemCode_VariantItem(a);
        return variant == ItemCode_VariantItem(b);
    }
    return *a == *b;
}

/* func_02024d38: the table of the player's item at 0x124 for the talk object's type, then the
 * talk told to show its next line and the line said:
 *   type 2: data_021c2e3c, the item's name in slot 0; in the villager object's steps 2-4 the
 *     item's place in its kind (VillagerTalkObject_ItemPart) set as a flag of the villager
 *     object and sent to the others in the session;
 *   type 3: data_021c2e3c from step 2; before, data_021c2e24 when the item is the villager's
 *     clothes, data_021c2e3c when its value (func_0204c228) is not the villager data's byte
 *     0x2a, else data_021c2e0c; the item's name in slot 2;
 *   type 4: data_021c2e24 when the villager likes the item (VillagerData_ItemLiking above 0),
 *     it has variants and the villager's house has two of it, or one and the item's shape is
 *     2; data_021c2e3c when it is liked with variants otherwise; else data_021c2e0c; the
 *     item's name in slot 0.
 * QUIRK: other types keep the table set before; a part of -1 sets flag 255. */
void VillagerTalkObject_SayJudgeItem(VillagerTalk *talk)
{
    u8 *record = object_record(talk);
    switch (object_type(talk)) {
        case VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM:
            func_0202da88(talk, data_021c2e3c);
            if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
                SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &talk->item, 0, 7);
            }
            if (VillagerObject_Step(object_villager_object(talk)) < 2) {
                break;
            }
            if (VillagerObject_Step(object_villager_object(talk)) > 4) {
                break;
            }
            {
                u8 part = (u8) VillagerTalkObject_ItemPart(&talk->item);
                VillagerObject_SetFlag(object_villager_object(talk), part);
                SessionVillager_SendObjectBit30(record, part);
            }
            break;
        case VILLAGER_TALK_OBJECT_TYPE_CLOTHES:
            if (VillagerObject_Step(object_villager_object(talk)) >= 2) {
                func_0202da88(talk, data_021c2e3c);
            } else {
                const u8 *data = VillagerData_Byte29(record);
                u16 *clothes = TownVillager_Clothes(record);
                if (object_same_item(&talk->item, clothes)) {
                    func_0202da88(talk, data_021c2e24);
                } else if (data[1] != func_0204c228(&talk->item)) {
                    func_0202da88(talk, data_021c2e3c);
                } else {
                    func_0202da88(talk, data_021c2e0c);
                }
            }
            if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
                SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &talk->item, 2, 7);
            }
            break;
        case VILLAGER_TALK_OBJECT_TYPE_FURNITURE:
            if (VillagerData_ItemLiking(record, &talk->item) > 0) {
                if (ItemCode_HasVariant(&talk->item)) {
                    int same = VillagerHouseItems_CountSame(record, &talk->item);
                    int shape = FurnitureInfo_ItemShape(&talk->item);
                    if (same >= 2 || (same == 1 && shape == 2)) {
                        func_0202da88(talk, data_021c2e24);
                    } else {
                        func_0202da88(talk, data_021c2e3c);
                    }
                } else {
                    func_0202da88(talk, data_021c2e0c);
                }
            } else {
                func_0202da88(talk, data_021c2e0c);
            }
            if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
                SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &talk->item, 0, 7);
            }
            break;
        default:
            break;
    }
    object_next_line(talk);
    object_say_set(talk);
}
CLEAN_AS(func_02024d38, VillagerTalkObject_SayJudgeItem)

/* When the pockets screen gave no pocket (GroupParams_C4CIs1 is 0): the talk told to show its
 * next line and the line of the table data_021c2adc said; else the item of that pocket of the
 * current player becomes the item at 0x124, the pocket is emptied when `empty`, the item is
 * taken (motion 14) and `next` set at 0xe0. */
static void object_take_pocket(VillagerTalk *talk, MemberPointer next, int empty)
{
    if (GroupParams_C4CIs1() == 0) {
        object_next_line(talk);
        object_say(talk, data_021c2adc);
        return;
    }
    int slot = GroupParams_Arg();
    talk->item = *PlayerPockets_Slot(PlayerRecord_Pockets(PlayerRecords_Current()), slot);
    if (empty) {
        u16 none = VILLAGER_TALK_OBJECT_NO_ITEM;
        CurrentPockets_Set(&none, 0, slot);
    }
    SceneCommand_RequestMotion14(&talk->scene, &talk->item, 0, 4, 0);
    func_0202dbdc(talk, next);
}

/* func_02024f40: the item of the pocket the pockets screen gave taken (data_020d9200 next), or
 * the line of data_021c2adc said. */
void VillagerTalkObject_TakePocket9200(VillagerTalk *talk)
{
    object_take_pocket(talk, data_020d9200, 0);
}
CLEAN_AS(func_02024f40, VillagerTalkObject_TakePocket9200)

/* The pockets screen asked for the items `predicate` accepts. */
static void object_ask_predicate(VillagerTalk *talk, PocketPredicate predicate)
{
    SceneCommand_SetPocketPredicate(&talk->scene, predicate, VILLAGER_TALK_OBJECT_POCKET_ARG, 1);
}

/* The pockets screen asked for the pockets of `mask`. */
static void object_ask_mask(VillagerTalk *talk, u16 mask)
{
    SceneCommand_SetPocketMask(&talk->scene, mask, VILLAGER_TALK_OBJECT_POCKET_ARG, 1);
}

/* The pockets screen opened, then `next` at the command's end. */
static void object_open_pockets(VillagerTalk *talk, MemberPointer next)
{
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_POCKETS);
    func_0202dbf0(talk, next);
}

/* func_02024fe4: the pockets screen opened by the talk object's type: for type 2 the items of
 * the predicate func_02029e18 in the villager object's steps 0-1, else the pockets holding the
 * villager object's item (func_02029910), then data_020d8f10; for type 3 the predicate
 * func_02029e5c in steps 0-1, else the pockets holding the talk object's item (func_02029a18),
 * then data_020d8e80; for type 4 the predicate func_02029ea0, then data_020d9050. Nothing for
 * other types. */
void VillagerTalkObject_AskPocketByType(VillagerTalk *talk)
{
    switch (object_type(talk)) {
        case VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM:
            if (VillagerObject_Step(object_villager_object(talk)) <= 1) {
                object_ask_predicate(talk, func_02029e18);
            } else {
                object_ask_mask(talk, func_02029910(object_villager_object(talk)));
            }
            object_open_pockets(talk, data_020d8f10);
            break;
        case VILLAGER_TALK_OBJECT_TYPE_CLOTHES:
            if (VillagerObject_Step(object_villager_object(talk)) <= 1) {
                object_ask_predicate(talk, func_02029e5c);
            } else {
                object_ask_mask(talk, func_02029a18(ItemObject_Item(func_0202d9c4(talk))));
            }
            object_open_pockets(talk, data_020d8e80);
            break;
        case VILLAGER_TALK_OBJECT_TYPE_FURNITURE:
            object_ask_predicate(talk, func_02029ea0);
            object_open_pockets(talk, data_020d9050);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02024fe4, VillagerTalkObject_AskPocketByType)

/* func_020250c8: for an object of type 4 and an item at 0x124 with variants, the villager's
 * liking of the item added to the villager object's count and the new count sent to the
 * others in the session; then the talk object given the value 1 in its low bits, that sent
 * (byte 0x0b), and the villager's state entry given flag 1. */
void VillagerTalkObject_CountItem(VillagerTalk *talk)
{
    u8 *record = object_record(talk);
    if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_FURNITURE && ItemCode_HasVariant(&talk->item)) {
        u8 liking = (u8) VillagerData_ItemLiking(record, &talk->item);
        u8 count = VillagerObject_AddCount(object_villager_object(talk), liking);
        SessionVillager_SendObjectByte2E(record, count);
    }
    ItemObject_SetLow5(func_0202d9c4(talk), 1);
    SessionVillager_SendObjectByte0B(record, 1);
    VillagerState_SetFlag1UnlessScene(VillagerStatus_StateEntry(record));
}
CLEAN_AS(func_020250c8, VillagerTalkObject_CountItem)

/* The set `other`, or `fish` for an object of type 1. */
static const VillagerTalkObjectTexts *object_texts_fish(VillagerTalk *talk, const VillagerTalkObjectTexts *other,
                                                        const VillagerTalkObjectTexts *fish)
{
    return object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_FISH ? fish : other;
}

/* func_02025148: a line of the set data_020c8d08, or data_020c8d20 for an object of type 1;
 * then data_020d8f18 run at the last message. */
void VillagerTalkObject_Line8d08(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, object_texts_fish(talk, &data_020c8d08, &data_020c8d20));
    talk->on_last_message = data_020d8f18;
}
CLEAN_AS(func_02025148, VillagerTalkObject_Line8d08)

/* func_020251d0: the gift at 0x19c shown (motion 13), then data_020d8f70 at the command's
 * end. */
void VillagerTalkObject_ShowGift8f70(VillagerTalk *talk)
{
    SceneCommand_RequestMotion13(&talk->scene, &talk->gift, 0, 5, 0);
    func_0202dbf0(talk, data_020d8f70);
}
CLEAN_AS(func_020251d0, VillagerTalkObject_ShowGift8f70)

/* func_02025200: the line of the table data_021c2e9c said from the villager object's step 4,
 * else that of data_021c2ddc. */
void VillagerTalkObject_SayByStep4(VillagerTalk *talk)
{
    if (VillagerObject_Step(object_villager_object(talk)) >= 4) {
        object_say(talk, data_021c2e9c);
    } else {
        object_say(talk, data_021c2ddc);
    }
}
CLEAN_AS(func_02025200, VillagerTalkObject_SayByStep4)

/* The reward given, then the item at 0x124, when there is one, put into the villager's items
 * and noted in the player's memory. */
static void object_reward_and_keep(VillagerTalk *talk)
{
    u8 *record = object_record(talk);
    VillagerTalkObject_GiveReward(talk);
    if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
        VillagerItems_Add(record, &talk->item);
        object_note_item(talk, record);
    }
}

/* func_02025274: the reward given and the item at 0x124 kept by the villager, then a line of
 * the set data_020c8b10, or data_020c8b00 for an object of type 1, and the sound 0x5f. */
void VillagerTalkObject_LineKeepItem8b10(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_reward_and_keep(talk);
    object_line(talk, out, object_texts_fish(talk, &data_020c8b10, &data_020c8b00));
    talk->sound = VILLAGER_TALK_OBJECT_SOUND_5F;
}
CLEAN_AS(func_02025274, VillagerTalkObject_LineKeepItem8b10)

/* func_0202534c: the line of the table data_021c2dc4 said while the talk is on the message
 * data_021f43f8. */
void VillagerTalkObject_SayIfOn2dc4(VillagerTalk *talk)
{
    object_say_if_on(talk, data_021c2dc4);
}
CLEAN_AS(func_0202534c, VillagerTalkObject_SayIfOn2dc4)

/* func_020253a0: the villager's motion 16, then data_020d9230 at the command's end. */
void VillagerTalkObject_Motion16(VillagerTalk *talk, int event)
{
    (void) event;
    SceneCommand_RequestMotion16(&talk->scene);
    func_0202dbf0(talk, data_020d9230);
}
CLEAN_AS(func_020253a0, VillagerTalkObject_Motion16)

/* func_020253bc: a line of the set data_020c8ad0, or data_020c8ac0 for an object of type 1. */
void VillagerTalkObject_Line8ad0(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, object_texts_fish(talk, &data_020c8ad0, &data_020c8ac0));
}
CLEAN_AS(func_020253bc, VillagerTalkObject_Line8ad0)

/* The villager object's item emptied and that sent to the others in the session. */
static void object_clear_item(VillagerTalk *talk)
{
    VillagerObject_ClearItem(object_villager_object(talk));
    SessionVillager_SendObjectClear(object_record(talk));
}

/* func_02025430: a line of the set data_020c8d38, or data_020c8cd0 for an object of type 1;
 * then the villager object's item emptied. */
void VillagerTalkObject_LineClearItem(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, object_texts_fish(talk, &data_020c8d38, &data_020c8cd0));
    object_clear_item(talk);
}
CLEAN_AS(func_02025430, VillagerTalkObject_LineClearItem)

/* func_020254bc: the talk told to show its next line, then the line of the table data_021c2dac
 * said. */
void VillagerTalkObject_Say2dac(VillagerTalk *talk)
{
    object_next_line(talk);
    object_say(talk, data_021c2dac);
}
CLEAN_AS(func_020254bc, VillagerTalkObject_Say2dac)

/* func_0202551c: the item of the pocket the pockets screen gave taken and the pocket emptied
 * (data_020d91c0 next), or the line of data_021c2adc said. */
void VillagerTalkObject_TakePocket91c0(VillagerTalk *talk)
{
    object_take_pocket(talk, data_020d91c0, 1);
}
CLEAN_AS(func_0202551c, VillagerTalkObject_TakePocket91c0)

/* For an object of the catch `type`: the line of the table data_021c2d94 said when the
 * villager object's item is in first-last, else the pockets screen opened on the pockets
 * holding the talk object's item (func_02029a18), then `next`. */
static void object_say_or_ask(VillagerTalk *talk, u16 first, u16 last, MemberPointer next)
{
    u16 item = *VillagerObject_Item(object_villager_object(talk));
    if (item >= first && item <= last) {
        object_say(talk, data_021c2d94);
    } else {
        object_ask_mask(talk, func_02029a18(ItemObject_Item(func_0202d9c4(talk))));
        object_open_pockets(talk, next);
    }
}

/* func_020255d8: for an object of type 0, the line of data_021c2d94 said when the villager
 * object's item is an insect, else the pockets screen opened (data_020d8f38 next); for type 1
 * the same for a fish (data_020d8fd0 next). Nothing for other types. */
void VillagerTalkObject_SayOrAskCatch(VillagerTalk *talk)
{
    switch (object_type(talk)) {
        case VILLAGER_TALK_OBJECT_TYPE_INSECT:
            object_say_or_ask(talk, VILLAGER_TALK_OBJECT_INSECT_FIRST, VILLAGER_TALK_OBJECT_INSECT_LAST, data_020d8f38);
            break;
        case VILLAGER_TALK_OBJECT_TYPE_FISH:
            object_say_or_ask(talk, VILLAGER_TALK_OBJECT_FISH_FIRST, VILLAGER_TALK_OBJECT_FISH_LAST, data_020d8fd0);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020255d8, VillagerTalkObject_SayOrAskCatch)

/* func_02025738: a line of the set data_020c8ce0, or data_020c8ad8 for an object of type 1;
 * then data_020d8f90 run at the last message. */
void VillagerTalkObject_Line8ce0(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, object_texts_fish(talk, &data_020c8ce0, &data_020c8ad8));
    talk->on_last_message = data_020d8f90;
}
CLEAN_AS(func_02025738, VillagerTalkObject_Line8ce0)

/* func_020257c0: the villager's motion 17, then the villager object's item emptied. */
void VillagerTalkObject_Motion17ClearItem(VillagerTalk *talk)
{
    SceneCommand_RequestMotion17(&talk->scene);
    object_clear_item(talk);
}
CLEAN_AS(func_020257c0, VillagerTalkObject_Motion17ClearItem)

/* func_020257f0: a line of the set data_020c8b58, or data_020c8a58 for an object of type 1;
 * then data_020d9398 run at the last message. */
void VillagerTalkObject_Line8b58(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, object_texts_fish(talk, &data_020c8b58, &data_020c8a58));
    talk->on_last_message = data_020d9398;
}
CLEAN_AS(func_020257f0, VillagerTalkObject_Line8b58)

/* func_02025878: the reward given and the item at 0x124 kept by the villager, then the group
 * numbered by the talk's message of the set data_020c8d58, or data_020c8ae8 for an object of
 * type 1, and the sound 0x5f. */
void VillagerTalkObject_LineKeepItem8d58(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_reward_and_keep(talk);
    const VillagerTalkObjectTexts *texts = object_texts_fish(talk, &data_020c8d58, &data_020c8ae8);
    object_draw(talk, texts->texts, texts->count, talk->message, 0);
    object_name(talk, out);
    talk->sound = VILLAGER_TALK_OBJECT_SOUND_5F;
}
CLEAN_AS(func_02025878, VillagerTalkObject_LineKeepItem8d58)

/* func_02025954: the line of the table data_021c2d34 said while the talk is on the message
 * data_021f43f8. */
void VillagerTalkObject_SayIfOn2d34(VillagerTalk *talk)
{
    object_say_if_on(talk, data_021c2d34);
}
CLEAN_AS(func_02025954, VillagerTalkObject_SayIfOn2d34)

/* func_020259a8: the pocket the pockets screen gave emptied, the villager's motion 16, then
 * data_020d8f28 at the command's end. */
void VillagerTalkObject_EmptyPocketMotion16(VillagerTalk *talk)
{
    object_empty_pocket();
    SceneCommand_RequestMotion16(&talk->scene);
    func_0202dbf0(talk, data_020d8f28);
}
CLEAN_AS(func_020259a8, VillagerTalkObject_EmptyPocketMotion16)

/* func_020259e4: a line of the set data_020c8aa0, or data_020c8ae0 for an object of type 1. */
void VillagerTalkObject_Line8aa0(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, object_texts_fish(talk, &data_020c8aa0, &data_020c8ae0));
}
CLEAN_AS(func_020259e4, VillagerTalkObject_Line8aa0)

/* func_02025a58: the value in bells (func_0204c878) of the item at 0x124 against that of the
 * villager object's item (0 for none): the table data_021c2d64 when they are equal,
 * data_021c2d1c when the item at 0x124 is worth more, else data_021c2d4c; the item's name in
 * slot 2 and the villager object's in slot 3; then the talk told to show its next line and the
 * line said.
 * QUIRK: the time is read (DateTime_Now) and not used. */
void VillagerTalkObject_SayByPrice(VillagerTalk *talk)
{
    DateTime now = {0};
    int value = 0;
    int object_value = 0;
    DateTime_Now(&now);
    if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
        value = func_0204c878(&talk->item);
    }
    u16 object_item = *VillagerObject_Item(object_villager_object(talk));
    if (object_item != VILLAGER_TALK_OBJECT_NO_ITEM) {
        object_value = func_0204c878(&object_item);
    }
    if (value == object_value) {
        func_0202da88(talk, data_021c2d64);
    } else if (value > object_value) {
        func_0202da88(talk, data_021c2d1c);
    } else {
        func_0202da88(talk, data_021c2d4c);
    }
    if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
        SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &talk->item, 2, 7);
    }
    if (object_item != VILLAGER_TALK_OBJECT_NO_ITEM) {
        SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &object_item, 3, 7);
    }
    object_next_line(talk);
    object_say_set(talk);
}
CLEAN_AS(func_02025a58, VillagerTalkObject_SayByPrice)

/* func_02025b54: the item of the pocket the pockets screen gave taken (data_020d92e8 next), or
 * the line of data_021c2adc said. */
void VillagerTalkObject_TakePocket92e8(VillagerTalk *talk)
{
    object_take_pocket(talk, data_020d92e8, 0);
}
CLEAN_AS(func_02025b54, VillagerTalkObject_TakePocket92e8)

/* func_02025bf8: the pockets screen opened on the insects (the predicate func_0202a17c) for an
 * object of type 0, else on the fish (func_0202a12c), then data_020d92f0 at the command's
 * end. */
void VillagerTalkObject_AskPocketCatch(VillagerTalk *talk)
{
    if (object_type(talk) == VILLAGER_TALK_OBJECT_TYPE_INSECT) {
        object_ask_predicate(talk, func_0202a17c);
    } else {
        object_ask_predicate(talk, func_0202a12c);
    }
    object_open_pockets(talk, data_020d92f0);
}
CLEAN_AS(func_02025bf8, VillagerTalkObject_AskPocketCatch)

/* func_02025c48: a line of the set data_020d92f8, its texts by the villager object's step
 * (data_020d9dd4, steps 0-6), when there are texts; `out` names the talk's text and message
 * in any case. */
void VillagerTalkObject_LineByStep9dd4(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkObjectTexts texts = data_020d92f8;
    int step = VillagerObject_Step(object_villager_object(talk));
    if (step < 7) {
        texts.texts = data_020d9dd4[step];
    }
    if (texts.texts != 0) {
        object_draw(talk, texts.texts, texts.count, 0, 0);
    }
    object_name(talk, out);
}
CLEAN_AS(func_02025c48, VillagerTalkObject_LineByStep9dd4)

/* func_02025cd8: the line of the table data_021c2cec said while the talk is on the message
 * data_021f43f8. */
void VillagerTalkObject_SayIfOn2cec(VillagerTalk *talk)
{
    object_say_if_on(talk, data_021c2cec);
}
CLEAN_AS(func_02025cd8, VillagerTalkObject_SayIfOn2cec)

/* func_02025d2c: a line of the set data_020d9308, its texts from the table of the talk
 * object's place in its group (data_020d9d10, places 0-4) at the villager object's step, when
 * the step is below the steps of the object's type; `out` names the talk's text and message in
 * any case. */
void VillagerTalkObject_LineByPlaceStep(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkObjectTexts texts = data_020d9308;
    int step = VillagerObject_Step(object_villager_object(talk));
    int type = object_type(talk);
    int place = 0;
    ItemObject_PlaceInGroup(func_0202d9c4(talk), &place);
    if (step < VillagerObject_StepsForType(type) && place < VILLAGER_TALK_OBJECT_GROUP_PLACES) {
        texts.texts = ((const u32 *) (uintptr_t) data_020d9d10[place])[step];
    }
    if (texts.texts != 0) {
        object_draw(talk, texts.texts, texts.count, 0, 0);
    }
    object_name(talk, out);
}
CLEAN_AS(func_02025d2c, VillagerTalkObject_LineByPlaceStep)

/* The villager object set from the item at 0x124 for `player`: of the talk object's type, as a
 * fresh one, when the villager object's object is not in use, else of its own type; the same
 * sent to the others in the session for `slot`, then the object of the villager's state entry
 * emptied. */
static void object_start(VillagerTalk *talk, int with_player)
{
    u8 *record = object_record(talk);
    int type;
    u8 fresh = 0;
    if (ItemObject_IsInUse(object_villager_item_object(talk)) == 0) {
        type = object_type(talk);
        fresh = 1;
    } else {
        type = ItemObject_Type(object_villager_item_object(talk));
    }
    if (with_player) {
        const DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
        VillagerObject_Set(object_villager_object(talk), (u32) type, &talk->item, player, fresh);
        SessionVillager_SendObject(record, type, &talk->item, data_020ccf94->local_slot, fresh);
    } else {
        VillagerObject_Set(object_villager_object(talk), (u32) type, &talk->item, NULL, fresh);
        SessionVillager_SendObject(record, type, &talk->item, 4, fresh);
    }
    ItemObject_Clear((ItemObject *) (void *) VillagerState_Object(VillagerStatus_StateEntry(record)));
}

/* func_02025de8: the villager object set from the item at 0x124 with no player, sent to the
 * others in the session with slot 4 (none), and the object of the villager's state entry
 * emptied. */
void VillagerTalkObject_Start(VillagerTalk *talk)
{
    object_start(talk, 0);
}
CLEAN_AS(func_02025de8, VillagerTalkObject_Start)

/* func_02025e70: a line of the set data_020c8d48, then data_020d9370 set at 0xe8. */
void VillagerTalkObject_Line8d48(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, &data_020c8d48);
    func_0202db48(talk, data_020d9370);
}
CLEAN_AS(func_02025e70, VillagerTalkObject_Line8d48)

/* func_02025ee0: the villager object set from the item at 0x124 for the current player, sent
 * to the others in the session with this system's slot, and the object of the villager's state
 * entry emptied. */
void VillagerTalkObject_StartForPlayer(VillagerTalk *talk)
{
    object_start(talk, 1);
}
CLEAN_AS(func_02025ee0, VillagerTalkObject_StartForPlayer)

/* func_02025f78: a line of the set data_020c8d50 and the sound 0x5e. */
void VillagerTalkObject_Line8d50(VillagerTalk *talk, VillagerTalkLine *out)
{
    object_line(talk, out, &data_020c8d50);
    talk->sound = VILLAGER_TALK_OBJECT_SOUND_5E;
}
CLEAN_AS(func_02025f78, VillagerTalkObject_Line8d50)

/* func_02025fe4: VillagerTalkObject_StartForPlayer. */
void VillagerTalkObject_StartForPlayerAgain(VillagerTalk *talk)
{
    VillagerTalkObject_StartForPlayer(talk);
}
CLEAN_AS(func_02025fe4, VillagerTalkObject_StartForPlayerAgain)

/* func_02025fec: two choices offered with cancel choice 1: message 0x1f running data_021c2ca4
 * and message 0x20 running data_021c2cbc; the reply data_020d9380; the talk's byte 0x18
 * set. */
void VillagerTalkObject_OfferChoices1f(VillagerTalk *talk)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 0, 0x1f, 0x1f, (int) (uintptr_t) data_021c2ca4);
    TalkChoices_Set((int) (uintptr_t) talk, &list, 1, 0x20, 0x20, (int) (uintptr_t) data_021c2cbc);
    list.count = 2;
    list.cancel = 1;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
    func_0202da74(talk, data_020d9380);
    func_02068388(object_talk(talk), 1);
}
CLEAN_AS(func_02025fec, VillagerTalkObject_OfferChoices1f)

/* func_02026058: the names the talk object's type puts into the talk's slots (the step is the
 * villager object's when its object is in use, else 0), then data_020d9388 set at 0xe8:
 *   types 0 and 1: the item at 0x124 in slot 0;
 *   type 2: without an item at 0x124 one picked for the step (VillagerTalkObject_PickByStep);
 *     from step 2 the index (ItemAttributes_KindIndex) of the villager object's kind, or of
 *     the item's kind when the object has none and the item is of 0x450c-0x45db, as a byte in
 *     slot 0 when it has one;
 *   type 3: without an item at 0x124 one picked for the step
 *     (VillagerTalkObject_PickClothesByStep); the item in slot 0.
 * QUIRK: the time is read (DateTime_Now) and not used. */
void VillagerTalkObject_PutItemNames(VillagerTalk *talk)
{
    DateTime now = {0};
    int step = 0;
    if (ItemObject_IsInUse(object_villager_item_object(talk)) != 0) {
        step = VillagerObject_Step(object_villager_object(talk));
    }
    DateTime_Now(&now);
    switch (object_type(talk)) {
        case VILLAGER_TALK_OBJECT_TYPE_INSECT:
        case VILLAGER_TALK_OBJECT_TYPE_FISH:
            if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
                SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &talk->item, 0, 7);
            }
            break;
        case VILLAGER_TALK_OBJECT_TYPE_KIND_ITEM: {
            if (talk->item == VILLAGER_TALK_OBJECT_NO_ITEM) {
                u16 picked;
                VillagerTalkObject_PickByStep(&picked, talk, (unsigned int) step);
                talk->item = picked;
            }
            if (step < 2) {
                break;
            }
            int kind = VillagerObject_Kind(object_villager_object(talk));
            if (kind >= VILLAGER_OBJECT_KIND_NONE && talk->item >= ITEM_ATTRIBUTES_KIND_ITEM_FIRST &&
                talk->item <= ITEM_ATTRIBUTES_KIND_ITEM_LAST) {
                kind = FurnitureInfo_MuseumKind(&talk->item);
            }
            if (kind < VILLAGER_OBJECT_KIND_NONE) {
                int index = ItemAttributes_KindIndex(kind);
                if (index != -1) {
                    u8 bytes[2] = {(u8) index, 0};
                    SceneBase_PutBytes(object_base(talk), 0, &bytes[0], (int) (uintptr_t) data_020d9f94, &bytes[1]);
                }
            }
            break;
        }
        case VILLAGER_TALK_OBJECT_TYPE_CLOTHES:
            if (talk->item == VILLAGER_TALK_OBJECT_NO_ITEM) {
                u16 picked;
                VillagerTalkObject_PickClothesByStep(&picked, talk, (unsigned int) step);
                talk->item = picked;
            }
            if (talk->item != VILLAGER_TALK_OBJECT_NO_ITEM) {
                SceneBase_PutItemName(object_base(talk), (int) (uintptr_t) &talk->item, 0, 7);
            }
            break;
        default:
            break;
    }
    func_0202db48(talk, data_020d9388);
}
CLEAN_AS(func_02026058, VillagerTalkObject_PutItemNames)

/* func_020261b0: an item picked by the game's function for `step` (data_020c8f24, steps 0-4)
 * with the villager's object and town record, or 0xfff1 when there is none. */
void VillagerTalkObject_PickByStep(u16 *out, VillagerTalk *talk, unsigned int step)
{
    if (step < 5 && data_020c8f24[step] != 0) {
        u32 function = data_020c8f24[step];
        u8 *record = object_record(talk);
        VillagerObject *object = VillagerObject_OfRecord((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record));
        ((void (*)(u16 *, VillagerObject *, u8 *))(uintptr_t) function)(out, object, record);
        return;
    }
    *out = VILLAGER_TALK_OBJECT_NO_ITEM;
}
CLEAN_AS(func_020261b0, VillagerTalkObject_PickByStep)

/* func_020261f8: the item of the villager object's kind (offset 0), or 0xfff1 when it has none.
 * Without a kind, one the villager's house items miss is picked
 * (ItemAttributes_PickMissingKind), set and sent to the others in the session. */
void VillagerTalkObject_KindItem(u16 *out, VillagerObject *object, u8 *villager)
{
    unsigned int kind = VillagerObject_Kind(object);
    if (kind == VILLAGER_OBJECT_KIND_NONE) {
        kind = ItemAttributes_PickMissingKind(VillagerHouseItems_Items(villager), VILLAGER_HOUSE_ITEMS);
        VillagerObject_SetKind(object, (u8) kind);
        SessionVillager_SendObjectByte2F(villager, (int) kind);
    }
    if (kind < VILLAGER_OBJECT_KIND_NONE) {
        ItemAttributes_KindItem(out, kind, 0);
    } else {
        *out = VILLAGER_TALK_OBJECT_NO_ITEM;
    }
}
CLEAN_AS(func_020261f8, VillagerTalkObject_KindItem)

/* func_02026250: the place of the item among the items of its kind
 * (VillagerTalkObject_KindPart with FurnitureInfo_MuseumKind). */
int VillagerTalkObject_ItemPart(u16 *item)
{
    return VillagerTalkObject_KindPart(item, FurnitureInfo_MuseumKind(item));
}
CLEAN_AS(func_02026250, VillagerTalkObject_ItemPart)

/* func_02026268: for an item of 0x450c-0x45db, its place (0-2) after the first of the 52 items
 * (four codes apart) whose kind (FurnitureInfo_MuseumKind) is `kind`; -1 for other items, when
 * no item is of the kind, or when the item is not within the three from that first one. */
int VillagerTalkObject_KindPart(u16 *item, int kind)
{
    if (*item < ITEM_ATTRIBUTES_KIND_ITEM_FIRST || *item > ITEM_ATTRIBUTES_KIND_ITEM_LAST) {
        return -1;
    }
    int index = (*item - ITEM_ATTRIBUTES_KIND_ITEM_FIRST) >> 2;
    for (int i = 0; i < ITEM_ATTRIBUTES_KIND_ITEMS; i++) {
        u16 code = (u16) (ITEM_ATTRIBUTES_KIND_ITEM_FIRST + i * 4);
        if (FurnitureInfo_MuseumKind(&code) == kind) {
            for (int part = 0; part < 3; part++) {
                if (index == i + part) {
                    return part;
                }
            }
            return -1;
        }
    }
    return -1;
}
CLEAN_AS(func_02026268, VillagerTalkObject_KindPart)

/* func_020262fc: an item of 0x450c-0x45db drawn twice (func_02063414: once for no player, once
 * for the current player); the first when the second is not of the range, or half of the time
 * (a random number below 10 is even) when both are; the second when the first is not. */
void VillagerTalkObject_DrawKindItem(u16 *out, int unused_object, int unused_villager)
{
    (void) unused_object;
    (void) unused_villager;
    u16 drawn[2];
    func_02063414(&drawn[0], ITEM_ATTRIBUTES_KIND_ITEM_FIRST, ITEM_ATTRIBUTES_KIND_ITEMS, 0, 0, NULL, 1, 0xa, 0, 1);
    func_02063414(&drawn[1], ITEM_ATTRIBUTES_KIND_ITEM_FIRST, ITEM_ATTRIBUTES_KIND_ITEMS, 0, 0, PlayerRecords_Current(), 0,
                  0xa, 0, 1);
    *out = VILLAGER_TALK_OBJECT_NO_ITEM;
    if (drawn[0] >= ITEM_ATTRIBUTES_KIND_ITEM_FIRST && drawn[0] <= ITEM_ATTRIBUTES_KIND_ITEM_LAST) {
        if (drawn[1] >= ITEM_ATTRIBUTES_KIND_ITEM_FIRST && drawn[1] <= ITEM_ATTRIBUTES_KIND_ITEM_LAST &&
            (func_020644cc(10) & 1) != 0) {
            *out = drawn[1];
        } else {
            *out = drawn[0];
        }
    } else {
        *out = drawn[1];
    }
}
CLEAN_AS(func_020262fc, VillagerTalkObject_DrawKindItem)

/* func_020263b0: an item picked by the game's function for `step` (data_020c8f7c, steps 0-6)
 * with the villager data's byte 0x29 and a copy of the villager's clothes, or 0xfff1 when there
 * is none. */
void VillagerTalkObject_PickClothesByStep(u16 *out, VillagerTalk *talk, unsigned int step)
{
    u32 function;
    if (step < 7 && (function = data_020c8f7c[step]) != 0) {
        u8 *record = object_record(talk);
        const u8 *data = VillagerData_Byte29(record);
        u16 clothes = *TownVillager_Clothes(record);
        ((void (*)(u16 *, const u8 *, u16 *))(uintptr_t) function)(out, data, &clothes);
    } else {
        *out = VILLAGER_TALK_OBJECT_NO_ITEM;
    }
}
CLEAN_AS(func_020263b0, VillagerTalkObject_PickClothesByStep)

/* Clothes (0x11a8-0x12a7) drawn by func_02063414 for the current player with `which` (0 or 1)
 * and the byte at `data`. */
static void object_draw_clothes(u16 *item, u8 *data, int clothes, u8 *player, int which)
{
    func_02063414(item, VILLAGER_TALK_OBJECT_CLOTHES_FIRST, VILLAGER_TALK_OBJECT_CLOTHES_COUNT, clothes, 1, player, which,
                  *data, 0, 1);
}

/* func_02026408: clothes drawn for the current player (func_02063414 with 0), or when that gave
 * none drawn again with 1. */
void VillagerTalkObject_DrawClothes(u16 *out, u8 *data, int clothes)
{
    u16 drawn[2];
    *out = VILLAGER_TALK_OBJECT_NO_ITEM;
    object_draw_clothes(&drawn[0], data, clothes, PlayerRecords_Current(), 0);
    *out = drawn[0];
    if (*out == VILLAGER_TALK_OBJECT_NO_ITEM) {
        object_draw_clothes(&drawn[1], data, clothes, PlayerRecords_Current(), 1);
        *out = drawn[1];
    }
}
CLEAN_AS(func_02026408, VillagerTalkObject_DrawClothes)

/* func_02026484: clothes drawn for no player (func_02063414 with 0). */
void VillagerTalkObject_DrawClothesAnyPlayer(u16 *out, u8 *data, int clothes)
{
    object_draw_clothes(out, data, clothes, NULL, 0);
}
CLEAN_AS(func_02026484, VillagerTalkObject_DrawClothesAnyPlayer)
