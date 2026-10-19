/* Members of the town villagers' talk scenes for the talk objects of types 10 and 19, from a
 * block of the player's villager part (villager_talk_part.h). */
#include "villager_talk_part.h"

#include "clean.h"
#include "group_params.h"
#include "item_object.h"
#include "item_record.h"
#include "lookups.h"
#include "mail.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "room_score.h"
#include "scene_base.h"
#include "scene_command.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_data.h"
#include "villager_items.h"
#include "villager_memory_entry.h"
#include "villager_mode.h"
#include "villager_object.h"
#include "villager_pairs.h"
#include "villager_part_block.h"
#include "villager_town.h"
#include "item_traits.h"
#include "letter.h"
#include "main_random.h"
#include "talk_item_draw.h"
#include "talk_object.h"
#include "villager_talk_approach.h"
#include "villager_talk_scene.h"

/* The villager scene object's town record (town_villager.h). */
#define VILLAGER_TALK_PART_RECORD 0x830
/* The talk's block of the player's villager part (or 0), and its villager object. */
#define VILLAGER_TALK_PART_BLOCK 0x160
#define VILLAGER_TALK_PART_VILLAGER_OBJECT 0x164

#define VILLAGER_TALK_PART_NO_ITEM 0xfff1
#define VILLAGER_TALK_PART_NO_SLOT (-1)

/* The talk object's types handled here (step types of band 1, villager_part_block.h). */
#define VILLAGER_TALK_PART_TYPE_10 10
#define VILLAGER_TALK_PART_TYPE_19 19
/* The villager object's types of group 0 that matter here (villager_talk_object.h). */
#define VILLAGER_TALK_PART_TYPE_INSECT 0
#define VILLAGER_TALK_PART_TYPE_FISH 1
#define VILLAGER_TALK_PART_TYPE_FURNITURE 4
#define VILLAGER_TALK_PART_GROUP_PLACES 5

/* The item type 19 goes with (villager_part_block.h). */
#define VILLAGER_TALK_PART_LETTER_ITEM 0x1565
#define VILLAGER_TALK_PART_CLOTHES_FIRST 0x11a8
#define VILLAGER_TALK_PART_CLOTHES_LAST 0x12a7
#define VILLAGER_TALK_PART_BAG_FIRST 0x1492
#define VILLAGER_TALK_PART_BAG_LAST 0x14fd
/* The bag of bells func_0204c120 gives none for. */
#define VILLAGER_TALK_PART_SMALLEST_BAG 0x1492

/* The villager's reaction to clothes (the block's byte 0x2c). */
#define VILLAGER_TALK_PART_REACT_STYLE0 0
#define VILLAGER_TALK_PART_REACT_OTHER 1
#define VILLAGER_TALK_PART_REACT_STYLE1 2

/* The state func_02065ec0 gives a letter that picks the first table. */
#define VILLAGER_TALK_PART_LETTER_STATE_7 7

/* A bells reward: 500 plus four times RoomScore_HouseLowX, rounded. */
#define VILLAGER_TALK_PART_BELLS_BASE 500
/* The chances of type 19's start, out of 100: below 20 an item of the villager, below 40 bells. */
#define VILLAGER_TALK_PART_ITEM_CHANCE 20
#define VILLAGER_TALK_PART_BELLS_CHANCE 40

/* The talk's memory of the player at least this fond picks the first line table. */
#define VILLAGER_TALK_PART_FOND 0x40

/* Bond changes between the block's villagers and the talk's villager. */
#define VILLAGER_TALK_PART_BOND_UP 20
#define VILLAGER_TALK_PART_BOND_DOWN (-20)
#define VILLAGER_TALK_PART_BOND_SMALL_UP 10
#define VILLAGER_TALK_PART_BOND_SMALL_DOWN (-10)

#define VILLAGER_TALK_PART_SOUND_5E 0x5e
#define VILLAGER_TALK_PART_SOUND_5F 0x5f

/* A text set of the talk lines: its texts and the lines a group has. */
typedef struct VillagerTalkPartTexts {
    u32 texts;
    u8 count;
} VillagerTalkPartTexts;

extern const VillagerTalkPartTexts data_020d8ff0;
extern const VillagerTalkPartTexts data_020c8d88;
extern const VillagerTalkPartTexts data_020c8d78;
extern const VillagerTalkPartTexts data_020c8d90;
extern const VillagerTalkPartTexts data_020c8b68;
extern const VillagerTalkPartTexts data_020c8d98;
extern const VillagerTalkPartTexts data_020c8da0;
extern const VillagerTalkPartTexts data_020c8da8;
extern const VillagerTalkPartTexts data_020c8dc8;
extern const VillagerTalkPartTexts data_020c8db8;
extern const VillagerTalkPartTexts data_020c8de0;
extern const VillagerTalkPartTexts data_020c8dd0;
extern const VillagerTalkPartTexts data_020c8df0;
extern const VillagerTalkPartTexts data_020c8de8;
extern const VillagerTalkPartTexts data_020c8df8;
extern const VillagerTalkPartTexts data_020c8e00;
extern const VillagerTalkPartTexts data_020c8e10;
extern const VillagerTalkPartTexts data_020c8e20;
extern const VillagerTalkPartTexts data_020c8e28;
extern const VillagerTalkPartTexts data_020c8ba8;
extern const VillagerTalkPartTexts data_020c8e48;
extern const VillagerTalkPartTexts data_020c8e40;
extern const VillagerTalkPartTexts data_020c8980;
extern const VillagerTalkPartTexts data_020c8978;
extern const VillagerTalkPartTexts data_020c8998;
extern const VillagerTalkPartTexts data_020c8a40;
extern const VillagerTalkPartTexts data_020c8990;
extern const VillagerTalkPartTexts data_020c8988;
extern const VillagerTalkPartTexts data_020c8e38;
extern const VillagerTalkPartTexts data_020c89b0;

/* The texts by the place of the talk's object in its group: five addresses of tables by the
 * villager object's step. */
extern const u32 data_020d9cc0[VILLAGER_TALK_PART_GROUP_PLACES];
/* What VillagerTalkPart_LineByPlaceStep9cc0 hands SceneBase_PutBytes in the place of the size. */
extern u8 data_020d9fa0[];

/* Tables of three member pointers for 0xb0 to 0xc0 (func_0202da88). */
extern const MemberPointer data_021c2c74[3];
extern const MemberPointer data_021c2c5c[3];
extern const MemberPointer data_021c2c44[3];
extern const MemberPointer data_021c29d4[][3];
extern const MemberPointer data_021c2b9c[3];
extern const MemberPointer data_021c2bb4[3];
extern const MemberPointer data_021c2b24[3];
extern const MemberPointer data_021c2b3c[3];
extern const MemberPointer data_021c2b54[3];
extern const MemberPointer data_021c2b84[3];
extern const MemberPointer data_021c2b6c[3];
extern const MemberPointer data_021c2adc[3];
extern const MemberPointer data_021c2af4[3];
extern const MemberPointer data_021c2a7c[3];
extern const MemberPointer data_021c2a94[3];

/* Member pointer constants the functions here store. */
extern const MemberPointer data_020d9460;
extern const MemberPointer data_020d9488;
extern const MemberPointer data_020d9068;
extern const MemberPointer data_020d94a0; /* VillagerTalkPart_SayNextLine */
extern const MemberPointer data_020d94a8;
extern const MemberPointer data_020d94b0;
extern const MemberPointer data_020d9080;
extern const MemberPointer data_020d94c8;
extern const MemberPointer data_020d94d8;
extern const MemberPointer data_020d8e48;
extern const MemberPointer data_020d8dc8;
extern const MemberPointer data_020d8e08;
extern const MemberPointer data_020d8e00;
extern const MemberPointer data_020d8df0;
extern const MemberPointer data_020d90b8;
extern const MemberPointer data_020d8f08;

/* The choices VillagerTalkPart_StartByType offers come in three message numbers each. */
#define VILLAGER_TALK_PART_CHOICES 3
#define VILLAGER_TALK_PART_CHOICE_FIRST 0x24
/* The tables of data_021c29d4 VillagerTalkPart_SayChoice29d4 picks from by the choice. */
#define VILLAGER_TALK_PART_CHOICE_TABLE 0x17

extern VillagerTown data_021e5a2c; /* the town's villagers */

/* The pockets predicate VillagerTalkPart_AskPocketsByType hands the scene (the game's
 * VillagerTalkPart_IsClothesInState2). */
extern u16 func_02027d38(u16 *item, int state);

static u8 *part_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneBase *part_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static u8 *part_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_PART_RECORD);
}

static VillagerPartBlock *part_block(const VillagerTalk *talk)
{
    return *(VillagerPartBlock **) (void *) ((u8 *) talk + VILLAGER_TALK_PART_BLOCK);
}

static ItemObject *part_block_object(const VillagerTalk *talk)
{
    return (ItemObject *) (void *) VillagerPartBlock_Object(part_block(talk));
}

static VillagerObject *part_villager_object(const VillagerTalk *talk)
{
    return *(VillagerObject **) (void *) ((u8 *) talk + VILLAGER_TALK_PART_VILLAGER_OBJECT);
}

static int part_type(VillagerTalk *talk)
{
    return ItemObject_Type((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
}

static int part_is_clothes(u16 item)
{
    return item >= VILLAGER_TALK_PART_CLOTHES_FIRST && item <= VILLAGER_TALK_PART_CLOTHES_LAST;
}

static int part_is_bag(u16 item)
{
    return item >= VILLAGER_TALK_PART_BAG_FIRST && item <= VILLAGER_TALK_PART_BAG_LAST;
}

static PlayerPockets *part_pockets(void)
{
    return PlayerRecord_Pockets(PlayerRecords_Current());
}

/* The line of `texts` drawn for the personality of the talk's villager into the talk's text
 * and message. */
static void part_draw(VillagerTalk *talk, const VillagerTalkPartTexts *texts)
{
    VillagerTalkScene_DrawLine(talk, talk->text, &talk->message, VILLAGER_TALK_TEXT_SIZE,
                               NpcId_Personality(TownVillager_NpcId(part_record(talk))), (int) texts->texts, texts->count, 0,
                               0);
}

/* `out` names the talk's text and message. */
static void part_name(VillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) talk->text;
    out->message = talk->message;
}

static void part_line(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkPartTexts *texts)
{
    part_draw(talk, texts);
    part_name(talk, out);
}

/* The line of `texts` when there are any; `out` names the talk's text either way. */
static void part_line_if(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkPartTexts *texts)
{
    if (texts != NULL) {
        part_draw(talk, texts);
    }
    part_name(talk, out);
}

/* The talk told to show its next line (word 8 of the talk), when there is a talk. */
static void part_next_line(VillagerTalk *talk)
{
    if (talk->scene.talk != NULL) {
        talk->scene.talk[2] = 1;
    }
}

/* The line of the line function at 0xb0, when there is one.
 * REQUIRES: the tables set hold a line function (the original then hands on an unset line). */
static VillagerTalkLine part_set_line(VillagerTalk *talk)
{
    VillagerTalkLine line = {0};
    if (talk->line.function != 0) {
        void *self = MemberPointer_Object(&talk->line, talk);
        ((void (*)(void *, VillagerTalkLine *))(uintptr_t) MemberPointer_Code(&talk->line, self))(self, &line);
    }
    return line;
}

/* The line of the line function given to the talk. */
static void part_say_set(VillagerTalk *talk)
{
    VillagerTalkLine line = part_set_line(talk);
    u8 message = line.message;
    TalkObject_SetMessage((TalkObject *) (void *) part_talk(talk), &message, (const char *) (uintptr_t) ((int) line.text));
}

/* The line of the line function given to the talk only while it is on the message
 * data_021f43f8 (func_02068484). */
static void part_say_set_if_on(VillagerTalk *talk)
{
    VillagerTalkLine line = part_set_line(talk);
    u8 message = line.message;
    TalkObject_SetMessageIfNone((TalkObject *) (void *) part_talk(talk), &message,
                                (const char *) (uintptr_t) ((int) line.text));
}

static void part_say_if_on(VillagerTalk *talk, const MemberPointer *table)
{
    VillagerTalkScene_SetLines(talk, table);
    part_say_set_if_on(talk);
}

/* The talk's text set by the type of the talk's object: `for_10`, `for_19`, else none. */
static const VillagerTalkPartTexts *part_texts_by_type(VillagerTalk *talk, const VillagerTalkPartTexts *for_10,
                                                       const VillagerTalkPartTexts *for_19)
{
    switch (part_type(talk)) {
        case VILLAGER_TALK_PART_TYPE_10:
            return for_10;
        case VILLAGER_TALK_PART_TYPE_19:
            return for_19;
        default:
            return NULL;
    }
}

/* The bond of the pair `first` and `second` changed by `amount`. */
static void part_bond(const NpcId *first, const NpcId *second, int amount)
{
    VillagerPair_AddBond(&data_021e5a2c, first, second, amount);
}

/* A bag of 500 bells plus four times RoomScore_HouseLowX, rounded to tens, as the item at 0x124
 * (the bells kept at 0x1a0). */
static void part_bells_item(VillagerTalk *talk)
{
    u16 bag;
    talk->bells = RoomScore_HouseLowX() * 4 + VILLAGER_TALK_PART_BELLS_BASE;
    talk->bells = VillagerTalkApproach_RoundBells(talk->bells);
    VillagerTalkPart_BellBag(&bag, talk->bells);
    talk->item = bag;
}

/* An item drawn by func_0202d5e4 as the item at 0x124. */
static void part_drawn_item(VillagerTalk *talk)
{
    u16 drawn;
    TalkItemDraw_ThreeLists(&drawn, 0);
    talk->item = drawn;
}

/* A random item of the villager's items as the item at 0x124, taken from them when there is
 * one; whether there was. */
static int part_villager_item(VillagerTalk *talk)
{
    u16 item;
    VillagerItems_Random(&item, part_record(talk));
    talk->item = item;
    if (talk->item == VILLAGER_TALK_PART_NO_ITEM) {
        return 0;
    }
    VillagerItems_Remove(part_record(talk), &talk->item);
    return 1;
}

/* func_02026804: a line of the set data_020d8ff0 with its texts by the place of the talk's
 * object in its group (data_020d9cc0) and the villager object's step, when the step is below
 * the steps of the type. The step and type are the villager object's when its object is in
 * use, else step 0 and the talk object's type. For type 4 (furniture) the index of what the
 * villager likes (VillagerData_Like of VillagerMode_Counter7D7) goes into slot 0 as a byte;
 * for a type other than 0 and 1 the sound 0x5e is set. `out` names the talk's text either
 * way. */
void VillagerTalkPart_LineByPlaceStep9cc0(VillagerTalk *talk, VillagerTalkLine *out)
{
    VillagerTalkPartTexts texts = data_020d8ff0;
    VillagerObject *object = part_villager_object(talk);
    int step = 0;
    int type = part_type(talk);
    int place = 0;
    if (ItemObject_IsInUse((ItemObject *) (void *) VillagerObject_Base(object)) != 0) {
        step = VillagerObject_Step(part_villager_object(talk));
        type = ItemObject_Type((ItemObject *) (void *) VillagerObject_Base(part_villager_object(talk)));
    }
    ItemObject_PlaceInGroup((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk), &place);
    if (step < VillagerObject_StepsForType(type) && place < VILLAGER_TALK_PART_GROUP_PLACES) {
        texts.texts = ((const u32 *) (uintptr_t) data_020d9cc0[place])[step];
        if (type == VILLAGER_TALK_PART_TYPE_FURNITURE) {
            u8 *record = part_record(talk);
            u8 bytes[2];
            bytes[0] = Lookups_SlotIndex((const u8 *) VillagerData_Like(record, VillagerMode_Counter7D7(record)));
            bytes[1] = 0;
            SceneBase_PutBytes(part_base(talk), 0, &bytes[0], (int) (uintptr_t) data_020d9fa0, &bytes[1]);
        }
        if (type != VILLAGER_TALK_PART_TYPE_INSECT && type != VILLAGER_TALK_PART_TYPE_FISH) {
            talk->sound = VILLAGER_TALK_PART_SOUND_5E;
        }
    }
    if (texts.texts != 0) {
        part_draw(talk, &texts);
    }
    part_name(talk, out);
}
CLEAN_AS(func_02026804, VillagerTalkPart_LineByPlaceStep9cc0)

/* func_0202692c: a line of the set data_020c8d78 for type 19, else data_020c8d88; the block
 * cleared when there is one; the sound 0x5f. */
void VillagerTalkPart_LineClearBlock(VillagerTalk *talk, VillagerTalkLine *out)
{
    const VillagerTalkPartTexts *texts = &data_020c8d88;
    if (part_type(talk) == VILLAGER_TALK_PART_TYPE_19) {
        texts = &data_020c8d78;
    }
    part_line(talk, out, texts);
    if (part_block(talk) != NULL) {
        VillagerPartBlock_Clear(part_block(talk));
    }
    talk->sound = VILLAGER_TALK_PART_SOUND_5F;
}
CLEAN_AS(func_0202692c, VillagerTalkPart_LineClearBlock)

/* func_020269c8: the line of the table data_021c2c74 said while the talk is on its message. */
void VillagerTalkPart_Say2c74(VillagerTalk *talk)
{
    part_say_if_on(talk, data_021c2c74);
}
CLEAN_AS(func_020269c8, VillagerTalkPart_Say2c74)

/* func_02026a1c: the item at 0x124 handed to the current player: for a bag (0x1492-0x14fd) the
 * bells at 0x1a0 added to the pockets (in bags); else, when there is an item and a free pocket,
 * the item put there and marked in the player's item record. Then the item shown (motion
 * 13). */
void VillagerTalkPart_HandItem(VillagerTalk *talk)
{
    u8 *player = PlayerRecords_Current();
    PlayerPockets *pockets = PlayerRecord_Pockets(player);
    if (part_is_bag(talk->item)) {
        PlayerPockets_AddBells(pockets, talk->bells, 1);
    } else if (talk->item != VILLAGER_TALK_PART_NO_ITEM) {
        int slot = PlayerPockets_FreeSlot(pockets);
        if (slot != VILLAGER_TALK_PART_NO_SLOT) {
            PlayerPockets_SetSlot(pockets, &talk->item, slot, 0);
            ItemRecord_SetBit((ItemRecord *) (void *) PlayerRecord_ItemRecord(player), &talk->item, 0, 1);
        }
    }
    SceneCommand_RequestMotion13(&talk->scene, &talk->item, 0, 5, 0);
}
CLEAN_AS(func_02026a1c, VillagerTalkPart_HandItem)

/* func_02026ab4: the bells at 0x1a0 put into slot 1 for a bag (0x1492-0x14fd) at 0x124, else
 * the item's name; then a line of the set data_020c8d90. */
void VillagerTalkPart_LinePutItem(VillagerTalk *talk, VillagerTalkLine *out)
{
    if (part_is_bag(talk->item)) {
        SceneBase_PutCount(part_base(talk), talk->bells, 1, 4, 1, 0, 0);
    } else {
        SceneBase_PutItemName(part_base(talk), (int) (uintptr_t) &talk->item, 1, 7);
    }
    part_line(talk, out, &data_020c8d90);
}
CLEAN_AS(func_02026ab4, VillagerTalkPart_LinePutItem)

/* func_02026b64: the line of the table data_021c2c5c said while the talk is on its message. */
void VillagerTalkPart_Say2c5c(VillagerTalk *talk)
{
    part_say_if_on(talk, data_021c2c5c);
}
CLEAN_AS(func_02026b64, VillagerTalkPart_Say2c5c)

/* func_02026bb8: a line of the set data_020c8b68. */
void VillagerTalkPart_Line8b68(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8b68);
}
CLEAN_AS(func_02026bb8, VillagerTalkPart_Line8b68)

/* func_02026c1c: the line of the table data_021c2c44 when there is a current player with a free
 * pocket, else that of data_021c2c74, said while the talk is on its message. */
void VillagerTalkPart_SayByPocketRoom(VillagerTalk *talk)
{
    if (PlayerRecords_Current() != NULL && PlayerPockets_FreeSlot(part_pockets()) != VILLAGER_TALK_PART_NO_SLOT) {
        part_say_if_on(talk, data_021c2c44);
    } else {
        part_say_if_on(talk, data_021c2c74);
    }
}
CLEAN_AS(func_02026c1c, VillagerTalkPart_SayByPocketRoom)

static u8 part_reaction(VillagerTalk *talk)
{
    return *VillagerPartBlock_Byte2C(part_block(talk));
}

/* func_02026c9c: the reward at 0x124: for the reaction 2 an item drawn (func_0202d5e4); when
 * that is none, bells; then a line of the set data_020c8d98. */
void VillagerTalkPart_LineReward8d98(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 reaction = part_reaction(talk);
    talk->item = VILLAGER_TALK_PART_NO_ITEM;
    if (reaction == VILLAGER_TALK_PART_REACT_STYLE1) {
        part_drawn_item(talk);
    }
    if (talk->item == VILLAGER_TALK_PART_NO_ITEM) {
        part_bells_item(talk);
    }
    part_line(talk, out, &data_020c8d98);
}
CLEAN_AS(func_02026c9c, VillagerTalkPart_LineReward8d98)

/* func_02026d70: the reward at 0x124: for the reaction 0 a random item of the villager's
 * (taken from them), for 1 an item drawn (func_0202d5e4); when that is none, bells; then a line
 * of the set data_020c8da0. */
void VillagerTalkPart_LineReward8da0(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 reaction = part_reaction(talk);
    talk->item = VILLAGER_TALK_PART_NO_ITEM;
    switch (reaction) {
        case VILLAGER_TALK_PART_REACT_STYLE0:
            part_villager_item(talk);
            break;
        case VILLAGER_TALK_PART_REACT_OTHER:
            part_drawn_item(talk);
            break;
        default:
            break;
    }
    if (talk->item == VILLAGER_TALK_PART_NO_ITEM) {
        part_bells_item(talk);
    }
    part_line(talk, out, &data_020c8da0);
}
CLEAN_AS(func_02026d70, VillagerTalkPart_LineReward8da0)

/* func_02026e78: the reward at 0x124: for the reaction 0 an item drawn (func_0202d5e4), for 1
 * a random item of the villager's (taken from them), for others the villager's item or when it
 * has none an item drawn; when that is none, bells; then a line of the set data_020c8da8. */
void VillagerTalkPart_LineReward8da8(VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 reaction = part_reaction(talk);
    talk->item = VILLAGER_TALK_PART_NO_ITEM;
    switch (reaction) {
        case VILLAGER_TALK_PART_REACT_STYLE0:
            part_drawn_item(talk);
            break;
        case VILLAGER_TALK_PART_REACT_OTHER:
            part_villager_item(talk);
            break;
        default:
            if (part_villager_item(talk) == 0) {
                part_drawn_item(talk);
            }
            break;
    }
    if (talk->item == VILLAGER_TALK_PART_NO_ITEM) {
        part_bells_item(talk);
    }
    part_line(talk, out, &data_020c8da8);
}
CLEAN_AS(func_02026e78, VillagerTalkPart_LineReward8da8)

/* func_02026fc0: the reply to a choice of VillagerTalkPart_StartByType: the line of the table
 * 0x17 + choice of data_021c29d4 (choice 0 when it is not 0-2) said while the talk is on its
 * message. */
void VillagerTalkPart_SayChoice29d4(VillagerTalk *talk, int unused, int choice)
{
    (void) unused;
    if (choice < 0 || choice >= VILLAGER_TALK_PART_CHOICES) {
        choice = 0;
    }
    part_say_if_on(talk, data_021c29d4[VILLAGER_TALK_PART_CHOICE_TABLE + choice]);
}
CLEAN_AS(func_02026fc0, VillagerTalkPart_SayChoice29d4)

/* func_0202703c: for type 10, three choices offered (messages 0x24, 0x25 and 0x26, running
 * nothing, no cancel choice) with the reply data_020d9460 and the talk's byte 0x18 set. For
 * type 19 the item at 0x124 drawn: with a chance of 20 in 100 a random item of the villager's
 * (taken from them), else of 20 more bells; when that is none an item drawn by func_0202d5e4;
 * then VillagerTalkPart_SayByPocketRoom. */
void VillagerTalkPart_StartByType(VillagerTalk *talk, int arg)
{
    (void) arg;
    switch (part_type(talk)) {
        case VILLAGER_TALK_PART_TYPE_10: {
            TalkChoiceList list;
            TalkChoices_Clear(talk, &list);
            for (int i = 0; i < VILLAGER_TALK_PART_CHOICES; i++) {
                u8 message = (u8) (VILLAGER_TALK_PART_CHOICE_FIRST + i);
                TalkChoices_Set((int) (uintptr_t) talk, &list, i, message, message, 0);
            }
            list.count = VILLAGER_TALK_PART_CHOICES;
            list.cancel = -1;
            TalkChoices_Offer((TalkChoicesScene *) (void *) talk, &list);
            VillagerTalkScene_SetReply(talk, data_020d9460);
            TalkObject_OpenChoices((TalkObject *) (void *) part_talk(talk), 1);
            break;
        }
        case VILLAGER_TALK_PART_TYPE_19: {
            int chance = MainRandom_Below(100);
            talk->item = VILLAGER_TALK_PART_NO_ITEM;
            if (chance < VILLAGER_TALK_PART_ITEM_CHANCE) {
                part_villager_item(talk);
            } else if (chance < VILLAGER_TALK_PART_BELLS_CHANCE) {
                part_bells_item(talk);
            }
            if (talk->item == VILLAGER_TALK_PART_NO_ITEM) {
                part_drawn_item(talk);
            }
            VillagerTalkPart_SayByPocketRoom(talk);
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_0202703c, VillagerTalkPart_StartByType)

/* func_02027170: the bag of bells for `bells` (func_0204c120), the smallest bag 0x1492 when it
 * gives none. */
void VillagerTalkPart_BellBag(u16 *out, int bells)
{
    *out = VILLAGER_TALK_PART_NO_ITEM;
    *out = (u16) ItemTraits_BellBagFor(bells, 0, NULL);
    if (*out == VILLAGER_TALK_PART_NO_ITEM) {
        *out = VILLAGER_TALK_PART_SMALLEST_BAG;
    }
}
CLEAN_AS(func_02027170, VillagerTalkPart_BellBag)

/* A line of `for_10` or `for_19` by the type, when there is a block and a set; `out` names the
 * talk's text either way. */
static void part_line_with_block(VillagerTalk *talk, VillagerTalkLine *out, const VillagerTalkPartTexts *for_10,
                                 const VillagerTalkPartTexts *for_19)
{
    const VillagerTalkPartTexts *texts = part_texts_by_type(talk, for_10, for_19);
    if (part_block(talk) != NULL && texts != NULL) {
        part_draw(talk, texts);
    }
    part_name(talk, out);
}

/* func_020271a0: a line of the set data_020c8dc8 for type 10 or data_020c8db8 for type 19, when
 * there is a block. */
void VillagerTalkPart_LineByType8dc8(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line_with_block(talk, out, &data_020c8dc8, &data_020c8db8);
}
CLEAN_AS(func_020271a0, VillagerTalkPart_LineByType8dc8)

/* func_02027230: a line of the set data_020c8de0 for type 10 or data_020c8dd0 for type 19, when
 * there is a block. */
void VillagerTalkPart_LineByType8de0(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line_with_block(talk, out, &data_020c8de0, &data_020c8dd0);
}
CLEAN_AS(func_02027230, VillagerTalkPart_LineByType8de0)

/* func_020272c0: the block's object given the value 1 in its low bits; for type 10 clothes at
 * 0x124 go into the villager's items; for type 19 the player's first letter of state 7 or 8 is
 * emptied (when there is one) and the line is of the set data_020c8de8 instead of
 * data_020c8df0. */
void VillagerTalkPart_LineTakeByType(VillagerTalk *talk, VillagerTalkLine *out)
{
    const VillagerTalkPartTexts *texts = &data_020c8df0;
    switch (part_type(talk)) {
        case VILLAGER_TALK_PART_TYPE_10:
            ItemObject_SetLow5(part_block_object(talk), 1);
            if (part_is_clothes(talk->item)) {
                VillagerItems_Add(part_record(talk), &talk->item);
            }
            break;
        case VILLAGER_TALK_PART_TYPE_19: {
            Letter *letter = VillagerTalkScene_LetterToSend(part_pockets());
            ItemObject_SetLow5(part_block_object(talk), 1);
            texts = &data_020c8de8;
            if (letter != NULL) {
                Letter_Clear(letter);
            }
            break;
        }
        default:
            break;
    }
    part_line(talk, out, texts);
}
CLEAN_AS(func_020272c0, VillagerTalkPart_LineTakeByType)

/* func_020273a8: the screen of group 12 asked for with the player's first letter of state 7 or
 * 8 (or 0), staying on the line; data_020d9488 at the command's end. */
void VillagerTalkPart_OpenLetter(VillagerTalk *talk, int event)
{
    (void) event;
    Letter *letter = VillagerTalkScene_LetterToSend(part_pockets());
    SceneCommand_SetScreenPointer(&talk->scene, (int) (uintptr_t) letter, 1);
    SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_GROUP_12);
    VillagerTalkScene_SetCommandEnd(talk, data_020d9488);
}
CLEAN_AS(func_020273a8, VillagerTalkPart_OpenLetter)

/* func_020273e0: motion 16, then data_020d9068 set at 0xe0. */
void VillagerTalkPart_Motion16Member9068(VillagerTalk *talk)
{
    SceneCommand_RequestMotion16(&talk->scene);
    VillagerTalkScene_SetNextCommandEnd(talk, data_020d9068);
}
CLEAN_AS(func_020273e0, VillagerTalkPart_Motion16Member9068)

/* func_020273fc: a line of the set data_020c8df8. */
void VillagerTalkPart_Line8df8(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8df8);
}
CLEAN_AS(func_020273fc, VillagerTalkPart_Line8df8)

/* func_02027460: when the villager's memory of the player is at least 0x40 fond, the line of
 * the table data_021c2b9c said while the talk is on its message; else motion 16 and
 * VillagerTalkPart_SayNextLine (data_020d94a0) at the command's end. */
void VillagerTalkPart_SayIfFond(VillagerTalk *talk)
{
    if (talk->memory != NULL &&
        VillagerMemoryEntry_Fondness((VillagerMemory *) (void *) talk->memory) >= VILLAGER_TALK_PART_FOND) {
        part_say_if_on(talk, data_021c2b9c);
    } else {
        SceneCommand_RequestMotion16(&talk->scene);
        VillagerTalkScene_SetCommandEnd(talk, data_020d94a0);
    }
}
CLEAN_AS(func_02027460, VillagerTalkPart_SayIfFond)

/* func_020274e0 (a member of the talk): the talk told to show its next line once the current
 * one is shown to its end (word 4 is 5), then the line of the table data_021c2bb4 said.
 * REQUIRES: the talk has its talk at 0x40 (the original reads it without a check). */
void VillagerTalkPart_SayNextLine(VillagerTalk *talk)
{
    if (talk->scene.talk[1] == 5) {
        talk->scene.talk[2] = 1;
    }
    VillagerTalkScene_SetLines(talk, data_021c2bb4);
    part_say_set(talk);
}
CLEAN_AS(_ZN13Base_0202746013func_020274e0Ev, VillagerTalkPart_SayNextLine)

/* func_02027540: a line of the set data_020c8e00. */
void VillagerTalkPart_Line8e00(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8e00);
}
CLEAN_AS(func_02027540, VillagerTalkPart_Line8e00)

/* func_020275a4: the block's object given the value 1 in its low bits, the bond of the block's
 * first villager with the talk's villager lowered by 20, motion 16, then data_020d94a8 at the
 * command's end. */
void VillagerTalkPart_LowerBondMotion16(VillagerTalk *talk)
{
    ItemObject_SetLow5(part_block_object(talk), 1);
    NpcId *first = VillagerPartBlock_Npc(part_block(talk), 0);
    part_bond(first, TownVillager_NpcId(part_record(talk)), VILLAGER_TALK_PART_BOND_DOWN);
    SceneCommand_RequestMotion16(&talk->scene);
    VillagerTalkScene_SetCommandEnd(talk, data_020d94a8);
}
CLEAN_AS(func_020275a4, VillagerTalkPart_LowerBondMotion16)

/* func_0202760c: a line of the set data_020c8e10, then data_020d94b0 run at the last
 * message. */
void VillagerTalkPart_Line8e10(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8e10);
    talk->on_last_message = data_020d94b0;
}
CLEAN_AS(func_0202760c, VillagerTalkPart_Line8e10)

/* func_02027684: the members of the table data_021c2bb4 set, motion 16, and their line said
 * while the talk is on its message. */
void VillagerTalkPart_Motion16Say2bb4(VillagerTalk *talk)
{
    VillagerTalkScene_SetLines(talk, data_021c2bb4);
    SceneCommand_RequestMotion16(&talk->scene);
    part_say_set_if_on(talk);
}
CLEAN_AS(func_02027684, VillagerTalkPart_Motion16Say2bb4)

/* func_020276dc: a line of the set data_020c8e20. */
void VillagerTalkPart_Line8e20(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8e20);
}
CLEAN_AS(func_020276dc, VillagerTalkPart_Line8e20)

/* func_02027740: motion 16, then the item at 0x124, when there is one, into the villager's
 * items. */
void VillagerTalkPart_Motion16KeepItem(VillagerTalk *talk)
{
    u8 *record = part_record(talk);
    SceneCommand_RequestMotion16(&talk->scene);
    if (talk->item != VILLAGER_TALK_PART_NO_ITEM) {
        VillagerItems_Add(record, &talk->item);
    }
}
CLEAN_AS(func_02027740, VillagerTalkPart_Motion16KeepItem)

/* func_0202777c: the block's object given the value 1 in its low bits, a line of the set
 * data_020c8e28, then data_020d9080 run at the last message. */
void VillagerTalkPart_LineStep1(VillagerTalk *talk, VillagerTalkLine *out)
{
    ItemObject_SetLow5(part_block_object(talk), 1);
    part_line(talk, out, &data_020c8e28);
    talk->on_last_message = data_020d9080;
}
CLEAN_AS(func_0202777c, VillagerTalkPart_LineStep1)

/* func_02027804: the members of the table data_021c2bb4 set, motion 15, data_020d94c8 at the
 * command's end, the bond of the block's first villager with the talk's villager raised by 20,
 * the villager's clothes as the item at 0x124, and the line said while the talk is on its
 * message. */
void VillagerTalkPart_RaiseBondClothes(VillagerTalk *talk)
{
    u8 *record = part_record(talk);
    VillagerTalkScene_SetLines(talk, data_021c2bb4);
    SceneCommand_RequestMotion15(&talk->scene);
    VillagerTalkScene_SetCommandEnd(talk, data_020d94c8);
    NpcId *first = VillagerPartBlock_Npc(part_block(talk), 0);
    part_bond(first, TownVillager_NpcId(record), VILLAGER_TALK_PART_BOND_UP);
    talk->item = *TownVillager_Clothes(record);
    part_say_set_if_on(talk);
}
CLEAN_AS(func_02027804, VillagerTalkPart_RaiseBondClothes)

/* func_020278b0: a line of the set data_020c8ba8. */
void VillagerTalkPart_Line8ba8(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8ba8);
}
CLEAN_AS(func_020278b0, VillagerTalkPart_Line8ba8)

/* func_02027914: the villager's reaction to the item at 0x124 kept in the block's byte 0x2c: for
 * clothes whose style value (func_0204c228) is the villager's first style byte (villager data
 * 0x29) 0, the second 2, else (and for other items) 1. The line of the table data_021c2b24,
 * data_021c2b3c or data_021c2b54 by it said while the talk is on its message. */
void VillagerTalkPart_ReactToClothes(VillagerTalk *talk)
{
    u8 reaction = VILLAGER_TALK_PART_REACT_OTHER;
    const u8 *styles = VillagerData_Byte29(part_record(talk));
    if (part_is_clothes(talk->item)) {
        int style = ItemTraits_ClothStyle(&talk->item);
        if (style == styles[0]) {
            reaction = VILLAGER_TALK_PART_REACT_STYLE0;
        } else if (style == styles[1]) {
            reaction = VILLAGER_TALK_PART_REACT_STYLE1;
        }
    }
    VillagerPartBlock_SetByte2C(part_block(talk), reaction);
    switch (reaction) {
        case VILLAGER_TALK_PART_REACT_STYLE0:
            VillagerTalkScene_SetLines(talk, data_021c2b24);
            break;
        case VILLAGER_TALK_PART_REACT_STYLE1:
            VillagerTalkScene_SetLines(talk, data_021c2b3c);
            break;
        default:
            VillagerTalkScene_SetLines(talk, data_021c2b54);
            break;
    }
    part_say_set_if_on(talk);
}
CLEAN_AS(func_02027914, VillagerTalkPart_ReactToClothes)

/* func_020279f4: for type 10 motion 18 and data_020d94d8 at the command's end; for type 19, when
 * the player has a letter of state 7 or 8, the line of the table data_021c2b84 for state 7,
 * else the letter emptied and the line of data_021c2b6c, said while the talk is on its message.
 * Then the bond of the block's first villager with the talk's villager raised by 10. */
void VillagerTalkPart_RaiseBondByType(VillagerTalk *talk)
{
    switch (part_type(talk)) {
        case VILLAGER_TALK_PART_TYPE_10:
            SceneCommand_RequestMotion18(&talk->scene);
            VillagerTalkScene_SetCommandEnd(talk, data_020d94d8);
            break;
        case VILLAGER_TALK_PART_TYPE_19: {
            Letter *letter = VillagerTalkScene_LetterToSend(part_pockets());
            if (letter != NULL) {
                if (Letter_State(letter) == VILLAGER_TALK_PART_LETTER_STATE_7) {
                    VillagerTalkScene_SetLines(talk, data_021c2b84);
                } else {
                    Letter_Clear(letter);
                    VillagerTalkScene_SetLines(talk, data_021c2b6c);
                }
                part_say_set_if_on(talk);
            }
            break;
        }
        default:
            break;
    }
    NpcId *first = VillagerPartBlock_Npc(part_block(talk), 0);
    part_bond(first, TownVillager_NpcId(part_record(talk)), VILLAGER_TALK_PART_BOND_SMALL_UP);
}
CLEAN_AS(func_020279f4, VillagerTalkPart_RaiseBondByType)

/* func_02027ad4: a line of the set data_020c8e48 for type 10 or data_020c8e40 for type 19. */
void VillagerTalkPart_LineByType8e48(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line_if(talk, out, part_texts_by_type(talk, &data_020c8e48, &data_020c8e40));
}
CLEAN_AS(func_02027ad4, VillagerTalkPart_LineByType8e48)

/* func_02027b58: without the screen's answer (GroupParams_C4CIs1 false) the table
 * data_021c2adc, and for type 19 the talk told to show its next line. With it: for type 10 the
 * item in the pocket the screen gave taken as the item at 0x124 (the pocket emptied) and shown
 * with motion 14 of mode 2; for type 19 data_020d8e48 set at 0xe0 and the item 0x1565 shown
 * with mode 0; the table data_021c2af4 either way. The line said. */
void VillagerTalkPart_TakeChosenItem(VillagerTalk *talk)
{
    if (GroupParams_C4CIs1() == 0) {
        if (part_type(talk) == VILLAGER_TALK_PART_TYPE_19) {
            part_next_line(talk);
        }
        VillagerTalkScene_SetLines(talk, data_021c2adc);
    } else {
        u32 mode = 2;
        int slot = GroupParams_Arg();
        PlayerPockets *pockets = part_pockets();
        switch (part_type(talk)) {
            case VILLAGER_TALK_PART_TYPE_10: {
                u16 none = VILLAGER_TALK_PART_NO_ITEM;
                talk->item = *PlayerPockets_Slot(pockets, slot);
                PlayerPockets_SetSlot(pockets, &none, slot, 0);
                break;
            }
            case VILLAGER_TALK_PART_TYPE_19:
                VillagerTalkScene_SetNextCommandEnd(talk, data_020d8e48);
                talk->item = VILLAGER_TALK_PART_LETTER_ITEM;
                mode = 0;
                break;
            default:
                break;
        }
        VillagerTalkScene_SetLines(talk, data_021c2af4);
        SceneCommand_RequestMotion14(&talk->scene, &talk->item, mode, 4, 0);
    }
    part_say_set(talk);
}
CLEAN_AS(func_02027b58, VillagerTalkPart_TakeChosenItem)

/* func_02027c58: the talk told to show its next line. */
void VillagerTalkPart_NextLine(VillagerTalk *talk)
{
    part_next_line(talk);
}
CLEAN_AS(func_02027c58, VillagerTalkPart_NextLine)

/* func_02027c64: a line of the set data_020c8980. */
void VillagerTalkPart_Line8980(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8980);
}
CLEAN_AS(func_02027c64, VillagerTalkPart_Line8980)

/* func_02027cc8: for type 10 the pockets screen asked for with the pockets of clothes in state
 * 2 (func_02027d38, argument 13), data_020d8dc8 at the command's end; for type 19 the screen in
 * mode 0x28 (staying on the line), data_020d8e08 at the command's end; else no screen, only the
 * next line. */
void VillagerTalkPart_AskPocketsByType(VillagerTalk *talk)
{
    switch (part_type(talk)) {
        case VILLAGER_TALK_PART_TYPE_10:
            SceneCommand_SetPocketPredicate(&talk->scene, (PocketPredicate) (void (*)(void)) func_02027d38, 13, 0);
            SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_POCKETS);
            VillagerTalkScene_SetCommandEnd(talk, data_020d8dc8);
            break;
        case VILLAGER_TALK_PART_TYPE_19:
            SceneCommand_SetScreenMode(&talk->scene, 0x28, 1);
            SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_MODE);
            VillagerTalkScene_SetCommandEnd(talk, data_020d8e08);
            break;
        default:
            SceneCommand_RequestScreen(&talk->scene, SCENE_COMMAND_SCREEN_NONE);
            break;
    }
}
CLEAN_AS(func_02027cc8, VillagerTalkPart_AskPocketsByType)

/* func_02027d38: 1 for clothes (0x11a8-0x12a7) in a pocket of state 2, else 0. */
u16 VillagerTalkPart_IsClothesInState2(u16 *item, int state)
{
    return (u16) (part_is_clothes(*item) && state == 2);
}
CLEAN_AS(func_02027d38, VillagerTalkPart_IsClothesInState2)

/* func_02027d68: a line of the set data_020c8978. */
void VillagerTalkPart_Line8978(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line(talk, out, &data_020c8978);
}
CLEAN_AS(func_02027d68, VillagerTalkPart_Line8978)

/* func_02027dcc: for type 19 the talk object's item shown with motion 14 (mode 0) and
 * data_020d8e00 at the command's end. Then the bond of the talk's villager with the block's
 * second villager lowered by 20 and the block cleared. */
void VillagerTalkPart_ShowObjectItemLowerBond(VillagerTalk *talk)
{
    if (part_type(talk) == VILLAGER_TALK_PART_TYPE_19) {
        SceneCommand_RequestMotion14(&talk->scene, ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)),
                                     0, 5, 0);
        VillagerTalkScene_SetCommandEnd(talk, data_020d8e00);
    }
    NpcId *own = TownVillager_NpcId(part_record(talk));
    part_bond(own, VillagerPartBlock_Npc(part_block(talk), 1), VILLAGER_TALK_PART_BOND_DOWN);
    VillagerPartBlock_Clear(part_block(talk));
}
CLEAN_AS(func_02027dcc, VillagerTalkPart_ShowObjectItemLowerBond)

/* func_02027e4c: a line of the set data_020c8998 for type 10 or data_020c8a40 for type 19; with
 * it, when there is a block, the names of its two villagers put into slots 0 and 1 and the
 * talk object's item into slot 0. data_020d8df0 run at the last message either way. */
void VillagerTalkPart_LinePutNames(VillagerTalk *talk, VillagerTalkLine *out)
{
    const VillagerTalkPartTexts *texts = part_texts_by_type(talk, &data_020c8998, &data_020c8a40);
    if (texts != NULL) {
        part_draw(talk, texts);
        if (part_block(talk) != NULL) {
            SceneBase_PutNpcName(part_base(talk), VillagerPartBlock_Npc(part_block(talk), 0), 0);
            SceneBase_PutNpcName(part_base(talk), VillagerPartBlock_Npc(part_block(talk), 1), 1);
            SceneBase_PutItemName(part_base(talk),
                                  (int) (uintptr_t) ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)),
                                  0, 7);
        }
    }
    part_name(talk, out);
    talk->on_last_message = data_020d8df0;
}
CLEAN_AS(func_02027e4c, VillagerTalkPart_LinePutNames)

/* func_02027f28: the bond of the talk's villager with the block's second villager lowered by 20
 * and the block cleared. */
void VillagerTalkPart_LowerBondClear(VillagerTalk *talk)
{
    NpcId *own = TownVillager_NpcId(part_record(talk));
    part_bond(own, VillagerPartBlock_Npc(part_block(talk), 1), VILLAGER_TALK_PART_BOND_DOWN);
    VillagerPartBlock_Clear(part_block(talk));
}
CLEAN_AS(func_02027f28, VillagerTalkPart_LowerBondClear)

/* func_02027f74: a line of the set data_020c8990 for type 10 or data_020c8988 for type 19. */
void VillagerTalkPart_LineByType8990(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line_if(talk, out, part_texts_by_type(talk, &data_020c8990, &data_020c8988));
}
CLEAN_AS(func_02027f74, VillagerTalkPart_LineByType8990)

/* func_02027ff8: for type 10 the item at 0x124 shown with motion 14 (mode 2) and data_020d90b8
 * at the command's end; then the block cleared. */
void VillagerTalkPart_ShowItemClear(VillagerTalk *talk)
{
    if (part_type(talk) == VILLAGER_TALK_PART_TYPE_10) {
        SceneCommand_RequestMotion14(&talk->scene, &talk->item, 2, 5, 0);
        VillagerTalkScene_SetCommandEnd(talk, data_020d90b8);
    }
    VillagerPartBlock_Clear(part_block(talk));
}
CLEAN_AS(func_02027ff8, VillagerTalkPart_ShowItemClear)

/* func_02028044: a line of the set data_020c8e38 for type 10 or data_020c89b0 for type 19. */
void VillagerTalkPart_LineByType8e38(VillagerTalk *talk, VillagerTalkLine *out)
{
    part_line_if(talk, out, part_texts_by_type(talk, &data_020c8e38, &data_020c89b0));
}
CLEAN_AS(func_02028044, VillagerTalkPart_LineByType8e38)

/* func_020280c8: for type 10, when a pocket holds an item like the talk object's
 * (func_0202d794), that item taken as the item at 0x124 (the pocket emptied) and the line of
 * the table data_021c2a7c, else of data_021c2a94, said while the talk is on its message. For
 * type 19 the item 0x1565 shown with motion 14 (mode 0) and data_020d8f08 at the command's end.
 * Then the bond of the talk's villager with the block's second villager lowered by 10. */
void VillagerTalkPart_TakeMatchingItem(VillagerTalk *talk)
{
    PlayerPockets *pockets = part_pockets();
    switch (part_type(talk)) {
        case VILLAGER_TALK_PART_TYPE_10: {
            int slot = VillagerTalkScene_PocketOfItem(
                pockets, ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)));
            if (slot != VILLAGER_TALK_PART_NO_SLOT) {
                u16 none = VILLAGER_TALK_PART_NO_ITEM;
                talk->item = *ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
                PlayerPockets_SetSlot(pockets, &none, slot, 0);
                VillagerTalkScene_SetLines(talk, data_021c2a7c);
            } else {
                VillagerTalkScene_SetLines(talk, data_021c2a94);
            }
            part_say_set_if_on(talk);
            break;
        }
        case VILLAGER_TALK_PART_TYPE_19:
            talk->item = VILLAGER_TALK_PART_LETTER_ITEM;
            SceneCommand_RequestMotion14(&talk->scene, &talk->item, 0, 5, 0);
            VillagerTalkScene_SetCommandEnd(talk, data_020d8f08);
            break;
        default:
            break;
    }
    NpcId *own = TownVillager_NpcId(part_record(talk));
    part_bond(own, VillagerPartBlock_Npc(part_block(talk), 1), VILLAGER_TALK_PART_BOND_SMALL_DOWN);
}
CLEAN_AS(func_020280c8, VillagerTalkPart_TakeMatchingItem)

/* func_020281f0: for type 19, when the player has a letter of state 7 or 8, the table
 * data_021c2a7c for state 7, else data_021c2a94, and the letter emptied. The line (of the
 * members set before when there was no letter) said while the talk is on its message. */
void VillagerTalkPart_SayByLetter(VillagerTalk *talk)
{
    PlayerPockets *pockets = part_pockets();
    if (part_type(talk) == VILLAGER_TALK_PART_TYPE_19) {
        Letter *letter = VillagerTalkScene_LetterToSend(pockets);
        if (letter != NULL) {
            if (Letter_State(letter) == VILLAGER_TALK_PART_LETTER_STATE_7) {
                VillagerTalkScene_SetLines(talk, data_021c2a7c);
            } else {
                VillagerTalkScene_SetLines(talk, data_021c2a94);
            }
            Letter_Clear(letter);
        }
    }
    part_say_set_if_on(talk);
}
CLEAN_AS(func_020281f0, VillagerTalkPart_SayByLetter)
