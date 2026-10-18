/* The functions of the events of main's queue, by kind (event_kinds.h). */
#include "event_kinds.h"

#include "clean.h"
#include "group_params.h"
#include "overlay_groups.h"
#include "scene_exit.h"
#include "scene_tables.h"
#include "session.h"
#include "object_claim.h"
#include "ov004/room_player_actor.h"
#include "player_actor_ops.h"
#include "scene_object_base.h"
#include "session_players.h"

/* The session's answer about an object (event_kinds.h); 6 when nothing was asked. */
extern u8 data_020dab94;
/* The session. */
extern NetSession *data_020ccf94;
/* A byte of field actor states 0x6e (2 while the state's animation runs, field_actor.c). */
extern u8 data_021c75b8;

/* The object registered under `id`, or NULL. */
static SceneObjectBase *find(u32 id)
{
    return (SceneObjectBase *) (uintptr_t) SceneObjectBase_FindAddress((int) id);
}

/* `object` told of an event (its vtable slot 0x4c), for this console's player. */
static void tell(SceneObjectBase *object, int code)
{
    ((SceneObjectBaseOnEvent *) SceneObjectBase_Slot(object, SCENE_OBJECT_BASE_SLOT_ON_EVENT))(object, code,
                                                                                               EVENT_KIND_THIS_PLAYER);
}

/* ---- The places a kind has nothing to do in ---- */

/* func_0203e63c: not yet (kinds 3 and 11 run until the scene changes; kind 13 is never taken
 * from the queue, EventQueue_StartKind13). */
int EventKind_NotYet(void)
{
    return 0;
}
CLEAN_AS(func_0203e63c, EventKind_NotYet)

/* func_0203e640: done at once. */
int EventKind_Done(void)
{
    return 1;
}
CLEAN_AS(func_0203e640, EventKind_Done)

/* func_0203e644: kind 0's, in all four tables: never. */
int EventKind_None(void)
{
    return 0;
}
CLEAN_AS(func_0203e644, EventKind_None)

/* ---- Kinds 8, 9, 13 and 14 ---- */

/* func_0203e648 (run, kind 13): once asked to end, func_02095f08(0) and done. */
int EventKind_RunKind13(EventQueueEntry *event)
{
    if (event->step != EVENT_STEP_FINISHED) {
        return 0;
    }
    PlayerActorOps_SwitchOwnFlag0b(0);
    return 1;
}
CLEAN_AS(func_0203e648, EventKind_RunKind13)

/* func_0203e664 (run, kinds 9 and 14): done once asked to end. */
int EventKind_RunKind9(EventQueueEntry *event)
{
    return event->step == EVENT_STEP_FINISHED;
}
CLEAN_AS(func_0203e664, EventKind_RunKind9)

/* func_0203e674 (take, kinds 9 and 14): taken at once, under way. */
int EventKind_TakeKind9(EventQueueEntry *event)
{
    event->step = EVENT_KIND_STEP_UNDER_WAY;
    return 1;
}
CLEAN_AS(func_0203e674, EventKind_TakeKind9)

/* func_0203e67c (run, kind 8): done once asked to end. */
int EventKind_RunKind8(EventQueueEntry *event)
{
    return event->step == EVENT_STEP_FINISHED;
}
CLEAN_AS(func_0203e67c, EventKind_RunKind8)

/* func_0203e68c (take, kind 8): when func_02095d04 and then func_ov004_0222bfb4 agree; under
 * way. */
int EventKind_TakeKind8(EventQueueEntry *event)
{
    if (!PlayerActorOps_QueueBelow5()) {
        return 0;
    }
    if (!RoomPlayerActor_RequestExit()) {
        return 0;
    }
    event->step = EVENT_KIND_STEP_UNDER_WAY;
    return 1;
}
CLEAN_AS(func_0203e68c, EventKind_TakeKind8)

/* ---- Kinds 5 and 10 (the start menu) ---- */

/* func_0203e6b4 (end): once func_02095bdc agrees. */
int EventKind_EndMenu(void)
{
    return PlayerActorOps_FinishState() != 0;
}
CLEAN_AS(func_0203e6b4, EventKind_EndMenu)

/* func_0203e6cc (run): done once asked to end. */
int EventKind_RunMenu(EventQueueEntry *event)
{
    return event->step == EVENT_STEP_FINISHED;
}
CLEAN_AS(func_0203e6cc, EventKind_RunMenu)

/* func_0203e6dc (take): when func_02095d84 and then func_02095904 agree; under way. */
int EventKind_TakeMenu(EventQueueEntry *event)
{
    if (!PlayerActorOps_MayAct()) {
        return 0;
    }
    if (!PlayerActorOps_RequestState10()) {
        return 0;
    }
    event->step = EVENT_KIND_STEP_UNDER_WAY;
    return 1;
}
CLEAN_AS(func_0203e6dc, EventKind_TakeMenu)

/* ---- Kinds 4 and 12 (a scene starts) ---- */

/* func_0203e704 (run): done once asked to end through byte 0x17 (EventQueue_FinishKind4Or12),
 * while flag 1 is clear and the byte data_021c75b8 is 2. */
int EventKind_RunSceneStart(EventQueueEntry *event)
{
    if (EventQueue_TestFlag1()) {
        return 0;
    }
    if (data_021c75b8 != 2) {
        return 0;
    }
    return event->step_17 == EVENT_STEP_FINISHED;
}
CLEAN_AS(func_0203e704, EventKind_RunSceneStart)

/* func_0203e740 (end, kind 12): this system's claim let go (ObjectClaim_Release), done. */
int EventKind_EndSceneObject(void)
{
    ObjectClaim_Release();
    return 1;
}
CLEAN_AS(func_0203e740, EventKind_EndSceneObject)

/* func_0203e750 (start, kind 12): with the object of the kept tile registered (its first id):
 * at EVENT_KIND_STEP_ASK_SESSION the session is asked about it (yes: go; asked: wait, and the
 * object let go); while waiting, the session's answer read (yes: go; no: the object let go, and
 * it keeps waiting); on go the object is told the scene starts and the event is under way. */
int EventKind_StartSceneObject(EventQueueEntry *event)
{
    SceneObjectBase *object = find(event->first_id);

    if (object == NULL) {
        return 0;
    }
    if (event->step == EVENT_KIND_STEP_ASK_SESSION) {
        switch (ObjectClaim_Ask(event->first_id)) {
            case 2:
                event->step = EVENT_KIND_STEP_GO;
                break;
            case 1:
                event->step = EVENT_KIND_STEP_ASKED;
                ObjectClaim_Claim(event->first_id);
                break;
        }
    }
    if (event->step == EVENT_KIND_STEP_ASKED) {
        switch (data_020dab94) {
            case EVENT_KIND_ANSWER_YES:
                event->step = EVENT_KIND_STEP_GO;
                break;
            case EVENT_KIND_ANSWER_NO:
                ObjectClaim_Claim(event->first_id);
                break;
        }
    }
    if (event->step == EVENT_KIND_STEP_GO) {
        tell(object, EVENT_KIND_TELL_SCENE_START);
        event->step = EVENT_KIND_STEP_UNDER_WAY;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0203e750, EventKind_StartSceneObject)

/* ---- Kind 11 ---- */

/* func_0203e7d4 (start): once func_02095d2c agrees, flag 4 set. */
int EventKind_StartKind11(void)
{
    if (!PlayerActorOps_Flag0bInState28_2_8()) {
        return 0;
    }
    EventQueue_SetFlag4();
    return 1;
}
CLEAN_AS(func_0203e7d4, EventKind_StartKind11)

/* func_0203e7f0 (take): when func_02095f28 agrees; func_02095f08(1) and flag 2 set. */
int EventKind_TakeKind11(void)
{
    if (!PlayerActorOps_StateFlagA20()) {
        return 0;
    }
    PlayerActorOps_SwitchOwnFlag0b(1);
    EventQueue_SetFlag2();
    return 1;
}
CLEAN_AS(func_0203e7f0, EventKind_TakeKind11)

/* ---- Kind 3 (the scene exit underfoot) ---- */

/* func_0203e814 (take): when func_02095d84 and then func_0209583c agree: the player (the first
 * id; looked up first) is told, if registered, and the scene exit of the event's step is
 * taken. */
int EventKind_TakeUnderfoot(EventQueueEntry *event)
{
    SceneObjectBase *player = find(event->first_id);

    if (!PlayerActorOps_MayAct()) {
        return 0;
    }
    if (!PlayerActorOps_StepOffDoor()) {
        return 0;
    }
    if (player != NULL) {
        tell(player, EVENT_KIND_TELL_UNDERFOOT);
    }
    SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), event->step);
    return 1;
}
CLEAN_AS(func_0203e814, EventKind_TakeUnderfoot)

/* ---- Kinds 2, 6 and 7 (an object acted on) ---- */

/* func_0203e860 (take, kind 7): with the player (the first id) registered and func_02095f28
 * and func_02095f08(1) agreeing, the object claimed (act EVENT_KIND_ACT_KIND_6_7). */
int EventKind_TakeKind7(EventQueueEntry *event)
{
    if (find(event->first_id) == NULL) {
        return 0;
    }
    if (!PlayerActorOps_StateFlagA20()) {
        return 0;
    }
    if (!PlayerActorOps_SwitchOwnFlag0b(1)) {
        return 0;
    }
    event->step_17 = EVENT_KIND_ACT_KIND_6_7;
    return EventKind_Claim(event);
}
CLEAN_AS(func_0203e860, EventKind_TakeKind7)

/* func_0203e89c (end): once func_02095bdc agrees, the object told the act ended and
 * this system's claim let go (ObjectClaim_Release). */
int EventKind_EndObjectEvent(EventQueueEntry *event)
{
    if (!PlayerActorOps_FinishState()) {
        return 0;
    }
    EventKind_TellTarget(event, EVENT_KIND_TELL_ENDED);
    ObjectClaim_Release();
    return 1;
}
CLEAN_AS(func_0203e89c, EventKind_EndObjectEvent)

/* func_0203e8c0 (run): the object looked up; while the player approaches, once func_02096174
 * agrees the object is told the act and the event is under way; done once asked to end.
 * REQUIRES: the object is still registered when func_02096174 agrees. */
int EventKind_RunObjectEvent(EventQueueEntry *event)
{
    SceneObjectBase *object = find(event->second_id);

    switch (event->step) {
        case EVENT_KIND_STEP_APPROACHING:
            if (PlayerActorOps_TestOwnFlag1()) {
                EventKind_TellObject(object, event->step_17);
                event->step = EVENT_KIND_STEP_UNDER_WAY;
            }
            break;
        case EVENT_STEP_FINISHED:
            return 1;
    }
    return 0;
}
CLEAN_AS(func_0203e8c0, EventKind_RunObjectEvent)

/* func_0203e904 (take, kind 6): when func_02095d84 agrees, the object claimed (act
 * EVENT_KIND_ACT_KIND_6_7); then func_02095904.
 * QUIRK: the player (the first id) is looked up and not used. */
int EventKind_TakeKind6(EventQueueEntry *event)
{
    (void) find(event->first_id);
    if (!PlayerActorOps_MayAct()) {
        return 0;
    }
    event->step_17 = EVENT_KIND_ACT_KIND_6_7;
    if (!EventKind_Claim(event)) {
        return 0;
    }
    PlayerActorOps_RequestState10();
    return 1;
}
CLEAN_AS(func_0203e904, EventKind_TakeKind6)

/* func_0203e938 (start): the object looked up. While asked (steps 0 and 1) the session's
 * answer is read: yes goes on (kind 7 first waits for func_02095d84 and func_02095904), no
 * refuses. On go the object is told the act starts and the player comes to it in the object's
 * way (func_02095944; the way is "none" for act EVENT_KIND_ACT_ASK_54): with "none",
 * func_02095904, the object told the act and the event under way; else the player approaches.
 * Refused, once func_02095bdc agrees the object is told and the event ends at once (0 here).
 * REQUIRES: the object is registered at steps 2 and 3. */
int EventKind_StartObjectEvent(EventQueueEntry *event)
{
    SceneObjectBase *object = find(event->second_id);
    int approach;

    switch (event->step) {
        case 0:
        case EVENT_KIND_STEP_ASKED:
            switch (data_020dab94) {
                case EVENT_KIND_ANSWER_YES:
                    event->step = event->kind == 7 ? EVENT_KIND_STEP_WAIT_PLAYER : EVENT_KIND_STEP_GO;
                    break;
                case EVENT_KIND_ANSWER_NO:
                    event->step = EVENT_KIND_STEP_REFUSED;
                    break;
            }
            break;
    }
    if (event->step == EVENT_KIND_STEP_WAIT_PLAYER) {
        if (!PlayerActorOps_MayAct()) {
            return 0;
        }
        if (!PlayerActorOps_RequestState10()) {
            return 0;
        }
        event->step = EVENT_KIND_STEP_GO;
    }
    switch (event->step) {
        case EVENT_KIND_STEP_GO:
            tell(object, EVENT_KIND_TELL_STARTS);
            approach = SceneObjectBase_ApproachKind(object);
            if (event->step_17 == EVENT_KIND_ACT_ASK_54) {
                approach = SCENE_OBJECT_BASE_APPROACH_NONE;
            }
            if (approach == SCENE_OBJECT_BASE_APPROACH_NONE) {
                PlayerActorOps_RequestState10();
                EventKind_TellObject(object, event->step_17);
                event->step = EVENT_KIND_STEP_UNDER_WAY;
            } else {
                PlayerActorOps_Approach((unsigned int) approach);
                event->step = EVENT_KIND_STEP_APPROACHING;
            }
            return 1;
        case EVENT_KIND_STEP_REFUSED:
            if (PlayerActorOps_FinishState()) {
                EventKind_TellTarget(event, EVENT_KIND_TELL_REFUSED);
                EventQueue_EndCurrent();
            }
            return 0;
    }
    return 0;
}
CLEAN_AS(func_0203e938, EventKind_StartObjectEvent)

/* func_0203ea04 (take, kind 2, EventQueue_RequestAct): the picked object (second id) and the
 * actor (first id) looked up; when func_02095d84 agrees: without a picked object the first one
 * the actor may act on is picked (none: not taken); with one, it must agree to be acted on
 * (act 0) or its slot 0x54 must (act EVENT_KIND_ACT_ASK_54). Then the object claimed, and
 * func_02095904. */
int EventKind_TakeAct(EventQueueEntry *event)
{
    SceneObjectBase *target = find(event->second_id);
    SceneObjectBase *actor = find(event->first_id);

    if (!PlayerActorOps_MayAct()) {
        return 0;
    }
    event->step_17 = EVENT_KIND_ACT_MAY_ACT;
    if (target == NULL) {
        void *found = SceneObjectBase_FindActable(actor);
        if (found == NULL) {
            return 0;
        }
        event->second_id = SceneObjectBase_Id(found);
    } else if (!SceneObjectBase_CanAct(target, actor)) {
        if (!((SceneObjectBaseAsk *) SceneObjectBase_Slot(target, SCENE_OBJECT_BASE_SLOT_ASK_54))(target, actor)) {
            return 0;
        }
        event->step_17 = EVENT_KIND_ACT_ASK_54;
    }
    if (!EventKind_Claim(event)) {
        return 0;
    }
    PlayerActorOps_RequestState10();
    return 1;
}
CLEAN_AS(func_0203ea04, EventKind_TakeAct)

/* func_0203ea80: the event's object (second id), if registered, told `code` (a person shared
 * through the session sends it there too, func_0203f320); then no target object, and for kind
 * 7 func_02095f08(0). */
void EventKind_TellTarget(EventQueueEntry *event, int code)
{
    SceneObjectBase *object = find(event->second_id);

    if (object != NULL) {
        if (SceneObjectBase_IsPerson(object) && ObjectClaim_Mode() == 1) {
            ObjectClaim_SendEvent(event->second_id, code);
        }
        tell(object, code);
    }
    EventQueue_SetTargetId(0);
    if (event->kind == 7) {
        PlayerActorOps_SwitchOwnFlag0b(0);
    }
}
CLEAN_AS(func_0203ea80, EventKind_TellTarget)

/* func_0203ead0: `object` told `code`; a person shared through the session sends it there too,
 * by the object's id.
 * REQUIRES: `object` is not NULL. */
void EventKind_TellObject(SceneObjectBase *object, int code)
{
    if (SceneObjectBase_IsPerson(object) && ObjectClaim_Mode() == 1) {
        ObjectClaim_SendEvent(SceneObjectBase_Id(object), code);
    }
    tell(object, code);
}
CLEAN_AS(func_0203ead0, EventKind_TellObject)

/* func_0203eb08: the event's object claimed, as a person or as another object.
 * REQUIRES: the object (second id) is registered. */
int EventKind_Claim(EventQueueEntry *event)
{
    if (SceneObjectBase_IsPerson(find(event->second_id))) {
        return EventKind_ClaimPerson(event);
    }
    return EventKind_ClaimObject(event);
}
CLEAN_AS(func_0203eb08, EventKind_Claim)

/* func_0203eb40: a person claimed. Decided here (func_0203f338 2): with a session linked, a
 * person acted on as act EVENT_KIND_ACT_KIND_6_7 must agree through its slot 0x58 about this
 * console's player; then go. Shared (1): asked (step 0). Then, except for kind 7, func_02095904
 * must agree; the person becomes the target object, and when shared the act is sent to the
 * other console (func_0203f32c). */
int EventKind_ClaimPerson(EventQueueEntry *event)
{
    int sharing = ObjectClaim_Mode();

    switch (sharing) {
        case 2:
            if (Session_IsLinked(data_020ccf94)) {
                SceneObjectBase *person = find(event->second_id);
                if (SceneObjectBase_IsPerson(person) && event->step_17 == EVENT_KIND_ACT_KIND_6_7) {
                    SceneObjectBaseAsk *ask =
                        (SceneObjectBaseAsk *) SceneObjectBase_Slot(person, SCENE_OBJECT_BASE_SLOT_ASK_58);
                    if (!ask(person, SessionPlayers_ActorOf(4))) {
                        return 0;
                    }
                }
            }
            event->step = EVENT_KIND_STEP_GO;
            break;
        case 1:
            event->step = 0;
            break;
        case 0:
            return 0;
    }
    if (event->kind != 7 && !PlayerActorOps_RequestState10()) {
        return 0;
    }
    EventQueue_SetTargetId(event->second_id);
    if (sharing == 1) {
        ObjectClaim_SendAct(event->second_id, event->step_17);
    }
    return 1;
}
CLEAN_AS(func_0203eb40, EventKind_ClaimPerson)

/* func_0203ebd0: another object claimed: the session asked about it (2: go; 1: asked; 0: not
 * now). Then, except for kind 7, func_02095904 must agree; the object becomes the target object
 * and is claimed in the session (ObjectClaim_Claim). */
int EventKind_ClaimObject(EventQueueEntry *event)
{
    switch (ObjectClaim_Ask(event->second_id)) {
        case 2:
            event->step = EVENT_KIND_STEP_GO;
            break;
        case 1:
            event->step = EVENT_KIND_STEP_ASKED;
            break;
        case 0:
            return 0;
    }
    if (event->kind != 7 && !PlayerActorOps_RequestState10()) {
        return 0;
    }
    EventQueue_SetTargetId(event->second_id);
    ObjectClaim_Claim(event->second_id);
    return 1;
}
CLEAN_AS(func_0203ebd0, EventKind_ClaimObject)

/* ---- Kind 1 (an overlay group opened, EventQueue_RequestKind1) ---- */

/* func_0203ec1c (end): once func_02095bdc agrees. */
int EventKind_EndGroup(void)
{
    return PlayerActorOps_FinishState() != 0;
}
CLEAN_AS(func_0203ec1c, EventKind_EndGroup)

/* func_0203ec34 (run): done once no group is open any more (GroupParams_CanOpen).
 * QUIRK: declared without a result; in the ROM GroupParams_CanOpen's answer is still in r0 when
 * it returns, and EventQueue_StepRunning reads it as the step's. */
void EventKind_RunGroup(void)
{
    (void) GroupParams_CanOpen();
}
CLEAN_AS(func_0203ec34, EventKind_RunGroup)

/* func_0203ec3c (take): when a group may be requested, func_02095e08 and func_02095ce0 agree:
 * the group of the event's step requested. */
int EventKind_TakeGroup(EventQueueEntry *event)
{
    if (!OverlayGroups_IsIdle()) {
        return 0;
    }
    if (!PlayerActorOps_MayActFree()) {
        return 0;
    }
    if (!PlayerActorOps_RequestState5()) {
        return 0;
    }
    OverlayGroups_Request(event->step);
    return 1;
}
CLEAN_AS(func_0203ec3c, EventKind_TakeGroup)
