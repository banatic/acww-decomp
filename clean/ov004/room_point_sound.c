/* The sounds of the room object on the floor at a point (room_point_sound.h). */
#include "room_point_sound.h"

#include <stddef.h>

#include "clean.h"
#include "room_object.h"
#include "room_object_anims.h"
#include "room_object_methods.h"
#include "room_objects.h"

#define LAYER_FLOOR 0

/* The object on the floor at `point` when it is of kind 0x36 or 0x37, else NULL. */
static RoomObject *RoomPointSound_object(Vec3 *point)
{
    RoomObject *object = RoomObjects_GridObjectAtPoint(RoomObjects_Grid(), point, LAYER_FLOOR);
    if (object != NULL && RoomObject_Unk00CIs36Or37(object) != 0) {
        return object;
    }
    return NULL;
}

/* func_ov004_0223a6ac: the object's sound at 4. */
void RoomPointSound_Play2(Vec3 *point)
{
    RoomObject *object = RoomPointSound_object(point);
    if (object != NULL) {
        RoomObject_PlaySound2(object);
    }
}
CLEAN_AS(func_ov004_0223a6ac, RoomPointSound_Play2)

/* func_ov004_0223a6d8: the object's sound at 0. */
void RoomPointSound_Play0(Vec3 *point)
{
    RoomObject *object = RoomPointSound_object(point);
    if (object != NULL) {
        RoomObject_PlaySound0(object);
    }
}
CLEAN_AS(func_ov004_0223a6d8, RoomPointSound_Play0)

/* func_ov004_0223a704: the object's sound at 2. */
void RoomPointSound_Play1(Vec3 *point)
{
    RoomObject *object = RoomPointSound_object(point);
    if (object != NULL) {
        RoomObject_PlaySound1(object);
    }
}
CLEAN_AS(func_ov004_0223a704, RoomPointSound_Play1)
