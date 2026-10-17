/* The villager of a house at the flea market (flea_market_villager.h). */
#include "flea_market_villager.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/actor_table.h"
#include "main/collision_map.h"
#include "main/current_pockets.h"
#include "main/event_queue.h"
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
#include "main/scene_object.h"
#include "main/scene_query.h"
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
/* Its state (machine of the class). */
extern void func_ov004_0221fdf4(FleaMarketVillager *villager, int state);
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

/* The states func_ov004_0221fdf4 is asked for here. */
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
                func_ov004_0221fdf4(villager, FLEA_MARKET_STATE_1);
            } else if (villager->stage == FLEA_MARKET_STAGE_AT_START) {
                func_ov004_0221fdf4(villager, FLEA_MARKET_STATE_3);
            } else {
                func_ov004_0221fdf4(villager, FLEA_MARKET_STATE_7);
            }
            break;
        case FLEA_MARKET_EVENT_TALK:
            fm_ready_talk(villager);
            func_ov004_0221fdf4(villager, FLEA_MARKET_STATE_1);
            break;
        case FLEA_MARKET_EVENT_ENDED:
            func_ov004_0221fdf4(villager, FLEA_MARKET_STATE_4);
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
