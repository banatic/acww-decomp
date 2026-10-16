/* How the activity process (activity.h) talks to the player: through a message receiver of its
 * own (vtable data_020e3b38, at Activity.receiver), handed to talk 0 with the name of a message
 * file and the number of a message in it. When the talk asks the receiver what follows a
 * message (its vtable slot 5), messages 8, 39 and 105 lead to another one and message 38
 * starts the activity's job 0x1e (activity_job.h). */
#ifndef CLEAN_MAIN_ACTIVITY_TALK_H
#define CLEAN_MAIN_ACTIVITY_TALK_H

#include "activity.h"
#include "types.h"

/* The first words of a talk (func_020682e0 gives one). */
typedef struct ActivityTalk {
    u32 unk_00;
    s32 state;   /* 0x04: 0 when closed */
    s32 request; /* 0x08: set to 1 to start the talk */
} ActivityTalk;

typedef struct ActivityReceiver {
    const u32 *vtable; /* data_020e3b38: slot 5 ActivityReceiver_OnMessage, slot 6
                        * ActivityReceiver_OnAnswer */
    char name[26];     /* 0x04: the message file, written by func_020a8164 */
    u8 message;        /* 0x1e: the message's number in it */
    u8 unk_1f;
    u8 unk_20[0x20];
    ActivityTalk *talk; /* 0x40: the talk showing it */
    u8 unk_44[4];
    Activity *owner; /* 0x48: set by func_020a2548 when the activity is made */
} ActivityReceiver;

int ActivityTalk_Show(Activity *activity, const char *name, char message);
void ActivityReceiver_OnAnswer(void);
void ActivityReceiver_OnMessage(ActivityReceiver *receiver);

/* The receiver's life, and talk 0 as the activity's jobs drive it. */
void ActivityReceiver_SetOwner(ActivityReceiver *receiver, Activity *owner);
ActivityReceiver *ActivityReceiver_DestructFree(ActivityReceiver *receiver);
ActivityReceiver *ActivityReceiver_Destruct(ActivityReceiver *receiver);
ActivityReceiver *ActivityReceiver_Construct(ActivityReceiver *receiver);
int ActivityTalk_FinishWaiting(Activity *activity, int value);
void ActivityTalk_Close(Activity *activity);
void ActivityTalk_QueueMessage11(Activity *activity);
void ActivityTalk_QueueMessage10(Activity *activity);

#endif
