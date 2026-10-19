/* A class of overlay 4's room objects (vtable 0x02251ff0, receiver part 0x0225209c, 0x848 bytes)
 * that shows one of the players' designs (design_assets.h): the room items of the four ranges
 * of design.c's room codes, eight designs a player, four codes (variants) a design. Once the
 * model is bound the player's texture of that design is put on the model's material "w", and
 * one of the model's nodes, "g" or "b" as byte 0x1c of the player's identity
 * (PlayerId_Byte1c) is 0 or not, has its node hook's word set to 0. */
#ifndef CLEAN_OV004_ROOM_OBJECT_PLAYER_DESIGN_H
#define CLEAN_OV004_ROOM_OBJECT_PLAYER_DESIGN_H

#include "main/g3d_render.h"
#include "types.h"

#include "room_object.h"
#include "room_object_methods.h"

typedef struct PlayerDesignObject {
    RoomObject base;
    s32 cleared_node; /* "g" or "b"; -1 when the player has no record */
} PlayerDesignObject;

void PlayerDesignObject_NodeHook(PlayerDesignObject *object, int node, G3dRenderState *state);
int PlayerDesignObject_Vfunc0C(void);
int PlayerDesignObject_Update(void);
int PlayerDesignObject_Start(PlayerDesignObject *object);
PlayerDesignObject *PlayerDesignObject_Delete(PlayerDesignObject *object);
PlayerDesignObject *PlayerDesignObject_Destroy(PlayerDesignObject *object);
PlayerDesignObject *PlayerDesignObject_Construct(PlayerDesignObject *object);
void PlayerDesignObject_Create(void);
PlayerDesignObject *PlayerDesignObjectReceiver_Delete(void *receiver);
PlayerDesignObject *PlayerDesignObjectReceiver_Destroy(void *receiver);

#endif
