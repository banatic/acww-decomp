/* The taxi driver of overlay 51: its object, its states and its creation (taxi_driver.h). */
#include "taxi_driver.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/act_effects.h"
#include "main/block_020b220c.h"
#include "main/camera_control.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/global_021cfc98.h"
#include "main/layered_model.h"
#include "main/main_random.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_exit.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_sound.h"
#include "main/scene_standard_anims.h"
#include "main/scene_tables.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/screen_transition.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/start_kind.h"
#include "main/state_block.h"
#include "main/talk_object.h"
#include "ov068/taxi.h"
#include "taxi_driver_talk.h"

static_assert(sizeof(TaxiDriverStep) == 0x10, "a state's functions");
static_assert(offsetof(TaxiDriver, state) == 0x654, "state");
static_assert(offsetof(TaxiDriver, talk) == 0x658, "talk scene");
static_assert(offsetof(TaxiDriver, points) == 0x714, "points");
static_assert(offsetof(TaxiDriver, wait) == 0x718, "wait");
static_assert(offsetof(TaxiDriver, anim_wait) == 0x71a, "animation wait");
static_assert(sizeof(TaxiDriver) == 0x71c, "the size TaxiDriver_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define TD_MODEL_FRAME 0x190    /* fx32: its model's animation frame, 20.12 */
#define TD_PERSON 0xea          /* u16: its person code */
#define TD_MODEL 0xec           /* LayeredModel */
#define TD_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TD_FACE 0x2ac           /* SceneFace */
#define TD_ANIM 0x334           /* SpeakerAnim */
#define TD_MOVER 0x350          /* SceneMover */
#define TD_PROBE 0x3a8          /* the probe ahead */
#define TD_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define TD_LOOK 0x3b0           /* SceneLook */
#define TD_TALK_STATE 0x418     /* SceneTalkState */
#define TD_EFFECTS 0x420        /* ActEffects */
#define TD_COLLIDER 0x49c       /* CollisionContacts */
#define TD_CARRIER 0x4cc        /* FieldOwnedBody */
#define TD_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define TD_EMITTER 0x514        /* SoundEmitterObject */
#define TD_FOOTSTEPS 0x558      /* Footsteps */
#define TD_MOTION 0x564         /* SceneMotion */
#define TD_ACTION 0x618         /* SceneAction */
#define TD_HEAP 0x640           /* PoolLink */

#define TD_NO_PERSON 0xfff1
#define TD_HELD 2

/* Its first standard animation, and the one it plays once the taxi's figure has started (the
 * ones overlay 68's handle follows, ov068/taxi.c). */
#define TD_FIRST_ANIM 0xfb
#define TD_FIGURE_ANIM 0x8f
#define TD_FIGURE_ANIM_DELAY 10

/* State 0's wait, in frames, once the screen is shown. */
#define TD_WAIT_FRAMES 0x29

/* State 3's start of the game: the screen shown at once (no transition) keeping the music,
 * the start's state block flag cleared, and the scene entered: scene 0 in front of the town's
 * building 0x5000 (player parameter 0x400000, angle 0x8000, arguments 3 and 2). */
#define TD_STATE_BLOCK_NEW_TOWN 0
#define TD_STATE_BLOCK_PLAYER_0 6
#define TD_STATE_BLOCK_NEW_PLAYER 1
#define TD_START_FLAG 0x12
#define TD_EXIT_SCENE 0
#define TD_EXIT_PLAYER_PARAM 0x400000
#define TD_EXIT_ANGLE (-0x8000)
#define TD_EXIT_CHANGE_ARG 3
#define TD_EXIT_NEXT_ARG 2

/* State 4's close of the screen: a fade to black over 15 frames. */
#define TD_CLOSE_FRAMES 15

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov051_0226193c[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* The one started last (not cleared when it leaves). */
extern TaxiDriver *data_ov051_02261b80;
/* Its states' functions (filled at start-up by __sinit_ov051_0226150c). */
extern TaxiDriverStep data_ov051_02261ba8[TAXI_DRIVER_STATES];
/* Its model's and texture's file names: "npc_sp/model/wip.nsbmd", "npc_sp/model/wip_tex.nsbtx". */
extern const char data_ov051_022617b0[];
extern const char data_ov051_022617e0[];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The screen's transition (its state, the first byte), the game's state block. */
extern u8 data_021c75b8;
extern StateBlock data_021dc7a8;

static u8 *td_part(TaxiDriver *driver, u32 offset)
{
    return driver->base + offset;
}

/* func_ov051_02260420 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
void *TaxiDriver_Destroy(void *object)
{
    TaxiDriver *driver = object;
    *(const u8 **) object = data_ov051_0226193c;
    TaxiDriverTalk_Destroy(&driver->talk);
    SpecialSceneObject_DestructBody(driver);
    return driver;
}
CLEAN_AS(func_ov051_02260420, TaxiDriver_Destroy)

/* func_ov051_02260448 (vtable slot 0x44): the same, then the object freed. */
void *TaxiDriver_Delete(void *object)
{
    TaxiDriver *driver = object;
    *(const u8 **) object = data_ov051_0226193c;
    TaxiDriverTalk_Destroy(&driver->talk);
    SpecialSceneObject_DestructBody(driver);
    Heap_FreeAux(driver);
    return driver;
}
CLEAN_AS(func_ov051_02260448, TaxiDriver_Delete)

/* func_ov051_02260474: the number of the animation the current one's animation player plays
 * (overlay 68's taxi handle plays the matching one).
 * REQUIRES: one was started. */
int TaxiDriver_CurrentAnim(void)
{
    return SpeakerAnim_Number((SpeakerAnim *) (void *) td_part(data_ov051_02261b80, TD_ANIM), 0);
}
CLEAN_AS(func_ov051_02260474, TaxiDriver_CurrentAnim)

/* func_ov051_02260490: the whole frame of the current one's animation (its word at 0x190, cut
 * to 16 bits).
 * REQUIRES: one was started. */
unsigned int TaxiDriver_CurrentFrame(void)
{
    u32 frame = *(const u32 *) (const void *) td_part(data_ov051_02261b80, TD_MODEL_FRAME);
    return (frame << 4) >> 16;
}
CLEAN_AS(func_ov051_02260490, TaxiDriver_CurrentFrame)

/* func_ov051_02261088 (state 4's update): once talk 0 is closed: one time in four the taxi's
 * figure starts, the camera's stage 3 starts and its animation 0x8f is due in 10 frames; then
 * the screen closes (a fade to black over 15 frames), the scene's sound stops and state 3
 * follows. 1. */
int TaxiDriver_UpdateLeave(TaxiDriver *driver)
{
    if (TalkObject_Get(0)->state != TALK_OBJECT_CLOSED) {
        return 1;
    }
    if (MainRandom_Below(4) == 0) {
        Taxi_StartFigure();
        CameraControl_StartStage3();
        driver->anim_wait = TD_FIGURE_ANIM_DELAY;
    }
    ScreenTransition_Close(SCREEN_TRANSITION_BLACK, TD_CLOSE_FRAMES);
    SceneSound_Stop();
    TaxiDriver_SetState(driver, TAXI_DRIVER_ARRIVE);
    return 1;
}
CLEAN_AS(func_ov051_02261088, TaxiDriver_UpdateLeave)

/* func_ov051_022610d0 (state 4's entry): 1. */
int TaxiDriver_EnterLeave(void)
{
    return 1;
}
CLEAN_AS(func_ov051_022610d0, TaxiDriver_EnterLeave)

/* func_ov051_022610d4 (state 3's update): once the screen is closed: it is shown at once
 * (keeping the music) and flag 0x4b18 of the block 0x020b220c set; starting as player 0 or a
 * new town, the clock's date and time are kept (Global021cfc98_CopyIn); the state block is
 * started in mode 0 (a new town), 6 (as player 0) or 1 (a new player) and finished, with any
 * other start not at all; its flag 0x12 is cleared; main's entry record enters scene 0 in
 * front of the town's building 0x5000; state 2. 1.
 * REQUIRES: the town has building 0x5000. Without it the original enters the scene at whatever
 * its stack held; here at the point (0, 0, 0). */
int TaxiDriver_UpdateArrive(TaxiDriver *driver)
{
    if (data_021c75b8 != SCREEN_TRANSITION_CLOSED) {
        return 1;
    }
    ScreenTransition_Open(SCREEN_TRANSITION_NONE, 0, 1);
    Block020b220c_SetFlag4b18();

    if (StartKind_IsPlayer0() || StartKind_IsNewTown()) {
        DateTime now = {0};
        DateTime_Now(&now);
        Global021cfc98_CopyIn(&now);
    }

    if (StartKind_IsNewTown()) {
        StateBlock_Start(&data_021dc7a8, TD_STATE_BLOCK_NEW_TOWN);
        StateBlock_FinishStart(&data_021dc7a8);
    } else if (StartKind_IsPlayer0()) {
        StateBlock_Start(&data_021dc7a8, TD_STATE_BLOCK_PLAYER_0);
        StateBlock_FinishStart(&data_021dc7a8);
    } else if (StartKind_IsNewPlayer()) {
        StateBlock_Start(&data_021dc7a8, TD_STATE_BLOCK_NEW_PLAYER);
        StateBlock_FinishStart(&data_021dc7a8);
    }

    StateBlock_ClearFlag((u32 *) (void *) &data_021dc7a8, TD_START_FLAG);
    int front[3] = {0, 0, 0};
    AcreMap_FindBuilding5000Front((int) AcreMap_Town(), front, NULL, NULL);
    SceneExit_SetTo((SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord(), TD_EXIT_SCENE,
                    (const Vec3 *) (const void *) front, TD_EXIT_PLAYER_PARAM, TD_EXIT_ANGLE, TD_EXIT_CHANGE_ARG,
                    TD_EXIT_NEXT_ARG);
    TaxiDriver_SetState(driver, TAXI_DRIVER_DONE);
    return 1;
}
CLEAN_AS(func_ov051_022610d4, TaxiDriver_UpdateArrive)

/* func_ov051_022611b4 (state 3's entry): 1. */
int TaxiDriver_EnterArrive(void)
{
    return 1;
}
CLEAN_AS(func_ov051_022611b4, TaxiDriver_EnterArrive)

/* func_ov051_022611b8 (state 2's update): nothing. 1. */
int TaxiDriver_UpdateDone(void)
{
    return 1;
}
CLEAN_AS(func_ov051_022611b8, TaxiDriver_UpdateDone)

/* func_ov051_022611bc (state 2's entry): 1. */
int TaxiDriver_EnterDone(void)
{
    return 1;
}
CLEAN_AS(func_ov051_022611bc, TaxiDriver_EnterDone)

/* func_ov051_022611c0 (state 1's update): nothing; the talk scene leads. 1. */
int TaxiDriver_UpdateTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov051_022611c0, TaxiDriver_UpdateTalk)

/* func_ov051_022611c4 (state 1's entry): it talks (resetting its motion). 1. */
int TaxiDriver_EnterTalk(TaxiDriver *driver)
{
    SceneAction_RequestTalk((SceneAction *) (void *) td_part(driver, TD_ACTION), 1, 0);
    return 1;
}
CLEAN_AS(func_ov051_022611c4, TaxiDriver_EnterTalk)

/* func_ov051_022611e0 (state 0's update): while the screen is shown, its wait counts down;
 * at 0 it talks (state 1). 1. */
int TaxiDriver_UpdateWait(TaxiDriver *driver)
{
    if (data_021c75b8 == SCREEN_TRANSITION_SHOWN && Countdown_Tick16(&driver->wait) == 0) {
        TaxiDriver_SetState(driver, TAXI_DRIVER_TALK);
    }
    return 1;
}
CLEAN_AS(func_ov051_022611e0, TaxiDriver_UpdateWait)

/* func_ov051_0226121c (state 0's entry): 1. */
int TaxiDriver_EnterWait(void)
{
    return 1;
}
CLEAN_AS(func_ov051_0226121c, TaxiDriver_EnterWait)

/* func_ov051_02261220 (vtable slot 0x9c): 10. */
int TaxiDriver_SoundNumber(void)
{
    return 10;
}
CLEAN_AS(func_ov051_02261220, TaxiDriver_SoundNumber)

/* func_ov051_02261224 (vtable slot 0x84, the sound of an action's start): none, 0xffff. */
int TaxiDriver_ActionSound(void)
{
    return 0xffff;
}
CLEAN_AS(func_ov051_02261224, TaxiDriver_ActionSound)

/* func_ov051_0226122c: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 4 (the table is not bounded). */
void TaxiDriver_SetState(TaxiDriver *driver, int state)
{
    const TaxiDriverStep *step = &data_ov051_02261ba8[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, driver);
    }
    if (taken != 0) {
        driver->state = state;
    }
}
CLEAN_AS(func_ov051_0226122c, TaxiDriver_SetState)

/* func_ov051_02261270 (vtable slot 0x68, each frame): its state's update when it has one; then
 * when the wait for its animation reaches 1 (counting down), its motion takes animation 0x8f
 * (priority 1, mode 1). The update's answer, else 0.
 * REQUIRES: its state is 0 to 4. */
int TaxiDriver_Update(TaxiDriver *driver)
{
    int result = 0;
    const TaxiDriverStep *step = &data_ov051_02261ba8[driver->state];
    if (step->update.function != 0) {
        result = MemberPointer_CallInt(&step->update, driver);
    }
    if (Countdown_Tick8(&driver->anim_wait) == 1) {
        SceneMotion_RequestAnimation((SceneMotion *) (void *) td_part(driver, TD_MOTION), 1, TD_FIGURE_ANIM, 1, data_020c80f8,
                                     0);
    }
    return result;
}
CLEAN_AS(func_ov051_02261270, TaxiDriver_Update)

/* func_ov051_022612f0 (vtable slot 0x70): its model's file name, "npc_sp/model/wip.nsbmd". */
int TaxiDriver_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov051_022617b0;
}
CLEAN_AS(func_ov051_022612f0, TaxiDriver_ModelName)

/* func_ov051_022612f8 (vtable slot 0x6c): its texture's file name,
 * "npc_sp/model/wip_tex.nsbtx". */
int TaxiDriver_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov051_022617e0;
}
CLEAN_AS(func_ov051_022612f8, TaxiDriver_TextureName)

/* func_ov051_02261300 (vtable slot 0x0c, its leaving): unless the special character refuses,
 * the event queue's flag 1 is cleared. Whether it left.
 * QUIRK: data_ov051_02261b80 keeps pointing to it. */
int TaxiDriver_Leave(void *driver)
{
    if (!SpecialSceneObject_Leave(driver)) {
        return 0;
    }
    EventQueue_ClearFlag1();
    return 1;
}
CLEAN_AS(func_ov051_02261300, TaxiDriver_Leave)

/* func_ov051_0226131c (vtable slot 0x00, its start): unless the special character refuses to
 * start, it becomes the current one, waits (state 0) and is held (flag 2 at 0x4e8); the event
 * queue's flag 1 is set and its wait is 0x29 frames. Whether it started. */
int TaxiDriver_Start(TaxiDriver *driver)
{
    if (SpecialSceneObject_Start(driver) == 0) {
        return 0;
    }
    data_ov051_02261b80 = driver;
    TaxiDriver_SetState(driver, TAXI_DRIVER_WAIT);
    *(u32 *) (void *) td_part(driver, TD_HELD_FLAGS) |= TD_HELD;
    EventQueue_SetFlag1();
    driver->wait = TD_WAIT_FRAMES;
    return 1;
}
CLEAN_AS(func_ov051_0226131c, TaxiDriver_Start)

/* func_ov051_02261364 (vtable slot 0x04, its set-up): unless the special character refuses,
 * its talk scene becomes its scene and gets it as its owner, and its first standard animation
 * is 0xfb. Whether it was set up. */
int TaxiDriver_Init(TaxiDriver *driver)
{
    if (SpecialSceneObject_Init(driver) == 0) {
        return 0;
    }
    SceneObject_SetScene(driver->base, &driver->talk.base);
    TaxiDriverTalk_Begin(&driver->talk, driver);
    SceneStandardAnims_SetFirst((SceneStandardAnims *) (void *) td_part(driver, TD_STANDARD_ANIMS), TD_FIRST_ANIM);
    return 1;
}
CLEAN_AS(func_ov051_02261364, TaxiDriver_Init)

/* func_ov051_022613a4 (the create function its record at 0x022617c8 names): a zeroed block of
 * 0x71c bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *TaxiDriver_Create(void)
{
    TaxiDriver *driver = (TaxiDriver *) Heap_AllocAuxZeroed(sizeof(TaxiDriver));
    if (driver == NULL) {
        return NULL;
    }
    u8 *object = driver->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) td_part(driver, TD_PERSON) = TD_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) td_part(driver, TD_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) td_part(driver, TD_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) td_part(driver, TD_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) td_part(driver, TD_ANIM));
    SceneMover_Construct((SceneMover *) (void *) td_part(driver, TD_MOVER));
    SceneProbe_Construct(td_part(driver, TD_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) td_part(driver, TD_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) td_part(driver, TD_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) td_part(driver, TD_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) td_part(driver, TD_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) td_part(driver, TD_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) td_part(driver, TD_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) td_part(driver, TD_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) td_part(driver, TD_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) td_part(driver, TD_MOTION));
    SceneAction_Construct((SceneAction *) (void *) td_part(driver, TD_ACTION));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) td_part(driver, TD_HEAP));
    *(const u8 **) (void *) object = data_ov051_0226193c;
    TaxiDriverTalk_Construct(&driver->talk);
    return driver;
}
CLEAN_AS(func_ov051_022613a4, TaxiDriver_Create)
