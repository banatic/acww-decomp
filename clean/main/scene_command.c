/* The commands a scene carries out one at a time (scene_command.h).
 *
 * REQUIRES: the scene and its talk at word-aligned addresses, as every object of the game is
 * (the ARM9 writes an aligned word at a misaligned address). */
#include "scene_command.h"

#include <string.h>

#include "clean.h"
#include "group_params.h"
#include "ov004/member_pointer.h"
#include "pockets.h"
#include "scene_talk.h"
#include "scene_base.h"
#include "scene_motion_request.h"
#include "talk_object.h"
#include "town_tune.h"

static_assert(offsetof(SceneCommandParams, pocket_predicate) == 0x10, "SceneCommandParams layout");
static_assert(offsetof(SceneCommandParams, sound_values) == 0x24, "SceneCommandParams layout");
static_assert(offsetof(SceneCommandParams, talk_mode) == 0x40, "SceneCommandParams layout");
static_assert(sizeof(SceneCommandParams) == 0x44, "SceneCommandParams layout");
static_assert(offsetof(SceneCommandScene, talk) == 0x40, "SceneCommandScene layout");
static_assert(offsetof(SceneCommandScene, speakers) == 0x4c, "SceneCommandScene layout");
static_assert(offsetof(SceneCommandScene, unk_60) == 0x60, "SceneCommandScene layout");
static_assert(offsetof(SceneCommandScene, command) == 0x64, "SceneCommandScene layout");
static_assert(offsetof(SceneCommandScene, params) == 0x68, "SceneCommandScene layout");
static_assert(offsetof(SceneCommandScene, state) == 0xac, "SceneCommandScene layout");
static_assert(offsetof(SceneCommandScene, busy) == 0xad, "SceneCommandScene layout");

/* The talk's words used here (scene_talk.h). */
#define SCENE_COMMAND_TALK_STATE 4
#define SCENE_COMMAND_TALK_NEXT 8
#define SCENE_COMMAND_TALK_MODE_WORD 0x14
#define SCENE_COMMAND_LINE_SHOWN 5

/* The first speaker's motion, and the kind of motion a talking speaker has (scene_action.h). */
#define SCENE_COMMAND_SPEAKER_MOTION 0x564
#define SCENE_COMMAND_MOTION_TALK 8
/* The priority every command sets a motion with. */
#define SCENE_COMMAND_PRIORITY 4

/* The speaker's vtable slot giving its sound (scene_action.h), and the answer for none. */
#define SCENE_COMMAND_SLOT_SOUND 0x84
#define SCENE_COMMAND_NO_SOUND 0xffff

/* The scene's vtable slots: one given 0 while the speaker still talks before commands 3 and 4
 * (func_02016014 by default), and the one told the number of the command that ended
 * (SceneCommand_Ended by default). */
#define SCENE_COMMAND_SLOT_SPEAKER_TALKS 0x38
#define SCENE_COMMAND_SLOT_ENDED 0x84

/* What the sound set gives while nothing plays (data_020df2a0, set each frame by
 * func_0206e8d8). */
#define SCENE_COMMAND_SOUND_IDLE (-1)

/* The commands (filled at start-up from constants), and each command's table of steps: a
 * guard word, the table and the constants it is filled from. */
extern u32 data_021c1524;
extern MemberPointer data_021c1814[];
extern const MemberPointer data_020d881c, data_020d8844, data_020d86cc, data_020d88c4, data_020d8904, data_020d8934,
    data_020d893c, data_020d8954, data_020d896c, data_020d8974, data_020d8984, data_020d8994;
extern u32 data_021c14fc;
extern MemberPointer data_021c166c[];
extern const MemberPointer data_020d862c, data_020d8624, data_020d861c;
extern u32 data_021c1500;
extern MemberPointer data_021c161c[];
extern const MemberPointer data_020d85ac, data_020d863c;
extern u32 data_021c14e8;
extern MemberPointer data_021c160c[];
extern const MemberPointer data_020d858c, data_020d8654;
extern u32 data_021c14dc;
extern MemberPointer data_021c15fc[];
extern const MemberPointer data_020d8574, data_020d866c;
extern u32 data_021c1518;
extern MemberPointer data_021c15ec[];
extern const MemberPointer data_020d8694, data_020d868c;
extern u32 data_021c14e0;
extern MemberPointer data_021c15dc[];
extern const MemberPointer data_020d8a5c, data_020d8a4c;
extern u32 data_021c14e4;
extern MemberPointer data_021c15bc[];
extern const MemberPointer data_020d8b24, data_020d8a94;
extern u32 data_021c1544;
extern MemberPointer data_021c165c[];
extern const MemberPointer data_020d8a44, data_020d8a74;
extern u32 data_021c152c;
extern MemberPointer data_021c164c[];
extern const MemberPointer data_020d8a0c, data_020d8a24;
extern u32 data_021c1540;
extern MemberPointer data_021c1714[];
extern const MemberPointer data_020d89cc, data_020d89e4, data_020d89ec;

extern u16 data_020c80f8;
extern s32 data_020df2a0;  /* the sound set's state, SCENE_COMMAND_SOUND_IDLE while nothing plays */
extern u8 data_021cfbbc[]; /* the sixteen values the sound set plays a sound with */

static u32 scene_command_slot(const void *object, u32 slot)
{
    const u8 *vtable = *(const u8 *const *) object;
    return *(const u32 *) (vtable + slot);
}

static void *scene_command_motion(const SceneCommandScene *scene)
{
    return scene->speakers[0] + SCENE_COMMAND_SPEAKER_MOTION;
}

/* Whether the first speaker's motion, with a talk held, is the given kind and done. */
static int scene_command_motion_done(const SceneCommandScene *scene, int kind)
{
    return scene->speakers[0] != NULL && scene->talk != NULL && SceneMotion_Kind(scene_command_motion(scene)) == kind &&
           SceneMotion_IsDone(scene_command_motion(scene)) != 0;
}

/* Whether the first speaker, with a talk, took the motion of the given kind. */
static int scene_command_set_motion(const SceneCommandScene *scene, int kind)
{
    return scene->speakers[0] != NULL && scene->talk != NULL &&
           SceneMotion_Request(scene_command_motion(scene), kind, SCENE_COMMAND_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8,
                               0) != 0;
}

static int scene_command_run_steps(SceneCommandScene *scene, u32 *guard, MemberPointer *table,
                                   const MemberPointer *const *steps, int count)
{
    MemberTable_InitOnce(guard, table, steps, count);
    u8 state = scene->state;
    if (state < count) {
        return MemberPointer_CallInt(&table[state], scene);
    }
    return 0;
}

/* _ZN12Obj_020d8bd413func_02014a68Ev (command 10): the step's function; its answer, 0 from step
 * 3 on. */
int SceneCommand_RunSound(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d862c, /* SceneCommand_SoundStart */
        &data_020d8624, /* SceneCommand_SoundWaitStart */
        &data_020d861c, /* SceneCommand_SoundEnd */
    };
    return scene_command_run_steps(scene, &data_021c14fc, data_021c166c, steps, 3);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02014a68Ev, SceneCommand_RunSound)

/* func_02014ae8 (command 10, step 2): once the sound set plays nothing, the talk is let go and
 * the step is 3. Whether the command is finished. */
int SceneCommand_SoundEnd(SceneCommandScene *scene)
{
    if (data_020df2a0 != SCENE_COMMAND_SOUND_IDLE) {
        return 0;
    }
    if (scene->talk != NULL) {
        TalkObject_Release((TalkObject *) scene->talk);
    }
    scene->state = 3;
    return 1;
}
CLEAN_AS(func_02014ae8, SceneCommand_SoundEnd)

/* func_02014b14 (command 10, step 1): once the sound set plays, the step is 2. The answer is 0. */
int SceneCommand_SoundWaitStart(SceneCommandScene *scene)
{
    if (data_020df2a0 != SCENE_COMMAND_SOUND_IDLE) {
        scene->state = 2;
    }
    return 0;
}
CLEAN_AS(func_02014b14, SceneCommand_SoundWaitStart)

/* func_02014b30 (command 10, step 0): the first speaker's sound (its vtable slot 0x84). With
 * none (0xffff) the command is finished at step 3. Else the talk is held, the sound set plays
 * it (with the sixteen values unpacked into data_021cfbbc, or by number alone when
 * `sound_without_values`) and the step is 1.
 * QUIRK: without a first speaker the sound is 0, which is played. */
int SceneCommand_SoundStart(SceneCommandScene *scene)
{
    typedef int (*SceneCommandSound)(void *speaker);

    int sound = 0;
    if (scene->speakers[0] != NULL) {
        u32 get_sound = scene_command_slot(scene->speakers[0], SCENE_COMMAND_SLOT_SOUND);
        sound = ((SceneCommandSound) (uintptr_t) get_sound)(scene->speakers[0]);
    }
    if (sound == SCENE_COMMAND_NO_SOUND) {
        scene->state = 3;
        return 1;
    }
    if (scene->talk != NULL) {
        TalkObject_Hold((TalkObject *) scene->talk);
    }
    if (scene->params.sound_without_values == 0) {
        TownTune_Unpack((const TownTunePacked *) scene->params.sound_values, data_021cfbbc);
        TownTune_Play((u16) sound);
    } else {
        TownTune_PlayRandomPreset((u16) sound);
    }
    scene->state = 1;
    return 0;
}
CLEAN_AS(func_02014b30, SceneCommand_SoundStart)

/* func_02014ba0: asks for the first speaker's sound, played by number alone. Whether the scene
 * took it. */
int SceneCommand_RequestSound(SceneCommandScene *scene)
{
    if (SceneCommand_Request(scene, SCENE_COMMAND_SOUND)) {
        scene->params.sound_without_values = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02014ba0, SceneCommand_RequestSound)

/* func_02014bc0: asks for the first speaker's sound, played with the sixteen 4-bit values packed
 * in the two words at `values`. Whether the scene took it. */
int SceneCommand_RequestSoundWith(SceneCommandScene *scene, const u32 *values)
{
    if (SceneCommand_Request(scene, SCENE_COMMAND_SOUND) != 0) {
        memcpy(scene->params.sound_values, values, sizeof(scene->params.sound_values));
        scene->params.sound_without_values = 0;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02014bc0, SceneCommand_RequestSoundWith)

/* _ZN12Obj_020d8bd413func_02014bf0Ev (command 9): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunMotion19(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d85ac, /* SceneCommand_StartMotion19 */
        &data_020d863c, /* SceneCommand_WaitMotion19 */
    };
    return scene_command_run_steps(scene, &data_021c1500, data_021c161c, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02014bf0Ev, SceneCommand_RunMotion19)

/* func_02014c60 (command 9, step 1): once the motion of kind 19 is done, the talk is let go, the
 * scene's byte 0x60 cleared and the step is 2. Whether the command is finished. */
int SceneCommand_WaitMotion19(SceneCommandScene *scene)
{
    if (!scene_command_motion_done(scene, 19)) {
        return 0;
    }
    TalkObject_Release((TalkObject *) scene->talk);
    SceneBase_ClearHolding((SceneBase *) scene);
    scene->state = 2;
    return 1;
}
CLEAN_AS(func_02014c60, SceneCommand_WaitMotion19)

/* func_02014cb0 (command 9, step 0): once the first speaker takes the motion of kind 19, the
 * talk is held and the step is 1. The answer is 0. */
int SceneCommand_StartMotion19(SceneCommandScene *scene)
{
    if (scene_command_set_motion(scene, 19)) {
        TalkObject_Hold((TalkObject *) scene->talk);
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_02014cb0, SceneCommand_StartMotion19)

/* func_02014d04: asks for the motion of kind 19. Whether the scene took it. */
int SceneCommand_RequestMotion19(SceneCommandScene *scene)
{
    return SceneCommand_Request(scene, SCENE_COMMAND_MOTION_19) ? 1 : 0;
}
CLEAN_AS(func_02014d04, SceneCommand_RequestMotion19)

/* _ZN12Obj_020d8bd413func_02014d1cEv (command 8): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunMotion18(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d858c, /* SceneCommand_StartMotion18 */
        &data_020d8654, /* SceneCommand_WaitMotion18 */
    };
    return scene_command_run_steps(scene, &data_021c14e8, data_021c160c, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02014d1cEv, SceneCommand_RunMotion18)

/* func_02014d8c (command 8, step 1): once the motion of kind 18 is done, the talk is let go and
 * the step is 2 (the scene's byte 0x60 is left as it is). Whether the command is finished. */
int SceneCommand_WaitMotion18(SceneCommandScene *scene)
{
    if (!scene_command_motion_done(scene, 18)) {
        return 0;
    }
    TalkObject_Release((TalkObject *) scene->talk);
    scene->state = 2;
    return 1;
}
CLEAN_AS(func_02014d8c, SceneCommand_WaitMotion18)

/* func_02014dd8 (command 8, step 0): once the first speaker takes the motion of kind 18, the
 * talk is held and the step is 1. The answer is 0. */
int SceneCommand_StartMotion18(SceneCommandScene *scene)
{
    if (scene_command_set_motion(scene, 18)) {
        TalkObject_Hold((TalkObject *) scene->talk);
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_02014dd8, SceneCommand_StartMotion18)

/* func_02014e2c: asks for the motion of kind 18. Whether the scene took it. */
int SceneCommand_RequestMotion18(SceneCommandScene *scene)
{
    return SceneCommand_Request(scene, SCENE_COMMAND_MOTION_18) ? 1 : 0;
}
CLEAN_AS(func_02014e2c, SceneCommand_RequestMotion18)

/* _ZN12Obj_020d8bd413func_02014e44Ev (command 7): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunMotion17(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d8574, /* SceneCommand_StartMotion17 */
        &data_020d866c, /* SceneCommand_WaitMotion17 */
    };
    return scene_command_run_steps(scene, &data_021c14dc, data_021c15fc, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02014e44Ev, SceneCommand_RunMotion17)

/* func_02014eb4 (command 7, step 1): once the motion of kind 17 is done, the talk is let go, the
 * scene's byte 0x60 cleared and the step is 2. Whether the command is finished. */
int SceneCommand_WaitMotion17(SceneCommandScene *scene)
{
    if (!scene_command_motion_done(scene, 17)) {
        return 0;
    }
    TalkObject_Release((TalkObject *) scene->talk);
    SceneBase_ClearHolding((SceneBase *) scene);
    scene->state = 2;
    return 1;
}
CLEAN_AS(func_02014eb4, SceneCommand_WaitMotion17)

/* func_02014f04 (command 7, step 0): once the first speaker takes the motion of kind 17, the
 * scene's byte 0x60 is set, the talk held and the step is 1. The answer is 0. */
int SceneCommand_StartMotion17(SceneCommandScene *scene)
{
    if (scene_command_set_motion(scene, 17)) {
        SceneBase_SetHolding((SceneBase *) scene);
        TalkObject_Hold((TalkObject *) scene->talk);
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_02014f04, SceneCommand_StartMotion17)

/* func_02014f60: asks for the motion of kind 17. Whether the scene took it. */
int SceneCommand_RequestMotion17(SceneCommandScene *scene)
{
    return SceneCommand_Request(scene, SCENE_COMMAND_MOTION_17) ? 1 : 0;
}
CLEAN_AS(func_02014f60, SceneCommand_RequestMotion17)

/* _ZN12Obj_020d8bd413func_02014f78Ev (command 6): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunMotion16(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d8694, /* SceneCommand_StartMotion16 */
        &data_020d868c, /* SceneCommand_WaitMotion16 */
    };
    return scene_command_run_steps(scene, &data_021c1518, data_021c15ec, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02014f78Ev, SceneCommand_RunMotion16)

/* func_02014fe8 (command 6, step 1): once the motion of kind 16 is done, the talk is let go, the
 * scene's byte 0x60 cleared and the step is 2. Whether the command is finished. */
int SceneCommand_WaitMotion16(SceneCommandScene *scene)
{
    if (!scene_command_motion_done(scene, 16)) {
        return 0;
    }
    TalkObject_Release((TalkObject *) scene->talk);
    SceneBase_ClearHolding((SceneBase *) scene);
    scene->state = 2;
    return 1;
}
CLEAN_AS(func_02014fe8, SceneCommand_WaitMotion16)

/* func_02015038 (command 6, step 0): once the first speaker takes the motion of kind 16, the
 * scene's byte 0x60 is set, the talk held and the step is 1. The answer is 0. */
int SceneCommand_StartMotion16(SceneCommandScene *scene)
{
    if (scene_command_set_motion(scene, 16)) {
        SceneBase_SetHolding((SceneBase *) scene);
        TalkObject_Hold((TalkObject *) scene->talk);
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_02015038, SceneCommand_StartMotion16)

/* func_02015094: asks for the motion of kind 16. Whether the scene took it. */
int SceneCommand_RequestMotion16(SceneCommandScene *scene)
{
    return SceneCommand_Request(scene, SCENE_COMMAND_MOTION_16) ? 1 : 0;
}
CLEAN_AS(func_02015094, SceneCommand_RequestMotion16)

/* _ZN12Obj_020d8bd413func_020150acEv (command 5): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunMotion15(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d8a5c, /* SceneCommand_StartMotion15 */
        &data_020d8a4c, /* SceneCommand_WaitMotion15 */
    };
    return scene_command_run_steps(scene, &data_021c14e0, data_021c15dc, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020150acEv, SceneCommand_RunMotion15)

/* func_0201511c (command 5, step 1): once the motion of kind 15 is done, the talk is let go, the
 * scene's byte 0x60 cleared and the step is 2. Whether the command is finished. */
int SceneCommand_WaitMotion15(SceneCommandScene *scene)
{
    if (!scene_command_motion_done(scene, 15)) {
        return 0;
    }
    TalkObject_Release((TalkObject *) scene->talk);
    SceneBase_ClearHolding((SceneBase *) scene);
    scene->state = 2;
    return 1;
}
CLEAN_AS(func_0201511c, SceneCommand_WaitMotion15)

/* func_0201516c (command 5, step 0): once the first speaker takes the motion of kind 15, the
 * talk is held and the step is 1. The answer is 0. */
int SceneCommand_StartMotion15(SceneCommandScene *scene)
{
    if (scene_command_set_motion(scene, 15)) {
        TalkObject_Hold((TalkObject *) scene->talk);
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_0201516c, SceneCommand_StartMotion15)

/* func_020151c0: asks for the motion of kind 15. Whether the scene took it. */
int SceneCommand_RequestMotion15(SceneCommandScene *scene)
{
    return SceneCommand_Request(scene, SCENE_COMMAND_MOTION_15) ? 1 : 0;
}
CLEAN_AS(func_020151c0, SceneCommand_RequestMotion15)

/* _ZN12Obj_020d8bd413func_020151d8Ev (command 4): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunMotion14(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d8b24, /* SceneCommand_StartMotion14 */
        &data_020d8a94, /* SceneCommand_WaitMotion14 */
    };
    return scene_command_run_steps(scene, &data_021c14e4, data_021c15bc, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020151d8Ev, SceneCommand_RunMotion14)

/* func_02015248 (command 4, step 1): once the motion of kind 14 is done, the talk is let go, the
 * scene's byte 0x60 cleared unless `motion_b` is 4, and the step is 2. Whether the command is
 * finished. */
int SceneCommand_WaitMotion14(SceneCommandScene *scene)
{
    if (!scene_command_motion_done(scene, 14)) {
        return 0;
    }
    TalkObject_Release((TalkObject *) scene->talk);
    if (scene->params.motion_b != 4) {
        SceneBase_ClearHolding((SceneBase *) scene);
    }
    scene->state = 2;
    return 1;
}
CLEAN_AS(func_02015248, SceneCommand_WaitMotion14)

/* Step 0 of commands 3 and 4, before the motion: with a first speaker, the talk is held; while
 * the speaker still talks (its motion of kind 8 is not done) the scene's vtable slot 0x38 is
 * given 0. Whether the speaker can be given the motion with the item now (it has stopped
 * talking and there is a talk). */
static int scene_command_item_motion_ready(SceneCommandScene *scene)
{
    typedef int (*SceneCommandSpeakerTalks)(void *scene, int a);

    if (scene->speakers[0] == NULL) {
        return 0;
    }
    if (scene->talk != NULL) {
        TalkObject_Hold((TalkObject *) scene->talk);
    }
    if (SceneMotion_Kind(scene_command_motion(scene)) == SCENE_COMMAND_MOTION_TALK &&
        SceneMotion_IsDone(scene_command_motion(scene)) == 0) {
        u32 speaker_talks = scene_command_slot(scene, SCENE_COMMAND_SLOT_SPEAKER_TALKS);
        ((SceneCommandSpeakerTalks) (uintptr_t) speaker_talks)(scene, 0);
        return 0;
    }
    return scene->talk != NULL;
}

/* func_020152a4 (command 4, step 0): once the first speaker takes the motion of kind 14 with the
 * item (after scene_command_item_motion_ready), the scene's byte 0x60 is set and the step is 1. The
 * answer is 0. */
int SceneCommand_StartMotion14(SceneCommandScene *scene)
{
    if (scene_command_item_motion_ready(scene) &&
        SceneMotion_RequestKind14(scene_command_motion(scene), SCENE_COMMAND_PRIORITY, &scene->params.item,
                                  (int) scene->params.motion_a, scene->params.motion_b, (int) scene->params.motion_c,
                                  scene->motion_d) != 0) {
        SceneBase_SetHolding((SceneBase *) scene);
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_020152a4, SceneCommand_StartMotion14)

/* func_02015330: asks for the motion of kind 14 with the item at `item` and its values. Whether
 * the scene took it. */
int SceneCommand_RequestMotion14(SceneCommandScene *scene, const u16 *item, u32 a, u8 b, u32 c)
{
    if (SceneCommand_Request(scene, SCENE_COMMAND_MOTION_14) == 0) {
        return 0;
    }
    scene->params.item = *item;
    scene->params.motion_a = a;
    scene->params.motion_b = b;
    scene->params.motion_c = c;
    return 1;
}
CLEAN_AS(func_02015330, SceneCommand_RequestMotion14)

/* _ZN12Obj_020d8bd413func_02015370Ev (command 3): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunMotion13(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d8a44, /* SceneCommand_StartMotion13 */
        &data_020d8a74, /* SceneCommand_WaitMotion13 */
    };
    return scene_command_run_steps(scene, &data_021c1544, data_021c165c, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02015370Ev, SceneCommand_RunMotion13)

/* func_020153e0 (command 3, step 1): once the motion of kind 13 is done, the talk is let go and
 * the step is 2. Whether the command is finished. */
int SceneCommand_WaitMotion13(SceneCommandScene *scene)
{
    if (!scene_command_motion_done(scene, 13)) {
        return 0;
    }
    TalkObject_Release((TalkObject *) scene->talk);
    scene->state = 2;
    return 1;
}
CLEAN_AS(func_020153e0, SceneCommand_WaitMotion13)

/* func_0201542c (command 3, step 0): once the first speaker takes the motion of kind 13 with the
 * item (after scene_command_item_motion_ready), the step is 1. The answer is 0. */
int SceneCommand_StartMotion13(SceneCommandScene *scene)
{
    if (scene_command_item_motion_ready(scene) &&
        SceneMotion_RequestKind13(scene_command_motion(scene), SCENE_COMMAND_PRIORITY, &scene->params.item,
                                  (int) scene->params.motion_a, scene->params.motion_b, (int) scene->params.motion_c,
                                  scene->motion_d) != 0) {
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_0201542c, SceneCommand_StartMotion13)

/* func_020154b4: asks for the motion of kind 13 with the item at `item` and its values. Whether
 * the scene took it. */
int SceneCommand_RequestMotion13(SceneCommandScene *scene, const u16 *item, u32 a, u8 b, u32 c)
{
    if (SceneCommand_Request(scene, SCENE_COMMAND_MOTION_13) == 0) {
        return 0;
    }
    scene->params.item = *item;
    scene->params.motion_a = a;
    scene->params.motion_b = b;
    scene->params.motion_c = c;
    return 1;
}
CLEAN_AS(func_020154b4, SceneCommand_RequestMotion13)

/* _ZN12Obj_020d8bd413func_020154f4Ev (command 2): the step's function; its answer, 0 from step
 * 2 on. */
int SceneCommand_RunTalkMode(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d8a0c, /* SceneCommand_SetTalkMode */
        &data_020d8a24, /* SceneCommand_LineShown */
    };
    return scene_command_run_steps(scene, &data_021c152c, data_021c164c, steps, 2);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020154f4Ev, SceneCommand_RunTalkMode)

/* func_02015564 (command 2, step 1): whether the talk's line is shown to its end (the command
 * is then finished). */
int SceneCommand_LineShown(SceneCommandScene *scene)
{
    const s32 *talk = scene->talk;
    return talk != NULL && talk[SCENE_COMMAND_TALK_STATE / 4] == SCENE_COMMAND_LINE_SHOWN;
}
CLEAN_AS(func_02015564, SceneCommand_LineShown)

/* func_02015578 (command 2, step 0): with a talk, its word 0x14 is `talk_mode` and the step is
 * 1. The answer is 0. */
int SceneCommand_SetTalkMode(SceneCommandScene *scene)
{
    s32 *talk = scene->talk;
    if (talk != NULL) {
        talk[SCENE_COMMAND_TALK_MODE_WORD / 4] = scene->params.talk_mode;
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_02015578, SceneCommand_SetTalkMode)

/* func_02015590: asks for the talk's word 0x14 to be `mode`. Whether the scene took it. */
int SceneCommand_RequestTalkMode(SceneCommandScene *scene, s32 mode)
{
    if (SceneCommand_Request(scene, SCENE_COMMAND_TALK_MODE) != 0) {
        scene->params.talk_mode = mode;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02015590, SceneCommand_RequestTalkMode)

/* func_020155b4 (command 1, its only step): once the talk's line is shown to its end, the next
 * line is asked for and the command is finished (the answer is 1, as an address).
 * QUIRK: the answer is declared as an address though it is only 0 or 1. */
void *SceneCommand_NextLine(SceneCommandScene *scene)
{
    s32 *talk = scene->talk;
    if (talk != NULL && talk[SCENE_COMMAND_TALK_STATE / 4] == SCENE_COMMAND_LINE_SHOWN) {
        talk[SCENE_COMMAND_TALK_NEXT / 4] = 1;
        return (void *) (uintptr_t) 1;
    }
    return NULL;
}
CLEAN_AS(func_020155b4, SceneCommand_NextLine)

/* func_020155cc: asks for the talk's next line. Whether the scene took it. */
int SceneCommand_RequestNextLine(SceneCommandScene *scene)
{
    return SceneCommand_Request(scene, SCENE_COMMAND_NEXT_LINE);
}
CLEAN_AS(func_020155cc, SceneCommand_RequestNextLine)

/* _ZN12Obj_020d8bd413func_020155d8Ev (command 0): the step's function; its answer, 0 from step
 * 3 on. */
int SceneCommand_RunScreen(SceneCommandScene *scene)
{
    static const MemberPointer *const steps[] = {
        &data_020d89cc, /* SceneCommand_BeginScreen */
        &data_020d89e4, /* SceneCommand_OpenScreen */
        &data_020d89ec, /* SceneCommand_WaitScreen */
    };
    return scene_command_run_steps(scene, &data_021c1540, data_021c1714, steps, 3);
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020155d8Ev, SceneCommand_RunScreen)

/* func_02015654 (command 0, step 2): once a group can be opened again (the screen is over), the
 * talk's next line is asked for unless `stay_on_line` is 1, and the command is finished at
 * step 3.
 * REQUIRES: the scene has its talk (step 1 found it, and nothing takes it away meanwhile); the
 * talk is not checked here. */
int SceneCommand_WaitScreen(SceneCommandScene *scene)
{
    if (!GroupParams_CanOpen()) {
        return 0;
    }
    if (scene->params.stay_on_line != 1) {
        scene->talk[SCENE_COMMAND_TALK_NEXT / 4] = 1;
    }
    scene->state = 3;
    return 1;
}
CLEAN_AS(func_02015654, SceneCommand_WaitScreen)

/* func_02015688 (command 0, step 1): once the talk's line is shown to its end, the screen is
 * opened (by `screen`, with the values set for it) and the step is 2 when it was; screen 7 opens
 * nothing and finishes the command as step 2 does. Unknown screens do nothing. The answer is 1
 * only when the command is finished. */
int SceneCommand_OpenScreen(SceneCommandScene *scene)
{
    s32 *talk = scene->talk;
    if (talk == NULL || talk[SCENE_COMMAND_TALK_STATE / 4] != SCENE_COMMAND_LINE_SHOWN) {
        return 0;
    }
    SceneCommandParams *params = &scene->params;
    int opened = 0;
    switch (params->screen) {
        case SCENE_COMMAND_SCREEN_POCKETS: {
            int mask = params->pocket_mask;
            if (params->pocket_predicate != NULL) {
                mask = Pockets_Select(params->pocket_predicate);
            }
            opened = GroupParams_OpenWithMask((u16) mask, params->pocket_arg);
            break;
        }
        case SCENE_COMMAND_SCREEN_MODE_25:
            params->stay_on_line = 1;
            opened = GroupParams_OpenLetter();
            break;
        case SCENE_COMMAND_SCREEN_MODE:
            opened = GroupParams_Open(params->mode);
            break;
        case SCENE_COMMAND_SCREEN_MODE_ARG:
            opened = GroupParams_OpenWithArg(params->mode, params->mode_arg);
            break;
        case SCENE_COMMAND_SCREEN_MODE_3D:
            opened = GroupParams_OpenWithC80C88(params->screen_a, params->screen_b);
            break;
        case SCENE_COMMAND_SCREEN_GROUP_12:
            opened = GroupParams_OpenGroup12((void *) (uintptr_t) params->group_12_pointer);
            break;
        case SCENE_COMMAND_SCREEN_MODE_TEXT:
            opened = GroupParams_OpenWithText(params->mode, (const u16 *) (uintptr_t) ((int) params->text),
                                              (int) params->text_units);
            break;
        case SCENE_COMMAND_SCREEN_NONE:
            if (params->stay_on_line != 1) {
                talk[SCENE_COMMAND_TALK_NEXT / 4] = 1;
            }
            scene->state = 3;
            return 1;
        default:
            break;
    }
    if (opened != 0) {
        scene->state = 2;
    }
    return 0;
}
CLEAN_AS(func_02015688, SceneCommand_OpenScreen)

/* func_02015760 (command 0, step 0): with a talk, its word 0x14 is 1 and the step is 1. The
 * answer is 0. */
int SceneCommand_BeginScreen(SceneCommandScene *scene)
{
    s32 *talk = scene->talk;
    if (talk != NULL) {
        talk[SCENE_COMMAND_TALK_MODE_WORD / 4] = 1;
        scene->state = 1;
    }
    return 0;
}
CLEAN_AS(func_02015760, SceneCommand_BeginScreen)

/* func_02015774: the values of screen 6 (a mode and a text) and `stay_on_line`. */
void SceneCommand_SetScreenText(SceneCommandScene *scene, u8 mode, u32 text, u32 units, u8 stay_on_line)
{
    scene->params.mode = mode;
    scene->params.text = text;
    scene->params.text_units = units;
    scene->params.stay_on_line = stay_on_line;
}
CLEAN_AS(func_02015774, SceneCommand_SetScreenText)

/* func_0201579c: the value of screen 5 (the address group 12 is opened with) and
 * `stay_on_line`. */
void SceneCommand_SetScreenPointer(SceneCommandScene *scene, int pointer, int stay_on_line)
{
    scene->params.group_12_pointer = (u32) pointer;
    scene->params.stay_on_line = (u8) stay_on_line;
}
CLEAN_AS(func_0201579c, SceneCommand_SetScreenPointer)

/* func_020157a4: the values of screen 4 and `stay_on_line`. */
void SceneCommand_SetScreenArgs(SceneCommandScene *scene, s32 a, s32 b, int stay_on_line)
{
    scene->params.screen_a = a;
    scene->params.screen_b = b;
    scene->params.stay_on_line = (u8) stay_on_line;
}
CLEAN_AS(func_020157a4, SceneCommand_SetScreenArgs)

/* func_020157b0: the values of screen 3 (a mode and its argument) and `stay_on_line`. */
void SceneCommand_SetScreenModeArg(SceneCommandScene *scene, u8 mode, u8 arg, u8 stay_on_line)
{
    scene->params.mode = mode;
    scene->params.mode_arg = arg;
    scene->params.stay_on_line = stay_on_line;
}
CLEAN_AS(func_020157b0, SceneCommand_SetScreenModeArg)

/* func_020157c8: the value of screen 2 (a mode) and `stay_on_line`. */
void SceneCommand_SetScreenMode(SceneCommandScene *scene, char mode, char stay_on_line)
{
    scene->params.mode = (u8) mode;
    scene->params.stay_on_line = (u8) stay_on_line;
}
CLEAN_AS(func_020157c8, SceneCommand_SetScreenMode)

/* func_020157d4: the values of screen 0 picking the pockets with a predicate, and
 * `stay_on_line`; the item is cleared to none. */
void SceneCommand_SetPocketPredicate(SceneCommandScene *scene, PocketPredicate predicate, u8 arg, u8 stay_on_line)
{
    scene->params.pocket_mask = 0;
    scene->params.pocket_predicate = predicate;
    scene->params.pocket_arg = arg;
    scene->params.item = 0xfff1;
    scene->params.stay_on_line = stay_on_line;
}
CLEAN_AS(func_020157d4, SceneCommand_SetPocketPredicate)

/* func_02015800: the values of screen 0 with a fixed mask of pockets, and `stay_on_line`; the
 * item is cleared to none. */
void SceneCommand_SetPocketMask(SceneCommandScene *scene, u16 mask, u8 arg, u8 stay_on_line)
{
    scene->params.pocket_mask = mask;
    scene->params.pocket_predicate = NULL;
    scene->params.pocket_arg = arg;
    scene->params.item = 0xfff1;
    scene->params.stay_on_line = stay_on_line;
}
CLEAN_AS(func_02015800, SceneCommand_SetPocketMask)

/* func_02015828: asks for screen `screen` (its values set beforehand). Whether the scene took
 * it. */
int SceneCommand_RequestScreen(SceneCommandScene *scene, int screen)
{
    if (SceneCommand_Request(scene, SCENE_COMMAND_SCREEN)) {
        scene->params.screen = (u32) screen;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02015828, SceneCommand_RequestScreen)

/* func_02015848: the scene's vtable slot 0x84 by default: told which command ended, it does
 * nothing. */
void SceneCommand_Ended(SceneCommandScene *scene, int command)
{
    (void) scene;
    (void) command;
}
CLEAN_AS(func_02015848, SceneCommand_Ended)

/* func_0201584c: a step of the scene's command. When the step says the command is finished,
 * the scene is no longer busy, its command is none, and its vtable slot 0x84 is told which
 * command ended.
 * REQUIRES: `command` is not negative (the original reads before its table then). */
void SceneCommand_Run(SceneCommandScene *scene)
{
    typedef void (*SceneCommandEnded)(SceneCommandScene *scene, int command);

    static const MemberPointer *const commands[SCENE_COMMAND_COUNT] = {
        &data_020d881c, /* SceneCommand_RunScreen */
        &data_020d8844, /* SceneCommand_NextLine */
        &data_020d86cc, /* SceneCommand_RunTalkMode */
        &data_020d88c4, /* SceneCommand_RunMotion13 */
        &data_020d8904, /* SceneCommand_RunMotion14 */
        &data_020d8934, /* SceneCommand_RunMotion15 */
        &data_020d893c, /* SceneCommand_RunMotion16 */
        &data_020d8954, /* SceneCommand_RunMotion17 */
        &data_020d896c, /* SceneCommand_RunMotion18 */
        &data_020d8974, /* SceneCommand_RunMotion19 */
        &data_020d8984, /* SceneCommand_RunSound */
        &data_020d8994, /* SceneTalk_Run */
    };
    MemberTable_InitOnce(&data_021c1524, data_021c1814, commands, SCENE_COMMAND_COUNT);
    if (scene->command >= SCENE_COMMAND_COUNT) {
        return;
    }
    if (MemberPointer_CallInt(&data_021c1814[scene->command], scene) == 0) {
        return;
    }
    int ended = scene->command;
    scene->busy = 0;
    scene->command = SCENE_COMMAND_NONE;
    u32 tell_ended = scene_command_slot(scene, SCENE_COMMAND_SLOT_ENDED);
    ((SceneCommandEnded) (uintptr_t) tell_ended)(scene, ended);
}
CLEAN_AS(func_0201584c, SceneCommand_Run)

/* func_0201595c: whether a command was asked for and has not ended. */
int SceneCommand_IsBusy(const SceneCommandScene *scene)
{
    return scene->busy != 0;
}
CLEAN_AS(func_0201595c, SceneCommand_IsBusy)

/* func_0201596c: asks for `command`, taken when there is none or the last one ended: it starts
 * at step 0 and the scene is busy. Whether it was taken. */
int SceneCommand_Request(SceneCommandScene *scene, u32 command)
{
    if ((u32) scene->command == SCENE_COMMAND_NONE || !SceneCommand_IsBusy(scene)) {
        scene->command = (s32) command;
        scene->state = 0;
        scene->busy = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0201596c, SceneCommand_Request)

/* func_0201599c: the commands' values as a new scene has them (the first argument is not
 * used). */
void SceneCommand_ResetParams(int unused, SceneCommandParams *params)
{
    (void) unused;
    params->screen = 8;
    params->screen_a = 0;
    params->screen_b = 0;
    params->group_12_pointer = 0;
    params->pocket_mask = 0;
    params->pocket_predicate = NULL;
    params->pocket_arg = 0xd;
    params->item = 0xfff1;
    params->motion_a = 0;
    params->mode = 0x45;
    params->mode_arg = 0;
    params->stay_on_line = 2;
    params->motion_b = 0xc;
    params->motion_c = 2;
    params->start_with_camera = 1;
    params->text = 0;
    params->text_units = 0;
    params->sound_without_values = 0;
    params->talk_mode = 0;
}
CLEAN_AS(func_0201599c, SceneCommand_ResetParams)

/* func_020159f0: no command, not busy, and the commands' values reset. */
void SceneCommand_Init(SceneCommandScene *scene)
{
    scene->command = SCENE_COMMAND_NONE;
    scene->state = 0;
    scene->busy = 0;
    SceneCommand_ResetParams((int) (uintptr_t) scene, &scene->params);
}
CLEAN_AS(func_020159f0, SceneCommand_Init)
