/* The fortune teller's talk scene and its text classes (fortune_teller_talk.h). */
#include "fortune_teller_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/group_params.h"
#include "main/message_receiver.h"
#include "main/music_queue.h"
#include "main/npc_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/session.h"
#include "main/session_villager.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/town_villager.h"
#include "main/villager_memories.h"
#include "main/villager_memory_entry.h"
#include "main/villager_roster.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "main/villager_town.h"
#include "ov004/tarot_object.h"

static_assert(sizeof(FortuneTellerTalkStep) == 12, "a sequence's function");
static_assert(sizeof(FortuneTellerLine) == 8, "a line");
static_assert(sizeof(FortuneWideText) == 0x24 && offsetof(FortuneWideText, chars) == 0x0e, "wide text");
static_assert(sizeof(FortuneText) == 0x28 && offsetof(FortuneText, chars) == 0x12, "8-bit text");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The vtables: the talk scene's and the text classes'. */
extern const u8 data_ov045_02261460[];
extern const TextVtable data_ov045_0226142c;
extern const TextVtable data_ov045_02261414;
/* The address of the message file's name, "sp_npc_panther". */
extern const u32 data_ov045_02261380;
/* The sequences' functions (filled at start-up by __sinit_ov045_022612d8). */
extern FortuneTellerTalkStep data_ov045_022615a4[FORTUNE_TELLER_TALK_SEQUENCES];
/* The game's state block (its villagers at 0x9284) and the session of the multiplayer game. */
extern StateBlock data_021dc7a8;
extern NetSession *data_020ccf94;

/* The daily bits of the current player (TalkChecks_TestSetDailyBit): the friendship reading,
 * the luck reading and the clearing of the luck given today. */
#define FT_DAILY_FRIENDSHIP 4
#define FT_DAILY_LUCK 5
#define FT_DAILY_CLEARING 6

/* The prices of a reading and of the clearing of the luck. */
#define FT_READING_PRICE 100
#define FT_CLEARING_PRICE 10000

/* The screen the player types the villager's name on (SceneCommand_RequestScreen), its mode
 * and the characters taken from it. */
#define FT_NAME_SCREEN 2
#define FT_NAME_SCREEN_MODE 0x13
#define FT_NAME_CHARS 10

/* The music request of the shuffle and of the clearing (Music_AddValue) and its priority,
 * which the tarot's state 2 drops. */
#define FT_MUSIC_PRIORITY 0x10

/* The talking styles that move the tarot cards to their states 1 to 3 (tarot_object.h), and
 * the motion kind during which a style of the current act moves nothing. */
#define FT_STYLE_TAROT_1 0x1e
#define FT_STYLE_TAROT_2 0x1f
#define FT_STYLE_TAROT_3 0x20
#define FT_MOTION_KIND_ACT 8

/* What a friendship reading does to the villager: its fondness for the player changed and its
 * state entry's counter and byte 0x18 set. */
#define FT_FONDNESS_GOOD 10
#define FT_FONDNESS_BAD (-3)
#define FT_COUNTER_GOOD 0xe10
#define FT_COUNTER_BAD 0x4b0
#define FT_STATE_GOOD 1
#define FT_STATE_BAD 4

/* The owner's motion (SceneMotion, main's scene_object.h). */
#define FT_OWNER_MOTION 0x564

/* The vtable slot its talks call first. */
#define FT_TALK_SLOT_08 0x08

static u8 ftt_line_shown(const FortuneTellerTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *ftt_talk_object(FortuneTellerTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* Message `message` of "sp_npc_panther" shown in `object`. */
static void ftt_say(TalkObject *object, u8 message)
{
    TalkObject_SetMessage(object, &message, (const char *) (uintptr_t) data_ov045_02261380);
}

static VillagerTown *ftt_town(void)
{
    return (VillagerTown *) (void *) data_021dc7a8.villagers;
}

/* ---- The text classes */

/* func_ov045_02260474 (the wide text's slot 0x0c): its characters, 0x0e past the text. */
int FortuneWideText_Chars(int text)
{
    return (int) ((u32) text + (u32) offsetof(FortuneWideText, chars));
}
CLEAN_AS(func_ov045_02260474, FortuneWideText_Chars)

/* func_ov045_02260478 (the wide text's slot 0x08): its room, 10 characters. */
int FortuneWideText_Capacity(void)
{
    return FORTUNE_WIDE_TEXT_CAPACITY;
}
CLEAN_AS(func_ov045_02260478, FortuneWideText_Capacity)

/* func_ov045_0226047c (the wide text's slot 0x04): its destructor, then the text freed. */
void *FortuneWideText_Delete(void *text)
{
    *(const TextVtable **) text = &data_ov045_0226142c;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_ov045_0226047c, FortuneWideText_Delete)

/* func_ov045_0226049c (the wide text's slot 0x00): the wide text base's destructor. */
FortuneWideText *FortuneWideText_Destruct(FortuneWideText *text)
{
    text->vtable = &data_ov045_0226142c;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_ov045_0226049c, FortuneWideText_Destruct)

/* func_ov045_022604b4: the constructor: a wide text base given this class's vtable. */
void *FortuneWideText_Construct(void *text)
{
    TextBase_WideConstruct(text);
    *(const TextVtable **) text = &data_ov045_0226142c;
    return text;
}
CLEAN_AS(func_ov045_022604b4, FortuneWideText_Construct)

/* func_ov045_022604cc (the 8-bit text's slot 0x0c): its characters, 0x12 past the text. */
int FortuneText_Chars(int text)
{
    return (int) ((u32) text + (u32) offsetof(FortuneText, chars));
}
CLEAN_AS(func_ov045_022604cc, FortuneText_Chars)

/* func_ov045_022604d0 (the 8-bit text's slot 0x08): its room, 22 bytes. */
int FortuneText_Capacity(void)
{
    return FORTUNE_TEXT_CAPACITY;
}
CLEAN_AS(func_ov045_022604d0, FortuneText_Capacity)

/* func_ov045_022604d4 (the 8-bit text's slot 0x04): its destructor, then the text freed. */
void *FortuneText_Delete(FortuneText *text)
{
    text->vtable = &data_ov045_02261414;
    TextBase_Destruct((TextBase *) (void *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_ov045_022604d4, FortuneText_Delete)

/* func_ov045_022604f4 (the 8-bit text's slot 0x00): the 8-bit text base's destructor. */
void *FortuneText_Destruct(void *text)
{
    *(const TextVtable **) text = &data_ov045_02261414;
    TextBase_Destruct((TextBase *) text);
    return text;
}
CLEAN_AS(func_ov045_022604f4, FortuneText_Destruct)

/* func_ov045_0226050c: the constructor: an 8-bit text base given this class's vtable. */
void *FortuneText_Construct(void *text)
{
    TextBase_Construct(text);
    *(const TextVtable **) text = &data_ov045_02261414;
    return text;
}
CLEAN_AS(func_ov045_0226050c, FortuneText_Construct)

/* ---- The talk scene */

/* func_ov045_02260724 (sequence 1, when the name screen's command ended): when the player
 * confirmed a name (GroupParams_C4CIs1), its address is kept in the owner, copied (10
 * characters) through a wide text into an 8-bit text and put in part 0 of the talk, and the
 * line is 0x0a ("is it this villager?"); else 0x0b. */
void FortuneTellerTalk_TakeName(FortuneTellerTalk *talk)
{
    TalkObject *object = ftt_talk_object(talk);
    u8 message = FORTUNE_TELLER_LINE_NO_NAME;
    if (GroupParams_C4CIs1()) {
        FortuneText bytes;
        FortuneWideText wide;
        talk->owner->villager_name = (u32) (uintptr_t) GroupParams_Text();
        FortuneText_Construct(&bytes);
        FortuneWideText_Construct(&wide);
        TextBase_SetWide(&wide, (const void *) (uintptr_t) talk->owner->villager_name, FT_NAME_CHARS);
        TextBase_WideToBytes((TextBase *) (void *) &bytes, (WideTextBase *) (void *) &wide, 0, 0);
        TalkObject_SetPart(ftt_talk_object(talk), 0, (TextBase *) (void *) &bytes);
        message = FORTUNE_TELLER_LINE_NAME_TAKEN;
        FortuneWideText_Destruct(&wide);
        FortuneText_Destruct(&bytes);
    }
    ftt_say(object, message);
}
CLEAN_AS(func_ov045_02260724, FortuneTellerTalk_TakeName)

/* func_ov045_022607ac: its sequence set. */
void FortuneTellerTalk_SetSequence(FortuneTellerTalk *talk, unsigned long sequence)
{
    talk->sequence = (u32) sequence;
}
CLEAN_AS(func_ov045_022607ac, FortuneTellerTalk_SetSequence)

/* func_ov045_022607b4 (slot 0x84, a command of the scene ended): a sequence not run each step
 * and with a function runs, and the sequence goes back to 0.
 * REQUIRES: the sequence is 0 or 1. */
void FortuneTellerTalk_RunCommandSequence(FortuneTellerTalk *talk)
{
    const FortuneTellerTalkStep *step = &data_ov045_022615a4[talk->sequence];
    if (step->each_step != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
    FortuneTellerTalk_SetSequence(talk, FORTUNE_TELLER_TALK_SEQUENCE_NONE);
}
CLEAN_AS(func_ov045_022607b4, FortuneTellerTalk_RunCommandSequence)

/* func_ov045_02260804 (slot 0x80, before each step of the scene): a sequence run each step
 * runs, when it has a function.
 * REQUIRES: the sequence is 0 or 1. */
void FortuneTellerTalk_RunStepSequence(FortuneTellerTalk *talk)
{
    const FortuneTellerTalkStep *step = &data_ov045_022615a4[talk->sequence];
    if (step->each_step != 0 && step->run.function != 0) {
        MemberPointer_CallVoid(&step->run, talk);
    }
}
CLEAN_AS(func_ov045_02260804, FortuneTellerTalk_RunStepSequence)

/* func_ov045_02260848 (slot 0x18, the player's answer), by the line shown and the answer
 * picked:
 * - 0x01, 0x03, 0x05: the first answer, 0x07 when the player can pay 100 bells, else 0x06;
 *   the second at 0x05, 0x14 (the clearing);
 * - 0x07, 0x08: the first, the luck: 0x08 when read today, else 0x0d and it is (reading of the
 *   luck); the second, the friendship: 0x08 when read today, else 0x09 (the name asked);
 * - 0x0a: the first, 0x0c and the friendship is read today (reading of the friendship); else
 *   0x0b (the name asked again);
 * - 0x14: the first, 0x17 when the player can pay 10,000 bells, else 0x15.
 * The line, when one was picked, is shown. */
void FortuneTellerTalk_OnAnswer(FortuneTellerTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    int next = FORTUNE_TELLER_NO_MESSAGE;
    int owner = (int) (u32) (uintptr_t) talk->owner;

    switch (ftt_line_shown(talk)) {
        case FORTUNE_TELLER_LINE_OFFER:
        case FORTUNE_TELLER_LINE_OFFER_3:
        case FORTUNE_TELLER_LINE_OFFER_FRIENDSHIP:
            if (answer == 0) {
                next =
                    SceneBells_CanPay(owner, FT_READING_PRICE) == 0 ? FORTUNE_TELLER_LINE_NO_BELLS : FORTUNE_TELLER_LINE_WHICH;
            } else if (ftt_line_shown(talk) == FORTUNE_TELLER_LINE_OFFER_FRIENDSHIP && answer == 1) {
                next = FORTUNE_TELLER_LINE_OFFER_CLEARING;
            }
            break;
        case FORTUNE_TELLER_LINE_WHICH:
        case FORTUNE_TELLER_LINE_WHICH_AGAIN:
            if (answer == 0) {
                if (TalkChecks_TestSetDailyBit(FT_DAILY_LUCK, 0) != 0) {
                    next = FORTUNE_TELLER_LINE_WHICH_AGAIN;
                } else {
                    next = FORTUNE_TELLER_LINE_LUCK;
                    talk->owner->reading = FORTUNE_TELLER_READING_LUCK;
                    TalkChecks_TestSetDailyBit(FT_DAILY_LUCK, 1);
                }
            } else if (answer == 1) {
                next = TalkChecks_TestSetDailyBit(FT_DAILY_FRIENDSHIP, 0) != 0 ? FORTUNE_TELLER_LINE_WHICH_AGAIN
                                                                               : FORTUNE_TELLER_LINE_ASK_NAME;
            }
            break;
        case FORTUNE_TELLER_LINE_NAME_TAKEN:
            if (answer == 0) {
                next = FORTUNE_TELLER_LINE_FRIENDSHIP;
                talk->owner->reading = FORTUNE_TELLER_READING_FRIENDSHIP;
                TalkChecks_TestSetDailyBit(FT_DAILY_FRIENDSHIP, 1);
            } else {
                next = FORTUNE_TELLER_LINE_NO_NAME;
            }
            break;
        case FORTUNE_TELLER_LINE_OFFER_CLEARING:
            if (answer == 0) {
                next = SceneBells_CanPay(owner, FT_CLEARING_PRICE) == 0 ? FORTUNE_TELLER_LINE_NO_BELLS_CLEARING
                                                                        : FORTUNE_TELLER_LINE_CLEARING;
            }
            break;
        default:
            break;
    }

    if (next != FORTUNE_TELLER_NO_MESSAGE) {
        ftt_say(ftt_talk_object(talk), (u8) next);
    }
}
CLEAN_AS(func_ov045_02260848, FortuneTellerTalk_OnAnswer)

/* func_ov045_02260958 (slot 0x10, a line begins): at the lines 0x0e and 0x17 the music queue
 * gets value 0 at priority 0x10. */
void FortuneTellerTalk_OnLineBegins(unsigned char *talk)
{
    u8 line = ((const MessageReceiver *) (const void *) talk)->message;
    if (line == FORTUNE_TELLER_LINE_DRAW || line == FORTUNE_TELLER_LINE_CLEARING) {
        Music_AddValue(FT_MUSIC_PRIORITY, 0, 0);
    }
}
CLEAN_AS(func_ov045_02260958, FortuneTellerTalk_OnLineBegins)

/* A friendship reading's effect on its villager's state entry: unless the session's slot of
 * this system is taken, its counter grows by `counter` when byte 0x18 is `state` already, else
 * is set to it, and byte 0x18 becomes `state`. */
static void ftt_mark_villager(VillagerState *entry, int counter, int state)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0 || entry == NULL) {
        return;
    }
    if (VillagerState_GetByte18(entry) == state) {
        VillagerState_AddCounter(entry, counter);
    } else {
        VillagerState_SetCounter(entry, counter);
    }
    VillagerState_SetByte18(entry, state);
}

/* The friendship reading of `luck` taken on the villager named: found by name in the town (by
 * the current player), its memory of `player` changed by +10 (good) or -3 (bad) and sent to
 * the session, and its state entry marked (ftt_mark_villager). Nothing when the villager or
 * its memory of the player is not found. */
static void ftt_read_friendship(FortuneTeller *teller, u8 *record, int luck, DesignCreator *player)
{
    u8 *villager = VillagerRoster_FindByName(ftt_town(), (const u16 *) (uintptr_t) teller->villager_name, FT_NAME_CHARS,
                                             PlayerRecord_Player(record));
    if (villager == NULL) {
        return;
    }
    int index = VillagerMemory_IndexOf(villager, player);
    VillagerMemory *memory = VillagerMemory_At(villager, index);
    VillagerState *entry = NULL;
    if (NpcId_IsValid(TownVillager_NpcId(villager))) {
        entry = VillagerStatus_StateEntry(villager);
    }
    if (memory == NULL) {
        return;
    }
    switch (luck) {
        case FORTUNE_TELLER_LUCK_GOOD:
            ftt_mark_villager(entry, FT_COUNTER_GOOD, FT_STATE_GOOD);
            VillagerMemoryEntry_ChangeFondness(memory, FT_FONDNESS_GOOD);
            SessionVillager_SendEntryByte6C(villager, index, VillagerMemoryEntry_Fondness(memory));
            break;
        case FORTUNE_TELLER_LUCK_BAD:
            ftt_mark_villager(entry, FT_COUNTER_BAD, FT_STATE_BAD);
            VillagerMemoryEntry_ChangeFondness(memory, FT_FONDNESS_BAD);
            SessionVillager_SendEntryByte6C(villager, index, VillagerMemoryEntry_Fondness(memory));
            break;
        default:
            break;
    }
}

/* func_ov045_02260978 (slot 0x14, a line ended), by the line shown:
 * - 0x09, 0x0b: the name screen asked for (mode 0x13, screen 2), sequence 1 to take the name;
 * - 0x0e: a card drawn (FortuneTeller_DrawCard), its line next;
 * - 0x10: 100 bells taken when the player can pay them; 0x16 next;
 * - 0x13: the owner closes (state 3);
 * - 0x18: 10,000 bells taken when the player can pay them, the current player's luck of the
 *   day cleared (0) and the clearing noted today; 0x16 next.
 * Then, with a card drawn: at the line of its meaning the reading takes effect and 0x10 is
 * next, the card's lines forgotten: the luck reading sets the current player's luck of the day
 * to the card's (good luck: VillagerTown_UpdateAlone with the player; bad luck:
 * VillagerTown_HalveByte1E), the friendship reading acts on the villager named
 * (ftt_read_friendship). At the line of the card, the line of its meaning is next. The line,
 * when one was picked, is shown. */
void FortuneTellerTalk_OnLineEnded(FortuneTellerTalk *talk)
{
    u8 *record = PlayerRecords_Current();
    int next = FORTUNE_TELLER_NO_MESSAGE;
    FortuneTeller *owner = talk->owner;

    switch (ftt_line_shown(talk)) {
        case FORTUNE_TELLER_LINE_ASK_NAME:
        case FORTUNE_TELLER_LINE_NO_NAME:
            SceneCommand_SetScreenMode((SceneCommandScene *) (void *) talk, FT_NAME_SCREEN_MODE, 0);
            SceneCommand_RequestScreen((SceneCommandScene *) (void *) talk, FT_NAME_SCREEN);
            FortuneTellerTalk_SetSequence(talk, FORTUNE_TELLER_TALK_SEQUENCE_TAKE_NAME);
            break;
        case FORTUNE_TELLER_LINE_DRAW:
            FortuneTeller_DrawCard(talk->owner);
            next = talk->owner->card_message;
            break;
        case FORTUNE_TELLER_LINE_PAY:
            if (SceneBells_CanPay((int) (u32) (uintptr_t) talk->owner, FT_READING_PRICE) != 0) {
                SceneBells_Take((int) (u32) (uintptr_t) talk->owner, FT_READING_PRICE);
            }
            next = FORTUNE_TELLER_LINE_PAID;
            break;
        case FORTUNE_TELLER_LINE_CLOSED:
            FortuneTeller_SetState(talk->owner, FORTUNE_TELLER_CLOSING);
            break;
        case FORTUNE_TELLER_LINE_CLEARED:
            if (SceneBells_CanPay((int) (u32) (uintptr_t) talk->owner, FT_CLEARING_PRICE) != 0) {
                SceneBells_Take((int) (u32) (uintptr_t) talk->owner, FT_CLEARING_PRICE);
            }
            PlayerRecord_SetDayState(record, FORTUNE_TELLER_LUCK_NONE);
            TalkChecks_TestSetDailyBit(FT_DAILY_CLEARING, 1);
            next = FORTUNE_TELLER_LINE_PAID;
            break;
        default:
            break;
    }

    owner = talk->owner;
    if (owner->result_message != FORTUNE_TELLER_NO_MESSAGE) {
        if (owner->result_message == ftt_line_shown(talk)) {
            next = FORTUNE_TELLER_LINE_PAY;
            int luck = FortuneTeller_CardLuck(talk->owner);
            DesignCreator *player = PlayerRecord_Player(PlayerRecords_Current());
            switch (talk->owner->reading) {
                case FORTUNE_TELLER_READING_LUCK:
                    PlayerRecord_SetDayState(record, luck);
                    if (luck == FORTUNE_TELLER_LUCK_GOOD) {
                        VillagerTown_UpdateAlone(ftt_town(), player);
                    } else if (luck == FORTUNE_TELLER_LUCK_BAD) {
                        VillagerTown_HalveByte1E(ftt_town());
                    }
                    break;
                case FORTUNE_TELLER_READING_FRIENDSHIP:
                    ftt_read_friendship(talk->owner, record, luck, player);
                    break;
                default:
                    break;
            }
            talk->owner->result_message = FORTUNE_TELLER_NO_MESSAGE;
            talk->owner->card_message = FORTUNE_TELLER_NO_MESSAGE;
        }
        if (talk->owner->card_message == ftt_line_shown(talk)) {
            next = talk->owner->result_message;
        }
    }

    if (next != FORTUNE_TELLER_NO_MESSAGE) {
        ftt_say(ftt_talk_object(talk), (u8) next);
    }
}
CLEAN_AS(func_ov045_02260978, FortuneTellerTalk_OnLineEnded)

/* func_ov045_02260c28 (slot 0x78, the line the talk starts with), of "sp_npc_panther": while
 * the luck or the friendship reading has not been given today, 0x01 (the luck not yet) or
 * 0x05 (the friendship not yet); with both, 0x11 until the luck was cleared today, then 0x19.
 * Before 6 a.m., 0x13 (closed) in any case. */
void FortuneTellerTalk_Line(FortuneTellerTalk *talk, FortuneTellerLine *out)
{
    (void) talk;
    out->text = data_ov045_02261380;
    int friendship = TalkChecks_TestSetDailyBit(FT_DAILY_FRIENDSHIP, 0);
    int luck = TalkChecks_TestSetDailyBit(FT_DAILY_LUCK, 0);
    int cleared = TalkChecks_TestSetDailyBit(FT_DAILY_CLEARING, 0);
    if (luck == 0 || friendship == 0) {
        out->message = luck == 0 ? FORTUNE_TELLER_LINE_OFFER : FORTUNE_TELLER_LINE_OFFER_FRIENDSHIP;
    } else {
        out->message = cleared == 0 ? FORTUNE_TELLER_LINE_BOTH_READ : FORTUNE_TELLER_LINE_ALL_DONE;
    }
    if (FortuneTeller_BeforeSix()) {
        out->message = FORTUNE_TELLER_LINE_CLOSED;
    }
}
CLEAN_AS(func_ov045_02260c28, FortuneTellerTalk_Line)

/* func_ov045_02260c94: its talk scene told through its vtable slot 0x08 and given its owner. */
void FortuneTellerTalk_Begin(FortuneTellerTalk *talk, void *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + FT_TALK_SLOT_08);
    ((void (*)(FortuneTellerTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov045_02260c94, FortuneTellerTalk_Begin)

/* func_ov045_02260cb0 (slot 0x38, the focus speaker's talking motion of `style`): unless the
 * owner's motion is in the act of that number (motion kind 8), styles 0x1e to 0x20 put the
 * tarot cards in their states 1 to 3 (with 0x1f the music request of priority 0x10 dropped
 * first); then the scene base's own. */
void FortuneTellerTalk_SetTalkStyle(FortuneTellerTalk *talk, int style)
{
    SceneMotion *motion = (SceneMotion *) (void *) (talk->owner->base + FT_OWNER_MOTION);
    int in_act = style == SceneMotion_ActNumber(motion) && SceneMotion_Kind(motion) == FT_MOTION_KIND_ACT;
    if (!in_act) {
        switch (style) {
            case FT_STYLE_TAROT_1:
                TarotObject_EnterState1Current();
                break;
            case FT_STYLE_TAROT_2:
                Music_DropPriority(FT_MUSIC_PRIORITY);
                TarotObject_EnterState2Current();
                break;
            case FT_STYLE_TAROT_3:
                TarotObject_EnterState3Current();
                break;
            default:
                break;
        }
    }
    SceneBase_FocusTalkStyle(&talk->base, style);
}
CLEAN_AS(func_ov045_02260cb0, FortuneTellerTalk_SetTalkStyle)

/* func_ov045_02260d14 (slot 0x04): its destructor, then the scene freed. */
void *FortuneTellerTalk_Delete(void *talk)
{
    *(const u8 **) talk = data_ov045_02261460;
    SceneBase_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov045_02260d14, FortuneTellerTalk_Delete)

/* func_ov045_02260d34 (slot 0x00): the scene base's destructor. */
void *FortuneTellerTalk_Destroy(void *talk)
{
    *(const u8 **) talk = data_ov045_02261460;
    SceneBase_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov045_02260d34, FortuneTellerTalk_Destroy)

/* func_ov045_02260d4c: the constructor: a scene base given this class's vtable. */
FortuneTellerTalk *FortuneTellerTalk_Construct(FortuneTellerTalk *talk)
{
    SceneBase_Construct(&talk->base);
    talk->base.vtable = data_ov045_02261460;
    return talk;
}
CLEAN_AS(func_ov045_02260d4c, FortuneTellerTalk_Construct)
