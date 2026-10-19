/* A villager out walking in the town: its life as a scene object (outdoor_villager_object.h). */
#include "outdoor_villager_object.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/actor.h"
#include "main/effect_system.h"
#include "main/field_body.h"
#include "main/held_item_link.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_motion.h"
#include "main/scene_motion_kinds.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/session_players.h"
#include "main/villager_checks.h"
#include "main/villager_entry.h"
#include "main/villager_mood.h"
#include "main/villager_scene_held.h"
#include "main/villager_scene_slots.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "ov004/member_pointer.h"
#include "outdoor_villager.h"
#include "outdoor_villager_behaviour.h"
#include "outdoor_villager_records.h"
#include "outdoor_villager_walks.h"
#include "outdoor_villager_watch.h"

/* The class's vtable. */
extern const u8 data_ov068_022771c0[];
/* Behaviour 0's draw hook (OutdoorVillagerObject_DrawWithItem), set when it starts. */
extern const MemberPointer data_ov068_02276eb0;
/* The countdown its effect gets when the player swings item 0x1376 or 0x1377 at the villager
 * the state table names at 0x160 (600). */
extern const u16 data_ov068_0227672c;
/* The word its held item's actions carry. */
extern u16 data_020c80f8;
/* The model matrix of the object being drawn (main's model_matrix.c). */
extern Mtx43 data_021cfe68;

/* The parts of the villager read here besides outdoor_villager.h's (main's scene_object.c). */
#define OBJECT_MODEL_MATRIX 0x150 /* Mtx43 */
#define OBJECT_ACT_EFFECTS 0x420  /* ActEffects */
#define OBJECT_JOINT_7_POINT 0x484
#define OBJECT_JOINT_4_POINT 0x490
#define OBJECT_BODY 0x4cc       /* FieldBody */
#define OBJECT_ENABLED 0x561    /* u8 */
#define OBJECT_POSED 0x562      /* u8 */
#define OBJECT_HELD_LINK 0x628  /* HeldItemLink *: the link the object's held item uses */
#define OBJECT_DRAW_HOOK 0x8b0  /* MemberPointer: called to draw in place of the plain joints */
#define OBJECT_ITEM_SHOWN 0x9f0 /* u8 */
#define OBJECT_BYTE_A05 0xa05   /* u8 */
#define OBJECT_COUNT_A06 0xa06  /* u16 */
#define OBJECT_MINUTE 0xa08     /* u8 */
#define OBJECT_BYTE_A09 0xa09   /* u8 */
/* The player's object: its walking direction and speed. */
#define OBJECT_WALK_ANGLE 0x94 /* s16 */
#define OBJECT_SPEED 0x98      /* fx32 */

/* The size of the object. */
#define OBJECT_SIZE 0xa10
/* The slot of the talk scene called at init (its reset, main's scene_base.h). */
#define OBJECT_TALK_SLOT_RESET 0x08

/* The act kind whose effects are reset, and the act started. */
#define OBJECT_ACT_KIND 8
#define OBJECT_ACT_0 0

/* The push count's limit, the flags of the bodies that count and the angle about straight. */
#define OBJECT_PUSH_FRAMES 100
#define OBJECT_PUSH_TOUCH 4
#define OBJECT_PUSH_ANGLE 0x31c6

/* The items swung at it that it minds (main's field_actor.c: a kind 2 object told the held
 * item). */
#define OBJECT_SWUNG_FIRST 0x1376
#define OBJECT_SWUNG_LAST 0x1377

#define OBJECT_NO_ITEM 0xfff1
#define OBJECT_ITEM_SCALE 0x1000
#define OBJECT_NO_HANDLE (-1)
#define OBJECT_NO_MINUTE 0xff

/* The behaviours it starts with, and the statuses that give them. */
#define OBJECT_DO_WALK 0
#define OBJECT_DO_IN 3
#define OBJECT_DO_12 12
#define OBJECT_DO_13 13
#define OBJECT_STATUS_WALK 0
#define OBJECT_STATUS_12_FIRST 3
#define OBJECT_STATUS_12_LAST 7

static u8 *object_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static u32 *object_word(void *object, u32 offset)
{
    return (u32 *) (void *) object_at(object, offset);
}

static OutdoorVillagerBehaviour *object_behaviour(u8 *villager)
{
    return (OutdoorVillagerBehaviour *) (void *) object_at(villager, OUTDOOR_VILLAGER_BEHAVIOUR);
}

static OutdoorVillagerEffect *object_effect(u8 *villager)
{
    return (OutdoorVillagerEffect *) (void *) object_at(villager, OUTDOOR_VILLAGER_EFFECT);
}

static HeldItemLink *object_link(u8 *villager)
{
    return (HeldItemLink *) (void *) object_at(villager, OUTDOOR_VILLAGER_LINK);
}

static const SceneAction *object_action(u8 *villager)
{
    return (const SceneAction *) (const void *) object_at(villager, OUTDOOR_VILLAGER_ACTION);
}

static SceneMotion *object_motion(u8 *villager)
{
    return (SceneMotion *) (void *) object_at(villager, OUTDOOR_VILLAGER_MOTION);
}

static Vec3 *object_position(void *object)
{
    return (Vec3 *) (void *) object_at(object, OUTDOOR_VILLAGER_POSITION);
}

/* The code at vtable slot `slot` of `object`. */
static uintptr_t object_slot(void *object, u32 slot)
{
    u32 vtable = *(const u32 *) object;
    return *(const u32 *) (uintptr_t) (vtable + slot);
}

/* Its town record (vtable slot 0x64), or null. */
static u8 *object_record(u8 *villager)
{
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *)) object_slot(villager, OUTDOOR_VILLAGER_SLOT_RECORD))(villager);
}

/* func_ov068_0226cee0 (slot 0x68): a frame: the push count, the tally of its state entry (held
 * still while its action is busy), its behaviour, its effect, its mood and its watch; the byte
 * at 0xa05 cleared; 1. */
int OutdoorVillagerObject_Frame(u8 *villager)
{
    OutdoorVillagerObject_CountPushed(villager);
    VillagerTally *tally = OutdoorVillagerRecords_Tally(villager);
    if (tally != NULL) {
        VillagerTally_Tick(tally, SceneAction_IsBusy(object_action(villager)));
    }
    OutdoorVillagerBehaviour_Tick(object_behaviour(villager), villager);
    OutdoorVillagerEffect_Tick(object_effect(villager), villager);
    VillagerMood_Update((VillagerMood *) (void *) object_at(villager, OUTDOOR_VILLAGER_MOOD), villager);
    OutdoorVillagerWatch_Update((OutdoorVillagerWatch *) (void *) object_at(villager, OUTDOOR_VILLAGER_WATCH), villager);
    *object_at(villager, OBJECT_BYTE_A05) = 0;
    return 1;
}
CLEAN_AS(func_ov068_0226cee0, OutdoorVillagerObject_Frame)

/* func_ov068_0226cfd4: with a motion of act kind 8 running whose act number is not 0, its act
 * effects start act 0's first part (act number 0 noted). */
void OutdoorVillagerObject_ResetActEffects(u8 *villager)
{
    if (SceneMotion_Kind(object_motion(villager)) != OBJECT_ACT_KIND) {
        return;
    }
    if (SceneMotion_ActNumber(object_motion(villager)) == 0) {
        return;
    }
    SceneMotionAct *act = SceneMotion_Act(OBJECT_ACT_0);
    if (act == NULL) {
        return;
    }
    ActEffects *effects = (ActEffects *) (void *) object_at(villager, OBJECT_ACT_EFFECTS);
    effects->act = OBJECT_ACT_0;
    ActEffects_StartPart(effects, act->part, 0);
}
CLEAN_AS(func_ov068_0226cfd4, OutdoorVillagerObject_ResetActEffects)

/* func_ov068_0226d4ac: the push count at 0xa06: one more frame (up to 100) while it is posed,
 * enabled and drawn by a hook, its action idle, it remembers this console's player and the
 * player pushes against it (OutdoorVillagerObject_PushedByPlayer); else back to 0. */
void OutdoorVillagerObject_CountPushed(u8 *villager)
{
    u16 *count = (u16 *) (void *) object_at(villager, OBJECT_COUNT_A06);
    const MemberPointer *hook = (const MemberPointer *) (const void *) object_at(villager, OBJECT_DRAW_HOOK);
    if (*object_at(villager, OBJECT_POSED) == 0 || *object_at(villager, OBJECT_ENABLED) == 0 || hook->function == 0 ||
        SceneAction_IsBusy(object_action(villager)) != 0 || OutdoorVillagerRecords_MemoryOfPlayer(villager) == NULL ||
        OutdoorVillagerObject_PushedByPlayer(villager) == 0) {
        *count = 0;
        return;
    }
    (*count)++;
    if (*count >= OBJECT_PUSH_FRAMES) {
        *count = OBJECT_PUSH_FRAMES;
    }
}
CLEAN_AS(func_ov068_0226d4ac, OutdoorVillagerObject_CountPushed)

/* func_ov068_0226d528: whether this console's player pushes against it: its body touched one
 * this frame, a body of flag 4 among them, and the player's object walks (its speed not 0) in a
 * direction no further than 0x31c6 (about 70 degrees) either way of straight at the villager.
 * QUIRK: the difference of the angles is taken as a 16-bit value, whose size of -0x8000 stays
 * negative and passes. */
int OutdoorVillagerObject_PushedByPlayer(u8 *villager)
{
    FieldBody *body = (FieldBody *) (void *) object_at(villager, OBJECT_BODY);
    if (body->touched == 0) {
        return 0;
    }
    if (FieldBody_TouchedWith(body, OBJECT_PUSH_TOUCH) == 0) {
        return 0;
    }
    int handle = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    if (handle == 0) {
        return 0;
    }
    u8 *player = (u8 *) (uintptr_t) (u32) handle;
    if (*(const s32 *) (const void *) object_at(player, OBJECT_SPEED) == 0) {
        return 0;
    }
    s16 walk = *(const s16 *) (const void *) object_at(player, OBJECT_WALK_ANGLE);
    s16 off = (s16) (Vec_YawTo(object_position(player), object_position(villager)) - walk);
    if (off < 0) {
        off = (s16) -off;
    }
    return off < OBJECT_PUSH_ANGLE;
}
CLEAN_AS(func_ov068_0226d528, OutdoorVillagerObject_PushedByPlayer)

/* func_ov068_0226d5f4: the item it holds (VillagerSceneHeld_Item), unless none, taken into its
 * held item link, which plays action 0 at full scale; the byte at 0x9f0 set. The item is asked
 * for twice. */
void OutdoorVillagerObject_ShowHeldItem(u8 *villager)
{
    u16 item;
    VillagerSceneHeld_Item(&item, villager);
    if (item == OBJECT_NO_ITEM) {
        return;
    }
    VillagerSceneHeld_Item(&item, villager);
    HeldItemLink_Take(object_link(villager), villager, &item, NULL, 0);
    HeldItemLink_Action0(object_link(villager), data_020c80f8, 0);
    HeldItemLink_SetScale(object_link(villager), OBJECT_ITEM_SCALE);
    *object_at(villager, OBJECT_ITEM_SHOWN) = 1;
}
CLEAN_AS(func_ov068_0226d5f4, OutdoorVillagerObject_ShowHeldItem)

/* func_ov068_0226d664 (slot 0xb0): when its effect's countdown runs, it is stopped; whether it
 * ran. */
int OutdoorVillagerObject_TakeCountdown(u8 *villager)
{
    if (OutdoorVillagerEffect_Countdown(object_effect(villager)) == 0) {
        return 0;
    }
    OutdoorVillagerEffect_SetCountdown(object_effect(villager), 0);
    return 1;
}
CLEAN_AS(func_ov068_0226d664, OutdoorVillagerObject_TakeCountdown)

/* func_ov068_0226d690 (slot 0x60): told of the item this console's player swung at it. For
 * items 0x1376 and 0x1377: its record's byte 0x1e halved (when it has a record; the record is
 * asked for twice); then, for the villager the state table names at 0x160, its effect stopped
 * with a countdown of data_ov068_0227672c and 1; otherwise, remembering the player, the byte at
 * 0xa05 set (behaviour 19 follows). 0 for other items and then. */
int OutdoorVillagerObject_OnItemSwung(u8 *villager, u16 *item)
{
    u16 swung = *item;
    if (swung < OBJECT_SWUNG_FIRST || swung > OBJECT_SWUNG_LAST) {
        return 0;
    }
    if (object_record(villager) != NULL) {
        VillagerEntry_HalveByte1E(object_record(villager));
    }
    u8 *town_record = *(u8 **) (void *) object_at(villager, OUTDOOR_VILLAGER_RECORD);
    if (VillagerCheck_IsIndex160(town_record) != 0) {
        OutdoorVillagerEffect_Stop(object_effect(villager), villager);
        OutdoorVillagerEffect_SetCountdown(object_effect(villager), data_ov068_0227672c);
        return 1;
    }
    if (OutdoorVillagerRecords_MemoryOfPlayer(villager) != NULL) {
        *object_at(villager, OBJECT_BYTE_A05) = 1;
    }
    return 0;
}
CLEAN_AS(func_ov068_0226d690, OutdoorVillagerObject_OnItemSwung)

/* func_ov068_0226d728 (slot 0x0c): the town villager's leave (VillagerSceneObject_Leave); once it
 * is done, the held item link released and forgotten and its effect handle ended; whether it
 * is done. */
int OutdoorVillagerObject_Leave(u8 *villager)
{
    if (VillagerSceneObject_Leave(villager) == 0) {
        return 0;
    }
    HeldItemLink_Release(object_link(villager));
    *object_word(villager, OBJECT_HELD_LINK) = 0;
    s32 *handle = (s32 *) (void *) object_at(villager, OUTDOOR_VILLAGER_EFFECT_HANDLE);
    if (*handle != OBJECT_NO_HANDLE) {
        EffectSystem_EndHandle(*handle);
        *handle = OBJECT_NO_HANDLE;
    }
    return 1;
}
CLEAN_AS(func_ov068_0226d728, OutdoorVillagerObject_Leave)

/* func_ov068_0226d770 (slot 0x24): drawn by its draw hook, with its answer, when it has one;
 * without, it is not drawn and the points of its joints 16, 7 and 4 are put at its position;
 * 1. */
int OutdoorVillagerObject_Draw(u8 *villager)
{
    const MemberPointer *hook = (const MemberPointer *) (const void *) object_at(villager, OBJECT_DRAW_HOOK);
    if (hook->function != 0) {
        return MemberPointer_CallInt(hook, villager);
    }
    const Vec3 *position = object_position(villager);
    *(Vec3 *) (void *) object_at(villager, OUTDOOR_VILLAGER_JOINT_16_POINT) = *position;
    *(Vec3 *) (void *) object_at(villager, OBJECT_JOINT_7_POINT) = *position;
    *(Vec3 *) (void *) object_at(villager, OBJECT_JOINT_4_POINT) = *position;
    return 1;
}
CLEAN_AS(func_ov068_0226d770, OutdoorVillagerObject_Draw)

/* func_ov068_0226d808 (behaviour 0's draw hook): its model matrix made the current one, the
 * object drawn (SceneObject_Draw) and then its held item put in its hand; whether it was
 * drawn. */
int OutdoorVillagerObject_DrawWithItem(u8 *villager)
{
    data_021cfe68 = *(const Mtx43 *) (const void *) object_at(villager, OBJECT_MODEL_MATRIX);
    if (SceneObject_Draw(villager) == 0) {
        return 0;
    }
    HeldItemLink_FollowHand(object_link(villager), villager);
    return 1;
}
CLEAN_AS(func_ov068_0226d808, OutdoorVillagerObject_DrawWithItem)

/* func_ov068_0226d850 (slot 0x00): the start. After the town villager's
 * (VillagerSceneObject_Start; 0 when it fails): behaviour 0's draw hook, the watch held on the
 * player, the held item's first check, the first behaviour by its town record (the header),
 * and its effect set up; 1. The town record is taken before the town villager's start. */
int OutdoorVillagerObject_Start(u8 *villager)
{
    u8 *record = object_record(villager);
    if (VillagerSceneObject_Start(villager) == 0) {
        return 0;
    }
    OutdoorVillagerBehaviour *behaviour = object_behaviour(villager);
    *(MemberPointer *) (void *) object_at(villager, OBJECT_DRAW_HOOK) = data_ov068_02276eb0;
    OutdoorVillagerWatch_HoldOnPlayer((OutdoorVillagerWatch *) (void *) object_at(villager, OUTDOOR_VILLAGER_WATCH), villager);
    int named = VillagerState_GetIndex16C();
    OutdoorVillagerWalks_InitItemCheck(behaviour);
    if (named == VillagerStatus_Index(record)) {
        OutdoorVillagerBehaviour_Start(behaviour, villager, OBJECT_DO_13);
    } else if (VillagerState_GetIndex162() == VillagerStatus_Index(record)) {
        OutdoorVillagerBehaviour_Start(behaviour, villager, OBJECT_DO_12);
    } else {
        int status = VillagerStatus_Get(record);
        if (status == OBJECT_STATUS_WALK) {
            OutdoorVillagerBehaviour_Start(behaviour, villager, OBJECT_DO_WALK);
            u16 item;
            VillagerSceneHeld_Item(&item, villager);
            if (item != OBJECT_NO_ITEM) {
                OutdoorVillagerObject_ShowHeldItem(villager);
            }
        } else if (status >= OBJECT_STATUS_12_FIRST && status <= OBJECT_STATUS_12_LAST) {
            OutdoorVillagerBehaviour_Start(behaviour, villager, OBJECT_DO_12);
        } else {
            OutdoorVillagerBehaviour_Start(behaviour, villager, OBJECT_DO_IN);
        }
    }
    OutdoorVillagerEffect_Init(object_effect(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226d850, OutdoorVillagerObject_Start)

/* func_ov068_0226d960 (slot 0x04): the init. After the town villager's
 * (VillagerSceneObject_Init; 0 when it fails): its talk scene made its scene and reset, no
 * partner, the default lines, no reaction (3); its held item link opened with no item (0 when
 * that fails) and named by the object's link pointer; no effect handle, the bytes at 0xa04,
 * 0xa05 and 0xa09 and the push count cleared, no minute looked at; then its kind of the moment
 * checked and its held item brought up to date; 1. */
int OutdoorVillagerObject_Init(u8 *villager)
{
    if (VillagerSceneObject_Init(villager) == 0) {
        return 0;
    }
    u8 *talk = object_at(villager, OUTDOOR_VILLAGER_TALK);
    SceneObject_SetScene(villager, (SceneBase *) (void *) talk);
    ((void (*)(u8 *)) object_slot(talk, OBJECT_TALK_SLOT_RESET))(talk);
    *object_word(villager, OUTDOOR_VILLAGER_PARTNER) = 0;
    *object_word(villager, OUTDOOR_VILLAGER_LINES) = OUTDOOR_VILLAGER_LINES_DEFAULT;
    *object_word(villager, OUTDOOR_VILLAGER_REACTION) = OUTDOOR_VILLAGER_REACTION_NONE;
    u16 none = OBJECT_NO_ITEM;
    if (HeldItemLink_Open(object_link(villager), &none) == 0) {
        return 0;
    }
    *object_word(villager, OBJECT_HELD_LINK) = (u32) (uintptr_t) object_link(villager);
    *(s32 *) (void *) object_at(villager, OUTDOOR_VILLAGER_EFFECT_HANDLE) = OBJECT_NO_HANDLE;
    *object_at(villager, OUTDOOR_VILLAGER_BYTE_A04) = 0;
    *object_at(villager, OBJECT_BYTE_A05) = 0;
    *(u16 *) (void *) object_at(villager, OBJECT_COUNT_A06) = 0;
    *object_at(villager, OBJECT_MINUTE) = OBJECT_NO_MINUTE;
    *object_at(villager, OBJECT_BYTE_A09) = 0;
    OutdoorVillagerRecords_CheckKind(villager);
    OutdoorVillagerRecords_RefreshItem(villager);
    return 1;
}
CLEAN_AS(func_ov068_0226d960, OutdoorVillagerObject_Init)

/* func_ov068_0226da28 (slot 0xa8): whether the state entry of its town record (at 0x830) is
 * linked (VillagerState_LinkedState answers 1); 0 without a record or entry. The entry is
 * looked up twice. */
int OutdoorVillagerObject_IsLinked(u8 *villager)
{
    u8 *record = *(u8 **) (void *) object_at(villager, OUTDOOR_VILLAGER_RECORD);
    if (record == NULL || VillagerStatus_StateEntry(record) == NULL) {
        return 0;
    }
    return VillagerState_LinkedState(VillagerStatus_StateEntry(record)) == 1;
}
CLEAN_AS(func_ov068_0226da28, OutdoorVillagerObject_IsLinked)

/* func_ov068_0226da64 (made by the profile record data_ov068_022771a0): the object, zeroed on
 * the auxiliary heap, made as a town villager and given this class's vtable and its members:
 * the watch, the behaviour, the held item link and the effect. Null when the heap has no
 * room. */
u8 *OutdoorVillagerObject_New(void)
{
    u8 *villager = Heap_AllocAuxZeroed(OBJECT_SIZE);
    if (villager == NULL) {
        return NULL;
    }
    VillagerSceneObject_Construct(villager);
    *(const u8 **) (void *) villager = data_ov068_022771c0;
    OutdoorVillagerWatch_Construct((OutdoorVillagerWatch *) (void *) object_at(villager, OUTDOOR_VILLAGER_WATCH));
    OutdoorVillagerBehaviour_Construct(object_behaviour(villager));
    HeldItemLink_Construct(object_link(villager));
    OutdoorVillagerEffect_Construct(object_effect(villager));
    return villager;
}
CLEAN_AS(func_ov068_0226da64, OutdoorVillagerObject_New)
