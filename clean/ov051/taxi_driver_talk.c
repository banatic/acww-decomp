/* The taxi driver's talk scene (taxi_driver_talk.h). */
#include "taxi_driver_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/date_time.h"
#include "main/group_params.h"
#include "main/message_receiver.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/start_kind.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/town_generator.h"
#include "ov068/taxi.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(TaxiDriverTalk, owner) == 0xb0, "owner");
static_assert(offsetof(TaxiDriverTalk, after) == 0xb4, "after");
static_assert(sizeof(TaxiDriverTalk) == 0xbc, "its talk scene");
static_assert(sizeof(TaxiDriverTalkStart) == 8, "a start");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The vtable of its class. */
extern const u8 data_ov051_02261804[];
/* The null member pointer. */
extern const MemberPointer __ptmf_null;
/* The address of the message file's name, "sp_etc_sequence3", and the name "st_general" of
 * the file of the greetings. */
extern const u32 data_ov051_022615c0;
extern const char data_ov051_02261b68[];
/* The lines the answers pick, by answer (TaxiDriverTalk_OnAnswerPoints1, _Points2 and
 * _Points4), the last two by answer and gender. */
extern const u8 data_ov051_022614bc[];
extern const u8 data_ov051_022614c0[];
extern const u8 data_ov051_022614c4[];
extern const u8 data_ov051_022614c8[];
/* The face for each number of points, two (a boy's and a girl's) a row. */
extern const s32 data_ov051_022614cc[];
/* The looks that go with each face, two (a boy and a girl) a row (main's table). */
typedef struct TaxiDriverTalkLooks {
    u8 head_kind;
    u8 hair_color;
    u16 clothes;
} TaxiDriverTalkLooks;
static_assert(sizeof(TaxiDriverTalkLooks) == 4, "looks");
extern const TaxiDriverTalkLooks data_020d19d0[];
/* The message the talk is given once the looks are set (main's, as activity_talk.c's). */
extern u8 data_021f43e8;

/* The handlers by line: of the answers and of the ends of lines; function-local statics the
 * compiler fills from the constants on the first call (bit 0 of their guard says it was). */
typedef struct TaxiDriverTalkHandler {
    s32 line;
    MemberPointer handler;
} TaxiDriverTalkHandler;
static_assert(sizeof(TaxiDriverTalkHandler) == 0xc, "a line's handler");

#define TDT_ANSWERS 14
extern TaxiDriverTalkHandler data_ov051_0226188c[TDT_ANSWERS];
extern u32 data_ov051_02261b8c;
extern const MemberPointer data_ov051_0226168c, data_ov051_022616cc, data_ov051_022616dc, data_ov051_02261664,
    data_ov051_022615dc, data_ov051_022615cc, data_ov051_022615d4, data_ov051_022615fc, data_ov051_02261614,
    data_ov051_022616a4, data_ov051_0226172c, data_ov051_02261654, data_ov051_022615ec, data_ov051_0226166c;

#define TDT_ENDS 32
extern TaxiDriverTalkHandler data_ov051_022619e8[TDT_ENDS];
extern u32 data_ov051_02261b88;
extern const MemberPointer data_ov051_0226164c, data_ov051_02261724, data_ov051_0226171c, data_ov051_02261714,
    data_ov051_0226170c, data_ov051_02261704, data_ov051_022616fc, data_ov051_022616f4, data_ov051_0226162c,
    data_ov051_022616e4, data_ov051_02261624, data_ov051_022616d4, data_ov051_0226161c, data_ov051_022616c4,
    data_ov051_02261604, data_ov051_022616b4, data_ov051_0226160c, data_ov051_0226173c, data_ov051_0226169c,
    data_ov051_0226167c, data_ov051_02261684, data_ov051_022616ac, data_ov051_022616bc, data_ov051_0226177c,
    data_ov051_022616ec, data_ov051_02261764, data_ov051_0226165c, data_ov051_02261744, data_ov051_02261734,
    data_ov051_02261644, data_ov051_0226163c, data_ov051_02261634;

/* The work after a command, by TAXI_DRIVER_TALK_AFTER_* (filled once, the same way). */
extern MemberPointer data_ov051_02261b90[TAXI_DRIVER_TALK_AFTERS];
extern u32 data_ov051_02261b84;
extern const MemberPointer data_ov051_0226175c, data_ov051_02261754, data_ov051_0226174c;

/* The lines of "sp_etc_sequence3" the code names. */
#define TDT_LINE_GREETING_0 0x00      /* begins with the greeting and the hour */
#define TDT_LINE_GREETING_2 0x02      /* the same, after the time's screen */
#define TDT_LINE_FIRST_SAME_TOWN 0x28 /* the first line of a start in the town as it is (a new player, or unchanged) */

/* The greetings of "st_general" (part 0 of the lines 0 and 2), from noon on the second. */
#define TDT_GREETING_MORNING 0x19
#define TDT_GREETING_AFTERNOON 0x1a
#define TDT_NOON 12

/* The screen of group 9 its ends of lines open (SceneCommand_RequestScreen) and its modes. */
#define TDT_SCREEN_MODE_TIME 0x30
#define TDT_MODE_PLAYER_NAME 0x0f
#define TDT_MODE_TOWN_NAME 0x10

/* The value slot and format the hour is put in (SceneBase_PutValue). */
#define TDT_HOUR_SLOT 1
#define TDT_HOUR_FORMAT 2

/* The driver's state once the looks are set. */
#define TDT_OWNER_LEAVES 4

/* The vtable slot its talks call first. */
#define TDT_SLOT_08 0x08

static TalkObject *tdt_talk_object(TaxiDriverTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static u8 tdt_shown(const TaxiDriverTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* Line `line` of "sp_etc_sequence3" shown. */
static void tdt_say(TaxiDriverTalk *talk, u8 line)
{
    TalkObject_SetMessage(tdt_talk_object(talk), &line, (const char *) (uintptr_t) data_ov051_022615c0);
}

/* The current player's gender (byte 0x1c of its id: 0 a boy, 1 a girl). */
static int tdt_gender(void)
{
    return PlayerId_Gender((const s8 *) (void *) PlayerRecord_Player(PlayerRecords_Current()));
}

/* A line's handler called with `answer` (an answer's) or alone (an end of line's). */
static void tdt_call_answer(const MemberPointer *handler, TaxiDriverTalk *talk, int answer)
{
    void *self = MemberPointer_Object(handler, talk);
    ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(handler, self))(self, answer);
}

/* `table` filled from `constants` once (bit 0 of `guard`), the lines being in place. */
static void tdt_fill_once(u32 *guard, TaxiDriverTalkHandler *table, const MemberPointer *const *constants, int count)
{
    u32 flags = *guard;
    if ((flags & 1) == 0) {
        for (int i = 0; i < count; i++) {
            table[i].handler = *constants[i];
        }
        *guard = flags | 1;
    }
}

/* func_ov051_022605e8: `line` plus the current player's gender, as a byte (the lines come in a
 * boy's and a girl's). */
unsigned char TaxiDriverTalk_GenderLine(TaxiDriverTalk *talk, int line)
{
    (void) talk;
    return (u8) (line + (u8) tdt_gender());
}
CLEAN_AS(func_ov051_022605e8, TaxiDriverTalk_GenderLine)

/* ---- The answers */

/* func_ov051_022604a8 (vtable slot 0x18, the player's answer): each handler of the line shown
 * is called with the answer picked (read again for each). */
void TaxiDriverTalk_OnAnswer(TaxiDriverTalk *talk)
{
    static const MemberPointer *const handlers[TDT_ANSWERS] = {
        &data_ov051_0226168c, /* 0x05: TaxiDriverTalk_OnAnswerPoints4 */
        &data_ov051_022616cc, /* 0x03: TaxiDriverTalk_OnAnswerPoints4 */
        &data_ov051_022616dc, /* 0x28: TaxiDriverTalk_OnAnswerPoints4 */
        &data_ov051_02261664, /* 0x0b: TaxiDriverTalk_OnAnswerGirlsName */
        &data_ov051_022615dc, /* 0x0c: TaxiDriverTalk_OnAnswerBoysName */
        &data_ov051_022615cc, /* 0x15: TaxiDriverTalk_OnAnswerTown */
        &data_ov051_022615d4, /* 0x16: TaxiDriverTalk_OnAnswerTown */
        &data_ov051_022615fc, /* 0x19: TaxiDriverTalk_OnAnswerPoints2 */
        &data_ov051_02261614, /* 0x1a: TaxiDriverTalk_OnAnswerPoints2 */
        &data_ov051_022616a4, /* 0x1f: TaxiDriverTalk_OnAnswerPoints1 */
        &data_ov051_0226172c, /* 0x20: TaxiDriverTalk_OnAnswerPoints1 */
        &data_ov051_02261654, /* 0x11: TaxiDriverTalk_OnAnswer11 */
        &data_ov051_022615ec, /* 0x12: TaxiDriverTalk_OnAnswer11 */
        &data_ov051_0226166c, /* 0x30: TaxiDriverTalk_OnAnswer30 */
    };

    tdt_fill_once(&data_ov051_02261b8c, data_ov051_0226188c, handlers, TDT_ANSWERS);
    for (u32 i = 0; i < TDT_ANSWERS; i++) {
        const TaxiDriverTalkHandler *entry = &data_ov051_0226188c[i];
        if (entry->line == tdt_shown(talk)) {
            int answer = (int) TalkAnswers_Picked(TalkObject_Answers(tdt_talk_object(talk)));
            tdt_call_answer(&entry->handler, talk, answer);
        }
    }
}
CLEAN_AS(func_ov051_022604a8, TaxiDriverTalk_OnAnswer)

/* func_ov051_02260608 (the lines 0x1f and 0x20): starting a new town, the line of
 * data_ov051_022614bc for the answer plus the gender; else the first answer 0x21 (a boy) or
 * 0x2f (any other), the others 0x23 plus the gender. The second answer is worth 1 point. */
void TaxiDriverTalk_OnAnswerPoints1(TaxiDriverTalk *talk, int answer)
{
    u8 line;
    if (StartKind_IsNewTown()) {
        line = TaxiDriverTalk_GenderLine(talk, data_ov051_022614bc[answer]);
    } else if (answer == 0) {
        line = tdt_gender() == 0 ? 0x21 : 0x2f;
    } else {
        line = TaxiDriverTalk_GenderLine(talk, 0x23);
    }
    tdt_say(talk, line);
    if (answer == 1) {
        talk->owner->points += 1;
    }
}
CLEAN_AS(func_ov051_02260608, TaxiDriverTalk_OnAnswerPoints1)

/* func_ov051_02260680 (the lines 0x19 and 0x1a): the line of data_ov051_022614c0 for the
 * answer plus the gender. The second answer is worth 2 points. */
void TaxiDriverTalk_OnAnswerPoints2(TaxiDriverTalk *talk, int answer)
{
    tdt_say(talk, TaxiDriverTalk_GenderLine(talk, data_ov051_022614c0[answer]));
    if (answer == 1) {
        talk->owner->points += 2;
    }
}
CLEAN_AS(func_ov051_02260680, TaxiDriverTalk_OnAnswerPoints2)

/* func_ov051_022606c8 (the lines 0x03, 0x05 and 0x28): starting as a player moved in, the line
 * of data_ov051_022614c8 for the answer and the gender; else the line of data_ov051_022614c4
 * for the answer. The second answer is worth 4 points. */
void TaxiDriverTalk_OnAnswerPoints4(TaxiDriverTalk *talk, int answer)
{
    u8 line;
    if (StartKind_IsMovedIn()) {
        line = data_ov051_022614c8[2 * answer + tdt_gender()];
    } else {
        line = data_ov051_022614c4[answer];
    }
    tdt_say(talk, line);
    if (answer == 1) {
        talk->owner->points += 4;
    }
}
CLEAN_AS(func_ov051_022606c8, TaxiDriverTalk_OnAnswerPoints4)

/* func_ov051_0226072c (the line 0x30): the first answer 0x31, the second 0x32. */
void TaxiDriverTalk_OnAnswer30(TaxiDriverTalk *talk, int answer)
{
    switch (answer) {
        case 0:
            tdt_say(talk, 0x31);
            break;
        case 1:
            tdt_say(talk, 0x32);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov051_0226072c, TaxiDriverTalk_OnAnswer30)

/* func_ov051_0226076c (the lines 0x15 and 0x16): 0x17 plus the gender, and the answer becomes
 * the town generator's special choice. */
void TaxiDriverTalk_OnAnswerTown(TaxiDriverTalk *talk, void *answer)
{
    tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x17));
    TownGenerator_SetSpecialChoice((unsigned int) (uintptr_t) answer);
}
CLEAN_AS(func_ov051_0226076c, TaxiDriverTalk_OnAnswerTown)

/* func_ov051_0226079c (the line 0x0b, "a cute girl's name"): the first answer makes the player
 * a girl (1) and goes on at 0x19 (starting a new player) or 0x0f, plus the gender; the second
 * makes it a boy (0), line 0x0d. */
void TaxiDriverTalk_OnAnswerGirlsName(TaxiDriverTalk *talk, int answer)
{
    switch (answer) {
        case 0:
            PlayerId_SetGender((u8 *) (void *) PlayerRecord_Player(PlayerRecords_Current()), 1);
            if (StartKind_IsNewPlayer()) {
                tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x19));
            } else {
                tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x0f));
            }
            break;
        case 1:
            PlayerId_SetGender((u8 *) (void *) PlayerRecord_Player(PlayerRecords_Current()), 0);
            tdt_say(talk, 0x0d);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov051_0226079c, TaxiDriverTalk_OnAnswerGirlsName)

/* func_ov051_02260828 (the line 0x0c, "a manly name"): the first answer makes the player a
 * boy (0) and goes on as at 0x0b; the second makes it a girl (1), line 0x0e. */
void TaxiDriverTalk_OnAnswerBoysName(TaxiDriverTalk *talk, int answer)
{
    switch (answer) {
        case 0:
            PlayerId_SetGender((u8 *) (void *) PlayerRecord_Player(PlayerRecords_Current()), 0);
            if (StartKind_IsNewPlayer()) {
                tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x19));
            } else {
                tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x0f));
            }
            break;
        case 1:
            PlayerId_SetGender((u8 *) (void *) PlayerRecord_Player(PlayerRecords_Current()), 1);
            tdt_say(talk, 0x0e);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov051_02260828, TaxiDriverTalk_OnAnswerBoysName)

/* func_ov051_022608b4 (the lines 0x11 and 0x12): the first answer 0x15 (starting as a player
 * moved in) or 0x19, the second 0x13, plus the gender. */
void TaxiDriverTalk_OnAnswer11(TaxiDriverTalk *talk, int answer)
{
    switch (answer) {
        case 0:
            if (StartKind_IsMovedIn()) {
                tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x15));
            } else {
                tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x19));
            }
            break;
        case 1:
            tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x13));
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov051_022608b4, TaxiDriverTalk_OnAnswer11)

/* ---- The ends of lines */

/* _ZN18Obj_ov051_0226180419func_ov051_02260928Ev (vtable slot 0x14, a line ended): each
 * handler of the line shown is called. */
void TaxiDriverTalk_OnLineEnded(TaxiDriverTalk *talk)
{
    static const MemberPointer *const handlers[TDT_ENDS] = {
        &data_ov051_0226164c, /* 0x01: TaxiDriverTalk_AskTime */
        &data_ov051_02261724, /* 0x04: TaxiDriverTalk_AskTime */
        &data_ov051_0226171c, /* 0x08: TaxiDriverTalk_AskPlayerName */
        &data_ov051_02261714, /* 0x0a: TaxiDriverTalk_AskPlayerName */
        &data_ov051_0226170c, /* 0x29: TaxiDriverTalk_AskPlayerName */
        &data_ov051_02261704, /* 0x0f: TaxiDriverTalk_AskTownName */
        &data_ov051_022616fc, /* 0x10: TaxiDriverTalk_AskTownName */
        &data_ov051_022616f4, /* 0x13: TaxiDriverTalk_AskTownName */
        &data_ov051_0226162c, /* 0x14: TaxiDriverTalk_AskTownName */
        &data_ov051_022616e4, /* 0x25: TaxiDriverTalk_SetLooks */
        &data_ov051_02261624, /* 0x26: TaxiDriverTalk_SetLooks */
        &data_ov051_022616d4, /* 0x06: TaxiDriverTalk_End06 */
        &data_ov051_0226161c, /* 0x07: TaxiDriverTalk_End06 */
        &data_ov051_022616c4, /* 0x1b: TaxiDriverTalk_End1b */
        &data_ov051_02261604, /* 0x1c: TaxiDriverTalk_End1b */
        &data_ov051_022616b4, /* 0x1d: TaxiDriverTalk_End1b */
        &data_ov051_0226160c, /* 0x1e: TaxiDriverTalk_End1b */
        &data_ov051_0226173c, /* 0x2b: TaxiDriverTalk_End2b */
        &data_ov051_0226169c, /* 0x2c: TaxiDriverTalk_End2b */
        &data_ov051_0226167c, /* 0x2d: TaxiDriverTalk_End2b */
        &data_ov051_02261684, /* 0x2e: TaxiDriverTalk_End2b */
        &data_ov051_022616ac, /* 0x0d: TaxiDriverTalk_End0d */
        &data_ov051_022616bc, /* 0x0e: TaxiDriverTalk_End0e */
        &data_ov051_0226177c, /* 0x17: TaxiDriverTalk_End17 */
        &data_ov051_022616ec, /* 0x18: TaxiDriverTalk_End17 */
        &data_ov051_02261764, /* 0x21: TaxiDriverTalk_EndLooksLine */
        &data_ov051_0226165c, /* 0x22: TaxiDriverTalk_EndLooksLine */
        &data_ov051_02261744, /* 0x23: TaxiDriverTalk_EndLooksLine */
        &data_ov051_02261734, /* 0x24: TaxiDriverTalk_EndLooksLine */
        &data_ov051_02261644, /* 0x2f: TaxiDriverTalk_EndLooksLine */
        &data_ov051_0226163c, /* 0x31: TaxiDriverTalk_EndLooksLine */
        &data_ov051_02261634, /* 0x32: TaxiDriverTalk_EndLooksLine */
    };

    tdt_fill_once(&data_ov051_02261b88, data_ov051_022619e8, handlers, TDT_ENDS);
    for (u32 i = 0; i < TDT_ENDS; i++) {
        const TaxiDriverTalkHandler *entry = &data_ov051_022619e8[i];
        if (entry->line == tdt_shown(talk)) {
            MemberPointer_CallVoid(&entry->handler, talk);
        }
    }
}
CLEAN_AS(_ZN18Obj_ov051_0226180419func_ov051_02260928Ev, TaxiDriverTalk_OnLineEnded)

/* func_ov051_02260b60 (the lines 0x25 and 0x26): starting a new player or a new town, the
 * current player's face, hair color, head and clothes from its points and gender: the face is
 * data_ov051_022614cc's for the points and the gender (8 more for girls), the rest
 * main's looks of that face and gender (data_020d19d0). Then the talk is given the message
 * data_021f43e8 (with no file name) and the driver leaves (state 4).
 * REQUIRES: the points are 0 to 7 and the gender 0 or 1 (the tables are not bounded). */
void TaxiDriverTalk_SetLooks(TaxiDriverTalk *talk)
{
    if (StartKind_IsNewPlayer() || StartKind_IsNewTown()) {
        u8 *record = PlayerRecords_Current();
        int gender = PlayerId_Gender((const s8 *) (void *) PlayerRecord_Player(record));
        s32 face = data_ov051_022614cc[2 * talk->owner->points + gender];
        u32 face_code = gender == 0 ? (u8) face : (u8) (face + 8);
        const TaxiDriverTalkLooks *looks = &data_020d19d0[2 * face + gender];
        PlayerRecord_SetFace(record, face_code);
        PlayerRecord_SetHairColor(record, looks->hair_color);
        PlayerRecord_SetHeadKind(record, looks->head_kind);
        u16 clothes = looks->clothes;
        PlayerRecord_SetClothes(record, &clothes);
    }
    TalkObject_SetMessage(tdt_talk_object(talk), &data_021f43e8, NULL);
    TaxiDriver_SetState(talk->owner, TDT_OWNER_LEAVES);
}
CLEAN_AS(func_ov051_02260b60, TaxiDriverTalk_SetLooks)

/* func_ov051_02260c1c (the lines 0x21 to 0x24, 0x2f, 0x31 and 0x32): 0x25 plus the gender. */
void TaxiDriverTalk_EndLooksLine(TaxiDriverTalk *talk)
{
    tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x25));
}
CLEAN_AS(func_ov051_02260c1c, TaxiDriverTalk_EndLooksLine)

/* func_ov051_02260c44 (the lines 0x17 and 0x18): 0x25 (starting as a player moved in) or 0x1f,
 * plus the gender. */
void TaxiDriverTalk_End17(TaxiDriverTalk *talk)
{
    if (StartKind_IsMovedIn()) {
        tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x25));
    } else {
        tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x1f));
    }
}
CLEAN_AS(func_ov051_02260c44, TaxiDriverTalk_End17)

/* func_ov051_02260c94 (the line 0x0e): 0x1a starting a new player, else 0x10. */
void TaxiDriverTalk_End0e(TaxiDriverTalk *talk)
{
    tdt_say(talk, StartKind_IsNewPlayer() ? 0x1a : 0x10);
}
CLEAN_AS(func_ov051_02260c94, TaxiDriverTalk_End0e)

/* func_ov051_02260cd8 (the line 0x0d): 0x19 starting a new player, else 0x0f. */
void TaxiDriverTalk_End0d(TaxiDriverTalk *talk)
{
    tdt_say(talk, StartKind_IsNewPlayer() ? 0x19 : 0x0f);
}
CLEAN_AS(func_ov051_02260cd8, TaxiDriverTalk_End0d)

/* func_ov051_02260d1c (the lines 0x2b to 0x2e): 0x0f plus the gender. */
void TaxiDriverTalk_End2b(TaxiDriverTalk *talk)
{
    tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x0f));
}
CLEAN_AS(func_ov051_02260d1c, TaxiDriverTalk_End2b)

/* func_ov051_02260d44 (the lines 0x1b to 0x1e): 0x15 (starting a new town) or 0x1f, plus the
 * gender. */
void TaxiDriverTalk_End1b(TaxiDriverTalk *talk)
{
    if (StartKind_IsNewTown()) {
        tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x15));
    } else {
        tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x1f));
    }
}
CLEAN_AS(func_ov051_02260d44, TaxiDriverTalk_End1b)

/* func_ov051_02260d94 (the lines 0x06 and 0x07): 0x30 when the start changes nothing; else the
 * talk goes on by itself. */
void TaxiDriverTalk_End06(TaxiDriverTalk *talk)
{
    if (StartKind_IsUnchanged()) {
        tdt_say(talk, 0x30);
    }
}
CLEAN_AS(func_ov051_02260d94, TaxiDriverTalk_End06)

/* Screen 2 opened in `mode` (staying on the line), and `after` done once it closes. */
static void tdt_ask(TaxiDriverTalk *talk, char mode, int after)
{
    SceneCommand_SetScreenMode((SceneCommandScene *) (void *) talk, mode, 0);
    SceneCommand_RequestScreen((SceneCommandScene *) (void *) talk, SCENE_COMMAND_SCREEN_MODE);
    TaxiDriverTalk_SetAfter(talk, after);
}

/* func_ov051_02260dc0 (the lines 0x0f, 0x10, 0x13 and 0x14): the town name's keyboard (mode
 * 0x10; "where are we going?"), then TaxiDriverTalk_AfterTownName. */
void TaxiDriverTalk_AskTownName(void *talk)
{
    tdt_ask(talk, TDT_MODE_TOWN_NAME, TAXI_DRIVER_TALK_AFTER_TOWN_NAME);
}
CLEAN_AS(func_ov051_02260dc0, TaxiDriverTalk_AskTownName)

/* func_ov051_02260de4 (the lines 0x08, 0x0a and 0x29): the player name's keyboard (mode
 * 0x0f; "what is your name?"), then TaxiDriverTalk_AfterPlayerName. */
void TaxiDriverTalk_AskPlayerName(void *talk)
{
    tdt_ask(talk, TDT_MODE_PLAYER_NAME, TAXI_DRIVER_TALK_AFTER_PLAYER_NAME);
}
CLEAN_AS(func_ov051_02260de4, TaxiDriverTalk_AskPlayerName)

/* func_ov051_02260e08 (the lines 0x01 and 0x04): the screen in mode 0x30, then
 * TaxiDriverTalk_AfterTime. */
void TaxiDriverTalk_AskTime(void *talk)
{
    tdt_ask(talk, TDT_SCREEN_MODE_TIME, TAXI_DRIVER_TALK_AFTER_TIME);
}
CLEAN_AS(func_ov051_02260e08, TaxiDriverTalk_AskTime)

/* ---- The other slots */

/* func_ov051_02260e2c (vtable slot 0x10, a line begins): at the lines 0 and 2, part 0 of talk
 * 0 is the greeting of "st_general" for the hour now (0x19 before noon, else 0x1a) and the
 * scene's value slot 1 the hour on a twelve-hour clock (format 2).
 * QUIRK: the hour 12 the clock turns 0 into is turned back into 0 at once: noon and midnight
 * are told as 0. */
void TaxiDriverTalk_OnLineBegins(TaxiDriverTalk *talk)
{
    if (tdt_shown(talk) != TDT_LINE_GREETING_0 && tdt_shown(talk) != TDT_LINE_GREETING_2) {
        return;
    }
    TalkObject *object = TalkObject_Get(0);
    DateTime now = {0};
    DateTime_Now(&now);
    u8 greeting = now.hour >= TDT_NOON ? TDT_GREETING_AFTERNOON : TDT_GREETING_MORNING;
    TalkObject_LoadPart(object, 0, &greeting, (unsigned int) (uintptr_t) data_ov051_02261b68);

    unsigned int hour = now.hour;
    if (hour >= TDT_NOON) {
        hour -= TDT_NOON;
    }
    if (hour == 0) {
        hour = TDT_NOON;
    }
    if (hour == TDT_NOON) {
        hour = 0;
    }
    SceneBase_PutValue(&talk->base, (int) hour, TDT_HOUR_SLOT, TDT_HOUR_FORMAT, 0, 0);
}
CLEAN_AS(func_ov051_02260e2c, TaxiDriverTalk_OnLineBegins)

/* func_ov051_02260ea0 (after the time's screen): line 2. */
void TaxiDriverTalk_AfterTime(TaxiDriverTalk *talk)
{
    tdt_say(talk, TDT_LINE_GREETING_2);
}
CLEAN_AS(func_ov051_02260ea0, TaxiDriverTalk_AfterTime)

/* func_ov051_02260ec0 (after the player's name, mode 0x0f): 0x29 when GroupParams_C4CIs2, else
 * 0x09. */
void TaxiDriverTalk_AfterPlayerName(TaxiDriverTalk *talk)
{
    tdt_say(talk, GroupParams_C4CIs2() ? 0x29 : 0x09);
}
CLEAN_AS(func_ov051_02260ec0, TaxiDriverTalk_AfterPlayerName)

/* func_ov051_02260f04 (after the town's name, mode 0x10): 0x11 plus the gender. */
void TaxiDriverTalk_AfterTownName(TaxiDriverTalk *talk)
{
    tdt_say(talk, TaxiDriverTalk_GenderLine(talk, 0x11));
}
CLEAN_AS(func_ov051_02260f04, TaxiDriverTalk_AfterTownName)

/* func_ov051_02260f2c: the work after the next command is `after`'s (its table filled once).
 * REQUIRES: `after` is 0 to 2 (the table is not bounded). */
void TaxiDriverTalk_SetAfter(TaxiDriverTalk *talk, int after)
{
    static const MemberPointer *const afters[TAXI_DRIVER_TALK_AFTERS] = {
        &data_ov051_0226175c, /* TaxiDriverTalk_AfterTownName */
        &data_ov051_02261754, /* TaxiDriverTalk_AfterPlayerName */
        &data_ov051_0226174c, /* TaxiDriverTalk_AfterTime */
    };
    MemberTable_InitOnce(&data_ov051_02261b84, data_ov051_02261b90, afters, TAXI_DRIVER_TALK_AFTERS);
    talk->after = data_ov051_02261b90[after];
}
CLEAN_AS(func_ov051_02260f2c, TaxiDriverTalk_SetAfter)

/* func_ov051_02260f94 (vtable slot 0x84, a command of the scene ended): the work set, if any,
 * done and cleared (the null member pointer). */
void TaxiDriverTalk_RunAfter(TaxiDriverTalk *talk)
{
    if (talk->after.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->after, talk);
    talk->after = __ptmf_null;
}
CLEAN_AS(func_ov051_02260f94, TaxiDriverTalk_RunAfter)

/* func_ov051_02260fd8 (vtable slot 0x78, the line the talk starts with), of
 * "sp_etc_sequence3": 0 starting a new town or as a player moved in, else 0x28. */
void TaxiDriverTalk_Line(int talk, TaxiDriverTalkStart *out)
{
    (void) talk;
    out->name = data_ov051_022615c0;
    if (StartKind_IsNewTown() || StartKind_IsMovedIn()) {
        out->message = TDT_LINE_GREETING_0;
    } else {
        out->message = TDT_LINE_FIRST_SAME_TOWN;
    }
}
CLEAN_AS(func_ov051_02260fd8, TaxiDriverTalk_Line)

/* func_ov051_02261008 (vtable slot 0x1c, a message's tag 1/11 to 1/15 handing 0 to 4): with 0
 * the taxi's rain ends. */
void TaxiDriverTalk_OnTag(int talk, int value)
{
    (void) talk;
    if (value == 0) {
        Taxi_StopRain();
    }
}
CLEAN_AS(func_ov051_02261008, TaxiDriverTalk_OnTag)

/* func_ov051_0226101c: its talk scene told through its vtable slot 0x08 and given its owner. */
void TaxiDriverTalk_Begin(TaxiDriverTalk *talk, TaxiDriver *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + TDT_SLOT_08);
    ((void (*)(TaxiDriverTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov051_0226101c, TaxiDriverTalk_Begin)

/* func_ov051_02261038 (slot 0x04): its destructor, then the scene freed. */
void *TaxiDriverTalk_Delete(void *talk)
{
    *(const u8 **) talk = data_ov051_02261804;
    SceneBase_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov051_02261038, TaxiDriverTalk_Delete)

/* func_ov051_02261058 (slot 0x00): the scene base's destructor. */
TaxiDriverTalk *TaxiDriverTalk_Destruct(TaxiDriverTalk *talk)
{
    talk->base.vtable = data_ov051_02261804;
    SceneBase_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov051_02261058, TaxiDriverTalk_Destruct)

/* func_ov051_02261070: the constructor: a scene base given this class's vtable. */
void *TaxiDriverTalk_Construct(void *talk)
{
    SceneBase_Construct(talk);
    *(const u8 **) talk = data_ov051_02261804;
    return talk;
}
CLEAN_AS(func_ov051_02261070, TaxiDriverTalk_Construct)
