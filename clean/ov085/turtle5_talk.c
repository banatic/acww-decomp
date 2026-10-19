/* The talk scene of overlay 85's turtle: his lines, the villager the player names and the
 * winner he names (turtle5_talk.h). */
#include "turtle5_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/bbs.h"
#include "main/current_pockets.h"
#include "main/event_winner.h"
#include "main/item_traits.h"
#include "main/mail_text.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/npc_id.h"
#include "main/obj_020d9ff8.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/town_villager.h"
#include "main/villager_roster.h"
#include "main/villager_town.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(Turtle5Talk, owner) == 0xb0, "owner");
static_assert(offsetof(Turtle5Talk, item_slot) == 0xb4, "item slot");
static_assert(offsetof(Turtle5Talk, next_villager) == 0xb8, "next villager");
static_assert(offsetof(Turtle5Talk, choices) == 0xbc, "choices");
static_assert(sizeof(Turtle5Line) == 8, "a line");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The talk scene's vtable. */
extern const u8 data_ov085_0227945c[];
/* The message files: "sp_npc_turtle5" (his) and "sp_npc_turtle" (the turtle's common one), and
 * the town board's archive "bbs_snowfes". */
extern const char data_ov085_0227959c[];
extern const char data_ov085_022795ac[];
extern const char data_ov085_022795bc[];
/* The record of who won one of the town's events, the town's villagers and the state block. */
extern EventWinner data_021f3aa4;
extern VillagerTown data_021e5a2c;
extern StateBlock data_021dc7a8;

/* The items exchanged while the pockets hold the item 0x37e0. */
#define T5T_ASKED_ITEM 0x37e0
#define T5T_EXCHANGE_ITEM 0x1559

/* The values the item motions (SceneCommand_RequestMotion13 and 14) are asked with. */
#define T5T_MOTION_B 5

/* The current player's daily bit of a talk with him. */
#define T5T_DAILY_TALKED 0x1f

/* The flag of the state block set once the winner was named. */
#define T5T_FLAG_RESULT 0x11

/* The last day of event 0x11 (Turtle5.festival_day). */
#define T5T_LAST_DAY 6

/* The talk's parts the names go in. */
#define T5T_PART_NAMED 0
#define T5T_PART_WINNER 1

/* The villagers listed at a time, the town's places, and the message of the answer that goes
 * on to the next ones (of the file TalkAnswers_SelectFileName(0)). */
#define T5T_LISTED 4
#define T5T_PLACES 8
#define T5T_MORE_MESSAGE 0x3d

/* The town's villagers, as the state block's address plus their place in it. */
#define T5T_TOWN_IN_STATE_BLOCK 0x9284

/* The talk scene's vtable slots: the one its talks call first (SceneBase_Reset) and the list of
 * villagers (Turtle5Talk_OfferVillagers). */
#define T5T_TALK_SLOT_08 0x08
#define T5T_TALK_SLOT_88 0x88

static u8 t5t_line_shown(const Turtle5Talk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *t5t_talk_object(Turtle5Talk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *t5t_scene(Turtle5Talk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* Message `message` of the file `name` shown in `object`. */
static void t5t_say(TalkObject *object, u8 message, const char *name)
{
    TalkObject_SetMessage(object, &message, name);
}

/* The talk scene's function at vtable slot `slot` called. */
static void t5t_call_slot(Turtle5Talk *talk, u32 slot)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + slot);
    ((void (*)(Turtle5Talk *))(uintptr_t) code)(talk);
}

static TextBase *t5t_text(PlayerIdText *name)
{
    return (TextBase *) (void *) name;
}

static char *t5t_chars(PlayerIdText *name)
{
    return (char *) (void *) name;
}

/* The common file's exchange of the item 0x37e0, in the player's answer: line 0 answered 0
 * takes it (its slot emptied, the scene's motion 14 with it): line 2. */
static void t5t_exchange_answer(Turtle5Talk *talk, unsigned int answer)
{
    if (t5t_line_shown(talk) == TURTLE5_COMMON_LINE_ASK && answer == 0) {
        CurrentPockets_Empty(talk->item_slot);
        u16 item = T5T_ASKED_ITEM;
        SceneCommand_RequestMotion14(t5t_scene(talk), &item, 0, T5T_MOTION_B, 0);
        t5t_say(t5t_talk_object(talk), TURTLE5_COMMON_LINE_TAKEN, data_ov085_022795ac);
    }
}

/* func_ov085_02278ab8 (slot 0x18, the player's answer):
 * - while the pockets hold the item 0x37e0: the exchange (t5t_exchange_answer);
 * - line 4: answered 0, line 7 or 8; else 5 or 6 (at random);
 * - lines 7, 8, 0x14 and 0x15 (the list of villagers): a villager answered is named: its name
 *   in the talk's part 0, at random half the time made the record's villager, and the record's
 *   NpcId at 0x2e in any case; line 9 or 10. The answer that goes on: line 0x14, or 0x15 after
 *   0x14.
 * The line, when one was picked, is shown.
 * REQUIRES: an answer of the list is 0 to 4. */
void Turtle5Talk_OnAnswer(Turtle5Talk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    int next = TURTLE5_NO_LINE;

    if (talk->item_slot >= 0) {
        t5t_exchange_answer(talk, answer);
        return;
    }

    u8 line = t5t_line_shown(talk);
    switch (line) {
        case TURTLE5_LINE_ASK:
            if (answer == 0) {
                next = (u8) (MainRandom_Below(2) + TURTLE5_LINE_NAME);
            } else {
                next = (u8) (MainRandom_Below(2) + TURTLE5_LINE_DECLINED);
            }
            break;
        case TURTLE5_LINE_NAME:
        case TURTLE5_LINE_NAME + 1:
        case TURTLE5_LINE_MORE:
        case TURTLE5_LINE_MORE_AGAIN:
            if (talk->choices[answer] >= 0) {
                PlayerIdText name;
                PlayerIdText_Construct(&name);
                u8 *villager = VillagerRoster_At(&data_021e5a2c, talk->choices[answer]);
                if (NpcId_IsValid(TownVillager_NpcId(villager))) {
                    NpcId_FormatName(TownVillager_NpcId(villager), t5t_chars(&name));
                    TalkObject_SetPart(t5t_talk_object(talk), T5T_PART_NAMED, t5t_text(&name));
                }
                if (MainRandom_Below(2) == 0) {
                    EventWinner_SetVillager(&data_021f3aa4, TownVillager_NpcId(villager));
                }
                EventWinner_SetNpc2E(&data_021f3aa4, TownVillager_NpcId(villager));
                next = (u8) (MainRandom_Below(2) + TURTLE5_LINE_NAMED);
                PlayerIdText_Destruct(&name);
            } else {
                next = line != TURTLE5_LINE_MORE ? TURTLE5_LINE_MORE : TURTLE5_LINE_MORE_AGAIN;
            }
            break;
        default:
            break;
    }
    if (next != TURTLE5_NO_LINE) {
        t5t_say(t5t_talk_object(talk), (u8) next, data_ov085_0227959c);
    }
}
CLEAN_AS(func_ov085_02278ab8, Turtle5Talk_OnAnswer)

/* The common file's exchange of the item 0x37e0, when a line ended: lines 1 and 4 end it;
 * line 2 shows (motion 13) and gives the item 0x1559, then line 4. */
static void t5t_exchange_line_ended(Turtle5Talk *talk)
{
    u8 line = t5t_line_shown(talk);
    if (line == TURTLE5_COMMON_LINE_DONE || line == TURTLE5_COMMON_LINE_GIVEN) {
        talk->item_slot = TURTLE5_TALK_SLOT_DONE;
    }
    if (t5t_line_shown(talk) != TURTLE5_COMMON_LINE_TAKEN) {
        return;
    }
    u16 shown = T5T_EXCHANGE_ITEM;
    SceneCommand_RequestMotion13(t5t_scene(talk), &shown, 0, T5T_MOTION_B, 0);
    u16 given = T5T_EXCHANGE_ITEM;
    CurrentPockets_Give(&given, 0);
    t5t_say(t5t_talk_object(talk), TURTLE5_COMMON_LINE_GIVEN, data_ov085_022795ac);
}

/* The winner named (line 0x0f ended): the record's villager, or when it has none the current
 * player's fondest villager (or any, VillagerRoster_FondestOrAny) made it when that place is
 * filled; its name in mail part 0 and the talk's part 1, one of two notices of "bbs_snowfes"
 * posted on the town's board and the villagers' memory flags cleared. */
static void t5t_name_winner(Turtle5Talk *talk)
{
    NpcId *winner = EventWinner_Villager(&data_021f3aa4);
    PlayerIdText name;
    PlayerIdText_Construct(&name);
    if (!NpcId_IsValid(winner)) {
        int block = ItemTraits_StateBlockAddress();
        VillagerTown *town = (VillagerTown *) (uintptr_t) (u32) (block + T5T_TOWN_IN_STATE_BLOCK);
        u8 *fondest = VillagerRoster_FondestOrAny(town, PlayerRecord_Player(PlayerRecords_Current()));
        if (NpcId_IsValid(TownVillager_NpcId(fondest))) {
            EventWinner_SetVillager(&data_021f3aa4, TownVillager_NpcId(fondest));
            winner = EventWinner_Villager(&data_021f3aa4);
        }
    }
    NpcId_FormatName(winner, t5t_chars(&name));
    MailText_SetPartText(0, &name);
    TalkObject_SetPart(t5t_talk_object(talk), T5T_PART_WINNER, t5t_text(&name));
    Bbs_PostMessage((int) MainRandom_Below(2), data_ov085_022795bc);
    VillagerTown_ClearMemoryFlags(&data_021e5a2c);
    PlayerIdText_Destruct(&name);
}

/* func_ov085_02278c14 (slot 0x14, a line ended):
 * - while the pockets held the item 0x37e0: the exchange (t5t_exchange_line_ended);
 * - line 0x0f: the winner named (t5t_name_winner), line 0x10;
 * - lines 7, 8, 0x14 and 0x15: the list of villagers offered (vtable slot 0x88).
 * The line, when one was picked, is shown. */
void Turtle5Talk_OnLineEnded(Turtle5Talk *talk)
{
    int next = TURTLE5_NO_LINE;

    if (talk->item_slot >= 0) {
        t5t_exchange_line_ended(talk);
        return;
    }
    if (t5t_line_shown(talk) == TURTLE5_LINE_RESULT) {
        t5t_name_winner(talk);
        next = TURTLE5_LINE_WINNER;
    }
    switch (t5t_line_shown(talk)) {
        case TURTLE5_LINE_NAME:
        case TURTLE5_LINE_NAME + 1:
        case TURTLE5_LINE_MORE:
        case TURTLE5_LINE_MORE_AGAIN:
            t5t_call_slot(talk, T5T_TALK_SLOT_88);
            break;
        default:
            break;
    }
    if (next != TURTLE5_NO_LINE) {
        t5t_say(t5t_talk_object(talk), (u8) next, data_ov085_0227959c);
    }
}
CLEAN_AS(func_ov085_02278c14, Turtle5Talk_OnLineEnded)

/* The name of `npc` put in the talk's part `part`, when it is valid. */
static void t5t_put_name(Turtle5Talk *talk, NpcId *npc, int part)
{
    PlayerIdText name;
    PlayerIdText_Construct(&name);
    NpcId_FormatName(npc, t5t_chars(&name));
    TalkObject_SetPart(t5t_talk_object(talk), part, t5t_text(&name));
    PlayerIdText_Destruct(&name);
}

/* func_ov085_02278d68 (slot 0x78, the line the talk starts with), of "sp_npc_turtle5" unless
 * said otherwise. The current player's villager part is looked up first (and not used).
 * - The pockets are looked through for the item 0x37e0 once a talk (Turtle5Talk.item_slot);
 *   when they hold it, line 0 of "sp_npc_turtle".
 * - The last day (6): the first time line 0x0f (flag 0x11 of the state block set now); later
 *   one of lines 0x11-0x13, the record's villager in part 1 when there is one.
 * - Days 0-5: with a villager named today (the record's NpcId at 0x2e) one of lines
 *   0x0b-0x0e, its name in part 0; else line 4, or before the player's first talk of the day
 *   (daily bit 0x1f, set now) line 0 on day 0, 1 on days 1-2, 2 on days 3-4 and 3 on day 5. */
void Turtle5Talk_FirstLine(Turtle5Talk *talk, Turtle5Line *out)
{
    (void) PlayerRecord_VillagerPart(PlayerRecords_Current());
    out->text = (u32) (uintptr_t) data_ov085_0227959c;

    if (talk->item_slot == TURTLE5_TALK_SLOT_UNKNOWN) {
        u16 asked = T5T_ASKED_ITEM;
        talk->item_slot = CurrentPockets_FindItem(&asked);
        if (talk->item_slot >= 0) {
            out->text = (u32) (uintptr_t) data_ov085_022795ac;
            out->message = TURTLE5_COMMON_LINE_ASK;
            return;
        }
    }

    if (talk->owner->festival_day == T5T_LAST_DAY) {
        if (StateBlock_TestFlag((u32 *) (void *) &data_021dc7a8, T5T_FLAG_RESULT) != 0) {
            NpcId *winner = EventWinner_Villager(&data_021f3aa4);
            if (NpcId_IsValid(winner)) {
                t5t_put_name(talk, winner, T5T_PART_WINNER);
            }
            out->message = (u8) (MainRandom_Below(3) + TURTLE5_LINE_AFTER_RESULT);
        } else {
            out->message = TURTLE5_LINE_RESULT;
            StateBlock_SetFlag((u32 *) (void *) &data_021dc7a8, T5T_FLAG_RESULT);
        }
        return;
    }

    NpcId *named = EventWinner_Npc2E(&data_021f3aa4);
    if (NpcId_IsValid(named)) {
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        NpcId_FormatName(named, t5t_chars(&name));
        TalkObject_SetPart(t5t_talk_object(talk), T5T_PART_NAMED, t5t_text(&name));
        out->message = (u8) (MainRandom_Below(4) + TURTLE5_LINE_NAMED_TODAY);
        PlayerIdText_Destruct(&name);
        return;
    }
    out->message = TURTLE5_LINE_ASK;
    if (TalkChecks_TestSetDailyBit(T5T_DAILY_TALKED, 1) != 0) {
        return;
    }
    switch (talk->owner->festival_day) {
        case 0:
            out->message = TURTLE5_LINE_DAY_0;
            break;
        case 1:
        case 2:
            out->message = TURTLE5_LINE_DAY_1;
            break;
        case 3:
        case 4:
            out->message = TURTLE5_LINE_DAY_3;
            break;
        case 5:
            out->message = TURTLE5_LINE_DAY_5;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov085_02278d68, Turtle5Talk_FirstLine)

/* func_ov085_02278eb8: his talk scene told through its vtable slot 0x08 and given its owner,
 * the pockets not looked through yet. */
void Turtle5Talk_Begin(Turtle5Talk *talk, Turtle5 *owner)
{
    t5t_call_slot(talk, T5T_TALK_SLOT_08);
    talk->owner = owner;
    talk->item_slot = TURTLE5_TALK_SLOT_UNKNOWN;
}
CLEAN_AS(func_ov085_02278eb8, Turtle5Talk_Begin)

/* func_ov085_02278edc (slot 0x04): its destructor (the scene class 0x020d9ff8's), then the
 * scene freed. */
void *Turtle5Talk_Delete(void *talk)
{
    Turtle5Talk *self = talk;
    self->base.vtable = data_ov085_0227945c;
    Obj020d9ff8_DestructBody(self);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_ov085_02278edc, Turtle5Talk_Delete)

/* func_ov085_02278efc (slot 0x00): the scene class 0x020d9ff8's destructor. */
void *Turtle5Talk_Destroy(void *talk)
{
    Turtle5Talk *self = talk;
    self->base.vtable = data_ov085_0227945c;
    Obj020d9ff8_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov085_02278efc, Turtle5Talk_Destroy)

/* func_ov085_02278f14: the constructor: a scene of class 0x020d9ff8 given this class's
 * vtable. */
Turtle5Talk *Turtle5Talk_Construct(Turtle5Talk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov085_0227945c;
    return talk;
}
CLEAN_AS(func_ov085_02278f14, Turtle5Talk_Construct)

/* Whether the town's place `place` holds a villager. */
static int t5t_place_filled(int place)
{
    return NpcId_IsValid(TownVillager_NpcId(VillagerRoster_At(&data_021e5a2c, place)));
}

/* func_ov085_02278f2c (slot 0x88): the list of villagers offered as the talk's answers: from
 * the place Turtle5Talk.next_villager (place 0 when it holds none) the next four places that
 * hold one, each answer's text the villager's name and its place noted (the others -1); the
 * list then goes on from the place after the last one looked at (0 past the eighth). When the
 * town has more than four villagers a last answer goes on to the next ones (message 0x3d of
 * the file TalkAnswers_SelectFileName(0)), and B picks it. */
void Turtle5Talk_OfferVillagers(Turtle5Talk *talk)
{
    TalkAnswers *answers = TalkObject_Answers(t5t_talk_object(talk));
    u8 more = T5T_MORE_MESSAGE;
    PlayerIdText name;

    PlayerIdText_Construct(&name);
    TalkAnswers_Clear(answers);
    for (int i = 0; i < TURTLE5_CHOICES; i++) {
        talk->choices[i] = -1;
    }
    if (!t5t_place_filled(talk->next_villager)) {
        talk->next_villager = 0;
    }

    int place = talk->next_villager;
    int count = 0;
    for (; place < T5T_PLACES && count < T5T_LISTED; place++) {
        u8 *villager = VillagerRoster_At(&data_021e5a2c, place);
        if (NpcId_IsValid(TownVillager_NpcId(villager))) {
            NpcId_FormatName(TownVillager_NpcId(villager), t5t_chars(&name));
            TextBase_Copy(TalkAnswers_Text(TalkAnswers_Answer(answers, count)), t5t_text(&name));
            talk->choices[count] = place;
            count++;
        }
    }
    talk->next_villager = (u8) place;
    if (talk->next_villager >= T5T_PLACES) {
        talk->next_villager = 0;
    }

    if (VillagerRoster_Count(&data_021e5a2c) > T5T_LISTED) {
        TalkAnswer *answer = TalkAnswers_Answer(answers, count);
        TalkAnswers_SetMessage(answer, &more);
        TalkAnswers_SetFile(answer, (int) TalkAnswers_SelectFileName(0));
        TalkAnswers_LoadAnswerText(answer);
        count++;
    }
    TalkAnswers_SetCount(answers, count);
    if (VillagerRoster_Count(&data_021e5a2c) > T5T_LISTED) {
        TalkAnswers_SetCancelToLast(answers);
    }
    TalkObject_OpenChoices(t5t_talk_object(talk), 1);
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov085_02278f2c, Turtle5Talk_OfferVillagers)
