/* How a scene object walks and turns (scene_mover.h). */
#include "scene_mover.h"

#include "actor.h"
#include "autoload_2/approach.h"
#include "clean.h"
#include "speaker_anim.h"

static_assert(offsetof(SceneMover, paces) == 0x0c, "SceneMover layout");
static_assert(offsetof(SceneMover, mode) == 0x30, "SceneMover layout");
static_assert(offsetof(SceneMover, angle) == 0x34, "SceneMover layout");
static_assert(offsetof(SceneMover, start) == 0x38, "SceneMover layout");
static_assert(offsetof(SceneMover, end) == 0x44, "SceneMover layout");
static_assert(offsetof(SceneMover, reach) == 0x50, "SceneMover layout");
static_assert(offsetof(SceneMover, turn_way) == 0x55, "SceneMover layout");
static_assert(sizeof(SceneMover) == 0x58, "SceneMover layout");

/* The object's parts used here. */
#define SCENE_MOVER_OBJECT_POSITION 0x5c   /* Vec3 */
#define SCENE_MOVER_OBJECT_ANGLE 0x8e      /* s16: where it faces */
#define SCENE_MOVER_OBJECT_WALK_ANGLE 0x94 /* s16: where it walks */
#define SCENE_MOVER_OBJECT_SPEED 0x98      /* fx32 */
#define SCENE_MOVER_OBJECT_STANDARD 0x2a0
#define SCENE_MOVER_OBJECT_ANIM 0x334 /* SpeakerAnim */
#define SCENE_MOVER_OBJECT_CARRIER 0x4cc

#define SCENE_MOVER_ANIM_SPEED 0x1000 /* 1.0 */

/* A mode's record. */
typedef struct SceneMoverMode {
    s32 animation; /* the body animation (SpeakerAnim_Play's number) */
    s16 turn_rate;
    u8 unk_06[2];
    s32 pace;
    fx32 reach;
    u8 continues;
    u8 unk_11[3];
} SceneMoverMode;

static_assert(sizeof(SceneMoverMode) == 0x14, "SceneMoverMode layout");

extern const SceneMoverMode data_020c822c[SCENE_MOVER_MODES];

/* `src` copied into `dst` a word at a time, each read just before it is written, as the game
 * does: with the two overlapping, a word written may be read again. */
static void scene_mover_copy_point(Vec3 *dst, const Vec3 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

static Vec3 *scene_mover_position(u8 *object)
{
    return (Vec3 *) (void *) (object + SCENE_MOVER_OBJECT_POSITION);
}

static s16 *scene_mover_object_s16(u8 *object, u32 offset)
{
    return (s16 *) (void *) (object + offset);
}

/* `value`'s magnitude as 16 bits: -0x8000 stays -0x8000. */
static s16 scene_mover_abs16(s16 value)
{
    return value < 0 ? (s16) -value : value;
}

/* func_0201af1c: the way of turning. */
void SceneMover_SetTurnWay(SceneMover *self, u8 way)
{
    self->turn_way = way;
}
CLEAN_AS(func_0201af1c, SceneMover_SetTurnWay)

/* func_0201af24: the mode's pace (at the start of the mover). */
ScenePace *SceneMover_Pace(SceneMover *self)
{
    return &self->pace;
}
CLEAN_AS(func_0201af24, SceneMover_Pace)

/* func_0201af28: pace 1 or 2 set; any other index is left alone. */
void SceneMover_SetPace(SceneMover *self, int index, fx32 speed, fx32 speed_up, fx32 slow_down)
{
    if (index < 1 || index >= SCENE_MOVER_PACES) {
        return;
    }
    ScenePace *pace = &self->paces[index];
    pace->speed = speed;
    pace->speed_up = speed_up;
    pace->slow_down = slow_down;
}
CLEAN_AS(func_0201af28, SceneMover_SetPace)

/* func_0201af48: the end point becomes the start point. */
void SceneMover_EndAtStart(SceneMover *self)
{
    scene_mover_copy_point(&self->end, &self->start);
}
CLEAN_AS(func_0201af48, SceneMover_EndAtStart)

/* func_0201afc0: whether the start and end points differ (Vec_Differ). */
int SceneMover_PointsDiffer(SceneMover *self)
{
    return Vec_Differ(&self->start, &self->end);
}
CLEAN_AS(func_0201afc0, SceneMover_PointsDiffer)

/* func_0201afd0: the end point (as SceneMover_EndPoint). */
Vec3 *SceneMover_End(SceneMover *self)
{
    return &self->end;
}
CLEAN_AS(func_0201afd0, SceneMover_End)

/* func_0201afd4: the end point. */
void SceneMover_SetEnd(SceneMover *self, const Vec3 *point)
{
    scene_mover_copy_point(&self->end, point);
}
CLEAN_AS(func_0201afd4, SceneMover_SetEnd)

/* func_0201afe4: the turning rate. */
s16 SceneMover_TurnRate(SceneMover *self)
{
    return self->turn_rate;
}
CLEAN_AS(func_0201afe4, SceneMover_TurnRate)

/* func_0201afec: the angle to walk at. */
s16 SceneMover_Angle(SceneMover *self)
{
    return self->angle;
}
CLEAN_AS(func_0201afec, SceneMover_Angle)

/* func_0201aff4: the angle to walk at (16 bits of `angle`). */
void SceneMover_SetAngle(SceneMover *self, int angle)
{
    self->angle = (s16) angle;
}
CLEAN_AS(func_0201aff4, SceneMover_SetAngle)

/* func_0201aff8: whether the object, at the height 0, is nearer than the reach to the start
 * point (`at_start`) or the end point (Vec_Distance). */
int SceneMover_Reached(SceneMover *self, u8 *object, int at_start)
{
    Vec3 at = *scene_mover_position(object);
    at.y = 0;
    fx32 distance = Vec_Distance(&at, at_start ? &self->start : &self->end);
    return distance < self->reach;
}
CLEAN_AS(func_0201aff8, SceneMover_Reached)

/* func_0201b040: the end point (as SceneMover_End). */
Vec3 *SceneMover_EndPoint(SceneMover *self)
{
    return &self->end;
}
CLEAN_AS(func_0201b040, SceneMover_EndPoint)

/* func_0201b044: the start point; while the two points were the same the end point moves
 * with it (SceneMover_SetEnd first). */
void SceneMover_SetStart(SceneMover *self, const Vec3 *point)
{
    if (Vec_Equal(&self->start, &self->end)) {
        SceneMover_SetEnd(self, point);
    }
    scene_mover_copy_point(&self->start, point);
}
CLEAN_AS(func_0201b044, SceneMover_SetStart)

/* func_0201b078: each frame, the object's walking angle (0x94) turns towards the mover's
 * angle by the turning rate, the way set (SceneMover_Turn), and the object faces it (0x8e). In
 * mode 4 the walking angle is set at once and the facing is left alone. */
void SceneMover_Steer(SceneMover *self, u8 *object)
{
    s16 *walk_angle = scene_mover_object_s16(object, SCENE_MOVER_OBJECT_WALK_ANGLE);
    if (SceneMover_Mode(self) == SCENE_MOVER_TURN_FIRST) {
        *walk_angle = self->angle;
    } else {
        SceneMover_Turn(self, walk_angle, self->angle, self->turn_rate, self->turn_way);
        *scene_mover_object_s16(object, SCENE_MOVER_OBJECT_ANGLE) = *walk_angle;
    }
}
CLEAN_AS(func_0201b078, SceneMover_Steer)

/* func_0201b0bc: `angle` turned a step towards `target`; whether it is there. With a step of
 * 0 nothing turns. The step's sign turns it up, or down while it is past the target (by its
 * 16-bit difference): way 0 always so, ways 1 and 2 only within a step of the target
 * (Math_AbsDiff16), turning up (1) or down (2) by the step's size further away. It lands on the
 * target once that is within the step just taken, on the side the step went towards (or on
 * it).
 * QUIRK: the sizes are 16-bit, so a step of -0x8000 has a size of -0x8000. */
int SceneMover_Turn(SceneMover *self, s16 *angle, s16 target, s16 step, u8 way)
{
    (void) self;
    if (step == 0) {
        return *angle == target;
    }

    s16 size = scene_mover_abs16(step);
    s16 delta = step;
    switch (way) {
        case SCENE_MOVER_TURN_UP:
        case SCENE_MOVER_TURN_DOWN:
            if (Math_AbsDiff16(target, *angle) <= size) {
                if ((s16) (*angle - target) > 0) {
                    delta = (s16) -step;
                }
            } else if (way == SCENE_MOVER_TURN_UP) {
                delta = size;
            } else {
                delta = (s16) -size;
            }
            break;
        default:
            if ((s16) (*angle - target) > 0) {
                delta = (s16) -step;
            }
            break;
    }

    *angle = (s16) (*angle + delta);
    s16 left = (s16) (*angle - target);
    if (scene_mover_abs16(left) <= scene_mover_abs16(delta) && left * delta >= 0) {
        *angle = target;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0201b0bc, SceneMover_Turn)

/* func_0201b188: the mover's angle set to the end point's from the object (Vec_YawTo). */
void SceneMover_AimAtEnd(SceneMover *self, u8 *object)
{
    self->angle = Vec_YawTo(scene_mover_position(object), &self->end);
}
CLEAN_AS(func_0201b188, SceneMover_AimAtEnd)

/* func_0201b1a0: the mode. */
int SceneMover_Mode(SceneMover *self)
{
    return self->mode;
}
CLEAN_AS(func_0201b1a0, SceneMover_Mode)

/* func_0201b1a4: mode `mode` (0 for one outside 0 to 4) from its record: its pace, its turning
 * rate unless `turn_rate` is nonzero, its reach; outside mode 4 its body animation plays with
 * `word`, going on from the frame of the one playing (SpeakerAnim_PlayFromBodyFrame) when both
 * the old and the new mode continue or the object's body already plays it
 * (SpeakerAnim_IsBody), else from its start (SpeakerAnim_Play). */
void SceneMover_SetMode(SceneMover *self, u8 *object, int mode, int turn_rate, u16 word)
{
    if (mode < 0 || mode >= SCENE_MOVER_MODES) {
        mode = SCENE_MOVER_STAND;
    }
    const SceneMoverMode *record = &data_020c822c[mode];

    const ScenePace *pace = &self->paces[record->pace];
    self->pace.speed = pace->speed;
    self->pace.speed_up = pace->speed_up;
    self->pace.slow_down = pace->slow_down;
    self->turn_rate = turn_rate == 0 ? record->turn_rate : (s16) turn_rate;
    self->reach = record->reach;

    if (mode != SCENE_MOVER_TURN_FIRST) {
        SpeakerAnim *anim = (SpeakerAnim *) (void *) (object + SCENE_MOVER_OBJECT_ANIM);
        if ((self->continues == 1 && record->continues == 1) ||
            SpeakerAnim_IsBody(anim, record->animation, object + SCENE_MOVER_OBJECT_STANDARD)) {
            SpeakerAnim_PlayFromBodyFrame(anim, object, record->animation, word, 0);
        } else {
            SpeakerAnim_Play(anim, object, record->animation, word, 0, SCENE_MOVER_ANIM_SPEED, 0, 0);
        }
    }

    self->mode = mode;
    self->continues = record->continues;
}
CLEAN_AS(func_0201b1a4, SceneMover_SetMode)

/* func_0201b268: each frame, the object's speed (0x98) goes to the pace's (Approach_S32), at
 * once to 0 when the pace stands; while the object walks straight at the end point
 * (Vec_YawTo equals its walking angle) the speed is cut to the distance left in the ground
 * plane (Vec_DistanceXZ). Then the object moves (Actor_Move, with its carrier at 0x4cc).
 * QUIRK: the step is chosen by comparing the speeding-up step with the pace's speed, not the
 * object's speed with it: with the paces the main program sets it is always the speeding-up
 * step, slowing down included. */
void SceneMover_Drive(SceneMover *self, u8 *object)
{
    int *speed = (int *) (void *) (object + SCENE_MOVER_OBJECT_SPEED);

    if (self->pace.speed == 0) {
        *speed = 0;
    } else {
        int step = self->pace.speed_up < self->pace.speed ? self->pace.speed_up : self->pace.slow_down;
        Approach_S32(speed, self->pace.speed, step);
        if (Vec_YawTo(scene_mover_position(object), &self->end) ==
            *scene_mover_object_s16(object, SCENE_MOVER_OBJECT_WALK_ANGLE)) {
            fx32 left = Vec_DistanceXZ(&self->end, scene_mover_position(object));
            if (left < *speed) {
                *speed = left;
            }
        }
    }
    Actor_Move((Actor *) (void *) object, (const ActorCarrier *) (const void *) (object + SCENE_MOVER_OBJECT_CARRIER));
}
CLEAN_AS(func_0201b268, SceneMover_Drive)

/* ---- Each frame, construction and reset */

/* The paces 0 to 2 a mover starts with (paces 1 and 2 walk at 0.0625 and 0.1). */
extern const ScenePace data_020c81d8[SCENE_MOVER_PACES];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The pace a new mover has (1.0, reached at once), and its mode: none of the five yet. */
#define SCENE_MOVER_NEW_SPEED 0x1000
#define SCENE_MOVER_NO_MODE SCENE_MOVER_MODES

/* The fields SceneMover_Reset and SceneMover_Construct share: `reach` is left as it is. */
static void scene_mover_clear(SceneMover *self)
{
    self->pace.speed = SCENE_MOVER_NEW_SPEED;
    self->pace.speed_up = 0;
    self->pace.slow_down = 0;
    self->mode = SCENE_MOVER_NO_MODE;
    self->start.x = 0;
    self->start.y = 0;
    self->start.z = 0;
    self->end.x = 0;
    self->end.y = 0;
    self->end.z = 0;
    self->continues = 0;
    self->turn_way = SCENE_MOVER_TURN_SHORTER;
}

/* func_0201b2d8: the object's frame (func_0201b910) moves it first of all (SceneMover_Drive). */
void SceneMover_Update(SceneMover *self, u8 *object)
{
    SceneMover_Drive(self, object);
}
CLEAN_AS(func_0201b2d8, SceneMover_Update)

/* func_0201b2e0: as SceneMover_Construct, and the three paces from data_020c81d8 (the object's
 * set-up, func_0201bdb4). */
void SceneMover_Reset(SceneMover *self)
{
    scene_mover_clear(self);
    MI_CpuCopy8(data_020c81d8, self->paces, sizeof(self->paces));
}
CLEAN_AS(func_0201b2e0, SceneMover_Reset)

/* func_0201b320: the destructor; nothing to do. */
void SceneMover_Destruct(SceneMover *self)
{
    (void) self;
}
CLEAN_AS(func_0201b320, SceneMover_Destruct)

/* func_0201b324: the constructor: pace 1.0, no mode, both points at the origin, turning by the
 * shorter side. The paces and `reach` are not set. Returns the mover. */
SceneMover *SceneMover_Construct(SceneMover *self)
{
    scene_mover_clear(self);
    return self;
}
CLEAN_AS(func_0201b324, SceneMover_Construct)
