/* A class of overlay 4's room objects (vtable 0x02250e5c, receiver part 0x02250f08) that is
 * drawn only once unk_846 has reached 2. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02250E5C_H
#define CLEAN_OV004_ROOM_OBJECT_02250E5C_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02250e5c {
    RoomObject base;
    u16 unk_844;
    u8 unk_846; /* drawn from 2 on */
} RoomObject02250e5c;

int RoomObject02250e5c_CanDraw(RoomObject02250e5c *object);
int RoomObject02250e5c_Vfunc0C(void);

#endif
