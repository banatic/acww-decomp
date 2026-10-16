/* A talk's steps from state to state (the talk: 0x1e9c bytes, two of them at data_021cda88,
 * talk_process.h; Base_02068144 of include/cpp/main/Base_02068144.h).
 *
 * Each frame func_02068144 runs the step of the talk's `state`, and func_02067108 enters the
 * state asked for in `next` (then sets `next` back to TALK_FLOW_NONE). The states here:
 * - 3, writing (TalkFlow_StepWriting): the message's text walked a little each frame into the
 *   window's page, the characters voiced, until the walk stops or the text ended; then the
 *   talk waits (state 2);
 * - when the walk stopped and the player went on (TalkFlow_WalkStopped): the choices asked for
 *   open, or the walk goes on (a new page, or the same window), or the talk follows with the
 *   message it was given, or it closes (state 4);
 * - 4, closing: the window slides away over four frames (TalkFlow_EnterClosing,
 *   TalkFlow_StepClosing); then the talk is gone (state 5), or back at rest (state 0) when it
 *   is kept open for more messages (mode 4);
 * - 5, gone (TalkFlow_EnterGone, TalkFlow_StepGone). */
#ifndef CLEAN_MAIN_TALK_FLOW_H
#define CLEAN_MAIN_TALK_FLOW_H

#include "main/message_walker.h"
#include "main/talk_page.h"
#include "main/talk_receiver.h"
#include "main/talk_object.h"
#include "main/talk_tags.h"
#include "types.h"

/* A talk's states (TalkFlowTalk.state and .next). */
enum TalkFlowState {
    TALK_FLOW_CLOSED = 0,
    TALK_FLOW_WAITING = 2, /* the walk stopped: waiting for the player (func_02066dc4) */
    TALK_FLOW_WRITING = 3,
    TALK_FLOW_CLOSING = 4,
    TALK_FLOW_GONE = 5,
    TALK_FLOW_NONE = 6, /* in `next`: no state asked for */
};

/* The talk's mode (word 0x14, which scene commands set) that keeps it open for more messages. */
#define TALK_FLOW_MODE_KEPT 4

/* The window's slide while closing: TALK_FLOW_SLIDE_STEPS steps down to 0, each an offset of
 * data_020def28. */
#define TALK_FLOW_SLIDE_STEPS 4

typedef struct TalkFlowTalk {
    u32 unk_00;
    s32 state;         /* 0x04: TalkFlowState */
    s32 next;          /* 0x08: the state to enter, TALK_FLOW_NONE for none */
    s32 slide;         /* 0x0c: the closing slide's step; while writing, 0 once the text ended */
    s32 unk_10;        /* 0x10 */
    s32 mode;          /* 0x14: set by the scene commands (scene_command.h) */
    u8 choices_asked;  /* 0x18: the choices open when the walk stops (func_02068388) */
    u8 unk_19[3];      /* 0x19 */
    u8 window[0x80];   /* 0x1c: the window (its offset set by func_02068d74) */
    s32 window_offset; /* 0x9c: the window's offset in the slide */
    u8 unk_a0[0x5e4];  /* 0xa0: the window's text windows at 0xb4 (talk_windows.h) */
    TalkPage page;     /* 0x684 */
    u8 unk_b14[0x8a4];
    TalkTagsWalker walker;  /* 0x13b8 */
    MessageWalkRun walk;    /* 0x149c */
    TalkReceiver *receiver; /* 0x14a8 */
    u8 unk_14ac[0x580];     /* 0x14ac */
    u8 last_chars[0x2c];    /* 0x1a2c: the last characters, voiced (func_02068a04) */
    u8 unk_1a58[0x41f];     /* 0x1a58 */
    u8 message;             /* 0x1e77: the message the talk is given next, or data_021f43f8 */
    u8 unk_1e78[0x20];      /* 0x1e78 */
    u8 silent;              /* 0x1e98: no voice and the music kept as it is */
    u8 unk_1e99;            /* 0x1e99 */
    u8 quiet;               /* 0x1e9a: no sounds of the window */
    u8 unk_1e9b;
} TalkFlowTalk;

void TalkFlow_WalkStopped(TalkFlowTalk *talk);
void TalkFlow_StepGone(void *talk);
void TalkFlow_EnterGone(TalkFlowTalk *talk);
void TalkFlow_StepClosing(TalkFlowTalk *talk);
void TalkFlow_EnterClosing(TalkFlowTalk *talk);
void TalkFlow_StepWriting(TalkFlowTalk *talk);

/* The other states' steps and entries, the state asked for entered, and what the talk does
 * when the walk goes on or ends (TalkObject from talk_object.h):
 * - 0, closed: nothing each frame; on entry the window closed (TalkFlow_EnterClosed);
 * - 1, opening (TalkFlow_EnterOpening, TalkFlow_StepOpening): the message loaded and begun,
 *   the window built for the speaker and slid in over five frames; then the talk writes;
 * - 2, waiting (TalkFlow_EnterWaiting, TalkFlow_StepWaiting): the window's arrow runs through
 *   its poses 0 to 3 as the player goes on, then TalkFlow_WalkStopped;
 * - 3, writing: entered by TalkFlow_EnterWriting. */
void TalkFlow_StepWaiting(TalkObject *talk);
void TalkFlow_EnterWriting(TalkObject *talk);
void TalkFlow_EnterWaiting(TalkObject *talk);
void TalkFlow_StepOpening(TalkObject *talk);
void TalkFlow_EnterOpening(TalkObject *talk);
void TalkFlow_StepClosed(void *talk);
void TalkFlow_EnterClosed(TalkObject *talk);
void TalkFlow_EnterNext(TalkObject *talk);
void TalkFlow_TakeAnswer(TalkObject *talk);
void TalkFlow_EndAtLast(TalkObject *talk);
void TalkFlow_End(TalkObject *talk);
void TalkFlow_NextMessage(TalkObject *talk);
void TalkFlow_NewPage(TalkObject *talk);
void TalkFlow_SameWindow(TalkObject *talk);
void TalkFlow_AfterChoices(TalkObject *talk);

#endif
