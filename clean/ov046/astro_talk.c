/* The talk scene of overlay 46's character (astro_talk.h). */
#include "astro_talk.h"

#include <stdint.h>

#include "astro.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/constellations.h"
#include "main/game_variables.h"
#include "main/group_params.h"
#include "main/main_random.h"
#include "main/message_reader.h"
#include "main/message_receiver.h"
#include "main/message_texts.h"
#include "main/obj_020d9ff8.h"
#include "main/player_records.h"
#include "main/scene_command.h"
#include "main/session.h"
#include "main/start_kind.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "autoload_2/heap.h"

static_assert(offsetof(AstroTalk, topic) == 0xb0 && offsetof(AstroTalk, after_screen) == 0xb8, "AstroTalk");
static_assert(offsetof(AstroTalk, cursor) == 0xc4 && offsetof(AstroTalk, listed) == 0xc8, "AstroTalk");
static_assert(sizeof(AstroTalk) == 0xe0, "AstroTalk");

/* The session. */
extern NetSession *data_020ccf94;

/* "sp_npc_astro", the archive of its lines; "st_general", whose messages 0x19 and 0x1a are put
 * before an hour; and "sp_etc_sequence4". */
extern const char data_ov046_02261fe8[];
extern const char data_ov046_02262420[];
extern const char data_ov046_0226242c[];

/* The class's vtable. */
extern const u8 data_ov046_0226204c[];

/* The talk scene's vtable slots it calls. */
#define ASTRO_TALK_SLOT_RESET 2
#define ASTRO_TALK_SLOT_LIST 0x22 /* 0x88: AstroTalk_ListConstellations */

/* The game variable tested with the session's link (game_variables.h). */
#define ASTRO_TALK_VARIABLE 0x4a

/* The parts of the talk a line's tags read (TalkObject_SetPart, TalkObject_LoadPart). */
#define ASTRO_TALK_PART_NAME_SCREEN 0 /* the constellation's name, after a screen */
#define ASTRO_TALK_PART_MONTH 2
#define ASTRO_TALK_PART_DAY 3
#define ASTRO_TALK_PART_HOUR 4
#define ASTRO_TALK_PART_MINUTE 5
#define ASTRO_TALK_PART_NAME 6     /* the constellation picked */
#define ASTRO_TALK_PART_NAME_NEW 7 /* the new constellation */
#define ASTRO_TALK_PART_HALF_DAY 8 /* "st_general"'s message 0x19 or 0x1a */

/* The messages of "st_general" before an hour of 0 to 12, and of 13 to 23. */
#define ASTRO_TALK_HALF_DAY_FIRST 0x19
#define ASTRO_TALK_HALF_DAY_SECOND 0x1a
#define ASTRO_TALK_HALF_DAY_HOURS 12

/* The screen modes the talk opens (SceneCommand_SetScreenMode) and their screens. */
#define ASTRO_TALK_MODE_12 0x12
#define ASTRO_TALK_MODE_2D 0x2d
#define ASTRO_TALK_MODE_2E 0x2e /* with a constellation's number */
#define ASTRO_TALK_SCREEN_2 2
#define ASTRO_TALK_SCREEN_3 3

/* What runs after a screen (AstroTalk_SetAfterScreen). */
#define ASTRO_TALK_AFTER_2D 0
#define ASTRO_TALK_AFTER_2E_NEW 1
#define ASTRO_TALK_AFTER_12_NEW 2
#define ASTRO_TALK_AFTER_2E_CHANGED 3
#define ASTRO_TALK_AFTER_12_CHANGED 4
#define ASTRO_TALK_AFTERS 5

/* The menu message of the line between a constellation's name and the rest of its answer, and
 * the messages of the list's last answer (to go on, or to stop when none is left). */
#define ASTRO_TALK_ANSWER_SUFFIX 0x7d
#define ASTRO_TALK_ANSWER_MORE 0xf
#define ASTRO_TALK_ANSWER_STOP 0x10
#define ASTRO_TALK_ANSWER_SELECT2 1 /* the select file "select2" */

/* The daily bit of its first talk of the day (talk_checks.h). */
#define ASTRO_TALK_DAILY_BIT 2

/* ---- Helpers */

static TalkObject *astro_talk_object(const AstroTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

/* The number of the line shown (the receiver's message). */
static u8 astro_talk_shown(const AstroTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static SceneCommandScene *astro_talk_command(AstroTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The talk scene's vtable slot `slot` called with no argument. */
static void astro_talk_slot(AstroTalk *talk, int slot)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(AstroTalk *))(uintptr_t) vtable[slot])(talk);
}

/* Whether the session is linked or game variable 0x4a is set (in this order, the second only
 * asked when the first is not). */
static int astro_talk_shared(void)
{
    return Session_IsLinked(data_020ccf94) || *(const s16 *) GameVariables_Slot(0, ASTRO_TALK_VARIABLE) != 0;
}

/* Whether a constellation is kept. */
static int astro_talk_any_kept(void)
{
    return Constellations_CountFree() < CONSTELLATIONS_COUNT;
}

/* The list starts over: all kept constellations to list, from the first. */
static void astro_talk_restart_list(AstroTalk *talk)
{
    talk->remaining = (u8) (CONSTELLATIONS_COUNT - Constellations_CountFree());
    talk->cursor = 0;
}

/* Line `line` of "sp_npc_astro" shown by `object`. */
static void astro_talk_say(TalkObject *object, u8 line)
{
    TalkObject_SetMessage(object, &line, data_ov046_02261fe8);
}

/* Constellation `number`'s name put in part `part`. */
static void astro_talk_put_name(AstroTalk *talk, int part, int number)
{
    ConstellationsLabel label;
    ConstellationsLabel_Construct(&label);
    Constellations_NameToText(&label, number);
    TalkObject_SetPart(astro_talk_object(talk), part, (TextBase *) (void *) &label);
    ConstellationsLabel_Destruct(&label);
}

/* The time constellation `number` is in view put in the parts: the month, the day and the
 * minute, then, with `hour_first`, the hour and the half of the day, else the other way round.
 * QUIRK: the hour 12 takes message 0x19 like the hours 0 to 11; only 13 to 23 take 0x1a, less 12. */
static void astro_talk_put_time(AstroTalk *talk, TalkObject *object, int number, int hour_first)
{
    struct {
        u8 message;
        u8 unk_01[3];
        DateTime when;
    } time;
    int hour;
    int half;

    time.when = (DateTime){0};
    Constellations_TimeInView(&time.when, number);
    SceneBase_PutNumberAlt(&talk->scene, (void *) (uintptr_t) time.when.month, ASTRO_TALK_PART_MONTH);
    SceneBase_PutNumber(&talk->scene, time.when.day, ASTRO_TALK_PART_DAY);
    SceneBase_PutValue(&talk->scene, time.when.minute, ASTRO_TALK_PART_MINUTE, 2, 0, 0);
    hour = time.when.hour;
    half = ASTRO_TALK_HALF_DAY_FIRST;
    if (hour > ASTRO_TALK_HALF_DAY_HOURS) {
        half = ASTRO_TALK_HALF_DAY_SECOND;
        hour -= ASTRO_TALK_HALF_DAY_HOURS;
    }
    time.message = (u8) half;
    if (hour_first) {
        SceneBase_PutValue(&talk->scene, hour, ASTRO_TALK_PART_HOUR, 2, 0, 0);
        TalkObject_LoadPart(object, ASTRO_TALK_PART_HALF_DAY, &time.message, (unsigned int) (uintptr_t) data_ov046_02262420);
    } else {
        TalkObject_LoadPart(object, ASTRO_TALK_PART_HALF_DAY, &time.message, (unsigned int) (uintptr_t) data_ov046_02262420);
        SceneBase_PutValue(&talk->scene, hour, ASTRO_TALK_PART_HOUR, 2, 0, 0);
    }
}

/* ---- The handlers of the answers */

/* func_ov046_02260644 (line 0x38): answer 0 goes to line 0x3b; another to the menu. */
void AstroTalk_OnAnswer38(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        talk->next_line = 0x3b;
    } else {
        talk->next_line = AstroTalk_MenuLine(talk);
    }
}
CLEAN_AS(func_ov046_02260644, AstroTalk_OnAnswer38)

/* func_ov046_02260664 (line 0x35): answer 0 goes to line 0x30; answer 1 lists the
 * constellations to tell when they are in view (line 0x15); another goes to line 0x16. */
void AstroTalk_OnAnswer35(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        talk->next_line = 0x30;
    } else if (answer == 1) {
        talk->purpose = ASTRO_TALK_PURPOSE_TIME;
        talk->next_line = 0x15;
    } else {
        talk->next_line = 0x16;
    }
}
CLEAN_AS(func_ov046_02260664, AstroTalk_OnAnswer35)

/* func_ov046_0226068c (line 0x24): the list starts over; answer 0 lists the constellations to
 * open screen 0x2e on (line 0x1e); another goes to line 0x25 while a constellation is kept,
 * else to the menu. */
void AstroTalk_OnAnswer24(AstroTalk *talk, int answer)
{
    astro_talk_restart_list(talk);
    if (answer == 0) {
        talk->purpose = ASTRO_TALK_PURPOSE_SCREEN;
        talk->next_line = 0x1e;
    } else if (astro_talk_any_kept()) {
        talk->next_line = 0x25;
    } else {
        talk->next_line = AstroTalk_MenuLine(talk);
    }
}
CLEAN_AS(func_ov046_0226068c, AstroTalk_OnAnswer24)

/* func_ov046_022606e0 (line 0x20): answer 0 goes to line 7, another to line 0xc. */
void AstroTalk_OnAnswer20(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        talk->next_line = 7;
    } else {
        talk->next_line = 0xc;
    }
}
CLEAN_AS(func_ov046_022606e0, AstroTalk_OnAnswer20)

/* func_ov046_022606f4 (lines 0x10, 0x13, 0x26 and 0x27, while the session is shared): answer 0
 * goes to line 0x35 while a constellation is kept, else to line 0x30; another to line 2. */
void AstroTalk_OnAnswerMenuShared(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        if (astro_talk_any_kept()) {
            talk->next_line = 0x35;
        } else {
            talk->next_line = 0x30;
        }
    } else {
        talk->next_line = 2;
    }
}
CLEAN_AS(func_ov046_022606f4, AstroTalk_OnAnswerMenuShared)

/* func_ov046_02260720 (lines 0x18, 0x25, 0x2a and 0x2b): the list starts over; answer 0 goes to
 * line 0x3e when no slot is free, else to line 7 (a new one is made); answer 1 lists the
 * constellations to open screen 0x2e on (line 0x1e); another goes to line 0xc. */
void AstroTalk_OnAnswerMake(AstroTalk *talk, int answer)
{
    astro_talk_restart_list(talk);
    if (answer == 0) {
        if (Constellations_CountFree() == 0) {
            talk->next_line = 0x3e;
        } else {
            talk->next_line = 7;
        }
    } else if (answer == 1) {
        talk->purpose = ASTRO_TALK_PURPOSE_SCREEN;
        talk->next_line = 0x1e;
    } else {
        talk->next_line = 0xc;
    }
}
CLEAN_AS(func_ov046_02260720, AstroTalk_OnAnswerMake)

/* func_ov046_0226077c (line 0x19, asked before a removal): answer 0 removes the constellation
 * picked, its name put in part 6 first (when one is), then the list starts over and line 0x1b;
 * another goes to the menu. */
void AstroTalk_OnAnswerRemove(AstroTalk *talk, int answer)
{
    talk->cursor = 0;
    if (answer == 0) {
        if (talk->constellation >= 0) {
            ConstellationsLabel label;
            ConstellationsLabel_Construct(&label);
            Constellations_NameToText(&label, talk->constellation);
            TalkObject_SetPart(astro_talk_object(talk), ASTRO_TALK_PART_NAME, (TextBase *) (void *) &label);
            Constellations_Remove(talk->constellation);
            ConstellationsLabel_Destruct(&label);
        }
        astro_talk_restart_list(talk);
        talk->next_line = 0x1b;
    } else {
        talk->next_line = AstroTalk_MenuLine(talk);
    }
}
CLEAN_AS(func_ov046_0226077c, AstroTalk_OnAnswerRemove)

/* func_ov046_022607f0 (lines 0x14 and 0x28, a constellation kept): the list starts over;
 * answer 0 goes to line 0x18 while a constellation is kept, else to line 7; answer 1 to line
 * 0x35; answer 2 lists the constellations to remove (line 0x1f); another goes to line 2. */
void AstroTalk_OnAnswerMenuWithKept(AstroTalk *talk, int answer)
{
    astro_talk_restart_list(talk);
    if (answer == 0) {
        if (astro_talk_any_kept()) {
            talk->next_line = 0x18;
        } else {
            talk->next_line = 7;
        }
    } else if (answer == 1) {
        talk->next_line = 0x35;
    } else if (answer == 2) {
        astro_talk_restart_list(talk);
        talk->next_line = 0x1f;
        talk->purpose = ASTRO_TALK_PURPOSE_REMOVE;
    } else {
        talk->next_line = 2;
    }
}
CLEAN_AS(func_ov046_022607f0, AstroTalk_OnAnswerMenuWithKept)

/* func_ov046_0226086c (lines 1 and 0x29, none kept): answer 0 goes to line 0x18 while a
 * constellation is kept, else to line 7; answer 1 to line 0x30; another to line 2. */
void AstroTalk_OnAnswerMenuNoneKept(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        if (astro_talk_any_kept()) {
            talk->next_line = 0x18;
        } else {
            talk->next_line = 7;
        }
    } else if (answer == 1) {
        talk->next_line = 0x30;
    } else {
        talk->next_line = 2;
    }
}
CLEAN_AS(func_ov046_0226086c, AstroTalk_OnAnswerMenuNoneKept)

/* func_ov046_022608a4 (line 0x23): answer 0 removes the constellation worked on (when one is),
 * the list starts over and line 0x21; another goes to line 9. */
void AstroTalk_OnAnswerDiscard(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        if (talk->constellation >= 0) {
            Constellations_Remove(talk->constellation);
        }
        astro_talk_restart_list(talk);
        talk->next_line = 0x21;
    } else {
        talk->next_line = 9;
    }
}
CLEAN_AS(func_ov046_022608a4, AstroTalk_OnAnswerDiscard)

/* func_ov046_022608e4 (line 0x31): answer 0 goes to line 7; another to line 0x2a while a
 * constellation is kept, else to the menu. */
void AstroTalk_OnAnswer31(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        talk->next_line = 7;
    } else if (astro_talk_any_kept()) {
        talk->next_line = 0x2a;
    } else {
        talk->next_line = AstroTalk_MenuLine(talk);
    }
}
CLEAN_AS(func_ov046_022608e4, AstroTalk_OnAnswer31)

/* func_ov046_02260914 (the lists, lines 0x15, 0x1e, 0x1f and their next pages 0x3f to 0x41):
 * the constellation of answer `answer` becomes the one worked on. When it is one, its name is
 * put in part 6 and, by the list's purpose: REMOVE asks to confirm (line 0x19); TIME tells when
 * it is in view (line 0x17, the hour after its half of the day); SCREEN opens screen mode 0x2e
 * on it (AstroTalk_AfterScreen2eChanged after the screen); the purpose is then REMOVE.
 * When the last answer was picked: with none left to list, the menu (its line by the session
 * and whether one is kept), or for TIME and SCREEN with one kept line 0x16 or 0x1d, and the
 * purpose REMOVE; else the list's next page (0x15, 0x1e and 0x1f go to 0x3f, 0x3f to 0x40, 0x40
 * to 0x41).
 * REQUIRES: `answer` is below 5 (the list has at most five answers). */
void AstroTalk_OnPick(AstroTalk *talk, int answer)
{
    TalkObject *object = astro_talk_object(talk);
    ConstellationsLabel label;

    talk->constellation = talk->listed[answer];
    if (talk->constellation < 0) {
        if (talk->remaining == 0) {
            talk->next_line = AstroTalk_MenuLine(talk);
            if (talk->purpose == ASTRO_TALK_PURPOSE_TIME || talk->purpose == ASTRO_TALK_PURPOSE_SCREEN) {
                if (astro_talk_any_kept()) {
                    talk->next_line = talk->purpose == ASTRO_TALK_PURPOSE_TIME ? 0x16 : 0x1d;
                }
            }
            talk->purpose = ASTRO_TALK_PURPOSE_REMOVE;
            return;
        }
        switch (astro_talk_shown(talk)) {
            case 0x15:
            case 0x1e:
            case 0x1f:
                talk->next_line = 0x3f;
                break;
            case 0x3f:
                talk->next_line = 0x40;
                break;
            case 0x40:
                talk->next_line = 0x41;
                break;
            default:
                break;
        }
        return;
    }
    ConstellationsLabel_Construct(&label);
    Constellations_NameToText(&label, talk->constellation);
    TalkObject_SetPart(object, ASTRO_TALK_PART_NAME, (TextBase *) (void *) &label);
    if (talk->purpose == ASTRO_TALK_PURPOSE_REMOVE) {
        talk->next_line = 0x19;
        talk->cursor = 0;
    } else if (talk->purpose == ASTRO_TALK_PURPOSE_TIME) {
        astro_talk_put_time(talk, object, talk->constellation, 0);
        talk->next_line = 0x17;
    } else if (talk->purpose == ASTRO_TALK_PURPOSE_SCREEN) {
        SceneCommand_SetScreenModeArg(astro_talk_command(talk), ASTRO_TALK_MODE_2E, (u8) talk->constellation, 0);
        SceneCommand_RequestScreen(astro_talk_command(talk), ASTRO_TALK_SCREEN_3);
        AstroTalk_SetAfterScreen(talk, ASTRO_TALK_AFTER_2E_CHANGED);
    }
    talk->purpose = ASTRO_TALK_PURPOSE_REMOVE;
    ConstellationsLabel_Destruct(&label);
}
CLEAN_AS(func_ov046_02260914, AstroTalk_OnPick)

/* func_ov046_02260aa8 (line 8): answer 0 goes to line 9, another to line 0x23. */
void AstroTalk_OnAnswer08(AstroTalk *talk, int answer)
{
    if (answer == 0) {
        talk->next_line = 9;
    } else {
        talk->next_line = 0x23;
    }
}
CLEAN_AS(func_ov046_02260aa8, AstroTalk_OnAnswer08)

/* A handler of the lines: the line it handles and its function, a member pointer the table is
 * filled with on the first call (bit 0 of the guard). */
typedef struct AstroTalkHandler {
    s32 line;
    MemberPointer handler;
} AstroTalkHandler;

#define ASTRO_TALK_ANSWERS 26
#define ASTRO_TALK_SHOWN 29
extern AstroTalkHandler data_ov046_0226218c[ASTRO_TALK_ANSWERS];
extern u32 data_ov046_02262458;
extern AstroTalkHandler data_ov046_022622c4[ASTRO_TALK_SHOWN];
extern u32 data_ov046_02262454;
extern const MemberPointer data_ov046_02261dc0, data_ov046_02261dc8, data_ov046_02261dd0, data_ov046_02261dd8,
    data_ov046_02261de0, data_ov046_02261de8, data_ov046_02261df0, data_ov046_02261df8, data_ov046_02261e00,
    data_ov046_02261e08, data_ov046_02261e10, data_ov046_02261e18, data_ov046_02261e20, data_ov046_02261e28,
    data_ov046_02261e30, data_ov046_02261e38, data_ov046_02261e40, data_ov046_02261e48, data_ov046_02261e50,
    data_ov046_02261e58, data_ov046_02261e60, data_ov046_02261e68, data_ov046_02261e70, data_ov046_02261e78,
    data_ov046_02261e80, data_ov046_02261e88, data_ov046_02261e90, data_ov046_02261e98, data_ov046_02261ea0,
    data_ov046_02261eb0, data_ov046_02261eb8, data_ov046_02261ec0, data_ov046_02261ec8, data_ov046_02261ed0,
    data_ov046_02261ed8, data_ov046_02261ee0, data_ov046_02261ee8, data_ov046_02261ef0, data_ov046_02261ef8,
    data_ov046_02261f00, data_ov046_02261f08, data_ov046_02261f10, data_ov046_02261f18, data_ov046_02261f20,
    data_ov046_02261f30, data_ov046_02261f38, data_ov046_02261f40, data_ov046_02261f48, data_ov046_02261f50,
    data_ov046_02261f60, data_ov046_02261f70, data_ov046_02261f78, data_ov046_02261f80, data_ov046_02261f88,
    data_ov046_02261fa0;

/* The table's functions filled in from `constants`, once. */
static void astro_talk_fill(u32 *guard, AstroTalkHandler *table, const MemberPointer *const *constants, int count)
{
    u32 flags = *guard;
    if ((flags & 1) == 0) {
        for (int i = 0; i < count; i++) {
            table[i].handler = *constants[i];
        }
        *guard = flags | 1;
    }
}

/* The line `next_line` names shown, when it names one. */
static void astro_talk_show_next(AstroTalk *talk)
{
    if (talk->next_line != ASTRO_TALK_NO_LINE) {
        astro_talk_say(astro_talk_object(talk), (u8) talk->next_line);
    }
}

/* func_ov046_02260abc (slot 0x18, the player's answer): with no line next yet, each handler of
 * the line shown is called with the answer picked; then the line next is shown. The line shown
 * is read again for each entry of the table. */
void AstroTalk_OnAnswer(AstroTalk *talk)
{
    static const MemberPointer *const handlers[ASTRO_TALK_ANSWERS] = {
        &data_ov046_02261de0, /* 0x01: AstroTalk_OnAnswerMenuNoneKept */
        &data_ov046_02261e50, /* 0x08: AstroTalk_OnAnswer08 */
        &data_ov046_02261dd8, /* 0x10: AstroTalk_OnAnswerMenuShared */
        &data_ov046_02261e40, /* 0x13: AstroTalk_OnAnswerMenuShared */
        &data_ov046_02261e38, /* 0x14: AstroTalk_OnAnswerMenuWithKept */
        &data_ov046_02261e30, /* 0x15: AstroTalk_OnPick */
        &data_ov046_02261dd0, /* 0x18: AstroTalk_OnAnswerMake */
        &data_ov046_02261e20, /* 0x19: AstroTalk_OnAnswerRemove */
        &data_ov046_02261e18, /* 0x1e: AstroTalk_OnPick */
        &data_ov046_02261e00, /* 0x1f: AstroTalk_OnPick */
        &data_ov046_02261e10, /* 0x20: AstroTalk_OnAnswer20 */
        &data_ov046_02261e70, /* 0x23: AstroTalk_OnAnswerDiscard */
        &data_ov046_02261e88, /* 0x24: AstroTalk_OnAnswer24 */
        &data_ov046_02261ee8, /* 0x25: AstroTalk_OnAnswerMake */
        &data_ov046_02261f78, /* 0x26: AstroTalk_OnAnswerMenuShared */
        &data_ov046_02261f60, /* 0x27: AstroTalk_OnAnswerMenuShared */
        &data_ov046_02261dc0, /* 0x28: AstroTalk_OnAnswerMenuWithKept */
        &data_ov046_02261dc8, /* 0x29: AstroTalk_OnAnswerMenuNoneKept */
        &data_ov046_02261de8, /* 0x2a: AstroTalk_OnAnswerMake */
        &data_ov046_02261df8, /* 0x2b: AstroTalk_OnAnswerMake */
        &data_ov046_02261eb0, /* 0x31: AstroTalk_OnAnswer31 */
        &data_ov046_02261e90, /* 0x35: AstroTalk_OnAnswer35 */
        &data_ov046_02261f80, /* 0x38: AstroTalk_OnAnswer38 */
        &data_ov046_02261e60, /* 0x3f: AstroTalk_OnPick */
        &data_ov046_02261df0, /* 0x40: AstroTalk_OnPick */
        &data_ov046_02261e08, /* 0x41: AstroTalk_OnPick */
    };
    int answer = (int) TalkAnswers_Picked((TalkAnswers *) (uintptr_t) SceneBase_TalkChoices(&talk->scene));

    talk->next_line = ASTRO_TALK_NO_LINE;
    astro_talk_fill(&data_ov046_02262458, data_ov046_0226218c, handlers, ASTRO_TALK_ANSWERS);
    for (u32 i = 0; i < ASTRO_TALK_ANSWERS; i++) {
        const AstroTalkHandler *entry = &data_ov046_0226218c[i];
        if (entry->line == astro_talk_shown(talk)) {
            void *self = MemberPointer_Object(&entry->handler, talk);
            ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(&entry->handler, self))(self, answer);
        }
    }
    astro_talk_show_next(talk);
}
CLEAN_AS(_ZN18Obj_ov046_0226204c19func_ov046_02260abcEv, AstroTalk_OnAnswer)

/* ---- The handlers of the lines shown */

/* Screen mode `mode` with screen 2, then `after` once it ends. */
static void astro_talk_open_screen(AstroTalk *talk, char mode, int after)
{
    SceneCommand_SetScreenMode(astro_talk_command(talk), mode, 0);
    SceneCommand_RequestScreen(astro_talk_command(talk), ASTRO_TALK_SCREEN_2);
    AstroTalk_SetAfterScreen(talk, after);
}

/* func_ov046_02260cd0 (line 0x30): screen mode 0x2d, then AstroTalk_AfterScreen2d. */
void AstroTalk_OpenScreen2d(AstroTalk *talk)
{
    astro_talk_open_screen(talk, ASTRO_TALK_MODE_2D, ASTRO_TALK_AFTER_2D);
}
CLEAN_AS(func_ov046_02260cd0, AstroTalk_OpenScreen2d)

/* func_ov046_02260cf4 (line 0x3b): screen mode 0x12, then AstroTalk_AfterScreen12Changed. */
void AstroTalk_OpenScreen12ForChanged(AstroTalk *talk)
{
    astro_talk_open_screen(talk, ASTRO_TALK_MODE_12, ASTRO_TALK_AFTER_12_CHANGED);
}
CLEAN_AS(func_ov046_02260cf4, AstroTalk_OpenScreen12ForChanged)

/* func_ov046_02260d18 (lines 5 and 9): screen mode 0x12, then AstroTalk_AfterScreen12New. */
void AstroTalk_OpenScreen12ForNew(AstroTalk *talk)
{
    astro_talk_open_screen(talk, ASTRO_TALK_MODE_12, ASTRO_TALK_AFTER_12_NEW);
}
CLEAN_AS(func_ov046_02260d18, AstroTalk_OpenScreen12ForNew)

/* func_ov046_02260d3c (the lists): the constellations listed (the scene's vtable slot 0x88,
 * AstroTalk_ListConstellations). */
void AstroTalk_List(AstroTalk *talk)
{
    astro_talk_slot(talk, ASTRO_TALK_SLOT_LIST);
}
CLEAN_AS(func_ov046_02260d3c, AstroTalk_List)

/* func_ov046_02260d50 (lines 0xc, 0x12, 0x16, 0x17, 0x1a, 0x1b, 0x1d, 0x21, 0x32, 0x33, 0x3d and
 * 0x3e): the menu next. */
void AstroTalk_ToMenu(AstroTalk *talk)
{
    talk->next_line = AstroTalk_MenuLine(talk);
}
CLEAN_AS(func_ov046_02260d50, AstroTalk_ToMenu)

/* func_ov046_02260d64 (line 0xb): a number below 101 drawn: below 70 the menu next, below 85
 * line 0x32, else line 0x33. */
void AstroTalk_RandomLine(AstroTalk *talk)
{
    int roll = (int) MainRandom_Below(101);
    if (roll < 70) {
        talk->next_line = AstroTalk_MenuLine(talk);
    } else if (roll < 85) {
        talk->next_line = 0x32;
    } else {
        talk->next_line = 0x33;
    }
}
CLEAN_AS(func_ov046_02260d64, AstroTalk_RandomLine)

/* func_ov046_02260d98 (line 7): a free slot becomes the constellation worked on; screen mode
 * 0x2e is opened on it with screen 3, then AstroTalk_AfterScreen2eNew; without one, line 0x3e
 * next. */
void AstroTalk_MakeInFreeSlot(AstroTalk *talk)
{
    talk->constellation = Constellations_FreeSlot();
    if (talk->constellation >= 0) {
        SceneCommand_SetScreenModeArg(astro_talk_command(talk), ASTRO_TALK_MODE_2E, (u8) talk->constellation, 0);
        SceneCommand_RequestScreen(astro_talk_command(talk), ASTRO_TALK_SCREEN_3);
        AstroTalk_SetAfterScreen(talk, ASTRO_TALK_AFTER_2E_NEW);
    } else {
        talk->next_line = 0x3e;
    }
}
CLEAN_AS(func_ov046_02260d98, AstroTalk_MakeInFreeSlot)

/* The line of a player who called it over: with the session shared, line 0x13 while a
 * constellation is kept, else 0x10; alone, line 0x14 or line 1. */
static u8 astro_talk_called_line(void)
{
    if (astro_talk_shared()) {
        return astro_talk_any_kept() ? 0x13 : 0x10;
    }
    return astro_talk_any_kept() ? 0x14 : 1;
}

/* func_ov046_02260ddc (line 4): with the session shared, line 0x13 while a constellation is
 * kept, else 0x10; alone, line 0x14 or line 1. */
void AstroTalk_CalledLine(AstroTalk *talk)
{
    talk->next_line = astro_talk_called_line();
}
CLEAN_AS(func_ov046_02260ddc, AstroTalk_CalledLine)

/* func_ov046_02260e34 (the greetings, lines 0 and 0x2c to 0x2e): the new constellations: with
 * none, line 0x2f with the session shared, else 0x11; with one, its name in part 7 and line
 * 0x39; with more, line 0x3a. Then (when there was one) none is new any more.
 * QUIRK: the new constellations are taken twice (Constellations_TakeNew unmarks those no longer
 * kept each time); the second answer picks the line. */
void AstroTalk_TellNew(AstroTalk *talk)
{
    int number = 0;
    int found = Constellations_TakeNew(&number);

    if (found == 0) {
        talk->next_line = astro_talk_shared() ? 0x2f : 0x11;
        return;
    }
    if (Constellations_TakeNew(&number) == 1) {
        astro_talk_put_name(talk, ASTRO_TALK_PART_NAME_NEW, number);
        talk->next_line = 0x39;
    } else {
        talk->next_line = 0x3a;
    }
    Constellations_ClearNew();
}
CLEAN_AS(func_ov046_02260e34, AstroTalk_TellNew)

/* func_ov046_02260ebc (slot 0x14, a line shown): unless the game started in a special way
 * (StartKind_IsSet), with no line next yet, each handler of the line shown is called; then the
 * line next is shown. The line shown is read again for each entry of the table.
 * QUIRK: the current player's record is fetched and not used. */
void AstroTalk_OnLineShown(AstroTalk *talk)
{
    static const MemberPointer *const handlers[ASTRO_TALK_SHOWN] = {
        &data_ov046_02261f50, /* 0x00: AstroTalk_TellNew */
        &data_ov046_02261e58, /* 0x04: AstroTalk_CalledLine */
        &data_ov046_02261f40, /* 0x05: AstroTalk_OpenScreen12ForNew */
        &data_ov046_02261f38, /* 0x07: AstroTalk_MakeInFreeSlot */
        &data_ov046_02261f30, /* 0x09: AstroTalk_OpenScreen12ForNew */
        &data_ov046_02261e48, /* 0x0b: AstroTalk_RandomLine */
        &data_ov046_02261f20, /* 0x0c: AstroTalk_ToMenu */
        &data_ov046_02261f18, /* 0x12: AstroTalk_ToMenu */
        &data_ov046_02261f10, /* 0x15: AstroTalk_List */
        &data_ov046_02261f08, /* 0x16: AstroTalk_ToMenu */
        &data_ov046_02261f00, /* 0x17: AstroTalk_ToMenu */
        &data_ov046_02261ef8, /* 0x1a: AstroTalk_ToMenu */
        &data_ov046_02261ef0, /* 0x1b: AstroTalk_ToMenu */
        &data_ov046_02261e28, /* 0x1d: AstroTalk_ToMenu */
        &data_ov046_02261ee0, /* 0x1e: AstroTalk_List */
        &data_ov046_02261ed8, /* 0x1f: AstroTalk_List */
        &data_ov046_02261ed0, /* 0x21: AstroTalk_ToMenu */
        &data_ov046_02261ec8, /* 0x2c: AstroTalk_TellNew */
        &data_ov046_02261ec0, /* 0x2d: AstroTalk_TellNew */
        &data_ov046_02261eb8, /* 0x2e: AstroTalk_TellNew */
        &data_ov046_02261e68, /* 0x30: AstroTalk_OpenScreen2d */
        &data_ov046_02261f88, /* 0x32: AstroTalk_ToMenu */
        &data_ov046_02261ea0, /* 0x33: AstroTalk_ToMenu */
        &data_ov046_02261e98, /* 0x3b: AstroTalk_OpenScreen12ForChanged */
        &data_ov046_02261e78, /* 0x3d: AstroTalk_ToMenu */
        &data_ov046_02261e80, /* 0x3e: AstroTalk_ToMenu */
        &data_ov046_02261fa0, /* 0x3f: AstroTalk_List */
        &data_ov046_02261f48, /* 0x40: AstroTalk_List */
        &data_ov046_02261f70, /* 0x41: AstroTalk_List */
    };

    if (StartKind_IsSet()) {
        return;
    }
    PlayerRecords_Current();
    talk->next_line = ASTRO_TALK_NO_LINE;
    astro_talk_fill(&data_ov046_02262454, data_ov046_022622c4, handlers, ASTRO_TALK_SHOWN);
    for (u32 i = 0; i < ASTRO_TALK_SHOWN; i++) {
        const AstroTalkHandler *entry = &data_ov046_022622c4[i];
        if (entry->line == astro_talk_shown(talk)) {
            MemberPointer_CallVoid(&entry->handler, talk);
        }
    }
    astro_talk_show_next(talk);
}
CLEAN_AS(_ZN18Obj_ov046_0226204c19func_ov046_02260ebcEv, AstroTalk_OnLineShown)

/* ---- The menu, the first line and the topic */

/* func_ov046_022610fc: the list starts over, and the menu's line: with the session shared,
 * line 0x27 while a constellation is kept, else 0x26; alone, line 0x28 or 0x29. */
int AstroTalk_MenuLine(AstroTalk *talk)
{
    astro_talk_restart_list(talk);
    if (astro_talk_shared()) {
        return astro_talk_any_kept() ? 0x27 : 0x26;
    }
    return astro_talk_any_kept() ? 0x28 : 0x29;
}
CLEAN_AS(func_ov046_022610fc, AstroTalk_MenuLine)

/* The first lines of the topics 0-4, all of "sp_npc_astro": 0, 0x2c, 0x2d, 0x2e and 4. */
extern const AstroTalkLine data_ov046_02261c84[ASTRO_TALK_TOPICS];

/* func_ov046_02261158 (slot 0x78): the line it starts with. When the game started in a special
 * way (StartKind_IsSet), message 0x14 of "sp_etc_sequence4". Else topic PENDING becomes FIRST
 * or AGAIN by the daily bit 2 (set by the test), each with BUSY after its animation; topic
 * CALLED when not after its animation is the line of a player who called it over (as
 * AstroTalk_CalledLine); the other topics take their line from the table. A topic above 4
 * leaves `line` as it was. */
void AstroTalk_Line(AstroTalk *talk, AstroTalkLine *line)
{
    s32 topic;

    if (StartKind_IsSet()) {
        line->name = data_ov046_0226242c;
        line->message = 0x14;
        return;
    }
    if ((s32) talk->topic == ASTRO_TALK_TOPIC_PENDING) {
        if (TalkChecks_TestSetDailyBit(ASTRO_TALK_DAILY_BIT, 1) == 0) {
            talk->topic = talk->owner->was_animating ? ASTRO_TALK_TOPIC_FIRST_BUSY : ASTRO_TALK_TOPIC_FIRST;
        } else {
            talk->topic = talk->owner->was_animating ? ASTRO_TALK_TOPIC_AGAIN_BUSY : ASTRO_TALK_TOPIC_AGAIN;
        }
    }
    topic = (s32) talk->topic;
    if (topic == ASTRO_TALK_TOPIC_CALLED && talk->owner->was_animating == 0) {
        line->message = astro_talk_called_line();
        line->name = data_ov046_02261fe8;
        return;
    }
    if (topic >= 0 && topic < ASTRO_TALK_TOPICS) {
        line->message = data_ov046_02261c84[topic].message;
        line->name = data_ov046_02261c84[topic].name;
    }
}
CLEAN_AS(func_ov046_02261158, AstroTalk_Line)

/* func_ov046_02261268 */
void AstroTalk_SetTopic(AstroTalk *talk, unsigned long topic)
{
    talk->topic = (u32) topic;
}
CLEAN_AS(func_ov046_02261268, AstroTalk_SetTopic)

/* func_ov046_02261270: the scene reset (its vtable slot 2), given its owner, and the list
 * started over. */
void AstroTalk_SetOwner(AstroTalk *talk, Astro *owner)
{
    astro_talk_slot(talk, ASTRO_TALK_SLOT_RESET);
    talk->owner = owner;
    talk->cursor = 0;
    talk->remaining = (u8) (CONSTELLATIONS_COUNT - Constellations_CountFree());
}
CLEAN_AS(func_ov046_02261270, AstroTalk_SetOwner)

/* ---- Its life */

extern const MemberPointer __ptmf_null;

/* func_ov046_022612a0 (slot 0x08): the scene base reset, nothing to run after a screen, and a
 * free slot (or -1) as the constellation worked on. */
void AstroTalk_Reset(AstroTalk *talk)
{
    SceneBase_Reset(&talk->scene);
    talk->after_screen = __ptmf_null;
    talk->constellation = Constellations_FreeSlot();
}
CLEAN_AS(func_ov046_022612a0, AstroTalk_Reset)

/* func_ov046_022612cc (slot 0x04): destructed, then freed. */
AstroTalk *AstroTalk_DestructDelete(AstroTalk *talk)
{
    talk->scene.vtable = data_ov046_0226204c;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov046_022612cc, AstroTalk_DestructDelete)

/* func_ov046_022612ec (slot 0x00): the destructor: its class's vtable, then the base class's
 * body. */
AstroTalk *AstroTalk_Destruct(AstroTalk *talk)
{
    talk->scene.vtable = data_ov046_0226204c;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov046_022612ec, AstroTalk_Destruct)

/* func_ov046_02261304: the base class constructed, then its class's vtable. */
AstroTalk *AstroTalk_Construct(AstroTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->scene.vtable = data_ov046_0226204c;
    return talk;
}
CLEAN_AS(func_ov046_02261304, AstroTalk_Construct)

/* ---- What runs after a screen */

/* The line after screen mode 0x12: when the group's parameters can be opened, line 5, or with
 * the screen's result 1 the constellation's name in part 0 and line `named`. Nothing when they
 * cannot. */
static void astro_talk_after_naming(AstroTalk *talk, u8 named)
{
    TalkObject *object = astro_talk_object(talk);
    u8 line = 5;

    if (!GroupParams_CanOpen()) {
        return;
    }
    if (GroupParams_C4CIs1()) {
        line = named;
        astro_talk_put_name(talk, ASTRO_TALK_PART_NAME_SCREEN, talk->constellation);
    }
    astro_talk_say(object, line);
}

/* func_ov046_0226131c (after screen mode 0x12 on a changed constellation): line 5, or with the
 * screen's result 1 line 0x3d. */
void AstroTalk_AfterScreen12Changed(AstroTalk *talk)
{
    astro_talk_after_naming(talk, 0x3d);
}
CLEAN_AS(func_ov046_0226131c, AstroTalk_AfterScreen12Changed)

/* func_ov046_02261378 (after screen mode 0x2e on a kept constellation): with the screen's
 * result 1 line 0x38; else the list starts over and line 0x1d. */
void AstroTalk_AfterScreen2eChanged(AstroTalk *talk)
{
    TalkObject *object = astro_talk_object(talk);
    u8 line;

    if (GroupParams_C4CIs1()) {
        line = 0x38;
    } else {
        astro_talk_restart_list(talk);
        line = 0x1d;
    }
    astro_talk_say(object, line);
}
CLEAN_AS(func_ov046_02261378, AstroTalk_AfterScreen2eChanged)

/* func_ov046_022613c8 (after screen mode 0x12 on a new constellation): line 5, or with the
 * screen's result 1 line 0xb. */
void AstroTalk_AfterScreen12New(AstroTalk *talk)
{
    astro_talk_after_naming(talk, 0xb);
}
CLEAN_AS(func_ov046_022613c8, AstroTalk_AfterScreen12New)

/* func_ov046_02261424 (after screen mode 0x2e in a free slot): with the screen's result 1 the
 * time the new constellation is in view (the hour before its half of the day) and line 8; else
 * the constellation removed, the list started over, and line 0xc. */
void AstroTalk_AfterScreen2eNew(AstroTalk *talk)
{
    TalkObject *object = astro_talk_object(talk);
    u8 line = 0xc;

    if (GroupParams_C4CIs1()) {
        astro_talk_put_time(talk, object, talk->constellation, 1);
        line = 8;
    } else {
        Constellations_Remove(talk->constellation);
        astro_talk_restart_list(talk);
    }
    astro_talk_say(object, line);
}
CLEAN_AS(func_ov046_02261424, AstroTalk_AfterScreen2eNew)

/* func_ov046_022614e8 (after screen mode 0x2d): line 0x12. */
void AstroTalk_AfterScreen2d(AstroTalk *talk)
{
    astro_talk_say(astro_talk_object(talk), 0x12);
}
CLEAN_AS(func_ov046_022614e8, AstroTalk_AfterScreen2d)

/* What runs after a screen, filled from their constants on the first call (bit 0 of the
 * guard). */
extern MemberPointer data_ov046_02262464[ASTRO_TALK_AFTERS];
extern u32 data_ov046_0226245c;
extern const MemberPointer data_ov046_02261f98, data_ov046_02261f90, data_ov046_02261f28, data_ov046_02261f58,
    data_ov046_02261f68;

/* func_ov046_02261508: `after` (ASTRO_TALK_AFTER_*) to run once the screen's command ends.
 * REQUIRES: `after` is below 5 (the game's are). */
void AstroTalk_SetAfterScreen(AstroTalk *talk, int after)
{
    static const MemberPointer *const afters[ASTRO_TALK_AFTERS] = {
        &data_ov046_02261f98, /* AstroTalk_AfterScreen2d */
        &data_ov046_02261f90, /* AstroTalk_AfterScreen2eNew */
        &data_ov046_02261f28, /* AstroTalk_AfterScreen12New */
        &data_ov046_02261f58, /* AstroTalk_AfterScreen2eChanged */
        &data_ov046_02261f68, /* AstroTalk_AfterScreen12Changed */
    };
    MemberTable_InitOnce(&data_ov046_0226245c, data_ov046_02262464, afters, ASTRO_TALK_AFTERS);
    talk->after_screen = data_ov046_02262464[after];
}
CLEAN_AS(func_ov046_02261508, AstroTalk_SetAfterScreen)

/* func_ov046_02261590 (slot 0x84, a command of the scene ended): what was left to run after the
 * screen, once. */
void AstroTalk_RunAfterScreen(AstroTalk *talk)
{
    if (talk->after_screen.function != 0) {
        MemberPointer_CallVoid(&talk->after_screen, talk);
        talk->after_screen = __ptmf_null;
    }
}
CLEAN_AS(func_ov046_02261590, AstroTalk_RunAfterScreen)

/* func_ov046_022615d4 (slot 0x88): the talk's answers: from `cursor`, up to four kept
 * constellations still to list, each answer its name followed by menu message 0x7d, noted in
 * `listed` (the others -1); then a last answer, message 0xf (more to list) or 0x10 (none
 * left). The cursor is left at the constellation after the last looked at (at most 15), and
 * the answers are opened. */
void AstroTalk_ListConstellations(AstroTalk *talk)
{
    TalkAnswers *answers = TalkObject_Answers(astro_talk_object(talk));
    ConstellationsLabel name;
    ConstellationsLabel suffix;
    MessageText256 text;
    TalkAnswer *answer;
    u8 message;
    int count = 0;
    int number;

    TalkAnswers_Clear(answers);
    ConstellationsLabel_Construct(&name);
    ConstellationsLabel_Construct(&suffix);
    message = ASTRO_TALK_ANSWER_SUFFIX;
    MessageReader_LoadMenuMessage(&suffix, &message, NULL);
    for (int i = 0; i < ASTRO_TALK_LIST_ENTRIES; i++) {
        talk->listed[i] = -1;
    }
    number = talk->cursor;
    while (number < CONSTELLATIONS_COUNT && count < ASTRO_TALK_LIST_ANSWERS && talk->remaining != 0) {
        if (Constellations_NameToText(&name, number) != 0) {
            MessageText256_Construct(&text);
            answer = TalkAnswers_Answer(answers, count);
            TextBase_AppendText(&text, (TextBase *) (void *) &name);
            TextBase_AppendText(&text, (TextBase *) (void *) &suffix);
            TextBase_Copy(TalkAnswers_Text(answer), (TextBase *) (void *) &text);
            talk->listed[count] = number;
            count++;
            talk->remaining--;
            MessageText256_Destruct(&text);
        }
        number++;
    }
    talk->cursor = (u8) number;
    if (talk->cursor >= CONSTELLATIONS_COUNT) {
        talk->cursor = CONSTELLATIONS_COUNT - 1;
    }
    message = talk->remaining == 0 ? ASTRO_TALK_ANSWER_STOP : ASTRO_TALK_ANSWER_MORE;
    answer = TalkAnswers_Answer(answers, count);
    TalkAnswers_SetMessage(answer, &message);
    TalkAnswers_SetFile(answer, (int) TalkAnswers_SelectFileName(ASTRO_TALK_ANSWER_SELECT2));
    TalkAnswers_LoadAnswerText(answer);
    TalkAnswers_SetCount(answers, count + 1);
    TalkAnswers_SetCancelToLast(answers);
    TalkObject_OpenChoices(astro_talk_object(talk), 1);
    ConstellationsLabel_Destruct(&suffix);
    ConstellationsLabel_Destruct(&name);
}
CLEAN_AS(func_ov046_022615d4, AstroTalk_ListConstellations)
