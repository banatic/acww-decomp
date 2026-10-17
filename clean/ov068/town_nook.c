/* The character who meets a new player in the town, and its talk scene (town_nook.h). */
#include "town_nook.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/camera_modes.h"
#include "main/house_record.h"
#include "main/music_queue.h"
#include "main/obj_020d9ff8.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
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

/* The character's state changed to `state` (its start run first; kept when that agrees). */
extern void func_ov068_0226e878(u8 *object, int state);

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
            func_ov068_0226e878(object, NOOK_STATE_2);
            break;
        case NOOK_EVENT_ENDED:
            func_ov068_0226e878(object, NOOK_STATE_5);
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
