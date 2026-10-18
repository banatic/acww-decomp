/* The choices a town villager's talk offers when the player starts it
 * (villager_talk_offers.h). */
#include "villager_talk_offers.h"

#include <string.h>

#include "clean.h"
#include "current_pockets.h"
#include "date_time.h"
#include "design.h"
#include "item_attributes.h"
#include "item_code.h"
#include "item_object.h"
#include "lookups.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_base.h"
#include "session.h"
#include "talk_choices.h"
#include "town_villager.h"
#include "villager_data.h"
#include "villager_kinds.h"
#include "villager_mode.h"
#include "villager_mode_record.h"
#include "villager_move.h"
#include "villager_move_record.h"
#include "villager_part_block.h"
#include "villager_part_handover.h"
#include "villager_roster.h"
#include "villager_scene_object.h"
#include "villager_state.h"
#include "villager_status.h"
#include "villager_talk_picks.h"
#include "villager_town.h"
#include "creature_draw.h"
#include "insect_draw.h"
#include "main_random.h"
#include "player_id.h"
#include "talk_object.h"
#include "villager_scene_held.h"
#include "villager_talk_scene.h"

/* The villager scene object's town record (town_villager.h). */
#define VILLAGER_TALK_OFFER_RECORD 0x830
/* The talk's block of the player's villager part, and its villager object. */
#define VILLAGER_TALK_OFFER_BLOCK 0x160
#define VILLAGER_TALK_OFFER_VILLAGER_OBJECT 0x164

#define VILLAGER_TALK_OFFER_TRIES 5
#define VILLAGER_TALK_OFFER_NO_ITEM 0xfff1
#define VILLAGER_TALK_OFFER_NOT_FOUND (-1)

/* The talk object's types of group 0 (villager_object.h). */
#define VILLAGER_TALK_OFFER_TYPE_INSECT 0
#define VILLAGER_TALK_OFFER_TYPE_FISH 1
#define VILLAGER_TALK_OFFER_TYPE_KIND 2
#define VILLAGER_TALK_OFFER_TYPE_CLOTHES 3
#define VILLAGER_TALK_OFFER_TYPE_VARIANT 4
/* The type of the record VillagerPartHandover keeps, and the first-pick types of block 0
 * (villager_part.h) VillagerTalkOffer_FirstPick answers. */
#define VILLAGER_TALK_OFFER_TYPE_HANDOVER 0x15
/* The groups and classes of types (item_object.h). */
#define VILLAGER_TALK_OFFER_GROUP_0 0
#define VILLAGER_TALK_OFFER_GROUP_1 1
#define VILLAGER_TALK_OFFER_CLASS_1 1
#define VILLAGER_TALK_OFFER_CLASS_HANDOVER 3
/* The band of steps of a part block's object (ItemObject_StepBand); 4 when there is none. */
#define VILLAGER_TALK_OFFER_NO_BAND 4
#define VILLAGER_TALK_OFFER_TYPES 0x16

/* The ranges of items. */
#define VILLAGER_TALK_OFFER_INSECT_FIRST 0x12b0
#define VILLAGER_TALK_OFFER_INSECT_LAST 0x12e7
#define VILLAGER_TALK_OFFER_FISH_FIRST 0x12e8
#define VILLAGER_TALK_OFFER_FISH_LAST 0x131f
#define VILLAGER_TALK_OFFER_CLOTHES_FIRST 0x11a8
#define VILLAGER_TALK_OFFER_CLOTHES_LAST 0x12a7
#define VILLAGER_TALK_OFFER_KIND_FIRST 0x450c
#define VILLAGER_TALK_OFFER_KIND_LAST 0x45db
/* The items the villager must hold, outdoors, for an errand of each type. */
#define VILLAGER_TALK_OFFER_HELD_INSECT 0x1376
#define VILLAGER_TALK_OFFER_HELD_FISH 0x1374
#define VILLAGER_TALK_OFFER_HELD_KIND 0x1369
#define VILLAGER_TALK_OFFER_HELD_OTHER_FIRST 0x1380
#define VILLAGER_TALK_OFFER_HELD_OTHER_LAST 0x139f
/* The step of the villager object at which the errand's item is no longer drawn. */
#define VILLAGER_TALK_OFFER_STEP_DONE 2
/* The classes func_0202cef4 and func_0202c9e8 look through. */
#define VILLAGER_TALK_OFFER_CLASSES_LAST 0x17

/* What SceneBase_PutItemName is told the item is. */
#define VILLAGER_TALK_OFFER_ITEM_KIND 7
/* The chance, out of 100, that the offers of the villager's state are looked at. */
#define VILLAGER_TALK_OFFER_ERRAND_CHANCE 30
#define VILLAGER_TALK_OFFER_ERRAND_ROLL 100
/* The kinds of items (item_attributes.h) VillagerTalkOffer_PocketsOfKind looks for. */
#define VILLAGER_TALK_OFFER_KIND_ITEMS 3
/* The time the clock compares with (all of the date and time). */
#define VILLAGER_TALK_OFFER_COMPARE_ALL 0x3f
/* The player record flag that stops the offers of the villager's state. */
#define VILLAGER_TALK_OFFER_PLAYER_FLAG 1

/* The hours of a 12-hour clock (VillagerTalkOffer_PutTime). */
#define VILLAGER_TALK_OFFER_HOURS 12

/* Two ranges of messages for the choices, and what they run. */
extern const u8 data_020c8920[2];
extern const u8 data_020c8924[2];
extern const u8 data_020c8928[2];
extern const u8 data_020c8930[2];
extern u8 data_021c1d6c[];
extern u8 data_021c1e14[];
extern u8 data_021c29ec[];
extern u8 data_021c2ac4[];
extern u8 data_021c2b0c[];
extern u8 data_021c2bcc[];
extern u8 data_021c2be4[];
extern u8 data_021c2c8c[];
extern u8 data_021c2cd4[];
extern u8 data_021c2d04[];
extern u8 data_021c2d7c[];
extern u8 data_021c2df4[];
extern u8 data_021c2eb4[];
extern u8 data_021c2ecc[];
extern u8 data_021c2ee4[];
extern u8 data_021c2f2c[];
extern u8 data_021c2f44[];
extern u8 data_021c2f5c[];
extern u8 data_021c2fbc[];
extern u8 data_021c2fec[];
extern u8 data_021c307c[];

/* The five offers tried (a function-local table filled once from constants, and its guard). */
extern MemberPointer data_021c1dc4[VILLAGER_TALK_OFFER_TRIES];
extern u32 data_021c1cf4;
extern const MemberPointer data_020d9108; /* VillagerTalkOffer_FirstPick */
extern const MemberPointer data_020d94c0; /* VillagerTalkOffer_AfterMove */
extern const MemberPointer data_020d9198; /* VillagerTalkOffer_PartBlock */
extern const MemberPointer data_020d91b0; /* VillagerTalkOffer_ByKnown */
extern const MemberPointer data_020d91b8; /* VillagerTalkOffer_ByState */

/* The replies the offers set (each the game's VillagerTalkOffer_Reply). */
extern const MemberPointer data_020d8db0;
extern const MemberPointer data_020d8db8;
extern const MemberPointer data_020d8dc0;
extern const MemberPointer data_020d8de8;
extern const MemberPointer data_020d8df8;
extern const MemberPointer data_020d8e10;
extern const MemberPointer data_020d8e20;
extern const MemberPointer data_020d8e40;
extern const MemberPointer data_020d8e78;
extern const MemberPointer data_020d8e98;
extern const MemberPointer data_020d8eb8;
extern const MemberPointer data_020d8f20;
extern const MemberPointer data_020d8f48;
extern const MemberPointer data_020d9188;
extern const MemberPointer data_020d9438;
extern const MemberPointer data_020d9490;

/* What SceneBase_PutBytes is handed in the place of the size. */
extern const u8 data_020d9f94[];
extern u8 data_020d9fa0[];

extern u8 data_020e54a8;           /* 0 outdoors, 1 in a room */
extern NetSession *data_020ccf94;  /* the session */
extern VillagerTown data_021e5a2c; /* the town's villagers */

/* `size` bytes cleared. */
extern void *func_02137550(void *dst, u32 size);
/* The game's pocket predicates handed to CurrentPockets_Mark and VillagerTalkOffer_ChoicesByPredicate. */
extern int func_02029e34(u16 *item);
extern int func_02029e78(u16 *item);
extern int func_02029ebc(u16 *item);
extern int func_0202a15c(u16 *item);
extern int func_0202a1ac(u16 *item);

static u8 *offer_talk(const VillagerTalk *talk)
{
    return (u8 *) talk->scene.talk;
}

static SceneBase *offer_base(VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static u8 *offer_record(const VillagerTalk *talk)
{
    return *(u8 **) (void *) (talk->villager + VILLAGER_TALK_OFFER_RECORD);
}

static VillagerPartBlock **offer_block(VillagerTalk *talk)
{
    return (VillagerPartBlock **) (void *) ((u8 *) talk + VILLAGER_TALK_OFFER_BLOCK);
}

static VillagerObject **offer_villager_object(VillagerTalk *talk)
{
    return (VillagerObject **) (void *) ((u8 *) talk + VILLAGER_TALK_OFFER_VILLAGER_OBJECT);
}

static ItemObject *offer_state_object(u8 *record)
{
    return (ItemObject *) (void *) VillagerState_Object(VillagerStatus_StateEntry(record));
}

static VillagerObject *offer_villager_object_of(u8 *record)
{
    return VillagerObject_OfRecord((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record));
}

static int offer_is_insect(u16 item)
{
    return item >= VILLAGER_TALK_OFFER_INSECT_FIRST && item <= VILLAGER_TALK_OFFER_INSECT_LAST;
}

static int offer_is_fish(u16 item)
{
    return item >= VILLAGER_TALK_OFFER_FISH_FIRST && item <= VILLAGER_TALK_OFFER_FISH_LAST;
}

static int offer_is_clothes(u16 item)
{
    return item >= VILLAGER_TALK_OFFER_CLOTHES_FIRST && item <= VILLAGER_TALK_OFFER_CLOTHES_LAST;
}

static int offer_is_kind_item(u16 item)
{
    return item >= VILLAGER_TALK_OFFER_KIND_FIRST && item <= VILLAGER_TALK_OFFER_KIND_LAST;
}

/* Choice `index` of `list`: the messages of `range`, running `function`. */
static void offer_set_from(VillagerTalk *talk, TalkChoiceList *list, int index, const u8 *range, const void *function)
{
    TalkChoices_SetFrom((int) (uintptr_t) talk, list, index, range, (u32) (uintptr_t) function);
}

/* Choice `index` of `list`: the message `message`, running `function`. */
static void offer_set(VillagerTalk *talk, TalkChoiceList *list, int index, int message, const void *function)
{
    TalkChoices_Set((int) (uintptr_t) talk, list, index, (u8) message, (u8) message, (int) (uintptr_t) function);
}

/* The `count` choices of `list` offered with the last one the cancel choice (or `cancel`), the
 * reply `reply`, and the talk's byte 0x18 set. */
static void offer_list(VillagerTalk *talk, TalkChoiceList *list, int count, int cancel, MemberPointer reply)
{
    list->count = (u8) count;
    list->cancel = (s8) cancel;
    TalkChoices_Offer((TalkChoicesScene *) (void *) talk, list);
    VillagerTalkScene_SetReply(talk, reply);
    TalkObject_OpenChoices((TalkObject *) (void *) offer_talk(talk), 1);
}

/* The plain two choices (data_020c8928 running data_021c1e14, data_020c8924 running
 * data_021c1d6c) offered with `reply`, the list cleared first. */
static void offer_plain(VillagerTalk *talk, MemberPointer reply)
{
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    offer_set_from(talk, &list, 0, data_020c8928, data_021c1e14);
    offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
    offer_list(talk, &list, 2, 1, reply);
}

/* Whether `current` and `other` are the same player: the same town (number and name) and the
 * same player in it (func_0209518c). */
static int offer_same_player(const DesignCreator *current, const DesignCreator *other)
{
    return current->town_id == other->town_id &&
           memcmp(current->town_name, other->town_name, sizeof current->town_name) == 0 &&
           PlayerId_SamePlayer(current, other) != 0;
}

/* The line of the line function at 0xb0, when there is one; whether there was.
 * REQUIRES: a line function set (the original then leaves the line unset). */
static int offer_set_line(VillagerTalk *talk, VillagerTalkLine *line)
{
    if (talk->line.function == 0) {
        return 0;
    }
    void *self = MemberPointer_Object(&talk->line, talk);
    ((void (*)(void *, VillagerTalkLine *))(uintptr_t) MemberPointer_Code(&talk->line, self))(self, line);
    return 1;
}

/* func_020288bc: the reply to a choice: the talk's line functions set from the table the choice
 * runs (or cleared when it runs none), then the line, when it has a text, said while the talk is
 * on its message.
 * REQUIRES: `choice` is 0-4. */
void VillagerTalkOffer_Reply(VillagerTalk *talk, int unused, int choice)
{
    (void) unused;
    u32 table = talk->functions[choice];
    if (table != 0) {
        VillagerTalkScene_SetLines(talk, (const MemberPointer *) (uintptr_t) table);
    } else {
        VillagerTalkScene_ClearLines(talk);
    }
    VillagerTalkLine line = {0};
    if (offer_set_line(talk, &line) && line.text != 0) {
        u8 message = line.message;
        TalkObject_SetMessageIfNone((TalkObject *) (void *) offer_talk(talk), &message,
                                    (const char *) (uintptr_t) ((int) line.text));
    }
}
CLEAN_AS(func_020288bc, VillagerTalkOffer_Reply)

/* func_02028924: the five offers tried in turn (the table data_021c1dc4, filled once), each with
 * the villager's town record and the current player's villager part, until one offers; when
 * none does, the plain two choices with the reply data_020d9188. */
void VillagerTalkOffer_Start(VillagerTalk *talk)
{
    static const MemberPointer *const constants[VILLAGER_TALK_OFFER_TRIES] = {
        &data_020d9108, &data_020d94c0, &data_020d9198, &data_020d91b0, &data_020d91b8,
    };
    MemberTable_InitOnce(&data_021c1cf4, data_021c1dc4, constants, VILLAGER_TALK_OFFER_TRIES);
    u8 *record = offer_record(talk);
    VillagerPart *part = (VillagerPart *) (void *) PlayerRecord_VillagerPart(PlayerRecords_Current());
    int i;
    for (i = 0; i < VILLAGER_TALK_OFFER_TRIES; i++) {
        const MemberPointer *offer = &data_021c1dc4[i];
        void *self = MemberPointer_Object(offer, talk);
        int (*function)(void *, u8 *, VillagerPart *) =
            (int (*)(void *, u8 *, VillagerPart *))(uintptr_t) MemberPointer_Code(offer, self);
        if (function(self, record, part) != 0) {
            break;
        }
    }
    if (i == VILLAGER_TALK_OFFER_TRIES) {
        /* The list is not cleared first: only the choices set are read. */
        TalkChoiceList list = {0};
        offer_set_from(talk, &list, 0, data_020c8928, data_021c1e14);
        offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
        offer_list(talk, &list, 2, 1, data_020d9188);
    }
}
CLEAN_AS(func_02028924, VillagerTalkOffer_Start)

/* func_02028a40: when this villager's plan to move away has ended in the last days (no plan,
 * VillagerMoveRecord_IsRecentlyDone on the clock's date) and its object is in use, and the
 * player its stages named most is set up: two choices, the first running data_021c2fbc (the
 * current player is that player, the object's low bits 1), data_021c2f5c (that player, other
 * bits), data_021c2f44 (another player the plan names) or data_021c2f2c (one it does not), the
 * second data_021c1d6c; the reply data_020d8e78; that player's name put into slot 1. Whether it
 * offered. */
int VillagerTalkOffer_AfterMove(VillagerTalk *talk, u8 *record)
{
    VillagerTown *town = &data_021e5a2c;
    int index = VillagerMove_VillagerIndex(town);
    if (index == VILLAGER_TALK_OFFER_NOT_FOUND || index != VillagerStatus_Index(record)) {
        return 0;
    }
    VillagerMove *move = VillagerMove_Record(town);
    ItemObject *object = (ItemObject *) (void *) VillagerMoveRecord_Object(move);
    if (ItemObject_IsInUse(object) == 0 || VillagerMoveRecord_IsRecentlyDone(move, NULL) == 0) {
        return 0;
    }
    DesignCreator *named = VillagerMoveRecord_MostNamedPlayer(move);
    if (named == NULL || PlayerId_IsSet(named) == 0) {
        return 0;
    }
    DesignCreator *current = PlayerRecord_Player(PlayerRecords_Current());
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    const u8 *first;
    if (offer_same_player(current, named)) {
        first = ItemObject_Low5(object) == 1 ? data_021c2fbc : data_021c2f5c;
    } else {
        first = VillagerMoveRecord_NamesPlayer(move, current) != 0 ? data_021c2f44 : data_021c2f2c;
    }
    offer_set_from(talk, &list, 0, data_020c8928, first);
    offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
    offer_list(talk, &list, 2, 1, data_020d8e78);
    SceneBase_PutNameAt10(offer_base(talk), named, 1);
    return 1;
}
CLEAN_AS(func_02028a40, VillagerTalkOffer_AfterMove)

/* func_02028b74: by the object of the villager's entry in the running state table, when it is
 * in use, the current player's flag 1 is clear and a roll below 100 is under 30: group 0 goes to
 * VillagerTalkOffer_StateGroup0, class 1 to VillagerTalkOffer_StateClass1 and class 3 (the
 * handover) to VillagerTalkOffer_StateHandover. Whether it offered. */
int VillagerTalkOffer_ByState(VillagerTalk *talk, u8 *record, VillagerPart *part)
{
    ItemObject *object = offer_state_object(record);
    if (ItemObject_IsInUse(object) == 0) {
        return 0;
    }
    if (PlayerRecord_TestFlag(PlayerRecords_Current(), VILLAGER_TALK_OFFER_PLAYER_FLAG) != 0) {
        return 0;
    }
    if (MainRandom_Below(VILLAGER_TALK_OFFER_ERRAND_ROLL) >= VILLAGER_TALK_OFFER_ERRAND_CHANCE) {
        return 0;
    }
    switch (ItemObject_Group(object)) {
        case VILLAGER_TALK_OFFER_GROUP_0:
            return VillagerTalkOffer_StateGroup0(talk, record, (int) (uintptr_t) part);
        case VILLAGER_TALK_OFFER_GROUP_1:
            switch (ItemObject_Class(object)) {
                case VILLAGER_TALK_OFFER_CLASS_1:
                    return VillagerTalkOffer_StateClass1(talk, record, part);
                case VILLAGER_TALK_OFFER_CLASS_HANDOVER:
                    return VillagerTalkOffer_StateHandover(talk, record, part);
            }
            break;
    }
    return 0;
}
CLEAN_AS(func_02028b74, VillagerTalkOffer_ByState)

/* func_02028c04: when this system holds no slot of the session, the part's handover object is
 * not in use, the player holds nothing of the villager's, the villager's stay is 3, there is no
 * town event, no villager's event within a day and the next town event is none: two choices
 * (data_021c2fec, data_021c1d6c) with the reply data_020d8eb8, the state object made the talk's.
 * Whether it offered. */
int VillagerTalkOffer_StateHandover(VillagerTalk *talk, u8 *record, VillagerPart *part)
{
    ItemObject *object = offer_state_object(record);
    VillagerPartHandover *handover = (VillagerPartHandover *) (void *) part->rest_a4;
    DateTime now = {0};
    DateTime_Now(&now);
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0 ||
        ItemObject_IsInUse((ItemObject *) (void *) handover->object) != 0 ||
        VillagerStatus_PlayerHolds(record, (u8 *) part) != 0 || VillagerStatus_Stay(record) != 3 ||
        VillagerSceneObject_Event(talk->villager) != VILLAGER_SCENE_OBJECT_NO_EVENT ||
        TownVillager_EventYearWithin(record, 1, &now) != VILLAGER_TALK_OFFER_NOT_FOUND ||
        VillagerTown_NextEvent(1, &now) != VILLAGER_SCENE_OBJECT_NO_EVENT) {
        return 0;
    }
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    offer_set_from(talk, &list, 0, data_020c8928, data_021c2fec);
    offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
    VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) object);
    offer_list(talk, &list, 2, 1, data_020d8eb8);
    return 1;
}
CLEAN_AS(func_02028c04, VillagerTalkOffer_StateHandover)

/* Outdoors (data_020e54a8 0), whether the item the villager holds is `first` to `last`; in a
 * room, always. */
static int offer_holds(VillagerTalk *talk, u16 first, u16 last)
{
    if (data_020e54a8 != 0) {
        return 1;
    }
    u16 held;
    VillagerSceneHeld_Item(&held, talk->villager);
    return held >= first && held <= last;
}

/* Outdoors, whether the villager holds nothing or an item of 0x1380-0x139f (asked twice); in a
 * room, always. */
static int offer_holds_other(VillagerTalk *talk)
{
    if (data_020e54a8 != 0) {
        return 1;
    }
    u16 held;
    VillagerSceneHeld_Item(&held, talk->villager);
    if (held == VILLAGER_TALK_OFFER_NO_ITEM) {
        return 1;
    }
    return offer_holds(talk, VILLAGER_TALK_OFFER_HELD_OTHER_FIRST, VILLAGER_TALK_OFFER_HELD_OTHER_LAST);
}

/* func_02028d04: an errand of group 0 from the state object, when there is no town event: an
 * insect (type 0) or a fish (type 1) drawn for step 0 when the villager holds the net 0x1376 or
 * rod 0x1374 outdoors, kept at 0x124 when it is one; type 2 when it holds 0x1369 outdoors; the
 * others when it holds nothing or 0x1380-0x139f outdoors. Then two choices (data_021c2c8c,
 * data_021c1d6c) with the reply data_020d8db8, the state object made the talk's. The villager
 * object of the record is kept at 0x164 first. Whether it offered. */
int VillagerTalkOffer_StateGroup0(VillagerTalk *talk, u8 *record, int unused)
{
    (void) unused;
    ItemObject *object = offer_state_object(record);
    int offers = 0;
    *offer_villager_object(talk) = offer_villager_object_of(record);
    if (VillagerSceneObject_Event(talk->villager) == VILLAGER_SCENE_OBJECT_NO_EVENT) {
        u16 drawn;
        switch (ItemObject_Type(object)) {
            case VILLAGER_TALK_OFFER_TYPE_INSECT:
                if (offer_holds(talk, VILLAGER_TALK_OFFER_HELD_INSECT, VILLAGER_TALK_OFFER_HELD_INSECT)) {
                    VillagerTalkPick_Insect(&drawn, (int) (uintptr_t) talk, 0);
                    if (offer_is_insect(drawn)) {
                        talk->item = drawn;
                        offers = 1;
                    }
                }
                break;
            case VILLAGER_TALK_OFFER_TYPE_FISH:
                if (offer_holds(talk, VILLAGER_TALK_OFFER_HELD_FISH, VILLAGER_TALK_OFFER_HELD_FISH)) {
                    VillagerTalkPick_Fish(&drawn, (int) (uintptr_t) talk, 0);
                    if (offer_is_fish(drawn)) {
                        talk->item = drawn;
                        offers = 1;
                    }
                }
                break;
            case VILLAGER_TALK_OFFER_TYPE_KIND:
                offers = offer_holds(talk, VILLAGER_TALK_OFFER_HELD_KIND, VILLAGER_TALK_OFFER_HELD_KIND);
                break;
            default:
                offers = offer_holds_other(talk);
                break;
        }
    }
    if (offers == 0) {
        return 0;
    }
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    offer_set_from(talk, &list, 0, data_020c8928, data_021c2c8c);
    VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) object);
    offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
    offer_list(talk, &list, 2, 1, data_020d8db8);
    return 1;
}
CLEAN_AS(func_02028d04, VillagerTalkOffer_StateGroup0)

/* func_02028f5c: a request of class 1 from the state object: when the part's block for it (by
 * ItemObject_Class1Split) is free, the type fits the villager's mode, there is no town event,
 * no villager has an event now and another resident can be named: two choices (data_021c29ec,
 * data_021c1d6c) with the reply data_020d8db0, the block kept at 0x160 and the state object
 * made the talk's. Whether it offered. */
int VillagerTalkOffer_StateClass1(VillagerTalk *talk, u8 *record, VillagerPart *part)
{
    ItemObject *object = offer_state_object(record);
    VillagerPartBlock *block = VillagerPart_Block(part, ItemObject_Class1Split(object));
    VillagerModeRecord *mode = VillagerObject_RecordMode((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record));
    DateTime now = {0};
    DateTime_Now(&now);
    if (block == NULL || ItemObject_IsInUse((ItemObject *) (void *) VillagerPartBlock_Object(block)) != 0) {
        return 0;
    }
    int type = ItemObject_Type(object);
    if (VillagerPartBlock_TypeFitsMode(type, VillagerModeRecord_Mode(mode)) == 0 ||
        VillagerSceneObject_Event(talk->villager) != VILLAGER_SCENE_OBJECT_NO_EVENT ||
        VillagerTown_FindEventVillager(&data_021e5a2c, &now) != VILLAGER_TALK_OFFER_NOT_FOUND ||
        VillagerTalkOffer_HasOtherResident(talk) == 0) {
        return 0;
    }
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    *offer_block(talk) = block;
    offer_set_from(talk, &list, 0, data_020c8928, data_021c29ec);
    offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
    VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) object);
    offer_list(talk, &list, 2, 1, data_020d8db0);
    return 1;
}
CLEAN_AS(func_02028f5c, VillagerTalkOffer_StateClass1)

/* func_02029074: whether a resident other than the talk's villager can be picked. */
int VillagerTalkOffer_HasOtherResident(VillagerTalk *talk)
{
    const NpcId *excluded;
    func_02137550(&excluded, sizeof excluded);
    excluded = TownVillager_NpcId(offer_record(talk));
    return (int) (uintptr_t) VillagerRoster_PickResident(&data_021e5a2c, &excluded, 1);
}
CLEAN_AS(func_02029074, VillagerTalkOffer_HasOtherResident)

/* func_020290b0: when the current player's flag 1 is clear, by the type of the object something
 * holds for the villager (VillagerKind_Known): group 0 goes to VillagerTalkOffer_KnownGroup0,
 * class 1 to VillagerTalkOffer_KnownBlock and class 3 (the handover) to
 * VillagerTalkOffer_KnownHandover. Whether it offered. */
int VillagerTalkOffer_ByKnown(VillagerTalk *talk, u8 *record, VillagerPart *part)
{
    u8 *player = PlayerRecords_Current();
    if (PlayerRecord_TestFlag(player, VILLAGER_TALK_OFFER_PLAYER_FLAG) != 0) {
        return 0;
    }
    unsigned int type = (unsigned int) VillagerKind_Known(&data_021e5a2c, record, player);
    if (type >= VILLAGER_TALK_OFFER_TYPES) {
        return 0;
    }
    switch (ItemObject_GroupOfType(type)) {
        case VILLAGER_TALK_OFFER_GROUP_0:
            return VillagerTalkOffer_KnownGroup0(talk, record, (int) (uintptr_t) part, type);
        case VILLAGER_TALK_OFFER_GROUP_1:
            switch (ItemObject_ClassOfType(type)) {
                case VILLAGER_TALK_OFFER_CLASS_1:
                    return VillagerTalkOffer_KnownBlock(talk, (int) (uintptr_t) record, part, (int) type);
                case VILLAGER_TALK_OFFER_CLASS_HANDOVER:
                    return VillagerTalkOffer_KnownHandover(talk, record, part, type);
            }
            break;
    }
    return 0;
}
CLEAN_AS(func_020290b0, VillagerTalkOffer_ByKnown)

/* func_0202913c: when there is no town event and the part's handover object is in use, of type
 * 21, from this villager and its low bits 0: the choice 0x30 running data_021c307c and
 * data_021c1d6c with the reply data_020d8df8, the handover's date put into the talk's slots;
 * otherwise the plain two choices with the reply data_020d8de8. Always offers. */
int VillagerTalkOffer_KnownHandover(VillagerTalk *talk, u8 *record, VillagerPart *part, unsigned int type)
{
    (void) type;
    VillagerPartHandover *handover = (VillagerPartHandover *) (void *) part->rest_a4;
    ItemObject *object = (ItemObject *) (void *) handover->object;
    if (VillagerSceneObject_Event(talk->villager) == VILLAGER_SCENE_OBJECT_NO_EVENT && ItemObject_IsInUse(object) != 0 &&
        ItemObject_Type(object) == VILLAGER_TALK_OFFER_TYPE_HANDOVER &&
        VillagerPartHandover_IsFrom(handover, TownVillager_NpcId(record)) != 0 && ItemObject_Low5(object) == 0) {
        TalkChoiceList list;
        TalkChoices_Clear(talk, &list);
        offer_set(talk, &list, 0, 0x30, data_021c307c);
        offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
        offer_list(talk, &list, 2, 1, data_020d8df8);
        VillagerTalkOffer_PutTime(talk, &handover->date);
        return 1;
    }
    offer_plain(talk, data_020d8de8);
    return 1;
}
CLEAN_AS(func_0202913c, VillagerTalkOffer_KnownHandover)

/* func_02029264: a time put into the talk's slots: its day (slot 0), its hour on a 12-hour
 * clock (slot 1, 12 for 0, two digits) and its minute (slot 2, two digits). */
void VillagerTalkOffer_PutTime(VillagerTalk *talk, const DateTime *when)
{
    unsigned int hour = when->hour;
    if (hour >= VILLAGER_TALK_OFFER_HOURS) {
        hour -= VILLAGER_TALK_OFFER_HOURS;
    }
    if (hour == 0) {
        hour = VILLAGER_TALK_OFFER_HOURS;
    }
    SceneBase_PutNumber(offer_base(talk), when->day, 0);
    SceneBase_PutValue(offer_base(talk), (int) hour, 1, 2, 0, 0);
    SceneBase_PutValue(offer_base(talk), when->minute, 2, 2, 6, 9);
}
CLEAN_AS(func_02029264, VillagerTalkOffer_PutTime)

/* The errand of group 0 the talk's object (the villager object's) asks for, when the villager
 * holds the right item outdoors (as VillagerTalkOffer_StateGroup0). An insect or a fish is kept
 * at 0x124: the object's own when it is one the month gives, else one drawn for the villager
 * object's step; whether it is one. At step 2 there is no item to draw. For the other types the
 * object's item, when it has one, is kept at 0x124. */
static int offer_known_errand(VillagerTalk *talk)
{
    u8 step = VillagerObject_Step(*offer_villager_object(talk));
    u16 item = *ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
    DateTime now = {0};
    DateTime_Now(&now);
    u16 drawn;
    switch (ItemObject_Type((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case VILLAGER_TALK_OFFER_TYPE_INSECT:
            if (!offer_holds(talk, VILLAGER_TALK_OFFER_HELD_INSECT, VILLAGER_TALK_OFFER_HELD_INSECT)) {
                return 0;
            }
            if (step == VILLAGER_TALK_OFFER_STEP_DONE) {
                return 1;
            }
            if (offer_is_insect(item) && InsectDraw_Available(&item, 0, VILLAGER_TALK_OFFER_CLASSES_LAST, now.month) != 0) {
                talk->item = item;
            } else {
                VillagerTalkPick_Insect(&drawn, (int) (uintptr_t) talk, step);
                talk->item = drawn;
            }
            return offer_is_insect(talk->item);
        case VILLAGER_TALK_OFFER_TYPE_FISH:
            if (!offer_holds(talk, VILLAGER_TALK_OFFER_HELD_FISH, VILLAGER_TALK_OFFER_HELD_FISH)) {
                return 0;
            }
            if (step == VILLAGER_TALK_OFFER_STEP_DONE) {
                return 1;
            }
            if (offer_is_fish(item) &&
                CreatureDraw_FishAvailable(&item, 0, VILLAGER_TALK_OFFER_CLASSES_LAST, now.month, now.day) != 0) {
                talk->item = item;
            } else {
                VillagerTalkPick_Fish(&drawn, (int) (uintptr_t) talk, step);
                talk->item = drawn;
            }
            return offer_is_fish(talk->item);
        case VILLAGER_TALK_OFFER_TYPE_KIND:
            if (!offer_holds(talk, VILLAGER_TALK_OFFER_HELD_KIND, VILLAGER_TALK_OFFER_HELD_KIND)) {
                return 0;
            }
            break;
        default:
            if (!offer_holds_other(talk)) {
                return 0;
            }
            break;
    }
    if (item != VILLAGER_TALK_OFFER_NO_ITEM) {
        talk->item = item;
    }
    return 1;
}

/* The choices for the errand of a villager object that names a player, by the talk object's
 * type: 0 and 1 through VillagerTalkOffer_ChoicesByPredicate (the game's insect or fish
 * predicate), 2-4 their own; for type 4 the index of what the villager likes
 * (VillagerData_Like of VillagerMode_Counter7D7) goes into slot 0 as a byte. Whether it offered. */
static int offer_known_named(VillagerTalk *talk, int type)
{
    int offered = 0;
    switch (type) {
        case VILLAGER_TALK_OFFER_TYPE_INSECT:
            offered = VillagerTalkOffer_ChoicesByPredicate(talk, func_0202a1ac, 0x28, 0x19);
            break;
        case VILLAGER_TALK_OFFER_TYPE_FISH:
            offered = VillagerTalkOffer_ChoicesByPredicate(talk, func_0202a15c, 0x29, 0x18);
            break;
        case VILLAGER_TALK_OFFER_TYPE_KIND:
            offered = VillagerTalkOffer_ChoicesKind(talk);
            break;
        case VILLAGER_TALK_OFFER_TYPE_CLOTHES:
            offered = VillagerTalkOffer_ChoicesClothes(talk);
            break;
        case VILLAGER_TALK_OFFER_TYPE_VARIANT:
            offered = VillagerTalkOffer_ChoicesVariant(talk);
            if (offered == 1) {
                u8 *record = offer_record(talk);
                u8 bytes[2];
                bytes[0] = Lookups_SlotIndex((const u8 *) VillagerData_Like(record, VillagerMode_Counter7D7(record)));
                bytes[1] = 0;
                SceneBase_PutBytes(offer_base(talk), 0, &bytes[0], (int) (uintptr_t) data_020d9fa0, &bytes[1]);
            }
            break;
    }
    return offered;
}

/* func_020292b4: the errand of the villager's own object (group 0). Its villager object is kept
 * at 0x164 and its object made the talk's. When there is no town event: if the villager object
 * names a player that is set up, that player's choices (offer_known_named); else, when the
 * villager can do the errand (offer_known_errand), two choices (data_021c2c8c, data_021c1d6c)
 * with the reply data_020d8e40. When nothing was offered, the plain two choices with the reply
 * data_020d8dc0. Always offers. */
int VillagerTalkOffer_KnownGroup0(VillagerTalk *talk, u8 *record, int unused, unsigned int type)
{
    (void) unused;
    (void) type;
    int offered = 0;
    *offer_villager_object(talk) = offer_villager_object_of(record);
    VillagerTalkScene_SetObject(talk,
                                (u32) (uintptr_t) ((ItemObject *) (void *) VillagerObject_Base(*offer_villager_object(talk))));
    int key = ItemObject_Type((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk));
    if (VillagerSceneObject_Event(talk->villager) == VILLAGER_SCENE_OBJECT_NO_EVENT) {
        if (PlayerId_IsSet(VillagerObject_Player(*offer_villager_object(talk))) != 0) {
            offered = offer_known_named(talk, key);
        } else if (offer_known_errand(talk)) {
            TalkChoiceList list;
            TalkChoices_Clear(talk, &list);
            offer_set_from(talk, &list, 0, data_020c8928, data_021c2c8c);
            offer_set_from(talk, &list, 1, data_020c8924, data_021c1d6c);
            offer_list(talk, &list, 2, 1, data_020d8e40);
            offered = 1;
        }
    }
    if (offered == 0) {
        offer_plain(talk, data_020d8dc0);
        offered = 1;
    }
    return offered;
}
CLEAN_AS(func_020292b4, VillagerTalkOffer_KnownGroup0)

/* The end of the choices of a named player's errand: unless `plain` is 0, data_020c8928 running
 * data_021c1e14; then data_020c8924 running data_021c1d6c, the last the cancel choice. */
static void offer_named_end(VillagerTalk *talk, TalkChoiceList *list, u8 index, int plain, MemberPointer reply)
{
    if (plain != 0) {
        offer_set_from(talk, list, index, data_020c8928, data_021c1e14);
        index++;
    }
    offer_set_from(talk, list, index, data_020c8924, data_021c1d6c);
    index++;
    offer_list(talk, list, index, index - 1, reply);
}

/* The choices of the talk object's low bits 1 (half the time data_021c2eb4 in the place of the
 * plain first choice) and 2 (data_021c2ecc in its place). */
static void offer_named_low1(VillagerTalk *talk, TalkChoiceList *list, u8 *index, int *plain)
{
    if (MainRandom_Below(10) & 1) {
        offer_set_from(talk, list, *index, data_020c8928, data_021c2eb4);
        *plain = 0;
        (*index)++;
    }
}

static void offer_named_low2(VillagerTalk *talk, TalkChoiceList *list, u8 *index, int *plain)
{
    offer_set_from(talk, list, *index, data_020c8928, data_021c2ecc);
    (*index)++;
    *plain = 0;
}

/* Whether the villager object names the current player. */
static int offer_names_current(VillagerTalk *talk)
{
    DesignCreator *named = VillagerObject_Player(*offer_villager_object(talk));
    DesignCreator *current = PlayerRecord_Player(PlayerRecords_Current());
    return offer_same_player(current, named);
}

/* func_020296f8: the choices of an errand of type 2 (an item of a kind) for the player the
 * villager object names, by the talk object's low bits. Low bits 0, when the named player is the
 * current one: choice 0x1a running data_021c2df4 when the pockets hold such an item (steps 0-1:
 * any of the kind items, VillagerTalkOffer_IsKindItem; later steps: one of the villager object's
 * kind, VillagerTalkOffer_PocketsOfKind), else 0x14 running data_021c2cd4; from step 2 the
 * kind's index goes into slot 0 as a byte. Then the end (offer_named_end) with the reply
 * data_020d8e20. Whether it offered. */
int VillagerTalkOffer_ChoicesKind(VillagerTalk *talk)
{
    int plain = 1;
    u8 index = 0;
    int offered = 0;
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    switch (ItemObject_Low5((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case 0: {
            if (!offer_names_current(talk)) {
                break;
            }
            VillagerObject *object = *offer_villager_object(talk);
            PocketsMarks marks;
            if (VillagerObject_Step(object) <= 1) {
                if (CurrentPockets_Mark(&marks, func_02029e34) > 0) {
                    offer_set(talk, &list, index, 0x1a, data_021c2df4);
                } else {
                    offer_set(talk, &list, index, 0x14, data_021c2cd4);
                }
            } else if (VillagerObject_Step(*offer_villager_object(talk)) >= 2) {
                if (VillagerTalkOffer_PocketsOfKind(*offer_villager_object(talk)) != 0) {
                    offer_set(talk, &list, index, 0x1a, data_021c2df4);
                } else {
                    offer_set(talk, &list, index, 0x14, data_021c2cd4);
                }
            } else {
                offer_set(talk, &list, index, 0x14, data_021c2cd4);
            }
            if (VillagerObject_Step(*offer_villager_object(talk)) >= 2) {
                int kind = ItemAttributes_KindIndex(VillagerObject_Kind(*offer_villager_object(talk)));
                if (kind != VILLAGER_TALK_OFFER_NOT_FOUND) {
                    u8 bytes[2];
                    bytes[0] = (u8) kind;
                    bytes[1] = 0;
                    SceneBase_PutBytes(offer_base(talk), 0, &bytes[0], (int) (uintptr_t) data_020d9f94, &bytes[1]);
                }
            }
            index++;
            offered = 1;
            break;
        }
        case 1:
            offer_named_low1(talk, &list, &index, &plain);
            offered = 1;
            break;
        case 2:
            offer_named_low2(talk, &list, &index, &plain);
            offered = 1;
            break;
    }
    if (offered == 1) {
        offer_named_end(talk, &list, index, plain, data_020d8e20);
    }
    return offered;
}
CLEAN_AS(func_020296f8, VillagerTalkOffer_ChoicesKind)

/* Whether the pocket item `item` is `wanted`, by the item a variant stands for when it has one. */
static int offer_same_item(u16 *item, u16 *wanted)
{
    if (ItemCode_HasVariant(item) != 0) {
        int variant = ItemCode_VariantItem(item);
        return variant == ItemCode_VariantItem(wanted);
    }
    return *item == *wanted;
}

/* func_02029910: the current player's pockets (a bit each) in state 0 holding an item of the
 * villager object's kind (0x450c-0x45db) that is one of the kind's three items whose flag is
 * clear. */
u16 VillagerTalkOffer_PocketsOfKind(VillagerObject *object)
{
    PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
    u16 *slot = PlayerPockets_Slot(pockets, 0);
    u16 wanted[VILLAGER_TALK_OFFER_KIND_ITEMS] = {VILLAGER_TALK_OFFER_NO_ITEM, VILLAGER_TALK_OFFER_NO_ITEM,
                                                  VILLAGER_TALK_OFFER_NO_ITEM};
    u16 mask = 0;
    for (int i = 0; i < VILLAGER_TALK_OFFER_KIND_ITEMS; i++) {
        if (VillagerObject_TestFlag(object, (u32) i) == 0) {
            u16 item;
            ItemAttributes_KindItem(&item, VillagerObject_Kind(object), (u32) i);
            wanted[i] = item;
        } else {
            wanted[i] = VILLAGER_TALK_OFFER_NO_ITEM;
        }
    }
    for (int i = 0; i < PLAYER_POCKETS_SLOTS; i++, slot++) {
        if (PlayerPockets_SlotState(pockets, i) != 0 || !offer_is_kind_item(*slot)) {
            continue;
        }
        for (int j = 0; j < VILLAGER_TALK_OFFER_KIND_ITEMS; j++) {
            if (offer_same_item(slot, &wanted[j])) {
                mask = (u16) (mask | (1u << i));
                break;
            }
        }
    }
    return mask;
}
CLEAN_AS(func_02029910, VillagerTalkOffer_PocketsOfKind)

/* func_02029a18: the current player's pockets (a bit each) in state 0 holding `item` (by the item
 * a variant stands for, when the pocket's has one). */
u16 VillagerTalkOffer_PocketsLike(u16 *item)
{
    PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
    u16 *slot = PlayerPockets_Slot(pockets, 0);
    u16 mask = 0;
    for (int i = 0; i < PLAYER_POCKETS_SLOTS; i++, slot++) {
        if (PlayerPockets_SlotState(pockets, i) == 0 && offer_same_item(slot, item)) {
            mask = (u16) (mask | (1u << i));
        }
    }
    return mask;
}
CLEAN_AS(func_02029a18, VillagerTalkOffer_PocketsLike)

/* func_02029a98: the choices of an errand of type 3 (clothes) for the player the villager
 * object names. Low bits 0, when the named player is the current one: steps 0-1, choice 0x1b
 * running data_021c2df4 when the pockets hold clothes, else 0x14 running data_021c2cd4; later
 * steps, 0x1b when the talk object's item is clothes the pockets hold, else 0x14; the item's
 * name put into slot 0 when it is clothes. Low bits 1 add nothing. Then the end with the reply
 * data_020d8e10. Whether it offered. */
int VillagerTalkOffer_ChoicesClothes(VillagerTalk *talk)
{
    int plain = 1;
    u8 index = 0;
    int offered = 0;
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    switch (ItemObject_Low5((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case 0: {
            if (!offer_names_current(talk)) {
                break;
            }
            if (VillagerObject_Step(*offer_villager_object(talk)) <= 1) {
                PocketsMarks marks;
                if (CurrentPockets_Mark(&marks, func_02029e78) > 0) {
                    offer_set(talk, &list, index, 0x1b, data_021c2df4);
                } else {
                    offer_set(talk, &list, index, 0x14, data_021c2cd4);
                }
            } else if (offer_is_clothes(*ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)))) {
                if (CurrentPockets_FindItem(ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) !=
                    VILLAGER_TALK_OFFER_NOT_FOUND) {
                    offer_set(talk, &list, index, 0x1b, data_021c2df4);
                } else {
                    offer_set(talk, &list, index, 0x14, data_021c2cd4);
                }
            } else {
                offer_set(talk, &list, 0, 0x14, data_021c2cd4);
            }
            if (offer_is_clothes(*ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)))) {
                SceneBase_PutItemName(
                    offer_base(talk),
                    (int) (uintptr_t) ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)), 0,
                    VILLAGER_TALK_OFFER_ITEM_KIND);
            }
            index++;
            offered = 1;
            break;
        }
        case 1:
            offered = 1;
            break;
        case 2:
            offer_named_low2(talk, &list, &index, &plain);
            offered = 1;
            break;
    }
    if (offered == 1) {
        offer_named_end(talk, &list, index, plain, data_020d8e10);
    }
    return offered;
}
CLEAN_AS(func_02029a98, VillagerTalkOffer_ChoicesClothes)

/* func_02029ca4: the choices of an errand of type 4 (an item with a variant) for the player the
 * villager object names. Low bits 0, when the named player is the current one: choice 0x1c
 * running data_021c2df4 when the pockets hold such an item (VillagerTalkOffer_IsVariant), else
 * 0x14 running data_021c2cd4. Then the end with the reply data_020d8e98. Whether it offered. */
int VillagerTalkOffer_ChoicesVariant(VillagerTalk *talk)
{
    int plain = 1;
    u8 index = 0;
    int offered = 0;
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    switch (ItemObject_Low5((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case 0: {
            if (!offer_names_current(talk)) {
                break;
            }
            PocketsMarks marks;
            if (CurrentPockets_Mark(&marks, func_02029ebc) > 0) {
                offer_set(talk, &list, index, 0x1c, data_021c2df4);
            } else {
                offer_set(talk, &list, index, 0x14, data_021c2cd4);
            }
            index++;
            offered = 1;
            break;
        }
        case 1:
            offer_named_low1(talk, &list, &index, &plain);
            offered = 1;
            break;
        case 2:
            offer_named_low2(talk, &list, &index, &plain);
            offered = 1;
            break;
    }
    if (offered == 1) {
        offer_named_end(talk, &list, index, plain, data_020d8e98);
    }
    return offered;
}
CLEAN_AS(func_02029ca4, VillagerTalkOffer_ChoicesVariant)

/* func_02029e18: a pocket predicate: an item of a kind (0x450c-0x45db) in state 0. */
int VillagerTalkOffer_IsKindItemFree(u16 *item, int state)
{
    return VillagerTalkOffer_IsKindItem(item) != 0 && state == 0;
}
CLEAN_AS(func_02029e18, VillagerTalkOffer_IsKindItemFree)

/* func_02029e34: whether the item is of a kind (0x450c-0x45db). */
int VillagerTalkOffer_IsKindItem(u16 *item)
{
    return offer_is_kind_item(*item);
}
CLEAN_AS(func_02029e34, VillagerTalkOffer_IsKindItem)

/* func_02029e5c: a pocket predicate: clothes in state 0. */
int VillagerTalkOffer_IsClothesFree(u16 *item, int state)
{
    return VillagerTalkOffer_IsClothes(item) != 0 && state == 0;
}
CLEAN_AS(func_02029e5c, VillagerTalkOffer_IsClothesFree)

/* func_02029e78: whether the item is clothes (0x11a8-0x12a7). */
int VillagerTalkOffer_IsClothes(u16 *item)
{
    return offer_is_clothes(*item);
}
CLEAN_AS(func_02029e78, VillagerTalkOffer_IsClothes)

/* func_02029ea0: a pocket predicate: an item with a variant, not of a kind, in state 0. */
int VillagerTalkOffer_IsVariantFree(u16 *item, int state)
{
    return VillagerTalkOffer_IsVariant(item) != 0 && state == 0;
}
CLEAN_AS(func_02029ea0, VillagerTalkOffer_IsVariantFree)

/* func_02029ebc: whether the item has a variant and is not of a kind (0x450c-0x45db). */
int VillagerTalkOffer_IsVariant(u16 *item)
{
    return ItemCode_HasVariant(item) != 0 && !offer_is_kind_item(*item);
}
CLEAN_AS(func_02029ebc, VillagerTalkOffer_IsVariant)

/* func_02029ef8: the choices of an errand of an insect or a fish (`test`, the game's predicate)
 * for the player the villager object names. Low bits 0, when the named player is the current
 * one: at step 2, choice `message_named` running data_021c2d04 when the villager object's item
 * passes `test` and the pockets hold one that does, else 0x14 running data_021c2cd4; at other
 * steps, `message_have` running data_021c2d7c when the talk object's item passes `test` and the
 * pockets hold it, else 0x14; the talk object's item's name put into slot 0 when it has one.
 * Then the end with the reply data_020d9438. Whether it offered. */
int VillagerTalkOffer_ChoicesByPredicate(VillagerTalk *talk, int (*test)(u16 *item), int message_named, int message_have)
{
    int plain = 1;
    u8 index = 0;
    int offered = 0;
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    switch (ItemObject_Low5((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) {
        case 0: {
            if (!offer_names_current(talk)) {
                break;
            }
            if (VillagerObject_Step(*offer_villager_object(talk)) == VILLAGER_TALK_OFFER_STEP_DONE) {
                PocketsMarks marks;
                if (test(VillagerObject_Item(*offer_villager_object(talk))) != 0 && CurrentPockets_Mark(&marks, test) > 0) {
                    offer_set(talk, &list, index, message_named, data_021c2d04);
                } else {
                    offer_set(talk, &list, 0, 0x14, data_021c2cd4);
                }
            } else if (test(ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) != 0) {
                if (CurrentPockets_FindItem(ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk))) !=
                    VILLAGER_TALK_OFFER_NOT_FOUND) {
                    offer_set(talk, &list, index, message_have, data_021c2d7c);
                } else {
                    offer_set(talk, &list, index, 0x14, data_021c2cd4);
                }
            } else {
                offer_set(talk, &list, index, 0x14, data_021c2cd4);
            }
            if (*ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)) != VILLAGER_TALK_OFFER_NO_ITEM) {
                SceneBase_PutItemName(
                    offer_base(talk),
                    (int) (uintptr_t) ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)), 0,
                    VILLAGER_TALK_OFFER_ITEM_KIND);
            }
            index++;
            offered = 1;
            break;
        }
        case 1:
            offer_named_low1(talk, &list, &index, &plain);
            offered = 1;
            break;
        case 2:
            offer_named_low2(talk, &list, &index, &plain);
            offered = 1;
            break;
    }
    if (offered == 1) {
        offer_named_end(talk, &list, index, plain, data_020d9438);
    }
    return offered;
}
CLEAN_AS(func_02029ef8, VillagerTalkOffer_ChoicesByPredicate)

/* func_0202a12c: a pocket predicate: a fish (0x12e8-0x131f) in state 0. */
u16 VillagerTalkOffer_IsFishFree(u16 *item, int state)
{
    return (u16) (offer_is_fish(*item) && state == 0);
}
CLEAN_AS(func_0202a12c, VillagerTalkOffer_IsFishFree)

/* func_0202a15c: whether the item is a fish (0x12e8-0x131f). */
u16 VillagerTalkOffer_IsFish(u16 *item)
{
    return (u16) offer_is_fish(*item);
}
CLEAN_AS(func_0202a15c, VillagerTalkOffer_IsFish)

/* func_0202a17c: a pocket predicate: an insect (0x12b0-0x12e7) in state 0. */
u16 VillagerTalkOffer_IsInsectFree(u16 *item, int state)
{
    return (u16) (offer_is_insect(*item) && state == 0);
}
CLEAN_AS(func_0202a17c, VillagerTalkOffer_IsInsectFree)

/* func_0202a1ac: whether the item is an insect (0x12b0-0x12e7). */
int VillagerTalkOffer_IsInsect(u16 *item)
{
    return offer_is_insect(*item);
}
CLEAN_AS(func_0202a1ac, VillagerTalkOffer_IsInsect)

/* func_0202a1cc: the part's block for a request of class 1 (by ItemObject_Class1SplitOfType of
 * `type`), kept at 0x160; when there is one: its object made the talk's, its two villagers put
 * into slots 0 and 1 and its item into slot 0, and three choices offered: 0x23 running
 * data_021c2be4 when the block's own type is past its limit, else 0x1e running data_021c2bcc;
 * then the plain two; the reply data_020d9490. Whether it offered. */
int VillagerTalkOffer_KnownBlock(VillagerTalk *talk, int unused, VillagerPart *part, int type)
{
    (void) unused;
    *offer_block(talk) = VillagerPart_Block(part, ItemObject_Class1SplitOfType((u32) type));
    if (*offer_block(talk) == NULL) {
        return 0;
    }
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    VillagerTalkScene_SetObject(talk,
                                (u32) (uintptr_t) ((ItemObject *) (void *) VillagerPartBlock_Object(*offer_block(talk))));
    SceneBase_PutNpcName(offer_base(talk), VillagerPartBlock_Npc(*offer_block(talk), 0), 0);
    SceneBase_PutNpcName(offer_base(talk), VillagerPartBlock_Npc(*offer_block(talk), 1), 1);
    SceneBase_PutItemName(offer_base(talk),
                          (int) (uintptr_t) ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)), 0,
                          VILLAGER_TALK_OFFER_ITEM_KIND);
    if (VillagerPartBlock_IsOwnTypePastLimit(*offer_block(talk)) != 0) {
        offer_set(talk, &list, 0, 0x23, data_021c2be4);
    } else {
        offer_set(talk, &list, 0, 0x1e, data_021c2bcc);
    }
    offer_set_from(talk, &list, 1, data_020c8928, data_021c1e14);
    offer_set_from(talk, &list, 2, data_020c8924, data_021c1d6c);
    offer_list(talk, &list, 3, 2, data_020d9490);
    return 1;
}
CLEAN_AS(func_0202a1cc, VillagerTalkOffer_KnownBlock)

/* func_0202a2ec: the part's block whose first villager is this one (VillagerPart_FindBlock),
 * when its object's band of steps is 0 or 2 and its type is not past its limit: the block kept
 * at 0x160, its object made the talk's, its two villagers put into slots 0 and 1 and its item
 * into slot 0. When the object's date is before now: choice 0x2b (band 2) or 0x27 (band 0)
 * running data_021c2ac4. Otherwise band 2 offers data_020c8920 and band 0 data_020c8930
 * (when the pockets hold the item in state 2) running data_021c2b0c. Then the plain two, the
 * reply data_020d8f20. Whether it offered. */
int VillagerTalkOffer_PartBlock(VillagerTalk *talk, u8 *record, VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_FindBlock(part, TownVillager_NpcId(record), 1);
    ItemObject *object = block != NULL ? (ItemObject *) (void *) VillagerPartBlock_Object(block) : NULL;
    int band = object != NULL ? ItemObject_StepBand(object) : VILLAGER_TALK_OFFER_NO_BAND;
    int offered = 0;
    if (band != 0 && band != 2) {
        return 0;
    }
    if (VillagerPartBlock_IsOwnTypePastLimit(block) != 0) {
        return 0;
    }
    u8 index = 0;
    DateTime now = {0};
    u8 *player = PlayerRecords_Current();
    DateTime_Now(&now);
    TalkChoiceList list;
    TalkChoices_Clear(talk, &list);
    *offer_block(talk) = block;
    VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) object);
    SceneBase_PutNpcName(offer_base(talk), VillagerPartBlock_Npc(*offer_block(talk), index), index);
    SceneBase_PutNpcName(offer_base(talk), VillagerPartBlock_Npc(*offer_block(talk), 1), 1);
    SceneBase_PutItemName(offer_base(talk),
                          (int) (uintptr_t) ItemObject_Item((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)), index,
                          VILLAGER_TALK_OFFER_ITEM_KIND);
    if (DateTime_Compare(ItemObject_Date((ItemObject *) (uintptr_t) VillagerTalkScene_Object(talk)), &now,
                         VILLAGER_TALK_OFFER_COMPARE_ALL) == -1) {
        offer_set(talk, &list, index, band == 2 ? 0x2b : 0x27, data_021c2ac4);
        index++;
        offered = 1;
    } else if (band == 2) {
        offer_set_from(talk, &list, index, data_020c8920, data_021c2b0c);
        index++;
        offered = 1;
    } else {
        PlayerPockets *pockets = PlayerRecord_Pockets(player);
        if (VillagerTalkScene_PocketOfItem(pockets, ItemObject_Item((ItemObject *) (void *) VillagerPartBlock_Object(
                                                        *offer_block(talk)))) != VILLAGER_TALK_OFFER_NOT_FOUND) {
            offer_set_from(talk, &list, index, data_020c8930, data_021c2b0c);
            index++;
            offered = 1;
        }
    }
    if (offered != 0) {
        offer_set_from(talk, &list, index, data_020c8928, data_021c1e14);
        offer_set_from(talk, &list, (u8) (index + 1), data_020c8924, data_021c1d6c);
        u8 count = (u8) (index + 2);
        offer_list(talk, &list, count, count - 1, data_020d8f20);
    }
    return offered;
}
CLEAN_AS(func_0202a2ec, VillagerTalkOffer_PartBlock)

/* func_0202a4d8: when block 0 of the part is in use in band 1 (types 10-19), names this
 * villager second (the same NpcId: number, name and number byte) and its type is not past its
 * limit, for the types 14, 16 and 17 (the first pick, the third, the second again): the block
 * kept at 0x160, its object made the talk's, three choices (0x1d running data_021c2ee4, then the
 * plain two) with the reply data_020d8f48. Whether it offered. */
int VillagerTalkOffer_FirstPick(VillagerTalk *talk, u8 *record, VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    ItemObject *object = (ItemObject *) (void *) VillagerPartBlock_Object(block);
    if (ItemObject_IsInUse(object) == 0 || ItemObject_StepBand(object) != 1) {
        return 0;
    }
    NpcId *named = VillagerPartBlock_Npc(block, 1);
    NpcId *own = TownVillager_NpcId(record);
    if (own->head.id != named->head.id || memcmp(own->head.data, named->head.data, sizeof own->head.data) != 0 ||
        own->number != named->number || VillagerPartBlock_IsOwnTypePastLimit(block) != 0) {
        return 0;
    }
    switch (ItemObject_Type(object)) {
        case VILLAGER_PART_TYPE_FIRST_PICK:
        case VILLAGER_PART_TYPE_THIRD_PICK:
        case VILLAGER_PART_TYPE_SECOND_AGAIN: {
            TalkChoiceList list;
            TalkChoices_Clear(talk, &list);
            *offer_block(talk) = block;
            VillagerTalkScene_SetObject(talk, (u32) (uintptr_t) object);
            offer_set(talk, &list, 0, 0x1d, data_021c2ee4);
            offer_set_from(talk, &list, 1, data_020c8928, data_021c1e14);
            offer_set_from(talk, &list, 2, data_020c8924, data_021c1d6c);
            offer_list(talk, &list, 3, 2, data_020d8f48);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0202a4d8, VillagerTalkOffer_FirstPick)
