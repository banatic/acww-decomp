/* Where a scene object looks (scene_look.h). */
#include "scene_look.h"

#include "actor.h"
#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "globe.h"
#include "model_object.h"
#include "player_actor_ops.h"
#include "session_players.h"

static_assert(offsetof(SceneLook, target) == 0x04, "SceneLook layout");
static_assert(offsetof(SceneLook, priority) == 0x14, "SceneLook layout");
static_assert(offsetof(SceneLook, pitch) == 0x1a, "SceneLook layout");
static_assert(offsetof(SceneLook, yaw) == 0x22, "SceneLook layout");
static_assert(offsetof(SceneLook, on_target) == 0x2a, "SceneLook layout");
static_assert(offsetof(SceneLook, head) == 0x2c, "SceneLook layout");
static_assert(offsetof(SceneLook, range) == 0x5c, "SceneLook layout");
static_assert(offsetof(SceneLook, actor) == 0x64, "SceneLook layout");
static_assert(sizeof(SceneLook) == 0x68, "SceneLook layout");

/* The object's parts read here. */
#define SCENE_LOOK_OBJECT_POSITION 0x5c /* Vec3 */
#define SCENE_LOOK_OBJECT_PITCH 0x8c    /* s16 */
#define SCENE_LOOK_OBJECT_ANGLE 0x8e    /* s16 */
#define SCENE_LOOK_OBJECT_MODEL 0xec
#define SCENE_LOOK_OBJECT_LOOK 0x3b0

/* The player's field actor, and the model's joint of the head. */
#define SCENE_LOOK_PLAYER_ACTOR 4
#define SCENE_LOOK_HEAD_JOINT 15

/* What SceneLook_Construct and SceneLook_Request set. */
#define SCENE_LOOK_PITCH_STEP 0x200
#define SCENE_LOOK_YAW_STEP 0x400
#define SCENE_LOOK_PITCH_LIMIT 0x1a00
#define SCENE_LOOK_YAW_LIMIT 0x3000
#define SCENE_LOOK_RANGE 0x8000 /* 8.0 */

/* The kinds' handlers (member pointers of the look, called with the object), and the origin. */
extern MemberPointer data_021c1794[SCENE_LOOK_KINDS];
extern Vec3 data_021fbee8;

/* `value`'s magnitude as the ARM computes it: the most negative int stays negative. */
static int scene_look_abs(int value)
{
    return value < 0 ? (int) (0u - (u32) value) : value;
}

/* `src` copied into `dst` a word at a time, each read just before it is written, as the game
 * does: with the two overlapping, a word written may be read again. */
static void scene_look_copy_point(Vec3 *dst, const Vec3 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

static Vec3 *scene_look_position(u8 *object)
{
    return (Vec3 *) (void *) (object + SCENE_LOOK_OBJECT_POSITION);
}

static s16 scene_look_object_s16(const u8 *object, u32 offset)
{
    return *(const s16 *) (const void *) (object + offset);
}

/* Both angles moved a step towards `pitch` and `yaw`, the yaw first; the look is off target
 * unless both are there. */
static void scene_look_turn(SceneLook *self, int pitch, int yaw)
{
    if (self->yaw != yaw) {
        Approach_S16Wrapped(&self->yaw, yaw, self->yaw_step);
    }
    if (self->pitch != pitch) {
        Approach_S16Wrapped(&self->pitch, pitch, self->pitch_step);
    }
    if (self->yaw != yaw || self->pitch != pitch) {
        self->on_target = 0;
    }
}

/* func_0201a7fc: whether the look is not locked and on target. */
int SceneLook_IsOnTarget(SceneLook *self)
{
    return self->locked == 0 && self->on_target == 1;
}
CLEAN_AS(func_0201a7fc, SceneLook_IsOnTarget)

/* func_0201a814: whether `yaw` is within the yaw limit (SceneLook_Within). */
int SceneLook_InView(SceneLook *self, int yaw)
{
    return SceneLook_Within(yaw, self->yaw_limit);
}
CLEAN_AS(func_0201a814, SceneLook_InView)

/* func_0201a824: whether `value`'s magnitude is below `limit` (signed).
 * QUIRK: the most negative int counts as negative, so it is below any other limit. */
int SceneLook_Within(int value, int limit)
{
    return scene_look_abs(value) < limit;
}
CLEAN_AS(func_0201a824, SceneLook_Within)

/* func_0201a838: each frame, unless the look is locked, the kind's handler (data_021c1794) is
 * called on the object's look (at 0x3b0 of `object`) with the object; a kind of 6 or more has
 * none. */
void SceneLook_Update(SceneLook *self, u8 *object)
{
    if (self->locked != 0 || self->kind >= SCENE_LOOK_KINDS) {
        return;
    }
    const MemberPointer *handler = &data_021c1794[self->kind];
    void *look = MemberPointer_Object(handler, object + SCENE_LOOK_OBJECT_LOOK);
    ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(handler, look))(look, object);
}
CLEAN_AS(func_0201a838, SceneLook_Update)

/* func_0201a878: kind 5's handler: both angles move towards the rest angles, the yaw first.
 * `on_target` is left as it is. */
void SceneLook_AimRest(SceneLook *self)
{
    if (self->yaw != self->yaw_rest) {
        Approach_S16Wrapped(&self->yaw, self->yaw_rest, self->yaw_step);
    }
    if (self->pitch != self->pitch_rest) {
        Approach_S16Wrapped(&self->pitch, self->pitch_rest, self->pitch_step);
    }
}
CLEAN_AS(func_0201a878, SceneLook_AimRest)

/* func_0201a8b4: kind 3's handler, the point: the aim is straight ahead while the point is
 * beyond the range or, with `in_view_only`, outside the yaw limit; else the yaw to it from the
 * object (SceneLook_ClampedYaw), and once the head point is known the pitch to it from there
 * less the object's pitch (SceneLook_ClampedPitch), with the look on target. Without a head
 * point the pitch aims at 0 and the look is not on target. */
void SceneLook_AimPoint(SceneLook *self, u8 *object)
{
    Vec3 *position = scene_look_position(object);
    int yaw = 0;
    int pitch = 0;
    Vec3 head;

    fx32 distance = Vec_Distance(&self->point, position);
    self->on_target = 0;
    if (self->range == 0 || scene_look_abs(distance) < self->range) {
        int angle = SceneLook_Yaw(self, &self->point, position, scene_look_object_s16(object, SCENE_LOOK_OBJECT_ANGLE));
        if (self->in_view_only == 0 || SceneLook_InView(self, angle)) {
            yaw = SceneLook_ClampedYaw(self, &self->point, position, scene_look_object_s16(object, SCENE_LOOK_OBJECT_ANGLE));
            if (SceneLook_HeadPoint(self, &head)) {
                pitch =
                    SceneLook_ClampedPitch(self, &self->point, &head, scene_look_object_s16(object, SCENE_LOOK_OBJECT_PITCH));
                self->on_target = 1;
            }
        }
    }
    scene_look_turn(self, pitch, yaw);
}
CLEAN_AS(func_0201a8b4, SceneLook_AimPoint)

/* func_0201a98c: kind 2's handler, an object: at the head point of the object's own look
 * (SceneLook_AimAt); nothing while there is no object or it has no head point. */
void SceneLook_AimObject(SceneLook *self, u8 *object)
{
    Vec3 head;

    if (self->target == 0) {
        return;
    }
    u8 *target = (u8 *) (uintptr_t) self->target;
    if (!SceneLook_HeadPoint((SceneLook *) (void *) (target + SCENE_LOOK_OBJECT_LOOK), &head)) {
        return;
    }
    Vec3 copy = head;
    SceneLook_AimAt(self, object, target, &copy, self->range, self->in_view_only);
}
CLEAN_AS(func_0201a98c, SceneLook_AimObject)

/* func_0201a9d8: kind 1's handler: the player (field actor 4, SceneLook_AimActor). */
void SceneLook_AimPlayer(SceneLook *self, u8 *object)
{
    SceneLook_AimActor(self, object, SCENE_LOOK_PLAYER_ACTOR, self->range, self->in_view_only);
}
CLEAN_AS(func_0201a9d8, SceneLook_AimPlayer)

/* func_0201a9f4: kind 4's handler: the field actor numbered `actor` (SceneLook_AimActor). */
void SceneLook_AimActorNumber(SceneLook *self, u8 *object)
{
    SceneLook_AimActor(self, object, self->actor, self->range, self->in_view_only);
}
CLEAN_AS(func_0201a9f4, SceneLook_AimActorNumber)

/* func_0201aa10: at the head point of field actor `actor` (SceneLook_AimAt); nothing while the
 * actor has no object (func_02096190) or no head point (func_020954c0). */
void SceneLook_AimActor(SceneLook *self, u8 *object, int actor, fx32 range, u8 in_view_only)
{
    Vec3 head;

    int target = SessionPlayers_ActorHandle(actor);
    if (target == 0) {
        return;
    }
    if (PlayerActorOps_HeadPoint(&head, actor) == 0) {
        return;
    }
    Vec3 copy = head;
    SceneLook_AimAt(self, object, (u8 *) (uintptr_t) (u32) target, &copy, range, in_view_only);
}
CLEAN_AS(func_0201aa10, SceneLook_AimActor)

/* func_0201aa5c: kind 0's handler: both angles move back to 0, the yaw first. `on_target` is
 * left as it is. */
void SceneLook_AimAhead(SceneLook *self)
{
    if (self->yaw != 0) {
        Approach_S16Wrapped(&self->yaw, 0, self->yaw_step);
    }
    if (self->pitch != 0) {
        Approach_S16Wrapped(&self->pitch, 0, self->pitch_step);
    }
}
CLEAN_AS(func_0201aa5c, SceneLook_AimAhead)

/* func_0201aa94: the aim at `target`, an object, whose head is at `target_head`: straight ahead
 * while the target's position is beyond the range or, with `in_view_only`, the yaw to it is
 * outside the yaw limit; else the pitch from the look's head point to the target's head (when
 * the head point is known, SceneLook_ClampedPitch with no base pitch) and the yaw to the
 * target's position from the object (clamped), with the look on target.
 * QUIRK: the test for no target is of the address of its position (the target plus 0x5c), so a
 * null target is not caught; callers pass none. */
void SceneLook_AimAt(SceneLook *self, u8 *object, u8 *target, const Vec3 *target_head, fx32 range, u8 in_view_only)
{
    uintptr_t target_at = (uintptr_t) target + SCENE_LOOK_OBJECT_POSITION;
    Vec3 *position = scene_look_position(object);
    int pitch = 0;
    int yaw = 0;
    Vec3 head;

    self->on_target = 0;
    if ((u32) target_at != 0) {
        Vec3 *target_position = (Vec3 *) target_at;
        fx32 distance = Vec_Distance(target_position, position);
        if (range == 0 || scene_look_abs(distance) < range) {
            int angle = SceneLook_Yaw(self, target_position, position, scene_look_object_s16(object, SCENE_LOOK_OBJECT_ANGLE));
            if (in_view_only == 0 || SceneLook_InView(self, angle)) {
                if (SceneLook_HeadPoint(self, &head)) {
                    pitch = SceneLook_ClampedPitch(self, target_head, &head, 0);
                }
                yaw = SceneLook_ClampYaw(self, angle);
                self->on_target = 1;
            }
        }
    }
    scene_look_turn(self, pitch, yaw);
}
CLEAN_AS(func_0201aa94, SceneLook_AimAt)

/* func_0201ab70: `pitch` held within the pitch limit: beyond it, the limit with its sign
 * (a pitch of 0 or more gives +limit, else -limit as 16 bits).
 * QUIRK: the most negative int counts as within any limit above it. */
int SceneLook_ClampPitch(SceneLook *self, int pitch)
{
    int limit = self->pitch_limit;
    if (scene_look_abs(pitch) > limit) {
        pitch = pitch >= 0 ? limit : (s16) -limit;
    }
    return pitch;
}
CLEAN_AS(func_0201ab70, SceneLook_ClampPitch)

/* func_0201ab94: the pitch to `target` from `eye` less `base` (SceneLook_Pitch), held within
 * the pitch limit. */
int SceneLook_ClampedPitch(SceneLook *self, const Vec3 *target, const Vec3 *eye, int base)
{
    return SceneLook_ClampPitch(self, SceneLook_Pitch(self, target, eye, base));
}
CLEAN_AS(func_0201ab94, SceneLook_ClampedPitch)

/* func_0201abac: `yaw` held within the yaw limit: beyond it, the limit with its sign (a yaw
 * above 0 gives +limit, else -limit as 16 bits).
 * QUIRK: unlike SceneLook_ClampPitch, 0 takes the negative side; it is only beyond a negative
 * limit. */
int SceneLook_ClampYaw(SceneLook *self, int yaw)
{
    int limit = self->yaw_limit;
    if (scene_look_abs(yaw) > limit) {
        yaw = yaw > 0 ? limit : (s16) -limit;
    }
    return yaw;
}
CLEAN_AS(func_0201abac, SceneLook_ClampYaw)

/* func_0201abd0: the yaw to `target` from `from` less `base` (SceneLook_Yaw), held within the
 * yaw limit. */
int SceneLook_ClampedYaw(SceneLook *self, const Vec3 *target, const Vec3 *from, int base)
{
    return SceneLook_ClampYaw(self, SceneLook_Yaw(self, target, from, base));
}
CLEAN_AS(func_0201abd0, SceneLook_ClampedYaw)

/* func_0201abe8: the angle up to `target` from `eye` (its height difference over their
 * distance, Math_Atan2) less `base`, as 16 bits. */
s16 SceneLook_Pitch(SceneLook *self, const Vec3 *target, const Vec3 *eye, int base)
{
    (void) self;
    fx32 distance = Vec_Distance(target, eye);
    s16 angle = Math_Atan2((fx32) ((u32) target->y - (u32) eye->y), distance);
    return (s16) ((u32) angle - (u32) base);
}
CLEAN_AS(func_0201abe8, SceneLook_Pitch)

/* func_0201ac10: the angle round to `target` from `from` (Vec_YawTo) less `base`, as 16 bits. */
int SceneLook_Yaw(SceneLook *self, const Vec3 *target, const Vec3 *from, int base)
{
    (void) self;
    return (s16) ((u32) Vec_YawTo(from, target) - (u32) base);
}
CLEAN_AS(func_0201ac10, SceneLook_Yaw)

/* func_0201ac28: whether the look's target can be seen from `object`: for kind 1 the position
 * of field actor `actor` (func_02096190), for kind 3 the point, else nothing; not when that is
 * the origin, beyond the range, or (with `in_view_only`) outside the yaw limit from the object's
 * angle. */
int SceneLook_CanSee(SceneLook *self, u8 *object)
{
    const Vec3 *seen = NULL;

    switch (self->kind) {
        case SCENE_LOOK_PLAYER: {
            int actor = SessionPlayers_ActorHandle(self->actor);
            if (actor != 0) {
                seen = scene_look_position((u8 *) (uintptr_t) (u32) actor);
            }
            break;
        }
        case SCENE_LOOK_POINT:
            seen = &self->point;
            break;
        default:
            break;
    }

    if (seen == NULL || !Vec_Differ(seen, &data_021fbee8)) {
        return 0;
    }
    Vec3 *position = scene_look_position(object);
    fx32 distance = Vec_Distance(seen, position);
    if (self->range != 0 && scene_look_abs(distance) >= self->range) {
        return 0;
    }
    int yaw = SceneLook_Yaw(self, seen, position, scene_look_object_s16(object, SCENE_LOOK_OBJECT_ANGLE));
    if (self->in_view_only != 0 && !SceneLook_InView(self, yaw)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_0201ac28, SceneLook_CanSee)

/* func_0201acbc: a request of kind 5, to hold the angles `pitch` and `yaw`, moved by
 * `pitch_step` and `yaw_step` a frame, taken as SceneLook_Request takes one. No object or
 * point; the range (8.0), `in_view_only` and the actor (the player's) are the constructor's. */
void SceneLook_RequestAngles(SceneLook *self, int priority, u16 pitch, u16 yaw, s16 pitch_step, s16 yaw_step)
{
    if (self->locked != 0 || self->priority == SCENE_LOOK_PRIORITY_FINAL || priority < self->priority) {
        return;
    }
    self->kind = SCENE_LOOK_ANGLES;
    self->target = 0;
    self->point.x = 0;
    self->point.y = 0;
    self->point.z = 0;
    self->priority = priority;
    self->on_target = 0;
    self->range = SCENE_LOOK_RANGE;
    self->in_view_only = 1;
    self->actor = SCENE_LOOK_PLAYER_ACTOR;
    self->pitch_rest = (s16) pitch;
    self->yaw_rest = (s16) yaw;
    self->pitch_step = pitch_step;
    self->yaw_step = yaw_step;
}
CLEAN_AS(func_0201acbc, SceneLook_RequestAngles)

/* func_0201ad18: a request to look at what `kind` names (the object `target`, the point
 * `point`, field actor `actor`) within `range`, in view only with `in_view_only`; taken unless
 * the look is locked, the waiting priority is final (4) or `priority` is below it. The rest
 * angles become 0 and the steps the standard ones. */
void SceneLook_Request(SceneLook *self, u8 kind, int priority, int target, const Vec3 *point, int actor, fx32 range,
                       u8 in_view_only)
{
    if (self->locked != 0 || self->priority == SCENE_LOOK_PRIORITY_FINAL || priority < self->priority) {
        return;
    }
    self->kind = kind;
    self->target = (u32) target;
    scene_look_copy_point(&self->point, point);
    self->priority = priority;
    self->on_target = 0;
    self->range = range;
    self->in_view_only = in_view_only;
    self->actor = actor;
    self->pitch_rest = 0;
    self->yaw_rest = 0;
    self->pitch_step = SCENE_LOOK_PITCH_STEP;
    self->yaw_step = SCENE_LOOK_YAW_STEP;
}
CLEAN_AS(func_0201ad18, SceneLook_Request)

/* func_0201ad78: the point of kind 3. */
void SceneLook_SetPoint(SceneLook *self, const Vec3 *point)
{
    scene_look_copy_point(&self->point, point);
}
CLEAN_AS(func_0201ad78, SceneLook_SetPoint)

/* func_0201ad88: the pitch limit (16 bits of `limit`). */
void SceneLook_SetPitchLimit(SceneLook *self, int limit)
{
    self->pitch_limit = (s16) limit;
}
CLEAN_AS(func_0201ad88, SceneLook_SetPitchLimit)

/* func_0201ad8c: the head point onto the curved ground drawn (func_0203f7d0) into `out`, and 1;
 * 0 while the head point is the origin (not read yet). */
int SceneLook_HeadPoint(SceneLook *self, Vec3 *out)
{
    fx32 x = self->head.m[3][0];
    if (x == 0 && self->head.m[3][1] == 0 && self->head.m[3][2] == 0) {
        return 0;
    }
    out->x = x;
    out->y = self->head.m[3][1];
    out->z = self->head.m[3][2];
    Globe_Unbend(out, out);
    return 1;
}
CLEAN_AS(func_0201ad8c, SceneLook_HeadPoint)

/* func_0201adbc: the head's matrix read from joint 15 of the object's model (func_02055d0c),
 * when there is an object. */
void SceneLook_ReadHead(SceneLook *self, u8 *object)
{
    if (object != NULL) {
        ModelObject_JointMatrix((ModelObject *) (void *) (object + SCENE_LOOK_OBJECT_MODEL), &self->head,
                                SCENE_LOOK_HEAD_JOINT);
    }
}
CLEAN_AS(func_0201adbc, SceneLook_ReadHead)

/* func_0201addc: the look takes no more requests and stops aiming. */
void SceneLook_Lock(SceneLook *self)
{
    self->locked = 1;
}
CLEAN_AS(func_0201addc, SceneLook_Lock)

/* func_0201ade4: the destructor: no target object. */
void SceneLook_Destruct(SceneLook *self)
{
    self->target = 0;
}
CLEAN_AS(func_0201ade4, SceneLook_Destruct)

/* func_0201adec: the constructor: looking at the player (kind 1) at priority 0 within 8.0 and
 * in view, straight ahead, with the standard steps and limits (pitch 0x1a00, yaw 0x3000),
 * unlocked and off target. The head's matrix is left as it is. */
void SceneLook_Construct(SceneLook *self)
{
    self->kind = SCENE_LOOK_PLAYER;
    self->target = 0;
    self->point.x = 0;
    self->point.y = 0;
    self->point.z = 0;
    self->priority = 0;
    self->pitch = 0;
    self->pitch_step = SCENE_LOOK_PITCH_STEP;
    self->pitch_rest = 0;
    self->pitch_limit = SCENE_LOOK_PITCH_LIMIT;
    self->yaw = 0;
    self->yaw_step = SCENE_LOOK_YAW_STEP;
    self->yaw_rest = 0;
    self->yaw_limit = SCENE_LOOK_YAW_LIMIT;
    self->locked = 0;
    self->on_target = 0;
    self->range = SCENE_LOOK_RANGE;
    self->in_view_only = 1;
    self->actor = SCENE_LOOK_PLAYER_ACTOR;
}
CLEAN_AS(func_0201adec, SceneLook_Construct)
