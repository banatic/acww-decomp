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
