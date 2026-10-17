/* The owl's talk scene (owl_donation.h): the end of its lines, the gifts to the museum, the
 * fossils it assesses and the tests of the items the pockets offer. */
#include "owl_donation.h"

#include <stdint.h>
#include <string.h>

#include "clean.h"
#include "main/current_pockets.h"
#include "main/furniture_info.h"
#include "main/game_variables.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/item_lists.h"
#include "main/item_object.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/museum_record.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_command.h"
#include "main/session.h"
#include "main/start_kind.h"
#include "main/state_block.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/villager_part.h"
#include "main/villager_part_entry.h"
#include "owl_talk.h"

/* "sp_npc_owl", the file of its lines. */
extern const char data_ov047_02262fc0[];
/* The state block (state_block.h) and the museum's record (museum_record.h). */
extern u32 data_021dc7a8[];
extern MuseumRecord data_021f38f8;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

/* The tests of the items the pockets offer, handed to the game as its own functions. */
extern int func_ov047_02261c00(u16 *item, int state);
extern int func_ov047_02261ea4(u16 *item, int state);

/* What follows the end of each line, by line: filled from the constants on the first call (bit 0
 * of the guard says it was). */
typedef struct OwlTalkLineEnd {
    s32 line;
    MemberPointer handler; /* void (talk) */
} OwlTalkLineEnd;
static_assert(sizeof(OwlTalkLineEnd) == 0xc, "a line's end");

#define OWL_DONATION_LINE_ENDS 35
extern OwlTalkLineEnd data_ov047_02262e1c[OWL_DONATION_LINE_ENDS];
extern u32 data_ov047_02263004;
extern const MemberPointer data_ov047_02262b18, data_ov047_02262b10, data_ov047_02262b08, data_ov047_02262b00,
    data_ov047_02262af8, data_ov047_02262af0, data_ov047_02262ae8, data_ov047_02262ae0, data_ov047_02262ad8,
    data_ov047_02262ad0, data_ov047_022629f8, data_ov047_02262ac0, data_ov047_02262ab8, data_ov047_02262ab0,
    data_ov047_022629e8, data_ov047_02262aa0, data_ov047_02262b28, data_ov047_02262a90, data_ov047_02262960,
    data_ov047_02262a80, data_ov047_02262a78, data_ov047_02262a70, data_ov047_02262a68, data_ov047_02262a60,
    data_ov047_02262a58, data_ov047_02262a50, data_ov047_02262a48, data_ov047_02262b60, data_ov047_02262a30,
    data_ov047_02262a40, data_ov047_02262aa8, data_ov047_02262b20, data_ov047_02262a18, data_ov047_02262a10,
    data_ov047_02262a08;

#define OWL_DONATION_NO_SLOT (-1)
#define OWL_DONATION_NO_LINE 0xff

/* The game variable (bank 0) that, when set, makes it act as when linked. */
#define OWL_DONATION_VARIABLE 0x4a
/* The state block's flag set once an item was given to the museum. */
#define OWL_DONATION_FLAG_GIVEN 0xc
/* The current player's flags: it gave an item to the museum, it had a fossil assessed. */
#define OWL_DONATION_FLAG_PLAYER_GAVE 8
#define OWL_DONATION_FLAG_ASSESSED 0x35

/* The items it knows (owl_donation.h). */
#define OWL_FOSSIL_FIRST 0x450c
#define OWL_FOSSIL_LAST 0x45db
#define OWL_FOSSIL_CODES 0x34 /* 52 fossils, four codes each */
#define OWL_INSECT_FIRST 0x12b0
#define OWL_INSECT_LAST 0x12e7
#define OWL_FISH_FIRST 0x12e8
#define OWL_FISH_LAST 0x131f
#define OWL_PAINTING_FIRST 0x3894
#define OWL_PAINTING_LAST 0x38e3
#define OWL_REPLACED_FIRST 0x38e4
#define OWL_REPLACED_LAST 0x3933
#define OWL_REPLACED_ITEMS 0x14
#define OWL_REPLACEMENT_FIRST 0x3934
#define OWL_REPLACEMENT_LAST 0x3983
#define OWL_UNASSESSED_FOSSIL 0x1549
#define OWL_ERRAND_FIRST 0x155f
#define OWL_ERRAND_LAST 0x1560
/* The insect (its index) whose gift has a line of its own (0x33). */
#define OWL_INSECT_OWN_LINE 0x34

/* The lines that name an item given: an insect, a fish, the last fossil of a kind. */
#define OWL_LINE_INSECT 0x6e
#define OWL_LINE_INSECT_LAST 0xa5
#define OWL_LINE_FISH 0xaa
#define OWL_LINE_FISH_LAST 0xe1
#define OWL_LINE_FOSSIL_KIND 0x50
#define OWL_LINE_FOSSIL_KIND_LAST 0x67

/* The states of the pockets' tests (PocketPredicate's second argument) they answer in. */
#define OWL_POCKET_STATE_PLAIN 0
#define OWL_POCKET_STATE_ERRAND 2
/* The mode of the screen of the pockets with a test, and the screens. */
#define OWL_POCKET_ARG 13
#define OWL_SCREEN_POCKETS 0
#define OWL_SCREEN_MODE 2
#define OWL_SCREEN_MODE_PROGRESS 0x41

/* The share of the museum's record given (20.12 percent) its lines change at: 30 and 70. */
#define OWL_PERCENT_FEW 0x1e000
#define OWL_PERCENT_HALF 0x46000

/* How ItemLists_DrawRange draws the fossil an assessed one becomes: from the record, style 10,
 * filtered. */
#define OWL_DRAW_IN_RECORD 1
#define OWL_DRAW_STYLE 10
#define OWL_DRAW_FILTER 1
/* The kind of the item names put in the talk's parts (SceneBase_PutItemName). */
#define OWL_ITEM_NAME_KIND 7

/* The values of the motion with an item (SceneCommand_RequestMotion14) it takes a gift and the
 * errand's item with. */
#define OWL_TAKE_A 0
#define OWL_TAKE_B 10
#define OWL_ERRAND_A 2
#define OWL_ERRAND_B 5

static SceneCommandScene *owl_scene(OwlTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

static TalkObject *owl_object(OwlTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* The line shown. */
static u8 owl_shown(const OwlTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* `object` shows `line` of "sp_npc_owl". */
static void owl_say_on(TalkObject *object, u8 line)
{
    TalkObject_SetMessage(object, &line, data_ov047_02262fc0);
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int owl_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, OWL_DONATION_VARIABLE) != 0;
}

static int owl_given_flag(void)
{
    return StateBlock_TestFlag(data_021dc7a8, OWL_DONATION_FLAG_GIVEN);
}

/* Whether `item` is "nothing": an item with variants is compared without its variant. */
static int owl_is_none(const u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = ITEM_CODE_NONE;
        int number = ItemCode_VariantItem(item);
        return number == ItemCode_VariantItem(&none);
    }
    return *item == ITEM_CODE_NONE;
}

static int owl_in(u16 item, u16 first, u16 last)
{
    return item >= first && item <= last;
}

/* The pockets opened offering what `predicate` accepts (mode 13, the talk going on after), and
 * `after` done once they close. */
static void owl_offer_pockets(OwlTalk *talk, int (*predicate)(u16 *item, int state), int after)
{
    SceneCommand_SetPocketPredicate(owl_scene(talk), predicate, OWL_POCKET_ARG, 1);
    SceneCommand_RequestScreen(owl_scene(talk), OWL_SCREEN_POCKETS);
    OwlTalk_SetAfter(talk, after);
}

/* The gift kept in the museum's record: the state block's flag 0xc and the giver's flag 8 set,
 * and its pocket emptied. */
static void owl_keep_gift(OwlTalk *talk, u8 *giver)
{
    MuseumRecord_Give(&data_021f38f8, &talk->item);
    StateBlock_SetFlag(data_021dc7a8, OWL_DONATION_FLAG_GIVEN);
    PlayerRecord_SetFlag(giver, OWL_DONATION_FLAG_PLAYER_GAVE);
    if (talk->slot >= 0) {
        CurrentPockets_Empty(talk->slot);
        talk->slot = OWL_DONATION_NO_SLOT;
    }
}

/* ---- The end of a line */

/* func_ov047_02260b9c (line 0x3f): the screen of mode 0x41 opened, then it tells how far the
 * museum is. */
void OwlTalk_EndProgressAsk(OwlTalk *talk)
{
    SceneCommand_SetScreenMode(owl_scene(talk), OWL_SCREEN_MODE_PROGRESS, 0);
    SceneCommand_RequestScreen(owl_scene(talk), OWL_SCREEN_MODE);
    OwlTalk_SetAfter(talk, OWL_TALK_AFTER_SAY_PROGRESS);
}
CLEAN_AS(func_ov047_02260b9c, OwlTalk_EndProgressAsk)

/* func_ov047_02260bc0 (lines 0x3a to 0x3d, about an item it has already): the motion of kind
 * 17 asked for, no item, and line 0x23. */
void OwlTalk_EndThanks(OwlTalk *talk)
{
    SceneCommand_RequestMotion17(owl_scene(talk));
    talk->item = ITEM_CODE_NONE;
    talk->next_line = 0x23;
}
CLEAN_AS(func_ov047_02260bc0, OwlTalk_EndThanks)

/* func_ov047_02260be0 (lines 0x37 to 0x39, the item was given already): with an item, line 0x3a
 * for a fossil, 0x3b for an insect, 0x3c for a fish, else 0x3d. */
void OwlTalk_EndHaveIt(OwlTalk *talk)
{
    if (owl_is_none(&talk->item)) {
        return;
    }
    if (owl_in(talk->item, OWL_FOSSIL_FIRST, OWL_FOSSIL_LAST)) {
        talk->next_line = 0x3a;
    } else if (owl_in(talk->item, OWL_INSECT_FIRST, OWL_INSECT_LAST)) {
        talk->next_line = 0x3b;
    } else if (owl_in(talk->item, OWL_FISH_FIRST, OWL_FISH_LAST)) {
        talk->next_line = 0x3c;
    } else {
        talk->next_line = 0x3d;
    }
}
CLEAN_AS(func_ov047_02260be0, OwlTalk_EndHaveIt)

/* func_ov047_02260c9c (line 0x35, a new fish): with an item, the line of the fish (0xaa plus its
 * index; 0xa9 for an item that is no fish). */
void OwlTalk_EndFish(OwlTalk *talk)
{
    if (owl_is_none(&talk->item)) {
        return;
    }
    int index = owl_in(talk->item, OWL_FISH_FIRST, OWL_FISH_LAST) ? talk->item - OWL_FISH_FIRST : -1;
    talk->next_line = (u8) (index + OWL_LINE_FISH);
}
CLEAN_AS(func_ov047_02260c9c, OwlTalk_EndFish)

/* func_ov047_02260d28 (lines 0x32 and 0x33, a new insect): after line 0x32 with an item, the
 * line of the insect (0x6e plus its index; 0x6d for an item that is no insect). Line 0x33 never
 * gets here (OwlTalk_OnLineEnded takes it first). */
void OwlTalk_EndInsect(OwlTalk *talk)
{
    if (owl_shown(talk) != 0x32) {
        return;
    }
    if (owl_is_none(&talk->item)) {
        return;
    }
    int index = owl_in(talk->item, OWL_INSECT_FIRST, OWL_INSECT_LAST) ? talk->item - OWL_INSECT_FIRST : -1;
    talk->next_line = (u8) (index + OWL_LINE_INSECT);
}
CLEAN_AS(func_ov047_02260d28, OwlTalk_EndInsect)

/* func_ov047_02260dbc (lines 0x2e to 0x30, a new painting): the item kept, line 0x31 when the
 * paintings are complete, else 0x27, and the motion of kind 16 asked for. */
void OwlTalk_EndPainting(OwlTalk *talk)
{
    OwlTalk_TakeItem(talk);
    if (MuseumRecord_GroupDComplete(&data_021f38f8)) {
        talk->next_line = 0x31;
    } else {
        talk->next_line = 0x27;
    }
    SceneCommand_RequestMotion16(owl_scene(talk));
}
CLEAN_AS(func_ov047_02260dbc, OwlTalk_EndPainting)

/* func_ov047_02260df0 (lines 0x29, 0x31, 0x34 and 0x36, a group complete): line 0x2a when the
 * whole museum is, else 0x2b. */
void OwlTalk_EndCompleteGroup(OwlTalk *talk)
{
    if (MuseumRecord_Complete(&data_021f38f8)) {
        talk->next_line = 0x2a;
    } else {
        talk->next_line = 0x2b;
    }
}
CLEAN_AS(func_ov047_02260df0, OwlTalk_EndCompleteGroup)

/* func_ov047_02260e18 (line 0x26, a fossil kept): the motion of kind 16 asked for, the item kept,
 * then line 0x27 (0x20 when assessing). */
void OwlTalk_EndTaken(OwlTalk *talk)
{
    SceneCommand_RequestMotion16(owl_scene(talk));
    OwlTalk_TakeItem(talk);
    talk->next_line = talk->assessing == 0 ? 0x27 : 0x20;
}
CLEAN_AS(func_ov047_02260e18, OwlTalk_EndTaken)

/* func_ov047_02260e44 (line 0x1f): the motion of kind 17 asked for and line 0x20. */
void OwlTalk_EndDeclined(OwlTalk *talk)
{
    SceneCommand_RequestMotion17(owl_scene(talk));
    talk->next_line = 0x20;
}
CLEAN_AS(func_ov047_02260e44, OwlTalk_EndDeclined)

/* func_ov047_02260e58 (line 0x1d, after an assessed fossil): line 0x1e when unlinked (without the
 * game variable 0x4a), this console is the host and the museum lacks the fossil; else the
 * motion of kind 17 asked for and line 0x20. */
void OwlTalk_EndAssessed(OwlTalk *talk)
{
    if (!owl_linked_or_variable(data_020ccf94)) {
        if (TalkChecks_IsHostOrAlone() && MuseumRecord_IsGiven(&data_021f38f8, &talk->item) == 0) {
            talk->next_line = 0x1e;
            return;
        }
    }
    SceneCommand_RequestMotion17(owl_scene(talk));
    talk->next_line = 0x20;
}
CLEAN_AS(func_ov047_02260e58, OwlTalk_EndAssessed)

/* func_ov047_02260ec0 (lines 0x1a to 0x1c, the fossil assessed): when assessing, line 0x1d; else
 * 0x69 when unlinked (without the game variable 0x4a), this console is the host and the museum
 * lacks the fossil, else 0x6a. */
void OwlTalk_EndAssessedFossil(OwlTalk *talk)
{
    if (talk->assessing != 0) {
        talk->next_line = 0x1d;
    } else if (!Session_IsLinked(data_020ccf94) && *GameVariables_Slot(0, OWL_DONATION_VARIABLE) == 0 &&
               TalkChecks_IsHostOrAlone() && MuseumRecord_IsGiven(&data_021f38f8, &talk->item) == 0) {
        talk->next_line = 0x69;
    } else {
        talk->next_line = 0x6a;
    }
}
CLEAN_AS(func_ov047_02260ec0, OwlTalk_EndAssessedFossil)

/* func_ov047_02260f24 (line 0x19, the assessment): with an item, the current player's flag 0x35
 * set, the item becomes a fossil drawn from the record's fossils (and so does its pocket, when
 * it came from one) and its name is the talk's part 0; another fossil drawn, not that one, is
 * part 1. Then one of the lines 0x1a to 0x1c at random. */
void OwlTalk_EndAssess(OwlTalk *talk)
{
    if (!owl_is_none(&talk->item)) {
        u16 fossil;
        u16 other;
        PlayerRecord_SetFlag(PlayerRecords_Current(), OWL_DONATION_FLAG_ASSESSED);
        ItemLists_DrawRange(&fossil, OWL_FOSSIL_FIRST, OWL_FOSSIL_CODES, NULL, 0, NULL, OWL_DRAW_IN_RECORD, OWL_DRAW_STYLE,
                            NULL, OWL_DRAW_FILTER);
        talk->item = fossil;
        if (talk->slot >= 0) {
            CurrentPockets_Set(&talk->item, 0, talk->slot);
        }
        SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->item, 0, OWL_ITEM_NAME_KIND);
        ItemLists_DrawRange(&other, OWL_FOSSIL_FIRST, OWL_FOSSIL_CODES, &talk->item, 1, NULL, OWL_DRAW_IN_RECORD,
                            OWL_DRAW_STYLE, NULL, OWL_DRAW_FILTER);
        SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &other, 1, OWL_ITEM_NAME_KIND);
    }
    talk->next_line = (u8) (MainRandom_Below(3) + 0x1a);
}
CLEAN_AS(func_ov047_02260f24, OwlTalk_EndAssess)

/* func_ov047_0226100c (line 0x15): with an item (a plain test, variants not dropped), the
 * motion of kind 17 asked for. */
void OwlTalk_EndNotGiven(OwlTalk *talk)
{
    if (talk->item != ITEM_CODE_NONE) {
        SceneCommand_RequestMotion17(owl_scene(talk));
    }
}
CLEAN_AS(func_ov047_0226100c, OwlTalk_EndNotGiven)

/* func_ov047_0226102c (lines 0x18, 0x40 and 0x41): the menu again, line 0x46 (0x45 before any
 * item was given to the museum). */
void OwlTalk_EndMenuLine(OwlTalk *talk)
{
    if (owl_given_flag()) {
        talk->next_line = 0x46;
    } else {
        talk->next_line = 0x45;
    }
}
CLEAN_AS(func_ov047_0226102c, OwlTalk_EndMenuLine)

/* func_ov047_02261054 (line 0x6a): the motion of kind 17 asked for and line 0x6b. */
void OwlTalk_EndOffer6a(OwlTalk *talk)
{
    SceneCommand_RequestMotion17(owl_scene(talk));
    talk->next_line = 0x6b;
}
CLEAN_AS(func_ov047_02261054, OwlTalk_EndOffer6a)

/* func_ov047_02261068 (lines 0x42 and 0x43, a room item): the motion of kind 17 asked for, then
 * the menu again (OwlTalk_EndMenuLine). */
void OwlTalk_EndOther(OwlTalk *talk)
{
    SceneCommand_RequestMotion17(owl_scene(talk));
    OwlTalk_EndMenuLine(talk);
}
CLEAN_AS(func_ov047_02261068, OwlTalk_EndOther)

/* func_ov047_0226107c (lines 0x16 and 0x17): the pockets opened offering the fossils to assess,
 * then OwlTalk_TakeFossil. */
void OwlTalk_EndAskFossil(OwlTalk *talk)
{
    owl_offer_pockets(talk, func_ov047_02261c00, OWL_TALK_AFTER_TAKE_FOSSIL);
}
CLEAN_AS(func_ov047_0226107c, OwlTalk_EndAskFossil)

/* func_ov047_022610a4 (line 0x14): the pockets opened offering the items for the museum, then
 * OwlTalk_TakeOffered. */
void OwlTalk_EndAskGift(OwlTalk *talk)
{
    owl_offer_pockets(talk, func_ov047_02261ea4, OWL_TALK_AFTER_TAKE_OFFERED);
}
CLEAN_AS(func_ov047_022610a4, OwlTalk_EndAskGift)

/* func_ov047_022610cc (vtable slot 0x14, a line ended), for the lines of "sp_npc_owl" only and
 * unless a game is being started anew:
 * - lines below 0xc: the menu, line 0x44 (0xc before any item was given to the museum);
 * - line 0x33 and the insects' lines (0x6e to 0xa5): the item kept, line 0x34 when the insects
 *   are complete, else 0x27, and the motion of kind 16 asked for;
 * - the fishes' lines (0xaa to 0xe1): the same, with line 0x36 when the fish are complete;
 * - else no line to go on with, then each handler of the line shown (the table, keyed by line),
 *   then:
 *   - the fossil kinds' lines (0x50 to 0x67): line 0x29 when the fossils are complete, else
 *     0x27 (0x20 when assessing), no item, and the motion of kind 16 asked for;
 *   - lines 0x25, 0x2c, 0x2d and 0x69, a new fossil: with an item, it is kept in the museum's
 *     record (the giver the current player at the start of the line's end); then, for a kind
 *     of one fossil, line 0x2d, and after line 0x2d the kind's line; for the kind's last fossil
 *     the kind's line; else 0x26.
 *   The talk shows the line set, if any.
 * The line shown is read again for each entry of the table and each test after it. */
void OwlTalk_OnLineEnded(OwlTalk *talk)
{
    static const MemberPointer *const handlers[OWL_DONATION_LINE_ENDS] = {
        &data_ov047_02262b18, /* 0x14: OwlTalk_EndAskGift */
        &data_ov047_02262b10, /* 0x15: OwlTalk_EndNotGiven */
        &data_ov047_02262b08, /* 0x16: OwlTalk_EndAskFossil */
        &data_ov047_02262b00, /* 0x17: OwlTalk_EndAskFossil */
        &data_ov047_02262af8, /* 0x18: OwlTalk_EndMenuLine */
        &data_ov047_02262af0, /* 0x19: OwlTalk_EndAssess */
        &data_ov047_02262ae8, /* 0x1a: OwlTalk_EndAssessedFossil */
        &data_ov047_02262ae0, /* 0x1b: OwlTalk_EndAssessedFossil */
        &data_ov047_02262ad8, /* 0x1c: OwlTalk_EndAssessedFossil */
        &data_ov047_02262ad0, /* 0x1d: OwlTalk_EndAssessed */
        &data_ov047_022629f8, /* 0x1f: OwlTalk_EndDeclined */
        &data_ov047_02262ac0, /* 0x26: OwlTalk_EndTaken */
        &data_ov047_02262ab8, /* 0x29: OwlTalk_EndCompleteGroup */
        &data_ov047_02262ab0, /* 0x2e: OwlTalk_EndPainting */
        &data_ov047_022629e8, /* 0x2f: OwlTalk_EndPainting */
        &data_ov047_02262aa0, /* 0x30: OwlTalk_EndPainting */
        &data_ov047_02262b28, /* 0x31: OwlTalk_EndCompleteGroup */
        &data_ov047_02262a90, /* 0x32: OwlTalk_EndInsect */
        &data_ov047_02262960, /* 0x33: OwlTalk_EndInsect */
        &data_ov047_02262a80, /* 0x34: OwlTalk_EndCompleteGroup */
        &data_ov047_02262a78, /* 0x35: OwlTalk_EndFish */
        &data_ov047_02262a70, /* 0x36: OwlTalk_EndCompleteGroup */
        &data_ov047_02262a68, /* 0x37: OwlTalk_EndHaveIt */
        &data_ov047_02262a60, /* 0x38: OwlTalk_EndHaveIt */
        &data_ov047_02262a58, /* 0x39: OwlTalk_EndHaveIt */
        &data_ov047_02262a50, /* 0x3a: OwlTalk_EndThanks */
        &data_ov047_02262a48, /* 0x3b: OwlTalk_EndThanks */
        &data_ov047_02262b60, /* 0x3c: OwlTalk_EndThanks */
        &data_ov047_02262a30, /* 0x3d: OwlTalk_EndThanks */
        &data_ov047_02262a40, /* 0x3f: OwlTalk_EndProgressAsk */
        &data_ov047_02262aa8, /* 0x40: OwlTalk_EndMenuLine */
        &data_ov047_02262b20, /* 0x41: OwlTalk_EndMenuLine */
        &data_ov047_02262a18, /* 0x42: OwlTalk_EndOther */
        &data_ov047_02262a10, /* 0x43: OwlTalk_EndOther */
        &data_ov047_02262a08, /* 0x6a: OwlTalk_EndOffer6a */
    };

    if (StartKind_IsSet()) {
        return;
    }
    if (strncmp(((const MessageReceiver *) (const void *) talk)->name, data_ov047_02262fc0, strlen(data_ov047_02262fc0)) !=
        0) {
        return;
    }
    u8 shown = owl_shown(talk);
    if (shown < 0xc) {
        talk->next_line = owl_given_flag() ? 0x44 : 0xc;
        owl_say_on(owl_object(talk), (u8) talk->next_line);
        return;
    }
    if (shown == 0x33 || owl_in(shown, OWL_LINE_INSECT, OWL_LINE_INSECT_LAST)) {
        OwlTalk_TakeItem(talk);
        talk->next_line = MuseumRecord_GroupCComplete(&data_021f38f8) ? 0x34 : 0x27;
        SceneCommand_RequestMotion16(owl_scene(talk));
        owl_say_on(owl_object(talk), (u8) talk->next_line);
        return;
    }
    if (owl_in(shown, OWL_LINE_FISH, OWL_LINE_FISH_LAST)) {
        OwlTalk_TakeItem(talk);
        talk->next_line = MuseumRecord_GroupBComplete(&data_021f38f8) ? 0x36 : 0x27;
        SceneCommand_RequestMotion16(owl_scene(talk));
        owl_say_on(owl_object(talk), (u8) talk->next_line);
        return;
    }

    u8 *giver = PlayerRecords_Current();
    talk->next_line = OWL_DONATION_NO_LINE;
    {
        u32 flags = data_ov047_02263004;
        if ((flags & 1) == 0) {
            for (int i = 0; i < OWL_DONATION_LINE_ENDS; i++) {
                data_ov047_02262e1c[i].handler = *handlers[i];
            }
            data_ov047_02263004 = flags | 1;
        }
    }
    for (u32 i = 0; i < OWL_DONATION_LINE_ENDS; i++) {
        const OwlTalkLineEnd *entry = &data_ov047_02262e1c[i];
        if (entry->line == owl_shown(talk)) {
            MemberPointer_CallVoid(&entry->handler, talk);
        }
    }

    if (owl_in(owl_shown(talk), OWL_LINE_FOSSIL_KIND, OWL_LINE_FOSSIL_KIND_LAST)) {
        if (MuseumRecord_GroupAComplete(&data_021f38f8)) {
            talk->next_line = 0x29;
        } else {
            talk->next_line = talk->assessing == 0 ? 0x27 : 0x20;
        }
        talk->item = ITEM_CODE_NONE;
        SceneCommand_RequestMotion16(owl_scene(talk));
    }
    shown = owl_shown(talk);
    if ((shown == 0x25 || shown == 0x2c || shown == 0x2d || shown == 0x69) && !owl_is_none(&talk->item)) {
        owl_keep_gift(talk, giver);
        int kind = FurnitureInfo_MuseumKind(&talk->item);
        int pieces = FurnitureInfo_CountMuseumKind(kind);
        int given = MuseumRecord_CountGroupAKind(&data_021f38f8, kind);
        if (pieces == 1) {
            if (owl_shown(talk) != 0x2d) {
                talk->next_line = 0x2d;
            } else if (!owl_is_none(&talk->item)) {
                talk->next_line = (u8) (kind + OWL_LINE_FOSSIL_KIND);
            }
        } else if (pieces == given) {
            if (!owl_is_none(&talk->item)) {
                talk->next_line = (u8) (kind + OWL_LINE_FOSSIL_KIND);
            }
        } else {
            talk->next_line = 0x26;
        }
    }
    if (talk->next_line != OWL_DONATION_NO_LINE) {
        owl_say_on(owl_object(talk), (u8) talk->next_line);
    }
}
CLEAN_AS(func_ov047_022610cc, OwlTalk_OnLineEnded)

/* func_ov047_02261618: with an item, it is kept in the museum's record (the giver the current
 * player), and the talk has no item any longer. */
void OwlTalk_TakeItem(OwlTalk *talk)
{
    if (owl_is_none(&talk->item)) {
        return;
    }
    u8 *giver = PlayerRecords_Current();
    owl_keep_gift(talk, giver);
    talk->item = ITEM_CODE_NONE;
}
CLEAN_AS(func_ov047_02261618, OwlTalk_TakeItem)

/* ---- The work after a screen */

/* func_ov047_02261a24 (OWL_TALK_AFTER_TAKE_ERRAND): when the pockets were closed on an item and
 * this console is the host, the item is taken from its pocket (the motion with it asked for
 * unless it is nothing), the current player's errand is marked done (its entry's low five bits
 * 1), and line 0xe7; else line 0xe8.
 * QUIRK: the pocket is emptied whatever it is (the test that it is one never fails). */
void OwlTalk_TakeErrand(OwlTalk *talk)
{
    TalkObject *object = owl_object(talk);
    u8 line = 0xe8;
    u8 *record = PlayerRecords_Current();

    if (GroupParams_C4CIs1() && TalkChecks_IsHostOrAlone()) {
        int slot = GroupParams_Arg();
        u16 item = CurrentPockets_Item((u32) slot);
        if (slot >= 0) {
            CurrentPockets_Empty(slot);
        }
        if (!owl_is_none(&item)) {
            SceneCommand_RequestMotion14(owl_scene(talk), &item, OWL_ERRAND_A, OWL_ERRAND_B, 0);
        }
        VillagerPart *part = (VillagerPart *) (void *) PlayerRecord_VillagerPart(record);
        VillagerPartEntry *entry = (VillagerPartEntry *) (void *) VillagerPart_Object94(part);
        ItemObject_SetLow5((ItemObject *) (void *) VillagerPartEntry_Self(entry), 1);
        line = 0xe7;
    }
    owl_say_on(object, line);
}
CLEAN_AS(func_ov047_02261a24, OwlTalk_TakeErrand)

/* func_ov047_02261b10 (OWL_TALK_AFTER_SAY_PROGRESS): when the screen was closed by a choice
 * (GroupParams_C4CIs1), how far the museum is: line 0x10 when nothing was given, 0x11 up to 30
 * percent, 0x12 up to 70, 0x49 when the museum is complete, else 0x13. */
void OwlTalk_SayProgress(OwlTalk *talk)
{
    TalkObject *object = owl_object(talk);

    if (GroupParams_C4CIs1()) {
        MuseumRecord *record = &data_021f38f8;
        u8 line = 0x13;
        int percent = MuseumRecord_PercentGiven(record);
        if (percent == 0) {
            line = 0x10;
        } else if (percent <= OWL_PERCENT_FEW) {
            line = 0x11;
        } else if (percent <= OWL_PERCENT_HALF) {
            line = 0x12;
        } else if (MuseumRecord_Complete(record)) {
            line = 0x49;
        }
        owl_say_on(object, line);
    }
}
CLEAN_AS(func_ov047_02261b10, OwlTalk_SayProgress)

/* func_ov047_02261b88 (OWL_TALK_AFTER_TAKE_FOSSIL): when the pockets were closed on an item, it
 * and its pocket are the talk's, the motion with it asked for, and line 0x19 (the
 * assessment); else no item, the next line asked for, and line 0x22. Then the next line is the
 * work after. */
void OwlTalk_TakeFossil(OwlTalk *talk)
{
    TalkObject *object = owl_object(talk);
    u8 line = 0x22;

    if (GroupParams_C4CIs1()) {
        talk->slot = GroupParams_Arg();
        talk->item = CurrentPockets_Item((u32) talk->slot);
        SceneCommand_RequestMotion14(owl_scene(talk), &talk->item, OWL_TAKE_A, OWL_TAKE_B, 0);
        line = 0x19;
    } else {
        talk->item = ITEM_CODE_NONE;
        SceneCommand_RequestNextLine(owl_scene(talk));
    }
    OwlTalk_SetNext(talk, OWL_TALK_AFTER_NEXT_LINE);
    owl_say_on(object, line);
}
CLEAN_AS(func_ov047_02261b88, OwlTalk_TakeFossil)

/* func_ov047_02261c20 (OWL_TALK_AFTER_NEXT_LINE): the next line asked for. */
void OwlTalk_NextLine(OwlTalk *talk)
{
    SceneCommand_RequestNextLine(owl_scene(talk));
}
CLEAN_AS(func_ov047_02261c20, OwlTalk_NextLine)

/* func_ov047_02261c28 (OWL_TALK_AFTER_TAKE_OFFERED): when the pockets were closed on an item, it
 * and its pocket are the talk's; unless it is nothing, its name is the talk's part 0 and:
 * - the fossil to assess (0x1549): line 0x21;
 * - an item the museum lacks: a fossil, not assessing and line 0x25; a painting, one of the
 *   lines 0x2e to 0x30 at random; an insect, line 0x32 (0x33 for the insect 0x34); a fish, line
 *   0x35; one of the room items 0x38e4-0x3933, it becomes its replacement 0x3934 on (in its
 *   pocket too) and line 0x42; one of those, line 0x43; else line 0x22;
 * - an item the museum has: by its giver, line 0x39 (the current player), 0x38 (another player
 *   of the town, whose name is the talk's part 0), 0x37 (a player who has left), else 0x22;
 * then the motion with it asked for and the next line as the work after. When the pockets were closed without one, no item and the next line asked for,
 * and line 0x22. */
void OwlTalk_TakeOffered(OwlTalk *talk)
{
    TalkObject *object = owl_object(talk);
    u8 line = 0x22;

    if (!GroupParams_C4CIs1()) {
        talk->item = ITEM_CODE_NONE;
        SceneCommand_RequestNextLine(owl_scene(talk));
        owl_say_on(object, line);
        return;
    }
    PlayerIdText name;
    PlayerIdText_Construct(&name);
    talk->slot = OWL_DONATION_NO_SLOT;
    talk->slot = GroupParams_Arg();
    talk->item = CurrentPockets_Item((u32) talk->slot);
    if (!owl_is_none(&talk->item)) {
        MuseumRecord *record = &data_021f38f8;
        SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->item, 0, OWL_ITEM_NAME_KIND);
        if (talk->item == OWL_UNASSESSED_FOSSIL) {
            line = 0x21;
        } else if (MuseumRecord_IsGiven(record, &talk->item) == 0) {
            u16 item = talk->item;
            if (owl_in(item, OWL_FOSSIL_FIRST, OWL_FOSSIL_LAST)) {
                talk->assessing = 0;
                line = 0x25;
            } else if (owl_in(item, OWL_PAINTING_FIRST, OWL_PAINTING_LAST)) {
                line = (u8) (MainRandom_Below(3) + 0x2e);
            } else if (owl_in(item, OWL_INSECT_FIRST, OWL_INSECT_LAST)) {
                line = item - OWL_INSECT_FIRST != OWL_INSECT_OWN_LINE ? 0x32 : 0x33;
            } else if (owl_in(item, OWL_FISH_FIRST, OWL_FISH_LAST)) {
                line = 0x35;
            } else if (owl_in(item, OWL_REPLACED_FIRST, OWL_REPLACED_LAST)) {
                unsigned int index = (unsigned int) (item - OWL_REPLACED_FIRST) >> 2;
                talk->item = (u16) (index < OWL_REPLACED_ITEMS ? OWL_REPLACEMENT_FIRST + index * 4 : OWL_REPLACEMENT_FIRST);
                if (talk->slot >= 0) {
                    CurrentPockets_Set(&talk->item, 0, talk->slot);
                }
                line = 0x42;
            } else if (owl_in(item, OWL_REPLACEMENT_FIRST, OWL_REPLACEMENT_LAST)) {
                line = 0x43;
            }
        } else {
            switch (MuseumRecord_Giver(record, &talk->item)) {
                case MUSEUM_BY_CURRENT_PLAYER:
                    line = 0x39;
                    break;
                case MUSEUM_BY_OTHER_PLAYER:
                    if (MuseumRecord_GiverName(record, &name, &talk->item)) {
                        TalkObject_SetPart(object, 0, (TextBase *) (void *) &name);
                    }
                    line = 0x38;
                    break;
                case MUSEUM_BY_FORMER_PLAYER:
                    line = 0x37;
                    break;
                default:
                    break;
            }
        }
        SceneCommand_RequestMotion14(owl_scene(talk), &talk->item, OWL_TAKE_A, OWL_TAKE_B, 0);
        OwlTalk_SetNext(talk, OWL_TALK_AFTER_NEXT_LINE);
    }
    PlayerIdText_Destruct(&name);
    owl_say_on(object, line);
}
CLEAN_AS(func_ov047_02261c28, OwlTalk_TakeOffered)

/* ---- The tests of the items the pockets offer */

/* func_ov047_02261ae8: in state 2, the items 0x155f and 0x1560 (a villager's errand). */
u16 OwlTalk_IsErrandItem(u16 *item, int state)
{
    if (state != OWL_POCKET_STATE_ERRAND) {
        return 0;
    }
    return owl_in(*item, OWL_ERRAND_FIRST, OWL_ERRAND_LAST);
}
CLEAN_AS(func_ov047_02261ae8, OwlTalk_IsErrandItem)

/* func_ov047_02261c00: in state 0, the fossil to assess (0x1549). */
int OwlTalk_IsFossilToAssess(u16 *item, int state)
{
    if (state != OWL_POCKET_STATE_PLAIN) {
        return 0;
    }
    return *item == OWL_UNASSESSED_FOSSIL;
}
CLEAN_AS(func_ov047_02261c00, OwlTalk_IsFossilToAssess)

/* func_ov047_02261ea4: in state 0, what the museum takes or the owl knows: the fossils, the
 * fish, the insects, the paintings, the room items 0x38e4-0x3983 and the fossil to assess. */
int OwlTalk_IsMuseumItem(u16 *item, int state)
{
    if (state != OWL_POCKET_STATE_PLAIN) {
        return 0;
    }
    u16 v = *item;
    return owl_in(v, OWL_UNASSESSED_FOSSIL, OWL_UNASSESSED_FOSSIL) | owl_in(v, OWL_FOSSIL_FIRST, OWL_FOSSIL_LAST) |
           owl_in(v, OWL_PAINTING_FIRST, OWL_PAINTING_LAST) | owl_in(v, OWL_INSECT_FIRST, OWL_INSECT_LAST) |
           owl_in(v, OWL_FISH_FIRST, OWL_FISH_LAST) | owl_in(v, OWL_REPLACED_FIRST, OWL_REPLACED_LAST) |
           owl_in(v, OWL_REPLACEMENT_FIRST, OWL_REPLACEMENT_LAST);
}
CLEAN_AS(func_ov047_02261ea4, OwlTalk_IsMuseumItem)
