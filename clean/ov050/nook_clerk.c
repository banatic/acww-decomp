/* Tom Nook and the twins in the store (nook_clerk.h): the object's vtable slots, what a clerk
 * notices of the player, and the states. */
#include "nook_clerk.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/block_021d27ac.h"
#include "main/block_021d27ac_parts.h"
#include "main/camera_modes.h"
#include "main/collision_map.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/game_variables.h"
#include "main/item_code.h"
#include "main/item_lists.h"
#include "main/item_object.h"
#include "main/layered_model.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_exit.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_music.h"
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
#include "main/villager_part.h"
#include "main/villager_part_block.h"
#include "nook_clerk_talk.h"
#include "ov004/room_objects.h"
#include "ov004/shop_display.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(NookClerkTalk, mode) == 0xb0 && offsetof(NookClerkTalk, owner) == 0xb4, "NookClerkTalk");
static_assert(offsetof(NookClerkTalk, sequence) == 0xb8 && offsetof(NookClerkTalk, extra_bags) == 0xc0, "NookClerkTalk");
static_assert(offsetof(NookClerkTalk, price) == 0xc4 && offsetof(NookClerkTalk, package_slot) == 0xcc, "NookClerkTalk");
static_assert(offsetof(NookClerkTalk, line) == 0xd0 && sizeof(NookClerkTalk) == 0xd4, "NookClerkTalk");
static_assert(offsetof(NookClerk, state) == 0x654 && offsetof(NookClerk, talk) == 0x658, "NookClerk");
static_assert(offsetof(NookClerk, has_event) == 0x72c && offsetof(NookClerk, act_countdown) == 0x72e, "NookClerk");
static_assert(offsetof(NookClerk, stand_word) == 0x730 && offsetof(NookClerk, item) == 0x732, "NookClerk");
static_assert(offsetof(NookClerk, tile_x) == 0x734 && offsetof(NookClerk, tile_z) == 0x738, "NookClerk");
static_assert(offsetof(NookClerk, bought) == 0x73c && offsetof(NookClerk, approach_frames) == 0x73d, "NookClerk");
static_assert(offsetof(NookClerk, job_step) == 0x73e && offsetof(NookClerk, sound_played) == 0x73f, "NookClerk");
static_assert(offsetof(NookClerk, greeting) == 0x740 && sizeof(NookClerk) == 0x744, "the size the clerks are made with");
static_assert(sizeof(NookClerkStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's actor.h,
 * scene_object.h and scene_object_members.h). */
#define NOOK_CLERK_CODE 0x08         /* u32: the code it was made with (Tom Nook: 0xd019-0xd01c) */
#define NOOK_CLERK_PROFILE 0x0c      /* u16: its profile, NOOK_CLERK_TWIN_A/_TWIN_B/_NOOK */
#define NOOK_CLERK_POSITION 0x5c     /* Vec3: its position */
#define NOOK_CLERK_X 0x5c            /* fx32 */
#define NOOK_CLERK_Y 0x60            /* fx32 */
#define NOOK_CLERK_Z 0x64            /* fx32 */
#define NOOK_CLERK_ANGLE 0x8e        /* s16: where it faces */
#define NOOK_CLERK_WALK_ANGLE 0x94   /* s16: where it walks */
#define NOOK_CLERK_PERSON 0xea       /* u16: its person code */
#define NOOK_CLERK_MODEL 0xec        /* LayeredModel */
#define NOOK_CLERK_ANIMS 0x2a0       /* SceneStandardAnims */
#define NOOK_CLERK_FACE 0x2ac        /* SceneFace */
#define NOOK_CLERK_ANIM 0x334        /* SpeakerAnim */
#define NOOK_CLERK_MOVER 0x350       /* SceneMover */
#define NOOK_CLERK_PROBE 0x3a8       /* the probe */
#define NOOK_CLERK_VALUE_3AA 0x3aa   /* SceneValue3aa */
#define NOOK_CLERK_LOOK 0x3b0        /* SceneLook */
#define NOOK_CLERK_TALK_STATE 0x418  /* SceneTalkState */
#define NOOK_CLERK_EFFECTS 0x420     /* ActEffects */
#define NOOK_CLERK_COLLIDER 0x49c    /* CollisionContacts */
#define NOOK_CLERK_CARRIER 0x4cc     /* FieldOwnedBody */
#define NOOK_CLERK_FLAGS 0x4e8       /* u32: the scene object's flags (2: held) */
#define NOOK_CLERK_EMITTER 0x514     /* SoundEmitterObject */
#define NOOK_CLERK_FOOTSTEPS 0x558   /* Footsteps */
#define NOOK_CLERK_PARTICIPANT 0x560 /* u8: whose system the last event came from */
#define NOOK_CLERK_MOTION 0x564      /* SceneMotion */
#define NOOK_CLERK_ACTION 0x618      /* SceneAction */
#define NOOK_CLERK_HEAP 0x640        /* PoolLink */
#define NOOK_CLERK_LEAD_STEP 0x651   /* u8: the step of state 17 */

#define NOOK_CLERK_NO_ITEM 0xfff1
#define NOOK_CLERK_HELD 2

/* The field actor of this console's player, and whom an event is for when it is for it. */
#define NOOK_CLERK_PLAYER_ACTOR 4
#define NOOK_CLERK_THIS_PLAYER 4

/* The codes of the vtable slot 0x4c (main's event_kinds.h). */
#define NOOK_CLERK_EVENT_TALK 0
#define NOOK_CLERK_EVENT_KIND6 1
#define NOOK_CLERK_EVENT_STARTS 3
#define NOOK_CLERK_EVENT_REFUSED 4
#define NOOK_CLERK_EVENT_ENDED 8

/* The vtable slot of the talk scene that resets it. */
#define NOOK_CLERK_TALK_SLOT_RESET 0x08

/* The game variable (bank 0) that, when set, makes the clerks act as when linked. */
#define NOOK_CLERK_VARIABLE 0x4a
/* The player record's flag set while the player works for Tom Nook (the part-time job). */
#define NOOK_CLERK_JOB_FLAG 1

/* The motion kinds asked for (scene_motion_request.h): a walk, a faster one, a turn and the
 * act; the faster walk's rate. */
#define NOOK_CLERK_MOTION_WALK 1
#define NOOK_CLERK_MOTION_HURRY 2
#define NOOK_CLERK_MOTION_TURN 3
#define NOOK_CLERK_MOTION_ACT 10
#define NOOK_CLERK_HURRY_RATE 0x800
/* The word of the stand after the act. */
#define NOOK_CLERK_WORD_BLEND 0x18

/* The distances to the player (fx32) beyond which a clerk hurries and walks, and the angle off
 * the player it turns beyond in state 1. */
#define NOOK_CLERK_HURRY_DISTANCE 0x4000
#define NOOK_CLERK_WALK_DISTANCE 0x3000
#define NOOK_CLERK_TURN_ANGLE 0x2000

/* Tom Nook's dated events (day_events.h), and the frames before he acts on such a day: 100
 * and 20 times 0 to 4 more. */
#define NOOK_CLERK_EVENT_KIND 3
#define NOOK_CLERK_ACT_FRAMES 100
#define NOOK_CLERK_ACT_FRAMES_STEP 20
#define NOOK_CLERK_ACT_FRAMES_STEPS 5
/* The frames a clerk walks toward the player in state 16 before it talks anyway. */
#define NOOK_CLERK_APPROACH_FRAMES 0x32

/* The player's states (PlayerActorOps_InState) in which a clerk neither turns nor walks. */
#define NOOK_CLERK_PLAYER_STATE_A 0x8b
#define NOOK_CLERK_PLAYER_STATE_B 0x8c

/* How far ahead of the player the tile looked at is (fx32, 2.0). */
#define NOOK_CLERK_AHEAD 0x2000

/* The items on display by class (their codes), as data_ov050_022650e4's rows: wallpaper and
 * carpets, the items 0x1000-0x10ff, the paint for the house's roof (row 2 with this system the
 * host or alone, else row 3), the items of the item lists' variant group 4, anything else. */
#define NOOK_CLERK_WALLPAPER_FIRST 0x1100
#define NOOK_CLERK_WALLPAPER_LAST 0x1143
#define NOOK_CLERK_CARPET_FIRST 0x1144
#define NOOK_CLERK_CARPET_LAST 0x1187
#define NOOK_CLERK_ITEMS_10_FIRST 0x1000
#define NOOK_CLERK_ITEMS_10_LAST 0x10ff
#define NOOK_CLERK_PAINT_FIRST 0x1521
#define NOOK_CLERK_PAINT_LAST 0x1530
#define NOOK_CLERK_ROW_INTERIOR 0
#define NOOK_CLERK_ROW_ITEMS_10 1
#define NOOK_CLERK_ROW_PAINT 2
#define NOOK_CLERK_ROW_PAINT_GUEST 3
#define NOOK_CLERK_ROW_GROUP_4 4
#define NOOK_CLERK_ROW_OTHER 5
#define NOOK_CLERK_ROWS 6

/* The twins' body's radius and height and their collider's size; the mover's pace (mode 2). */
#define NOOK_CLERK_TWIN_RADIUS 0xccd
#define NOOK_CLERK_TWIN_HEIGHT 0x2000
#define NOOK_CLERK_TWIN_COLLIDER 0xb00
#define NOOK_CLERK_PACE_MODE 2
#define NOOK_CLERK_PACE_SPEED 0x400
#define NOOK_CLERK_PACE_SPEED_UP 0x133
#define NOOK_CLERK_PACE_SLOW_DOWN 0x199

/* The scenes a clerk's start looks at (SceneQuery_Previous): none, 0x1d and 0x1e. */
#define NOOK_CLERK_FROM_NONE 0
#define NOOK_CLERK_FROM_1D 0x1d
#define NOOK_CLERK_FROM_1E 0x1e

/* The flag of main's block (Block021d27ac_TestFlag) with which the talk of state 4 puts the
 * player out (exit 0). */
#define NOOK_CLERK_BLOCK_FLAG_EXIT 5

/* The model and texture of a twin, after Tom Nook's four looks (data_ov050_0226585c). */
#define NOOK_CLERK_LOOK_TWIN 4
#define NOOK_CLERK_LOOKS 5
#define NOOK_CLERK_FIRST_LOOK 0xd019

/* The vtables of the class and of the classes it derives from. */
extern const u8 data_ov050_02265a60[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* The model and texture file names: Tom Nook's four looks, then the twins'. */
extern const char *const data_ov050_0226585c[NOOK_CLERK_LOOKS];
extern const char *const data_ov050_02265848[NOOK_CLERK_LOOKS];
/* The functions of the states (filled at start-up by __sinit_ov050_0226520c). */
extern NookClerkStep data_ov050_02265f08[NOOK_CLERK_STATES];
/* The talk modes of an item on display by class (NOOK_CLERK_ROW_*): Tom Nook's, a twin's. */
extern const s32 data_ov050_022650e4[NOOK_CLERK_ROWS][2];
/* Three points of the store: the player at work goes toward the door past (13.0, 8.0); the
 * player is led to (16.0, 9.0); the player may talk to a clerk at 8.0 or more along z. */
extern const Vec3 data_ov050_02265090;
extern const Vec3 data_ov050_0226509c;
extern const Vec3 data_ov050_022650a8;
/* The word motion requests carry, the angle off the player a clerk turns beyond when linked. */
extern u16 data_020c80f8;
extern s16 data_020c80f0[];
/* The map of the scene. */
extern AcreMap *data_021c80bc;
/* The buttons, and the pen coming down this frame (both bytes set). */
extern PadState data_021fbe40;
extern u8 data_021f6c38;
extern u8 data_021f6c34;
#define NOOK_CLERK_PAD_A 0x0001
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;
/* The field's rooms when 1 (special_scene_object.h). */
extern u8 data_020e54a8;
/* The scene's music lives at 0x2a0 of the object data_021c526c points to. */
extern u8 *data_021c526c;
#define NOOK_CLERK_SCENE_MUSIC 0x2a0
/* The sine and cosine table (FX_SinCosTable_), the SDK's fixed-point product and a vector's
 * length. */
extern const fx16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 VEC_Mag(const Vec3 *v);

static u8 *nclerk_part(NookClerk *clerk, u32 offset)
{
    return clerk->base + offset;
}

static SceneMotion *nclerk_motion(NookClerk *clerk)
{
    return (SceneMotion *) (void *) nclerk_part(clerk, NOOK_CLERK_MOTION);
}

static SceneAction *nclerk_action(NookClerk *clerk)
{
    return (SceneAction *) (void *) nclerk_part(clerk, NOOK_CLERK_ACTION);
}

static SceneMover *nclerk_mover(NookClerk *clerk)
{
    return (SceneMover *) (void *) nclerk_part(clerk, NOOK_CLERK_MOVER);
}

static const Vec3 *nclerk_position(NookClerk *clerk)
{
    return (const Vec3 *) (const void *) nclerk_part(clerk, NOOK_CLERK_POSITION);
}

static s16 nclerk_angle(NookClerk *clerk)
{
    return *(const s16 *) (const void *) nclerk_part(clerk, NOOK_CLERK_ANGLE);
}

static u16 nclerk_profile(NookClerk *clerk)
{
    return *(const u16 *) (const void *) nclerk_part(clerk, NOOK_CLERK_PROFILE);
}

static int nclerk_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* The object owned by `owner` and held by `holder`, when it is ours. */
static void nclerk_set_slots(NookClerk *clerk, int owner, int holder)
{
    SceneShare_SetSlotsIfOurs(clerk->base, 1, owner, holder);
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int nclerk_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, NOOK_CLERK_VARIABLE) != 0;
}

/* Whether the current player works for Tom Nook (the player record's flag 1); the record's
 * villager part is asked for first, and not used. */
static int nclerk_at_work(void)
{
    u8 *record = PlayerRecords_Current();
    PlayerRecord_VillagerPart(record);
    return PlayerRecord_TestFlag(record, NOOK_CLERK_JOB_FLAG);
}

/* The talk scene reset through its vtable slot 0x08, the talk's partner this console's
 * player's field actor. */
static void nclerk_reset_talk(NookClerk *clerk)
{
    u32 vtable = *(const u32 *) (const void *) &clerk->talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + NOOK_CLERK_TALK_SLOT_RESET);
    ((void (*)(NookClerkTalk *))(uintptr_t) code)(&clerk->talk);
    SceneBase_SetMotionArg(&clerk->talk.base, SceneObject_ActorObject(clerk->base, NOOK_CLERK_PLAYER_ACTOR));
}

/* A motion of `kind` asked for (priority 1) at `rate` and `angle`, with the plain word. */
static void nclerk_request(NookClerk *clerk, int kind, s16 rate, s16 angle)
{
    SceneMotion_Request(nclerk_motion(clerk), kind, 1, 0, 0, rate, angle, 0, 0, data_020c80f8, 0);
}

/* Whether the motion is of `kind`. */
static int nclerk_motion_is(NookClerk *clerk, int kind)
{
    return SceneMotion_Kind(nclerk_motion(clerk)) == kind;
}

static int nclerk_yaw_to_player(NookClerk *clerk)
{
    return (int) (uintptr_t) SceneObject_YawToActor(clerk->base, NOOK_CLERK_PLAYER_ACTOR);
}

static void nclerk_face_player(NookClerk *clerk)
{
    SceneMover_SetAngle(nclerk_mover(clerk), nclerk_yaw_to_player(clerk));
}

/* The walk toward the player at `distance` beyond `hurry`: the faster walk (from the walk);
 * within it, the walk again (from the faster one); then the mover starts toward `step`. */
static void nclerk_walk_toward(NookClerk *clerk, int distance, int hurry, const Vec3 *step)
{
    if (distance > hurry) {
        if (nclerk_motion_is(clerk, NOOK_CLERK_MOTION_WALK)) {
            nclerk_request(clerk, NOOK_CLERK_MOTION_HURRY, NOOK_CLERK_HURRY_RATE, 0);
        }
    } else if (nclerk_motion_is(clerk, NOOK_CLERK_MOTION_HURRY)) {
        nclerk_request(clerk, NOOK_CLERK_MOTION_WALK, 0, 0);
    }
    SceneMover_SetStart(nclerk_mover(clerk), step);
}

/* Whether the item code at `item` is empty (0xfff1, or a variant of the empty item). */
static int nclerk_is_empty(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = NOOK_CLERK_NO_ITEM;
        return ItemCode_VariantItem(item) == ItemCode_VariantItem(&none);
    }
    return *item == NOOK_CLERK_NO_ITEM;
}

static int nclerk_in(u16 item, u16 first, u16 last)
{
    return item >= first && item <= last;
}

/* Main's block's part 0x18, a date. */
static DateTime *nclerk_part18(void)
{
    return (DateTime *) Block021d27ac_Part18(Block021d27ac_Get());
}

/* Tom Nook's dated event of kind 3 today. */
static int nclerk_todays_event(NookClerk *clerk)
{
    u8 event;
    return TalkChecks_TodaysEventOfKind((int) (uintptr_t) clerk, &event, NOOK_CLERK_EVENT_KIND);
}

/* The checks most states make first, in order: the player at work going for the door, the
 * player's start point taken, the date of main's block part 0x18 passed, an item on display
 * asked about. Whether one of them took over. */
static int nclerk_noticed(NookClerk *clerk)
{
    return NookClerk_CheckJobDoor(clerk) || NookClerk_CheckSpotTaken(clerk) || NookClerk_CheckDatePassed(clerk) ||
           NookClerk_OfferShown(clerk);
}

/* ---- The object's slots and questions */

/* func_ov050_02260420 (vtable slot 0x40): the talk scene's and the special character's
 * destructors; the object. */
void *NookClerk_Destruct(NookClerk *clerk)
{
    *(const u8 **) (void *) clerk = data_ov050_02265a60;
    NookClerkTalk_Destruct(&clerk->talk);
    SpecialSceneObject_DestructBody(clerk);
    return clerk;
}
CLEAN_AS(func_ov050_02260420, NookClerk_Destruct)

/* func_ov050_02260448 (vtable slot 0x44): the same, then the object freed. */
void *NookClerk_DestructDelete(NookClerk *clerk)
{
    *(const u8 **) (void *) clerk = data_ov050_02265a60;
    NookClerkTalk_Destruct(&clerk->talk);
    SpecialSceneObject_DestructBody(clerk);
    Heap_FreeAux(clerk);
    return clerk;
}
CLEAN_AS(func_ov050_02260448, NookClerk_DestructDelete)

/* func_ov050_02260474: the distance beyond which a clerk hurries, 4.0.
 * QUIRK: for a twin it first asks whether it is the nearer of the two, and does not use it. */
int NookClerk_HurryDistance(NookClerk *clerk)
{
    if (NookClerk_IsTwin(clerk)) {
        NookClerk_IsNearerThanTwin(clerk);
    }
    return NOOK_CLERK_HURRY_DISTANCE;
}
CLEAN_AS(func_ov050_02260474, NookClerk_HurryDistance)

/* func_ov050_02260498: the distance beyond which a clerk walks, 3.0, with the same unused
 * question as NookClerk_HurryDistance. */
int NookClerk_WalkDistance(NookClerk *clerk)
{
    if (NookClerk_IsTwin(clerk)) {
        NookClerk_IsNearerThanTwin(clerk);
    }
    return NOOK_CLERK_WALK_DISTANCE;
}
CLEAN_AS(func_ov050_02260498, NookClerk_WalkDistance)

/* func_ov050_022604bc: whether the clerk is one of the twins. */
int NookClerk_IsTwin(NookClerk *clerk)
{
    return NookClerk_IsTwinA(clerk) || NookClerk_IsTwinB(clerk);
}
CLEAN_AS(func_ov050_022604bc, NookClerk_IsTwin)

/* func_ov050_022604e0: whether the clerk is twin 0x74. */
int NookClerk_IsTwinA(NookClerk *clerk)
{
    return nclerk_profile(clerk) == NOOK_CLERK_TWIN_A;
}
CLEAN_AS(func_ov050_022604e0, NookClerk_IsTwinA)

/* func_ov050_022604f8: whether the clerk is twin 0x75. */
int NookClerk_IsTwinB(NookClerk *clerk)
{
    return nclerk_profile(clerk) == NOOK_CLERK_TWIN_B;
}
CLEAN_AS(func_ov050_022604f8, NookClerk_IsTwinB)

/* func_ov050_02260510: whether the clerk is Tom Nook. */
int NookClerk_IsNook(NookClerk *clerk)
{
    return nclerk_profile(clerk) == NOOK_CLERK_NOOK;
}
CLEAN_AS(func_ov050_02260510, NookClerk_IsNook)

/* func_ov050_02260528: not during an event, unlinked (and without the game variable 0x4a) and
 * with the player not at work, once the date of main's block part 0x18 has passed: Tom Nook's
 * talk takes mode 6, twin 0x74's mode 0x1d (twin 0x75's keeps its mode), and an event of kind
 * 6 is asked for. Whether it was. */
int NookClerk_CheckDatePassed(NookClerk *clerk)
{
    if (EventQueue_HasCurrent() != 0) {
        return 0;
    }
    if (nclerk_linked_or_variable(data_020ccf94)) {
        return 0;
    }
    if (PlayerRecord_TestFlag(PlayerRecords_Current(), NOOK_CLERK_JOB_FLAG) != 0) {
        return 0;
    }
    if (Block021d27acPart18_HasPassed(nclerk_part18()) == 0) {
        return 0;
    }
    if (NookClerk_IsNook(clerk)) {
        NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_NOOK_DATE);
    } else if (NookClerk_IsTwinA(clerk)) {
        NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_TWIN_A_DATE);
    }
    EventQueue_RequestKind6(clerk, 0);
    return 1;
}
CLEAN_AS(func_ov050_02260528, NookClerk_CheckDatePassed)

/* func_ov050_022605c0: whether the clerk talks because the player's start point is claimed on
 * the collision map. Unless the talk is about that already (modes 1 and 0x12): a twin that is
 * not the nearer of the two only faces the player when the point is claimed, and answers no;
 * linked (or with the game variable 0x4a), or with the player at work, the answer is no. When
 * the point is claimed the talk takes mode 0x12 (a twin) or 1 (Tom Nook), an event of kind 6
 * is asked for and the clerk turns to ask (state 18). */
int NookClerk_CheckSpotTaken(NookClerk *clerk)
{
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);

    if (NookClerkTalk_Mode(&clerk->talk) != NOOK_CLERK_MODE_SPOT_TAKEN &&
        NookClerkTalk_Mode(&clerk->talk) != NOOK_CLERK_MODE_TWIN_SPOT) {
        if (NookClerk_IsTwin(clerk) && NookClerk_IsNearerThanTwin(clerk) == 0) {
            if (CollisionMap_IsClaimedAtPoint(&start)) {
                nclerk_face_player(clerk);
            }
            return 0;
        }
        if (nclerk_linked_or_variable(data_020ccf94)) {
            return 0;
        }
        if (nclerk_at_work()) {
            return 0;
        }
    }
    if (CollisionMap_IsClaimedAtPoint(&start)) {
        if (NookClerk_IsTwin(clerk)) {
            NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_TWIN_SPOT);
        } else {
            NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_SPOT_TAKEN);
        }
        EventQueue_RequestKind6(clerk, 0);
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_TURN_ASK);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov050_022605c0, NookClerk_CheckSpotTaken)

/* func_ov050_022606b4: with the player at work and its start point past (13.0, 8.0) of the
 * store toward the door (x beyond 13.0, z short of 8.0), the talk takes mode 0x1e and an event
 * of kind 6 is asked for. Whether it was. */
int NookClerk_CheckJobDoor(NookClerk *clerk)
{
    if (nclerk_at_work() == 0) {
        return 0;
    }
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);
    if (start.z >= data_ov050_02265090.z || start.x <= data_ov050_02265090.x) {
        return 0;
    }
    NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_JOB_DOOR);
    EventQueue_RequestKind6(clerk, 0);
    return 1;
}
CLEAN_AS(func_ov050_022606b4, NookClerk_CheckJobDoor)

/* func_ov050_02260718: when the player faces an item on display (NookClerk_FindShown), an
 * event of kind 6 is asked for. Whether it was. */
int NookClerk_OfferShown(NookClerk *clerk)
{
    if (NookClerk_FindShown(clerk)) {
        EventQueue_RequestKind6(clerk, 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov050_02260718, NookClerk_OfferShown)

/* func_ov050_02260738: whether the player asks the clerk about an item on display. Not without
 * the player's actor, during an event, while the clerk's action runs, or without A pressed or
 * the pen coming down this frame; linked (or with the game variable 0x4a) not twin 0x74;
 * unlinked not a twin that is not the nearer of the two. The tile asked about is the one 2.0
 * ahead of the player (where it faces); with the pen, the room object standing there must be
 * the one touched, or, with none, the ground touched must be on that tile. The item on display
 * on that tile (not an empty one) gives the talk mode of its class (data_ov050_022650e4, by
 * the clerk: Tom Nook or a twin); the item and the tile are kept and nothing is bought yet. The
 * item is 0xfff1 from the first checks passed on, also when nothing is found. */
int NookClerk_FindShown(NookClerk *clerk)
{
    u8 *player = (u8 *) SessionPlayers_ActorOf(NOOK_CLERK_PLAYER_ACTOR);
    int touched = data_021f6c38 != 0 && data_021f6c34 != 0;

    if (player == NULL || EventQueue_HasCurrent() != 0 || SceneAction_IsBusy(nclerk_action(clerk)) != 0 ||
        ((data_021fbe40.pressed & NOOK_CLERK_PAD_A) == 0 && !touched)) {
        return 0;
    }
    if (nclerk_linked_or_variable(data_020ccf94)) {
        if (NookClerk_IsTwinA(clerk)) {
            return 0;
        }
    } else if (NookClerk_IsTwin(clerk) && NookClerk_IsNearerThanTwin(clerk) == 0) {
        return 0;
    }

    clerk->item = NOOK_CLERK_NO_ITEM;
    Vec3 ahead = *(const Vec3 *) (const void *) (player + NOOK_CLERK_POSITION);
    u16 facing = *(const u16 *) (const void *) (player + NOOK_CLERK_ANGLE);
    int x = 0;
    int z = 0;
    int i = (facing >> 4) * 2;
    ahead.x = ahead.x + FX_MulFunc(NOOK_CLERK_AHEAD, FX_SinCosTable_[i]);
    ahead.z = ahead.z + FX_MulFunc(NOOK_CLERK_AHEAD, FX_SinCosTable_[i + 1]);
    Position_Tile(&x, &z, (const Position *) (const void *) &ahead);

    if (touched) {
        RoomObject *object = RoomObjects_GridObjectAt(RoomObjects_Grid(), x, z, 0);
        if (object != NULL) {
            TouchPick *pick = (TouchPick *) (uintptr_t) (u32) SceneQuery_FieldObject();
            if ((int) (uintptr_t) object != TouchPick_PickedObject(pick, NULL, NULL)) {
                return 0;
            }
        } else {
            Vec3 ground;
            int ground_x = 0;
            int ground_z = 0;
            TouchPick_GetGround((TouchPick *) (uintptr_t) (u32) SceneQuery_FieldObject(), &ground);
            Position_Tile(&ground_x, &ground_z, (const Position *) (const void *) &ground);
            if (ground_x != x || ground_z != z) {
                return 0;
            }
        }
    }

    u16 item = *ShopDisplay_ItemAt(x, z);
    if (nclerk_is_empty(&item)) {
        return 0;
    }
    int twin = NookClerk_IsTwin(clerk) ? 1 : 0;
    int row = NOOK_CLERK_ROW_OTHER;
    if (nclerk_in(item, NOOK_CLERK_WALLPAPER_FIRST, NOOK_CLERK_WALLPAPER_LAST) ||
        nclerk_in(item, NOOK_CLERK_CARPET_FIRST, NOOK_CLERK_CARPET_LAST)) {
        row = NOOK_CLERK_ROW_INTERIOR;
    } else if (nclerk_in(item, NOOK_CLERK_ITEMS_10_FIRST, NOOK_CLERK_ITEMS_10_LAST)) {
        row = NOOK_CLERK_ROW_ITEMS_10;
    } else if (nclerk_in(item, NOOK_CLERK_PAINT_FIRST, NOOK_CLERK_PAINT_LAST)) {
        PlayerRecords_Current();
        row = TalkChecks_IsHostOrAlone() ? NOOK_CLERK_ROW_PAINT : NOOK_CLERK_ROW_PAINT_GUEST;
    } else if (ItemLists_IsVariantGroup4(&item)) {
        row = NOOK_CLERK_ROW_GROUP_4;
    }
    NookClerkTalk_SetMode(&clerk->talk, (unsigned long) data_ov050_022650e4[row][twin]);
    clerk->item = item;
    clerk->tile_x = x;
    clerk->tile_z = z;
    clerk->bought = 0;
    return 1;
}
CLEAN_AS(func_ov050_02260738, NookClerk_FindShown)

/* func_ov050_022609d8: the other twin's profile (0x74 for any clerk but twin 0x74). */
int NookClerk_OtherTwin(NookClerk *clerk)
{
    return NookClerk_IsTwinA(clerk) ? NOOK_CLERK_TWIN_B : NOOK_CLERK_TWIN_A;
}
CLEAN_AS(func_ov050_022609d8, NookClerk_OtherTwin)

/* func_ov050_022609f0: whether a twin is nearer to the player's start point than the other
 * twin (a scene object of that profile); no for Tom Nook or without the other twin. */
int NookClerk_IsNearerThanTwin(NookClerk *clerk)
{
    NookClerk *self = clerk;
    if (NookClerk_IsTwin(clerk) == 0) {
        return 0;
    }
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);
    u8 *other = (u8 *) Actor_FindNextOfProfile(NookClerk_OtherTwin(self), NULL);
    if (other == NULL) {
        return 0;
    }
    Vec3 there = *(const Vec3 *) (const void *) (other + NOOK_CLERK_POSITION);
    Vec3 to_other;
    Vec_Subtract(&to_other, &start, &there);
    fx32 other_distance = VEC_Mag(&to_other);
    Vec3 to_self;
    Vec_Subtract(&to_self, &start, nclerk_position(self));
    fx32 own_distance = VEC_Mag(&to_self);
    return own_distance < other_distance;
}
CLEAN_AS(func_ov050_022609f0, NookClerk_IsNearerThanTwin)

/* func_ov050_02260a68 (vtable slot 0x4c, told of an event about the clerk by `participant`'s
 * system, 4 for this one):
 * - 3, an event starts: the participant kept; another system's: owned by this system and held
 *   by it, paused; this one's (with the object ours): owned and held by this system, paused;
 * - 1, the event of kind 6 the clerk asked for: the participant kept; another system's (not
 *   this one's slot): owned and held by it, state 9; this one's (with the object ours): owned
 *   and held by this system, the talk reset with this console's player as the partner; in talk
 *   mode 0 or 0x11 it talks (state 4); in modes 1, 0x12, 6 and 0x1d it talks and the player
 *   leaves (state 5); else linked (or with the game variable 0x4a) the talk is reset again and
 *   it talks, unlinked it first walks toward the player (state 16);
 * - 0, the player talks to the clerk: as 1 for another system; this one's: owned and held by
 *   this system, the talk reset with the partner, talk mode 5 (Tom Nook) or 0x13, and it talks;
 * - 8, the event ended, for this console's player: when this system holds the scene, owned by
 *   this one and held by none; unless the talk was in modes 1, 0x12, 6 or 0x1d, linked (or with
 *   the game variable 0x4a) it stands as when linked (state 13), else stands (state 1); twin
 *   0x74 no longer greets. Else owned by none and held by this system, it awaits the session;
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), owned by this system and held by none, state 13. */
void NookClerk_OnEvent(NookClerk *clerk, int code, int participant)
{
    switch (code) {
        case NOOK_CLERK_EVENT_STARTS:
            *nclerk_part(clerk, NOOK_CLERK_PARTICIPANT) = (u8) participant;
            if (participant != NOOK_CLERK_THIS_PLAYER) {
                nclerk_set_slots(clerk, nclerk_local_slot(), participant);
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_PAUSED);
            } else if (SceneShare_IsOurs(clerk->base)) {
                int slot = nclerk_local_slot();
                nclerk_set_slots(clerk, slot, slot);
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_PAUSED);
            }
            break;
        case NOOK_CLERK_EVENT_KIND6:
            *nclerk_part(clerk, NOOK_CLERK_PARTICIPANT) = (u8) participant;
            if (participant != NOOK_CLERK_THIS_PLAYER && participant != nclerk_local_slot()) {
                nclerk_set_slots(clerk, participant, participant);
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_OTHER);
            } else if (SceneShare_IsOurs(clerk->base)) {
                NetSession *session = data_020ccf94;
                int slot = session->local_slot;
                nclerk_set_slots(clerk, slot, slot);
                nclerk_reset_talk(clerk);
                unsigned long mode = NookClerkTalk_Mode(&clerk->talk);
                if (mode == NOOK_CLERK_MODE_NOOK_GREET || NookClerkTalk_Mode(&clerk->talk) == NOOK_CLERK_MODE_TWIN_GREET) {
                    NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALK);
                } else if (NookClerkTalk_Mode(&clerk->talk) == NOOK_CLERK_MODE_SPOT_TAKEN ||
                           NookClerkTalk_Mode(&clerk->talk) == NOOK_CLERK_MODE_TWIN_SPOT ||
                           NookClerkTalk_Mode(&clerk->talk) == NOOK_CLERK_MODE_NOOK_DATE ||
                           NookClerkTalk_Mode(&clerk->talk) == NOOK_CLERK_MODE_TWIN_A_DATE) {
                    NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALK_LEAVE);
                } else if (nclerk_linked_or_variable(session)) {
                    nclerk_reset_talk(clerk);
                    NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALK);
                } else {
                    NookClerk_SetState(clerk, NOOK_CLERK_STATE_APPROACH);
                }
            }
            break;
        case NOOK_CLERK_EVENT_TALK:
            *nclerk_part(clerk, NOOK_CLERK_PARTICIPANT) = (u8) participant;
            if (participant != NOOK_CLERK_THIS_PLAYER && participant != nclerk_local_slot()) {
                nclerk_set_slots(clerk, participant, participant);
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_OTHER);
            } else if (SceneShare_IsOurs(clerk->base)) {
                int slot = nclerk_local_slot();
                nclerk_set_slots(clerk, slot, slot);
                nclerk_reset_talk(clerk);
                if (NookClerk_IsNook(clerk)) {
                    NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_NOOK_TALKED);
                } else {
                    NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_TWIN_TALKED);
                }
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALK);
            }
            break;
        case NOOK_CLERK_EVENT_ENDED:
            if (participant != NOOK_CLERK_THIS_PLAYER) {
                break;
            }
            if (LinkGlobal_HoldsScene()) {
                NetSession *session = data_020ccf94;
                nclerk_set_slots(clerk, session->local_slot, SCENE_SHARE_NO_SLOT);
                if (NookClerkTalk_Mode(&clerk->talk) != NOOK_CLERK_MODE_SPOT_TAKEN &&
                    NookClerkTalk_Mode(&clerk->talk) != NOOK_CLERK_MODE_TWIN_SPOT &&
                    NookClerkTalk_Mode(&clerk->talk) != NOOK_CLERK_MODE_NOOK_DATE &&
                    NookClerkTalk_Mode(&clerk->talk) != NOOK_CLERK_MODE_TWIN_A_DATE) {
                    if (nclerk_linked_or_variable(session)) {
                        NookClerk_SetState(clerk, NOOK_CLERK_STATE_LINKED_STAND);
                    } else {
                        NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
                    }
                }
                clerk->greeting = 0;
            } else {
                nclerk_set_slots(clerk, SCENE_SHARE_NO_SLOT, nclerk_local_slot());
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_AWAIT);
            }
            break;
        case NOOK_CLERK_EVENT_REFUSED: {
            if (SceneShare_IsHeld(clerk->base) == 0 || SceneShare_IsOurs(clerk->base) == 0) {
                break;
            }
            int owner = SCENE_SHARE_NO_SLOT;
            int holder = SCENE_SHARE_NO_SLOT;
            if (SceneShare_ReadSlots(clerk->base, &owner, &holder) == 0) {
                break;
            }
            if (participant == NOOK_CLERK_THIS_PLAYER || participant == holder) {
                nclerk_set_slots(clerk, nclerk_local_slot(), SCENE_SHARE_NO_SLOT);
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_LINKED_STAND);
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov050_02260a68, NookClerk_OnEvent)

/* func_ov050_02260d60 (vtable slot 0x58, the act of an event of kind 6): whether the clerk
 * agrees: its action idle and no system holding it. */
int NookClerk_MayActKind6(NookClerk *clerk)
{
    if (SceneAction_IsBusy(nclerk_action(clerk)) != 0) {
        return 0;
    }
    return SceneShare_IsHeld(clerk->base) == 0;
}
CLEAN_AS(func_ov050_02260d60, NookClerk_MayActKind6)

/* func_ov050_02260d8c (vtable slot 0x48): whether the player may talk to the clerk: it stands
 * at 8.0 or more along z (the counter's side), its action is idle, no system holds it, and no
 * item on display is asked about (which asks for an event of its own, NookClerk_OfferShown). */
int NookClerk_MayAct(NookClerk *clerk)
{
    if (*(const s32 *) (const void *) nclerk_part(clerk, NOOK_CLERK_Z) < data_ov050_022650a8.z) {
        return 0;
    }
    if (SceneAction_IsBusy(nclerk_action(clerk)) != 0 || SceneShare_IsHeld(clerk->base) != 0 ||
        NookClerk_OfferShown(clerk) != 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov050_02260d8c, NookClerk_MayAct)

/* func_ov050_02262de8 (vtable slot 0x80): the action's start sound noted as played. */
void NookClerk_SoundPlayed(NookClerk *clerk)
{
    clerk->sound_played = 1;
}
CLEAN_AS(func_ov050_02262de8, NookClerk_SoundPlayed)

/* func_ov050_02262df4 (vtable slot 0x7c): whether an action's start has a sound: never for twin
 * 0x75; else always, except in the rooms' field (data_020e54a8 1) once it has played. */
int NookClerk_HasActionSound(NookClerk *clerk)
{
    if (NookClerk_IsTwinB(clerk)) {
        return 0;
    }
    if (data_020e54a8 != 1 || clerk->sound_played == 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov050_02262df4, NookClerk_HasActionSound)

/* ---- The states */

/* func_ov050_02263be4 (state 16's update): the clerk walks toward the player along the
 * counter's path (the faster walk beyond 4.0); while the player is farther than 3.0 and the
 * clerk is not at the path's step, it goes on for up to 50 frames; then its talk is reset with
 * this console's player as the partner and it talks. 1. */
int NookClerk_UpdateApproach(NookClerk *clerk)
{
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);
    Vec3 step;
    ScenePathStep_Choose(&step, clerk->base, &start);
    int distance = SceneObject_DistanceToActor(clerk->base, NOOK_CLERK_PLAYER_ACTOR);
    AcreTile_PathDirectionsAt(data_021c80bc, nclerk_position(clerk));
    nclerk_walk_toward(clerk, distance, NOOK_CLERK_HURRY_DISTANCE, &step);
    if (distance > NOOK_CLERK_WALK_DISTANCE && Vec_Equal(&step, nclerk_position(clerk)) == 0 &&
        Countdown_Tick8(&clerk->approach_frames) != 0) {
        return 1;
    }
    nclerk_reset_talk(clerk);
    NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALK);
    return 1;
}
CLEAN_AS(func_ov050_02263be4, NookClerk_UpdateApproach)

/* func_ov050_02263cfc (state 16's entry): 50 frames to walk, and a walk asked for. 1. */
int NookClerk_EnterApproach(NookClerk *clerk)
{
    clerk->approach_frames = NOOK_CLERK_APPROACH_FRAMES;
    nclerk_request(clerk, NOOK_CLERK_MOTION_WALK, 0, 0);
    return 1;
}
CLEAN_AS(func_ov050_02263cfc, NookClerk_EnterApproach)

/* func_ov050_02263d3c (state 15's update): nothing. 1. */
int NookClerk_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov050_02263d3c, NookClerk_UpdatePaused)

/* func_ov050_02263d40 (state 15's entry): nothing. 1. */
int NookClerk_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov050_02263d40, NookClerk_EnterPaused)

/* func_ov050_02263d44 (state 14's update): once the turn is done, state 13; while it is not,
 * an item on display asked about is looked for. 1. */
int NookClerk_UpdateLinkedTurn(NookClerk *clerk)
{
    if (nclerk_motion_is(clerk, NOOK_CLERK_MOTION_TURN)) {
        if (SceneMotion_IsDone(nclerk_motion(clerk)) != 0) {
            NookClerk_SetState(clerk, NOOK_CLERK_STATE_LINKED_STAND);
        } else {
            NookClerk_OfferShown(clerk);
        }
    }
    return 1;
}
CLEAN_AS(func_ov050_02263d44, NookClerk_UpdateLinkedTurn)

/* func_ov050_02263d7c (state 14's entry): a turn (priority 1) to the player. 1. */
int NookClerk_EnterLinkedTurn(NookClerk *clerk)
{
    int yaw = nclerk_yaw_to_player(clerk);
    nclerk_request(clerk, NOOK_CLERK_MOTION_TURN, 0, (s16) yaw);
    return 1;
}
CLEAN_AS(func_ov050_02263d7c, NookClerk_EnterLinkedTurn)

/* func_ov050_02263dbc (state 13's update): when the clerk faces data_020c80f0[0] or more off the
 * player it turns (state 14), else it looks for an item on display asked about. 1. */
int NookClerk_UpdateLinkedStand(NookClerk *clerk)
{
    int yaw = nclerk_yaw_to_player(clerk);
    int off = Math_AbsDiff16(nclerk_angle(clerk), yaw);
    if (off >= data_020c80f0[0]) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_LINKED_TURN);
    } else {
        NookClerk_OfferShown(clerk);
    }
    return 1;
}
CLEAN_AS(func_ov050_02263dbc, NookClerk_UpdateLinkedStand)

/* func_ov050_02263df8 (state 13's entry): the clerk stands (priority 1, its stand's word). 1. */
int NookClerk_EnterLinkedStand(NookClerk *clerk)
{
    SceneMotion_RequestStand(nclerk_motion(clerk), 1, clerk->stand_word);
    return 1;
}
CLEAN_AS(func_ov050_02263df8, NookClerk_EnterLinkedStand)

/* func_ov050_02263e1c (state 9's update, another system's player talked to the clerk): once the
 * object is ours, the shared slots read show no owner and this system holds the scene, it is
 * owned by this system, held by none, and stands (state 13). 1. */
int NookClerk_UpdateOther(NookClerk *clerk)
{
    if (SceneShare_IsOurs(clerk->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(clerk->base, &owner, &holder) && owner == SCENE_SHARE_NO_SLOT && LinkGlobal_HoldsScene()) {
            nclerk_set_slots(clerk, nclerk_local_slot(), SCENE_SHARE_NO_SLOT);
            NookClerk_SetState(clerk, NOOK_CLERK_STATE_LINKED_STAND);
        }
    }
    return 1;
}
CLEAN_AS(func_ov050_02263e1c, NookClerk_UpdateOther)

/* func_ov050_02263e74 (state 9's entry): nothing. 1. */
int NookClerk_EnterOther(void)
{
    return 1;
}
CLEAN_AS(func_ov050_02263e74, NookClerk_EnterOther)

/* func_ov050_02263e78 (state 8's update, awaiting the session): with the object ours, when the
 * shared slots read have this system as both owner and holder, they are set so, the talk is
 * reset with this console's player as the partner, takes talk mode 5 (Tom Nook) or 0x13 when no
 * item on display is talked about, and the clerk talks; else, when this system holds the scene
 * and no system holds the clerk, it is owned by this system and stands (state 13). Without the
 * object ours, an item on display asked about is looked for. 1. */
int NookClerk_UpdateAwait(NookClerk *clerk)
{
    if (!SceneShare_IsOurs(clerk->base)) {
        NookClerk_OfferShown(clerk);
        return 1;
    }
    int owner = SCENE_SHARE_NO_SLOT;
    int holder = SCENE_SHARE_NO_SLOT;
    if (SceneShare_ReadSlots(clerk->base, &owner, &holder) && owner == nclerk_local_slot() && owner == holder) {
        int slot = nclerk_local_slot();
        nclerk_set_slots(clerk, slot, slot);
        nclerk_reset_talk(clerk);
        if (nclerk_is_empty(&clerk->item)) {
            if (NookClerk_IsNook(clerk)) {
                NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_NOOK_TALKED);
            } else {
                NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_TWIN_TALKED);
            }
        }
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALK);
    } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
        nclerk_set_slots(clerk, nclerk_local_slot(), SCENE_SHARE_NO_SLOT);
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_LINKED_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov050_02263e78, NookClerk_UpdateAwait)

/* func_ov050_02263f88 (state 8's entry): nothing. 1. */
int NookClerk_EnterAwait(void)
{
    return 1;
}
CLEAN_AS(func_ov050_02263f88, NookClerk_EnterAwait)

/* func_ov050_02263f8c (state 18's update): once the turn is done the clerk stands (its stand's
 * word); it faces the player, and an event of kind 6 is asked for. 1. */
int NookClerk_UpdateTurnAsk(NookClerk *clerk)
{
    if (nclerk_motion_is(clerk, NOOK_CLERK_MOTION_TURN) && SceneMotion_IsDone(nclerk_motion(clerk)) != 0) {
        SceneMotion_RequestStand(nclerk_motion(clerk), 1, clerk->stand_word);
    }
    nclerk_face_player(clerk);
    EventQueue_RequestKind6(clerk, 0);
    return 1;
}
CLEAN_AS(func_ov050_02263f8c, NookClerk_UpdateTurnAsk)

/* func_ov050_02263fe4 (state 18's entry): a turn (priority 1). 1. */
int NookClerk_EnterTurnAsk(NookClerk *clerk)
{
    nclerk_request(clerk, NOOK_CLERK_MOTION_TURN, 0, 0);
    return 1;
}
CLEAN_AS(func_ov050_02263fe4, NookClerk_EnterTurnAsk)

/* func_ov050_02264018 (state 17's update), by its step: 0, once the clerk's action is idle the
 * camera's mode is reset; 1, the player is walked to (16.0, 9.0) of the store; 2, once the
 * player is no longer busy the event ends and the clerk turns (state 2). The tiles of that
 * point and of the player's start point are computed first and not used. 1. */
int NookClerk_UpdateLead(NookClerk *clerk)
{
    PlayerRecords_Current();
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);
    int tiles[4] = {0, 0, 0, 0};
    Vec3 target = data_ov050_0226509c;
    Position_Tile(&tiles[2], &tiles[3], (const Position *) (const void *) &target);
    Position_Tile(&tiles[0], &tiles[1], (const Position *) (const void *) &start);

    u8 *step = nclerk_part(clerk, NOOK_CLERK_LEAD_STEP);
    switch (*step) {
        case 0:
            if (SceneAction_IsBusy(nclerk_action(clerk)) == 0) {
                CameraControl_ResetMode();
                *step = 1;
            }
            break;
        case 1: {
            Vec3 point = target;
            PlayerActorOps_MoveTo(&point, 0x266, NOOK_CLERK_PLAYER_ACTOR);
            *step = 2;
            break;
        }
        case 2:
            if (PlayerActorOps_IsBusy(NOOK_CLERK_PLAYER_ACTOR) == 0) {
                EventQueue_FinishObjectEvent(clerk);
                NookClerk_SetState(clerk, NOOK_CLERK_STATE_TURN);
            }
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov050_02264018, NookClerk_UpdateLead)

/* func_ov050_022640d4 (state 17's entry): its step 0. 1. */
int NookClerk_EnterLead(NookClerk *clerk)
{
    *nclerk_part(clerk, NOOK_CLERK_LEAD_STEP) = 0;
    return 1;
}
CLEAN_AS(func_ov050_022640d4, NookClerk_EnterLead)

/* func_ov050_022640e4 (state 7's update): unless something else is noticed (nclerk_noticed),
 * once the act is done the next stand blends in (word 0x18) and the clerk stands. 1. */
int NookClerk_UpdateAct(NookClerk *clerk)
{
    if (nclerk_noticed(clerk)) {
        return 1;
    }
    if (nclerk_motion_is(clerk, NOOK_CLERK_MOTION_ACT) && SceneMotion_IsDone(nclerk_motion(clerk)) != 0) {
        clerk->stand_word = NOOK_CLERK_WORD_BLEND;
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov050_022640e4, NookClerk_UpdateAct)

/* func_ov050_02264154 (state 7's entry): the act (motion kind 10, priority 1). 1. */
int NookClerk_EnterAct(NookClerk *clerk)
{
    nclerk_request(clerk, NOOK_CLERK_MOTION_ACT, 0, 0);
    return 1;
}
CLEAN_AS(func_ov050_02264154, NookClerk_EnterAct)

/* func_ov050_02264188 (state 11's update): the clerk faces the player. 1. */
int NookClerk_UpdateFace(NookClerk *clerk)
{
    nclerk_face_player(clerk);
    return 1;
}
CLEAN_AS(func_ov050_02264188, NookClerk_UpdateFace)

/* func_ov050_022641a8 (state 11's entry): a turn (priority 1). 1. */
int NookClerk_EnterFace(NookClerk *clerk)
{
    nclerk_request(clerk, NOOK_CLERK_MOTION_TURN, 0, 0);
    return 1;
}
CLEAN_AS(func_ov050_022641a8, NookClerk_EnterFace)

/* func_ov050_022641dc (state 12's update): nothing. 1. */
int NookClerk_UpdateStill(void)
{
    return 1;
}
CLEAN_AS(func_ov050_022641dc, NookClerk_UpdateStill)

/* func_ov050_022641e0 (state 12's entry): the stand's word is the plain one, and the clerk
 * stands with it (priority 1). 1. */
int NookClerk_EnterStill(NookClerk *clerk)
{
    clerk->stand_word = data_020c80f8;
    SceneMotion_RequestStand(nclerk_motion(clerk), 1, clerk->stand_word);
    return 1;
}
CLEAN_AS(func_ov050_022641e0, NookClerk_EnterStill)

/* func_ov050_02264210 (state 10's update): once the other twin is out of state 0, and stands
 * (state 1) or no longer greets, this one stands. 1.
 * REQUIRES: the other twin exists (the result of the search is not tested). */
int NookClerk_UpdateAwaitTwin(NookClerk *clerk)
{
    NookClerk *other = (NookClerk *) Actor_FindNextOfProfile(NookClerk_OtherTwin(clerk), NULL);
    int state = other->state;
    if (state != NOOK_CLERK_STATE_GREET && (state == NOOK_CLERK_STATE_STAND || other->greeting == 0)) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov050_02264210, NookClerk_UpdateAwaitTwin)

/* func_ov050_0226424c (state 10's entry): nothing. 1. */
int NookClerk_EnterAwaitTwin(void)
{
    return 1;
}
CLEAN_AS(func_ov050_0226424c, NookClerk_EnterAwaitTwin)

/* func_ov050_02264250 (state 6's update): nothing. 1. */
int NookClerk_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov050_02264250, NookClerk_UpdateTalked)

/* func_ov050_02264254 (state 6's entry): nothing. 1. */
int NookClerk_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov050_02264254, NookClerk_EnterTalked)

/* func_ov050_02264258 (state 5's update): once the clerk's action is idle, main's entry record
 * takes exit 1 when a twin talked and the date of main's block part 0x18 has passed, else exit
 * 0 (the player is put out of the store); then state 6. 1. */
int NookClerk_UpdateTalkLeave(NookClerk *clerk)
{
    if (SceneAction_IsBusy(nclerk_action(clerk)) != 0) {
        return 1;
    }
    DateTime *date = nclerk_part18();
    if (NookClerk_IsTwin(clerk) && Block021d27acPart18_HasPassed(date) != 0) {
        SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 1);
    } else {
        SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0);
    }
    NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALKED);
    return 1;
}
CLEAN_AS(func_ov050_02264258, NookClerk_UpdateTalkLeave)

/* func_ov050_022642b4 (state 5's entry): the clerk's action turns it by the yaw to its talk's
 * partner (0 without one) and talks, keeping the camera; Tom Nook clears main's block part
 * 0x18. 1. */
int NookClerk_EnterTalkLeave(NookClerk *clerk)
{
    int partner = SceneBase_MotionArg(&clerk->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(clerk->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(nclerk_action(clerk), 0, yaw, 1);
    if (NookClerk_IsNook(clerk)) {
        Block021d27acPart18_Clear(nclerk_part18());
    }
    return 1;
}
CLEAN_AS(func_ov050_022642b4, NookClerk_EnterTalkLeave)

/* func_ov050_02264304 (state 4's update): once the clerk's action is idle and, with the item on
 * display bought, the shops' answers are all in (Shops_AllAnsweredC): with main's block's flag
 * 5 the player is put out (exit 0), else the clerk's event ends; then state 6. 1. */
int NookClerk_UpdateTalk(NookClerk *clerk)
{
    if (SceneAction_IsBusy(nclerk_action(clerk)) != 0) {
        return 1;
    }
    if (clerk->bought != 0 && Shops_AllAnsweredC() == 0) {
        return 1;
    }
    if (Block021d27ac_TestFlag((u32 *) Block021d27ac_Get(), NOOK_CLERK_BLOCK_FLAG_EXIT) != 0) {
        SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0);
    } else {
        EventQueue_FinishObjectEvent(clerk);
    }
    NookClerk_SetState(clerk, NOOK_CLERK_STATE_TALKED);
    return 1;
}
CLEAN_AS(func_ov050_02264304, NookClerk_UpdateTalk)

/* func_ov050_02264364 (state 4's entry): the clerk's action turns it by the yaw to its talk's
 * partner (0 without one) and talks. Unless the player is at work, Tom Nook notes a dated
 * event of kind 3 today. 1. */
int NookClerk_EnterTalk(NookClerk *clerk)
{
    int partner = SceneBase_MotionArg(&clerk->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(clerk->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(nclerk_action(clerk), 0, yaw, 0);
    if (nclerk_at_work()) {
        return 1;
    }
    if (NookClerk_IsNook(clerk) && nclerk_todays_event(clerk) != 0) {
        clerk->has_event = 1;
    }
    return 1;
}
CLEAN_AS(func_ov050_02264364, NookClerk_EnterTalk)

/* Whether the player is in one of the states in which the clerks stay where they are. */
static int nclerk_player_held(void)
{
    return PlayerActorOps_InState(NOOK_CLERK_PLAYER_STATE_A, NOOK_CLERK_PLAYER_ACTOR) != 0 ||
           PlayerActorOps_InState(NOOK_CLERK_PLAYER_STATE_B, NOOK_CLERK_PLAYER_ACTOR) != 0;
}

/* func_ov050_022643dc (state 3's update): with the player in state 0x8b or 0x8c the clerk
 * stands; else, unless something else is noticed (nclerk_noticed), it walks toward the player
 * along the counter's path (the faster walk beyond NookClerk_HurryDistance) and stands once the
 * player is within NookClerk_WalkDistance or it is at the path's step. 1. */
int NookClerk_UpdateWalk(NookClerk *clerk)
{
    if (nclerk_player_held()) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
        return 1;
    }
    if (nclerk_noticed(clerk)) {
        return 1;
    }
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);
    int distance = SceneObject_DistanceToActor(clerk->base, NOOK_CLERK_PLAYER_ACTOR);
    Vec3 step;
    ScenePathStep_Choose(&step, clerk->base, &start);
    int walk = NookClerk_WalkDistance(clerk);
    nclerk_walk_toward(clerk, distance, NookClerk_HurryDistance(clerk), &step);
    if (distance <= walk || Vec_Equal(&step, nclerk_position(clerk)) != 0) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov050_022643dc, NookClerk_UpdateWalk)

/* func_ov050_02264510 (state 3's entry): a walk (priority 1). 1. */
int NookClerk_EnterWalk(NookClerk *clerk)
{
    nclerk_request(clerk, NOOK_CLERK_MOTION_WALK, 0, 0);
    return 1;
}
CLEAN_AS(func_ov050_02264510, NookClerk_EnterWalk)

/* func_ov050_02264544 (state 2's update): unless something else is noticed (nclerk_noticed) or
 * the player is in state 0x8b or 0x8c: the clerk walks (state 3) when the player is farther
 * than NookClerk_WalkDistance and the path's step is not where it is; else it faces the player,
 * and stands once its turn is done. The difference of its angle and the yaw is computed and
 * not used. 1. */
int NookClerk_UpdateTurn(NookClerk *clerk)
{
    if (nclerk_noticed(clerk)) {
        return 1;
    }
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);
    int distance = SceneObject_DistanceToActor(clerk->base, NOOK_CLERK_PLAYER_ACTOR);
    int yaw = nclerk_yaw_to_player(clerk);
    Math_AbsDiff16(nclerk_angle(clerk), yaw);
    int walk = NookClerk_WalkDistance(clerk);
    Vec3 step;
    ScenePathStep_Choose(&step, clerk->base, &start);
    if (nclerk_player_held()) {
        return 1;
    }
    if (distance > walk && Vec_Differ(&step, nclerk_position(clerk)) != 0) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_WALK);
        return 1;
    }
    SceneMover_SetAngle(nclerk_mover(clerk), yaw);
    if (nclerk_motion_is(clerk, NOOK_CLERK_MOTION_TURN) && SceneMotion_IsDone(nclerk_motion(clerk)) != 0) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov050_02264544, NookClerk_UpdateTurn)

/* func_ov050_02264638 (state 2's entry): a turn (priority 1). 1. */
int NookClerk_EnterTurn(NookClerk *clerk)
{
    nclerk_request(clerk, NOOK_CLERK_MOTION_TURN, 0, 0);
    return 1;
}
CLEAN_AS(func_ov050_02264638, NookClerk_EnterTurn)

/* func_ov050_0226466c (state 1's update): unless the player is in state 0x8b or 0x8c, the clerk
 * walks (state 3) when the player is farther than NookClerk_WalkDistance and the path's step is
 * not where it is, else turns (state 2) when it faces more than 0x2000 off the player. Then,
 * unless something else is noticed (nclerk_noticed), Tom Nook with a dated event of kind 3
 * today acts (state 7) once his countdown ends. 1. */
int NookClerk_UpdateStand(NookClerk *clerk)
{
    Vec3 start = *PlayerActorOps_StartPosition(NOOK_CLERK_PLAYER_ACTOR);
    int distance = SceneObject_DistanceToActor(clerk->base, NOOK_CLERK_PLAYER_ACTOR);
    int yaw = nclerk_yaw_to_player(clerk);
    int off = Math_AbsDiff16(nclerk_angle(clerk), yaw);
    int walk = NookClerk_WalkDistance(clerk);
    Vec3 step;
    ScenePathStep_Choose(&step, clerk->base, &start);
    if (nclerk_player_held()) {
        return 1;
    }
    if (distance > walk && Vec_Differ(&step, nclerk_position(clerk)) != 0) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_WALK);
    } else if (off > NOOK_CLERK_TURN_ANGLE) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_TURN);
    }
    if (nclerk_noticed(clerk)) {
        return 1;
    }
    if (clerk->has_event != 0 && Countdown_Tick16(&clerk->act_countdown) == 0) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_ACT);
    }
    return 1;
}
CLEAN_AS(func_ov050_0226466c, NookClerk_UpdateStand)

/* func_ov050_02264764 (state 1's entry): the clerk stands (priority 1, its stand's word), acts
 * after 100 to 180 frames (in steps of 20, at random), its next stand's word is the plain one,
 * and Tom Nook notes whether he has a dated event of kind 3 today. 1. */
int NookClerk_EnterStand(NookClerk *clerk)
{
    SceneMotion_RequestStand(nclerk_motion(clerk), 1, clerk->stand_word);
    clerk->act_countdown =
        (u16) (MainRandom_Below(NOOK_CLERK_ACT_FRAMES_STEPS) * NOOK_CLERK_ACT_FRAMES_STEP + NOOK_CLERK_ACT_FRAMES);
    clerk->stand_word = data_020c80f8;
    if (NookClerk_IsNook(clerk) && nclerk_todays_event(clerk) != 0) {
        clerk->has_event = 1;
    } else {
        clerk->has_event = 0;
    }
    return 1;
}
CLEAN_AS(func_ov050_02264764, NookClerk_EnterStand)

/* func_ov050_022647d4 (state 0's update): an event of kind 6 asked for. 1. */
int NookClerk_UpdateGreet(NookClerk *clerk)
{
    EventQueue_RequestKind6(clerk, 0);
    return 1;
}
CLEAN_AS(func_ov050_022647d4, NookClerk_UpdateGreet)

/* func_ov050_022647e8 (state 0's entry): Tom Nook's talk takes mode 0; a twin's mode 0x11, and
 * twin 0x74 greets (twin 0x75 waits for it in state 10). 1. */
int NookClerk_EnterGreet(NookClerk *clerk)
{
    if (NookClerk_IsNook(clerk)) {
        NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_NOOK_GREET);
    } else if (NookClerk_IsTwin(clerk)) {
        if (NookClerk_IsTwinA(clerk)) {
            clerk->greeting = 1;
        }
        NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_TWIN_GREET);
    }
    return 1;
}
CLEAN_AS(func_ov050_022647e8, NookClerk_EnterGreet)

/* func_ov050_02264834: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 18 (the table is not bounded). */
void NookClerk_SetState(NookClerk *clerk, int state)
{
    const NookClerkStep *step = &data_ov050_02265f08[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, clerk);
    }
    if (taken != 0) {
        clerk->state = state;
    }
}
CLEAN_AS(func_ov050_02264834, NookClerk_SetState)

/* func_ov050_02264878 (vtable slot 0x68, each frame): the state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: the state is 0 to 18. */
int NookClerk_Update(NookClerk *clerk)
{
    const NookClerkStep *step = &data_ov050_02265f08[(u32) clerk->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, clerk);
}
CLEAN_AS(func_ov050_02264878, NookClerk_Update)

/* The look of a clerk: a twin's, else Tom Nook's by the code he was made with (0xd019 to
 * 0xd01c; any other code the first). */
static int nclerk_look(NookClerk *clerk)
{
    if (NookClerk_IsTwin(clerk)) {
        return NOOK_CLERK_LOOK_TWIN;
    }
    u32 look = *(const u32 *) (const void *) nclerk_part(clerk, NOOK_CLERK_CODE) - NOOK_CLERK_FIRST_LOOK;
    return look < NOOK_CLERK_LOOK_TWIN ? (int) look : 0;
}

/* func_ov050_022648c4 (vtable slot 0x70): the model's file name of the clerk's look. */
int NookClerk_ModelName(NookClerk *clerk)
{
    return (int) (uintptr_t) data_ov050_0226585c[nclerk_look(clerk)];
}
CLEAN_AS(func_ov050_022648c4, NookClerk_ModelName)

/* func_ov050_0226491c (vtable slot 0x6c): the texture's file name of the clerk's look. */
int NookClerk_TextureName(NookClerk *clerk)
{
    return (int) (uintptr_t) data_ov050_02265848[nclerk_look(clerk)];
}
CLEAN_AS(func_ov050_0226491c, NookClerk_TextureName)

/* An invalid date of main's block part 0x18 becomes today's. */
static void nclerk_date_today_if_invalid(void)
{
    if (DateTime_IsInvalid(Block021d27acPart18_Get(nclerk_part18())) != 0) {
        Block021d27acPart18_SetToday(nclerk_part18());
    }
}

/* With the date of `date` passed, the scene's music is made the late one. */
static void nclerk_late_music(DateTime *date)
{
    if (Block021d27acPart18_HasPassed(date) != 0) {
        SceneMusic_ForceLateMusic((SceneMusic *) (void *) (data_021c526c + NOOK_CLERK_SCENE_MUSIC));
    }
}

/* func_ov050_02264974 (vtable slot 0x00, the start): unless the special character refuses to
 * start:
 * - linked (or with the game variable 0x4a set) the clerk is held (flag 2 at 0x4e8); when this
 *   system holds the scene, an invalid date of main's block part 0x18 becomes today's, the clerk
 *   faces and walks along angle 0 and stands (state 13), else it awaits the session;
 * - else an invalid date of that part becomes today's. With the player at work, the map's
 *   object 1 is claimed, the talk takes mode 5, the date becomes today's (the late music when it
 *   has passed), and the clerk stands when block 0's object of the player's villager part is in
 *   use and past its first step or of type 0xc or more, else greets;
 * - else twin 0x74 coming from the scene 0x1d greets (the date today's), twin 0x75 from there
 *   awaits its twin, Tom Nook coming from none greets (the date today's); any other start but
 *   from the scene 0x1e makes the date today's and the clerk stands. The map's object 0 is
 *   claimed, and Tom Nook makes the music the late one once the date has passed and notes a
 *   dated event of kind 3 today.
 * Whether it started. */
int NookClerk_Start(NookClerk *clerk)
{
    if (SpecialSceneObject_Start(clerk) == 0) {
        return 0;
    }
    u32 *flags = (u32 *) (void *) nclerk_part(clerk, NOOK_CLERK_FLAGS);
    if (nclerk_linked_or_variable(data_020ccf94)) {
        *flags |= NOOK_CLERK_HELD;
        if (LinkGlobal_HoldsScene()) {
            nclerk_date_today_if_invalid();
            *(s16 *) (void *) nclerk_part(clerk, NOOK_CLERK_ANGLE) = 0;
            *(s16 *) (void *) nclerk_part(clerk, NOOK_CLERK_WALK_ANGLE) = 0;
            NookClerk_SetState(clerk, NOOK_CLERK_STATE_LINKED_STAND);
        } else {
            NookClerk_SetState(clerk, NOOK_CLERK_STATE_AWAIT);
        }
        return 1;
    }

    nclerk_date_today_if_invalid();
    DateTime *date = nclerk_part18();
    u8 *record = PlayerRecords_Current();
    VillagerPart *part = (VillagerPart *) PlayerRecord_VillagerPart(record);
    if (PlayerRecord_TestFlag(record, NOOK_CLERK_JOB_FLAG) != 0) {
        ItemObject *errand = (ItemObject *) VillagerPartBlock_Object(VillagerPart_Block(part, 0));
        CollisionMap_Claim(1);
        NookClerkTalk_SetMode(&clerk->talk, NOOK_CLERK_MODE_NOOK_TALKED);
        Block021d27acPart18_SetToday(date);
        nclerk_late_music(date);
        if (ItemObject_IsInUse(errand) != 0 && (ItemObject_Low5(errand) >= 1 || ItemObject_Type(errand) >= 0xc)) {
            NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
        } else {
            NookClerk_SetState(clerk, NOOK_CLERK_STATE_GREET);
        }
        return 1;
    }

    if (NookClerk_IsTwinA(clerk) && SceneQuery_Previous() == NOOK_CLERK_FROM_1D) {
        Block021d27acPart18_SetToday(date);
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_GREET);
    } else if (NookClerk_IsTwinB(clerk) && SceneQuery_Previous() == NOOK_CLERK_FROM_1D) {
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_AWAIT_TWIN);
    } else if (NookClerk_IsNook(clerk) && SceneQuery_Previous() == NOOK_CLERK_FROM_NONE) {
        Block021d27acPart18_SetToday(date);
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_GREET);
    } else {
        if (SceneQuery_Previous() != NOOK_CLERK_FROM_1E) {
            Block021d27acPart18_SetToday(date);
        }
        NookClerk_SetState(clerk, NOOK_CLERK_STATE_STAND);
    }
    CollisionMap_Claim(0);
    if (NookClerk_IsNook(clerk)) {
        nclerk_late_music(date);
        if (nclerk_todays_event(clerk) != 0) {
            clerk->has_event = 1;
        }
    }
    return 1;
}
CLEAN_AS(func_ov050_02264974, NookClerk_Start)

/* func_ov050_02264b7c (vtable slot 0x04, the set-up): unless the special character refuses, the
 * talk scene becomes its scene and gets the clerk as its owner; a twin's body is 0xccd wide and
 * 0x2000 high and its collider 0xb00; the stand's word is the plain one and the mover's pace
 * (mode 2) is set. Linked (or with the game variable 0x4a) the clerk is put at the place of the
 * code it was made with. Twin 0x74 does not greet. Whether it was set up. */
int NookClerk_Init(NookClerk *clerk)
{
    if (SpecialSceneObject_Init(clerk) == 0) {
        return 0;
    }
    SceneObject_SetScene(clerk->base, &clerk->talk.base);
    NookClerkTalk_Begin(&clerk->talk, clerk);
    if (NookClerk_IsTwin(clerk)) {
        SpecialSceneObject_SetBodySize(clerk->base, NOOK_CLERK_TWIN_RADIUS, NOOK_CLERK_TWIN_HEIGHT);
        SceneObject_SetColliderSize(clerk->base, NOOK_CLERK_TWIN_COLLIDER);
    }
    clerk->stand_word = data_020c80f8;
    SceneMover_SetPace(nclerk_mover(clerk), NOOK_CLERK_PACE_MODE, NOOK_CLERK_PACE_SPEED, NOOK_CLERK_PACE_SPEED_UP,
                       NOOK_CLERK_PACE_SLOW_DOWN);

    if (nclerk_linked_or_variable(data_020ccf94)) {
        fx32 x;
        fx32 z;
        int place = 1;
        switch (*(const u32 *) (const void *) nclerk_part(clerk, NOOK_CLERK_CODE)) {
            case 0xd00f:
                x = 0xf000, z = 0x11000;
                break;
            case 0xd010:
                x = 0xf000, z = 0x13000;
                break;
            case 0xd019:
                x = 0xf000, z = 0x19000;
                break;
            case 0xd01a:
                x = 0x13000, z = 0x17000;
                break;
            case 0xd01b:
                x = 0xf000, z = 0x15000;
                break;
            case 0xd01c:
                x = 0x11000, z = 0x13000;
                break;
            default:
                x = 0, z = 0;
                place = 0;
                break;
        }
        if (place) {
            *(fx32 *) (void *) nclerk_part(clerk, NOOK_CLERK_X) = x;
            *(fx32 *) (void *) nclerk_part(clerk, NOOK_CLERK_Y) = 0;
            *(fx32 *) (void *) nclerk_part(clerk, NOOK_CLERK_Z) = z;
        }
    }
    clerk->greeting = 0;
    return 1;
}
CLEAN_AS(func_ov050_02264b7c, NookClerk_Init)

/* A zeroed block of 0x744 bytes from the auxiliary heap, constructed: the scene object base,
 * the class 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the clerks' class's vtable, its talk scene, no item
 * and no tile. Null when there is no room. */
static void *nclerk_create(void)
{
    NookClerk *clerk = (NookClerk *) Heap_AllocAuxZeroed(sizeof(NookClerk));
    if (clerk == NULL) {
        return NULL;
    }
    u8 *object = clerk->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) nclerk_part(clerk, NOOK_CLERK_PERSON) = NOOK_CLERK_NO_ITEM;
    LayeredModel_ConstructB((LayeredModel *) (void *) nclerk_part(clerk, NOOK_CLERK_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) nclerk_part(clerk, NOOK_CLERK_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) nclerk_part(clerk, NOOK_CLERK_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) nclerk_part(clerk, NOOK_CLERK_ANIM));
    SceneMover_Construct(nclerk_mover(clerk));
    SceneProbe_Construct(nclerk_part(clerk, NOOK_CLERK_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) nclerk_part(clerk, NOOK_CLERK_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) nclerk_part(clerk, NOOK_CLERK_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) nclerk_part(clerk, NOOK_CLERK_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) nclerk_part(clerk, NOOK_CLERK_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) nclerk_part(clerk, NOOK_CLERK_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) nclerk_part(clerk, NOOK_CLERK_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) nclerk_part(clerk, NOOK_CLERK_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) nclerk_part(clerk, NOOK_CLERK_FOOTSTEPS));
    SceneMotion_Construct(nclerk_motion(clerk));
    SceneAction_Construct(nclerk_action(clerk));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) nclerk_part(clerk, NOOK_CLERK_HEAP));
    *(const u8 **) (void *) object = data_ov050_02265a60;
    NookClerkTalk_Construct(&clerk->talk);
    clerk->item = NOOK_CLERK_NO_ITEM;
    clerk->tile_x = 0;
    clerk->tile_z = 0;
    return clerk;
}

/* func_ov050_02264cf4 (twin 0x74's record's create function, data_ov050_02265918): a clerk. */
void *NookClerk_CreateTwinA(void)
{
    return nclerk_create();
}
CLEAN_AS(func_ov050_02264cf4, NookClerk_CreateTwinA)

/* func_ov050_02264e28 (twin 0x75's record's create function, data_ov050_02265900): a clerk. */
void *NookClerk_CreateTwinB(void)
{
    return nclerk_create();
}
CLEAN_AS(func_ov050_02264e28, NookClerk_CreateTwinB)

/* func_ov050_02264f5c (Tom Nook's record's create function, data_ov050_022658e8): a clerk. */
void *NookClerk_CreateNook(void)
{
    return nclerk_create();
}
CLEAN_AS(func_ov050_02264f5c, NookClerk_CreateNook)
