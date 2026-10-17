/* The villager who buys an item of the player's room at the flea market (flea_market_buyer.h). */
#include "flea_market_buyer.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/block_020b220c.h"
#include "main/collision_map.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/footsteps.h"
#include "main/furniture_info.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/item_traits.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/npc_id.h"
#include "main/player_actor_ops.h"
#include "main/player_id.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/scene_exit.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_path_step.h"
#include "main/scene_place.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/screen_panels.h"
#include "main/session_players.h"
#include "main/sound_emitter.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/town_objects.h"
#include "main/town_villager.h"
#include "main/villager_entry.h"
#include "main/villager_items.h"
#include "main/villager_memories.h"
#include "main/villager_memory_bits.h"
#include "main/villager_memory_entry.h"
#include "main/villager_scene_slots.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "main/villager_talk_scene.h"
#include "room_object_body.h"

static_assert(sizeof(VillagerTalk) == 0x1a4, "the town villager's talk scene");
static_assert(sizeof(FleaMarketBuyerTalk) == 0x1b0, "its talk scene");
static_assert(sizeof(FleaMarketBuyerTalkStep) == 0xc, "a step of its talk");
static_assert(offsetof(FleaMarketBuyer, item) == 0x898, "item");
static_assert(offsetof(FleaMarketBuyer, target) == 0x89c, "target");
static_assert(offsetof(FleaMarketBuyer, object) == 0x8a8, "object");
static_assert(offsetof(FleaMarketBuyer, recent) == 0x8ac, "recent objects");
static_assert(offsetof(FleaMarketBuyer, state) == 0x910, "state");
static_assert(offsetof(FleaMarketBuyer, previous_state) == 0x914, "previous state");
static_assert(offsetof(FleaMarketBuyer, talk) == 0x918, "talk scene");
static_assert(offsetof(FleaMarketBuyer, talk.price) == 0xac0, "price");
static_assert(offsetof(FleaMarketBuyer, stage) == 0xac8, "stage");
static_assert(offsetof(FleaMarketBuyer, leave_wait) == 0xacc, "leave wait");
static_assert(offsetof(FleaMarketBuyer, talk_time) == 0xad0, "talk time");
static_assert(offsetof(FleaMarketBuyer, reach) == 0xad8, "reach");
static_assert(offsetof(FleaMarketBuyer, step_wait) == 0xadc, "step wait");
static_assert(offsetof(FleaMarketBuyer, talk_wait) == 0xadd, "talk wait");
static_assert(offsetof(FleaMarketBuyer, sound_played) == 0xade, "sound played");
static_assert(offsetof(FleaMarketBuyer, bought) == 0xae0, "bought");
static_assert(offsetof(FleaMarketBuyer, object_count) == 0xae4, "object count");
static_assert(offsetof(FleaMarketBuyer, browse_frames) == 0xae8, "browse frames");
static_assert(sizeof(FleaMarketBuyer) == 0xaec, "the size func_ov004_022217fc allocates");

/* The parts of the town villager scene object used here, by place (main's scene_object.h). */
#define FMB_MOVER 0x350  /* SceneMover */
#define FMB_MOTION 0x564 /* SceneMotion */
#define FMB_ACTION 0x618 /* SceneAction */
#define FMB_RECORD 0x830 /* u8 *: its town record */

/* The field actor of this console's player. */
#define FMB_PLAYER_ACTOR 4

/* The stages of its visit (FleaMarketBuyer.stage). */
#define FMB_STAGE_CALL 0
#define FMB_STAGE_GREETED 1
#define FMB_STAGE_BROWSE 2
#define FMB_STAGE_TIME_UP 3
#define FMB_STAGE_TIME_UP_BYE 4
#define FMB_STAGE_PLAYER_AT_EXIT 5
#define FMB_STAGE_PLAYER_AT_EXIT_BYE 6

/* Its states (func_ov004_02221550). */
#define FMB_STATE_GREET 1
#define FMB_STATE_BROWSE 3
#define FMB_STATE_FACE 4
#define FMB_STATE_GO 5
#define FMB_STATE_TALK 6
#define FMB_STATE_BYE 7
#define FMB_STATE_DONE 8

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define FMB_EVENT_TALK 0
#define FMB_EVENT_1 1
#define FMB_EVENT_ENDED 8

/* The kinds of motion asked for (scene_motion_request.h) and the rate of its run. */
#define FMB_MOTION_STAND 0
#define FMB_MOTION_WALK 1
#define FMB_MOTION_RUN 2
#define FMB_MOTION_TURN 3
#define FMB_RUN_RATE 0x800

/* The steps of its talk (FleaMarketBuyerTalk.step). */
#define FMB_TALK_STEP_NONE 0
#define FMB_TALK_STEP_OFFER 1

/* The item code of "no item", the value kind of an item's name (SceneBase_PutItemName), and the
 * bag of bells given when the price has none (ItemTraits_BellBagFor). */
#define FMB_NO_ITEM 0xfff1
#define FMB_ITEM_NAME_KIND 7
#define FMB_DEFAULT_BELL_BAG 0x1492
/* The items it does not buy: the player's designs (four ranges of 0x80 codes) and three others. */
#define FMB_DESIGNS_A_FIRST 0x3d84
#define FMB_DESIGNS_A_LAST 0x3e03
#define FMB_DESIGNS_B_FIRST 0x3ea4
#define FMB_DESIGNS_B_LAST 0x3f23
#define FMB_DESIGNS_C_FIRST 0x4224
#define FMB_DESIGNS_C_LAST 0x42a3
#define FMB_DESIGNS_D_FIRST 0x3f24
#define FMB_DESIGNS_D_LAST 0x3fa3
#define FMB_KEPT_ITEM_A 0x409c
#define FMB_KEPT_ITEM_B 0x40a0
#define FMB_KEPT_ITEM_C 0x3820
/* The items it buys in a visit at most. */
#define FMB_MAX_BOUGHT 3
/* A cleared entry of its recent objects. */
#define FMB_NO_RECENT 0xff

/* The frames it is given to leave after no item could be found (10 seconds). */
#define FMB_LEAVE_FRAMES 0x258
/* It leaves an hour after its last talk, or after 600 frames of looking about. */
#define FMB_STAY_MINUTES 0x3c
#define FMB_BROWSE_FRAMES 0x258

/* How close it walks to an item by the item's shape (FurnitureInfo_Shape). */
#define FMB_REACH_SMALL 0x3000
#define FMB_REACH_LARGE 0x4000
/* Farther than its reach and this it runs to the item. */
#define FMB_RUN_MARGIN 0x1000
/* Turned away from the item by more than this (an eighth of a turn) it turns to it. */
#define FMB_TURN_ANGLE 0x2000
/* How far ahead of it the object it may buy on its way is looked for (a tile). */
#define FMB_AHEAD 0x2000
/* State 2: the facing into the room, how far it walks and the frames it then waits. */
#define FMB_INTO_ROOM_YAW ((s16) - 0x8000)
#define FMB_STEP_IN 0x4000
#define FMB_STEP_IN_FRAMES 0x1e
/* The frames before the talk of a greeted villager's step-in. */
#define FMB_GREETED_WAIT 0x28
/* The yaw's bits below one step of FX_SinCosTable_. */
#define FMB_SIN_SHIFT 4
/* The exits it takes from the room (SceneExit_Take): with the player, and alone. */
#define FMB_EXIT_WITH_PLAYER 0
#define FMB_EXIT_ALONE 6

/* The least price, the value slot and format of the price (SceneBase_PutValue). */
#define FMB_MIN_PRICE 10
#define FMB_PRICE_SLOT 0
#define FMB_PRICE_FORMAT 10
/* What the fondness of the player raises its price from, and its divisor (0x200 in 20.12). */
#define FMB_BASE_FONDNESS 0xff
#define FMB_PRICE_DIVISOR 0x200000
/* The screen of the price asked (SceneCommand_SetScreenMode, SceneCommand_RequestScreen). */
#define FMB_PRICE_SCREEN_MODE 0x38
#define FMB_PRICE_SCREEN 2

/* The motion its pay is handed with (SceneCommand_RequestMotion13). */
#define FMB_HAND_OVER 5

/* The size of the texts the message file names are written in. */
#define FMB_FILE_NAME_SIZE 0x28
/* A message number for "none chosen". */
#define FMB_NO_MESSAGE 0xff

/* The vtables: the class's, and its talk scene's. */
extern const u8 data_ov004_02253e10[];
extern const u8 data_ov004_02253d80[];
/* The steps of its talk (filled at start-up). */
extern FleaMarketBuyerTalkStep data_ov004_02257dd8[2];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The message number that ends the talk. */
extern u8 data_021f43e8;
/* 1 while the game is in a room. */
extern u8 data_020e54a8;
/* The sine and cosine of each 16th of an angle step. */
extern const s16 FX_SinCosTable_[];
/* The texts the message file names are written in: by its talk's step of the offer, its answer,
 * its line and its message's end. */
extern char data_ov004_02257df0[FMB_FILE_NAME_SIZE];
extern char data_ov004_02257e18[FMB_FILE_NAME_SIZE];
extern char data_ov004_02257e40[FMB_FILE_NAME_SIZE];
extern char data_ov004_02257e68[FMB_FILE_NAME_SIZE];
/* The message files: "ev_fmarket3", "q_bye", "q10_wait" and "q10_call". */
extern const char data_ov004_02253ed0[], data_ov004_02253edc[], data_ov004_02253ee4[], data_ov004_02253ef0[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* The functions of the room kept as the game's. */
/* The room's list of objects, its object of a number (NULL for none) and how many it holds. */
extern void *func_ov004_0223ce84(void);
extern RoomObject *func_ov004_0223cd58(void *objects, int index);
extern int func_ov004_0223cdc0(void *objects);
/* Whether the room's object of a number may be taken: there is one, its vtable slot 0xa0 agrees
 * and nothing stands on it. */
extern int func_ov004_0223ba78(int number);
/* The room object taken away by number. */
extern int func_ov004_0223bb14(int number);
/* The grid of the room's objects, and the number at a cell of it (-1 for none). */
extern void *func_ov004_0223cd50(void);
extern int func_ov004_0223cc5c(void *grid, int x, int z, int layer);
/* Notes that a villager of the flea market is in the room (sets data_ov004_022595b4). */
extern void func_ov004_0223d33c(void);

static u8 *fmb_part(FleaMarketBuyer *buyer, u32 offset)
{
    return buyer->base + offset;
}

static Actor *fmb_actor_of(FleaMarketBuyer *buyer)
{
    return (Actor *) (void *) buyer->base;
}

static SceneAction *fmb_action_of(FleaMarketBuyer *buyer)
{
    return (SceneAction *) (void *) fmb_part(buyer, FMB_ACTION);
}

static SceneMotion *fmb_motion_of(FleaMarketBuyer *buyer)
{
    return (SceneMotion *) (void *) fmb_part(buyer, FMB_MOTION);
}

static SceneMover *fmb_mover_of(FleaMarketBuyer *buyer)
{
    return (SceneMover *) (void *) fmb_part(buyer, FMB_MOVER);
}

/* Its town record. */
static u8 *fmb_record(FleaMarketBuyer *buyer)
{
    return *(u8 **) (void *) fmb_part(buyer, FMB_RECORD);
}

static SceneBase *fmb_scene_of(FleaMarketBuyerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static SceneCommandScene *fmb_command_of(FleaMarketBuyerTalk *talk)
{
    return &talk->base.scene;
}

static TalkObject *fmb_talk_object(FleaMarketBuyerTalk *talk)
{
    return (TalkObject *) (void *) talk->base.scene.talk;
}

/* The talk scene's vtable slot 0x08 called. */
static void fmb_talk_slot_08(FleaMarketBuyerTalk *talk)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + 0x08);
    ((void (*)(FleaMarketBuyerTalk *))(uintptr_t) code)(talk);
}

/* Whether `item` is `code`: for an item with a variant, the same item of any variant. */
static int fmb_item_is(const u16 *item, u16 code)
{
    if (ItemCode_HasVariant(item)) {
        u16 other = code;
        int same = ItemCode_VariantItem(item);
        return same == ItemCode_VariantItem(&other);
    }
    return *item == code;
}

/* The message file `name` for the villager, written into `text`. */
static void fmb_format_file(FleaMarketBuyer *buyer, char *text, const char *name)
{
    NpcId_FormatResourceName(TownVillager_NpcId(fmb_record(buyer)), text, FMB_FILE_NAME_SIZE, name);
}

/* A motion of `kind` (priority 1) asked for with no arguments but `rate` and `angle`. */
static void fmb_request_motion(FleaMarketBuyer *buyer, int kind, s16 rate, s16 angle)
{
    SceneMotion_Request(fmb_motion_of(buyer), kind, 1, 0, 0, rate, angle, 0, 0, data_020c80f8, 0);
}

/* The turn of its action to the talk's partner (none: angle 0), then talking; `keep_camera` as
 * SceneAction_RequestTurnAndTalk takes it. */
static void fmb_turn_and_talk(FleaMarketBuyer *buyer, int keep_camera)
{
    int partner = SceneBase_MotionArg(fmb_scene_of(&buyer->talk));
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(buyer->base, (u8 *) (uintptr_t) partner);
    }
    SceneAction_RequestTurnAndTalk(fmb_action_of(buyer), 0, angle, keep_camera);
}

/* The room's object of `number` becomes the item it wants: its item (variant 0), its centre and
 * the reach of its shape; the number is remembered among its last chosen. */
static void fmb_choose(FleaMarketBuyer *buyer, int number)
{
    RoomObject *object = func_ov004_0223cd58(func_ov004_0223ce84(), number);
    buyer->item = ItemCode_MakeVariant(RoomObject_Number(object), 0);
    RoomObject_Centre(object, &buyer->target);
    FleaMarketBuyer_SetReach(buyer, object);
    FleaMarketBuyer_Remember(buyer, (u8) number);
    buyer->object = number;
}

/* func_ov004_0221ffc4 (vtable slot 0x40): the destructor, without freeing: its talk scene, then
 * the town villager scene object. */
FleaMarketBuyer *FleaMarketBuyer_Destroy(FleaMarketBuyer *buyer)
{
    *(const u8 **) (void *) buyer->base = data_ov004_02253e10;
    FleaMarketBuyerTalk_Destroy(&buyer->talk);
    VillagerSceneObject_DestructBody(buyer->base);
    return buyer;
}
CLEAN_AS(func_ov004_0221ffc4, FleaMarketBuyer_Destroy)

/* func_ov004_0221ffec (vtable slot 0x44, the deleting destructor). */
FleaMarketBuyer *FleaMarketBuyer_Delete(FleaMarketBuyer *buyer)
{
    *(const u8 **) (void *) buyer->base = data_ov004_02253e10;
    FleaMarketBuyerTalk_Destroy(&buyer->talk);
    VillagerSceneObject_DestructBody(buyer->base);
    Heap_FreeAux(buyer);
    return buyer;
}
CLEAN_AS(func_ov004_0221ffec, FleaMarketBuyer_Delete)

/* func_ov004_02220018: how close it walks to `object`: 0x3000 for an item of shape 0, 0x4000 for
 * shapes 1 and 2; another shape leaves it as it is. */
void FleaMarketBuyer_SetReach(FleaMarketBuyer *buyer, RoomObject *object)
{
    switch (FurnitureInfo_Shape(RoomObject_Number(object))) {
        case 0:
            buyer->reach = FMB_REACH_SMALL;
            break;
        case 1:
        case 2:
            buyer->reach = FMB_REACH_LARGE;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02220018, FleaMarketBuyer_SetReach)

/* func_ov004_0222005c: `number` remembered as the newest of its last chosen objects, the oldest
 * forgotten. */
void FleaMarketBuyer_Remember(FleaMarketBuyer *buyer, u8 number)
{
    for (int i = 0; i < FLEA_MARKET_BUYER_RECENT - 1; i++) {
        buyer->recent[i] = buyer->recent[i + 1];
    }
    buyer->recent[FLEA_MARKET_BUYER_RECENT - 1] = number;
}
CLEAN_AS(func_ov004_0222005c, FleaMarketBuyer_Remember)

/* func_ov004_02220084: whether it may want the room's object of `number`: there is one, it may
 * be taken (func_ov004_0223ba78), its item (variant 0) is none of the player's designs nor
 * 0x409c, 0x40a0 or 0x3820 (by the variant's item), and it is not among its last chosen. */
int FleaMarketBuyer_MayBuy(FleaMarketBuyer *buyer, int number)
{
    RoomObject *object = func_ov004_0223cd58(func_ov004_0223ce84(), number);
    if (object == NULL) {
        return 0;
    }
    if (func_ov004_0223ba78(number) == 0) {
        return 0;
    }
    u16 item = ItemCode_MakeVariant(RoomObject_Number(object), 0);
    if ((item >= FMB_DESIGNS_A_FIRST && item <= FMB_DESIGNS_A_LAST) ||
        (item >= FMB_DESIGNS_B_FIRST && item <= FMB_DESIGNS_B_LAST) ||
        (item >= FMB_DESIGNS_C_FIRST && item <= FMB_DESIGNS_C_LAST) ||
        (item >= FMB_DESIGNS_D_FIRST && item <= FMB_DESIGNS_D_LAST) || fmb_item_is(&item, FMB_KEPT_ITEM_A) ||
        fmb_item_is(&item, FMB_KEPT_ITEM_B) || fmb_item_is(&item, FMB_KEPT_ITEM_C)) {
        return 0;
    }
    for (int i = 0; i < FLEA_MARKET_BUYER_RECENT; i++) {
        if (number == buyer->recent[i]) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02220084, FleaMarketBuyer_MayBuy)

/* The leaving countdown started (10 seconds) unless it runs. */
static void fmb_start_leave_wait(FleaMarketBuyer *buyer)
{
    if (buyer->leave_wait == 0) {
        buyer->leave_wait = FMB_LEAVE_FRAMES;
    }
}

/* func_ov004_02220210: with no item wanted, an object of the room it may buy is chosen: from a
 * random number below the room's count of objects, each number in turn (wrapping to 0 at the
 * count). Whether it wants an item now; when none could be had (no objects, 3 items bought or
 * none it may buy) its leaving countdown is started.
 * QUIRK: only the numbers below the count of the objects are tried, though the room's list may
 * have empty places among them. */
int FleaMarketBuyer_PickItem(FleaMarketBuyer *buyer)
{
    if (!fmb_item_is(&buyer->item, FMB_NO_ITEM)) {
        return 1;
    }
    if (buyer->object_count == 0 || buyer->bought >= FMB_MAX_BOUGHT) {
        fmb_start_leave_wait(buyer);
        return 0;
    }
    int start = (int) MainRandom_Below(buyer->object_count);
    int number = start;
    do {
        if (FleaMarketBuyer_MayBuy(buyer, number)) {
            fmb_choose(buyer, number);
            return 1;
        }
        number++;
        if (number >= buyer->object_count) {
            number = 0;
        }
    } while (number != start);
    fmb_start_leave_wait(buyer);
    return 0;
}
CLEAN_AS(func_ov004_02220210, FleaMarketBuyer_PickItem)

/* Its stage set and an event of kind 6 about it asked for. */
static int fmb_leave(FleaMarketBuyer *buyer, u8 stage)
{
    buyer->stage = stage;
    EventQueue_RequestKind6(buyer, 0);
    return 1;
}

/* func_ov004_02220318: whether it asks to leave (stage 5, or 3, and an event of kind 6): stage 5
 * when the player (where their frame began) is on the unit the collision map has claimed.
 * Else, with no event going on, its leaving countdown runs down, and asks on reaching 1; its
 * frames of looking about are counted while nonzero, and it asks when an hour has passed since
 * its last talk or after 600 of them. */
int FleaMarketBuyer_CheckLeave(FleaMarketBuyer *buyer)
{
    Vec3 player = *PlayerActorOps_StartPosition(FMB_PLAYER_ACTOR);
    if (CollisionMap_IsClaimedAtPoint(&player)) {
        return fmb_leave(buyer, FMB_STAGE_PLAYER_AT_EXIT);
    }
    if (EventQueue_HasCurrent() != 0) {
        return 0;
    }
    if (buyer->leave_wait != 0) {
        buyer->leave_wait--;
        if (buyer->leave_wait == 1) {
            return fmb_leave(buyer, FMB_STAGE_TIME_UP);
        }
    }
    DateTime now = {0};
    DateTime_Now(&now);
    int minutes = DateTime_MinutesBetween(&buyer->talk_time, &now);
    if (buyer->browse_frames != 0) {
        buyer->browse_frames++;
    }
    if (minutes >= FMB_STAY_MINUTES || buyer->browse_frames > FMB_BROWSE_FRAMES) {
        return fmb_leave(buyer, FMB_STAGE_TIME_UP);
    }
    return 0;
}
CLEAN_AS(func_ov004_02220318, FleaMarketBuyer_CheckLeave)

/* Its talk told through its vtable slot 0x08 and given this console's player's object as the
 * motion's argument. */
static void fmb_ready_talk(FleaMarketBuyer *buyer)
{
    fmb_talk_slot_08(&buyer->talk);
    SceneBase_SetMotionArg(fmb_scene_of(&buyer->talk), SceneObject_ActorObject(buyer->base, FMB_PLAYER_ACTOR));
}

/* func_ov004_022203e0 (vtable slot 0x4c, told of an event):
 * - 1: its talk readied, then it says goodbye (state 7) in stages 3 and 5, else talks (state
 *   6). In stage 0 (it has just come) the room's objects are counted, the town's extra
 *   visitors set, the collision map's claim set to 0, the room notes a villager of the flea
 *   market (func_ov004_0223d33c) and the time is its last talk's;
 * - 0, the player talks to it: its talk readied, state 6;
 * - 8, the event ended: in stage 6 with the player on the claimed unit the claim is cleared;
 *   else it browses (state 3). */
void FleaMarketBuyer_OnEvent(FleaMarketBuyer *buyer, int code)
{
    switch (code) {
        case FMB_EVENT_1:
            fmb_ready_talk(buyer);
            if (buyer->stage == FMB_STAGE_PLAYER_AT_EXIT || buyer->stage == FMB_STAGE_TIME_UP) {
                FleaMarketBuyer_SetState(buyer, FMB_STATE_BYE);
            } else {
                FleaMarketBuyer_SetState(buyer, FMB_STATE_TALK);
            }
            if (buyer->stage == FMB_STAGE_CALL) {
                buyer->object_count = func_ov004_0223cdc0(func_ov004_0223ce84());
                TownObjects_SetExtraVisitors();
                CollisionMap_Claim(0);
                func_ov004_0223d33c();
                DateTime_Now(&buyer->talk_time);
            }
            break;
        case FMB_EVENT_TALK:
            fmb_ready_talk(buyer);
            FleaMarketBuyer_SetState(buyer, FMB_STATE_TALK);
            break;
        case FMB_EVENT_ENDED:
            if (buyer->stage == FMB_STAGE_PLAYER_AT_EXIT_BYE) {
                Vec3 player = *PlayerActorOps_StartPosition(FMB_PLAYER_ACTOR);
                if (CollisionMap_IsClaimedAtPoint(&player)) {
                    CollisionMap_ClearClaim();
                    break;
                }
            }
            FleaMarketBuyer_SetState(buyer, FMB_STATE_BROWSE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_022203e0, FleaMarketBuyer_OnEvent)

/* func_ov004_022204cc (vtable slot 0x58): whether its action is idle. */
int FleaMarketBuyer_IsIdle(FleaMarketBuyer *buyer)
{
    return SceneAction_IsBusy(fmb_action_of(buyer)) == 0;
}
CLEAN_AS(func_ov004_022204cc, FleaMarketBuyer_IsIdle)

/* func_ov004_022204ec (vtable slot 0x48): whether the player may talk to it: its action idle. */
int FleaMarketBuyer_MayAct(FleaMarketBuyer *buyer)
{
    return SceneAction_IsBusy(fmb_action_of(buyer)) == 0;
}
CLEAN_AS(func_ov004_022204ec, FleaMarketBuyer_MayAct)

/* The message of the talk scene's receiver. */
static u8 fmb_message_of(FleaMarketBuyerTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* func_ov004_0222050c (the talk scene's receiver slot 0x18, the player's answer; read whatever
 * the message), in stage 2 only, all from "ev_fmarket3":
 * - after messages 6, 7, 10 and 11 (it asks to buy the item): the first answer opens the
 *   screen of the price asked and the talk's step becomes the offer; the other: message 8 or 9
 *   and the item is no longer wanted;
 * - after messages 12 and 13 (it agrees to the price): the first answer, when the player's
 *   pockets can take the price in bells: the bells handed over in their bag (0x1492 when the
 *   price makes none), given to the player and the item bought (FleaMarketBuyerTalk_Buy), then
 *   message 14 or 15; when the bells fit neither the wallet nor bags nothing more is said; when
 *   the pockets cannot take them, message 18 or 19. The other answer: message 16 or 17 and the
 *   item is no longer wanted. */
void FleaMarketBuyerTalk_OnAnswer(FleaMarketBuyerTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) SceneBase_TalkChoices(fmb_scene_of(talk)));
    u8 message = FMB_NO_MESSAGE;

    if (talk->buyer->stage != FMB_STAGE_BROWSE) {
        return;
    }
    switch (fmb_message_of(talk)) {
        case 6:
        case 7:
        case 10:
        case 11:
            fmb_format_file(talk->buyer, data_ov004_02257e18, data_ov004_02253ed0);
            if (answer == 0) {
                SceneCommand_SetScreenMode(fmb_command_of(talk), FMB_PRICE_SCREEN_MODE, 0);
                SceneCommand_RequestScreen(fmb_command_of(talk), FMB_PRICE_SCREEN);
                FleaMarketBuyerTalk_SetStep(talk, FMB_TALK_STEP_OFFER);
            } else {
                message = (u8) (MainRandom_Below(2) + 8);
                FleaMarketBuyerTalk_DropItem(talk);
            }
            break;
        case 12:
        case 13:
            fmb_format_file(talk->buyer, data_ov004_02257e18, data_ov004_02253ed0);
            if (answer == 0) {
                PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
                int fit = SceneBells_Fit((int) (uintptr_t) talk->buyer, talk->price, 0);
                u16 bag = (u16) ItemTraits_BellBagFor(talk->price, 0, NULL);
                if (bag == FMB_NO_ITEM) {
                    bag = FMB_DEFAULT_BELL_BAG;
                }
                if (!PlayerPockets_CanChangeBells(pockets, talk->price, 1, 0)) {
                    message = (u8) (MainRandom_Below(2) + 18);
                } else if (fit == SCENE_BELLS_FIT_WALLET) {
                    SceneCommand_RequestMotion13(fmb_command_of(talk), &bag, 0, FMB_HAND_OVER, 0);
                    SceneBells_Give((int) (uintptr_t) talk->buyer, talk->price);
                    message = (u8) (MainRandom_Below(2) + 14);
                    FleaMarketBuyerTalk_Buy(talk);
                } else if (fit == SCENE_BELLS_FIT_BAGS) {
                    SceneCommand_RequestMotion13(fmb_command_of(talk), &bag, 0, FMB_HAND_OVER, 0);
                    message = (u8) (MainRandom_Below(2) + 14);
                    SceneBells_Give((int) (uintptr_t) talk->buyer, talk->price);
                    FleaMarketBuyerTalk_Buy(talk);
                }
            } else {
                message = (u8) (MainRandom_Below(2) + 16);
                FleaMarketBuyerTalk_DropItem(talk);
            }
            break;
        default:
            break;
    }
    if (message != FMB_NO_MESSAGE) {
        TalkObject_SetMessage(fmb_talk_object(talk), &message, data_ov004_02257e18);
    }
}
CLEAN_AS(func_ov004_0222050c, FleaMarketBuyerTalk_OnAnswer)

/* func_ov004_022206c0: the item is no longer wanted.
 * QUIRK: answers 0x898, the place of the item in the villager. */
int FleaMarketBuyerTalk_DropItem(FleaMarketBuyerTalk *talk)
{
    talk->buyer->item = FMB_NO_ITEM;
    return (int) offsetof(FleaMarketBuyer, item);
}
CLEAN_AS(func_ov004_022206c0, FleaMarketBuyerTalk_DropItem)

/* func_ov004_022206d8 (the talk scene's receiver slot 0x14, a message ended):
 * - in stages 5 and 3, it says goodbye: stage 6 or 4, and a message 0 to 2 of "q_bye";
 * - else after messages 0 to 2: in stages 6 and 1 the talk ends (message data_021f43e8); in
 *   stage 0, the villager (with a record) flags its memory of the current player (when there is
 *   one), stage 1, 40 frames before it steps in, the talk ends and it steps in (state 1);
 * - after messages 8, 9 and 14 to 19, a request of the bottom screen's panels is cleared. */
void FleaMarketBuyerTalk_OnMessageEnded(FleaMarketBuyerTalk *talk)
{
    u8 stage = talk->buyer->stage;
    if (stage == FMB_STAGE_PLAYER_AT_EXIT || stage == FMB_STAGE_TIME_UP) {
        talk->buyer->stage = stage == FMB_STAGE_PLAYER_AT_EXIT ? FMB_STAGE_PLAYER_AT_EXIT_BYE : FMB_STAGE_TIME_UP_BYE;
        fmb_format_file(talk->buyer, data_ov004_02257e68, data_ov004_02253edc);
        u8 message = (u8) MainRandom_Below(3);
        TalkObject_SetMessage(fmb_talk_object(talk), &message, data_ov004_02257e68);
        return;
    }

    switch (fmb_message_of(talk)) {
        case 0:
        case 1:
        case 2:
            if (stage == FMB_STAGE_PLAYER_AT_EXIT_BYE || stage == FMB_STAGE_GREETED) {
                TalkObject_SetMessage(fmb_talk_object(talk), &data_021f43e8, NULL);
            } else if (stage == FMB_STAGE_CALL) {
                DesignCreator *player = NULL;
                if (PlayerRecords_Current() != NULL) {
                    player = PlayerRecord_Player(PlayerRecords_Current());
                }
                if (fmb_record(talk->buyer) != NULL && player != NULL) {
                    VillagerEntry_FlagMemory(fmb_record(talk->buyer), player);
                }
                talk->buyer->stage = FMB_STAGE_GREETED;
                talk->buyer->step_wait = FMB_GREETED_WAIT;
                TalkObject_SetMessage(fmb_talk_object(talk), &data_021f43e8, NULL);
                FleaMarketBuyer_SetState(talk->buyer, FMB_STATE_GREET);
            }
            break;
        case 8:
        case 9:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            ScreenPanels_ClearRequest(stage);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_022206d8, FleaMarketBuyerTalk_OnMessageEnded)

/* func_ov004_022207fc (vtable slot 0x80): notes its action sound was played. */
FleaMarketBuyer *FleaMarketBuyer_ActionSoundPlayed(FleaMarketBuyer *buyer)
{
    buyer->sound_played = 1;
    return buyer;
}
CLEAN_AS(func_ov004_022207fc, FleaMarketBuyer_ActionSoundPlayed)

/* func_ov004_02220808 (vtable slot 0x7c): its action sound is played outside a room, and in a
 * room until it was once. */
int FleaMarketBuyer_HasActionSound(FleaMarketBuyer *buyer)
{
    return data_020e54a8 != 1 || buyer->sound_played == 0;
}
CLEAN_AS(func_ov004_02220808, FleaMarketBuyer_HasActionSound)

/* func_ov004_02220834 (the talk scene's vtable slot 0x78, the line to say): its memory of the
 * current player (met now if new) is updated with no player, town or date. Then the text is
 * written into data_ov004_02257e40:
 * - stage 5: "q10_wait", a message 0 to 2 at random;
 * - stage 3: "ev_fmarket3", 2 or 3;
 * - stage 0: "q10_call", 0 to 2; stage 1: "ev_fmarket3", 0 or 1;
 * - stage 2: "ev_fmarket3"; with no item wanted or come from walking to it (its state before
 *   is 5), 4 or 5; else the item's name is the talk's value 0, and 6 or 7;
 * - another stage leaves the message as it is. */
void FleaMarketBuyerTalk_Line(FleaMarketBuyerTalk *talk, VillagerTalkLine *out)
{
    VillagerMemory *memory = VillagerMemory_Meet(fmb_record(talk->buyer), PlayerRecord_Player(PlayerRecords_Current()));
    if (memory != NULL) {
        VillagerMemoryEntry_Update(memory, NULL, NULL, NULL);
    }

    FleaMarketBuyer *buyer = talk->buyer;
    switch (buyer->stage) {
        case FMB_STAGE_PLAYER_AT_EXIT:
            fmb_format_file(buyer, data_ov004_02257e40, data_ov004_02253ee4);
            out->text = (u32) (uintptr_t) data_ov004_02257e40;
            out->message = (u8) MainRandom_Below(3);
            return;
        case FMB_STAGE_TIME_UP:
            fmb_format_file(buyer, data_ov004_02257e40, data_ov004_02253ed0);
            out->text = (u32) (uintptr_t) data_ov004_02257e40;
            out->message = (u8) (MainRandom_Below(2) + 2);
            return;
        case FMB_STAGE_CALL:
            fmb_format_file(buyer, data_ov004_02257e40, data_ov004_02253ef0);
            out->message = (u8) MainRandom_Below(3);
            break;
        case FMB_STAGE_GREETED:
            fmb_format_file(buyer, data_ov004_02257e40, data_ov004_02253ed0);
            out->message = (u8) MainRandom_Below(2);
            break;
        case FMB_STAGE_BROWSE:
            fmb_format_file(buyer, data_ov004_02257e40, data_ov004_02253ed0);
            if (fmb_item_is(&talk->buyer->item, FMB_NO_ITEM) || talk->buyer->previous_state == FMB_STATE_GO) {
                out->message = (u8) (MainRandom_Below(2) + 4);
            } else {
                SceneBase_PutItemName(fmb_scene_of(talk), (int) (uintptr_t) &talk->buyer->item, 0, FMB_ITEM_NAME_KIND);
                out->message = (u8) (MainRandom_Below(2) + 6);
            }
            break;
        default:
            break;
    }
    out->text = (u32) (uintptr_t) data_ov004_02257e40;
}
CLEAN_AS(func_ov004_02220834, FleaMarketBuyerTalk_Line)

/* func_ov004_022209b4: the item it wants is bought, unless it is none or its object is none: a
 * villager with an id (TownVillager_NpcId) notes the item in a memory it may reuse (when there is
 * one) and adds it to its items; the room object is taken away, no object or item is wanted,
 * one more item is bought and its last chosen objects are cleared. */
void FleaMarketBuyerTalk_Buy(FleaMarketBuyerTalk *talk)
{
    if (fmb_item_is(&talk->buyer->item, FMB_NO_ITEM)) {
        return;
    }
    FleaMarketBuyer *buyer = talk->buyer;
    if (buyer->object == -1) {
        return;
    }
    if (TownVillager_NpcId(fmb_record(buyer)) != NULL) {
        VillagerMemory *memory = VillagerMemory_Reusable(fmb_record(talk->buyer));
        if (memory != NULL) {
            VillagerMemoryEntry_SetItem(memory, &talk->buyer->item);
        }
        VillagerItems_Add(fmb_record(talk->buyer), &talk->buyer->item);
    }
    func_ov004_0223bb14(talk->buyer->object);
    talk->buyer->object = -1;
    talk->buyer->item = FMB_NO_ITEM;
    talk->buyer->bought++;
    for (int i = 0; i < FLEA_MARKET_BUYER_RECENT; i++) {
        talk->buyer->recent[i] = FMB_NO_RECENT;
    }
}
CLEAN_AS(func_ov004_022209b4, FleaMarketBuyerTalk_Buy)

/* `n` in 20.12 as the ROM makes it: through a float, adding 0.5 away from zero and truncating.
 * That is n << 12 (kept to 32 bits), except where the shift wraps to the other sign below 2^23
 * in size.
 * QUIRK: an integer is converted through a float. */
static fx32 fmb_fx_from_int(int n)
{
    s32 shifted = (s32) ((u32) n << 12);
    if (n > 0 && shifted < 0 && shifted > -(1 << 23)) {
        return shifted + 1;
    }
    if (n <= 0 && shifted > 0 && shifted < (1 << 23)) {
        return shifted - 1;
    }
    return shifted;
}

/* func_ov004_02220aa8 (step 1 of its talk, the offer, once the price was asked): the price is 0.
 * Nothing more while the screen's overlay group cannot be opened. When the screen was answered
 * (GroupParams_C4CIs1) and an item is wanted: the most it pays is the item's price times
 * (0xff + fondness) / 0x200, its fondness of the player being 0 without a current player or
 * memory, and at least 10; the price asked (GroupParams_C78) becomes the talk's value 0. Above
 * the most, message 10 or 11; else that is the price, the bottom screen's panels are asked for
 * and message 12 or 13. Otherwise message 8 or 9. All from "ev_fmarket3"; the step is 0 after. */
void FleaMarketBuyerTalk_Offer(FleaMarketBuyerTalk *talk)
{
    TalkObject *talk_object = fmb_talk_object(talk);
    u8 message = (u8) (MainRandom_Below(2) + 8);

    talk->price = 0;
    if (!GroupParams_CanOpen()) {
        return;
    }
    if (GroupParams_C4CIs1()) {
        VillagerMemory *memory = NULL;
        int fondness = 0;
        if (!fmb_item_is(&talk->buyer->item, FMB_NO_ITEM)) {
            talk->price = ItemTraits_Price(&talk->buyer->item);
            if (PlayerRecords_Current() != NULL) {
                memory = VillagerMemory_Of(fmb_record(talk->buyer), PlayerRecord_Player(PlayerRecords_Current()));
            }
            if (memory != NULL) {
                fondness = VillagerMemoryEntry_Fondness(memory);
            }
            fx32 share = FX_Div(fmb_fx_from_int(fondness + FMB_BASE_FONDNESS), FMB_PRICE_DIVISOR);
            SceneBase_PutValue(fmb_scene_of(talk), GroupParams_C78(), FMB_PRICE_SLOT, FMB_PRICE_FORMAT, 0, 0);
            int most = FX_MulFunc(talk->price, share);
            if (most <= FMB_MIN_PRICE) {
                most = FMB_MIN_PRICE;
            }
            if (GroupParams_C78() > most) {
                message = (u8) (MainRandom_Below(2) + 10);
            } else {
                talk->price = GroupParams_C78();
                message = (u8) (MainRandom_Below(2) + 12);
                ScreenPanels_Request();
            }
        }
    }
    fmb_format_file(talk->buyer, data_ov004_02257df0, data_ov004_02253ed0);
    TalkObject_SetMessage(talk_object, &message, data_ov004_02257df0);
    FleaMarketBuyerTalk_SetStep(talk, FMB_TALK_STEP_NONE);
}
CLEAN_AS(func_ov004_02220aa8, FleaMarketBuyerTalk_Offer)

/* func_ov004_02220c34: the step of its talk to run. */
void FleaMarketBuyerTalk_SetStep(FleaMarketBuyerTalk *talk, int step)
{
    talk->step = step;
}
CLEAN_AS(func_ov004_02220c34, FleaMarketBuyerTalk_SetStep)

/* func_ov004_02220c40 (the talk scene's vtable slot 0x84, its command ended): the talk's step,
 * when it is one to run then and has a function, run once; the step is 0 after.
 * REQUIRES: the step is 0 or 1. */
void FleaMarketBuyerTalk_OnCommandEnd(FleaMarketBuyerTalk *talk)
{
    const FleaMarketBuyerTalkStep *step = &data_ov004_02257dd8[talk->step];
    if (step->before_each == 0 && step->member.function != 0) {
        MemberPointer_CallVoid(&step->member, talk);
        FleaMarketBuyerTalk_SetStep(talk, FMB_TALK_STEP_NONE);
    }
}
CLEAN_AS(func_ov004_02220c40, FleaMarketBuyerTalk_OnCommandEnd)

/* func_ov004_02220c94 (the talk scene's vtable slot 0x80, before each of its steps): the talk's
 * step run when it is one to run then and has a function.
 * REQUIRES: the step is 0 or 1. */
void FleaMarketBuyerTalk_BeforeStep(FleaMarketBuyerTalk *talk)
{
    const FleaMarketBuyerTalkStep *step = &data_ov004_02257dd8[talk->step];
    if (step->before_each != 0 && step->member.function != 0) {
        MemberPointer_CallVoid(&step->member, talk);
    }
}
CLEAN_AS(func_ov004_02220c94, FleaMarketBuyerTalk_BeforeStep)

/* The lines table VillagerTalkScene_Start is given: 17 and above leave the line members as they
 * are (the talk scene's own vtable slot 0x78 says the line). */
#define FMB_TALK_OWN_LINES 0x11

/* func_ov004_02220cdc: its talk scene told through its vtable slot 0x08, started for `buyer` and
 * kept pointing back at it. */
void FleaMarketBuyerTalk_Start(FleaMarketBuyerTalk *talk, FleaMarketBuyer *buyer)
{
    fmb_talk_slot_08(talk);
    VillagerTalkScene_Start(&talk->base, buyer->base, FMB_TALK_OWN_LINES);
    talk->buyer = buyer;
}
CLEAN_AS(func_ov004_02220cdc, FleaMarketBuyerTalk_Start)

/* func_ov004_02220d04 (the talk scene's vtable slot 0x04, its deleting destructor). */
FleaMarketBuyerTalk *FleaMarketBuyerTalk_Delete(FleaMarketBuyerTalk *talk)
{
    talk->base.scene.vtable = data_ov004_02253d80;
    VillagerTalkScene_DestructBody(&talk->base);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_02220d04, FleaMarketBuyerTalk_Delete)

/* func_ov004_02220d24 (the talk scene's vtable slot 0x00, its destructor). */
FleaMarketBuyerTalk *FleaMarketBuyerTalk_Destroy(FleaMarketBuyerTalk *talk)
{
    talk->base.scene.vtable = data_ov004_02253d80;
    VillagerTalkScene_DestructBody(&talk->base);
    return talk;
}
CLEAN_AS(func_ov004_02220d24, FleaMarketBuyerTalk_Destroy)

/* func_ov004_02220d3c: its talk scene's constructor. */
FleaMarketBuyerTalk *FleaMarketBuyerTalk_Construct(FleaMarketBuyerTalk *talk)
{
    VillagerTalkScene_ConstructAlt(&talk->base);
    talk->base.scene.vtable = data_ov004_02253d80;
    return talk;
}
CLEAN_AS(func_ov004_02220d3c, FleaMarketBuyerTalk_Construct)

/* func_ov004_02220d54 (state 8's update): nothing. 1. */
int FleaMarketBuyer_UpdateDone(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02220d54, FleaMarketBuyer_UpdateDone)

/* func_ov004_02220d58 (state 8's entry): nothing. 1. */
int FleaMarketBuyer_EnterDone(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02220d58, FleaMarketBuyer_EnterDone)

/* func_ov004_02220d5c (state 6's update): while its talk's countdown runs, it turns to the
 * talk's partner and talks (the camera kept) when the countdown is at 1, and counts down. Then
 * the time is its last talk's, and once its action is idle the object's event ends, a greeted
 * villager starts looking about (stage 2, its frames 0) and it is done (state 8). 1. */
int FleaMarketBuyer_UpdateTalk(FleaMarketBuyer *buyer)
{
    u8 wait = buyer->talk_wait;
    if (wait != 0) {
        if (wait == 1) {
            fmb_turn_and_talk(buyer, 1);
        }
        Countdown_Tick8(&buyer->talk_wait);
        return 1;
    }
    DateTime_Now(&buyer->talk_time);
    if (SceneAction_IsBusy(fmb_action_of(buyer)) == 0) {
        EventQueue_FinishObjectEvent(buyer);
        if (buyer->stage == FMB_STAGE_GREETED) {
            buyer->stage = FMB_STAGE_BROWSE;
            buyer->browse_frames = 0;
        }
        FleaMarketBuyer_SetState(buyer, FMB_STATE_DONE);
    }
    return 1;
}
CLEAN_AS(func_ov004_02220d5c, FleaMarketBuyer_UpdateTalk)

/* func_ov004_02220df4 (state 6's entry): no leaving countdown; past stage 0 it turns to the
 * talk's partner and talks. 1.
 * QUIRK: the turn to the partner is worked out in stage 0 too. */
int FleaMarketBuyer_EnterTalk(FleaMarketBuyer *buyer)
{
    int partner = SceneBase_MotionArg(fmb_scene_of(&buyer->talk));
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(buyer->base, (u8 *) (uintptr_t) partner);
    }
    buyer->leave_wait = 0;
    if (buyer->stage != FMB_STAGE_CALL) {
        SceneAction_RequestTurnAndTalk(fmb_action_of(buyer), 0, angle, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_02220df4, FleaMarketBuyer_EnterTalk)

/* func_ov004_02220e40 (state 7's update): once its action is idle it takes the room's way out
 * into main's entry record: in stage 5 exit 0 (the player leaves with it), else the player's
 * place is saved and exit 6 taken; it is done (state 8). 1.
 * QUIRK: the player's position is fetched and not used. */
int FleaMarketBuyer_UpdateBye(FleaMarketBuyer *buyer)
{
    (void) PlayerActorOps_StartPosition(FMB_PLAYER_ACTOR);
    if (SceneAction_IsBusy(fmb_action_of(buyer)) == 0) {
        if (buyer->stage == FMB_STAGE_PLAYER_AT_EXIT) {
            SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), FMB_EXIT_WITH_PLAYER);
        } else {
            ScenePlace_SavePlayer(SceneTables_EntryRecord(), 0);
            SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), FMB_EXIT_ALONE);
        }
        FleaMarketBuyer_SetState(buyer, FMB_STATE_DONE);
    }
    return 1;
}
CLEAN_AS(func_ov004_02220e40, FleaMarketBuyer_UpdateBye)

/* func_ov004_02220ea8 (state 7's entry): it turns to the talk's partner and talks, the camera
 * kept. 1. */
int FleaMarketBuyer_EnterBye(FleaMarketBuyer *buyer)
{
    fmb_turn_and_talk(buyer, 1);
    return 1;
}
CLEAN_AS(func_ov004_02220ea8, FleaMarketBuyer_EnterBye)

/* func_ov004_02220ee0 (state 5's update): nothing more when it asks to leave. It steps along the
 * paths to the item's centre, running when farther than its reach and 0x1000 (a walk becomes a
 * run and a run a walk); within its reach or with no step to take it browses (state 3). Then the
 * object on the tile 0x2000 ahead of it, first on layer 1 then on layer 0, becomes the item
 * when it may buy it. 1. */
int FleaMarketBuyer_UpdateGo(FleaMarketBuyer *buyer)
{
    if (FleaMarketBuyer_CheckLeave(buyer) != 0) {
        return 1;
    }
    Actor *actor = fmb_actor_of(buyer);
    int distance = Vec_DistanceXZ(&actor->position, &buyer->target);
    Vec3 step;
    ScenePathStep_Choose(&step, buyer->base, &buyer->target);
    if (distance > buyer->reach + FMB_RUN_MARGIN) {
        if (SceneMotion_Kind(fmb_motion_of(buyer)) == FMB_MOTION_WALK) {
            fmb_request_motion(buyer, FMB_MOTION_RUN, FMB_RUN_RATE, 0);
        }
    } else if (SceneMotion_Kind(fmb_motion_of(buyer)) == FMB_MOTION_RUN) {
        fmb_request_motion(buyer, FMB_MOTION_WALK, 0, 0);
    }
    SceneMover_SetStart(fmb_mover_of(buyer), &step);
    if (distance <= buyer->reach || Vec_Equal(&step, &actor->position)) {
        FleaMarketBuyer_SetState(buyer, FMB_STATE_BROWSE);
    }

    Vec3 ahead = actor->position;
    int index = ((u16) actor->angle[1] >> FMB_SIN_SHIFT) * 2;
    int x = 0;
    int z = 0;
    ahead.x += FX_MulFunc(FMB_AHEAD, FX_SinCosTable_[index]);
    ahead.z += FX_MulFunc(FMB_AHEAD, FX_SinCosTable_[index + 1]);
    Position_Tile(&x, &z, (const Position *) (const void *) &ahead);
    int floor = func_ov004_0223cc5c(func_ov004_0223cd50(), x, z, 0);
    int top = func_ov004_0223cc5c(func_ov004_0223cd50(), x, z, 1);
    if (FleaMarketBuyer_MayBuy(buyer, top)) {
        fmb_choose(buyer, top);
    } else if (FleaMarketBuyer_MayBuy(buyer, floor)) {
        fmb_choose(buyer, floor);
    }
    return 1;
}
CLEAN_AS(func_ov004_02220ee0, FleaMarketBuyer_UpdateGo)

/* func_ov004_022210c8 (state 5's entry): a walk. 1. */
int FleaMarketBuyer_EnterGo(FleaMarketBuyer *buyer)
{
    fmb_request_motion(buyer, FMB_MOTION_WALK, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_022210c8, FleaMarketBuyer_EnterGo)

/* func_ov004_022210fc (state 4's update): nothing more when it asks to leave; with its turn done
 * it browses (state 3). 1. */
int FleaMarketBuyer_UpdateFace(FleaMarketBuyer *buyer)
{
    if (FleaMarketBuyer_CheckLeave(buyer) != 0) {
        return 1;
    }
    if (SceneMotion_Kind(fmb_motion_of(buyer)) == FMB_MOTION_TURN && SceneMotion_IsDone(fmb_motion_of(buyer))) {
        FleaMarketBuyer_SetState(buyer, FMB_STATE_BROWSE);
    }
    return 1;
}
CLEAN_AS(func_ov004_022210fc, FleaMarketBuyer_UpdateFace)

/* func_ov004_02221138 (state 4's entry): a turn to the item's centre. 1.
 * QUIRK: its distance to the item and its step towards it are worked out and not used. */
int FleaMarketBuyer_EnterFace(FleaMarketBuyer *buyer)
{
    Actor *actor = fmb_actor_of(buyer);
    Vec3 step;
    Vec_DistanceXZ(&actor->position, &buyer->target);
    ScenePathStep_Choose(&step, buyer->base, &buyer->target);
    fmb_request_motion(buyer, FMB_MOTION_TURN, 0, Vec_YawTo(&actor->position, &buyer->target));
    return 1;
}
CLEAN_AS(func_ov004_02221138, FleaMarketBuyer_EnterFace)

/* func_ov004_02221198 (state 3's update): nothing more when it asks to leave or before stage 2.
 * With an item wanted (FleaMarketBuyer_PickItem): farther than its reach with a step to take
 * towards it, it goes to it (state 5); else turned away from it by more than 0x2000 it turns to
 * it (state 4). 1. */
int FleaMarketBuyer_UpdateBrowse(FleaMarketBuyer *buyer)
{
    if (FleaMarketBuyer_CheckLeave(buyer) != 0) {
        return 1;
    }
    if (buyer->stage != FMB_STAGE_BROWSE) {
        return 1;
    }
    if (FleaMarketBuyer_PickItem(buyer)) {
        Actor *actor = fmb_actor_of(buyer);
        int distance = Vec_DistanceXZ(&actor->position, &buyer->target);
        Vec3 step;
        ScenePathStep_Choose(&step, buyer->base, &buyer->target);
        int yaw = actor->angle[1];
        int away = Math_AbsDiff16(yaw, Vec_YawTo(&actor->position, &buyer->target));
        if (distance > buyer->reach && Vec_Differ(&step, &actor->position)) {
            FleaMarketBuyer_SetState(buyer, FMB_STATE_GO);
        } else if (away > FMB_TURN_ANGLE) {
            FleaMarketBuyer_SetState(buyer, FMB_STATE_FACE);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02221198, FleaMarketBuyer_UpdateBrowse)

/* func_ov004_0222123c (state 3's entry): it stands. 1. */
int FleaMarketBuyer_EnterBrowse(FleaMarketBuyer *buyer)
{
    fmb_request_motion(buyer, FMB_MOTION_STAND, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0222123c, FleaMarketBuyer_EnterBrowse)

/* func_ov004_02221270 (state 2's update): it faces into the room (its angles and its movement's
 * angles (0, 0x8000, 0)). On the first frame it walks 0x4000 ahead (priority 2) and waits 30
 * frames; when the wait comes down to 1 it stands (priority 2), the object's event ends and it is
 * done (state 8). 1. */
int FleaMarketBuyer_UpdateStepIn(FleaMarketBuyer *buyer)
{
    Actor *actor = fmb_actor_of(buyer);
    actor->angle[0] = 0;
    actor->angle[1] = FMB_INTO_ROOM_YAW;
    actor->angle[2] = 0;
    actor->move_angle[0] = 0;
    actor->move_angle[1] = FMB_INTO_ROOM_YAW;
    actor->move_angle[2] = 0;

    u8 wait = buyer->step_wait;
    if (wait == 1) {
        SceneMotion_Request(fmb_motion_of(buyer), FMB_MOTION_STAND, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        EventQueue_FinishObjectEvent(buyer);
        FleaMarketBuyer_SetState(buyer, FMB_STATE_DONE);
        return 1;
    }
    if (wait == 0) {
        int index = ((u16) actor->angle[1] >> FMB_SIN_SHIFT) * 2;
        int x = FX_MulFunc(FMB_STEP_IN, FX_SinCosTable_[index]) + actor->position.x;
        int z = FX_MulFunc(FMB_STEP_IN, FX_SinCosTable_[index + 1]) + actor->position.z;
        SceneMotion_Request(fmb_motion_of(buyer), FMB_MOTION_WALK, 2, x, z, 0, 0, 0, 0, data_020c80f8, 0);
        buyer->step_wait = FMB_STEP_IN_FRAMES;
        return 1;
    }
    buyer->step_wait = (u8) (wait - 1);
    return 1;
}
CLEAN_AS(func_ov004_02221270, FleaMarketBuyer_UpdateStepIn)

/* func_ov004_0222136c (state 2's entry): no wait. 1. */
int FleaMarketBuyer_EnterStepIn(FleaMarketBuyer *buyer)
{
    buyer->step_wait = 0;
    return 1;
}
CLEAN_AS(func_ov004_0222136c, FleaMarketBuyer_EnterStepIn)

/* The parts of the town villager scene object used by its start, greeting and set-up. */
#define FMB_LOOK 0x3b0      /* SceneLook */
#define FMB_SOUND 0x514     /* SoundEmitter */
#define FMB_FOOTSTEPS 0x558 /* Footsteps */
/* Its vtable slot giving its town record. */
#define FMB_SLOT_RECORD 0x64

/* State 0: the frames between its tries to knock, the chance of a try (it knocks when a draw
 * below 101 is 25 or less), how far from it the player must be, its knock's sound, and the
 * frames it asks for its event after a knock. */
#define FMB_CALL_WAIT 100
#define FMB_CALL_DRAWS 0x65
#define FMB_CALL_CHANCE 0x19
#define FMB_CALL_DISTANCE 0x8000
#define FMB_KNOCK_SOUND 0x4ca
#define FMB_KNOCK_FRAMES 0x1e
/* Its sounds' volume. */
#define FMB_SOUND_VOLUME 0x7f
/* State 1: the sound of its greeting, the frame of its wait it is put in place at, and where. */
#define FMB_GREETING_SOUND 0x4cb
#define FMB_PLACE_FRAME 8
#define FMB_PLACE_X 0x10000
#define FMB_PLACE_Z 0x1f000
/* Where it waits to call the player, at the room's way in. */
#define FMB_DOOR_X 0x10000
#define FMB_DOOR_Z 0x23000
/* The state of the villager's state entry set when it starts (VillagerState_SetState), and
 * the index VillagerState_SetIndex164 is given when it leaves in stage 4 or 6 (none). */
#define FMB_VILLAGER_STATE_VISITING 2
#define FMB_NO_INDEX 0xff
/* Its states 0 and 2 (FleaMarketBuyer_SetState). */
#define FMB_STATE_CALL 0
#define FMB_STATE_STEP_IN 2
/* The talk FleaMarketBuyer_UpdateGreet waits on. */
#define FMB_TALK_INDEX 0

/* The functions of its states (filled at start-up by __sinit_ov004_0224e484): 0 to 7, and 8
 * right after them (data_ov004_02257f10). */
extern FleaMarketBuyerStep data_ov004_02257e90[FLEA_MARKET_BUYER_STATES];

/* Its town record, through its vtable slot 0x64. */
static u8 *fmb_record_virtual(FleaMarketBuyer *buyer)
{
    u32 vtable = *(const u32 *) (const void *) buyer->base;
    u32 code = *(const u32 *) (uintptr_t) (vtable + FMB_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *))(uintptr_t) code)(buyer->base);
}

/* Its position and the one at the start of the frame set to (x, z), the height kept. */
static void fmb_place(FleaMarketBuyer *buyer, fx32 x, fx32 z)
{
    Actor *actor = fmb_actor_of(buyer);
    actor->position.x = x;
    actor->last_position.x = x;
    actor->position.z = z;
    actor->last_position.z = z;
}

/* func_ov004_0222137c (state 1's update): nothing while talk 0 is open. With 40 frames of its
 * wait left it plays its greeting (FleaMarketBuyer_PlayGreeting). It faces into the room (its
 * angles and its movement's angles (0, 0x8000, 0)) and its wait counts down: at 8 it is put at
 * (0x10000, 0x1f000); at 0 it steps in (state 2). 1. */
int FleaMarketBuyer_UpdateGreet(FleaMarketBuyer *buyer)
{
    TalkObject *talk = TalkObject_Get(FMB_TALK_INDEX);
    if (talk != NULL && talk->state != TALK_OBJECT_CLOSED) {
        return 1;
    }
    if (buyer->step_wait == FMB_GREETED_WAIT) {
        FleaMarketBuyer_PlayGreeting(buyer);
    }
    Actor *actor = fmb_actor_of(buyer);
    actor->angle[0] = 0;
    actor->angle[1] = FMB_INTO_ROOM_YAW;
    actor->angle[2] = 0;
    actor->move_angle[0] = 0;
    actor->move_angle[1] = FMB_INTO_ROOM_YAW;
    actor->move_angle[2] = 0;
    if (Countdown_Tick8(&buyer->step_wait) != 0) {
        if (buyer->step_wait == FMB_PLACE_FRAME) {
            fmb_place(buyer, FMB_PLACE_X, FMB_PLACE_Z);
        }
        return 1;
    }
    FleaMarketBuyer_SetState(buyer, FMB_STATE_STEP_IN);
    return 1;
}
CLEAN_AS(func_ov004_0222137c, FleaMarketBuyer_UpdateGreet)

/* func_ov004_02221410 (state 1's entry): it stands. 1. */
int FleaMarketBuyer_EnterGreet(FleaMarketBuyer *buyer)
{
    fmb_request_motion(buyer, FMB_MOTION_STAND, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_02221410, FleaMarketBuyer_EnterGreet)

/* func_ov004_02221444 (state 0's update): while it is not knocking, the wait between its tries
 * (byte 0xadf) counts down; at 0, three draws in four (above 25 of 0 to 100) wait another 100
 * frames; else, with this console's player's field actor farther than 0x8000 from it, it knocks
 * (sound 0x4ca) and knocks for 30 frames. While it knocks, its event (kind 6) is asked for each
 * frame and the count goes down to 1 (it stays there). 1.
 * QUIRK: with no field actor of the player, or the player near, the wait stays 0 and the next
 * frame draws again. */
int FleaMarketBuyer_UpdateCall(FleaMarketBuyer *buyer)
{
    if (buyer->talk_wait == 0) {
        if (Countdown_Tick8(&buyer->unk_adf) != 0) {
            return 1;
        }
        if (MainRandom_Below(FMB_CALL_DRAWS) > FMB_CALL_CHANCE) {
            buyer->unk_adf = FMB_CALL_WAIT;
            return 1;
        }
        const Actor *player = SessionPlayers_ActorOf(FMB_PLAYER_ACTOR);
        if (player != NULL) {
            Vec3 at = player->position;
            if (Vec_DistanceXZ(&at, &fmb_actor_of(buyer)->position) > FMB_CALL_DISTANCE) {
                SoundEmitter_PlayB((SoundEmitter *) (void *) fmb_part(buyer, FMB_SOUND), FMB_KNOCK_SOUND, FMB_SOUND_VOLUME, 0);
                buyer->talk_wait = FMB_KNOCK_FRAMES;
            }
        }
    }
    if (buyer->talk_wait != 0) {
        EventQueue_RequestKind6(buyer, 0);
        if (buyer->talk_wait > 1) {
            Countdown_Tick8(&buyer->talk_wait);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02221444, FleaMarketBuyer_UpdateCall)

/* func_ov004_022214f0 (state 0's entry): its visit at stage 0, and it stands. 1. */
int FleaMarketBuyer_EnterCall(FleaMarketBuyer *buyer)
{
    buyer->stage = FMB_STAGE_CALL;
    fmb_request_motion(buyer, FMB_MOTION_STAND, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_022214f0, FleaMarketBuyer_EnterCall)

/* func_ov004_0222152c: its greeting: the sound 0x4cb, then the scene's sound
 * (Block020b220c_PlaySceneSound). */
void FleaMarketBuyer_PlayGreeting(FleaMarketBuyer *buyer)
{
    SoundEmitter_PlayB((SoundEmitter *) (void *) fmb_part(buyer, FMB_SOUND), FMB_GREETING_SOUND, FMB_SOUND_VOLUME, 0);
    Block020b220c_PlaySceneSound();
}
CLEAN_AS(func_ov004_0222152c, FleaMarketBuyer_PlayGreeting)

/* func_ov004_02221550: state `state` taken when its entry function, if it has one, answers
 * nonzero; the state before is kept.
 * REQUIRES: `state` is 0 to 8 (the table is not bounded). */
void FleaMarketBuyer_SetState(FleaMarketBuyer *buyer, int state)
{
    const FleaMarketBuyerStep *step = &data_ov004_02257e90[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, buyer);
    }
    if (taken != 0) {
        buyer->previous_state = buyer->state;
        buyer->state = state;
    }
}
CLEAN_AS(func_ov004_02221550, FleaMarketBuyer_SetState)

/* func_ov004_022215a0 (vtable slot 0x68, its update): its state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: its state is 0 to 8. */
int FleaMarketBuyer_RunState(FleaMarketBuyer *buyer)
{
    const FleaMarketBuyerStep *step = &data_ov004_02257e90[(u32) buyer->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, buyer);
}
CLEAN_AS(func_ov004_022215a0, FleaMarketBuyer_RunState)

/* func_ov004_022215ec (vtable slot 0x24, the drawing): drawn once past stage 0 (calling at the
 * way in it is not seen). 1. */
int FleaMarketBuyer_Draw(FleaMarketBuyer *buyer)
{
    if (buyer->stage != FMB_STAGE_CALL) {
        SceneObject_Draw(buyer->base);
    }
    return 1;
}
CLEAN_AS(func_ov004_022215ec, FleaMarketBuyer_Draw)

/* func_ov004_02221608 (vtable slot 0x0c): the town villager's leaving; when it agrees: leaving
 * after its goodbye (stage 4 or 6) the town's extra visitors are cleared and the index of
 * VillagerState_SetIndex164 set to none; with a town record (asked twice), its state entry is
 * settled. Whether it agreed. */
int FleaMarketBuyer_Leave(FleaMarketBuyer *buyer)
{
    if (VillagerSceneObject_Leave(buyer->base) == 0) {
        return 0;
    }
    if (buyer->stage == FMB_STAGE_PLAYER_AT_EXIT_BYE || buyer->stage == FMB_STAGE_TIME_UP_BYE) {
        TownObjects_ClearExtraVisitors();
        VillagerState_SetIndex164(FMB_NO_INDEX);
    }
    if (fmb_record_virtual(buyer) != NULL) {
        VillagerState_SettleState(VillagerStatus_StateEntry(fmb_record_virtual(buyer)));
    }
    return 1;
}
CLEAN_AS(func_ov004_02221608, FleaMarketBuyer_Leave)

/* Whether `player` (the current player's, NULL without one) is set and known to the villager
 * with bit 14 of its memory of them. Its town record is asked of its vtable at each step. */
static int fmb_player_known(FleaMarketBuyer *buyer, DesignCreator *player)
{
    if (fmb_record_virtual(buyer) == NULL || player == NULL || PlayerId_IsSet(player) == 0) {
        return 0;
    }
    if (VillagerMemory_Of(fmb_record_virtual(buyer), player) == NULL) {
        return 0;
    }
    return VillagerMemoryBits_Bit14(VillagerMemory_Of(fmb_record_virtual(buyer), player)) != 0;
}

/* func_ov004_02221658 (vtable slot 0x00, its start): the town villager's start; then no item is
 * wanted, its footsteps are on, the item's centre is its position, its reach 0x3000, its recent
 * objects cleared and its look locked. When the previous scene is one SceneQuery_Is31 names, or
 * the current player is known to it (fmb_player_known), it is in the room already: the room's
 * objects are counted, the town's extra visitors set, the collision map's claim set to 0, the
 * room notes a villager of the flea market (func_ov004_0223d33c), the time is its last talk's
 * and it browses (stage 2, state 3). Else it waits at the way in, (0x10000, 0x23000), to call
 * (its first try in 100 frames, its frames of looking about counted, state 0). With a town
 * record, its state entry is set to state 2. Whether the start was done. */
int FleaMarketBuyer_Start(FleaMarketBuyer *buyer)
{
    if (VillagerSceneObject_Start(buyer->base) == 0) {
        return 0;
    }
    buyer->item = FMB_NO_ITEM;
    Footsteps_Enable((Footsteps *) (void *) fmb_part(buyer, FMB_FOOTSTEPS));
    buyer->target = fmb_actor_of(buyer)->position;
    buyer->reach = FMB_REACH_SMALL;
    for (int i = 0; i < FLEA_MARKET_BUYER_RECENT; i++) {
        buyer->recent[i] = FMB_NO_RECENT;
    }
    SceneLook_Lock((SceneLook *) (void *) fmb_part(buyer, FMB_LOOK));

    DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    if (SceneQuery_Is31(SceneQuery_Previous()) != 0 || fmb_player_known(buyer, player)) {
        buyer->object_count = func_ov004_0223cdc0(func_ov004_0223ce84());
        TownObjects_SetExtraVisitors();
        CollisionMap_Claim(0);
        func_ov004_0223d33c();
        DateTime_Now(&buyer->talk_time);
        buyer->stage = FMB_STAGE_BROWSE;
        FleaMarketBuyer_SetState(buyer, FMB_STATE_BROWSE);
    } else {
        fmb_place(buyer, FMB_DOOR_X, FMB_DOOR_Z);
        buyer->unk_adf = FMB_CALL_WAIT;
        buyer->browse_frames = 1;
        FleaMarketBuyer_SetState(buyer, FMB_STATE_CALL);
    }
    if (fmb_record_virtual(buyer) != NULL) {
        VillagerState_SetState(VillagerStatus_StateEntry(fmb_record_virtual(buyer)), FMB_VILLAGER_STATE_VISITING);
    }
    return 1;
}
CLEAN_AS(func_ov004_02221658, FleaMarketBuyer_Start)

/* func_ov004_022217cc (vtable slot 0x04, its set-up): the town villager's set-up; then its talk
 * scene becomes its scene and is started (FleaMarketBuyerTalk_Start). Whether the set-up was
 * done. */
int FleaMarketBuyer_Init(FleaMarketBuyer *buyer)
{
    if (VillagerSceneObject_Init(buyer->base) == 0) {
        return 0;
    }
    SceneObject_SetScene(buyer->base, fmb_scene_of(&buyer->talk));
    FleaMarketBuyerTalk_Start(&buyer->talk, buyer);
    return 1;
}
CLEAN_AS(func_ov004_022217cc, FleaMarketBuyer_Init)

/* func_ov004_022217fc (its entry in the overlay's table of profiles, data_ov004_02253d60):
 * allocates (zeroed) and builds a villager: the town villager scene object, no item wanted, its talk
 * scene, and no last talk. */
FleaMarketBuyer *FleaMarketBuyer_New(void)
{
    FleaMarketBuyer *buyer = Heap_AllocAuxZeroed(sizeof(FleaMarketBuyer));
    if (buyer != NULL) {
        VillagerSceneObject_Construct(buyer->base);
        *(const u8 **) (void *) buyer->base = data_ov004_02253e10;
        buyer->item = FMB_NO_ITEM;
        FleaMarketBuyerTalk_Construct(&buyer->talk);
        buyer->talk_time = (DateTime){0};
    }
    return buyer;
}
CLEAN_AS(func_ov004_022217fc, FleaMarketBuyer_New)
