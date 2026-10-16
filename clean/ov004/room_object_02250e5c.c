/* The room objects of vtable 0x02250e5c (room_object_02250e5c.h). */
#include "room_object_02250e5c.h"

#include "clean.h"

static_assert(offsetof(RoomObject02250e5c, unk_846) == 0x846, "unk_846");

/* func_ov004_02212764 (vtable slot 0x88): drawn once unk_846 is 2 or more. */
int RoomObject02250e5c_CanDraw(RoomObject02250e5c *object)
{
    return object->unk_846 >= 2;
}
CLEAN_AS(func_ov004_02212764, RoomObject02250e5c_CanDraw)

/* func_ov004_02212778 (vtable slot 0x0c) */
int RoomObject02250e5c_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02212778, RoomObject02250e5c_Vfunc0C)
