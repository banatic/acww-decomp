/* The room objects that show a player's design (room_object_player_design.h). */
#include "room_object_player_design.h"

#include <stdint.h>

#include "clean.h"
#include "main/design_assets.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "main/g3d_resource.h"
#include "main/item_code.h"
#include "main/material_bind.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"

static_assert(offsetof(PlayerDesignObject, cleared_node) == 0x844, "cleared node");
static_assert(sizeof(PlayerDesignObject) == 0x848, "the size PlayerDesignObject_Create allocates");

#define PLAYER_DESIGN_OBJECT_SIZE 0x848
#define PLAYER_DESIGN_NO_NODE (-1)
#define PLAYER_DESIGN_RANGES 4
#define PLAYER_DESIGN_RANGE_CODES 0x80 /* 4 players by 8 designs by 4 variants */
#define PLAYER_DESIGNS_PER_PLAYER 8

/* The first codes of the four ranges, in the order they are tried (any: they do not overlap). */
static const u16 player_design_first[PLAYER_DESIGN_RANGES] = {0x3d84, 0x3ea4, 0x4224, 0x3f24};

/* "w", the material the design goes on, and the nodes "g" and "b". */
extern const char data_ov004_022531c8[];
extern const char data_ov004_022531cc[];
extern const char data_ov004_022531d0[];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251ff0[];
extern const u8 data_ov004_0225209c[];

/* func_ov004_02213b70 (vtable slot 0x64, the model's hook for a node): for the cleared node,
 * sets the word the state points to to 0. */
void PlayerDesignObject_NodeHook(PlayerDesignObject *object, int node, G3dRenderState *state)
{
    if (node == object->cleared_node) {
        *state->visible = 0;
    }
}
CLEAN_AS(func_ov004_02213b70, PlayerDesignObject_NodeHook)

/* func_ov004_02213b88 (vtable slot 0x0c) */
int PlayerDesignObject_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02213b88, PlayerDesignObject_Vfunc0C)

/* func_ov004_02213b8c (vtable slot 0x80, each frame while neither appearing nor vanishing) */
int PlayerDesignObject_Update(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02213b8c, PlayerDesignObject_Update)

/* func_ov004_02213b90 (vtable slot 0x7c, once the model is bound): which design the item code
 * shows (player 0's first for a code outside the ranges); the node to clear, when the player
 * has a record; and the player's texture of the design on "w". Done at once. */
int PlayerDesignObject_Start(PlayerDesignObject *object)
{
    u16 item = ItemCode_MakeVariant(RoomObject_Number(&object->base), 0);
    object->cleared_node = PLAYER_DESIGN_NO_NODE;
    int design = 0;
    for (int i = 0; i < PLAYER_DESIGN_RANGES; i++) {
        if (item >= player_design_first[i] && item < player_design_first[i] + PLAYER_DESIGN_RANGE_CODES) {
            design = (item - player_design_first[i]) >> 2;
            break;
        }
    }
    int player = (design / PLAYER_DESIGNS_PER_PLAYER) & (DESIGN_PLAYERS - 1);
    int index = design % PLAYER_DESIGNS_PER_PLAYER;
    u8 *record = PlayerRecords_Get(player);
    if (record != NULL) {
        if (PlayerId_Byte1c((const s8 *) PlayerRecord_Player(record)) == 0) {
            object->cleared_node = G3dRes_NodeIndex((const u8 *) object->base.model_resource, data_ov004_022531cc);
        } else {
            object->cleared_node = G3dRes_NodeIndex((const u8 *) object->base.model_resource, data_ov004_022531d0);
        }
    }
    DesignManager *designs = (DesignManager *) (uintptr_t) DesignManager_Get();
    int texture = DesignManager_PlayerTexture(designs, (u8) player, (u8) index);
    MaterialBind_BindByIndex((u8 *) object->base.model_resource, data_ov004_022531c8, (G3dResTex *) (uintptr_t) texture, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_02213b90, PlayerDesignObject_Start)

static void PlayerDesignObject_set_vtables(PlayerDesignObject *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02251ff0;
    object->base.receiver_vtable = data_ov004_0225209c;
}

/* func_ov004_02213ce0 (the deleting destructor, vtable slot 0x44) */
PlayerDesignObject *PlayerDesignObject_Delete(PlayerDesignObject *object)
{
    PlayerDesignObject_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02213ce0, PlayerDesignObject_Delete)

/* func_ov004_02213d0c (the destructor, vtable slot 0x40) */
PlayerDesignObject *PlayerDesignObject_Destroy(PlayerDesignObject *object)
{
    PlayerDesignObject_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02213d0c, PlayerDesignObject_Destroy)

/* func_ov004_02213d30 (the constructor). Its node is left as the allocation zeroed it until the
 * start sets it. */
PlayerDesignObject *PlayerDesignObject_Construct(PlayerDesignObject *object)
{
    RoomObject_ConstructBase(&object->base);
    PlayerDesignObject_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02213d30, PlayerDesignObject_Construct)

/* func_ov004_02213d54: a new one from the room's heap; nothing when it has no room. */
void PlayerDesignObject_Create(void)
{
    PlayerDesignObject *object = RoomObject_Alloc(PLAYER_DESIGN_OBJECT_SIZE);
    if (object != NULL) {
        PlayerDesignObject_Construct(object);
    }
}
CLEAN_AS(func_ov004_02213d54, PlayerDesignObject_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters PlayerDesignObject's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static PlayerDesignObject *PlayerDesignObject_from_receiver(void *receiver)
{
    return (PlayerDesignObject *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a9c4: the deleting destructor, entered from the receiver part. */
PlayerDesignObject *PlayerDesignObjectReceiver_Delete(void *receiver)
{
    return PlayerDesignObject_Delete(PlayerDesignObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251ff0D0Ev, PlayerDesignObjectReceiver_Delete)

/* func_ov004_0221a9e0: the destructor, entered from the receiver part. */
PlayerDesignObject *PlayerDesignObjectReceiver_Destroy(void *receiver)
{
    return PlayerDesignObject_Destroy(PlayerDesignObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251ff0D1Ev, PlayerDesignObjectReceiver_Destroy)
