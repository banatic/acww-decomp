/* The indoor room's own object (data_ov004_022595c0 while a room is set up: set by its start,
 * RoomManager_Init, and cleared by its end, RoomManager_Release), as far as it is known
 * here: what its televisions show, its furniture mover, and a flag the TV's sound reads.
 *
 * It is a process (vtable data_ov004_02256018 on the Process base, 0x2b4 bytes; created by
 * RoomManager_New): slot 0 starts the room (RoomManager_Init), slot 3 ends it
 * (RoomManager_Release), slot 6 is its frame (RoomManager_Update) and slot 9 its draw, which
 * does nothing. The room's start also sets up the table of its objects and their heap
 * (room_objects.h), the record of pushes (room_pushes.h), the model pool of its objects
 * (data_ov004_02259698, given the Shift-JIS name "kagu manager", furniture manager) and the
 * files of the item shown (room_preview.h). */
#ifndef CLEAN_OV004_ROOM_MANAGER_H
#define CLEAN_OV004_ROOM_MANAGER_H

#include "autoload_2/process.h"
#include "furniture_mover.h"
#include "room_sound.h"
#include "tv_broadcast.h"
#include "types.h"

/* The bytes of the room's furniture mover (FurnitureMover, whose model is a plain animated
 * model, shorter than the AnimatedModel structure). */
#define ROOM_MANAGER_MOVER_SIZE 0xe4

typedef struct RoomManager {
    Process process;                   /* 0x000 */
    RoomSoundList sounds;              /* 0x050 */
    TvBroadcast tv;                    /* 0x064 */
    u8 mover[ROOM_MANAGER_MOVER_SIZE]; /* 0x1c4: a FurnitureMover */
    u8 unk_2a8[8];                     /* 0x2a8 */
    u8 broadcast_changed;              /* 0x2b0: set when the TV shows a new programme or forecast */
} RoomManager;

FurnitureMover *RoomManager_Mover(void);
int RoomManager_BroadcastChanged(void);
void RoomManager_SetBroadcastChanged(void);

/* What the TV's sound kept of the frame before (RoomManager.unk_2a8, set up by the room's
 * start, func_ov004_0223d434: 0, 1 and 0). */
typedef struct RoomTvSoundState {
    u8 told;   /* 0x2a8: the sound has been silenced or raised once */
    u8 silent; /* 0x2a9: no TV that is on was near the player */
    u8 pad_2aa[2];
    int channel; /* 0x2ac: the channel shown (RoomManager_TvChannel) */
} RoomTvSoundState;

int RoomManager_TvFrame(void);
int RoomManager_TvLoops(void);
int RoomManager_TvSound(void);
short RoomManager_TvChannel(void);
int RoomManager_TvTexture(void);
void RoomManager_UpdateTvSound(RoomManager *room);
void RoomManager_MarkNearestClock(RoomManager *room);
void RoomManager_MarkNearestStriker(RoomManager *room);
void RoomManager_PlaceMapFurniture(RoomManager *room);
void RoomManager_StartStub(RoomManager *room);
unsigned short RoomManager_FrameCounter(void);

RoomSoundList *RoomManager_SoundList(void);
void RoomManager_SetShopMode(void);
unsigned char RoomManager_ShopMode(void);
int RoomManager_Release(RoomManager *room);
int RoomManager_Draw(void);
int RoomManager_Update(RoomManager *room);
int RoomManager_Init(RoomManager *room);
RoomManager *RoomManager_Delete(RoomManager *room);
RoomManager *RoomManager_Destruct(RoomManager *room);
RoomManager *RoomManager_Construct(RoomManager *room);
void RoomManager_New(void);

#endif
