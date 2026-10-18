/* The functions of the events of main's queue (event_queue.h), by kind: the four tables
 * data_020daa28 (whether a queued event may be taken), data_020daa64 (EVENT_STARTING),
 * data_020da9ec (EVENT_RUNNING) and data_020daaa0 (EVENT_ENDING). EventKind_Done and
 * EventKind_NotYet fill the places a kind has nothing to do in.
 *
 *   kind   take                 start                 run                    end
 *   0      EventKind_None       EventKind_None        EventKind_None         EventKind_None
 *   1      TakeGroup            Done                  RunGroup               EndGroup
 *   2      TakeAct              StartObjectEvent      RunObjectEvent         EndObjectEvent
 *   3      TakeUnderfoot        Done                  NotYet                 Done
 *   4      Done                 Done                  RunSceneStart          Done
 *   5, 10  TakeMenu             Done                  RunMenu                EndMenu
 *   6      TakeKind6            StartObjectEvent      RunObjectEvent         EndObjectEvent
 *   7      TakeKind7            StartObjectEvent      RunObjectEvent         EndObjectEvent
 *   8      TakeKind8            Done                  RunKind8               Done
 *   9, 14  TakeKind9            Done                  RunKind9               Done
 *   11     TakeKind11           StartKind11           NotYet                 Done
 *   12     Done                 StartSceneObject      RunSceneStart          EndSceneObject
 *   13     NotYet               NotYet                RunKind13              Done
 *
 * Kind 1 opens an overlay group (the event's step is the group); kinds 2, 6 and 7 are about an
 * object (the event's second id) that this console's player acts on, kind 3 takes the scene
 * exit underfoot, kinds 4 and 12 start a scene (EventQueue_StartSceneEvent), 12 about the
 * object on the kept tile.
 *
 * An event about an object may be shared with a session (data_020ccf94): the object's events
 * are then sent to the other console (ObjectClaim_SendEvent, ObjectClaim_SendAct), or the
 * object is asked for and claimed (ObjectClaim_Ask, ObjectClaim_Claim) and let go again
 * (ObjectClaim_Release); the answer comes back in the byte data_020dab94. */
#ifndef CLEAN_MAIN_EVENT_KINDS_H
#define CLEAN_MAIN_EVENT_KINDS_H

#include "event_queue.h"
#include "scene_object_base.h"
#include "types.h"

/* The steps (EventQueueEntry.step) of an event about an object (kinds 2, 6, 7; 12 uses 1, 2, 5
 * and 7 too). */
#define EVENT_KIND_STEP_ASKED 1       /* waiting for the session's answer */
#define EVENT_KIND_STEP_GO 2          /* the object may be acted on */
#define EVENT_KIND_STEP_REFUSED 3     /* the session said no */
#define EVENT_KIND_STEP_APPROACHING 4 /* the player goes to the object */
#define EVENT_KIND_STEP_UNDER_WAY 5   /* the event runs */
#define EVENT_KIND_STEP_ASK_SESSION 7 /* kind 12: the object is to be asked of the session */
#define EVENT_KIND_STEP_WAIT_PLAYER 8 /* kind 7: waiting for the player before going on */

/* The session's answer (data_020dab94). */
#define EVENT_KIND_ANSWER_YES 1
#define EVENT_KIND_ANSWER_NO 2

/* Which question of the object agreed (EventQueueEntry.step_17 for kinds 2, 6, 7): slot 0x48
 * (talk, check), 1 for kinds 6 and 7, slot 0x54. The object's slot 0x4c is told it when the
 * event runs. */
#define EVENT_KIND_ACT_MAY_ACT 0
#define EVENT_KIND_ACT_KIND_6_7 1
#define EVENT_KIND_ACT_ASK_54 5

/* The codes events tell an object (its vtable slot 0x4c). */
#define EVENT_KIND_TELL_UNDERFOOT 2
#define EVENT_KIND_TELL_STARTS 3
#define EVENT_KIND_TELL_REFUSED 4
#define EVENT_KIND_TELL_SCENE_START 6
#define EVENT_KIND_TELL_ENDED 8

/* Whom an object's slot 0x4c is told an event is for: this console's player. */
#define EVENT_KIND_THIS_PLAYER 4

int EventKind_NotYet(void);
int EventKind_Done(void);
int EventKind_None(void);
int EventKind_RunKind13(EventQueueEntry *event);
int EventKind_RunKind9(EventQueueEntry *event);
int EventKind_TakeKind9(EventQueueEntry *event);
int EventKind_RunKind8(EventQueueEntry *event);
int EventKind_TakeKind8(EventQueueEntry *event);
int EventKind_EndMenu(void);
int EventKind_RunMenu(EventQueueEntry *event);
int EventKind_TakeMenu(EventQueueEntry *event);
int EventKind_RunSceneStart(EventQueueEntry *event);
int EventKind_EndSceneObject(void);
int EventKind_StartSceneObject(EventQueueEntry *event);
int EventKind_StartKind11(void);
int EventKind_TakeKind11(void);
int EventKind_TakeUnderfoot(EventQueueEntry *event);
int EventKind_TakeKind7(EventQueueEntry *event);
int EventKind_EndObjectEvent(EventQueueEntry *event);
int EventKind_RunObjectEvent(EventQueueEntry *event);
int EventKind_TakeKind6(EventQueueEntry *event);
int EventKind_StartObjectEvent(EventQueueEntry *event);
int EventKind_TakeAct(EventQueueEntry *event);
void EventKind_TellTarget(EventQueueEntry *event, int code);
void EventKind_TellObject(SceneObjectBase *object, int code);
int EventKind_Claim(EventQueueEntry *event);
int EventKind_ClaimPerson(EventQueueEntry *event);
int EventKind_ClaimObject(EventQueueEntry *event);
int EventKind_EndGroup(void);
void EventKind_RunGroup(void);
int EventKind_TakeGroup(EventQueueEntry *event);

#endif
