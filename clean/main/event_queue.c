/* Main's queue of events (event_queue.h). */
#include "event_queue.h"

#include "clean.h"
#include "event_entries.h"
#include "list_ops.h"
#include "player_actor_ops.h"
#include "scene_object_base.h"
#include "session_players.h"
#include "state_flags.h"
#include "talk_object.h"

/* The four tables of functions, by kind (event_queue.h). */
extern EventQueueStepFn const data_020da9ec[15]; /* EVENT_RUNNING */
extern EventQueueStepFn const data_020daa28[15]; /* whether a queued event may be taken */
extern EventQueueStepFn const data_020daa64[15]; /* EVENT_STARTING */
extern EventQueueStepFn const data_020daaa0[15]; /* EVENT_ENDING */

extern EventQueueEntry *data_021c72b8; /* the current event, or NULL */
extern u32 data_021c72bc;              /* the id of the object events of kinds 2, 6 and 7 are about */
extern u32 data_021c72c0;              /* the flags */
extern List data_021c72c4;             /* the events waiting */

static_assert(sizeof(EventQueueEntry) == 0x1c, "EventQueueEntry size");
static_assert(offsetof(EventQueueEntry, priority) == 0x08, "EventQueueEntry layout");
static_assert(offsetof(EventQueueEntry, first_id) == 0x0c, "EventQueueEntry layout");
static_assert(offsetof(EventQueueEntry, state) == 0x14, "EventQueueEntry layout");
static_assert(offsetof(EventQueueEntry, step) == 0x16, "EventQueueEntry layout");
static_assert(offsetof(EventQueueEntry, unk_19) == 0x19, "EventQueueEntry layout");

/* The id of this console's player. */
static u32 player_id(void)
{
    return SceneObjectBase_Id(SessionPlayers_ActorOf(4));
}

/* Whether the current event is of kind 2, 6 or 7, asked in that order. */
static int is_object_event(void)
{
    return EventQueue_IsKind(2) || EventQueue_IsKind(6) || EventQueue_IsKind(7);
}

/* ---- Flags (data_021c72c0) ---- */

/* func_0203dec4 */
void EventQueue_ClearFlag10(void)
{
    EventQueue_ClearFlags(0x10);
}
CLEAN_AS(func_0203dec4, EventQueue_ClearFlag10)

/* func_0203ded0 */
void EventQueue_SetFlag10(void)
{
    EventQueue_SetFlags(0x10);
}
CLEAN_AS(func_0203ded0, EventQueue_SetFlag10)

/* func_0203dedc */
int EventQueue_TestFlag10(void)
{
    return EventQueue_TestFlags(0x10);
}
CLEAN_AS(func_0203dedc, EventQueue_TestFlag10)

/* ---- The current event and the queue ---- */

/* func_0203dee8: a current event of kind 13 is asked to end; 1 when there was one. */
int EventQueue_FinishKind13(void)
{
    if (!EventQueue_IsKind(13)) {
        return 0;
    }
    data_021c72b8->step = EVENT_STEP_FINISHED;
    return 1;
}
CLEAN_AS(func_0203dee8, EventQueue_FinishKind13)

/* func_0203df10: an event of kind 13 made current at once, already EVENT_RUNNING with step 5,
 * when this console's player exists, there is no current event (else func_0206f5cc) and
 * func_02095f28 agrees; func_02095f08(1) first. 1 when it started.
 * REQUIRES: a free entry (with all 15 taken the original writes through NULL). */
int EventQueue_StartKind13(void)
{
    EventQueueEntry *event;

    if (SessionPlayers_ActorOf(4) == NULL) {
        return 0;
    }
    if (EventQueue_HasCurrent()) {
        StateFlags_AskMenuClose();
        return 0;
    }
    if (!PlayerActorOps_StateFlagA20()) {
        return 0;
    }
    PlayerActorOps_SwitchOwnFlag0b(1);
    event = EventEntries_FindFree();
    event->first_id = 0;
    event->second_id = 0;
    event->kind = 13;
    event->state = EVENT_RUNNING;
    event->step = 5;
    data_021c72b8 = event;
    return 1;
}
CLEAN_AS(func_0203df10, EventQueue_StartKind13)

/* func_0203df6c: the current event freed; none is current. */
void EventQueue_EndCurrent(void)
{
    EventEntries_Free(data_021c72b8);
    data_021c72b8 = NULL;
}
CLEAN_AS(func_0203df6c, EventQueue_EndCurrent)

/* func_0203df88 (from func_0203ee08): the talk showing the receiver lets it go. */
void EventQueue_ReceiverLeaveTalk(TalkReceiver *receiver)
{
    TalkObject_DetachReceiver((TalkObject *) receiver->talk);
}
CLEAN_AS(func_0203df88, EventQueue_ReceiverLeaveTalk)

/* func_0203df94 (from func_0203ee14): the receiver handed to talk 0. */
void EventQueue_ReceiverToTalk(TalkReceiver *receiver)
{
    TalkObject_AttachReceiver(TalkObject_Get(0), receiver);
}
CLEAN_AS(func_0203df94, EventQueue_ReceiverToTalk)

/* func_0203dfac: during an event of kind 2, 6 or 7, the object registered under the target id
 * (data_021c72bc), as an address; otherwise 0. */
int EventQueue_TargetObjectAddress(void)
{
    if (is_object_event()) {
        return SceneObjectBase_FindAddress(data_021c72bc);
    }
    return 0;
}
CLEAN_AS(func_0203dfac, EventQueue_TargetObjectAddress)

/* func_0203dfe4 */
void EventQueue_SetTargetId(u32 id)
{
    data_021c72bc = id;
}
CLEAN_AS(func_0203dfe4, EventQueue_SetTargetId)

/* func_0203dff0: whether the current event is of kind 2, 6 or 7. */
int EventQueue_IsObjectEvent(void)
{
    return is_object_event();
}
CLEAN_AS(func_0203dff0, EventQueue_IsObjectEvent)

/* func_0203e020: a current event of kind 2, 6 or 7 about `object` (its second id) is asked to
 * end; 1 when there was one. */
int EventQueue_FinishObjectEvent(void *object)
{
    EventQueueEntry *event;

    if (!is_object_event()) {
        return 0;
    }
    event = data_021c72b8;
    if (event->second_id != SceneObjectBase_Id(object)) {
        return 0;
    }
    event->step = EVENT_STEP_FINISHED;
    return 1;
}
CLEAN_AS(func_0203e020, EventQueue_FinishObjectEvent)

/* func_0203e070: unless `blocked`, an event of kind 7 (priority 3) about this console's player
 * and `object`.
 * REQUIRES: this console's player exists (else func_0203efbc reads near address 0). */
int EventQueue_RequestKind7(void *object, int blocked)
{
    u32 player;

    if (blocked != 0) {
        return 0;
    }
    player = player_id();
    return EventQueue_Push((int) player, (int) SceneObjectBase_Id(object), 7, 3, 0);
}
CLEAN_AS(func_0203e070, EventQueue_RequestKind7)

/* func_0203e0a8: as EventQueue_RequestKind7, for kind 6.
 * REQUIRES: this console's player exists. */
int EventQueue_RequestKind6(void *object, int blocked)
{
    u32 player;

    if (blocked != 0) {
        return 0;
    }
    player = player_id();
    return EventQueue_Push((int) player, (int) SceneObjectBase_Id(object), 6, 3, 0);
}
CLEAN_AS(func_0203e0a8, EventQueue_RequestKind6)

/* func_0203e0e0 (from func_02010538, on an act): an event of kind 2 (priority 3) about the actor
 * and the object it picked (id 0 for none). The picked object's id is read first. */
int EventQueue_RequestAct(void *actor, void *picked)
{
    u32 picked_id = 0;

    if (picked != NULL) {
        picked_id = SceneObjectBase_Id(picked);
    }
    return EventQueue_Push((int) SceneObjectBase_Id(actor), (int) picked_id, 2, 3, 0);
}
CLEAN_AS(func_0203e0e0, EventQueue_RequestAct)

/* func_0203e110: a current event of kind 4 or 12 is asked to end through its byte 0x17; 1 when
 * there was one. */
int EventQueue_FinishKind4Or12(void)
{
    if (!EventQueue_IsKind(4) && !EventQueue_IsKind(12)) {
        return 0;
    }
    data_021c72b8->step_17 = EVENT_STEP_FINISHED;
    return 1;
}
CLEAN_AS(func_0203e110, EventQueue_FinishKind4Or12)

/* func_0203e140 */
int EventQueue_FinishKind14(void)
{
    if (!EventQueue_IsKind(14)) {
        return 0;
    }
    data_021c72b8->step = EVENT_STEP_FINISHED;
    return 1;
}
CLEAN_AS(func_0203e140, EventQueue_FinishKind14)

/* func_0203e168: an event of kind 14 (priority 0), only while none is current. */
int EventQueue_RequestKind14(void)
{
    if (data_021c72b8 != NULL) {
        return 0;
    }
    return EventQueue_Push(0, 0, 14, 0, 0);
}
CLEAN_AS(func_0203e168, EventQueue_RequestKind14)

/* func_0203e190 */
int EventQueue_IsKind9(void)
{
    return EventQueue_IsKind(9);
}
CLEAN_AS(func_0203e190, EventQueue_IsKind9)

/* func_0203e19c */
int EventQueue_FinishKind9(void)
{
    if (!EventQueue_IsKind(9)) {
        return 0;
    }
    data_021c72b8->step = EVENT_STEP_FINISHED;
    return 1;
}
CLEAN_AS(func_0203e19c, EventQueue_FinishKind9)

/* func_0203e1c4: an event of kind 9 (priority 0), only while none is current. */
int EventQueue_RequestKind9(void)
{
    if (data_021c72b8 != NULL) {
        return 0;
    }
    return EventQueue_Push(0, 0, 9, 0, 0);
}
CLEAN_AS(func_0203e1c4, EventQueue_RequestKind9)

/* func_0203e1ec */
int EventQueue_FinishKind10(void)
{
    return EventQueue_FinishIfKind(10);
}
CLEAN_AS(func_0203e1ec, EventQueue_FinishKind10)

/* func_0203e1f8 */
int EventQueue_IsKind10Unfinished(void)
{
    return EventQueue_IsKindUnfinished(10);
}
CLEAN_AS(func_0203e1f8, EventQueue_IsKind10Unfinished)

/* func_0203e204 */
int EventQueue_RequestKind10(void)
{
    return EventQueue_RequestForPlayer(10);
}
CLEAN_AS(func_0203e204, EventQueue_RequestKind10)

/* func_0203e210 */
void EventQueue_FinishKind5(void)
{
    EventQueue_FinishIfKind(5);
}
CLEAN_AS(func_0203e210, EventQueue_FinishKind5)

/* func_0203e21c */
int EventQueue_IsKind5Unfinished(void)
{
    return EventQueue_IsKindUnfinished(5);
}
CLEAN_AS(func_0203e21c, EventQueue_IsKind5Unfinished)

/* func_0203e228 */
int EventQueue_RequestKind5(void)
{
    return EventQueue_RequestForPlayer(5);
}
CLEAN_AS(func_0203e228, EventQueue_RequestKind5)

/* func_0203e234: a current event of `kind` is asked to end; 1 when there was one. */
int EventQueue_FinishIfKind(u8 kind)
{
    if (!EventQueue_IsKind(kind)) {
        return 0;
    }
    data_021c72b8->step = EVENT_STEP_FINISHED;
    return 1;
}
CLEAN_AS(func_0203e234, EventQueue_FinishIfKind)

/* func_0203e258: whether the current event is of `kind` and not asked to end. */
int EventQueue_IsKindUnfinished(u8 kind)
{
    return EventQueue_IsKind(kind) && data_021c72b8->step != EVENT_STEP_FINISHED;
}
CLEAN_AS(func_0203e258, EventQueue_IsKindUnfinished)

/* func_0203e280: an event of `kind` (priority 4) about this console's player (its second id).
 * REQUIRES: this console's player exists. */
int EventQueue_RequestForPlayer(int kind)
{
    return EventQueue_Push(0, (int) player_id(), kind, 4, 0);
}
CLEAN_AS(func_0203e280, EventQueue_RequestForPlayer)

/* func_0203e2a8 */
void EventQueue_ClearFlags(u32 mask)
{
    data_021c72c0 &= ~mask;
}
CLEAN_AS(func_0203e2a8, EventQueue_ClearFlags)

/* func_0203e2b8 */
void EventQueue_SetFlags(u32 mask)
{
    data_021c72c0 |= mask;
}
CLEAN_AS(func_0203e2b8, EventQueue_SetFlags)

/* func_0203e2c8: whether any flag of `mask` is set. */
int EventQueue_TestFlags(int mask)
{
    return (data_021c72c0 & (u32) mask) != 0;
}
CLEAN_AS(func_0203e2c8, EventQueue_TestFlags)

/* func_0203e2e0 */
void EventQueue_ClearFlag20(void)
{
    EventQueue_ClearFlags(0x20);
}
CLEAN_AS(func_0203e2e0, EventQueue_ClearFlag20)

/* func_0203e2ec */
void EventQueue_SetFlag20(void)
{
    EventQueue_SetFlags(0x20);
}
CLEAN_AS(func_0203e2ec, EventQueue_SetFlag20)

/* func_0203e2f8 */
int EventQueue_TestFlag20(void)
{
    return EventQueue_TestFlags(0x20);
}
CLEAN_AS(func_0203e2f8, EventQueue_TestFlag20)

/* func_0203e304 */
void EventQueue_ClearFlag8(void)
{
    EventQueue_ClearFlags(8);
}
CLEAN_AS(func_0203e304, EventQueue_ClearFlag8)

/* func_0203e310 */
void EventQueue_SetFlag8(void)
{
    EventQueue_SetFlags(8);
}
CLEAN_AS(func_0203e310, EventQueue_SetFlag8)

/* func_0203e31c */
int EventQueue_TestFlag8(void)
{
    return EventQueue_TestFlags(8);
}
CLEAN_AS(func_0203e31c, EventQueue_TestFlag8)

/* func_0203e328 */
void EventQueue_ClearFlag1(void)
{
    EventQueue_ClearFlags(1);
}
CLEAN_AS(func_0203e328, EventQueue_ClearFlag1)

/* func_0203e334 */
void EventQueue_SetFlag1(void)
{
    EventQueue_SetFlags(1);
}
CLEAN_AS(func_0203e334, EventQueue_SetFlag1)

/* func_0203e340 */
int EventQueue_TestFlag1(void)
{
    return EventQueue_TestFlags(1);
}
CLEAN_AS(func_0203e340, EventQueue_TestFlag1)

/* func_0203e34c (from func_0203e7d4, an event function) */
void EventQueue_SetFlag4(void)
{
    EventQueue_SetFlags(4);
}
CLEAN_AS(func_0203e34c, EventQueue_SetFlag4)

/* func_0203e358 (from func_0203e7f0, an event function) */
void EventQueue_SetFlag2(void)
{
    EventQueue_SetFlags(2);
}
CLEAN_AS(func_0203e358, EventQueue_SetFlag2)

/* func_0203e364 */
int EventQueue_TestFlag4(void)
{
    return EventQueue_TestFlags(4);
}
CLEAN_AS(func_0203e364, EventQueue_TestFlag4)

/* func_0203e370 */
int EventQueue_TestFlag2(void)
{
    return EventQueue_TestFlags(2);
}
CLEAN_AS(func_0203e370, EventQueue_TestFlag2)

/* func_0203e37c (from func_020414e0 and func_020415a8): unless flag 8 or 0x20 is set and when
 * this console's player exists, flags 2 and 4 are cleared and an event of kind 11 (priority 1)
 * about the player is asked for. */
int EventQueue_RequestKind11(void)
{
    void *player;

    if (EventQueue_TestFlag8() || EventQueue_TestFlag20()) {
        return 0;
    }
    player = SessionPlayers_ActorOf(4);
    if (player == NULL) {
        return 0;
    }
    EventQueue_ClearFlags(2 | 4);
    return EventQueue_Push(0, (int) SceneObjectBase_Id(player), 11, 1, 0);
}
CLEAN_AS(func_0203e37c, EventQueue_RequestKind11)

/* func_0203e3c8 (from func_02070218): when this console's player exists, an event of kind 1
 * (priority 2) about it, starting at `step`. */
int EventQueue_RequestKind1(int step)
{
    void *player = SessionPlayers_ActorOf(4);

    if (player == NULL) {
        return 0;
    }
    return EventQueue_Push(0, (int) SceneObjectBase_Id(player), 1, 2, (u8) step);
}
CLEAN_AS(func_0203e3c8, EventQueue_RequestKind1)

/* func_0203e3f8 */
int EventQueue_FinishKind8(void)
{
    if (!EventQueue_IsKind(8)) {
        return 0;
    }
    data_021c72b8->step = EVENT_STEP_FINISHED;
    return 1;
}
CLEAN_AS(func_0203e3f8, EventQueue_FinishKind8)

/* func_0203e420 (after the object underfoot is noted, and overlay 3's state 0x6d): an event of
 * kind 8 (priority 1) about this console's player.
 * REQUIRES: this console's player exists. */
int EventQueue_RequestKind8(void)
{
    return EventQueue_Push(0, (int) player_id(), 8, 1, 0);
}
CLEAN_AS(func_0203e420, EventQueue_RequestKind8)

/* func_0203e444 (FieldActor_NoteObjectUnderfoot, with func_02096190(4) and the object's
 * number, -1 for none): with an object, an event of kind 3 (priority 1) about `player` (id 0
 * for NULL) whose step is the object's number's low byte. */
int EventQueue_RequestUnderfoot(void *player, int object)
{
    u32 id;

    if (object < 0) {
        return 0;
    }
    id = 0;
    if (player != NULL) {
        id = SceneObjectBase_Id(player);
    }
    return EventQueue_Push((int) id, 0, 3, 1, (u8) object);
}
CLEAN_AS(func_0203e444, EventQueue_RequestUnderfoot)

/* func_0203e478: an event asked for: a free entry filled (state EVENT_QUEUED, bytes 0x17-0x19
 * cleared) and inserted into the queue by priority. 0 when all 15 are taken. */
int EventQueue_Push(int first_id, int second_id, int kind, int priority, u8 step)
{
    EventQueueEntry *event = EventEntries_FindFree();

    if (event == NULL) {
        return 0;
    }
    event->first_id = (u32) first_id;
    event->second_id = (u32) second_id;
    event->kind = (u8) kind;
    event->priority = (u8) priority;
    event->step = step;
    event->step_17 = 0;
    event->unk_18 = 0;
    event->unk_19 = 0;
    event->state = EVENT_QUEUED;
    ListOps_InsertByPriority(&data_021c72c4, (ListOpsPriorityNode *) event);
    return 1;
}
CLEAN_AS(func_0203e478, EventQueue_Push)

/* func_0203e4c0: whether there is a current event and it is of `kind`. */
int EventQueue_IsKind(u8 kind)
{
    EventQueueEntry *event = data_021c72b8;

    return event != NULL && event->kind == kind;
}
CLEAN_AS(func_0203e4c0, EventQueue_IsKind)

/* ---- The steps the process runs each frame (Process020daae4_Execute) ---- */

/* func_0203e55c: a current event in EVENT_ENDING is stepped through data_020daaa0; nonzero
 * frees it.
 * REQUIRES: a current event (the process checks func_0203ec98 first). */
void EventQueue_StepEnding(Process *process)
{
    EventQueueEntry *event = data_021c72b8;

    (void) process;
    if (event->state == EVENT_ENDING && data_020daaa0[event->kind](event)) {
        EventQueue_EndCurrent();
    }
}
CLEAN_AS(func_0203e55c, EventQueue_StepEnding)

/* func_0203e58c: a current event in EVENT_RUNNING is stepped through data_020da9ec; nonzero
 * makes the event current after the call EVENT_ENDING.
 * REQUIRES: a current event. */
void EventQueue_StepRunning(Process *process)
{
    EventQueueEntry *event = data_021c72b8;

    (void) process;
    if (event->state == EVENT_RUNNING && data_020da9ec[event->kind](event)) {
        data_021c72b8->state = EVENT_ENDING;
    }
}
CLEAN_AS(func_0203e58c, EventQueue_StepRunning)

/* func_0203e5c0: a current event in EVENT_STARTING is stepped through data_020daa64; nonzero
 * makes the event current after the call EVENT_RUNNING.
 * REQUIRES: a current event. */
void EventQueue_StepStarting(Process *process)
{
    EventQueueEntry *event = data_021c72b8;

    (void) process;
    if (event->state == EVENT_STARTING && data_020daa64[event->kind](event)) {
        data_021c72b8->state = EVENT_RUNNING;
    }
}
CLEAN_AS(func_0203e5c0, EventQueue_StepStarting)

/* func_0203e5f4: the first queued event, in queue order, whose kind's function of data_020daa28
 * agrees is taken out of the queue and made current, EVENT_STARTING. */
void EventQueue_TakeNext(Process *process)
{
    EventQueueEntry *event = (EventQueueEntry *) data_021c72c4.first;

    (void) process;
    while (event != NULL) {
        if (data_020daa28[event->kind](event)) {
            List_Remove(&data_021c72c4, &event->link);
            data_021c72b8 = event;
            event->state = EVENT_STARTING;
            return;
        }
        event = (EventQueueEntry *) event->link.next;
    }
}
CLEAN_AS(func_0203e5f4, EventQueue_TakeNext)

/* ---- Starting over ---- */

#include "town_objects.h"

/* func_0203ec98: whether there is a current event. */
int EventQueue_HasCurrent(void)
{
    return data_021c72b8 != NULL;
}
CLEAN_AS(func_0203ec98, EventQueue_HasCurrent)

/* func_0203ecac (when a scene starts, func_020b6d20): the queue started over, and the scene's
 * own event made current at once (priority 1, byte 0x17 at 5): of kind 12 about the object on
 * the kept tile (TownObjects_AtKeptTile) when there is one, starting at step 7; else of kind 4,
 * already EVENT_RUNNING at step 5. */
void EventQueue_StartScene(void)
{
    EventQueueEntry *event;
    int object;

    EventQueue_Reset();
    event = EventEntries_FindFree();
    object = TownObjects_AtKeptTile();
    if (object != 0) {
        event->first_id = (u32) object;
        event->second_id = 0;
        event->kind = 12;
        event->state = EVENT_STARTING;
        event->step = 7;
    } else {
        event->first_id = 0;
        event->second_id = 0;
        event->kind = 4;
        event->state = EVENT_RUNNING;
        event->step = 5;
    }
    event->priority = 1;
    event->step_17 = 5;
    data_021c72b8 = event;
}
CLEAN_AS(func_0203ecac, EventQueue_StartScene)

/* func_0203ecfc: the queue emptied, every entry freed, no current event nor target object, and
 * flags 2 and 4 cleared. */
void EventQueue_Reset(void)
{
    ListOps_Clear(&data_021c72c4);
    EventEntries_FreeAll();
    data_021c72b8 = NULL;
    data_021c72bc = 0;
    EventQueue_ClearFlags(2 | 4);
}
CLEAN_AS(func_0203ecfc, EventQueue_Reset)
