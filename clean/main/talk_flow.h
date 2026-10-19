/* A talk's steps from state to state (the talk: TalkObject of talk_object.h, 0x1e9c bytes, two
 * of them at data_021cda88, talk_process.h; Base_02068144 of include/cpp/main/Base_02068144.h).
 *
 * Each frame func_02068144 runs the step of the talk's `state`, and func_02067108 enters the
 * state asked for in `next_state` (then sets it back to TALK_OBJECT_NO_STATE). The states here:
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

/* The talk's mode (word 0x14, which scene commands set) that keeps it open for more messages. */
#define TALK_FLOW_MODE_KEPT 4

/* The window's slide while closing: TALK_FLOW_SLIDE_STEPS steps down to 0, each an offset of
 * data_020def28. */
#define TALK_FLOW_SLIDE_STEPS 4

void TalkFlow_WalkStopped(TalkObject *talk);
void TalkFlow_StepGone(void *talk);
void TalkFlow_EnterGone(TalkObject *talk);
void TalkFlow_StepClosing(TalkObject *talk);
void TalkFlow_EnterClosing(TalkObject *talk);
void TalkFlow_StepWriting(TalkObject *talk);

/* The other states' steps and entries, the state asked for entered, and what the talk does
 * when the walk goes on or ends:
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
