/* The announcements of the town's events (event_announce.h). */
#include "event_announce.h"

#include "acre_map.h"
#include "autoload_2/heap.h"
#include "block_021d27ac.h"
#include "block_021d27ac_parts.h"
#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "event_calendar.h"
#include "event_queue.h"
#include "event_schedule.h"
#include "link_scene.h"
#include "music_queue.h"
#include "scene_exit.h"
#include "scene_place.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"
#include "talk_flow.h"
#include "town_objects.h"

static_assert(offsetof(EventAnnounceState, message) == 0x04, "EventAnnounceState.message");
static_assert(offsetof(EventAnnounceState, event) == 0x08, "EventAnnounceState.event");
static_assert(offsetof(EventAnnounceProcess, receiver) == 0x54, "EventAnnounceProcess.receiver");
static_assert(offsetof(TalkReceiver, base.message) == 0x1e, "TalkReceiver.base.message");
static_assert(sizeof(EventAnnounceProcess) == 0x9c, "EventAnnounceProcess");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* Talk `index` (0x1e9c-byte entries at data_021cda88), its receiver taken off it, and a
 * receiver handed to it. */
extern TalkFlowTalk *func_020682e0(int index);
extern void func_02068320(TalkFlowTalk *talk);
extern void func_02068340(TalkFlowTalk *talk, TalkReceiver *receiver);
/* Nonzero while data_021cfbac is set or func_02004130 says data_021cfbcc is busy: the field is
 * not ready for an announcement. */
extern int func_0206e980(void);
/* The town's object at data_021c779c started (func_0204763c with 0), and the day's change
 * handled there (func_02046a74). */
extern void func_0204762c(void);
extern void func_02046a74(int arg);

extern EventAnnounceState data_021c75a0;
extern int data_021c758c; /* the music's part in it: 0 (event 0x44, the day), 1 start, 2 end */
extern int data_021c7590; /* the player was sent to scene 0x31 for it */
extern int data_021c7588; /* the last creation was linked or in scene 0xd */
extern u32 data_020db6e4; /* the event looked at by the check */
extern u32 data_020db6e0; /* the event going on */
extern u32 data_020db6dc; /* the event the music plays for */
extern const u8 data_020ca508[EVENT_ANNOUNCE_EVENTS];
extern const char *const data_020db6f0[2]; /* "obj_ev_start", "obj_ev_end" */

extern EventSchedule data_021f39c0; /* unk_11: the event going on, kept in the save */
extern NetSession *data_020ccf94;
extern Obj021c526c *data_021c526c;
extern Process *data_021f42f4; /* the running scene's process, or NULL */
extern u8 data_021c75b8;       /* the screen transition's state (screen_transition.h) */

/* This class's vtable and the base class's (Process). */
extern const u32 data_020db71c[];
extern const u32 data_020da13c[];

#define SCREEN_SHOWN 2      /* data_021c75b8: the screen is shown */
#define FIELD_SCENE_CLASS 6 /* the field's process class */
#define SCENE_IN_LINK_WAIT 0xd
#define BUILDING_5020_MESSAGE 14 /* the message whose building is found by FindBuilding5020 */
#define PLAYER_PARAM 0x400000
#define EXIT_RETURN 0x14 /* the scene exit that takes the player back out */

static Music2d0 *music_2d0(void)
{
    return (Music2d0 *) (void *) data_021c526c->unk_2d0;
}

/* func_020412a0: 1 in the scenes the announcements leave alone: 6, 0xc-0xe, 0x2c-0x30 and
 * 0x32. */
int EventAnnounce_SceneIsExcluded(void)
{
    switch (SceneQuery_Current()) {
        case 6:
        case 12:
        case 13:
        case 14:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_020412a0, EventAnnounce_SceneIsExcluded)

/* func_0204130c: an announcement asked for: of `event`'s start (`ending` 0) or end (1) for
 * events 0x09-0x12, of event 0x44 when nothing is under way, or of the day's change (`event`
 * below 0); `record` is made the event going on once it is shown. Nothing while linked, in
 * scene 0 when the flag of data_021d27ac's part 0x30 is set and this system's slot is not
 * taken, or while another announcement is pending. The day's change starts at once (step 3)
 * except at minute 0 of the hour (step 1); the others wait for the field (step 2). */
void EventAnnounce_Request(int event, int record, int ending)
{
    EventAnnounceState *state = &data_021c75a0;
    NetSession *session = data_020ccf94;
    int message = -1;
    int step = EVENT_ANNOUNCE_IDLE;

    if (Session_IsLinked(session)) {
        return;
    }
    if (SceneQuery_Current() == 0 && Block021d27acPart30_IsSet(Block021d27ac_Part30(Block021d27ac_Get())) &&
        !Session_IsSlotTaken(session, session->local_slot)) {
        return;
    }
    if (state->pending) {
        return;
    }

    if (event >= EVENT_ANNOUNCE_FIRST && event <= EVENT_ANNOUNCE_LAST) {
        message = event - EVENT_ANNOUNCE_FIRST;
        data_021c758c = ending == 0 ? 1 : 2;
        step = EVENT_ANNOUNCE_WAIT_FREE;
    } else if (event == EVENT_ANNOUNCE_EVENT_44) {
        if (state->step == EVENT_ANNOUNCE_IDLE) {
            message = EVENT_ANNOUNCE_MESSAGE_44;
            data_021c758c = 0;
            step = EVENT_ANNOUNCE_WAIT_FREE;
        }
    } else if (event < 0) {
        if (state->step == EVENT_ANNOUNCE_IDLE) {
            DateTime now = {0};
            message = EVENT_ANNOUNCE_MESSAGE_DAY;
            data_021c758c = 0;
            state->new_day = 1;
            DateTime_Now(&now);
            step = now.minute != 0 ? EVENT_ANNOUNCE_ENTER : EVENT_ANNOUNCE_WAIT_BUSY;
        } else if (state->step == EVENT_ANNOUNCE_WAIT_FREE) {
            state->new_day = 1;
        }
    }

    if (message < 0) {
        return;
    }
    EventAnnounce_SetStep(step);
    state->message = (u8) message;
    state->ending = (u8) ending;
    state->event = (u32) record;
}
CLEAN_AS(func_0204130c, EventAnnounce_Request)

/* func_020413f4: nothing. */
void EventAnnounce_Nothing13f4(void *unused)
{
    (void) unused;
}
CLEAN_AS(func_020413f4, EventAnnounce_Nothing13f4)

/* func_020413f8: the step set; step 3 only when the event queue takes the event of kind 11. */
void EventAnnounce_SetStep(int step)
{
    int set = step == EVENT_ANNOUNCE_ENTER ? EventAnnounce_QueueEvent() : 1;
    if (set) {
        data_021c75a0.step = (u8) step;
    }
}
CLEAN_AS(func_020413f8, EventAnnounce_SetStep)

/* func_0204141c (step 6): once talk 0 is closed, its receiver taken off, the player sent back
 * out by the entry's exit 0x14, the music told, and the announcement over. */
void EventAnnounce_StepTalking(void *unused)
{
    (void) unused;
    TalkFlowTalk *talk = func_020682e0(0);
    if (talk->state != TALK_FLOW_CLOSED) {
        return;
    }
    func_02068320(talk);
    SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), EXIT_RETURN);
    Music2d0_Mark08Unless(music_2d0(), data_021c758c, data_021c75a0.message);
    data_021c758c = 0;
    data_021c75a0.step = EVENT_ANNOUNCE_IDLE;
    data_021c75a0.pending = 0;
}
CLEAN_AS(func_0204141c, EventAnnounce_StepTalking)

/* func_02041470 (step 5): once the screen is shown, the process's receiver reset (its vtable
 * slot 2), given the message file and number, handed to talk 0 and the talk started. */
void EventAnnounce_StepShow(EventAnnounceProcess *process)
{
    if (data_021c75b8 != SCREEN_SHOWN) {
        return;
    }
    TalkFlowTalk *talk = func_020682e0(0);
    TalkReceiver *receiver = &process->receiver;
    void (*const *vtable)(TalkReceiver *) = (void (*const *)(TalkReceiver *)) receiver->base.vtable;
    vtable[2](receiver);
    MessageReceiver_SetName(&receiver->base, data_020db6f0[data_021c75a0.ending]);
    receiver->base.message = data_021c75a0.message;
    func_02068340(talk, receiver);
    talk->next = TALK_OBJECT_OPENING;
    data_021c75a0.step = EVENT_ANNOUNCE_TALKING;
}
CLEAN_AS(func_02041470, EventAnnounce_StepShow)

/* func_020414e0 (step 3): until the event queue runs the event of kind 11, it is asked for
 * again (the announcement dropped when it is not taken). Once it runs, the announcement's
 * event is made the one looked at and the one going on, and when the queue allows it and the
 * field is ready the player is sent into scene 0x31 at the town's building (the one of event
 * 0x44's message found by FindBuilding5020, the others' by HasBuilding5000), the music told,
 * and the step is 4. */
void EventAnnounce_StepEnter(void *unused)
{
    (void) unused;
    Vec3 position;

    if (!EventQueue_TestFlag2()) {
        if (!EventQueue_RequestKind11()) {
            data_021c75a0.step = EVENT_ANNOUNCE_IDLE;
            data_021c75a0.pending = 0;
        }
        return;
    }

    data_020db6e4 = data_021c75a0.event;
    data_020db6e0 = data_021c75a0.event;

    if (!EventQueue_TestFlag4() || func_0206e980()) {
        return;
    }
    int map = (int) AcreMap_Town();
    if (map == 0) {
        return;
    }
    int found;
    if (data_021c75a0.message == BUILDING_5020_MESSAGE) {
        found = AcreMap_FindBuilding5020(map, (int) (uintptr_t) &position);
    } else {
        found = AcreMap_HasBuilding5000(map, (int) (uintptr_t) &position, 0, 0);
    }
    if (!found) {
        return;
    }

    ScenePlace_SavePlayer(SceneTables_EntryRecord(), 0);
    SceneExit_SetTo((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), EVENT_ANNOUNCE_SCENE, &position, PLAYER_PARAM, 0, 2,
                    2);
    Music2d0_Mark08And0b(music_2d0(), data_021c758c, data_021c75a0.message);
    data_021c75a0.step = EVENT_ANNOUNCE_ENTERING;
    data_021c7590 = 1;
}
CLEAN_AS(func_020414e0, EventAnnounce_StepEnter)

/* func_020415a8: the event of kind 11 asked of the event queue; 1 and the announcement
 * pending when it took it, else 0 and the announcement dropped. */
int EventAnnounce_QueueEvent(void)
{
    if (!EventQueue_RequestKind11()) {
        data_021c75a0.step = EVENT_ANNOUNCE_IDLE;
        data_021c75a0.pending = 0;
        return 0;
    }
    data_021c75a0.pending = 1;
    return 1;
}
CLEAN_AS(func_020415a8, EventAnnounce_QueueEvent)

/* func_020415d0 (step 2): once the field is ready, step 3 asked for. */
void EventAnnounce_StepWaitFree(void *unused)
{
    (void) unused;
    if (!func_0206e980()) {
        EventAnnounce_SetStep(EVENT_ANNOUNCE_ENTER);
    }
}
CLEAN_AS(func_020415d0, EventAnnounce_StepWaitFree)

/* func_020415e8 (step 1): once the field is busy, step 2. */
void EventAnnounce_StepWaitBusy(void *unused)
{
    (void) unused;
    if (func_0206e980()) {
        data_021c75a0.step = EVENT_ANNOUNCE_WAIT_FREE;
    }
}
CLEAN_AS(func_020415e8, EventAnnounce_StepWaitBusy)

/* func_02041604 (steps 0 and 4): nothing. */
void EventAnnounce_StepNothing(void *unused)
{
    (void) unused;
}
CLEAN_AS(func_02041604, EventAnnounce_StepNothing)

/* func_02041608: the event going on. */
u32 EventAnnounce_CurrentEvent(void)
{
    return data_020db6e0;
}
CLEAN_AS(func_02041608, EventAnnounce_CurrentEvent)

/* func_02041614: the event the music plays for. */
u32 EventAnnounce_MusicEvent(void)
{
    return data_020db6dc;
}
CLEAN_AS(func_02041614, EventAnnounce_MusicEvent)

/* func_02041620: whether the player was sent to scene 0x31 for an announcement. */
int EventAnnounce_Entered(void)
{
    return data_021c7590;
}
CLEAN_AS(func_02041620, EventAnnounce_Entered)

/* func_0204162c: the events checked when an announcement may be made now. */
void EventAnnounce_CheckIfAllowed(void)
{
    if (EventAnnounce_IsAllowed()) {
        EventAnnounce_Check();
    }
}
CLEAN_AS(func_0204162c, EventAnnounce_CheckIfAllowed)

/* func_02041644: the events checked against the calendar now. While none is looked at, each of
 * the eleven: one that is on is announced (before 6:00 it is only made the one going on;
 * event 0x13 is made the one looked at and going on without one), and event 0x12 ending is
 * made all three. Then an event going on that the calendar has off is announced as over
 * (event 0x13 is only forgotten). */
void EventAnnounce_Check(void)
{
    DateTime now = {0};
    DateTime when;

    DateTime_Now(&now);

    if (data_020db6e4 == EVENT_CALENDAR_NONE) {
        for (int i = 0; i < EVENT_ANNOUNCE_EVENTS; i++) {
            u8 event = data_020ca508[i];
            MI_CpuCopy8(&now, &when, sizeof(when));
            switch (EventCalendar_StateOn(event, &when, 0)) {
                case EVENT_CALENDAR_ON:
                    if (event == EVENT_ANNOUNCE_QUIET) {
                        data_020db6e4 = event;
                        data_020db6e0 = event;
                    } else if (now.hour < EVENT_ANNOUNCE_HOUR) {
                        data_020db6e0 = event;
                    } else {
                        EventAnnounce_Request(event, event, 0);
                    }
                    break;
                case EVENT_CALENDAR_ENDING:
                    if (event == EVENT_ANNOUNCE_LAST) {
                        data_020db6e4 = EVENT_ANNOUNCE_LAST;
                        data_020db6e0 = EVENT_ANNOUNCE_LAST;
                        data_020db6dc = EVENT_ANNOUNCE_LAST;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (data_020db6e0 != EVENT_CALENDAR_NONE) {
        MI_CpuCopy8(&now, &when, sizeof(when));
        if (EventCalendar_StateOn((int) data_020db6e0, &when, 0) == EVENT_CALENDAR_OFF) {
            if (data_020db6e0 == EVENT_ANNOUNCE_QUIET) {
                data_020db6e4 = EVENT_CALENDAR_NONE;
                data_020db6e0 = EVENT_CALENDAR_NONE;
            } else {
                EventAnnounce_Request((int) data_020db6e0, EVENT_CALENDAR_NONE, 1);
            }
        }
    }
}
CLEAN_AS(func_02041644, EventAnnounce_Check)

/* func_02041718: 1 when an announcement may be made: the screen is shown, the scene is none of
 * 0x3f, 0x2c and 6 nor a linking scene, and the running scene, if any, is the field's. */
int EventAnnounce_IsAllowed(void)
{
    if (data_021c75b8 != SCREEN_SHOWN) {
        return 0;
    }
    if (SceneQuery_Current() == LINK_SCENE_NONE || SceneQuery_Current() == 0x2c || SceneQuery_Current() == 6) {
        return 0;
    }
    if (LinkScene_IsLinkingScene(SceneQuery_Current())) {
        return 0;
    }
    if (data_021f42f4 != NULL && data_021f42f4->class_id != FIELD_SCENE_CLASS) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_02041718, EventAnnounce_IsAllowed)

/* func_02041788: everything forgotten, then the events checked unless linked. */
void EventAnnounce_ResetAndCheck(void)
{
    EventAnnounce_Reset();
    if (!Session_IsLinked(data_020ccf94)) {
        EventAnnounce_Check();
    }
}
CLEAN_AS(func_02041788, EventAnnounce_ResetAndCheck)

/* func_020417ac: no event looked at, going on or for the music, and no announcement. */
void EventAnnounce_Reset(void)
{
    data_020db6e4 = EVENT_CALENDAR_NONE;
    data_020db6e0 = EVENT_CALENDAR_NONE;
    data_020db6dc = EVENT_CALENDAR_NONE;
    data_021c75a0.step = EVENT_ANNOUNCE_IDLE;
    data_021c75a0.pending = 0;
    data_021c75a0.new_day = 0;
}
CLEAN_AS(func_020417ac, EventAnnounce_Reset)

/* func_020417d8 (vtable slot 0x0c): the deletion; always 1. Outside the excluded scenes: the
 * announcement dropped when the event queue's flag 1 is set (and the flag cleared), the events
 * forgotten when idle with none going on, step 1 moved to 2, and the event going on kept in
 * the save unless linked. */
int EventAnnounceProcess_Delete(void)
{
    if (EventAnnounce_SceneIsExcluded()) {
        return 1;
    }
    if (EventQueue_TestFlag1()) {
        EventQueue_ClearFlag1();
        data_021c7590 = 0;
        data_021c75a0.step = EVENT_ANNOUNCE_IDLE;
        data_021c75a0.pending = 0;
    }
    switch (data_021c75a0.step) {
        case EVENT_ANNOUNCE_IDLE:
            if (data_020db6e0 == EVENT_CALENDAR_NONE) {
                EventAnnounce_Reset();
            }
            break;
        case EVENT_ANNOUNCE_WAIT_BUSY:
            data_021c75a0.step = EVENT_ANNOUNCE_WAIT_FREE;
            break;
        default:
            break;
    }
    if (!Session_IsLinked(data_020ccf94)) {
        data_021f39c0.unk_11 = (u8) data_020db6e0;
    }
    return 1;
}
CLEAN_AS(func_020417d8, EventAnnounceProcess_Delete)

/* func_02041850 (vtable slot 0x18): the execution; always 1. Unless linked: the events checked
 * when allowed, then the announcement's step run. */
int EventAnnounceProcess_Execute(EventAnnounceProcess *process)
{
    if (Session_IsLinked(data_020ccf94)) {
        return 1;
    }
    EventAnnounce_CheckIfAllowed();
    switch (data_021c75a0.step) {
        case EVENT_ANNOUNCE_IDLE:
            EventAnnounce_StepNothing(process);
            break;
        case EVENT_ANNOUNCE_WAIT_BUSY:
            EventAnnounce_StepWaitBusy(process);
            break;
        case EVENT_ANNOUNCE_WAIT_FREE:
            EventAnnounce_StepWaitFree(process);
            break;
        case EVENT_ANNOUNCE_ENTER:
            EventAnnounce_StepEnter(process);
            break;
        case EVENT_ANNOUNCE_ENTERING:
            EventAnnounce_StepNothing(process);
            break;
        case EVENT_ANNOUNCE_SHOW:
            EventAnnounce_StepShow(process);
            break;
        case EVENT_ANNOUNCE_TALKING:
            EventAnnounce_StepTalking(process);
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_02041850, EventAnnounceProcess_Execute)

/* func_020418d0 (vtable slot 0x00): the creation; 0 in the excluded scenes, else 1.
 * Not linked and outside scene 0xd: when the last creation was, the event kept in the save is
 * made all three if the calendar has it on or not started yet; the kept event is cleared, and
 * in scene 0x31 without the day's change data_021c779c's object is started. Otherwise
 * everything is forgotten and the kept event made all three.
 * Then an announcement entering scene 0x31 goes on to step 5 there (the event queue's flag 1
 * set, the day's change handled, the event looked at made the music's and the extra visitors
 * cleared); outside scene 0x31, and at step 1, it is dropped. */
int EventAnnounceProcess_Create(void)
{
    if (EventAnnounce_SceneIsExcluded()) {
        return 0;
    }

    if (!Session_IsLinked(data_020ccf94) && SceneQuery_Current() != SCENE_IN_LINK_WAIT) {
        if (data_021c7588) {
            DateTime now = {0};
            DateTime when;
            DateTime_Now(&now);
            EventAnnounce_Reset();
            u8 kept = data_021f39c0.unk_11;
            MI_CpuCopy8(&now, &when, sizeof(when));
            int state = EventCalendar_State(kept, &when, 0);
            if (state != EVENT_CALENDAR_OFF && state != EVENT_CALENDAR_ENDING) {
                data_020db6dc = kept;
                data_020db6e4 = kept;
                data_020db6e0 = kept;
            }
        }
        data_021f39c0.unk_11 = EVENT_CALENDAR_NONE;
        data_021c7588 = 0;
        if (SceneQuery_CurrentIs31() && !data_021c75a0.new_day) {
            func_0204762c();
        }
    } else {
        EventAnnounce_Reset();
        u8 kept = data_021f39c0.unk_11;
        data_020db6dc = kept;
        data_020db6e4 = kept;
        data_020db6e0 = kept;
        data_021c7588 = 1;
    }

    switch (data_021c75a0.step) {
        case EVENT_ANNOUNCE_IDLE:
        case EVENT_ANNOUNCE_WAIT_FREE:
        case EVENT_ANNOUNCE_ENTER:
            break;
        case EVENT_ANNOUNCE_WAIT_BUSY:
            EventAnnounce_Reset();
            break;
        default:
            if (!SceneQuery_CurrentIs31()) {
                EventAnnounce_Reset();
                break;
            }
            EventQueue_SetFlag1();
            data_021c75a0.step = EVENT_ANNOUNCE_SHOW;
            if (data_021c75a0.new_day) {
                func_02046a74(0);
                data_021c75a0.new_day = 0;
            }
            if (data_020db6e4 != EVENT_CALENDAR_NONE) {
                data_020db6dc = data_020db6e4;
            }
            TownObjects_ClearExtraVisitors();
            break;
    }
    return 1;
}
CLEAN_AS(func_020418d0, EventAnnounceProcess_Create)

/* func_02041a00 (vtable slot 0x44): the destructor that also frees the process. */
EventAnnounceProcess *EventAnnounceProcess_DestructFree(EventAnnounceProcess *process)
{
    process->base.vtable = data_020db71c;
    TalkReceiver_DestructSlot(&process->receiver);
    process->base.vtable = data_020da13c;
    Process_Destruct(&process->base);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_02041a00, EventAnnounceProcess_DestructFree)

/* func_02041a30 (vtable slot 0x40): the destructor. */
EventAnnounceProcess *EventAnnounceProcess_Destruct(EventAnnounceProcess *process)
{
    process->base.vtable = data_020db71c;
    TalkReceiver_DestructSlot(&process->receiver);
    process->base.vtable = data_020da13c;
    Process_Destruct(&process->base);
    return process;
}
CLEAN_AS(func_02041a30, EventAnnounceProcess_Destruct)

/* func_02041a5c: the constructor. */
EventAnnounceProcess *EventAnnounceProcess_Construct(EventAnnounceProcess *process)
{
    Process_Construct(&process->base);
    process->base.vtable = data_020da13c;
    process->base.vtable = data_020db71c;
    TalkReceiver_Construct(&process->receiver);
    return process;
}
CLEAN_AS(func_02041a5c, EventAnnounceProcess_Construct)

/* func_02041a84: the profile's create: a new process (0x9c bytes from the auxiliary heap,
 * cleared), nothing when there is no room.
 * QUIRK: declared without a result, as its matching source is; the ROM's code leaves the new
 * process (or NULL) in r0, the register a profile's create returns it in. */
void EventAnnounceProcess_New(void)
{
    EventAnnounceProcess *process = Heap_AllocAuxZeroed(sizeof(EventAnnounceProcess));
    if (process != NULL) {
        EventAnnounceProcess_Construct(process);
    }
}
CLEAN_AS(func_02041a84, EventAnnounceProcess_New)
