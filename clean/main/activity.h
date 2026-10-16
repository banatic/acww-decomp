/* The activity process (class vtable data_020e3ae8; created by func_020a503c, which makes it
 * the current activity, data_021f3c3c): it saves the state block to the card and runs the
 * exchanges of a linked session, each as a numbered step state, and talks to the player
 * through a message receiver of its own (vtable data_020e3b38) in talk 0 (func_020a1954).
 * Its layout past the receiver is only partly known. */
#ifndef CLEAN_MAIN_ACTIVITY_H
#define CLEAN_MAIN_ACTIVITY_H

#include "autoload_2/process.h"
#include "session.h"
#include "types.h"

#define ACTIVITY_SLOTS 4

typedef struct Activity {
    Process process;
    u32 unk_50;
    u8 receiver[0x4c];                /* 0x54: its message receiver (func_020a256c destructs it) */
    u8 unk_a0;                        /* 0xa0 */
    u8 state;                         /* 0xa1: the step of the current exchange */
    u8 unk_a2[0xf8 - 0xa2];           /* 0xa2 */
    u8 slot_reported[ACTIVITY_SLOTS]; /* 0xf8: set for a slot by system packet 16 (func_020a1200) */
} Activity;

Activity *Activity_Destruct(Activity *activity);
Activity *Activity_DestructFree(Activity *activity);
void Activity_TalkSequence2(Activity *activity);
void Activity_TalkGatekeeper(Activity *activity, int quiet);
void Activity_StepSendReport(Activity *activity, u8 *step, int first);
int Activity_AllPeersReported(Activity *activity);
void Activity_StepRequestMode1(Activity *activity, u8 *step, int first, int scene_a, int scene_b);

#endif
