/* The indoor room's own object (data_ov004_022595c0 while a room is set up: set by its start,
 * func_ov004_0223d434, and cleared by its end, func_ov004_0223d354), as far as it is known
 * here: what its televisions show, its furniture mover, and a flag the TV's sound reads. */
#ifndef CLEAN_OV004_ROOM_MANAGER_H
#define CLEAN_OV004_ROOM_MANAGER_H

#include "furniture_mover.h"
#include "tv_broadcast.h"
#include "types.h"

/* The bytes of the room's furniture mover (FurnitureMover, whose model is a plain animated
 * model, shorter than the AnimatedModel structure). */
#define ROOM_MANAGER_MOVER_SIZE 0xe4

typedef struct RoomManager {
    u8 unk_000[0x64];
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

#endif
