/* How the activity process talks to the player (activity_talk.h). */
#include "activity_talk.h"

#include "clean.h"

static_assert(sizeof(ActivityReceiver) == sizeof(((Activity *) 0)->receiver), "activity receiver");
static_assert(offsetof(ActivityReceiver, message) == 0x1e && offsetof(ActivityReceiver, owner) == 0x48, "receiver");

#define TALK_INDEX 0
#define RECEIVER_SLOT_RESET 2 /* the receiver's vtable slot called before it gets a message */

/* Talk `index`. */
extern ActivityTalk *func_020682e0(int index);
/* The talk's byte 0x1e93 set to 1 (its meaning is not known yet). */
extern void func_02068440(ActivityTalk *talk);
/* The talk's next message: the number at `message`, from the file `name` (none when NULL). */
extern void func_0206844c(ActivityTalk *talk, const u8 *message, const char *name);
/* The talk handed the receiver whose message it shows. */
extern void func_02068340(ActivityTalk *talk, ActivityReceiver *receiver);
/* The receiver given the name of its message file. */
extern void func_020a8164(ActivityReceiver *receiver, const char *name);
/* The activity's job `job` started (activity_job.h). */
extern void func_020a4e94(Activity *activity, int job);

/* A message number (bss) the talk is given after messages 8, 39 and 105. */
extern u8 data_021f43e8;

enum ActivityMessage {
    ACTIVITY_MESSAGE_8 = 8,
    ACTIVITY_MESSAGE_10 = 10,
    ACTIVITY_MESSAGE_38 = 38,
    ACTIVITY_MESSAGE_39 = 39,
    ACTIVITY_MESSAGE_105 = 105,
};

#define JOB_AFTER_MESSAGE_38 0x1e

/* func_020a1954: message `message` of file `name` shown by talk 0 through the activity's
 * receiver (after its vtable slot 2), with the talk's byte 0x1e93 set, and the talk asked to
 * start; gives 1. */
int ActivityTalk_Show(Activity *activity, const char *name, char message)
{
    ActivityTalk *talk = func_020682e0(TALK_INDEX);
    ActivityReceiver *receiver = (ActivityReceiver *) (void *) activity->receiver;
    ((void (*)(ActivityReceiver *))(uintptr_t) receiver->vtable[RECEIVER_SLOT_RESET])(receiver);
    func_020a8164(receiver, name);
    receiver->message = (u8) message;
    func_02068440(talk);
    func_02068340(talk, receiver);
    talk->request = 1;
    return 1;
}
CLEAN_AS(func_020a1954, ActivityTalk_Show)

/* func_020a24d4: the receiver's vtable slot 6 (an answer), which does nothing. */
void ActivityReceiver_OnAnswer(void) {}
CLEAN_AS(func_020a24d4, ActivityReceiver_OnAnswer)

/* func_020a24d8: the receiver's vtable slot 5, what follows the message talk 0 shows: after
 * message 10 the talk's byte 0x1e93 is set; after 8, 39 and 105 it is given the message
 * number at data_021f43e8 (with no file name); after 38 the byte is set and the owner starts
 * job 0x1e. Other messages change nothing. */
void ActivityReceiver_OnMessage(ActivityReceiver *receiver)
{
    ActivityTalk *talk = func_020682e0(TALK_INDEX);
    switch (receiver->message) {
        case ACTIVITY_MESSAGE_10:
            func_02068440(talk);
            break;
        case ACTIVITY_MESSAGE_8:
        case ACTIVITY_MESSAGE_39:
        case ACTIVITY_MESSAGE_105:
            func_0206844c(talk, &data_021f43e8, NULL);
            break;
        case ACTIVITY_MESSAGE_38:
            func_02068440(talk);
            func_020a4e94(receiver->owner, JOB_AFTER_MESSAGE_38);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020a24d8, ActivityReceiver_OnMessage)

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */

/* The receiver's vtable, and its base class's destructor and constructor. */
extern const u32 data_020e3b38[];
extern void *func_02066994(ActivityReceiver *receiver);
extern void *func_02066a30(ActivityReceiver *receiver);
/* Talk 0: func_02068c10 on its part at 0x1c, func_02068c24 given a value there, and its byte
 * 0x1e93 cleared (func_02068440 sets it). */
extern void func_02068358(ActivityTalk *talk);
extern void func_02068364(ActivityTalk *talk, int value);
extern void func_02068434(ActivityTalk *talk);

extern const char data_020e3c40[]; /* "sp_etc_sequence2" */

#define TALK_WAITING 2 /* ActivityTalk.state while the talk waits at its message */

enum ActivityQueuedMessage {
    ACTIVITY_MESSAGE_11 = 11,
};

/* func_020a2548: the receiver's owner set, when the activity is made. */
void ActivityReceiver_SetOwner(ActivityReceiver *receiver, Activity *owner)
{
    receiver->owner = owner;
}
CLEAN_AS(func_020a2548, ActivityReceiver_SetOwner)

/* func_020a254c: the receiver destructed (its base class's destructor), then freed. */
ActivityReceiver *ActivityReceiver_DestructFree(ActivityReceiver *receiver)
{
    receiver->vtable = data_020e3b38;
    func_02066994(receiver);
    Heap_OperatorDeleteB(receiver);
    return receiver;
}
CLEAN_AS(func_020a254c, ActivityReceiver_DestructFree)

/* func_020a256c: the receiver destructed (its base class's destructor). */
ActivityReceiver *ActivityReceiver_Destruct(ActivityReceiver *receiver)
{
    receiver->vtable = data_020e3b38;
    func_02066994(receiver);
    return receiver;
}
CLEAN_AS(func_020a256c, ActivityReceiver_Destruct)

/* func_020a2584: the receiver constructed: its base class's constructor, then its vtable. */
ActivityReceiver *ActivityReceiver_Construct(ActivityReceiver *receiver)
{
    func_02066a30(receiver);
    receiver->vtable = data_020e3b38;
    return receiver;
}
CLEAN_AS(func_020a2584, ActivityReceiver_Construct)

/* func_020a259c: when talk 0 waits at its message, it is given whether `value` is non-zero
 * (func_02068364) and 1 is given; else 0. `activity` is not read. */
int ActivityTalk_FinishWaiting(Activity *activity, int value)
{
    (void) activity;
    ActivityTalk *talk = func_020682e0(TALK_INDEX);
    if (talk->state != TALK_WAITING) {
        return 0;
    }
    func_02068364(talk, value != 0);
    return 1;
}
CLEAN_AS(func_020a259c, ActivityTalk_FinishWaiting)

/* func_020a25cc: talk 0 told func_02068358 and its byte 0x1e93 cleared. `activity` is not
 * read. */
void ActivityTalk_Close(Activity *activity)
{
    (void) activity;
    ActivityTalk *talk = func_020682e0(TALK_INDEX);
    func_02068358(talk);
    func_02068434(talk);
}
CLEAN_AS(func_020a25cc, ActivityTalk_Close)

/* The talk closed (ActivityTalk_Close) and given message `message` of "sp_etc_sequence2" next. */
static void close_and_queue(u8 message)
{
    ActivityTalk *talk = func_020682e0(TALK_INDEX);
    func_02068358(talk);
    func_02068434(talk);
    func_0206844c(talk, &message, data_020e3c40);
}

/* func_020a25e8: talk 0 closed and given message 11 of "sp_etc_sequence2" next. `activity` is
 * not read. */
void ActivityTalk_QueueMessage11(Activity *activity)
{
    (void) activity;
    close_and_queue(ACTIVITY_MESSAGE_11);
}
CLEAN_AS(func_020a25e8, ActivityTalk_QueueMessage11)

/* func_020a261c: talk 0 closed and given message 10 of "sp_etc_sequence2" next. `activity` is
 * not read. */
void ActivityTalk_QueueMessage10(Activity *activity)
{
    (void) activity;
    close_and_queue(ACTIVITY_MESSAGE_10);
}
CLEAN_AS(func_020a261c, ActivityTalk_QueueMessage10)
