/* A scene object's face (scene_face.h). */
#include "scene_face.h"

#include "clean.h"
#include "resource_pools.h"

static_assert(sizeof(SceneFaceAnim) == 0x2c, "SceneFaceAnim layout");
static_assert(offsetof(SceneFace, anim_a) == 0x1c, "SceneFace layout");
static_assert(offsetof(SceneFace, anim_b) == 0x48, "SceneFace layout");
static_assert(offsetof(SceneFace, anim_a_number) == 0x74, "SceneFace layout");
static_assert(offsetof(SceneFace, talk_variant) == 0x80, "SceneFace layout");
static_assert(offsetof(SceneFace, ready) == 0x84, "SceneFace layout");

/* The object's talking state. */
#define SCENE_FACE_OBJECT_TALK 0x418
/* The talking styles with a talking animation (0 and 1); from this one on there is none. */
#define SCENE_FACE_TALK_STYLES 2
/* A style that sets the second animation even while it talks (SceneFace_Play). */
#define SCENE_FACE_STYLE_NOW 2

/* The variant that starts at frame 5, and that frame. */
#define SCENE_FACE_VARIANT_LATE 1
#define SCENE_FACE_LATE_FRAME 5
/* The variant the constructor leaves. */
#define SCENE_FACE_VARIANT_UNSET 2

/* The model's vtable slot giving the face's texture file, and its G3D model. */
#define SCENE_FACE_MODEL_SLOT_TEXTURE 0x6c
#define SCENE_FACE_MODEL_G3D 0x148

#define SCENE_FACE_SPEED 0x1000 /* 1.0 in 20.12 */

/* The talking animations by style, and the name of the second animation's entry that is mapped
 * (SceneFace_MapNamed). */
extern const u32 data_020c8170[];
extern const u8 data_020d8d18[];

/* The timer at the face's start. */
extern int func_020645e0(void *timer);
extern void func_020645bc(void *timer);
extern void func_020645d4(void *timer);
extern void func_02064638(void *timer);
extern void func_0206463c(void *timer);
extern int func_020644cc(int range); /* a random number below `range` */

/* The links, and what they give. */
extern void *func_02082da8(void *link);         /* the animation set */
extern ResourceSlot *func_02082e1c(void *link); /* the block slot, or null */
extern void *func_02082d34(void *link);         /* the part */
extern int func_0208308c(void *link);           /* gives the link a number in its pool */
extern void func_02083068(void *link);
extern void *func_02082d78(void *link);
extern void *func_02082d90(void *link);
extern void *func_02082dec(void *link);
extern void *func_02082e04(void *link);
extern void *func_02082e60(void *link);
extern void *func_02082e78(void *link);

/* The animation set and the face's animations. */
extern int func_0205cf28(int animation);
extern int func_0205cf1c(int animation);
extern void func_0205d7b8(void *set, int number, int a, int b);
extern int func_0205d8a0(void *set);
extern int func_0205d894(void *set);
extern u8 *NNS_G3dGetAnmByIdx(int resource, int index);
extern void *func_0205db38(void *part);
extern int func_0205685c(void *anim, int model, int texture, int a, void *heap);
extern void func_0205678c(void *anim, int resource, int frame, int a, int flags, fx32 speed);
extern void func_02056730(void *anim);
extern void func_02056778(void *anim);
extern void func_0205682c(void *anim);
extern void *func_02056910(void *anim);
extern void *func_02056928(void *anim);
extern void func_02056610(void *anim, const void *name);
extern void func_02056658(void *anim, const void *name);
extern int func_020566a0(void *anim, const void *name, void *target);

/* Whether the object talks (byte 0 of its talking state is 1). */
extern int func_0201a7bc(const void *talk);

/* The whole frames of a 20.12 frame position (bits 12 to 27). */
static int scene_face_whole(fx32 frame)
{
    return (int) (((u32) frame << 4) >> 16);
}

/* func_02019f1c: the face's frame, once it is ready. The first animation runs a step, except
 * number 0 at its first frame until the timer lets it go on. While the object talks in style 0
 * or 1, its talking animation plays (SceneFace_StartTalk then a new cycle) when another one
 * plays, else a new cycle starts when one ends; while it does not talk, the talking animation
 * stops at the end of its cycle; in another style it stops at once (SceneFace_EndTalk). Then
 * the second animation runs a step. */
void SceneFace_Step(SceneFace *self, u8 *object)
{
    if (!SceneFace_IsReady(self)) {
        return;
    }

    if (self->anim_a_number != 0 || !FrameCtrl_Passed(&self->anim_a.ctrl, 0) || func_020645e0(self->timer) != 0) {
        func_02056778(&self->anim_a);
    }

    int *talk = (int *) (void *) (object + SCENE_FACE_OBJECT_TALK);
    if (SceneTalkState_Style(talk) < SCENE_FACE_TALK_STYLES) {
        if (func_0201a7bc(talk) != 0) {
            if (!SceneFace_IsTalkAnim(self, self->anim_b_number)) {
                SceneFace_StartTalk(self, SceneTalkState_Style(talk));
                SceneFace_StartTalkCycle(self);
            } else if (SceneFace_TalkCycleDone(self)) {
                SceneFace_StartTalkCycle(self);
            }
        } else if (SceneFace_IsTalkAnim(self, self->anim_b_number) && SceneFace_TalkCycleDone(self)) {
            SceneFace_EndTalk(self);
        }
    } else if (SceneFace_IsTalkAnim(self, self->anim_b_number)) {
        SceneFace_EndTalk(self);
    }

    func_02056778(&self->anim_b);
}
CLEAN_AS(func_02019f1c, SceneFace_Step)

/* func_02019ff0: both animations are let go (func_0205682c), then the texture's, the set's
 * and the part's links (func_02083068). */
void SceneFace_Release(SceneFace *self)
{
    func_0205682c(&self->anim_a);
    func_0205682c(&self->anim_b);
    func_02083068(self->texture_link);
    func_02083068(self->set_link);
    func_02083068(self->part_link);
}
CLEAN_AS(func_02019ff0, SceneFace_Release)

/* func_0201a020: the timer starts over (func_020645bc). */
void SceneFace_ResetTimer(SceneFace *self)
{
    func_020645bc(self->timer);
}
CLEAN_AS(func_0201a020, SceneFace_ResetTimer)

/* func_0201a028: the second animation's entry named by data_020d8d18 is turned off
 * (func_02056610). */
void SceneFace_DisableNamed(SceneFace *self)
{
    func_02056610(&self->anim_b, data_020d8d18);
}
CLEAN_AS(func_0201a028, SceneFace_DisableNamed)

/* func_0201a038: the second animation's entry named by data_020d8d18 is mapped to `target`
 * (SceneFace_MapEntry). */
void SceneFace_MapNamed(SceneFace *self, void *target)
{
    SceneFace_MapEntry(self, &self->anim_b, data_020d8d18, target);
}
CLEAN_AS(func_0201a038, SceneFace_MapNamed)

/* func_0201a054: once the face is ready, the entry `name` of `anim` is turned on
 * (func_02056658) and mapped to `target` (func_020566a0); when that fails it is turned off
 * again (func_02056610). Whether it was mapped. */
int SceneFace_MapEntry(SceneFace *self, void *anim, const void *name, void *target)
{
    if (SceneFace_IsReady(self)) {
        func_02056658(anim, name);
        if (func_020566a0(anim, name, target)) {
            return 1;
        }
        func_02056610(anim, name);
    }
    return 0;
}
CLEAN_AS(func_0201a054, SceneFace_MapEntry)

/* func_0201a090: once the face is ready, its animations follow the body's `animation`
 * (func_0205cf28 and func_0205cf1c; none gives the defaults) through SceneFace_Play. */
void SceneFace_MatchBody(SceneFace *self, int animation, int flags, int style)
{
    if (!SceneFace_IsReady(self)) {
        return;
    }
    int number_a = func_0205cf28(animation);
    int number_b = func_0205cf1c(animation);
    if (number_a == SCENE_FACE_ANIM_NONE) {
        number_a = SCENE_FACE_ANIM_A_DEFAULT;
    }
    if (number_b == SCENE_FACE_ANIM_NONE) {
        number_b = SCENE_FACE_ANIM_B_DEFAULT;
    }
    SceneFace_Play(self, number_a, number_b, flags, style);
}
CLEAN_AS(func_0201a090, SceneFace_MatchBody)

/* func_0201a0dc: once the face is ready, the first animation becomes `number_a`, started from
 * frame 0 with `flags` and run a step, unless it is 0 and 0 already plays; the second becomes
 * `number_b` (SceneFace_PlayB), or, while a talking animation plays and `style` is not 2, is
 * kept for when the talking stops.
 * QUIRK: the set's first animation is looked up (NNS_G3dGetAnmByIdx) and not used. A nonzero
 * first animation starts again even when it already plays. */
void SceneFace_Play(SceneFace *self, int number_a, int number_b, int flags, int style)
{
    if (!SceneFace_IsReady(self)) {
        return;
    }

    void *set = func_02082da8(self->set_link);
    if (number_a != 0 || self->anim_a_number != 0) {
        func_0205d7b8(set, number_a, 1, 0);
        NNS_G3dGetAnmByIdx(func_0205d8a0(set), 0);
        func_0205678c(&self->anim_a, func_0205d8a0(set), 0, 0, flags, SCENE_FACE_SPEED);
        self->anim_a_number = number_a;
        self->anim_a.ctrl.frame = 0;
        func_02056730(&self->anim_a);
    }

    if (style == SCENE_FACE_STYLE_NOW || !SceneFace_IsTalkAnim(self, self->anim_b_number)) {
        SceneFace_PlayB(self, number_b, 0);
    } else {
        self->anim_b_after_talk = number_b;
    }
}
CLEAN_AS(func_0201a0dc, SceneFace_Play)

/* func_0201a174: the talking stops: the animation kept for it plays (the default when none
 * was kept, which is written there first), and none is kept any more. */
void SceneFace_EndTalk(SceneFace *self)
{
    if (self->anim_b_after_talk == SCENE_FACE_ANIM_NONE) {
        self->anim_b_after_talk = SCENE_FACE_ANIM_B_DEFAULT;
    }
    SceneFace_PlayB(self, self->anim_b_after_talk, 0);
    self->anim_b_after_talk = SCENE_FACE_ANIM_NONE;
}
CLEAN_AS(func_0201a174, SceneFace_EndTalk)

/* func_0201a19c: for style 0 or 1 (else nothing), the second animation is kept for when the
 * talking stops unless it is a talking animation, and the style's talking animation plays. */
void SceneFace_StartTalk(SceneFace *self, int style)
{
    if (style < 0 || style >= SCENE_FACE_TALK_STYLES) {
        return;
    }
    if (!SceneFace_IsTalkAnim(self, self->anim_b_number)) {
        self->anim_b_after_talk = self->anim_b_number;
    }
    SceneFace_PlayB(self, (int) data_020c8170[style], 0);
}
CLEAN_AS(func_0201a19c, SceneFace_StartTalk)

/* func_0201a1d4: once the face is ready, the second animation becomes `number`, started from
 * frame 0 with `flags` (a talking animation then starts a cycle, SceneFace_StartTalkCycle),
 * and runs a step. */
void SceneFace_PlayB(SceneFace *self, int number, int flags)
{
    if (!SceneFace_IsReady(self)) {
        return;
    }
    void *set = func_02082da8(self->set_link);
    func_0205d7b8(set, number, 1, 0);
    func_0205678c(&self->anim_b, func_0205d894(set), 0, 0, flags, SCENE_FACE_SPEED);
    self->anim_b.ctrl.frame = 0;
    self->anim_b_number = number;
    SceneFace_StartTalkCycle(self);
    func_02056730(&self->anim_b);
}
CLEAN_AS(func_0201a1d4, SceneFace_PlayB)

/* func_0201a234: whether the second animation's cycle is over: for a talking animation as
 * SceneFace_TalkCycleEnded says of its whole frame and frame count, else at the end of an
 * animation that plays once (FrameCtrl_IsDone). */
int SceneFace_TalkCycleDone(SceneFace *self)
{
    if (SceneFace_IsTalkAnim(self, self->anim_b_number)) {
        return SceneFace_TalkCycleEnded(self, self->talk_variant, scene_face_whole(self->anim_b.ctrl.frame),
                                        scene_face_whole(self->anim_b.ctrl.end));
    }
    return FrameCtrl_IsDone(&self->anim_b.ctrl) ? 1 : 0;
}
CLEAN_AS(func_0201a234, SceneFace_TalkCycleDone)

/* func_0201a27c: for a talking animation, a new cycle: its variant is picked
 * (SceneFace_PickTalkCycle) and the animation goes to the variant's first frame. */
void SceneFace_StartTalkCycle(SceneFace *self)
{
    if (SceneFace_IsTalkAnim(self, self->anim_b_number)) {
        SceneFace_PickTalkCycle(self);
        self->anim_b.ctrl.frame = (fx32) ((u32) SceneFace_TalkStartFrame(self, self->talk_variant) << 12);
    }
}
CLEAN_AS(func_0201a27c, SceneFace_StartTalkCycle)

/* func_0201a2a8: whether a talking cycle of `variant` is over at whole frame `frame` of `end`:
 * variant 0 at frame 5 exactly, any other once `frame` is at least `end` - 0x1000.
 * QUIRK: the whole frame count is compared less 0x1000, one frame in 20.12, so for any
 * animation shorter than 0x1000 frames a cycle of variant 1 is over at its first check. */
int SceneFace_TalkCycleEnded(SceneFace *self, int variant, int frame, int end)
{
    (void) self;
    if (variant == 0) {
        return frame == SCENE_FACE_LATE_FRAME;
    }
    return frame >= (int) ((u32) end - 0x1000u);
}
CLEAN_AS(func_0201a2a8, SceneFace_TalkCycleEnded)

/* func_0201a2c8: the first frame of a talking cycle of `variant`: 5 for variant 1, else 0. */
int SceneFace_TalkStartFrame(SceneFace *self, int variant)
{
    (void) self;
    return variant == SCENE_FACE_VARIANT_LATE ? SCENE_FACE_LATE_FRAME : 0;
}
CLEAN_AS(func_0201a2c8, SceneFace_TalkStartFrame)

/* func_0201a2d4: the talking cycle's variant is picked at random (SceneFace_PickTalkVariant). */
void SceneFace_PickTalkCycle(SceneFace *self)
{
    self->talk_variant = SceneFace_PickTalkVariant();
}
CLEAN_AS(func_0201a2d4, SceneFace_PickTalkCycle)

/* func_0201a2e8: whether `number` is a talking animation (0x137 or 0x138). */
int SceneFace_IsTalkAnim(SceneFace *self, int number)
{
    (void) self;
    return number == SCENE_FACE_TALK_0 || number == SCENE_FACE_TALK_1;
}
CLEAN_AS(func_0201a2e8, SceneFace_IsTalkAnim)

/* func_0201a304: loads the face for `model` when it is not loaded and the model names a texture
 * file (its vtable slot 0x6c): the texture's link gets a slot (func_0208308c) and the file is
 * read into it (ResourcePools_BlockSlotLoad); the part's link gets one too, both animations are
 * bound (func_0205685c) to the model's G3D model (0x148) with the texture, on the part's heap;
 * the set's link gets one; no animation plays, the timer starts (func_020645d4) and the face is
 * ready. 0 when a link gets no slot or a binding fails (the steps done stay done), else 1. */
int SceneFace_Load(SceneFace *self, void *model)
{
    const u8 *vtable = *(const u8 *const *) model;
    u32 code = *(const u32 *) (vtable + SCENE_FACE_MODEL_SLOT_TEXTURE);
    const char *path = (const char *) (uintptr_t) ((int (*)(void *))(uintptr_t) code)(model);

    if (func_02082e1c(self->texture_link) != NULL || path == NULL) {
        return 1;
    }
    if (!func_0208308c(self->texture_link)) {
        return 0;
    }
    ResourceSlot *texture = func_02082e1c(self->texture_link);
    ResourcePools_BlockSlotLoad(texture, path);
    if (!func_0208308c(self->part_link)) {
        return 0;
    }
    void *part = func_02082d34(self->part_link);
    int g3d = *(const int *) ((const u8 *) model + SCENE_FACE_MODEL_G3D);
    int block = ResourcePools_BlockSlotBlock(texture);
    if (!func_0205685c(&self->anim_a, g3d, block, 1, func_0205db38(part))) {
        return 0;
    }
    g3d = *(const int *) ((const u8 *) model + SCENE_FACE_MODEL_G3D);
    block = ResourcePools_BlockSlotBlock(texture);
    if (!func_0205685c(&self->anim_b, g3d, block, 1, func_0205db38(part))) {
        return 0;
    }
    if (!func_0208308c(self->set_link)) {
        return 0;
    }
    self->anim_a_number = SCENE_FACE_ANIM_NONE;
    self->anim_b_number = SCENE_FACE_ANIM_NONE;
    func_020645d4(self->timer);
    self->ready = 1;
    return 1;
}
CLEAN_AS(func_0201a304, SceneFace_Load)

/* func_0201a3e4: the second animation's number. */
int SceneFace_AnimB(SceneFace *self)
{
    return self->anim_b_number;
}
CLEAN_AS(func_0201a3e4, SceneFace_AnimB)

/* func_0201a3e8: whether the face is loaded. */
int SceneFace_IsReady(SceneFace *self)
{
    return self->ready != 0;
}
CLEAN_AS(func_0201a3e8, SceneFace_IsReady)

/* func_0201a3f8: the destructor: the animations, the links and the timer, in the reverse order
 * of their places. Returns the face. */
SceneFace *SceneFace_Destruct(SceneFace *self)
{
    func_02056910(&self->anim_b);
    func_02056910(&self->anim_a);
    func_02082dec(self->set_link);
    func_02082e60(self->texture_link);
    func_02082d78(self->part_link);
    func_02064638(self->timer);
    return self;
}
CLEAN_AS(func_0201a3f8, SceneFace_Destruct)

/* func_0201a430: the constructor: the timer, the links and the animations in the order of their
 * places; not ready, no animation playing or kept, variant 2. Returns the face. */
SceneFace *SceneFace_Construct(SceneFace *self)
{
    func_0206463c(self->timer);
    func_02082d90(self->part_link);
    func_02082e78(self->texture_link);
    func_02082e04(self->set_link);
    func_02056928(&self->anim_a);
    func_02056928(&self->anim_b);
    self->ready = 0;
    self->anim_a_number = SCENE_FACE_ANIM_NONE;
    self->anim_b_number = SCENE_FACE_ANIM_NONE;
    self->anim_b_after_talk = SCENE_FACE_ANIM_NONE;
    self->talk_variant = SCENE_FACE_VARIANT_UNSET;
    return self;
}
CLEAN_AS(func_0201a430, SceneFace_Construct)

/* func_0201a798: a talking cycle's variant at random: 1 when a random number below 4 is even,
 * else 0. */
int SceneFace_PickTalkVariant(void)
{
    return (func_020644cc(4) & 1) ? 0 : 1;
}
CLEAN_AS(func_0201a798, SceneFace_PickTalkVariant)

/* func_0201a7b4: the talking state's style (its word 4). */
int SceneTalkState_Style(int *talk)
{
    return talk[1];
}
CLEAN_AS(func_0201a7b4, SceneTalkState_Style)
