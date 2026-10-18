/* The animations of a scene object's talking (speaker_anim.h).
 *
 * REQUIRES: the member and its object at word-aligned addresses, as every object of the game
 * is (the ARM9 reads an aligned word at a misaligned address). */
#include "speaker_anim.h"

#include "clean.h"
#include "anim_slots.h"
#include "anim_tables.h"
#include "animated_model.h"
#include "frame_ctrl.h"
#include "held_item_pool.h"
#include "item_traits.h"
#include "layered_model.h"
#include "model_object.h"
#include "pool_link.h"
#include "scene_face.h"
#include "scene_mover.h"
#include "scene_standard_anims.h"
#include "scene_talk_state.h"

static_assert(offsetof(SpeakerAnim, entry) == 0x04, "SpeakerAnim layout");
static_assert(offsetof(SpeakerAnim, speed) == 0x08, "SpeakerAnim layout");
static_assert(offsetof(SpeakerAnim, variant) == 0x0c, "SpeakerAnim layout");
static_assert(offsetof(SpeakerAnim, playing) == 0x10, "SpeakerAnim layout");
static_assert(offsetof(SpeakerAnim, speed_scale) == 0x14, "SpeakerAnim layout");
static_assert(offsetof(SpeakerAnim, keep_speed) == 0x18, "SpeakerAnim layout");

/* The object's parts used here: its speed, its model (an animated member), its body
 * animation and its talking state (byte 0: 1 while talking; word 4: the style). */
#define SPEAKER_ANIM_OBJECT_SPEED 0x98
#define SPEAKER_ANIM_OBJECT_MODEL 0xec
#define SPEAKER_ANIM_OBJECT_BODY 0x188
#define SPEAKER_ANIM_BODY_FRAMES 0x18c
#define SPEAKER_ANIM_BODY_FRAME 0x190
#define SPEAKER_ANIM_BODY_SPEED 0x198
#define SPEAKER_ANIM_OBJECT_GROUND 0x350
#define SPEAKER_ANIM_OBJECT_TALKING 0x418

/* The animation numbers: the talking animation, and the answer for none. */
#define SPEAKER_ANIM_TALK 0x143
#define SPEAKER_ANIM_NONE 0x144
/* The animation slot of the body. */
#define SPEAKER_ANIM_SLOT_BODY 0

/* The talking styles SpeakerAnim_SetTalkStyle picks; from 2 on the talking animation stops. */
#define SPEAKER_ANIM_STYLE_NONE 0
#define SPEAKER_ANIM_STYLE_1 1
#define SPEAKER_ANIM_STYLE_2 2

/* The joint ranges of an animation are listed in a table of four sets (func_0205cebc). */
#define SPEAKER_ANIM_JOINT_SETS 4

/* fx32 1.0 */
#define SPEAKER_ANIM_ONE 0x1000

extern s32 FX_MulFunc(s32 a, s32 b);

static s32 speaker_anim_word(const u8 *object, u32 offset)
{
    return *(const s32 *) (object + offset);
}

/* The body animations with which a speaker talks in style 2, and in style 1. */
static const u16 speaker_anim_style_2[] = {
    0x45, 0x47, 0x49, 0x4b, 0x4d, 0x4f, 0x51, 0x53, 0x55, 0x57, 0x59, 0x5b, 0x5d, 0x5f, 0x61, 0x63,  0x65,
    0x67, 0x69, 0x6e, 0x70, 0x72, 0x75, 0x77, 0x79, 0x7b, 0x7c, 0x7f, 0x80, 0x81, 0x84, 0x86, 0x88,  0x8a,
    0x8c, 0x8d, 0x8f, 0x91, 0x93, 0x94, 0x97, 0x98, 0x99, 0x9c, 0x9f, 0xa1, 0xa3, 0xa5, 0xa7, 0x144,
};
static const u16 speaker_anim_style_1[] = {
    0x46, 0x48, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x5a, 0x60, 0x62, 0x64, 0x68, 0x6c, 0x6d, 0x71,
    0x76, 0x78, 0x83, 0x85, 0x87, 0x8b, 0x96, 0x9b, 0x9d, 0x9e, 0xa0, 0xa2, 0xa4, 0xa8, 0xe6, 0xea,
};

static int speaker_anim_listed(const u16 *list, size_t count, int number)
{
    for (size_t i = 0; i < count; i++) {
        if (list[i] == number) {
            return 1;
        }
    }
    return 0;
}

/* func_020161e4: sets the object's talking style from the number of its body animation: 2 for
 * the numbers of speaker_anim_style_2 (none, 0x144, among them), 1 for those of
 * speaker_anim_style_1, else 0. */
void SpeakerAnim_SetTalkStyle(SpeakerAnim *anim, u8 *object)
{
    int number = SpeakerAnim_Number(anim, SPEAKER_ANIM_SLOT_BODY);
    int style = SPEAKER_ANIM_STYLE_NONE;
    if (speaker_anim_listed(speaker_anim_style_2, sizeof speaker_anim_style_2 / sizeof speaker_anim_style_2[0], number)) {
        style = SPEAKER_ANIM_STYLE_2;
    } else if (speaker_anim_listed(speaker_anim_style_1, sizeof speaker_anim_style_1 / sizeof speaker_anim_style_1[0],
                                   number)) {
        style = SPEAKER_ANIM_STYLE_1;
    }
    SceneTalkState_SetStyle((SceneTalkState *) (void *) (object + SPEAKER_ANIM_OBJECT_TALKING), style);
}
CLEAN_AS(func_020161e4, SpeakerAnim_SetTalkStyle)

/* func_0201637c: releases the member's entry in its set of animations (func_02083068). */
void SpeakerAnim_Release(SpeakerAnim *anim)
{
    PoolLink_Release((PoolLink *) anim);
}
CLEAN_AS(func_0201637c, SpeakerAnim_Release)

/* func_02016384: the frame's step. With the talking animation in the set: in style 2 or more
 * a playing talking animation stops; while the object does not talk, it stops once its cycle
 * ends; while the object talks, a new cycle starts (over frames picked by func_0201a798) when
 * none plays or the last one ended. Then, unless `keep_speed`, SpeakerAnim_UpdateSpeed. */
void SpeakerAnim_Update(SpeakerAnim *anim, u8 *object)
{
    u8 *talking = object + SPEAKER_ANIM_OBJECT_TALKING;
    u8 *model = object + SPEAKER_ANIM_OBJECT_MODEL;

    if (SpeakerAnim_HasTalk(anim) != 0) {
        if (SceneTalkState_Style((int *) (void *) talking) >= SPEAKER_ANIM_STYLE_2) {
            if (anim->playing == 1) {
                SpeakerAnim_StopTalk(anim, object);
                anim->playing = 0;
            }
        } else if (SceneTalkState_IsTalking((const SceneTalkState *) (void *) talking) == 0) {
            if (anim->playing == 1 && LayeredModel_IsBDone((LayeredModel *) (void *) model) != 0) {
                SpeakerAnim_StopTalk(anim, object);
                anim->playing = 0;
            }
        } else if (anim->playing == 0 || LayeredModel_IsBDone((LayeredModel *) (void *) model) != 0) {
            anim->variant = SceneFace_PickTalkVariant();
            int first = SpeakerAnim_FirstFrame(anim, anim->variant);
            int last = SpeakerAnim_LastFrame(anim, anim->variant);
            SpeakerAnim_StartTalk(anim, object, first, last);
            anim->playing = 1;
        }
    }
    if (anim->keep_speed == 0) {
        SpeakerAnim_UpdateSpeed(anim, object);
    }
}
CLEAN_AS(func_02016384, SpeakerAnim_Update)

/* func_02016430: the last frame of the talking animation: 12 for variant 1, else 7. */
int SpeakerAnim_LastFrame(SpeakerAnim *anim, int variant)
{
    (void) anim;
    return variant == 1 ? 12 : 7;
}
CLEAN_AS(func_02016430, SpeakerAnim_LastFrame)

/* func_0201643c: the first frame of the talking animation: 6 for variant 1, else 0. */
int SpeakerAnim_FirstFrame(SpeakerAnim *anim, int variant)
{
    (void) anim;
    return variant == 1 ? 6 : 0;
}
CLEAN_AS(func_0201643c, SpeakerAnim_FirstFrame)

/* func_02016448: the body animation's speed: 1.0 while the object stands still (speed 0) or
 * the word at the start of its member at 0x350 (func_0201af24 gives the member) is 0, else
 * the object's speed times `speed_scale`. It is given to the body animation when not above the
 * body's word at 0x18c (signed). */
void SpeakerAnim_UpdateSpeed(SpeakerAnim *anim, u8 *object)
{
    s32 speed = speaker_anim_word(object, SPEAKER_ANIM_OBJECT_SPEED);
    if (speed == 0) {
        anim->speed = SPEAKER_ANIM_ONE;
    } else if (*(const s32 *) SceneMover_Pace((SceneMover *) (void *) (object + SPEAKER_ANIM_OBJECT_GROUND)) == 0) {
        anim->speed = SPEAKER_ANIM_ONE;
    } else {
        anim->speed = FX_MulFunc(speed, anim->speed_scale);
    }
    if (anim->speed <= speaker_anim_word(object, SPEAKER_ANIM_BODY_FRAMES)) {
        *(s32 *) (object + SPEAKER_ANIM_BODY_SPEED) = anim->speed;
    }
}
CLEAN_AS(func_02016448, SpeakerAnim_UpdateSpeed)

/* func_020164a0: the number of animation `which` of the member's entry (func_0205cb80), or
 * 0x144 without one. QUIRK: func_02082fec is asked twice. */
int SpeakerAnim_Number(SpeakerAnim *anim, int which)
{
    if (PoolLink_Pool1E48Byte((PoolLink *) anim, which) == 0) {
        return SPEAKER_ANIM_NONE;
    }
    return AnimSlots_SlotResource((void *) (uintptr_t) PoolLink_Pool1E48Byte((PoolLink *) anim, which));
}
CLEAN_AS(func_020164a0, SpeakerAnim_Number)

/* func_020164cc: whether the object's body animation is at its end (func_02056f94). */
int SpeakerAnim_BodyAtEnd(SpeakerAnim *anim, u8 *object)
{
    (void) anim;
    return FrameCtrl_IsDone((const FrameCtrl *) (void *) (object + SPEAKER_ANIM_OBJECT_BODY)) != 0;
}
CLEAN_AS(func_020164cc, SpeakerAnim_BodyAtEnd)

/* func_020164ec: func_02016764 with the body animation's speed and the whole part of its frame
 * (bits 12 to 27 of the fx32 frame). */
void SpeakerAnim_PlayFromBodyFrame(SpeakerAnim *anim, u8 *object, int animation, int arg, int slot)
{
    u32 frame = (u32) speaker_anim_word(object, SPEAKER_ANIM_BODY_FRAME);
    SpeakerAnim_Play(anim, object, animation, arg, 0, speaker_anim_word(object, SPEAKER_ANIM_BODY_SPEED),
                     (u16) ((frame << 4) >> 16), slot);
}
CLEAN_AS(func_020164ec, SpeakerAnim_PlayFromBodyFrame)

/* func_0201651c */
void SpeakerAnim_SetKeepSpeed(SpeakerAnim *anim, int keep)
{
    anim->keep_speed = (u8) keep;
}
CLEAN_AS(func_0201651c, SpeakerAnim_SetKeepSpeed)

/* func_02016520: stops the animation on the object's model (func_020541e8 with 0). */
void SpeakerAnim_StopTalk(SpeakerAnim *anim, u8 *object)
{
    (void) anim;
    LayeredModel_StartBFromBase((LayeredModel *) (void *) (object + SPEAKER_ANIM_OBJECT_MODEL), 0, 0);
}
CLEAN_AS(func_02016520, SpeakerAnim_StopTalk)

/* func_02016530: plays the talking animation (func_020165bc) on the object's model over the
 * frames `first` to `last`, on the joint ranges listed for animation 0x143 (func_020541b8).
 * Without the animation, or without a joint set for it (4 or more), the model's animation
 * stops instead. */
void SpeakerAnim_StartTalk(SpeakerAnim *anim, u8 *object, int first, int last)
{
    u8 *model = object + SPEAKER_ANIM_OBJECT_MODEL;
    int animation = SpeakerAnim_TalkResource(anim);
    if (animation == 0) {
        SpeakerAnim_StopTalk(anim, object);
        return;
    }
    LayeredModel_PlayB((LayeredModel *) (void *) model, (const void *) (uintptr_t) animation, 0, 1, SPEAKER_ANIM_ONE,
                       (u16) first, (u16) last, 0);
    int set = AnimTables_HeldJointGroup(SPEAKER_ANIM_TALK);
    if (set >= SPEAKER_ANIM_JOINT_SETS) {
        SpeakerAnim_StopTalk(anim, object);
        return;
    }
    unsigned int count = AnimTables_HeldJointCount((unsigned int) set);
    for (unsigned int i = 0; i < count; i++) {
        unsigned int from = AnimTables_HeldJointA(set, (int) i);
        unsigned int to = AnimTables_HeldJointB(set, (int) i);
        LayeredModel_MoveNodesToB((LayeredModel *) (void *) model, from, to);
    }
}
CLEAN_AS(func_02016530, SpeakerAnim_StartTalk)

/* ---- Loading and playing animations on the object's model */

/* The object's parts used by the functions below: its three standard animation numbers (words
 * 0, 1 and 2 of its member at 0x2a0, func_0201b380, func_0201b37c and func_0201b378), and the
 * member at 0x2ac that is told of each new body animation (func_0201a090). */
#define SPEAKER_ANIM_OBJECT_STANDARD 0x2a0
#define SPEAKER_ANIM_OBJECT_FOLLOWER 0x2ac

/* The animation slots of the member's entry: the body (0), the item pose (1) and the talking
 * animation (2). */
#define SPEAKER_ANIM_SLOT_ITEM 1
#define SPEAKER_ANIM_SLOT_TALK 2
#define SPEAKER_ANIM_SLOTS 3

/* The play modes in which frame 0 asks for the last frame. */
#define SPEAKER_ANIM_MODE_2 2
#define SPEAKER_ANIM_MODE_3 3
#define SPEAKER_ANIM_LAST_FRAME 0xffff

/* The item with a pose of its own (animation 0x13f on joints 0x0c to 0x0e), and what
 * func_0205ceb0 gives for a pose that stops the item animation. */
#define SPEAKER_ANIM_ITEM_OWN_POSE 0x1369
#define SPEAKER_ANIM_OWN_POSE 0x13f
#define SPEAKER_ANIM_OWN_POSE_FIRST_JOINT 0x0c
#define SPEAKER_ANIM_OWN_POSE_LAST_JOINT 0x0e
#define SPEAKER_ANIM_POSE_NONE 3

extern int NNS_G3dGetJntAnmSet(int resource);
extern int func_02107b44(int set, int index);
extern void func_0201c6a8(void *object);

/* An animation's resource: the first entry of its joint animation set. */
static int speaker_anim_resource(int animation)
{
    return func_02107b44(NNS_G3dGetJntAnmSet(AnimSlots_SlotData((void *) (uintptr_t) animation)), 0);
}

/* func_020165bc: the talking animation's resource, or 0 when slot 2 does not hold the talking
 * animation or the entry has no slot 2. */
int SpeakerAnim_TalkResource(SpeakerAnim *anim)
{
    if (SpeakerAnim_HasTalk(anim) == 0) {
        return 0;
    }
    int animation = PoolLink_Pool1E48Byte((PoolLink *) anim, SPEAKER_ANIM_SLOT_TALK);
    if (animation == 0) {
        return 0;
    }
    return speaker_anim_resource(animation);
}
CLEAN_AS(func_020165bc, SpeakerAnim_TalkResource)

/* func_020165f4: puts the talking animation (0x143) into slot 2, when the entry has one. */
void SpeakerAnim_LoadTalk(SpeakerAnim *anim)
{
    int animation = PoolLink_Pool1E48Byte((PoolLink *) anim, SPEAKER_ANIM_SLOT_TALK);
    if (animation != 0) {
        AnimSlots_Load((void *) (uintptr_t) animation, SPEAKER_ANIM_TALK, 0, 0);
    }
}
CLEAN_AS(func_020165f4, SpeakerAnim_LoadTalk)

/* func_02016618: whether slot 2 holds the talking animation. */
int SpeakerAnim_HasTalk(SpeakerAnim *anim)
{
    return SpeakerAnim_Number(anim, SPEAKER_ANIM_SLOT_TALK) == SPEAKER_ANIM_TALK;
}
CLEAN_AS(func_02016618, SpeakerAnim_HasTalk)

/* func_02016638: the pose of holding `item` on the object's model, in slot 1 (`arg` is
 * func_020547b0's third argument): animation 0x13f on joints 0x0c to 0x0e for item 0x1369, else
 * the item's own pose (func_0205f670) on the joint ranges listed for it. The model's item
 * animation stops (func_02054768) for no item (func_0204c4e8 gives 0), for a `pose` func_0205ceb0
 * gives 3 for, for an item without a pose (0x144) and for a pose without joint ranges (a set of
 * 4 or more; the animation was set already). Nothing happens when the entry has no slot 1. */
void SpeakerAnim_PlayItemPose(SpeakerAnim *anim, u8 *object, u16 *item, int pose, u16 arg)
{
    u8 *model = object + SPEAKER_ANIM_OBJECT_MODEL;

    if (ItemTraits_HasHeldModel(item) == 0 || AnimTables_HeldMode((unsigned int) pose) == SPEAKER_ANIM_POSE_NONE) {
        LayeredModel_StartAFromBase((LayeredModel *) (void *) model, 0, 0);
        return;
    }
    if (*item == SPEAKER_ANIM_ITEM_OWN_POSE) {
        int animation = SpeakerAnim_Load(anim, SPEAKER_ANIM_OWN_POSE, SPEAKER_ANIM_SLOT_ITEM);
        if (animation == 0) {
            return;
        }
        LayeredModel_PlayA((LayeredModel *) (void *) model, (const void *) (uintptr_t) animation, arg, 0, SPEAKER_ANIM_ONE, 0,
                           0, 0);
        LayeredModel_MoveNodesToA((LayeredModel *) (void *) model, SPEAKER_ANIM_OWN_POSE_FIRST_JOINT,
                                  SPEAKER_ANIM_OWN_POSE_LAST_JOINT);
        return;
    }

    unsigned int number = HeldItemPool_ItemAnim(item);
    if (number == SPEAKER_ANIM_NONE) {
        LayeredModel_StartAFromBase((LayeredModel *) (void *) model, 0, 0);
        return;
    }
    int animation = SpeakerAnim_Load(anim, (int) number, SPEAKER_ANIM_SLOT_ITEM);
    if (animation == 0) {
        return;
    }
    LayeredModel_PlayA((LayeredModel *) (void *) model, (const void *) (uintptr_t) animation, arg, 0, SPEAKER_ANIM_ONE, 0, 0,
                       0);
    int set = AnimTables_HeldJointGroup(number);
    if (set >= SPEAKER_ANIM_JOINT_SETS) {
        LayeredModel_StartAFromBase((LayeredModel *) (void *) model, 0, 0);
        return;
    }
    unsigned int count = AnimTables_HeldJointCount((unsigned int) set);
    for (unsigned int i = 0; i < count; i++) {
        unsigned int from = AnimTables_HeldJointA(set, (int) i);
        unsigned int to = AnimTables_HeldJointB(set, (int) i);
        LayeredModel_MoveNodesToA((LayeredModel *) (void *) model, from, to);
    }
}
CLEAN_AS(func_02016638, SpeakerAnim_PlayItemPose)

/* func_02016764: plays animation `number` in slot `slot` (0 to 2, else nothing) on the object's
 * model, in play mode `mode` at `speed` from frame `frame` (in modes 2 and 3 frame 0 means the
 * last frame, 0xffff); `arg` is the model call's third argument.
 *
 * In slot 0 (the body), `number` 0 to 2 names one of the object's standard animations
 * (SpeakerAnim_Resolve); the animation is (re)started unless it is the object's first standard
 * animation and already the body's. Then the talking style follows the body animation, and the
 * member at 0x2ac is told the body's number, the mode and the talking style. Slot 1 plays with
 * func_020547b0, slot 2 with func_02054240. */
void SpeakerAnim_Play(SpeakerAnim *anim, u8 *object, int number, int arg, int mode, int speed, u16 frame, int slot)
{
    void *model = object + SPEAKER_ANIM_OBJECT_MODEL;
    void *standard = object + SPEAKER_ANIM_OBJECT_STANDARD;
    unsigned int start = frame;

    if (frame == 0 && (mode == SPEAKER_ANIM_MODE_2 || mode == SPEAKER_ANIM_MODE_3)) {
        start = SPEAKER_ANIM_LAST_FRAME;
    }
    if (slot < 0 || slot >= SPEAKER_ANIM_SLOTS) {
        return;
    }

    if (slot == SPEAKER_ANIM_SLOT_BODY) {
        int resolved = SpeakerAnim_Resolve(anim, number, standard);
        if (resolved != SceneStandardAnims_First(standard) || SpeakerAnim_IsBody(anim, resolved, standard) == 0) {
            int animation = SpeakerAnim_Load(anim, resolved, slot);
            if (animation != 0) {
                LayeredModel_PlayBaseB(model, (const void *) (uintptr_t) animation, arg, mode, speed, (u16) start, 0);
            }
        }
        SpeakerAnim_SetTalkStyle(anim, object);
        int body = SpeakerAnim_Number(anim, SPEAKER_ANIM_SLOT_BODY);
        int style = SceneTalkState_Style((int *) (void *) (object + SPEAKER_ANIM_OBJECT_TALKING));
        SceneFace_MatchBody((SceneFace *) (void *) (object + SPEAKER_ANIM_OBJECT_FOLLOWER), body, mode, style);
    } else if (slot == SPEAKER_ANIM_SLOT_ITEM) {
        int animation = SpeakerAnim_Load(anim, number, slot);
        if (animation != 0) {
            LayeredModel_PlayA(model, (const void *) (uintptr_t) animation, arg, mode, speed, (u16) start, 0, 0);
        }
    } else {
        int animation = SpeakerAnim_Load(anim, number, slot);
        if (animation != 0) {
            LayeredModel_PlayB(model, (const void *) (uintptr_t) animation, arg, mode, speed, (u16) start, 0, 0);
        }
    }
}
CLEAN_AS(func_02016764, SpeakerAnim_Play)

/* func_02016884: whether animation `number` (resolved as SpeakerAnim_Resolve does) is the
 * body's. */
int SpeakerAnim_IsBody(SpeakerAnim *anim, int number, void *standard)
{
    int resolved = SpeakerAnim_Resolve(anim, number, standard);
    return resolved == SpeakerAnim_Number(anim, SPEAKER_ANIM_SLOT_BODY);
}
CLEAN_AS(func_02016884, SpeakerAnim_IsBody)

/* func_020168ac: `number` 0, 1 or 2 is the object's standard animation of that number (a word
 * of `standard`, its member at 0x2a0); any other number is itself. */
int SpeakerAnim_Resolve(SpeakerAnim *anim, int number, void *standard)
{
    (void) anim;
    switch (number) {
        case 0:
            return SceneStandardAnims_First(standard);
        case 1:
            return SceneStandardAnims_Second(standard);
        case 2:
            return SceneStandardAnims_Third(standard);
        default:
            return number;
    }
}
CLEAN_AS(func_020168ac, SpeakerAnim_Resolve)

/* func_020168e4: puts animation `number` into slot `slot` (func_0205cc1c) and gives its
 * resource, or 0 when the entry has no such slot. */
int SpeakerAnim_Load(SpeakerAnim *anim, int number, int slot)
{
    int animation = PoolLink_Pool1E48Byte((PoolLink *) anim, slot);
    if (animation == 0) {
        return 0;
    }
    AnimSlots_Load((void *) (uintptr_t) animation, number, 0, 0);
    return speaker_anim_resource(animation);
}
CLEAN_AS(func_020168e4, SpeakerAnim_Load)

/* func_0201691c: sets the member up for `object` with the speed scale `speed_scale`: the body
 * speed follows the object again and, once func_0208308c gives the entry, the object's first
 * standard animation plays, the model is reset (func_02055050) and given func_0201c6a8 as its
 * callback with the object, the variant is 2, slot 2 gets the talking animation unless it has
 * it, and no talking animation plays. Returns 0 without an entry, else 1. */
int SpeakerAnim_Init(SpeakerAnim *anim, u8 *object, s32 speed_scale)
{
    u8 *model = object + SPEAKER_ANIM_OBJECT_MODEL;

    SpeakerAnim_SetKeepSpeed(anim, 0);
    anim->speed_scale = speed_scale;
    if (PoolLink_Take((PoolLink *) anim) == 0) {
        return 0;
    }
    SpeakerAnim_Play(anim, object, 0, 0, 0, SPEAKER_ANIM_ONE, 0, SPEAKER_ANIM_SLOT_BODY);
    AnimatedModel_Attach((AnimatedModel *) (void *) model);
    ModelObject_SetNodeCallback((ModelObject *) (void *) model, (void *) (uintptr_t) func_0201c6a8, 6, 1, object, 0);
    anim->variant = 2;
    if (SpeakerAnim_HasTalk(anim) == 0) {
        SpeakerAnim_LoadTalk(anim);
    }
    anim->playing = 0;
    return 1;
}
CLEAN_AS(func_0201691c, SpeakerAnim_Init)

/* func_02016998: the destructor: the holder's (PoolLink_Pool1E48Destruct). Returns the member.
 * Its name and SpeakerAnim_Destruct's are the wrong way round: their callers in the overlays
 * use these names. */
SpeakerAnim *SpeakerAnim_Construct(SpeakerAnim *anim)
{
    PoolLink_Pool1E48Destruct((PoolLink *) anim);
    return anim;
}
CLEAN_AS(func_02016998, SpeakerAnim_Construct)

/* func_020169a8: the constructor (see SpeakerAnim_Construct): the holder's
 * (PoolLink_Pool1E48Construct). Returns the member. */
SpeakerAnim *SpeakerAnim_Destruct(SpeakerAnim *anim)
{
    PoolLink_Pool1E48Construct((PoolLink *) anim);
    return anim;
}
CLEAN_AS(func_020169a8, SpeakerAnim_Destruct)
