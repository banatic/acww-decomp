/* The fox in his tent (fox_tent.h): his object's vtable slots, the reasons he talks and his
 * states. */
#include "fox_tent.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "fox_tent_talk.h"
#include "main/act_effects.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/calendar.h"
#include "main/collision_map.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/item_code.h"
#include "main/layered_model.h"
#include "main/player_actor_ops.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_exit.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_path_step.h"
#include "main/scene_probe.h"
#include "main/scene_query.h"
#include "main/scene_share.h"
#include "main/scene_standard_anims.h"
#include "main/scene_tables.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/session_players.h"
#include "main/shops.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/touch_pick_shapes.h"
#include "ov004/room_objects.h"
#include "ov004/shop_display.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(FoxTentTalk, sequence) == 0xb0 && offsetof(FoxTentTalk, owner) == 0xb4, "FoxTentTalk");
static_assert(offsetof(FoxTentTalk, price) == 0xb8 && offsetof(FoxTentTalk, card_slot) == 0xbc, "FoxTentTalk");
static_assert(offsetof(FoxTentTalk, declined) == 0xc0 && sizeof(FoxTentTalk) == 0xc4, "FoxTentTalk");
static_assert(offsetof(FoxTent, state) == 0x654 && offsetof(FoxTent, talk) == 0x658, "FoxTent");
static_assert(offsetof(FoxTent, stand_word) == 0x71c && offsetof(FoxTent, item) == 0x71e, "FoxTent");
static_assert(offsetof(FoxTent, told) == 0x720 && offsetof(FoxTent, item_x) == 0x728, "FoxTent");
static_assert(offsetof(FoxTent, item_z) == 0x72c && offsetof(FoxTent, awaiting_answers) == 0x730, "FoxTent");
static_assert(offsetof(FoxTent, come_frames) == 0x731 && offsetof(FoxTent, sold) == 0x732, "FoxTent");
static_assert(offsetof(FoxTent, offer_used) == 0x733 && offsetof(FoxTent, thanks_used) == 0x738, "FoxTent");
static_assert(sizeof(FoxTent) == 0x740, "the size FoxTent_Create allocates");
static_assert(sizeof(FoxTentStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define FOX_TENT_POSITION 0x5c        /* Vec3: where he stands */
#define FOX_TENT_ANGLE 0x8e           /* s16: where he faces */
#define FOX_TENT_PERSON 0xea          /* u16: his person code */
#define FOX_TENT_MODEL 0xec           /* LayeredModel */
#define FOX_TENT_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define FOX_TENT_FACE 0x2ac           /* SceneFace */
#define FOX_TENT_ANIM 0x334           /* SpeakerAnim */
#define FOX_TENT_MOVER 0x350          /* SceneMover */
#define FOX_TENT_PROBE 0x3a8          /* the probe */
#define FOX_TENT_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define FOX_TENT_LOOK 0x3b0           /* SceneLook */
#define FOX_TENT_TALK_STATE 0x418     /* SceneTalkState */
#define FOX_TENT_EFFECTS 0x420        /* ActEffects */
#define FOX_TENT_COLLIDER 0x49c       /* CollisionContacts */
#define FOX_TENT_CARRIER 0x4cc        /* FieldOwnedBody */
#define FOX_TENT_EMITTER 0x514        /* SoundEmitterObject */
#define FOX_TENT_FOOTSTEPS 0x558      /* Footsteps */
#define FOX_TENT_PARTICIPANT 0x560    /* u8: whose system the last event came from */
#define FOX_TENT_MOTION 0x564         /* SceneMotion */
#define FOX_TENT_ACTION 0x618         /* SceneAction */
#define FOX_TENT_HEAP 0x640           /* PoolLink */

/* The parts of the player's field actor read: its position and where it faces. */
#define FOX_TENT_ACTOR_POSITION 0x5c
#define FOX_TENT_ACTOR_ANGLE 0x8e

#define FOX_TENT_NO_PERSON 0xfff1
#define FOX_TENT_NO_ITEM 0xfff1

/* The field actor of this console's player. */
#define FOX_TENT_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player talked to him (slot
 * 0x48 agreed), the event of kind 6 he asked for (slot 0x58 agreed), an event starts, the event
 * ended. */
#define FOX_TENT_EVENT_TALK 0
#define FOX_TENT_EVENT_OWN 1
#define FOX_TENT_EVENT_STARTS 3
#define FOX_TENT_EVENT_ENDED 8

/* The vtable slot of his talk scene that resets it (FoxTentTalk_Reset). */
#define FOX_TENT_SLOT_RESET 0x08

/* The motions he asks for (scene_motion_request.h): a walk, a faster walk (at the rate 0x800)
 * and a turn. */
#define FOX_TENT_MOTION_WALK 1
#define FOX_TENT_MOTION_RUN 2
#define FOX_TENT_MOTION_TURN 3
#define FOX_TENT_RUN_RATE 0x800

/* The distances (fx32) beyond which he follows the player and runs, and the angle off the
 * player beyond which he turns. */
#define FOX_TENT_FOLLOW_DISTANCE 0x3000
#define FOX_TENT_RUN_DISTANCE 0x4000
#define FOX_TENT_TURN_ANGLE 0x2000

/* How far ahead of the player the item faced is looked for (2.0). */
#define FOX_TENT_REACH 0x2000

/* The frames he walks to the player before he talks. */
#define FOX_TENT_COME_FRAMES 50

/* Before this hour his tent closes. */
#define FOX_TENT_CLOSING_HOUR 6

/* The map's object he claims (collision_map.h): the way out. */
#define FOX_TENT_EXIT_OBJECT 0

/* The A button (PadState.pressed). */
#define FOX_TENT_BUTTON_A 1

/* His mover's pace (SceneMover_SetPace): pace 2 at 0.25, speeding up by 0x133 and slowing down
 * by 0x199. */
#define FOX_TENT_PACE 2
#define FOX_TENT_PACE_SPEED 0x400
#define FOX_TENT_PACE_SPEED_UP 0x133
#define FOX_TENT_PACE_SLOW_DOWN 0x199

/* The vtables of his class and of the classes he derives from. */
extern const u8 data_ov052_02261f40[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model and texture file names: "npc_sp/model/fox.nsbmd", "npc_sp/model/fox_tex.nsbtx". */
extern const char data_ov052_02261e5c[];
extern const char data_ov052_02261e8c[];
/* The functions of his states (filled at start-up by __sinit_ov052_02261c48). */
extern FoxTentStep data_ov052_02262000[FOX_TENT_STATES];
/* The word his motion requests carry. */
extern u16 data_020c80f8;
/* The buttons, and the pen: it came down this frame when both bytes are set. */
extern PadState data_021fbe40;
extern u8 data_021f6c38;
extern u8 data_021f6c34;
/* The map of the scene. */
extern AcreMap *data_021c80bc;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern const fx16 FX_SinCosTable_[];
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
/* The item code's constructor and destructor, as the game hands them to __cxa_vec_ctor and
 * __cxa_vec_cleanup (the game's symbols, main's room_interior.h and trivial_object.h). */
extern void func_02034ce0(void *code);
extern void func_020051b0(void *code);

static u8 *fox_tent_part(FoxTent *fox, u32 offset)
{
    return fox->base + offset;
}

static SceneMotion *fox_tent_motion(FoxTent *fox)
{
    return (SceneMotion *) (void *) fox_tent_part(fox, FOX_TENT_MOTION);
}

static SceneAction *fox_tent_action(FoxTent *fox)
{
    return (SceneAction *) (void *) fox_tent_part(fox, FOX_TENT_ACTION);
}

static SceneMover *fox_tent_mover(FoxTent *fox)
{
    return (SceneMover *) (void *) fox_tent_part(fox, FOX_TENT_MOVER);
}

static const Vec3 *fox_tent_position(FoxTent *fox)
{
    return (const Vec3 *) (const void *) fox_tent_part(fox, FOX_TENT_POSITION);
}

/* The angle he faces, as the 16-bit signed value it is read as. */
static s16 fox_tent_angle(FoxTent *fox)
{
    return *(const s16 *) (const void *) fox_tent_part(fox, FOX_TENT_ANGLE);
}

/* His motion of `kind` asked for (priority 1), at `rate`. */
static void fox_tent_request(FoxTent *fox, int kind, s16 rate)
{
    SceneMotion_Request(fox_tent_motion(fox), kind, 1, 0, 0, rate, 0, 0, 0, data_020c80f8, 0);
}

/* This console's player's start position (PlayerActorOps_StartPosition), copied. */
static Vec3 fox_tent_player_position(void)
{
    return *PlayerActorOps_StartPosition(FOX_TENT_PLAYER_ACTOR);
}

/* His talk scene reset through its vtable slot 0x08. */
static void fox_tent_reset_talk(FoxTent *fox)
{
    u32 vtable = *(const u32 *) (const void *) &fox->talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + FOX_TENT_SLOT_RESET);
    ((void (*)(FoxTentTalk *))(uintptr_t) code)(&fox->talk);
}

/* His talk's partner: this console's player's field actor. */
static void fox_tent_partner_player(FoxTent *fox)
{
    SceneBase_SetMotionArg(&fox->talk.base, SceneObject_ActorObject(fox->base, FOX_TENT_PLAYER_ACTOR));
}

/* The angle from him to this console's player. */
static int fox_tent_yaw_to_player(FoxTent *fox)
{
    return (int) (uintptr_t) SceneObject_YawToActor(fox->base, FOX_TENT_PLAYER_ACTOR);
}

/* Whether a code is the empty one: for a code with a variant, whether its item is the empty
 * code's item. */
static int fox_tent_no_item(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = FOX_TENT_NO_ITEM;
        int own = ItemCode_VariantItem(item);
        return own == ItemCode_VariantItem(&none);
    }
    return *item == FOX_TENT_NO_ITEM;
}

/* As he walks to the player: beyond 4.0 a walk becomes a run (rate 0x800), within it a run
 * becomes a walk. */
static void fox_tent_pace_to_distance(FoxTent *fox, int distance)
{
    if (distance > FOX_TENT_RUN_DISTANCE) {
        if (SceneMotion_Kind(fox_tent_motion(fox)) == FOX_TENT_MOTION_WALK) {
            fox_tent_request(fox, FOX_TENT_MOTION_RUN, FOX_TENT_RUN_RATE);
        }
    } else if (SceneMotion_Kind(fox_tent_motion(fox)) == FOX_TENT_MOTION_RUN) {
        fox_tent_request(fox, FOX_TENT_MOTION_WALK, 0);
    }
}

/* func_ov052_02260420 (vtable slot 0x40): the told items' destructors, his talk scene's
 * destructor, then the special character's; the object. */
FoxTent *FoxTent_Destruct(FoxTent *fox)
{
    *(const u8 **) (void *) fox->base = data_ov052_02261f40;
    __cxa_vec_cleanup(fox->told, FOX_TENT_TOLD_ITEMS, sizeof(u16), func_020051b0);
    FoxTentTalk_Destruct(&fox->talk);
    SpecialSceneObject_DestructBody(fox);
    return fox;
}
CLEAN_AS(func_ov052_02260420, FoxTent_Destruct)

/* func_ov052_0226045c (vtable slot 0x44): the same, then the object freed. */
FoxTent *FoxTent_DestructDelete(FoxTent *fox)
{
    *(const u8 **) (void *) fox->base = data_ov052_02261f40;
    __cxa_vec_cleanup(fox->told, FOX_TENT_TOLD_ITEMS, sizeof(u16), func_020051b0);
    FoxTentTalk_Destruct(&fox->talk);
    SpecialSceneObject_DestructBody(fox);
    Heap_FreeAux(fox);
    return fox;
}
CLEAN_AS(func_ov052_0226045c, FoxTent_DestructDelete)

/* ---- The reasons he talks */

/* func_ov052_022604a0: with no current event, before 6 a.m. his next talk is the closing one
 * and an event of kind 6 is asked for him. Whether it was. */
int FoxTent_TalkIfLate(FoxTent *fox)
{
    if (EventQueue_HasCurrent()) {
        return 0;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.hour >= FOX_TENT_CLOSING_HOUR) {
        return 0;
    }
    FoxTentTalk_SetSequence(&fox->talk, FOX_TENT_TALK_CLOSING);
    EventQueue_RequestKind6(fox, 0);
    return 1;
}
CLEAN_AS(func_ov052_022604a0, FoxTent_TalkIfLate)

/* func_ov052_022604ec: when this console's player stands on the way out (the map's claimed
 * object), his next talk is that of the exit (2 after a sale in this visit, else 1), an event
 * of kind 6 is asked for him and he turns to the player (state 10). Whether it was. */
int FoxTent_TalkAtExit(FoxTent *fox)
{
    Vec3 player = fox_tent_player_position();
    if (!CollisionMap_IsClaimedAtPoint(&player)) {
        return 0;
    }
    if (fox->sold == 0) {
        FoxTentTalk_SetSequence(&fox->talk, FOX_TENT_TALK_EXIT);
    } else {
        FoxTentTalk_SetSequence(&fox->talk, FOX_TENT_TALK_EXIT_AFTER_SALE);
    }
    EventQueue_RequestKind6(fox, 0);
    FoxTent_SetState(fox, FOX_TENT_AT_EXIT);
    return 1;
}
CLEAN_AS(func_ov052_022604ec, FoxTent_TalkAtExit)

/* func_ov052_02260554: when the player asks about an item faced (FoxTent_FindFacedItem), an
 * event of kind 6 is asked for him. Whether it was. */
int FoxTent_TalkAboutItem(FoxTent *fox)
{
    if (!FoxTent_FindFacedItem(fox)) {
        return 0;
    }
    EventQueue_RequestKind6(fox, 0);
    return 1;
}
CLEAN_AS(func_ov052_02260554, FoxTent_TalkAboutItem)

/* func_ov052_02260574: whether the player asks about an item on the tent's floor. With this
 * console's player's field actor, no current event, his action idle and either the A button
 * pressed or the pen come down this frame: the tile 2.0 ahead of the player (along the angle it
 * faces). With the pen, the tile must be the one tapped: the room's object on it must be the
 * object the pen picked, or with none there, the ground the pen met must be on it. The tile's
 * item of the fox's shop (overlay 4's ShopDisplay_ItemAt), unless none, is the item faced, with
 * its tile; his talk does not wait for answers. */
int FoxTent_FindFacedItem(FoxTent *fox)
{
    u8 *actor = SessionPlayers_ActorOf(FOX_TENT_PLAYER_ACTOR);
    int tapped = data_021f6c38 != 0 && data_021f6c34 != 0;

    if (actor == NULL || EventQueue_HasCurrent() || SceneAction_IsBusy(fox_tent_action(fox)) ||
        ((data_021fbe40.pressed & FOX_TENT_BUTTON_A) == 0 && !tapped)) {
        return 0;
    }

    Vec3 ahead = *(const Vec3 *) (const void *) (actor + FOX_TENT_ACTOR_POSITION);
    u16 angle = *(const u16 *) (const void *) (actor + FOX_TENT_ACTOR_ANGLE);
    int index = (angle >> 4) * 2;
    int x = 0;
    int z = 0;
    ahead.x += FX_MulFunc(FOX_TENT_REACH, FX_SinCosTable_[index]);
    ahead.z += FX_MulFunc(FOX_TENT_REACH, FX_SinCosTable_[index + 1]);
    Position_Tile(&x, &z, (const Position *) (const void *) &ahead);

    if (tapped) {
        TouchPick *pick;
        RoomObject *object = RoomObjects_GridObjectAt(RoomObjects_Grid(), x, z, 0);
        if (object != NULL) {
            pick = (TouchPick *) (uintptr_t) (u32) SceneQuery_FieldObject();
            if ((int) (uintptr_t) object != TouchPick_PickedObject(pick, NULL, NULL)) {
                return 0;
            }
        } else {
            int ground_x = 0;
            int ground_z = 0;
            Vec3 ground;
            pick = (TouchPick *) (uintptr_t) (u32) SceneQuery_FieldObject();
            TouchPick_GetGround(pick, &ground);
            Position_Tile(&ground_x, &ground_z, (const Position *) (const void *) &ground);
            if (ground_x != x || ground_z != z) {
                return 0;
            }
        }
    }

    u16 item = *ShopDisplay_ItemAt(x, z);
    if (fox_tent_no_item(&item)) {
        return 0;
    }
    fox->item = item;
    fox->item_x = x;
    fox->item_z = z;
    fox->awaiting_answers = 0;
    return 1;
}
CLEAN_AS(func_ov052_02260574, FoxTent_FindFacedItem)

/* ---- His vtable slots */

/* func_ov052_02260718 (vtable slot 0x4c, told of an event about him by `participant`'s system,
 * which is kept):
 * - 3, an event starts: paused (state 8);
 * - 0, the player talked to him: his talk scene reset with this console's player as the
 *   partner, and he talks (state 5);
 * - 1, the event he asked for: the same, then he talks at once for the greeting (state 5),
 *   talks before putting the player out for the exit and closing talks (state 6), else comes to
 *   the player first (state 9);
 * - 8, the event ended: after an exit talk, the way out is released when the player stands on
 *   it, else he stands; after the closing talk, main's entry record takes exit 0; else he
 *   stands. */
void FoxTent_OnEvent(FoxTent *fox, unsigned int code, int participant)
{
    FoxTentTalk *talk = &fox->talk;

    *fox_tent_part(fox, FOX_TENT_PARTICIPANT) = (u8) participant;
    switch (code) {
        case FOX_TENT_EVENT_STARTS:
            FoxTent_SetState(fox, FOX_TENT_PAUSED);
            break;
        case FOX_TENT_EVENT_OWN:
            fox_tent_reset_talk(fox);
            fox_tent_partner_player(fox);
            if (FoxTentTalk_Sequence(talk) == FOX_TENT_TALK_GREETING) {
                FoxTent_SetState(fox, FOX_TENT_TALK);
                break;
            }
            if (FoxTentTalk_Sequence(talk) == FOX_TENT_TALK_EXIT ||
                FoxTentTalk_Sequence(talk) == FOX_TENT_TALK_EXIT_AFTER_SALE ||
                FoxTentTalk_Sequence(talk) == FOX_TENT_TALK_CLOSING) {
                FoxTent_SetState(fox, FOX_TENT_TALK_THEN_OUT);
            } else {
                FoxTent_SetState(fox, FOX_TENT_COME);
            }
            break;
        case FOX_TENT_EVENT_TALK:
            fox_tent_reset_talk(fox);
            fox_tent_partner_player(fox);
            FoxTent_SetState(fox, FOX_TENT_TALK);
            break;
        case FOX_TENT_EVENT_ENDED:
            if (FoxTentTalk_Sequence(talk) == FOX_TENT_TALK_EXIT ||
                FoxTentTalk_Sequence(talk) == FOX_TENT_TALK_EXIT_AFTER_SALE) {
                Vec3 player = fox_tent_player_position();
                if (CollisionMap_IsClaimedAtPoint(&player)) {
                    CollisionMap_ClearClaim();
                } else {
                    FoxTent_SetState(fox, FOX_TENT_STAND);
                }
            } else if (FoxTentTalk_Sequence(talk) == FOX_TENT_TALK_CLOSING) {
                SceneExit_Take((SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord(), 0);
            } else {
                FoxTent_SetState(fox, FOX_TENT_STAND);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov052_02260718, FoxTent_OnEvent)

/* func_ov052_02260854 (vtable slot 0x58, whether an event of kind 6 about him may run): his
 * action idle and no system holding him. */
int FoxTent_MayAct1(FoxTent *fox)
{
    if (SceneAction_IsBusy(fox_tent_action(fox))) {
        return 0;
    }
    return SceneShare_IsHeld(fox->base) == 0;
}
CLEAN_AS(func_ov052_02260854, FoxTent_MayAct1)

/* func_ov052_02260880 (vtable slot 0x48): whether the player may talk to him: his action idle,
 * no system holding him, and the player not asking about an item (FoxTent_TalkAboutItem, which
 * then asks for its own event). */
int FoxTent_MayAct(FoxTent *fox)
{
    if (SceneAction_IsBusy(fox_tent_action(fox)) || SceneShare_IsHeld(fox->base) || FoxTent_TalkAboutItem(fox)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov052_02260880, FoxTent_MayAct)

/* ---- His states */

/* func_ov052_022611ac (state 10's update): once his turn is done he stands (priority 1, with his
 * stand's word); an event of kind 6 is asked for him each frame. 1. */
int FoxTent_UpdateAtExit(FoxTent *fox)
{
    if (SceneMotion_Kind(fox_tent_motion(fox)) == FOX_TENT_MOTION_TURN && SceneMotion_IsDone(fox_tent_motion(fox))) {
        SceneMotion_RequestStand(fox_tent_motion(fox), 1, fox->stand_word);
    }
    EventQueue_RequestKind6(fox, 0);
    return 1;
}
CLEAN_AS(func_ov052_022611ac, FoxTent_UpdateAtExit)

/* func_ov052_022611f0 (state 10's entry): a turn (priority 1), his mover set to the angle to the
 * player. 1. */
int FoxTent_EnterAtExit(FoxTent *fox)
{
    fox_tent_request(fox, FOX_TENT_MOTION_TURN, 0);
    SceneMover_SetAngle(fox_tent_mover(fox), fox_tent_yaw_to_player(fox));
    return 1;
}
CLEAN_AS(func_ov052_022611f0, FoxTent_EnterAtExit)

/* func_ov052_02261240 (state 9's update): his next step towards the player's start position
 * (ScenePathStep_Choose) and the distance to the player; he runs or walks by the distance and his
 * mover starts at the step. While the player is more than 3.0 away, the step moves him and his
 * frames to come have not run out, he goes on; else his talk scene is reset with this console's
 * player as the partner and he talks (state 5). 1.
 * QUIRK: the path directions of his tile are asked for (AcreTile_PathDirectionsAt) and not
 * used. */
int FoxTent_UpdateCome(FoxTent *fox)
{
    Vec3 player = fox_tent_player_position();
    Vec3 step;

    ScenePathStep_Choose(&step, fox->base, &player);
    int distance = SceneObject_DistanceToActor(fox->base, FOX_TENT_PLAYER_ACTOR);
    AcreTile_PathDirectionsAt(data_021c80bc, fox_tent_position(fox));
    fox_tent_pace_to_distance(fox, distance);
    SceneMover_SetStart(fox_tent_mover(fox), &step);

    if (distance > FOX_TENT_FOLLOW_DISTANCE && !Vec_Equal(&step, fox_tent_position(fox)) &&
        Countdown_Tick8(&fox->come_frames) != 0) {
        return 1;
    }
    fox_tent_reset_talk(fox);
    fox_tent_partner_player(fox);
    FoxTent_SetState(fox, FOX_TENT_TALK);
    return 1;
}
CLEAN_AS(func_ov052_02261240, FoxTent_UpdateCome)

/* func_ov052_02261358 (state 9's entry): 50 frames to come; a walk (priority 1). 1. */
int FoxTent_EnterCome(FoxTent *fox)
{
    fox->come_frames = FOX_TENT_COME_FRAMES;
    fox_tent_request(fox, FOX_TENT_MOTION_WALK, 0);
    return 1;
}
CLEAN_AS(func_ov052_02261358, FoxTent_EnterCome)

/* func_ov052_02261398 (state 8's update): nothing. 1. */
int FoxTent_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov052_02261398, FoxTent_UpdatePaused)

/* func_ov052_0226139c (state 8's entry): nothing. 1. */
int FoxTent_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov052_0226139c, FoxTent_EnterPaused)

/* func_ov052_022613a0 (state 7's update): nothing. 1. */
int FoxTent_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov052_022613a0, FoxTent_UpdateTalked)

/* func_ov052_022613a4 (state 7's entry): nothing. 1. */
int FoxTent_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov052_022613a4, FoxTent_EnterTalked)

/* func_ov052_022613a8 (state 6's update): once his action is idle, main's entry record takes the
 * scene's exit 0 (the player is put out of the tent), and state 7. 1.
 * QUIRK: this console's player's start position is read first and not used. */
int FoxTent_UpdateTalkThenOut(FoxTent *fox)
{
    (void) PlayerActorOps_StartPosition(FOX_TENT_PLAYER_ACTOR);
    if (!SceneAction_IsBusy(fox_tent_action(fox))) {
        SceneExit_Take((SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord(), 0);
        FoxTent_SetState(fox, FOX_TENT_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov052_022613a8, FoxTent_UpdateTalkThenOut)

/* His action turns him by the angle to his talk's partner (0 without one) and talks, keeping
 * the camera when `keep_camera`. */
static void fox_tent_turn_and_talk(FoxTent *fox, int keep_camera)
{
    int partner = SceneBase_MotionArg(&fox->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(fox->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(fox_tent_action(fox), 0, yaw, keep_camera);
}

/* func_ov052_022613ec (state 6's entry): he turns to his talk's partner and talks, keeping the
 * camera. 1. */
int FoxTent_EnterTalkThenOut(FoxTent *fox)
{
    fox_tent_turn_and_talk(fox, 1);
    return 1;
}
CLEAN_AS(func_ov052_022613ec, FoxTent_EnterTalkThenOut)

/* func_ov052_02261424 (state 5's update): once his action is idle and, when his talk waits for
 * them, every answer came (Shops_AllAnsweredA), his event ends and state 7. 1. */
int FoxTent_UpdateTalk(FoxTent *fox)
{
    if (SceneAction_IsBusy(fox_tent_action(fox))) {
        return 1;
    }
    if (fox->awaiting_answers != 0 && !Shops_AllAnsweredA()) {
        return 1;
    }
    EventQueue_FinishObjectEvent(fox);
    FoxTent_SetState(fox, FOX_TENT_TALKED);
    return 1;
}
CLEAN_AS(func_ov052_02261424, FoxTent_UpdateTalk)

/* func_ov052_0226146c (state 5's entry): he turns to his talk's partner and talks. 1. */
int FoxTent_EnterTalk(FoxTent *fox)
{
    fox_tent_turn_and_talk(fox, 0);
    return 1;
}
CLEAN_AS(func_ov052_0226146c, FoxTent_EnterTalk)

/* States 3 and 4's update: unless he talks (at the exit, closing, or about an item), his next
 * step towards the player's start position; he runs or walks by the distance to the player and
 * his mover starts at the step; within 3.0 of the player, or when the step does not move him, he
 * stands (state 1). 1. */
static int fox_tent_follow(FoxTent *fox)
{
    if (FoxTent_TalkAtExit(fox) || FoxTent_TalkIfLate(fox) || FoxTent_TalkAboutItem(fox)) {
        return 1;
    }
    Vec3 player = fox_tent_player_position();
    Vec3 step;
    int distance = SceneObject_DistanceToActor(fox->base, FOX_TENT_PLAYER_ACTOR);
    ScenePathStep_Choose(&step, fox->base, &player);
    fox_tent_pace_to_distance(fox, distance);
    SceneMover_SetStart(fox_tent_mover(fox), &step);
    if (distance <= FOX_TENT_FOLLOW_DISTANCE || Vec_Equal(&step, fox_tent_position(fox))) {
        FoxTent_SetState(fox, FOX_TENT_STAND);
    }
    return 1;
}

/* func_ov052_022614a4 (state 4's update): as state 3's. */
int FoxTent_UpdateFollow4(FoxTent *fox)
{
    return fox_tent_follow(fox);
}
CLEAN_AS(func_ov052_022614a4, FoxTent_UpdateFollow4)

/* func_ov052_022615a4 (state 4's entry): a walk (priority 1). 1. */
int FoxTent_EnterFollow4(FoxTent *fox)
{
    fox_tent_request(fox, FOX_TENT_MOTION_WALK, 0);
    return 1;
}
CLEAN_AS(func_ov052_022615a4, FoxTent_EnterFollow4)

/* func_ov052_022615d8 (state 3's update): see fox_tent_follow. */
int FoxTent_UpdateFollow(FoxTent *fox)
{
    return fox_tent_follow(fox);
}
CLEAN_AS(func_ov052_022615d8, FoxTent_UpdateFollow)

/* func_ov052_022616d8 (state 3's entry): a walk (priority 1). 1. */
int FoxTent_EnterFollow(FoxTent *fox)
{
    fox_tent_request(fox, FOX_TENT_MOTION_WALK, 0);
    return 1;
}
CLEAN_AS(func_ov052_022616d8, FoxTent_EnterFollow)

/* func_ov052_0226170c (state 2's update): unless he talks (at the exit, closing, or about an
 * item): when the player is more than 3.0 away and his next step towards the player moves him,
 * he follows (state 3); else his mover turns to the angle to the player, and once his turn is
 * done he stands (state 1). 1.
 * QUIRK: the angle between his facing and the player is asked for (Math_AbsDiff16) and not
 * used. */
int FoxTent_UpdateTurn(FoxTent *fox)
{
    if (FoxTent_TalkAtExit(fox) || FoxTent_TalkIfLate(fox) || FoxTent_TalkAboutItem(fox)) {
        return 1;
    }
    Vec3 player = fox_tent_player_position();
    Vec3 step;
    int distance = SceneObject_DistanceToActor(fox->base, FOX_TENT_PLAYER_ACTOR);
    int yaw = fox_tent_yaw_to_player(fox);
    Math_AbsDiff16(fox_tent_angle(fox), yaw);
    ScenePathStep_Choose(&step, fox->base, &player);
    if (distance > FOX_TENT_FOLLOW_DISTANCE && Vec_Differ(&step, fox_tent_position(fox))) {
        FoxTent_SetState(fox, FOX_TENT_FOLLOW);
        return 1;
    }
    SceneMover_SetAngle(fox_tent_mover(fox), yaw);
    if (SceneMotion_Kind(fox_tent_motion(fox)) == FOX_TENT_MOTION_TURN && SceneMotion_IsDone(fox_tent_motion(fox))) {
        FoxTent_SetState(fox, FOX_TENT_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov052_0226170c, FoxTent_UpdateTurn)

/* func_ov052_022617d4 (state 2's entry): a turn (priority 1). 1. */
int FoxTent_EnterTurn(FoxTent *fox)
{
    fox_tent_request(fox, FOX_TENT_MOTION_TURN, 0);
    return 1;
}
CLEAN_AS(func_ov052_022617d4, FoxTent_EnterTurn)

/* func_ov052_02261808 (state 1's update): when the player is more than 3.0 away and his next
 * step towards the player moves him, he follows (state 3); else when the player is more than an
 * eighth of a turn off his facing, he turns (state 2). Then he may talk (at the exit, closing,
 * or about an item). 1. */
int FoxTent_UpdateStand(FoxTent *fox)
{
    Vec3 player = fox_tent_player_position();
    Vec3 step;
    int distance = SceneObject_DistanceToActor(fox->base, FOX_TENT_PLAYER_ACTOR);
    int off = Math_AbsDiff16(fox_tent_angle(fox), fox_tent_yaw_to_player(fox));
    ScenePathStep_Choose(&step, fox->base, &player);
    if (distance > FOX_TENT_FOLLOW_DISTANCE && Vec_Differ(&step, fox_tent_position(fox))) {
        FoxTent_SetState(fox, FOX_TENT_FOLLOW);
    } else if (off > FOX_TENT_TURN_ANGLE) {
        FoxTent_SetState(fox, FOX_TENT_TURN);
    }
    if (FoxTent_TalkAtExit(fox) || FoxTent_TalkIfLate(fox)) {
        return 1;
    }
    FoxTent_TalkAboutItem(fox);
    return 1;
}
CLEAN_AS(func_ov052_02261808, FoxTent_UpdateStand)

/* func_ov052_022618a8 (state 1's entry): he stands (priority 1, with his stand's word), and his
 * next stand's word is the plain one. 1. */
int FoxTent_EnterStand(FoxTent *fox)
{
    SceneMotion_RequestStand(fox_tent_motion(fox), 1, fox->stand_word);
    fox->stand_word = data_020c80f8;
    return 1;
}
CLEAN_AS(func_ov052_022618a8, FoxTent_EnterStand)

/* func_ov052_022618d8 (state 0's update): an event of kind 6 asked for him. 1. */
int FoxTent_UpdateGreet(FoxTent *fox)
{
    EventQueue_RequestKind6(fox, 0);
    return 1;
}
CLEAN_AS(func_ov052_022618d8, FoxTent_UpdateGreet)

/* func_ov052_022618ec (state 0's entry): his next talk is the greeting. 1. */
int FoxTent_EnterGreet(FoxTent *fox)
{
    FoxTentTalk_SetSequence(&fox->talk, FOX_TENT_TALK_GREETING);
    return 1;
}
CLEAN_AS(func_ov052_022618ec, FoxTent_EnterGreet)

/* func_ov052_02261908: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 10 (the table is not bounded); the fox at a word-aligned address,
 * as every object of the game (the ROM's store drops the low two bits). */
void FoxTent_SetState(FoxTent *fox, int state)
{
    const FoxTentStep *step = &data_ov052_02262000[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, fox);
    }
    if (taken != 0) {
        fox->state = state;
    }
}
CLEAN_AS(func_ov052_02261908, FoxTent_SetState)

/* func_ov052_0226194c (vtable slot 0x68, each frame): his state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: his state is 0 to 10. */
int FoxTent_Update(FoxTent *fox)
{
    const FoxTentStep *step = &data_ov052_02262000[fox->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, fox);
}
CLEAN_AS(func_ov052_0226194c, FoxTent_Update)

/* func_ov052_02261998 (vtable slot 0x70): his model's file name. */
int FoxTent_ModelName(void)
{
    return (int) (uintptr_t) data_ov052_02261e5c;
}
CLEAN_AS(func_ov052_02261998, FoxTent_ModelName)

/* func_ov052_022619a0 (vtable slot 0x6c): his texture's file name. */
int FoxTent_TextureName(void)
{
    return (int) (uintptr_t) data_ov052_02261e8c;
}
CLEAN_AS(func_ov052_022619a0, FoxTent_TextureName)

/* func_ov052_022619a8 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (state 1) when the previous scene is not scene 0, else greets the player
 * (state 0); he claims the way out (the map's object 0); no item faced and none told. Whether
 * he started. */
int FoxTent_Start(FoxTent *fox)
{
    if (SpecialSceneObject_Start(fox) == 0) {
        return 0;
    }
    if (SceneQuery_Previous() != 0) {
        FoxTent_SetState(fox, FOX_TENT_STAND);
    } else {
        FoxTent_SetState(fox, FOX_TENT_GREET);
    }
    CollisionMap_Claim(FOX_TENT_EXIT_OBJECT);
    fox->item = FOX_TENT_NO_ITEM;
    for (int i = 0; i < FOX_TENT_TOLD_ITEMS; i++) {
        fox->told[i] = FOX_TENT_NO_ITEM;
    }
    return 1;
}
CLEAN_AS(func_ov052_022619a8, FoxTent_Start)

/* func_ov052_02261a04 (vtable slot 0x04, his set-up): unless the special character refuses, his
 * talk scene becomes his scene and gets him as its owner; his stand's word is the plain one, no
 * offer or thanks said yet, and his mover's pace 2 set. Whether he was set up. */
int FoxTent_Init(FoxTent *fox)
{
    if (SpecialSceneObject_Init(fox) == 0) {
        return 0;
    }
    SceneObject_SetScene(fox->base, &fox->talk.base);
    FoxTentTalk_Begin(&fox->talk, fox);
    fox->stand_word = data_020c80f8;
    MI_CpuFill8(fox->offer_used, 0, FOX_TENT_LINE_VARIANTS);
    MI_CpuFill8(fox->thanks_used, 0, FOX_TENT_LINE_VARIANTS);
    SceneMover_SetPace(fox_tent_mover(fox), FOX_TENT_PACE, FOX_TENT_PACE_SPEED, FOX_TENT_PACE_SPEED_UP,
                       FOX_TENT_PACE_SLOW_DOWN);
    return 1;
}
CLEAN_AS(func_ov052_02261a04, FoxTent_Init)

/* func_ov052_02261a8c (his record's create function): a zeroed block of 0x740 bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and members
 * in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link, then his
 * class's vtable, his talk scene, no item faced, the three told items (constructed as item
 * codes) and the item's tile (0, 0). Null when there is no room. */
void *FoxTent_Create(void)
{
    FoxTent *fox = (FoxTent *) Heap_AllocAuxZeroed(sizeof(FoxTent));
    if (fox == NULL) {
        return NULL;
    }
    u8 *object = fox->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) fox_tent_part(fox, FOX_TENT_PERSON) = FOX_TENT_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) fox_tent_part(fox, FOX_TENT_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) fox_tent_part(fox, FOX_TENT_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) fox_tent_part(fox, FOX_TENT_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) fox_tent_part(fox, FOX_TENT_ANIM));
    SceneMover_Construct(fox_tent_mover(fox));
    SceneProbe_Construct(fox_tent_part(fox, FOX_TENT_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) fox_tent_part(fox, FOX_TENT_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) fox_tent_part(fox, FOX_TENT_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) fox_tent_part(fox, FOX_TENT_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) fox_tent_part(fox, FOX_TENT_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) fox_tent_part(fox, FOX_TENT_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) fox_tent_part(fox, FOX_TENT_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) fox_tent_part(fox, FOX_TENT_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) fox_tent_part(fox, FOX_TENT_FOOTSTEPS));
    SceneMotion_Construct(fox_tent_motion(fox));
    SceneAction_Construct(fox_tent_action(fox));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) fox_tent_part(fox, FOX_TENT_HEAP));
    *(const u8 **) (void *) object = data_ov052_02261f40;
    FoxTentTalk_Construct(&fox->talk);
    fox->item = FOX_TENT_NO_ITEM;
    __cxa_vec_ctor(fox->told, FOX_TENT_TOLD_ITEMS, sizeof(u16), func_02034ce0, func_020051b0);
    fox->item_x = 0;
    fox->item_z = 0;
    return fox;
}
CLEAN_AS(func_ov052_02261a8c, FoxTent_Create)
