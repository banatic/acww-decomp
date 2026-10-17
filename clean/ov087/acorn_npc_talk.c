/* The talk scene of overlay 87's character: the items it takes for points, its rewards and the
 * fortune letter (acorn_npc_talk.h). */
#include "acorn_npc_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/current_pockets.h"
#include "main/item_code.h"
#include "main/item_record.h"
#include "main/letter.h"
#include "main/mail_text.h"
#include "main/main_random.h"
#include "main/message_reader.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_field_2416.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(sizeof(AcornNpcLine) == 8, "a line");
static_assert(sizeof(AcornNpcLevel) == 4, "a level");
static_assert(sizeof(AcornNpcFortunePart) == 8, "a part of the fortune");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The talk scene's vtable. */
extern const u8 data_ov087_0227945c[];
/* The message file's name, "sp_npc_acorn", and the fortune letter's, "ev_fortune". */
extern const char data_ov087_02279598[];
extern const char data_ov087_022795a8[];
/* The fortune letter's parts and its tag and paper. */
extern const AcornNpcFortunePart data_ov087_02279304[ACORN_NPC_FORTUNE_PARTS];
extern const u8 data_ov087_022793c4[];
extern const u8 data_ov087_022793c0[];
/* The levels of the rewards. Indexed by the player's level unchecked in places (see
 * AcornNpcTalk_OnLineEnded), so declared without a bound. */
extern const AcornNpcLevel data_ov087_02279324[];

/* The game's pocket predicate handed to Pockets_Select (AcornNpcTalk_IsItemInState0). */
extern int func_ov087_02278f04(u16 *item, int state);

/* The daily bits of the current player, and the player record's flag of the first meeting. */
#define ACT_DAILY_TALKED 0x19
#define ACT_DAILY_FORTUNE 0x1a
#define ACT_FLAG_MET 0x0f

/* The fortune: message 2 of "ev_fortune"; one of four kinds (message 4-7 of "st_fortune"),
 * then for each further part a message of "st_fortune2": four per kind, sixteen per part; a
 * pile of four of item 0x1d marked in the player's item record. */
#define ACT_FORTUNE_MESSAGE 2
#define ACT_FORTUNE_KINDS 4
#define ACT_FORTUNE_KIND_FIRST 4
#define ACT_FORTUNE_LINES_PER_KIND 4
#define ACT_FORTUNE_LINES_PER_PART 16
#define ACT_FORTUNE_PILE_ITEM 0x1d
#define ACT_FORTUNE_PILE_COUNT 4

/* The item shown with line 0x15. */
#define ACT_ITEM_1565 0x1565

/* The ways of SceneBase_PutValue's numbers, and of item names. */
#define ACT_VALUE_FORMAT 3
#define ACT_ITEM_NAME_KIND 7

static u8 act_line_shown(const AcornNpcTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *act_talk_object(AcornNpcTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *act_scene(AcornNpcTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* Message `message` of "sp_npc_acorn" shown. */
static void act_say(AcornNpcTalk *talk, u8 message)
{
    TalkObject_SetMessage(act_talk_object(talk), &message, data_ov087_02279598);
}

static PlayerField2416 *act_field(u8 *record)
{
    return (PlayerField2416 *) (void *) PlayerRecord_Field2416(record);
}

static int act_is_taken(u16 item)
{
    return item >= ACORN_NPC_ITEM_FIRST && item <= ACORN_NPC_ITEM_LAST;
}

/* Whether `item` is 0x1546: an item with variants is compared without its variant. */
static int act_is_spoiler(const u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 spoiler = ACORN_NPC_ITEM_SPOILER;
        int number = ItemCode_VariantItem(item);
        return number == ItemCode_VariantItem(&spoiler);
    }
    return *item == ACORN_NPC_ITEM_SPOILER;
}

/* The items brought (answer 0 to line 5): each of the items 0x1542-0x1546 in the pockets is
 * counted (0x1546 apart) and its slot emptied. Without 0x1546 among them, one of the lines
 * 7-9 and a point for each; with it, no points: line 0x18 with item 0x1546 shown when there
 * were others too, else line 0x19. The item shown with the line (motion 14) is 0x1542 but in
 * that one case. */
static int act_take_items(AcornNpcTalk *talk, u8 *record)
{
    PlayerField2416 *field = act_field(record);
    int others = 0;
    int spoilers = 0;
    for (int slot = 0; slot < POCKET_SLOTS; slot++) {
        u16 item = CurrentPockets_Item((u32) slot);
        if (!act_is_taken(item)) {
            continue;
        }
        if (act_is_spoiler(&item)) {
            spoilers++;
        } else {
            others++;
        }
        CurrentPockets_Empty(slot);
    }
    u16 shown = ACORN_NPC_ITEM_FIRST;
    int line;
    if (spoilers == 0) {
        line = (u8) (MainRandom_Below(3) + ACORN_NPC_LINE_TAKEN);
        for (; others > 0; others--) {
            PlayerField2416_AddPoints(field, 1);
        }
    } else if (others != 0) {
        shown = ACORN_NPC_ITEM_SPOILER;
        line = ACORN_NPC_LINE_SPOILED_SOME;
    } else {
        line = ACORN_NPC_LINE_SPOILED_ALL;
    }
    SceneCommand_RequestMotion14(act_scene(talk), &shown, 0, 5, 0);
    return line;
}

/* The fortune (answer 0 to line 0x10), when the pockets have a free letter: its first part a
 * kind drawn at random (message 4-7 of "st_fortune"), the next three a line of that kind drawn
 * at random (of "st_fortune2", the n-th part's in the n-th sixteen); the letter of message 2 of
 * "ev_fortune" written to the player; a pile of four of item 0x1d marked in the player's item
 * record; the daily bit 0x1a set. Line 0x13, or 0x12 without a free letter. */
static int act_write_fortune(u8 *record)
{
    if (CurrentPockets_FreeLetterIndex() == -1) {
        return ACORN_NPC_LINE_NO_LETTER;
    }
    Letter *letter = (Letter *) (void *) CurrentPockets_FreeLetter();
    if (letter == NULL) {
        return ACORN_NPC_LINE_NO_LETTER;
    }
    MessagePart text;
    MessagePart_Construct(&text);
    int kind = (int) MainRandom_Below(ACT_FORTUNE_KINDS) + ACT_FORTUNE_KIND_FIRST;
    int message = kind;
    for (int i = 0; i < ACORN_NPC_FORTUNE_PARTS; i++) {
        u8 number = (u8) message;
        const AcornNpcFortunePart *part = &data_ov087_02279304[i];
        MessageReader_LoadMessage((int) (u32) (uintptr_t) &text, &number, (int) (u32) (uintptr_t) part->file);
        MailText_SetPartText(part->part, &text);
        message = (kind - ACT_FORTUNE_KIND_FIRST) * ACT_FORTUNE_LINES_PER_KIND;
        message += (int) MainRandom_Below(ACT_FORTUNE_LINES_PER_KIND);
        message += i * ACT_FORTUNE_LINES_PER_PART;
    }
    u8 letter_message = ACT_FORTUNE_MESSAGE;
    Letter_WriteSpecialToPlayer(letter, &letter_message, data_ov087_022795a8, data_ov087_022793c4, data_ov087_022793c0,
                                PlayerRecord_Player(record));
    if (record != NULL) {
        u16 pile = ItemCode_MakePile(ACT_FORTUNE_PILE_ITEM, ACT_FORTUNE_PILE_COUNT);
        ItemRecord_Mark((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &pile, 0);
    }
    TalkChecks_TestSetDailyBit(ACT_DAILY_FORTUNE, 1);
    MessagePart_Destruct(&text);
    return ACORN_NPC_LINE_FORTUNE_DONE;
}

/* func_ov087_02278ab8 (slot 0x18, the player's answer), by the line shown, answered 0:
 * - line 5: the items brought taken (act_take_items);
 * - line 0x10: the fortune written (act_write_fortune).
 * The line, when one was picked, is shown. */
void AcornNpcTalk_OnAnswer(AcornNpcTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    u8 *record = PlayerRecords_Current();
    int next = ACORN_NPC_NO_LINE;

    switch (act_line_shown(talk)) {
        case ACORN_NPC_LINE_BROUGHT:
            if (answer == 0) {
                next = act_take_items(talk, record);
            }
            break;
        case ACORN_NPC_LINE_FORTUNE:
            if (answer == 0) {
                next = act_write_fortune(record);
            }
            break;
        default:
            break;
    }
    if (next != ACORN_NPC_NO_LINE) {
        act_say(talk, (u8) next);
    }
}
CLEAN_AS(func_ov087_02278ab8, AcornNpcTalk_OnAnswer)

/* How many of the pockets' slots hold one of the items 0x1542-0x1546. */
static int act_count_items(void)
{
    int count = 0;
    for (int slot = 0; slot < POCKET_SLOTS; slot++) {
        if (act_is_taken(CurrentPockets_Item((u32) slot))) {
            count++;
        }
    }
    return count;
}

/* The points the level's reward still needs, at the player's level. */
static int act_points_needed(PlayerField2416 *field)
{
    int level = PlayerField2416_Level(field);
    return data_ov087_02279324[level].points - PlayerField2416_Points(field);
}

/* Whether the points reach the bound of the level's reward (the points asked for first). */
static int act_reward_due(PlayerField2416 *field)
{
    int points = PlayerField2416_Points(field);
    return points >= data_ov087_02279324[PlayerField2416_Level(field)].points;
}

/* The level's reward's name put in part 0, at the player's level. */
static void act_put_reward(AcornNpcTalk *talk, PlayerField2416 *field)
{
    u16 reward = data_ov087_02279324[PlayerField2416_Level(field)].item;
    SceneBase_PutItemName(&talk->base, (int) (u32) (uintptr_t) &reward, 0, ACT_ITEM_NAME_KIND);
}

/* func_ov087_02278cb0 (slot 0x14, a line ended), by the line shown:
 * - 0x02, 0x03: with any of the items 0x1542-0x1546 in a pocket in state 0, their count in
 *   value slot 2 and line 5; else with every level given line 0x17; else the points the
 *   level's reward needs in slot 1 and line 4, or line 0x16 when it needs none;
 * - 0x07-0x09: the points in slot 0, then line 0x16 with every level given, else 0x0a;
 * - 0x0a: with the points the level's reward needs, its name in part 0 and line 0x0b; else
 *   the points it needs in slot 1 and line 0x0f;
 * - 0x0b, 0x0d: the reward put in the pockets (line 0x0c without room); the level raised, the
 *   reward shown (motion 13; QUIRK: the new level's, not the one given); then, unless every
 *   level was given, line 0x0d with the next reward's name when its points are there too,
 *   else 0x0e;
 * - 0x14: item 0x1565 shown (motion 13) and line 0x15.
 * The line, when one was picked, is shown.
 * QUIRK: lines 0x0a, 0x0b and 0x0d read the level's entry unchecked: at level 12 (every
 * level given) a thirteenth entry, the overlay's bytes that follow the table. */
void AcornNpcTalk_OnLineEnded(AcornNpcTalk *talk)
{
    PlayerField2416 *field = act_field(PlayerRecords_Current());
    int next = ACORN_NPC_NO_LINE;

    switch (act_line_shown(talk)) {
        case ACORN_NPC_LINE_TODAY:
        case ACORN_NPC_LINE_AGAIN:
            if (Pockets_Select(func_ov087_02278f04) != 0) {
                SceneBase_PutValue(&talk->base, act_count_items(), 2, ACT_VALUE_FORMAT, 0, 0);
                next = ACORN_NPC_LINE_BROUGHT;
            } else if (PlayerField2416_Level(field) >= ACORN_NPC_LEVELS) {
                next = ACORN_NPC_LINE_ALL_GIVEN;
            } else {
                int needed = act_points_needed(field);
                if (needed > 0) {
                    SceneBase_PutValue(&talk->base, needed, 1, ACT_VALUE_FORMAT, 0, 0);
                    next = ACORN_NPC_LINE_NEEDED;
                } else {
                    next = ACORN_NPC_LINE_16;
                }
            }
            break;
        case ACORN_NPC_LINE_TAKEN:
        case ACORN_NPC_LINE_TAKEN + 1:
        case ACORN_NPC_LINE_TAKEN + 2:
            SceneBase_PutValue(&talk->base, PlayerField2416_Points(field), 0, ACT_VALUE_FORMAT, 0, 0);
            next = PlayerField2416_Level(field) >= ACORN_NPC_LEVELS ? ACORN_NPC_LINE_16 : ACORN_NPC_LINE_POINTS;
            break;
        case ACORN_NPC_LINE_POINTS:
            if (act_reward_due(field)) {
                act_put_reward(talk, field);
                next = ACORN_NPC_LINE_REWARD;
            } else {
                SceneBase_PutValue(&talk->base, act_points_needed(field), 1, ACT_VALUE_FORMAT, 0, 0);
                next = ACORN_NPC_LINE_NOT_YET;
            }
            break;
        case ACORN_NPC_LINE_REWARD:
        case ACORN_NPC_LINE_NEXT_REWARD: {
            u16 reward = data_ov087_02279324[PlayerField2416_Level(field)].item;
            if (CurrentPockets_Give(&reward, 0) == 0) {
                next = ACORN_NPC_LINE_NO_ROOM;
                break;
            }
            PlayerField2416_RaiseLevel(field);
            u16 shown = data_ov087_02279324[PlayerField2416_Level(field)].item;
            SceneCommand_RequestMotion13(act_scene(talk), &shown, 0, 5, 0);
            if (PlayerField2416_Level(field) < ACORN_NPC_LEVELS && act_reward_due(field)) {
                act_put_reward(talk, field);
                next = ACORN_NPC_LINE_NEXT_REWARD;
            } else {
                next = ACORN_NPC_LINE_GIVEN;
            }
            break;
        }
        case ACORN_NPC_LINE_14: {
            u16 shown = ACT_ITEM_1565;
            SceneCommand_RequestMotion13(act_scene(talk), &shown, 0, 5, 0);
            next = ACORN_NPC_LINE_15;
            break;
        }
        default:
            break;
    }
    if (next != ACORN_NPC_NO_LINE) {
        act_say(talk, (u8) next);
    }
}
CLEAN_AS(func_ov087_02278cb0, AcornNpcTalk_OnLineEnded)

/* func_ov087_02278f04 (the predicate AcornNpcTalk_OnLineEnded selects the pockets with): an
 * item 0x1542-0x1546 in state 0. */
int AcornNpcTalk_IsItemInState0(u16 *item, int state)
{
    if (state != 0) {
        return 0;
    }
    return act_is_taken(*item);
}
CLEAN_AS(func_ov087_02278f04, AcornNpcTalk_IsItemInState0)

/* func_ov087_02278f2c (slot 0x78, the line the talk starts with), of "sp_npc_acorn": the first
 * talk ever (the player record's flag 0x0f clear) line 0, the flag and the daily bit 0x19 then
 * set; else the first talk today (daily bit 0x19, set now) line 2; else line 3 on one talk in
 * two or once the fortune was given today (daily bit 0x1a), else line 0x10 (the fortune
 * offered). The player record's villager part is asked for first, its answer unused. */
void AcornNpcTalk_FirstLine(AcornNpcTalk *talk, AcornNpcLine *out)
{
    (void) talk;
    u8 *record = PlayerRecords_Current();
    (void) PlayerRecord_VillagerPart(record);
    out->text = (u32) (uintptr_t) data_ov087_02279598;
    if (PlayerRecord_TestFlag(record, ACT_FLAG_MET) == 0) {
        out->message = ACORN_NPC_LINE_MEET;
        PlayerRecord_SetFlag(record, ACT_FLAG_MET);
        TalkChecks_TestSetDailyBit(ACT_DAILY_TALKED, 1);
    } else if (TalkChecks_TestSetDailyBit(ACT_DAILY_TALKED, 1) == 0) {
        out->message = ACORN_NPC_LINE_TODAY;
    } else if (MainRandom_Below(2) == 0 || TalkChecks_TestSetDailyBit(ACT_DAILY_FORTUNE, 0) != 0) {
        out->message = ACORN_NPC_LINE_AGAIN;
    } else {
        out->message = ACORN_NPC_LINE_FORTUNE;
    }
}
CLEAN_AS(func_ov087_02278f2c, AcornNpcTalk_FirstLine)

/* func_ov087_02278fa0: the talk scene told through its vtable slot 0x08 and given its owner. */
void AcornNpcTalk_Begin(AcornNpcTalk *talk, AcornNpc *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + 0x08);
    ((void (*)(AcornNpcTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov087_02278fa0, AcornNpcTalk_Begin)

/* func_ov087_02278fbc (slot 0x04): its destructor, then the scene freed. */
void *AcornNpcTalk_Delete(void *talk)
{
    *(const u8 **) talk = data_ov087_0227945c;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov087_02278fbc, AcornNpcTalk_Delete)

/* func_ov087_02278fdc (slot 0x00): the scene class 0x020d9ff8's destructor. */
void *AcornNpcTalk_Destroy(void *talk)
{
    *(const u8 **) talk = data_ov087_0227945c;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov087_02278fdc, AcornNpcTalk_Destroy)

/* func_ov087_02278ff4: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
void *AcornNpcTalk_Construct(void *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) talk = data_ov087_0227945c;
    return talk;
}
CLEAN_AS(func_ov087_02278ff4, AcornNpcTalk_Construct)
