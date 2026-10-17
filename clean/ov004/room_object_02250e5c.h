/* The room's floor: a class of overlay 4's room objects (vtable 0x02250e5c, receiver part
 * 0x02250f08, 0x870 bytes) whose model has a material named "m_dummy_floor". Once its model is
 * bound it keeps the word at 0x10 of data_ov004_022596b0 (func_ov004_0223d03c,
 * func_ov004_0223d2ac), loads the carpet it names (item 0x1144 plus it, 0x1144 when it is 0x44
 * or more) into the room's floor texture file (func_ov004_0223d044, func_0203cb3c) and puts that
 * texture on the material. It is drawn from the second frame after that on. The twin class for
 * the wall is room_object_022511e0.h. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02250E5C_H
#define CLEAN_OV004_ROOM_OBJECT_02250E5C_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02250e5c {
    RoomObject base;
    u16 unk_844; /* func_ov004_0223d2ac of data_ov004_022596b0: the carpet's number */
    u8 unk_846;  /* frames since the carpet was put on, up to 2; drawn from 2 on */
    u8 unk_847;
    /* Puts a texture on a material of the model (built by func_020b9e58, filled by
     * func_020b9d3c). */
    u8 material_texture[0x28];
} RoomObject02250e5c;

int RoomObject02250e5c_CanDraw(RoomObject02250e5c *object);
int RoomObject02250e5c_Vfunc0C(void);
int RoomObject02250e5c_Update(RoomObject02250e5c *object);
int RoomObject02250e5c_Start(RoomObject02250e5c *object);
RoomObject02250e5c *RoomObject02250e5c_Delete(RoomObject02250e5c *object);
RoomObject02250e5c *RoomObject02250e5c_Destroy(RoomObject02250e5c *object);
RoomObject02250e5c *RoomObject02250e5c_Construct(RoomObject02250e5c *object);
void RoomObject02250e5c_Create(void);

RoomObject02250e5c *RoomObject02250e5cReceiver_Delete(void *receiver);
RoomObject02250e5c *RoomObject02250e5cReceiver_Destroy(void *receiver);

#endif
