/* The scene objects' base class: flags, reach, the base class's own slots and the registry
 * (scene_object_base.h). */
#include "scene_object_base.h"

#include "actor.h" /* Vec_YawTo */
#include "clean.h"
#include "event_queue.h"

/* The registered objects. */
extern List data_021c72cc;
/* Half the angle (a 16-bit fraction of a turn) within which a viewer must face an object to act
 * on it. */
extern const s16 data_020ca4cc[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* The node of `list` registered under `id`, or NULL (and NULL for id 0). */
extern SceneObjectRegistryNode *func_02065c00(List *list, int id);

static_assert(sizeof(Process) == 0x50, "Process size");
static_assert(offsetof(SceneObjectBase, position) == 0x5c, "SceneObjectBase layout");
static_assert(offsetof(SceneObjectBase, yaw) == 0x8e, "SceneObjectBase layout");
static_assert(offsetof(SceneObjectBase, entry) == 0xd4, "SceneObjectBase layout");
static_assert(offsetof(SceneObjectBase, entry.id) == 0xdc, "SceneObjectBase layout");
static_assert(offsetof(SceneObjectBase, reach_squared) == 0xe4, "SceneObjectBase layout");
static_assert(offsetof(SceneObjectBase, flags) == 0xe8, "SceneObjectBase layout");

/* The point `object` is reached at (vtable slot 0x50). */
static Vec3 *reach_point(SceneObjectBase *object)
{
    return ((SceneObjectBaseReachPoint *) SceneObjectBase_Slot(object, SCENE_OBJECT_BASE_SLOT_REACH_POINT))(object);
}

/* ---- Flags (0xe8) ---- */

/* func_0203ed58 */
void SceneObjectBase_ClearFlags(SceneObjectBase *object, u16 mask)
{
    object->flags &= (u16) ~mask;
}
CLEAN_AS(func_0203ed58, SceneObjectBase_ClearFlags)

/* func_0203ed68 */
void SceneObjectBase_SetFlags(SceneObjectBase *object, u16 mask)
{
    object->flags |= mask;
}
CLEAN_AS(func_0203ed68, SceneObjectBase_SetFlags)

/* func_0203ed78: whether any flag of `mask` is set. */
int SceneObjectBase_TestFlags(SceneObjectBase *object, u16 mask)
{
    return (object->flags & mask) != 0;
}
CLEAN_AS(func_0203ed78, SceneObjectBase_TestFlags)

/* func_0203ed8c */
int SceneObjectBase_IsPerson(SceneObjectBase *object)
{
    return SceneObjectBase_TestFlags(object, SCENE_OBJECT_BASE_PERSON);
}
CLEAN_AS(func_0203ed8c, SceneObjectBase_IsPerson)

/* func_0203ed98 (from SceneObject_Init) */
void SceneObjectBase_MarkPerson(SceneObjectBase *object)
{
    SceneObjectBase_SetFlags(object, SCENE_OBJECT_BASE_PERSON);
}
CLEAN_AS(func_0203ed98, SceneObjectBase_MarkPerson)

/* func_0203eda4: how this console's player comes to the object when an act on it starts (given
 * to func_02095944): 0 with flag 1, else 1 with flag 2, else SCENE_OBJECT_BASE_APPROACH_NONE. */
int SceneObjectBase_ApproachKind(SceneObjectBase *object)
{
    if (SceneObjectBase_TestFlags(object, SCENE_OBJECT_BASE_APPROACH_0)) {
        return 0;
    }
    if (SceneObjectBase_TestFlags(object, SCENE_OBJECT_BASE_APPROACH_1)) {
        return 1;
    }
    return SCENE_OBJECT_BASE_APPROACH_NONE;
}
CLEAN_AS(func_0203eda4, SceneObjectBase_ApproachKind)

/* func_0203edd0: flags 1 and 2 cleared: the player does not move to the object. */
void SceneObjectBase_ClearApproach(SceneObjectBase *object)
{
    SceneObjectBase_ClearFlags(object, SCENE_OBJECT_BASE_APPROACH_0 | SCENE_OBJECT_BASE_APPROACH_1);
}
CLEAN_AS(func_0203edd0, SceneObjectBase_ClearApproach)

/* func_0203eddc (the base class's set-up, and overlay 68): flag 1 cleared and flag 2 set. */
void SceneObjectBase_DefaultApproach(SceneObjectBase *object)
{
    SceneObjectBase_ClearFlags(object, SCENE_OBJECT_BASE_APPROACH_0 | SCENE_OBJECT_BASE_APPROACH_1);
    SceneObjectBase_SetFlags(object, SCENE_OBJECT_BASE_APPROACH_1);
}
CLEAN_AS(func_0203eddc, SceneObjectBase_DefaultApproach)

/* func_0203edf4: the distance within which the player may act on the object, kept squared. */
void SceneObjectBase_SetReach(SceneObjectBase *object, int distance)
{
    object->reach_squared = FX_MulFunc(distance, distance);
}
CLEAN_AS(func_0203edf4, SceneObjectBase_SetReach)

/* ---- The object's message receiver ---- */

/* func_0203ee08: the talk showing the object's receiver lets it go. */
void SceneObjectBase_ReleaseReceiver(SceneObjectBase *object, MessageReceiver *receiver)
{
    (void) object;
    EventQueue_ReceiverLeaveTalk(receiver);
}
CLEAN_AS(func_0203ee08, SceneObjectBase_ReleaseReceiver)

/* func_0203ee14: the object's receiver handed to talk 0. */
void SceneObjectBase_TakeReceiver(SceneObjectBase *object, MessageReceiver *receiver)
{
    (void) object;
    EventQueue_ReceiverToTalk(receiver);
}
CLEAN_AS(func_0203ee14, SceneObjectBase_TakeReceiver)

/* ---- The base class's own slots ---- */

/* func_0203ee20 (slot 0x5c): no. */
int SceneObjectBase_Slot5c(void)
{
    return 0;
}
CLEAN_AS(func_0203ee20, SceneObjectBase_Slot5c)

/* func_0203ee24 (slot 0x58): no. */
int SceneObjectBase_Ask58(void)
{
    return 0;
}
CLEAN_AS(func_0203ee24, SceneObjectBase_Ask58)

/* func_0203ee28 (slot 0x54): no. */
int SceneObjectBase_Ask54(void)
{
    return 0;
}
CLEAN_AS(func_0203ee28, SceneObjectBase_Ask54)

/* func_0203ee2c (slot 0x50): the object is reached at its position. */
int SceneObjectBase_ReachPointAddress(SceneObjectBase *object)
{
    return (int) (uintptr_t) &object->position;
}
CLEAN_AS(func_0203ee2c, SceneObjectBase_ReachPointAddress)

/* func_0203ee30 (slot 0x4c): events change nothing. */
void SceneObjectBase_OnEvent(void) {}
CLEAN_AS(func_0203ee30, SceneObjectBase_OnEvent)

/* func_0203ee78 (slot 0x48): no one may act on it. */
int SceneObjectBase_MayAct(void)
{
    return 0;
}
CLEAN_AS(func_0203ee78, SceneObjectBase_MayAct)

/* ---- Whether an object may be acted on ---- */

/* func_0203ee34: whether `actor` may act on `target`: within its reach, facing it within the
 * angle data_020ca4cc[0] either way, and the target's slot 0x48 agrees. */
int SceneObjectBase_CanAct(SceneObjectBase *target, SceneObjectBase *actor)
{
    s16 half_angle;

    if (!SceneObjectBase_InReach(target, actor)) {
        return 0;
    }
    half_angle = data_020ca4cc[0];
    if (!SceneObjectBase_Faces(target, actor, (s16) -half_angle, half_angle)) {
        return 0;
    }
    return ((SceneObjectBaseAsk *) SceneObjectBase_Slot(target, SCENE_OBJECT_BASE_SLOT_MAY_ACT))(target, actor);
}
CLEAN_AS(func_0203ee34, SceneObjectBase_CanAct)

/* func_0203ee7c: whether `actor`'s reach point is within the target's reach of the target's, in
 * the ground plane (always, without a reach). The reach points are asked for each coordinate,
 * the actor's first. */
int SceneObjectBase_InReach(SceneObjectBase *target, SceneObjectBase *actor)
{
    Vec3 offset;
    const Vec3 *from;
    const Vec3 *to;

    if (target->reach_squared == 0) {
        return 1;
    }
    to = reach_point(actor);
    from = reach_point(target);
    offset.x = to->x - from->x;
    to = reach_point(actor);
    from = reach_point(target);
    offset.y = to->y - from->y;
    to = reach_point(actor);
    from = reach_point(target);
    offset.z = to->z - from->z;
    return Vec_LengthSquaredXZ(&offset) < (s64) target->reach_squared;
}
CLEAN_AS(func_0203ee7c, SceneObjectBase_InReach)

/* func_0203ef00: whether the heading from `viewer`'s reach point to the target's, less the
 * viewer's yaw (kept to 16 bits), is within [min, max]. */
int SceneObjectBase_Faces(SceneObjectBase *target, SceneObjectBase *viewer, int min, int max)
{
    Vec3 from = *reach_point(viewer);
    Vec3 to = *reach_point(target);
    s16 turn = (s16) (Vec_YawTo(&from, &to) - viewer->yaw);

    return turn >= min && turn <= max;
}
CLEAN_AS(func_0203ef00, SceneObjectBase_Faces)

/* ---- The registry (data_021c72cc) ---- */

/* func_0203ef5c (EventQueue's act without a picked object): the first registered object, other
 * than `actor`, that `actor` may act on; NULL for none. */
void *SceneObjectBase_FindActable(void *actor)
{
    SceneObjectRegistryNode *node = (SceneObjectRegistryNode *) data_021c72cc.first;

    while (node != NULL) {
        SceneObjectBase *object = node->object;
        if (object != actor && SceneObjectBase_CanAct(object, actor)) {
            return object;
        }
        node = (SceneObjectRegistryNode *) node->link.next;
    }
    return NULL;
}
CLEAN_AS(func_0203ef5c, SceneObjectBase_FindActable)

/* func_0203ef90: the object registered under `id`, as an address; 0 for none (and for id 0). */
int SceneObjectBase_FindAddress(int id)
{
    SceneObjectRegistryNode *node = func_02065c00(&data_021c72cc, id);

    return node != NULL ? (int) (uintptr_t) node->object : 0;
}
CLEAN_AS(func_0203ef90, SceneObjectBase_FindAddress)

/* func_0203efb0: the object's id: its class id in the high half, `value` (with its own high
 * half or'ed in) below. */
void SceneObjectBase_SetId(SceneObjectBase *object, u32 value)
{
    object->entry.id = value | ((u32) object->process.class_id << 16);
}
CLEAN_AS(func_0203efb0, SceneObjectBase_SetId)
