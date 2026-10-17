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

/* The player's actor (func_020961a8). */
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

/* The table of the room's objects. */
extern void *func_ov004_0223ce84(void);
extern RoomObject *func_ov004_0223cd58(void *objects, unsigned int index);

static RoomObject *room_object(unsigned int index)
{
    return func_ov004_0223cd58(func_ov004_0223ce84(), index);
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
