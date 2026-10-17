/* The post office clerk's talk scene (post_clerk_talk.h): its class, the line it starts with,
 * the menu and the other answers, the ends of lines and the steps after the screens. */
#include "post_clerk_talk.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/network.h"
#include "clean.h"
#include "main/block_021d27ac.h"
#include "main/current_pockets.h"
#include "main/global_021cfc98.h"
#include "main/group_params.h"
#include "main/house_record.h"
#include "main/item_code.h"
#include "main/item_object.h"
#include "main/library_overlay.h"
#include "main/mail.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_options.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/savings.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/session_link.h"
#include "main/start_kind.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/town_day.h"
#include "main/town_name.h"
#include "main/town_record.h"
#include "main/activity_job.h"
#include "main/villager_part.h"
#include "main/villager_part_entry.h"

static_assert(sizeof(PostClerkTalkStep) == 12, "a step's function");
static_assert(sizeof(PostClerkTalkLine) == 8, "a line");
static_assert(sizeof(PostClerkFiles) == 12, "a clerk's message files");
static_assert(sizeof(PostClerkTalk) == 0x1ac, "the talk up to the clerk's next member");
static_assert(offsetof(MessageReceiver, name) == 0x04 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The vtable of its class. */
extern const u8 data_ov054_02263004[];
/* The clerks' message files. */
extern const PostClerkFiles data_ov054_02262fac[2];
/* The steps' functions (filled at start-up by __sinit_ov054_02262a70; their flags are the
 * overlay's data). */
extern PostClerkTalkStep data_ov054_02263140[POST_CLERK_TALK_STEPS];
/* The menus: the answers' messages, their counts, and the handlers of the answers picked
 * (function-local statics, below) by menu. */
extern const u8 *const data_ov054_02262f50[POST_CLERK_TALK_MENUS];
extern const s32 data_ov054_022629b4[POST_CLERK_TALK_MENUS];
extern const s32 data_ov054_022629a0[POST_CLERK_TALK_MENUS];
extern MemberPointer *const data_ov054_02262f3c[POST_CLERK_TALK_MENUS];
/* By the counter place she serves: the line the talk starts with when nothing else is to say,
 * the line when the player keeps the errand's item, and the line after the second answer to a
 * dated event's line. */
extern const u8 data_ov054_02262974[2];
extern const u8 data_ov054_02262978[2];
extern const u8 data_ov054_02262984[2];
/* The line of each dated event of kind 0 and its part, six parts a row. */
#define POST_CLERK_TALK_DRAMA_PARTS 6
extern const u8 data_ov054_022629f8[];
/* The town-wide amounts the savings ranks start at (rank i from entry i, 1 to 20). */
#define POST_CLERK_TALK_RANKS 21
extern const s32 data_ov054_02262a18[POST_CLERK_TALK_RANKS + 1];
/* The house, the town's four players' records and the state block. */
extern HouseRecord data_021ebcd4;
extern u8 data_021dc7bc[];
extern u32 data_021dc7a8[];

/* The test of the items the pockets offer for the errand (the game's function, handed on). */
extern unsigned short func_ov054_02261850(unsigned short *r0, int r1);

/* The handlers by message file: her own, another, the sequence's; each table is a
 * function-local static the compiler fills from the constants on the first call (bit 0 of its
 * guard says it was). The answers take (talk, arg), the ends of lines too. */
#define POST_CLERK_TALK_FILE_OWN 0
#define POST_CLERK_TALK_FILE_DRAMA 1
#define POST_CLERK_TALK_FILE_SEQUENCE 2
#define POST_CLERK_TALK_FILES 3
extern MemberPointer data_ov054_0226325c[POST_CLERK_TALK_FILES];
extern u32 data_ov054_02263210;
extern const MemberPointer data_ov054_02262db8, data_ov054_02262db0, data_ov054_02262da8;
extern MemberPointer data_ov054_02263244[POST_CLERK_TALK_FILES];
extern u32 data_ov054_02263208;
extern const MemberPointer data_ov054_02262cf0, data_ov054_02262dd8, data_ov054_02262dd0;

/* The handlers of the menus' answers (void (talk)), by menu: each a function-local static with
 * its guard, filled from the constants in this order. */
extern MemberPointer data_ov054_02263294[4], data_ov054_022632b4[5], data_ov054_0226321c[2], data_ov054_0226322c[3],
    data_ov054_02263274[4];
extern u32 data_ov054_02263200, data_ov054_02263214, data_ov054_02263218, data_ov054_0226320c, data_ov054_02263204;
extern const MemberPointer data_ov054_02262e90, data_ov054_02262ec0, data_ov054_02262e18, data_ov054_02262ce0,
    data_ov054_02262df0, data_ov054_02262d00, data_ov054_02262d50, data_ov054_02262d58, data_ov054_02262d98,
    data_ov054_02262d88, data_ov054_02262e20, data_ov054_02262ec8, data_ov054_02262d30, data_ov054_02262ce8,
    data_ov054_02262d60, data_ov054_02262d68, data_ov054_02262e40, data_ov054_02262e58;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The vtable slot of the scene that resets it. */
#define POST_CLERK_TALK_SLOT_RESET 0x08

#define POST_CLERK_TALK_NO_LINE 0xff
#define POST_CLERK_TALK_NO_ITEM 0xfff1

/* The persons of the two clerks: an errand for either is one for her. */
#define POST_CLERK_TALK_DAY_PERSON 0xd006
#define POST_CLERK_TALK_NIGHT_PERSON 0xd007

/* The items the scene's motions hold up: the letters taken (0x1565) and the bells (0x149b). */
#define POST_CLERK_TALK_LETTERS_ITEM 0x1565
#define POST_CLERK_TALK_BELLS_ITEM 0x149b
/* The item handed over once (flag 0x20), and its motion's second value. */
#define POST_CLERK_TALK_GIFT_ITEM 0x1379
#define POST_CLERK_TALK_MOTION_B 5

/* The errand's items (PostClerkTalk_IsErrandItem) and the pockets' test argument. */
#define POST_CLERK_TALK_ERRAND_FIRST 0x155f
#define POST_CLERK_TALK_ERRAND_LAST 0x1560
#define POST_CLERK_TALK_ERRAND_STATE 2
#define POST_CLERK_TALK_POCKET_ARG 0xd

/* The screens (SceneCommand_RequestScreen): the pockets (0), the letters (1) and screen 2 in a
 * mode (SceneCommand_SetScreenMode). */
#define POST_CLERK_TALK_SCREEN_POCKETS 0
#define POST_CLERK_TALK_SCREEN_LETTERS 1
#define POST_CLERK_TALK_SCREEN 2
#define POST_CLERK_TALK_MODE_26 0x26
#define POST_CLERK_TALK_MODE_DATE 0x33
#define POST_CLERK_TALK_MODE_LOAN 0x34
#define POST_CLERK_TALK_MODE_TOWN_AMOUNT 0x37
#define POST_CLERK_TALK_MODE_SAVINGS 0x3b
#define POST_CLERK_TALK_MODE_3F 0x3f

/* The current player's flags (player_record.h): the loan offered (1), the line 0x1a said once
 * (4), the sequence's first talk (9), the gift handed over (0x20). */
#define POST_CLERK_TALK_FLAG_1 1
#define POST_CLERK_TALK_FLAG_4 4
#define POST_CLERK_TALK_FLAG_SEQUENCE_TALKED 9
#define POST_CLERK_TALK_FLAG_GIFT 0x20

/* Values put into the talk (SceneBase_PutValue's formats): bells, and a year. */
#define POST_CLERK_TALK_VALUE_BELLS 10
#define POST_CLERK_TALK_VALUE_YEAR 4
#define POST_CLERK_TALK_YEAR_BASE 2000
/* The savings line tells a 200th of the balance too, and a deposit of 5,000 bells or more to
 * the town-wide amount gets its own line. */
#define POST_CLERK_TALK_SAVINGS_PART 200
#define POST_CLERK_TALK_BIG_AMOUNT 5000

/* The linked game: the frames to find one, the session's start, the entries looked for (14
 * bytes, open when byte 0xd is 1, with a town name of 6 wide characters when byte 0xc is 0)
 * and the talk's part the name goes in. */
#define POST_CLERK_TALK_SEARCH_FRAMES 600
#define POST_CLERK_TALK_SESSION_MODE 2
#define POST_CLERK_TALK_SESSION_PLAYERS 2
#define POST_CLERK_TALK_ENTRY_SIZE 0xe
#define POST_CLERK_TALK_ENTRY_NAMELESS 0xc
#define POST_CLERK_TALK_ENTRY_OPEN 0xd
#define POST_CLERK_TALK_ENTRY_NAME_CHARS 6
#define POST_CLERK_TALK_PART_TOWN 8

/* Her lines named in the code (of her own file unless said). */
#define POST_CLERK_LINE_MENU 0x00         /* also 0x52, 0x53, 0x56: they end with the menu */
#define POST_CLERK_LINE_GOODBYE 0x01      /* the menu's last answer */
#define POST_CLERK_LINE_JOB_12 0x02       /* activity job 0x12 reached its step 3 */
#define POST_CLERK_LINE_NOT_POSTED 0x03   /* the letter screen closed without posting */
#define POST_CLERK_LINE_POSTED 0x05       /* letters posted */
#define POST_CLERK_LINE_POSTED_ALL 0x07   /* all posted; also the dated letter kept */
#define POST_CLERK_LINE_LINKED_START 0x08 /* linked with a slot, at the first counter place */
#define POST_CLERK_LINE_NONE_POSTED 0x09
#define POST_CLERK_LINE_DATE_SELF 0x0b  /* one letter to the player themself */
#define POST_CLERK_LINE_DATE_TAKEN 0x0c /* the date picked for it */
#define POST_CLERK_LINE_NOT_DATED 0x0e  /* not dated: back to the pockets */
#define POST_CLERK_LINE_DATED_KEPT 0x0f /* a dated letter is kept already (its date) */
#define POST_CLERK_LINE_REDATE 0x11
#define POST_CLERK_LINE_LOAN 0x12      /* the loan told; ends opening its screen */
#define POST_CLERK_LINE_LOAN_NONE 0x13 /* the loan's screen closed without paying */
#define POST_CLERK_LINE_LOAN_PAID 0x14
#define POST_CLERK_LINE_LOAN_PAID_OFF 0x15
#define POST_CLERK_LINE_SAVINGS 0x16      /* ends opening the account's screen */
#define POST_CLERK_LINE_SAVINGS_DONE 0x17 /* the balance told */
#define POST_CLERK_LINE_SAVINGS_NONE 0x18
#define POST_CLERK_LINE_LINKED_FAILED 0x37 /* no linked game found or joined */
#define POST_CLERK_LINE_GAME_FOUND 0x38
#define POST_CLERK_LINE_GAME_NAMED 0x39 /* a game found, its town's name in part 8 */
#define POST_CLERK_LINE_SESSION_ENDED 0x3a
#define POST_CLERK_LINE_JOB_1F 0x3c
#define POST_CLERK_LINE_ERRAND_TAKEN 0x50
#define POST_CLERK_LINE_ERRAND_NONE 0x51
#define POST_CLERK_LINE_ERRAND_OTHER 0x57 /* taken, though the errand was not for her */
#define POST_CLERK_LINE_MENU_AGAIN 0x52
#define POST_CLERK_LINE_ERRAND 0x5f /* a villager's errand for a clerk */
#define POST_CLERK_LINE_UNSENT 0x61 /* not all the letters were posted */
#define POST_CLERK_LINE_NO_ADDRESSEE 0x58
#define POST_CLERK_LINE_FULL_MAILBOXES 0x58 /* plus the number of full mailboxes, 1 to 3 */

/* The lines of "sp_etc_sequence4" named in the code. */
#define POST_CLERK_SEQUENCE_LINE_OPTION 0x12   /* its answers set the player's option flag */
#define POST_CLERK_SEQUENCE_LINE_TOWN 0x13     /* the number of the town's players told */
#define POST_CLERK_SEQUENCE_LINE_NEW 0x12      /* the first talk, of a new town or player */
#define POST_CLERK_SEQUENCE_LINE_FIRST 0x20    /* the first talk otherwise */
#define POST_CLERK_SEQUENCE_LINE_AGAIN 0x07    /* a later talk */
#define POST_CLERK_SEQUENCE_PLAYERS_LINE 0x22  /* plus the number of the town's players */
#define POST_CLERK_SEQUENCE_NEW_TOWN_LINE 0x02 /* after line 0x13 in a new town */
#define POST_CLERK_SEQUENCE_MODE 0x2f          /* the screen its lines open */

static TalkObject *pct_object(PostClerkTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *pct_scene(PostClerkTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The line shown. */
static u8 pct_shown(const PostClerkTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The answer picked in the scene's choices. */
static int pct_answer(PostClerkTalk *talk)
{
    return (int) TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
}

static const PostClerkFiles *pct_files(PostClerkTalk *talk)
{
    return &data_ov054_02262fac[talk->owner->clerk];
}

/* Her message file `which` (POST_CLERK_TALK_FILE_*). */
static const char *pct_file(PostClerkTalk *talk, int which)
{
    const PostClerkFiles *files = pct_files(talk);
    switch (which) {
        case POST_CLERK_TALK_FILE_DRAMA:
            return files->drama;
        case POST_CLERK_TALK_FILE_SEQUENCE:
            return files->sequence;
        default:
            return files->own;
    }
}

/* Line `line` of `file` shown. */
static void pct_say_in(PostClerkTalk *talk, u8 line, const char *file)
{
    TalkObject_SetMessage(pct_object(talk), &line, file);
}

/* Line `line` of her own file shown. */
static void pct_say(PostClerkTalk *talk, u8 line)
{
    pct_say_in(talk, line, pct_files(talk)->own);
}

/* Calls `handler` with the talk (adjusted) and `arg`. */
static void pct_call(const MemberPointer *handler, PostClerkTalk *talk, u32 arg)
{
    void *self = MemberPointer_Object(handler, talk);
    ((void (*)(void *, u32))(uintptr_t) MemberPointer_Code(handler, self))(self, arg);
}

/* Which handler of a table by file: the sequence's while a game is being started anew, else
 * her own when the talk's file is her own (its name begins as hers), else another. The C
 * library's strlen and strncmp are asked first. */
static int pct_file_kind(PostClerkTalk *talk)
{
    const char *own = pct_files(talk)->own;
    size_t length = strlen(own);
    int differs = strncmp((const char *) talk->base.receiver, own, length);
    if (StartKind_IsSet() != 0) {
        return POST_CLERK_TALK_FILE_SEQUENCE;
    }
    return differs == 0 ? POST_CLERK_TALK_FILE_OWN : POST_CLERK_TALK_FILE_DRAMA;
}

/* The screen 2 in `mode` asked for, then `step` when its command ends. */
static void pct_open(PostClerkTalk *talk, char mode, char stay_on_line, unsigned long step)
{
    SceneCommand_SetScreenMode(pct_scene(talk), mode, stay_on_line);
    SceneCommand_RequestScreen(pct_scene(talk), POST_CLERK_TALK_SCREEN);
    PostClerkTalk_SetStep(talk, step);
}

/* The scene's motion 13 or 14 holding up `item` (its first value `a`, the second 5, the third
 * 1). */
static void pct_hold_up(PostClerkTalk *talk, u16 item, u32 a)
{
    SceneCommand_RequestMotion13(pct_scene(talk), &item, a, POST_CLERK_TALK_MOTION_B, 1);
}

static void pct_hand_over(PostClerkTalk *talk, u16 item, u32 a)
{
    SceneCommand_RequestMotion14(pct_scene(talk), &item, a, POST_CLERK_TALK_MOTION_B, 1);
}

/* The talk's window freed of the spinner and let go. */
static void pct_release(TalkObject *object)
{
    TalkObject_StopSpinner(object);
    TalkObject_Release(object);
}

/* A linked game given up: the session ended, line 0x37, the talk let go, no step. */
static void pct_give_up_linked(PostClerkTalk *talk)
{
    TalkObject *object = pct_object(talk);
    PostClerkTalk_EndLinkedGame(talk);
    pct_say(talk, POST_CLERK_LINE_LINKED_FAILED);
    pct_release(object);
    PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
}

/* ---- The class */

/* func_ov054_02261f5c: the scene reset through its vtable slot 0x08 and given its owner. */
void PostClerkTalk_Begin(PostClerkTalk *talk, PostClerk *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + POST_CLERK_TALK_SLOT_RESET);
    ((void (*)(PostClerkTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov054_02261f5c, PostClerkTalk_Begin)

/* func_ov054_02261f78 (vtable slot 0x04): the destructor of the scene class it derives from,
 * then the scene freed. */
PostClerkTalk *PostClerkTalk_DestructDelete(PostClerkTalk *talk)
{
    talk->base.vtable = data_ov054_02263004;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov054_02261f78, PostClerkTalk_DestructDelete)

/* func_ov054_02261f98 (vtable slot 0x00): the destructor of the scene class it derives from. */
PostClerkTalk *PostClerkTalk_Destruct(PostClerkTalk *talk)
{
    talk->base.vtable = data_ov054_02263004;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov054_02261f98, PostClerkTalk_Destruct)

/* func_ov054_02261fb0: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
PostClerkTalk *PostClerkTalk_Construct(PostClerkTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov054_02263004;
    return talk;
}
CLEAN_AS(func_ov054_02261fb0, PostClerkTalk_Construct)

/* func_ov054_02261cc4: its step set. */
void PostClerkTalk_SetStep(PostClerkTalk *talk, unsigned long step)
{
    talk->step = (u32) step;
}
CLEAN_AS(func_ov054_02261cc4, PostClerkTalk_SetStep)

/* func_ov054_02261ccc (slot 0x84, a command of the scene ended): a step not run each step and
 * with a function runs (the step stays as it is unless it changes it).
 * REQUIRES: the step is 0 to 15. */
void PostClerkTalk_RunCommandStep(PostClerkTalk *talk)
{
    const PostClerkTalkStep *step = &data_ov054_02263140[talk->step];
    if (step->each_step != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
}
CLEAN_AS(func_ov054_02261ccc, PostClerkTalk_RunCommandStep)

/* func_ov054_02261d10 (slot 0x80, before each step of the scene): a step run each step runs,
 * when it has a function.
 * REQUIRES: the step is 0 to 15. */
void PostClerkTalk_RunEachStep(PostClerkTalk *talk)
{
    const PostClerkTalkStep *step = &data_ov054_02263140[talk->step];
    if (step->each_step != 0 && step->run.function != 0) {
        MemberPointer_CallVoid(&step->run, talk);
    }
}
CLEAN_AS(func_ov054_02261d10, PostClerkTalk_RunEachStep)

/* func_ov054_02261f44: the linked session ended; when it was, overlay 68 is switched to
 * (LibraryOverlay_Switch68). The talk is not looked at. */
void PostClerkTalk_EndLinkedGame(PostClerkTalk *talk)
{
    (void) talk;
    if (Session_End()) {
        LibraryOverlay_Switch68();
    }
}
CLEAN_AS(func_ov054_02261f44, PostClerkTalk_EndLinkedGame)

/* ---- The lines */

/* func_ov054_02261df8 (vtable slot 0x78, the line the talk starts with):
 * - unlinked while a game is being started anew, of "sp_etc_sequence4": the first talk (the
 *   current player's flag 9 clear, then set) is 0x12 in a new town or for a new player, else
 *   0x20; a later one 0x07;
 * - unlinked, with a villager's errand for either clerk (persons 0xd006 and 0xd007): 0x5f;
 * - unlinked, with today's dated event of kind 0 not told yet in this visit: its line of her
 *   dated events' file, now told;
 * - else her usual line by the counter place she serves (0x08 instead at the first place when
 *   this system has a slot in the session). */
void PostClerkTalk_Line(PostClerkTalk *talk, PostClerkTalkLine *out)
{
    PostClerk *clerk = talk->owner;
    u8 *record = PlayerRecords_Current();
    int file = POST_CLERK_TALK_FILE_OWN;
    int usual = 0;
    VillagerPartEntry *errand =
        (VillagerPartEntry *) (void *) VillagerPart_Object94((VillagerPart *) (void *) PlayerRecord_VillagerPart(record));

    if (PostClerk_IsLinked(clerk)) {
        usual = 1;
    } else if (StartKind_IsSet() != 0) {
        if (PlayerRecord_TestFlag(record, POST_CLERK_TALK_FLAG_SEQUENCE_TALKED) == 0) {
            if (StartKind_IsNewTown() != 0 || StartKind_IsNewPlayer() != 0) {
                out->message = POST_CLERK_SEQUENCE_LINE_NEW;
            } else {
                out->message = POST_CLERK_SEQUENCE_LINE_FIRST;
            }
            PlayerRecord_SetFlag(record, POST_CLERK_TALK_FLAG_SEQUENCE_TALKED);
        } else {
            out->message = POST_CLERK_SEQUENCE_LINE_AGAIN;
        }
        file = POST_CLERK_TALK_FILE_SEQUENCE;
    } else {
        u16 day = POST_CLERK_TALK_DAY_PERSON;
        u16 night = POST_CLERK_TALK_NIGHT_PERSON;
        u8 event;
        if (VillagerPartEntry_Accepts(errand, &day) != 0 || VillagerPartEntry_Accepts(errand, &night) != 0) {
            out->message = POST_CLERK_LINE_ERRAND;
        } else if (clerk->event_told == 0 && TalkChecks_TodaysEventOfKind((int) (uintptr_t) clerk, &event, 0) != 0) {
            out->message = data_ov054_022629f8[((event >> 2) & 7) * POST_CLERK_TALK_DRAMA_PARTS + ((event >> 5) & 7)];
            file = POST_CLERK_TALK_FILE_DRAMA;
            clerk->event_told = 1;
        } else {
            usual = 1;
        }
    }

    if (usual) {
        out->message = data_ov054_02262974[clerk->spot];
        file = POST_CLERK_TALK_FILE_OWN;
        if (clerk->spot == 0 && PostClerk_HasSessionSlot(clerk) != 0) {
            out->message = POST_CLERK_LINE_LINKED_START;
        }
    }
    out->name = pct_file(talk, file);
}
CLEAN_AS(func_ov054_02261df8, PostClerkTalk_Line)

/* func_ov054_02261380 (vtable slot 0x10, a line begins): at line 0x0f the date of the current
 * player's dated letter goes in (the year, 2000 on, in slot 1; the month in slot 2; the day in
 * slot 3). While a game is being started anew, at the lines 0x24 to 0x26 the names of the
 * town's other players go into the slots from 2 on. */
void PostClerkTalk_OnLineBegin(PostClerkTalk *talk)
{
    if (pct_shown(talk) == POST_CLERK_LINE_DATED_KEPT) {
        MailTime *date = MailDated_Date((MailDatedLetter *) (void *) PlayerRecord_DatedLetter(PlayerRecords_Current()));
        u8 month = date->month;
        u8 day = date->day;
        SceneBase_PutValue(&talk->base, date->year + POST_CLERK_TALK_YEAR_BASE, 1, POST_CLERK_TALK_VALUE_YEAR, 0, 0);
        SceneBase_PutNumberAlt(&talk->base, (void *) (uintptr_t) month, 2);
        SceneBase_PutNumber(&talk->base, day, 3);
    }
    if (StartKind_IsSet() == 0) {
        return;
    }
    switch (pct_shown(talk)) {
        case 0x24:
        case 0x25:
        case 0x26: {
            int slot = 2;
            for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
                if (PlayerRecords_TownExists(data_021dc7bc, i) != 0 && i != PlayerRecords_CurrentNumber()) {
                    SceneBase_PutNameAt10(&talk->base, PlayerRecord_Player(PlayerRecords_TownRecord(data_021dc7bc, i)), slot);
                    slot++;
                }
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov054_02261380, PostClerkTalk_OnLineBegin)

/* func_ov054_02261d54: the scene's motion 13 holding up the letters taken (item 0x1565), once
 * in a talk. */
void PostClerkTalk_ShowLetters(PostClerkTalk *talk)
{
    if (talk->letters_shown == 0) {
        pct_hold_up(talk, POST_CLERK_TALK_LETTERS_ITEM, 0);
        talk->letters_shown = 1;
    }
}
CLEAN_AS(func_ov054_02261d54, PostClerkTalk_ShowLetters)

/* func_ov054_02261d8c: after the letter screen, line 5 when letters were posted
 * (GroupParams_LetterFlag200), else 9. */
int PostClerkTalk_PostedLine(PostClerkTalk *talk)
{
    (void) talk;
    return GroupParams_LetterFlag200() ? POST_CLERK_LINE_POSTED : POST_CLERK_LINE_NONE_POSTED;
}
CLEAN_AS(func_ov054_02261d8c, PostClerkTalk_PostedLine)

/* func_ov054_02261da4: 0x58 plus the number of the full mailboxes (GroupParams_LetterBits6),
 * or 9 when none was full. */
u8 PostClerkTalk_FullMailboxLine(PostClerkTalk *talk)
{
    (void) talk;
    int full = GroupParams_LetterBits6();
    if (full != 0) {
        return (u8) (full + POST_CLERK_LINE_FULL_MAILBOXES);
    }
    return POST_CLERK_LINE_NONE_POSTED;
}
CLEAN_AS(func_ov054_02261da4, PostClerkTalk_FullMailboxLine)

/* func_ov054_02261dc0: 0x58 when a written letter had no addressee (GroupParams_LetterFlag8),
 * else PostClerkTalk_FullMailboxLine. */
int PostClerkTalk_NoAddresseeLine(PostClerkTalk *talk)
{
    if (GroupParams_LetterFlag8()) {
        return POST_CLERK_LINE_NO_ADDRESSEE;
    }
    return PostClerkTalk_FullMailboxLine(talk);
}
CLEAN_AS(func_ov054_02261dc0, PostClerkTalk_NoAddresseeLine)

/* func_ov054_02261ddc: 0x61 when not all the letters were posted (GroupParams_LetterFlag400),
 * else PostClerkTalk_NoAddresseeLine. */
int PostClerkTalk_UnsentLine(PostClerkTalk *talk)
{
    if (GroupParams_LetterFlag400()) {
        return POST_CLERK_LINE_UNSENT;
    }
    return PostClerkTalk_NoAddresseeLine(talk);
}
CLEAN_AS(func_ov054_02261ddc, PostClerkTalk_UnsentLine)

/* ---- The menu */

/* func_ov054_02260894 (the menu's answer 0xeb): the letter screen, then step 1. */
void PostClerkTalk_ChooseLetters(PostClerkTalk *talk)
{
    SceneCommand_RequestScreen(pct_scene(talk), POST_CLERK_TALK_SCREEN_LETTERS);
    PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_LETTERS);
}
CLEAN_AS(func_ov054_02260894, PostClerkTalk_ChooseLetters)

/* func_ov054_02260860 (the menu's answer 0x56): line 1. */
void PostClerkTalk_ChooseGoodbye(PostClerkTalk *talk)
{
    pct_say(talk, POST_CLERK_LINE_GOODBYE);
}
CLEAN_AS(func_ov054_02260860, PostClerkTalk_ChooseGoodbye)

/* func_ov054_0226083c (the menu's answer 0xd5): the screen in mode 0x26, then step 2. */
void PostClerkTalk_ChooseScreen26(PostClerkTalk *talk)
{
    pct_open(talk, POST_CLERK_TALK_MODE_26, 0, POST_CLERK_TALK_STEP_SCREEN_26);
}
CLEAN_AS(func_ov054_0226083c, PostClerkTalk_ChooseScreen26)

/* func_ov054_022607ec (the menu's answer 0xed): the house's loan in slot 4 (as bells), line
 * 0x12. */
void PostClerkTalk_ChooseLoan(PostClerkTalk *talk)
{
    SceneBase_PutValue(&talk->base, HouseRecord_Loan(&data_021ebcd4), 4, POST_CLERK_TALK_VALUE_BELLS, 0, 0);
    pct_say(talk, POST_CLERK_LINE_LOAN);
}
CLEAN_AS(func_ov054_022607ec, PostClerkTalk_ChooseLoan)

/* func_ov054_022607b8 (the menu's answer 0xec): line 0x16. */
void PostClerkTalk_ChooseSavings(PostClerkTalk *talk)
{
    pct_say(talk, POST_CLERK_LINE_SAVINGS);
}
CLEAN_AS(func_ov054_022607b8, PostClerkTalk_ChooseSavings)

/* func_ov054_022608ac (an answer to the menu): the handler of the answer picked in the menu
 * offered, when the menu has that many. The five handler tables are filled on the first call
 * each (menus 2, 0, 1, 3 and 4, in this order). */
void PostClerkTalk_OnMenuAnswer(PostClerkTalk *talk, unsigned int arg)
{
    static const MemberPointer *const menu_guest[2] = {
        &data_ov054_02262e90, /* 0xeb PostClerkTalk_ChooseLetters */
        &data_ov054_02262ec0, /* 0x56 PostClerkTalk_ChooseGoodbye */
    };
    static const MemberPointer *const menu_plain[4] = {
        &data_ov054_02262e18, /* 0xeb PostClerkTalk_ChooseLetters */
        &data_ov054_02262ce0, /* 0xec PostClerkTalk_ChooseSavings */
        &data_ov054_02262df0, /* 0xd5 PostClerkTalk_ChooseScreen26 */
        &data_ov054_02262d00, /* 0x56 PostClerkTalk_ChooseGoodbye */
    };
    static const MemberPointer *const menu_loan[5] = {
        &data_ov054_02262d50, /* 0xeb PostClerkTalk_ChooseLetters */
        &data_ov054_02262d58, /* 0xed PostClerkTalk_ChooseLoan */
        &data_ov054_02262d98, /* 0xec PostClerkTalk_ChooseSavings */
        &data_ov054_02262d88, /* 0xd5 PostClerkTalk_ChooseScreen26 */
        &data_ov054_02262e20, /* 0x56 PostClerkTalk_ChooseGoodbye */
    };
    static const MemberPointer *const menu_linked[3] = {
        &data_ov054_02262ec8, /* 0xeb PostClerkTalk_ChooseLetters */
        &data_ov054_02262d30, /* 0xec PostClerkTalk_ChooseSavings */
        &data_ov054_02262ce8, /* 0x56 PostClerkTalk_ChooseGoodbye */
    };
    static const MemberPointer *const menu_linked_loan[4] = {
        &data_ov054_02262d60, /* 0xeb PostClerkTalk_ChooseLetters */
        &data_ov054_02262d68, /* 0xed PostClerkTalk_ChooseLoan */
        &data_ov054_02262e40, /* 0xec PostClerkTalk_ChooseSavings */
        &data_ov054_02262e58, /* 0x56 PostClerkTalk_ChooseGoodbye */
    };
    (void) arg;

    int answer = pct_answer(talk);
    MemberTable_InitOnce(&data_ov054_02263218, data_ov054_0226321c, menu_guest, 2);
    MemberTable_InitOnce(&data_ov054_02263200, data_ov054_02263294, menu_plain, 4);
    MemberTable_InitOnce(&data_ov054_02263214, data_ov054_022632b4, menu_loan, 5);
    MemberTable_InitOnce(&data_ov054_0226320c, data_ov054_0226322c, menu_linked, 3);
    MemberTable_InitOnce(&data_ov054_02263204, data_ov054_02263274, menu_linked_loan, 4);

    if (answer < data_ov054_022629a0[talk->menu]) {
        MemberPointer_CallVoid(&data_ov054_02262f3c[talk->menu][answer], talk);
    }
}
CLEAN_AS(_ZN18Obj_ov054_0226300419func_ov054_022608acEj, PostClerkTalk_OnMenuAnswer)

/* func_ov054_02260a88 (at the end of the lines 0, 0x52, 0x53, 0x56): the menu offered, its last
 * answer the one cancelling, and the choices opened:
 * - linked, and this system not the host: menu 2 (the letters and goodbye);
 * - with a loan owed and the current player's flag 1 clear: the loan's menu (4 with a slot in
 *   the session, else 1);
 * - else 3 with a slot in the session, else 0. */
void PostClerkTalk_OfferMenu(PostClerkTalk *talk, int arg)
{
    (void) arg;
    TalkObject *object = pct_object(talk);
    u8 *record = PlayerRecords_Current();
    u32 menu = POST_CLERK_TALK_MENU_PLAIN;

    if (TalkChecks_IsHostOrAlone() == 0) {
        menu = POST_CLERK_TALK_MENU_GUEST;
    } else if (PlayerRecord_TestFlag(record, POST_CLERK_TALK_FLAG_1) == 0 && HouseRecord_Loan(&data_021ebcd4) != 0) {
        menu = PostClerk_HasSessionSlot(talk->owner) ? POST_CLERK_TALK_MENU_LINKED_LOAN : POST_CLERK_TALK_MENU_LOAN;
    } else if (PostClerk_HasSessionSlot(talk->owner)) {
        menu = POST_CLERK_TALK_MENU_LINKED;
    }
    talk->menu = menu;
    s32 count = data_ov054_022629b4[menu];
    TalkChecks_OfferMessages(&talk->base, data_ov054_02262f50[menu], count, count - 1);
    TalkObject_OpenChoices(object, 1);
}
CLEAN_AS(func_ov054_02260a88, PostClerkTalk_OfferMenu)

/* ---- The answers */

/* func_ov054_02261850 (the pockets' test of the errand's screen): for an item in state 2,
 * whether it is 0x155f or 0x1560. */
unsigned short PostClerkTalk_IsErrandItem(unsigned short *item, int state)
{
    if (state != POST_CLERK_TALK_ERRAND_STATE) {
        return 0;
    }
    return *item >= POST_CLERK_TALK_ERRAND_FIRST && *item <= POST_CLERK_TALK_ERRAND_LAST;
}
CLEAN_AS(func_ov054_02261850, PostClerkTalk_IsErrandItem)

/* func_ov054_02260b30 (an answer in "sp_etc_sequence4"): at line 0x12 the current player's
 * option flag is set by the answer (0 clears it, 1 sets it) and the options are stored. The
 * current player's record is asked for and not used. */
void PostClerkTalk_OnSequenceAnswer(PostClerkTalk *talk, unsigned int arg)
{
    (void) arg;
    int answer = pct_answer(talk);
    (void) PlayerRecords_Current();
    if (pct_shown(talk) != POST_CLERK_SEQUENCE_LINE_OPTION) {
        return;
    }
    if (answer == 0) {
        PlayerOptions_ChangeFlag(0);
    } else if (answer == 1) {
        PlayerOptions_ChangeFlag(1);
    }
    PlayerOptions_Store();
}
CLEAN_AS(func_ov054_02260b30, PostClerkTalk_OnSequenceAnswer)

/* func_ov054_02260b70 (an answer to a line of her dated events' file): at the lines 0 to
 * 0x19, the second answer gives her line by the counter place she serves; another answer
 * marks today's dated event of kind 0 (when there is one) as reached. */
void PostClerkTalk_OnDramaAnswer(PostClerkTalk *talk, unsigned int arg)
{
    (void) arg;
    int answer = pct_answer(talk);
    int line = POST_CLERK_TALK_NO_LINE;
    if (pct_shown(talk) <= 0x19) {
        if (answer == 1) {
            line = data_ov054_02262984[talk->owner->spot];
        } else {
            u8 event;
            if (TalkChecks_TodaysEventOfKind((int) (uintptr_t) talk->owner, &event, 0) != 0) {
                TalkChecks_MarkDayEvent((int) (uintptr_t) talk->owner, &event);
            }
        }
    }
    if (line != POST_CLERK_TALK_NO_LINE) {
        pct_say(talk, (u8) line);
    }
}
CLEAN_AS(func_ov054_02260b70, PostClerkTalk_OnDramaAnswer)

/* func_ov054_02260c00 (an answer to a line of her own file), by the line shown:
 * - 0x5f (an errand): the first answer opens the pockets' screen offering the errand's items
 *   (func_ov054_02261850), then step 11; the second gives her line by the counter place;
 * - 0, 0x52, 0x53, 0x56: the menu's answer (PostClerkTalk_OnMenuAnswer);
 * - 3 and 9: the first answer opens the letter screen again (step 1);
 * - 0x10: the first answer 0x11; the second puts the letter back in the pockets, 0x0e;
 * - 0x0c: the first answer keeps the letter as the dated letter, 0x07;
 * - 4, 0x1c, 0x34, 0x5d, 0x5e: the third answer 0x1a the first time (flag 4 set), then 0x19;
 *   the fourth 0x60 with the current player's flag 1, else 0x35;
 * - 0x38 and 0x39 (a linked game found): the second answer ends the session, 0x3a. */
void PostClerkTalk_OnOwnAnswer(PostClerkTalk *talk, unsigned int arg)
{
    int answer = pct_answer(talk);
    u8 *record = PlayerRecords_Current();
    int line = POST_CLERK_TALK_NO_LINE;

    switch (pct_shown(talk)) {
        case POST_CLERK_LINE_ERRAND:
            if (answer == 0) {
                SceneCommand_SetPocketPredicate(pct_scene(talk), (PocketPredicate) (void (*)(void)) func_ov054_02261850,
                                                POST_CLERK_TALK_POCKET_ARG, 0);
                SceneCommand_RequestScreen(pct_scene(talk), POST_CLERK_TALK_SCREEN_POCKETS);
                PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_ERRAND);
            } else if (answer == 1) {
                line = data_ov054_02262978[talk->owner->spot];
            }
            break;
        case POST_CLERK_LINE_MENU:
        case 0x52:
        case 0x53:
        case 0x56:
            PostClerkTalk_OnMenuAnswer(talk, arg);
            break;
        case POST_CLERK_LINE_NOT_POSTED:
        case POST_CLERK_LINE_NONE_POSTED:
            if (answer == 0) {
                SceneCommand_RequestScreen(pct_scene(talk), POST_CLERK_TALK_SCREEN_LETTERS);
                PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_LETTERS);
            }
            break;
        case 0x10:
            if (answer == 0) {
                line = POST_CLERK_LINE_REDATE;
            } else if (answer == 1) {
                line = POST_CLERK_LINE_NOT_DATED;
                GroupParams_LetterToPockets();
            }
            break;
        case POST_CLERK_LINE_DATE_TAKEN:
            if (answer == 0) {
                GroupParams_LetterToDated();
                line = POST_CLERK_LINE_POSTED_ALL;
            }
            break;
        case 0x04:
        case 0x1c:
        case 0x34:
        case 0x5d:
        case 0x5e:
            if (answer == 2) {
                if (PlayerRecord_TestFlag(record, POST_CLERK_TALK_FLAG_4) == 0) {
                    line = 0x1a;
                    PlayerRecord_SetFlag(record, POST_CLERK_TALK_FLAG_4);
                } else {
                    line = 0x19;
                }
            } else if (answer == 3) {
                line = PlayerRecord_TestFlag(record, POST_CLERK_TALK_FLAG_1) != 0 ? 0x60 : 0x35;
            }
            break;
        case POST_CLERK_LINE_GAME_FOUND:
        case POST_CLERK_LINE_GAME_NAMED:
            if (answer == 1) {
                PostClerkTalk_EndLinkedGame(talk);
                line = POST_CLERK_LINE_SESSION_ENDED;
            }
            break;
        default:
            break;
    }
    if (line != POST_CLERK_TALK_NO_LINE) {
        pct_say(talk, (u8) line);
    }
}
CLEAN_AS(_ZN18Obj_ov054_0226300419func_ov054_02260c00Ej, PostClerkTalk_OnOwnAnswer)

/* func_ov054_02260d9c (vtable slot 0x18, the player's answer): to the handler by the talk's
 * file (PostClerkTalk_OnOwnAnswer, PostClerkTalk_OnDramaAnswer, PostClerkTalk_OnSequenceAnswer)
 * with `arg`; the table is filled on the first call. */
void PostClerkTalk_OnAnswer(PostClerkTalk *talk, u32 arg)
{
    static const MemberPointer *const kinds[POST_CLERK_TALK_FILES] = {
        &data_ov054_02262db8, /* PostClerkTalk_OnOwnAnswer */
        &data_ov054_02262db0, /* PostClerkTalk_OnDramaAnswer */
        &data_ov054_02262da8, /* PostClerkTalk_OnSequenceAnswer */
    };
    MemberTable_InitOnce(&data_ov054_02263210, data_ov054_0226325c, kinds, POST_CLERK_TALK_FILES);
    pct_call(&data_ov054_0226325c[pct_file_kind(talk)], talk, arg);
}
CLEAN_AS(_ZN18Obj_ov054_0226300419func_ov054_02260d9cEj, PostClerkTalk_OnAnswer)

/* ---- The ends of lines */

/* func_ov054_02260e58 (the end of a line of "sp_etc_sequence4"): at the lines 2, 0x20 and
 * 0x23 to 0x26 the screen in mode 0x2f; at line 0x13 the town's players are told: 2 in a new
 * town, else 0x22 plus their number. */
void PostClerkTalk_OnSequenceLineEnd(PostClerkTalk *talk, unsigned int arg)
{
    (void) arg;
    const char *file = pct_files(talk)->sequence;
    int line = 0;

    switch (pct_shown(talk)) {
        case 0x02:
        case 0x20:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
            SceneCommand_SetScreenMode(pct_scene(talk), POST_CLERK_SEQUENCE_MODE, 0);
            SceneCommand_RequestScreen(pct_scene(talk), POST_CLERK_TALK_SCREEN);
            break;
        case POST_CLERK_SEQUENCE_LINE_TOWN: {
            int players = PlayerRecords_CountTown(data_021dc7bc);
            if (StartKind_IsNewTown() != 0) {
                line = POST_CLERK_SEQUENCE_NEW_TOWN_LINE;
            } else {
                line = (u8) (players + POST_CLERK_SEQUENCE_PLAYERS_LINE);
            }
            break;
        }
        default:
            break;
    }
    if (line != 0) {
        pct_say_in(talk, (u8) line, file);
    }
}
CLEAN_AS(func_ov054_02260e58, PostClerkTalk_OnSequenceLineEnd)

/* func_ov054_02260ef8 (the end of a line of her dated events' file): nothing. */
void PostClerkTalk_OnDramaLineEnd(PostClerkTalk *talk, unsigned int arg)
{
    (void) talk;
    (void) arg;
}
CLEAN_AS(func_ov054_02260ef8, PostClerkTalk_OnDramaLineEnd)

/* func_ov054_02260710 (the end of the lines 0x1d and 0x1e, an amount added to the town-wide
 * amount): the savings rank whose range [entry i, entry i + 1) holds the town-wide amount (1 to
 * 20, data_ov054_02262a18) becomes the account's; when the amount before was below that rank's
 * start the current player's rank letter is to be written (flag 0x16). The line is 0x1f plus the
 * rank (the account's rank when none matches). */
void PostClerkTalk_TellSavingsRank(PostClerkTalk *talk, int arg)
{
    (void) arg;
    TalkObject *object = pct_object(talk);
    const char *file = pct_files(talk)->own;
    u8 *record = PlayerRecords_Current();
    SavingsAccount *account = PlayerRecord_Savings(record);
    int amount = (int) Savings_Total();
    u8 line = (u8) (Savings_Rank(account) + 0x1f);

    for (int rank = 1; rank < POST_CLERK_TALK_RANKS; rank++) {
        int start = data_ov054_02262a18[rank];
        if (amount >= start && amount < data_ov054_02262a18[rank + 1]) {
            Savings_SetRank(account, (u8) rank);
            if (talk->town_amount < start) {
                PlayerRecord_SetFlag(record, SAVINGS_FLAG_RANK_LETTER);
            }
            line = (u8) (rank + 0x1f);
        }
    }
    TalkObject_SetMessage(object, &line, file);
}
CLEAN_AS(func_ov054_02260710, PostClerkTalk_TellSavingsRank)

/* The line of the town summary (TownDay_Summarize): 0x42 down to 0x3e for 0 to 4, else 0x40. */
static int pct_summary_line(int summary)
{
    switch (summary) {
        case 0:
            return 0x42;
        case 1:
            return 0x41;
        case 2:
            return 0x40;
        case 3:
            return 0x3f;
        case 4:
            return 0x3e;
        default:
            return 0x40;
    }
}

/* The line of the acre summary's word 8 (TownDay_Acres18): 0x43 to 0x48 for 0 to 5, else 0x43. */
static int pct_acres_line(int value)
{
    if (value >= 0 && value <= 5) {
        return 0x43 + value;
    }
    return 0x43;
}

/* func_ov054_02260efc (the end of a line of her own file), by the line shown:
 * - 2: the talk held;
 * - 0, 0x52, 0x53, 0x56: the menu (PostClerkTalk_OfferMenu);
 * - 0x0e, 0x5c, 0x62: the letters shown; 9 when no written letter was handled, else
 *   PostClerkTalk_UnsentLine (5 instead of 9);
 * - 0x07: PostClerkTalk_UnsentLine; 0x61: the letters shown;
 * - 0x58: the letters shown, PostClerkTalk_FullMailboxLine (PostClerkTalk_PostedLine instead
 *   of 9); 0x59 to 0x5b: the letters shown, PostClerkTalk_PostedLine;
 * - 0x0b, 0x0d, 0x11: the date's screen (mode 0x33), step 5; 0x12: the loan's (mode 0x34),
 *   step 6; 0x16: the balance noted, the account's screen (mode 0x3b), step 7; 0x19, 0x1b: the
 *   screen in mode 0x37, step 3; 0x49: the screen in mode 0x3f, step 4;
 * - 0x13 to 0x15, 0x17, 0x18: 0x52 (the menu again);
 * - 0x55: the talk held, its spinner (sound 0), step 8 (activity job 0x12);
 * - 0x1d, 0x1e: PostClerkTalk_TellSavingsRank;
 * - 0x36: the talk held, its spinner (sound 1), overlay 66 switched to, a linked session
 *   started (mode 2, two players), 600 frames to find a game, step 12;
 * - 0x3d: the town summary's line; 0x40 to 0x42: the acre summary's line;
 * - 0x3e: 0x4b when the gift was handed over (flag 0x20); else when the town's summary
 *   answered 4 long enough and this system is the host (or alone), 0x4d when the gift 0x1379
 *   goes into the pockets; else 0x4c;
 * - 0x4e: the gift held up (motion 13), flag 0x20 set;
 * - 0x3b: the talk held, its spinner (sound 0), step 14 (activity job 0x1f);
 * - 0x3c: the talk's mode 0, and she leaves (state 8).
 * The line, when there is one, is shown. */
void PostClerkTalk_OnOwnLineEnd(PostClerkTalk *talk, int arg)
{
    TalkObject *object = pct_object(talk);
    u8 *record = PlayerRecords_Current();
    SavingsAccount *account = PlayerRecord_Savings(record);
    const char *file = pct_files(talk)->own;
    int line = 0;

    switch (pct_shown(talk)) {
        case POST_CLERK_LINE_JOB_12:
            TalkObject_Hold(object);
            break;
        case POST_CLERK_LINE_MENU:
        case 0x52:
        case 0x53:
        case 0x56:
            PostClerkTalk_OfferMenu(talk, arg);
            break;
        case POST_CLERK_LINE_NOT_DATED:
        case 0x5c:
        case 0x62:
            PostClerkTalk_ShowLetters(talk);
            if (GroupParams_LetterNoFlag100()) {
                line = POST_CLERK_LINE_NONE_POSTED;
                break;
            }
            line = PostClerkTalk_UnsentLine(talk);
            if (line == POST_CLERK_LINE_NONE_POSTED) {
                line = POST_CLERK_LINE_POSTED;
            }
            break;
        case POST_CLERK_LINE_POSTED_ALL:
            line = PostClerkTalk_UnsentLine(talk);
            break;
        case POST_CLERK_LINE_UNSENT:
            PostClerkTalk_ShowLetters(talk);
            break;
        case 0x58:
            PostClerkTalk_ShowLetters(talk);
            line = PostClerkTalk_FullMailboxLine(talk);
            if (line == POST_CLERK_LINE_NONE_POSTED) {
                line = PostClerkTalk_PostedLine(talk);
            }
            break;
        case 0x59:
        case 0x5a:
        case 0x5b:
            PostClerkTalk_ShowLetters(talk);
            line = PostClerkTalk_PostedLine(talk);
            break;
        case POST_CLERK_LINE_DATE_SELF:
        case 0x0d:
        case POST_CLERK_LINE_REDATE:
            pct_open(talk, POST_CLERK_TALK_MODE_DATE, 0, POST_CLERK_TALK_STEP_DATED_LETTER);
            break;
        case POST_CLERK_LINE_LOAN:
            pct_open(talk, POST_CLERK_TALK_MODE_LOAN, 1, POST_CLERK_TALK_STEP_LOAN);
            break;
        case POST_CLERK_LINE_SAVINGS:
            talk->balance = Savings_Balance(account);
            pct_open(talk, POST_CLERK_TALK_MODE_SAVINGS, 1, POST_CLERK_TALK_STEP_SAVINGS);
            break;
        case POST_CLERK_LINE_LOAN_NONE:
        case POST_CLERK_LINE_LOAN_PAID:
        case POST_CLERK_LINE_LOAN_PAID_OFF:
        case POST_CLERK_LINE_SAVINGS_DONE:
        case POST_CLERK_LINE_SAVINGS_NONE:
            line = POST_CLERK_LINE_MENU_AGAIN;
            break;
        case 0x55:
            TalkObject_Hold(object);
            TalkObject_StartSpinner(object, 0);
            PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_ASK_JOB_12);
            break;
        case 0x19:
        case 0x1b:
            pct_open(talk, POST_CLERK_TALK_MODE_TOWN_AMOUNT, 1, POST_CLERK_TALK_STEP_TOWN_AMOUNT);
            break;
        case 0x49:
            pct_open(talk, POST_CLERK_TALK_MODE_3F, 0, POST_CLERK_TALK_STEP_SCREEN_3F);
            break;
        case 0x1d:
        case 0x1e:
            PostClerkTalk_TellSavingsRank(talk, arg);
            break;
        case 0x36:
            TalkObject_Hold(object);
            TalkObject_StartSpinner(object, 1);
            LibraryOverlay_Switch66();
            Session_Start(POST_CLERK_TALK_SESSION_MODE, POST_CLERK_TALK_SESSION_PLAYERS, 0);
            talk->search_frames = POST_CLERK_TALK_SEARCH_FRAMES;
            PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_SEARCH);
            break;
        case 0x3d:
            line = pct_summary_line(TownDay_Summarize());
            break;
        case 0x3e:
            if (PlayerRecord_TestFlag(record, POST_CLERK_TALK_FLAG_GIFT) != 0) {
                line = 0x4b;
                break;
            }
            if (TownRecord_Summary4Long() != 0 && TalkChecks_IsHostOrAlone() != 0) {
                u16 gift = POST_CLERK_TALK_GIFT_ITEM;
                if (CurrentPockets_Give(&gift, 0) != 0) {
                    line = 0x4d;
                    break;
                }
            }
            line = 0x4c;
            break;
        case 0x40:
        case 0x41:
        case 0x42: {
            const s32 *acres = (const s32 *) (uintptr_t) (u32) TownDay_Acres18();
            line = pct_acres_line(acres[2]);
            break;
        }
        case 0x4e:
            pct_hold_up(talk, POST_CLERK_TALK_GIFT_ITEM, 0);
            PlayerRecord_SetFlag(record, POST_CLERK_TALK_FLAG_GIFT);
            break;
        case 0x3b:
            TalkObject_Hold(object);
            TalkObject_StartSpinner(object, 0);
            PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_ASK_JOB_1F);
            break;
        case POST_CLERK_LINE_JOB_1F:
            object->mode = 0;
            PostClerk_SetState(talk->owner, POST_CLERK_LEAVE);
            break;
        default:
            break;
    }
    if (line != 0) {
        pct_say_in(talk, (u8) line, file);
    }
}
CLEAN_AS(func_ov054_02260efc, PostClerkTalk_OnOwnLineEnd)

/* func_ov054_022612c4 (vtable slot 0x14, a line ended): to the handler by the talk's file
 * (PostClerkTalk_OnOwnLineEnd, PostClerkTalk_OnDramaLineEnd, PostClerkTalk_OnSequenceLineEnd)
 * with `arg`; the table is filled on the first call. */
void PostClerkTalk_OnLineEnd(PostClerkTalk *talk, u32 arg)
{
    static const MemberPointer *const kinds[POST_CLERK_TALK_FILES] = {
        &data_ov054_02262cf0, /* PostClerkTalk_OnOwnLineEnd */
        &data_ov054_02262dd8, /* PostClerkTalk_OnDramaLineEnd */
        &data_ov054_02262dd0, /* PostClerkTalk_OnSequenceLineEnd */
    };
    MemberTable_InitOnce(&data_ov054_02263208, data_ov054_02263244, kinds, POST_CLERK_TALK_FILES);
    pct_call(&data_ov054_02263244[pct_file_kind(talk)], talk, arg);
}
CLEAN_AS(_ZN18Obj_ov054_0226300419func_ov054_022612c4Ej, PostClerkTalk_OnLineEnd)

/* ---- The steps */

/* func_ov054_02261c00 (step 1, after the letter screen): when letters were posted, the line by
 * what was posted (GroupParams_LetterKind): none to the player themself, PostClerkTalk_UnsentLine
 * (7 instead of 9); one, 0x0f when a dated letter is kept already, else 0x0b; several, 0x5c;
 * linked, 0x62. The letters are taken (motion 14 with the item 0x1565), then step 10. When
 * nothing was posted, line 3 and the next line. The letters are not shown yet in this talk. */
void PostClerkTalk_AfterLetters(PostClerkTalk *talk)
{
    int line = 0;
    talk->letters_shown = 0;
    if (GroupParams_C4CIs1()) {
        switch (GroupParams_LetterKind()) {
            case 0:
                line = PostClerkTalk_UnsentLine(talk);
                if (line == POST_CLERK_LINE_NONE_POSTED) {
                    line = POST_CLERK_LINE_POSTED_ALL;
                }
                break;
            case 1:
                line = Mail_HasDatedLetter(NULL) != 0 ? POST_CLERK_LINE_DATED_KEPT : POST_CLERK_LINE_DATE_SELF;
                break;
            case 2:
                line = 0x5c;
                break;
            case 3:
                line = 0x62;
                break;
            default:
                break;
        }
        pct_hand_over(talk, POST_CLERK_TALK_LETTERS_ITEM, 0);
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NEXT_LINE);
    } else {
        line = POST_CLERK_LINE_NOT_POSTED;
        SceneCommand_RequestNextLine(pct_scene(talk));
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    }
    pct_say(talk, (u8) line);
}
CLEAN_AS(func_ov054_02261c00, PostClerkTalk_AfterLetters)

/* func_ov054_02261bb4 (step 2, after the screen in mode 0x26): line 0x54 when it was confirmed,
 * else 0x53; no step. */
void PostClerkTalk_AfterScreen26(PostClerkTalk *talk)
{
    pct_say(talk, GroupParams_C4CIs1() ? 0x54 : 0x53);
    PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
}
CLEAN_AS(func_ov054_02261bb4, PostClerkTalk_AfterScreen26)

/* func_ov054_02261af8 (step 3, after the screen in mode 0x37): when confirmed, the amount
 * given (GroupParams_C78) in slot 7 as bells, line 0x1d for 5,000 bells or more, else 0x1e; the
 * bells taken (motion 14 with the item 0x149b), step 10; the town-wide amount noted and the
 * amount added to it. Else line 0x1c and the next line. The current player's account is asked
 * for and not used. */
void PostClerkTalk_AfterTownAmount(PostClerkTalk *talk)
{
    u8 line;
    if (GroupParams_C4CIs1()) {
        int amount = GroupParams_C78();
        SceneBase_PutValue(&talk->base, amount, 7, POST_CLERK_TALK_VALUE_BELLS, 0, 0);
        line = amount >= POST_CLERK_TALK_BIG_AMOUNT ? 0x1d : 0x1e;
        pct_hand_over(talk, POST_CLERK_TALK_BELLS_ITEM, 0);
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NEXT_LINE);
        (void) PlayerRecord_Savings(PlayerRecords_Current());
        talk->town_amount = (s32) Savings_Total();
        Savings_SetTotal(talk->town_amount + amount);
    } else {
        line = 0x1c;
        SceneCommand_RequestNextLine(pct_scene(talk));
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    }
    pct_say(talk, line);
}
CLEAN_AS(func_ov054_02261af8, PostClerkTalk_AfterTownAmount)

/* func_ov054_02261a94 (step 4, after the screen in mode 0x3f): with a slot in the session, line
 * 0x63 when confirmed, else 0x64; without, 0x5d or 0x5e; no step. */
void PostClerkTalk_AfterScreen3f(PostClerkTalk *talk)
{
    u8 line;
    if (PostClerk_HasSessionSlot(talk->owner) != 0) {
        line = GroupParams_C4CIs1() ? 0x63 : 0x64;
    } else {
        line = GroupParams_C4CIs1() ? 0x5d : 0x5e;
    }
    PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    pct_say(talk, line);
}
CLEAN_AS(func_ov054_02261a94, PostClerkTalk_AfterScreen3f)

/* func_ov054_02261a00 (step 5, after the date's screen): when a date was picked, it (the kept
 * date, Global021cfc98_CopyOut) goes in (the year, 2000 on, in slot 1; the month in slot 2;
 * the day in slot 3), line 0x0c; else the letter goes back to the pockets, line 0x0e. No
 * step. */
void PostClerkTalk_AfterDatedLetter(PostClerkTalk *talk)
{
    u8 line;
    if (GroupParams_C4CIs1()) {
        line = POST_CLERK_LINE_DATE_TAKEN;
        DateTime when = {0};
        Global021cfc98_CopyOut(&when);
        u8 month = when.month;
        u8 day = when.day;
        SceneBase_PutValue(&talk->base, when.year + POST_CLERK_TALK_YEAR_BASE, 1, POST_CLERK_TALK_VALUE_YEAR, 0, 0);
        SceneBase_PutNumberAlt(&talk->base, (void *) (uintptr_t) month, 2);
        SceneBase_PutNumber(&talk->base, day, 3);
    } else {
        line = POST_CLERK_LINE_NOT_DATED;
        GroupParams_LetterToPockets();
    }
    PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    pct_say(talk, line);
}
CLEAN_AS(func_ov054_02261a00, PostClerkTalk_AfterDatedLetter)

/* func_ov054_0226194c (step 6, after the loan's screen): when confirmed, the loan left in slot
 * 4 as bells; none left: line 0x15, flag 0 of block 0x021d27ac set and flag 0x10 of the state
 * block cleared; else 0x14. The bells taken (motion 14 with the item 0x149b), step 10. Else
 * line 0x13 and the next line. */
void PostClerkTalk_AfterLoan(PostClerkTalk *talk)
{
    u8 line;
    if (GroupParams_C4CIs1()) {
        int loan = HouseRecord_Loan(&data_021ebcd4);
        SceneBase_PutValue(&talk->base, loan, 4, POST_CLERK_TALK_VALUE_BELLS, 0, 0);
        if (loan == 0) {
            line = POST_CLERK_LINE_LOAN_PAID_OFF;
            Block021d27ac_SetFlag((u32 *) (void *) Block021d27ac_Get(), 0);
            StateBlock_ClearFlag(data_021dc7a8, 0x10);
        } else {
            line = POST_CLERK_LINE_LOAN_PAID;
        }
        pct_hand_over(talk, POST_CLERK_TALK_BELLS_ITEM, 0);
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NEXT_LINE);
    } else {
        line = POST_CLERK_LINE_LOAN_NONE;
        SceneCommand_RequestNextLine(pct_scene(talk));
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    }
    pct_say(talk, line);
}
CLEAN_AS(func_ov054_0226194c, PostClerkTalk_AfterLoan)

/* func_ov054_02261878 (step 7, after the account's screen): when confirmed, the balance in
 * slot 5 and a 200th of it in slot 6, as bells, line 0x17; the bells taken (motion 14 with the
 * item 0x149b) when the balance grew, else handed over (motion 13); step 10. Else line 0x18 and
 * the next line. */
void PostClerkTalk_AfterSavings(PostClerkTalk *talk)
{
    u8 line;
    if (GroupParams_C4CIs1()) {
        int balance = Savings_Balance(PlayerRecord_Savings(PlayerRecords_Current()));
        SceneBase_PutValue(&talk->base, balance, 5, POST_CLERK_TALK_VALUE_BELLS, 0, 0);
        SceneBase_PutValue(&talk->base, balance / POST_CLERK_TALK_SAVINGS_PART, 6, POST_CLERK_TALK_VALUE_BELLS, 0, 0);
        line = POST_CLERK_LINE_SAVINGS_DONE;
        if (balance > talk->balance) {
            pct_hand_over(talk, POST_CLERK_TALK_BELLS_ITEM, 0);
        } else {
            pct_hold_up(talk, POST_CLERK_TALK_BELLS_ITEM, 0);
        }
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NEXT_LINE);
    } else {
        line = POST_CLERK_LINE_SAVINGS_NONE;
        SceneCommand_RequestNextLine(pct_scene(talk));
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    }
    pct_say(talk, line);
}
CLEAN_AS(func_ov054_02261878, PostClerkTalk_AfterSavings)

/* func_ov054_02261738 (step 8, each step): once the clerk is ready (PostClerk_ReadyForJob),
 * activity job 0x12 is asked for, step 9. */
void PostClerkTalk_AskJob12(PostClerkTalk *talk)
{
    if (PostClerk_ReadyForJob(talk->owner)) {
        ActivityJob_Ask12();
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_AWAIT_JOB_12);
    }
}
CLEAN_AS(func_ov054_02261738, PostClerkTalk_AskJob12)

/* func_ov054_022616c4 (step 9, each step): once activity job 0x12 is at its step 3, the talk is
 * let go and line 2 shown; or once no job runs, the talk is let go. Then no step. */
void PostClerkTalk_AwaitJob12(PostClerkTalk *talk)
{
    TalkObject *object = pct_object(talk);
    if (ActivityJob_Is12AtStep3()) {
        pct_release(object);
        pct_say(talk, POST_CLERK_LINE_JOB_12);
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    } else if (ActivityJob_IsIdle()) {
        pct_release(object);
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    }
}
CLEAN_AS(func_ov054_022616c4, PostClerkTalk_AwaitJob12)

/* func_ov054_022616ac (step 10, after a motion): the next line; no step. */
void PostClerkTalk_NextLine(PostClerkTalk *talk)
{
    SceneCommand_RequestNextLine(pct_scene(talk));
    PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
}
CLEAN_AS(func_ov054_022616ac, PostClerkTalk_NextLine)

/* func_ov054_0226175c (step 11, after the pockets' screen of the errand): when the player
 * picked an item and this system is the host (or alone), the item of the slot picked is taken
 * from the pockets; unless it is empty she takes it (motion 14), the line is 0x50 when the
 * errand was for her person, else 0x57, and the current player's errand is marked done
 * (ItemObject_SetLow5 1). Else the line is 0x51. No step.
 * QUIRK: the slot is a byte, so the test that it is not negative before emptying it always
 * passes. */
void PostClerkTalk_AfterErrand(PostClerkTalk *talk)
{
    u8 line = POST_CLERK_LINE_ERRAND_NONE;
    if (GroupParams_C4CIs1()) {
        VillagerPartEntry *errand = (VillagerPartEntry *) (void *) VillagerPart_Object94(
            (VillagerPart *) (void *) PlayerRecord_VillagerPart(PlayerRecords_Current()));
        if (TalkChecks_IsHostOrAlone()) {
            int slot = GroupParams_Arg();
            u16 item = CurrentPockets_Item((u32) slot);
            if (slot >= 0) {
                CurrentPockets_Empty(slot);
            }
            int empty;
            if (ItemCode_HasVariant(&item)) {
                u16 none = POST_CLERK_TALK_NO_ITEM;
                int own = ItemCode_VariantItem(&item);
                empty = own == ItemCode_VariantItem(&none);
            } else {
                empty = item == POST_CLERK_TALK_NO_ITEM;
            }
            if (!empty) {
                SceneCommand_RequestMotion14(pct_scene(talk), &item, 2, POST_CLERK_TALK_MOTION_B, 1);
                u16 *person = (u16 *) (void *) (talk->owner->base + 0xea);
                line = VillagerPartEntry_Accepts(errand, person) != 0 ? POST_CLERK_LINE_ERRAND_TAKEN
                                                                      : POST_CLERK_LINE_ERRAND_OTHER;
                ItemObject_SetLow5((ItemObject *) (void *) VillagerPartEntry_Self(errand), 1);
            }
        }
    }
    PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    pct_say(talk, line);
}
CLEAN_AS(func_ov054_0226175c, PostClerkTalk_AfterErrand)

/* func_ov054_02261534 (step 12, each step, looking for a linked game): the session's nothing
 * sent and the joinable games counted; once the frames to find one run out, the game is given
 * up. Else each listed entry (overlay 66 required before each library call) whose data is 14
 * bytes and open (byte 0xd 1) is a game found: line 0x38, or 0x39 with its town's name (6 wide
 * characters, when byte 0xc is 0) in part 8; selected, step 13 (connecting), else the game is
 * given up. Only the first such entry is looked at.
 * QUIRK: the entries are counted with a byte, so more than 255 would never end the loop. */
void PostClerkTalk_SearchGame(PostClerkTalk *talk)
{
    TalkObject *object = pct_object(talk);
    const char *file = pct_files(talk)->own;

    Session_SendNothing();
    int count = Net_CountJoinable();
    if (Countdown_Tick16(&talk->search_frames) == 0) {
        pct_give_up_linked(talk);
        return;
    }
    if (count <= 0) {
        return;
    }

    LibraryOverlay_Require66();
    void **entries = Local_ListEntries();
    TownNameText name;
    TownNameWideText wide;
    TownNameText_Construct(&name);
    TownNameWideText_Construct(&wide);
    for (u8 i = 0; i < count; i++) {
        void *entry = entries[i];
        if (entry == NULL) {
            continue;
        }
        LibraryOverlay_Require66();
        int size = Local_EntryDataSize(entry);
        if (size != POST_CLERK_TALK_ENTRY_SIZE) {
            continue;
        }
        LibraryOverlay_Require66();
        u8 data[0x10];
        MI_CpuCopy8(Local_EntryData(entry), data, (u32) size);
        if (data[POST_CLERK_TALK_ENTRY_OPEN] != 1) {
            continue;
        }
        u8 line = POST_CLERK_LINE_GAME_FOUND;
        if (data[POST_CLERK_TALK_ENTRY_NAMELESS] == 0) {
            TextBase_SetWide(&wide, data, POST_CLERK_TALK_ENTRY_NAME_CHARS);
            TextBase_WideToBytes((TextBase *) (void *) &name, (WideTextBase *) (void *) &wide, 0, 0);
            TalkObject_SetPart(object, POST_CLERK_TALK_PART_TOWN, (TextBase *) (void *) &name);
            line = POST_CLERK_LINE_GAME_NAMED;
        }
        pct_say_in(talk, line, file);
        LibraryOverlay_Require66();
        if (Local_SelectEntry(entry) != 0) {
            PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_CONNECT);
        } else {
            pct_give_up_linked(talk);
        }
        break;
    }
    TownNameWideText_Destruct(&wide);
    TownNameText_Destruct(&name);
}
CLEAN_AS(func_ov054_02261534, PostClerkTalk_SearchGame)

/* func_ov054_022614b4 (step 13, each step, connecting): once the frames run out, the game is
 * given up; else (with the network library's overlay required) once the connection is made,
 * the talk is let go, no step. */
void PostClerkTalk_AwaitConnection(PostClerkTalk *talk)
{
    TalkObject *object = pct_object(talk);
    if (Countdown_Tick16(&talk->search_frames) == 0) {
        pct_give_up_linked(talk);
        return;
    }
    LibraryOverlay_RequireAny();
    if (Net_UpdateConnection()) {
        pct_release(object);
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    }
}
CLEAN_AS(func_ov054_022614b4, PostClerkTalk_AwaitConnection)

/* func_ov054_02261490 (step 14, each step): once the clerk is ready (PostClerk_ReadyForJob),
 * activity job 0x1f is asked for, step 15. */
void PostClerkTalk_AskJob1f(PostClerkTalk *talk)
{
    if (PostClerk_ReadyForJob(talk->owner)) {
        ActivityJob_Ask1F();
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_AWAIT_JOB_1F);
    }
}
CLEAN_AS(func_ov054_02261490, PostClerkTalk_AskJob1f)

/* func_ov054_02261428 (step 15, each step): while activity job 0x1f is at its step 15 or 20,
 * no step; else once no job runs, the talk is let go, line 0x3c, no step. */
void PostClerkTalk_AwaitJob1f(PostClerkTalk *talk)
{
    TalkObject *object = pct_object(talk);
    if (ActivityJob_Is1FAtStep15Or20()) {
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
        return;
    }
    if (ActivityJob_IsIdleForOv054()) {
        pct_release(object);
        pct_say(talk, POST_CLERK_LINE_JOB_1F);
        PostClerkTalk_SetStep(talk, POST_CLERK_TALK_STEP_NONE);
    }
}
CLEAN_AS(func_ov054_02261428, PostClerkTalk_AwaitJob1f)
