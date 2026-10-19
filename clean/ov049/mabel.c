/* Mabel of the Able Sisters (mabel.h): her object's vtable slots, what she notices of the
 * player, and her states. */
#include "mabel.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "mabel_talk.h"
#include "main/act_effects.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/collision_map.h"
#include "main/design_info.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/game_variables.h"
#include "main/item_code.h"
#include "main/item_form.h"
#include "main/layered_model.h"
#include "main/link_global.h"
#include "main/main_random.h"
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
#include "main/session.h"
#include "main/session_players.h"
#include "main/shops.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/talk_checks.h"
#include "main/touch_pick_shapes.h"
#include "ov004/room_objects.h"
#include "ov004/shop_display.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(MabelTalk, owner) == 0xb0 && offsetof(MabelTalk, mode) == 0xb4, "MabelTalk");
static_assert(offsetof(MabelTalk, sequence) == 0xb8 && offsetof(MabelTalk, price) == 0xbc, "MabelTalk");
static_assert(offsetof(MabelTalk, extra_bags) == 0xc0 && sizeof(MabelTalk) == 0xd0, "MabelTalk");
static_assert(offsetof(Mabel, state) == 0x654 && offsetof(Mabel, talk) == 0x658, "Mabel");
static_assert(offsetof(Mabel, tile_x) == 0x728 && offsetof(Mabel, tile_z) == 0x72c, "Mabel");
static_assert(offsetof(Mabel, worn) == 0x734 && offsetof(Mabel, worn_second) == 0x736, "Mabel");
static_assert(offsetof(Mabel, item) == 0x738 && offsetof(Mabel, design) == 0x73c, "Mabel");
static_assert(offsetof(Mabel, act_countdown) == 0x970 && offsetof(Mabel, stand_word) == 0x972, "Mabel");
static_assert(offsetof(Mabel, bought) == 0x974 && offsetof(Mabel, has_event) == 0x975, "Mabel");
static_assert(offsetof(Mabel, design_slot) == 0x976 && offsetof(Mabel, approach_frames) == 0x977, "Mabel");
static_assert(sizeof(Mabel) == 0x978, "the size Mabel_Create allocates");
static_assert(sizeof(MabelStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define MABEL_POSITION 0x5c        /* Vec3: her position */
#define MABEL_X 0x5c               /* fx32 */
#define MABEL_Z 0x64               /* fx32 */
#define MABEL_ANGLE 0x8e           /* s16: where she faces */
#define MABEL_WALK_ANGLE 0x94      /* s16: where she walks */
#define MABEL_PERSON 0xea          /* u16: her person code */
#define MABEL_MODEL 0xec           /* LayeredModel */
#define MABEL_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define MABEL_FACE 0x2ac           /* SceneFace */
#define MABEL_ANIM 0x334           /* SpeakerAnim */
#define MABEL_MOVER 0x350          /* SceneMover */
#define MABEL_PROBE 0x3a8          /* the probe */
#define MABEL_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define MABEL_LOOK 0x3b0           /* SceneLook */
#define MABEL_TALK_STATE 0x418     /* SceneTalkState */
#define MABEL_EFFECTS 0x420        /* ActEffects */
#define MABEL_COLLIDER 0x49c       /* CollisionContacts */
#define MABEL_CARRIER 0x4cc        /* FieldOwnedBody */
#define MABEL_FLAGS 0x4e8          /* u32: the scene object's flags (2: held) */
#define MABEL_EMITTER 0x514        /* SoundEmitterObject */
#define MABEL_FOOTSTEPS 0x558      /* Footsteps */
#define MABEL_PARTICIPANT 0x560    /* u8: whose system the last event came from */
#define MABEL_MOTION 0x564         /* SceneMotion */
#define MABEL_ACTION 0x618         /* SceneAction */
#define MABEL_HEAP 0x640           /* PoolLink */

#define MABEL_NO_ITEM 0xfff1
#define MABEL_HELD 2

/* The field actor of this console's player, and whom an event is for when it is for it. */
#define MABEL_PLAYER_ACTOR 4
#define MABEL_THIS_PLAYER 4

/* The codes of her vtable slot 0x4c (main's event_kinds.h): 1 is the event of kind 6 she
 * asked for. */
#define MABEL_EVENT_TALK 0
#define MABEL_EVENT_KIND6 1
#define MABEL_EVENT_STARTS 3
#define MABEL_EVENT_REFUSED 4
#define MABEL_EVENT_ENDED 8

/* The vtable slot of her talk scene that resets it. */
#define MABEL_TALK_SLOT_RESET 0x08

/* The game variable (bank 0) that, when set, makes her act as when linked. */
#define MABEL_VARIABLE 0x4a

/* The look she asks for when a talk ends: the player. */
#define MABEL_LOOK_PLAYER 1

/* The motion kinds she asks for (scene_motion_request.h): a walk, a faster one, a turn and her
 * act; the faster walk's rate. */
#define MABEL_MOTION_WALK 1
#define MABEL_MOTION_HURRY 2
#define MABEL_MOTION_TURN 3
#define MABEL_MOTION_ACT 10
#define MABEL_HURRY_RATE 0x800
/* The word of the stand after her act. */
#define MABEL_WORD_BLEND 0x18

/* The distances to the player (fx32) she hurries beyond and walks beyond, and the angle off
 * the player she turns beyond in state 1. */
#define MABEL_HURRY_DISTANCE 0x6000
#define MABEL_WALK_DISTANCE 0x5000
#define MABEL_TURN_ANGLE 0x2000

/* The dated events of kind 2 (day_events.h) and the frames before she acts on such a day:
 * 100 and 20 times 0 to 4 more. */
#define MABEL_EVENT_KIND 2
#define MABEL_ACT_FRAMES 100
#define MABEL_ACT_FRAMES_STEP 20
#define MABEL_ACT_FRAMES_STEPS 5
/* The frames she walks toward the player in state 13 before she talks anyway. */
#define MABEL_APPROACH_FRAMES 0x32

/* The daily bit (TalkChecks_TestSetDailyBit) set once she has greeted the player today. */
#define MABEL_DAILY_GREETED 0xf

/* How far ahead of the player the tile she looks at is (fx32, 2.0). */
#define MABEL_AHEAD 0x2000

/* The items on display she sells (by code): clothes and the like as they stand in the shop
 * (turned into the item carried, ItemForm_ToCarried), and the shop's designs (four codes
 * each, 0x3e04 to 0x3e23). */
#define MABEL_SHOWN_A_FIRST 0x3984
#define MABEL_SHOWN_A_LAST 0x3d83
#define MABEL_SHOWN_B_FIRST 0x3fa4
#define MABEL_SHOWN_B_LAST 0x40a3
#define MABEL_SHOWN_C_FIRST 0x40a4
#define MABEL_SHOWN_C_LAST 0x4123
#define MABEL_SHOWN_D_FIRST 0x4124
#define MABEL_SHOWN_D_LAST 0x4223
#define MABEL_SHOWN_E_FIRST 0x3e24
#define MABEL_SHOWN_E_LAST 0x3ea3
#define MABEL_DESIGN_FIRST 0x3e04
#define MABEL_DESIGN_LAST 0x3e23

/* Her body's radius and height, the collider's size, and her mover's pace (mode 2). */
#define MABEL_BODY_RADIUS 0x119a
#define MABEL_BODY_HEIGHT 0x2000
#define MABEL_COLLIDER_SIZE 0xf00
#define MABEL_PACE_MODE 2
#define MABEL_PACE_SPEED 0x333
#define MABEL_PACE_SPEED_UP 0xcc
#define MABEL_PACE_SLOW_DOWN 0x133

/* Where she stands when she starts in a linked game held by this system: (13.0, 25.0). */
#define MABEL_LINKED_X 0xd000
#define MABEL_LINKED_Z 0x19000

/* The vtables of her class and of the classes it derives from. */
extern const u8 data_ov049_02263544[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Her model and texture file names: "npc_sp/model/hgh.nsbmd", "npc_sp/model/hgh_tex.nsbtx". */
extern const char data_ov049_022632d8[];
extern const char data_ov049_02263308[];
/* The functions of her states (filled at start-up by __sinit_ov049_02262e14). */
extern MabelStep data_ov049_02263640[MABEL_STATES];
/* The word her motion requests carry, and the angle off the player she turns beyond when
 * linked. */
extern u16 data_020c80f8;
extern s16 data_020c80f0[];
/* The look's point and range when it names neither. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The map of the scene. */
extern AcreMap *data_021c80bc;
/* The buttons, and the pen coming down this frame (both bytes set). */
extern PadState data_021fbe40;
extern u8 data_021f6c38;
extern u8 data_021f6c34;
#define MABEL_PAD_A 0x0001
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;
/* The sine and cosine table (FX_SinCosTable_), and the SDK's fixed-point product. */
extern const fx16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);

static u8 *mabel_part(Mabel *mabel, u32 offset)
{
    return mabel->base + offset;
}

static SceneMotion *mabel_motion(Mabel *mabel)
{
    return (SceneMotion *) (void *) mabel_part(mabel, MABEL_MOTION);
}

static SceneAction *mabel_action(Mabel *mabel)
{
    return (SceneAction *) (void *) mabel_part(mabel, MABEL_ACTION);
}

static SceneMover *mabel_mover(Mabel *mabel)
{
    return (SceneMover *) (void *) mabel_part(mabel, MABEL_MOVER);
}

static const Vec3 *mabel_position(Mabel *mabel)
{
    return (const Vec3 *) (const void *) mabel_part(mabel, MABEL_POSITION);
}

static s16 mabel_angle(Mabel *mabel)
{
    return *(const s16 *) (const void *) mabel_part(mabel, MABEL_ANGLE);
}

static int mabel_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* The object owned by `owner` and held by `holder`, when it is ours. */
static void mabel_set_slots(Mabel *mabel, int owner, int holder)
{
    SceneShare_SetSlotsIfOurs(mabel->base, 1, owner, holder);
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int mabel_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, MABEL_VARIABLE) != 0;
}

/* Her talk scene reset through its vtable slot 0x08, the talk's partner this console's
 * player's field actor. */
static void mabel_reset_talk(Mabel *mabel)
{
    u32 vtable = *(const u32 *) (const void *) &mabel->talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + MABEL_TALK_SLOT_RESET);
    ((void (*)(MabelTalk *))(uintptr_t) code)(&mabel->talk);
    SceneBase_SetMotionArg(&mabel->talk.base, SceneObject_ActorObject(mabel->base, MABEL_PLAYER_ACTOR));
}

/* A motion of `kind` asked for (priority 1) at `rate` and `angle`, with the plain word. */
static void mabel_request(Mabel *mabel, int kind, s16 rate, s16 angle)
{
    SceneMotion_Request(mabel_motion(mabel), kind, 1, 0, 0, rate, angle, 0, 0, data_020c80f8, 0);
}

/* Whether her motion is of `kind` and done. */
static int mabel_motion_done(Mabel *mabel, int kind)
{
    return SceneMotion_Kind(mabel_motion(mabel)) == kind && SceneMotion_IsDone(mabel_motion(mabel));
}

static int mabel_yaw_to_player(Mabel *mabel)
{
    return (int) (uintptr_t) SceneObject_YawToActor(mabel->base, MABEL_PLAYER_ACTOR);
}

/* The step of the counter's path toward the player's start point (into `step`), and the
 * player's distance. The map's path directions at her position are asked for and not used. */
static int mabel_path_step(Mabel *mabel, Vec3 *step)
{
    Vec3 start = *PlayerActorOps_StartPosition(MABEL_PLAYER_ACTOR);
    ScenePathStep_Choose(step, mabel->base, &start);
    int distance = SceneObject_DistanceToActor(mabel->base, MABEL_PLAYER_ACTOR);
    AcreTile_PathDirectionsAt(data_021c80bc, mabel_position(mabel));
    return distance;
}

/* The walk of states 3 and 13 at the player's `distance`: the faster walk beyond 6.0 (from
 * the walk), the walk again within it (from the faster one); the mover starts toward `step`. */
static void mabel_walk_toward(Mabel *mabel, int distance, const Vec3 *step)
{
    if (distance > MABEL_HURRY_DISTANCE) {
        if (SceneMotion_Kind(mabel_motion(mabel)) == MABEL_MOTION_WALK) {
            mabel_request(mabel, MABEL_MOTION_HURRY, MABEL_HURRY_RATE, 0);
        }
    } else if (SceneMotion_Kind(mabel_motion(mabel)) == MABEL_MOTION_HURRY) {
        mabel_request(mabel, MABEL_MOTION_WALK, 0, 0);
    }
    SceneMover_SetStart(mabel_mover(mabel), step);
}

/* Whether the item code at `item` is empty (0xfff1, or a variant of the empty item). */
static int mabel_is_empty(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = MABEL_NO_ITEM;
        return ItemCode_VariantItem(item) == ItemCode_VariantItem(&none);
    }
    return *item == MABEL_NO_ITEM;
}

/* func_ov049_02260420 (vtable slot 0x40): her design's, her talk scene's and the special
 * character's destructors; the object. */
Mabel *Mabel_Destruct(Mabel *mabel)
{
    *(const u8 **) (void *) mabel = data_ov049_02263544;
    Design_Destruct(&mabel->design);
    MabelTalk_Destruct(&mabel->talk);
    SpecialSceneObject_DestructBody(mabel);
    return mabel;
}
CLEAN_AS(func_ov049_02260420, Mabel_Destruct)

/* func_ov049_02260454 (vtable slot 0x44): the same, then the object freed. */
void *Mabel_DestructDelete(Mabel *mabel)
{
    *(const u8 **) (void *) mabel = data_ov049_02263544;
    Design_Destruct(&mabel->design);
    MabelTalk_Destruct(&mabel->talk);
    SpecialSceneObject_DestructBody(mabel);
    Heap_FreeAux(mabel);
    return mabel;
}
CLEAN_AS(func_ov049_02260454, Mabel_DestructDelete)

/* func_ov049_0226048c: unlinked (and without the game variable 0x4a), when the player's start
 * point is claimed on the collision map, her talk takes mode 3, an event of kind 6 is asked
 * for and she turns to ask (state 15). Whether she did. */
int Mabel_CheckSpotTaken(Mabel *mabel)
{
    if (mabel_linked_or_variable(data_020ccf94)) {
        return 0;
    }
    Vec3 start = *PlayerActorOps_StartPosition(MABEL_PLAYER_ACTOR);
    if (CollisionMap_IsClaimedAtPoint(&start)) {
        MabelTalk_SetMode(&mabel->talk, MABEL_TALK_MODE_SPOT_TAKEN);
        EventQueue_RequestKind6(mabel, 0);
        Mabel_SetState(mabel, MABEL_STATE_TURN_ASK);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov049_0226048c, Mabel_CheckSpotTaken)

/* func_ov049_02260500: when the player faces an item on display (Mabel_FindShown), an event
 * of kind 6 is asked for. Whether it was. */
int Mabel_OfferShown(Mabel *mabel)
{
    if (Mabel_FindShown(mabel)) {
        EventQueue_RequestKind6(mabel, 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov049_02260500, Mabel_OfferShown)

/* func_ov049_02260520: whether the player asks about an item on display. Not without the
 * player's actor, during an event, while her action runs, or without A pressed or the pen
 * coming down this frame. The tile asked about is the one 2.0 ahead of the player (where it
 * faces); with the pen, the room object standing there must be the one touched, or, with none,
 * the ground touched must be on that tile. The item on that tile of the room: not an empty
 * one; the clothes and the like (MABEL_SHOWN_*, turned into the item carried) give talk mode 4,
 * the shop's designs talk mode 5, anything else nothing. The item and the tile are kept and
 * nothing is bought yet. The item is 0xfff1 from the first checks passed on, also when nothing
 * is found. */
int Mabel_FindShown(Mabel *mabel)
{
    u8 *player = (u8 *) SessionPlayers_ActorOf(MABEL_PLAYER_ACTOR);
    int touched = data_021f6c38 != 0 && data_021f6c34 != 0;

    if (player == NULL || EventQueue_HasCurrent() != 0 || SceneAction_IsBusy(mabel_action(mabel)) != 0 ||
        ((data_021fbe40.pressed & MABEL_PAD_A) == 0 && !touched)) {
        return 0;
    }

    mabel->item = MABEL_NO_ITEM;
    Vec3 ahead = *(const Vec3 *) (const void *) (player + MABEL_POSITION);
    u16 facing = *(const u16 *) (const void *) (player + MABEL_ANGLE);
    int x = 0;
    int z = 0;
    int i = (facing >> 4) * 2;
    ahead.x = ahead.x + FX_MulFunc(MABEL_AHEAD, FX_SinCosTable_[i]);
    ahead.z = ahead.z + FX_MulFunc(MABEL_AHEAD, FX_SinCosTable_[i + 1]);
    Position_Tile(&x, &z, (const Position *) (const void *) &ahead);

    if (touched) {
        int object = (int) (uintptr_t) RoomObjects_GridObjectAt(RoomObjects_Grid(), x, z, 0);
        if (object != 0) {
            if (object != TouchPick_PickedObject((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), NULL, NULL)) {
                return 0;
            }
        } else {
            Vec3 ground;
            int ground_x = 0;
            int ground_z = 0;
            TouchPick_GetGround((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &ground);
            Position_Tile(&ground_x, &ground_z, (const Position *) (const void *) &ground);
            if (ground_x != x || ground_z != z) {
                return 0;
            }
        }
    }

    u16 item = *(const u16 *) ShopDisplay_ListAItemAt(x, z);
    if (mabel_is_empty(&item)) {
        return 0;
    }
    if ((item >= MABEL_SHOWN_A_FIRST && item <= MABEL_SHOWN_A_LAST) ||
        (item >= MABEL_SHOWN_B_FIRST && item <= MABEL_SHOWN_B_LAST) ||
        (item >= MABEL_SHOWN_C_FIRST && item <= MABEL_SHOWN_C_LAST) ||
        (item >= MABEL_SHOWN_D_FIRST && item <= MABEL_SHOWN_D_LAST) ||
        (item >= MABEL_SHOWN_E_FIRST && item <= MABEL_SHOWN_E_LAST)) {
        u16 carried;
        ItemForm_ToCarried(&carried, &item);
        item = carried;
        MabelTalk_SetMode(&mabel->talk, MABEL_TALK_MODE_ITEM);
    } else if (item >= MABEL_DESIGN_FIRST && item <= MABEL_DESIGN_LAST) {
        MabelTalk_SetMode(&mabel->talk, MABEL_TALK_MODE_SHOP_DESIGN);
    } else {
        return 0;
    }
    mabel->item = item;
    mabel->tile_x = x;
    mabel->tile_z = z;
    mabel->bought = 0;
    return 1;
}
CLEAN_AS(func_ov049_02260520, Mabel_FindShown)

/* func_ov049_022607ac (vtable slot 0x4c, told of an event about her by `participant`'s
 * system, 4 for this one), then the scene object's own slot 0x4c:
 * - 3, an event starts: the participant kept; another system's: owned by this system and held
 *   by it, paused; this one's (with the object ours): owned and held by this system, paused;
 * - 1, the event of kind 6 she asked for: the participant kept; another system's (not this
 *   one's slot): owned and held by it, state 9; this one's (with the object ours): owned and
 *   held by this system; in talk mode 0 or 1 she talks (state 4), in mode 3 she talks and the
 *   player leaves (state 5); else linked (or with the game variable 0x4a) she talks, unlinked
 *   she first walks toward the player (state 13). Her talk is reset with this console's player
 *   as the partner before she talks;
 * - 0, the player talks to her: as 1 for another system; this one's: owned and held by this
 *   system, her talk reset with the partner, talk mode 2, and she talks;
 * - 8, the event ended, for this console's player: when this system holds the scene, owned by
 *   this one and held by none, she stands when linked (or with the game variable 0x4a), else,
 *   unless in talk mode 3, she stands (state 1); else owned by none and held by this system,
 *   she awaits the session;
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), owned by this system and held by none, state 10. */
void Mabel_OnEvent(Mabel *mabel, int code, int participant)
{
    switch (code) {
        case MABEL_EVENT_STARTS:
            *mabel_part(mabel, MABEL_PARTICIPANT) = (u8) participant;
            if (participant != MABEL_THIS_PLAYER) {
                mabel_set_slots(mabel, mabel_local_slot(), participant);
                Mabel_SetState(mabel, MABEL_STATE_PAUSED);
            } else if (SceneShare_IsOurs(mabel->base)) {
                int slot = mabel_local_slot();
                mabel_set_slots(mabel, slot, slot);
                Mabel_SetState(mabel, MABEL_STATE_PAUSED);
            }
            break;
        case MABEL_EVENT_KIND6:
            *mabel_part(mabel, MABEL_PARTICIPANT) = (u8) participant;
            if (participant != MABEL_THIS_PLAYER && participant != mabel_local_slot()) {
                mabel_set_slots(mabel, participant, participant);
                Mabel_SetState(mabel, MABEL_STATE_OTHER);
            } else if (SceneShare_IsOurs(mabel->base)) {
                NetSession *session = data_020ccf94;
                int slot = session->local_slot;
                mabel_set_slots(mabel, slot, slot);
                if (MabelTalk_Mode(&mabel->talk) == MABEL_TALK_MODE_AGAIN ||
                    MabelTalk_Mode(&mabel->talk) == MABEL_TALK_MODE_FIRST) {
                    mabel_reset_talk(mabel);
                    Mabel_SetState(mabel, MABEL_STATE_TALK);
                } else if (MabelTalk_Mode(&mabel->talk) == MABEL_TALK_MODE_SPOT_TAKEN) {
                    mabel_reset_talk(mabel);
                    Mabel_SetState(mabel, MABEL_STATE_TALK_LEAVE);
                } else if (mabel_linked_or_variable(session)) {
                    mabel_reset_talk(mabel);
                    Mabel_SetState(mabel, MABEL_STATE_TALK);
                } else {
                    Mabel_SetState(mabel, MABEL_STATE_APPROACH);
                }
            }
            break;
        case MABEL_EVENT_TALK:
            *mabel_part(mabel, MABEL_PARTICIPANT) = (u8) participant;
            if (participant != MABEL_THIS_PLAYER && participant != mabel_local_slot()) {
                mabel_set_slots(mabel, participant, participant);
                Mabel_SetState(mabel, MABEL_STATE_OTHER);
            } else if (SceneShare_IsOurs(mabel->base)) {
                int slot = mabel_local_slot();
                mabel_set_slots(mabel, slot, slot);
                mabel_reset_talk(mabel);
                MabelTalk_SetMode(&mabel->talk, MABEL_TALK_MODE_TALKED);
                Mabel_SetState(mabel, MABEL_STATE_TALK);
            }
            break;
        case MABEL_EVENT_ENDED:
            if (participant != MABEL_THIS_PLAYER) {
                break;
            }
            if (LinkGlobal_HoldsScene()) {
                NetSession *session = data_020ccf94;
                mabel_set_slots(mabel, session->local_slot, SCENE_SHARE_NO_SLOT);
                if (mabel_linked_or_variable(session)) {
                    Mabel_SetState(mabel, MABEL_STATE_LINKED_STAND);
                } else if (MabelTalk_Mode(&mabel->talk) != MABEL_TALK_MODE_SPOT_TAKEN) {
                    Mabel_SetState(mabel, MABEL_STATE_STAND);
                }
            } else {
                mabel_set_slots(mabel, SCENE_SHARE_NO_SLOT, mabel_local_slot());
                Mabel_SetState(mabel, MABEL_STATE_AWAIT);
            }
            break;
        case MABEL_EVENT_REFUSED: {
            if (SceneShare_IsHeld(mabel->base) == 0 || SceneShare_IsOurs(mabel->base) == 0) {
                break;
            }
            int owner = SCENE_SHARE_NO_SLOT;
            int holder = SCENE_SHARE_NO_SLOT;
            if (SceneShare_ReadSlots(mabel->base, &owner, &holder) == 0) {
                break;
            }
            if (participant == MABEL_THIS_PLAYER || participant == holder) {
                mabel_set_slots(mabel, mabel_local_slot(), SCENE_SHARE_NO_SLOT);
                Mabel_SetState(mabel, MABEL_STATE_LINKED_STAND);
            }
            break;
        }
        default:
            break;
    }
    SceneObject_Vfunc4c(mabel, code, participant);
}
CLEAN_AS(func_ov049_022607ac, Mabel_OnEvent)

/* func_ov049_02260a64 (vtable slot 0x58, the act of an event of kind 6): whether she agrees:
 * her action idle and no system holding her. */
int Mabel_MayActKind6(Mabel *mabel)
{
    if (SceneAction_IsBusy(mabel_action(mabel)) != 0) {
        return 0;
    }
    return SceneShare_IsHeld(mabel->base) == 0;
}
CLEAN_AS(func_ov049_02260a64, Mabel_MayActKind6)

/* func_ov049_02260a90 (vtable slot 0x48): whether the player may talk to her: her action
 * idle, no system holding her, and no item on display asked about (which asks for an event of
 * its own, Mabel_OfferShown). */
int Mabel_MayAct(Mabel *mabel)
{
    if (SceneAction_IsBusy(mabel_action(mabel)) != 0 || SceneShare_IsHeld(mabel->base) != 0 || Mabel_OfferShown(mabel) != 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov049_02260a90, Mabel_MayAct)

/* ---- Her states */

/* func_ov049_02262100 (state 15's update): once her turn is done she stands (her stand's
 * word); she faces the player, and an event of kind 6 is asked for. 1. */
int Mabel_UpdateTurnAsk(Mabel *mabel)
{
    if (mabel_motion_done(mabel, MABEL_MOTION_TURN)) {
        SceneMotion_RequestStand(mabel_motion(mabel), 1, mabel->stand_word);
    }
    SceneMover_SetAngle(mabel_mover(mabel), mabel_yaw_to_player(mabel));
    EventQueue_RequestKind6(mabel, 0);
    return 1;
}
CLEAN_AS(func_ov049_02262100, Mabel_UpdateTurnAsk)

/* func_ov049_02262158 (state 15's entry): a turn (priority 1, angle 0). 1. */
int Mabel_EnterTurnAsk(Mabel *mabel)
{
    mabel_request(mabel, MABEL_MOTION_TURN, 0, 0);
    return 1;
}
CLEAN_AS(func_ov049_02262158, Mabel_EnterTurnAsk)

/* func_ov049_0226218c (state 14's update): nothing. 1. */
int Mabel_UpdateSpeaker(void)
{
    return 1;
}
CLEAN_AS(func_ov049_0226218c, Mabel_UpdateSpeaker)

/* func_ov049_02262190 (state 14's entry): she stands as in state 1 (Mabel_EnterStand).
 * QUIRK: the function has no result, but the state machine takes what is left in r0, the
 * stand's 1. */
void Mabel_EnterSpeaker(Mabel *mabel)
{
    Mabel_EnterStand(mabel);
}
CLEAN_AS(func_ov049_02262190, Mabel_EnterSpeaker)

/* func_ov049_02262198 (vtable slot 0x90, a talk she was in ended): she looks at the player
 * (priority 0) and stands (state 1). */
void Mabel_TalkEnded(Mabel *mabel)
{
    SceneLook_Request((SceneLook *) (void *) mabel_part(mabel, MABEL_LOOK), MABEL_LOOK_PLAYER, 0, 0, &data_021fbee8,
                      MABEL_PLAYER_ACTOR, data_020c814c, 1);
    Mabel_SetState(mabel, MABEL_STATE_STAND);
}
CLEAN_AS(func_ov049_02262198, Mabel_TalkEnded)

/* func_ov049_022621d8 (vtable slot 0x8c, she joined a talk as a speaker): state 14. */
void Mabel_JoinedTalk(Mabel *mabel)
{
    Mabel_SetState(mabel, MABEL_STATE_SPEAKER);
}
CLEAN_AS(func_ov049_022621d8, Mabel_JoinedTalk)

/* func_ov049_022621e4 (state 13's update): she walks toward the player along the counter's
 * path (mabel_walk_toward); while the player is farther than 5.0 and she is not at the path's
 * step, she goes on for up to 50 frames; then her talk is reset with this console's player as
 * the partner and she talks. 1. */
int Mabel_UpdateApproach(Mabel *mabel)
{
    Vec3 step;
    int distance = mabel_path_step(mabel, &step);
    mabel_walk_toward(mabel, distance, &step);
    if (distance > MABEL_WALK_DISTANCE && Vec_Equal(&step, mabel_position(mabel)) == 0 &&
        Countdown_Tick8(&mabel->approach_frames) != 0) {
        return 1;
    }
    mabel_reset_talk(mabel);
    Mabel_SetState(mabel, MABEL_STATE_TALK);
    return 1;
}
CLEAN_AS(func_ov049_022621e4, Mabel_UpdateApproach)

/* func_ov049_022622fc (state 13's entry): 50 frames to walk, and a walk asked for. 1. */
int Mabel_EnterApproach(Mabel *mabel)
{
    mabel->approach_frames = MABEL_APPROACH_FRAMES;
    mabel_request(mabel, MABEL_MOTION_WALK, 0, 0);
    return 1;
}
CLEAN_AS(func_ov049_022622fc, Mabel_EnterApproach)

/* func_ov049_0226233c (state 12's update): nothing. 1. */
int Mabel_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov049_0226233c, Mabel_UpdatePaused)

/* func_ov049_02262340 (state 12's entry): nothing. 1. */
int Mabel_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov049_02262340, Mabel_EnterPaused)

/* func_ov049_02262344 (state 11's update): once her turn is done, state 10. 1. */
int Mabel_UpdateLinkedTurn(Mabel *mabel)
{
    if (mabel_motion_done(mabel, MABEL_MOTION_TURN)) {
        Mabel_SetState(mabel, MABEL_STATE_LINKED_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov049_02262344, Mabel_UpdateLinkedTurn)

/* func_ov049_02262374 (state 11's entry): a turn (priority 1) to the player. 1. */
int Mabel_EnterLinkedTurn(Mabel *mabel)
{
    int yaw = mabel_yaw_to_player(mabel);
    mabel_request(mabel, MABEL_MOTION_TURN, 0, (s16) yaw);
    return 1;
}
CLEAN_AS(func_ov049_02262374, Mabel_EnterLinkedTurn)

/* func_ov049_022623b4 (state 10's update): when she faces data_020c80f0[0] or more off the
 * player she turns (state 11), else she looks for an item on display asked about. 1. */
int Mabel_UpdateLinkedStand(Mabel *mabel)
{
    int yaw = mabel_yaw_to_player(mabel);
    int off = Math_AbsDiff16(mabel_angle(mabel), yaw);
    if (off >= data_020c80f0[0]) {
        Mabel_SetState(mabel, MABEL_STATE_LINKED_TURN);
    } else {
        Mabel_OfferShown(mabel);
    }
    return 1;
}
CLEAN_AS(func_ov049_022623b4, Mabel_UpdateLinkedStand)

/* func_ov049_022623f0 (state 10's entry): she stands (priority 1, her stand's word). 1. */
int Mabel_EnterLinkedStand(Mabel *mabel)
{
    SceneMotion_RequestStand(mabel_motion(mabel), 1, mabel->stand_word);
    return 1;
}
CLEAN_AS(func_ov049_022623f0, Mabel_EnterLinkedStand)

/* func_ov049_02262414 (state 9's update, another system's player talked to her): once the
 * object is ours, the shared slots read show no owner and this system holds the scene, she is
 * owned by this system, held by none, and stands (state 10). 1. */
int Mabel_UpdateOther(Mabel *mabel)
{
    if (SceneShare_IsOurs(mabel->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(mabel->base, &owner, &holder) && owner == SCENE_SHARE_NO_SLOT && LinkGlobal_HoldsScene()) {
            mabel_set_slots(mabel, mabel_local_slot(), SCENE_SHARE_NO_SLOT);
            Mabel_SetState(mabel, MABEL_STATE_LINKED_STAND);
        }
    }
    return 1;
}
CLEAN_AS(func_ov049_02262414, Mabel_UpdateOther)

/* func_ov049_0226246c (state 9's entry): nothing. 1. */
int Mabel_EnterOther(void)
{
    return 1;
}
CLEAN_AS(func_ov049_0226246c, Mabel_EnterOther)

/* func_ov049_02262470 (state 8's update, awaiting the session): with the object ours, when the
 * shared slots read have this system as both owner and holder, they are set so, her talk is
 * reset with this console's player as the partner, takes talk mode 2 when no item on display
 * is talked about, and she talks; else, when this system holds the scene and no system holds
 * her, she is owned by this system and stands (state 10). Without the object ours, she looks
 * for an item on display asked about. 1. */
int Mabel_UpdateAwait(Mabel *mabel)
{
    if (!SceneShare_IsOurs(mabel->base)) {
        Mabel_OfferShown(mabel);
        return 1;
    }
    int owner = SCENE_SHARE_NO_SLOT;
    int holder = SCENE_SHARE_NO_SLOT;
    if (SceneShare_ReadSlots(mabel->base, &owner, &holder) && owner == mabel_local_slot() && owner == holder) {
        mabel_set_slots(mabel, mabel_local_slot(), mabel_local_slot());
        mabel_reset_talk(mabel);
        if (mabel_is_empty(&mabel->item)) {
            MabelTalk_SetMode(&mabel->talk, MABEL_TALK_MODE_TALKED);
        }
        Mabel_SetState(mabel, MABEL_STATE_TALK);
    } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
        mabel_set_slots(mabel, mabel_local_slot(), SCENE_SHARE_NO_SLOT);
        Mabel_SetState(mabel, MABEL_STATE_LINKED_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov049_02262470, Mabel_UpdateAwait)

/* func_ov049_02262568 (state 8's entry): nothing. 1. */
int Mabel_EnterAwait(void)
{
    return 1;
}
CLEAN_AS(func_ov049_02262568, Mabel_EnterAwait)

/* func_ov049_0226256c (state 7's update): unless the player's start point is taken or an item
 * on display is asked about, once her act is done her next stand blends in (word 0x18) and
 * she stands. 1. */
int Mabel_UpdateAct(Mabel *mabel)
{
    if (Mabel_CheckSpotTaken(mabel) || Mabel_OfferShown(mabel)) {
        return 1;
    }
    if (mabel_motion_done(mabel, MABEL_MOTION_ACT)) {
        mabel->stand_word = MABEL_WORD_BLEND;
        Mabel_SetState(mabel, MABEL_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov049_0226256c, Mabel_UpdateAct)

/* func_ov049_022625c0 (state 7's entry): her act (motion kind 10, priority 1). 1. */
int Mabel_EnterAct(Mabel *mabel)
{
    mabel_request(mabel, MABEL_MOTION_ACT, 0, 0);
    return 1;
}
CLEAN_AS(func_ov049_022625c0, Mabel_EnterAct)

/* func_ov049_022625f4 (state 6's update): nothing. 1. */
int Mabel_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov049_022625f4, Mabel_UpdateTalked)

/* func_ov049_022625f8 (state 6's entry): nothing. 1. */
int Mabel_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov049_022625f8, Mabel_EnterTalked)

/* func_ov049_022625fc (state 5's update): once her action is idle, main's entry record takes
 * exit 0 (the player is put out of the shop) and state 6. 1. */
int Mabel_UpdateTalkLeave(Mabel *mabel)
{
    if (SceneAction_IsBusy(mabel_action(mabel)) == 0) {
        SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0);
        Mabel_SetState(mabel, MABEL_STATE_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov049_022625fc, Mabel_UpdateTalkLeave)

/* func_ov049_0226262c (state 5's entry): her action turns her by the yaw to her talk's
 * partner (0 without one) and talks, keeping the camera. 1. */
int Mabel_EnterTalkLeave(Mabel *mabel)
{
    int partner = SceneBase_MotionArg(&mabel->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(mabel->base, (u8 *) (uintptr_t) partner);
    }
    SceneAction_RequestTurnAndTalk(mabel_action(mabel), 0, yaw, 1);
    return 1;
}
CLEAN_AS(func_ov049_0226262c, Mabel_EnterTalkLeave)

/* func_ov049_02262664 (state 4's update): once her action is idle and, with the item on
 * display bought, the shops' answers are all in (Shops_AllAnsweredB), her event ends and
 * state 6. 1. */
int Mabel_UpdateTalk(Mabel *mabel)
{
    if (SceneAction_IsBusy(mabel_action(mabel)) != 0) {
        return 1;
    }
    if (mabel->bought != 0 && Shops_AllAnsweredB() == 0) {
        return 1;
    }
    EventQueue_FinishObjectEvent(mabel);
    Mabel_SetState(mabel, MABEL_STATE_TALKED);
    return 1;
}
CLEAN_AS(func_ov049_02262664, Mabel_UpdateTalk)

/* func_ov049_022626ac (state 4's entry): her action turns her by the yaw to her talk's
 * partner (0 without one) and talks. 1. */
int Mabel_EnterTalk(Mabel *mabel)
{
    int partner = SceneBase_MotionArg(&mabel->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(mabel->base, (u8 *) (uintptr_t) partner);
    }
    SceneAction_RequestTurnAndTalk(mabel_action(mabel), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov049_022626ac, Mabel_EnterTalk)

/* func_ov049_022626e4 (state 3's update): unless the player's start point is taken or an item
 * on display is asked about, she walks toward the player along the counter's path
 * (mabel_walk_toward) and stands once the player is within 5.0 or she is at the path's step.
 * 1. */
int Mabel_UpdateWalk(Mabel *mabel)
{
    if (Mabel_CheckSpotTaken(mabel) || Mabel_OfferShown(mabel)) {
        return 1;
    }
    Vec3 step;
    int distance = mabel_path_step(mabel, &step);
    mabel_walk_toward(mabel, distance, &step);
    if (distance <= MABEL_WALK_DISTANCE || Vec_Equal(&step, mabel_position(mabel)) != 0) {
        Mabel_SetState(mabel, MABEL_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov049_022626e4, Mabel_UpdateWalk)

/* func_ov049_022627e4 (state 3's entry): a walk (priority 1). 1. */
int Mabel_EnterWalk(Mabel *mabel)
{
    mabel_request(mabel, MABEL_MOTION_WALK, 0, 0);
    return 1;
}
CLEAN_AS(func_ov049_022627e4, Mabel_EnterWalk)

/* func_ov049_02262818 (state 2's update): unless the player's start point is taken or an item
 * on display is asked about: she walks (state 3) when the player is farther than 5.0 and the
 * path's step is not where she is; she faces the player, and stands once her turn is done.
 * The difference of her angle and the yaw is computed and not used. 1. */
int Mabel_UpdateTurn(Mabel *mabel)
{
    if (Mabel_CheckSpotTaken(mabel) || Mabel_OfferShown(mabel)) {
        return 1;
    }
    Vec3 start = *PlayerActorOps_StartPosition(MABEL_PLAYER_ACTOR);
    Vec3 step;
    ScenePathStep_Choose(&step, mabel->base, &start);
    int distance = SceneObject_DistanceToActor(mabel->base, MABEL_PLAYER_ACTOR);
    int yaw = mabel_yaw_to_player(mabel);
    Math_AbsDiff16(mabel_angle(mabel), yaw);
    AcreTile_PathDirectionsAt(data_021c80bc, mabel_position(mabel));
    if (distance > MABEL_WALK_DISTANCE && Vec_Differ(&step, mabel_position(mabel)) != 0) {
        Mabel_SetState(mabel, MABEL_STATE_WALK);
    }
    SceneMover_SetAngle(mabel_mover(mabel), yaw);
    if (mabel_motion_done(mabel, MABEL_MOTION_TURN)) {
        Mabel_SetState(mabel, MABEL_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov049_02262818, Mabel_UpdateTurn)

/* func_ov049_022628e0 (state 2's entry): a turn (priority 1). 1. */
int Mabel_EnterTurn(Mabel *mabel)
{
    mabel_request(mabel, MABEL_MOTION_TURN, 0, 0);
    return 1;
}
CLEAN_AS(func_ov049_022628e0, Mabel_EnterTurn)

/* func_ov049_02262914 (state 1's update): she walks (state 3) when the player is farther than
 * 5.0 and the path's step is not where she is, else turns (state 2) when she faces more than
 * 0x2000 off the player. Then, unless the player's start point is taken or an item on display
 * is asked about, with a dated event of kind 2 today she acts (state 7) once her countdown
 * ends. 1. */
int Mabel_UpdateStand(Mabel *mabel)
{
    Vec3 start = *PlayerActorOps_StartPosition(MABEL_PLAYER_ACTOR);
    Vec3 step;
    ScenePathStep_Choose(&step, mabel->base, &start);
    int distance = SceneObject_DistanceToActor(mabel->base, MABEL_PLAYER_ACTOR);
    int yaw = mabel_yaw_to_player(mabel);
    int off = Math_AbsDiff16(mabel_angle(mabel), yaw);
    AcreTile_PathDirectionsAt(data_021c80bc, mabel_position(mabel));
    if (distance > MABEL_WALK_DISTANCE && Vec_Differ(&step, mabel_position(mabel)) != 0) {
        Mabel_SetState(mabel, MABEL_STATE_WALK);
    } else if (off > MABEL_TURN_ANGLE) {
        Mabel_SetState(mabel, MABEL_STATE_TURN);
    }
    if (Mabel_CheckSpotTaken(mabel) || Mabel_OfferShown(mabel)) {
        return 1;
    }
    if (mabel->has_event != 0 && Countdown_Tick16(&mabel->act_countdown) == 0) {
        Mabel_SetState(mabel, MABEL_STATE_ACT);
    }
    return 1;
}
CLEAN_AS(func_ov049_02262914, Mabel_UpdateStand)

/* func_ov049_022629e4 (state 1's entry): she stands (priority 1, her stand's word), her next
 * stand's word is the plain one, she acts after 100 to 180 frames (in steps of 20, at random)
 * and notes whether the player has a dated event of kind 2 today. 1. */
int Mabel_EnterStand(Mabel *mabel)
{
    u8 event;
    SceneMotion_RequestStand(mabel_motion(mabel), 1, mabel->stand_word);
    mabel->stand_word = data_020c80f8;
    mabel->act_countdown = (u16) (MainRandom_Below(MABEL_ACT_FRAMES_STEPS) * MABEL_ACT_FRAMES_STEP + MABEL_ACT_FRAMES);
    mabel->has_event = TalkChecks_TodaysEventOfKind((int) (uintptr_t) mabel, &event, MABEL_EVENT_KIND) != 0 ? 1 : 0;
    return 1;
}
CLEAN_AS(func_ov049_022629e4, Mabel_EnterStand)

/* func_ov049_02262a4c (state 0's update): an event of kind 6 asked for. 1. */
int Mabel_UpdateGreet(Mabel *mabel)
{
    EventQueue_RequestKind6(mabel, 0);
    return 1;
}
CLEAN_AS(func_ov049_02262a4c, Mabel_UpdateGreet)

/* func_ov049_02262a60 (state 0's entry): the daily bit 15 tested and set: her talk takes mode
 * 1 when it was set already (greeted today), else mode 0. 1. */
int Mabel_EnterGreet(Mabel *mabel)
{
    if (TalkChecks_TestSetDailyBit(MABEL_DAILY_GREETED, 1) != 0) {
        MabelTalk_SetMode(&mabel->talk, MABEL_TALK_MODE_AGAIN);
    } else {
        MabelTalk_SetMode(&mabel->talk, MABEL_TALK_MODE_FIRST);
    }
    return 1;
}
CLEAN_AS(func_ov049_02262a60, Mabel_EnterGreet)

/* func_ov049_02262a94: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 15 (the table is not bounded). */
void Mabel_SetState(Mabel *mabel, int state)
{
    const MabelStep *step = &data_ov049_02263640[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, mabel);
    }
    if (taken != 0) {
        mabel->state = state;
    }
}
CLEAN_AS(func_ov049_02262a94, Mabel_SetState)

/* func_ov049_02262ad8 (vtable slot 0x68, each frame): her state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: her state is 0 to 15. */
int Mabel_Update(Mabel *mabel)
{
    const MabelStep *step = &data_ov049_02263640[mabel->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, mabel);
}
CLEAN_AS(func_ov049_02262ad8, Mabel_Update)

/* func_ov049_02262b24 (vtable slot 0x70): her model's file name. */
int Mabel_ModelName(void)
{
    return (int) (uintptr_t) data_ov049_022632d8;
}
CLEAN_AS(func_ov049_02262b24, Mabel_ModelName)

/* func_ov049_02262b2c (vtable slot 0x6c): her texture's file name. */
int Mabel_TextureName(void)
{
    return (int) (uintptr_t) data_ov049_02263308;
}
CLEAN_AS(func_ov049_02262b2c, Mabel_TextureName)

/* func_ov049_02262b34 (vtable slot 0x00, her start): unless the special character refuses to
 * start: linked (or with the game variable 0x4a set) she is held (flag 2 at 0x4e8); when this
 * system holds the scene she is put at (13.0, 25.0) facing and walking angle 0 and stands
 * (state 10), else she awaits the session. Unlinked she greets (state 0) when the scene came
 * from none (SceneQuery_Previous 0), else stands; she claims her place on the collision map
 * and notes a dated event of kind 2 today. Whether she started. */
int Mabel_Start(Mabel *mabel)
{
    u8 event;

    if (SpecialSceneObject_Start(mabel) == 0) {
        return 0;
    }
    u32 *flags = (u32 *) (void *) mabel_part(mabel, MABEL_FLAGS);
    if (mabel_linked_or_variable(data_020ccf94)) {
        if (LinkGlobal_HoldsScene()) {
            *flags |= MABEL_HELD;
            *(u32 *) (void *) mabel_part(mabel, MABEL_X) = MABEL_LINKED_X;
            *(u32 *) (void *) mabel_part(mabel, MABEL_Z) = MABEL_LINKED_Z;
            *(s16 *) (void *) mabel_part(mabel, MABEL_ANGLE) = 0;
            *(s16 *) (void *) mabel_part(mabel, MABEL_WALK_ANGLE) = 0;
            Mabel_SetState(mabel, MABEL_STATE_LINKED_STAND);
        } else {
            *flags |= MABEL_HELD;
            Mabel_SetState(mabel, MABEL_STATE_AWAIT);
        }
        return 1;
    }
    if (SceneQuery_Previous() == 0) {
        Mabel_SetState(mabel, MABEL_STATE_GREET);
    } else {
        Mabel_SetState(mabel, MABEL_STATE_STAND);
    }
    CollisionMap_Claim(0);
    if (TalkChecks_TodaysEventOfKind((int) (uintptr_t) mabel, &event, MABEL_EVENT_KIND)) {
        mabel->has_event = 1;
    }
    return 1;
}
CLEAN_AS(func_ov049_02262b34, Mabel_Start)

/* func_ov049_02262c00 (vtable slot 0x04, her set-up): unless the special character refuses,
 * her talk scene becomes her scene and gets her as its owner; her body is 0x119a wide and
 * 0x2000 high, her collider 0xf00; her stand's word is the plain one and her mover's pace
 * (mode 2) is set. Whether she was set up. */
int Mabel_Init(Mabel *mabel)
{
    if (SpecialSceneObject_Init(mabel) == 0) {
        return 0;
    }
    SceneObject_SetScene(mabel->base, &mabel->talk.base);
    MabelTalk_Begin(&mabel->talk, mabel);
    SpecialSceneObject_SetBodySize(mabel->base, MABEL_BODY_RADIUS, MABEL_BODY_HEIGHT);
    SceneObject_SetColliderSize(mabel->base, MABEL_COLLIDER_SIZE);
    mabel->stand_word = data_020c80f8;
    SceneMover_SetPace(mabel_mover(mabel), MABEL_PACE_MODE, MABEL_PACE_SPEED, MABEL_PACE_SPEED_UP, MABEL_PACE_SLOW_DOWN);
    return 1;
}
CLEAN_AS(func_ov049_02262c00, Mabel_Init)

/* func_ov049_02262c80 (her record's create function, data_ov049_022632f0): a zeroed block of
 * 0x978 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then her class's vtable, her talk scene, no tile and no
 * item, and her design. Null when there is no room. */
void *Mabel_Create(void)
{
    Mabel *mabel = (Mabel *) Heap_AllocAuxZeroed(sizeof(Mabel));
    if (mabel == NULL) {
        return NULL;
    }
    u8 *object = mabel->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) mabel_part(mabel, MABEL_PERSON) = MABEL_NO_ITEM;
    LayeredModel_ConstructB((LayeredModel *) (void *) mabel_part(mabel, MABEL_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) mabel_part(mabel, MABEL_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) mabel_part(mabel, MABEL_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) mabel_part(mabel, MABEL_ANIM));
    SceneMover_Construct(mabel_mover(mabel));
    SceneProbe_Construct(mabel_part(mabel, MABEL_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) mabel_part(mabel, MABEL_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) mabel_part(mabel, MABEL_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) mabel_part(mabel, MABEL_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) mabel_part(mabel, MABEL_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) mabel_part(mabel, MABEL_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) mabel_part(mabel, MABEL_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) mabel_part(mabel, MABEL_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) mabel_part(mabel, MABEL_FOOTSTEPS));
    SceneMotion_Construct(mabel_motion(mabel));
    SceneAction_Construct(mabel_action(mabel));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) mabel_part(mabel, MABEL_HEAP));
    *(const u8 **) (void *) object = data_ov049_02263544;
    MabelTalk_Construct(&mabel->talk);
    mabel->tile_x = 0;
    mabel->tile_z = 0;
    mabel->item = MABEL_NO_ITEM;
    Design_Construct((char *) (void *) &mabel->design);
    return mabel;
}
CLEAN_AS(func_ov049_02262c80, Mabel_Create)
