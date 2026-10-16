/* A class of overlay 4's room objects (vtable 0x02252374, receiver part 0x02252420, 0x878 bytes,
 * class number 0x1b in RoomObject.unk_780) for the room items 0x3984-0x3d83 (four codes,
 * variants, an item). Once its model is bound it loads, from the room's heap, a copy of the
 * model of the item those codes convert to (func_02061e2c: 0x11a8 and on, the design item's
 * model and those after it), and puts a texture on its own model's material "w" by its state
 * (RoomObject02252374.state, through tables of member pointers, member_pointer.h):
 *
 * - ON (0): its switch on, every frame; the texture of the loaded model;
 * - OFF (1): its switch off, every frame; the texture "myD" of its own texture file.
 *
 * Its start enters the state the switch says, then ON in any case (QUIRK, see
 * RoomObject02252374_Start). Others turn it on or off by requesting the state for the object at
 * its cell (func_0205265c, through func_ov004_0223b364 and func_ov004_0223b3c0). */
#ifndef CLEAN_OV004_ROOM_OBJECT_02252374_H
#define CLEAN_OV004_ROOM_OBJECT_02252374_H

#include "types.h"

#include "main/design_assets.h" /* DesignModel */
#include "room_object.h"

typedef struct RoomObject02252374 {
    RoomObject base;
    DesignModel *item_model; /* the item's model, NULL until the start loads it */
    /* Puts a texture on a material of the model (built by func_020b9e58, filled by
     * func_020b9d3c). */
    u8 material_texture[0x28];
    u8 unk_870; /* cleared when OFF's texture went on */
    u8 unk_871;
    u8 unk_872;
    u8 starting; /* set while the start runs */
    u8 state;    /* RoomObject02252374State */
    u8 unk_875[3];
} RoomObject02252374;

enum RoomObject02252374State {
    ROOM_OBJECT_02252374_ON = 0,
    ROOM_OBJECT_02252374_OFF = 1,
    ROOM_OBJECT_02252374_STATE_COUNT = 2
};

void RoomObject02252374_UpdateOff(RoomObject02252374 *object);
int RoomObject02252374_EnterOff(RoomObject02252374 *object);
void RoomObject02252374_UpdateOn(RoomObject02252374 *object);
int RoomObject02252374_EnterOn(RoomObject02252374 *object);
void RoomObject02252374_UpdateState(RoomObject02252374 *object);
int RoomObject02252374_EnterState(RoomObject02252374 *object, unsigned int state, int value);
u8 RoomObject02252374_StateIsOn(RoomObject02252374 *object, unsigned int state);
int RoomObject02252374_RequestOff(RoomObject02252374 *object);
int RoomObject02252374_RequestOn(RoomObject02252374 *object);
int RoomObject02252374_KeepsTextureCopy(void);
int RoomObject02252374_Vfunc0C(void);
int RoomObject02252374_Update(RoomObject02252374 *object);
int RoomObject02252374_Start(RoomObject02252374 *object);
RoomObject02252374 *RoomObject02252374_Delete(RoomObject02252374 *object);
RoomObject02252374 *RoomObject02252374_Destroy(RoomObject02252374 *object);
RoomObject02252374 *RoomObject02252374_Construct(RoomObject02252374 *object);
void RoomObject02252374_Create(void);

#endif
