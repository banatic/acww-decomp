/* A talk's steps from state to state (talk_flow.h). */
#include "talk_flow.h"

#include "clean.h"
#include "talk_box.h"
#include "music_volume.h"
#include "ov004/member_pointer.h"
#include "quick_message.h"
#include "session.h"
#include "sound.h"
#include "talk_object.h"
#include "talk_voice.h"

static_assert(offsetof(TalkFlowTalk, slide) == 0x0c, "talk slide");
static_assert(offsetof(TalkFlowTalk, mode) == 0x14, "talk mode");
static_assert(offsetof(TalkFlowTalk, window) == 0x1c, "talk window");
static_assert(offsetof(TalkFlowTalk, window_offset) == 0x9c, "talk window offset");
static_assert(offsetof(TalkFlowTalk, page) == 0x684, "talk page");
static_assert(offsetof(TalkFlowTalk, walker) == 0x13b8, "talk walker");
static_assert(offsetof(TalkFlowTalk, walk) == 0x149c, "talk walk");
static_assert(offsetof(TalkFlowTalk, receiver) == 0x14a8, "talk receiver");
static_assert(offsetof(TalkFlowTalk, last_chars) == 0x1a2c, "talk last characters");
static_assert(offsetof(TalkFlowTalk, message) == 0x1e77, "talk message");
static_assert(offsetof(TalkFlowTalk, silent) == 0x1e98, "talk silent");
static_assert(offsetof(TalkFlowTalk, quiet) == 0x1e9a, "talk quiet");
static_assert(sizeof(TalkFlowTalk) == 0x1e9c, "talk");

/* The window's offsets by slide step: -101, -48, -20, -10, 0. */
extern const s16 data_020def28[];

/* The message numbers: the one that ends the talk, and the one meaning no message given. */
extern u8 data_021f43e8;
extern u8 data_021f43f8;

/* The field's sound object; its music volume slots are at 0x1c4 (music_volume.h). */
extern u8 *data_021c526c;
#define TALK_FLOW_MUSIC_VOLUME 0x1c4

/* The talk's sound effects. */
#define TALK_FLOW_SE_CLOSE 10

/* The receiver's slot told the talk closes. */
#define TALK_FLOW_SLOT_CLOSING 0x70

/* The talk as talk_object.h lays it out. */
static TalkObject *talk_flow_object(TalkFlowTalk *talk)
{
    return (TalkObject *) (void *) talk;
}

/* What TalkFlow_WalkStopped does after setting the states. */
enum TalkFlowAction {
    TALK_FLOW_NO_ACTION,
    TALK_FLOW_AFTER_CHOICES,
    TALK_FLOW_SAME_WINDOW,
    TALK_FLOW_NEW_PAGE,
    TALK_FLOW_NEXT_MESSAGE,
    TALK_FLOW_END,
    TALK_FLOW_END_LAST,
};

/* func_02066abc: the walk stopped and the player went on:
 * - with the choices asked for, they open (and the states stay);
 * - after the choices, at a stop that keeps the window or at a full page, the walk goes on
 *   (the walker running, the talk writing);
 * - else the talk closes when its message is the last one (data_021f43e8) or it is not kept
 *   open (mode 4), the walker idle; a kept talk given a message follows with it (writing);
 *   one given none stays as it is. */
void TalkFlow_WalkStopped(TalkFlowTalk *talk)
{
    s32 walk = talk->walker.state;
    int page_full = walk == TALK_TAGS_STATE_PAGE_FULL;
    int stop_keep = walk == TALK_TAGS_STATE_STOP_KEEP;
    int choosing = walk == TALK_TAGS_STATE_CHOOSING;
    s32 new_walk = TALK_FLOW_NONE;
    s32 next = TALK_FLOW_NONE;
    int follow = 0;
    enum TalkFlowAction action = TALK_FLOW_NO_ACTION;

    if (talk->choices_asked != 0) {
        talk->choices_asked = 0;
        TalkObject_OpenChoices((TalkObject *) talk, 0);
    } else if (page_full || stop_keep || choosing) {
        new_walk = TALK_TAGS_STATE_RUNNING;
        next = TALK_FLOW_WRITING;
        if (choosing) {
            action = TALK_FLOW_AFTER_CHOICES;
        } else if (stop_keep) {
            action = TALK_FLOW_SAME_WINDOW;
        } else {
            action = TALK_FLOW_NEW_PAGE;
        }
    } else {
        u8 none = data_021f43f8;
        u8 message = talk->message;
        u8 last = data_021f43e8;
        if (message == last) {
            new_walk = TALK_TAGS_STATE_IDLE;
            next = TALK_FLOW_CLOSING;
            action = TALK_FLOW_END_LAST;
        } else if (talk->mode != TALK_FLOW_MODE_KEPT) {
            new_walk = TALK_TAGS_STATE_IDLE;
            next = TALK_FLOW_CLOSING;
            action = TALK_FLOW_END;
        } else if (message != none) {
            follow = 1;
            action = TALK_FLOW_NEXT_MESSAGE;
        }
    }

    if (follow) {
        TalkObject_StartGivenMessage(talk_flow_object(talk));
        new_walk = TALK_TAGS_STATE_RUNNING;
        next = TALK_FLOW_WRITING;
    }
    if (new_walk != TALK_FLOW_NONE) {
        talk->walker.state = new_walk;
    }
    if (next == TALK_FLOW_NONE) {
        return;
    }
    talk->next = next;
    switch (action) {
        case TALK_FLOW_AFTER_CHOICES:
            TalkFlow_AfterChoices(talk_flow_object(talk));
            break;
        case TALK_FLOW_SAME_WINDOW:
            TalkFlow_SameWindow(talk_flow_object(talk));
            break;
        case TALK_FLOW_NEW_PAGE:
            TalkFlow_NewPage(talk_flow_object(talk));
            break;
        case TALK_FLOW_NEXT_MESSAGE:
            TalkFlow_NextMessage(talk_flow_object(talk));
            break;
        case TALK_FLOW_END:
            TalkFlow_End(talk_flow_object(talk));
            break;
        case TALK_FLOW_END_LAST:
            TalkFlow_EndAtLast(talk_flow_object(talk));
            break;
        case TALK_FLOW_NO_ACTION:
            break;
    }
}
CLEAN_AS(func_02066abc, TalkFlow_WalkStopped)

/* func_02066bd0 (step of state 5, gone): nothing. */
void TalkFlow_StepGone(void *talk)
{
    (void) talk;
}
CLEAN_AS(func_02066bd0, TalkFlow_StepGone)

/* func_02066bd4 (entry of state 5, gone): the window closed. */
void TalkFlow_EnterGone(TalkFlowTalk *talk)
{
    TalkBox_Hide((TalkBox *) (void *) talk->window);
}
CLEAN_AS(func_02066bd4, TalkFlow_EnterGone)

/* func_02066be0 (step of state 4, closing): the window slides a step further; once the slide
 * is done (the frame after it reached 0), the object at 0x680 is freed and the page's boxes,
 * and the talk is gone, or, kept open (mode 4), at rest with its sounds back on.
 * REQUIRES: slide is 0 to 4 (TalkFlow_EnterClosing sets 4); below 0 the ROM reads before the
 * offsets. */
void TalkFlow_StepClosing(TalkFlowTalk *talk)
{
    int done = 0;
    if (talk->slide > 0) {
        talk->slide--;
    } else {
        done = 1;
    }
    talk->window_offset = data_020def28[talk->slide];
    TalkBox_SetOffset((TalkBox *) (void *) talk->window, talk->window_offset);
    if (!done) {
        return;
    }
    TalkObject_FreeNameBox(talk_flow_object(talk));
    TalkPage_FreeBoxes(&talk->page);
    if (talk->mode != TALK_FLOW_MODE_KEPT) {
        talk->next = TALK_FLOW_GONE;
    } else {
        talk->silent = 0;
        talk->quiet = 0;
        talk->next = TALK_FLOW_CLOSED;
    }
}
CLEAN_AS(func_02066be0, TalkFlow_StepClosing)

/* func_02066c54 (entry of state 4, closing): the window's closing begins at the first step of
 * the slide; unless silent, the voice stops and, but in modes 1 to 3, the music's volume comes
 * back (slot 2 of the field's volume slots); unless quiet, the closing sound; the receiver
 * told (its slot 0x70).
 * REQUIRES: the talk has a receiver. */
void TalkFlow_EnterClosing(TalkFlowTalk *talk)
{
    typedef void TalkFlowReceiverSlot(TalkReceiver * receiver);

    TalkBox_HideArrow((TalkBox *) (void *) talk->window);
    talk->slide = TALK_FLOW_SLIDE_STEPS;
    talk->window_offset = data_020def28[talk->slide];
    if (talk->silent == 0) {
        TalkVoice_Stop((TalkVoice *) (void *) talk->last_chars);
        if (talk->mode != 1 && talk->mode != 2 && talk->mode != 3) {
            MusicVolume_EndSlot2((MusicVolume *) (void *) (data_021c526c + TALK_FLOW_MUSIC_VOLUME));
        }
    }
    if (talk->quiet == 0) {
        SoundSys_PlaySe(TALK_FLOW_SE_CLOSE);
    }
    TalkReceiver *receiver = talk->receiver;
    const u8 *vtable = (const u8 *) receiver->base.vtable;
    u32 closing = *(const u32 *) (const void *) (vtable + TALK_FLOW_SLOT_CLOSING);
    ((TalkFlowReceiverSlot *) (uintptr_t) closing)(receiver);
}
CLEAN_AS(func_02066c54, TalkFlow_EnterClosing)

/* func_02066cd4 (step of state 3, writing): the walker hurried when the player asks; the last
 * characters' codes reset, the walk run a step, the page drawn, and the
 * characters voiced unless silent. Once the text ended (slide cleared the frame before), or
 * the walk stopped (a full page, a stop, the choices) or is idle, the talk waits (state 2),
 * the receiver first told its answer when the text ended; its last characters cleared. */
void TalkFlow_StepWriting(TalkFlowTalk *talk)
{
    if (TalkObject_HurryPressed((TalkObject *) talk)) {
        TalkTags_Hurry(&talk->walker);
    }
    TalkVoice_Clear((TalkVoice *) (void *) talk->last_chars, 0);
    MessageWalkRun_Step(&talk->walk);
    TalkPage_Update(&talk->page);
    if (talk->silent == 0) {
        TalkVoice_Update((TalkVoice *) (void *) talk->last_chars);
    }

    s32 walk = talk->walker.state;
    int ended = talk->slide == 0;
    int stopped = ended || walk == TALK_TAGS_STATE_PAGE_FULL || walk == TALK_TAGS_STATE_STOP_KEEP ||
                  walk == TALK_TAGS_STATE_CHOOSING || walk == TALK_TAGS_STATE_IDLE;
    if (walk == TALK_TAGS_STATE_ENDED) {
        talk->slide = 0;
    }
    if (!stopped) {
        return;
    }
    if (ended) {
        TalkObject_TellMessageEnded(talk_flow_object(talk));
    }
    talk->next = TALK_FLOW_WAITING;
    TalkObject_ClearVoice((TalkObject *) talk);
}
CLEAN_AS(func_02066cd4, TalkFlow_StepWriting)

/* The window's offsets while it slides in, by step: 0, -7, -14, -25, -50, -101. */
extern const s16 data_020def1c[];

/* The table of the states' entries (a function-local static of the game, filled on the first
 * call): the guard, the table, and the constants it is filled from (Base_02068144::func_020670fc,
 * func_02066f8c, func_02066f20, func_02066db0, func_02066c54, func_02066bd4). */
extern u32 data_021cda94;
extern MemberPointer data_021cdb44[6];
extern const MemberPointer data_020dec04, data_020ded0c, data_020dee1c, data_020de81c, data_020de844, data_020de884;

/* The link session, or NULL. */
extern NetSession *data_020ccf94;

/* The window's slide in: TALK_FLOW_OPEN_STEPS steps down to 0, each an offset of
 * data_020def1c. */
#define TALK_FLOW_OPEN_STEPS 5

/* While writing, `slide` is TALK_FLOW_TEXT_GOING until the text ended (TalkFlow_StepWriting
 * clears it). */
#define TALK_FLOW_TEXT_GOING 1

/* The window's kind (Block020a8248_GroupOfKind of the message) for a speaker without a name. */
#define TALK_FLOW_KIND_NO_SPEAKER 5

/* The talk's sound effects: the window opens, the player goes on, the choices follow. */
#define TALK_FLOW_SE_OPEN 9
#define TALK_FLOW_SE_GO_ON 0x10
#define TALK_FLOW_SE_CHOICES 0x13

/* The receiver's vtable slots the talk calls here: the villager talked to (or NULL), and the
 * walk going on after a stop. */
#define TALK_FLOW_SLOT_VILLAGER 0x68
#define TALK_FLOW_SLOT_GOES_ON 0x74

/* The receiver's vtable entry at `slot`. */
static u32 talk_flow_receiver_slot(const TalkReceiver *receiver, int slot)
{
    const u8 *vtable = (const u8 *) receiver->base.vtable;
    return *(const u32 *) (const void *) (vtable + slot);
}

/* The talk's message window. */
static TalkBox *talk_flow_box(TalkObject *talk)
{
    return (TalkBox *) (void *) talk->window;
}

/* func_02066db0 (entry of state 3, writing): the window's arrow in pose 0; the text going. */
void TalkFlow_EnterWriting(TalkObject *talk)
{
    TalkBox_HideArrow(talk_flow_box(talk));
    talk->slide = TALK_FLOW_TEXT_GOING;
}
CLEAN_AS(func_02066db0, TalkFlow_EnterWriting)

/* func_02066dc4 (step of state 2, waiting): the walk run a step; a choice decided is taken.
 * Then, at a full page, the end of the text or a stop that keeps the window:
 * - while a scene command holds the talk or a choice window is shown, the window's arrow
 *   back in pose 0;
 * - else the walk goes on when the talk was asked to; otherwise the arrow goes from pose 0
 *   to 1, from 1 to 2 when the player goes on or the talk's countdown runs out (with the
 *   sound of going on, and that of the choices when they follow), from 2 to 3 once its
 *   animations are done, and once they are done in 3 the walk goes on.
 * While the slider window is open, the walk goes on once no choice window is shown. */
void TalkFlow_StepWaiting(TalkObject *talk)
{
    MessageWalkRun_Step(&talk->run);
    s32 walk = talk->walker.state;
    int stopped = walk == TALK_TAGS_STATE_PAGE_FULL || walk == TALK_TAGS_STATE_ENDED || walk == TALK_TAGS_STATE_STOP_KEEP;
    int choosing = walk == TALK_TAGS_STATE_CHOOSING;
    TalkFlowTalk *flow = (TalkFlowTalk *) (void *) talk;
    TalkBox *box = talk_flow_box(talk);

    if (TalkWindows_Decided(&talk->choice_windows)) {
        TalkFlow_TakeAnswer(talk);
    }
    if (!stopped) {
        if (choosing && TalkWindows_NoneShown(&talk->choice_windows)) {
            TalkFlow_WalkStopped(flow);
        }
        return;
    }
    if (talk->held != 0 || !TalkWindows_NoneShown(&talk->choice_windows)) {
        if (!TalkBox_ArrowHidden(box)) {
            TalkBox_HideArrow(talk_flow_box(talk));
        }
        return;
    }
    if (talk->go_on != 0) {
        TalkFlow_WalkStopped(flow);
        return;
    }
    if (TalkBox_ArrowHidden(box)) {
        TalkBox_ShowArrow(box);
        return;
    }
    if (TalkBox_ArrowWaiting(box)) {
        if (TalkObject_AdvancePressed(talk) || TalkObject_AutoAdvanceDue(talk)) {
            TalkBox_SetArrowPose2(box);
            if (talk->quiet == 0) {
                SoundSys_PlaySe(TALK_FLOW_SE_GO_ON);
            }
            if (talk->choices_asked != 0 || talk->walker.choices_shown != 0) {
                SoundSys_PlaySe(TALK_FLOW_SE_CHOICES);
            }
        }
        return;
    }
    if (TalkBox_ArrowPose2Done(box)) {
        TalkBox_SetArrowPose3(box);
        return;
    }
    if (TalkBox_ArrowPose3Done(box)) {
        TalkFlow_WalkStopped(flow);
    }
}
CLEAN_AS(func_02066dc4, TalkFlow_StepWaiting)

/* func_02066f20 (entry of state 2, waiting): the window's arrow in pose 0. */
void TalkFlow_EnterWaiting(TalkObject *talk)
{
    TalkBox_HideArrow(talk_flow_box(talk));
}
CLEAN_AS(func_02066f20, TalkFlow_EnterWaiting)

/* func_02066f2c (step of state 1, opening): the window slides a step further in; once the
 * slide is done (the frame after it reached 0) the voice starts, unless silent, and the talk
 * writes.
 * REQUIRES: slide is 0 to 5 (TalkFlow_EnterOpening sets 5); below 0 the ROM reads before the
 * offsets. */
void TalkFlow_StepOpening(TalkObject *talk)
{
    int done = 0;
    if (talk->slide > 0) {
        talk->slide--;
    } else {
        done = 1;
    }
    talk->window_offset = data_020def1c[talk->slide];
    TalkBox_SetOffset(talk_flow_box(talk), talk->window_offset);
    if (!done) {
        return;
    }
    if (talk->silent == 0) {
        TalkVoice_Start(&talk->voice);
    }
    talk->next_state = TALK_OBJECT_WRITING;
}
CLEAN_AS(func_02066f2c, TalkFlow_StepOpening)

/* func_02066f8c (entry of state 1, opening): the input mode taken; the message begun (the one
 * the talk was given, unless the talk is kept open for more messages, mode 4); the window
 * built for the message's kind and the speaker (a speaker with an empty name that is not
 * unnamed, on a message of kind 0, gets the kind of no speaker), the voice told the kind; the
 * window's screen set up and the window placed at the first step of its slide in, its sprite
 * in pose 0; the speaker's name box made and the page's boxes; this system's quick message
 * dismissed in a link; unless asked not to (byte 0x1e99), the opening sound; unless silent
 * and but in modes 1 to 3, the music's volume lowered (slot 2 of the field's volume slots).
 * A talk that was not kept open is from now on (mode 4). */
void TalkFlow_EnterOpening(TalkObject *talk)
{
    typedef const char *TalkFlowChars(TalkReceiverName * name);
    typedef void *TalkFlowVillager(TalkReceiver * receiver);

    TalkObject_TakeInputMode(talk);
    int fresh = talk->mode != TALK_FLOW_MODE_KEPT;
    if (fresh) {
        TalkObject_StartGivenMessage(talk);
    } else {
        TalkObject_StartMessage(talk);
    }

    int kind = Block020a8248_GroupOfKind(&talk->unk_14ac);
    TalkReceiverName *speaker = TalkReceiver_SpeakerName(talk->receiver);
    const char *name = ((TalkFlowChars *) (uintptr_t) speaker->vtable->buffer)(speaker);
    int style = TalkReceiver_SpeakerStyle(talk->receiver);
    TalkReceiver *receiver = talk->receiver;
    TalkFlowVillager *villager = (TalkFlowVillager *) (uintptr_t) talk_flow_receiver_slot(receiver, TALK_FLOW_SLOT_VILLAGER);
    int no_villager = villager(receiver) == NULL;
    int nameless = TalkReceiver_IsNameless(talk->receiver);
    if (nameless == 0 && kind == 0 && name[0] == 0 && name[1] == 0) {
        kind = TALK_FLOW_KIND_NO_SPEAKER;
    }
    TalkBox_Load(talk_flow_box(talk), kind, nameless, style, (u8) no_villager);
    TalkVoice_SetKind(&talk->voice, kind);

    TalkBox_SetUpBg2();
    TalkBox_Upload(talk_flow_box(talk));
    TalkBox_Show();
    TalkBox_FreeFiles(talk_flow_box(talk));
    talk->slide = TALK_FLOW_OPEN_STEPS;
    talk->window_offset = data_020def1c[talk->slide];
    TalkBox_SetOffset(talk_flow_box(talk), talk->window_offset);
    TalkBox_HideArrow(talk_flow_box(talk));
    TalkObject_MakeNameBox(talk);
    TalkPage_NewBoxes(&talk->page);

    if (data_020ccf94 != NULL) {
        QuickMessage_Dismiss((unsigned int) data_020ccf94->local_slot);
    }
    if (talk->unk_1e99 == 0) {
        SoundSys_PlaySe(TALK_FLOW_SE_OPEN);
    }
    if (talk->silent == 0 && talk->mode != 1 && talk->mode != 2 && talk->mode != 3) {
        MusicVolume_BeginSlot2((MusicVolume *) (void *) (data_021c526c + TALK_FLOW_MUSIC_VOLUME));
    }
    if (fresh) {
        talk->mode = TALK_FLOW_MODE_KEPT;
    }
}
CLEAN_AS(func_02066f8c, TalkFlow_EnterOpening)

/* func_020670f8 (step of state 0, closed): nothing. */
void TalkFlow_StepClosed(void *talk)
{
    (void) talk;
}
CLEAN_AS(func_020670f8, TalkFlow_StepClosed)

/* func_020670fc (entry of state 0, closed): the window closed. */
void TalkFlow_EnterClosed(TalkObject *talk)
{
    TalkBox_Hide(talk_flow_box(talk));
}
CLEAN_AS(func_020670fc, TalkFlow_EnterClosed)

/* func_02067108: the state asked for in `next_state` entered (its entry run through the
 * table of member functions), and none asked for any more.
 * REQUIRES: next_state is 0 to 6. */
void TalkFlow_EnterNext(TalkObject *talk)
{
    static const MemberPointer *const constants[6] = {
        &data_020dec04, &data_020ded0c, &data_020dee1c, &data_020de81c, &data_020de844, &data_020de884,
    };
    MemberTable_InitOnce(&data_021cda94, data_021cdb44, constants, 6);
    if (talk->next_state == TALK_OBJECT_NO_STATE) {
        return;
    }
    talk->state = talk->next_state;
    MemberPointer_CallVoid(&data_021cdb44[talk->next_state], talk);
    talk->next_state = TALK_OBJECT_NO_STATE;
}
CLEAN_AS(func_02067108, TalkFlow_EnterNext)

/* func_020671b0: the choice decided: the talk goes on with the message of the answer picked
 * (its number and file), the picked answer's text walked (its tags run on the talk), and the
 * receiver told the answer. */
void TalkFlow_TakeAnswer(TalkObject *talk)
{
    const u8 *message = TalkAnswers_Picked70(&talk->answers);
    const char *name = TalkAnswers_PickedName(&talk->answers);
    TalkObject_SetMessage(talk, message, name);
    TalkObject_GoOn(talk);
    talk->unk_1e96 = 1;
    TalkObject_RunAnswerText(talk);
    TalkObject_TellAnswer(talk);
}
CLEAN_AS(func_020671b0, TalkFlow_TakeAnswer)

/* func_02067b1c: the talk ends at its last message: as TalkFlow_End, and its message parts
 * and values cleared, and the talk no longer held. */
void TalkFlow_EndAtLast(TalkObject *talk)
{
    TalkFlow_End(talk);
    TalkObject_ClearParts(talk);
    TalkObject_ClearValues(talk);
    TalkObject_Release(talk);
}
CLEAN_AS(func_02067b1c, TalkFlow_EndAtLast)

/* func_02067b3c: the talk ends: as for the next message, and the opening sound back on. */
void TalkFlow_End(TalkObject *talk)
{
    TalkFlow_NextMessage(talk);
    talk->unk_1e99 = 0;
}
CLEAN_AS(func_02067b3c, TalkFlow_End)

/* func_02067b54: the walk goes on with the next message: the walker's colour reset, the texts
 * loaded from the villager and the others cleared, and a new page. */
void TalkFlow_NextMessage(TalkObject *talk)
{
    TalkTags_ResetColour(&talk->walker);
    TalkObject_ClearRandomNpc(talk);
    TalkObject_ClearOtherPlayer(talk);
    TalkObject_ClearCatchphrase(talk);
    TalkObject_ClearTownName(talk);
    TalkObject_ClearPlayerName(talk);
    TalkObject_ClearLikedNpc(talk);
    TalkObject_ClearDislikedNpc(talk);
    TalkObject_ClearBoom(talk);
    TalkObject_ClearImpression(talk);
    TalkObject_ClearNickname(talk);
    TalkObject_ClearPraise(talk);
    TalkObject_ClearMemory(talk);
    TalkFlow_NewPage(talk);
}
CLEAN_AS(func_02067b54, TalkFlow_NextMessage)

/* func_02067bb8: the walk goes on on a new page: the walker's lines and the page's boxes
 * cleared, then as in the same window. */
void TalkFlow_NewPage(TalkObject *talk)
{
    TalkTags_NewPage(&talk->walker);
    TalkPage_ClearBoxes(&talk->page);
    TalkFlow_SameWindow(talk);
}
CLEAN_AS(func_02067bb8, TalkFlow_NewPage)

/* func_02067be0: the walk goes on in the same window: the talk no longer asked to go on, as
 * after the choices, and the receiver told (its slot 0x74). */
void TalkFlow_SameWindow(TalkObject *talk)
{
    typedef void TalkFlowGoesOn(TalkReceiver * receiver);

    TalkObject_StopGoingOn(talk);
    TalkFlow_AfterChoices(talk);
    TalkReceiver *receiver = talk->receiver;
    ((TalkFlowGoesOn *) (uintptr_t) talk_flow_receiver_slot(receiver, TALK_FLOW_SLOT_GOES_ON))(receiver);
}
CLEAN_AS(func_02067be0, TalkFlow_SameWindow)

/* func_02067c04: the walk goes on after the choices: the walker's hurry and the talk's
 * countdown cleared. */
void TalkFlow_AfterChoices(TalkObject *talk)
{
    TalkTags_ClearHurry(&talk->walker);
    TalkObject_ClearAutoAdvance(talk);
}
CLEAN_AS(func_02067c04, TalkFlow_AfterChoices)
