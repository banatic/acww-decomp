/* The actions a scene object is asked to play (scene_action.h). */
#include "scene_action.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "camera_modes.h"
#include "message_receiver.h"
#include "player_actor_ops.h"
#include "player_id.h"
#include "scene_base.h"
#include "scene_motion_request.h"
#include "scene_object.h"
#include "scene_object_base.h"
#include "scene_talk_state.h"
#include "talk_object.h"
#include "talk_receiver.h"
#include "town_tune.h"

static_assert(offsetof(SceneAction, motion_b) == 0x04, "SceneAction layout");
static_assert(offsetof(SceneAction, action) == 0x08, "SceneAction layout");
static_assert(offsetof(SceneAction, released) == 0x0e, "SceneAction layout");

/* The scene object's parts used here. */
#define SCENE_ACTION_OBJECT_POSITION 0x5c /* a Vec3 */
#define SCENE_ACTION_OBJECT_ANGLE 0x8e    /* s16, the angle about y */
#define SCENE_ACTION_OBJECT_TALKING 0x418 /* func_0201a7d4 sets its byte, func_0201a7cc clears it */
#define SCENE_ACTION_OBJECT_FLAGS 0x4e8
#define SCENE_ACTION_OBJECT_MOTION 0x564
#define SCENE_ACTION_OBJECT_SCENE 0x634 /* the scene it talks in, or null */

/* The object's vtable slots used here: its name into a string object, whether it has a sound
 * to play on starting an action, that sound (0xffff for none), what follows playing it, and
 * (on the other speaker) what an action's end tells it. */
#define SCENE_ACTION_SLOT_NAME 0x74
#define SCENE_ACTION_SLOT_HAS_SOUND 0x7c
#define SCENE_ACTION_SLOT_SOUND_PLAYED 0x80
#define SCENE_ACTION_SLOT_SOUND 0x84
#define SCENE_ACTION_SLOT_ENDED 0x90
#define SCENE_ACTION_NO_SOUND 0xffff

/* The scene's parts and vtable slots used here: the talk's state (word 4: 0 once the talk is
 * over; word 8: 1 to begin; byte 0x1e97: func_02068370), a byte the talk's line gives, the
 * line itself, and what the end of the talk tells the scene. */
#define SCENE_ACTION_SCENE_LINE_BYTE 0x1e
#define SCENE_ACTION_SCENE_TALK 0x40
#define SCENE_ACTION_SLOT_LINE 0x78
#define SCENE_ACTION_SLOT_TALK_OVER 0x7c

/* Bit 2 of the object's flags at 0x4e8: an action holds the object. */
#define SCENE_ACTION_HELD 2

/* The kinds of motion the actions set or wait for, and the priorities they set them with. */
#define SCENE_ACTION_MOTION_STAND 0
#define SCENE_ACTION_MOTION_TURN 3
#define SCENE_ACTION_MOTION_TIMED 7
#define SCENE_ACTION_MOTION_TALK 8
#define SCENE_ACTION_PRIORITY 2
#define SCENE_ACTION_PRIORITY_LOW 1

/* The height above the object's position the camera aims at. */
#define SCENE_ACTION_CAMERA_HEIGHT 0x2000

typedef struct SceneActionEntry {
    MemberPointer start; /* (action, object) */
    MemberPointer run;   /* (action, object) */
} SceneActionEntry;

/* What the scene's vtable slot 0x78 gives: the name to hand to the talk (func_020a8164) and a
 * byte for the scene's 0x1e. */
typedef struct SceneActionLine {
    u32 name;
    u8 byte;
    u8 unk_05[3];
} SceneActionLine;

/* A string object (0x24 bytes): built by func_02094fd4, destroyed by func_02094fbc; its vtable
 * slot 0x0c gives its characters. */
typedef struct SceneActionText {
    const u8 *vtable;
    u8 unk_04[0x20];
} SceneActionText;

#define SCENE_ACTION_TEXT_SLOT_CHARS 0x0c

/* The actions (filled at start-up), and each run's table of phases: a guard word, the table
 * and the constants it is filled from. */
extern const SceneActionEntry data_021c17c4[];
extern u32 data_021c153c;
extern MemberPointer data_021c1574[];
extern const MemberPointer data_020d8a54;
extern u32 data_021c14f8;
extern MemberPointer data_021c156c[];
extern const MemberPointer data_020d89f4;
extern u32 data_021c1520;
extern MemberPointer data_021c16fc[];
extern const MemberPointer data_020d895c;
extern const MemberPointer data_020d897c;
extern const MemberPointer data_020d899c;
extern u32 data_021c14f4;
extern MemberPointer data_021c163c[];
extern const MemberPointer data_020d8804;
extern const MemberPointer data_020d884c;
extern u32 data_021c150c;
extern MemberPointer data_021c16cc[];
extern const MemberPointer data_020d8764;
extern const MemberPointer data_020d88fc;
extern const MemberPointer data_020d87dc;

/* The last word every motion is set with. */
extern u16 data_020c80f8;

static u8 *scene_action_part(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static void *scene_action_motion(void *object)
{
    return scene_action_part(object, SCENE_ACTION_OBJECT_MOTION);
}

static u8 *scene_action_scene(void *object)
{
    return *(u8 **) scene_action_part(object, SCENE_ACTION_OBJECT_SCENE);
}

static u32 *scene_action_flags(void *object)
{
    return (u32 *) scene_action_part(object, SCENE_ACTION_OBJECT_FLAGS);
}

static u32 scene_action_slot(const void *object, u32 offset)
{
    const u8 *vtable = *(const u8 *const *) object;
    return *(const u32 *) (vtable + offset);
}

static int scene_action_call_int(void *object, u32 offset)
{
    return ((int (*)(void *))(uintptr_t) scene_action_slot(object, offset))(object);
}

static void scene_action_call_void(void *object, u32 offset)
{
    ((void (*)(void *))(uintptr_t) scene_action_slot(object, offset))(object);
}

/* A call through an action's or a phase's member pointer. */
static void scene_action_call(const MemberPointer *member, SceneAction *self, void *object)
{
    void *target = MemberPointer_Object(member, self);
    ((void (*)(void *, void *))(uintptr_t) MemberPointer_Code(member, target))(target, object);
}

static void scene_action_set_motion(void *object, int kind, int priority, int b, int c)
{
    SceneMotion_Request(scene_action_motion(object), kind, priority, 0, 0, b, c, 0, 0, data_020c80f8, 0);
}

/* Whether a speaker's motion is the talk's (kind 8) and not done. */
static int scene_action_talk_motion_on(void *speaker)
{
    void *motion = scene_action_motion(speaker);
    return SceneMotion_Kind(motion) == SCENE_ACTION_MOTION_TALK && SceneMotion_IsDone(motion) == 0;
}

/* The motion of kind `kind` is done. */
static int scene_action_motion_done(void *object, int kind)
{
    void *motion = scene_action_motion(object);
    return SceneMotion_Kind(motion) == kind && SceneMotion_IsDone(motion) != 0;
}

/* The object is held by the action: bit 2 of its flags is set (and the action remembers when it
 * found it clear). */
static void scene_action_hold(SceneAction *self, void *object)
{
    u32 *flags = scene_action_flags(object);
    if ((*flags & SCENE_ACTION_HELD) == 0) {
        self->set_flag = 1;
    }
    *flags |= SCENE_ACTION_HELD;
}

/* QUIRK: `set_flag` is never cleared once set (only SceneAction_Init clears it), so a later
 * action clears the bit even when it found it set. */
static void scene_action_release(SceneAction *self, void *object)
{
    if (self->set_flag == 1) {
        *scene_action_flags(object) &= ~(u32) SCENE_ACTION_HELD;
    }
}

/* The object's sound for starting an action, when it has one. */
static void scene_action_play_sound(void *object)
{
    if (scene_action_call_int(object, SCENE_ACTION_SLOT_HAS_SOUND) != 0) {
        int sound = scene_action_call_int(object, SCENE_ACTION_SLOT_SOUND);
        if (sound != SCENE_ACTION_NO_SOUND) {
            TownTune_PlayOwn(sound);
        }
        scene_action_call_void(object, SCENE_ACTION_SLOT_SOUND_PLAYED);
    }
}

/* The camera at `at` (the object's position) and the other speaker's, both raised, or at `at`
 * alone without one. */
static void scene_action_aim_camera(void *object, Vec3 *at)
{
    u8 *scene = scene_action_scene(object);
    u8 *other = scene != NULL ? (u8 *) (uintptr_t) SceneBase_SecondSpeaker((SceneBase *) (void *) scene) : NULL;
    if (other != NULL) {
        Vec3 other_at = *(const Vec3 *) scene_action_part(other, SCENE_ACTION_OBJECT_POSITION);
        at->y += SCENE_ACTION_CAMERA_HEIGHT;
        other_at.y += SCENE_ACTION_CAMERA_HEIGHT;
        CameraControl_FocusOnPair(at, &other_at);
    } else {
        at->y += SCENE_ACTION_CAMERA_HEIGHT;
        CameraControl_FocusOn(at);
    }
}

/* ---- Action 4: a timed motion */

/* _ZN12Obj_020d8bd413func_02013c34EPv: the phase of action 4, through its table.
 * REQUIRES: phase 0, the only one in the table (the action ends as it leaves it); for 1 and 2
 * the original calls through empty entries. */
void SceneAction_RunPhase4(SceneAction *self, void *object)
{
    static const MemberPointer *const phases[] = {
        &data_020d8a54, /* SceneAction_WaitMotion7 */
    };
    MemberTable_InitOnce(&data_021c153c, data_021c1574, phases, 1);
    if (self->phase < 3) {
        scene_action_call(&data_021c1574[self->phase], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02013c34EPv, SceneAction_RunPhase4)

/* func_02013c98: once the timed motion (kind 7) is done, kind 0 with the low priority; the
 * object is let go and the action ends. */
void SceneAction_WaitMotion7(SceneAction *self, void *object)
{
    if (scene_action_motion_done(object, SCENE_ACTION_MOTION_TIMED)) {
        scene_action_set_motion(object, SCENE_ACTION_MOTION_STAND, SCENE_ACTION_PRIORITY_LOW, 0, 0);
        scene_action_release(self, object);
        self->phase = 1;
        self->action = SCENE_ACTION_NONE;
    }
}
CLEAN_AS(func_02013c98, SceneAction_WaitMotion7)

/* func_02013d08: the timed motion (func_02019cc8, kind 7) with `motion_b`, `motion_c` and
 * `motion_arg`; the object is held. */
void SceneAction_Start4(SceneAction *self, void *object)
{
    SceneMotion_RequestGesture(scene_action_motion(object), SCENE_ACTION_PRIORITY, self->motion_b, (u16) self->motion_c,
                               self->motion_arg, data_020c80f8);
    scene_action_hold(self, object);
    self->phase = 0;
}
CLEAN_AS(func_02013d08, SceneAction_Start4)

/* ---- Action 3: hold until released */

/* _ZN12Obj_020d8bd413func_02013d5cEPv: the phase of action 3, through its table. */
void SceneAction_RunPhase3(SceneAction *self, void *object)
{
    static const MemberPointer *const phases[] = {
        &data_020d89f4, /* SceneAction_WaitRelease */
    };
    MemberTable_InitOnce(&data_021c14f8, data_021c156c, phases, 1);
    if (self->phase < 1) {
        scene_action_call(&data_021c156c[self->phase], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02013d5cEPv, SceneAction_RunPhase3)

/* func_02013dc0: (kind 0 first with `reset_motion`) the motion's byte 0x19 is 1 (func_02019b78);
 * the object is held and plays its sound. */
void SceneAction_Start3(SceneAction *self, void *object)
{
    if (self->reset_motion != 0) {
        scene_action_set_motion(object, SCENE_ACTION_MOTION_STAND, SCENE_ACTION_PRIORITY, 0, 0);
    }
    SceneMotion_AskHold(scene_action_motion(object));
    scene_action_hold(self, object);
    scene_action_play_sound(object);
    self->phase = 0;
}
CLEAN_AS(func_02013dc0, SceneAction_Start3)

/* ---- Action 1: a talk */

/* _ZN12Obj_020d8bd413func_02013e68EPv: the phase of action 1, through its table. */
void SceneAction_RunPhase1(SceneAction *self, void *object)
{
    static const MemberPointer *const phases[] = {
        &data_020d895c, /* SceneAction_OpenTalk1 */
        &data_020d897c, /* SceneAction_WaitTalk1 */
        &data_020d899c, /* SceneAction_WaitSpeakers1 */
    };
    MemberTable_InitOnce(&data_021c1520, data_021c16fc, phases, 3);
    if (self->phase < 3) {
        scene_action_call(&data_021c16fc[self->phase], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02013e68EPv, SceneAction_RunPhase1)

/* Once neither speaker is in the talk's motion (kind 8) any more, the action ends with the
 * phase `phase`. */
static void scene_action_wait_speakers(SceneAction *self, void *object, u8 phase)
{
    u8 *scene = scene_action_scene(object);
    if (scene != NULL) {
        u8 *other = (u8 *) (uintptr_t) SceneBase_SecondSpeaker((SceneBase *) (void *) scene);
        if (other != NULL && scene_action_talk_motion_on(other)) {
            return;
        }
    }
    if (scene_action_talk_motion_on(object)) {
        return;
    }
    SceneAction_Finish(self, object);
    self->phase = phase;
    self->action = SCENE_ACTION_NONE;
}

/* func_02013ee4 */
void SceneAction_WaitSpeakers1(SceneAction *self, void *object)
{
    scene_action_wait_speakers(self, object, 1);
}
CLEAN_AS(func_02013ee4, SceneAction_WaitSpeakers1)

/* While the scene's talk goes on, the scene's func_02016110 and the talking flag follow it
 * (SceneAction_ShowTalking). Once it is over: the scene is told (vtable slot 0x7c), and
 * func_0203ee08; the speaker's talking flag is cleared; if a speaker is still in the talk's
 * motion, func_02016024 tells the scene of each (the object 0, the other 1) and the phase is
 * 2, else the action ends with the phase `phase`. Nothing without a scene or a talk. */
static void scene_action_wait_talk(SceneAction *self, void *object, u8 phase)
{
    u8 *scene = scene_action_scene(object);
    if (scene == NULL) {
        return;
    }
    const u8 *talk = *(u8 *const *) (scene + SCENE_ACTION_SCENE_TALK);
    if (talk == NULL) {
        return;
    }
    if (*(const s32 *) (talk + 4) != 0) {
        SceneBase_Update((SceneBase *) (void *) scene);
        SceneAction_ShowTalking(self, object);
        return;
    }

    scene_action_call_void(scene, SCENE_ACTION_SLOT_TALK_OVER);
    SceneObjectBase_ReleaseReceiver(object, (TalkReceiver *) (void *) scene);
    u8 *speaker = (u8 *) (uintptr_t) SceneBase_SpeakingSpeaker((SceneBase *) (void *) scene);
    if (speaker != NULL) {
        SceneTalkState_Stop((SceneTalkState *) (void *) (speaker + SCENE_ACTION_OBJECT_TALKING));
    }

    u8 *other = (u8 *) (uintptr_t) SceneBase_SecondSpeaker((SceneBase *) (void *) scene);
    int other_on = other != NULL && scene_action_talk_motion_on(other);
    int own_on = scene_action_talk_motion_on(object);
    if (other_on || own_on) {
        if (own_on) {
            SceneBase_SetSpeakerTalkStyle((SceneBase *) (void *) scene, 0, 0);
        }
        if (other_on) {
            SceneBase_SetSpeakerTalkStyle((SceneBase *) (void *) scene, 0, 1);
        }
        self->phase = 2;
    } else {
        SceneAction_Finish(self, object);
        self->phase = phase;
        self->action = SCENE_ACTION_NONE;
    }
}

/* func_02013f58 */
void SceneAction_WaitTalk1(SceneAction *self, void *object)
{
    scene_action_wait_talk(self, object, 1);
}
CLEAN_AS(func_02013f58, SceneAction_WaitTalk1)

/* func_0201404c */
void SceneAction_OpenTalk1(SceneAction *self, void *object)
{
    SceneAction_OpenTalk(self, object);
    self->phase = 1;
}
CLEAN_AS(func_0201404c, SceneAction_OpenTalk1)

/* func_02014060: (kind 0 first with `reset_motion`) the camera aims at the speakers unless
 * `keep_camera`; the object is held and plays its sound. */
void SceneAction_Start1(SceneAction *self, void *object)
{
    Vec3 at = *(const Vec3 *) scene_action_part(object, SCENE_ACTION_OBJECT_POSITION);
    if (self->reset_motion != 0) {
        scene_action_set_motion(object, SCENE_ACTION_MOTION_STAND, SCENE_ACTION_PRIORITY, 0, 0);
    }
    self->phase = 0;
    if (self->keep_camera == 0) {
        scene_action_aim_camera(object, &at);
    }
    scene_action_hold(self, object);
    scene_action_play_sound(object);
}
CLEAN_AS(func_02014060, SceneAction_Start1)

/* ---- Action 2: a turn, then hold until released */

/* func_02014158: the phase of action 2, through its table. */
void SceneAction_RunPhase2(SceneAction *self, void *object)
{
    static const MemberPointer *const phases[] = {
        &data_020d8804, /* SceneAction_WaitMotion3 */
        &data_020d884c, /* SceneAction_WaitRelease */
    };
    MemberTable_InitOnce(&data_021c14f4, data_021c163c, phases, 2);
    if (self->phase < 2) {
        scene_action_call(&data_021c163c[self->phase], self, object);
    }
}
CLEAN_AS(func_02014158, SceneAction_RunPhase2)

/* func_020141c4: once `released`, the motion's byte 0x19 is 2 (func_02019b70) and the action
 * ends. */
void SceneAction_WaitRelease(SceneAction *self, void *object)
{
    if (self->released != 0) {
        SceneMotion_AskRelease(scene_action_motion(object));
        self->phase = 2;
        self->action = SCENE_ACTION_NONE;
    }
}
CLEAN_AS(func_020141c4, SceneAction_WaitRelease)

/* func_020141e8: once the turn (kind 3) is done, kind 0 and the motion's byte 0x19 is 1. */
void SceneAction_WaitMotion3(SceneAction *self, void *object)
{
    if (scene_action_motion_done(object, SCENE_ACTION_MOTION_TURN)) {
        scene_action_set_motion(object, SCENE_ACTION_MOTION_STAND, SCENE_ACTION_PRIORITY, 0, 0);
        SceneMotion_AskHold(scene_action_motion(object));
        self->phase = 1;
    }
}
CLEAN_AS(func_020141e8, SceneAction_WaitMotion3)

/* func_02014244: the turn (kind 3, `motion_b` and `motion_c`); the object is held and plays its
 * sound. */
void SceneAction_Start2(SceneAction *self, void *object)
{
    scene_action_set_motion(object, SCENE_ACTION_MOTION_TURN, SCENE_ACTION_PRIORITY, (s16) self->motion_b, self->motion_c);
    scene_action_hold(self, object);
    scene_action_play_sound(object);
    self->phase = 0;
}
CLEAN_AS(func_02014244, SceneAction_Start2)

/* ---- Action 0: a turn, then a talk */

/* _ZN12Obj_020d8bd413func_020142e4EPv: the phase of action 0, through its table. */
void SceneAction_RunPhase0(SceneAction *self, void *object)
{
    static const MemberPointer *const phases[] = {
        &data_020d8764, /* SceneAction_WaitTurn0 */
        &data_020d88fc, /* SceneAction_WaitTalk0 */
        &data_020d87dc, /* SceneAction_WaitSpeakers0 */
    };
    MemberTable_InitOnce(&data_021c150c, data_021c16cc, phases, 3);
    if (self->phase < 3) {
        scene_action_call(&data_021c16cc[self->phase], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020142e4EPv, SceneAction_RunPhase0)

/* func_02014360 */
void SceneAction_WaitSpeakers0(SceneAction *self, void *object)
{
    scene_action_wait_speakers(self, object, 3);
}
CLEAN_AS(func_02014360, SceneAction_WaitSpeakers0)

/* func_020143d4 */
void SceneAction_WaitTalk0(SceneAction *self, void *object)
{
    scene_action_wait_talk(self, object, 3);
}
CLEAN_AS(func_020143d4, SceneAction_WaitTalk0)

/* func_020144c8: once the object faces the angle `motion_c` and the turn (kind 3) is done,
 * kind 0 and the talk opens. */
void SceneAction_WaitTurn0(SceneAction *self, void *object)
{
    s16 angle = *(const s16 *) scene_action_part(object, SCENE_ACTION_OBJECT_ANGLE);
    if (self->motion_c == angle && scene_action_motion_done(object, SCENE_ACTION_MOTION_TURN)) {
        scene_action_set_motion(object, SCENE_ACTION_MOTION_STAND, SCENE_ACTION_PRIORITY, 0, 0);
        SceneAction_OpenTalk(self, object);
        self->phase = 1;
    }
}
CLEAN_AS(func_020144c8, SceneAction_WaitTurn0)

/* func_02014530: the turn (kind 3, `motion_b` and `motion_c`); the camera aims at the speakers
 * unless `keep_camera`; the object is held and plays its sound. */
void SceneAction_Start0(SceneAction *self, void *object)
{
    Vec3 at = *(const Vec3 *) scene_action_part(object, SCENE_ACTION_OBJECT_POSITION);
    scene_action_set_motion(object, SCENE_ACTION_MOTION_TURN, SCENE_ACTION_PRIORITY, (s16) self->motion_b, self->motion_c);
    if (self->keep_camera == 0) {
        scene_action_aim_camera(object, &at);
    }
    scene_action_hold(self, object);
    scene_action_play_sound(object);
    self->phase = 0;
}
CLEAN_AS(func_02014530, SceneAction_Start0)

/* ---- Common */

/* func_0201462c: the end of a talk: the other speaker is told (its vtable slot 0x90), the
 * camera turns back (func_0203b144) unless `keep_camera`, the object is let go, and
 * func_02095518(0, 0, 4). */
void SceneAction_Finish(SceneAction *self, void *object)
{
    u8 *scene = scene_action_scene(object);
    if (scene != NULL) {
        u8 *other = (u8 *) (uintptr_t) SceneBase_SecondSpeaker((SceneBase *) (void *) scene);
        if (other != NULL) {
            scene_action_call_void(other, SCENE_ACTION_SLOT_ENDED);
        }
    }
    if (self->keep_camera == 0) {
        CameraControl_ResetMode();
    }
    scene_action_release(self, object);
    PlayerActorOps_SetLook(0, 0, 4);
}
CLEAN_AS(func_0201462c, SceneAction_Finish)

/* func_02014688: a frame: the request waiting starts (SceneAction_StartPending), then the action
 * running takes its step. */
void SceneAction_Run(SceneAction *self, void *object)
{
    SceneAction_StartPending(self, object);
    if (self->action < SCENE_ACTION_COUNT) {
        scene_action_call(&data_021c17c4[self->action].run, self, object);
    }
}
CLEAN_AS(func_02014688, SceneAction_Run)

/* func_020146cc: when an action is requested and none runs, it runs from phase 0 (not
 * released), its start is called and the request is taken. */
void SceneAction_StartPending(SceneAction *self, void *object)
{
    if (self->pending < SCENE_ACTION_COUNT && self->action == SCENE_ACTION_NONE) {
        self->action = self->pending;
        self->phase = 0;
        self->released = 0;
        scene_action_call(&data_021c17c4[self->action].start, self, object);
        self->pending = SCENE_ACTION_NONE;
    }
}
CLEAN_AS(func_020146cc, SceneAction_StartPending)

/* func_02014718: the talk in the object's scene opens (nothing without a scene): the object's
 * name (its vtable slot 0x74 fills a string object) goes to the scene as the speaker's
 * (func_02066954, with func_0201c250's answer), func_0203ee14, the scene's line (its vtable slot
 * 0x78) gives the talk's name (func_020a8164) and the scene's byte 0x1e, and the talk begins
 * (word 8 is 1). */
void SceneAction_OpenTalk(SceneAction *self, void *object)
{
    typedef void (*SceneActionFill)(void *object, void *out);
    typedef const char *(*SceneActionChars)(SceneActionText *text);
    (void) self;

    u8 *scene = scene_action_scene(object);
    if (scene == NULL) {
        return;
    }
    SceneActionText text;
    PlayerIdText_Construct((PlayerIdText *) &text);
    ((SceneActionFill) (uintptr_t) scene_action_slot(object, SCENE_ACTION_SLOT_NAME))(object, &text);
    const char *name = ((SceneActionChars) (uintptr_t) scene_action_slot(&text, SCENE_ACTION_TEXT_SLOT_CHARS))(&text);
    int a = SceneObject_Sort(object);
    TalkReceiver_SetSpeaker((TalkReceiver *) (void *) scene, name, a);
    SceneObjectBase_TakeReceiver(object, (TalkReceiver *) (void *) scene);

    SceneActionLine line;
    ((SceneActionFill) (uintptr_t) scene_action_slot(scene, SCENE_ACTION_SLOT_LINE))(scene, &line);
    MessageReceiver_SetName((MessageReceiver *) (void *) scene, (const char *) (uintptr_t) line.name);
    scene[SCENE_ACTION_SCENE_LINE_BYTE] = line.byte;
    u8 *talk = *(u8 **) (scene + SCENE_ACTION_SCENE_TALK);
    *(s32 *) (talk + 8) = 1;
    PlayerIdText_Destruct((PlayerIdText *) &text);
}
CLEAN_AS(func_02014718, SceneAction_OpenTalk)

/* func_02014788: action `action` is requested with its arguments, when none is requested yet;
 * whether it was. */
int SceneAction_Request(SceneAction *self, u8 action, s32 motion_arg, u16 motion_b, s16 motion_c, u8 reset_motion,
                        u8 keep_camera)
{
    if (self->pending != SCENE_ACTION_NONE) {
        return 0;
    }
    self->pending = action;
    self->motion_b = motion_b;
    self->motion_c = motion_c;
    self->motion_arg = motion_arg;
    self->reset_motion = reset_motion;
    self->keep_camera = keep_camera;
    return 1;
}
CLEAN_AS(func_02014788, SceneAction_Request)

/* func_020147b8: action 4 (the timed motion). */
int SceneAction_RequestMotion7(SceneAction *self, int motion_arg, int motion_b, int motion_c, u8 keep_camera)
{
    return SceneAction_Request(self, 4, motion_arg, (u16) motion_b, (s16) motion_c, 1, keep_camera);
}
CLEAN_AS(func_020147b8, SceneAction_RequestMotion7)

/* func_020147e0: action 1 (a talk). */
int SceneAction_RequestTalk(SceneAction *self, int reset_motion, int keep_camera)
{
    return SceneAction_Request(self, 1, 0, 0, 0, (u8) reset_motion, (u8) keep_camera);
}
CLEAN_AS(func_020147e0, SceneAction_RequestTalk)

/* func_020147fc: action 0 (a turn to `angle`, then a talk). */
int SceneAction_RequestTurnAndTalk(SceneAction *self, int motion_b, int angle, int keep_camera)
{
    return SceneAction_Request(self, 0, 0, (u16) motion_b, (s16) angle, 1, (u8) keep_camera);
}
CLEAN_AS(func_020147fc, SceneAction_RequestTurnAndTalk)

/* func_0201481c: the talking flag of the scene's speaker (func_02015d68) follows the talk's
 * byte 0x1e97 (func_02068370); nothing without a scene, a talk or a speaker. */
void SceneAction_ShowTalking(void *unused, void *object)
{
    (void) unused;
    u8 *scene = scene_action_scene(object);
    if (scene == NULL) {
        return;
    }
    u8 *talk = *(u8 **) (scene + SCENE_ACTION_SCENE_TALK);
    if (talk == NULL) {
        return;
    }
    u8 *speaker = (u8 *) (uintptr_t) SceneBase_SpeakingSpeaker((SceneBase *) (void *) scene);
    if (speaker == NULL) {
        return;
    }
    if (TalkObject_Voiced((TalkObject *) (void *) talk) != 0) {
        SceneTalkState_Start((SceneTalkState *) (void *) (speaker + SCENE_ACTION_OBJECT_TALKING));
    } else {
        SceneTalkState_Stop((SceneTalkState *) (void *) (speaker + SCENE_ACTION_OBJECT_TALKING));
    }
}
CLEAN_AS(func_0201481c, SceneAction_ShowTalking)

/* func_02014868: whether an action runs or is requested. */
int SceneAction_IsBusy(const SceneAction *self)
{
    return self->pending < SCENE_ACTION_COUNT || self->action < SCENE_ACTION_COUNT;
}
CLEAN_AS(func_02014868, SceneAction_IsBusy)

/* func_0201487c: no action, none requested. */
void SceneAction_Init(SceneAction *self)
{
    self->action = SCENE_ACTION_NONE;
    self->pending = SCENE_ACTION_NONE;
    self->phase = 0;
    self->motion_b = 0;
    self->motion_c = 0;
    self->set_flag = 0;
    self->motion_arg = 5;
    self->reset_motion = 1;
    self->keep_camera = 0;
    self->released = 0;
}
CLEAN_AS(func_0201487c, SceneAction_Init)

/* func_02014898: the destructor; nothing to release. */
void SceneAction_Destruct(SceneAction *self)
{
    (void) self;
}
CLEAN_AS(func_02014898, SceneAction_Destruct)

/* func_0201489c: the constructor; nothing to set. */
void SceneAction_Construct(SceneAction *self)
{
    (void) self;
}
CLEAN_AS(func_0201489c, SceneAction_Construct)
