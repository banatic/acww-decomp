/* The title scene (title_scene.h): its states, the table they run from, its music, its frame,
 * its start and end, and its construction. */
#include "title_scene.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/activity_card.h"
#include "main/activity_job.h"
#include "main/control_mode_icon.h"
#include "main/event_queue.h"
#include "main/message_receiver.h"
#include "main/music_queue.h"
#include "main/player_options.h"
#include "main/scene_exit.h"
#include "main/scene_process_base.h"
#include "main/scene_tables.h"
#include "main/screen_transition.h"
#include "main/start_kind.h"
#include "main/state_block.h"
#include "main/talk_object.h"
#include "main/wfc_setup.h"

static_assert(sizeof(Process) == 0x50, "Process");
static_assert(offsetof(TitleScene, receiver) == 0x54, "TitleScene.receiver");
static_assert(offsetof(TitleScene, card_unreadable) == 0xa2, "TitleScene.card_unreadable");
static_assert(offsetof(TitleScene, logo_step) == 0xa4, "TitleScene.logo_step");
static_assert(offsetof(TitleScene, logo_state) == 0xaa, "TitleScene.logo_state");
static_assert(offsetof(TitleScene, idle_timer) == 0xac, "TitleScene.idle_timer");
static_assert(offsetof(TitleScene, mes) == 0xb0, "TitleScene.mes");
static_assert(offsetof(TitleScene, chars_task) == 0xd0, "TitleScene.chars_task");
static_assert(offsetof(TitleScene, wfc_failed) == 0xf4, "TitleScene.wfc_failed");
static_assert(sizeof(TitleScene) == 0xf8, "TitleScene");

/* The buttons that answer the title (PadState.pressed) and those it ignores. */
#define TITLE_PAD_A 0x0001
#define TITLE_PAD_B 0x0002
#define TITLE_PAD_START 0x0008
#define TITLE_PAD_X 0x0400
#define TITLE_PAD_Y 0x0800

#define TITLE_TALK 0
#define TITLE_IDLE_FRAMES 0xe10
#define TITLE_PRESS_DELAY 12 /* frames after a press during the logo's wipe in */
#define TITLE_WFC_INIT_FAILED 3
#define TITLE_STATE_FLAG_12 0x12

/* The messages the talk starts with (title_menu.c). */
#define TITLE_MESSAGE_WFC_FAILED 0x32
#define TITLE_MESSAGE_CARD_UNREADABLE 9 /* of "sp_etc_sequence2" */
#define TITLE_MESSAGE_PLAYER_0 0x24

/* The scenes left to and what the process between scenes is asked for with
 * (SceneExit_SetToScene's change_arg and next_arg). */
#define TITLE_SCENE_TITLE 0x2c
#define TITLE_SCENE_NEW 0x2d
#define TITLE_SCENE_2E 0x2e
#define TITLE_SCENE_30 0x30
#define TITLE_SCENE_6 6
#define TITLE_CHANGE_ARG 2

/* The vtable, and the processes' root class's. */
extern const u32 data_ov147_0229aa28[];
extern const u32 data_020da13c[];

/* "sp_etc_sequence1" (a pointer to it) and "sp_etc_sequence2". */
extern const char *const data_ov147_0229a8b0;
extern const char data_ov147_0229abe0[];

/* The buttons, and the pen: down, and down or up since the frame before. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
/* The screen's transition (main/screen_transition.h); the state block; main's sound object. */
extern u8 data_021c75b8;
extern u32 data_021dc7a8[];
extern Obj021c526c *data_021c526c;

/* The table of the states' {entry, frame} member functions (24 entries in the overlay's .bss,
 * of which the last eight are the symbol data_ov147_0229adcc), and its constants. */
extern MemberPointer data_ov147_0229ad4c[2 * TITLE_STATES];
extern MemberPointer data_ov147_0229adcc[8];
extern const MemberPointer data_ov147_0229a954, data_ov147_0229a9a4, data_ov147_0229a95c, data_ov147_0229a9ec,
    data_ov147_0229a96c, data_ov147_0229a974, data_ov147_0229a97c, data_ov147_0229a94c, data_ov147_0229a98c,
    data_ov147_0229a934, data_ov147_0229a994, data_ov147_0229a9f4, data_ov147_0229a9c4, data_ov147_0229a9d4,
    data_ov147_0229a9e4, data_ov147_0229a9dc, data_ov147_0229a8dc, data_ov147_0229a9cc, data_ov147_0229a8e4,
    data_ov147_0229a9bc, data_ov147_0229a9b4, data_ov147_0229a9ac, data_ov147_0229a8fc, data_ov147_0229a99c;

static SceneExit *title_entry_record(void)
{
    return (SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord();
}

/* Whether the screen is shown. */
static int title_screen_shown(void)
{
    return data_021c75b8 == SCREEN_TRANSITION_SHOWN;
}

/* Whether the pen has just touched. */
static int title_pen_touched(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The member function of the table at `entry` called on the scene, unless it is null. */
static void title_call_entry(const MemberPointer *entry, TitleScene *self)
{
    if (entry->function != 0) {
        MemberPointer_CallVoid(entry, self);
    }
}

/* --- The ways out --- */

/* func_ov147_02299b00 (TITLE_STATE_EXIT_REQUEST): with the screen shown and talk 0 closed, the
 * talk let go, process class 2 asked for (SceneProcessBase_Request) and the music stopped. */
void TitleScene_ExitByRequest(TitleScene *self)
{
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (title_screen_shown() && talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        SceneProcessBase_Request(2, 2, 0, 0);
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299b00, TitleScene_ExitByRequest)

/* func_ov147_02299b44 (TITLE_STATE_EXIT_REQUEST's entry). */
void TitleScene_EnterExitRequest(TitleScene *self)
{
    TitleScene_EndMusicOnLeave(self);
}
CLEAN_AS(func_ov147_02299b44, TitleScene_EnterExitRequest)

/* func_ov147_02299b4c (TITLE_STATE_EXIT_SCENE_30): with the screen shown and talk 0 closed, the
 * talk let go, scene 0x30 to go to (arguments 2 and 2) and the music stopped. */
void TitleScene_ExitToScene30(TitleScene *self)
{
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (title_screen_shown() && talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        SceneExit_SetToScene(title_entry_record(), TITLE_SCENE_30, TITLE_CHANGE_ARG, 2);
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299b4c, TitleScene_ExitToScene30)

/* func_ov147_02299b90 (TITLE_STATE_EXIT_SCENE_30's entry). */
void TitleScene_EnterExitScene30(TitleScene *self)
{
    TitleScene_EndMusicOnLeave(self);
}
CLEAN_AS(func_ov147_02299b90, TitleScene_EnterExitScene30)

/* func_ov147_02299b98 (TITLE_STATE_EXIT_JOB_1C): with the screen shown and talk 0 closed, the
 * talk let go, scene 0x2e to go to (arguments 2 and 3) with the activity's job 0x1c, and the
 * music stopped. */
void TitleScene_ExitForJob1c(TitleScene *self)
{
    if (!title_screen_shown()) {
        return;
    }
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        SceneExit_SetToScene(title_entry_record(), TITLE_SCENE_2E, TITLE_CHANGE_ARG, 3);
        ActivityJob_Ask1C();
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299b98, TitleScene_ExitForJob1c)

/* func_ov147_02299be0 (TITLE_STATE_EXIT_JOB_1C's entry). */
void TitleScene_EnterExitJob1c(TitleScene *self)
{
    TitleScene_EndMusicOnLeave(self);
}
CLEAN_AS(func_ov147_02299be0, TitleScene_EnterExitJob1c)

/* func_ov147_02299be8 (TITLE_STATE_EXIT_NEW): with the screen shown and talk 0 closed, the talk
 * let go, scene 0x2d to go to (arguments 2 and 0) and the music stopped; the start kind set
 * before is applied when the scene ends (TitleScene_End). */
void TitleScene_ExitToScene2d(TitleScene *self)
{
    if (!title_screen_shown()) {
        return;
    }
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        SceneExit_SetToScene(title_entry_record(), TITLE_SCENE_NEW, TITLE_CHANGE_ARG, 0);
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299be8, TitleScene_ExitToScene2d)

/* func_ov147_02299c2c (TITLE_STATE_EXIT_NEW's entry). */
void TitleScene_EnterExitNew(TitleScene *self)
{
    TitleScene_EndMusicOnLeave(self);
}
CLEAN_AS(func_ov147_02299c2c, TitleScene_EnterExitNew)

/* func_ov147_02299c34 (TITLE_STATE_EXIT_SCENE_6): with the screen shown and talk 0 closed, the
 * talk let go, scene 6 to go to (arguments 2 and 2) and the music stopped. */
void TitleScene_ExitToScene6(TitleScene *self)
{
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (title_screen_shown() && talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        SceneExit_SetToScene(title_entry_record(), TITLE_SCENE_6, TITLE_CHANGE_ARG, 2);
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299c34, TitleScene_ExitToScene6)

/* func_ov147_02299c78 (TITLE_STATE_EXIT_SCENE_6's entry). */
void TitleScene_EnterExitScene6(TitleScene *self)
{
    TitleScene_EndMusicOnLeave(self);
}
CLEAN_AS(func_ov147_02299c78, TitleScene_EnterExitScene6)

/* func_ov147_02299c80 (TITLE_STATE_EXIT_JOB_5): with the screen shown and talk 0 closed, the
 * talk let go, scene 0x2e to go to (arguments 2 and 3) with the activity's job 5, and the music
 * stopped. */
void TitleScene_ExitForJob5(TitleScene *self)
{
    if (!title_screen_shown()) {
        return;
    }
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        SceneExit_SetToScene(title_entry_record(), TITLE_SCENE_2E, TITLE_CHANGE_ARG, 3);
        ActivityJob_Ask5();
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299c80, TitleScene_ExitForJob5)

/* func_ov147_02299cc8 (TITLE_STATE_EXIT_JOB_5's entry). */
void TitleScene_EnterExitJob5(TitleScene *self)
{
    TitleScene_EndMusicOnLeave(self);
}
CLEAN_AS(func_ov147_02299cc8, TitleScene_EnterExitJob5)

/* func_ov147_02299cd0 (TITLE_STATE_EXIT_JOB_6): with the screen shown and talk 0 closed, the
 * talk let go, scene 0x2e to go to (arguments 2 and 3) with the activity's job 6 (the town
 * player picked removed), and the music stopped. */
void TitleScene_ExitForJob6(TitleScene *self)
{
    if (!title_screen_shown()) {
        return;
    }
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        SceneExit_SetToScene(title_entry_record(), TITLE_SCENE_2E, TITLE_CHANGE_ARG, 3);
        ActivityJob_Ask6();
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299cd0, TitleScene_ExitForJob6)

/* func_ov147_02299d18 (TITLE_STATE_EXIT_JOB_6's entry). */
void TitleScene_EnterExitJob6(TitleScene *self)
{
    TitleScene_EndMusicOnLeave(self);
}
CLEAN_AS(func_ov147_02299d18, TitleScene_EnterExitJob6)

/* --- The talk --- */

/* func_ov147_02299d20 (_ZN18Obj_ov147_0229aa2819func_ov147_02299d20Ev,
 * TITLE_STATE_END_TALK): once talk 0 is closed, the talk let go, the scene waits again and
 * message 1 is asked for. */
void TitleScene_WaitTalkClosed(TitleScene *self)
{
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    if (talk->state != TALK_OBJECT_CLOSED) {
        return;
    }
    TalkObject_DetachReceiver(talk);
    TitleScene_SetState(self, TITLE_STATE_WAIT);
    TitleMes_Request(&self->mes, 1);
}
CLEAN_AS(_ZN18Obj_ov147_0229aa2819func_ov147_02299d20Ev, TitleScene_WaitTalkClosed)

/* func_ov147_02299d4c (TITLE_STATE_END_TALK's entry): nothing. */
void TitleScene_EnterEndTalk(void) {}
CLEAN_AS(func_ov147_02299d4c, TitleScene_EnterEndTalk)

/* func_ov147_02299d50 (TITLE_STATE_TALK's frame): nothing; the receiver acts. */
void TitleScene_RunTalk(void) {}
CLEAN_AS(func_ov147_02299d50, TitleScene_RunTalk)

/* func_ov147_02299d54 (TITLE_STATE_TALK's entry): nothing. */
void TitleScene_EnterTalk(void) {}
CLEAN_AS(func_ov147_02299d54, TitleScene_EnterTalk)

/* func_ov147_02299d58 (_ZN18Obj_ov147_0229aa2819func_ov147_02299d58Ev,
 * TITLE_STATE_START_TALK): once the message has gone, the receiver reset (its slot 2) and given
 * its first message: 0x32 after a failed Wi-Fi start (cleared then), message 9 of
 * "sp_etc_sequence2" with the card's stamp unreadable, 0x24 with flag 0x12 of the state block,
 * else the greeting for the part of the day; talk 0 shows it, opening (its next state 1), and
 * the scene talks (TITLE_STATE_TALK). */
void TitleScene_StartTalk(TitleScene *self)
{
    if (TitleMes_IsIdle(&self->mes) == 0) {
        return;
    }
    TalkObject *talk = TalkObject_Get(TITLE_TALK);
    TitleReceiver *receiver = &self->receiver;
    MessageReceiver *message = &receiver->base.base;
    const u32 *vtable = (const u32 *) message->vtable;
    ((void (*)(TitleReceiver *))(uintptr_t) vtable[2])(receiver);

    if (self->wfc_failed != 0) {
        MessageReceiver_SetName(message, data_ov147_0229a8b0);
        message->message = TITLE_MESSAGE_WFC_FAILED;
        self->wfc_failed = 0;
    } else if (self->card_unreadable != 0) {
        MessageReceiver_SetName(message, data_ov147_0229abe0);
        message->message = TITLE_MESSAGE_CARD_UNREADABLE;
    } else if (StateBlock_TestFlag(data_021dc7a8, TITLE_STATE_FLAG_12) != 0) {
        MessageReceiver_SetName(message, data_ov147_0229a8b0);
        message->message = TITLE_MESSAGE_PLAYER_0;
    } else {
        MessageReceiver_SetName(message, data_ov147_0229a8b0);
        message->message = TitleMenu_GreetingMessage(receiver);
    }
    TalkObject_AttachReceiver(talk, &receiver->base);
    talk->next_state = TALK_OBJECT_OPENING;
    TitleScene_SetState(self, TITLE_STATE_TALK);
}
CLEAN_AS(_ZN18Obj_ov147_0229aa2819func_ov147_02299d58Ev, TitleScene_StartTalk)

/* func_ov147_02299e28 (TITLE_STATE_START_TALK's entry): nothing. */
void TitleScene_EnterStartTalk(void) {}
CLEAN_AS(func_ov147_02299e28, TitleScene_EnterStartTalk)

/* func_ov147_02299e2c (TITLE_STATE_IDLE_RESTART): once the message has gone, main's event flag
 * 0x10 set (the next title skips its logo), scene 0x2c to go to again (arguments 2 and 2) and
 * the music stopped. */
void TitleScene_RestartTitle(TitleScene *self)
{
    if (TitleMes_IsIdle(&self->mes) != 0) {
        EventQueue_SetFlag10();
        SceneExit_SetToScene(title_entry_record(), TITLE_SCENE_TITLE, TITLE_CHANGE_ARG, 2);
        TitleScene_StopMusic(self);
    }
}
CLEAN_AS(func_ov147_02299e2c, TitleScene_RestartTitle)

/* func_ov147_02299e58 (TITLE_STATE_IDLE_RESTART's entry): nothing. */
void TitleScene_EnterIdleRestart(void) {}
CLEAN_AS(func_ov147_02299e58, TitleScene_EnterIdleRestart)

/* func_ov147_02299e5c (_ZN18Obj_ov147_0229aa2819func_ov147_02299e5cEv, TITLE_STATE_WAIT):
 * waiting for the player.
 *
 * - A button press makes main's control icon the buttons', a touch the pen's.
 * - Unless B, X or Y is pressed: after a failed Wi-Fi start, with the card's stamp unreadable,
 *   or on START, A or a touch, with the screen shown and the logo loaded: while it wipes in the
 *   wipe is finished and the first message waits 12 frames; else, once that wait is over, the
 *   logo is sent away, the message taken away and the talk starts (TITLE_STATE_START_TALK).
 * - The wait counted; when it ends, message 0 is asked for.
 * - Once the logo is gone the idle time is counted: when it runs out the message is taken
 *   away and the title restarts (TITLE_STATE_IDLE_RESTART); before, it is held at 0xe10. */
void TitleScene_WaitForPress(TitleScene *self)
{
    if (data_021fbe40.pressed != 0) {
        ControlModeIcon_SetButtons();
    } else if (title_pen_touched()) {
        ControlModeIcon_SetTouch();
    }

    u16 pressed = data_021fbe40.pressed;
    if ((pressed & (TITLE_PAD_B | TITLE_PAD_X | TITLE_PAD_Y)) == 0) {
        int go = self->wfc_failed != 0 || self->card_unreadable != 0 || (pressed & TITLE_PAD_START) != 0 ||
                 (pressed & TITLE_PAD_A) != 0 || title_pen_touched();
        if (go && title_screen_shown() && self->logo_state != TITLE_LOGO_LOAD) {
            if (self->logo_state == TITLE_LOGO_WIPE_IN) {
                TitleLogo_FinishWipeIn(self);
                self->press_delay = TITLE_PRESS_DELAY;
            } else if (self->press_delay == 0) {
                TitleLogo_Dismiss(self);
                TitleMes_Withdraw(&self->mes);
                TitleScene_SetState(self, TITLE_STATE_START_TALK);
            }
        }
    }

    if (self->press_delay != 0) {
        self->press_delay--;
        if (self->press_delay == 0) {
            TitleMes_Request(&self->mes, 0);
        }
    }

    if (self->logo_state == TITLE_LOGO_GONE || self->logo_state == TITLE_LOGO_HIDDEN) {
        if (Countdown_Tick16(&self->idle_timer) == 0) {
            TitleMes_Withdraw(&self->mes);
            TitleScene_SetState(self, TITLE_STATE_IDLE_RESTART);
        }
    } else {
        self->idle_timer = TITLE_IDLE_FRAMES;
    }
}
CLEAN_AS(_ZN18Obj_ov147_0229aa2819func_ov147_02299e5cEv, TitleScene_WaitForPress)

/* func_ov147_02299fbc (TITLE_STATE_WAIT's entry): the idle time from its start. */
void TitleScene_ResetIdleTimer(TitleScene *self)
{
    self->idle_timer = TITLE_IDLE_FRAMES;
}
CLEAN_AS(func_ov147_02299fbc, TitleScene_ResetIdleTimer)

/* func_ov147_02299fc8 (_ZN18Obj_ov147_0229aa2819func_ov147_02299fc8Ei): state `state`
 * entered: its entry run, if any, then the state set.
 * REQUIRES: the state is below 12; the game reads past the table for others. */
void TitleScene_SetState(TitleScene *self, int state)
{
    title_call_entry(&data_ov147_0229ad4c[2 * state], self);
    self->state = state;
}
CLEAN_AS(_ZN18Obj_ov147_0229aa2819func_ov147_02299fc8Ei, TitleScene_SetState)

/* --- The music --- */

/* func_ov147_0229a000 (the ways out's entries): with the title's music started, the word at
 * 0x248 of main's sound object (the one a talk's end sets) given 0xb. */
void TitleScene_EndMusicOnLeave(TitleScene *self)
{
    if (self->music == TITLE_MUSIC_STARTED) {
        *(s32 *) (void *) ((u8 *) data_021c526c + 0x248) = 0xb;
    }
}
CLEAN_AS(func_ov147_0229a000, TitleScene_EndMusicOnLeave)

/* func_ov147_0229a01c: the music the scene started dropped (the title's music, or the value
 * of priority 1), a value of priority 1 added over 15 frames, and none started.
 * QUIRK: a `music` other than 0-2 drops nothing but still adds the value. */
void TitleScene_StopMusic(TitleScene *self)
{
    u8 music = self->music;
    if (music == TITLE_MUSIC_NONE) {
        return;
    }
    if (music == TITLE_MUSIC_STARTED) {
        Music_DropMusic(0);
    } else if (music == TITLE_MUSIC_VALUE) {
        Music_DropPriority(1);
    }
    Music_AddValue(1, 0xf, 0xf);
    self->music = TITLE_MUSIC_NONE;
}
CLEAN_AS(func_ov147_0229a01c, TitleScene_StopMusic)

/* func_ov147_0229a054: unless some is, music started: after main's event flag 0x10 a value of
 * priority 1, else the title's music (music 0 at priority 2). */
void TitleScene_StartMusic(TitleScene *self, int after_event)
{
    if (self->music != TITLE_MUSIC_NONE) {
        return;
    }
    if (after_event != 0) {
        Music_AddValue(1, 0xf, 0);
        self->music = TITLE_MUSIC_VALUE;
    } else {
        Music_Add(2, 0, 0x7f, 0);
        self->music = TITLE_MUSIC_STARTED;
    }
}
CLEAN_AS(func_ov147_0229a054, TitleScene_StartMusic)

/* --- The process --- */

/* func_ov147_0229a090 (_ZN18Obj_ov147_0229aa2819func_ov147_0229a090Ev, vtable slot 6): a frame:
 * the state's frame function, if any, the logo's and the message's. Answers 1. */
int TitleScene_Update(TitleScene *self)
{
    title_call_entry(&data_ov147_0229ad4c[2 * self->state + 1], self);
    TitleLogo_Update(self);
    TitleMes_Update(&self->mes);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov147_0229aa2819func_ov147_0229a090Ev, TitleScene_Update)

/* func_ov147_0229a0e0 (vtable slot 3): the scene ends: its music stopped, the logo's task
 * ended, main's event flag 1 cleared, and the start kind applied when it leaves for a new town
 * or player (TITLE_STATE_EXIT_NEW). Answers 1. */
int TitleScene_End(TitleScene *self)
{
    TitleScene_StopMusic(self);
    TitleMes_Release(&self->mes);
    LayerTask_End(&self->chars_task);
    EventQueue_ClearFlag1();
    if (self->state == TITLE_STATE_EXIT_NEW) {
        StartKind_Apply();
    }
    return 1;
}
CLEAN_AS(func_ov147_0229a0e0, TitleScene_End)

/* func_ov147_0229a110 (_ZN18Obj_ov147_0229aa2819func_ov147_0229a110Ev, vtable slot 0): the
 * scene starts: the receiver given the scene, the options in use cleared, main's event flag 1
 * set, a failed Wi-Fi start noted; waiting (TITLE_STATE_WAIT) with the logo to load and no
 * press; the message set up; the card's stamp checked; the music started; and after main's
 * event flag 0x10 (cleared then) no logo. Answers 1. */
int TitleScene_Init(TitleScene *self)
{
    TitleReceiver_SetScene(&self->receiver, self);
    PlayerOptions_Clear((PlayerOptions *) (uintptr_t) (u32) PlayerOptions_InUse());
    EventQueue_SetFlag1();
    if (WfcSetup_TakeInitResult() == TITLE_WFC_INIT_FAILED) {
        self->wfc_failed = 1;
    }
    TitleScene_SetState(self, TITLE_STATE_WAIT);
    self->logo_state = TITLE_LOGO_LOAD;
    self->press_delay = 0;
    TitleMes_Init(&self->mes);
    if (ActivityCard_Copy0StampUnreadable() == 1) {
        self->card_unreadable = 1;
    }
    TitleScene_StartMusic(self, EventQueue_TestFlag10() != 0);
    if (EventQueue_TestFlag10() != 0) {
        self->logo_state = TITLE_LOGO_SKIPPED;
        EventQueue_ClearFlag10();
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov147_0229aa2819func_ov147_0229a110Ev, TitleScene_Init)

/* func_ov147_0229a194 (vtable slot 17): destructed (TitleScene_Destruct) and freed. */
TitleScene *TitleScene_Delete(TitleScene *self)
{
    self->base.vtable = data_ov147_0229aa28;
    TitleMes_Destruct(&self->mes);
    TitleReceiver_Destruct(&self->receiver);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov147_0229a194, TitleScene_Delete)

/* func_ov147_0229a1cc (vtable slot 16): the destructor: the message and the receiver in turn,
 * then the root class's vtable and the process destructor. The logo's task has none. */
TitleScene *TitleScene_Destruct(TitleScene *self)
{
    self->base.vtable = data_ov147_0229aa28;
    TitleMes_Destruct(&self->mes);
    TitleReceiver_Destruct(&self->receiver);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov147_0229a1cc, TitleScene_Destruct)

/* func_ov147_0229a200: the constructor: the process, the root class's vtable then the scene's,
 * the receiver, the message and the logo's task. */
TitleScene *TitleScene_Construct(TitleScene *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov147_0229aa28;
    TitleReceiver_Construct(&self->receiver);
    TitleMes_Construct(&self->mes);
    LayerTask_Construct(&self->chars_task);
    return self;
}
CLEAN_AS(func_ov147_0229a200, TitleScene_Construct)

/* func_ov147_0229a238 (the create function, data_ov147_0229a91c): a new scene from the
 * auxiliary heap, zeroed and constructed; nothing when there is no memory.
 * QUIRK: the ROM's code leaves the new scene (or NULL) in r0 for its caller; the matching source
 * declares no result, and so does this. */
void TitleScene_New(void)
{
    TitleScene *self = Heap_AllocAuxZeroed(sizeof(TitleScene));
    if (self != NULL) {
        TitleScene_Construct(self);
    }
}
CLEAN_AS(func_ov147_0229a238, TitleScene_New)

/* __sinit_ov147_0229a700: the overlay's static initializer: the table of the states' {entry,
 * frame} member functions copied from its constants. Answers the address of the table's last
 * part (data_ov147_0229adcc), as the original leaves it. */
int TitleScene_InitStateTable(void)
{
    static const MemberPointer *const first[16] = {
        &data_ov147_0229a954, &data_ov147_0229a9a4, /* TITLE_STATE_WAIT */
        &data_ov147_0229a95c, &data_ov147_0229a9ec, /* TITLE_STATE_START_TALK */
        &data_ov147_0229a96c, &data_ov147_0229a974, /* TITLE_STATE_TALK */
        &data_ov147_0229a97c, &data_ov147_0229a94c, /* TITLE_STATE_END_TALK */
        &data_ov147_0229a98c, &data_ov147_0229a934, /* TITLE_STATE_EXIT_JOB_6 */
        &data_ov147_0229a994, &data_ov147_0229a9f4, /* TITLE_STATE_EXIT_JOB_5 */
        &data_ov147_0229a9c4, &data_ov147_0229a9d4, /* TITLE_STATE_EXIT_SCENE_6 */
        &data_ov147_0229a9e4, &data_ov147_0229a9dc, /* TITLE_STATE_EXIT_NEW */
    };
    static const MemberPointer *const last[8] = {
        &data_ov147_0229a8dc, &data_ov147_0229a9cc, /* TITLE_STATE_EXIT_REQUEST */
        &data_ov147_0229a8e4, &data_ov147_0229a9bc, /* TITLE_STATE_EXIT_JOB_1C */
        &data_ov147_0229a9b4, &data_ov147_0229a9ac, /* TITLE_STATE_EXIT_SCENE_30 */
        &data_ov147_0229a8fc, &data_ov147_0229a99c, /* TITLE_STATE_IDLE_RESTART */
    };
    for (int i = 0; i < 16; i++) {
        data_ov147_0229ad4c[i] = *first[i];
    }
    for (int i = 0; i < 8; i++) {
        data_ov147_0229adcc[i] = *last[i];
    }
    return (int) (uintptr_t) data_ov147_0229adcc;
}
CLEAN_AS(__sinit_ov147_0229a700, TitleScene_InitStateTable)
