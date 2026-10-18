/* How a scene object's motion runs, and its note (scene_motion_core.h). */
#include "scene_motion_core.h"

#include "clean.h"
#include "ov004/member_pointer.h"
#include "packed_bytes.h"
#include "scene_motion_request.h"

static_assert(offsetof(SceneMotion, note_kind) == 0x04, "SceneMotion layout");
static_assert(offsetof(SceneMotion, unk_18) == 0x18, "SceneMotion layout");
static_assert(offsetof(SceneMotion, kind) == 0x1c, "SceneMotion layout");
static_assert(offsetof(SceneMotion, next_kind) == 0x24, "SceneMotion layout");

/* The columns of a kind's row in data_021c1ad4. */
#define MOTION_CORE_RUN 1
#define MOTION_CORE_AFTER 2

/* The bytes of a packed point and of a 16-bit value in a note. */
#define MOTION_CORE_POINT_SIZE 5
#define MOTION_CORE_HALF_SIZE 2

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_02019af0: sets whether the motion is done. */
void SceneMotion_SetDone(SceneMotion *self, u32 done)
{
    self->done = (s32) done;
}
CLEAN_AS(func_02019af0, SceneMotion_SetDone)

/* func_02019af8: the motion asked for (`next_kind` with `next_priority`, none at priority 0)
 * starts when its priority is at least the running one's, when the running one is done or when
 * the running one yields (priority 3): its arguments are copied in (func_02019e80) and it
 * starts (func_02019d94). Then the byte 0x19's request sets or clears the byte 0x18, and the
 * request for a motion is cleared (func_02019d78). */
void SceneMotion_Update(SceneMotion *self, u8 *object)
{
    if (self->next_priority != 0 && (self->next_priority >= self->priority || SceneMotion_IsDone(self) != 0 ||
                                     self->priority == SCENE_MOTION_PRIORITY_YIELDS)) {
        SceneMotionArgs_Copy(&self->args, &self->next_args);
        SceneMotion_Start(self, object, self->next_kind, self->next_priority);
    }

    if (self->hold == SCENE_MOTION_HOLD_SET) {
        SceneMotion_Hold(self);
        self->hold = 0;
    } else if (self->hold == SCENE_MOTION_HOLD_CLEAR) {
        SceneMotion_Release(self);
        self->hold = 0;
    }

    SceneMotion_ClearRequest(self);
}
CLEAN_AS(func_02019af8, SceneMotion_Update)

/* func_02019b68: sets the motion's byte 0x18. */
void SceneMotion_Hold(SceneMotion *self)
{
    self->unk_18 = 1;
}
CLEAN_AS(func_02019b68, SceneMotion_Hold)

/* func_02019b60: clears the motion's byte 0x18. */
void SceneMotion_Release(SceneMotion *self)
{
    self->unk_18 = 0;
}
CLEAN_AS(func_02019b60, SceneMotion_Release)

/* Calls the running kind's function in `column` with the object, unless the motion has no kind
 * or the pointer is null (its function word is 0). */
static void motion_core_call(SceneMotion *self, u8 *object, int column)
{
    const MemberPointer *row = (const MemberPointer *) (uintptr_t) self->entry;
    if (row == NULL || row[column].function == 0) {
        return;
    }
    const MemberPointer *member = &row[column];
    void *target = MemberPointer_Object(member, self);
    ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, target))(target, object);
}

/* Once the motion is done, its priority falls to 0. */
static void motion_core_drop_priority(SceneMotion *self)
{
    if (SceneMotion_IsDone(self) != 0) {
        self->priority = 0;
    }
}

/* func_0201998c: each frame before the object moves: the motion asked for starts
 * (SceneMotion_Update), and the running kind runs. */
void SceneMotion_Run(SceneMotion *self, u8 *object)
{
    SceneMotion_Update(self, object);
    motion_core_call(self, object, MOTION_CORE_RUN);
    motion_core_drop_priority(self);
}
CLEAN_AS(func_0201998c, SceneMotion_Run)

/* func_02019948: each frame once the object has moved: the running kind's after-step. */
void SceneMotion_After(SceneMotion *self, u8 *object)
{
    motion_core_call(self, object, MOTION_CORE_AFTER);
    motion_core_drop_priority(self);
}
CLEAN_AS(func_02019948, SceneMotion_After)

/* ---- The note */

/* func_020199d8: kind 20's item code from a note. */
void SceneMotionNote_UnpackItem(u16 *item, const u8 *note)
{
    *item = PackedBytes_ReadItem(note);
}
CLEAN_AS(func_020199d8, SceneMotionNote_UnpackItem)

/* func_020199ec: kind 20's item code into a note. The item's address is passed on as well,
 * and not read. */
void SceneMotionNote_PackItem(SceneMotion *self, u8 *note, const u16 *item)
{
    (void) self;
    PackedBytes_WriteItem(note, *item, item);
}
CLEAN_AS(func_020199ec, SceneMotionNote_PackItem)

/* func_020199f8: kind 12's animation, mode, word and frame from a note (a byte each). */
void SceneMotionNote_UnpackAnimation(u32 *animation, u8 *mode, u16 *word, u16 *frame, const u8 *note)
{
    *animation = note[0];
    *mode = note[1];
    *word = note[2];
    *frame = note[3];
}
CLEAN_AS(func_020199f8, SceneMotionNote_UnpackAnimation)

/* func_02019a18: kind 12's animation, mode, word and frame into a note.
 * QUIRK: only the low byte of the frame is kept. */
void SceneMotionNote_PackAnimation(u8 *note, u8 animation, u8 mode, u8 word, u16 frame)
{
    note[0] = animation;
    note[1] = mode;
    note[2] = word;
    note[3] = (u8) frame;
}
CLEAN_AS(func_02019a18, SceneMotionNote_PackAnimation)

/* func_02019a2c: kind 3's rate and angle (2 bytes each) and word (a byte) from a note. */
void SceneMotionNote_UnpackTurn(s16 *rate, s16 *angle, u16 *word, const u8 *note)
{
    MI_CpuCopy8(note, rate, MOTION_CORE_HALF_SIZE);
    MI_CpuCopy8(note + MOTION_CORE_HALF_SIZE, angle, MOTION_CORE_HALF_SIZE);
    *word = note[2 * MOTION_CORE_HALF_SIZE];
}
CLEAN_AS(func_02019a2c, SceneMotionNote_UnpackTurn)

/* func_02019a58: kind 3's rate, angle and the low byte of the word into a note. */
void SceneMotionNote_PackTurn(u8 *note, u16 rate, u16 angle, char word)
{
    MI_CpuCopy8(&rate, note, MOTION_CORE_HALF_SIZE);
    MI_CpuCopy8(&angle, note + MOTION_CORE_HALF_SIZE, MOTION_CORE_HALF_SIZE);
    note[2 * MOTION_CORE_HALF_SIZE] = (u8) word;
}
CLEAN_AS(func_02019a58, SceneMotionNote_PackTurn)

/* func_02019a84: a path's start and end points, rate and word from a note (the points'
 * coordinates are 20 bits, as PackedBytes_UnpackPoint gives them). */
void SceneMotionNote_UnpackPath(u32 *from_x, u32 *from_z, u32 *to_x, u32 *to_z, s16 *rate, s16 *word, const u8 *note)
{
    PackedBytes_UnpackPoint(note, from_x, from_z);
    PackedBytes_UnpackPoint(note + MOTION_CORE_POINT_SIZE, to_x, to_z);
    MI_CpuCopy8(note + 2 * MOTION_CORE_POINT_SIZE, rate, MOTION_CORE_HALF_SIZE);
    *word = note[2 * MOTION_CORE_POINT_SIZE + MOTION_CORE_HALF_SIZE];
}
CLEAN_AS(func_02019a84, SceneMotionNote_UnpackPath)

/* func_02019ac0: a path's start and end points, rate and the low byte of the word into a
 * note. */
void SceneMotionNote_PackPath(u8 *note, s32 from_x, s32 from_z, s32 to_x, s32 to_z, s16 rate, u16 word)
{
    PackedBytes_PackPoint(note, from_x, from_z);
    PackedBytes_PackPoint(note + MOTION_CORE_POINT_SIZE, to_x, to_z);
    MI_CpuCopy8(&rate, note + 2 * MOTION_CORE_POINT_SIZE, MOTION_CORE_HALF_SIZE);
    note[2 * MOTION_CORE_POINT_SIZE + MOTION_CORE_HALF_SIZE] = (u8) word;
}
CLEAN_AS(func_02019ac0, SceneMotionNote_PackPath)
