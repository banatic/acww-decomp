/* A town villager's mood as its scene object shows it (villager_mood.h). */
#include "villager_mood.h"

#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "npc_id.h"
#include "scene_action.h"
#include "scene_motion_request.h"
#include "scene_standard_anims.h"
#include "session.h"
#include "sound_emitter.h"
#include "speaker_anim.h"
#include "town_villager.h"
#include "villager_state.h"
#include "villager_status.h"

static_assert(offsetof(VillagerMood, shown) == 0x40, "VillagerMood layout");
static_assert(offsetof(VillagerMood, effect_mood) == 0x44, "VillagerMood layout");
static_assert(offsetof(VillagerMood, effect) == 0x4c, "VillagerMood layout");
static_assert(offsetof(VillagerMood, asked_frames) == 0x56, "VillagerMood layout");
static_assert(offsetof(VillagerMood, sounds_on) == 0x5a, "VillagerMood layout");

/* The villager scene object's parts used here (villager_scene_object.h). */
#define VILLAGER_MOOD_POSITION 0x5c /* Vec3 */
#define VILLAGER_MOOD_ANGLE 0x8e    /* s16 */
#define VILLAGER_MOOD_STANDARD_ANIMS 0x2a0
#define VILLAGER_MOOD_ANIM 0x334
#define VILLAGER_MOOD_JOINT_16_POINT 0x478 /* Vec3 */
#define VILLAGER_MOOD_MOTION 0x564
#define VILLAGER_MOOD_ACTION 0x618
#define VILLAGER_MOOD_TOWN_VILLAGER 0x830 /* u8 *: its record of the town (town_villager.h) */
#define VILLAGER_MOOD_SLOT_RECORD 0x64    /* vtable slot: the villager's record, or 0 */

/* Each unit of a mood's length, in frames. */
#define VILLAGER_MOOD_UNIT_FRAMES 1200
/* The mood whose look depends on the personality, and the moods it shows. */
#define VILLAGER_MOOD_BY_PERSONALITY 4
#define VILLAGER_MOOD_2 2
#define VILLAGER_MOOD_3 3
/* The first of the moods' animations, and the moods' effects (VillagerMood_StartEffect). */
#define VILLAGER_MOOD_FIRST_ANIMATION 0xe5
#define VILLAGER_MOOD_EFFECT_1 1
#define VILLAGER_MOOD_EFFECT_2 2
#define VILLAGER_MOOD_EFFECT_3 3
#define VILLAGER_MOOD_EFFECTS 5
/* The effects' cycles in frames, the frame of mood 1's second effect and the volume. */
#define VILLAGER_MOOD_CYCLE_1 40
#define VILLAGER_MOOD_CYCLE_1_SECOND 20
#define VILLAGER_MOOD_CYCLE_2 20
#define VILLAGER_MOOD_CYCLE_3 14
#define VILLAGER_MOOD_VOLUME 0x7f

/* The moods' first and second standard animations. */
extern const s32 data_020c8ed4[VILLAGER_MOOD_COUNT];
extern const s32 data_020c8ee8[VILLAGER_MOOD_COUNT];
/* The motions' last word (scene_motion_kinds.h). */
extern u16 data_020c80f8;
extern NetSession *data_020ccf94;

/* The effects as member pointers: the null one, the three runs, and the table of the starts
 * (VillagerMood_StartEffect) with its guard and the constants it is filled from. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_020d8f80; /* VillagerMood_RunEffect3 */
extern const MemberPointer data_020d92d0; /* VillagerMood_RunEffect2 */
extern const MemberPointer data_020d9340; /* VillagerMood_RunEffect1 */
extern u32 data_021c1cf0;
extern MemberPointer data_021c1dec[VILLAGER_MOOD_EFFECTS];
extern const MemberPointer data_020d9328; /* VillagerMood_StartEffect1 */
extern const MemberPointer data_020d8ef0; /* VillagerMood_StartEffect2 */
extern const MemberPointer data_020d9010; /* VillagerMood_StartEffect3 */
extern const MemberPointer data_020d9098; /* VillagerMood_StartEffect2 */

/* Spawns effect `effect` at `point` turned by `angle`. */
extern int func_020912d4(int effect, Vec3 *point, s16 *angle, int a);

static u8 *villager_mood_at(u8 *villager, u32 offset)
{
    return villager + offset;
}

static SoundEmitter *villager_mood_emitter(VillagerMood *mood)
{
    return (SoundEmitter *) (void *) mood;
}

static SpeakerAnim *villager_mood_anim(u8 *villager)
{
    return (SpeakerAnim *) (void *) villager_mood_at(villager, VILLAGER_MOOD_ANIM);
}

/* The animation the villager plays. */
static int villager_mood_animation(u8 *villager)
{
    return SpeakerAnim_Number(villager_mood_anim(villager), 0);
}

static int villager_mood_others_share(void)
{
    return Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0;
}

/* The villager's vtable slot `slot`, called with the villager. */
static int villager_mood_call_slot(u8 *villager, u32 slot)
{
    const u8 *vtable = *(const u8 *const *) (const void *) villager;
    u32 code = *(const u32 *) (const void *) (vtable + slot);
    return ((int (*)(void *))(uintptr_t) code)(villager);
}

/* ---- The update */

/* func_0201c6d0: the update while the member is on, with the villager's running state (its
 * entry and mood are read first) and unless others share the session (villager_mood.h): the
 * mood ends while the villager's action is busy; else a mood waiting to be taken on is (a
 * mood below 5: lengthening the villager's mood when it is the same, else replacing it), the
 * counter runs down and the mood ends when it is out. The villager's standard animations are
 * the mood's; a villager that plays an animation other than its first standard one, while that
 * animation is one of the moods' first ones, is asked for the standing motion at the priority
 * of its motion. Then the effects run, the mood is kept as shown and the emitter follows the
 * villager. */
void VillagerMood_Update(VillagerMood *mood, u8 *villager)
{
    VillagerState *entry =
        VillagerStatus_StateEntry(*(u8 **) (void *) villager_mood_at(villager, VILLAGER_MOOD_TOWN_VILLAGER));
    int shown = VillagerState_GetByte18(entry);

    if (VillagerMood_IsOn(mood) == 0) {
        return;
    }
    if (villager_mood_others_share()) {
        return;
    }

    if (SceneAction_IsBusy((const SceneAction *) (const void *) villager_mood_at(villager, VILLAGER_MOOD_ACTION)) != 0) {
        shown = VILLAGER_MOOD_NONE;
        VillagerMood_ShowAnimations(mood, villager, shown);
    } else {
        if (mood->apply != 0) {
            if (mood->asked < VILLAGER_MOOD_COUNT) {
                if (shown != VILLAGER_MOOD_NONE && shown == mood->asked) {
                    VillagerState_AddCounter(entry, mood->asked_frames);
                } else {
                    VillagerState_SetCounter(entry, mood->asked_frames);
                }
                VillagerState_SetByte18(entry, mood->asked);
                shown = mood->asked;
            }
            mood->apply = 0;
            VillagerMood_ClearAsked(mood);
        }
        VillagerState_CountDown(entry);
        if (shown != VILLAGER_MOOD_NONE && VillagerState_GetCounter(entry) == 0) {
            shown = VILLAGER_MOOD_NONE;
            VillagerState_SetByte18(entry, shown);
        }
        VillagerMood_ShowAnimations(mood, villager, shown);
    }

    int playing = villager_mood_animation(villager);
    if (playing !=
        SpeakerAnim_Resolve(villager_mood_anim(villager), 0, villager_mood_at(villager, VILLAGER_MOOD_STANDARD_ANIMS))) {
        if (VillagerMood_IsFirstAnimation(mood, villager) != 0) {
            SceneMotion *motion = (SceneMotion *) (void *) villager_mood_at(villager, VILLAGER_MOOD_MOTION);
            SceneMotion_Request(motion, 0, motion->priority, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    VillagerMood_UpdateEffect(mood, villager, shown);
    mood->shown = (u8) shown;
    VillagerMood_FollowVillager(mood, villager);
}
CLEAN_AS(func_0201c6d0, VillagerMood_Update)

/* ---- The effects */

/* A call through the effect's member pointer with the villager. */
static void villager_mood_run(const MemberPointer *effect, VillagerMood *mood, u8 *villager)
{
    void *target = MemberPointer_Object(effect, mood);
    ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(effect, target))(target, villager);
}

/* func_0201c828: the effect of mood `shown`. A running effect of another mood is dropped.
 * Without one, the effect fitting the animation the villager plays and the mood is started:
 * effect 1 for mood 1 with animation 0xe5 or 0xe6, effect 2 for moods 2 and 4 with 0xe7 or
 * 0xe8, effect 3 for moods 3 and 4 with 0xe9 or 0xea. The effect there is then run. */
void VillagerMood_UpdateEffect(VillagerMood *mood, u8 *villager, int shown)
{
    if (shown != mood->effect_mood && mood->effect_mood != VILLAGER_MOOD_UNSET) {
        mood->effect = __ptmf_null;
        mood->effect_mood = VILLAGER_MOOD_UNSET;
    } else if (mood->effect.function == 0) {
        unsigned int which = 0;
        switch (villager_mood_animation(villager) - VILLAGER_MOOD_FIRST_ANIMATION) {
            case 0:
            case 1:
                if (shown == 1) {
                    which = VILLAGER_MOOD_EFFECT_1;
                }
                break;
            case 2:
            case 3:
                if (shown == 2 || shown == 4) {
                    which = VILLAGER_MOOD_EFFECT_2;
                }
                break;
            case 4:
            case 5:
                /* QUIRK: the mood is compared by its low 8 bits. */
                if ((u8) (shown - 3) <= 1) {
                    which = VILLAGER_MOOD_EFFECT_3;
                }
                break;
            default:
                break;
        }
        if (which != 0 && VillagerMood_StartEffect(mood, villager, which) != 0) {
            mood->effect_mood = shown;
        }
    }
    if (mood->effect.function != 0) {
        villager_mood_run(&mood->effect, mood, villager);
    }
}
CLEAN_AS(func_0201c828, VillagerMood_UpdateEffect)

/* func_0201c8fc: starts effect `which` (1 to 4) through the table of starts, filled once; 1
 * when the start agreed, 0 for no start (0 and from 5). */
int VillagerMood_StartEffect(VillagerMood *mood, u8 *villager, unsigned int which)
{
    static const MemberPointer *const starts[VILLAGER_MOOD_EFFECTS] = {
        &__ptmf_null, &data_020d9328, &data_020d8ef0, &data_020d9010, &data_020d9098,
    };
    MemberTable_InitOnce(&data_021c1cf0, data_021c1dec, starts, VILLAGER_MOOD_EFFECTS);
    if (which < VILLAGER_MOOD_EFFECTS && data_021c1dec[which].function != 0) {
        const MemberPointer *start = &data_021c1dec[which];
        void *target = MemberPointer_Object(start, mood);
        if (((int (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(start, target))(target, villager) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0201c8fc, VillagerMood_StartEffect)

/* func_0201c9a4: whether the villager plays one of the moods' first standard animations. */
int VillagerMood_IsFirstAnimation(VillagerMood *mood, u8 *villager)
{
    (void) mood;
    int playing = villager_mood_animation(villager);
    for (int i = 0; i < VILLAGER_MOOD_COUNT; i++) {
        if (playing == data_020c8ed4[i]) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0201c9a4, VillagerMood_IsFirstAnimation)

/* func_0201c9dc: effect 3's run: while the villager plays a mood's animation, it plays at the
 * start of each cycle of 14 frames. */
void VillagerMood_RunEffect3(VillagerMood *mood, u8 *villager)
{
    if (VillagerMood_IsMoodAnimation(mood, villager) == 0) {
        return;
    }
    if (mood->frame == 0) {
        VillagerMood_PlayEffect3(mood, villager);
    }
    mood->frame++;
    if (mood->frame >= VILLAGER_MOOD_CYCLE_3) {
        mood->frame = 0;
    }
}
CLEAN_AS(func_0201c9dc, VillagerMood_RunEffect3)

/* func_0201ca24: effect 3's start: its run from frame 0. Returns 1. */
int VillagerMood_StartEffect3(VillagerMood *mood, u8 *villager)
{
    (void) villager;
    mood->frame = 0;
    mood->effect = data_020d8f80;
    return 1;
}
CLEAN_AS(func_0201ca24, VillagerMood_StartEffect3)

/* func_0201ca40: effect 0x62 with sound 0x7f. */
void VillagerMood_PlayEffect3(VillagerMood *mood, u8 *villager)
{
    VillagerMood_PlayEffect(mood, villager, 0x62, 0x7f);
}
CLEAN_AS(func_0201ca40, VillagerMood_PlayEffect3)

/* func_0201ca54: effect 2's run: as effect 3's, with a cycle of 20 frames. */
void VillagerMood_RunEffect2(VillagerMood *mood, u8 *villager)
{
    if (VillagerMood_IsMoodAnimation(mood, villager) == 0) {
        return;
    }
    if (mood->frame == 0) {
        VillagerMood_PlayEffect2(mood, villager);
    }
    mood->frame++;
    if (mood->frame >= VILLAGER_MOOD_CYCLE_2) {
        mood->frame = 0;
    }
}
CLEAN_AS(func_0201ca54, VillagerMood_RunEffect2)

/* func_0201ca9c: effect 2's start. Returns 1. */
int VillagerMood_StartEffect2(VillagerMood *mood, u8 *villager)
{
    (void) villager;
    mood->frame = 0;
    mood->effect = data_020d92d0;
    return 1;
}
CLEAN_AS(func_0201ca9c, VillagerMood_StartEffect2)

/* func_0201cab8: effect 0x5c with sound 0x83. */
void VillagerMood_PlayEffect2(VillagerMood *mood, u8 *villager)
{
    VillagerMood_PlayEffect(mood, villager, 0x5c, 0x83);
}
CLEAN_AS(func_0201cab8, VillagerMood_PlayEffect2)

/* func_0201cacc: effect 1's run: while the villager plays a mood's animation, a cycle of 40
 * frames plays effect 0x5a at its start and 0x5b at frame 20. */
void VillagerMood_RunEffect1(VillagerMood *mood, u8 *villager)
{
    if (VillagerMood_IsMoodAnimation(mood, villager) == 0) {
        return;
    }
    if (mood->frame == 0) {
        VillagerMood_PlayEffect1A(mood, villager);
    } else if (mood->frame == VILLAGER_MOOD_CYCLE_1_SECOND) {
        VillagerMood_PlayEffect1B(mood, villager);
    }
    mood->frame++;
    if (mood->frame >= VILLAGER_MOOD_CYCLE_1) {
        mood->frame = 0;
    }
}
CLEAN_AS(func_0201cacc, VillagerMood_RunEffect1)

/* func_0201cb24: effect 1's start. Returns 1. */
int VillagerMood_StartEffect1(VillagerMood *mood, u8 *villager)
{
    (void) villager;
    mood->frame = 0;
    mood->effect = data_020d9340;
    return 1;
}
CLEAN_AS(func_0201cb24, VillagerMood_StartEffect1)

/* func_0201cb40: effect 0x5b with sound 0x7b; VillagerMood_PlayEffect's answer. */
int VillagerMood_PlayEffect1B(VillagerMood *mood, u8 *villager)
{
    return VillagerMood_PlayEffect(mood, villager, 0x5b, 0x7b);
}
CLEAN_AS(func_0201cb40, VillagerMood_PlayEffect1B)

/* func_0201cb54: effect 0x5a with sound 0x7b. */
void VillagerMood_PlayEffect1A(VillagerMood *mood, u8 *villager)
{
    VillagerMood_PlayEffect(mood, villager, 0x5a, 0x7b);
}
CLEAN_AS(func_0201cb54, VillagerMood_PlayEffect1A)

/* func_0201cb68: whether the villager plays one of the moods' standard animations, first or
 * second. */
int VillagerMood_IsMoodAnimation(VillagerMood *mood, u8 *villager)
{
    (void) mood;
    int playing = villager_mood_animation(villager);
    for (int i = 0; i < VILLAGER_MOOD_COUNT; i++) {
        if (playing == data_020c8ed4[i] || playing == data_020c8ee8[i]) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0201cb68, VillagerMood_IsMoodAnimation)

/* func_0201cbac */
int VillagerMood_SoundsOn(const VillagerMood *mood)
{
    return mood->sounds_on != 0;
}
CLEAN_AS(func_0201cbac, VillagerMood_SoundsOn)

/* func_0201cbbc */
void VillagerMood_SoundsOff(VillagerMood *mood)
{
    mood->sounds_on = 0;
}
CLEAN_AS(func_0201cbbc, VillagerMood_SoundsOff)

/* func_0201cbc4 */
void VillagerMood_SetSoundsOn(VillagerMood *mood)
{
    mood->sounds_on = 1;
}
CLEAN_AS(func_0201cbc4, VillagerMood_SetSoundsOn)

/* func_0201cbcc: the emitter's sounds follow a copy of the villager's position. */
void VillagerMood_FollowVillager(VillagerMood *mood, u8 *villager)
{
    Vec3 position = *(const Vec3 *) (const void *) villager_mood_at(villager, VILLAGER_MOOD_POSITION);
    SoundEmitter_UpdateAtB(villager_mood_emitter(mood), &position);
}
CLEAN_AS(func_0201cbcc, VillagerMood_FollowVillager)

/* func_0201cbec: with the sounds on, plays sound `sound` on the emitter at full volume and
 * spawns effect `effect` at a copy of the villager's joint 16 point turned as the villager
 * faces; the effect's handle. 0 with the sounds off. */
int VillagerMood_PlayEffect(VillagerMood *mood, u8 *villager, int effect, int sound)
{
    if (VillagerMood_SoundsOn(mood) == 0) {
        return 0;
    }
    Vec3 point = *(const Vec3 *) (const void *) villager_mood_at(villager, VILLAGER_MOOD_JOINT_16_POINT);
    s16 angle = *(const s16 *) (const void *) villager_mood_at(villager, VILLAGER_MOOD_ANGLE);
    SoundEmitter_PlayB(villager_mood_emitter(mood), sound, VILLAGER_MOOD_VOLUME, 0);
    return func_020912d4(effect, &point, &angle, 0);
}
CLEAN_AS(func_0201cbec, VillagerMood_PlayEffect)

/* ---- Asking for a mood */

/* func_0201cc48: the mood asked for is taken on at the next update, unless others share the
 * session. */
void VillagerMood_Apply(VillagerMood *mood)
{
    if (!villager_mood_others_share()) {
        mood->apply = 1;
    }
}
CLEAN_AS(func_0201cc48, VillagerMood_Apply)

/* func_0201cc6c: asks for mood `which` (below 5) for `units` times 1200 frames, added to the
 * length when it is the mood already asked for; nothing while others share the session.
 * QUIRK: the length is kept in 16 bits, the sum too. */
void VillagerMood_Ask(VillagerMood *mood, unsigned int which, unsigned int units)
{
    if (villager_mood_others_share() || which >= VILLAGER_MOOD_COUNT) {
        return;
    }
    u16 frames = (u16) (units * VILLAGER_MOOD_UNIT_FRAMES);
    if (which == mood->asked) {
        mood->asked_frames = (u16) (mood->asked_frames + frames);
    } else {
        mood->asked = (u8) which;
        mood->asked_frames = frames;
    }
}
CLEAN_AS(func_0201cc6c, VillagerMood_Ask)

/* func_0201ccc0: no mood asked for. */
void VillagerMood_ClearAsked(VillagerMood *mood)
{
    mood->asked = VILLAGER_MOOD_UNSET;
    mood->asked_frames = 0;
}
CLEAN_AS(func_0201ccc0, VillagerMood_ClearAsked)

/* func_0201ccd0: the villager's first and second standard animations are mood `shown`'s
 * (data_020c8ed4, data_020c8ee8); mood 4, for a villager with a record (vtable slot 0x64),
 * shows mood 3's for the personalities 0 and 3 and mood 2's for the others. The record is
 * asked for whatever the mood.
 * REQUIRES: `shown` is below 5 (the ROM reads past the tables for others; the running state's
 * mood 5, as VillagerState_Init sets it, has a counter of 0 and ends before it is shown). */
void VillagerMood_ShowAnimations(VillagerMood *mood, u8 *villager, int shown)
{
    (void) mood;
    int record = villager_mood_call_slot(villager, VILLAGER_MOOD_SLOT_RECORD);
    if (shown == VILLAGER_MOOD_BY_PERSONALITY && record != 0) {
        int personality = NpcId_Personality(TownVillager_NpcId((u8 *) (uintptr_t) record));
        shown = (personality == 0 || personality == 3) ? VILLAGER_MOOD_3 : VILLAGER_MOOD_2;
    }
    SceneStandardAnims *anims = (SceneStandardAnims *) (void *) villager_mood_at(villager, VILLAGER_MOOD_STANDARD_ANIMS);
    SceneStandardAnims_SetFirst(anims, data_020c8ed4[shown]);
    SceneStandardAnims_SetSecond(anims, data_020c8ee8[shown]);
}
CLEAN_AS(func_0201ccd0, VillagerMood_ShowAnimations)

/* ---- Its life */

/* func_0201cd2c */
int VillagerMood_IsOn(const VillagerMood *mood)
{
    return mood->on != 0;
}
CLEAN_AS(func_0201cd2c, VillagerMood_IsOn)

/* func_0201cd3c: when on, the emitter is finished (its slot 4); the member is off. Returns 0. */
int VillagerMood_Stop(VillagerMood *mood)
{
    if (VillagerMood_IsOn(mood) != 0) {
        SoundEmitter_Vfunc10B(villager_mood_emitter(mood));
    }
    mood->on = 0;
    return 0;
}
CLEAN_AS(func_0201cd3c, VillagerMood_Stop)

/* func_0201cd5c: reset (VillagerMood_Reset), the emitter set up (its slot 2), the sounds and
 * the member on. */
void VillagerMood_Start(VillagerMood *mood)
{
    VillagerMood_Reset(mood);
    SoundEmitter_StopB(villager_mood_emitter(mood));
    mood->sounds_on = 1;
    mood->on = 1;
}
CLEAN_AS(func_0201cd5c, VillagerMood_Start)

/* func_0201cd7c: off, no mood shown, asked for or with an effect, the sounds off. */
void VillagerMood_Reset(VillagerMood *mood)
{
    mood->on = 0;
    mood->shown = VILLAGER_MOOD_UNSET;
    mood->effect_mood = VILLAGER_MOOD_UNSET;
    mood->frame = 0;
    mood->effect = __ptmf_null;
    VillagerMood_ClearAsked(mood);
    mood->apply = 0;
    mood->sounds_on = 0;
}
CLEAN_AS(func_0201cd7c, VillagerMood_Reset)

/* func_0201cdbc: the destructor: the emitter's base class's. Returns the member. */
void *VillagerMood_Destruct(VillagerMood *mood)
{
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) (void *) mood);
    return mood;
}
CLEAN_AS(func_0201cdbc, VillagerMood_Destruct)

/* func_0201cdcc: the constructor: the emitter's base class's. Returns the member (its
 * address). */
int VillagerMood_Construct(VillagerMood *mood)
{
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) (void *) mood);
    return (int) (uintptr_t) mood;
}
CLEAN_AS(func_0201cdcc, VillagerMood_Construct)
