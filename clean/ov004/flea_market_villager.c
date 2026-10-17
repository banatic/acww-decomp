/* The villager of a house at the flea market (flea_market_villager.h). */
#include "flea_market_villager.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_templates.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/collision_map.h"
#include "main/current_pockets.h"
#include "main/event_queue.h"
#include "main/footsteps.h"
#include "main/item_code.h"
#include "main/item_traits.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/npc_id.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_bells.h"
#include "main/scene_exit.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_path_step.h"
#include "main/scene_object.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/screen_panels.h"
#include "main/session_players.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/touch_pick_shapes.h"
#include "main/town_villager.h"
#include "main/villager_house_items.h"
#include "main/villager_memories.h"
#include "main/villager_memory_entry.h"
#include "main/villager_scene_slots.h"
#include "main/villager_talk_scene.h"
#include "room_object.h"
#include "room_object_body.h"
#include "room_object_methods.h"

static_assert(sizeof(FleaMarketTalk) == 0x1ac, "its talk scene");
static_assert(offsetof(FleaMarketVillager, item) == 0x898, "item");
static_assert(offsetof(FleaMarketVillager, tile) == 0x89c, "tile");
static_assert(offsetof(FleaMarketVillager, talk) == 0x8a8, "talk scene");
static_assert(offsetof(FleaMarketVillager, talk.price) == 0xa50, "price");
static_assert(offsetof(FleaMarketVillager, stage) == 0xa54, "stage");
static_assert(offsetof(FleaMarketVillager, sound_played) == 0xa56, "sound played");
static_assert(offsetof(FleaMarketVillager, spots) == 0xa58, "spots");
static_assert(offsetof(FleaMarketVillager, spot_count) == 0xa5c, "spot count");
static_assert(offsetof(FleaMarketVillager, state) == 0x8a4, "state");
static_assert(offsetof(FleaMarketVillager, walk_wait) == 0xa55, "walk wait");
static_assert(sizeof(FleaMarketVillagerStep) == 0x10, "a state's functions");
static_assert(sizeof(FleaMarketVillager) == 0xa60, "the size func_ov004_0221ff70 allocates");

/* The parts of the town villager scene object used here, by place (main's scene_object.h). */
#define FLEA_MARKET_ACTION 0x618 /* SceneAction */
#define FLEA_MARKET_RECORD 0x830 /* u8 *: its town record */
/* The parts of a field actor read here: its position and its yaw. */
#define FLEA_MARKET_ACTOR_POSITION 0x5c /* Vec3 */
#define FLEA_MARKET_ACTOR_YAW 0x8e      /* u16 */

/* Its vtable slot giving its town record, and its talk scene's vtable slot its talks call. */
#define FLEA_MARKET_SLOT_RECORD 0x64
#define FLEA_MARKET_TALK_SLOT_08 0x08

/* The field actor of this console's player. */
#define FLEA_MARKET_PLAYER_ACTOR 4

/* The stages of the trade (FleaMarketVillager.stage). */
#define FLEA_MARKET_STAGE_NONE 0
#define FLEA_MARKET_STAGE_ASK 1
#define FLEA_MARKET_STAGE_LOOK 2
#define FLEA_MARKET_STAGE_AT_START 3

/* The item code of "no item", and the value kind of an item's name (SceneBase_PutItemName). */
#define FLEA_MARKET_NO_ITEM 0xfff1
#define FLEA_MARKET_ITEM_NAME_KIND 7
/* The items it does not sell. */
#define FLEA_MARKET_KEPT_ITEM_A 0x409c
#define FLEA_MARKET_KEPT_ITEM_B 0x40a0
#define FLEA_MARKET_KEPT_ITEM_C 0x3820

/* The size of the texts the message file names are written in. */
#define FLEA_MARKET_FILE_NAME_SIZE 0x28

/* The vtables: the class's, and its talk scene's. */
extern const u8 data_ov004_02253bb4[];
extern const u8 data_ov004_02253b24[];
/* main's bytes that are both set when the field is tapped (the picks of the touch screen are
 * read then), and the pad's state (button A pressed: bit 0 of `pressed`). */
extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern PadState data_021fbe40;
/* 1 while the game is in a room. */
extern u8 data_020e54a8;
/* The sine and cosine of each 16th of an angle step. */
extern const s16 FX_SinCosTable_[];
/* The texts the message file names are written in, by its answer and by its lines. */
extern char data_ov004_02257d08[FLEA_MARKET_FILE_NAME_SIZE];
extern char data_ov004_02257d30[FLEA_MARKET_FILE_NAME_SIZE];
/* The message files: "q11_trade2", "q_no", "q11_yes", "q11_no", "ev_fmarket2", "q11_trade4",
 * "q11_trade3" and "q11_trade1". */
extern const char data_ov004_02253c74[], data_ov004_02253c80[], data_ov004_02253c88[], data_ov004_02253c90[],
    data_ov004_02253c98[], data_ov004_02253ca4[], data_ov004_02253cb0[], data_ov004_02253cbc[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* The class's functions kept as the game's. */
/* The grid of the room's objects, the number at a cell of it (-1 for none) and the object
 * there (NULL for none); the room object taken away by number. */
extern void *func_ov004_0223cd50(void);
extern int func_ov004_0223cc5c(void *grid, int x, int z, int layer);
extern RoomObject *func_ov004_0223cc10(void *grid, int x, int z, int layer);
extern int func_ov004_0223bb14(int number);

static u8 *fm_part(FleaMarketVillager *villager, u32 offset)
{
    return villager->base + offset;
}

static SceneAction *fm_action_of(FleaMarketVillager *villager)
{
    return (SceneAction *) (void *) fm_part(villager, FLEA_MARKET_ACTION);
}

static u8 *fm_record_field(FleaMarketVillager *villager)
{
    return *(u8 **) (void *) fm_part(villager, FLEA_MARKET_RECORD);
}

/* Its town record, through its vtable slot 0x64. */
static u8 *fm_record(FleaMarketVillager *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager->base;
    u32 code = *(const u32 *) (uintptr_t) (vtable + FLEA_MARKET_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *))(uintptr_t) code)(villager->base);
}

static SceneBase *fm_scene_of(FleaMarketTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

/* The talk scene's vtable slot 0x08 called. */
static void fm_talk_slot_08(FleaMarketTalk *talk)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + FLEA_MARKET_TALK_SLOT_08);
    ((void (*)(FleaMarketTalk *))(uintptr_t) code)(talk);
}

/* Whether `item` is `code`: for an item with a variant, the same item of any variant. */
static int fm_item_is(const u16 *item, u16 code)
{
    if (ItemCode_HasVariant(item)) {
        u16 other = code;
        int same = ItemCode_VariantItem(item);
        return same == ItemCode_VariantItem(&other);
    }
    return *item == code;
}

/* func_ov004_0221eed8 (vtable slot 0x40): the destructor, without freeing: its talk scene, then
 * the town villager scene object. */
FleaMarketVillager *FleaMarketVillager_Destroy(FleaMarketVillager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_02253bb4;
    FleaMarketTalk_Destroy(&villager->talk);
    VillagerSceneObject_DestructBody(villager->base);
    return villager;
}
CLEAN_AS(func_ov004_0221eed8, FleaMarketVillager_Destroy)

/* func_ov004_0221ef00 (vtable slot 0x44, the deleting destructor). */
FleaMarketVillager *FleaMarketVillager_Delete(FleaMarketVillager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_02253bb4;
    FleaMarketTalk_Destroy(&villager->talk);
    VillagerSceneObject_DestructBody(villager->base);
    Heap_FreeAux(villager);
    return villager;
}
CLEAN_AS(func_ov004_0221ef00, FleaMarketVillager_Delete)

/* func_ov004_0221ef2c: when the room's start point of this console's player
 * (PlayerActorOps_StartPosition) is on the unit the collision map has claimed, the stage is 3
 * and an event of kind 6 about it is asked for; whether it was. */
int FleaMarketVillager_RequestIfStartClaimed(FleaMarketVillager *villager)
{
    Vec3 start = *PlayerActorOps_StartPosition(FLEA_MARKET_PLAYER_ACTOR);
    if (CollisionMap_IsClaimedAtPoint(&start)) {
        villager->stage = FLEA_MARKET_STAGE_AT_START;
        EventQueue_RequestKind6(villager, 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221ef2c, FleaMarketVillager_RequestIfStartClaimed)

/* func_ov004_0221ef70: when the player asks about an item (FleaMarketVillager_PickItemAhead), an
 * event of kind 6 about it is asked for; whether it was. */
int FleaMarketVillager_RequestItemTalk(FleaMarketVillager *villager)
{
    if (FleaMarketVillager_PickItemAhead(villager)) {
        EventQueue_RequestKind6(villager, 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221ef70, FleaMarketVillager_RequestItemTalk)

/* How far ahead of the player the item is looked for (a tile). */
#define FLEA_MARKET_AHEAD 0x2000
/* The yaw's bits below one step of FX_SinCosTable_. */
#define FLEA_MARKET_SIN_SHIFT 4

/* func_ov004_0221ef90: in stage 2, with this console's player's field actor there, no event
 * going on, its action idle, and button A pressed or the field tapped: the room object on the
 * tile 0x2000 ahead of the player (layer 0; when tapped, there must be an object at that tile
 * and it must be the one tapped, or with no object the tapped ground must be that tile) is
 * the item asked about (its number, variant 0); its tile is moved to the cell of the object
 * holding a variant code (RoomObject_FindVariantCell). That tile is kept when the villager has
 * a record marking it among its house's spots and the item is none of 0x409c, 0x40a0 and 0x3820,
 * else (-1, -1). Whether an item was taken (1 also when it is not for sale). */
int FleaMarketVillager_PickItemAhead(FleaMarketVillager *villager)
{
    u8 *player = SessionPlayers_ActorOf(FLEA_MARKET_PLAYER_ACTOR);
    int tapped = data_021f6c38 != 0 && data_021f6c34 != 0;

    if (villager->stage != FLEA_MARKET_STAGE_LOOK) {
        return 0;
    }
    if (player == NULL || EventQueue_HasCurrent() != 0 || SceneAction_IsBusy(fm_action_of(villager)) != 0 ||
        ((data_021fbe40.pressed & 1) == 0 && !tapped)) {
        return 0;
    }

    Vec3 ahead = *(const Vec3 *) (const void *) (player + FLEA_MARKET_ACTOR_POSITION);
    int index = (*(const u16 *) (const void *) (player + FLEA_MARKET_ACTOR_YAW) >> FLEA_MARKET_SIN_SHIFT) * 2;
    ahead.x += FX_MulFunc(FLEA_MARKET_AHEAD, FX_SinCosTable_[index]);
    ahead.z += FX_MulFunc(FLEA_MARKET_AHEAD, FX_SinCosTable_[index + 1]);
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) (const void *) &ahead);

    if (tapped) {
        if (func_ov004_0223cc5c(func_ov004_0223cd50(), x, z, 0) == -1) {
            return 0;
        }
        RoomObject *object = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
        if (object != NULL) {
            TouchPick *pick = (TouchPick *) (uintptr_t) SceneQuery_FieldObject();
            if ((int) (uintptr_t) object != TouchPick_PickedObject(pick, NULL, NULL)) {
                return 0;
            }
        } else {
            int ground_x = 0;
            int ground_z = 0;
            Vec3 ground;
            TouchPick_GetGround((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &ground);
            Position_Tile(&ground_x, &ground_z, (const Position *) (const void *) &ground);
            if (ground_x != x || ground_z != z) {
                return 0;
            }
        }
    }

    RoomObject *object = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
    if (object == NULL) {
        return 0;
    }
    u16 item = ItemCode_MakeVariant(RoomObject_Number(object), 0);
    int cell_x = x;
    int cell_z = z;
    RoomObject_FindVariantCell(object, &cell_x, &cell_z, NULL, 0);
    VillagerFurnitureTile tile = {cell_x, cell_z};
    villager->item = item;
    if (fm_record(villager) != NULL &&
        VillagerFurniture_IsMarkedAt(fm_record(villager), &tile, villager->spots, villager->spot_count) != 0 &&
        !fm_item_is(&villager->item, FLEA_MARKET_KEPT_ITEM_A) && !fm_item_is(&villager->item, FLEA_MARKET_KEPT_ITEM_B) &&
        !fm_item_is(&villager->item, FLEA_MARKET_KEPT_ITEM_C)) {
        villager->tile = tile;
    } else {
        villager->tile.x = -1;
        villager->tile.z = -1;
    }
    return 1;
}
CLEAN_AS(func_ov004_0221ef90, FleaMarketVillager_PickItemAhead)

/* The states asked for here (FleaMarketVillager_SetState). */
#define FLEA_MARKET_STATE_1 1
#define FLEA_MARKET_STATE_3 3
#define FLEA_MARKET_STATE_4 4
#define FLEA_MARKET_STATE_7 7

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define FLEA_MARKET_EVENT_TALK 0
#define FLEA_MARKET_EVENT_1 1
#define FLEA_MARKET_EVENT_ENDED 8

/* Its talk scene told through its vtable slot 0x08 and given this console's player's object as
 * the motion's argument. */
static void fm_ready_talk(FleaMarketVillager *villager)
{
    fm_talk_slot_08(&villager->talk);
    SceneBase_SetMotionArg(fm_scene_of(&villager->talk), SceneObject_ActorObject(villager->base, FLEA_MARKET_PLAYER_ACTOR));
}

/* func_ov004_0221f254 (vtable slot 0x4c, told of an event; the participant is not read):
 * - 1: its talk readied (fm_ready_talk), then state 1 in stage 0, 3 in stage 3, else 7;
 * - 0, the player talks to it: its talk readied, state 1;
 * - 8, the event ended: state 4. */
void FleaMarketVillager_OnEvent(FleaMarketVillager *villager, int code)
{
    switch (code) {
        case FLEA_MARKET_EVENT_1:
            fm_ready_talk(villager);
            if (villager->stage == FLEA_MARKET_STAGE_NONE) {
                FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_1);
            } else if (villager->stage == FLEA_MARKET_STAGE_AT_START) {
                FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_3);
            } else {
                FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_7);
            }
            break;
        case FLEA_MARKET_EVENT_TALK:
            fm_ready_talk(villager);
            FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_1);
            break;
        case FLEA_MARKET_EVENT_ENDED:
            FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_4);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221f254, FleaMarketVillager_OnEvent)

/* func_ov004_0221f2e8 (vtable slot 0x58): whether its action is idle. */
int FleaMarketVillager_IsIdle(FleaMarketVillager *villager)
{
    return SceneAction_IsBusy(fm_action_of(villager)) == 0;
}
CLEAN_AS(func_ov004_0221f2e8, FleaMarketVillager_IsIdle)

/* func_ov004_0221f308 (vtable slot 0x48): whether the player may talk to it: its action idle
 * and no talk about an item asked for (FleaMarketVillager_RequestItemTalk, which asks for it
 * when it can). */
int FleaMarketVillager_MayAct(FleaMarketVillager *villager)
{
    if (SceneAction_IsBusy(fm_action_of(villager))) {
        return 0;
    }
    return FleaMarketVillager_RequestItemTalk(villager) == 0;
}
CLEAN_AS(func_ov004_0221f308, FleaMarketVillager_MayAct)

/* The message of the talk scene's receiver. */
static u8 fm_message_of(FleaMarketTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The message file `name` for the villager, written into `text`. */
static void fm_format_file(FleaMarketTalk *talk, char *text, const char *name)
{
    NpcId_FormatResourceName(TownVillager_NpcId(fm_record_field(talk->villager)), text, FLEA_MARKET_FILE_NAME_SIZE, name);
}

/* func_ov004_0221f334 (the talk scene's receiver slot 0x18, the player's answer), after messages
 * 0 to 2:
 * - stage 1: a message 0 to 2 at random; the first answer: of "q11_trade2", the bottom
 *   screen's panels asked for and stage 2; the other: of "q_no";
 * - stage 2: the first answer: of "q11_yes", and the item is sold (FleaMarketTalk_Sell); the
 *   other: of "q11_no"; then a message 0 to 2 at random.
 * The answer is read whatever the stage. */
void FleaMarketTalk_OnAnswer(FleaMarketTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) SceneBase_TalkChoices(fm_scene_of(talk)));
    int message;

    if (talk->villager->stage == FLEA_MARKET_STAGE_ASK) {
        if (fm_message_of(talk) > 2) {
            return;
        }
        message = (int) MainRandom_Below(3);
        if (answer == 0) {
            fm_format_file(talk, data_ov004_02257d08, data_ov004_02253c74);
            ScreenPanels_Request();
            talk->villager->stage = FLEA_MARKET_STAGE_LOOK;
        } else {
            fm_format_file(talk, data_ov004_02257d08, data_ov004_02253c80);
        }
    } else if (talk->villager->stage == FLEA_MARKET_STAGE_LOOK) {
        if (fm_message_of(talk) > 2) {
            return;
        }
        if (answer == 0) {
            fm_format_file(talk, data_ov004_02257d08, data_ov004_02253c88);
            FleaMarketTalk_Sell(talk);
        } else {
            fm_format_file(talk, data_ov004_02257d08, data_ov004_02253c90);
        }
        message = (int) MainRandom_Below(3);
    } else {
        return;
    }
    u8 number = (u8) message;
    TalkObject_SetMessage((TalkObject *) (void *) talk->base.scene.talk, &number, data_ov004_02257d08);
}
CLEAN_AS(func_ov004_0221f334, FleaMarketTalk_OnAnswer)

/* func_ov004_0221f438 (the talk scene's receiver slot 0x14, a message ended): nothing. */
void FleaMarketTalk_OnMessageEnded(void) {}
CLEAN_AS(func_ov004_0221f438, FleaMarketTalk_OnMessageEnded)

/* func_ov004_0221f43c (vtable slot 0x80): notes its action sound was played. */
FleaMarketVillager *FleaMarketVillager_ActionSoundPlayed(FleaMarketVillager *villager)
{
    villager->sound_played = 1;
    return villager;
}
CLEAN_AS(func_ov004_0221f43c, FleaMarketVillager_ActionSoundPlayed)

/* func_ov004_0221f448 (vtable slot 0x7c): its action sound is played outside a room, and in a
 * room until it was once. */
int FleaMarketVillager_HasActionSound(FleaMarketVillager *villager)
{
    return data_020e54a8 != 1 || villager->sound_played == 0;
}
CLEAN_AS(func_ov004_0221f448, FleaMarketVillager_HasActionSound)

/* The least price, the price's step and what the fondness of the player lowers it from. */
#define FLEA_MARKET_MIN_PRICE 10
#define FLEA_MARKET_PRICE_STEP 10
#define FLEA_MARKET_FULL_FONDNESS 0xff
/* The price is the item's times (0xff - fondness) / 0x200 (FX_Div by 0x200 in 20.12). */
#define FLEA_MARKET_PRICE_DIVISOR 0x200000
/* The value slot and format of the price (SceneBase_PutValue). */
#define FLEA_MARKET_PRICE_SLOT 3
#define FLEA_MARKET_PRICE_FORMAT 10
/* The places of a villager's house, and the least items it keeps there to sell. */
#define FLEA_MARKET_HOUSE_PLACES 10
#define FLEA_MARKET_MIN_ITEMS 3

/* `n` in 20.12 as the ROM makes it: through a float, adding 0.5 away from zero and truncating
 * (FX32_CONST). That is n << 12 (kept to 32 bits), except where the shift wraps to the other
 * sign below 2^23 in size.
 * QUIRK: an integer is converted through a float. */
static fx32 fm_fx_from_int(int n)
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

/* func_ov004_0221f474 (the talk scene's vtable slot 0x78, the line to say): its memory of the
 * current player is updated (with no player, town or date) when it has one. Then the text is
 * written into data_ov004_02257d30:
 * - in stage 3: "ev_fmarket2", a message 3 to 5 at random;
 * - with an item asked about: its name is the talk's value 0; the price is its price (at least
 *   10) times (0xff - fondness) / 0x200, its fondness of the player being 0 without a memory,
 *   rounded to the nearest 10 (5 up), and becomes value 3. "q11_trade4" when the item is not
 *   for sale, the player's pockets are full, the villager keeps 3 items or fewer in its house
 *   or the player cannot pay, else "q11_trade3"; a message 0 to 2 at random;
 * - else by the stage: 0 "ev_fmarket2" and a message 0 to 2, 1 "q11_trade1" and 0 to 2, 2
 *   "ev_fmarket2" and 6 to 8; another stage leaves the message as it is.
 * QUIRK: with no current player when the price is set, the memory found at first is used. */
void FleaMarketTalk_Line(FleaMarketTalk *talk, VillagerTalkLine *out)
{
    VillagerMemory *memory = VillagerMemory_Of(fm_record_field(talk->villager), PlayerRecord_Player(PlayerRecords_Current()));
    if (memory != NULL) {
        VillagerMemoryEntry_Update(memory, NULL, NULL, NULL);
    }

    FleaMarketVillager *villager = talk->villager;
    if (villager->stage == FLEA_MARKET_STAGE_AT_START) {
        fm_format_file(talk, data_ov004_02257d30, data_ov004_02253c98);
        out->text = (u32) (uintptr_t) data_ov004_02257d30;
        out->message = (u8) (MainRandom_Below(3) + 3);
        return;
    }

    if (!fm_item_is(&villager->item, FLEA_MARKET_NO_ITEM)) {
        int fondness = 0;
        SceneBase_PutItemName(fm_scene_of(talk), (int) (uintptr_t) &talk->villager->item, 0, FLEA_MARKET_ITEM_NAME_KIND);
        talk->price = ItemTraits_Price(&talk->villager->item);
        if (talk->price < FLEA_MARKET_MIN_PRICE) {
            talk->price = FLEA_MARKET_MIN_PRICE;
        }
        if (PlayerRecords_Current() != NULL) {
            memory = VillagerMemory_Of(fm_record_field(talk->villager), PlayerRecord_Player(PlayerRecords_Current()));
        }
        if (memory != NULL) {
            fondness = VillagerMemoryEntry_Fondness(memory);
        }
        fx32 share = fm_fx_from_int(FLEA_MARKET_FULL_FONDNESS - fondness);
        talk->price = FX_Div(FX_MulFunc(talk->price, share), FLEA_MARKET_PRICE_DIVISOR);
        int price = talk->price;
        int rounded = price / FLEA_MARKET_PRICE_STEP * FLEA_MARKET_PRICE_STEP;
        if (price - rounded >= FLEA_MARKET_PRICE_STEP / 2) {
            rounded += FLEA_MARKET_PRICE_STEP;
        }
        talk->price = rounded;
        SceneBase_PutValue(fm_scene_of(talk), talk->price, FLEA_MARKET_PRICE_SLOT, FLEA_MARKET_PRICE_FORMAT, 0, 0);

        int kept = 0;
        if (fm_record_field(talk->villager) != NULL) {
            u16 none = FLEA_MARKET_NO_ITEM;
            kept = FLEA_MARKET_HOUSE_PLACES - VillagerHouseItems_CountSame(fm_record_field(talk->villager), &none);
        }
        if (talk->villager->tile.x == -1 || CurrentPockets_FreeSlot() == -1 || kept <= FLEA_MARKET_MIN_ITEMS ||
            SceneBells_CanPay((int) (uintptr_t) talk->villager, talk->price) == 0) {
            fm_format_file(talk, data_ov004_02257d30, data_ov004_02253ca4);
        } else {
            fm_format_file(talk, data_ov004_02257d30, data_ov004_02253cb0);
        }
        out->text = (u32) (uintptr_t) data_ov004_02257d30;
        out->message = (u8) MainRandom_Below(3);
        return;
    }

    switch (talk->villager->stage) {
        case FLEA_MARKET_STAGE_NONE:
            fm_format_file(talk, data_ov004_02257d30, data_ov004_02253c98);
            out->message = (u8) MainRandom_Below(3);
            break;
        case FLEA_MARKET_STAGE_ASK:
            fm_format_file(talk, data_ov004_02257d30, data_ov004_02253cbc);
            out->message = (u8) MainRandom_Below(3);
            break;
        case FLEA_MARKET_STAGE_LOOK:
            fm_format_file(talk, data_ov004_02257d30, data_ov004_02253c98);
            out->message = (u8) (MainRandom_Below(3) + 6);
            break;
        default:
            break;
    }
    out->text = (u32) (uintptr_t) data_ov004_02257d30;
}
CLEAN_AS(func_ov004_0221f474, FleaMarketTalk_Line)

/* func_ov004_0221f71c: the item asked about sold to the player, unless it is none: the price
 * taken from the player's bells, the item given into their pockets, the room object at its tile
 * (layer 0) taken away when there is one, and then the item taken out of the villager's house
 * when it has a record; the item asked about is none after. */
void FleaMarketTalk_Sell(FleaMarketTalk *talk)
{
    FleaMarketVillager *villager = talk->villager;
    if (fm_item_is(&villager->item, FLEA_MARKET_NO_ITEM)) {
        return;
    }
    SceneBells_Take((int) (uintptr_t) villager, talk->price);
    CurrentPockets_Give(&villager->item, 0);
    int number = func_ov004_0223cc5c(func_ov004_0223cd50(), villager->tile.x, villager->tile.z, 0);
    if (number != -1) {
        func_ov004_0223bb14(number);
        if (fm_record(villager) != NULL) {
            VillagerFurniture_TakeAt(fm_record(villager), &villager->tile, villager->spots, villager->spot_count);
        }
    }
    villager->item = FLEA_MARKET_NO_ITEM;
}
CLEAN_AS(func_ov004_0221f71c, FleaMarketTalk_Sell)

/* The lines table VillagerTalkScene_Start is given: 17 and above leave the line members as they
 * are (the talk scene's own vtable slot 0x78 says the line). */
#define FLEA_MARKET_TALK_OWN_LINES 0x11

/* func_ov004_0221f800: its talk scene told through its vtable slot 0x08, started for `villager`
 * and kept pointing back at it. */
void FleaMarketTalk_Start(FleaMarketTalk *talk, FleaMarketVillager *villager)
{
    fm_talk_slot_08(talk);
    VillagerTalkScene_Start(&talk->base, villager->base, FLEA_MARKET_TALK_OWN_LINES);
    talk->villager = villager;
}
CLEAN_AS(func_ov004_0221f800, FleaMarketTalk_Start)

/* func_ov004_0221f828 (the talk scene's vtable slot 0x04, its deleting destructor). */
FleaMarketTalk *FleaMarketTalk_Delete(FleaMarketTalk *talk)
{
    talk->base.scene.vtable = data_ov004_02253b24;
    VillagerTalkScene_DestructBody(&talk->base);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_0221f828, FleaMarketTalk_Delete)

/* func_ov004_0221f848 (the talk scene's vtable slot 0x00, its destructor). */
FleaMarketTalk *FleaMarketTalk_Destroy(FleaMarketTalk *talk)
{
    talk->base.scene.vtable = data_ov004_02253b24;
    VillagerTalkScene_DestructBody(&talk->base);
    return talk;
}
CLEAN_AS(func_ov004_0221f848, FleaMarketTalk_Destroy)

/* func_ov004_0221f860: its talk scene's constructor. */
FleaMarketTalk *FleaMarketTalk_Construct(FleaMarketTalk *talk)
{
    VillagerTalkScene_ConstructAlt(&talk->base);
    talk->base.scene.vtable = data_ov004_02253b24;
    return talk;
}
CLEAN_AS(func_ov004_0221f860, FleaMarketTalk_Construct)

/* The parts of the town villager scene object its states use, by place (main's scene_object.h). */
#define FLEA_MARKET_MOVER 0x350     /* SceneMover */
#define FLEA_MARKET_FOOTSTEPS 0x558 /* Footsteps */
#define FLEA_MARKET_MOTION 0x564    /* SceneMotion */

/* Its states (FleaMarketVillager_SetState, flea_market_villager.h). */
#define FLEA_MARKET_STATE_CALL 0
#define FLEA_MARKET_STATE_TALK 1
#define FLEA_MARKET_STATE_WAIT 2
#define FLEA_MARKET_STATE_WATCH 4
#define FLEA_MARKET_STATE_TURN 5
#define FLEA_MARKET_STATE_FOLLOW 6

/* The kinds of motion asked for (scene_motion_request.h) and the rate of its run. */
#define FLEA_MARKET_MOTION_STAND 0
#define FLEA_MARKET_MOTION_WALK 1
#define FLEA_MARKET_MOTION_RUN 2
#define FLEA_MARKET_MOTION_TURN 3
#define FLEA_MARKET_RUN_RATE 0x800

/* Farther from the player than this it runs, and than this it follows them (20.12). */
#define FLEA_MARKET_RUN_DISTANCE 0x4000
#define FLEA_MARKET_FOLLOW_DISTANCE 0x3000
/* Turned away from the player by more than this (an eighth of a turn) it turns to them. */
#define FLEA_MARKET_TURN_ANGLE 0x2000
/* The frames of state 7's walk. */
#define FLEA_MARKET_COME_FRAMES 0x32

/* The word its motion requests carry, and the map of the scene. */
extern u16 data_020c80f8;
extern AcreMap *data_021c80bc;
/* The current heap. */
extern Heap *data_021fbe94;
/* Its states' functions (filled at start-up from the overlay's constants). */
extern FleaMarketVillagerStep data_ov004_02257d58[FLEA_MARKET_VILLAGER_STATES];

/* Notes that a villager of the flea market is in the room (sets data_ov004_022595b4). */
extern void func_ov004_0223d33c(void);

static Actor *fm_actor_of(FleaMarketVillager *villager)
{
    return (Actor *) (void *) villager->base;
}

static SceneMotion *fm_motion_of(FleaMarketVillager *villager)
{
    return (SceneMotion *) (void *) fm_part(villager, FLEA_MARKET_MOTION);
}

static SceneMover *fm_mover_of(FleaMarketVillager *villager)
{
    return (SceneMover *) (void *) fm_part(villager, FLEA_MARKET_MOVER);
}

/* A motion of `kind` (priority 1) asked for with no arguments but `rate`. */
static void fm_request_motion(FleaMarketVillager *villager, int kind, s16 rate)
{
    SceneMotion_Request(fm_motion_of(villager), kind, 1, 0, 0, rate, 0, 0, 0, data_020c80f8, 0);
}

/* Running when farther than FLEA_MARKET_RUN_DISTANCE from the player, else walking: a walk becomes
 * a run and a run a walk, other motions are left alone. */
static void fm_walk_or_run(FleaMarketVillager *villager, int distance)
{
    if (distance > FLEA_MARKET_RUN_DISTANCE) {
        if (SceneMotion_Kind(fm_motion_of(villager)) == FLEA_MARKET_MOTION_WALK) {
            fm_request_motion(villager, FLEA_MARKET_MOTION_RUN, FLEA_MARKET_RUN_RATE);
        }
    } else if (SceneMotion_Kind(fm_motion_of(villager)) == FLEA_MARKET_MOTION_RUN) {
        fm_request_motion(villager, FLEA_MARKET_MOTION_WALK, 0);
    }
}

/* The turn of its action to the talk's partner (none: angle 0), then talking; `keep_camera` as
 * SceneAction_RequestTurnAndTalk takes it. */
static void fm_turn_and_talk(FleaMarketVillager *villager, int keep_camera)
{
    int partner = SceneBase_MotionArg(fm_scene_of(&villager->talk));
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(villager->base, (u8 *) (uintptr_t) partner);
    }
    SceneAction_RequestTurnAndTalk(fm_action_of(villager), 0, angle, keep_camera);
}

/* func_ov004_0221f878 (state 7's update): it steps along the paths to the player (as they were
 * when their frame began), running when far (fm_walk_or_run). Close to them (0x3000 or less),
 * with no step to take, or once the walk's frames have run out, its talk is told through its
 * vtable slot 0x08, given the player's object, and it talks (state 1). 1.
 * QUIRK: the map's path directions at its position are asked for and not used.
 * REQUIRES: the player has a field actor (PlayerActorOps_StartPosition is not NULL), here and in
 * the other states that read the player's position. */
int FleaMarketVillager_UpdateCome(FleaMarketVillager *villager)
{
    Vec3 player = *PlayerActorOps_StartPosition(FLEA_MARKET_PLAYER_ACTOR);
    Vec3 step;
    ScenePathStep_Choose(&step, villager->base, &player);
    int distance = SceneObject_DistanceToActor(villager->base, FLEA_MARKET_PLAYER_ACTOR);
    AcreTile_PathDirectionsAt(data_021c80bc, &fm_actor_of(villager)->position);
    fm_walk_or_run(villager, distance);
    SceneMover_SetStart(fm_mover_of(villager), &step);
    if (distance <= FLEA_MARKET_FOLLOW_DISTANCE || Vec_Equal(&step, &fm_actor_of(villager)->position) ||
        Countdown_Tick8(&villager->walk_wait) == 0) {
        fm_ready_talk(villager);
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_TALK);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221f878, FleaMarketVillager_UpdateCome)

/* func_ov004_0221f990 (state 7's entry): 50 frames to walk, and a walk. 1. */
int FleaMarketVillager_EnterCome(FleaMarketVillager *villager)
{
    villager->walk_wait = FLEA_MARKET_COME_FRAMES;
    fm_request_motion(villager, FLEA_MARKET_MOTION_WALK, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221f990, FleaMarketVillager_EnterCome)

/* func_ov004_0221f9d0 (state 2's update): nothing. 1. */
int FleaMarketVillager_UpdateWait(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221f9d0, FleaMarketVillager_UpdateWait)

/* func_ov004_0221f9d4 (state 1's update): once its action is idle, the trade's stage 0 becomes 1,
 * the item asked about is none, the object's event ends and it waits (state 2). 1. */
int FleaMarketVillager_UpdateTalk(FleaMarketVillager *villager)
{
    if (SceneAction_IsBusy(fm_action_of(villager)) == 0) {
        if (villager->stage == FLEA_MARKET_STAGE_NONE) {
            villager->stage = FLEA_MARKET_STAGE_ASK;
        }
        villager->item = FLEA_MARKET_NO_ITEM;
        EventQueue_FinishObjectEvent(villager);
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_WAIT);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221f9d4, FleaMarketVillager_UpdateTalk)

/* func_ov004_0221fa20 (state 1's entry): it turns to the talk's partner and talks. 1. */
int FleaMarketVillager_EnterTalk(FleaMarketVillager *villager)
{
    fm_turn_and_talk(villager, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221fa20, FleaMarketVillager_EnterTalk)

/* func_ov004_0221fa58 (state 3's update): once its action is idle, the room's exit 0 is taken
 * into main's entry record and it waits (state 2). 1.
 * QUIRK: the player's position is fetched and not used. */
int FleaMarketVillager_UpdateBye(FleaMarketVillager *villager)
{
    (void) PlayerActorOps_StartPosition(FLEA_MARKET_PLAYER_ACTOR);
    if (SceneAction_IsBusy(fm_action_of(villager)) == 0) {
        SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0);
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_WAIT);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221fa58, FleaMarketVillager_UpdateBye)

/* func_ov004_0221fa9c (state 3's entry): it turns to the talk's partner and talks, the camera
 * kept. 1. */
int FleaMarketVillager_EnterBye(FleaMarketVillager *villager)
{
    fm_turn_and_talk(villager, 1);
    return 1;
}
CLEAN_AS(func_ov004_0221fa9c, FleaMarketVillager_EnterBye)

/* func_ov004_0221fad4 (state 6's update): nothing more once the event of the player at the
 * room's start point or of an item asked about is asked for. Else it steps along the paths to
 * the player, running when far, and watches them (state 4) when close (0x3000 or less) or with
 * no step to take. 1. */
int FleaMarketVillager_UpdateFollow(FleaMarketVillager *villager)
{
    if (FleaMarketVillager_RequestIfStartClaimed(villager) || FleaMarketVillager_RequestItemTalk(villager)) {
        return 1;
    }
    Vec3 player = *PlayerActorOps_StartPosition(FLEA_MARKET_PLAYER_ACTOR);
    int distance = SceneObject_DistanceToActor(villager->base, FLEA_MARKET_PLAYER_ACTOR);
    Vec3 step;
    ScenePathStep_Choose(&step, villager->base, &player);
    fm_walk_or_run(villager, distance);
    SceneMover_SetStart(fm_mover_of(villager), &step);
    if (distance <= FLEA_MARKET_FOLLOW_DISTANCE || Vec_Equal(&step, &fm_actor_of(villager)->position)) {
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_WATCH);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221fad4, FleaMarketVillager_UpdateFollow)

/* func_ov004_0221fbc4 (state 6's entry): a walk. 1. */
int FleaMarketVillager_EnterFollow(FleaMarketVillager *villager)
{
    fm_request_motion(villager, FLEA_MARKET_MOTION_WALK, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221fbc4, FleaMarketVillager_EnterFollow)

/* func_ov004_0221fbf8 (state 5's update): nothing more once the events of state 6 are asked for.
 * Farther than 0x3000 from the player with a step to take towards them, it follows them (state
 * 6); else its mover turns to them, and with its turn done it watches them (state 4). 1. */
int FleaMarketVillager_UpdateTurn(FleaMarketVillager *villager)
{
    if (FleaMarketVillager_RequestIfStartClaimed(villager) || FleaMarketVillager_RequestItemTalk(villager)) {
        return 1;
    }
    Vec3 player = *PlayerActorOps_StartPosition(FLEA_MARKET_PLAYER_ACTOR);
    int distance = SceneObject_DistanceToActor(villager->base, FLEA_MARKET_PLAYER_ACTOR);
    int yaw = (int) (uintptr_t) SceneObject_YawToActor(villager->base, FLEA_MARKET_PLAYER_ACTOR);
    Vec3 step;
    ScenePathStep_Choose(&step, villager->base, &player);
    if (distance > FLEA_MARKET_FOLLOW_DISTANCE && Vec_Differ(&step, &fm_actor_of(villager)->position)) {
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_FOLLOW);
        return 1;
    }
    SceneMover_SetAngle(fm_mover_of(villager), yaw);
    if (SceneMotion_Kind(fm_motion_of(villager)) == FLEA_MARKET_MOTION_TURN && SceneMotion_IsDone(fm_motion_of(villager))) {
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_WATCH);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221fbf8, FleaMarketVillager_UpdateTurn)

/* func_ov004_0221fca8 (state 5's entry): a turn. 1. */
int FleaMarketVillager_EnterTurn(FleaMarketVillager *villager)
{
    fm_request_motion(villager, FLEA_MARKET_MOTION_TURN, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221fca8, FleaMarketVillager_EnterTurn)

/* func_ov004_0221fcdc (state 4's update): farther than 0x3000 from the player with a step to take
 * towards them, it follows them (state 6); else turned away from them by more than 0x2000 it
 * turns (state 5). Then the event of the player at the room's start point is asked for, or when
 * it is not, that of an item asked about. 1. */
int FleaMarketVillager_UpdateWatch(FleaMarketVillager *villager)
{
    Vec3 player = *PlayerActorOps_StartPosition(FLEA_MARKET_PLAYER_ACTOR);
    int distance = SceneObject_DistanceToActor(villager->base, FLEA_MARKET_PLAYER_ACTOR);
    int yaw = fm_actor_of(villager)->angle[1];
    int away = Math_AbsDiff16(yaw, (int) (uintptr_t) SceneObject_YawToActor(villager->base, FLEA_MARKET_PLAYER_ACTOR));
    Vec3 step;
    ScenePathStep_Choose(&step, villager->base, &player);
    if (distance > FLEA_MARKET_FOLLOW_DISTANCE && Vec_Differ(&step, &fm_actor_of(villager)->position)) {
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_FOLLOW);
    } else if (away > FLEA_MARKET_TURN_ANGLE) {
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_TURN);
    }
    if (FleaMarketVillager_RequestIfStartClaimed(villager) == 0) {
        FleaMarketVillager_RequestItemTalk(villager);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221fcdc, FleaMarketVillager_UpdateWatch)

/* func_ov004_0221fd70 (state 4's entry): it stands. 1. */
int FleaMarketVillager_EnterWatch(FleaMarketVillager *villager)
{
    fm_request_motion(villager, FLEA_MARKET_MOTION_STAND, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221fd70, FleaMarketVillager_EnterWatch)

/* func_ov004_0221fda4 (state 0's update): an event of kind 6 about it is asked for. 1. */
int FleaMarketVillager_UpdateCall(FleaMarketVillager *villager)
{
    EventQueue_RequestKind6(villager, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221fda4, FleaMarketVillager_UpdateCall)

/* func_ov004_0221fdb8 (state 0's entry): the trade's stage back to 0, and it stands. 1. */
int FleaMarketVillager_EnterCall(FleaMarketVillager *villager)
{
    villager->stage = FLEA_MARKET_STAGE_NONE;
    fm_request_motion(villager, FLEA_MARKET_MOTION_STAND, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221fdb8, FleaMarketVillager_EnterCall)

/* func_ov004_0221fdf4: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 7 (the table is not bounded). */
void FleaMarketVillager_SetState(FleaMarketVillager *villager, int state)
{
    const FleaMarketVillagerStep *step = &data_ov004_02257d58[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, villager);
    }
    if (taken != 0) {
        villager->state = state;
    }
}
CLEAN_AS(func_ov004_0221fdf4, FleaMarketVillager_SetState)

/* func_ov004_0221fe38 (vtable slot 0x68, its update): its state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: its state is 0 to 7. */
int FleaMarketVillager_RunState(FleaMarketVillager *villager)
{
    const FleaMarketVillagerStep *step = &data_ov004_02257d58[(u32) villager->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, villager);
}
CLEAN_AS(func_ov004_0221fe38, FleaMarketVillager_RunState)

/* func_ov004_0221fe84 (vtable slot 0x0c): the town villager's leaving; when it agrees, the list
 * of its house's spots is freed (when there is one) and forgotten. Whether it agreed. */
int FleaMarketVillager_Leave(FleaMarketVillager *villager)
{
    if (VillagerSceneObject_Leave(villager->base) == 0) {
        return 0;
    }
    if (villager->spots != NULL) {
        Heap_FreeCurrent((void *) (uintptr_t) villager->spots);
        villager->spots = NULL;
        villager->spot_count = 0;
    }
    return 1;
}
CLEAN_AS(func_ov004_0221fe84, FleaMarketVillager_Leave)

/* func_ov004_0221febc (vtable slot 0x00, its start): the town villager's start; then the room
 * notes a villager of the flea market (func_ov004_0223d33c), no item is asked about, its
 * footsteps are on, and it watches the player (state 4) when the previous scene is one
 * SceneQuery_Is31 names, else calls them (state 0). The collision map's claim is set to 0, and
 * the spots of its house's items are read for its person (AcreTemplates_VillagerRecords, from
 * the current heap). Whether the start was done. */
int FleaMarketVillager_Start(FleaMarketVillager *villager)
{
    if (VillagerSceneObject_Start(villager->base) == 0) {
        return 0;
    }
    func_ov004_0223d33c();
    villager->item = FLEA_MARKET_NO_ITEM;
    Footsteps_Enable((Footsteps *) (void *) fm_part(villager, FLEA_MARKET_FOOTSTEPS));
    if (SceneQuery_Is31(SceneQuery_Previous())) {
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_WATCH);
    } else {
        FleaMarketVillager_SetState(villager, FLEA_MARKET_STATE_CALL);
    }
    CollisionMap_Claim(0);
    villager->spot_count = 0;
    int person = SceneObject_PersonIndex(villager->base);
    villager->spots = (const VillagerFurnitureSpot *) (uintptr_t) AcreTemplates_VillagerRecords(
        (int *) (void *) &villager->spot_count, person, (int) (uintptr_t) data_021fbe94);
    return 1;
}
CLEAN_AS(func_ov004_0221febc, FleaMarketVillager_Start)

/* func_ov004_0221ff40 (vtable slot 0x04, its set-up): the town villager's set-up; then its talk
 * scene becomes its scene and is started (FleaMarketTalk_Start). Whether the set-up was done. */
int FleaMarketVillager_Init(FleaMarketVillager *villager)
{
    if (VillagerSceneObject_Init(villager->base) == 0) {
        return 0;
    }
    SceneObject_SetScene(villager->base, fm_scene_of(&villager->talk));
    FleaMarketTalk_Start(&villager->talk, villager);
    return 1;
}
CLEAN_AS(func_ov004_0221ff40, FleaMarketVillager_Init)

/* func_ov004_0221ff70 (its entry in the overlay's table of profiles): allocates (zeroed) and
 * builds a villager: the town villager scene object, no item asked about, its tile (0, 0) and its
 * talk scene. */
FleaMarketVillager *FleaMarketVillager_New(void)
{
    FleaMarketVillager *villager = Heap_AllocAuxZeroed(sizeof(FleaMarketVillager));
    if (villager != NULL) {
        VillagerSceneObject_Construct(villager->base);
        *(const u8 **) (void *) villager->base = data_ov004_02253bb4;
        villager->item = FLEA_MARKET_NO_ITEM;
        villager->tile.x = 0;
        villager->tile.z = 0;
        FleaMarketTalk_Construct(&villager->talk);
    }
    return villager;
}
CLEAN_AS(func_ov004_0221ff70, FleaMarketVillager_New)
