/* Asking a scene object's motion for a kind, starting it, and constructing the motion
 * (scene_motion_request.h). */
#include "scene_motion_request.h"

#include "clean.h"
#include "ov004/member_pointer.h"
#include "scene_motion_core.h"
#include "scene_motion_kinds.h"

static_assert(offsetof(SceneMotion, next_args) == 0x2c, "SceneMotion layout");
static_assert(offsetof(SceneMotion, args) == 0x60, "SceneMotion layout");
static_assert(offsetof(SceneMotion, done) == 0x94, "SceneMotion layout");
static_assert(offsetof(SceneMotion, step) == 0x98, "SceneMotion layout");
static_assert(sizeof(SceneMotionArgs) == 0x34, "SceneMotionArgs layout");

/* The kinds asked for here. */
#define MOTION_REQUEST_KIND_STAND 0
#define MOTION_REQUEST_KIND_GESTURE 7
#define MOTION_REQUEST_KIND_ACT 8
#define MOTION_REQUEST_KIND_ANIMATION 12
#define MOTION_REQUEST_KIND_13 13
#define MOTION_REQUEST_KIND_14 14

/* The item code of no item. */
#define MOTION_REQUEST_NO_ITEM 0xfff1

/* The bytes of the note (0x04 to 0x12) cleared when a motion starts at once. */
#define MOTION_REQUEST_NOTE_SIZE 15

/* A row of data_021c1ad4: the kind's start, run and after-step. */
typedef struct SceneMotionRow {
    MemberPointer start;
    MemberPointer run;
    MemberPointer after;
} SceneMotionRow;

static_assert(sizeof(SceneMotionRow) == 0x18, "SceneMotionRow layout");

/* The motion's words from its step (0x98) that the kinds keep (scene_motion_kinds.c). */
typedef struct SceneMotionState {
    u8 step;       /* 0x98 */
    u8 unk_99;     /* 0x99 */
    u8 unk_9a[2];  /* 0x9a */
    s32 walk_mode; /* 0x9c */
    s16 half_3ac;  /* 0xa0 */
    u8 unk_a2[2];  /* 0xa2 */
    u32 act;       /* 0xa4: kind 8's record */
    u8 act_mode;   /* 0xa8 */
    u8 act_number; /* 0xa9 */
    u8 unk_aa[2];  /* 0xaa */
    s32 effect;    /* 0xac */
    s32 gesture;   /* 0xb0: kind 7's */
} SceneMotionState;

#define MOTION_REQUEST_STATE 0x98
static_assert(offsetof(SceneMotionState, walk_mode) == 0x9c - MOTION_REQUEST_STATE, "SceneMotionState layout");
static_assert(offsetof(SceneMotionState, act_number) == 0xa9 - MOTION_REQUEST_STATE, "SceneMotionState layout");
static_assert(offsetof(SceneMotionState, gesture) == 0xb0 - MOTION_REQUEST_STATE, "SceneMotionState layout");

/* The kinds' rows, and the standard word. */
extern SceneMotionRow data_021c1ad4[];
extern u16 data_020c80f8;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static SceneMotionPlan *motion_request_plan(SceneMotionArgs *args)
{
    return (SceneMotionPlan *) (void *) args;
}

static SceneMotionState *motion_request_state(SceneMotion *self)
{
    return (SceneMotionState *) (void *) ((u8 *) self + MOTION_REQUEST_STATE);
}

/* Whether a request of `priority` is taken: at least the waiting request's priority, or the
 * waiting one gives way. */
static int motion_request_taken(const SceneMotion *self, int priority)
{
    return priority >= self->next_priority || self->next_priority == SCENE_MOTION_PRIORITY_YIELDS;
}

/* func_02019b70: asks for the motion's byte 0x18 to be cleared on the next update. */
void SceneMotion_AskRelease(SceneMotion *self)
{
    self->hold = SCENE_MOTION_HOLD_CLEAR;
}
CLEAN_AS(func_02019b70, SceneMotion_AskRelease)

/* func_02019b78: asks for the motion's byte 0x18 to be set on the next update. */
void SceneMotion_AskHold(SceneMotion *self)
{
    self->hold = SCENE_MOTION_HOLD_SET;
}
CLEAN_AS(func_02019b78, SceneMotion_AskHold)

/* Kinds 13 and 14's request: the item `*item`, the values a, b and `variant`, the partner. */
static int motion_request_exchange(SceneMotion *self, int kind, int priority, const u16 *item, int a, u8 b, int variant,
                                   int partner)
{
    if (!motion_request_taken(self, priority)) {
        return 0;
    }
    SceneMotionPlan *plan = motion_request_plan(&self->next_args);
    SceneMotion_SetNext(self, kind, priority);
    SceneMotionArgs_Clear(&self->next_args);
    plan->item = *item;
    plan->unk_24 = (u32) a;
    plan->unk_2c = b;
    plan->variant = variant;
    plan->partner = (u32) partner;
    return 1;
}

/* func_02019b80: asks for kind 14 (motion_request_exchange). Whether it was taken. */
int SceneMotion_RequestKind14(SceneMotion *self, int priority, u16 *item, int a, u8 b, int variant, int partner)
{
    return motion_request_exchange(self, MOTION_REQUEST_KIND_14, priority, item, a, b, variant, partner);
}
CLEAN_AS(func_02019b80, SceneMotion_RequestKind14)

/* func_02019bd0: asks for kind 13 (motion_request_exchange). Whether it was taken. */
int SceneMotion_RequestKind13(SceneMotion *self, int priority, u16 *item, int a, u8 b, int variant, int partner)
{
    return motion_request_exchange(self, MOTION_REQUEST_KIND_13, priority, item, a, b, variant, partner);
}
CLEAN_AS(func_02019bd0, SceneMotion_RequestKind13)

/* func_02019c20: asks for kind 12, `animation` played in `mode` with `word` from `frame`.
 * Whether it was taken. */
int SceneMotion_RequestAnimation(SceneMotion *self, int priority, int animation, char mode, u16 word, u16 frame)
{
    if (!motion_request_taken(self, priority)) {
        return 0;
    }
    SceneMotionPlan *plan = motion_request_plan(&self->next_args);
    SceneMotion_SetNext(self, MOTION_REQUEST_KIND_ANIMATION, priority);
    SceneMotionArgs_Clear(&self->next_args);
    plan->animation = (u32) animation;
    plan->mode = (u8) mode;
    plan->word = word;
    plan->frame = frame;
    return 1;
}
CLEAN_AS(func_02019c20, SceneMotion_RequestAnimation)

/* func_02019c6c: asks for kind 0 (stand) with `word`. Whether it was taken. */
int SceneMotion_RequestStand(SceneMotion *self, int priority, int word)
{
    return SceneMotion_Request(self, MOTION_REQUEST_KIND_STAND, priority, 0, 0, 0, 0, 0, 0, (u16) word, 0);
}
CLEAN_AS(func_02019c6c, SceneMotion_RequestStand)

/* func_02019c90: asks for kind 8 with `word`, then sets its act to `act`. Whether it was taken. */
int SceneMotion_RequestAct(SceneMotion *self, int priority, int act, int word)
{
    if (!SceneMotion_Request(self, MOTION_REQUEST_KIND_ACT, priority, 0, 0, 0, 0, 0, 0, (u16) word, 0)) {
        return 0;
    }
    motion_request_plan(&self->next_args)->act = (u8) act;
    return 1;
}
CLEAN_AS(func_02019c90, SceneMotion_RequestAct)

/* func_02019cc8: asks for kind 7 with the rate, the angle (16 bits each) and `word`, then sets
 * its gesture. Whether it was taken. */
int SceneMotion_RequestGesture(SceneMotion *self, int priority, int rate, int angle, int gesture, u16 word)
{
    if (!SceneMotion_Request(self, MOTION_REQUEST_KIND_GESTURE, priority, 0, 0, (s16) rate, (s16) angle, 0, 0, word, 0)) {
        return 0;
    }
    motion_request_plan(&self->next_args)->gesture = gesture;
    return 1;
}
CLEAN_AS(func_02019cc8, SceneMotion_RequestGesture)

/* func_02019d0c: asks for `kind` with a path from (from_x, from_z) to (to_x, to_z) (both 0:
 * the start point), the rate, the angle, the word and the frame. Kind 12 is never taken here
 * (SceneMotion_RequestAnimation asks for it). Whether it was taken. */
int SceneMotion_Request(SceneMotion *self, int kind, int priority, int from_x, int from_z, s16 rate, s16 angle, int to_x,
                        int to_z, u16 word, u16 frame)
{
    if (!motion_request_taken(self, priority) || kind == MOTION_REQUEST_KIND_ANIMATION) {
        return 0;
    }
    SceneMotionPlan *plan = motion_request_plan(&self->next_args);
    SceneMotion_SetNext(self, kind, priority);
    SceneMotionArgs_Clear(&self->next_args);
    plan->from_x = from_x;
    plan->from_z = from_z;
    if (to_x == 0 && to_z == 0) {
        plan->to_x = from_x;
        plan->to_z = from_z;
    } else {
        plan->to_x = to_x;
        plan->to_z = to_z;
    }
    plan->angle = angle;
    plan->rate = rate;
    plan->word = word;
    plan->frame = frame;
    return 1;
}
CLEAN_AS(func_02019d0c, SceneMotion_Request)

/* func_02019d70: the kind and priority asked for. */
void SceneMotion_SetNext(SceneMotion *self, int kind, int priority)
{
    self->next_kind = kind;
    self->next_priority = priority;
}
CLEAN_AS(func_02019d70, SceneMotion_SetNext)

/* func_02019d78: no kind is asked for any more (SCENE_MOTION_KIND_NONE at priority 0), and the
 * arguments asked with are cleared. */
void SceneMotion_ClearRequest(SceneMotion *self)
{
    SceneMotion_SetNext(self, SCENE_MOTION_KIND_NONE, 0);
    SceneMotionArgs_Clear(&self->next_args);
}
CLEAN_AS(func_02019d78, SceneMotion_ClearRequest)

/* func_02019d94: `kind` starts (0 for a kind outside 0 to 21) at `priority`: `entry` points at
 * its row of data_021c1ad4, the step is 0, and the row's start is called with the object.
 * REQUIRES: the row's start is not a null member pointer (every kind's row has one; the ROM
 * would call address 0). */
void SceneMotion_Start(SceneMotion *self, u8 *object, int kind, int priority)
{
    self->kind = kind;
    if (kind < 0 || kind >= SCENE_MOTION_KINDS) {
        self->kind = 0;
    }
    self->priority = priority;
    self->entry = (u32) (uintptr_t) &data_021c1ad4[self->kind];
    self->step = 0;

    const SceneMotionRow *row = (const SceneMotionRow *) (uintptr_t) self->entry;
    void *target = MemberPointer_Object(&row->start, self);
    ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(&row->start, target))(target, object);
}
CLEAN_AS(func_02019d94, SceneMotion_Start)

/* func_02019de4: the arguments of the running kind. */
SceneMotionArgs *SceneMotion_Args(SceneMotion *self)
{
    return &self->args;
}
CLEAN_AS(func_02019de4, SceneMotion_Args)

/* func_02019de8: whether the motion is done (`done` is exactly 1). */
int SceneMotion_IsDone(SceneMotion *self)
{
    return self->done == 1;
}
CLEAN_AS(func_02019de8, SceneMotion_IsDone)

/* func_02019df8: the act number the motion shows (its byte 0xa9). */
u8 SceneMotion_ActNumber(SceneMotion *self)
{
    return motion_request_state(self)->act_number;
}
CLEAN_AS(func_02019df8, SceneMotion_ActNumber)

/* func_02019e00: the running kind. */
int SceneMotion_Kind(SceneMotion *self)
{
    return self->kind;
}
CLEAN_AS(func_02019e00, SceneMotion_Kind)

/* func_02019e04: `kind` at `priority` starts at once, with a path from (from_x, from_z) to
 * (to_x, to_z) (both 0: the start point), `angle` and the standard word: the request is made
 * whatever waits, its arguments become the running ones, the note and the bytes 0x18 and 0x19
 * are cleared, and the kind starts (SceneMotion_Start). */
void SceneMotion_StartNow(SceneMotion *self, u8 *object, int kind, int priority, u32 from_x, u32 from_z, s16 angle, u32 to_x,
                          u32 to_z)
{
    SceneMotionPlan *plan = motion_request_plan(&self->next_args);
    SceneMotion_SetNext(self, kind, priority);
    SceneMotionArgs_Clear(&self->next_args);
    plan->from_x = (s32) from_x;
    plan->from_z = (s32) from_z;
    if (to_x == 0 && to_z == 0) {
        plan->to_x = (s32) from_x;
        plan->to_z = (s32) from_z;
    } else {
        plan->to_x = (s32) to_x;
        plan->to_z = (s32) to_z;
    }
    plan->angle = angle;
    plan->word = data_020c80f8;

    SceneMotionArgs_Copy(&self->args, &self->next_args);
    MI_CpuFill8(&self->note_kind, 0, MOTION_REQUEST_NOTE_SIZE);
    self->unk_18 = 0;
    self->hold = 0;
    SceneMotion_Start(self, object, self->next_kind, self->next_priority);
}
CLEAN_AS(func_02019e04, SceneMotion_StartNow)

/* func_02019e80: `src`'s arguments copied to `dst` (MI_CpuCopy8).
 * QUIRK: the partner word (0x28) is copied a second time after the whole block. */
void SceneMotionArgs_Copy(SceneMotionArgs *dst, SceneMotionArgs *src)
{
    MI_CpuCopy8(src, dst, sizeof(SceneMotionArgs));
    dst->partner = src->partner;
}
CLEAN_AS(func_02019e80, SceneMotionArgs_Copy)

/* func_02019ea0: the arguments cleared (MI_CpuFill8). */
void SceneMotionArgs_Clear(SceneMotionArgs *args)
{
    MI_CpuFill8(args, 0, sizeof(SceneMotionArgs));
}
CLEAN_AS(func_02019ea0, SceneMotionArgs_Clear)

/* func_02019eac: the motion's destructor, which does nothing. */
void SceneMotion_Destruct(SceneMotion *self)
{
    (void) self;
}
CLEAN_AS(func_02019eac, SceneMotion_Destruct)

/* func_02019eb0: the motion's constructor: no item in either set of arguments, no kind running
 * (SCENE_MOTION_KIND_NONE, no row, priority 0), none asked for (SceneMotion_ClearRequest), done,
 * and the kinds' words at their rest (act mode 1, gesture 5, no effect). Returns the motion.
 * QUIRK: the item written into `next_args` is wiped at once by SceneMotion_ClearRequest. */
SceneMotion *SceneMotion_Construct(SceneMotion *self)
{
    SceneMotionState *state = motion_request_state(self);
    self->next_args.item = MOTION_REQUEST_NO_ITEM;
    self->args.item = MOTION_REQUEST_NO_ITEM;
    self->kind = SCENE_MOTION_KIND_NONE;
    self->entry = 0;
    self->priority = 0;
    SceneMotion_ClearRequest(self);
    SceneMotion_SetDone(self, 1);
    state->unk_99 = 0;
    state->walk_mode = 0;
    state->half_3ac = 0;
    state->act = 0;
    state->act_mode = 1;
    state->act_number = 0;
    state->gesture = 5;
    state->effect = -1;
    return self;
}
CLEAN_AS(func_02019eb0, SceneMotion_Construct)
