/* Items on their way to the ground (dropped_items.h). */
#include "dropped_items.h"

#include "autoload_2/matrix.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "icon_models.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/globe.h"
#include "main/scene_query.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/sound_emitter.h"
#include "room_objects.h"

static_assert(sizeof(DroppedItem) == 0x94, "dropped item");
static_assert(offsetof(DroppedItem, target) == 0x18, "dropped item target");
static_assert(offsetof(DroppedItem, scale) == 0x3c, "dropped item scale");
static_assert(offsetof(DroppedItem, sound) == 0x4c, "dropped item sound");
static_assert(offsetof(DroppedItem, bounces) == 0x8c, "dropped item bounces");
static_assert(offsetof(DroppedItem, layer) == 0x90, "dropped item layer");

/* The items, and the process of the items' models. */
extern DroppedItem data_ov004_02258af4[DROPPED_ITEMS];
extern IconModels *data_ov004_02258ae4;

extern AcreMap *data_021c80bc;    /* the town's map, or null */
extern NetSession *data_020ccf94; /* the session */
extern Mtx43 data_021fbe48;       /* the matrix being built */

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* A place's destructor, handed to the C++ runtime: the game's. */
extern void func_ov004_02233ff4(void *drop);

#define ONE 0x1000

/* The arc: frames to the ground (or to a height), the speed up it starts with, the pull down
 * each frame, and the bounce. */
#define FLIGHT_FRAMES 9
#define FLIGHT_FRAMES_HIGH 12
#define FLIGHT_RISE ONE
#define FLIGHT_RISE_HIGH 0x1800
#define GRAVITY 0x400
#define BOUNCE_RISE 0x600
#define BOUNCE_KEEP 0x4cd /* of the speed along the ground, 0.3 */
#define GROWTH 0x19a      /* of the scale each frame */

/* Its sounds: thrown, and landing for items 0x1492-0x14fd. */
#define SOUND_THROWN 0x75
#define SOUND_LANDING 0x70
#define SOUND_VOLUME 0x7f
#define LANDING_SOUND_FIRST 0x1492
#define LANDING_SOUND_LAST 0x14fd

/* The kinds of item (the top four bits of its code). */
#define ITEM_KIND(code) (((code) & 0xf000) >> 12)

static SoundEmitter *DroppedItem_sound(DroppedItem *drop)
{
    return (SoundEmitter *) drop->sound;
}

/* func_ov004_0223356c: an item dropped by `player` from `from` to `to`, with no tile change
 * waiting; whether a place was free.
 * QUIRK: its tile is (0, 0), whose change on `layer` is finished when it lands. */
int DroppedItems_DropFrom(int player, int item, const Vec3 *from, const Vec3 *to, u8 layer)
{
    TileChangesTile tile = {0, 0};
    return DroppedItems_Start(data_ov004_02258af4, player, &tile, from, to, 0, (u16) item, 0, layer);
}
CLEAN_AS(func_ov004_0223356c, DroppedItems_DropFrom)

/* func_ov004_022335b8: an item dropped by `player` from `from` onto the centre of `tile`
 * (on top of what stands there for a layer other than 0); whether a place was free. */
int DroppedItems_DropOnTile(int player, int item, const TileChangesTile *tile, const Vec3 *from, u8 layer)
{
    Vec3 to;
    AcreTile_TileCentre(&to, (u32) tile->x, (u32) tile->z);
    if (layer != 0) {
        to.y = RoomObjects_HeightAtCell(tile->x, tile->z);
    }
    TileChangesTile at = *tile;
    return DroppedItems_Start(data_ov004_02258af4, player, &at, from, &to, 0, (u16) item, 0, layer);
}
CLEAN_AS(func_ov004_022335b8, DroppedItems_DropOnTile)

/* func_ov004_0223362c: the item set going in the first free of the player's three places;
 * whether there was one (none without the town's map). */
int DroppedItems_Start(DroppedItem *items, int player, const TileChangesTile *tile, const Vec3 *from, const Vec3 *to,
                       int landed, u16 item, short unk_48, u8 layer)
{
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    DroppedItem *drop = &items[player * DROPPED_ITEMS_PER_PLAYER];
    for (int i = 0; i < DROPPED_ITEMS_PER_PLAYER; i++, drop++) {
        if (drop->state == DROPPED_ITEM_FREE) {
            DroppedItem_Set(drop, player, tile, from, to, landed, item, map, unk_48, layer);
            drop->state = DROPPED_ITEM_FLYING;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223362c, DroppedItems_Start)

/* func_ov004_022336c4 (at the process's release): every item in use finished, and the sounds
 * let go. */
void DroppedItems_Release(DroppedItem *items)
{
    for (int i = 0; i < DROPPED_ITEMS; i++) {
        DroppedItem *drop = &items[i];
        if (drop->state != DROPPED_ITEM_FREE) {
            DroppedItem_Finish(drop);
        }
        SoundEmitter_Vfunc10B(DroppedItem_sound(drop));
    }
}
CLEAN_AS(func_ov004_022336c4, DroppedItems_Release)

/* func_ov004_022336f0: each item in use drawn where it is, the items of kinds 1, 3 and 4 with
 * their models at scale 1.
 * QUIRK: the item's own scale goes into a matrix that IconModels_DrawItem builds again from
 * the start, so it is never seen. */
void DroppedItems_Draw(DroppedItem *items)
{
    for (int i = 0; i < DROPPED_ITEMS; i++) {
        DroppedItem *drop = &items[i];
        u16 item = drop->item;
        if (drop->state == DROPPED_ITEM_FREE || item == DROPPED_ITEM_NONE) {
            continue;
        }
        Vec3 bent;
        int angle = Globe_BendFar(&bent, &drop->position);
        Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
        Mtx43_RotateX(&data_021fbe48, angle);
        Mtx43_Scale(&data_021fbe48, drop->scale.x, drop->scale.y, drop->scale.z);
        switch (ITEM_KIND(item)) {
            case 1:
            case 3:
            case 4: {
                Vec3 position = drop->position;
                Vec3 scale = {ONE, ONE, ONE};
                IconModels_DrawItem(data_ov004_02258ae4, item, &position, &scale, 0, 0, 0);
                break;
            }
        }
    }
}
CLEAN_AS(func_ov004_022336f0, DroppedItems_Draw)

/* func_ov004_022337ac: each flying item a frame on (unless it has landed), its sound following
 * it. */
void DroppedItems_Update(DroppedItem *items)
{
    for (int i = 0; i < DROPPED_ITEMS; i++) {
        DroppedItem *drop = &items[i];
        if (drop->state != DROPPED_ITEM_FLYING) {
            continue;
        }
        drop->frames++;
        if (!drop->landed) {
            DroppedItem_Fly(drop);
        }
        Vec3 position = drop->position;
        SoundEmitter_UpdateAtB(DroppedItem_sound(drop), &position);
    }
}
CLEAN_AS(func_ov004_022337ac, DroppedItems_Update)

/* func_ov004_0223380c (at the process's start): every place free, with no item, its sound
 * stopped. */
void DroppedItems_Reset(DroppedItem *items)
{
    for (int i = 0; i < DROPPED_ITEMS; i++) {
        DroppedItem *drop = &items[i];
        drop->state = DROPPED_ITEM_FREE;
        drop->item = DROPPED_ITEM_NONE;
        drop->item_0a = DROPPED_ITEM_NONE;
        SoundEmitter_StopB(DroppedItem_sound(drop));
    }
}
CLEAN_AS(func_ov004_0223380c, DroppedItems_Reset)

/* func_ov004_0223383c: a frame of flight: the item grows, falls and moves on; once it is
 * falling below its target's height it is put there and either bounces (the first time, at
 * 0.3 of its speed along the ground) or stops and is finished. Items 0x1492-0x14fd sound on
 * the first two times. */
void DroppedItem_Fly(DroppedItem *drop)
{
    drop->scale.x += GROWTH;
    if (drop->scale.x >= ONE) {
        drop->scale.x = ONE;
    }
    drop->scale.z = drop->scale.x;
    drop->velocity.y -= GRAVITY;
    VEC_Add(&drop->position, &drop->velocity, &drop->position);
    if (drop->velocity.y >= 0 || drop->position.y >= drop->target.y) {
        return;
    }
    if (drop->bounces < 2) {
        u16 item = drop->item_0a;
        if (item >= LANDING_SOUND_FIRST && item <= LANDING_SOUND_LAST) {
            SoundEmitter_PlayB(DroppedItem_sound(drop), SOUND_LANDING, SOUND_VOLUME, 0);
        }
    }
    drop->position.y = drop->target.y;
    if (drop->bounces == 0) {
        drop->bounces = 1;
        drop->velocity.y = BOUNCE_RISE;
        drop->velocity.x = (fx32) ((u32) drop->velocity.x * BOUNCE_KEEP) >> 12;
        drop->velocity.z = (fx32) ((u32) drop->velocity.z * BOUNCE_KEEP) >> 12;
    } else {
        drop->velocity.x = 0;
        drop->velocity.y = 0;
        drop->velocity.z = 0;
        DroppedItem_Finish(drop);
    }
}
CLEAN_AS(func_ov004_0223383c, DroppedItem_Fly)

/* func_ov004_02233918: the flight from `from` to `to` (rising at 1.5 over 12 frames when `to`
 * is above the ground, else at 1.0 over 9), flat to start with; thrown with a sound unless
 * the item is of kind 3 or 4.
 * QUIRK: the centre of `tile` is worked out and not used. */
void DroppedItem_Launch(DroppedItem *drop, const TileChangesTile *tile, const Vec3 *from, const Vec3 *to, u16 item)
{
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    if (to->y == 0) {
        fx32 z = (to->z - from->z) / FLIGHT_FRAMES;
        drop->velocity.x = (to->x - from->x) / FLIGHT_FRAMES;
        drop->velocity.y = FLIGHT_RISE;
        drop->velocity.z = z;
    } else {
        fx32 z = (to->z - from->z) / FLIGHT_FRAMES_HIGH;
        drop->velocity.x = (to->x - from->x) / FLIGHT_FRAMES_HIGH;
        drop->velocity.y = FLIGHT_RISE_HIGH;
        drop->velocity.z = z;
    }
    drop->item = item;
    drop->item_0a = item;
    drop->position = *from;
    drop->scale.x = 0;
    drop->scale.y = ONE;
    drop->scale.z = 0;
    switch (ITEM_KIND(item)) {
        case 3:
        case 4:
            drop->unk_8e = 0;
            break;
        default:
            SoundEmitter_PlayB(DroppedItem_sound(drop), SOUND_THROWN, SOUND_VOLUME, 0);
            break;
    }
}
CLEAN_AS(func_ov004_02233918, DroppedItem_Launch)

/* func_ov004_022339e0: the item's tile change finished and its place freed. */
void DroppedItem_Finish(DroppedItem *drop)
{
    DroppedItem_FinishTile(drop);
    drop->state = DROPPED_ITEM_FREE;
    drop->landed = 1;
    drop->item = DROPPED_ITEM_NONE;
    drop->item_0a = DROPPED_ITEM_NONE;
}
CLEAN_AS(func_ov004_022339e0, DroppedItem_Finish)

/* func_ov004_02233a00: the place set for the player's item; unless it is `landed` its flight
 * starts. */
void DroppedItem_Set(DroppedItem *drop, int player, const TileChangesTile *tile, const Vec3 *from, const Vec3 *to, int landed,
                     u16 item, AcreMap *map, short unk_48, u8 layer)
{
    (void) map;
    drop->player = player;
    drop->state = DROPPED_ITEM_SET;
    drop->landed = landed;
    drop->tile = *tile;
    drop->target = *to;
    drop->unk_48 = unk_48;
    drop->unk_4a = 0;
    drop->unk_8e = 1;
    drop->tile_pending = 1;
    drop->layer = layer;
    drop->frames = 0;
    drop->bounces = 0;
    if (landed == 0) {
        TileChangesTile at = *tile;
        Vec3 start = *from;
        Vec3 end = *to;
        DroppedItem_Launch(drop, &at, &start, &end, item);
    }
}
CLEAN_AS(func_ov004_02233a00, DroppedItem_Set)

/* func_ov004_02233aa4: the tile change waiting for the item finished, once. */
void DroppedItem_FinishTile(DroppedItem *drop)
{
    if (drop->tile_pending) {
        drop->tile_pending = 0;
        TileChangesTile tile = drop->tile;
        TileChanges_FinishAtTile(&tile, drop->layer);
    }
}
CLEAN_AS(func_ov004_02233aa4, DroppedItem_FinishTile)

/* func_ov004_02233ad4: `item` put on the town map at tile (x, z) of `layer`.
 * QUIRK: whether the scene is scene 0 is asked and not used. */
void DroppedItems_PutOnMap(int x, int z, u16 item, int layer)
{
    SceneQuery_CurrentIs0();
    AcreMap *map = data_021c80bc;
    if (map != NULL) {
        u16 code = item;
        AcreTile_SetItem(map, &code, x, z, (u8) layer);
    }
}
CLEAN_AS(func_ov004_02233ad4, DroppedItems_PutOnMap)

/* func_ov004_02233ba8: `item` dropped by this console's player (player 0 unless linked) from
 * where it stands to `to`; whether it could be (it needs the town's map and the player). */
int DroppedItems_DropFromLocalPlayer(const u16 *item, const Vec3 *to)
{
    AcreMap *map = data_021c80bc;
    Actor *actor = SessionPlayers_ActorOf(4);
    if (map == NULL || actor == NULL) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    int player = Session_IsLinked(session) ? session->local_slot : 0;
    Vec3 from = actor->position;
    Vec3 end = *to;
    return DroppedItems_DropFrom(player, *item, &from, &end, 0) != 0;
}
CLEAN_AS(func_ov004_02233ba8, DroppedItems_DropFromLocalPlayer)

/* func_ov004_02233fd8 (the array's destructor, handed to the C++ runtime at start): each
 * place's destructor (DroppedItem_Destruct, the game's), last first. */
DroppedItem *DroppedItems_Destruct(DroppedItem *items)
{
    __cxa_vec_cleanup(items, DROPPED_ITEMS, sizeof(DroppedItem), func_ov004_02233ff4);
    return items;
}
CLEAN_AS(func_ov004_02233fd8, DroppedItems_Destruct)

/* func_ov004_02233ff4: a place's destructor: its sound emitter's. */
DroppedItem *DroppedItem_Destruct(DroppedItem *drop)
{
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) drop->sound);
    return drop;
}
CLEAN_AS(func_ov004_02233ff4, DroppedItem_Destruct)

/* func_ov004_02234008: a place's constructor: tile (0, 0) and its sound emitter. */
DroppedItem *DroppedItem_Construct(DroppedItem *drop)
{
    drop->tile.x = 0;
    drop->tile.z = 0;
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) drop->sound);
    return drop;
}
CLEAN_AS(func_ov004_02234008, DroppedItem_Construct)
