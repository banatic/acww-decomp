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

#endif
