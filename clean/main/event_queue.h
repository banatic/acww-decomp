/* Main's queue of events (the process of class data_020daae4, process_020daae4.h, runs it each
 * frame): actors and scenes ask for an event of a kind (EventQueue_Push) and at most one runs
 * at a time, the current one (data_021c72b8).
 *
 * An event is one of 15 entries of 0x1c bytes (data_021c72e8; func_0203f504 gives a free one,
 * func_0203f58c frees one). Asked-for events wait in the queue (data_021c72c4), sorted by
 * priority (func_02065c2c). Each frame the process (Process020daae4_Execute):
 *   - steps the current event: in EVENT_RUNNING through its kind's function of the table
 *     data_020da9ec (nonzero: EVENT_ENDING), then in EVENT_ENDING through data_020daaa0
 *     (nonzero: the event is freed and there is none current);
 *   - without one, takes the first queued event whose kind's function of data_020daa28 agrees;
 *   - steps a current event in EVENT_STARTING through data_020daa64 (nonzero: EVENT_RUNNING);
 *   - then frees every event still queued: an event asked for and not taken that frame is lost.
 *
 * An event's `step` is its kind's own; step EVENT_STEP_FINISHED (6) asks its functions to end
 * it (EventQueue_FinishIfKind and the other Finish functions set it).
 *
 * The kinds asked for here (what the callers are, as far as known):
 *   1  func_02070218 (an overlay task's answer), priority 2
 *   2  an act on the object picked (EventQueue_RequestAct), priority 3
 *   3  the object underfoot (EventQueue_RequestUnderfoot), priority 1
 *   5, 10  the start menu (start_menu.c), priority 4
 *   6, 7  an object of overlays 3, 4 and 45-88 (EventQueue_RequestKind6, EventQueue_RequestKind7),
 *         priority 3
 *   8  after the object underfoot is noted (EventQueue_RequestKind8), priority 1
 *   9  a field actor's message receiver (EventQueue_RequestKind9), priority 0
 *   11 func_020414e0 (EventQueue_RequestKind11), priority 1
 *   13 started at once, not queued (EventQueue_StartKind13)
 *   14 overlay 3's field actor (EventQueue_RequestKind14), priority 0
 *
 * The process also keeps flags (data_021c72c0, EventQueue_SetFlags) and the id of an object
 * (data_021c72bc, EventQueue_SetTargetId) that the events of kinds 2, 6 and 7 are about. */
#ifndef CLEAN_MAIN_EVENT_QUEUE_H
#define CLEAN_MAIN_EVENT_QUEUE_H

#include "autoload_2/links.h"
#include "autoload_2/process.h"
#include "ov002/error_message.h" /* MessageReceiver */
#include "types.h"

/* EventQueueEntry.state */
enum EventQueueState {
    EVENT_FREE = 0,     /* the entry is unused */
    EVENT_QUEUED = 1,   /* in the queue, waiting to be taken */
    EVENT_STARTING = 2, /* current; stepped through data_020daa64 */
    EVENT_RUNNING = 3,  /* current; stepped through data_020da9ec */
    EVENT_ENDING = 4,   /* current; stepped through data_020daaa0 */
};

/* The step value that asks an event to end (EventQueueEntry.step, and .step_17 for kinds 4
 * and 12). */
#define EVENT_STEP_FINISHED 6

/* An event (an entry of data_021c72e8). */
typedef struct EventQueueEntry {
    ListNode link; /* 0x00: in the queue */
    u8 priority;   /* 0x08: the queue is sorted by it, lowest first */
    u8 pad_09[3];  /* 0x09 */
    u32 first_id;  /* 0x0c: an object's id (its word 0xdc, func_0203efbc), or 0 */
    u32 second_id; /* 0x10: another object's id, or 0 */
    u8 state;      /* 0x14: EventQueueState */
    u8 kind;       /* 0x15: the index in the four tables of functions */
    u8 step;       /* 0x16: the kind's own; EVENT_STEP_FINISHED asks it to end */
    u8 step_17;    /* 0x17: the kind's own (kinds 4 and 12 end on EVENT_STEP_FINISHED) */
    u8 unk_18;     /* 0x18 */
    u8 unk_19;     /* 0x19 */
    u8 pad_1a[2];  /* 0x1a */
} EventQueueEntry;

/* A function of one of the four tables, by kind: nonzero when the event may go on. */
typedef int (*EventQueueStepFn)(EventQueueEntry *event);

int EventQueue_IsKind(u8 kind);
int EventQueue_Push(int first_id, int second_id, int kind, int priority, u8 step);

void EventQueue_ClearFlags(u32 mask);
void EventQueue_SetFlags(u32 mask);
int EventQueue_TestFlags(int mask);
void EventQueue_ClearFlag10(void);
void EventQueue_SetFlag10(void);
int EventQueue_TestFlag10(void);
void EventQueue_ClearFlag20(void);
void EventQueue_SetFlag20(void);
int EventQueue_TestFlag20(void);
void EventQueue_ClearFlag8(void);
void EventQueue_SetFlag8(void);
int EventQueue_TestFlag8(void);
void EventQueue_ClearFlag1(void);
void EventQueue_SetFlag1(void);
int EventQueue_TestFlag1(void);
void EventQueue_SetFlag4(void);
void EventQueue_SetFlag2(void);
int EventQueue_TestFlag4(void);
int EventQueue_TestFlag2(void);

int EventQueue_FinishKind13(void);
int EventQueue_StartKind13(void);
void EventQueue_EndCurrent(void);
void EventQueue_ReceiverLeaveTalk(MessageReceiver *receiver);
void EventQueue_ReceiverToTalk(MessageReceiver *receiver);
int EventQueue_TargetObjectAddress(void);
void EventQueue_SetTargetId(u32 id);
int EventQueue_IsObjectEvent(void);
int EventQueue_FinishObjectEvent(void *object);
int EventQueue_RequestKind7(void *object, int blocked);
int EventQueue_RequestKind6(void *object, int blocked);
int EventQueue_RequestAct(void *actor, void *picked);
int EventQueue_FinishKind4Or12(void);
int EventQueue_FinishKind14(void);
int EventQueue_RequestKind14(void);
int EventQueue_IsKind9(void);
int EventQueue_FinishKind9(void);
int EventQueue_RequestKind9(void);
int EventQueue_FinishKind10(void);
int EventQueue_IsKind10Unfinished(void);
int EventQueue_RequestKind10(void);
void EventQueue_FinishKind5(void);
int EventQueue_IsKind5Unfinished(void);
int EventQueue_RequestKind5(void);
int EventQueue_FinishIfKind(u8 kind);
int EventQueue_IsKindUnfinished(u8 kind);
int EventQueue_RequestForPlayer(int kind);
int EventQueue_RequestKind11(void);
int EventQueue_RequestKind1(int step);
int EventQueue_FinishKind8(void);
int EventQueue_RequestKind8(void);
int EventQueue_RequestUnderfoot(void *player, int object);

void EventQueue_StepEnding(Process *process);
void EventQueue_StepRunning(Process *process);
void EventQueue_StepStarting(Process *process);
void EventQueue_TakeNext(Process *process);

int EventQueue_HasCurrent(void);
void EventQueue_StartScene(void);
void EventQueue_Reset(void);

#endif
