/* The announcements of the town's events: when one of eleven events of the calendar
 * (data_020ca508: 0x09-0x13) starts or ends, or the day changes (event_kinds' check at 6:00,
 * func_020469f4) or event 0x44 is over (func_020be830), the player is taken into scene 0x31 at
 * a building of the town map and talk 0 shows a message of "obj_ev_start" or "obj_ev_end",
 * then the player goes back out.
 *
 * The announcement runs in steps (EventAnnounceState.step), one a frame in the execution of
 * the process of vtable data_020db71c (EventAnnounceProcess, profile data_020db6e8):
 *
 *   0  nothing asked for
 *   1  asked for while the field was busy (func_0206e980): waits until it is (then 2)
 *   2  waits until the field is not busy, then asks the event queue for an event of kind 11
 *      (EventAnnounce_QueueEvent): 3 when it took it, else 0
 *   3  while the event of kind 11 runs: the player sent to scene 0x31 (then 4); when the
 *      queue stops running it and does not take a new one, 0
 *   4  waiting for scene 0x31: the process is made again there (EventAnnounceProcess_Create,
 *      then 5)
 *   5  once the screen is shown, the talk started (then 6)
 *   6  once the talk is closed, the player sent back out (then 0)
 *
 * Three event numbers are kept (EVENT_CALENDAR_NONE for none): the one looked at by the
 * check (data_020db6e4; the check looks for a new event only while it is none), the one
 * going on (data_020db6e0, EventAnnounce_CurrentEvent) and the one the music plays for
 * (data_020db6dc, EventAnnounce_MusicEvent). The event going on is kept in the save in the
 * town's schedule (EventSchedule.unk_11) while the game is not linked. */
#ifndef CLEAN_MAIN_EVENT_ANNOUNCE_H
#define CLEAN_MAIN_EVENT_ANNOUNCE_H

#include "autoload_2/process.h"
#include "main/talk_receiver.h"
#include "types.h"

#define EVENT_ANNOUNCE_EVENTS 11      /* the events of data_020ca508 */
#define EVENT_ANNOUNCE_FIRST 0x09     /* events 0x09-0x12 have messages 0-9 */
#define EVENT_ANNOUNCE_LAST 0x12      /* (the last of them, also the one whose end is special) */
#define EVENT_ANNOUNCE_QUIET 0x13     /* an event of the list that is never announced */
#define EVENT_ANNOUNCE_EVENT_44 0x44  /* announced (message 14) only when nothing else is */
#define EVENT_ANNOUNCE_MESSAGE_44 14  /* the message of event 0x44 */
#define EVENT_ANNOUNCE_MESSAGE_DAY 15 /* the message for the day's change (event below 0) */
#define EVENT_ANNOUNCE_HOUR 6         /* an event on before 6:00 is not announced */
#define EVENT_ANNOUNCE_SCENE 0x31     /* the scene the announcement is made in */

/* EventAnnounceState.step */
enum EventAnnounceStep {
    EVENT_ANNOUNCE_IDLE = 0,
    EVENT_ANNOUNCE_WAIT_BUSY = 1,
    EVENT_ANNOUNCE_WAIT_FREE = 2,
    EVENT_ANNOUNCE_ENTER = 3,
    EVENT_ANNOUNCE_ENTERING = 4,
    EVENT_ANNOUNCE_SHOW = 5,
    EVENT_ANNOUNCE_TALKING = 6,
};

/* The announcement under way (data_021c75a0). */
typedef struct EventAnnounceState {
    u8 step;    /* enum EventAnnounceStep */
    u8 ending;  /* 0x01: 0: "obj_ev_start", 1: "obj_ev_end" (the message file's index) */
    u8 pending; /* 0x02: an announcement is asked for or running; no other is taken */
    u8 new_day; /* 0x03: the announcement is the day's change */
    u8 message; /* 0x04: the message's number in its file */
    u8 unk_05[3];
    u32 event; /* 0x08: the event it is for, made the one looked at when it is shown */
} EventAnnounceState;

/* The process of vtable data_020db71c: the base process and the receiver of talk 0's
 * message. */
typedef struct EventAnnounceProcess {
    Process base;
    u32 unk_50;
    TalkReceiver receiver; /* 0x54: vtable data_020df008 */
} EventAnnounceProcess;

int EventAnnounce_SceneIsExcluded(void);
void EventAnnounce_Request(int event, int record, int ending);
void EventAnnounce_Nothing13f4(void *unused);
void EventAnnounce_SetStep(int step);
void EventAnnounce_StepTalking(void *unused);
void EventAnnounce_StepShow(EventAnnounceProcess *process);
void EventAnnounce_StepEnter(void *unused);
int EventAnnounce_QueueEvent(void);
void EventAnnounce_StepWaitFree(void *unused);
void EventAnnounce_StepWaitBusy(void *unused);
void EventAnnounce_StepNothing(void *unused);
u32 EventAnnounce_CurrentEvent(void);
u32 EventAnnounce_MusicEvent(void);
int EventAnnounce_Entered(void);
void EventAnnounce_CheckIfAllowed(void);
void EventAnnounce_Check(void);
int EventAnnounce_IsAllowed(void);
void EventAnnounce_ResetAndCheck(void);
void EventAnnounce_Reset(void);
int EventAnnounceProcess_Delete(void);
int EventAnnounceProcess_Execute(EventAnnounceProcess *process);
int EventAnnounceProcess_Create(void);
EventAnnounceProcess *EventAnnounceProcess_DestructFree(EventAnnounceProcess *process);
EventAnnounceProcess *EventAnnounceProcess_Destruct(EventAnnounceProcess *process);
EventAnnounceProcess *EventAnnounceProcess_Construct(EventAnnounceProcess *process);
void EventAnnounceProcess_New(void);

#endif
