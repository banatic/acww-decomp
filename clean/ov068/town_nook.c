/* The character who meets a new player in the town, and its talk scene (town_nook.h). */
#include "town_nook.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/camera_modes.h"
#include "main/event_queue.h"
#include "main/house_record.h"
#include "main/music_queue.h"
#include "main/nook_store.h"
#include "main/obj_020d9ff8.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/scene_object_members.h"
#include "main/scene_probe.h"
#include "main/scene_value_3aa.h"
#include "main/special_scene_object.h"
#include "main/start_kind.h"
#include "main/talk_object.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(TownNookScene, step) == 0xb0, "step");
static_assert(offsetof(TownNookScene, owner) == 0xb8, "owner");
static_assert(sizeof(TownNookScene) == 0xd0, "scene");

/* A step of the scene (the table data_ov068_02277454, filled when the overlay starts). */
typedef struct TownNookStep {
    MemberPointer run;
    u8 each_frame; /* runs each frame while the talk's link is open, else once it closes */
    u8 unk_09[3];
} TownNookStep;

static_assert(sizeof(TownNookStep) == 0xc, "step row");

/* The vtables of the character and of its scene. */
extern const u8 data_ov068_02277574[];
extern const u8 data_ov068_022774e4[];
/* The scene's steps. */
extern TownNookStep data_ov068_02277454[];
/* The name of the talk's message file ("sp_etc_sequence4"). */
extern const char *const data_ov068_0227733c;
/* The message that ends a talk. */
extern u8 data_021f43e8;
/* The word motion requests carry. */
extern u16 data_020c80f8;
/* The house and the players' records. */
extern HouseRecord data_021ebcd4;
extern u8 data_021dc7bc[];

/* The parts of the character read here. */
#define NOOK_STATE 0x654   /* s32 */
#define NOOK_SCENE 0x658   /* TownNookScene */
#define NOOK_POSITION 0x5c /* Vec3 */
#define NOOK_MOTION 0x564  /* SceneMotion */
#define NOOK_WALK_TO 0x718 /* Vec3 */
#define NOOK_SCENE_SLOT_RESET 0x08

/* Its events and the states they give. */
#define NOOK_EVENT_1 1
#define NOOK_EVENT_ENDED 8
#define NOOK_STATE_2 2
#define NOOK_STATE_5 5

/* The scene's step 1. */
#define NOOK_STEP_NONE 0
#define NOOK_STEP_WALK 1
#define NOOK_WALK_WAIT_GONE 0
#define NOOK_WALK_GOING 1
#define NOOK_WALK_STANDING 2
#define NOOK_WALK_DISTANCE 0x6000
#define NOOK_LOOK_HEIGHT 0x2000
#define NOOK_MOTION_STAND 0
#define NOOK_MOTION_WALK 2
#define NOOK_MOTION_PRIORITY 2
#define NOOK_MUSIC_DROPPED 0x13
#define NOOK_MUSIC_PRIORITY 0x15
#define NOOK_MUSIC 0x47
#define NOOK_MUSIC_0C 0x7f
#define NOOK_PLAYER 4
#define NOOK_PLAYER_FLAG_RECORD 0x23 /* the current player's record flag cleared as the talk starts */

/* The messages. */
#define NOOK_MESSAGE_FIRST 0x22
#define NOOK_MESSAGE_HOUSE 0xa
#define NOOK_MESSAGE_HOUSE_NEW_TOWN 0xd
#define NOOK_MESSAGE_LOAN_NEW_TOWN 0x1c
#define NOOK_MESSAGE_LOAN_ALONE 0x27
#define NOOK_MESSAGE_LOAN 0xb
#define NOOK_MESSAGE_NO_LOAN 0xf
#define NOOK_MESSAGE_AFTER_LOAN 0xe
#define NOOK_MESSAGE_AFTER_LOAN_NEW 0xc
#define NOOK_MESSAGE_AFTER_NO_LOAN 0x10
#define NOOK_MESSAGE_AFTER_NO_LOAN_NEW 0x11
#define NOOK_LOAN_SLOT 1
#define NOOK_LOAN_FORMAT 10

static u8 *nook_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static TownNookScene *nook_scene(u8 *object)
{
    return (TownNookScene *) (void *) nook_at(object, NOOK_SCENE);
}

static TalkObject *nook_talk(TownNookScene *scene)
{
    return (TalkObject *) (void *) scene->base.talk;
}

/* func_ov068_0226e184 (slot 0x40): its scene's destructor, then the special character's
 * (SpecialSceneObject_DestructBody); the object. */
u8 *TownNook_Destruct(u8 *object)
{
    *(const u8 **) (void *) object = data_ov068_02277574;
    TownNookScene_Destruct(nook_scene(object));
    SpecialSceneObject_DestructBody(object);
    return object;
}
CLEAN_AS(func_ov068_0226e184, TownNook_Destruct)

/* func_ov068_0226e1ac (slot 0x44): the same, then the object freed (Heap_FreeAux). */
u8 *TownNook_DestructDelete(u8 *object)
{
    *(const u8 **) (void *) object = data_ov068_02277574;
    TownNookScene_Destruct(nook_scene(object));
    SpecialSceneObject_DestructBody(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_ov068_0226e1ac, TownNook_DestructDelete)

/* func_ov068_0226e1d8 (slot 0x4c): told of an event: 1 gives state 2, 8 (ended) state 5. */
void TownNook_OnEvent(u8 *object, int code)
{
    switch (code) {
        case NOOK_EVENT_1:
            TownNook_SetState(object, NOOK_STATE_2);
            break;
        case NOOK_EVENT_ENDED:
            TownNook_SetState(object, NOOK_STATE_5);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov068_0226e1d8, TownNook_OnEvent)

/* func_ov068_0226e1fc (slot 0x48): whether the player may act on it: in state 0. */
int TownNook_MayAct(u8 *object)
{
    return *(const s32 *) (const void *) nook_at(object, NOOK_STATE) == 0;
}
CLEAN_AS(func_ov068_0226e1fc, TownNook_MayAct)

/* func_ov068_0226e210 (the scene's step 1, each frame while the talk's link is open): once the
 * talk's window is gone, the music of priority 0x13 dropped and music 0x47 added, the player
 * held (PlayerActorOps_SwitchFlag0e off), and the character walks to 6.0 along x from where it
 * stands; once the walk is done, it stands; once that is done, the talk opens with message 0xd
 * in a new town (else 0xa), the camera looks 2.0 above the character, and the scene goes back
 * to step 0. */
void TownNookScene_WalkAndTalk(TownNookScene *scene)
{
    u8 *owner = scene->owner;
    SceneMotion *motion = (SceneMotion *) (void *) nook_at(owner, NOOK_MOTION);
    switch (scene->state) {
        case NOOK_WALK_WAIT_GONE:
            if (nook_talk(scene)->state != TALK_OBJECT_GONE) {
                break;
            }
            Music_DropPriority(NOOK_MUSIC_DROPPED);
            Music_Add(NOOK_MUSIC_PRIORITY, NOOK_MUSIC, NOOK_MUSIC_0C, 1);
            PlayerActorOps_SwitchFlag0e(0, NOOK_PLAYER);
            {
                Vec3 *to = (Vec3 *) (void *) nook_at(owner, NOOK_WALK_TO);
                *to = *(const Vec3 *) (const void *) nook_at(owner, NOOK_POSITION);
                to->x = (s32) ((u32) to->x + NOOK_WALK_DISTANCE);
                SceneMotion_Request(motion, NOOK_MOTION_WALK, NOOK_MOTION_PRIORITY, to->x, to->z, 0, 0, 0, 0, data_020c80f8,
                                    0);
            }
            scene->state = NOOK_WALK_GOING;
            break;
        case NOOK_WALK_GOING:
            if (SceneMotion_IsDone(motion) != 0 && SceneMotion_Kind(motion) == NOOK_MOTION_WALK) {
                SceneMotion_Request(motion, NOOK_MOTION_STAND, NOOK_MOTION_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                scene->state = NOOK_WALK_STANDING;
            }
            break;
        case NOOK_WALK_STANDING:
            if (SceneMotion_IsDone(motion) != 0 && SceneMotion_Kind(motion) == NOOK_MOTION_STAND) {
                TalkObject *talk = nook_talk(scene);
                u8 message = StartKind_IsNewTown() != 0 ? NOOK_MESSAGE_HOUSE_NEW_TOWN : NOOK_MESSAGE_HOUSE;
                TalkObject_SetMessage(talk, &message, data_ov068_0227733c);
                talk->next_state = TALK_OBJECT_OPENING;
                Vec3 look = *(const Vec3 *) (const void *) nook_at(owner, NOOK_POSITION);
                look.y = (s32) ((u32) look.y + NOOK_LOOK_HEIGHT);
                CameraControl_FocusOn(&look);
                TownNookScene_SetStep(scene, NOOK_STEP_NONE);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov068_0226e210, TownNookScene_WalkAndTalk)

/* func_ov068_0226e3a4: the scene's step set, from its first state. */
void TownNookScene_SetStep(TownNookScene *scene, int step)
{
    scene->step = step;
    scene->state = 0;
}
CLEAN_AS(func_ov068_0226e3a4, TownNookScene_SetStep)

/* func_ov068_0226e3b4 (slot 0x84, once the talk's link has closed): a step that runs once it
 * closes, when there is one, is run, and the scene goes back to step 0. */
void TownNookScene_OnTalkClosed(TownNookScene *scene)
{
    const TownNookStep *step = &data_ov068_02277454[scene->step];
    if (step->each_frame != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, scene);
    TownNookScene_SetStep(scene, NOOK_STEP_NONE);
}
CLEAN_AS(func_ov068_0226e3b4, TownNookScene_OnTalkClosed)

/* func_ov068_0226e404 (slot 0x80, each frame the talk's link stays open): a step that runs
 * each frame, when there is one, is run. */
void TownNookScene_WhileTalkOpen(TownNookScene *scene)
{
    const TownNookStep *step = &data_ov068_02277454[scene->step];
    if (step->each_frame == 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, scene);
}
CLEAN_AS(func_ov068_0226e404, TownNookScene_WhileTalkOpen)

/* func_ov068_0226e448 (the receiver's slot 0x18, the player's answer): nothing. */
void TownNookScene_OnAnswer(void) {}
CLEAN_AS(func_ov068_0226e448, TownNookScene_OnAnswer)

/* func_ov068_0226e44c (the receiver's slot 0x14, a message ended): after message 0x22 the
 * talk is given the message that ends it, its mode cleared and the scene goes to step 1; after
 * 0xa or 0xd, with no loan on the house message 0xf, else the loan put into the talk's slot 1
 * and message 0x1c in a new town, 0x27 with at most one player in the town, else 0xb; after
 * 0x1c, 0x27 or 0xb, message 0xe for an old player in an old town, else 0xc; after 0xf, 0x10 or
 * 0x11 the same way. The messages after the first are of the file "sp_etc_sequence4". */
void TownNookScene_OnMessageEnded(TownNookScene *scene)
{
    TalkObject *talk = nook_talk(scene);
    u8 message = 0;
    switch (((const u8 *) scene)[0x1e]) {
        case NOOK_MESSAGE_FIRST:
            TalkObject_SetMessage(talk, &data_021f43e8, NULL);
            talk->mode = 0;
            TownNookScene_SetStep(scene, NOOK_STEP_WALK);
            break;
        case NOOK_MESSAGE_HOUSE:
        case NOOK_MESSAGE_HOUSE_NEW_TOWN: {
            int loan = HouseRecord_Loan(&data_021ebcd4);
            if (loan == 0) {
                message = NOOK_MESSAGE_NO_LOAN;
            } else {
                SceneBase_PutValue(&scene->base, loan, NOOK_LOAN_SLOT, NOOK_LOAN_FORMAT, 0, 0);
                if (StartKind_IsNewTown() != 0) {
                    message = NOOK_MESSAGE_LOAN_NEW_TOWN;
                } else if (PlayerRecords_CountTown(data_021dc7bc) <= 1) {
                    message = NOOK_MESSAGE_LOAN_ALONE;
                } else {
                    message = NOOK_MESSAGE_LOAN;
                }
            }
            break;
        }
        case NOOK_MESSAGE_LOAN_NEW_TOWN:
        case NOOK_MESSAGE_LOAN_ALONE:
        case NOOK_MESSAGE_LOAN:
            if (StartKind_IsNewPlayer() == 0 && StartKind_IsNewTown() == 0) {
                message = NOOK_MESSAGE_AFTER_LOAN;
            } else {
                message = NOOK_MESSAGE_AFTER_LOAN_NEW;
            }
            break;
        case NOOK_MESSAGE_NO_LOAN:
            if (StartKind_IsNewPlayer() == 0 && StartKind_IsNewTown() == 0) {
                message = NOOK_MESSAGE_AFTER_NO_LOAN;
            } else {
                message = NOOK_MESSAGE_AFTER_NO_LOAN_NEW;
            }
            break;
        default:
            break;
    }
    if (message != 0) {
        TalkObject_SetMessage(talk, &message, data_ov068_0227733c);
    }
}
CLEAN_AS(func_ov068_0226e44c, TownNookScene_OnMessageEnded)

/* func_ov068_0226e570 (slot 0x78, the talk starting): the current player's record flag 0x23
 * cleared (when there is a current record), and the talk starts with message 0x22 of
 * "sp_etc_sequence4". */
void TownNookScene_StartTalk(TownNookScene *scene, TownNookTalkStart *start)
{
    (void) scene;
    u8 *record = PlayerRecords_Current();
    if (record != NULL) {
        PlayerRecord_ClearFlag(record, NOOK_PLAYER_FLAG_RECORD);
    }
    start->name = data_ov068_0227733c;
    start->message = NOOK_MESSAGE_FIRST;
}
CLEAN_AS(func_ov068_0226e570, TownNookScene_StartTalk)

/* func_ov068_0226e598: the scene reset (its slot 0x08) and given its character. */
void TownNookScene_Begin(TownNookScene *scene, u8 *owner)
{
    u32 vtable = *(const u32 *) (const void *) scene;
    uintptr_t reset = *(const u32 *) (uintptr_t) (vtable + NOOK_SCENE_SLOT_RESET);
    ((void (*)(TownNookScene *)) reset)(scene);
    scene->owner = owner;
}
CLEAN_AS(func_ov068_0226e598, TownNookScene_Begin)

/* func_ov068_0226e5b4 (the scene's slot 0x04): the destructor of main's class 0x020d9ff8, then
 * the scene freed (Heap_OperatorDeleteB). */
TownNookScene *TownNookScene_DestructDelete(TownNookScene *scene)
{
    *(const u8 **) (void *) scene = data_ov068_022774e4;
    Obj020d9ff8_DestructBody(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_ov068_0226e5b4, TownNookScene_DestructDelete)

/* func_ov068_0226e5d4 (the scene's slot 0x00): the destructor of main's class 0x020d9ff8. */
TownNookScene *TownNookScene_Destruct(TownNookScene *scene)
{
    *(const u8 **) (void *) scene = data_ov068_022774e4;
    Obj020d9ff8_DestructBody(scene);
    return scene;
}
CLEAN_AS(func_ov068_0226e5d4, TownNookScene_Destruct)

/* func_ov068_0226e5ec: the constructor: a scene of main's class 0x020d9ff8 given this class's
 * vtable. */
TownNookScene *TownNookScene_Construct(TownNookScene *scene)
{
    Obj020d9ff8_Construct(scene);
    *(const u8 **) (void *) scene = data_ov068_022774e4;
    return scene;
}
CLEAN_AS(func_ov068_0226e5ec, TownNookScene_Construct)

/* ---- The character's states, vtable slots and creation */

/* The parts of the character read here (besides those above). */
#define NOOK_PERSON 0xea      /* u16: its person code */
#define NOOK_YAW 0x8e         /* s16: where it faces */
#define NOOK_MOVER 0x350      /* SceneMover */
#define NOOK_HELD_FLAGS 0x4e8 /* u32: the scene object's flags (2: held, scene_action.h) */
#define NOOK_ACTION 0x618     /* SceneAction */
#define NOOK_START_YAW 0x714  /* s16: where it faced when it started */
#define NOOK_TIMER 0x724      /* u8: frames left (Countdown_Tick8) */
#define NOOK_SIZE 0x728
#define NOOK_HELD 2
#define NOOK_NO_PERSON 0xfff1
#define NOOK_SCENE_SLOT_RESET_INDEX 2 /* the talk scene's vtable slot 0x08 */

/* Where the members of the scene object lie (scene_object_members.h). */
#define NOOK_MODEL 0xec
#define NOOK_STANDARD_ANIMS 0x2a0
#define NOOK_FACE 0x2ac
#define NOOK_ANIM 0x334
#define NOOK_PROBE 0x3a8
#define NOOK_VALUE_3AA 0x3aa
#define NOOK_LOOK 0x3b0
#define NOOK_TALK_STATE 0x418
#define NOOK_EFFECTS 0x420
#define NOOK_COLLIDER 0x49c
#define NOOK_CARRIER 0x4cc
#define NOOK_EMITTER 0x514
#define NOOK_FOOTSTEPS 0x558
#define NOOK_HEAP 0x640

/* The motions it asks for (scene_motion_kinds.h) and their priority. */
#define NOOK_MOTION_TURN 3
#define NOOK_MOTION_LEAVE_PRIORITY 1
#define NOOK_LEAVE_X (-0x2000)
#define NOOK_LEAVE_Z 0xa000
#define NOOK_LEAVE_FRAMES 0x3c
#define NOOK_END_FRAMES 10

/* The player's walk in state 2: 2.0 south of its starting point, at this acceleration. */
#define NOOK_PLAYER_STEP_Z 0x2000
#define NOOK_PLAYER_ACCEL 0x400

/* The music asked for. */
#define NOOK_MUSIC_START_VALUE 0xf
#define NOOK_MUSIC_TALKED_VALUE 0x3c
#define NOOK_MUSIC_END_PRIORITY 0x12
#define NOOK_MUSIC_END_VALUE 5
#define NOOK_MUSIC_END_FRAMES 5

/* The player's record flag cleared at the start for an old player in an old town. */
#define NOOK_PLAYER_FLAG_START 1

/* Its walking pace 2 (scene_mover.h). */
#define NOOK_PACE 2
#define NOOK_PACE_SPEED 0x399
#define NOOK_PACE_SPEED_UP 0x133
#define NOOK_PACE_SLOW_DOWN 0x199

/* Its four looks, one per level of Nook's store (NookStore_Level): the person codes
 * 0xd019-0xd01c and the files "npc_sp/model/rcn", "rcc", "rcs" and "rcd" (.nsbmd and
 * _tex.nsbtx). */
#define NOOK_LOOKS 4
#define NOOK_PERSON_FIRST 0xd019

/* A state's start and update (filled when the overlay starts, from data_ov068_02277340 on). */
typedef struct TownNookStateFns {
    MemberPointer start;
    MemberPointer update;
} TownNookStateFns;

static_assert(sizeof(TownNookStateFns) == 0x10, "state row");

extern TownNookStateFns data_ov068_02278658[TOWN_NOOK_STATES];
/* The model and texture file names, one per look. */
extern const char *const data_ov068_022773a8[NOOK_LOOKS];
extern const char *const data_ov068_022773b8[NOOK_LOOKS];
/* The person codes of the looks (a function-local static of TownNook_Init, built once and
 * registered for destruction with the records at 0x02278628-0x02278658), and its guard. */
extern u32 data_ov068_0227861c;
extern u16 data_ov068_02278620[NOOK_LOOKS];
extern u8 data_ov068_02278628[];
extern u8 data_ov068_02278634[];
extern u8 data_ov068_02278640[];
extern u8 data_ov068_0227864c[];
/* Nook's store. */
extern NookStore data_021f395c;
/* The vtable of the class 0x020da088 (special_scene_object.h). */
extern const u8 data_020da088[];

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of a person code (TrivialObject_DestructItemCode), as the game registers it. */
extern void func_020051b0(void *item);

static SceneMotion *nook_motion(u8 *object)
{
    return (SceneMotion *) (void *) nook_at(object, NOOK_MOTION);
}

static u8 *nook_timer(u8 *object)
{
    return nook_at(object, NOOK_TIMER);
}

static SceneAction *nook_action(u8 *object)
{
    return (SceneAction *) (void *) nook_at(object, NOOK_ACTION);
}

/* The talk scene's vtable slot 0x08 (its reset), called virtually. */
static void nook_reset_scene(TownNookScene *scene)
{
    const u32 *vtable = *(const u32 *const *) (const void *) scene;
    ((void (*)(TownNookScene *))(uintptr_t) vtable[NOOK_SCENE_SLOT_RESET_INDEX])(scene);
}

/* func_ov068_0226e604 (update of TOWN_NOOK_END): once its timer runs out, the music of
 * priority 0x13 is dropped, value 5 added for 5 frames with priority 0x12, and it is deleted. */
int TownNook_UpdateEnd(u8 *object)
{
    if (Countdown_Tick8(nook_timer(object)) == 0) {
        Music_DropPriority(NOOK_MUSIC_DROPPED);
        Music_AddValue(NOOK_MUSIC_END_PRIORITY, NOOK_MUSIC_END_VALUE, NOOK_MUSIC_END_FRAMES);
        Process_RequestDelete((Process *) (void *) object);
    }
    return 1;
}
CLEAN_AS(func_ov068_0226e604, TownNook_UpdateEnd)

/* func_ov068_0226e638 (start of TOWN_NOOK_END): 10 frames. */
int TownNook_StartEnd(u8 *object)
{
    *nook_timer(object) = NOOK_END_FRAMES;
    return 1;
}
CLEAN_AS(func_ov068_0226e638, TownNook_StartEnd)

/* func_ov068_0226e648 (update of TOWN_NOOK_LEAVE): once its walk is done or its timer runs out
 * (the walk is asked first, so the timer only counts while it walks), its event is finished
 * (EventQueue_FinishObjectEvent) and, when there is a current player, the kind of start is
 * cleared. This is done again each frame until the event queue ends the state. */
int TownNook_UpdateLeave(u8 *object)
{
    if (SceneMotion_IsDone(nook_motion(object)) != 0 || Countdown_Tick8(nook_timer(object)) == 0) {
        EventQueue_FinishObjectEvent(object);
        if (PlayerRecords_Current() != NULL) {
            StartKind_Clear();
        }
    }
    return 1;
}
CLEAN_AS(func_ov068_0226e648, TownNook_UpdateLeave)

/* func_ov068_0226e688 (start of TOWN_NOOK_LEAVE): it walks (motion kind 2, priority 1) to 2.0
 * west and 10.0 south of where it stands (kept at 0x718), for at most 60 frames. */
int TownNook_StartLeave(u8 *object)
{
    Vec3 *to = (Vec3 *) (void *) nook_at(object, NOOK_WALK_TO);
    *to = *(const Vec3 *) (const void *) nook_at(object, NOOK_POSITION);
    to->x += NOOK_LEAVE_X;
    to->z += NOOK_LEAVE_Z;
    SceneMotion_Request(nook_motion(object), NOOK_MOTION_WALK, NOOK_MOTION_LEAVE_PRIORITY, to->x, to->z, 0, 0, 0, 0,
                        data_020c80f8, 0);
    *nook_timer(object) = NOOK_LEAVE_FRAMES;
    return 1;
}
CLEAN_AS(func_ov068_0226e688, TownNook_StartLeave)

/* func_ov068_0226e708 (update of TOWN_NOOK_TURN): once the turn is done, TOWN_NOOK_LEAVE. */
int TownNook_UpdateTurn(u8 *object)
{
    SceneMotion *motion = nook_motion(object);
    if (SceneMotion_Kind(motion) == NOOK_MOTION_TURN && SceneMotion_IsDone(motion) != 0) {
        TownNook_SetState(object, TOWN_NOOK_LEAVE);
    }
    return 1;
}
CLEAN_AS(func_ov068_0226e708, TownNook_UpdateTurn)

/* func_ov068_0226e738 (start of TOWN_NOOK_TURN): a turn (motion kind 3, priority 1). */
int TownNook_StartTurn(u8 *object)
{
    SceneMotion_Request(nook_motion(object), NOOK_MOTION_TURN, NOOK_MOTION_LEAVE_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov068_0226e738, TownNook_StartTurn)

/* func_ov068_0226e76c (update of TOWN_NOOK_CALL_PLAYER): once the player is no longer busy, the
 * talk scene is reset (its vtable slot 0x08), given the player's object as its motion argument,
 * and TOWN_NOOK_TALK follows. */
int TownNook_UpdateCallPlayer(u8 *object)
{
    if (PlayerActorOps_IsBusy(NOOK_PLAYER) == 0) {
        TownNookScene *scene = nook_scene(object);
        nook_reset_scene(scene);
        SceneBase_SetMotionArg(&scene->base, SceneObject_ActorObject(object, NOOK_PLAYER));
        TownNook_SetState(object, TOWN_NOOK_TALK);
    }
    return 1;
}
CLEAN_AS(func_ov068_0226e76c, TownNook_UpdateCallPlayer)

/* func_ov068_0226e7ac (start of TOWN_NOOK_CALL_PLAYER): the player walks to 2.0 south of its
 * starting point. */
int TownNook_StartCallPlayer(void)
{
    Vec3 point = *PlayerActorOps_StartPosition(NOOK_PLAYER);
    point.z += NOOK_PLAYER_STEP_Z;
    PlayerActorOps_MoveTo(&point, NOOK_PLAYER_ACCEL, NOOK_PLAYER);
    return 1;
}
CLEAN_AS(func_ov068_0226e7ac, TownNook_StartCallPlayer)

/* func_ov068_0226e7e4 (update of TOWN_NOOK_TALK): once its action has ended, the camera's mode
 * is reset, value 0x3c added to the music of priority 0x13, music 0x47 dropped, and
 * TOWN_NOOK_TURN follows. */
int TownNook_UpdateTalk(u8 *object)
{
    if (SceneAction_IsBusy(nook_action(object)) == 0) {
        CameraControl_ResetMode();
        Music_AddValue(NOOK_MUSIC_DROPPED, NOOK_MUSIC_TALKED_VALUE, 0);
        Music_DropMusic(NOOK_MUSIC);
        TownNook_SetState(object, TOWN_NOOK_TURN);
    }
    return 1;
}
CLEAN_AS(func_ov068_0226e7e4, TownNook_UpdateTalk)

/* func_ov068_0226e81c (start of TOWN_NOOK_TALK): it turns to its talk scene's other speaker
 * (angle 0 when there is none) and talks, without moving the camera. */
int TownNook_StartTalk(u8 *object)
{
    int other = SceneBase_MotionArg(&nook_scene(object)->base);
    int angle = 0;
    if (other != 0) {
        angle = SceneObject_YawTo(object, (u8 *) (uintptr_t) (u32) other);
    }
    SceneAction_RequestTurnAndTalk(nook_action(object), 0, angle, 1);
    return 1;
}
CLEAN_AS(func_ov068_0226e81c, TownNook_StartTalk)

/* func_ov068_0226e854 (update of TOWN_NOOK_WAIT): once the event queue gives it an event of
 * kind 6, the player's flag 0x0e is set on. */
int TownNook_UpdateWait(u8 *object)
{
    if (EventQueue_RequestKind6(object, 0) != 0) {
        PlayerActorOps_SwitchFlag0e(1, NOOK_PLAYER);
    }
    return 1;
}
CLEAN_AS(func_ov068_0226e854, TownNook_UpdateWait)

/* func_ov068_0226e874 (start of TOWN_NOOK_WAIT) */
int TownNook_StartWait(void)
{
    return 1;
}
CLEAN_AS(func_ov068_0226e874, TownNook_StartWait)

/* func_ov068_0226e878: the state's start run (when it has one); unless it answers 0 the state
 * is taken.
 * REQUIRES: `state` is one of the six. */
void TownNook_SetState(u8 *object, int state)
{
    const TownNookStateFns *fns = &data_ov068_02278658[state];
    int taken = 1;
    if (fns->start.function != 0) {
        taken = MemberPointer_CallInt(&fns->start, object);
    }
    if (taken != 0) {
        *(s32 *) (void *) nook_at(object, NOOK_STATE) = state;
    }
}
CLEAN_AS(func_ov068_0226e878, TownNook_SetState)

/* func_ov068_0226e8bc (slot 0x68): the state's update (when it has one); its answer, else 0.
 * REQUIRES: the state is one of the six. */
int TownNook_Update(u8 *object)
{
    s32 state = *(const s32 *) (const void *) nook_at(object, NOOK_STATE);
    const TownNookStateFns *fns = &data_ov068_02278658[state];
    if (fns->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&fns->update, object);
}
CLEAN_AS(func_ov068_0226e8bc, TownNook_Update)

/* func_ov068_0226e908 (slot 0x70): the model's file name for the store's level.
 * REQUIRES: the level is 0-3. */
int TownNook_ModelName(void)
{
    return (int) (uintptr_t) data_ov068_022773a8[NookStore_Level(&data_021f395c)];
}
CLEAN_AS(func_ov068_0226e908, TownNook_ModelName)

/* func_ov068_0226e928 (slot 0x6c): the texture's file name for the store's level.
 * REQUIRES: the level is 0-3. */
int TownNook_TextureName(void)
{
    return (int) (uintptr_t) data_ov068_022773b8[NookStore_Level(&data_021f395c)];
}
CLEAN_AS(func_ov068_0226e928, TownNook_TextureName)

/* func_ov068_0226e948 (slot 0x00): unless the base class refuses to start, TOWN_NOOK_WAIT; it
 * notes where it faces, is held (flag 2 at 0x4e8), clears the current player's record flag 1
 * for an old player in an old town, and adds value 0xf to the music of priority 0x13. Whether
 * it started. */
int TownNook_Start(u8 *object)
{
    if (SpecialSceneObject_Start(object) == 0) {
        return 0;
    }
    TownNook_SetState(object, TOWN_NOOK_WAIT);
    *(s16 *) (void *) nook_at(object, NOOK_START_YAW) = *(const s16 *) (const void *) nook_at(object, NOOK_YAW);
    *(u32 *) (void *) nook_at(object, NOOK_HELD_FLAGS) |= NOOK_HELD;
    u8 *record = PlayerRecords_Current();
    if (record != NULL && StartKind_IsNewPlayer() == 0 && StartKind_IsNewTown() == 0) {
        PlayerRecord_ClearFlag(record, NOOK_PLAYER_FLAG_START);
    }
    Music_AddValue(NOOK_MUSIC_DROPPED, NOOK_MUSIC_START_VALUE, 0);
    return 1;
}
CLEAN_AS(func_ov068_0226e948, TownNook_Start)

/* The person codes of the looks, built and registered (with func_020051b0) the first time. */
static void nook_init_persons(void)
{
    static u8 *const records[NOOK_LOOKS] = {
        data_ov068_0227864c,
        data_ov068_02278640,
        data_ov068_02278628,
        data_ov068_02278634,
    };
    if ((data_ov068_0227861c & 1) != 0) {
        return;
    }
    for (int i = 0; i < NOOK_LOOKS; i++) {
        data_ov068_02278620[i] = (u16) (NOOK_PERSON_FIRST + i);
        __register_global_object(&data_ov068_02278620[i], (void *) func_020051b0, records[i]);
    }
    data_ov068_0227861c |= 1;
}

/* func_ov068_0226e9b0 (slot 0x04): unless the base class refuses, it takes the person code of
 * the store's level, its scene is its talk (which gets it as its owner), and its walking pace
 * 2 is set. Whether it was set up.
 * REQUIRES: the store's level is 0-3. */
int TownNook_Init(u8 *object)
{
    nook_init_persons();
    if (SpecialSceneObject_Init(object) == 0) {
        return 0;
    }
    SceneObject_SetPerson(object, &data_ov068_02278620[NookStore_Level(&data_021f395c)]);
    TownNookScene *scene = nook_scene(object);
    SceneObject_SetScene(object, &scene->base);
    TownNookScene_Begin(scene, object);
    SceneMover_SetPace((SceneMover *) (void *) nook_at(object, NOOK_MOVER), NOOK_PACE, NOOK_PACE_SPEED, NOOK_PACE_SPEED_UP,
                       NOOK_PACE_SLOW_DOWN);
    return 1;
}
CLEAN_AS(func_ov068_0226e9b0, TownNook_Init)

/* func_ov068_0226eaac (its record's create function, at 0x0227743c): a zeroed block of 0x728
 * bytes from the auxiliary heap, constructed: the scene object base, the class 0x020d8c64's
 * vtable and members in place order (no person yet, 0xfff1), the class 0x020da088's vtable and
 * heap link, then the class's vtable and its talk scene. Null when there is no room. */
u8 *TownNook_Create(void)
{
    u8 *object = (u8 *) Heap_AllocAuxZeroed(NOOK_SIZE);
    if (object == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) nook_at(object, NOOK_PERSON) = NOOK_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) nook_at(object, NOOK_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) nook_at(object, NOOK_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) nook_at(object, NOOK_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) nook_at(object, NOOK_ANIM));
    SceneMover_Construct((SceneMover *) (void *) nook_at(object, NOOK_MOVER));
    SceneProbe_Construct(nook_at(object, NOOK_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) nook_at(object, NOOK_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) nook_at(object, NOOK_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) nook_at(object, NOOK_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) nook_at(object, NOOK_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) nook_at(object, NOOK_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) nook_at(object, NOOK_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) nook_at(object, NOOK_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) nook_at(object, NOOK_FOOTSTEPS));
    SceneMotion_Construct(nook_motion(object));
    SceneAction_Construct(nook_action(object));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) nook_at(object, NOOK_HEAP));
    *(const u8 **) (void *) object = data_ov068_02277574;
    TownNookScene_Construct(nook_scene(object));
    return object;
}
CLEAN_AS(func_ov068_0226eaac, TownNook_Create)
