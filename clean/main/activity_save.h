/* The steps with which the activity process (activity.h) saves the town to the card during a
 * visit and ends it. Each runs one step of the activity's step number (Activity.state) a call,
 * from a first step the caller gives, and moves it on.
 *
 * Every step first checks the link (Session_IsLinkLost, with the AIDs the caller gives): when it
 * is lost the session's send timeout is raised (Session_RaiseSendTimeout) and nothing else is
 * done. The systems tell each other how far they are with system packet 14 (one byte, kept in
 * Activity.slot_answer of the receiver for the sender's slot): ACTIVITY_ANSWER_OK to go on,
 * ACTIVITY_ANSWER_END to stop.
 *
 * The card's parts are read and written by step functions of the activity's own
 * (func_020a238c, func_020a19c0 with the part in bits 0-3 of Activity.card_parts, func_020a2120
 * with bits 4-7), each giving 0 when done, 1 when it failed and another value while it is
 * under way. */
#ifndef CLEAN_MAIN_ACTIVITY_SAVE_H
#define CLEAN_MAIN_ACTIVITY_SAVE_H

#include "activity.h"
#include "types.h"

enum ActivityAnswer {
    ACTIVITY_ANSWER_NONE = 0,
    ACTIVITY_ANSWER_OK = 1,
    ACTIVITY_ANSWER_END = 2,
};

#define ACTIVITY_STEP_RESULT 0x20 /* what the step functions give; no caller reads it */

int ActivitySave_GuestSteps(Activity *activity, u8 *step, int first, int fail_step, u8 end_step, u8 with_exchange, u8 restore,
                            int aids);
int ActivitySave_HostSteps(Activity *activity, u8 *step, int forced, int first, u8 fail_step, u8 end_step, int slot,
                           u8 with_exchange, int aids);
int ActivitySave_EndSteps(Activity *activity, u8 *step, int first, int second, int aids, u8 show_message);
void ActivitySave_LeaveSession(Activity *activity, int record_number, int keep_town);

#endif
