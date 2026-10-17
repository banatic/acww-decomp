/* The owl's talk scene (owl_talk.h): its class's constructor and destructors, the line it
 * starts with, the player's answers and the work done after a command. */
#include "owl_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/block_021d27ac.h"
#include "main/day_events.h"
#include "main/game_variables.h"
#include "main/message_receiver.h"
#include "main/museum_record.h"
#include "main/obj_020d9ff8.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/scene_command.h"
#include "main/session.h"
#include "main/start_kind.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/villager_part.h"
#include "main/villager_part_entry.h"

/* The vtable of its class. */
extern const u8 data_ov047_02262c14[];
/* The null member pointer. */
extern const MemberPointer __ptmf_null;
/* Its message files: "sp_npc_owl", "sp_etc_sequence4" and "sp_npc_drama1". */
extern const char data_ov047_02262fc0[];
extern const char data_ov047_02262fcc[];
extern const char data_ov047_02262fe0[];
/* The line of "sp_npc_drama1" for each dated event of kind 1 and its part, six parts a row. */
extern const u8 data_ov047_02262818[];
#define OWL_TALK_DRAMA_PARTS 6
/* The state block (state_block.h) and the museum's record (museum_record.h). */
extern u32 data_021dc7a8[];
extern MuseumRecord data_021f38f8;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

/* The tests of the items the pockets offer (the game's functions, owl_donation.h). */
extern u16 func_ov047_02261ae8(u16 *item, int state);
extern int func_ov047_02261c00(u16 *item, int state);

/* The handlers of the player's answers, by line; each table is a function-local static the
 * compiler fills from the constants on the first call (bit 0 of its guard says it was). */
typedef struct OwlTalkAnswer {
    s32 line;
    MemberPointer handler; /* void (talk, int answer) */
} OwlTalkAnswer;
static_assert(sizeof(OwlTalkAnswer) == 0xc, "an answer's handler");

#define OWL_TALK_ANSWERS 17
extern OwlTalkAnswer data_ov047_02262d50[OWL_TALK_ANSWERS];
extern u32 data_ov047_02263000;
extern const MemberPointer data_ov047_022629d0, data_ov047_022629c8, data_ov047_022629b0, data_ov047_022629b8,
    data_ov047_02262a28, data_ov047_02262ac8, data_ov047_02262a20, data_ov047_02262998, data_ov047_02262a00,
    data_ov047_02262968, data_ov047_02262a88, data_ov047_02262980, data_ov047_022629c0, data_ov047_02262a38,
    data_ov047_022629a0, data_ov047_02262990, data_ov047_02262a98;

/* The two kinds of answers: to its own lines and to a dated event's. */
extern MemberPointer data_ov047_02263010[2];
extern u32 data_ov047_0226300c;
extern const MemberPointer data_ov047_022629f0, data_ov047_02262988;

/* The work after a command, by OWL_TALK_AFTER_*. */
extern MemberPointer data_ov047_02263020[OWL_TALK_AFTERS];
extern u32 data_ov047_02263008;
extern const MemberPointer data_ov047_02262b58, data_ov047_02262b50, data_ov047_02262b48, data_ov047_02262b40,
    data_ov047_02262b38;

#define OWL_TALK_NO_SLOT (-1)
#define OWL_TALK_NO_ITEM 0xfff1
#define OWL_TALK_NO_LINE 0xff

/* The vtable slot of the scene that resets it (OwlTalk_Reset). */
#define OWL_TALK_SLOT_RESET 0x08

/* The game variable (bank 0) that, when set, makes it act as when linked. */
#define OWL_TALK_VARIABLE 0x4a
/* The dated events it tells: kind 1. */
#define OWL_TALK_EVENT_KIND 1
/* The code a villager's errand to it accepts (VillagerPartEntry_Accepts). */
#define OWL_TALK_ERRAND_CODE 0xd00c
/* The flag of the block 0x021d27ac set once it has said its greeting in the museum. */
#define OWL_TALK_GREETED_FLAG 9
/* The state block's flag set once an item was given to the museum. */
#define OWL_TALK_FLAG_GIVEN 0xc
/* The current player's flag set once it has had a fossil assessed. */
#define OWL_TALK_FLAG_ASSESSED 0x35

/* The screen of the pockets (SceneCommand_RequestScreen) and the mode of its tests. */
#define OWL_TALK_SCREEN_POCKETS 0
#define OWL_TALK_POCKET_ARG 0xd

/* The menu's choices (OwlTalk_OnMenu). */
#define OWL_TALK_MENU_GIVE 0
#define OWL_TALK_MENU_ASSESS 1
#define OWL_TALK_MENU_2 2
#define OWL_TALK_MENU_PROGRESS 3
#define OWL_TALK_MENU_4 4

/* The share of the museum's record given (20.12 percent) its lines change at: 30 and 70. */
#define OWL_TALK_PERCENT_FEW 0x1e000
#define OWL_TALK_PERCENT_HALF 0x46000

static TalkObject *owl_talk_object(OwlTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* The line shown. */
static u8 owl_talk_shown(const OwlTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The talk shows `line` of "sp_npc_owl". */
static void owl_talk_say(OwlTalk *talk, s32 line)
{
    u8 message = (u8) line;
    TalkObject_SetMessage(owl_talk_object(talk), &message, data_ov047_02262fc0);
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int owl_talk_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, OWL_TALK_VARIABLE) != 0;
}

static int owl_talk_given_flag(void)
{
    return StateBlock_TestFlag(data_021dc7a8, OWL_TALK_FLAG_GIVEN);
}

/* The answer picked in the talk's menu of choices. */
static unsigned int owl_talk_answer(OwlTalk *talk)
{
    return TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
}

static int owl_talk_greeted(void)
{
    return Block021d27ac_TestFlag((u32 *) (void *) Block021d27ac_Get(), OWL_TALK_GREETED_FLAG);
}

static void owl_talk_set_greeted(void)
{
    Block021d27ac_SetFlag((u32 *) (void *) Block021d27ac_Get(), OWL_TALK_GREETED_FLAG);
}

/* ---- The class */

/* func_ov047_02261958 (vtable slot 0x04): its destructor, then the scene freed. */
void *OwlTalk_DestructDelete(void *talk)
{
    *(const u8 **) talk = data_ov047_02262c14;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov047_02261958, OwlTalk_DestructDelete)

/* func_ov047_02261978 (vtable slot 0x00): the destructor of the scene class it derives from. */
void *OwlTalk_Destruct(OwlTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov047_02262c14;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov047_02261978, OwlTalk_Destruct)

/* func_ov047_02261990: the constructor: a scene of class 0x020d9ff8 given this class's vtable,
 * with no item handed over. */
OwlTalk *OwlTalk_Construct(OwlTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov047_02262c14;
    talk->item = OWL_TALK_NO_ITEM;
    return talk;
}
CLEAN_AS(func_ov047_02261990, OwlTalk_Construct)

/* func_ov047_02261908 (vtable slot 0x08): the scene base's reset (SceneBase_Reset); no pocket,
 * no item and no work after a command. */
void OwlTalk_Reset(OwlTalk *talk)
{
    SceneBase_Reset(&talk->base);
    talk->slot = OWL_TALK_NO_SLOT;
    talk->item = OWL_TALK_NO_ITEM;
    MemberPointer none = __ptmf_null;
    talk->after = none;
    talk->next = none;
}
CLEAN_AS(func_ov047_02261908, OwlTalk_Reset)

/* func_ov047_022618cc: the scene reset through its vtable slot 0x08 and given its owner; no
 * dated event's line shown, no pocket, no assessing and no item. */
void OwlTalk_Begin(OwlTalk *talk, Owl *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + OWL_TALK_SLOT_RESET);
    ((void (*)(OwlTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->drama = 0;
    talk->slot = OWL_TALK_NO_SLOT;
    talk->assessing = 0;
    talk->item = OWL_TALK_NO_ITEM;
}
CLEAN_AS(func_ov047_022618cc, OwlTalk_Begin)

/* ---- The line it starts with */

/* func_ov047_022616b4 (vtable slot 0x78, the line to say):
 * - when a game is being started anew: line 8 of "sp_etc_sequence4";
 * - else of "sp_npc_owl" unless said: unlinked (without the game variable 0x4a), when the
 *   current player has a villager's errand to it (its entry accepts the code 0xd00c), line 0xe6
 *   (0xe5 when it was asleep);
 * - when no dated event of kind 1 was told since it started, none is being told, unlinked, and
 *   the player has one today: its line by event and part (data_ov047_02262818) of
 *   "sp_npc_drama1", noted as told and being told;
 * - else no dated event is being told; then, by whether it greeted the player already in the
 *   museum (the flag 9 of the block 0x021d27ac, set by the greeting) and whether it was asleep:
 *     not the host:     4/5 asleep/awake at the greeting, else 6/7;
 *     the greeting:     0/1 asleep/awake when the museum is complete, else 8/9, and it is no
 *                       longer taken as woken;
 *     again:            3/2 asleep/awake when the museum is complete, else 0xa/0xb; asleep it is
 *                       no longer taken as woken.
 * QUIRK: the table has six parts a row though an event has up to seven; a seventh part reads the
 * next row's first line. */
void OwlTalk_Line(OwlTalk *talk, OwlTalkStart *out)
{
    Owl *owner;
    u16 code;
    u8 event;

    if (StartKind_IsSet()) {
        out->name = data_ov047_02262fcc;
        out->message = 8;
        return;
    }
    out->name = data_ov047_02262fc0;
    VillagerPart *part = (VillagerPart *) (void *) PlayerRecord_VillagerPart(PlayerRecords_Current());
    VillagerPartEntry *errand = (VillagerPartEntry *) (void *) VillagerPart_Object94(part);
    NetSession *session = data_020ccf94;
    owner = talk->owner;

    if (!owl_talk_linked_or_variable(session)) {
        code = OWL_TALK_ERRAND_CODE;
        if (VillagerPartEntry_Accepts(errand, &code)) {
            out->message = owner->asleep == 0 ? 0xe6 : 0xe5;
            return;
        }
    }
    if (owner->drama_told == 0 && talk->drama != 1 && !owl_talk_linked_or_variable(session) &&
        TalkChecks_TodaysEventOfKind((int) (uintptr_t) owner, &event, OWL_TALK_EVENT_KIND)) {
        out->name = data_ov047_02262fe0;
        out->message = data_ov047_02262818[DAY_EVENT_INDEX(event) * OWL_TALK_DRAMA_PARTS + DAY_EVENT_PART(event)];
        talk->drama = 1;
        owner->drama_told = 1;
        return;
    }
    talk->drama = 0;

    if (!TalkChecks_IsHostOrAlone()) {
        if (!owl_talk_greeted()) {
            out->message = owner->asleep != 0 ? 4 : 5;
        } else {
            out->message = owner->asleep != 0 ? 6 : 7;
        }
        owl_talk_set_greeted();
        return;
    }
    if (!owl_talk_greeted()) {
        if (MuseumRecord_Complete(&data_021f38f8)) {
            out->message = owner->asleep != 0 ? 0 : 1;
        } else {
            out->message = owner->asleep != 0 ? 8 : 9;
        }
        owner->asleep = 0;
        owl_talk_set_greeted();
        return;
    }
    if (MuseumRecord_Complete(&data_021f38f8)) {
        if (owner->asleep != 0) {
            out->message = 3;
            owner->asleep = 0;
        } else {
            out->message = 2;
        }
    } else {
        if (owner->asleep != 0) {
            out->message = 0xa;
            owner->asleep = 0;
        } else {
            out->message = 0xb;
        }
    }
}
CLEAN_AS(func_ov047_022616b4, OwlTalk_Line)

/* ---- The player's answers */

/* func_ov047_02260b14 (vtable slot 0x18, the player's answer): unless a game is being started
 * anew, the answer goes to OwlTalk_OnDramaAnswer while a dated event is told, else to
 * OwlTalk_OnPlainAnswer, with `arg`.
 * QUIRK: the current player's villager part is fetched and not used. */
void OwlTalk_OnAnswer(OwlTalk *talk, int arg)
{
    static const MemberPointer *const kinds[2] = {
        &data_ov047_022629f0, /* OwlTalk_OnPlainAnswer */
        &data_ov047_02262988, /* OwlTalk_OnDramaAnswer */
    };

    if (StartKind_IsSet()) {
        return;
    }
    MemberTable_InitOnce(&data_ov047_0226300c, data_ov047_02263010, kinds, 2);
    PlayerRecord_VillagerPart(PlayerRecords_Current());
    const MemberPointer *handler = &data_ov047_02263010[talk->drama == 1 ? 1 : 0];
    void *self = MemberPointer_Object(handler, talk);
    ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(handler, self))(self, arg);
}
CLEAN_AS(_ZN18Obj_ov047_02262c1419func_ov047_02260b14Ei, OwlTalk_OnAnswer)

/* func_ov047_022608f8: an answer to its own lines: no line to go on with, then each handler of
 * the line shown is called with the answer picked; the talk shows the line set, if any. The line
 * is read again for each entry. */
void OwlTalk_OnPlainAnswer(OwlTalk *talk, int unused)
{
    static const MemberPointer *const handlers[OWL_TALK_ANSWERS] = {
        &data_ov047_022629d0, /* 0x0c: OwlTalk_OnMenu */
        &data_ov047_022629c8, /* 0x0e: OwlTalk_OnAnswer0e */
        &data_ov047_022629b0, /* 0x1e: OwlTalk_OnAnswer1e */
        &data_ov047_022629b8, /* 0x20: OwlTalk_OnAnswer20 */
        &data_ov047_02262a28, /* 0x21: OwlTalk_OnAnswer21 */
        &data_ov047_02262ac8, /* 0x23: OwlTalk_OnAnswer23 */
        &data_ov047_02262a20, /* 0x27: OwlTalk_OnAnswer27 */
        &data_ov047_02262998, /* 0x44: OwlTalk_OnMenu */
        &data_ov047_02262a00, /* 0x45: OwlTalk_OnMenu */
        &data_ov047_02262968, /* 0x46: OwlTalk_OnMenu */
        &data_ov047_02262a88, /* 0x47: OwlTalk_OnMenu */
        &data_ov047_02262980, /* 0x48: OwlTalk_OnMenu */
        &data_ov047_022629c0, /* 0x6b: OwlTalk_OnAnswer6b */
        &data_ov047_02262a38, /* 0xe5: OwlTalk_OnAnswerErrand */
        &data_ov047_022629a0, /* 0xe6: OwlTalk_OnAnswerErrand */
        &data_ov047_02262990, /* 0xe9: OwlTalk_OnMenu */
        &data_ov047_02262a98, /* 0xea: OwlTalk_OnMenu */
    };
    (void) unused;

    int answer = (int) owl_talk_answer(talk);
    talk->next_line = OWL_TALK_NO_LINE;
    {
        u32 flags = data_ov047_02263000;
        if ((flags & 1) == 0) {
            for (int i = 0; i < OWL_TALK_ANSWERS; i++) {
                data_ov047_02262d50[i].handler = *handlers[i];
            }
            data_ov047_02263000 = flags | 1;
        }
    }
    for (u32 i = 0; i < OWL_TALK_ANSWERS; i++) {
        const OwlTalkAnswer *entry = &data_ov047_02262d50[i];
        if (entry->line == owl_talk_shown(talk)) {
            void *self = MemberPointer_Object(&entry->handler, talk);
            ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(&entry->handler, self))(self, answer);
        }
    }
    if (talk->next_line != OWL_TALK_NO_LINE) {
        owl_talk_say(talk, talk->next_line);
    }
}
CLEAN_AS(func_ov047_022608f8, OwlTalk_OnPlainAnswer)

/* func_ov047_02260a88: an answer to a dated event's line (lines 0 to 0x15 only): with any answer
 * but the first, line 0x47 (0x48 before any item was given to the museum) and no dated event
 * is being told any longer; with the first, the player's dated event of today (of kind 1) is
 * marked as reached. */
void OwlTalk_OnDramaAnswer(OwlTalk *talk, int unused)
{
    u8 event;
    (void) unused;

    if (owl_talk_shown(talk) > 0x15) {
        return;
    }
    unsigned int answer = owl_talk_answer(talk);
    talk->next_line = OWL_TALK_NO_LINE;
    if (answer != 0) {
        talk->next_line = owl_talk_given_flag() ? 0x47 : 0x48;
        talk->drama = 0;
        owl_talk_say(talk, talk->next_line);
        return;
    }
    if (!TalkChecks_TodaysEventOfKind((int) (uintptr_t) talk->owner, &event, OWL_TALK_EVENT_KIND)) {
        return;
    }
    TalkChecks_MarkDayEvent((int) (uintptr_t) talk->owner, &event);
}
CLEAN_AS(func_ov047_02260a88, OwlTalk_OnDramaAnswer)

/* func_ov047_0226063c (lines 0xe5 and 0xe6, the errand): the first answer opens the pockets
 * offering the items 0x155f and 0x1560 (the mode 0xd) and the errand's item is taken after;
 * another goes on with line 0xea (0xe9 before any item was given to the museum). */
void OwlTalk_OnAnswerErrand(OwlTalk *talk, int answer)
{
    if (answer == 0) {
        SceneCommandScene *scene = (SceneCommandScene *) (void *) talk;
        SceneCommand_SetPocketPredicate(scene, (PocketPredicate) (void (*)(void)) func_ov047_02261ae8, OWL_TALK_POCKET_ARG, 0);
        SceneCommand_RequestScreen(scene, OWL_TALK_SCREEN_POCKETS);
        OwlTalk_SetAfter(talk, OWL_TALK_AFTER_TAKE_ERRAND);
    } else if (owl_talk_given_flag()) {
        talk->next_line = 0xea;
    } else {
        talk->next_line = 0xe9;
    }
}
CLEAN_AS(func_ov047_0226063c, OwlTalk_OnAnswerErrand)

/* func_ov047_02260688 (line 0x27): the first answer goes on with line 0x14 (whose end opens the pockets for a gift), another
 * with 0x28. */
void OwlTalk_OnAnswer27(OwlTalk *talk, int answer)
{
    talk->next_line = answer == 0 ? 0x14 : 0x28;
}
CLEAN_AS(func_ov047_02260688, OwlTalk_OnAnswer27)

/* func_ov047_0226069c (line 0x23): another answer than the first goes on with line 0x24; the
 * first with 0x40 when this console is not the host, 0x41 linked (or with the game variable
 * 0x4a set), else 0x14. */
void OwlTalk_OnAnswer23(OwlTalk *talk, int answer)
{
    if (answer != 0) {
        talk->next_line = 0x24;
    } else if (!TalkChecks_IsHostOrAlone()) {
        talk->next_line = 0x40;
    } else if (owl_talk_linked_or_variable(data_020ccf94)) {
        talk->next_line = 0x41;
    } else {
        talk->next_line = 0x14;
    }
}
CLEAN_AS(func_ov047_0226069c, OwlTalk_OnAnswer23)

/* func_ov047_022606f0 (line 0x21): the first answer goes on with line 0x19 when the current
 * player has had a fossil assessed before, else 0x4b; another with 0x15. */
void OwlTalk_OnAnswer21(OwlTalk *talk, int answer)
{
    if (answer != 0) {
        talk->next_line = 0x15;
    } else if (PlayerRecord_TestFlag(PlayerRecords_Current(), OWL_TALK_FLAG_ASSESSED) == 0) {
        talk->next_line = 0x4b;
    } else {
        talk->next_line = 0x19;
    }
}
CLEAN_AS(func_ov047_022606f0, OwlTalk_OnAnswer21)

/* func_ov047_02260724 (line 0x20): the first answer goes on with line 0x16 when the pockets
 * hold a fossil to assess (item 0x1549), else 0x18; another with 0x3e. */
void OwlTalk_OnAnswer20(OwlTalk *talk, int answer)
{
    if (answer != 0) {
        talk->next_line = 0x3e;
    } else if (Pockets_Select(func_ov047_02261c00) == 0) {
        talk->next_line = 0x18;
    } else {
        talk->next_line = 0x16;
    }
}
CLEAN_AS(func_ov047_02260724, OwlTalk_OnAnswer20)

/* func_ov047_02260758 (line 0x1e): the first answer goes on with line 0x2c, another with 0x1f. */
void OwlTalk_OnAnswer1e(OwlTalk *talk, int answer)
{
    talk->next_line = answer == 0 ? 0x2c : 0x1f;
}
CLEAN_AS(func_ov047_02260758, OwlTalk_OnAnswer1e)

/* func_ov047_0226076c (line 0x6b): the first answer goes on with line 0x14 (whose end opens the pockets for a gift), another
 * with 0x28. */
void OwlTalk_OnAnswer6b(OwlTalk *talk, int answer)
{
    talk->next_line = answer == 0 ? 0x14 : 0x28;
}
CLEAN_AS(func_ov047_0226076c, OwlTalk_OnAnswer6b)

/* func_ov047_02260780 (line 0x0e): the first answer goes on with line 0x14 (whose end opens the pockets for a gift). */
void OwlTalk_OnAnswer0e(OwlTalk *talk, int answer)
{
    if (answer == 0) {
        talk->next_line = 0x14;
    }
}
CLEAN_AS(func_ov047_02260780, OwlTalk_OnAnswer0e)

/* func_ov047_0226078c (the menu: lines 0x0c, 0x44 to 0x48, 0xe9 and 0xea): once an item was given
 * to the museum, the menu's third choice does what the fifth did and the next two move up one.
 * By the choice:
 * - give: not assessing; line 0x40 when this console is not the host, else 0x41 linked (or with
 *   the game variable 0x4a set), else 0x14 (whose end opens the pockets for a gift);
 * - assess: not assessing; line 0x18 when the pockets hold no fossil to assess (item 0x1549),
 *   else assessing and 0x17 (the first time for the current player) or 0x16;
 * - 2: line 0x4a linked (or with the game variable 0x4a set), else 0xd;
 * - how far the museum is: line 0x10 when nothing was given, 0x11 up to 30 percent, 0x12 up to
 *   70, 0x49 when the museum is complete, else 0x13;
 * - 4: line 0x3f (whose end opens the screen of mode 0x41, then tells how far the museum is). */
void OwlTalk_OnMenu(OwlTalk *talk, int choice)
{
    if (owl_talk_given_flag()) {
        if (choice == OWL_TALK_MENU_2) {
            choice = OWL_TALK_MENU_4;
        } else if (choice > OWL_TALK_MENU_2) {
            choice--;
        }
    }
    switch (choice) {
        case OWL_TALK_MENU_GIVE:
            talk->assessing = 0;
            if (!TalkChecks_IsHostOrAlone()) {
                talk->next_line = 0x40;
            } else if (owl_talk_linked_or_variable(data_020ccf94)) {
                talk->next_line = 0x41;
            } else {
                talk->next_line = 0x14;
            }
            break;
        case OWL_TALK_MENU_ASSESS: {
            talk->assessing = 0;
            u8 *record = PlayerRecords_Current();
            if (Pockets_Select(func_ov047_02261c00) == 0) {
                talk->next_line = 0x18;
            } else if (PlayerRecord_TestFlag(record, OWL_TALK_FLAG_ASSESSED) == 0) {
                talk->assessing = 1;
                talk->next_line = 0x17;
            } else {
                talk->assessing = 1;
                talk->next_line = 0x16;
            }
            break;
        }
        case OWL_TALK_MENU_2:
            if (owl_talk_linked_or_variable(data_020ccf94)) {
                talk->next_line = 0x4a;
            } else {
                talk->next_line = 0xd;
            }
            break;
        case OWL_TALK_MENU_PROGRESS: {
            MuseumRecord *record = &data_021f38f8;
            int percent = MuseumRecord_PercentGiven(record);
            talk->next_line = 0x13;
            if (percent == 0) {
                talk->next_line = 0x10;
            } else if (percent <= OWL_TALK_PERCENT_FEW) {
                talk->next_line = 0x11;
            } else if (percent <= OWL_TALK_PERCENT_HALF) {
                talk->next_line = 0x12;
            } else if (MuseumRecord_Complete(record)) {
                talk->next_line = 0x49;
            }
            break;
        }
        case OWL_TALK_MENU_4:
            talk->next_line = 0x3f;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov047_0226078c, OwlTalk_OnMenu)

/* ---- The work after a command */

/* func_ov047_02261f94: into `out` the work `after` (OWL_TALK_AFTER_*), from the table filled on
 * the first call.
 * REQUIRES: `after` is 0 to 4 (the table is not bounded). */
void OwlTalk_AfterAt(OwlTalk *talk, MemberPointer *out, int after)
{
    static const MemberPointer *const afters[OWL_TALK_AFTERS] = {
        &data_ov047_02262b58, /* OwlTalk_TakeOffered */
        &data_ov047_02262b50, /* OwlTalk_TakeFossil */
        &data_ov047_02262b48, /* OwlTalk_TakeErrand */
        &data_ov047_02262b40, /* OwlTalk_SayProgress */
        &data_ov047_02262b38, /* OwlTalk_NextLine */
    };
    (void) talk;

    MemberTable_InitOnce(&data_ov047_02263008, data_ov047_02263020, afters, OWL_TALK_AFTERS);
    *out = data_ov047_02263020[after];
}
CLEAN_AS(func_ov047_02261f94, OwlTalk_AfterAt)

/* func_ov047_02261f84: the work done once the command of the scene ends. */
void OwlTalk_SetAfter(OwlTalk *talk, int after)
{
    OwlTalk_AfterAt(talk, &talk->after, after);
}
CLEAN_AS(func_ov047_02261f84, OwlTalk_SetAfter)

/* func_ov047_02261f74: the work done once the command after that ends. */
void OwlTalk_SetNext(OwlTalk *talk, int after)
{
    OwlTalk_AfterAt(talk, &talk->next, after);
}
CLEAN_AS(func_ov047_02261f74, OwlTalk_SetNext)

/* func_ov047_02262014 (vtable slot 0x84, a command of the scene ended): the work set, if any, is
 * done and dropped; the next one, if any, becomes the work set. */
void OwlTalk_RunAfter(OwlTalk *talk)
{
    if (talk->after.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->after, talk);
    MemberPointer none = __ptmf_null;
    talk->after = none;
    if (talk->next.function != 0) {
        talk->after = talk->next;
        talk->next = none;
    }
}
CLEAN_AS(func_ov047_02262014, OwlTalk_RunAfter)
