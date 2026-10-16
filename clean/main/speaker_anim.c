/* The animations of a scene object's talking (speaker_anim.h).
 *
 * REQUIRES: the member and its object at word-aligned addresses, as every object of the game
 * is (the ARM9 reads an aligned word at a misaligned address). */
#include "speaker_anim.h"

#include "clean.h"

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

extern int func_02016618(SpeakerAnim *anim);
extern int func_020165bc(SpeakerAnim *anim);
extern void func_02016764(SpeakerAnim *anim, u8 *object, int a2, int a3, int a5, int a6, u16 a7, int a8);
extern int func_0201a7b4(void *talking);
extern void func_0201a7b8(void *talking, int style);
extern int func_0201a7bc(const void *talking);
extern int func_0201a798(void);
extern void *func_0201af24(void *object);
extern int func_02082fec(SpeakerAnim *anim, int which);
extern u16 func_0205cb80(void *animation);
extern void func_02083068(SpeakerAnim *anim);
extern int func_02056f94(void *animation);
extern int func_02054230(void *model);
extern void func_020541e8(void *model, int a, int b);
extern void func_02054240(void *model, int animation, int a, int b, int c, u16 first, u16 last, int d);
extern void func_020541b8(void *model, unsigned int first, unsigned int last);
extern u16 func_0205cebc(unsigned int animation);
extern u8 func_0205cf10(unsigned int set);
extern u8 func_0205ceec(int set, int index);
extern u8 func_0205cec8(int set, int index);
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
    func_0201a7b8(object + SPEAKER_ANIM_OBJECT_TALKING, style);
}
CLEAN_AS(func_020161e4, SpeakerAnim_SetTalkStyle)

/* func_0201637c: releases the member's entry in its set of animations (func_02083068). */
void SpeakerAnim_Release(SpeakerAnim *anim)
{
    func_02083068(anim);
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

    if (func_02016618(anim) != 0) {
        if (func_0201a7b4(talking) >= SPEAKER_ANIM_STYLE_2) {
            if (anim->playing == 1) {
                SpeakerAnim_StopTalk(anim, object);
                anim->playing = 0;
            }
        } else if (func_0201a7bc(talking) == 0) {
            if (anim->playing == 1 && func_02054230(model) != 0) {
                SpeakerAnim_StopTalk(anim, object);
                anim->playing = 0;
            }
        } else if (anim->playing == 0 || func_02054230(model) != 0) {
            anim->variant = func_0201a798();
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
    } else if (*(const s32 *) func_0201af24(object + SPEAKER_ANIM_OBJECT_GROUND) == 0) {
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
    if (func_02082fec(anim, which) == 0) {
        return SPEAKER_ANIM_NONE;
    }
    return func_0205cb80((void *) (uintptr_t) func_02082fec(anim, which));
}
CLEAN_AS(func_020164a0, SpeakerAnim_Number)

/* func_020164cc: whether the object's body animation is at its end (func_02056f94). */
int SpeakerAnim_BodyAtEnd(SpeakerAnim *anim, u8 *object)
{
    (void) anim;
    return func_02056f94(object + SPEAKER_ANIM_OBJECT_BODY) != 0;
}
CLEAN_AS(func_020164cc, SpeakerAnim_BodyAtEnd)

/* func_020164ec: func_02016764 with the body animation's speed and the whole part of its frame
 * (bits 12 to 27 of the fx32 frame). */
void SpeakerAnim_PlayFromBodyFrame(SpeakerAnim *anim, u8 *object, int animation, int arg, int slot)
{
    u32 frame = (u32) speaker_anim_word(object, SPEAKER_ANIM_BODY_FRAME);
    func_02016764(anim, object, animation, arg, 0, speaker_anim_word(object, SPEAKER_ANIM_BODY_SPEED),
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
    func_020541e8(object + SPEAKER_ANIM_OBJECT_MODEL, 0, 0);
}
CLEAN_AS(func_02016520, SpeakerAnim_StopTalk)

/* func_02016530: plays the talking animation (func_020165bc) on the object's model over the
 * frames `first` to `last`, on the joint ranges listed for animation 0x143 (func_020541b8).
 * Without the animation, or without a joint set for it (4 or more), the model's animation
 * stops instead. */
void SpeakerAnim_StartTalk(SpeakerAnim *anim, u8 *object, int first, int last)
{
    u8 *model = object + SPEAKER_ANIM_OBJECT_MODEL;
    int animation = func_020165bc(anim);
    if (animation == 0) {
        SpeakerAnim_StopTalk(anim, object);
        return;
    }
    func_02054240(model, animation, 0, 1, SPEAKER_ANIM_ONE, (u16) first, (u16) last, 0);
    int set = func_0205cebc(SPEAKER_ANIM_TALK);
    if (set >= SPEAKER_ANIM_JOINT_SETS) {
        SpeakerAnim_StopTalk(anim, object);
        return;
    }
    unsigned int count = func_0205cf10((unsigned int) set);
    for (unsigned int i = 0; i < count; i++) {
        unsigned int from = func_0205ceec(set, (int) i);
        unsigned int to = func_0205cec8(set, (int) i);
        func_020541b8(model, from, to);
    }
}
CLEAN_AS(func_02016530, SpeakerAnim_StartTalk)
