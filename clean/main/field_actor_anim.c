/* The field actor's animations (field_actor.h): the body's (its model at 0x234, the animation
 * playing at FieldActor.animation), the held item's that go with them, and the face's two
 * animations at 0x710 and 0x73c (field_actor_parts.h).
 *
 * An animation number picks the body's animation through data_020c7d04 and, through tables of
 * its own, the held item's and each face animation's. */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "anim_slots.h"
#include "anim_tables.h"
#include "face_anim_heaps.h"
#include "face_anim_slots.h"
#include "face_anim_timer.h"
#include "face_texture.h"
#include "frame_ctrl.h"
#include "held_item_pool.h"
#include "layered_model.h"
#include "tex_pattern_anim.h"

static_assert(offsetof(FieldActor, anim) == 0x2d0, "body animation");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");

/* The scene: 0 outdoors (overlay 3), else indoors (overlay 4). */
extern u8 data_020e54a8;
/* The body's animation resource by animation number. */
extern const u16 data_020c7d04[];

/* PlayAnimation's `resource` below this is the resource itself; this value takes the
 * animation number's (data_020c7d04). */
#define ANIM_RESOURCE_BY_NUMBER 0x137
/* An animation after which the next one starts without blending. */
#define ANIM_NO_BLEND_AFTER 0xa1
/* The face animations' numbers when an animation's table has none for them. */
#define FACE_ANIM_A_DEFAULT 0
#define FACE_ANIM_B_DEFAULT 0xba
/* A held item without an animation of its own (func_0205f670). */
#define HELD_ANIM_NONE 0x144
#define ITEM_NONE 0xfff1
/* The model's G3D model, 0x5c into a model object. */
#define MODEL_G3D 0x5c

/* The animation sets and the joint animations in them. */
extern int NNS_G3dGetJntAnmSet(int resource);
extern int func_02107b44(int set, int index);

/* The byte `offset` into the actor. */
static u8 *field_actor_anim_at(FieldActor *actor, u32 offset)
{
    return (u8 *) actor + offset;
}

/* The whole frame of a 20.12 frame position, in 16 bits. */
static u16 field_actor_anim_whole_frame(fx32 frame)
{
    return (u16) (((u32) frame << 4) >> 16);
}

/* ---- The held item's animation */

/* func_0201079c: the held item `item` with the body's `animation`, blended over `frames`. The
 * item's animation (func_0205f670) plays (func_020547b0) with its joints (func_0205cebc's group
 * below 4: func_0205cf10's count of func_0205ceec and func_0205cec8 pairs, with group 1's first
 * one more for the animation's mode 2), unless the animation's mode (func_0205ceb0) is 3, the
 * item has no animation, or the mode is 1 and the item is outside 0x1380 to 0x13a7: then (or
 * with a group of 4 or more) the held item is left without one (func_02054768). The item's
 * animation is kept at 0x708 either way. */
void FieldActor_PlayHeldAnimation(FieldActor *actor, u16 *item, int animation, int frames)
{
    u8 *body = field_actor_anim_at(actor, FIELD_ACTOR_BODY);
    u32 held = HeldItemPool_ItemAnim(item);
    int mode = AnimTables_HeldMode(animation);
    int play = mode != 3 && held != HELD_ANIM_NONE;
    if (play && mode == 1 && (*item < 0x1380 || *item > 0x13a7)) {
        play = 0;
    }

    if (!play) {
        LayeredModel_StartAFromBase((LayeredModel *) (void *) body, frames, 0);
    } else {
        u8 *set = field_actor_anim_at(actor, FIELD_ACTOR_HELD_ANIM_SET);
        AnimSlots_Load(set, (int) held, 1, 0);
        int joints = func_02107b44(NNS_G3dGetJntAnmSet(AnimSlots_SlotData(set)), 0);
        LayeredModel_PlayA((LayeredModel *) (void *) body, (const void *) (uintptr_t) joints, frames, 0, FX32_ONE, 0, 0, 0);
        u32 group = AnimTables_HeldJointGroup(held);
        if (group < 4) {
            u32 count = AnimTables_HeldJointCount(group);
            for (u32 i = 0; i < count; i++) {
                int a = AnimTables_HeldJointA((int) group, (int) i);
                LayeredModel_AddNodesA((LayeredModel *) (void *) body, a, AnimTables_HeldJointB((int) group, (int) i));
            }
            if (mode == 2) {
                int a = AnimTables_HeldJointA(1, 0);
                LayeredModel_RemoveNodesA((LayeredModel *) (void *) body, a, AnimTables_HeldJointB(1, 0));
            }
        } else {
            LayeredModel_StartAFromBase((LayeredModel *) (void *) body, frames, 0);
        }
    }
    FIELD_ACTOR_HELD_ANIM(actor) = (int) held;
}
CLEAN_AS(func_0201079c, FieldActor_PlayHeldAnimation)

/* func_020108cc: FieldActor_PlayHeldAnimation with the held item of the record outdoors with
 * flag 0 (FieldActor_RecordHeldItem), else with none. */
void FieldActor_AnimateHeldItem(FieldActor *actor, int animation, int frames)
{
    u16 item = ITEM_NONE;
    if (data_020e54a8 == 0 && FieldActor_TestFlag(actor, 0) != 0) {
        u16 held;
        FieldActor_RecordHeldItem(&held, actor);
        item = held;
    }
    FieldActor_PlayHeldAnimation(actor, &item, animation, frames);
}
CLEAN_AS(func_020108cc, FieldActor_AnimateHeldItem)

/* ---- The body's animation */

/* func_02010934: the animation playing starts again (blended over 3 frames) at the body
 * animation's whole frame, with its speed and flags; the face animations' frames lose their
 * fractions (and all but 16 bits of their whole part). */
void FieldActor_RestartAnimation(FieldActor *actor)
{
    fx32 frame_a = (fx32) ((u32) FIELD_ACTOR_FACE_ANIM_A_FRAME(actor) & 0x0ffff000);
    fx32 frame_b = (fx32) ((u32) FIELD_ACTOR_FACE_ANIM_B_FRAME(actor) & 0x0ffff000);
    FieldActor_PlayAnimation(actor, actor->animation, 3, actor->anim.flags, (int) actor->anim.speed,
                             field_actor_anim_whole_frame(actor->anim.frame), 0, ANIM_RESOURCE_BY_NUMBER);
    FIELD_ACTOR_FACE_ANIM_A_FRAME(actor) = frame_a;
    FIELD_ACTOR_FACE_ANIM_B_FRAME(actor) = frame_b;
}
CLEAN_AS(func_02010934, FieldActor_RestartAnimation)

/* func_020109a0: `animation` once from its start at normal speed, blended over `blend` frames
 * (the held item's over `held_blend`). */
void FieldActor_PlayAnimationOnce(FieldActor *actor, int animation, int blend, u16 held_blend)
{
    FieldActor_PlayAnimation(actor, animation, blend, FRAME_CTRL_ONCE, FX32_ONE, 0, held_blend, ANIM_RESOURCE_BY_NUMBER);
}
CLEAN_AS(func_020109a0, FieldActor_PlayAnimationOnce)

/* func_020109c8: `animation` looping from the body animation's whole frame at its speed. */
void FieldActor_SwitchAnimation(FieldActor *actor, int animation, int blend, int held_blend)
{
    FieldActor_PlayAnimation(actor, animation, blend, 0, (int) actor->anim.speed,
                             field_actor_anim_whole_frame(actor->anim.frame), (u16) held_blend, ANIM_RESOURCE_BY_NUMBER);
}
CLEAN_AS(func_020109c8, FieldActor_SwitchAnimation)

/* func_020109fc: `animation` looping from its start at normal speed. */
void FieldActor_PlayAnimationLoop(FieldActor *actor, int animation, int blend, int held_blend)
{
    FieldActor_PlayAnimation(actor, animation, blend, 0, FX32_ONE, 0, (u16) held_blend, ANIM_RESOURCE_BY_NUMBER);
}
CLEAN_AS(func_020109fc, FieldActor_PlayAnimationLoop)

/* func_02010a24: plays `animation` with the body resource `resource` (or the number's, from
 * ANIM_RESOURCE_BY_NUMBER up), blended over `blend` frames, with the FrameCtrl `flags`, `speed`
 * and `start` frame. After animation ANIM_NO_BLEND_AFTER there is no blending. The body's
 * animation starts unless animation 0 is asked for while 0 plays, from frame 0, blended, and by
 * number; then it runs on. The held item follows over `held_blend` frames, and so do the face
 * animations with the flags. */
void FieldActor_PlayAnimation(FieldActor *actor, int animation, int blend, u8 flags, int speed, u16 start, u16 held_blend,
                              int resource)
{
    int current = actor->animation;
    if (current == ANIM_NO_BLEND_AFTER) {
        blend = 0;
        held_blend = 0;
    }

    int body_resource;
    if (resource < ANIM_RESOURCE_BY_NUMBER) {
        body_resource = resource;
    } else {
        unsigned int number = (unsigned int) animation;
        body_resource = FieldActor_AnimationResource(actor, &number);
    }

    if (animation != 0 || current != 0 || start != 0 || blend == 0 || resource < ANIM_RESOURCE_BY_NUMBER) {
        u8 *set = field_actor_anim_at(actor, FIELD_ACTOR_BODY_ANIM_SET);
        AnimSlots_Load(set, body_resource, 1, 0);
        int joints = func_02107b44(NNS_G3dGetJntAnmSet(AnimSlots_SlotData(set)), 0);
        LayeredModel_PlayBaseA((LayeredModel *) (void *) field_actor_anim_at(actor, FIELD_ACTOR_BODY),
                               (const void *) (uintptr_t) joints, blend, flags, speed, start, 0);
        actor->animation = animation;
        FIELD_ACTOR_ANIM_FLAGS(actor) = flags;
    }

    FieldActor_AnimateHeldItem(actor, body_resource, held_blend);
    FieldActor_MatchFaceAnimA(actor, &body_resource, &flags);
    FieldActor_MatchFaceAnimB(actor, &body_resource, &flags);
}
CLEAN_AS(func_02010a24, FieldActor_PlayAnimation)

/* func_020110b4: the body's animation resource of the animation number. */
unsigned short FieldActor_AnimationResource(FieldActor *actor, const unsigned int *animation)
{
    (void) actor;
    return data_020c7d04[*animation];
}
CLEAN_AS(func_020110b4, FieldActor_AnimationResource)

/* func_02010f5c: the body's model runs a frame (func_02054860). */
void FieldActor_UpdateBody(FieldActor *actor)
{
    LayeredModel_UpdateA((LayeredModel *) (void *) field_actor_anim_at(actor, FIELD_ACTOR_BODY));
}
CLEAN_AS(func_02010f5c, FieldActor_UpdateBody)

/* ---- The face's animations */

/* func_02010af4: the face's second animation becomes `number` (func_0205d7b8 on the set at
 * 0x70e), started from frame 0 at normal speed with `flags` and run a step. */
void FieldActor_PlayFaceAnimB(FieldActor *actor, const int *number, const u8 *flags)
{
    u8 *set = field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_SET);
    u8 *anim = field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_B);
    FaceAnimSlots_Load(set, *number, 1, 0);
    TexPatternAnim_Start((TexPatternAnim *) (void *) anim, (void *) (uintptr_t) FaceAnimSlots_SlotDataB(set), 0, 0, *flags,
                         FX32_ONE);
    TexPatternAnim_Step((TexPatternAnim *) (void *) anim);
    FIELD_ACTOR_FACE_ANIM_B_NUMBER(actor) = *number;
}
CLEAN_AS(func_02010af4, FieldActor_PlayFaceAnimB)

/* func_02010b50: the same for the face's first animation. */
void FieldActor_PlayFaceAnimA(FieldActor *actor, const int *number, const u8 *flags)
{
    u8 *set = field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_SET);
    u8 *anim = field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_A);
    FaceAnimSlots_Load(set, *number, 1, 0);
    TexPatternAnim_Start((TexPatternAnim *) (void *) anim, (void *) (uintptr_t) FaceAnimSlots_SlotDataA(set), 0, 0, *flags,
                         FX32_ONE);
    TexPatternAnim_Step((TexPatternAnim *) (void *) anim);
    FIELD_ACTOR_FACE_ANIM_A_NUMBER(actor) = *number;
}
CLEAN_AS(func_02010b50, FieldActor_PlayFaceAnimA)

/* func_02010bac: the face's second animation for the body's `animation` (func_0205cf1c): when
 * it has none, FACE_ANIM_B_DEFAULT unless that already plays; nothing more when it is none
 * then. */
void FieldActor_MatchFaceAnimB(FieldActor *actor, const int *animation, const u8 *flags)
{
    int playing = FIELD_ACTOR_FACE_ANIM_B_NUMBER(actor);
    int number = AnimTables_FaceAnimB((u32) *animation);
    if (number == FACE_ANIM_NONE && playing != FACE_ANIM_B_DEFAULT) {
        number = FACE_ANIM_B_DEFAULT;
    }
    if (number != FACE_ANIM_NONE) {
        FieldActor_PlayFaceAnimB(actor, &number, flags);
    }
}
CLEAN_AS(func_02010bac, FieldActor_MatchFaceAnimB)

/* func_02010bf0: the same for the face's first animation (func_0205cf28, FACE_ANIM_A_DEFAULT). */
void FieldActor_MatchFaceAnimA(FieldActor *actor, const int *animation, const u8 *flags)
{
    int playing = FIELD_ACTOR_FACE_ANIM_A_NUMBER(actor);
    int number = AnimTables_FaceAnimA((u32) *animation);
    if (number == FACE_ANIM_NONE && playing != FACE_ANIM_A_DEFAULT) {
        number = FACE_ANIM_A_DEFAULT;
    }
    if (number != FACE_ANIM_NONE) {
        FieldActor_PlayFaceAnimA(actor, &number, flags);
    }
}
CLEAN_AS(func_02010bf0, FieldActor_MatchFaceAnimA)

/* func_02010c34: both face animations are bound (func_0205685c) to the model of the head's
 * first model (0x3e8) with the face's texture, on the heap of the part at 0x70f. */
void FieldActor_BindFaceAnims(FieldActor *actor)
{
    static const u32 anims[2] = {FIELD_ACTOR_FACE_ANIM_A, FIELD_ACTOR_FACE_ANIM_B};
    for (int i = 0; i < 2; i++) {
        int model = FIELD_ACTOR_FIELD(actor, int, FIELD_ACTOR_MODEL_A + MODEL_G3D);
        int texture = FaceTexture_SlotFile(field_actor_anim_at(actor, FIELD_ACTOR_FACE));
        Heap *heap = (Heap *) (uintptr_t) FaceAnimHeaps_SlotHeap(field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_HEAP));
        TexPatternAnim_Load((TexPatternAnim *) (void *) field_actor_anim_at(actor, anims[i]), (u8 *) (uintptr_t) model,
                            (u8 *) (uintptr_t) texture, 1, heap);
    }
}
CLEAN_AS(func_02010c34, FieldActor_BindFaceAnims)

/* func_02010ecc: the face's second animation runs a step, unless it is none. */
void FieldActor_StepFaceAnimB(FieldActor *actor)
{
    if (FIELD_ACTOR_FACE_ANIM_B_NUMBER(actor) != FACE_ANIM_NONE) {
        TexPatternAnim_Step((TexPatternAnim *) (void *) field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_B));
    }
}
CLEAN_AS(func_02010ecc, FieldActor_StepFaceAnimB)

/* func_02010ef4: the face's first animation runs a step, unless it is none; number 0 rests at
 * its first frame (func_02056f28) until the timer at 0x768 lets it go on (func_020645e0). */
void FieldActor_StepFaceAnimA(FieldActor *actor)
{
    int number = FIELD_ACTOR_FACE_ANIM_A_NUMBER(actor);
    u8 *anim = field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_A);
    if (number == FACE_ANIM_NONE) {
        return;
    }
    if (number != 0 || FrameCtrl_Passed((const FrameCtrl *) (void *) anim, 0) == 0 ||
        FaceAnimTimer_Step((FaceAnimTimer *) (void *) field_actor_anim_at(actor, FIELD_ACTOR_FACE_ANIM_TIMER)) != 0) {
        TexPatternAnim_Step((TexPatternAnim *) (void *) anim);
    }
}
CLEAN_AS(func_02010ef4, FieldActor_StepFaceAnimA)

/* func_02010f48: both face animations run a step. */
void FieldActor_StepFaceAnims(FieldActor *actor)
{
    FieldActor_StepFaceAnimA(actor);
    FieldActor_StepFaceAnimB(actor);
}
CLEAN_AS(func_02010f48, FieldActor_StepFaceAnims)
