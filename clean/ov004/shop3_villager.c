/* The villager who talks with the lines of "ai_shop3" (shop3_villager.h). */
#include "shop3_villager.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/event_queue.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/scene_standard_anims.h"
#include "main/town_villager.h"
#include "main/villager_scene_slots.h"
#include "main/villager_talk_scene.h"

static_assert(sizeof(VillagerTalk) == 0x1a4, "the town villager's talk scene");
static_assert(sizeof(Shop3VillagerTalk) == 0x1a8, "its talk scene");
static_assert(sizeof(Shop3VillagerStep) == 0x10, "a state's functions");
static_assert(offsetof(Shop3Villager, state) == 0x898, "state");
static_assert(offsetof(Shop3Villager, talk) == 0x89c, "talk scene");
static_assert(sizeof(Shop3Villager) == 0xa44, "the size func_ov004_02221b68 allocates");

/* The parts of the town villager scene object used here, by place (main's scene_object.h). */
#define SHOP3_VILLAGER_ANIMS 0x2a0  /* SceneStandardAnims */
#define SHOP3_VILLAGER_MOTION 0x564 /* SceneMotion */
#define SHOP3_VILLAGER_ACTION 0x618 /* SceneAction */
#define SHOP3_VILLAGER_RECORD 0x830 /* u8 *: its town record */

/* The field actor of this console's player. */
#define SHOP3_VILLAGER_PLAYER_ACTOR 4

/* The codes of its vtable slot 0x4c (main's event_kinds.h): the player talks to it, and the
 * event ended. */
#define SHOP3_VILLAGER_EVENT_TALK 0
#define SHOP3_VILLAGER_EVENT_ENDED 8

/* Its talk scene's vtable slot its talks call first. */
#define SHOP3_VILLAGER_TALK_SLOT_08 0x08

/* The kind of motion of a stand (scene_motion_request.h). */
#define SHOP3_VILLAGER_MOTION_STAND 0

/* The animation its three standard animations are set to at its set-up. */
#define SHOP3_VILLAGER_ANIM 0x1e

/* The lines table VillagerTalkScene_Start is given: 17 and above leave the line members as they
 * are (the talk scene's own vtable slot 0x78 says the line). */
#define SHOP3_VILLAGER_TALK_OWN_LINES 0x11

/* The size of the text the message file's name is written in, and how many lines it has. */
#define SHOP3_VILLAGER_FILE_NAME_SIZE 0x28
#define SHOP3_VILLAGER_LINES 5

/* The vtables: the class's, and its talk scene's. */
extern const u8 data_ov004_02253fd4[];
extern const u8 data_ov004_02253f44[];
/* The functions of its states (filled at start-up by __sinit_ov004_0224e5b0). */
extern Shop3VillagerStep data_ov004_02257f48[SHOP3_VILLAGER_STATES];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The message file "ai_shop3", and the text its name for the villager is written in. */
extern const char data_ov004_02254094[];
extern char data_ov004_02257f20[SHOP3_VILLAGER_FILE_NAME_SIZE];

static u8 *sv_part(Shop3Villager *villager, u32 offset)
{
    return villager->base + offset;
}

static SceneMotion *sv_motion_of(Shop3Villager *villager)
{
    return (SceneMotion *) (void *) sv_part(villager, SHOP3_VILLAGER_MOTION);
}

static SceneAction *sv_action_of(Shop3Villager *villager)
{
    return (SceneAction *) (void *) sv_part(villager, SHOP3_VILLAGER_ACTION);
}

static SceneBase *sv_scene_of(Shop3VillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

/* The talk scene's vtable slot 0x08 called. */
static void sv_talk_slot_08(Shop3VillagerTalk *talk)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + SHOP3_VILLAGER_TALK_SLOT_08);
    ((void (*)(Shop3VillagerTalk *))(uintptr_t) code)(talk);
}

/* func_ov004_02221850 (vtable slot 0x40): the destructor, without freeing: its talk scene, then
 * the town villager scene object. */
Shop3Villager *Shop3Villager_Destroy(Shop3Villager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_02253fd4;
    Shop3VillagerTalk_Destroy(&villager->talk);
    VillagerSceneObject_DestructBody(villager->base);
    return villager;
}
CLEAN_AS(func_ov004_02221850, Shop3Villager_Destroy)

/* func_ov004_02221878 (vtable slot 0x44, the deleting destructor). */
Shop3Villager *Shop3Villager_Delete(Shop3Villager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_02253fd4;
    Shop3VillagerTalk_Destroy(&villager->talk);
    VillagerSceneObject_DestructBody(villager->base);
    Heap_FreeAux(villager);
    return villager;
}
CLEAN_AS(func_ov004_02221878, Shop3Villager_Delete)

/* func_ov004_022218a4 (vtable slot 0x4c, told of an event): 0, the player talks to it: its talk
 * scene told through its vtable slot 0x08, the talk's partner this console's player's field
 * actor, and it talks (state 0); 8, the event ended: it stands (state 2). */
void Shop3Villager_OnEvent(Shop3Villager *villager, int code)
{
    switch (code) {
        case SHOP3_VILLAGER_EVENT_TALK:
            sv_talk_slot_08(&villager->talk);
            SceneBase_SetMotionArg(sv_scene_of(&villager->talk),
                                   SceneObject_ActorObject(villager->base, SHOP3_VILLAGER_PLAYER_ACTOR));
            Shop3Villager_SetState(villager, SHOP3_VILLAGER_TALK);
            break;
        case SHOP3_VILLAGER_EVENT_ENDED:
            Shop3Villager_SetState(villager, SHOP3_VILLAGER_STAND);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_022218a4, Shop3Villager_OnEvent)

/* func_ov004_022218e8 (vtable slot 0x48): whether the player may talk to it: its action idle. */
int Shop3Villager_MayAct(Shop3Villager *villager)
{
    return SceneAction_IsBusy(sv_action_of(villager)) == 0;
}
CLEAN_AS(func_ov004_022218e8, Shop3Villager_MayAct)

/* func_ov004_02221908 (the talk scene's receiver slot 0x18, the player's answer): nothing. */
void Shop3VillagerTalk_OnAnswer(void) {}
CLEAN_AS(func_ov004_02221908, Shop3VillagerTalk_OnAnswer)

/* func_ov004_0222190c (the talk scene's receiver slot 0x14, a message ended): nothing. */
void Shop3VillagerTalk_OnMessageEnded(void) {}
CLEAN_AS(func_ov004_0222190c, Shop3VillagerTalk_OnMessageEnded)

/* func_ov004_02221910 (the talk scene's vtable slot 0x78, the line to say): "ai_shop3" for the
 * villager, written into data_ov004_02257f20, and a message 0 to 4 at random. The draw. */
int Shop3VillagerTalk_Line(Shop3VillagerTalk *talk, VillagerTalkLine *out)
{
    u8 *record = *(u8 **) (void *) sv_part(talk->villager, SHOP3_VILLAGER_RECORD);
    NpcId_FormatResourceName(TownVillager_NpcId(record), data_ov004_02257f20, SHOP3_VILLAGER_FILE_NAME_SIZE,
                             data_ov004_02254094);
    out->text = (u32) (uintptr_t) data_ov004_02257f20;
    int line = (int) MainRandom_Below(SHOP3_VILLAGER_LINES);
    out->message = (u8) line;
    return line;
}
CLEAN_AS(func_ov004_02221910, Shop3VillagerTalk_Line)

/* func_ov004_0222194c: its talk scene told through its vtable slot 0x08, started for `villager`
 * and kept pointing back at it. */
void Shop3VillagerTalk_Start(Shop3VillagerTalk *talk, Shop3Villager *villager)
{
    sv_talk_slot_08(talk);
    VillagerTalkScene_Start(&talk->base, villager->base, SHOP3_VILLAGER_TALK_OWN_LINES);
    talk->villager = villager;
}
CLEAN_AS(func_ov004_0222194c, Shop3VillagerTalk_Start)

/* func_ov004_02221974 (the talk scene's vtable slot 0x04, its deleting destructor). */
Shop3VillagerTalk *Shop3VillagerTalk_Delete(Shop3VillagerTalk *talk)
{
    talk->base.scene.vtable = data_ov004_02253f44;
    VillagerTalkScene_DestructBody(&talk->base);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_02221974, Shop3VillagerTalk_Delete)

/* func_ov004_02221994 (the talk scene's vtable slot 0x00, its destructor). */
Shop3VillagerTalk *Shop3VillagerTalk_Destroy(Shop3VillagerTalk *talk)
{
    talk->base.scene.vtable = data_ov004_02253f44;
    VillagerTalkScene_DestructBody(&talk->base);
    return talk;
}
CLEAN_AS(func_ov004_02221994, Shop3VillagerTalk_Destroy)

/* func_ov004_022219ac: its talk scene's constructor. */
Shop3VillagerTalk *Shop3VillagerTalk_Construct(Shop3VillagerTalk *talk)
{
    VillagerTalkScene_ConstructAlt(&talk->base);
    talk->base.scene.vtable = data_ov004_02253f44;
    return talk;
}
CLEAN_AS(func_ov004_022219ac, Shop3VillagerTalk_Construct)

/* func_ov004_022219c4 (state 1's update): nothing. 1. */
int Shop3Villager_UpdateIdle(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022219c4, Shop3Villager_UpdateIdle)

/* func_ov004_022219c8 (state 0's update): once its action is idle, the object's event ends and
 * it idles (state 1). 1. */
int Shop3Villager_UpdateTalk(Shop3Villager *villager)
{
    if (SceneAction_IsBusy(sv_action_of(villager)) == 0) {
        EventQueue_FinishObjectEvent(villager);
        Shop3Villager_SetState(villager, SHOP3_VILLAGER_IDLE);
    }
    return 1;
}
CLEAN_AS(func_ov004_022219c8, Shop3Villager_UpdateTalk)

/* func_ov004_022219f4 (state 0's entry): the turn of its action to the talk's partner (none:
 * angle 0), then talking. 1. */
int Shop3Villager_EnterTalk(Shop3Villager *villager)
{
    int partner = SceneBase_MotionArg(sv_scene_of(&villager->talk));
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(villager->base, (u8 *) (uintptr_t) partner);
    }
    SceneAction_RequestTurnAndTalk(sv_action_of(villager), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov004_022219f4, Shop3Villager_EnterTalk)

/* func_ov004_02221a2c (state 2's update): nothing. 1. */
int Shop3Villager_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02221a2c, Shop3Villager_UpdateStand)

/* func_ov004_02221a30 (state 2's entry): it stands (priority 1). 1. */
int Shop3Villager_EnterStand(Shop3Villager *villager)
{
    SceneMotion_Request(sv_motion_of(villager), SHOP3_VILLAGER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov004_02221a30, Shop3Villager_EnterStand)

/* func_ov004_02221a64: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded). */
void Shop3Villager_SetState(Shop3Villager *villager, int state)
{
    const Shop3VillagerStep *step = &data_ov004_02257f48[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, villager);
    }
    if (taken != 0) {
        villager->state = state;
    }
}
CLEAN_AS(func_ov004_02221a64, Shop3Villager_SetState)

/* func_ov004_02221aa8 (vtable slot 0x68, its update): its state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: its state is 0 to 2. */
int Shop3Villager_RunState(Shop3Villager *villager)
{
    const Shop3VillagerStep *step = &data_ov004_02257f48[(u32) villager->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, villager);
}
CLEAN_AS(func_ov004_02221aa8, Shop3Villager_RunState)

/* func_ov004_02221af4 (vtable slot 0x00, its start): the town villager's start; then it stands
 * (state 2). Whether the start was done. */
int Shop3Villager_Start(Shop3Villager *villager)
{
    if (VillagerSceneObject_Start(villager->base) == 0) {
        return 0;
    }
    Shop3Villager_SetState(villager, SHOP3_VILLAGER_STAND);
    return 1;
}
CLEAN_AS(func_ov004_02221af4, Shop3Villager_Start)

/* func_ov004_02221b14 (vtable slot 0x04, its set-up): the town villager's set-up; then its three
 * standard animations are 0x1e, its talk scene becomes its scene and is started
 * (Shop3VillagerTalk_Start). Whether the set-up was done. */
int Shop3Villager_Init(Shop3Villager *villager)
{
    if (VillagerSceneObject_Init(villager->base) == 0) {
        return 0;
    }
    SceneStandardAnims *anims = (SceneStandardAnims *) (void *) sv_part(villager, SHOP3_VILLAGER_ANIMS);
    SceneStandardAnims_SetFirst(anims, SHOP3_VILLAGER_ANIM);
    SceneStandardAnims_SetSecond(anims, SHOP3_VILLAGER_ANIM);
    SceneStandardAnims_SetThird(anims, SHOP3_VILLAGER_ANIM);
    SceneObject_SetScene(villager->base, sv_scene_of(&villager->talk));
    Shop3VillagerTalk_Start(&villager->talk, villager);
    return 1;
}
CLEAN_AS(func_ov004_02221b14, Shop3Villager_Init)

/* func_ov004_02221b68 (its entry in the overlay's table of profiles, data_ov004_02253f24):
 * allocates (zeroed) and builds a villager: the town villager scene object and its talk
 * scene. */
Shop3Villager *Shop3Villager_New(void)
{
    Shop3Villager *villager = Heap_AllocAuxZeroed(sizeof(Shop3Villager));
    if (villager != NULL) {
        VillagerSceneObject_Construct(villager->base);
        *(const u8 **) (void *) villager->base = data_ov004_02253fd4;
        Shop3VillagerTalk_Construct(&villager->talk);
    }
    return villager;
}
CLEAN_AS(func_ov004_02221b68, Shop3Villager_New)
