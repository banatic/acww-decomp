/* The indoor room's own object (room_manager.h). */
#include "room_manager.h"

#include "clean.h"
#include "itcm/vector.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/item_code.h"
#include "main/session_players.h"
#include "main/sound_object.h"
#include "room_object_map.h"
#include "room_objects.h"
#include "tv.h"

#include "autoload_2/heap.h"
#include "main/backup_card.h"
#include "main/model_pool.h"
#include "main/scene_kinds.h"
#include "main/scene_query.h"
#include "room_preview.h"
#include "room_pushes.h"

static_assert(offsetof(RoomManager, tv) == 0x064, "TV broadcast");
static_assert(offsetof(RoomManager, mover) == 0x1c4, "furniture mover");
static_assert(offsetof(RoomManager, broadcast_changed) == 0x2b0, "broadcast changed");

/* The room, NULL while none is set up. */
extern RoomManager *data_ov004_022595c0;

/* func_ov004_0223b22c: the room's furniture mover, NULL without a room. */
FurnitureMover *RoomManager_Mover(void)
{
    RoomManager *room = data_ov004_022595c0;
    if (room != NULL) {
        return (FurnitureMover *) (void *) room->mover;
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223b22c, RoomManager_Mover)

/* func_ov004_0223b258: 0 without a room. */
int RoomManager_BroadcastChanged(void)
{
    if (data_ov004_022595c0 != NULL) {
        return data_ov004_022595c0->broadcast_changed;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b258, RoomManager_BroadcastChanged)

/* func_ov004_0223b274 */
void RoomManager_SetBroadcastChanged(void)
{
    if (data_ov004_022595c0 != NULL) {
        data_ov004_022595c0->broadcast_changed = 1;
    }
}
CLEAN_AS(func_ov004_0223b274, RoomManager_SetBroadcastChanged)

/* ---- The TV's picture and sound, and what the room does with its objects each frame. */

static_assert(offsetof(RoomManager, unk_2a8) == 0x2a8, "TV sound state");
static_assert(offsetof(RoomObject, sound.position) == 0x7b8, "object's sound point");

/* The player's actor (SessionPlayers_ActorOf). */
#define ROOM_MANAGER_PLAYER 4

/* Set by the room's start in a house's room or a scene of kind 11: the TV is heard. */
extern u8 data_ov004_022595b8;
/* The room's shared frame counter, counted 0 to 0x27 by the room's update. */
extern u16 data_ov004_022595bc;
/* The square of an acre's depth (set by the overlay's static initialisation): an object
 * farther from the player is never the nearest. */
extern s32 data_ov004_022595d8;
/* The point the TV's sound plays at when no TV is near. */
extern Vec3 data_021fbee8;
/* The town's map, the room being its only acre. */
extern AcreMap *data_021c80bc;

/* The tests of the objects looked for (room_object_methods.h), and the marks the nearest get
 * (clock.h). */
struct Clock;
int RoomObject_Unk00CIs3BOr3CAndOn(RoomObject *object);
int RoomObject_Check022111f0(RoomObject *object);
int RoomObject_SettledUnk780Is10(RoomObject *object);
struct Clock *Clock_MarkNearest(struct Clock *clock);
struct Clock *Clock_MarkNearestStriker(struct Clock *clock);

static RoomObject *room_object(unsigned int index)
{
    return RoomObjects_At(RoomObjects_Table(), index);
}

/* The objects nearest_object looks for. */
enum NearestKind { NEAREST_TV_ON, NEAREST_CLOCK, NEAREST_STRIKER };

static int is_kind(RoomObject *object, int kind)
{
    switch (kind) {
        case NEAREST_TV_ON:
            return RoomObject_Unk00CIs3BOr3CAndOn(object);
        case NEAREST_CLOCK:
            return RoomObject_Check022111f0(object);
        default:
            return RoomObject_SettledUnk780Is10(object);
    }
}

/* The index of the object of `kind` nearest to `from` (by its sound's point), nearer than an
 * acre's depth; ~0 for none.
 * QUIRK: the squared distance is cut to 32 bits. */
static unsigned int nearest_object(const Vec3 *from, int kind)
{
    unsigned int nearest = ~0u;
    s32 best = data_ov004_022595d8;
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        RoomObject *object = room_object(i);
        if (object == NULL || is_kind(object, kind) == 0) {
            continue;
        }
        Vec3 point = object->sound.position;
        s32 distance = (s32) Vec_DistanceSquared(&point, from);
        if (distance < best) {
            nearest = i;
            best = distance;
        }
    }
    return nearest;
}

/* func_ov004_0223b28c: the frame of the TV's picture (TvBroadcast_Frame), 0 without a room. */
int RoomManager_TvFrame(void)
{
    RoomManager *room = data_ov004_022595c0;
    if (room != NULL) {
        return TvBroadcast_Frame(&room->tv);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b28c, RoomManager_TvFrame)

/* func_ov004_0223b2ac: the times the picture's animation passed its frame 0
 * (TvBroadcast_Loops), 0xff without a room. */
int RoomManager_TvLoops(void)
{
    RoomManager *room = data_ov004_022595c0;
    if (room != NULL) {
        return TvBroadcast_Loops(&room->tv);
    }
    return 0xff;
}
CLEAN_AS(func_ov004_0223b2ac, RoomManager_TvLoops)

/* func_ov004_0223b2cc: the TV's sound object (TvBroadcast_Sound), 0 without a room. */
int RoomManager_TvSound(void)
{
    RoomManager *room = data_ov004_022595c0;
    if (room != NULL) {
        return TvBroadcast_Sound(&room->tv);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b2cc, RoomManager_TvSound)

/* func_ov004_0223b2ec: the channel shown (TvBroadcast_Channel, cut to 16 bits), -1 without a
 * room. */
short RoomManager_TvChannel(void)
{
    if (data_ov004_022595c0 != NULL) {
        return (short) TvBroadcast_Channel(&data_ov004_022595c0->tv);
    }
    return -1;
}
CLEAN_AS(func_ov004_0223b2ec, RoomManager_TvChannel)

/* func_ov004_0223b314: the texture of the TV's picture (TvBroadcast_Texture), 0 without a
 * room. */
int RoomManager_TvTexture(void)
{
    RoomManager *room = data_ov004_022595c0;
    if (room != NULL) {
        return TvBroadcast_Texture(&room->tv);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b314, RoomManager_TvTexture)

/* func_ov004_0223bdac: while the TV is heard (data_ov004_022595b8), the TV that is on nearest to
 * the player (RoomObject_Unk00CIs3BOr3CAndOn) is marked heard (Tv_SetHeard) and the TV's sound
 * plays at it, at the picture's frame. With none near, the sound is silenced once and plays
 * without a point. When a TV comes near, the first time, or when the channel changes, the
 * sound is raised: with 1 at the start of a new picture (frame at most 1, no loop yet,
 * RoomManager_BroadcastChanged), else with 0. */
void RoomManager_UpdateTvSound(RoomManager *room)
{
    if (data_ov004_022595b8 == 0) {
        return;
    }
    RoomTvSoundState *state = (RoomTvSoundState *) (void *) room->unk_2a8;
    int silent = 1;
    Vec3 at = data_021fbee8;
    MapActor *player = SessionPlayers_ActorOf(ROOM_MANAGER_PLAYER);
    if (player != NULL) {
        Vec3 from = player->position;
        unsigned int nearest = nearest_object(&from, NEAREST_TV_ON);
        if (nearest != ~0u) {
            RoomObject *tv = room_object(nearest);
            if (tv != NULL) {
                Tv_SetHeard((Tv *) (void *) tv);
                at = tv->sound.position;
                silent = 0;
            }
        }
    }
    SoundObject *sound = (SoundObject *) (uintptr_t) (u32) RoomManager_TvSound();
    if (sound != NULL) {
        if (silent) {
            if (state->silent == 0 || state->told == 0) {
                SoundObject_Silence(sound);
                state->told = 1;
            }
            SoundObject_UpdateAt(sound, RoomManager_TvFrame(), NULL);
        } else {
            if (state->silent != 0 || state->told == 0 || state->channel != RoomManager_TvChannel()) {
                int frame = RoomManager_TvFrame() - 1;
                if (frame < 0) {
                    frame = 0;
                }
                int fresh = RoomManager_TvLoops() == 0 && frame == 0 && RoomManager_BroadcastChanged() != 0;
                SoundObject_Raise(sound, fresh);
                state->told = 1;
            }
            SoundObject_UpdateAt(sound, RoomManager_TvFrame(), &at);
        }
    }
    state->silent = (u8) silent;
    state->channel = RoomManager_TvChannel();
}
CLEAN_AS(func_ov004_0223bdac, RoomManager_UpdateTvSound)

/* func_ov004_0223bf40: marks the clock nearest to the player that RoomObject_Check022111f0
 * accepts (Clock_MarkNearest). */
void RoomManager_MarkNearestClock(RoomManager *room)
{
    (void) room;
    MapActor *player = SessionPlayers_ActorOf(ROOM_MANAGER_PLAYER);
    if (player == NULL) {
        return;
    }
    Vec3 from = player->position;
    unsigned int nearest = nearest_object(&from, NEAREST_CLOCK);
    if (nearest != ~0u) {
        RoomObject *clock = room_object(nearest);
        if (clock != NULL) {
            Clock_MarkNearest((struct Clock *) (void *) clock);
        }
    }
}
CLEAN_AS(func_ov004_0223bf40, RoomManager_MarkNearestClock)

/* func_ov004_0223bfe0: the same for the striking clocks (RoomObject_SettledUnk780Is10,
 * Clock_MarkNearestStriker). */
void RoomManager_MarkNearestStriker(RoomManager *room)
{
    (void) room;
    MapActor *player = SessionPlayers_ActorOf(ROOM_MANAGER_PLAYER);
    if (player == NULL) {
        return;
    }
    Vec3 from = player->position;
    unsigned int nearest = nearest_object(&from, NEAREST_STRIKER);
    if (nearest != ~0u) {
        RoomObject *clock = room_object(nearest);
        if (clock != NULL) {
            Clock_MarkNearestStriker((struct Clock *) (void *) clock);
        }
    }
}
CLEAN_AS(func_ov004_0223bfe0, RoomManager_MarkNearestStriker)

/* func_ov004_0223c080: at the room's start, an object for every piece of furniture on the
 * room's acre of the map (an item code with a variant), layer 0 then 1, row by row
 * (RoomObjects_Place, mode 0). */
void RoomManager_PlaceMapFurniture(RoomManager *room)
{
    (void) room;
    AcreMap *map = data_021c80bc;
    AcreRecord *acre = NULL;
    if (map->acres_wide != 0 && map->acres_high != 0 && map->acres != NULL) {
        acre = (AcreRecord *) (void *) map->acres;
    }
    for (u32 layer = 0; layer < 2; layer++) {
        for (int z = 0; z < 16; z++) {
            for (int x = 0; x < 16; x++) {
                u16 *tile = AcreRecord_Tile(acre, (unsigned int) x, (unsigned int) z, layer);
                if (tile != NULL && ItemCode_HasVariant(tile)) {
                    int number = ItemCode_VariantItem(tile);
                    int side = ItemCode_Variant(tile);
                    RoomObjects_Place(x, z, number, side, (u8) layer, 0);
                }
            }
        }
    }
}
CLEAN_AS(func_ov004_0223c080, RoomManager_PlaceMapFurniture)

/* func_ov004_0223c108: called by the room's start; does nothing. */
void RoomManager_StartStub(RoomManager *room)
{
    (void) room;
}
CLEAN_AS(func_ov004_0223c108, RoomManager_StartStub)

/* func_ov004_0223c1e0: the room's shared frame counter (0 to 0x27). */
unsigned short RoomManager_FrameCounter(void)
{
    return data_ov004_022595bc;
}
CLEAN_AS(func_ov004_0223c1e0, RoomManager_FrameCounter)

/* ---- The room's process: its start, frame, end, and its construction */

static_assert(sizeof(Process) == 0x50, "room's process");
static_assert(offsetof(RoomManager, sounds) == 0x050, "room's sounds");
static_assert(sizeof(RoomManager) == 0x2b4, "room");

#define ROOM_MANAGER_SIZE 0x2b4
/* The frame counter counts 0 to this less one. */
#define ROOM_MANAGER_FRAME_PERIOD 0x28
/* The model pool's VRAM of each entry, and its heap (smaller in scenes of kind 20). */
#define ROOM_MANAGER_POOL_TEXTURE 0x2000
#define ROOM_MANAGER_POOL_PALETTE 0x80
#define ROOM_MANAGER_POOL_HEAP 0x1cc4
#define ROOM_MANAGER_POOL_HEAP_SMALL 0x1c00

/* Set in Nook's shops and scenes 0xa and 0xf (RoomObjects_InNookOrScene0AOr0F) by the room's
 * start, and when a villager of the flea market is in the room (flea_market_villager.c); the
 * room's objects read it (room_object_body.c, room_pushes.c). */
extern u8 data_ov004_022595b4;
/* The heap of the room's objects (room_objects.h). */
extern Heap *data_ov004_022595c4;
/* The model pool of the room's objects, and the name it is given. */
extern ModelPool data_ov004_02259698;
extern const char data_ov004_02256188[];
/* The game card's save memory. */
extern BackupCard data_021c8188;

/* The vtables: the process base's and the room's. */
extern const u32 data_020da13c[];
extern const u32 data_ov004_02256018[];

/* The model pool's heap hooks, handed to the pool: the game's (SceneHeaps_CreateOv004PoolC and
 * SceneHeaps_DestroyOv004PoolC in Clean). */
extern int func_0205ca98(int size, int parent);
extern void func_0205ca7c(void);

/* func_ov004_0223d028: the room's list of point sounds, NULL without a room. */
RoomSoundList *RoomManager_SoundList(void)
{
    if (data_ov004_022595c0 != NULL) {
        return &data_ov004_022595c0->sounds;
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223d028, RoomManager_SoundList)

/* func_ov004_0223d33c: sets data_ov004_022595b4 (a villager of the flea market is in). */
void RoomManager_SetShopMode(void)
{
    data_ov004_022595b4 = 1;
}
CLEAN_AS(func_ov004_0223d33c, RoomManager_SetShopMode)

/* func_ov004_0223d348 */
unsigned char RoomManager_ShopMode(void)
{
    return data_ov004_022595b4;
}
CLEAN_AS(func_ov004_0223d348, RoomManager_ShopMode)

/* func_ov004_0223d354 (vtable slot 3): the room's end: its sounds, furniture mover, TVs (where
 * the scene has room for more than one object), the item shown's files and the model pool are
 * released, the room is gone, the pushes are reset and the objects' heap deleted; 1. */
int RoomManager_Release(RoomManager *room)
{
    RoomSoundList_Release(&room->sounds);
    FurnitureMover_Release((FurnitureMover *) (void *) room->mover);
    if (RoomObjects_Capacity() > 1) {
        TvBroadcast_Release(&room->tv);
    }
    RoomPreview_FreeFiles(RoomPreview_Get());
    ModelPool_Destroy(&data_ov004_02259698);
    data_ov004_022595c0 = NULL;
    RoomPushes_Reset(RoomPushes_Records());
    RoomObjects_HeapDelete(&data_ov004_022595c4);
    return 1;
}
CLEAN_AS(func_ov004_0223d354, RoomManager_Release)

/* func_ov004_0223d3b0 (vtable slot 9): the draw; nothing to do. */
int RoomManager_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0223d3b0, RoomManager_Draw)

/* func_ov004_0223d3b4 (vtable slot 6): the room's frame: its sound list is started (once it
 * can be) and flushed, the frame counter goes on, the TVs follow their schedule and their sound
 * (where the scene has room for more than one object, the save memory is idle, and the scene
 * is neither of kinds 6 to 8 nor a session with other players), the nearest clocks are marked
 * and the pushes reset; 1. */
int RoomManager_Update(RoomManager *room)
{
    RoomSoundList_Start(&room->sounds);
    RoomSoundList_Flush(&room->sounds);
    data_ov004_022595bc = (u16) ((data_ov004_022595bc + 1) % ROOM_MANAGER_FRAME_PERIOD);
    if (RoomObjects_Capacity() > 1 && BackupCard_Status(&data_021c8188) == BACKUP_CARD_IDLE &&
        SceneKinds_CurrentIn6To8() == 0 && SceneKinds_CurrentIsSession() == 0) {
        TvBroadcast_FollowSchedule(&room->tv);
        RoomManager_UpdateTvSound(room);
        TvBroadcast_UpdateScreen(&room->tv);
    }
    RoomManager_MarkNearestClock(room);
    RoomManager_MarkNearestStriker(room);
    RoomPushes_Reset(RoomPushes_Records());
    return 1;
}
CLEAN_AS(func_ov004_0223d3b4, RoomManager_Update)

/* func_ov004_0223d434 (vtable slot 0): the room's start: the TV is heard in a house's room and
 * in scenes of kind 11; the TV's sound state and the broadcast's flag are cleared; the shop
 * mode is set by the scene; the objects' heap is made for the scene's number of objects; this
 * is the room; the objects' grid and the pushes are cleared; the model pool is made (one entry
 * per object); then the TVs (with room for more than one object), the furniture mover, the item
 * shown's files and the furniture of the room's map; 1. */
int RoomManager_Init(RoomManager *room)
{
    if (SceneKinds_CurrentIsHouseRoom() != 0 || SceneQuery_CurrentIn11() != 0) {
        data_ov004_022595b8 = 1;
    }
    RoomTvSoundState *state = (RoomTvSoundState *) (void *) room->unk_2a8;
    state->silent = 1;
    state->told = 0;
    state->channel = 0;
    room->broadcast_changed = 0;
    data_ov004_022595b4 = (u8) RoomObjects_InNookOrScene0AOr0F();
    RoomObjects_HeapCreate(&data_ov004_022595c4, RoomObjects_Capacity());
    data_ov004_022595c0 = room;
    RoomObjects_GridClear(RoomObjects_Grid());
    RoomPushes_Reset(RoomPushes_Records());
    int heap_size = ROOM_MANAGER_POOL_HEAP;
    if (SceneQuery_CurrentIn20() != 0) {
        heap_size = ROOM_MANAGER_POOL_HEAP_SMALL;
    }
    u32 count = (u32) RoomObjects_Capacity();
    ModelPool_Create(&data_ov004_02259698, count, ROOM_MANAGER_POOL_TEXTURE, ROOM_MANAGER_POOL_PALETTE, heap_size,
                     func_0205ca98, func_0205ca7c, (void *) (uintptr_t) data_ov004_02256188);
    RoomManager_StartStub(room);
    if (RoomObjects_Capacity() > 1) {
        TvBroadcast_Init(&room->tv);
    }
    FurnitureMover_Load((FurnitureMover *) (void *) room->mover);
    RoomPreview_AllocFiles(RoomPreview_Get());
    RoomManager_PlaceMapFurniture(room);
    return 1;
}
CLEAN_AS(func_ov004_0223d434, RoomManager_Init)

/* The destructor: the members in the reverse order, then the process. */
static void RoomManager_destruct(RoomManager *room)
{
    room->process.vtable = data_ov004_02256018;
    FurnitureMover_Destruct((FurnitureMover *) (void *) room->mover);
    TvBroadcast_Destruct(&room->tv);
    RoomSoundList_Destruct(&room->sounds);
    room->process.vtable = data_020da13c;
    Process_Destruct(&room->process);
}

/* func_ov004_0223d52c: the destructor that frees the room. */
RoomManager *RoomManager_Delete(RoomManager *room)
{
    RoomManager_destruct(room);
    Heap_FreeAux(room);
    return room;
}
CLEAN_AS(func_ov004_0223d52c, RoomManager_Delete)

/* func_ov004_0223d570 */
RoomManager *RoomManager_Destruct(RoomManager *room)
{
    RoomManager_destruct(room);
    return room;
}
CLEAN_AS(func_ov004_0223d570, RoomManager_Destruct)

/* func_ov004_0223d5b0: the constructor: the process, then the members. */
RoomManager *RoomManager_Construct(RoomManager *room)
{
    Process_Construct(&room->process);
    room->process.vtable = data_020da13c;
    room->process.vtable = data_ov004_02256018;
    RoomSoundList_Construct(&room->sounds);
    TvBroadcast_Construct(&room->tv);
    FurnitureMover_Construct((FurnitureMover *) (void *) room->mover);
    return room;
}
CLEAN_AS(func_ov004_0223d5b0, RoomManager_Construct)

/* func_ov004_0223d5ec: the class's create function: a zeroed room from the aux heap,
 * constructed. */
void RoomManager_New(void)
{
    RoomManager *room = Heap_AllocAuxZeroed(ROOM_MANAGER_SIZE);
    if (room != NULL) {
        RoomManager_Construct(room);
    }
}
CLEAN_AS(func_ov004_0223d5ec, RoomManager_New)
