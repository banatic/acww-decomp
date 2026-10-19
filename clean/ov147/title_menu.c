/* The title's menu: the talk receiver of the title scene (title_scene.h, TitleReceiver, vtable
 * data_ov147_0229aae4) and what it does with talk 0's messages of "sp_etc_sequence1" (or
 * "sp_etc_sequence2"). Its slots override main's (main/talk_receiver.h): 0x14, what follows a
 * message (TitleMenu_AfterMessage); 0x18, the player's answer (TitleMenu_OnAnswer); 0x70, the
 * talk closes (TitleMenu_OnClose).
 *
 * The receiver's message number says where the menu is. The first menu (messages 0x2d-0x2f by
 * the part of the day, and 0x31) offers what the town allows, one of four sets of answers by
 * how many players the town has (main's player records) and whether a town is set up (the
 * state block); each answer runs a member function of the matching table (TitleMenu_OnAnswer)
 * or none. Messages 0, 0x30 and 0x35 ask yes or no, and yes leaves the title by a state of the
 * scene; message 3 lists the town's players to pick one to remove. */
#include "title_scene.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/activity_vars.h"
#include "main/calendar.h"
#include "main/exchange_block.h"
#include "main/letter.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sound.h"
#include "main/start_kind.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/text_base.h"

static_assert(sizeof(TitleReceiver) == 0x4c, "TitleReceiver");
static_assert(sizeof(TitleChoices) == 0x0c, "TitleChoices");

/* The talk the title uses. */
#define TITLE_TALK 0

/* The receiver's messages acted on (in "sp_etc_sequence1" unless said). */
enum TitleMenuMessage {
    TITLE_MESSAGE_ASK_REQUEST = 0x00, /* yes: TITLE_STATE_EXIT_REQUEST */
    TITLE_MESSAGE_SUB_MENU = 0x01,    /* answers by the town's state */
    TITLE_MESSAGE_PICK_PLAYER = 0x03, /* the town's players listed */
    TITLE_MESSAGE_REMOVE = 0x04,      /* a player picked to remove, its name as part 0 */
    TITLE_MESSAGE_THEN_31A = 0x05,    /* message 0x31 follows */
    TITLE_MESSAGE_REMOVED = 0x06,     /* the talk ends: TITLE_STATE_EXIT_JOB_6 */
    TITLE_MESSAGE_THEN_31B = 0x0a,    /* message 0x31 follows */
    TITLE_MESSAGE_JOB_5 = 0x0b,       /* the talk ends: TITLE_STATE_EXIT_JOB_5 */
    TITLE_MESSAGE_ANSWER_YES = 0x12,  /* the answers' messages with sound kind 1 (and 0, 1) */
    TITLE_MESSAGE_PLAYER_0 = 0x24,    /* with flag 0x12 of the state block: START_KIND_PLAYER_0 */
    TITLE_MESSAGE_NEW_PLAYER = 0x27,  /* START_KIND_NEW_PLAYER */
    TITLE_MESSAGE_MENU_FIRST = 0x2d,  /* the first menu, by the part of the day: 0x2d-0x2f */
    TITLE_MESSAGE_MENU_LAST = 0x2f,
    TITLE_MESSAGE_ASK_JOB_1C = 0x30, /* yes: TITLE_STATE_EXIT_JOB_1C */
    TITLE_MESSAGE_MENU = 0x31,       /* the first menu again */
    TITLE_MESSAGE_WFC_FAILED = 0x32, /* the talk ends: back to the title */
    TITLE_MESSAGE_ASK_BOTTLE = 0x35, /* yes: TITLE_STATE_EXIT_SCENE_30 */
    TITLE_MESSAGE_BACK = 0x37        /* back to the title */
};

#define TITLE_MESSAGE_LIST_CANCEL 0x10 /* the last answer of the players' list */
#define TITLE_PLAYER_ANSWER_70 4       /* the players' answers' unk_70 */
#define TITLE_SE_CLOSE 0x3a            /* the sound when the talk of 0x24 or 0x27 closes */
#define TITLE_STATE_FLAG_12 0x12       /* the flag of the state block job 0xe reads */

/* The answers' tables, by the town (TitleMenu_TownCase). */
enum TitleTownCase {
    TITLE_TOWN_NO_PLAYER = 0, /* set up, no player */
    TITLE_TOWN_NONE = 1,      /* no town set up */
    TITLE_TOWN_FULL = 2,      /* four players */
    TITLE_TOWN_OTHER = 3,
    TITLE_TOWN_CASES = 4
};

/* The vtable. */
extern const u8 data_ov147_0229aae4[];

/* "sp_etc_sequence1" (a pointer to it) and "sp_etc_sequence2". */
extern const char *const data_ov147_0229a8b0;
extern const char data_ov147_0229abe0[];

/* The greeting message by the part of the day (0x2d, 0x2e, 0x2f, 0x2f). */
extern const u8 data_ov147_0229a6fc[];

/* The players' records and the state block, and this system's exchange block. */
extern u8 data_021dc7bc[];
extern u32 data_021dc7a8[];
extern ExchangeBlock data_021ee418;

/* The byte for no message (main's). */
extern const u8 data_021f43e8;

/* The sets of answers: the first menu's and the sub menu's by TitleTownCase, and yes or no. */
extern const TitleChoices data_ov147_0229aa70, data_ov147_0229aa7c, data_ov147_0229aa88, data_ov147_0229aa94;
extern const TitleChoices data_ov147_0229aaa0, data_ov147_0229aaac, data_ov147_0229aab8, data_ov147_0229aac4;
extern const TitleChoices data_ov147_0229aad0;

/* Bytes of the answers' values that are main's no-message byte, set the first time the
 * function runs (each with its guard). */
extern u8 data_ov147_0229a8a0[], data_ov147_0229a8a8[], data_ov147_0229a894[], data_ov147_0229a8c4[], data_ov147_0229a880[];
extern u32 data_ov147_0229aca4, data_ov147_0229acb4, data_ov147_0229acb0, data_ov147_0229aca0, data_ov147_0229acb8;

/* The answers' member functions of the first menu, by TitleTownCase (tables of the overlay's
 * .bss, filled once from the constants, with their guards; the last has five entries), and the
 * table of the four. */
extern u32 data_ov147_0229acc0, data_ov147_0229aca8, data_ov147_0229acbc, data_ov147_0229acac;
extern MemberPointer data_ov147_0229acc4[4], data_ov147_0229ace4[4], data_ov147_0229ad04[4], data_ov147_0229ad24[5];
extern MemberPointer *const data_ov147_0229a9fc[TITLE_TOWN_CASES];
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov147_0229a8f4, data_ov147_0229a904, data_ov147_0229a924, data_ov147_0229a92c,
    data_ov147_0229a93c, data_ov147_0229a944, data_ov147_0229a964, data_ov147_0229a984, data_ov147_0229a8ec,
    data_ov147_0229a90c, data_ov147_0229a914;

static TalkObject *title_receiver_talk(TitleReceiver *self)
{
    return (TalkObject *) (void *) self->base.talk;
}

static void title_set_byte_once(u32 *guard, u8 *byte, int count, const int *at)
{
    u32 flags = *guard;
    if ((flags & 1) == 0) {
        u8 none = data_021f43e8;
        for (int i = 0; i < count; i++) {
            byte[at[i]] = none;
        }
        *guard = flags | 1;
    }
}

/* Which answers the first menu has, from the town's players and whether it is set up. */
static int title_town_case(int players, int set_up)
{
    if (players <= 0 && set_up != 0) {
        return TITLE_TOWN_NO_PLAYER;
    }
    if (set_up == 0) {
        return TITLE_TOWN_NONE;
    }
    if (players == STATE_BLOCK_PLAYERS) {
        return TITLE_TOWN_FULL;
    }
    return TITLE_TOWN_OTHER;
}

/* func_ov147_02299320: the greeting message for the part of the day. */
unsigned char TitleMenu_GreetingMessage(TitleReceiver *self)
{
    (void) self;
    return data_ov147_0229a6fc[Calendar_PartOfDay()];
}
CLEAN_AS(func_ov147_02299320, TitleMenu_GreetingMessage)

/* func_ov147_02299338 (an answer of the first menu): when this system's letter in a bottle is
 * there and has not drifted yet, the talk asks message 0x35 next. */
void TitleMenu_CheckBottleLetter(TitleReceiver *self)
{
    ExchangeBlock *block = &data_021ee418;
    if (Letter_State((const Letter *) ExchangeBlock_BottleLetter(block)) == 0) {
        return;
    }
    if (ExchangeBlock_Drifts(block) != 0) {
        return;
    }
    u8 message = TITLE_MESSAGE_ASK_BOTTLE;
    TalkObject_SetMessage(title_receiver_talk(self), &message, NULL);
}
CLEAN_AS(func_ov147_02299338, TitleMenu_CheckBottleLetter)

/* func_ov147_02299374 (the answer to message 3): the town's player picked among those that
 * exist (in their order) made the activity's town player, and message 4 asked with its name as
 * part 0; with the last answer (none of them), message 0x31. */
void TitleMenu_PickTownPlayer(TitleReceiver *self)
{
    (void) self;
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    int picked = (int) TalkAnswers_Picked(TalkObject_Answers(talk));
    int message = TITLE_MESSAGE_MENU;
    int listed = 0;

    for (int i = 0; i < STATE_BLOCK_PLAYERS; i++) {
        if (PlayerRecords_TownExists(data_021dc7bc, i) == 0) {
            continue;
        }
        if (picked == listed) {
            PlayerIdText name;
            ActivityVars_SetTownPlayer(i);
            PlayerIdText_Construct(&name);
            PlayerId_NameToText(PlayerRecord_Player(PlayerRecords_TownRecord(data_021dc7bc, i)), (TextBase *) (void *) &name);
            TalkObject_SetPart(talk, 0, (TextBase *) (void *) &name);
            message = TITLE_MESSAGE_REMOVE;
            PlayerIdText_Destruct(&name);
        }
        listed++;
    }
    u8 byte = (u8) message;
    TalkObject_SetMessage(talk, &byte, data_ov147_0229a8b0);
}
CLEAN_AS(func_ov147_02299374, TitleMenu_PickTownPlayer)

/* func_ov147_022993fc (an answer of the first menu): back to the title (TITLE_STATE_END_TALK). */
void TitleMenu_EndToTitle(TitleReceiver *self)
{
    TitleScene_SetState(self->scene, TITLE_STATE_END_TALK);
}
CLEAN_AS(func_ov147_022993fc, TitleMenu_EndToTitle)

/* func_ov147_02299408 (an answer of the first menu): to scene 6 (TITLE_STATE_EXIT_SCENE_6). */
void TitleMenu_ToScene6(TitleReceiver *self)
{
    TitleScene_SetState(self->scene, TITLE_STATE_EXIT_SCENE_6);
}
CLEAN_AS(func_ov147_02299408, TitleMenu_ToScene6)

/* func_ov147_02299414 (an answer of the first menu without a town): a new town
 * (START_KIND_NEW_TOWN), to scene 0x2d (TITLE_STATE_EXIT_NEW). */
void TitleMenu_NewTown(TitleReceiver *self)
{
    StartKind_SetNewTown();
    TitleScene_SetState(self->scene, TITLE_STATE_EXIT_NEW);
}
CLEAN_AS(func_ov147_02299414, TitleMenu_NewTown)

/* func_ov147_0229942c (slot 0x18): the player's answer to the receiver's message:
 * - the first menu: the member function of the town's table for the answer, if any;
 * - messages 0 and 0x30: yes ends the talk and leaves by TITLE_STATE_EXIT_REQUEST or
 *   TITLE_STATE_EXIT_JOB_1C; message 0x35: yes ends the receiver's talk and leaves by
 *   TITLE_STATE_EXIT_SCENE_30;
 * - message 3: the player picked (TitleMenu_PickTownPlayer).
 * The four tables are filled first, once each.
 * REQUIRES: the answer is in its table (below 4, or 5 for TITLE_TOWN_OTHER); the game reads past
 * the table for others. */
void TitleMenu_OnAnswer(TitleReceiver *self)
{
    static const MemberPointer *const no_player[4] = {&__ptmf_null, &data_ov147_0229a8f4, &__ptmf_null, &data_ov147_0229a904};
    static const MemberPointer *const no_town[4] = {&data_ov147_0229a924, &data_ov147_0229a92c, &__ptmf_null,
                                                    &data_ov147_0229a93c};
    static const MemberPointer *const full[4] = {&data_ov147_0229a944, &data_ov147_0229a964, &__ptmf_null,
                                                 &data_ov147_0229a984};
    static const MemberPointer *const other[5] = {&data_ov147_0229a8ec, &__ptmf_null, &data_ov147_0229a90c, &__ptmf_null,
                                                  &data_ov147_0229a914};

    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    unsigned int picked = TalkAnswers_Picked(TalkObject_Answers(talk));
    int players = PlayerRecords_CountTown(data_021dc7bc);
    int set_up = StateBlock_IsSetUp((StateBlock *) (void *) data_021dc7a8);

    MemberTable_InitOnce(&data_ov147_0229acc0, data_ov147_0229acc4, no_player, 4);
    MemberTable_InitOnce(&data_ov147_0229aca8, data_ov147_0229ace4, no_town, 4);
    MemberTable_InitOnce(&data_ov147_0229acbc, data_ov147_0229ad04, full, 4);
    MemberTable_InitOnce(&data_ov147_0229acac, data_ov147_0229ad24, other, 5);

    switch (self->base.base.message) {
        case TITLE_MESSAGE_ASK_REQUEST:
            if (picked == 0) {
                TalkObject_SetMessage(talk, &data_021f43e8, NULL);
                TitleScene_SetState(self->scene, TITLE_STATE_EXIT_REQUEST);
            }
            break;
        case TITLE_MESSAGE_MENU_FIRST:
        case TITLE_MESSAGE_MENU_FIRST + 1:
        case TITLE_MESSAGE_MENU_LAST:
        case TITLE_MESSAGE_MENU: {
            const MemberPointer *entry = &data_ov147_0229a9fc[title_town_case(players, set_up)][picked];
            if (entry->function != 0) {
                MemberPointer_CallVoid(entry, self);
            }
            break;
        }
        case TITLE_MESSAGE_ASK_JOB_1C:
            if (picked == 0) {
                TalkObject_SetMessage(talk, &data_021f43e8, NULL);
                TitleScene_SetState(self->scene, TITLE_STATE_EXIT_JOB_1C);
            }
            break;
        case TITLE_MESSAGE_ASK_BOTTLE:
            if (picked == 0) {
                TalkObject_SetMessage(title_receiver_talk(self), &data_021f43e8, NULL);
                TitleScene_SetState(self->scene, TITLE_STATE_EXIT_SCENE_30);
            }
            break;
        case TITLE_MESSAGE_PICK_PLAYER:
            TitleMenu_PickTownPlayer(self);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov147_0229942c, TitleMenu_OnAnswer)

/* func_ov147_02299698 (slot 0x70): the talk closes; after messages 0x24 and 0x27 a sound. */
void TitleMenu_OnClose(TitleReceiver *self)
{
    u8 message = self->base.base.message;
    if (message == TITLE_MESSAGE_PLAYER_0 || message == TITLE_MESSAGE_NEW_PLAYER) {
        SoundSys_PlaySe(TITLE_SE_CLOSE);
    }
}
CLEAN_AS(func_ov147_02299698, TitleMenu_OnClose)

/* func_ov147_022996b4 (after message 3): the receiver's talk offers the town's players by name
 * (their answers' unk_70 4), then message 0x10 of answers' file 1 (unk_70 0), which B picks;
 * the choices open. */
void TitleMenu_ListTownPlayers(TitleReceiver *self)
{
    TalkObject *talk = title_receiver_talk(self);
    TalkAnswers *answers = TalkObject_Answers(talk);
    u8 player_value;
    u8 cancel_message;
    u8 cancel_value;
    int count = 0;

    TalkAnswers_Clear(answers);
    for (int i = 0; i < STATE_BLOCK_PLAYERS; i++) {
        if (PlayerRecords_TownExists(data_021dc7bc, i) == 0) {
            continue;
        }
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        PlayerId_NameToText(PlayerRecord_Player(PlayerRecords_TownRecord(data_021dc7bc, i)), (TextBase *) (void *) &name);
        TalkAnswer *answer = TalkAnswers_Answer(answers, count);
        player_value = TITLE_PLAYER_ANSWER_70;
        TalkAnswers_Set70(answer, &player_value);
        TextBase_Copy(TalkAnswers_Text(answer), (TextBase *) (void *) &name);
        count++;
        PlayerIdText_Destruct(&name);
    }

    TalkAnswer *cancel = TalkAnswers_Answer(answers, count);
    cancel_message = TITLE_MESSAGE_LIST_CANCEL;
    TalkAnswers_SetMessage(cancel, &cancel_message);
    TalkAnswers_SetFile(cancel, (int) TalkAnswers_SelectFileName(1));
    cancel_value = 0;
    TalkAnswers_Set70(cancel, &cancel_value);
    TalkAnswers_LoadAnswerText(cancel);
    TalkAnswers_SetCount(answers, count + 1);
    TalkAnswers_SetCancelToLast(answers);
    TalkObject_OpenChoices(talk, 1);
}
CLEAN_AS(func_ov147_022996b4, TitleMenu_ListTownPlayers)

/* func_ov147_0229977c: the receiver's talk offers the answers of `choices` (messages of the
 * answers' file 1, B picking the last), answers of messages 0, 1 and 0x12 with sound kind 1;
 * their texts loaded and the choices open. */
void TitleMenu_OfferChoices(TitleReceiver *self, const TitleChoices *choices)
{
    TalkObject *talk = title_receiver_talk(self);
    TalkAnswers *answers = TalkObject_Answers(talk);
    const u8 *messages = choices->messages;
    const u8 *values = choices->values;
    int count = choices->count;

    TalkAnswers_Reset(answers, count, count - 1);
    for (int i = 0; i < count; i++) {
        u8 answer[2];
        answer[0] = messages[i];
        answer[1] = values[i];
        int sound_kind = answer[0] == TITLE_MESSAGE_ANSWER_YES || answer[0] <= 1;
        TalkAnswers_Set(answers, i, &answer[0], 1, &answer[1], NULL, sound_kind);
    }
    TalkAnswers_LoadTexts(answers);
    TalkObject_OpenChoices(talk, 1);
}
CLEAN_AS(func_ov147_0229977c, TitleMenu_OfferChoices)

/* func_ov147_022997ec (slot 0x14): what follows the receiver's message, once the answers'
 * values that are main's no-message byte are set. With the card's stamp unreadable the talk is
 * held. Else, by the message:
 * - the first menu and message 1: their answers by the town (TitleTownCase);
 * - 0x27: a new player (START_KIND_NEW_PLAYER), the talk quiet, TITLE_STATE_EXIT_NEW;
 * - 0x24: the talk quiet and ended, START_KIND_PLAYER_0, TITLE_STATE_EXIT_NEW;
 * - 3: the players listed; 0, 0x30, 0x35: yes or no;
 * - 6 and 0x0b: the talk ended, TITLE_STATE_EXIT_JOB_6 or TITLE_STATE_EXIT_JOB_5;
 * - 5 and 0x0a: message 0x31 next; 0x37: back to the title; 0x32: the talk ended, back to the
 *   title. */
void TitleMenu_AfterMessage(TitleReceiver *self)
{
    static const int at_3[] = {3}, at_0_3[] = {0, 3}, at_0_4[] = {0, 4}, at_0[] = {0};
    title_set_byte_once(&data_ov147_0229aca4, data_ov147_0229a8a0, 1, at_3);
    title_set_byte_once(&data_ov147_0229acb4, data_ov147_0229a8a8, 2, at_0_3);
    title_set_byte_once(&data_ov147_0229acb0, data_ov147_0229a894, 2, at_0_3);
    title_set_byte_once(&data_ov147_0229aca0, data_ov147_0229a8c4, 2, at_0_4);
    title_set_byte_once(&data_ov147_0229acb8, data_ov147_0229a880, 1, at_0);

    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    int players = PlayerRecords_CountTown(data_021dc7bc);
    int set_up = StateBlock_IsSetUp((StateBlock *) (void *) data_021dc7a8);

    if (self->scene->card_unreadable != 0) {
        TalkObject_Hold(talk);
        return;
    }

    static const TitleChoices *const menu[TITLE_TOWN_CASES] = {&data_ov147_0229aa70, &data_ov147_0229aa7c,
                                                               &data_ov147_0229aa88, &data_ov147_0229aa94};
    static const TitleChoices *const sub_menu[TITLE_TOWN_CASES] = {&data_ov147_0229aaa0, &data_ov147_0229aaac,
                                                                   &data_ov147_0229aab8, &data_ov147_0229aac4};

    switch (self->base.base.message) {
        case TITLE_MESSAGE_MENU_FIRST:
        case TITLE_MESSAGE_MENU_FIRST + 1:
        case TITLE_MESSAGE_MENU_LAST:
        case TITLE_MESSAGE_MENU:
            TitleMenu_OfferChoices(self, menu[title_town_case(players, set_up)]);
            break;
        case TITLE_MESSAGE_SUB_MENU:
            TitleMenu_OfferChoices(self, sub_menu[title_town_case(players, set_up)]);
            break;
        case TITLE_MESSAGE_NEW_PLAYER:
            StartKind_SetNewPlayer();
            TalkObject_SetQuiet(talk);
            TitleScene_SetState(self->scene, TITLE_STATE_EXIT_NEW);
            break;
        case TITLE_MESSAGE_PICK_PLAYER:
            TitleMenu_ListTownPlayers(self);
            break;
        case TITLE_MESSAGE_REMOVED:
            TalkObject_SetMessage(talk, &data_021f43e8, NULL);
            TitleScene_SetState(self->scene, TITLE_STATE_EXIT_JOB_6);
            break;
        case TITLE_MESSAGE_JOB_5:
            TalkObject_SetMessage(talk, &data_021f43e8, NULL);
            TitleScene_SetState(self->scene, TITLE_STATE_EXIT_JOB_5);
            break;
        case TITLE_MESSAGE_THEN_31A:
        case TITLE_MESSAGE_THEN_31B: {
            u8 message = TITLE_MESSAGE_MENU;
            TalkObject_SetMessage(talk, &message, data_ov147_0229a8b0);
            break;
        }
        case TITLE_MESSAGE_BACK:
            TitleScene_SetState(self->scene, TITLE_STATE_END_TALK);
            break;
        case TITLE_MESSAGE_ASK_REQUEST:
        case TITLE_MESSAGE_ASK_JOB_1C:
        case TITLE_MESSAGE_ASK_BOTTLE:
            TitleMenu_OfferChoices(self, &data_ov147_0229aad0);
            break;
        case TITLE_MESSAGE_PLAYER_0:
            TalkObject_SetQuiet(talk);
            TalkObject_SetMessage(talk, &data_021f43e8, NULL);
            StartKind_SetPlayer0();
            TitleScene_SetState(self->scene, TITLE_STATE_EXIT_NEW);
            break;
        case TITLE_MESSAGE_WFC_FAILED:
            TalkObject_SetMessage(talk, &data_021f43e8, NULL);
            TitleScene_SetState(self->scene, TITLE_STATE_END_TALK);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov147_022997ec, TitleMenu_AfterMessage)

/* func_ov147_02299aac: the scene the receiver belongs to. */
void TitleReceiver_SetScene(TitleReceiver *self, TitleScene *scene)
{
    self->scene = scene;
}
CLEAN_AS(func_ov147_02299aac, TitleReceiver_SetScene)

/* func_ov147_02299ab0 (vtable slot 1): destructed (main's receiver) and freed. */
TitleReceiver *TitleReceiver_Delete(TitleReceiver *self)
{
    self->base.base.vtable = data_ov147_0229aae4;
    TalkReceiver_Destruct(&self->base);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_ov147_02299ab0, TitleReceiver_Delete)

/* func_ov147_02299ad0 (vtable slot 0): the destructor: the class's vtable, then main's
 * receiver's destructor. */
TitleReceiver *TitleReceiver_Destruct(TitleReceiver *self)
{
    self->base.base.vtable = data_ov147_0229aae4;
    TalkReceiver_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov147_02299ad0, TitleReceiver_Destruct)

/* func_ov147_02299ae8: the constructor: main's receiver, then the class's vtable. */
TitleReceiver *TitleReceiver_Construct(TitleReceiver *self)
{
    TalkReceiver_ConstructBase(&self->base);
    self->base.base.vtable = data_ov147_0229aae4;
    return self;
}
CLEAN_AS(func_ov147_02299ae8, TitleReceiver_Construct)
