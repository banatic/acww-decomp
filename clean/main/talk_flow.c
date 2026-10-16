/* A talk's steps from state to state (talk_flow.h). */
#include "talk_flow.h"

#include "clean.h"
#include "music_volume.h"
#include "sound.h"

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

/* The choices open now (`asked` 0), or are asked to open once the walk stops (`asked` 1). */
extern void func_02068388(TalkFlowTalk *talk, int asked);
/* The talk follows with the message it was given (its number to the receiver, then the talk
 * begun again). */
extern void func_02067218(TalkFlowTalk *talk);
/* The walk goes on: after the choices (func_02067c04), on in the same window (func_02067be0),
 * on a new page (func_02067bb8), with the next message (func_02067b54); the talk ends
 * (func_02067b3c), the talk ends at its last message (func_02067b1c). */
extern void func_02067c04(TalkFlowTalk *talk);
extern void func_02067be0(TalkFlowTalk *talk);
extern void func_02067bb8(TalkFlowTalk *talk);
extern void func_02067b54(TalkFlowTalk *talk);
extern void func_02067b3c(TalkFlowTalk *talk);
extern void func_02067b1c(TalkFlowTalk *talk);
/* The window: its offset, opened, closed. */
extern void func_02068d74(void *window, int offset);
extern void func_02068d38(void *window);
extern void func_02068d80(void *window);
/* The object at the talk's 0x680 freed. */
extern void func_020675c0(TalkFlowTalk *talk);
/* The last characters: their voice stopped; their codes reset (with `all`, one more); voiced. */
extern void func_0206899c(void *last_chars);
extern void func_02068ae4(void *last_chars, int all);
extern void func_02068a04(void *last_chars);
/* Whether the player asks to hurry (the pen or a button; never while silent). */
extern int func_02067d7c(TalkFlowTalk *talk);
/* The answer the receiver waits for, told to it (its slot 0x14). */
extern void func_02067540(TalkFlowTalk *talk);
/* The talk's byte 0x1e97 cleared and its last characters cleared. */
extern void func_020680d0(TalkFlowTalk *talk);

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
        func_02068388(talk, 0);
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
        func_02067218(talk);
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
            func_02067c04(talk);
            break;
        case TALK_FLOW_SAME_WINDOW:
            func_02067be0(talk);
            break;
        case TALK_FLOW_NEW_PAGE:
            func_02067bb8(talk);
            break;
        case TALK_FLOW_NEXT_MESSAGE:
            func_02067b54(talk);
            break;
        case TALK_FLOW_END:
            func_02067b3c(talk);
            break;
        case TALK_FLOW_END_LAST:
            func_02067b1c(talk);
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
    func_02068d80(talk->window);
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
    func_02068d74(talk->window, talk->window_offset);
    if (!done) {
        return;
    }
    func_020675c0(talk);
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

    func_02068d38(talk->window);
    talk->slide = TALK_FLOW_SLIDE_STEPS;
    talk->window_offset = data_020def28[talk->slide];
    if (talk->silent == 0) {
        func_0206899c(talk->last_chars);
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
    if (func_02067d7c(talk)) {
        TalkTags_Hurry(&talk->walker);
    }
    func_02068ae4(talk->last_chars, 0);
    MessageWalkRun_Step(&talk->walk);
    TalkPage_Update(&talk->page);
    if (talk->silent == 0) {
        func_02068a04(talk->last_chars);
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
        func_02067540(talk);
    }
    talk->next = TALK_FLOW_WAITING;
    func_020680d0(talk);
}
CLEAN_AS(func_02066cd4, TalkFlow_StepWriting)
